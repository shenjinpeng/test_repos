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
// ID Code      : Osd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __NONE_OSD__

#include "Common\Header\Include.h"

#if(_OSD_TYPE == _NONE_OSD)

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdHandler(void)
{
    COsdSystemFlowProc();
    COsdEventMsgProc();

    if(ucCurrState == _ACTIVE_STATE)
    {
        if(ucKeyMessage < _KEY_AMOUNT)
        {
            (*OperationTable[ucOsdState][ucKeyMessage])();

            if(stOsdUserData.OsdTimeout > 3)
            {
                CTimerReactiveTimerEvent(SEC(stOsdUserData.OsdTimeout), COsdDispOsdTimerEvent);
            }
            else
            {
                CTimerCancelTimerEvent(COsdDispOsdTimerEvent);
            }
        }
    }

#if(_SWITCH_INPUT_SOURCE == _ON)
    else
    {
        if(ucKeyMessage == _EXIT_KEY_MESSAGE)
        {
            CSourceSwitchInputSource();
        }
    }
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdSystemFlowProc(void)
{
    BYTE connect = 1;

    switch(ucCurrState)
    {
        case _PWOFF_STATE:
            break;

        case _INITIAL_STATE:
            break;

        case _SEARCH_STATE:
            break;

        case _ACTIVE_STATE:
            if(GET_OSD_READYFORDISPLAY() == _TRUE)
            {
                CLR_OSD_READYFORDISPLAY();
                CAdjustBackgroundColor(0x00, 0x00, 0x00);

                if(GET_FIRST_LOADFONT() == _TRUE)
                {
                    CLR_FIRST_LOADFONT();
                    COsdDispFirstTimeLoadFont();
                }
            }
            break;

        case _NOSIGNAL_STATE:
            if(GET_OSD_READYFORDISPLAY() == _TRUE)
            {

                CLR_OSD_READYFORDISPLAY();
                CAdjustBackgroundColor(0x00, 0x00, 0x00);

#ifdef _A0_PORT
                connect = connect & bA0_CONNECT;
#endif

#ifdef _A1_PORT
                connect = connect & bA1_CONNECT;
#endif

#ifdef _D0_PORT

#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
                connect = connect & CDpAuxPinCableConnect();
#else
                connect = connect & bD0_CONNECT;
#endif

#endif

#ifdef _D1_PORT
                connect = connect & bD1_CONNECT;
#endif

                    if(connect)
                    {
                        CTimerReactiveTimerEvent(SEC(1), CModeNoCableEvent);
                    }
                    else
                    {
                        CTimerReactiveTimerEvent(SEC(1), CModeNoSignalEvent);
                        //CTimerActiveTimerEvent(SEC(6), CModePowerSavingEvent);
                    }
            }
            break;

        case _SLEEP_STATE:
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdEventMsgProc(void)
{
    switch(ucOsdEventMsg)
    {
        case _SHOW_NOSIGNAL_MSG:
            break;

        case _SHOW_NOCABLE_MSG:
            break;

        case _SHOW_NOSUPPORT_MSG:
            break;

        case _SAVE_EE_MODEUSERDATA_MSG:
            CEepromSaveModeData(stModeInfo.ModeCurr);
            break;

        case _SAVE_EE_SYSTEMDATA_MSG:
            CEepromSaveSystemData();
            break;

        case _SAVE_EE_OSDUSERDATA_MSG:
            CEepromSaveOsdUserData();
            break;

#if(_MEMORY_LOCATION == _EEPROM)
        case _SAVE_EE_OSDRESERVEDATA_MSG:
            CEepromSaveOsdReserveData();
            break;
#endif

        case _SAVE_EE_ADCDATA_MSG:
            CEepromSaveAdcData();
            break;

        case _SAVE_EE_COLORPROC0_MSG:
            CEepromSaveBriConData();
            break;

        case _SAVE_EE_COLORPROC1_MSG:
            CEepromSaveColorTempData();
            break;

        case _ENTER_FACTORY_MODE_MSG:
            stOsdUserData.OsdSettingFlag |= _BIT7;
            break;

        case _CHANGE_SOURCE_MSG:
            CEepromSaveSystemData();


            CModeResetMode();
            break;

        case _DO_AUTO_CONFIG:
            break;

        default:
            break;
    }

    ucOsdEventMsg = _NONE_MSG;
}


//----------------------------------------------------------------------------------------------------
// OSD Menu None Operation
//----------------------------------------------------------------------------------------------------
void COsdNone(void) // Just for Demo Fuction
{
    BYTE temp;

    //-------------------------------
    // Row Command & Charactar Command & OSD Fuctiom
    //-------------------------------
    COsdFxApplyMapSetting(_OSD_MAP0);
    COsdFxDisableOsd();
    COsdFxEnableOsd();

    temp = COsdFxGetColWithinText(15, 4, tMain_Menu_TABLE[0], _TEXTWITH);

    //-------------------------------
    // Font & Icon Fuctiom
    //-------------------------------
    COsdFxLoadText(ROW(0), COL(0), 0, tMain_Menu_TABLE[0]);
    COsdFxLoadIcon(ROW(0), COL(0), tMain_Menu_TABLE[0]);
    COsdDispClearText(ROW(5), COL(5), 18, 15);

    COsdFxHLine(ROW(0), COL(0), LENGTH(1), 0x0e, _WRITE_BYTE1);
    COsdFxVLine(ROW(0), COL(0), LENGTH(1), 0x0e, _WRITE_BYTE1);
    COsdFxShowNumber(ROW(0), COL(0), 100, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(22), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange2bitColor(ROW(0), COL(0), WIDTH(25), HEIGHT(5), COLOR00(_CP_BLACK), COLOR01(_CP_WHITE), COLOR10(_CP_WHITE), COLOR11(_CP_BLUE));
    COsdFxChange4bitLUTColor(ROW(4), COL(12), WIDTH(3), HEIGHT(1), COLOR00(_CP_WHITE));

    //-------------------------------
    // Windows Fuctiom
    //-------------------------------
    COsdFxDrawWindow(XSTART(0), YSTART(0), XEND(10), YEND(10), tOSD_WINDOW0_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_WHITE), tOSD_WINDOW0_STYLE);
    COsdFxCloseWindow(WINNO(0));
    COsdFxSetPosition(WIDTH(10), WIDTH(10), stOsdUserData.OsdHPos, stOsdUserData.OsdVPos, 0x01);

    //-------------------------------
    // Arithmetic Fuctiom
    //-------------------------------
    stModeUserData.HPosition = COsdFxDetOverRange(stModeUserData.HPosition, COsdFxGetHPositionRange(_GET_HPOSITIONRANGE_MAX), COsdFxGetHPositionRange(_GET_HPOSITIONRANGE_MIN), _DET_OVERRANGE_MAX);
    stModeUserData.VPosition = COsdFxDetOverRange(stModeUserData.VPosition, COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MAX), COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MIN), _DET_OVERRANGE_MAX);
    stModeUserData.Clock = COsdFxDetOverRange(stModeUserData.Clock, COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MAX), COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN), _DET_OVERRANGE_MIN);

    temp = COsdDispRealToPercent(stConBriData.Contrast, _CONTRAST_MAX, _CONTRAST_MIN);
    stConBriData.Contrast = COsdDispPercentToRealValue(stConBriData.Contrast, _CONTRAST_MAX, _CONTRAST_MIN);

    CAutoDoAutoConfig();
    CAutoDoWhiteBalance();
    CAdjustVolume(stOsdUserData.Volume);
    CSourceSwitchInputPort(_D0_INPUT_PORT);
    CSourceSwitchInputSource();
}


void COsdMenuNone(void)
{
    CAutoDoAutoConfig();
}

void COsdLeftNone(void)
{
    CSourceSwitchInputSource();
}

void COsdRightNone(void)
{
}

void COsdExitNone(void)
{
    COsdNone();
}

#endif // End of #if(_OSD_TYPE == _NONE_OSD)

