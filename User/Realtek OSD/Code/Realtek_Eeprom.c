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

//----------------------------------------------------------------------------------------------------
// ID Code      : Eeprom.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __REALTEK_EEPROM__

#include "Common\Header\Include.h"

#if(_OSD_TYPE == _REALTEK_OSD)

#if(_MEMORY_LOCATION == _EEPROM)
//--------------------------------------------------
// Description  : Eeprom check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromStartupCheck(void)
{
    BYTE cnt;

    //This delay is for Eeprom power rising time when the connector plug in (VGA_5V or DVI_5V).
    CTimerDelayXms(20);
    for(cnt = 0; cnt < 2; cnt++)
    {
        pData[0] = _VERSION_CODE ^ 0xff;

        CEepromRead(_VERSION_CODE_ADDRESS, 1, pData);

        if(pData[0] == _VERSION_CODE)
        {
            break;
        }
    }
//	pData[0]=0;

    if(pData[0] != _VERSION_CODE)
    {
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("CEepromLoadDefault", 0);
#endif
        CEepromLoadDefault();
        pData[0] = _VERSION_CODE;

        CEepromWrite(_VERSION_CODE_ADDRESS, 1, pData);
    }
    else
    {
        CEepromLoadSystemData();

        CEepromLoadOsdUserData();
        CEepromLoadOsdReserveData();

        CEepromLoadAdcData();
        CEepromLoadOsdUserData();
        CEepromLoadBriConData();
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("CEepromLoadBriConData", stConBriData.Dicom);
#endif
if(stConBriData.Dicom>10)
	{
	stConBriData.Dicom=0;//sjp20111207
	CEepromSaveBriConData();
	}
if(stConBriData.Gamma>4)
{
	stConBriData.Gamma =0;//sjp20111207
	CEepromSaveBriConData();
}
if((stConBriData.Contrast>0x90)||(stConBriData.Contrast<0x70))
{
	stConBriData.Contrast=0x80;//sjp20111207
	CEepromSaveBriConData();
}
if((stConBriData.Brightness>0x90)||(stConBriData.Brightness<0x70))
{
	stConBriData.Brightness=0x80;//sjp20111207
	CEepromSaveBriConData();
}
	
        CEepromLoadColorTempData();
       CEepromLoadLSlumiData();//load LSLUMI VALUE 20110621
       CEepromLoadPWMlumiData();//load PWMLUMI VALUE 20110715
    }
    CEepromLoadDDCData();
}


//--------------------------------------------------
// Description  : Load eeprom default
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadDefault(void)
{
    StructModeUserFIFODataType stFIFOModeTemp;

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
    BYTE ucSourceTemp = 0;
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End

    // V013 System Patch Note (6) Modify 20100507 Start
    // Patch Reason : Make sure stModeUserData and stModeUserCenterData are not changed after the initialization of mode user data and mode center data.
    StructModeUserDataType stModeUserDataTemp;
    StructModeUserCenterDataType stModeUserCenterDataTemp;

    stModeUserDataTemp = stModeUserData;
    stModeUserCenterDataTemp = stModeUserCenterData;
    // V013 System Patch Note (6) Modify 20100507 End

    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
    /*
    if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < 16))
    */
#if(_FIFO_MODE_ONLY == _ON)
    if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < (_MAX_FIFO_MODE_INDEX + 1)))
#else
    if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < 16))
#endif
    // V013 VGA Patch Note (11) Modify 20100416 End
    {
        CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);
        stFIFOModeTemp.ModeNum = pData[(stModeInfo.ModeCurr % 4) * 4];
    }

    CEepromInitialModeData();
    CEepromInitialUserFIFOModeData();
    CEepromInitialCenterModeData();
#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage("CEepromLoadSystemDataDefault", 0);
#endif
	
    CEepromLoadSystemDataDefault();

    CEepromLoadOsdUserDataDefault();
    CEepromLoadOsdReserveDataDefault();
    CEepromLoadAdcDataDefault();
    CEepromLoadBriConDataDefault();
    CEepromLoadColorTempDataDefault();
    CEepromLoadLSlumiDataDefault();//load default LSlumi SJP20110625
    CEepromLoadPWMlumiDataDefault();//load default PWMlumi sjp20110715
    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
    ucSourceTemp = GET_INPUTSOURCE_TYPE();
    SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);
    CEepromLoadModeData(stModeInfo.ModeCurr);
    SET_INPUTSOURCE_TYPE(ucSourceTemp);
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End

    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
    /*
    if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < 16))
    */
#if(_FIFO_MODE_ONLY == _ON)
    if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < (_MAX_FIFO_MODE_INDEX + 1)))
#else
    if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < 16))
#endif
    // V013 VGA Patch Note (11) Modify 20100416 End
    {
        // V013 VGA Patch Note (11) Modify 20100416 Start
        // Patch Reason : Add FIFO Mode Only to save EEPROM space.
        // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
        /*
        if(stSystemData.UserFIFOMode >= 15)
        */
#if(_FIFO_MODE_ONLY == _ON)
        if(stSystemData.UserFIFOMode >= _MAX_FIFO_MODE_INDEX)
#else
        if(stSystemData.UserFIFOMode >= 15)
#endif
        // V013 VGA Patch Note (11) Modify 20100416 End
        {
            stSystemData.UserFIFOMode = 0;
        }
        else
        {
            stSystemData.UserFIFOMode++;
        }

        // V013 System Patch Note (7) Modify 20100507 Start
        // Patch Reason : Correct saving FIFO Data, right after data initialization.
        /*
        stFIFOModeTemp.IHFreq = stModeInfo.IHFreq;
        stFIFOModeTemp.IVFreq = stModeInfo.IVFreq;
        CEepromSaveUserFIFOModeData(stFIFOModeTemp);

        stModeUserData.HPosition = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IHStartPos;
        stModeUserData.VPosition = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IVStartPos;
        stModeUserData.Clock = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IHTotal;
        stModeUserData.Phase = 0;
        CEepromSaveModeData(stSystemData.UserFIFOMode);

        stModeInfo.ModeCurr = stSystemData.UserFIFOMode;
        */
        if(stFIFOModeTemp.ModeNum < _MAX_PRESET_MODE)
        {
            stFIFOModeTemp.IHFreq = stModeInfo.IHFreq;
            stFIFOModeTemp.IVFreq = stModeInfo.IVFreq;
            CEepromSaveUserFIFOModeData(stFIFOModeTemp);

            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
#if(_COLOR_FORMAT_CONVERT == _ON)
            CLR_MODE_COLOR_FORMAT_FLAG();
#endif
// V014 VGA Patch Note (6) Modify 20100527 End

            stModeUserData.HPosition = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IHStartPos;
            stModeUserData.VPosition = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IVStartPos;
            stModeUserData.Clock = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IHTotal;
            stModeUserData.Phase = 0;
            CEepromSaveModeData(stSystemData.UserFIFOMode);
            stModeInfo.ModeCurr = stSystemData.UserFIFOMode;
        }
        // V013 System Patch Note (7) Modify 20100507 End
    }
    else if((GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE) && (stModeInfo.ModeCurr < _MAX_PRESET_MODE))
    {
        // V013 System Patch Note (6) Modify 20100507 Start
        // Patch Reason : Make sure stModeUserData and stModeUserCenterData are not changed after the initialization of mode user data and mode center data.
        /*
        CEepromLoadModeData(stModeInfo.ModeCurr);
        */
        stModeUserData = stModeUserDataTemp;
        stModeUserCenterData = stModeUserCenterDataTemp;

        // V013 System Patch Note (7) Modify 20100507 Start
        // Patch Reason : Save FIFO Data, if _FIFO_MODE_ONLY is ON, right after data initialization.
        /*
        CEepromLoadModeData(stModeInfo.ModeCurr);
        */
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

        if(stModeInfo.ModeCurr < _MAX_PRESET_MODE)
        {
            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
#if(_COLOR_FORMAT_CONVERT == _ON)
            CLR_MODE_COLOR_FORMAT_FLAG();
#endif
// V014 VGA Patch Note (6) Modify 20100527 End

            stModeUserData.HPosition = tINPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHStartPos;
            stModeUserData.VPosition = tINPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IVStartPos;
            stModeUserData.Clock = tINPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHTotal;
            stModeUserData.Phase = 0;

            stFIFOModeTemp.ModeNum = stModeInfo.ModeCurr;
            stFIFOModeTemp.IHFreq = stModeInfo.IHFreq;
            stFIFOModeTemp.IVFreq = stModeInfo.IVFreq;

            CEepromSaveUserFIFOModeData(stFIFOModeTemp);
            CEepromSaveModeData(stModeInfo.ModeCurr);
        }
#else
        CEepromLoadModeData(stModeInfo.ModeCurr);
#endif
        // V013 System Patch Note (7) Modify 20100507 End

        // V013 System Patch Note (6) Modify 20100507 End
    }

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    SET_SOURCE_SEARCH_AUTO();
#endif
}

//--------------------------------------------------
// Description  : Eeprom write function
// Input Value  : usAddr        --> absolute address
//                usLength      --> Numbers of data we want to write
//                pWriteArray   --> Writing data array
// Output Value : Return _SUCCESS if succeed
//--------------------------------------------------
bit CEepromWrite(WORD usAddr, WORD usLength, BYTE *pWriteArray)
{
    bit bRet = _FALSE;

#if((_PCB_TYPE == _RTD2472D_DEMO_PCB) || (_PCB_TYPE == _RTD2472RD_DEMO_PCB) || (_PCB_TYPE == _RTD2545LR_QA_PCB) || (_PCB_TYPE == _RTD2472RD_DEMO_PCB) || (_PCB_TYPE == _RTD2472RD_QA_PCB)) //||(_PCB_TYPE == _RTD2472D_QA_PCB)||(_PCB_TYPE == _RTD2472RD_QA_PCB))
    bEEPROM_WRITE_PROTECT = _LOW;
#endif

    bRet = CI2cWrite(NVRAM_LINE,_EEPROM_ADDRESS + (BYTE)((usAddr & 0xff00) >> 7), (BYTE)(usAddr & 0x00ff), usLength, pWriteArray);

    if(bRet == _SUCCESS)
    {
        bRet = CI2cWritePolling(NVRAM_LINE,_EEPROM_ADDRESS + (BYTE)((usAddr & 0xff00) >> 7));
    }

#if((_PCB_TYPE == _RTD2472D_DEMO_PCB) || (_PCB_TYPE == _RTD2472RD_DEMO_PCB) || (_PCB_TYPE == _RTD2545LR_QA_PCB) || (_PCB_TYPE == _RTD2472RD_DEMO_PCB) || (_PCB_TYPE == _RTD2472RD_QA_PCB)) //||(_PCB_TYPE == _RTD2472D_QA_PCB)||(_PCB_TYPE == _RTD2472RD_QA_PCB))
    bEEPROM_WRITE_PROTECT = _HIGH;
#endif

    return bRet;
}

//--------------------------------------------------
// Description  : Eeprom read function
// Input Value  : usAddr        --> absolute address
//                usLength      --> Numbers of data we want to read
//                pReadArray    --> Result array
// Output Value : Return _SUCCESS if succeed
//--------------------------------------------------
bit CEepromRead(WORD usAddr, WORD usLength, BYTE *pReadArray)
{
    return CI2cRead(NVRAM_LINE,_EEPROM_ADDRESS + (BYTE)((usAddr & 0xff00) >> 7), (BYTE)(usAddr & 0x00ff), usLength, pReadArray);
}

//----------------------------------------------------------------------------------------------------

// V012 Modify 20100309 Start
// V012 Patch Note (10) : Adjust EEPROM mode data structure to save space.
/*
//--------------------------------------------------
// Description  : Save mode setting data, such as FirstAuto,
//                HPosition, VPosition, Clock and Phase.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveModeData(BYTE ucMode)
{
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        CEepromWrite(_MODE_DATA_0_ADDRESS + (WORD)ucMode * 8, sizeof(StructModeUserDataType), &stModeUserData.FirstAuto);
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromWrite(_USER_FIFO_MODE_DATA_1_ADDRESS + (WORD)ucMode * 8, sizeof(StructModeUserDataType), &stModeUserData.FirstAuto);
    }
}
*/

// V013 VGA Patch Note (11) Modify 20100416 Start
// Patch Reason : Add FIFO Mode Only to save EEPROM space.
// Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
/*
void CEepromSaveModeData(BYTE ucMode)
{
    pData[0] = (stModeUserData.FirstAuto & 0xE0) | ((stModeUserData.FirstAuto & 0x01) << 4) | (BYTE)((stModeUserData.Clock >> 8) & 0x0F);
    pData[1] = (BYTE)((stModeUserData.HPosition >> 4) & 0xF0) | (BYTE)((stModeUserData.VPosition >> 8) & 0x0F);
    pData[2] = (BYTE)(stModeUserData.HPosition);
    pData[3] = (BYTE)(stModeUserData.VPosition);
    pData[4] = (BYTE)(stModeUserData.Clock);
    pData[5] = (BYTE)(stModeUserData.Phase);

    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        CEepromWrite(_MODE_DATA_0_ADDRESS + (WORD)ucMode * _MODE_USER_DATA_SIZE, _MODE_USER_DATA_SIZE, pData);
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromWrite(_USER_FIFO_MODE_DATA_1_ADDRESS + (WORD)ucMode * _MODE_USER_DATA_SIZE, _MODE_USER_DATA_SIZE, pData);
    }
}
*/
//--------------------------------------------------
// Description  : Save mode setting data, such as FirstAuto,
//                HPosition, VPosition, Clock and Phase.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveModeData(BYTE ucMode)
{
#if(_FIFO_MODE_ONLY == _ON)
    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
    /*
    // Just for the warning from the compiler.
    ucMode = g_ucFIFOModeNum;

    CEepromWrite(_MODE_DATA_0_ADDRESS + (WORD)g_ucFIFOModeNum * sizeof(StructModeUserDataType), sizeof(StructModeUserDataType), &stModeUserData.FirstAuto);
    */
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        CEepromWrite(_MODE_DATA_YPBPR_ADDRESS + (WORD)ucMode * sizeof(StructModeUserDataType), sizeof(StructModeUserDataType), &stModeUserData.FirstAuto);
    }
    else
#endif
    {
#if((_FIFO_MODE_ONLY == _OFF) || (_YUV_AUTO_CONFIG_SUPPORT == _OFF))
        // Just for the warning from the compiler.
        ucMode = g_ucFIFOModeNum;
#endif

        CEepromWrite(_MODE_DATA_0_ADDRESS + (WORD)g_ucFIFOModeNum * sizeof(StructModeUserDataType), sizeof(StructModeUserDataType), &stModeUserData.FirstAuto);
    }
    // V013 VGA Patch Note (10) 20100416 Modify End
#else
    pData[0] = (stModeUserData.FirstAuto & 0xE0) | ((stModeUserData.FirstAuto & 0x01) << 4) | (BYTE)((stModeUserData.Clock >> 8) & 0x0F);
    pData[1] = (BYTE)((stModeUserData.HPosition >> 4) & 0xF0) | (BYTE)((stModeUserData.VPosition >> 8) & 0x0F);
    pData[2] = (BYTE)(stModeUserData.HPosition);
    pData[3] = (BYTE)(stModeUserData.VPosition);
    pData[4] = (BYTE)(stModeUserData.Clock);
    pData[5] = (BYTE)(stModeUserData.Phase);

    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        CEepromWrite(_MODE_DATA_0_ADDRESS + (WORD)ucMode * _MODE_USER_DATA_SIZE, _MODE_USER_DATA_SIZE, pData);
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromWrite(_USER_FIFO_MODE_DATA_1_ADDRESS + (WORD)ucMode * _MODE_USER_DATA_SIZE, _MODE_USER_DATA_SIZE, pData);
    }
#endif
}
// V013 VGA Patch Note (11) Modify 20100416 End

// V012 Modify 20100309 End

// V012 Modify 20100309 Start
// V012 Patch Note (10) : Adjust EEPROM mode data structure to save space.
/*
//--------------------------------------------------
// Description  : Load mode setting data, such as FirstAuto,
//                HPosition, VPosition, Clock and Phase.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadModeData(BYTE ucMode)
{
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        if(CEepromRead(_MODE_DATA_0_ADDRESS + (WORD)ucMode * 8, sizeof(StructModeUserDataType), &stModeUserData.FirstAuto) == _FAIL)
        {
            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();

            stModeUserData.HPosition    = stModeInfo.IHStartPos;
            stModeUserData.VPosition    = stModeInfo.IVStartPos;
            stModeUserData.Clock        = stModeInfo.IHTotal;
            stModeUserData.Phase        = 0;
        }
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        if(CEepromRead(_USER_FIFO_MODE_DATA_1_ADDRESS + (WORD)ucMode * 8, sizeof(StructModeUserDataType), &stModeUserData.FirstAuto) == _FAIL)
        {
            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();

            stModeUserData.HPosition    = stModeInfo.IHStartPos;
            stModeUserData.VPosition    = stModeInfo.IVStartPos;
            stModeUserData.Clock        = stModeInfo.IHTotal;
            stModeUserData.Phase        = 0;
        }
    }
}
*/
//--------------------------------------------------
// Description  : Load mode setting data, such as FirstAuto,
//                HPosition, VPosition, Clock and Phase.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadModeData(BYTE ucMode)
{
    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
    /*
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        if(CEepromRead(_MODE_DATA_0_ADDRESS + (WORD)ucMode * _MODE_USER_DATA_SIZE, _MODE_USER_DATA_SIZE, pData) == _FAIL)
        {
            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();

            stModeUserData.HPosition = stModeInfo.IHStartPos;
            stModeUserData.VPosition = stModeInfo.IVStartPos;
            stModeUserData.Clock = stModeInfo.IHTotal;
            stModeUserData.Phase = 0;
        }
        else
        {
            stModeUserData.FirstAuto = (pData[0] & 0xE0) | ((pData[0] & 0x10) >> 4);
            stModeUserData.HPosition = (((WORD)(pData[1]) << 4) & 0x0F00) | pData[2];
            stModeUserData.VPosition = (((WORD)(pData[1]) << 8) & 0x0F00) | pData[3];
            stModeUserData.Clock = (((WORD)(pData[0]) << 8) & 0x0F00) | pData[4];
            stModeUserData.Phase = pData[5];
        }
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        if(CEepromRead(_USER_FIFO_MODE_DATA_1_ADDRESS + (WORD)ucMode * _MODE_USER_DATA_SIZE, _MODE_USER_DATA_SIZE, pData) == _FAIL)
        {
            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();

            stModeUserData.HPosition = stModeInfo.IHStartPos;
            stModeUserData.VPosition = stModeInfo.IVStartPos;
            stModeUserData.Clock = stModeInfo.IHTotal;
            stModeUserData.Phase = 0;
        }
        else
        {
            stModeUserData.FirstAuto = (pData[0] & 0xE0) | ((pData[0] & 0x10) >> 4);
            stModeUserData.HPosition = (((WORD)(pData[1]) << 4) & 0x0F00) | pData[2];
            stModeUserData.VPosition = (((WORD)(pData[1]) << 8) & 0x0F00) | pData[3];
            stModeUserData.Clock = (((WORD)(pData[0]) << 8) & 0x0F00) | pData[4];
            stModeUserData.Phase = pData[5];
        }
    }
    */
#if(_FIFO_MODE_ONLY == _ON)
    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
    /*
    // Just for the warning from the compiler.
    ucMode = g_ucFIFOModeNum;

    if(CEepromRead(_MODE_DATA_0_ADDRESS + (WORD)g_ucFIFOModeNum * sizeof(StructModeUserDataType), sizeof(StructModeUserDataType), &stModeUserData.FirstAuto) == _FAIL)
    {
        CLR_AUTO_FLAG();
        CLR_AUTO_FAIL_COUNT();

        stModeUserData.HPosition = stModeInfo.IHStartPos;
        stModeUserData.VPosition = stModeInfo.IVStartPos;
        stModeUserData.Clock = stModeInfo.IHTotal;
        stModeUserData.Phase = 0;
    }
    */
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        if(CEepromRead(_MODE_DATA_YPBPR_ADDRESS + (WORD)ucMode * sizeof(StructModeUserDataType), sizeof(StructModeUserDataType), &stModeUserData.FirstAuto) == _FAIL)
        {
            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
#if(_COLOR_FORMAT_CONVERT == _ON)
            SET_MODE_COLOR_FORMAT_FLAG(_YUV_COLOR_FORMAT);
#endif
// V014 VGA Patch Note (6) Modify 20100527 End

            stModeUserData.HPosition = stModeInfo.IHStartPos;
            stModeUserData.VPosition = stModeInfo.IVStartPos;
            stModeUserData.Clock = stModeInfo.IHTotal;
            stModeUserData.Phase = 0;
        }
    }
    else
#endif
    {
#if((_FIFO_MODE_ONLY == _OFF) || (_YUV_AUTO_CONFIG_SUPPORT == _OFF))
        // Just for the warning from the compiler.
        ucMode = g_ucFIFOModeNum;
#endif

        if(CEepromRead(_MODE_DATA_0_ADDRESS + (WORD)g_ucFIFOModeNum * sizeof(StructModeUserDataType), sizeof(StructModeUserDataType), &stModeUserData.FirstAuto) == _FAIL)
        {
            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
#if(_COLOR_FORMAT_CONVERT == _ON)
            CLR_MODE_COLOR_FORMAT_FLAG();
#endif
// V014 VGA Patch Note (6) Modify 20100527 End

            stModeUserData.HPosition = stModeInfo.IHStartPos;
            stModeUserData.VPosition = stModeInfo.IVStartPos;
            stModeUserData.Clock = stModeInfo.IHTotal;
            stModeUserData.Phase = 0;
        }
    }
    // V013 VGA Patch Note (10) 20100416 Modify End
#else
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        if(CEepromRead(_MODE_DATA_0_ADDRESS + (WORD)ucMode * _MODE_USER_DATA_SIZE, _MODE_USER_DATA_SIZE, pData) == _FAIL)
        {
            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
#if(_COLOR_FORMAT_CONVERT == _ON)
            CLR_MODE_COLOR_FORMAT_FLAG();
#endif
// V014 VGA Patch Note (6) Modify 20100527 End

            stModeUserData.HPosition = stModeInfo.IHStartPos;
            stModeUserData.VPosition = stModeInfo.IVStartPos;
            stModeUserData.Clock = stModeInfo.IHTotal;
            stModeUserData.Phase = 0;
        }
        else
        {
            stModeUserData.FirstAuto = (pData[0] & 0xE0) | ((pData[0] & 0x10) >> 4);
            stModeUserData.HPosition = (((WORD)(pData[1]) << 4) & 0x0F00) | pData[2];
            stModeUserData.VPosition = (((WORD)(pData[1]) << 8) & 0x0F00) | pData[3];
            stModeUserData.Clock = (((WORD)(pData[0]) << 8) & 0x0F00) | pData[4];
            stModeUserData.Phase = pData[5];
        }
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        if(CEepromRead(_USER_FIFO_MODE_DATA_1_ADDRESS + (WORD)ucMode * _MODE_USER_DATA_SIZE, _MODE_USER_DATA_SIZE, pData) == _FAIL)
        {
            CLR_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
#if(_COLOR_FORMAT_CONVERT == _ON)
            CLR_MODE_COLOR_FORMAT_FLAG();
#endif
// V014 VGA Patch Note (6) Modify 20100527 End

            stModeUserData.HPosition = stModeInfo.IHStartPos;
            stModeUserData.VPosition = stModeInfo.IVStartPos;
            stModeUserData.Clock = stModeInfo.IHTotal;
            stModeUserData.Phase = 0;
        }
        else
        {
            stModeUserData.FirstAuto = (pData[0] & 0xE0) | ((pData[0] & 0x10) >> 4);
            stModeUserData.HPosition = (((WORD)(pData[1]) << 4) & 0x0F00) | pData[2];
            stModeUserData.VPosition = (((WORD)(pData[1]) << 8) & 0x0F00) | pData[3];
            stModeUserData.Clock = (((WORD)(pData[0]) << 8) & 0x0F00) | pData[4];
            stModeUserData.Phase = pData[5];
        }
    }
#endif
    // V013 VGA Patch Note (11) Modify 20100416 End
}
// V012 Modify 20100309 End

//--------------------------------------------------
// Description  : Initial mode setting data with defaults
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromInitialModeData(void)
{
    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
    /*
    BYTE modecnt, modetype;

    modetype = GET_MODE_SEARCH_TYPE();
    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);

    for(modecnt = 0; modecnt < _MAX_PRESET_MODE; modecnt++)
    {
        CLR_AUTO_FLAG();
        CLR_AUTO_FAIL_COUNT();

        stModeUserData.HPosition = tINPUTMODE_PRESET_TABLE[modecnt].IHStartPos;
        stModeUserData.VPosition = tINPUTMODE_PRESET_TABLE[modecnt].IVStartPos;
        stModeUserData.Clock = tINPUTMODE_PRESET_TABLE[modecnt].IHTotal;
        stModeUserData.Phase = 0;

        CEepromSaveModeData(modecnt);
    }

    // V012 Modify 20100309 Start
    // V012 Patch Note (10) : Adjust EEPROM mode data structure to save space.
    /*
    for(modecnt=0; modecnt<8; modecnt++)
    {
        CEepromWrite(_USER_FIFO_MODE_DATA_1_ADDRESS + (modecnt * 16), 16, tEEPROM_USER_FIFO_MODE_DEFAULT);
    }
    * /
    for(modecnt = 0; modecnt < _MODE_USER_DATA_SIZE; modecnt++)
    {
        CEepromWrite(_USER_FIFO_MODE_DATA_1_ADDRESS + (modecnt * sizeof(tEEPROM_USER_FIFO_MODE_DEFAULT)), sizeof(tEEPROM_USER_FIFO_MODE_DEFAULT), tEEPROM_USER_FIFO_MODE_DEFAULT);
    }
    // V012 Modify 20100309 End

    SET_MODE_SEARCH_TYPE(modetype);
    */
#if(_FIFO_MODE_ONLY == _ON)
    BYTE ucModeCnt = 0;

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
    BYTE ucModeType = 0;
    // V013 VGA Patch Note (10) 20100416 Modify End

    for(ucModeCnt = 0; ucModeCnt <= _MAX_FIFO_MODE_INDEX; ucModeCnt++)
    {
        g_ucFIFOModeNum = ucModeCnt;
        stModeUserData.FirstAuto = 0xFF;
        stModeUserData.HPosition = 0xFFFF;
        stModeUserData.VPosition = 0xFFFF;
        stModeUserData.Clock = 0xFFFF;
        stModeUserData.Phase = 0xFF;

        CEepromSaveModeData(ucModeCnt);
    }

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
    ucModeType = GET_INPUTSOURCE_TYPE();
    SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);

    for(ucModeCnt = 0; ucModeCnt < _MAX_YPBPR_MODE; ucModeCnt++)
    {
        CLR_AUTO_FLAG();
        CLR_AUTO_FAIL_COUNT();

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
#if(_COLOR_FORMAT_CONVERT == _ON)
        SET_MODE_COLOR_FORMAT_FLAG(_YUV_COLOR_FORMAT);
#endif
// V014 VGA Patch Note (6) Modify 20100527 End

        stModeUserData.HPosition = tYPBPR_MODE_TABLE[ucModeCnt].IHStartPos;
        stModeUserData.VPosition = tYPBPR_MODE_TABLE[ucModeCnt].IVStartPos;
        stModeUserData.Clock = tYPBPR_MODE_TABLE[ucModeCnt].IHTotal;
        stModeUserData.Phase = 0;

        CEepromSaveModeData(ucModeCnt);
    }

    SET_INPUTSOURCE_TYPE(ucModeType);
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End
#else
    BYTE ucModeCnt = 0;
    BYTE ucModeType = 0;

    ucModeType = GET_MODE_SEARCH_TYPE();
    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);

    for(ucModeCnt = 0; ucModeCnt < _MAX_PRESET_MODE; ucModeCnt++)
    {
        CLR_AUTO_FLAG();
        CLR_AUTO_FAIL_COUNT();

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
#if(_COLOR_FORMAT_CONVERT == _ON)
        CLR_MODE_COLOR_FORMAT_FLAG();
#endif
// V014 VGA Patch Note (6) Modify 20100527 End

        stModeUserData.HPosition = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHStartPos;
        stModeUserData.VPosition = tINPUTMODE_PRESET_TABLE[ucModeCnt].IVStartPos;
        stModeUserData.Clock = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHTotal;
        stModeUserData.Phase = 0;

        CEepromSaveModeData(ucModeCnt);
    }

    for(ucModeCnt = 0; ucModeCnt < 16; ucModeCnt++)
    {
        CEepromWrite(_USER_FIFO_MODE_DATA_1_ADDRESS + (ucModeCnt * _MODE_USER_DATA_SIZE), _MODE_USER_DATA_SIZE, tEEPROM_USER_FIFO_MODE_DEFAULT);
    }

    SET_MODE_SEARCH_TYPE(ucModeType);
#endif
    // V013 VGA Patch Note (11) Modify 20100416 End
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save user FIFO mode data, such as ModeNum,
//                IHFreq, IVFreq.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode)
{
    stUserFIFOMode.IHFreq = ((stUserFIFOMode.IVFreq & 0x0f00) << 4) | (stUserFIFOMode.IHFreq & 0x0fff);
    stUserFIFOMode.IVFreq = ((stUserFIFOMode.IVFreq & 0x00ff) << 8);

    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
#if(_FIFO_MODE_ONLY == _ON)
    stUserFIFOMode.IHFreq = (stUserFIFOMode.IHFreq & ~_BIT15) | ((WORD)GET_MODE_SEARCH_TYPE() << 15);
#endif
    // V013 VGA Patch Note (11) Modify 20100416 End

    CEepromWrite(_USER_FIFO_MODE_DATA_0_ADDRESS + (stSystemData.UserFIFOMode * 4), 4, &stUserFIFOMode.ModeNum);
}

//--------------------------------------------------
// Description  : Load 4 sets of user FIFO mode data.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray)
{
    CEepromRead(_USER_FIFO_MODE_DATA_0_ADDRESS + (ucNum * 16), 16, pArray);
}

//--------------------------------------------------
// Description  : Initial user FIFO mode data with defaults
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromInitialUserFIFOModeData(void)
{
    BYTE modecnt;

    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
    /*
    for(modecnt = 0; modecnt < 4; modecnt++)
    */
#if(_FIFO_MODE_ONLY == _ON)
    for(modecnt = 0; modecnt < 16; modecnt++)
#else
    for(modecnt = 0; modecnt < 4; modecnt++)
#endif
    // V013 VGA Patch Note (11) Modify 20100416 End
    {
        CEepromWrite(_USER_FIFO_MODE_DATA_0_ADDRESS + (modecnt * 16), 16, tEEPROM_USER_FIFO_MODE_DEFAULT);
    }
}

//----------------------------------------------------------------------------------------------------

// V012 Modify 20100309 Start
// V012 Patch Note (10) : Adjust EEPROM mode data structure to save space.
/*
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value : None
//--------------------------------------------------
void CEepromSaveCenterModeData(BYTE ucMode)
{
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + (WORD)ucMode * 8, sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos);
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + (WORD)_MAX_PRESET_MODE * 8 + (WORD)ucMode * 8, sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos);
    }
}
*/
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value : None
//--------------------------------------------------
void CEepromSaveCenterModeData(BYTE ucMode)
{
    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
    /*
    pData[0] = (BYTE)((stModeUserCenterData.CenterHPos >> 4) & 0xF0) | (BYTE)((stModeUserCenterData.CenterVPos >> 8) & 0x0F);
    pData[1] = (BYTE)(stModeUserCenterData.CenterHPos);
    pData[2] = (BYTE)(stModeUserCenterData.CenterVPos);
    pData[3] = (BYTE)(stModeUserCenterData.CenterClock >> 8);
    pData[4] = (BYTE)(stModeUserCenterData.CenterClock);
    pData[5] = (BYTE)(stModeUserCenterData.CenterPhase);

    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + (WORD)ucMode * _MODE_CENTER_DATA_SIZE, _MODE_CENTER_DATA_SIZE, pData);
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + (WORD)_MAX_PRESET_MODE * _MODE_CENTER_DATA_SIZE + (WORD)ucMode * _MODE_CENTER_DATA_SIZE, _MODE_CENTER_DATA_SIZE, pData);
    }
    */
#if(_FIFO_MODE_ONLY == _ON)
    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
    /*
    // Just for the warning from the compiler.
    ucMode = g_ucFIFOModeNum;
    CEepromWrite(_MODE_CENTER_DATA_ADDRESS + g_ucFIFOModeNum * sizeof(StructModeUserCenterDataType), sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos);
    */
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        CEepromWrite(_MODE_CENTER_DATA_YPBPR_ADDRESS + ucMode * sizeof(StructModeUserCenterDataType), sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos);
    }
    else
#endif
    {
#if((_FIFO_MODE_ONLY == _OFF) || (_YUV_AUTO_CONFIG_SUPPORT == _OFF))
        // Just for the warning from the compiler.
        ucMode = g_ucFIFOModeNum;
#endif

        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + g_ucFIFOModeNum * sizeof(StructModeUserCenterDataType), sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos);
    }
    // V013 VGA Patch Note (10) 20100416 Modify End
#else
    pData[0] = (BYTE)((stModeUserCenterData.CenterHPos >> 4) & 0xF0) | (BYTE)((stModeUserCenterData.CenterVPos >> 8) & 0x0F);
    pData[1] = (BYTE)(stModeUserCenterData.CenterHPos);
    pData[2] = (BYTE)(stModeUserCenterData.CenterVPos);
    pData[3] = (BYTE)(stModeUserCenterData.CenterClock >> 8);
    pData[4] = (BYTE)(stModeUserCenterData.CenterClock);
    pData[5] = (BYTE)(stModeUserCenterData.CenterPhase);

    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + (WORD)ucMode * _MODE_CENTER_DATA_SIZE, _MODE_CENTER_DATA_SIZE, pData);
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + (WORD)_MAX_PRESET_MODE * _MODE_CENTER_DATA_SIZE + (WORD)ucMode * _MODE_CENTER_DATA_SIZE, _MODE_CENTER_DATA_SIZE, pData);
    }
#endif
    // V013 VGA Patch Note (11) Modify 20100416 End
}
// V012 Modify 20100309 End

// V012 Modify 20100309 Start
// V012 Patch Note (10) : Adjust EEPROM mode data structure to save space.
/*
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value : None
//--------------------------------------------------
void CEepromLoadCenterModeData(BYTE ucMode)
{

    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        if(CEepromRead(_MODE_CENTER_DATA_ADDRESS + (WORD)ucMode * 8, sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos) == _FAIL)
        {
            stModeUserCenterData.CenterHPos     = stModeInfo.IHStartPos;
            stModeUserCenterData.CenterVPos     = stModeInfo.IVStartPos;
            stModeUserCenterData.CenterClock    = stModeInfo.IHTotal;
            stModeUserCenterData.CenterPhase    = 0x00;
        }
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        if(CEepromRead(_MODE_CENTER_DATA_ADDRESS + (WORD)_MAX_PRESET_MODE * 8 + (WORD)ucMode * 8, sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos) == _FAIL)
        {
            stModeUserCenterData.CenterHPos     = stModeInfo.IHStartPos;
            stModeUserCenterData.CenterVPos     = stModeInfo.IVStartPos;
            stModeUserCenterData.CenterClock    = stModeInfo.IHTotal;
            stModeUserCenterData.CenterPhase    = 0x00;
        }
    }

    if((stModeUserCenterData.CenterHPos == 0xffff) && (stModeUserCenterData.CenterVPos == 0xffff) && (stModeUserCenterData.CenterClock == 0xffff))
    {
        stModeUserCenterData.CenterHPos     = stModeInfo.IHStartPos;
        stModeUserCenterData.CenterVPos     = stModeInfo.IVStartPos;
        stModeUserCenterData.CenterClock    = stModeInfo.IHTotal;
        stModeUserCenterData.CenterPhase    = 0x00;
    }

}
*/
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value : None
//--------------------------------------------------
void CEepromLoadCenterModeData(BYTE ucMode)
{
    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
    /*
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        if(CEepromRead(_MODE_CENTER_DATA_ADDRESS + (WORD)ucMode * _MODE_CENTER_DATA_SIZE, _MODE_CENTER_DATA_SIZE, pData) == _FAIL)
        {
            stModeUserCenterData.CenterHPos = stModeInfo.IHStartPos;
            stModeUserCenterData.CenterVPos = stModeInfo.IVStartPos;
            stModeUserCenterData.CenterClock = stModeInfo.IHTotal;
            stModeUserCenterData.CenterPhase = 0x00;
        }
        else
        {
            stModeUserCenterData.CenterHPos = (((WORD)(pData[0]) << 4) & 0x0F00) | pData[1];
            stModeUserCenterData.CenterVPos = (((WORD)(pData[0]) << 8) & 0x0F00) | pData[2];
            stModeUserCenterData.CenterClock = (((WORD)(pData[3]) << 8) & 0x0F00) | pData[4];
            stModeUserCenterData.CenterPhase = pData[5];
        }
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        if(CEepromRead(_MODE_CENTER_DATA_ADDRESS + (WORD)_MAX_PRESET_MODE * _MODE_CENTER_DATA_SIZE + (WORD)ucMode * _MODE_CENTER_DATA_SIZE, _MODE_CENTER_DATA_SIZE, pData) == _FAIL)
        {
            stModeUserCenterData.CenterHPos = stModeInfo.IHStartPos;
            stModeUserCenterData.CenterVPos = stModeInfo.IVStartPos;
            stModeUserCenterData.CenterClock = stModeInfo.IHTotal;
            stModeUserCenterData.CenterPhase = 0x00;
        }
        else
        {
            stModeUserCenterData.CenterHPos = (((WORD)(pData[0]) << 4) & 0x0F00) | pData[1];
            stModeUserCenterData.CenterVPos = (((WORD)(pData[0]) << 8) & 0x0F00) | pData[2];
            stModeUserCenterData.CenterClock = (((WORD)(pData[3]) << 8) & 0x0F00) | pData[4];
            stModeUserCenterData.CenterPhase = pData[5];
        }
    }
    */
#if(_FIFO_MODE_ONLY == _ON)
    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
    /*
    // Just for the warning from the compiler.
    ucMode = g_ucFIFOModeNum;

    if(CEepromRead(_MODE_CENTER_DATA_ADDRESS + g_ucFIFOModeNum * sizeof(StructModeUserCenterDataType), sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos) == _FAIL)
    {
        stModeUserCenterData.CenterHPos = stModeInfo.IHStartPos;
        stModeUserCenterData.CenterVPos = stModeInfo.IVStartPos;
        stModeUserCenterData.CenterClock = stModeInfo.IHTotal;
        stModeUserCenterData.CenterPhase = 0x00;
    }
    */
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        if(CEepromRead(_MODE_CENTER_DATA_YPBPR_ADDRESS + ucMode * sizeof(StructModeUserCenterDataType), sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos) == _FAIL)
        {
            stModeUserCenterData.CenterHPos = stModeInfo.IHStartPos;
            stModeUserCenterData.CenterVPos = stModeInfo.IVStartPos;
            stModeUserCenterData.CenterClock = stModeInfo.IHTotal;
            stModeUserCenterData.CenterPhase = 0x00;
        }
    }
    else
#endif
    {
#if((_FIFO_MODE_ONLY == _OFF) || (_YUV_AUTO_CONFIG_SUPPORT == _OFF))
        // Just for the warning from the compiler.
        ucMode = g_ucFIFOModeNum;
#endif
        if(CEepromRead(_MODE_CENTER_DATA_ADDRESS + g_ucFIFOModeNum * sizeof(StructModeUserCenterDataType), sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos) == _FAIL)
        {
            stModeUserCenterData.CenterHPos = stModeInfo.IHStartPos;
            stModeUserCenterData.CenterVPos = stModeInfo.IVStartPos;
            stModeUserCenterData.CenterClock = stModeInfo.IHTotal;
            stModeUserCenterData.CenterPhase = 0x00;
        }
    }
    // V013 VGA Patch Note (10) 20100416 Modify End
#else
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        if(CEepromRead(_MODE_CENTER_DATA_ADDRESS + (WORD)ucMode * _MODE_CENTER_DATA_SIZE, _MODE_CENTER_DATA_SIZE, pData) == _FAIL)
        {
            stModeUserCenterData.CenterHPos = stModeInfo.IHStartPos;
            stModeUserCenterData.CenterVPos = stModeInfo.IVStartPos;
            stModeUserCenterData.CenterClock = stModeInfo.IHTotal;
            stModeUserCenterData.CenterPhase = 0x00;
        }
        else
        {
            stModeUserCenterData.CenterHPos = (((WORD)(pData[0]) << 4) & 0x0F00) | pData[1];
            stModeUserCenterData.CenterVPos = (((WORD)(pData[0]) << 8) & 0x0F00) | pData[2];
            stModeUserCenterData.CenterClock = (((WORD)(pData[3]) << 8) & 0x0F00) | pData[4];
            stModeUserCenterData.CenterPhase = pData[5];
        }
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        if(CEepromRead(_MODE_CENTER_DATA_ADDRESS + (WORD)_MAX_PRESET_MODE * _MODE_CENTER_DATA_SIZE + (WORD)ucMode * _MODE_CENTER_DATA_SIZE, _MODE_CENTER_DATA_SIZE, pData) == _FAIL)
        {
            stModeUserCenterData.CenterHPos = stModeInfo.IHStartPos;
            stModeUserCenterData.CenterVPos = stModeInfo.IVStartPos;
            stModeUserCenterData.CenterClock = stModeInfo.IHTotal;
            stModeUserCenterData.CenterPhase = 0x00;
        }
        else
        {
            stModeUserCenterData.CenterHPos = (((WORD)(pData[0]) << 4) & 0x0F00) | pData[1];
            stModeUserCenterData.CenterVPos = (((WORD)(pData[0]) << 8) & 0x0F00) | pData[2];
            stModeUserCenterData.CenterClock = (((WORD)(pData[3]) << 8) & 0x0F00) | pData[4];
            stModeUserCenterData.CenterPhase = pData[5];
        }
    }
#endif
    // V013 VGA Patch Note (11) Modify 20100416 End

    if((stModeUserCenterData.CenterHPos == 0xffff) && (stModeUserCenterData.CenterVPos == 0xffff) && (stModeUserCenterData.CenterClock == 0xffff))
    {
        stModeUserCenterData.CenterHPos = stModeInfo.IHStartPos;
        stModeUserCenterData.CenterVPos = stModeInfo.IVStartPos;
        stModeUserCenterData.CenterClock = stModeInfo.IHTotal;
        stModeUserCenterData.CenterPhase = 0x00;
    }

}
// V012 Modify 20100309 End

//--------------------------------------------------
// Description  : Initial mode setting data with defaults
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromInitialCenterModeData(void)
{
    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
    /*
    BYTE modecnt, modetype;

    modetype = GET_MODE_SEARCH_TYPE();
    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);

    for(modecnt = 0; modecnt < _MAX_PRESET_MODE; modecnt++)
    {
        stModeUserCenterData.CenterHPos = tINPUTMODE_PRESET_TABLE[modecnt].IHStartPos;
        stModeUserCenterData.CenterVPos = tINPUTMODE_PRESET_TABLE[modecnt].IVStartPos;
        stModeUserCenterData.CenterClock = tINPUTMODE_PRESET_TABLE[modecnt].IHTotal;

        stModeUserCenterData.CenterPhase = 0x00;

        CEepromSaveCenterModeData(modecnt);
    }

    // V012 Modify 20100309 Start
    // V012 Patch Note (10) : Adjust EEPROM mode data structure to save space.
    /*
    for(modecnt=0; modecnt<8; modecnt++)
    {
        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + (WORD)_MAX_PRESET_MODE * 8 + ((WORD)modecnt * 16), 16, tEEPROM_USER_FIFO_MODE_DEFAULT);
    }
    * /
    for(modecnt = 0; modecnt < _MODE_CENTER_DATA_SIZE; modecnt++)
    {
        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + (WORD)_MAX_PRESET_MODE * _MODE_CENTER_DATA_SIZE + ((WORD)modecnt * sizeof(tEEPROM_USER_FIFO_MODE_DEFAULT)), sizeof(tEEPROM_USER_FIFO_MODE_DEFAULT), tEEPROM_USER_FIFO_MODE_DEFAULT);
    }
    // V012 Modify 20100309 End

    SET_MODE_SEARCH_TYPE(modetype);
    */
#if(_FIFO_MODE_ONLY == _ON)
    BYTE ucModeCnt = 0;

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
    BYTE ucModeType = 0;
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End

    for(ucModeCnt = 0; ucModeCnt <= _MAX_FIFO_MODE_INDEX; ucModeCnt++)
    {
        g_ucFIFOModeNum = ucModeCnt;
        stModeUserCenterData.CenterHPos = 0xFFFF;
        stModeUserCenterData.CenterVPos = 0xFFFF;
        stModeUserCenterData.CenterClock = 0xFFFF;
        stModeUserCenterData.CenterPhase = 0xFF;

        CEepromSaveCenterModeData(ucModeCnt);
    }

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
    ucModeType = GET_INPUTSOURCE_TYPE();
    SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);

    for(ucModeCnt = 0; ucModeCnt < _MAX_YPBPR_MODE; ucModeCnt++)
    {
        stModeUserCenterData.CenterHPos = tYPBPR_MODE_TABLE[ucModeCnt].IHStartPos;
        stModeUserCenterData.CenterVPos = tYPBPR_MODE_TABLE[ucModeCnt].IVStartPos;
        stModeUserCenterData.CenterClock = tYPBPR_MODE_TABLE[ucModeCnt].IHTotal;
        stModeUserCenterData.CenterPhase = 0x00;

        CEepromSaveCenterModeData(ucModeCnt);
    }

    SET_INPUTSOURCE_TYPE(ucModeType);
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End
#else
    BYTE ucModeCnt = 0;
    BYTE ucModeType = 0;

    ucModeType = GET_MODE_SEARCH_TYPE();
    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);

    for(ucModeCnt = 0; ucModeCnt < _MAX_PRESET_MODE; ucModeCnt++)
    {
        stModeUserCenterData.CenterHPos = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHStartPos;
        stModeUserCenterData.CenterVPos = tINPUTMODE_PRESET_TABLE[ucModeCnt].IVStartPos;
        stModeUserCenterData.CenterClock = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHTotal;
        stModeUserCenterData.CenterPhase = 0x00;

        CEepromSaveCenterModeData(ucModeCnt);
    }

    for(ucModeCnt = 0; ucModeCnt < 16; ucModeCnt++)
    {
        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + (WORD)_MAX_PRESET_MODE * _MODE_CENTER_DATA_SIZE + ((WORD)ucModeCnt * _MODE_CENTER_DATA_SIZE), _MODE_CENTER_DATA_SIZE, tEEPROM_USER_FIFO_MODE_DEFAULT);
    }

    SET_MODE_SEARCH_TYPE(ucModeType);
#endif
    // V013 VGA Patch Note (11) Modify 20100416 End
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save system data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveSystemData(void)
{
    CEepromWrite(_SYSTEM_DATA_ADDRESS, sizeof(StructSystemDataType), &stSystemData.MonitorFlag);
}

//--------------------------------------------------
// Description  : Load system data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadSystemData(void)
{
    CEepromRead(_SYSTEM_DATA_ADDRESS, sizeof(StructSystemDataType), &stSystemData.MonitorFlag);
if(stSystemData.SearchIndex>1)
	{
	stSystemData.SearchIndex=1;//sjp20111206
	CEepromSaveSystemData();	
	}	
	
}

//--------------------------------------------------
// Description  : Load default system data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadSystemDataDefault(void)
{
    CEepromWrite(_SYSTEM_DATA_ADDRESS, sizeof(StructSystemDataType), &tEEPROM_SYSTEM_DATA.MonitorFlag);
    stSystemData = tEEPROM_SYSTEM_DATA;
#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage("tEEPROM_SYSTEM_DATA.BackLight", tEEPROM_SYSTEM_DATA.BackLight);
	CDebugMessage("stSystemData.BackLight",stSystemData.BackLight);
#endif
	CEepromLoadSystemData();
#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage("tEEPROM_SYSTEM_DATA.BackLight_load", tEEPROM_SYSTEM_DATA.BackLight);
	CDebugMessage("stSystemData.BackLight_load",stSystemData.BackLight);
#endif
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveOsdUserData(void)
{
    CEepromWrite(_OSDUSER_DATA_ADDRESS, sizeof(StructOsdUserDataType), &stOsdUserData.OsdSettingFlag);
}

//--------------------------------------------------
// Description  : Load OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadOsdUserData(void)
{
    CEepromRead(_OSDUSER_DATA_ADDRESS, sizeof(StructOsdUserDataType), &stOsdUserData.OsdSettingFlag);
}

//--------------------------------------------------
// Description  : Load default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadOsdUserDataDefault(void)
{
    CEepromWrite(_OSDUSER_DATA_ADDRESS, sizeof(StructOsdUserDataType), &tEEPROM_OSDUSER_DATA.OsdSettingFlag);
    stOsdUserData = tEEPROM_OSDUSER_DATA;
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save OSD data Factory
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveOsdReserveData(void)
{
    CEepromWrite(_OSDRESERVE_DATA_ADDRESS, sizeof(StructOsdReserveDataType), &stOsdReserveData.OsdReserveFlag);
}

//--------------------------------------------------
// Description  : Load OSD data Factory
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadOsdReserveData(void)
{
    CEepromRead(_OSDRESERVE_DATA_ADDRESS, sizeof(StructOsdReserveDataType), &stOsdReserveData.OsdReserveFlag);
}

//--------------------------------------------------
// Description  : Load default OSD data Factory
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadOsdReserveDataDefault(void)
{
    CEepromWrite(_OSDRESERVE_DATA_ADDRESS, sizeof(StructOsdReserveDataType), &tEEPROM_OSDRESERVE_DATA.OsdReserveFlag);
    stOsdReserveData = tEEPROM_OSDRESERVE_DATA;
}

//----------------------------------------------------------------------------------------------------


//--------------------------------------------------
// Description  : Save ADC data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveAdcData(void)
{

    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
    
        CEepromWrite(_ADC_DATA_ADDRESS, sizeof(StructAdcDataType), &stAdcData.AdcGain[_RED]);
        CEepromWrite(_ADC_DATA_ADDRESS + sizeof(StructAdcDataType), 1, &g_ucAdcPGA);
    }

#if(_YPBPR_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        CEepromWrite(_ADC_DATA_ADDRESS + sizeof(StructAdcDataType) + 1, sizeof(StructAdcDataType), &stAdcData.AdcGain[_RED]);
        CEepromWrite(_ADC_DATA_ADDRESS + (sizeof(StructAdcDataType) * 2) + 1, 1, &g_ucAdcPGA);
    }
#endif
}

//--------------------------------------------------
// Description  : Load ADC data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadAdcData(void)
{
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        CEepromRead(_ADC_DATA_ADDRESS, sizeof(StructAdcDataType), &stAdcData.AdcGain[_RED]);
        CEepromRead(_ADC_DATA_ADDRESS + sizeof(StructAdcDataType), 1, &g_ucAdcPGA);
    }

#if(_YPBPR_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        CEepromRead(_ADC_DATA_ADDRESS + sizeof(StructAdcDataType) + 1, sizeof(StructAdcDataType), &stAdcData.AdcGain[_RED]);
        CEepromRead(_ADC_DATA_ADDRESS + (sizeof(StructAdcDataType) * 2) + 1, 1, &g_ucAdcPGA);
    }
#endif

}

//--------------------------------------------------
// Description  : Load default ADC data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadAdcDataDefault(void)
{
    stAdcData = tEEPROM_ADC_DATA;
    g_ucAdcPGA = 0x07;

    CEepromWrite(_ADC_DATA_ADDRESS, sizeof(StructAdcDataType), &tEEPROM_ADC_DATA.AdcGain[_RED]);
    CEepromWrite(_ADC_DATA_ADDRESS + sizeof(StructAdcDataType), 1, &g_ucAdcPGA);
    CEepromWrite(_ADC_DATA_ADDRESS + sizeof(StructAdcDataType) + 1, sizeof(StructAdcDataType), &tEEPROM_ADC_DATA.AdcGain[_RED]);
    CEepromWrite(_ADC_DATA_ADDRESS + (sizeof(StructAdcDataType) * 2) + 1, 1, &g_ucAdcPGA);
}

//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
// SJP20110625
//--------------------------------------------------
// Description  : Save LSlumi data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveLSlumiData(void)
{
	    CEepromWrite(_LSLUMI_DATA_ADDRESS, sizeof(StructLSlumiDataType), (BYTE*)&stLSlumiData.DICOM350);

}

//--------------------------------------------------
// Description  : Load LSlumi data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadLSlumiData(void)
{
	    CEepromRead(_LSLUMI_DATA_ADDRESS, sizeof(StructLSlumiDataType), (BYTE*)&stLSlumiData.DICOM350);
}


//--------------------------------------------------
// Description  : Load default Lslumi data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadLSlumiDataDefault(void)
{
	stLSlumiData=tEEPROM_LSLUMI_DATA;
	CEepromWrite(_LSLUMI_DATA_ADDRESS, sizeof(StructLSlumiDataType),(BYTE*) &tEEPROM_LSLUMI_DATA.DICOM350);//BYTE* NEED TO BE added
}

//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
// SJP20110715
//--------------------------------------------------
// Description  : Save PWMlumi data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSavePWMlumiData(void)
{
	CEepromWrite(_PWMLUMI_DATA_ADDRESS, sizeof(StructPWMlumiDataType), (BYTE*)&stPWMlumiData.DICOM350);
}
//--------------------------------------------------
// Description  : Load PWMlumi data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadPWMlumiData(void)
{
	CEepromRead(_PWMLUMI_DATA_ADDRESS, sizeof(StructPWMlumiDataType), (BYTE*)&stPWMlumiData.DICOM350);
	tOSD_DICOMlumi[0] = stPWMlumiData.DICOM350;
	tOSD_DICOMlumi[1]=	stPWMlumiData.DICOM400;
	tOSD_DICOMlumi[2]=	stPWMlumiData.DICOM450;
	tOSD_DICOMlumi[3]=stPWMlumiData.DICOM500;
	tOSD_DICOMlumi[4]=stPWMlumiData.DICOM550;
	tOSD_DICOMlumi[5]=stPWMlumiData.DICOM600;
	tOSD_DICOMlumi[6]=stPWMlumiData.DICOM650;
	tOSD_DICOMlumi[7]=	stPWMlumiData.DICOM700;
	tOSD_DICOMlumi[8]=stPWMlumiData.DICOM500;
	tOSD_DICOMlumi[9]=stPWMlumiData.DICOM500;
	tOSD_DICOMlumi[10]=stPWMlumiData.DICOM500;
}
//--------------------------------------------------
// Description  : Load default PWMlumi data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadPWMlumiDataDefault(void)
{
	stPWMlumiData=tEEPROM_PWMLUMI_DATA;
	CEepromWrite(_PWMLUMI_DATA_ADDRESS, sizeof(StructPWMlumiDataType),(BYTE*) &tEEPROM_PWMLUMI_DATA.DICOM350);//BYTE* NEED TO BE added
	tOSD_DICOMlumi[0] = stPWMlumiData.DICOM350;
	tOSD_DICOMlumi[1]=	stPWMlumiData.DICOM400;
	tOSD_DICOMlumi[2]=	stPWMlumiData.DICOM450;
	tOSD_DICOMlumi[3]=stPWMlumiData.DICOM500;
	tOSD_DICOMlumi[4]=stPWMlumiData.DICOM550;
	tOSD_DICOMlumi[5]=stPWMlumiData.DICOM600;
	tOSD_DICOMlumi[6]=stPWMlumiData.DICOM650;
	tOSD_DICOMlumi[7]=	stPWMlumiData.DICOM700;
	tOSD_DICOMlumi[8]=stPWMlumiData.DICOM500;
	tOSD_DICOMlumi[9]=stPWMlumiData.DICOM500;
	tOSD_DICOMlumi[10]=stPWMlumiData.DICOM500;
}

//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// Description  : Save Brightness/Contrast data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveBriConData(void)
{
    if(GET_INPUTSOURCE_TYPE() != _SOURCE_NONE)
    {
        CEepromWrite(_COLOR_PROC0_ADDRESS + (GET_INPUTSOURCE_TYPE()) * 5, 4, &stConBriData.Brightness);
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
        CEepromRead(_COLOR_PROC0_ADDRESS + (GET_INPUTSOURCE_TYPE()) * 5, 5, &stConBriData.Brightness);
    }
if(stConBriData.Dicom>10)
	{
	stConBriData.Dicom=0;//sjp20111207
	CEepromSaveBriConData();
	}
if(stConBriData.Gamma>4)
{
	stConBriData.Gamma =0;//sjp20111207
	CEepromSaveBriConData();
}
if((stConBriData.Contrast>0x90)||(stConBriData.Contrast<0x70))
{
	stConBriData.Contrast=0x80;//sjp20111207
	CEepromSaveBriConData();
}
if((stConBriData.Brightness>0x90)||(stConBriData.Brightness<0x70))
{
	stConBriData.Brightness=0x80;//sjp20111207
	CEepromSaveBriConData();
}
}

//--------------------------------------------------
// Description  : Load default Brightness/Contrast data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadBriConDataDefault(void)
{
    CEepromWrite(_COLOR_PROC0_ADDRESS, (5 * _SOURCE_AMOUNT), &tEEPROM_COLOR_PROC0_DATA[0].Brightness);
    CEepromLoadBriConData();
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
        CEepromWrite(_COLORTEMP_DATA_ADDRESS + (_CT_COLORTEMP_AMOUNT * 3) * GET_INPUTSOURCE_TYPE() + 3 * GET_COLOR_TEMP_TYPE(), 3, &stColorTempData.ColorTemp[_RED]);
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
        CEepromRead(_COLORTEMP_DATA_ADDRESS + (_CT_COLORTEMP_AMOUNT * 3) * GET_INPUTSOURCE_TYPE() + 3 * GET_COLOR_TEMP_TYPE(), 3, &stColorTempData.ColorTemp[_RED]);
    }
}

//--------------------------------------------------
// Description  : Load default Color Temperature data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadColorTempDataDefault(void)
{
    CEepromWrite(_COLORTEMP_DATA_ADDRESS, ((_CT_COLORTEMP_AMOUNT * 3)  * (_SOURCE_AMOUNT)), &tEEPROM_COLORTEMP_DATA[0].ColorTemp9300Red);
    CEepromLoadColorTempData();
}

//----------------------------------------------------------------------------------------------------


//--------------------------------------------------
// Description  : Load EDID data to DDC RAM
// Input Value  : ucTable --> Default EDID Table or Flash Data
// Output Value : None
//--------------------------------------------------
void CEepromLoadDDCData(void)
{
    WORD cnt;
#if(_EMBEDDED_EDID == _ON)
#if(_MCU_TYPE == _REALTEK_EMBEDDED)

    for(cnt = 0; cnt < 128; cnt++)
    {
        MCU_DDCRAM_A0[cnt] = tEDID_TABLE_A0[cnt];
    }

#if(_TMDS_SUPPORT == _ON)
    for(cnt = 0; cnt < 256; cnt++)
    {
#if((_DDC_CHANNEL_FOR_D0 == _DDC2))
        MCU_DDCRAM_DDC2[cnt] = tEDID_TABLE_D0[cnt];
        MCU_DDCRAM_DDC3[cnt] = tEDID_TABLE_D1[cnt];
#else
        MCU_DDCRAM_DDC2[cnt] = tEDID_TABLE_D1[cnt];
        MCU_DDCRAM_DDC3[cnt] = tEDID_TABLE_D0[cnt];
#endif
    }

#endif

#else

    for(cnt = 0; cnt < 128; cnt++)
    {
        MCU_DDCRAM_A0[cnt] = tEDID_TABLE_A0[cnt];
    }

    for(cnt = 0; cnt < 256; cnt++)
    {
        MCU_DDCRAM_D0[cnt] = tEDID_TABLE_D0[cnt];
    }

#endif // End of #if(_MCU_TYPE == _REALTEK_EMBEDDED)

#else //Else of #if(_EMBEDDED_EDID == _ON)

#if(_MCU_TYPE == _REALTEK_EMBEDDED)

    for(cnt = 0; cnt < 256; cnt++)
    {
#if((_DDC_CHANNEL_FOR_D0 == _DDC2) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))
        MCU_DDCRAM_DDC2[cnt] = tEDID_TABLE_D0[cnt];
#elif(_DDC_CHANNEL_FOR_D0 == _DDC3) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        MCU_DDCRAM_DDC3[cnt] = tEDID_TABLE_D0[cnt];
#elif(_DDC_CHANNEL_FOR_D1 == _DDC2) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        MCU_DDCRAM_DDC2[cnt] = tEDID_TABLE_D1[cnt];
#elif(_DDC_CHANNEL_FOR_D1 == _DDC3) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        MCU_DDCRAM_DDC3[cnt] = tEDID_TABLE_D1[cnt];
#endif
    }
#endif // End of #if(_MCU_TYPE == _REALTEK_EMBEDDED)
#endif //End of #if(_EMBEDDED_EDID == _ON)

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
#endif

#endif  //End of #if(_MEMORY_LOCATION == _EEPROM)



//--------------------------------------------------------------------------------------------------------------------
//******************* Using Flash to replace external Eeprom *******************//
//--------------------------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------------------------


#endif  // End of #if(_OSD_TYPE == _REALTEK_OSD)


