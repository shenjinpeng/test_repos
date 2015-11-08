/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2010>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.

//----------------------------------------------------------------------------------------------------
// ID Code      : Flash.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __REALTEK_FLASH__

#include "Common\Header\Include.h"

#if(_OSD_TYPE == _REALTEK_OSD)

#if(_MEMORY_LOCATION == _FLASH)
//--------------------------------------------------
// Description  : Flash check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CFlashStartupCheck(void)
{
    bit  bNeedIntialFlash = _FALSE;
    bit  bNeedRecoverMISC = _FALSE;
    BYTE ucTemp = 0;

    // Check data at the end of Flash Space are Version Code and related info.
    if((MCU_FLASH[_FLASH_SPACE - 1] != 0xFF)
    && (MCU_FLASH[_FLASH_SPACE - 1] == _VERSION_CODE)
    && (MCU_FLASH[_FLASH_SPACE - 2] == _RTK_LOW_BYTE)
    && (MCU_FLASH[_FLASH_SPACE - 3] == _RTK_HIGH_BYTE)
    && (MCU_FLASH[_FLASH_SPACE - 4] == _RSL_LOW_BYTE)
    && (MCU_FLASH[_FLASH_SPACE - 5] == _RSL_HIGH_BYTE))
    {
        bNeedIntialFlash = _FALSE;
        bNeedRecoverMISC = _FALSE;
    }
    else if(MCU_FLASH[_FLASH_SPACE - 1] == 0xFF) // If the data at the end of Flash Space is 0xFF, not Version Code
    {
        // Find a free page which maybe store the Misc data & Version Code Info
        ucTemp = CFlashFreePageLocateAtStartup();

        if((ucTemp < (_END_PAGE - _START_PAGE + 1))
        && (MCU_FLASH[ucTemp * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR] == _VERSION_CODE)
        && (MCU_FLASH[ucTemp * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 1] == _RTK_LOW_BYTE)
        && (MCU_FLASH[ucTemp * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 2] == _RTK_HIGH_BYTE)
        && (MCU_FLASH[ucTemp * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 3] == _RSL_LOW_BYTE)
        && (MCU_FLASH[ucTemp * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 4] == _RSL_HIGH_BYTE))
        {
            bNeedIntialFlash = _FALSE;
            bNeedRecoverMISC = _TRUE;
        }
        else
        {
            bNeedIntialFlash = _TRUE;
            bNeedRecoverMISC = _FALSE;
        }
    }
    else
    {
        bNeedIntialFlash = _TRUE;
        bNeedRecoverMISC = _FALSE;
    }

    if(bNeedIntialFlash == _FALSE)
    {
        if(bNeedRecoverMISC == _TRUE)
        {
            // Recover MISC Data from the finded free page to _MISC_PAGE
            CFlashRecoverMISCPage(ucTemp);
        }

        // Initial some global variables,such as g_ucFlashPage, g_usFlashAddr, g_ulFlashMovePage, g_ucFlashFreePage
        CFlashInitialAddr();

        // Check End Tag existence in each page,if End Tag does not exist, load Default to each page
        for(ucTemp = 0; ucTemp < _NUMBER_OF_PAGES; ucTemp++)
        {
            CFlashCheckLoadDefault(ucTemp);
        }

        CEepromLoadSystemData();
        CEepromLoadOsdUserData();
        CEepromLoadAdcData();
        CEepromLoadBriConData();
        CEepromLoadColorTempData();

#if(_EDID_PRO == _ON)
        // Load EDID in _MISC_PAGE to DDCRAM
        CFlashLoadMISCPage2DDCRAM();
#elif(_EMBEDDED_EDID == _OFF)
        CFlashLoadDDCData();
#endif
    }
    else
    {
        // Initial each flash page content and page info field newly
        CFlashInitial();

#if(_EDID_PRO == _ON)
        // Load EDID in _MISC_PAGE to DDCRAM
        CFlashLoadMISCPage2DDCRAM();
#elif(_EMBEDDED_EDID == _OFF)
        CFlashLoadDDCData();
#endif
    }
}

//--------------------------------------------------
// Description  : Flash Initial
// Input Value  : None
// Output Value : Return _TURE if succeed
//--------------------------------------------------
bit CFlashInitial(void)
{
    BYTE cnt = 0;

    // Sector Erase _MISC_PAGE page
    if(CFlashErase(_MISC_PAGE) == _FALSE)
    {
        return _FALSE;
    }

    g_ulFlashMovePage = 0;

    // Initialize _MODE & _GLOBAL page content and page info field in each page
    for(cnt = 0; cnt < _NUMBER_OF_PAGES; cnt++)
    {
        CFlashInitialPage(cnt, (GET_ABSOLUTE_PAGE_NUM(cnt)));
    }

    // Load default content to ucPageID page
    CEepromLoadDefault();

    // Initial Misc page and load misc page default
    CFlashInitialPage(_MISC, _MISC_PAGE);
    CFlashLoadPageDefault(_MISC);

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
        CFlashWREN(_MISC_PAGE);
        MCU_FLASH[_FLASH_SPACE - 1] = _VERSION_CODE;
        CFlashWREN(_MISC_PAGE);
        MCU_FLASH[_FLASH_SPACE - 2] = _RTK_LOW_BYTE;
        CFlashWREN(_MISC_PAGE);
        MCU_FLASH[_FLASH_SPACE - 3] = _RTK_HIGH_BYTE;
        CFlashWREN(_MISC_PAGE);
        MCU_FLASH[_FLASH_SPACE - 4] = _RSL_LOW_BYTE;
        CFlashWREN(_MISC_PAGE);
        MCU_FLASH[_FLASH_SPACE - 5] = _RSL_HIGH_BYTE;
        CFlashWRDis();
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
        CFlashWREN(_MISC_PAGE);
        MCU_FLASH[_FLASH_SPACE - 1] = _VERSION_CODE;
        MCU_FLASH[_FLASH_SPACE - 2] = _RTK_LOW_BYTE;
        MCU_FLASH[_FLASH_SPACE - 3] = _RTK_HIGH_BYTE;
        MCU_FLASH[_FLASH_SPACE - 4] = _RSL_LOW_BYTE;
        MCU_FLASH[_FLASH_SPACE - 5] = _RSL_HIGH_BYTE;
        CFlashWRDis();
#endif
    }

    // Clear Buffer
    memset(g_ucFlashTemp, 0x00, sizeof(g_ucFlashTemp));

    g_ucFlashFreePage = _NUMBER_OF_PAGES; // The first free page right after initialization, is _NUMBER_OF_PAGES

    return _TRUE;
}

//--------------------------------------------------
// Description  : Initial a single page specified by
//                the input page ID
// Input Value  : Page ID, and the Free Page Index in Absolute Format
// Output Value : None
//--------------------------------------------------
void CFlashInitialPage(BYTE ucPageID, BYTE ucFreePage)
{
    // Sector erase the ucFreePage
    CFlashErase(ucFreePage);

    if(ucPageID != _MISC)
    {
        // Move Count
        g_ulFlashMovePage++;

        // Specify ucPageID's actual page index
        g_ucFlashPage[ucPageID] = GET_RELATIVE_PAGE_NUM(ucFreePage);
        g_usFlashAddr[ucPageID] = 0;

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
        if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
        {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
            CFlashWREN(ucFreePage);
            MCU_FLASH[(ucFreePage - _START_PAGE + 1) * _PAGE_SIZE - 1] = ucPageID;
            CFlashWREN(ucFreePage);
            MCU_FLASH[(ucFreePage - _START_PAGE + 1) * _PAGE_SIZE - 2] = (BYTE)g_ulFlashMovePage;
            CFlashWREN(ucFreePage);
            MCU_FLASH[(ucFreePage - _START_PAGE + 1) * _PAGE_SIZE - 3] = (BYTE)(g_ulFlashMovePage >> 8);
            CFlashWREN(ucFreePage);
            MCU_FLASH[(ucFreePage - _START_PAGE + 1) * _PAGE_SIZE - 4] = (BYTE)(g_ulFlashMovePage >> 16);
            CFlashWREN(ucFreePage);
            MCU_FLASH[(ucFreePage - _START_PAGE + 1) * _PAGE_SIZE - 5] = tFLASHSIZE[ucPageID];
            CFlashWREN(ucFreePage);
            MCU_FLASH[(ucFreePage - _START_PAGE + 1) * _PAGE_SIZE - 6] = (BYTE)(g_ulFlashMovePage >> 16) ^ (BYTE)(g_ulFlashMovePage >> 8) ^ (BYTE)g_ulFlashMovePage ^ tFLASHSIZE[ucPageID] ^ ucPageID;
            CFlashWRDis();
#endif
        }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
        else
#endif
        {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
            CFlashWREN(ucFreePage);
            MCU_FLASH[(ucFreePage - _START_PAGE + 1) * _PAGE_SIZE - 1] = ucPageID;
            MCU_FLASH[(ucFreePage - _START_PAGE + 1) * _PAGE_SIZE - 2] = (BYTE)g_ulFlashMovePage;
            MCU_FLASH[(ucFreePage - _START_PAGE + 1) * _PAGE_SIZE - 3] = (BYTE)(g_ulFlashMovePage >> 8);
            MCU_FLASH[(ucFreePage - _START_PAGE + 1) * _PAGE_SIZE - 4] = (BYTE)(g_ulFlashMovePage >> 16);
            MCU_FLASH[(ucFreePage - _START_PAGE + 1) * _PAGE_SIZE - 5] = tFLASHSIZE[ucPageID];
            MCU_FLASH[(ucFreePage - _START_PAGE + 1) * _PAGE_SIZE - 6] = (BYTE)(g_ulFlashMovePage >> 16) ^ (BYTE)(g_ulFlashMovePage >> 8) ^ (BYTE)g_ulFlashMovePage ^ tFLASHSIZE[ucPageID] ^ ucPageID;
            CFlashWRDis();
#endif
        }
    }
}

//--------------------------------------------------
// Description  : Flash Address Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CFlashInitialAddr(void)
{
    BYTE cnt = 0;
    BYTE ucPageIndex = 0;

    // Move Count
    g_ulFlashMovePage = 0;

    memset(g_usFlashAddr, 0x00, sizeof(g_usFlashAddr));

    // Find the page index which has the biggest move count value
    ucPageIndex = CFlashSearchPage();
    g_ulFlashMovePage = (((DWORD)(MCU_FLASH[(ucPageIndex + 1) * _PAGE_SIZE - 4]) << 16) | ((DWORD)(MCU_FLASH[(ucPageIndex + 1) * _PAGE_SIZE - 3]) << 8) | ((DWORD)(MCU_FLASH[(ucPageIndex + 1) * _PAGE_SIZE - 2])));

    // Find a free page index after the page which has the biggest move count value, save the value to g_ucFlashFreePage
    g_ucFlashFreePage = CFlashSearchFreePage(ucPageIndex);

    for(cnt = 0; cnt < _NUMBER_OF_PAGES; cnt++)
    {
        // If this page is missing, intial this single page
        if(g_ucFlashPage[cnt] == 0xFF)
        {
            // This function will increase g_ulFlashMovePage,and now g_ucFlashFreePage is the page index which has the biggest move count value
            CFlashInitialPage(cnt, GET_ABSOLUTE_PAGE_NUM(g_ucFlashFreePage));

            // Load default values for each page
            CFlashLoadPageDefault(cnt);

            // Find a new free page index after the page which has the biggest move count value
            g_ucFlashFreePage = CFlashSearchFreePage(g_ucFlashFreePage);
        }
        else
        {
            // Initial g_usFlashAddr[]
            g_usFlashAddr[cnt] = CFlashSearchPageAddr(cnt);
        }
    }
}

//--------------------------------------------------
// Description  : Search Valid Page from the Flash
// Input Value  : Buffer to save the search result
// Output Value : Return the relative page ID where the
//                largest move count lies
//--------------------------------------------------
BYTE CFlashSearchPage()
{
    BYTE i = 0;
    BYTE ucPageIndex = 0xFF;
    WORD usTemp = 0;
    DWORD ulMaxMoveCount = 0;

    memset(g_ucFlashPage, 0xFF, _NUMBER_OF_PAGES);

    for(i = 0; i < (_END_PAGE - _START_PAGE + 1); i++)
    {
        usTemp = (i + 1) * _PAGE_SIZE;

        if((MCU_FLASH[usTemp - 1] < _NUMBER_OF_PAGES) // Page Info, Page ID Code Field < _NUMBER_OF_PAGES
        && (MCU_FLASH[usTemp - 6] == (MCU_FLASH[usTemp - 5] ^ MCU_FLASH[usTemp - 4] ^ MCU_FLASH[usTemp - 3] ^ MCU_FLASH[usTemp - 2] ^ MCU_FLASH[usTemp - 1])) // Page Info, CheckSum field
        && (MCU_FLASH[usTemp - 5] == tFLASHSIZE[MCU_FLASH[usTemp - 1]])) // Page Info, Item Length Field
        {
            // Find the biggest move count value, and the page ID code which has the biggest move count value
            if((((DWORD)(MCU_FLASH[usTemp - 4]) << 16) | ((DWORD)(MCU_FLASH[usTemp - 3]) << 8) | ((DWORD)(MCU_FLASH[usTemp - 2]))) >= ulMaxMoveCount)
            {
                ulMaxMoveCount = (((DWORD)(MCU_FLASH[usTemp - 4]) << 16) | ((DWORD)(MCU_FLASH[usTemp - 3]) << 8) | ((DWORD)(MCU_FLASH[usTemp - 2])));
                ucPageIndex = i;
            }

            // If exists two page with the same page ID Code but with different move count value because of move page exception,
            // Find the right page which has the bigger move count value and upate the g_ucFlashPage
            if(g_ucFlashPage[MCU_FLASH[usTemp - 1]] != 0xFF)
            {
                if((((DWORD)(MCU_FLASH[usTemp - 4]) << 16) | ((DWORD)(MCU_FLASH[usTemp - 3]) << 8) | ((DWORD)(MCU_FLASH[usTemp - 2]))) >=
                   (((DWORD)(MCU_FLASH[(g_ucFlashPage[MCU_FLASH[usTemp - 1]] + 1) * _PAGE_SIZE - 4]) << 16) | ((DWORD)(MCU_FLASH[(g_ucFlashPage[MCU_FLASH[usTemp - 1]] + 1) * _PAGE_SIZE - 3]) << 8) | ((DWORD)(MCU_FLASH[(g_ucFlashPage[MCU_FLASH[usTemp - 1]] + 1) * _PAGE_SIZE - 2]))))
                {
                    g_ucFlashPage[MCU_FLASH[usTemp - 1]] = i;
                }
            }
            else
            {
                g_ucFlashPage[MCU_FLASH[usTemp - 1]] = i;
            }
        }
    }

    // Initial g_ucFlashPage[] with valid page index
    // Return the Page Index which has the biggest Move Count value
    return ucPageIndex;
}

//--------------------------------------------------
// Description  : Search Address of Page in Flash
// Input Value  : Number of Page (0 ~ 1)
// Output Value : Return address
//--------------------------------------------------
WORD CFlashSearchPageAddr(BYTE ucPageID)
{
    BYTE ucItemSize = 0;
    WORD cnt = 0;

    if((ucPageID >= 0) && (ucPageID < (_END_PAGE - _START_PAGE)))
    {
        // Item length
        ucItemSize = MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 5];

        // Find the last Data item address
        for(cnt = ((_PAGE_SIZE - _PAGE_INFO_LENGTH) / ucItemSize); cnt > 0; cnt--)
        {
            if(MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + (cnt - 1) * ucItemSize] != 0xFF)
            {
                return cnt;
            }
        }
    }
    else
    {
        return 0;
    }

    return 0;

}
//--------------------------------------------------
// Description  : Search Free Page of Flash
// Input Value  : Number of Page of Flash which has
//                the biggest move count
// Output Value : Free Page after the page with the
//                biggest move count value
//--------------------------------------------------
BYTE CFlashSearchFreePage(BYTE ucFreePage)
{
    SBYTE chPage = 0;

    // If the _END_PAGE page has the biggest move count, suppose first page is free page
    if(ucFreePage == (_END_PAGE - _START_PAGE))
    {
        ucFreePage = 0;
    }
    else // Otherwise suppose the next page is free page
    {
        ucFreePage += 1;
    }

    // Check the supposed free page is actual free page which has not been used ever
    do
    {
        if(ucFreePage == g_ucFlashPage[chPage])
        {
            if(ucFreePage == (_END_PAGE - _START_PAGE))
            {
                ucFreePage = 0;
            }
            else
            {
                ucFreePage += 1;
            }

            chPage = -1;
        }

        chPage++;
    }
    while(chPage < _NUMBER_OF_PAGES);

    return ucFreePage;
}

//--------------------------------------------------
// Description  : This function get a free page index from _START_PAGE to _END_PAGE
// Input Value  : None
// Output Value : The free page index
//--------------------------------------------------
BYTE CFlashFreePageLocateAtStartup(void)
{
    BYTE ucPageIndex = 0xFF;

    // Find the page index which has the biggest move count value
    ucPageIndex = CFlashSearchPage();

    if(ucPageIndex == 0xFF)
    {
        ucPageIndex = 0;
    }
    else
    {
        // Find a free page index after the page which has the biggest move count value
        ucPageIndex = CFlashSearchFreePage(ucPageIndex);
    }

    return ucPageIndex;
}

//--------------------------------------------------
// Description  : This function Load default values for the Mode Page
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CFlashLoadPageModeDefault(void)
{
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
    BYTE ucSourceTemp = 0;
#endif

    StructModeUserFIFODataType stFIFOModeTemp;

    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < (_MAX_FIFO_MODE_INDEX + 1)))
        {
            CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);
            stFIFOModeTemp.ModeNum = pData[(stModeInfo.ModeCurr % 4) * 4];
        }
    }

    CFlashStartLoadDefault(_MODE);
    CEepromInitialModeData();
    CEepromInitialUserFIFOModeData();
    CFlashFinishLoadDefault(_MODE);

    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        CEepromLoadModeData(stModeInfo.ModeCurr);
    }
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
#if(_FIFO_MODE_ONLY == _ON)

        if(stSystemData.UserFIFOMode >= _MAX_FIFO_MODE_INDEX)
        {
            stSystemData.UserFIFOMode = 0;
        }
        else
        {
            stSystemData.UserFIFOMode++;
        }

        g_ucFIFOModeNum = stSystemData.UserFIFOMode;

        if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
        {
            stFIFOModeTemp.ModeNum = stModeInfo.ModeCurr;
        }

        if(stFIFOModeTemp.ModeNum < _MAX_PRESET_MODE)
        {
            // Prepare FIFO Info
            stFIFOModeTemp.IHFreq = stModeInfo.IHFreq;
            stFIFOModeTemp.IVFreq = stModeInfo.IVFreq;

            CEepromSaveUserFIFOModeData(stFIFOModeTemp);

            // Prepare User Data and Center Data
            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();
            SET_COLOR_FORMAT_STATUS(_RGB_COLOR_FORMAT);

            stModeUserData.HPosition = tINPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHStartPos;
            stModeUserData.VPosition = tINPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IVStartPos;
            stModeUserData.Clock = tINPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHTotal;
            stModeUserData.Phase = 0;

            stModeUserCenterData.CenterHPos = tINPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHStartPos;
            stModeUserCenterData.CenterVPos = tINPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IVStartPos;
            stModeUserCenterData.CenterClock = tINPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHTotal;
            stModeUserCenterData.CenterPhase = 0;

            if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
            {
                stModeInfo.ModeCurr = stSystemData.UserFIFOMode;
            }

            CEepromSaveModeData(stModeInfo.ModeCurr);
        }

#else

        if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < (_MAX_FIFO_MODE_INDEX + 1)))
        {
            if(stSystemData.UserFIFOMode >= _MAX_FIFO_MODE_INDEX)
            {
                stSystemData.UserFIFOMode = 0;
            }
            else
            {
                stSystemData.UserFIFOMode++;
            }

            if(stFIFOModeTemp.ModeNum < _MAX_PRESET_MODE)
            {
                // Prepare FIFO Info
                stFIFOModeTemp.IHFreq = stModeInfo.IHFreq;
                stFIFOModeTemp.IVFreq = stModeInfo.IVFreq;

                CEepromSaveUserFIFOModeData(stFIFOModeTemp);

                // Prepare User Data and Center Data
                stModeUserData.FirstAuto = 0;
                stModeUserData.HPosition = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IHStartPos;
                stModeUserData.VPosition = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IVStartPos;
                stModeUserData.Clock = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IHTotal;
                stModeUserData.Phase = 0;

                stModeInfo.ModeCurr = stSystemData.UserFIFOMode;

                CEepromSaveModeData(stModeInfo.ModeCurr);
                CEepromLoadCenterModeData(stModeInfo.ModeCurr);
            }
        }
        else if((GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE) && (stModeInfo.ModeCurr < _MAX_PRESET_MODE))
        {
            CEepromLoadModeData(stModeInfo.ModeCurr);
            CEepromLoadCenterModeData(stModeInfo.ModeCurr);
        }

#endif
    }
}

//--------------------------------------------------
// Description  : Load Flash Default
// Input Value  : Enummed Page ID
// Output Value : None
//--------------------------------------------------
void CFlashLoadPageDefault(BYTE ucPageID)
{
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
    BYTE ucSourceTemp = 0;
#endif

    switch(ucPageID)
    {
        case _MODE:

            CFlashLoadPageModeDefault();

            break;

        case _GLOBAL:

            CFlashStartLoadDefault(_GLOBAL);

            CEepromLoadSystemDataDefault();
            CEepromLoadOsdUserDataDefault();
            CEepromLoadAdcDataDefault();
            CEepromLoadBriConDataDefault();
            CEepromLoadColorTempDataDefault();

            CFlashFinishLoadDefault(_GLOBAL);

#ifdef _SOURCE_SEARCH_TYPE_BY_OSD
#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
            SET_SOURCE_SEARCH_AUTO();
#endif
#endif

            //CEepromSaveSystemData();
            CEepromSaveOsdUserData();

            break;

        case _MISC:

            CFlashLoadMISCPageDefault();

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Load default settings for _MODE page and _GLOBAL page
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadDefault(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _NUMBER_OF_PAGES; ucTemp++)
    {
        CFlashLoadPageDefault(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Start for Load Eeprom default
// Input Value  : Enummed Page ID
// Output Value : None
//--------------------------------------------------
void CFlashStartLoadDefault(BYTE ucPageID)
{
    BYTE i = 0;

    g_ucFlashTemp[0] = _FLASH_INITIAL;

    for(i = _ITEM_ID_CODE_LENGTH; i < (tFLASHSIZE[ucPageID] - _ITEM_CHECKSUM_LENGTH); i++)
    {
        g_ucFlashTemp[i] = 0xFF;
    }

    CFlashSaveData(ucPageID, g_ucFlashTemp);
}

//--------------------------------------------------
// Description  : Start for Load Eeprom default
// Input Value  : Enummed Page ID
// Output Value : None
//--------------------------------------------------
void CFlashFinishLoadDefault(BYTE ucPageID)
{
    BYTE i = 0;

    g_ucFlashTemp[0] = _FLASH_INITIAL;

    for(i = _ITEM_ID_CODE_LENGTH; i < (tFLASHSIZE[ucPageID] - _ITEM_CHECKSUM_LENGTH); i++)
    {
        g_ucFlashTemp[i] = 0x00;
    }

    CFlashSaveData(ucPageID, g_ucFlashTemp);
}

//--------------------------------------------------
// Description  : Check for Load Eeprom default
// Input Value  : Enummed Page ID
// Output Value : None
//--------------------------------------------------
void CFlashCheckLoadDefault(BYTE ucPageID)
{
    BYTE i = 0;

    if(CFlashLoadData(ucPageID, _FLASH_INITIAL, g_ucFlashTemp) == _TRUE) //Flash Data ID Code
    {
        for(i = _ITEM_ID_CODE_LENGTH; i < (tFLASHSIZE[ucPageID] - _ITEM_CHECKSUM_LENGTH); i++)
        {
            if(g_ucFlashTemp[i] != 0x00)
            {
                CFlashLoadPageDefault(ucPageID);

                break;
            }
        }
    }
    else
    {
        CFlashLoadPageDefault(ucPageID);
    }
}

//--------------------------------------------------
// Description  : Save mode setting data, such as FirstAuto,
//                HPosition, VPosition, Clock and Phase.
// Input Value  : Mode Number
// Output Value : None
//--------------------------------------------------
void CEepromSaveModeData(BYTE ucMode)
{
    BYTE i = 0;

    memset(g_ucFlashTemp, 0xFF, sizeof(g_ucFlashTemp));

#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        g_ucFlashTemp[0] = GET_YPBPR_MODE_ITEM_CODE(ucMode);
    }
    else
#endif
    {
#if(_FIFO_MODE_ONLY == _ON)
        ucMode = g_ucFIFOModeNum;
        g_ucFlashTemp[0] = GET_FIFO_MODE_ITEM_CODE(ucMode);
#else
        g_ucFlashTemp[0] = (GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE) ? GET_PRESET_MODE_ITEM_CODE(ucMode) : GET_FIFO_MODE_ITEM_CODE(ucMode);
#endif
    }

    // Mode Data Here
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0] = (stModeUserData.FirstAuto & 0xE0) | (BYTE)((stModeUserData.FirstAuto & (_BIT0)) << 4) | ((BYTE)(stModeUserData.HPosition >> 8) & 0x0F);
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 1] = (BYTE)stModeUserData.HPosition;
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 2] = (BYTE)stModeUserData.VPosition;
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 3] = ((BYTE)(stModeUserData.VPosition >> 4) & 0xF0) | ((BYTE)(stModeUserData.Clock >> 8) & 0x0F);
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 4] = (BYTE)(stModeUserData.Clock);
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 5] = stModeUserData.Phase;

    // Mode Center Data Here
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 6] = (BYTE)(stModeUserCenterData.CenterHPos >> 8) & 0x0F;
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 7] = (BYTE)stModeUserCenterData.CenterHPos;
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 8] = (BYTE)(stModeUserCenterData.CenterVPos);
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 9] = (((BYTE)stModeUserCenterData.CenterVPos >> 4) & 0xF0) | ((BYTE)(stModeUserCenterData.CenterClock >> 8) & 0x0F);
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 10] = (BYTE)stModeUserCenterData.CenterClock;
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 11] = stModeUserCenterData.CenterPhase;

    CFlashSaveData(_MODE, g_ucFlashTemp);
}

//--------------------------------------------------
// Description  : Load mode setting data, such as FirstAuto,
//                HPosition, VPosition, Clock and Phase.
// Input Value  : Mode Number
// Output Value : None
//--------------------------------------------------
void CEepromLoadModeData(BYTE ucMode)
{
    bit bResult = _FALSE;

#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        if(CFlashLoadData(_MODE,
                          GET_YPBPR_MODE_ITEM_CODE(ucMode),
                          g_ucFlashTemp) == _TRUE)
        {
            bResult = _TRUE;
        }
    }
    else
#endif
    {
#if(_FIFO_MODE_ONLY == _ON)
        ucMode = g_ucFIFOModeNum;

        if(CFlashLoadData(_MODE,
                          GET_FIFO_MODE_ITEM_CODE(ucMode),
                          g_ucFlashTemp) == _TRUE)
        {
            bResult = _TRUE;
        }
#else
        if(CFlashLoadData(_MODE,
                          (GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE) ? GET_PRESET_MODE_ITEM_CODE(ucMode) : GET_FIFO_MODE_ITEM_CODE(ucMode),
                          g_ucFlashTemp) == _TRUE)
        {
            bResult = _TRUE;
        }
#endif
    }

    if(bResult == _TRUE)
    {
#if(_COLOR_FORMAT_CONVERT == _ON)
        stModeUserData.FirstAuto = ((g_ucFlashTemp[0] >> 7) & _BIT0) | (g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0] & (_BIT7 | _BIT6)) | (g_ucFlashTemp[0] & _BIT5);
#else
        stModeUserData.FirstAuto = ((g_ucFlashTemp[0] >> 7) & _BIT0) | (g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0] & (_BIT7 | _BIT6));
#endif

        // Load Mode Data Here
        stModeUserData.FirstAuto = (g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0] & 0xE0) | ((g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0] & 0x10) >> 4);
        stModeUserData.HPosition = ((g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0] & 0x0F) << 8) | g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 1];
        stModeUserData.VPosition = ((g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 3] & 0xF0) << 4) | g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 2];
        stModeUserData.Clock = ((g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 3] & 0x0F) << 8) | g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 4];
        stModeUserData.Phase = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 5];

        // Load Center Data Here
        stModeUserCenterData.CenterHPos = ((g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 6] & 0x0F) << 8) | g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 7];
        stModeUserCenterData.CenterVPos = ((g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 9] & 0xF0) << 4) | g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 8];
        stModeUserCenterData.CenterClock = ((g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 9] & 0x0F) << 8) | g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 10];
        stModeUserCenterData.CenterPhase = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 11];
    }
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        // Load YPbPr Default Values
        CLR_AUTO_FLAG();
        CLR_AUTO_FAIL_COUNT();

#if(_COLOR_FORMAT_CONVERT == _ON)
        SET_MODE_COLOR_FORMAT_FLAG(_YUV_COLOR_FORMAT);
#endif

        stModeUserData.HPosition = tYPBPR_MODE_TABLE[ucMode].IHStartPos;
        stModeUserData.VPosition = tYPBPR_MODE_TABLE[ucMode].IVStartPos;
        stModeUserData.Clock = tYPBPR_MODE_TABLE[ucMode].IHTotal;
        stModeUserData.Phase = 0;

        stModeUserCenterData.CenterHPos = stModeUserData.HPosition;
        stModeUserCenterData.CenterVPos = stModeUserData.VPosition;
        stModeUserCenterData.CenterClock = stModeUserData.Clock;
        stModeUserCenterData.CenterPhase = 0x00;
    }
#endif
    else
    {
        // Load VGA-RGB Default Values
        CLR_AUTO_FLAG();
        CLR_AUTO_FAIL_COUNT();

#if(_COLOR_FORMAT_CONVERT == _ON)
        SET_MODE_COLOR_FORMAT_FLAG(_RGB_COLOR_FORMAT);
#endif

        stModeUserData.HPosition = tINPUTMODE_PRESET_TABLE[ucMode].IHStartPos;
        stModeUserData.VPosition = tINPUTMODE_PRESET_TABLE[ucMode].IVStartPos;
        stModeUserData.Clock = tINPUTMODE_PRESET_TABLE[ucMode].IHTotal;
        stModeUserData.Phase = 0;

        stModeUserCenterData.CenterHPos = stModeUserData.HPosition;
        stModeUserCenterData.CenterVPos = stModeUserData.VPosition;
        stModeUserCenterData.CenterClock = stModeUserData.Clock;
        stModeUserCenterData.CenterPhase = 0x00;
    }
}

//--------------------------------------------------
// Description  : Initial mode setting data with defaults
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromInitialModeData(void)
{
    BYTE ucModeCnt = 0;
    BYTE ucModeSourceType = 0;
    BYTE i = 0;

#if(_FIFO_MODE_ONLY == _ON)

    for(ucModeCnt = 0; ucModeCnt < (_MAX_FIFO_MODE_INDEX + 1); ucModeCnt++)
    {
        if(CFlashLoadData(_MODE, GET_FIFO_MODE_ITEM_CODE(ucModeCnt), g_ucFlashTemp) == _TRUE)
        {
            g_ucFIFOModeNum = ucModeCnt;

            stModeUserData.FirstAuto = 0xFF;
            stModeUserData.HPosition = 0xFF;
            stModeUserData.VPosition = 0xFF;
            stModeUserData.Clock = 0xFF;
            stModeUserData.Phase = 0xFF;

            stModeUserCenterData.CenterHPos = 0xFFFF;
            stModeUserCenterData.CenterVPos = 0xFFFF;
            stModeUserCenterData.CenterClock = 0xFFFF;
            stModeUserCenterData.CenterPhase = 0xFF;

            CEepromSaveModeData(ucModeCnt);
        }
    }

#else

    ucModeSourceType = GET_MODE_SEARCH_TYPE();
    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);

    for(ucModeCnt = 0; ucModeCnt < _MAX_PRESET_MODE; ucModeCnt++)
    {
        if(CFlashLoadData(_MODE, GET_PRESET_MODE_ITEM_CODE(ucModeCnt), g_ucFlashTemp) == _TRUE)
        {
            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();

#if(_COLOR_FORMAT_CONVERT == _ON)
            CLR_MODE_COLOR_FORMAT_FLAG();
#endif

            stModeUserData.HPosition = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHStartPos;
            stModeUserData.VPosition = tINPUTMODE_PRESET_TABLE[ucModeCnt].IVStartPos;
            stModeUserData.Clock = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHTotal;
            stModeUserData.Phase = 0;

            stModeUserCenterData.CenterHPos = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHStartPos;
            stModeUserCenterData.CenterVPos = tINPUTMODE_PRESET_TABLE[ucModeCnt].IVStartPos;
            stModeUserCenterData.CenterClock = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHTotal;
            stModeUserCenterData.CenterPhase = 0;

            CEepromSaveModeData(ucModeCnt);
        }
    }

    for(ucModeCnt = 0; ucModeCnt < 16; ucModeCnt++)
    {
        if(CFlashLoadData(_MODE, GET_FIFO_MODE_ITEM_CODE(ucModeCnt), g_ucFlashTemp) == _TRUE)
        {
            g_ucFlashTemp[0] = GET_FIFO_MODE_ITEM_CODE(ucModeCnt);

            for(i = _ITEM_ID_CODE_LENGTH; i < (tFLASHSIZE[_MODE] - _ITEM_CHECKSUM_LENGTH); i++)
            {
                g_ucFlashTemp[i] = 0xff;
            }

            CFlashSaveData(_MODE, g_ucFlashTemp);
        }
    }

    SET_MODE_SEARCH_TYPE(ucModeSourceType);

#endif

#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)

    ucModeSourceType = GET_INPUTSOURCE_TYPE();
    SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);

    for(ucModeCnt = 0; ucModeCnt < _MAX_YPBPR_MODE; ucModeCnt++)
    {
        if(CFlashLoadData(_MODE, GET_YPBPR_MODE_ITEM_CODE(ucModeCnt), g_ucFlashTemp))
        {
            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();

#if(_COLOR_FORMAT_CONVERT == _ON)
            SET_MODE_COLOR_FORMAT_FLAG(_YUV_COLOR_FORMAT);
#endif

            stModeUserData.HPosition = tYPBPR_MODE_TABLE[ucModeCnt].IHStartPos;
            stModeUserData.VPosition = tYPBPR_MODE_TABLE[ucModeCnt].IVStartPos;
            stModeUserData.Clock = tYPBPR_MODE_TABLE[ucModeCnt].IHTotal;
            stModeUserData.Phase = 0;

            stModeUserCenterData.CenterHPos = tYPBPR_MODE_TABLE[ucModeCnt].IHStartPos;
            stModeUserCenterData.CenterVPos = tYPBPR_MODE_TABLE[ucModeCnt].IVStartPos;
            stModeUserCenterData.CenterClock = tYPBPR_MODE_TABLE[ucModeCnt].IHTotal;
            stModeUserCenterData.CenterPhase = 0;

            CEepromSaveModeData(ucModeCnt);
        }
    }

    SET_INPUTSOURCE_TYPE(ucModeSourceType);

#endif
}

//--------------------------------------------------
// Description  : Save user FIFO mode data, such as ModeNum,
//                IHFreq, IVFreq.
// Input Value  : StructModeUserFIFODataType
// Output Value : None
//--------------------------------------------------
void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode)
{
    stUserFIFOMode.IHFreq = ((stUserFIFOMode.IVFreq & 0x0f00) << 4) | (stUserFIFOMode.IHFreq & 0x0fff);

    memset(g_ucFlashTemp, 0xFF, sizeof(g_ucFlashTemp));

    g_ucFlashTemp[0] = GET_FIFO_MODE_FIFO_ITEM_CODE(stSystemData.UserFIFOMode);
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0] = stUserFIFOMode.ModeNum;

#if(_FIFO_MODE_ONLY == _ON)
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 1] = (BYTE)(stUserFIFOMode.IHFreq >> 8) | ((BYTE)GET_MODE_SEARCH_TYPE() << 7);
#else
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 1] = (BYTE)(stUserFIFOMode.IHFreq >> 8);
#endif

    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 2] = (BYTE)stUserFIFOMode.IHFreq;
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 3] = (BYTE)stUserFIFOMode.IVFreq;

    CFlashSaveData(_MODE, g_ucFlashTemp);
}

//--------------------------------------------------
// Description  : Load 4 sets of user FIFO mode data.
// Input Value  : FIFO group number, StructModeUserFIFODataType
// Output Value : None
//--------------------------------------------------
void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray)
{
    BYTE cnt = 0;
    BYTE i = 0;

    for(cnt = ucNum * 4; cnt < ucNum * 4 + 4; cnt++)
    {
        if(CFlashLoadData(_MODE, GET_FIFO_MODE_FIFO_ITEM_CODE(cnt), g_ucFlashTemp) == _TRUE)
        {
            for(i = 0; i < 4; i++)
            {
                pArray[(cnt & 0x03) * 4 + i] = g_ucFlashTemp[i + _ITEM_ID_CODE_LENGTH];
            }
        }
        else
        {
            for(i = 0; i < 4; i++)
            {
                pArray[(cnt & 0x03) * 4 + i] = 0xff;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Initial user FIFO mode data with defaults
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromInitialUserFIFOModeData(void)
{
    BYTE cnt = 0, i = 0;

    for(cnt = 0; cnt < (_MAX_FIFO_MODE_INDEX + 1); cnt++)
    {
        if(CFlashLoadData(_MODE, GET_FIFO_MODE_FIFO_ITEM_CODE(cnt), g_ucFlashTemp))
        {
            g_ucFlashTemp[0] = GET_FIFO_MODE_FIFO_ITEM_CODE(cnt);

            for(i = _ITEM_ID_CODE_LENGTH; i < (tFLASHSIZE[_MODE] - _ITEM_CHECKSUM_LENGTH); i++)
            {
                g_ucFlashTemp[i] = 0xff;
            }

            CFlashSaveData(_MODE, g_ucFlashTemp);
        }
    }
}

//--------------------------------------------------
// Description  : Save Centered Mode Data
// Input Value  : Mode Number
// Output Value : None
//--------------------------------------------------
void CEepromSaveCenterModeData(BYTE ucMode)
{
    CEepromSaveModeData(ucMode);
}

//--------------------------------------------------
// Description  : Load Centered Mode Data
// Input Value  : Mode Number
// Output Value : None
//--------------------------------------------------
void CEepromLoadCenterModeData(BYTE ucMode)
{
    CEepromLoadModeData(ucMode);
}


//--------------------------------------------------
// Description  : Save system data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveSystemData(void)
{
    memset(g_ucFlashTemp, 0xFF, sizeof(g_ucFlashTemp));

    g_ucFlashTemp[0] = _FLASH_SYSTEM_DATA;

    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0] = stSystemData.MonitorFlag;
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 1] = stSystemData.SearchIndex;
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 2] = stSystemData.BackLight;
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 3] = stSystemData.UserFIFOMode;
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 4] = stSystemData.ODTable;
#if(_COLOR_FORMAT_CONVERT == _ON)
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 5] = stSystemData.ColorSetting;
#endif
    CFlashSaveData(_GLOBAL, g_ucFlashTemp);
}

//--------------------------------------------------
// Description  : Load system data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadSystemData(void)
{
    if(CFlashLoadData(_GLOBAL, _FLASH_SYSTEM_DATA, g_ucFlashTemp) == _TRUE)
    {
        stSystemData.MonitorFlag = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0];
        stSystemData.SearchIndex = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 1];
        stSystemData.BackLight = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 2];
        stSystemData.UserFIFOMode = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 3];
        stSystemData.ODTable = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 4];
#if(_COLOR_FORMAT_CONVERT == _ON)
        stSystemData.ColorSetting = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 5];
#endif
    }
    else
    {
        stSystemData = tEEPROM_SYSTEM_DATA;
    }
}

//--------------------------------------------------
// Description  : Load default system data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadSystemDataDefault(void)
{
    stSystemData = tEEPROM_SYSTEM_DATA;
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("tEEPROM_SYSTEM_DATA.BackLight", tEEPROM_SYSTEM_DATA.BackLight);
CDebugMessage("stSystemData.BackLight",stSystemData.BackLight);
#endif
CEepromSaveSystemData();
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveOsdUserData(void)
{
    CFlashWrite(_GLOBAL, _FLASH_OSD_USER_DATA_1, sizeof(StructOsdUserDataType), &stOsdUserData.OsdSettingFlag);
}

//--------------------------------------------------
// Description  : Load OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadOsdUserData(void)
{
    if(CFlashRead(_GLOBAL, _FLASH_OSD_USER_DATA_1, sizeof(StructOsdUserDataType), &stOsdUserData.OsdSettingFlag) == _FALSE)
    {
        stOsdUserData = tEEPROM_OSDUSER_DATA;
    }
}

//--------------------------------------------------
// Description  : Load default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadOsdUserDataDefault(void)
{
    stOsdUserData = tEEPROM_OSDUSER_DATA;
    CEepromSaveOsdUserData();
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save ADC data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveAdcData(void)
{
    memset(g_ucFlashTemp, 0xFF, sizeof(g_ucFlashTemp));

    g_ucFlashTemp[0] = (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) ? _FLASH_ADC_DATA_VGA : _FLASH_ADC_DATA_YPBPR;

    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0] = stAdcData.AdcGain[_RED];
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 1] = stAdcData.AdcGain[_GREEN];
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 2] = stAdcData.AdcGain[_BLUE];
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 3] = stAdcData.AdcOffset[_RED];
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 4] = stAdcData.AdcOffset[_GREEN];
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 5] = stAdcData.AdcOffset[_BLUE];
    g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 6] = g_ucAdcPGA;

    CFlashSaveData(_GLOBAL, g_ucFlashTemp);
}

//--------------------------------------------------
// Description  : Load ADC data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadAdcData(void)
{
    if(CFlashLoadData(_GLOBAL, (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) ? _FLASH_ADC_DATA_VGA : _FLASH_ADC_DATA_YPBPR, g_ucFlashTemp) == _TRUE) //Flash Data ID Code
    {
        stAdcData.AdcGain[_RED] = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0];
        stAdcData.AdcGain[_GREEN] = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 1];
        stAdcData.AdcGain[_BLUE] = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 2];
        stAdcData.AdcOffset[_RED] = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 3];
        stAdcData.AdcOffset[_GREEN] = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 4];
        stAdcData.AdcOffset[_BLUE] = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 5];
        g_ucAdcPGA = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 6];
    }
    else
    {
        stAdcData = tEEPROM_ADC_DATA;
        g_ucAdcPGA = 0x08;
    }
}

//--------------------------------------------------
// Description  : Load default ADC data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadAdcDataDefault(void)
{
    BYTE ucTemp = 0;

    ucTemp = GET_INPUTSOURCE_TYPE();
    stAdcData = tEEPROM_ADC_DATA;
    g_ucAdcPGA = 0x08;

    SET_INPUTSOURCE_TYPE(_SOURCE_VGA);
    CEepromSaveAdcData();
    SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);
    CEepromSaveAdcData();
    SET_INPUTSOURCE_TYPE(ucTemp);
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save Brightness/Contrast data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveBriConData(void)
{
    memset(g_ucFlashTemp, 0xFF, sizeof(g_ucFlashTemp));

    if(GET_INPUTSOURCE_TYPE() != _SOURCE_NONE)
    {
        g_ucFlashTemp[0] = _FLASH_BRI_CON_DATA_VGA + GET_INPUTSOURCE_TYPE();

        g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0] = stConBriData.Brightness;
        g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 1] = stConBriData.Contrast;

        CFlashSaveData(_GLOBAL, g_ucFlashTemp);
    }
}

//--------------------------------------------------
// Description  : Load Brightness/Contrast data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadBriConData(void)
{
    if(GET_INPUTSOURCE_TYPE() != _SOURCE_NONE)
    {
        if(CFlashLoadData(_GLOBAL, _FLASH_BRI_CON_DATA_VGA + GET_INPUTSOURCE_TYPE(), g_ucFlashTemp) == _TRUE)
        {
            stConBriData.Brightness = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0];
            stConBriData.Contrast = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 1];
        }
        else
        {
            stConBriData.Brightness = tEEPROM_COLOR_PROC0_DATA[GET_INPUTSOURCE_TYPE()].Brightness;
            stConBriData.Contrast = tEEPROM_COLOR_PROC0_DATA[GET_INPUTSOURCE_TYPE()].Contrast;
        }
    }
}

//--------------------------------------------------
// Description  : Load default Brightness/Contrast data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadBriConDataDefault(void)
{
    stConBriData.Brightness = tEEPROM_COLOR_PROC0_DATA[GET_INPUTSOURCE_TYPE()].Brightness;
    stConBriData.Contrast = tEEPROM_COLOR_PROC0_DATA[GET_INPUTSOURCE_TYPE()].Contrast;
	
    CEepromSaveBriConData();
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save Color Temperature data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveColorTempData(void)
{
    if(GET_INPUTSOURCE_TYPE() != _SOURCE_NONE)
    {
        memset(g_ucFlashTemp, 0xFF, sizeof(g_ucFlashTemp));

        g_ucFlashTemp[0] = _FLASH_COLOR_TEMP_DATA_VGA_9300 + GET_COLOR_TEMP_TYPE() + GET_INPUTSOURCE_TYPE() * _SOURCE_AMOUNT;

        g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0] = stColorTempData.ColorTemp[_RED];
        g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 1] = stColorTempData.ColorTemp[_GREEN];
        g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 2] = stColorTempData.ColorTemp[_BLUE];

        CFlashSaveData(_GLOBAL, g_ucFlashTemp);
    }
}

//--------------------------------------------------
// Description  : Load Color Temperature data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadColorTempData(void)
{
    if(GET_INPUTSOURCE_TYPE() != _SOURCE_NONE)
    {
        if(CFlashLoadData(_GLOBAL, _FLASH_COLOR_TEMP_DATA_VGA_9300 + GET_COLOR_TEMP_TYPE() + GET_INPUTSOURCE_TYPE() * _SOURCE_AMOUNT, g_ucFlashTemp) == _TRUE)
        {
            stColorTempData.ColorTemp[_RED] = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 0];
            stColorTempData.ColorTemp[_GREEN] = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 1];
            stColorTempData.ColorTemp[_BLUE] = g_ucFlashTemp[_ITEM_ID_CODE_LENGTH + 2];
        }
        else
        {
            stColorTempData.ColorTemp[_RED] = *(&tEEPROM_COLORTEMP_DATA[GET_INPUTSOURCE_TYPE()].ColorTemp9300Red + stOsdUserData.ColorTemp * 3);
            stColorTempData.ColorTemp[_GREEN] = *(&tEEPROM_COLORTEMP_DATA[GET_INPUTSOURCE_TYPE()].ColorTemp9300Red + stOsdUserData.ColorTemp * 3 + 1);
            stColorTempData.ColorTemp[_BLUE] = *(&tEEPROM_COLORTEMP_DATA[GET_INPUTSOURCE_TYPE()].ColorTemp9300Red + stOsdUserData.ColorTemp * 3 + 2);
        }
    }
}

//--------------------------------------------------
// Description  : Load default Color Temperature data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadColorTempDataDefault(void)
{
    stColorTempData.ColorTemp[_RED] = *(&tEEPROM_COLORTEMP_DATA[GET_INPUTSOURCE_TYPE()].ColorTemp9300Red + stOsdUserData.ColorTemp * 3);
    stColorTempData.ColorTemp[_GREEN] = *(&tEEPROM_COLORTEMP_DATA[GET_INPUTSOURCE_TYPE()].ColorTemp9300Red + stOsdUserData.ColorTemp * 3 + 1);
    stColorTempData.ColorTemp[_BLUE] = *(&tEEPROM_COLORTEMP_DATA[GET_INPUTSOURCE_TYPE()].ColorTemp9300Red + stOsdUserData.ColorTemp * 3 + 2);

    CEepromSaveColorTempData();
}

#if(_DDCCI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadBackLightDefault(void)
{
    stSystemData.BackLight = tEEPROM_SYSTEM_DATA.BackLight;
    CEepromSaveSystemData();
}
#endif // End of #if(_DDCCI_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Flash write function
// Input Value  : ucPage        --> Flash Page
//                usLength      --> Numbers of data we want to write (it can't be more than 56)
//                ucIndex       --> Number of Index in the Page
//                pWriteArray   --> Writing data array
// Output Value : None
//--------------------------------------------------
void CFlashWrite(BYTE ucPage, BYTE ucIndex, BYTE ucLength, BYTE *pWriteArray)
{
    BYTE i = 0;
    BYTE cnt = 0;

    if(ucLength > ((tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH) * (_FLASH_OSD_USER_DATA_END - _FLASH_OSD_USER_DATA_1)))
    {
        return;
    }

    if(ucLength >= (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH))
    {
        for(cnt = 0; cnt < (ucLength / (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH)); cnt++)
        {
            g_ucFlashTemp[0] = ucIndex + cnt; //Flash Data Item ID Code

            for(i = _ITEM_ID_CODE_LENGTH; i < (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH); i++)
            {
                g_ucFlashTemp[i] = *(pWriteArray + cnt * (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH) + i - _ITEM_ID_CODE_LENGTH);
            }

            CFlashSaveData(ucPage, g_ucFlashTemp);
        }
    }

    if(ucLength % (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH) != 0)
    {
        memset(g_ucFlashTemp, 0xFF, sizeof(g_ucFlashTemp));

        g_ucFlashTemp[0] = ucIndex + cnt; // Flash Data Item ID Code

        for(i = _ITEM_ID_CODE_LENGTH; i < ((ucLength % (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH)) + _ITEM_ID_CODE_LENGTH); i++)
        {
            g_ucFlashTemp[i] = *(pWriteArray + cnt * (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH) + i - _ITEM_ID_CODE_LENGTH);
        }

        CFlashSaveData(ucPage, g_ucFlashTemp);
    }
}

//--------------------------------------------------
// Description  : Flash read function
// Input Value  : ucPage        --> Flash Page
//                ucIndex     --> Number of Index in the Page
//                usLength      --> Numbers of data we want to write (it can't be more than 56)
//                pWriteArray   --> Writing data array
// Output Value : Return _SUCCESS if succeed
//--------------------------------------------------
bit CFlashRead(BYTE ucPage, BYTE ucIndex, BYTE ucLength, BYTE *pWriteArray)
{
    BYTE i = 0;
    BYTE cnt = 0;

    if(ucLength > ((tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH) * (_FLASH_OSD_USER_DATA_END - _FLASH_OSD_USER_DATA_1)))
    {
        return _FALSE;
    }

    for(cnt = 0; cnt < (ucLength % (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH) ? (ucLength / (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH) + 1) : ucLength / (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH)); cnt++)
    {
        if(CFlashLoadData(ucPage, ucIndex + cnt, g_ucFlashTemp) == _TRUE)
        {
            for(i = _ITEM_ID_CODE_LENGTH; i < ((cnt == ucLength / (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH)) ? (ucLength % (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH) + 1) : tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH); i++)
            {
                *(pWriteArray + cnt * (tFLASHSIZE[ucPage] - _ITEM_CHECKSUM_LENGTH - _ITEM_ID_CODE_LENGTH) + i - _ITEM_ID_CODE_LENGTH) = g_ucFlashTemp[i];
            }
        }
        else
        {
            return _FALSE;
        }
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Save Data of Flash.
// Input Value  : Page ID
// Output Value : None
//--------------------------------------------------
void CFlashSaveData(BYTE ucPageID, BYTE *pArray)
{
    bit bEqual = _TRUE;
    BYTE ucCount = 0;
    WORD cnt = 0;

    // Calculate the Checksum of the Data item in buffer
    pArray[tFLASHSIZE[ucPageID] - _ITEM_CHECKSUM_LENGTH] = CFlashBufferChecksum(tFLASHSIZE[ucPageID]);

    for(cnt = g_usFlashAddr[ucPageID] + 1; cnt > 0; cnt--)
    {
        // Check Item ID index and Item checksum to make sure that this Item which has the same ID index is valid
        if((MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + (cnt - 1) * tFLASHSIZE[ucPageID]] == pArray[0])
        && (CFlashCalculateItemChecksum(ucPageID, cnt) == (MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + (cnt - 1) * tFLASHSIZE[ucPageID] + tFLASHSIZE[ucPageID] - _ITEM_CHECKSUM_LENGTH])))
        {
            // Check data item in buffer is equal to the existed data item in page or not
            for(ucCount = 0; ucCount < tFLASHSIZE[ucPageID]; ucCount++)
            {
                if(MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + (cnt - 1) * tFLASHSIZE[ucPageID] + ucCount] != pArray[ucCount])
                {
                    bEqual = _FALSE;
                    break;
                }
            }

            break;
        }

        // If g_usFlashAddr[ucPage] == 0, indicate the ucPage page has not saved data item,is free page
        if(cnt == 1)
        {
            bEqual = _FALSE;
        }
    }

    if(!bEqual)
    {
        // Page full when update data, need to move page
        if(g_usFlashAddr[ucPageID] == ((_PAGE_SIZE-_PAGE_INFO_LENGTH) / tFLASHSIZE[ucPageID]))
        {
            CFlashMoveData(ucPageID);
        }
        else
        {
            // Find an available Item space address which is 0xFF for Item all fields
            // Use this mechanism to avoid save Item to the wrong address which update data exception happens
            for(cnt = g_usFlashAddr[ucPageID]; cnt <= ((_PAGE_SIZE - _PAGE_INFO_LENGTH) / tFLASHSIZE[ucPageID]); cnt++)
            {
                if(cnt == ((_PAGE_SIZE - _PAGE_INFO_LENGTH) / tFLASHSIZE[ucPageID]))
                {
                    CFlashMoveData(ucPageID);
                    return;
                }

                // Use this variable to mark if it finds an available item space.
                bEqual = _TRUE;

                for(ucCount = 0; ucCount < tFLASHSIZE[ucPageID]; ucCount++)
                {
                    if((MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + cnt * tFLASHSIZE[ucPageID] + ucCount]) != 0xFF)
                    {
                        bEqual = _FALSE;
                        break;
                    }
                }

                if(bEqual == _TRUE)
                {
                    break;
                }
                else
                {
                    g_usFlashAddr[ucPageID] = cnt + 1;
                }
            }

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
            if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
            {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
                for(cnt = _ITEM_ID_CODE_LENGTH; cnt < tFLASHSIZE[ucPageID]; cnt++)
                {
                    CFlashWREN(_START_PAGE + g_ucFlashPage[ucPageID]);
                    MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + g_usFlashAddr[ucPageID] * tFLASHSIZE[ucPageID] + cnt] = pArray[cnt];
                }

                CFlashWREN(_START_PAGE + g_ucFlashPage[ucPageID]);
                MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + g_usFlashAddr[ucPageID] * tFLASHSIZE[ucPageID]] = pArray[0];
                CFlashWRDis();
#endif
            }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
            else
#endif
            {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
                CFlashWREN(_START_PAGE + g_ucFlashPage[ucPageID]);
                memcpy(&(MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + g_usFlashAddr[ucPageID] * tFLASHSIZE[ucPageID] + _ITEM_ID_CODE_LENGTH]), (pArray + _ITEM_ID_CODE_LENGTH), (tFLASHSIZE[ucPageID] - _ITEM_ID_CODE_LENGTH));
                MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + g_usFlashAddr[ucPageID] * tFLASHSIZE[ucPageID]] = pArray[0];
                CFlashWRDis();
#endif
            }

            g_usFlashAddr[ucPageID]++;
        }
    }
}

//--------------------------------------------------
// Description  : Load Data of Flash.
// Input Value  : uCPageID    --> Page ID
//                ucIndex     --> Number of Index in the Page
// Output Value : Return _TRUE if succeed
//--------------------------------------------------
bit CFlashLoadData(BYTE ucPageID, BYTE ucIndex, BYTE *pArray)
{
    BYTE i = 0;
    BYTE ItemChecksum = 0;
    WORD cnt = 0;

    // Find the data item which item index is ucIndex in the ucPage page from bottom to top
    for(cnt = (g_usFlashAddr[ucPageID] + 1); cnt > 0; cnt--)
    {
        ItemChecksum = 0;

        // If data item index matches
        if(MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + (cnt - 1) * tFLASHSIZE[ucPageID]] == ucIndex)
        {
            // Calculate the checksum of the data item
            for(i = 0; i < (tFLASHSIZE[ucPageID] - _ITEM_CHECKSUM_LENGTH); i++)
            {
                ItemChecksum = ItemChecksum ^ MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + (cnt - 1) * tFLASHSIZE[ucPageID] + i];
            }

            // Check checksum value matches or not
            if(MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + (cnt - 1) * tFLASHSIZE[ucPageID] + tFLASHSIZE[ucPageID] - _ITEM_CHECKSUM_LENGTH] != ItemChecksum)
            {
                return _FALSE;
            }

            // Load the found data item to the buffer
            for(i = 0; i < tFLASHSIZE[ucPageID]; i++)
            {
                pArray[i] = MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + (cnt - 1) * tFLASHSIZE[ucPageID] + i];
            }

            break;
        }

        // If g_usFlashAddr[ucPage] == 0, indicate the ucPage page has not saved data item,is free page
        if(cnt == 1)
        {
            //Can't find the Index Number
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Move data to another page of Flash
// Input Value  : Page ID
// Output Value : Return _TRUE if succeed
//--------------------------------------------------
bit CFlashMoveData(BYTE ucPageID)
{
    BYTE ucModeCnt = 0;
    BYTE i = 0;
    BYTE ucPage = g_ucFlashPage[ucPageID];
    WORD cnt = 0;
    WORD j = 1;

    // First sector erase the free page specified by g_ucFlashFreePage
    if(CFlashErase(g_ucFlashFreePage + _START_PAGE) == _FALSE)
    {
        return _FALSE;
    }

    // Then save latest data item to the new page
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
        for(cnt = 0; cnt < tFLASHSIZE[ucPageID]; cnt++)
        {
            CFlashWREN(_START_PAGE + g_ucFlashFreePage);
            MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + cnt] = g_ucFlashTemp[cnt];
        }
        CFlashWRDis();
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
        CFlashWREN(_START_PAGE + g_ucFlashFreePage);
        memcpy(&(MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE]), g_ucFlashTemp, tFLASHSIZE[ucPageID]);
        CFlashWRDis();
#endif
    }

    // Clear Buffer
    memset(g_ucFlashTemp, 0x00, sizeof(g_ucFlashTemp));

    g_ucFlashPage[ucPageID] = g_ucFlashFreePage; // Update g_ucFlashPage, Move data to the page g_ucFlashFreePage
    g_ucFlashFreePage = CFlashSearchFreePage(g_ucFlashFreePage); // Find another free page index
    g_ulFlashMovePage += 1; // Update move count value

    // And then load the latest data items which saved in the old full page to the new page from bottom to top
    j = 1;

    for(cnt = ((_PAGE_SIZE - _PAGE_INFO_LENGTH) / tFLASHSIZE[ucPageID]); cnt > 0; cnt--)
    {
        ucModeCnt = MCU_FLASH[ucPage * _PAGE_SIZE + (cnt - 1) * tFLASHSIZE[ucPageID]];

        if((ucModeCnt != 0xFF) && (CFlashSearchItem(ucPageID, j, ucModeCnt) == _FALSE))
        {
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
            if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
            {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
                for(i = 0; i < tFLASHSIZE[ucPageID]; i++)
                {
                    CFlashWREN(_START_PAGE + g_ucFlashPage[ucPageID]);
                    MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + j * tFLASHSIZE[ucPageID] + i] = MCU_FLASH[ucPage * _PAGE_SIZE + (cnt - 1) * tFLASHSIZE[ucPageID] + i];
                }

                CFlashWRDis();
#endif
            }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
            else
#endif
            {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
                CFlashWREN(_START_PAGE + g_ucFlashPage[ucPageID]);
                memcpy(&(MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + j * tFLASHSIZE[ucPageID]]), &(MCU_FLASH[ucPage * _PAGE_SIZE + (cnt - 1) * tFLASHSIZE[ucPageID]]), tFLASHSIZE[ucPageID]);
                CFlashWRDis();
#endif
            }

            j++;
        }
    }

    // Update the data item address in the new page
    g_usFlashAddr[ucPageID] = j;

    // Last update the new moved page info fields
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
        CFlashWREN(_START_PAGE + g_ucFlashPage[ucPageID]);
        MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 5] = tFLASHSIZE[ucPageID];
        CFlashWREN(_START_PAGE + g_ucFlashPage[ucPageID]);
        MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 4] = (BYTE)(g_ulFlashMovePage >> 16);
        CFlashWREN(_START_PAGE + g_ucFlashPage[ucPageID]);
        MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 3] = (BYTE)(g_ulFlashMovePage >> 8);
        CFlashWREN(_START_PAGE + g_ucFlashPage[ucPageID]);
        MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 2] = (BYTE)g_ulFlashMovePage;
        CFlashWREN(_START_PAGE + g_ucFlashPage[ucPageID]);
        MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 1] = tFLASHCODE[ucPageID];
        CFlashWREN(_START_PAGE + g_ucFlashPage[ucPageID]);
        MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 6] = tFLASHSIZE[ucPageID] ^ ((BYTE)(g_ulFlashMovePage >> 16)) ^ ((BYTE)(g_ulFlashMovePage >> 8)) ^ ((BYTE)g_ulFlashMovePage) ^ tFLASHCODE[ucPageID];
        CFlashWRDis();
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
        CFlashWREN(_START_PAGE + g_ucFlashPage[ucPageID]);
        MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 5] = tFLASHSIZE[ucPageID];
        MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 4] = (BYTE)(g_ulFlashMovePage >> 16);
        MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 3] = (BYTE)(g_ulFlashMovePage >> 8);
        MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 2] = (BYTE)g_ulFlashMovePage;
        MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 1] = tFLASHCODE[ucPageID];
        MCU_FLASH[(g_ucFlashPage[ucPageID] + 1) * _PAGE_SIZE - 6] = tFLASHSIZE[ucPageID] ^ ((BYTE)(g_ulFlashMovePage >> 16)) ^ ((BYTE)(g_ulFlashMovePage >> 8)) ^ ((BYTE)g_ulFlashMovePage) ^ tFLASHCODE[ucPageID];
        CFlashWRDis();
#endif
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Search Item in a specified page
//                from a specified address for a
//                specified Item ID Code
// Input Value  : Page Number, Start Address, and Item ID Code
// Output Value : Return _TURE if ID Code is found
//--------------------------------------------------
bit CFlashSearchItem(BYTE ucPageID, WORD usStartAddr, BYTE ucItemCode)
{
    WORD cnt = 0;

    for(cnt = usStartAddr; cnt > 0; cnt--)
    {
        if(MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + (cnt - 1) * tFLASHSIZE[ucPageID]] == ucItemCode)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Calculate the checksum in the buffer g_ucFlashTemp by a specified length
// Input Value  : Length of the checksum calculation
// Output Value : the Checksum
//--------------------------------------------------
BYTE CFlashBufferChecksum(BYTE ucLength)
{
    BYTE i = 0;
    BYTE ucChecksum = 0;

    for(i = 0; i < (ucLength - _ITEM_CHECKSUM_LENGTH); i++)
    {
        ucChecksum ^= g_ucFlashTemp[i];
    }

    return ucChecksum;
}

//--------------------------------------------------
// Description  : Calculate the checksum of specified Item
// Input Value  : ucPage,usItemAddr
// Output Value : the Checksum
//--------------------------------------------------
BYTE CFlashCalculateItemChecksum(BYTE ucPageID, WORD usItemAddr)
{
    BYTE i = 0;
    BYTE ucChecksum = 0;

    for(i = 0; i < (tFLASHSIZE[ucPageID] - _ITEM_CHECKSUM_LENGTH); i++)
    {
        ucChecksum = ucChecksum ^ MCU_FLASH[g_ucFlashPage[ucPageID] * _PAGE_SIZE + (usItemAddr - 1) * tFLASHSIZE[ucPageID] + i];
    }

    return ucChecksum;
}
#endif  // End of #if(_MEMORY_LOCATION == _FLASH)

//--------------------------------------------------------------
// Description  : Get Detailed INFO of specified Flash type
// Input Value  : index of tFLASH_DETAILED_INFO
// Output Value : data of tFLASH_DETAILED_INFO at specified index
//--------------------------------------------------------------
BYTE CFlashGetFlashDetailedInfo(BYTE ucFlashType, BYTE ucIndex)
{
    return tFLASH_DETAILED_INFO[ucFlashType][ucIndex];
}

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
//--------------------------------------------------------------
// Description  : Get Flash INFO supported by FW
// Input Value  : index of tFLASH_SUPPORT_INFO
// Output Value : data of tFLASH_SUPPORT_INFO at specified index
//--------------------------------------------------------------
BYTE CFlashGetFlashSupportInfo(BYTE ucIndex)
{
    return tFLASH_SUPPORT_INFO[ucIndex];
}

//--------------------------------------------------
// Description  : Check if flash type is valid
// Input Value  : None
// Output Value : Detected Flash type index
//--------------------------------------------------
bit CFlashCheckFlashType()
{
    g_ucFlashType = CFlashCheckFWSupportFlashType();

    if(g_ucFlashType >= CFlashGetFlashSupportInfo(_FLASH_SUPPORT_INFO_SUPPORT_COUNT))
    {
        g_ucFlashType = _FLASH_TYPE_DEFAULT_SUPPORT;

        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Check if flash type is valid
// Input Value  : None
// Output Value : _TRUE  : Current flash type is valid
//                _FALSE : Current flash type is invalid
//--------------------------------------------------
BYTE CFlashCheckFWSupportFlashType()
{
    bit bMatchedFlashType = _FALSE;
    bit bIsUnequal = _FALSE;
    BYTE i = 0;
    BYTE j = 0;
    BYTE ucMatchedJEDECIDFlashTypeCount = 0;

    //Clear buffer
    memset(pData, 0x00, sizeof(pData));

    //////////////////////////////////////////////////////////////////////////
    // Use JEDECID Instruction first to get Flash Manufacture ID, Device ID //
    //////////////////////////////////////////////////////////////////////////
    if(CFlashReadFlashIDCode(0x9F, &pData[0], &pData[1], &pData[2]))
    {
        ucMatchedJEDECIDFlashTypeCount = 0;
        bMatchedFlashType = _FALSE;

        // Get JEDEC ID Code, and match with the ID Code table
        for(i = 0; i < CFlashGetFlashSupportInfo(_FLASH_SUPPORT_INFO_SUPPORT_COUNT); i++)
        {
            if((CFlashGetFlashDetailedInfo(i, _FLASH_INFO_JEDEC_ID_CODE_0) != 0x00) ||
               (CFlashGetFlashDetailedInfo(i, _FLASH_INFO_JEDEC_ID_CODE_1) != 0x00) ||
               (CFlashGetFlashDetailedInfo(i, _FLASH_INFO_JEDEC_ID_CODE_2) != 0x00))
            {
                if((pData[0] == CFlashGetFlashDetailedInfo(i, _FLASH_INFO_JEDEC_ID_CODE_0)) &&
                   (pData[1] == CFlashGetFlashDetailedInfo(i, _FLASH_INFO_JEDEC_ID_CODE_1)) &&
                   (pData[2] == CFlashGetFlashDetailedInfo(i, _FLASH_INFO_JEDEC_ID_CODE_2)))
                {
                    // Save matched flash type index to buffer
                    pData[ucMatchedJEDECIDFlashTypeCount + 6] = i;
                    ucMatchedJEDECIDFlashTypeCount++;
                    bMatchedFlashType = _TRUE;
                }
            }
        }

        // Find the matched Flash Type supported by F/W
        if(bMatchedFlashType == _TRUE)
        {
            bMatchedFlashType = _FALSE;

            // Find only one matched flash type
            if(ucMatchedJEDECIDFlashTypeCount == 1)
            {
                return pData[6];
            }

            // matched flash type is over 6,this is a limit by the size of pData
            if(ucMatchedJEDECIDFlashTypeCount > 6)
            {
                return pData[6];
            }
            else // Find more than one matched flash type
            {
                // USE RDID(0x90) Instruction to distinguish flash type further
                if(CFlashReadFlashIDCode(0x90, &pData[0], &pData[1], &pData[2]))
                {
                    for(i = 0; i < ucMatchedJEDECIDFlashTypeCount; i++)
                    {
                        bIsUnequal = _FALSE;

                        for(j = 0; j < 3; j++)
                        {
                            if(CFlashGetFlashDetailedInfo(pData[i + 6], (_FLASH_INFO_0x90_ID_CODE_0 + j)) == 0x00)
                            {
                                break;
                            }

                            if(pData[0 + j] != CFlashGetFlashDetailedInfo(pData[i + 6], (_FLASH_INFO_0x90_ID_CODE_0 + j)))
                            {
                                bIsUnequal = _TRUE;
                                break;
                            }
                        }

                        if(j == 0)
                        {
                            // Current flash type do not support RDID(0x90)
                            continue;

                        }
                        else
                        {

                            if(bIsUnequal == _FALSE)
                            {
                                bMatchedFlashType = _TRUE;

                                // Matched Flash Type Index
                                pData[0] = pData[i + 6];
                                break;
                            }
                            else
                            {
                                // Current flash type mismatches, check next flash type
                                continue;
                            }
                        }
                    }

                    if(bMatchedFlashType == _TRUE)
                    {
                        // Find the matched Flash Type supported by F/W
                        return pData[0];
                    }
                    else
                    {
                        // Don't find the matched Flash Type with RDID(0x90)
                        // return the first matched flash type with JEDEC ID
                        return pData[6];
                    }
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////
    // Use RDID(0x90) Instruction first to get Flash Manufacture ID, Device ID //
    /////////////////////////////////////////////////////////////////////////////
    if(CFlashMatchFlashIDCode(0x90, &pData[0], &pData[1], &pData[2]))
    {
        return pData[0];
    }

    /////////////////////////////////////////////////////////////////////////////
    // Use RDID(0xAB) Instruction first to get Flash Manufacture ID, Device ID //
    /////////////////////////////////////////////////////////////////////////////
    if(CFlashMatchFlashIDCode(0xAB, &pData[0], &pData[1], &pData[2]))
    {
        return pData[0];
    }

    return 0xFF; // Don't Find a matched Flash type
}

bit  CFlashReadFlashIDCode(BYTE RDIDOPCode, BYTE *pReadID0Array, BYTE *pReadID1Array, BYTE *pReadID2Array)
{
    BYTE i = 0;

    switch(RDIDOPCode)
    {
        case 0x9F:

            //////////////////////////////////////////////////////////////////////////
            // Use JEDECID Instruction to get Flash Manufacture ID, Device ID       //
            //////////////////////////////////////////////////////////////////////////
            MCU_COMM_INST_EN_FF60 = 0x46;
            MCU_COMM_OP_CODE_FF61 = RDIDOPCode;
            MCU_COMM_INST_EN_FF60 = 0x47;
            (*pReadID0Array) = MCU_COMM_INST_READ_P0_FF67;
            (*pReadID1Array) = MCU_COMM_INST_READ_P1_FF68;
            (*pReadID2Array) = MCU_COMM_INST_READ_P2_FF69;

            // Repeatedly Read Flash ID Code and Check Flash ID Code data between twice RDID instructions
            for(i = 0; i < 10; i++)
            {
                MCU_COMM_INST_EN_FF60 = 0x46;
                MCU_COMM_OP_CODE_FF61 = RDIDOPCode;
                MCU_COMM_INST_EN_FF60 = 0x47;
                pData[3] = MCU_COMM_INST_READ_P0_FF67;
                pData[4] = MCU_COMM_INST_READ_P1_FF68;
                pData[5] = MCU_COMM_INST_READ_P2_FF69;

                if(((*pReadID0Array) == pData[3]) &&
                   ((*pReadID1Array) == pData[4]) &&
                   ((*pReadID2Array) == pData[5]))
                {
                    break;
                }
                else
                {
                    (*pReadID0Array) = pData[3];
                    (*pReadID1Array) = pData[4];
                    (*pReadID2Array) = pData[5];
                }
            }

            if(i >= 10)
            {
                return _FALSE;
            }

        break;

        case 0x90:
        case 0xAB:

            //////////////////////////////////////////////////////////////////////////////////
            // Use RDID(0x90/0xAB) Instruction first to get Flash Manufacture ID, Device ID //
            //////////////////////////////////////////////////////////////////////////////////
            MCU_COMM_INST_EN_FF60 = 0x5E;
            MCU_COMM_OP_CODE_FF61 = RDIDOPCode;
            MCU_FLASH_PROG_ISP0_FF64 = 0x00;
            MCU_FLASH_PROG_ISP1_FF65 = 0x00;
            MCU_FLASH_PROG_ISP2_FF66 = 0x00;
            MCU_COMM_INST_EN_FF60 = 0x5F;

            (*pReadID0Array) = MCU_COMM_INST_READ_P0_FF67;
            (*pReadID1Array) = MCU_COMM_INST_READ_P1_FF68;
            (*pReadID2Array) = MCU_COMM_INST_READ_P2_FF69;

            for(i = 0; i < 10; i++)
            {
                MCU_COMM_INST_EN_FF60 = 0x5E;
                MCU_COMM_OP_CODE_FF61 = RDIDOPCode;
                MCU_FLASH_PROG_ISP0_FF64 = 0x00;
                MCU_FLASH_PROG_ISP1_FF65 = 0x00;
                MCU_FLASH_PROG_ISP2_FF66 = 0x00;
                MCU_COMM_INST_EN_FF60 = 0x5F;

                pData[3] = MCU_COMM_INST_READ_P0_FF67;
                pData[4] = MCU_COMM_INST_READ_P1_FF68;
                pData[5] = MCU_COMM_INST_READ_P2_FF69;

                if(((*pReadID0Array) == pData[3]) &&
                   ((*pReadID1Array) == pData[4]) &&
                   ((*pReadID2Array) == pData[5]))
                {
                    break;
                }
                else
                {
                    (*pReadID0Array) = pData[3];
                    (*pReadID1Array) = pData[4];
                    (*pReadID2Array) = pData[5];
                }
            }

            if(i >= 10)
            {
                return _FALSE;
            }

            break;
    }

    return _TRUE;
}

bit  CFlashMatchFlashIDCode(BYTE RDIDOPCode, BYTE *pReadID0Array, BYTE *pReadID1Array, BYTE *pReadID2Array)
{
    bit bMatchedFlashType = _FALSE;
    BYTE i = 0;

    (*pReadID0Array) = 0x00;
    (*pReadID1Array) = 0x00;
    (*pReadID2Array) = 0x00;

    if(CFlashReadFlashIDCode(RDIDOPCode, pReadID0Array, pReadID1Array, pReadID2Array))
    {
        bMatchedFlashType = _FALSE;

        for(i = 0; i < CFlashGetFlashSupportInfo(_FLASH_SUPPORT_INFO_SUPPORT_COUNT); i++)
        {
            switch(RDIDOPCode)
            {
                case 0x90:
                    pData[13] = CFlashGetFlashDetailedInfo(i, _FLASH_INFO_0x90_ID_CODE_0);
                    pData[14] = CFlashGetFlashDetailedInfo(i, _FLASH_INFO_0x90_ID_CODE_1);
                    pData[15] = CFlashGetFlashDetailedInfo(i, _FLASH_INFO_0x90_ID_CODE_2);
                    break;

                case 0xAB:
                    pData[13] = CFlashGetFlashDetailedInfo(i, _FLASH_INFO_0xAB_ID_CODE_0);
                    pData[14] = CFlashGetFlashDetailedInfo(i, _FLASH_INFO_0xAB_ID_CODE_1);
                    pData[15] = CFlashGetFlashDetailedInfo(i, _FLASH_INFO_0xAB_ID_CODE_2);
                    break;
            }

            if((pData[13] != 0x00) || (pData[14] != 0x00) || (pData[15] != 0x00))
            {
                if(pData[13] != 0x00)
                {
                    if(pData[14] == 0x00)
                    {
                        if((*pReadID0Array) == pData[13])
                        {
                            bMatchedFlashType = _TRUE;

                            // Matched Flash Type Index
                            (*pReadID0Array) = i;
                            break;
                        }
                    }
                    else
                    {
                        if(pData[15] == 0x00)
                        {
                            if(((*pReadID0Array) == pData[13]) &&
                               ((*pReadID1Array) == pData[14]))
                            {
                                bMatchedFlashType = _TRUE;

                                // Matched Flash Type Index
                                (*pReadID0Array) = i;
                                break;
                            }
                        }
                        else
                        {
                            if(((*pReadID0Array) == pData[13]) &&
                               ((*pReadID1Array) == pData[14]) &&
                               ((*pReadID2Array) == pData[15]))
                            {
                                bMatchedFlashType = _TRUE;

                                // Matched Flash Type Index
                                (*pReadID0Array) = i;
                                break;
                            }
                        }
                    }
                }
            }
        }

        if(bMatchedFlashType == _FALSE)
        {
            // Don't find a matched Flash Type supported by F/W
            return _FALSE;
        }
        else
        {
            // Find the matched Flash Type supported by F/W
            return _TRUE;
        }
    }
}
#endif // End of #if(_AUTO_DETECT_FLASH_TYPE == _ON)

#if(_MEMORY_LOCATION == _FLASH)
//--------------------------------------------------
// Description  : Flash Erase
// Input Value  : Number of Page (0 ~ 31)
// Output Value : Return _TURE if succeed
//--------------------------------------------------
bit CFlashErase(BYTE ucPage)
{
    if(ucPage != _MISC_PAGE)
    {
        if((ucPage < _START_PAGE) || (ucPage > _END_PAGE))
        {
            return _FALSE;
        }
    }

    CFlashWREN(ucPage);

    // Sector Erase
    MCU_COMM_INST_EN_FF60 = 0xB8;
    MCU_COMM_OP_CODE_FF61 = CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_SECTOR_ERASE_OPCODE); // Sector Erase OP Code

    // Set WR address
    MCU_FLASH_PROG_ISP0_FF64 = _FLASH_BANK;
    MCU_FLASH_PROG_ISP1_FF65 = (BYTE)(ucPage * _SECTOR_SIZE * 4);
    MCU_FLASH_PROG_ISP2_FF66 = 0x00;

    // Start Bit0
    MCU_COMM_INST_EN_FF60 = MCU_COMM_INST_EN_FF60 | _BIT0;

    // No need to polling, 8051 will halt when common instruction executes
    MCU_COMM_OP_CODE_FF61 = 0xFF;

    CFlashWRDis();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Write Enable Process for Serial Flash
// Input Value  : Number of Page (12 ~ 15)
// Output Value : Return _TURE if succeed
//--------------------------------------------------
bit CFlashWREN(BYTE ucPage)
{
    BYTE ucWRSR = 0x00;

    if(ucPage != _MISC_PAGE)
    {
        if((ucPage < _START_PAGE) || (ucPage > _END_PAGE))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }
    }

    // V016 System Patch Note (28) Modify 20100831 Start
    // Patch Reason : Clear WDT when execute Flash instruction
    MCU_WATCHDOG_TIMER_FFEA |= 0x40; // Clr WDT.
    // V016 System Patch Note (28) Modify 20100831 End

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    if((GET_FLASH_TYPE_INDEX() == _FLASH_Pm25LV020) ||
       (GET_FLASH_TYPE_INDEX() == _FLASH_Pm25LD020))
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_FLASH_TYPE == _FLASH_Pm25LV020) || (_FLASH_TYPE == _FLASH_Pm25LD020))
            // Program OP Code
            MCU_PROG_OP_CODE_FF6D = 0x02;

            // Sector Unprotect Enable
            MCU_COMM_INST_EN_FF60 = 0x78;

            // Set OP code
            MCU_COMM_OP_CODE_FF61 = CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WREN_OPCODE);

            // Set WR address
            MCU_FLASH_PROG_ISP0_FF64 = _FLASH_BANK;
            MCU_FLASH_PROG_ISP1_FF65 = (BYTE)(ucPage * _SECTOR_SIZE * 4);
            MCU_FLASH_PROG_ISP2_FF66 = 0x00;

            // Start Bit0
            MCU_COMM_INST_EN_FF60 = MCU_COMM_INST_EN_FF60 | _BIT0;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _TRUE;
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else if((GET_FLASH_TYPE_INDEX() == _FLASH_W25X20A) ||
            (GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2025))
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_FLASH_TYPE == _FLASH_W25X20A) || (_FLASH_TYPE == _FLASH_MX25L2025))
        ucPage = ucPage;
        MCU_PROG_OP_CODE_FF6D = 0x02;

        if(!CFlashSetWREN(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WREN_OPCODE), 40))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }

        if(!CFlashSetWRSR(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WRSR_UNPROTECT), 40, 0x00))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            return _FALSE;
        }

        // Disable Command OP code
        MCU_COMM_OP_CODE_FF61 = 0xFF;
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else if(GET_FLASH_TYPE_INDEX() == _FLASH_SST25LF020A)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_FLASH_TYPE == _FLASH_SST25LF020A))
        ucPage = ucPage;
        MCU_PROG_OP_CODE_FF6D = 0x02;

        if(!CFlashSetWREN(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WREN_OPCODE), 40))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }

        if(!CFlashSetWRSR(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WRSR_UNPROTECT), 40, 0x01))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            return _FALSE;
        }

        // Disable Command OP code
        MCU_COMM_OP_CODE_FF61 = 0xFF;
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_FLASH_TYPE == _FLASH_MX25L2026))
        MCU_PROG_OP_CODE_FF6D = 0x02;

        if(!CFlashSetWREN(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WREN_OPCODE), 40))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }

        if(!CFlashSetWRSR(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WRSR_UNPROTECT), 40, 0x00))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }

        if(!CFlashSetWREN(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WREN_OPCODE), 40))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }

        switch(ucPage)
        {
            case _START_PAGE:
            case _START_PAGE + 1:
                ucWRSR = 0x0C; // BP0 = BP1 = 1, BP2 = 0
                break;

            case _END_PAGE:
                ucWRSR = 0x14; // BP0 =1, BP1 = 0, BP2 = 1
                break;

            case _MISC_PAGE:
                ucWRSR = 0x18; // BP0 = 0, BP1 = BP2 = 1
                break;

            default:
                // Disable Program OP code
                MCU_PROG_OP_CODE_FF6D = 0xFF;

                // Disable Command OP code
                MCU_COMM_OP_CODE_FF61 = 0xFF;

                return _FALSE;
        }

        if(!CFlashSetWRSR(ucWRSR, 40, 0x00))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }

        if(!CFlashSetWREN(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WREN_OPCODE), 40))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }

        // Disable Command OP code
        MCU_COMM_OP_CODE_FF61 = 0xFF;
        MCU_FLASH_PROG_ISP0_FF64 = 0x03;
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else if(GET_FLASH_TYPE_INDEX() == _FLASH_EN25F20)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_FLASH_TYPE == _FLASH_EN25F20))
        MCU_PROG_OP_CODE_FF6D = 0x02;

        if(!CFlashSetWREN(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WREN_OPCODE), 40))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }

        switch(ucPage)
        {
            case _START_PAGE:
            case (_START_PAGE + 1):
                ucWRSR = 0x14;
                break;

            case _END_PAGE:
            case _MISC_PAGE:
                ucWRSR = 0x18;
                break;

            default:
                // Disable Program OP code
                MCU_PROG_OP_CODE_FF6D = 0xFF;

                // Disable Command OP code
                MCU_COMM_OP_CODE_FF61 = 0xFF;

                return _FALSE;
        }

        if(!CFlashSetWRSR(ucWRSR, 40, 0x00))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            return _FALSE;
        }

        // Disable Command OP code
        MCU_COMM_OP_CODE_FF61 = 0xFF;
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else
    {
        return _FALSE;
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Write Disable Process for Serial Flash
// Input Value  : None
// Output Value : Return _TURE if succeed
//--------------------------------------------------
bit CFlashWRDis(void)
{
    // V016 System Patch Note (28) Modify 20100831 Start
    // Patch Reason : Clear WDT when execute Flash instruction
    MCU_WATCHDOG_TIMER_FFEA |= 0x40; // Clr WDT.
    // V016 System Patch Note (28) Modify 20100831 End

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    if((GET_FLASH_TYPE_INDEX() == _FLASH_Pm25LV020) ||
       (GET_FLASH_TYPE_INDEX() == _FLASH_Pm25LD020))
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_FLASH_TYPE == _FLASH_Pm25LV020) || (_FLASH_TYPE == _FLASH_Pm25LD020))
        // Sector Unprotect Disable
        MCU_COMM_INST_EN_FF60 = 0x60;

        // Set OP code
        MCU_COMM_OP_CODE_FF61 = CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WRDIS_OPCODE);

        // Start Bit0
        MCU_COMM_INST_EN_FF60 = MCU_COMM_INST_EN_FF60 | _BIT0;

        // Disable Program OP code
        MCU_PROG_OP_CODE_FF6D = 0xFF;

        // Disable Command OP code
        MCU_COMM_OP_CODE_FF61 = 0xFF;
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else if((GET_FLASH_TYPE_INDEX() == _FLASH_W25X20A)
         || (GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
         || (GET_FLASH_TYPE_INDEX() == _FLASH_EN25F20)
         || (GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2025))
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_FLASH_TYPE == _FLASH_W25X20A) \
    || (_FLASH_TYPE == _FLASH_MX25L2026) || (_FLASH_TYPE == _FLASH_EN25F20) \
    || (_FLASH_TYPE == _FLASH_MX25L2025))
        if(!CFlashSetWRSR(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WRSR_PROTECT), 40, 0x00))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }


        if(!CFlashSetWREN(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WRDIS_OPCODE), 40))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }

        // Disable Program OP code
        MCU_PROG_OP_CODE_FF6D = 0xFF;

        // Disable Command OP code
        MCU_COMM_OP_CODE_FF61 = 0xFF;
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else if(GET_FLASH_TYPE_INDEX() == _FLASH_SST25LF020A)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_FLASH_TYPE == _FLASH_SST25LF020A))
        if(!CFlashSetWRSR(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WRSR_PROTECT), 40, 0x01))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }


        if(!CFlashSetWREN(CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WRDIS_OPCODE), 40))
        {
            // Disable Program OP code
            MCU_PROG_OP_CODE_FF6D = 0xFF;

            // Disable Command OP code
            MCU_COMM_OP_CODE_FF61 = 0xFF;

            return _FALSE;
        }

        // Disable Program OP code
        MCU_PROG_OP_CODE_FF6D = 0xFF;

        // Disable Command OP code
        MCU_COMM_OP_CODE_FF61 = 0xFF;
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else
    {
        return _FALSE;
    }
#endif

    return _TRUE;
}

#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_FLASH_TYPE == _FLASH_W25X20A) \
    || (_FLASH_TYPE == _FLASH_MX25L2026) || (_FLASH_TYPE == _FLASH_EN25F20) \
    || (_FLASH_TYPE == _FLASH_MX25L2025) || (_FLASH_TYPE == _FLASH_SST25LF020A))
//--------------------------------------------------
// Description  : WREN instructions for Serial Flash
// Input Value  : ucOpCode        --> WREN instruction op code
//                usTimeOut       --> Timeout number (Max: 255 ms)
// Output Value : Return _TURE if succeed
//--------------------------------------------------
bit CFlashSetWREN(BYTE ucOpCode, WORD usTimeOut)
{
    // WREN instructions
    MCU_COMM_INST_EN_FF60 = 0x20;
    MCU_COMM_OP_CODE_FF61 = ucOpCode;
    MCU_COMM_INST_EN_FF60 = MCU_COMM_INST_EN_FF60 | _BIT0;

    usTimeOut = usTimeOut;

    // No need to polling, 8051 will halt when common instruction executes
    return _TRUE;
}

//--------------------------------------------------
// Description  : WRSR instructions for Serial Flash
// Input Value  : ucWRSR          --> Value written to Flash Status Reg
//                usTimeOut       --> Timeout number (Max: 255 ms)
//                ucIsSST         --> SST Flash
// Output Value : Return _TURE if succeed
//--------------------------------------------------
bit CFlashSetWRSR(BYTE ucWRSR, WORD usTimeOut, BYTE ucIsSST)
{
    CMiscConfigureFlashWPPinHigh();

    usTimeOut = usTimeOut;

    //WRSR
    if(ucIsSST == 0x01)
    {
        MCU_COMM_INST_EN_FF60 = 0x88;
    }
    else
    {
        MCU_COMM_INST_EN_FF60 = 0x68;
    }

    MCU_COMM_OP_CODE_FF61 = 0x01;
    MCU_FLASH_PROG_ISP0_FF64 = ucWRSR;
    MCU_COMM_INST_EN_FF60 = MCU_COMM_INST_EN_FF60 | _BIT0;

    // No need to polling, 8051 will halt when common instruction executes

    // Disable Command OP code
    MCU_COMM_OP_CODE_FF61 = 0xFF;

    CMiscConfigureFlashWPPinLow();

    return _TRUE;
}
#endif

#if((_EDID_PRO == _ON) || (_FLASH_XDATA_ACCESS == _ON))
//--------------------------------------------------
// Description  : Backup _MISC_PAGE and erase _MISC_PAGE
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CFlashInitialMISCPageStart()
{
    // Find a free page
    //g_ucFlashFreePage = CFlashFreePageLocateAtStartup();

    // Back up MISC PAGE
    CFlashBackupMISCPage();

    // Erase the MISC PAGE
    CFlashErase(_MISC_PAGE);
}

//--------------------------------------------------
// Description  : Restore _MISC_PAGE if needed
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CFlashInitialMISCPageEnd()
{
    /////////////////////////////////////////
    // Check EDID block if need to recover //
    /////////////////////////////////////////
#if(_EDID_PRO == _ON)
    if(CFlashCheckIsAllFF(&(MCU_FLASH[_FLASH_DATA_SPACE]), _EDID_TOTAL_SIZE))
    {
        CFlashLoadEDIDData(_FLASH_MISC, g_ucFlashFreePage);
    }
#endif // End of #if(_EDID_PRO == _ON)

    /////////////////////////////////////////
    // Check HDCP block if need to recover //
    /////////////////////////////////////////
#if((_EMBEDDED_HDCP_KEY == _ON) && (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH))
    if(CFlashCheckIsAllFF(&(MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE]), _HDCP_KEY_SIZE))
    {
        // Recover HDCP KEY data from free page
        CFlashLoadHDCPKeyData(_FLASH_MISC, g_ucFlashFreePage);
    }
#endif // End of #if((_EMBEDDED_HDCP_KEY == _ON) && (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH))

    ////////////////////////////////////////
    // Check LUT block if need to recover //
    ////////////////////////////////////////
#if((_GAMMA_FUNCTION == _ON) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH))
    if(CFlashCheckIsAllFF(&(MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE]), (_GAMMA_LUT_FLASH_CHANNEL_SIZE * 3)))
    {
        CFlashLoadLUTTableData(_FLASH_MISC, g_ucFlashFreePage);
    }
#endif // End of #if((_GAMMA_FUNCTION == _ON) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH))

    // Update Version Code
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
        CFlashWREN(_MISC_PAGE);
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR] = MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR];

        CFlashWREN(_MISC_PAGE);
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 1] = MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 1];

        CFlashWREN(_MISC_PAGE);
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 2] = MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 2];

        CFlashWREN(_MISC_PAGE);
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 3] = MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 3];

        CFlashWREN(_MISC_PAGE);
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 4] = MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 4];
        CFlashWRDis();
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
        CFlashWREN(_MISC_PAGE);
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR] = MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR];
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 1] = MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 1];
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 2] = MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 2];
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 3] = MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 3];
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 4] = MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 4];
        CFlashWRDis();
#endif
    }
}

//--------------------------------------------------
// Description  : Check if all byte is 0xFF
// Input Value  : pArray : Pointer of data buffer
//                usSize : Length of data buffer
// Output Value : Return _TRUE if succeed
//--------------------------------------------------
bit  CFlashCheckIsAllFF(BYTE *pArray, WORD usSize)
{
    WORD i = 0;

    for(i = 0; i < usSize; i++)
    {
        if((*(pArray + i)) != 0xFF)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Backup the MISC PAGE in the free page
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CFlashBackupMISCPage(void)
{
    WORD i = 0;

    // Erase the free page first just in case
    CFlashErase(GET_ABSOLUTE_PAGE_NUM(g_ucFlashFreePage));

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))

#if(_EDID_PRO == _ON)
        // Back up EDID data
        for(i = 0; i < _EDID_TOTAL_SIZE; i++)
        {
            CFlashWREN(GET_ABSOLUTE_PAGE_NUM(g_ucFlashFreePage));
            MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + i] = MCU_FLASH[_FLASH_DATA_SPACE + i];
        }
#endif

#if((_EMBEDDED_HDCP_KEY == _ON) && (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH))
        // Back up HDCP Key data
        for(i = 0; i < _HDCP_KEY_SIZE; i++)
        {
            CFlashWREN(GET_ABSOLUTE_PAGE_NUM(g_ucFlashFreePage));
            MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _EDID_TOTAL_SIZE + i] = MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE + i];
        }
#endif

#if((_GAMMA_FUNCTION == _ON) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH))
        // Back up LUT Table data
        for(i = 0; i < (_GAMMA_LUT_FLASH_CHANNEL_SIZE * 3); i++)
        {
            CFlashWREN(GET_ABSOLUTE_PAGE_NUM(g_ucFlashFreePage));
            MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE + i] = MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE + i];
        }
#endif

        // Update Version Code
        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(g_ucFlashFreePage));
        MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR] = MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR];

        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(g_ucFlashFreePage));
        MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 1] = MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 1];

        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(g_ucFlashFreePage));
        MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 2] = MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 2];

        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(g_ucFlashFreePage));
        MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 3] = MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 3];

        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(g_ucFlashFreePage));
        MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 4] = MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 4];
        CFlashWRDis();

#endif // End of #if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))

        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(g_ucFlashFreePage));

#if(_EDID_PRO == _ON)
        memcpy(&(MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE]), &(MCU_FLASH[_FLASH_DATA_SPACE]), _EDID_TOTAL_SIZE); // Back up EDID data
#endif

#if((_EMBEDDED_HDCP_KEY == _ON) && (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH))
        memcpy(&(MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _EDID_TOTAL_SIZE]), &(MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE]), _HDCP_KEY_SIZE); // Back up HDCP Key data
#endif

#if((_GAMMA_FUNCTION == _ON) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH))
        memcpy(&(MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE]), &(MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE]), (_GAMMA_LUT_FLASH_CHANNEL_SIZE * 3)); // Back up LUT Table data
#endif

        // Update Version Code
        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(g_ucFlashFreePage));
        MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR] = MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR];
        MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 1] = MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 1];
        MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 2] = MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 2];
        MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 3] = MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 3];
        MCU_FLASH[g_ucFlashFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 4] = MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 4];
        CFlashWRDis();
#endif // End of #if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
    }
}
#endif // End of #if(_FLASH_XDATA_ACCESS == _ON)

//--------------------------------------------------
// Description  : Recover the MISC PAGE in the free page
// Input Value  : the free page which back up the MISC page
// Output Value : None
//--------------------------------------------------
void CFlashRecoverMISCPage(BYTE ucFreePage)
{
    //Erase MISC page first
    CFlashErase(_MISC_PAGE);

#if(_EDID_PRO == _ON)
    CFlashLoadEDIDData(_FLASH_MISC, ucFreePage);
#endif

#if((_EMBEDDED_HDCP_KEY == _ON) && (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH))
    CFlashLoadHDCPKeyData(_FLASH_MISC, ucFreePage);
#endif

#if((_GAMMA_FUNCTION == _ON) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH))
    CFlashLoadLUTTableData(_FLASH_MISC, ucFreePage);
#endif

    //Update Version Code
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(ucFreePage));
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR] = MCU_FLASH[ucFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR];

        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(ucFreePage));
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 1] = MCU_FLASH[ucFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 1];

        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(ucFreePage));
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 2] = MCU_FLASH[ucFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 2];

        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(ucFreePage));
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 3] = MCU_FLASH[ucFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 3];

        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(ucFreePage));
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 4] = MCU_FLASH[ucFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 4];
        CFlashWRDis();
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
        CFlashWREN(GET_ABSOLUTE_PAGE_NUM(ucFreePage));
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR] = MCU_FLASH[ucFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR];
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 1] = MCU_FLASH[ucFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 1];
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 2] = MCU_FLASH[ucFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 2];
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 3] = MCU_FLASH[ucFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 3];
        MCU_FLASH[_FLASH_DATA_SPACE + _FLASH_VERSION_CODE_PAGE_ADDR - 4] = MCU_FLASH[ucFreePage * _PAGE_SIZE + _FLASH_VERSION_CODE_PAGE_ADDR - 4];
        CFlashWRDis();
#endif
    }
}

//--------------------------------------------------
// Description  : Load default data to MISC Page
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CFlashLoadMISCPageDefault(void)
{
    /////////////////////////////////////////
    // Load default EDID Data to MISC PAGE //
    /////////////////////////////////////////
#if(_EDID_PRO == _ON)
    CFlashLoadEDIDData(_DEFAULT_MISC, g_ucFlashFreePage);
#endif

    /////////////////////////////////////////
    // Load default HDCP Data to MISC PAGE //
    /////////////////////////////////////////
#if((_EMBEDDED_HDCP_KEY == _ON) && (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH))
    CFlashLoadHDCPKeyData(_DEFAULT_MISC, g_ucFlashFreePage);
#endif

    /////////////////////////////////////////
    // Load default LUT Data to MISC PAGE  //
    /////////////////////////////////////////
#if((_GAMMA_FUNCTION == _ON) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH))
    CFlashLoadLUTTableData(_DEFAULT_MISC, g_ucFlashFreePage);
#endif

}
#endif // End of #if(_MEMORY_LOCATION == _FLASH)

#if((_MEMORY_LOCATION == _FLASH) && (_EMBEDDED_HDCP_KEY == _ON) && (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH))
//--------------------------------------------------
// Description  : Load HDCP data to _MISC_PAGE
// Input Value  : ucTable, Default HDCP Table or Flash Data
//                ucFreePage, free page index in relative format
// Output Value : None
//--------------------------------------------------
void CFlashLoadHDCPKeyData(BYTE ucTable, BYTE ucFreePage)
{
    WORD usCount = 0;

    if(ucTable == _DEFAULT_MISC)
    {
        CAdjustGetDefaultHDCPKeyDatafromTable();
    }
    else if(ucTable == _FLASH_MISC)
    {
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
        if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
        {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
            for(usCount = 0; usCount < _HDCP_KEY_SIZE; usCount++)
            {
                CFlashWREN(_MISC_PAGE);
                MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE + usCount] = MCU_FLASH[ucFreePage * _PAGE_SIZE + _EDID_TOTAL_SIZE + usCount];
            }

            CFlashWRDis();
#endif
        }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
        else
#endif
        {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
           CFlashWREN(_MISC_PAGE);
           memcpy(&(MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE]), &(MCU_FLASH[ucFreePage * _PAGE_SIZE + _EDID_TOTAL_SIZE]), _HDCP_KEY_SIZE);
           CFlashWRDis();
#endif
        }

    }
}
#endif // End of #if((_EMBEDDED_HDCP_KEY == _ON) && (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH))

#if((_MEMORY_LOCATION == _FLASH) && (_GAMMA_FUNCTION == _ON) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH))
//--------------------------------------------------
// Description  : Load LUT data to _MISC_PAGE
// Input Value  : ucTable, Default LUT Table or Flash Data
//                ucFreePage, free page index in relative format
// Output Value : None
//--------------------------------------------------
void CFlashLoadLUTTableData(BYTE ucTable, BYTE ucFreePage)
{
    WORD usCount = 0;

    if(ucTable == _DEFAULT_MISC)
    {
        CAdjustGetDefaultLUTTableDatafromTable();
    }
    else if(ucTable == _FLASH_MISC)
    {
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
        if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
        {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
            for(usCount = 0; usCount < (_GAMMA_LUT_FLASH_CHANNEL_SIZE * 3); usCount++)
            {
                CFlashWREN(_MISC_PAGE);
                MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE + usCount] = MCU_FLASH[ucFreePage * _PAGE_SIZE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE + usCount];
            }

            CFlashWRDis();
#endif
        }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
        else
#endif
        {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
           CFlashWREN(_MISC_PAGE);
           memcpy(&(MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE]), &(MCU_FLASH[ucFreePage * _PAGE_SIZE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE]), (_GAMMA_LUT_FLASH_CHANNEL_SIZE * 3));
           CFlashWRDis();
#endif
        }
    }
}
#endif // End of #if((_MEMORY_LOCATION == _FLASH) && (_GAMMA_FUNCTION == _ON) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH))


#if((_MEMORY_LOCATION == _FLASH) && (_EDID_PRO == _ON))
//--------------------------------------------------
// Description  : Save Data of DDC RAM to Flash.
// Input Value  : None
// Output Value : _TRUE : success
//--------------------------------------------------
void CFlashSaveDDCData(void)
{
    bit bVGAEDIDVerifyOK = _TRUE;
    bit bDDC2EDIDVerifyOK = _TRUE;
    bit bDDC3EDIDVerifyOK = _TRUE;

    if((CFlashVerifyDDCRAMEDID(MCU_DDCRAM_A0, _ADC_EDID_SIZE) == _FALSE))
    {
        bVGAEDIDVerifyOK = _FALSE;
        CFlashLoadMISCPage2EDIDDDCRAM(_VGA_EDID);
    }

#if((_DDC_CHANNEL_FOR_D0 == _DDC2) || (_DDC_CHANNEL_FOR_D1 == _DDC2))
    if(CFlashVerifyDDCRAMEDID(MCU_DDCRAM_DDC2, _DDC2_EDID_SIZE) == _FALSE)
    {
        bDDC2EDIDVerifyOK = _FALSE;
        CFlashLoadMISCPage2EDIDDDCRAM(_DDC2_EDID);
    }
#endif

#if((_DDC_CHANNEL_FOR_D0 == _DDC3) || (_DDC_CHANNEL_FOR_D1 == _DDC3))
    if(CFlashVerifyDDCRAMEDID(MCU_DDCRAM_DDC3, _DDC3_EDID_SIZE) == _FALSE)
    {
        bDDC3EDIDVerifyOK = _FALSE;
        CFlashLoadMISCPage2EDIDDDCRAM(_DDC3_EDID);
    }
#endif

    if((bVGAEDIDVerifyOK == _TRUE)
#if((_DDC_CHANNEL_FOR_D0 == _DDC2) || (_DDC_CHANNEL_FOR_D1 == _DDC2))
        && (bDDC2EDIDVerifyOK == _TRUE)
#endif
#if((_DDC_CHANNEL_FOR_D0 == _DDC3) || (_DDC_CHANNEL_FOR_D1 == _DDC3))
        && (bDDC3EDIDVerifyOK == _TRUE)
#endif
       )
    {
        // Initial _MISC_PAGE
        CFlashInitialMISCPageStart();

        // Save EDID DDCRAM to _MISC_PAGE
        CFlashSaveDDCRAM2MISCPage();

        // Restore _MISC_PAGE
        CFlashInitialMISCPageEnd();
    }
}

//--------------------------------------------------
// Description  : Verify EDID Content in a specified memory space
// Input Value  : pDDCRAM : Source Data pointer;
//                usSize  : EDID Size
// Output Value : _TRUE : Verify OK
//                _FALSE: Verify Failed
//--------------------------------------------------
bit CFlashVerifyDDCRAMEDID(BYTE *pucDDCRAM, WORD usSize)
{
    BYTE ucChksum = 0;
    WORD usCount = 0;

    for(usCount = 0; usCount < usSize; usCount++)
    {
        ucChksum += pucDDCRAM[usCount];
    }

    // Checksum Check & EDID Header Check
    if((ucChksum != 0)
    || (pucDDCRAM[0] != 0x00) || (pucDDCRAM[1] != 0xFF)
    || (pucDDCRAM[2] != 0xFF) || (pucDDCRAM[3] != 0xFF)
    || (pucDDCRAM[4] != 0xFF) || (pucDDCRAM[5] != 0xFF)
    || (pucDDCRAM[6] != 0xFF) || (pucDDCRAM[7] != 0x00))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Load EDID data to _MISC_PAGE
// Input Value  : ucTable, Default EDID Table or Flash Data
//                ucFreePag, free page index in relative format
// Output Value : None
//--------------------------------------------------
void CFlashLoadEDIDData(BYTE ucTable, BYTE ucFreePage)
{
    WORD i = 0;
    BYTE * pucEDIDArray = NULL;

    if(ucTable == _DEFAULT_MISC)
    {
        pucEDIDArray = tEDID_TABLE_A0;
    }

    else if(ucTable == _FLASH_MISC)
    {
        pucEDIDArray = &(MCU_FLASH[ucFreePage * _PAGE_SIZE]);
    }

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
        for(i = 0; i < _ADC_EDID_SIZE; i++)
        {
            CFlashWREN(_MISC_PAGE);
            MCU_FLASH[_FLASH_DATA_SPACE + i] = pucEDIDArray[i];
        }

        CFlashWRDis();
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
        CFlashWREN(_MISC_PAGE);
        memcpy(&(MCU_FLASH[_FLASH_DATA_SPACE]), pucEDIDArray, _ADC_EDID_SIZE);
        CFlashWRDis();
#endif
    }

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

    if(ucTable == _DEFAULT_MISC)
    {
#if(_DDC_CHANNEL_FOR_D0 == _DDC2)
        pucEDIDArray = tEDID_TABLE_D0;
#elif(_DDC_CHANNEL_FOR_D0 == _DDC3)
        pucEDIDArray = tEDID_TABLE_D1;
#else
        #error No Settings Here!!!
#endif
    }
    else
    {
        pucEDIDArray = &(MCU_FLASH[ucFreePage * _PAGE_SIZE + _ADC_EDID_SIZE]);
    }

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
        for(i = 0; i < _DDC2_EDID_SIZE; i++)
        {
            CFlashWREN(_MISC_PAGE);
            MCU_FLASH[_FLASH_DATA_SPACE + _ADC_EDID_SIZE + i] = pucEDIDArray[i];
        }

        CFlashWRDis();
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
        CFlashWREN(_MISC_PAGE);
        memcpy(&(MCU_FLASH[_FLASH_DATA_SPACE + _ADC_EDID_SIZE]), pucEDIDArray, _DDC2_EDID_SIZE);
        CFlashWRDis();
#endif
    }

#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

    if(ucTable == _DEFAULT_MISC)
    {
#if(_DDC_CHANNEL_FOR_D1 == _DDC3)
        pucEDIDArray = tEDID_TABLE_D1;
#elif(_DDC_CHANNEL_FOR_D1 == _DDC2)
        pucEDIDArray = tEDID_TABLE_D0;
#else
        #error No Settings Here!!!
#endif
    }
    else
    {
        pucEDIDArray = &(MCU_FLASH[ucFreePage * _PAGE_SIZE + _ADC_EDID_SIZE + _DDC2_EDID_SIZE]);
    }

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
        for(i = 0; i < _DDC3_EDID_SIZE; i++)
        {
            CFlashWREN(_MISC_PAGE);
            MCU_FLASH[_FLASH_DATA_SPACE + _ADC_EDID_SIZE + _DDC2_EDID_SIZE + i] = pucEDIDArray[i];
        }

        CFlashWRDis();
#endif
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
        CFlashWREN(_MISC_PAGE);
        memcpy(&(MCU_FLASH[_FLASH_DATA_SPACE + _ADC_EDID_SIZE + _DDC2_EDID_SIZE]), pucEDIDArray, _DDC3_EDID_SIZE);
        CFlashWRDis();
#endif
    }
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

}

//--------------------------------------------------
// Description  : Save EDID data from _MISC_PAGE to DDCRAM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CFlashLoadMISCPage2DDCRAM(void)
{
    CFlashLoadMISCPage2EDIDDDCRAM(_VGA_EDID);

    CFlashLoadMISCPage2EDIDDDCRAM(_DDC2_EDID);

    CFlashLoadMISCPage2EDIDDDCRAM(_DDC3_EDID);
}

//--------------------------------------------------
// Description  : Save EDID data from _MISC_PAGE to DDCRAM
// Input Value  : ucDDCRAMType : EDID DDCRAM type index
// Output Value : None
//--------------------------------------------------
void CFlashLoadMISCPage2EDIDDDCRAM(BYTE ucDDCRAMType)
{
   switch(ucDDCRAMType)
    {
        case _VGA_EDID:
            memcpy(MCU_DDCRAM_A0, &(MCU_FLASH[_FLASH_DATA_SPACE]), _ADC_EDID_SIZE);
            break;

#if((_DDC_CHANNEL_FOR_D0 == _DDC2) || (_DDC_CHANNEL_FOR_D1 == _DDC2))
        case _DDC2_EDID:
            memcpy(MCU_DDCRAM_DDC2, &(MCU_FLASH[_FLASH_DATA_SPACE + _ADC_EDID_SIZE]), _DDC2_EDID_SIZE);
            break;
#endif

#if((_DDC_CHANNEL_FOR_D0 == _DDC3) || (_DDC_CHANNEL_FOR_D1 == _DDC3))
        case _DDC3_EDID:
            memcpy(MCU_DDCRAM_DDC3, &(MCU_FLASH[_FLASH_DATA_SPACE + _ADC_EDID_SIZE + _DDC2_EDID_SIZE]), _DDC3_EDID_SIZE);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Save DDCRAM data to the _MISC_PAGE
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CFlashSaveDDCRAM2MISCPage(void)
{
    CFlashSaveEDIDDDCRAM2MISCPage(_VGA_EDID);

    CFlashSaveEDIDDDCRAM2MISCPage(_DDC2_EDID);

    CFlashSaveEDIDDDCRAM2MISCPage(_DDC3_EDID);
}

//--------------------------------------------------
// Description  : Save DDCRAM data to the _MISC_PAGE
// Input Value  : ucDDCRAMType : EDID DDCRAM type index
// Output Value : None
//--------------------------------------------------
void CFlashSaveEDIDDDCRAM2MISCPage(BYTE ucDDCRAMType)
{
    WORD usCount = 0;

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    if(GET_FLASH_TYPE_INDEX() == _FLASH_MX25L2026)
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
        switch(ucDDCRAMType)
        {
            case _VGA_EDID:
                for(usCount = 0; usCount < _ADC_EDID_SIZE; usCount++)
                {
                    CFlashWREN(_MISC_PAGE);
                    MCU_FLASH[_FLASH_DATA_SPACE + usCount] = MCU_DDCRAM_A0[usCount];
                }

                CFlashWRDis();
                break;

#if((_DDC_CHANNEL_FOR_D0 == _DDC2) || (_DDC_CHANNEL_FOR_D1 == _DDC2))
            case _DDC2_EDID:

                for(usCount = 0; usCount < _DDC2_EDID_SIZE; usCount++)
                {
                    CFlashWREN(_MISC_PAGE);
                    MCU_FLASH[_FLASH_DATA_SPACE + _ADC_EDID_SIZE + usCount] = MCU_DDCRAM_DDC2[usCount];
                }

                CFlashWRDis();
                break;
#endif

#if((_DDC_CHANNEL_FOR_D0 == _DDC3) || (_DDC_CHANNEL_FOR_D1 == _DDC3))
            case _DDC3_EDID:

                for(usCount = 0; usCount < _DDC3_EDID_SIZE; usCount++)
                {
                    CFlashWREN(_MISC_PAGE);
                    MCU_FLASH[_FLASH_DATA_SPACE + _ADC_EDID_SIZE + _DDC2_EDID_SIZE + usCount] = MCU_DDCRAM_DDC3[usCount];
                }

                CFlashWRDis();
                break;
#endif

            default:
                break;
        }
#endif // End of #if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _TRUE))
    }
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    else
#endif
    {
#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_WREN_FOR_SINGLE_BYTE == _FALSE))
        CFlashWREN(_MISC_PAGE);

        switch(ucDDCRAMType)
        {
            case _VGA_EDID:
                memcpy(&(MCU_FLASH[_FLASH_DATA_SPACE]), MCU_DDCRAM_A0, _ADC_EDID_SIZE);
                break;

#if((_DDC_CHANNEL_FOR_D0 == _DDC2) || (_DDC_CHANNEL_FOR_D1 == _DDC2))
            case _DDC2_EDID:
                memcpy(&(MCU_FLASH[_FLASH_DATA_SPACE + _ADC_EDID_SIZE]), MCU_DDCRAM_DDC2, _DDC2_EDID_SIZE);
                break;
#endif

#if((_DDC_CHANNEL_FOR_D0 == _DDC3) || (_DDC_CHANNEL_FOR_D1 == _DDC3))
            case _DDC3_EDID:
                memcpy(&(MCU_FLASH[_FLASH_DATA_SPACE + _ADC_EDID_SIZE + _DDC2_EDID_SIZE]), MCU_DDCRAM_DDC3, _DDC3_EDID_SIZE);
                break;
#endif

            default:
                break;
        }

        CFlashWRDis();
#endif
    }
}
#endif // End of #if((_MEMORY_LOCATION == _FLASH) && (_EDID_PRO == _ON))

// V016 System Patch Note (3) Modify 20100803 Start
// Patch Reason : Modify CFlashLoadDDCData to avoid complie warning.
/*
#if(_EMBEDDED_EDID == _OFF)
*/
#if((_MEMORY_LOCATION == _FLASH) && (_EMBEDDED_EDID == _OFF))
// V016 System Patch Note (3) Modify 20100803 End

//--------------------------------------------------
// Description  : Load DP Embedded EDID to the DDC Ram
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CFlashLoadDDCData(void)
{
#if((_DDC_CHANNEL_FOR_D0 == _DDC2) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))
    memcpy(MCU_DDCRAM_DDC2, tEDID_TABLE_D0, _DDC2_EDID_SIZE);
#elif(_DDC_CHANNEL_FOR_D0 == _DDC3) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    memcpy(MCU_DDCRAM_DDC3, tEDID_TABLE_D0, _DDC3_EDID_SIZE);
#elif(_DDC_CHANNEL_FOR_D1 == _DDC2) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    memcpy(MCU_DDCRAM_DDC2, tEDID_TABLE_D1, _DDC2_EDID_SIZE);
#elif(_DDC_CHANNEL_FOR_D1 == _DDC3) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    memcpy(MCU_DDCRAM_DDC3, tEDID_TABLE_D1, _DDC3_EDID_SIZE);
#endif
}
#endif // End of #if((_MEMORY_LOCATION == _FLASH) && (_EMBEDDED_EDID == _OFF))

#endif // End of #if(_OSD_TYPE == _REALTEK_OSD)

// V015 System Patch Note (7) Modify 20100630 End

