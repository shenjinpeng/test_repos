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

#define __REALTEK_OSD__

#include "Common\Header\Include.h"

#if(_OSD_TYPE == _REALTEK_OSD)

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdHandler(void)
{
    COsdSystemFlowProc();
    COsdEventMsgProc();
#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
    if(((ucCurrState == _ACTIVE_STATE ) || (ucCurrState == _SLEEP_STATE) || (ucCurrState == _NOSIGNAL_STATE) || (ucCurrState == _NOSUPPORT_STATE)))
    {
        if(((ucCurrState == _SLEEP_STATE) || (ucCurrState == _NOSIGNAL_STATE) || (ucCurrState == _NOSUPPORT_STATE)) && (ucKeyMessage == _MENU_KEY_MESSAGE) && (ucOsdState == _MENU_NONE)&&!bAgeModeOn)
        {
        #if _DEBUG_MESSAGE_SUPPORT
		CDebugMessage("CWakeUpShowSource", 0);
	 #endif
            CWakeUpShowSource();
        }

	if(((ucCurrState == _SLEEP_STATE) || (ucCurrState == _NOSIGNAL_STATE) )&&(ucKeyMessage ==_AGE_MODE_MESSAGE) &&(ucOsdState == _MENU_NONE)&&bTimerAgeModeCtrl)
		{
		if(bAgeModeOn)
			{
			bAgeModeOn=_FALSE;	
			bTimerAgeModeCtrl=_FALSE;
			ucTimer0Cnt1=600;
			CModeResetMode();
			#if _DEBUG_MESSAGE_SUPPORT
			CDebugMessage("bAgeModeOn", bAgeModeOn);
			CDebugMessage("bTimerAgeModeCtrl", bTimerAgeModeCtrl);

			#endif

			}
		else
			{
				{
				bAgeModeOn=_TRUE;
				ucTimer0Cnt1=100;
				CScalerSetBit(_HOST_CTRL_01, ~_BIT1, 0x00);
				CModeSetFreeRun();
				CScalerEnableDisplayTiming();
				CPowerPanelOn();

				CScalerSetByte(0x6C, 0x20);
				CScalerSetByte(0x6D, 0xFF);
				CScalerSetByte(0x6D, 0xFF);
				CScalerSetByte(0x6D, 0xFF);			

				if(!bAgeModeWhiteFlag)
					bAgeModeWhiteFlag=_TRUE;
				else
					bAgeModeWhiteFlag=_FALSE;
				}

			#if _DEBUG_MESSAGE_SUPPORT
			CDebugMessage("bAgeModeOn2", bAgeModeOn);
			CDebugMessage("bTimerAgeModeCtrl2", bTimerAgeModeCtrl);

			#endif

			
			}
		
		
		
		}
        if((ucKeyMessage < _KEY_AMOUNT) && ((ucCurrState == _ACTIVE_STATE ) || (GET_SOURCE_OSD_STATUS()))&&!bAgeModeOn)
        {
        #if _DEBUG_MESSAGE_SUPPORT
		CDebugMessage("ucOsdState", ucOsdState);
		CDebugMessage("ucKeyMessage",ucKeyMessage);
	 #endif
            (*OperationTable[ucOsdState][ucKeyMessage])();

            if(GET_SOURCE_OSD_STATUS())
            {
                CTimerReactiveTimerEvent(SEC(2), COsdDispOsdTimerEvent);
                CTimerReactiveTimerEvent(SEC(2), CModePowerSavingEvent);
            }
            else
            {
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
	else if((ucKeyMessage ==4) && ((ucCurrState == _ACTIVE_STATE ) || (GET_SOURCE_OSD_STATUS()))&&!bAgeModeOn)//for auto key issue sjp20110804
		{
		
		(*OperationTable[0][1])();
		
		}
	else if((ucKeyMessage ==6) && ((ucCurrState == _ACTIVE_STATE ) || (GET_SOURCE_OSD_STATUS()))&&!bAgeModeOn)//for autoCOLOR 20110809	
		{
			(*OperationTable[0][2])();
		}
	/*else if ((ucKeyMessage ==8) && ((ucCurrState == _ACTIVE_STATE ) || (GET_SOURCE_OSD_STATUS())))
	{
	    GCMode = 1;//Factory mode sjp20110625
	   (*OperationTable[0][0])();

	}
	else if((ucKeyMessage ==9) && ((ucCurrState == _ACTIVE_STATE ) || (GET_SOURCE_OSD_STATUS())))
	{
	   GCMode = 2;//for PWMLUMI
	   (*OperationTable[0][0])();	
		}	*/
    }
#else
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
#endif  // End of (_SWITCH_INPUT_SOURCE_OSD == _ON)

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

#if(_CABLE_CONNECT_CHECK)

    BYTE connect_d0 = 1, connect_d1 = 1, connect_a0 = 1, connect_a1 = 1;


#endif

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

#if(_DDCCI_SUPPORT == _ON)
                if(GET_DDCCI_STATUS())
                {

#if((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122))

                    if((GET_INPUT_PORT(g_ucSearchIndex) == _A0_INPUT_PORT)
                    || (GET_INPUT_PORT(g_ucSearchIndex) == _A1_INPUT_PORT)
                    || (GET_INPUT_PORT(g_ucSearchIndex) == _VI_INPUT_PORT))
                    {
                        MCU_I2C_SET_SLAVE_FF27 = MCU_I2C_SET_SLAVE_FF27 & (~_BIT0);
                    }
                    else
                    {
                        MCU_I2C_SET_SLAVE_FF27 = MCU_I2C_SET_SLAVE_FF27 | (_BIT0);
                    }

#elif(_MCU_TYPE == _REALTEK_EMBEDDED)

                    if((GET_INPUT_PORT(g_ucSearchIndex) == _A0_INPUT_PORT)
                    || (GET_INPUT_PORT(g_ucSearchIndex) == _A1_INPUT_PORT)
                    || (GET_INPUT_PORT(g_ucSearchIndex) == _VI_INPUT_PORT))
                    {
                        MCU_I2C_CHANNEL_CTRL_FF2B &= (~_BIT0);
                        MCU_I2C_SET_SLAVE_FF23 = MCU_I2C_SET_SLAVE_FF23 & (~_BIT0);
                    }
                    else if(GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT)
                    {

#if(_DDC_CHANNEL_FOR_D0 == _DDC2)
                        MCU_I2C_CHANNEL_CTRL_FF2B &= (~_BIT0);
                        MCU_I2C_SET_SLAVE_FF23 |= _BIT0;
#else
                        MCU_I2C_CHANNEL_CTRL_FF2B |= _BIT0;
                        MCU_I2C_SET_SLAVE_FF23 &= (~_BIT0);
#endif

                    }
                    else
                    {

#if(_DDC_CHANNEL_FOR_D1 == _DDC2)
                        MCU_I2C_CHANNEL_CTRL_FF2B &= (~_BIT0);
                        MCU_I2C_SET_SLAVE_FF23 |= _BIT0;
#else
                        MCU_I2C_CHANNEL_CTRL_FF2B |= _BIT0;
                        MCU_I2C_SET_SLAVE_FF23 &= (~_BIT0);
#endif

                    }
#endif // End of _MCU_TYPE

                }
#else   // #if(_DDCCI_SUPPORT == _ON)

    #if((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122))
                    MCU_I2C_SET_SLAVE_FF27 = 0x6a;

    #elif(_MCU_TYPE == _REALTEK_EMBEDDED)
                    MCU_I2C_SET_SLAVE_FF23 = 0x6a;
    #endif

#endif  // End of #if(_DDCCI_SUPPORT == _ON)

                CLR_OSD_READYFORDISPLAY();
                CAdjustBackgroundColor(0x00, 0x00, 0x00);

                if(GET_FIRST_LOADFONT() == _TRUE)
                {
                    CLR_FIRST_LOADFONT();
                    COsdDispFirstTimeLoadFont();
                }
            }

            break;

        case _NOSUPPORT_STATE:
            if(GET_OSD_READYFORDISPLAY() == _TRUE)
            {
                CLR_OSD_READYFORDISPLAY();
                CAdjustBackgroundColor(0xff, 0x00, 0x00);
                CTimerReactiveTimerEvent(SEC(1), CModeNoSupportEvent);
            }

            break;

        case _NOSIGNAL_STATE:
            if(GET_OSD_READYFORDISPLAY() == _TRUE)
            {

                CLR_OSD_READYFORDISPLAY();
                CAdjustBackgroundColor(0x00, 0x00, 0x00);
#if(_CABLE_CONNECT_CHECK)

#ifdef _A0_PORT
                connect_a0 = connect & bA0_CONNECT;
#endif

#ifdef _A1_PORT
                connect_a1 = connect & bA1_CONNECT;
#endif

#ifdef _D0_PORT

#if(_DP_SUPPORT == _ON)

#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
                connect_d0 = connect & CDpAuxPinCableConnect();
#else
                connect_d0 = connect & bD0_CONNECT;
#endif

#endif  // End of #if(_DP_SUPPORT == _ON)

#endif

#ifdef _D1_PORT
                connect_d1 = connect & bD1_CONNECT;
#endif

                connect = (connect_a0 & connect_a1 & connect_d0 & connect_d1);

#endif



                if(connect)
                {
                    CTimerReactiveTimerEvent(SEC(2), CModeNoCableEvent);
                    CTimerActiveTimerEvent(SEC(4), CModePowerSavingEvent);
                    // In DP Power Management,this stage must to enter PowerDown Mode
                }
                else
                {
                    CTimerReactiveTimerEvent(SEC(1), CModeNoSignalEvent);
                    CTimerActiveTimerEvent(SEC(3), CModePowerSavingEvent);
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
            COsdDispNoSignalProc();
            break;

        case _SHOW_NOCABLE_MSG:
            COsdDispNoCableProc();
            break;

        case _SHOW_NOSUPPORT_MSG:
            COsdDispNoSupportProc();
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
	    CEepromSaveSystemData();
            break;

        case _SAVE_EE_COLORPROC1_MSG:
            CEepromSaveColorTempData();
            break;

        case _ENTER_FACTORY_MODE_MSG:
            break;

        case _CHANGE_SOURCE_MSG:

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
            CEepromSaveOsdUserData();
#endif

            CEepromSaveSystemData();

#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("CModeResetMode__CHANGE_SOURCE_MSG",0);
//CDebugMessage("g_ucSearchIndex__CHANGE_SOURCE_MSG=%d",g_ucSearchIndex);
#endif

            CModeResetMode();
            break;

        case _DO_AUTO_CONFIG:
            COsdDispAutoProc();

            CTimerReactiveTimerEvent(SEC(0), CModeOsdDisplayTimingAndInputEvent);
            break;

        case _SHOW_TIMINGINPUT_MSG:
            COsdDispTimingAndInputSource();
            CTimerActiveTimerEvent(SEC(5), COsdDispOsdTimerEvent);
            break;
	case     _SAVE_LSLUMIDATA_MSG:
	     CEepromSaveLSlumiData();//lslumi DATA save sjp20110625
	     break;
	case    _SAVE_PWMLUMIDATA_MSG:
		CEepromSavePWMlumiData();//PWM DATA save sjp20110715
		break;
        default:
            break;
    }

    ucOsdEventMsg = _NONE_MSG;
}

void COsdMenuNone(void)
{
    COsdFxDisableOsd();

    CScalerLoadHardwareVLCFont(tFONT_GLOBAL2ND, 0x54);
    CScalerLoadHardwareVLCFont(tFONT_CHI, 0x60);
    //stOsdUserData.Language=_CHINESE_S;
	switch(stOsdUserData.Language)
    {
        case _CHINESE_T:
        case _CHINESE_S:
            CScalerLoadHardwareVLCFont(tFONT_CHI, 0x60);
            break;

        case _JAPAN:
            CScalerLoadHardwareVLCFont(tFONT_JAP, 0x60);
            break;
    }

    COsdFxApplyMapSetting(_OSD_MAP0);

    COsdFxChange1bitColor(ROW(0), COL(0), WIDTH(12), HEIGHT(9), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange2bitColor(ROW(18), COL(3), WIDTH(10), HEIGHT(2), COLOR00(_CP_BLACK), COLOR01(_CP_WHITE), COLOR10(_CP_WHITE), COLOR11(_CP_BLUE));

    COsdDispClearIcon(ROW(18), COL(3), 10, 2);//zhangping 101109
   COsdFxLoadIcon(ROW(18), COL(3), tOSD_RT_MARK_ICO1);//zhangping 101109
   COsdDispDrawInitWindow();
   #if _DEBUG_MESSAGE_SUPPORT
   CDebugMessage("stConBriData.Dicom==", stConBriData.Dicom);
   CDebugMessage("stConBriData.Gamma==", stConBriData.Gamma);
   #endif
   if((stConBriData.Gamma==0))
	   COsdFxChange1bitColor(ROW(1+stConBriData.Dicom), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));//sjp20110625
   else
   	{
   	if(stConBriData.Gamma==4)//zp for OSD display the same with table loaded
   		{
   		stConBriData.Gamma=3;
	   COsdFxChange1bitColor(ROW(11+stConBriData.Gamma), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));//sjp20110625
   		}
	else
		COsdFxChange1bitColor(ROW(11+stConBriData.Gamma), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));//sjp20110625
	   
   	}

  //  COsdDispClearIcon(ROW(9), COL(0), 2, 15);

    COsdFxCloseWindow(WINNO(1));
    COsdFxCloseWindow(WINNO(2));
    COsdFxCloseWindow(WINNO(3));
    COsdFxCloseWindow(WINNO(4));
    COsdFxCloseWindow(WINNO(6));
	
if(GCMode==1)
{	
    COsdFxDrawWindow(XSTART(0), YSTART(0), XEND(232), YEND(370), tOSD_WINDOW0_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_LIGHTBLUE), tOSD_WINDOW0_STYLE);

    COsdFxDrawWindow(XSTART(0), YSTART(314), XEND(232), YEND(370), tOSD_WINDOW5_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_GRAY), tOSD_WINDOW5_STYLE);

COsdFxShowNumber(ROW(1), COL(14), stLSlumiData.DICOM350, (_ALIGN_LEFT| _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110624   
COsdFxShowNumber(ROW(2), COL(14), stLSlumiData.DICOM400, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110624 	    		
COsdFxShowNumber(ROW(3), COL(14), stLSlumiData.DICOM450, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110624	
COsdFxShowNumber(ROW(4), COL(14), stLSlumiData.DICOM500, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110624		
COsdFxShowNumber(ROW(5), COL(14), stLSlumiData.DICOM550, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110624		
COsdFxShowNumber(ROW(6), COL(14), stLSlumiData.DICOM600, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110624		
COsdFxShowNumber(ROW(7), COL(14), stLSlumiData.DICOM650, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110624		
COsdFxShowNumber(ROW(8), COL(14), stLSlumiData.DICOM700, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110624		
}
else if(GCMode==2)//for PWMLUMI
{
    COsdFxDrawWindow(XSTART(0), YSTART(0), XEND(232), YEND(370), tOSD_WINDOW0_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_LIGHTBLUE), tOSD_WINDOW0_STYLE);

    COsdFxDrawWindow(XSTART(0), YSTART(314), XEND(232), YEND(370), tOSD_WINDOW5_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_GRAY), tOSD_WINDOW5_STYLE);

COsdFxShowNumber(ROW(1), COL(14), stPWMlumiData.DICOM350, (_ALIGN_LEFT| _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110715  
COsdFxShowNumber(ROW(2), COL(14), stPWMlumiData.DICOM400, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110715 	    		
COsdFxShowNumber(ROW(3), COL(14), stPWMlumiData.DICOM450, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110715	
COsdFxShowNumber(ROW(4), COL(14), stPWMlumiData.DICOM500, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110715		
COsdFxShowNumber(ROW(5), COL(14), stPWMlumiData.DICOM550, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110715		
COsdFxShowNumber(ROW(6), COL(14), stPWMlumiData.DICOM600, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110715		
COsdFxShowNumber(ROW(7), COL(14), stPWMlumiData.DICOM650, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110715		
COsdFxShowNumber(ROW(8), COL(14), stPWMlumiData.DICOM700, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//sjp20110715		
}
else
{
    COsdFxDrawWindow(XSTART(0), YSTART(0), XEND(192), YEND(370), tOSD_WINDOW0_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_LIGHTBLUE), tOSD_WINDOW0_STYLE);

    COsdFxDrawWindow(XSTART(0), YSTART(314), XEND(192), YEND(370), tOSD_WINDOW5_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_GRAY), tOSD_WINDOW5_STYLE);
}
    // V015 VGA Patch Note (12) Modify 20100625 Start
    // Patch Reason : Modify OSD Reslotion show type for vedio timing.
    /*
    // V012 Modify 20100320 Start
    // V012 Patch Note (12) : Show video timing info in OSD.
    /*
    COsdFxShowNumber(ROW(23), COL(10), stModeInfo.IHWidth, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
    COsdFxHLine(ROW(23), COL(11), LENGTH(1), 0x0e, _WRITE_BYTE1);
    COsdFxShowNumber(ROW(23), COL(12), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    * /
    #if(_YPBPR_SUPPORT == _ON)
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
         switch(stModeInfo.ModeCurr)
        {
            // V013 VGA Patch Note (5) 20100409 Modify Start
            // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
            /*
            case _VIDEO_720x576i_50HZ:
            case _VIDEO_720x480i_60HZ:
            * /
            case _VIDEO_1440x576i_50HZ:
            case _VIDEO_1440x480i_60HZ:
            // V013 VGA Patch Note (5) 20100409 Modify End

            case _VIDEO_1920x1080i_50HZ:
            case _VIDEO_1920x1080i_60HZ:

            // V013 VGA Patch Note (5) 20100409 Modify Start
            // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
            case _VIDEO_1920x1080i_50HZ_2:
            // V013 VGA Patch Note (5) 20100409 Modify End

                COsdFxShowNumber(ROW(23), COL(10), stModeInfo.IVHeight * 2, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                COsdFxHLine(ROW(23), COL(14), LENGTH(1), _i_, _WRITE_BYTE1);
            break;

            case _VIDEO_720x576p_50HZ:
            case _VIDEO_720x480p_60HZ:
            case _VIDEO_1280x720p_50HZ:
            case _VIDEO_1280x720p_60HZ:
            case _VIDEO_1920x1080p_50HZ:
            case _VIDEO_1920x1080p_60HZ:
            default:
                COsdFxShowNumber(ROW(23), COL(10), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                COsdFxHLine(ROW(23), COL(14), LENGTH(1), _p_, _WRITE_BYTE1);
            break;
        }
    }
    else
    #endif
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
        {
            if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
            {
                pData[0] = stModeInfo.ModeCurr;
            }
            else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
            {
                CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);
                pData[0] = pData[(stModeInfo.ModeCurr % 4) * 4];
            }

            switch(pData[0])
            {
                // V013 VGA Patch Note (24) Modify 20100514 Start
                // Patch Reason : Mode search updates.
                /*
                case _MODE_720x480i_60Hz:
                case _MODE_720x576i_50Hz:
                * /
                // V013 VGA Patch Note (24) Modify 20100514 End

                case _MODE_1920x1080i_50Hz:
                case _MODE_1920x1080i_60HZ:
                case _MODE_1440x480i_60HZ:
                case _MODE_1440x576i_50Hz:
                case _MODE_1920x1080i_50HZ_2:
                    COsdFxShowNumber(ROW(23), COL(10), stModeInfo.IVHeight * 2, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                    COsdFxHLine(ROW(23), COL(14), LENGTH(1), _i_, _WRITE_BYTE1);
                    break;

                case _MODE_720x480p_60HZ:
                case _MODE_720x576p_50Hz:
                case _MODE_1280x720p_50HZ:
                case _MODE_1280x720p_60HZ:
                case _MODE_1920x1080p_50Hz:
                case _MODE_1920x1080p_60HZ:
                    COsdFxShowNumber(ROW(23), COL(10), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                    COsdFxHLine(ROW(23), COL(14), LENGTH(1), _p_, _WRITE_BYTE1);
                    break;

                default:
                    COsdFxShowNumber(ROW(23), COL(10), stModeInfo.IHWidth, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                    COsdFxHLine(ROW(23), COL(11), LENGTH(1), 0x0e, _WRITE_BYTE1);
                    COsdFxShowNumber(ROW(23), COL(12), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
                    break;
            }
        }
        else
        {
            COsdFxShowNumber(ROW(23), COL(10), stModeInfo.IHWidth, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
            COsdFxHLine(ROW(23), COL(11), LENGTH(1), 0x0e, _WRITE_BYTE1);
            COsdFxShowNumber(ROW(23), COL(12), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
        }
    }
    // V012 Modify 20100320 End

    COsdFxShowNumber(ROW(23), COL(17), (stModeInfo.IVFreq + 5) / 10, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2));

    COsdFxHLine(ROW(23), COL(19), LENGTH(1), _H_, _WRITE_BYTE1);
    COsdFxHLine(ROW(23), COL(20), LENGTH(1), _z_, _WRITE_BYTE1);

    COsdFxChange1bitColor(ROW(23), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_PINK), BGCOLOR(_CP_BLACK));
    */
 //   COSDDispTimingInfoStyle();
    // V015 VGA Patch Note (12) Modify 20100625 End
	if((stConBriData.Gamma==0)||(stConBriData.Gamma==4))
		COsdDispPenPoint(ROW(17), COL(3), ROW(5), COL(3), _MENU_DICOM_SETTING);
	else		
		COsdDispPenPoint(ROW(17), COL(3), ROW(5), COL(3), _MENU_GAMMA_SETTING);


    // V016 System Patch Note (1) Modify 20100729 Start
    // Patch Reason : Modify OSD Set position and Draw Window Function
    /*
    COsdFxSetPosition(WIDTH(280), WIDTH(400), stOsdUserData.OsdHPos, stOsdUserData.OsdVPos, 0x01);
    */
    COsdFxSetPosition(WIDTH(1040), WIDTH(440), stOsdUserData.OsdHPos, stOsdUserData.OsdVPos, 0x01);
    // V016 System Patch Note (1) Modify 20100729 End

    COsdFxEnableOsd();
}

void COsdLeftNone(void)// aoto keymessage sjp20110804
{
     if(ucKeyMessage==4)
	{
			stConBriData.Dicom=10;
			stConBriData.Gamma=0;
			Adjust_LUTtable(stConBriData.Dicom+3);//CTMRI TABLE SJP20110804
			stSystemData.BackLight=tOSD_DICOMlumi[stConBriData.Dicom] ;
				COsdLeftSubBrightness();        
			//CAdjustBacklight(stSystemData.BackLight);
			(*OperationTable[0][0])();
			
	}
    /*COsdFxDisableOsd();
    COsdDispAutoProc();*/
}

void COsdRightNone(void)
{
     if(ucKeyMessage==6)
	{
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("11111111111111",0);
#endif
	
    COsdFxDisableOsd();
    COsdDispAutoColorProc();
	} 
//	COsdMenuFAutoColor();
}

void COsdExitNone(void)
{
#if(_SWITCH_INPUT_SOURCE == _ON)
    CSourceSwitchInputSource();
#endif
}

//----------------------------------------------------------------------------------------------------
// OSD "ColorSetting" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuDicomSetting(void)
{
/*
    ucOsdState = _MENU_SUB_DICOM;

    COsdFxDrawWindow(XSTART(80), YSTART(90), XEND(460), YEND(108), tOSD_WINDOW1_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_GRAY), tOSD_WINDOW1_STYLE);
//    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
*/
if((GCMode==1) ||(GCMode==2))//sjp20110715
{

   ucOsdState =117;//sjp20110620 
}
   if( ucOsdState == _MENU_DICOM_SETTING)
   	{
 //  	 stConBriData.Dicom=0;
	     	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("stConBriData.Dicom4==", stConBriData.Dicom);

#endif

              ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;
        
       }

  else if (ucOsdState == _MENU_SIGNAL_SWITCH)
  	{
	if(GET_INPUTSOURCE_TYPE()==_SOURCE_VGA)
			COsdMenuSingalDVI();

	else
			COsdMenuSingalVGA();       

       }

else if(ucOsdState == _MENU_AUTO_ADJUST_SETTING)
	{
	
        COsdDispAutoProc();

	}

}

void COsdLeftDicomSetting(void)
{



/*
    if(stConBriData.Dicom<8)
    	{
		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_SIGNAL_SWITCH);
		COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
	}
    else
    	{
		COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_GAMMA_SETTING);
		COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
	}

*/

if(ucOsdState ==_MENU_DICOM_SETTING)
{
    if(stConBriData.Dicom==0)
    	{
#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState2==", ucOsdState);

#endif

		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_AUTO_ADJUST_SETTING);
		COsdFxChange1bitColor(ROW(1), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));//SJP20110625 LONGER BLACK LINE
		COsdFxChange1bitColor(ROW(16), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));//SJP20110625 LONGER BLACK LINE
    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState3==", ucOsdState);

#endif
		
	}

    else if ((stConBriData.Dicom>0)&&(stConBriData.Dicom<=10))
    	{
    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("stConBriData.Dicom2==", stConBriData.Dicom);

#endif

    	
    	       stConBriData.Dicom--;
#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("stConBriData.Dicom3==", stConBriData.Dicom);

#endif

		COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_DICOM_SETTING);
		COsdFxChange1bitColor(ROW(1+stConBriData.Dicom+1), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));//SJP20110625 LONGER BLACK LINE
		COsdFxChange1bitColor(ROW(1+stConBriData.Dicom), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));//SJP20110625 LONGER BLACK LINE
		if((stConBriData.Dicom>=0)&&(stConBriData.Dicom<=7))
		{			
		Adjust_LUTtable(stConBriData.Dicom+3);//DICOM700table sjp20110615
		if(stSystemData.BackLight<2500)//sjp 20110927 for pwm bug
			stSystemData.BackLight=stSystemData.BackLight+200;//SJP20110923 FOR pwm VALUE
	//	else 
	//		stSystemData.BackLight = stSystemData.BackLight+(65535-stSystemData.BackLight)/2;//sjp 20110927 for pwm bug
		}
		else if((stConBriData.Dicom>7)&&(stConBriData.Dicom<=10))//sjp20110615
			{
			Adjust_LUTtable(stConBriData.Dicom+3);//DSA DSI CTMRI TABLE SJP20110615
			stSystemData.BackLight=tOSD_DICOMlumi[stConBriData.Dicom] ;
			}
		//CAdjustBrightness( stConBriData.DicomLumi);
		COsdLeftSubBrightness();
		}
}
/*
else if(ucOsdState ==_MENU_SIGNAL_SWITCH)
{

    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState4==", ucOsdState);

#endif


		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_DICOM_SETTING);
		COsdFxChange1bitColor(ROW(9), COL(1), WIDTH(10), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(8), COL(1), WIDTH(10), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		stConBriData.Dicom=7;
		Adjust_LUTtable(3+stConBriData.Dicom);
		stSystemData.BackLight=tOSD_DICOMlumi[stConBriData.Dicom] ;
		//CAdjustBrightness( stConBriData.DicomLumi);
		COsdLeftSubBrightness();
    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState5==", ucOsdState);

#endif

		
}

else if(ucOsdState ==_MENU_AUTO_ADJUST_SETTING)
{
    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState6==", ucOsdState);

#endif


		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3),_MENU_SIGNAL_SWITCH);
		COsdFxChange1bitColor(ROW(10), COL(1), WIDTH(10), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(9), COL(1), WIDTH(10), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));


    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState7==", ucOsdState);

#endif
		
}

*/
	ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;// zp for data save
}

void COsdRightDicomSetting(void)
{
/*
#if(_DDCCI_SUPPORT == _ON)
    COsdDispPenPoint(ROW(5), COL(3), ROW(19), COL(3), _MENU_DDCCI);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(19), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#else

    COsdDispPenPoint(ROW(5), COL(3), ROW(17), COL(3), _MENU_FACTORY_RESET);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#endif // End of #if(_DDCCI_SUPPORT == _ON)

*/


if(ucOsdState ==_MENU_DICOM_SETTING)
{
    if(stConBriData.Dicom==10)
    	{
#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState8==", ucOsdState);

#endif

		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_GAMMA_SETTING);
		COsdFxChange1bitColor(ROW(11), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));//SJP20110625 LONGER BLACK LINE
		COsdFxChange1bitColor(ROW(12), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));//SJP20110625 LONGER BLACK LINE
		stConBriData.Gamma=1;
		Adjust_LUTtable(0);
		//stSystemData.BackLight=tOSD_DICOMlumi[3] ;//GAMMA USE DICOM500 LUMI sjp20110615
		COsdRightSubBrightness();		

		
	}
    else if (stConBriData.Dicom<10)
    	{
 #if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("stConBriData.Dicom6==", stConBriData.Dicom);
#endif
   	
    	       stConBriData.Dicom++;

		COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_DICOM_SETTING);
		COsdFxChange1bitColor(ROW(1+stConBriData.Dicom-1), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));//SJP20110625 LONGER BLACK LINE
		COsdFxChange1bitColor(ROW(1+stConBriData.Dicom), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));//SJP20110625 LONGER BLACK LINE
	
	if((stConBriData.Dicom>0)&&(stConBriData.Dicom<=7))
	{  
	Adjust_LUTtable(stConBriData.Dicom+3);//DICOM700tble sjp20110615
	if(stSystemData.BackLight>300)//sjp20110927
		stSystemData.BackLight = stSystemData.BackLight-200;//sjp20110923 for pwm value
	else 
		stSystemData.BackLight = stSystemData.BackLight /2;
	}
	else if((stConBriData.Dicom>7)&&(stConBriData.Dicom<=10))
		{
		Adjust_LUTtable(stConBriData.Dicom+3);//DSA DSI CTMRITABLE sjp20110615
		stSystemData.BackLight=tOSD_DICOMlumi[stConBriData.Dicom] ;
		}

		COsdRightSubBrightness();

		}
}
/*
else if(ucOsdState ==_MENU_SIGNAL_SWITCH)
{
    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState10==", ucOsdState);

#endif


		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_AUTO_ADJUST_SETTING);
		COsdFxChange1bitColor(ROW(9), COL(1), WIDTH(10), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(10), COL(1), WIDTH(10), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));

    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState11==", ucOsdState);

#endif

		
}

else if(ucOsdState ==_MENU_AUTO_ADJUST_SETTING)
{


    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState12==", ucOsdState);

#endif

		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3),_MENU_DICOM_SETTING);
		COsdFxChange1bitColor(ROW(10), COL(1), WIDTH(10), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(1), COL(1), WIDTH(10), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		stConBriData.Dicom=0;
	       Adjust_LUTtable(3+stConBriData.Dicom);
		stSystemData.BackLight =tOSD_DICOMlumi[stConBriData.Dicom] ;
	//	CAdjustBrightness( stConBriData.DicomLumi);
		COsdRightSubBrightness();
    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState13==", ucOsdState);

#endif

		

}

*/

	ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;//zp fpr data save


}

void COsdExitDicomSetting(void)
{
    GCMode = 0;//EXIT Factory Mode sjp20110625
    COsdFxDisableOsd();
    COsdDispPenPoint(ROW(19), COL(3), ROW(5), COL(3), _MENU_NONE);
    COsdFxChange1bitColor(ROW(19), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
	ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;//zp for data save
}

//----------------------------------------------------------------------------------------------------
// OSD "ImageSetting" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuGammaSetting(void)
{
	ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;
/*	
    ucOsdState = _MENU_SUB_GAMMA;
    COsdFxDrawWindow(XSTART(80), YSTART(126), XEND(460), YEND(144), tOSD_WINDOW1_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_GRAY), tOSD_WINDOW1_STYLE);
    */
}

void COsdLeftGammaSetting(void)
{
/*
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_BRIGHTNESS_SETTING);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    */
	 
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("stConBriData.Gamma_left", stConBriData.Gamma);
#endif
    if(stConBriData.Gamma==1)
    	{

		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_DICOM_SETTING);
		COsdFxChange1bitColor(ROW(12), COL(1), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));//SJP20110625 LONGER BLACK LINE
		COsdFxChange1bitColor(ROW(11), COL(1), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));//SJP20110625 LONGER BLACK LINE
		stConBriData.Gamma=0;
		stConBriData.Dicom=10;
		Adjust_LUTtable(stConBriData.Dicom+3);//CTMRItable sjp20110615
		//stSystemData.BackLight=tOSD_DICOMlumi[stConBriData.Dicom] ;
		COsdRightSubBrightness();		
	}

    else if ((stConBriData.Gamma>1)&&(stConBriData.Gamma<=3))
    	{
    	       stConBriData.Gamma--;

		COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_GAMMA_SETTING);
		COsdFxChange1bitColor(ROW(11+stConBriData.Gamma+1), COL(1), WIDTH(12), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(11+stConBriData.Gamma), COL(1), WIDTH(12), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		Adjust_LUTtable(stConBriData.Gamma-1);
		//stSystemData.BackLight=tOSD_DICOMlumi[3] ;//GAMMATABLE USE DICOM500 LUMI sjp20110615 no adj sjp20110923
		COsdLeftSubBrightness();

	}
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("stConBriData.Gamma_left2", stConBriData.Gamma);
#endif
	ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;//zp for data save


}

void COsdRightGammaSetting(void)
{
/*
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_DICOM_SETTING);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    */
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("stConBriData.Gamma_right", stConBriData.Gamma);
#endif

    if(stConBriData.Gamma==3)
    	{

		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_SIGNAL_SWITCH);
		COsdFxChange1bitColor(ROW(14), COL(1), WIDTH(12), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(15), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		stConBriData.Gamma=4;
	}

    else if (stConBriData.Gamma<3)
    	{
    	       stConBriData.Gamma++;

		COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_GAMMA_SETTING);
		COsdFxChange1bitColor(ROW(11+stConBriData.Gamma-1), COL(1), WIDTH(12), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(11+stConBriData.Gamma), COL(1), WIDTH(12), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		Adjust_LUTtable(stConBriData.Gamma-1);
		//stSystemData.BackLight=tOSD_DICOMlumi[3] ;//GAMMA USE DICOM500 LUMI sjp20110615 no adj sjp20110923
		COsdLeftSubBrightness();

	}

#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("stConBriData.Gamma_right2", stConBriData.Gamma);
#endif
	ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;//zp for data save 


}

void COsdExitGammaSetting(void)
{
    COsdExitDicomSetting();
}

//----------------------------------------------------------------------------------------------------
// OSD "OsdSetting" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuBrightnessSetting(void)
{
    ucOsdState = _MENU_SUB_BRIGHTNESS;

    COsdFxDrawWindow(XSTART(80), YSTART(162), XEND(460), YEND(180), tOSD_WINDOW1_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_GRAY), tOSD_WINDOW1_STYLE);

}

void COsdLeftBrightnessSetting(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_CONTRAST_SETTING);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightBrightnessSetting(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_GAMMA_SETTING);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitBrightnessSetting(void)
{
    COsdExitDicomSetting();
}

//----------------------------------------------------------------------------------------------------
// OSD "SignalSource" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSignalSource(void)
{

/*
    ucOsdState = _MENU_SIGNAL_SELECT;

    COsdFxDrawWindow(XSTART(80), YSTART(234), XEND(460), YEND(252), tOSD_WINDOW1_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_GRAY), tOSD_WINDOW1_STYLE);
*/


	if(stSystemData.SearchIndex==1)
			COsdMenuSingalDVI();

	else
		{
		#if _DEBUG_MESSAGE_SUPPORT
	//	CDebugMessage("COsdMenuSingalVGA_COsdMenuSignalSource", 0);
		#endif
			COsdMenuSingalVGA();       
		}	




}

void COsdLeftSignalSource(void)
{


    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState4==", ucOsdState);

#endif


		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_GAMMA_SETTING);
		COsdFxChange1bitColor(ROW(15), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(14), COL(1), WIDTH(12), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		stConBriData.Gamma=3;
		Adjust_LUTtable(stConBriData.Gamma-1);
		stSystemData.BackLight=tOSD_DICOMlumi[3];//DICOM500 LUMI sjp20110615
		COsdRightSubBrightness();



//#if(_AUDIO_SUPPORT == _ON)
/*
    COsdDispPenPoint(ROW(13), COL(3), ROW(15), COL(3), _MENU_AUTO_ADJUST_SETTING);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
*/    
/*#else
    COsdDispPenPoint(ROW(11), COL(3), ROW(15), COL(3), _MENU_AUTO_ADJUST);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif*/

ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;
}

void COsdRightSignalSource(void)
{
/*
    if(stConBriData.Dicom<8)
    	{
		COsdDispPenPoint(ROW(13), COL(3), ROW(5), COL(3), _MENU_DICOM_SETTING);
		COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
	}
    else
    	{
		COsdDispPenPoint(ROW(13), COL(3), ROW(11), COL(3), _MENU_CONTRAST_SETTING);
		COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
	}
	*/

    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState10==", ucOsdState);

#endif


		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_AUTO_ADJUST_SETTING);
		COsdFxChange1bitColor(ROW(15), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(16), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));

    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState11==", ucOsdState);

#endif




}

void COsdExitSignalSource(void)
{
    COsdExitDicomSetting();
}


//#if(_AUDIO_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// OSD "Volume" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuContrastSetting(void)
{
    ucOsdState = _MENU_SUB_CONTRAST;

    COsdFxDrawWindow(XSTART(80), YSTART(198), XEND(460), YEND(216), tOSD_WINDOW1_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_GRAY), tOSD_WINDOW1_STYLE);

}

void COsdLeftContrastSetting(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(13), COL(3), _MENU_SIGNAL_SWITCH);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightContrastSetting(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_BRIGHTNESS_SETTING);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitContrastSetting(void)
{
    COsdExitDicomSetting();
}
//#endif // End of #if(_AUDIO_SUPPORT==_ON)

//----------------------------------------------------------------------------------------------------
// OSD "Special" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuAutoAdjust(void)
{
/*
    ucOsdState = _MENU_SUB_AUTO_ADJUST;

    COsdFxDrawWindow(XSTART(80), YSTART(270), XEND(460), YEND(288), tOSD_WINDOW1_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_GRAY), tOSD_WINDOW1_STYLE);
*/

        COsdDispAutoProc();

  ucOsdState = _MENU_NONE;
if(GET_INPUTSOURCE_TYPE() == _SOURCE_DVI)//sjp20110825 for DVI_auto bug
COsdFxDisableOsd();

}

void COsdLeftAutoAdjust(void)
{

    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState6==", ucOsdState);

#endif


		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3),_MENU_SIGNAL_SWITCH);
		COsdFxChange1bitColor(ROW(16), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
		COsdFxChange1bitColor(ROW(15), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));


    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState7==", ucOsdState);

#endif





//#if(_AUDIO_SUPPORT == _ON)
/*
    COsdDispPenPoint(ROW(15), COL(3), ROW(17), COL(3), _MENU_FACTORY_RESET);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    */
/*
#else
    COsdDispPenPoint(ROW(15), COL(3), ROW(11), COL(3), _MENU_SIGNAL_SWITCH);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#endif
*/
}


void COsdRightAutoAdjust(void)
{




    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState12==", ucOsdState);

#endif

		COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3),_MENU_DICOM_SETTING);
		COsdFxChange1bitColor(ROW(16), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));//SJP20110625 LONGER BLACK LINE
		COsdFxChange1bitColor(ROW(1), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));//SJP20110625 LONGER BLACK LINE
		stConBriData.Dicom=0;
		stConBriData.Gamma=0;//zp for gamma index reset
	       Adjust_LUTtable(stConBriData.Dicom+3);//DICOM350_LUTtable sjp20110615
		stSystemData.BackLight=tOSD_DICOMlumi[stConBriData.Dicom] ;
		//CAdjustBrightness( stConBriData.DicomLumi);
		COsdLeftSubBrightness();
    	    	#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("ucOsdState13==", ucOsdState);

#endif

ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;

//#if(_AUDIO_SUPPORT == _ON)
/*
    COsdDispPenPoint(ROW(15), COL(3), ROW(13), COL(3), _MENU_SIGNAL_SWITCH);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
*/
/*
#else
    COsdDispPenPoint(ROW(15), COL(3), ROW(11), COL(3), _MENU_SIGNAL_SWITCH);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#endif
*/
}

void COsdExitAutoAdjust(void)
{
    COsdExitDicomSetting();
}

//----------------------------------------------------------------------------------------------------
// OSD "Factory Mode" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFactory(void)
{
    ucOsdState = _MENU_SUB_FACTORY_RESET;

    COsdFxDrawWindow(XSTART(80), YSTART(306), XEND(460), YEND(324), tOSD_WINDOW1_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_GRAY), tOSD_WINDOW1_STYLE);

}

void COsdLeftFactory(void)
{
#if(_DDCCI_SUPPORT == _ON)
    COsdDispPenPoint(ROW(17), COL(3), ROW(19), COL(3), _MENU_DDCCI);
    COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(19), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#else
    COsdDispPenPoint(ROW(17), COL(3), ROW(5), COL(3), _MENU_DICOM_SETTING);
    COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#endif

}

void COsdRightFactory(void)
{
//#if(_AUDIO_SUPPORT == _ON)
    COsdDispPenPoint(ROW(17), COL(3), ROW(15), COL(3), _MENU_AUTO_ADJUST_SETTING);
    COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
/*
#else
    COsdDispPenPoint(ROW(17), COL(3), ROW(15), COL(3), _MENU_AUTO_ADJUST_SETTING);
    COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#endif
*/
}

void COsdExitFactory(void)
{
    COsdExitDicomSetting();
}

#if(_DDCCI_SUPPORT == _ON)
void COsdMenuDDCCI(void)
{

    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 18, 15);

    COsdFxLoadText(ROW(5), COL(7), stOsdUserData.Language, tOSD_DDCCI_STR);

    COsdDispPenPoint(ROW(5), COL(3), ROW(5), COL(3), _MENU_DDCCIONOFF);

    COsdFxDrawWindow(XSTART(40), YSTART(300), XEND(250), YEND(400), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_BLACK), tOSD_WINDOW2_STYLE);

    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(10), (GET_DDCCI_STATUS()), tOSDDDCCI_ON_OFF_STR);
}

void COsdLeftDDCCI(void)
{

    COsdDispPenPoint(ROW(19), COL(3), ROW(5), COL(3), _MENU_DICOM_SETTING);
    COsdFxChange1bitColor(ROW(19), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightDDCCI(void)
{

    COsdDispPenPoint(ROW(19), COL(3), ROW(17), COL(3), _MENU_FACTORY_RESET);
    COsdFxChange1bitColor(ROW(19), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));


}

void COsdExitDDCCI(void)
{
    COsdExitDicomSetting();
}
#endif
//----------------------------------------------------------------------------------------------------
// OSD "Dicom" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubDicom(void)
{
//stConBriData.Dicom=0;
    ucOsdState = _MENU_DICOM_SETTING;
    ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;
    COsdFxDisableWindow(1);
}


 void COsdLeftSubDicom(void)

 {
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("stConBriData.Dicom", stConBriData.Dicom);
#endif


if(stConBriData.Dicom==8)
	{
		stConBriData.Dicom=0;
		COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(35), HEIGHT(5), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
       }
else
	{
		if(stConBriData.Dicom==7)
			{
			stConBriData.Dicom++;
			COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(35), HEIGHT(5), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
			CAdjustBrightness( stConBriData.Brightness);
			
			}
		else
			stConBriData.Dicom++;
       }
 
    COsdDispDicomContent(ROW(5), COL(14),stConBriData.Dicom);// draw dicom curve
	//COsdFxLoadText(ROW(5),COL(33), stOsdUserData.Language, tOSD_DICOM_STR2[stConBriData.Dicom]);//zhangping 101110

    if(stConBriData.Dicom<8)	
        {
		Adjust_LUTtable(3+stConBriData.Dicom);
		stConBriData.DicomLumi=tOSD_DICOMlumi[stConBriData.Dicom] ;
		CAdjustBrightness( stConBriData.DicomLumi);
	
    	}
}


void COsdRightSubDicom(void)

{
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("stConBriData.Dicom", stConBriData.Dicom);
#endif

	if (stConBriData.Dicom==0)
	      {
			stConBriData.Dicom=8;
			COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(35), HEIGHT(5), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
			CAdjustBrightness( stConBriData.Brightness);
	      }
	else
	   {
	       if(stConBriData.Dicom==8)
	       	{
			stConBriData.Dicom--;
			COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(35), HEIGHT(5), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
	       	}
		 else
			stConBriData.Dicom--;
	    }

	
	COsdDispDicomContent(ROW(5), COL(14),stConBriData.Dicom);// draw dicom curve
//	COsdFxLoadText(ROW(5),COL(33), stOsdUserData.Language, tOSD_DICOM_STR2[stConBriData.Dicom]);//zhangping 101110
	if(stConBriData.Dicom<8)	
	{
		Adjust_LUTtable(3+stConBriData.Dicom);
		stConBriData.DicomLumi=tOSD_DICOMlumi[stConBriData.Dicom] ;
		CAdjustBrightness( stConBriData.DicomLumi);

	}	
}


void COsdExitSubDicom(void)

{

       COsdFxDisableWindow(1);
        ucOsdState = _MENU_DICOM_SETTING;

}





void COsdMenuSubGamma(void)
{
//stConBriData.Gamma=0;
    ucOsdState = _MENU_GAMMA_SETTING;
    ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;
    COsdFxDisableWindow(1);
}


 void COsdLeftSubGamma(void)
{

if(stConBriData.Gamma==2)
	stConBriData.Gamma=0;
else
   stConBriData.Gamma++;
#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage("stConBriData.Gamma",  stConBriData.Gamma);
#endif
 
	COsdDispGammaContent(ROW(7), COL(13),stConBriData.Gamma);// draw dicom curve
	Adjust_LUTtable(stConBriData.Gamma);
	
}

void COsdRightSubGamma(void)
{
	if (stConBriData.Gamma==0)
		stConBriData.Gamma=2;
	else
	       stConBriData.Gamma--;
	COsdDispGammaContent(ROW(7), COL(13),stConBriData.Gamma);// draw dicom curve
	Adjust_LUTtable(stConBriData.Gamma);

}

void COsdExitSubGamma(void)
{

       COsdFxDisableWindow(1);
        ucOsdState = _MENU_GAMMA_SETTING;

}



//----------------------------------------------------------------------------------------------------
// OSD "Contrast" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuContrast(void)
{
    ucOsdState = _MENU_SUB_CONTRAST;
    COsdDispFullSlider(ROW(19), COL(5), 12, stConBriData.Contrast, _CONTRAST_MAX - _CONTRAST_MIN, _CONTRAST_MIN, _CP_WHITE, _CP_WHITE);
}

void COsdLeftContrast(void)
{
   // COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_BRIGHTNESS);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightContrast(void)
{
#if(_DCR_MODE != _DCR_TYPE_OFF)
    COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_COLOR_DCR);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

    COsdDispClearText(ROW(19), COL(9), 16, 1);

    if(GET_DCR_STATUS())
    {
        COsdFxLoadText(ROW(19), COL(9), (_DCR_MODE), tCOLOR_TABLE[5]);
    }
    else
    {
        COsdFxLoadText(ROW(19), COL(9), (_DCR_TYPE_OFF), tCOLOR_TABLE[5]);
    }

#else
    COsdDispPenPoint(ROW(5), COL(3), ROW(11), COL(3), _MENU_COLOR_TEMP);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#endif

}

void COsdExitContrast(void)
{
    COsdFxCloseWindow(WINNO(2));
    COsdDispDrawInitWindow();
    COsdFxLoadIcon(ROW(5), COL(3), tOSD_POINT_ICO);
    ucOsdState = _MENU_DICOM_SETTING;
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

//----------------------------------------------------------------------------------------------------
// OSD "subContrast" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubContrast(void)
{
    ucOsdState = _MENU_CONTRAST_SETTING;
    ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;
    COsdFxDisableWindow(1);
}

void COsdLeftSubContrast(void)
{
    SET_KEYREPEATENABLE();
    stConBriData.Contrast = COsdFxDetOverRange(stConBriData.Contrast, _CONTRAST_MAX, _CONTRAST_MIN, _DET_OVERRANGE_MAX);
    CAdjustContrast(stConBriData.Contrast);
    COsdDispFullSlider(ROW(11), COL(22), 12, stConBriData.Contrast, _CONTRAST_MAX - _CONTRAST_MIN, _CONTRAST_MIN, _CP_WHITE, _CP_WHITE);//draw contrast slide bar

}

void COsdRightSubContrast(void)
{
    SET_KEYREPEATENABLE();
    stConBriData.Contrast = COsdFxDetOverRange(stConBriData.Contrast, _CONTRAST_MAX, _CONTRAST_MIN, _DET_OVERRANGE_MIN);
    CAdjustContrast(stConBriData.Contrast);
    COsdDispFullSlider(ROW(11), COL(22), 12, stConBriData.Contrast, _CONTRAST_MAX - _CONTRAST_MIN, _CONTRAST_MIN, _CP_WHITE, _CP_WHITE);//draw contrast slide bar
}

void COsdExitSubContrast(void)
{
    COsdMenuSubContrast();
}


//----------------------------------------------------------------------------------------------------
// OSD "Brightness" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuBrightness(void)
{
    ucOsdState = _MENU_SUB_BRIGHTNESS;
    COsdDispFullSlider(ROW(19), COL(5), 12, stSystemData.BackLight, 255, 0, _CP_WHITE, _CP_WHITE);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdLeftBrightness(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_COLOR_ADJ);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightBrightness(void)
{
   // COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_CONTRAST);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitBrightness(void)
{
    COsdExitContrast();
}


//----------------------------------------------------------------------------------------------------
// OSD "SubBrightness" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubBrightness(void)
{
    ucOsdState = _MENU_BRIGHTNESS_SETTING;
    ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
    COsdFxDisableWindow(1);
}

void COsdLeftSubBrightness(void)
{
    SET_KEYREPEATENABLE();
 //  stSystemData.BackLight = COsdFxDetOverRange(stSystemData.BackLight, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _DET_OVERRANGE_MAX);
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("stSystemData.BackLight", stSystemData.BackLight);
#endif
/*
switch(stConBriData.Dicom)
{
	case 0:
	stSystemData.BackLight=110;
	break;
	
	case 1:
	stSystemData.BackLight=130;
	break;
	
	case 2:
	stSystemData.BackLight=150;
	break;

	case 3:
	stSystemData.BackLight=170;
	break;

	case 4:
	stSystemData.BackLight=190;
	break;

	case 5:
	stSystemData.BackLight=210;
	break;

	case 6:
	stSystemData.BackLight=230;
	break;

	case 7:
	stSystemData.BackLight=250;
	break;
	
	default:
	break;

}	
*/
#if _DEBUG_MESSAGE_SUPPORT
	//CDebugMessage("stSystemData.BackLight", stSystemData.BackLight);
#endif

    CAdjustBacklight(stSystemData.BackLight);
   // COsdDispFullSlider(ROW(9), COL(22), 12, stSystemData.BackLight, 255, 0, _CP_WHITE, _CP_WHITE);//draw brightness slide bar
}

void COsdRightSubBrightness(void)
{
    SET_KEYREPEATENABLE();
  //  stSystemData.BackLight = COsdFxDetOverRange(stSystemData.BackLight, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _DET_OVERRANGE_MIN);

#if _DEBUG_MESSAGE_SUPPORT
//  CDebugMessage("stSystemData.BackLight", stSystemData.BackLight);
#endif
/*
switch(stConBriData.Dicom)

{
	case 0:
	stSystemData.BackLight=10;
	break;
	
	case 1:
	stSystemData.BackLight=40;
	break;
	
	case 2:
	stSystemData.BackLight=700;
	break;

	case 3:
	stSystemData.BackLight=100;
	break;

	case 4:
	stSystemData.BackLight=130;
	break;

	case 5:
	stSystemData.BackLight=160;
	break;

	case 6:
	stSystemData.BackLight=190;
	break;

	case 7:
	stSystemData.BackLight=230;
	break;
	
	default:
	break;

}
*/
#if _DEBUG_MESSAGE_SUPPORT
	//CDebugMessage("stSystemData.BackLight", stSystemData.BackLight);
#endif
    
   
    CAdjustBacklight(stSystemData.BackLight);
   // COsdDispFullSlider(ROW(9), COL(22), 12, stSystemData.BackLight, 255, 0, _CP_WHITE, _CP_WHITE);//draw brightness slide bar

}

void COsdExitSubBrightness(void)
{
    COsdMenuSubBrightness();
}


void COsdMenuSignalSelect(void)
{
    ucOsdState = _MENU_SIGNAL_SWITCH;
   // ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
    COsdFxDisableWindow(1);
}

void COsdLeftSignalSelect(void)
{
      ucOsdState=_MENU_NONE;
	if(GET_INPUTSOURCE_TYPE()==_SOURCE_VGA)
		{

			COsdDispSignalContent(ROW(13), COL(22),1);// draw SIGNAL TYPE
			COsdMenuSingalDVI();

		}
	else
		{

			COsdDispSignalContent(ROW(13), COL(22),0);// draw SIGNAL TYPE
			COsdMenuSingalVGA();
		}


}

void COsdRightSignalSelect(void)
{
      ucOsdState=_MENU_NONE;

	if(GET_INPUTSOURCE_TYPE()==_SOURCE_VGA)
		{

			COsdDispSignalContent(ROW(13), COL(22),1);// draw SIGNAL TYPE
			COsdMenuSingalDVI();

		}
	else
		{

			COsdDispSignalContent(ROW(13), COL(22),0);// draw SIGNAL TYPE
			COsdMenuSingalVGA();
		}
}

void COsdExitSignalSelect(void)
{
	COsdMenuSignalSelect();
}

void COsdMenuSubAutoAdjust(void)
{
    ucOsdState = _MENU_AUTO_ADJUST_SETTING;
   // ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
    COsdFxDisableWindow(1);
}

void COsdLeftSubAutoAdjust(void)
{

        COsdDisp_YES_NO(ROW(15), COL(22),0);// draw AUTO ADJUST YES/NO
        COsdDispAutoProc();
	//  COsdDisp_YES_NO(ROW(17), COL(22),1);// draw FACTORY RESET YES/NO

}

void COsdRightSubAutoAdjust(void)
{
        COsdDisp_YES_NO(ROW(15), COL(22),0);// draw AUTO ADJUST YES/NO
        COsdDispAutoProc();


}

void COsdExitSubAutoAdjust(void)
{
	COsdMenuSignalSelect();
}


void COsdMenuSubFacReset(void)
{
    ucOsdState = _MENU_SUB_FACTORY_RESET;
   // ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
    COsdFxDisableWindow(1);
}

void COsdLeftSubFacReset(void)
{
	COsdDisp_YES_NO(ROW(17), COL(22),1);// draw FACTORY RESET YES/NO
       COsdFactoryReset();

}

void COsdRightSubFacReset(void)
{
        COsdDisp_YES_NO(ROW(15), COL(22),0);// draw AUTO ADJUST YES/NO
        COsdFactoryReset();


}

void COsdExitSubFacReset(void)
{
	COsdMenuSubFacReset();
}




//----------------------------------------------------------------------------------------------------
// OSD "ColorAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorAdj(void)
{
    if(GET_COLOR_TEMP_TYPE() != 4)
    {
        return;
    }
    else
    {
        COsdFxLoadText(ROW(20), COL(5), stOsdUserData.Language, tOSD_RGB_STR);
        COsdDispArrowPoint(ROW(19), COL(7), ROW(19), COL(7), _MENU_SUB_ADJ_R);
    }
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdLeftColorAdj(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_COLOR_TEMP);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightColorAdj(void)
{
//    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_BRIGHTNESS);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitColorAdj(void)
{
    COsdExitContrast();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubColorAdjR" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubColorAdjR(void)
{
    COsdDispFullSlider(ROW(18), COL(5), 12, stColorTempData.ColorTemp[_RED], 255, 0, _CP_RED, _CP_WHITE);
    ucOsdState = _MENU_ADJ_R;
}

void COsdLeftSubColorAdjR(void)
{
    COsdDispArrowPoint(ROW(19), COL(7), ROW(19), COL(11), _MENU_SUB_ADJ_G);
}

void COsdRightSubColorAdjR(void)
{
    COsdDispArrowPoint(ROW(19), COL(7), ROW(19), COL(15), _MENU_SUB_ADJ_B);
}

void COsdExitSubColorAdjR(void)
{
    ucOsdState = _MENU_COLOR_ADJ;
    COsdDispClearText(ROW(17), COL(5), 18, 5);
}

//----------------------------------------------------------------------------------------------------
// OSD "SubColorAdjG" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubColorAdjG(void)
{
    COsdDispFullSlider(ROW(18), COL(5), 12, stColorTempData.ColorTemp[_GREEN], 255, 0, _CP_GREEN, _CP_WHITE);
    ucOsdState = _MENU_ADJ_G;
}

void COsdLeftSubColorAdjG(void)
{
    COsdDispArrowPoint(ROW(19), COL(11), ROW(19), COL(15), _MENU_SUB_ADJ_B);
}

void COsdRightSubColorAdjG(void)
{
    COsdDispArrowPoint(ROW(19), COL(11), ROW(19), COL(7), _MENU_SUB_ADJ_R);
}

void COsdExitSubColorAdjG(void)
{
    COsdExitSubColorAdjR();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubColorAdjB" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubColorAdjB(void)
{
    COsdDispFullSlider(ROW(18), COL(5), 12, stColorTempData.ColorTemp[_BLUE], 255, 0, _CP_BLUE, _CP_WHITE);
    ucOsdState = _MENU_ADJ_B;
}

void COsdLeftSubColorAdjB(void)
{
    COsdDispArrowPoint(ROW(19), COL(15), ROW(19), COL(7), _MENU_SUB_ADJ_R);
}

void COsdRightSubColorAdjB(void)
{
    COsdDispArrowPoint(ROW(19), COL(15), ROW(19), COL(11), _MENU_SUB_ADJ_G);
}

void COsdExitSubColorAdjB(void)
{
    COsdExitSubColorAdjR();
}

//----------------------------------------------------------------------------------------------------
// OSD "AdjR" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuAdjR(void)
{
    ucOsdState = _MENU_SUB_ADJ_R;
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
    COsdDispClearText(ROW(17), COL(5), 18, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftAdjR(void)
{
    SET_KEYREPEATENABLE();
    stColorTempData.ColorTemp[_RED] = COsdFxDetOverRange(stColorTempData.ColorTemp[_RED], 255, 0, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(18), COL(5), 12, stColorTempData.ColorTemp[_RED], 255, 0, _CP_RED, _CP_WHITE);
    CAdjustContrast(stConBriData.Contrast);
}

void COsdRightAdjR(void)
{
    SET_KEYREPEATENABLE();
    stColorTempData.ColorTemp[_RED] = COsdFxDetOverRange(stColorTempData.ColorTemp[_RED], 255, 0, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(18), COL(5), 12, stColorTempData.ColorTemp[_RED], 255, 0, _CP_RED, _CP_WHITE);
    CAdjustContrast(stConBriData.Contrast);
}

void COsdExitAdjR(void)
{
    COsdMenuAdjR();
}

//----------------------------------------------------------------------------------------------------
// OSD "AdjG" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuAdjG(void)
{
    ucOsdState = _MENU_SUB_ADJ_G;
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
    COsdDispClearText(ROW(17), COL(5), 18, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftAdjG(void)
{
    SET_KEYREPEATENABLE();
    stColorTempData.ColorTemp[_GREEN] = COsdFxDetOverRange(stColorTempData.ColorTemp[_GREEN], 255, 0, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(18), COL(5), 12, stColorTempData.ColorTemp[_GREEN], 255, 0, _CP_GREEN, _CP_WHITE);
    CAdjustContrast(stConBriData.Contrast);
}

void COsdRightAdjG(void)
{
    SET_KEYREPEATENABLE();
    stColorTempData.ColorTemp[_GREEN] = COsdFxDetOverRange(stColorTempData.ColorTemp[_GREEN], 255, 0, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(18), COL(5), 12, stColorTempData.ColorTemp[_GREEN], 255, 0, _CP_GREEN, _CP_WHITE);
    CAdjustContrast(stConBriData.Contrast);
}

void COsdExitAdjG(void)
{
    COsdMenuAdjG();
}

//----------------------------------------------------------------------------------------------------
// OSD "AdjB" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuAdjB(void)
{
    ucOsdState = _MENU_SUB_ADJ_B;
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
    COsdDispClearText(ROW(17), COL(5), 17, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftAdjB(void)
{
    SET_KEYREPEATENABLE();
    stColorTempData.ColorTemp[_BLUE] = COsdFxDetOverRange(stColorTempData.ColorTemp[_BLUE], 255, 0, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(18), COL(5), 12, stColorTempData.ColorTemp[_BLUE], 255, 0, _CP_BLUE, _CP_WHITE);
    CAdjustContrast(stConBriData.Contrast);
}

void COsdRightAdjB(void)
{
    SET_KEYREPEATENABLE();
    stColorTempData.ColorTemp[_BLUE] = COsdFxDetOverRange(stColorTempData.ColorTemp[_BLUE], 255, 0, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(18), COL(5), 12, stColorTempData.ColorTemp[_BLUE], 255, 0, _CP_BLUE, _CP_WHITE);
    CAdjustContrast(stConBriData.Contrast);
}

void COsdExitAdjB(void)
{
    COsdMenuAdjB();
}

//----------------------------------------------------------------------------------------------------
// OSD "ColorTemp" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorTemp(void)
{
    CScalerLoadHardwareVLCFont(tFONT_COLORTEMP, 0x54);

//    CScalerLoadFont(tFONT_COLORTEMP, 0x54, 0x0a, _COMPRESS_FONT);
    COsdFxChange1bitColor(ROW(19), COL(5), WIDTH(14), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxLoadIcon(ROW(19), COL(5), tOSD_COLORTEMP_ITEM_ICO);

    switch(GET_COLOR_TEMP_TYPE())
    {
        case _CT_9300:
            COsdDispArrowPoint(ROW(18), COL(6), ROW(18), COL(6), _MENU_SUB_TEMP_COLOR9300);
            break;

        case _CT_6500:
            COsdDispArrowPoint(ROW(18), COL(9), ROW(18), COL(9), _MENU_SUB_TEMP_COLOR6500);
            break;

        case _CT_5800:
            COsdDispArrowPoint(ROW(18), COL(12), ROW(18), COL(12), _MENU_SUB_TEMP_COLOR5800);
            break;

        case _CT_SRGB:
            COsdDispArrowPoint(ROW(18), COL(15), ROW(18), COL(15), _MENU_SUB_TEMP_SRGB);
            break;

        case _CT_USER:
            COsdDispArrowPoint(ROW(18), COL(18), ROW(18), COL(18), _MENU_SUB_TEMP_USER);
            break;
    }
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));


}
void COsdLeftColorTemp(void)
{
#if(_DCR_MODE != _DCR_TYPE_OFF)
    COsdDispPenPoint(ROW(11), COL(3), ROW(13), COL(3), _MENU_COLOR_DCR);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

    COsdDispClearText(ROW(19), COL(9), 16, 1);

    if(GET_DCR_STATUS())
    {
        COsdFxLoadText(ROW(19), COL(9), (_DCR_MODE), tCOLOR_TABLE[5]);
    }
    else
    {
        COsdFxLoadText(ROW(19), COL(9), (_DCR_TYPE_OFF), tCOLOR_TABLE[5]);
    }

#else
//    COsdDispPenPoint(ROW(11), COL(3), ROW(5), COL(3), _MENU_CONTRAST);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#endif
}

void COsdRightColorTemp(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_COLOR_ADJ);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitColorTemp(void)
{
    COsdExitContrast();
}



//----------------------------------------------------------------------------------------------------
// OSD "Temp 9300" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubTempColor9300(void)
{
    CEepromSaveOsdUserData();

    COsdDispClearText(ROW(18), COL(5), 18, 2);
    CScalerLoadHardwareVLCFont(tFONT_GLOBAL2ND, 0x54);
    ucOsdState = _MENU_COLOR_TEMP;
}

void COsdLeftSubTempColor9300(void)
{
    COsdDispArrowPoint(ROW(18), COL(6), ROW(18), COL(9), _MENU_SUB_TEMP_COLOR6500);
    SET_COLOR_TEMP_TYPE(1);
    CEepromLoadColorTempData();
    CAdjustContrast(stConBriData.Contrast);
}

void COsdRightSubTempColor9300(void)
{
    COsdDispArrowPoint(ROW(18), COL(6), ROW(18), COL(18), _MENU_SUB_TEMP_USER);
    SET_COLOR_TEMP_TYPE(4);
    CEepromLoadColorTempData();
    CAdjustContrast(stConBriData.Contrast);
}

void COsdExitSubTempColor9300(void)
{
    COsdMenuSubTempColor9300();
}

//----------------------------------------------------------------------------------------------------
// OSD "Temp 6500" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubTempColor6500(void)
{
    CEepromSaveOsdUserData();

    COsdDispClearText(ROW(18), COL(5), 18, 2);
    CScalerLoadHardwareVLCFont(tFONT_GLOBAL2ND, 0x54);
    ucOsdState = _MENU_COLOR_TEMP;
}

void COsdLeftSubTempColor6500(void)
{
    COsdDispArrowPoint(ROW(18), COL(9), ROW(18), COL(12), _MENU_SUB_TEMP_COLOR5800);
    SET_COLOR_TEMP_TYPE(2);
    CEepromLoadColorTempData();
    CAdjustContrast(stConBriData.Contrast);
}

void COsdRightSubTempColor6500(void)
{
    COsdDispArrowPoint(ROW(18), COL(9), ROW(18), COL(6), _MENU_SUB_TEMP_COLOR9300);
    SET_COLOR_TEMP_TYPE(0);
    CEepromLoadColorTempData();
    CAdjustContrast(stConBriData.Contrast);
}

void COsdExitSubTempColor6500(void)
{
    COsdMenuSubTempColor6500();
}

//----------------------------------------------------------------------------------------------------
// OSD "Temp 5800" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubTempColor5800(void)
{
    CEepromSaveOsdUserData();

    COsdDispClearText(ROW(18), COL(5), 18, 2);
    CScalerLoadHardwareVLCFont(tFONT_GLOBAL2ND, 0x54);
    ucOsdState = _MENU_COLOR_TEMP;
}

void COsdLeftSubTempColor5800(void)
{
    COsdDispArrowPoint(ROW(18), COL(12), ROW(18), COL(15), _MENU_SUB_TEMP_SRGB);
    SET_COLOR_TEMP_TYPE(3);
    CEepromLoadColorTempData();
    CAdjustContrast(stConBriData.Contrast);
}

void COsdRightSubTempColor5800(void)
{
    COsdDispArrowPoint(ROW(18), COL(12), ROW(18), COL(9), _MENU_SUB_TEMP_COLOR6500);
    SET_COLOR_TEMP_TYPE(1);
    CEepromLoadColorTempData();
    CAdjustContrast(stConBriData.Contrast);
}

void COsdExitSubTempColor5800(void)
{
    COsdMenuSubTempColor5800();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubTempSrgb" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubTempSrgb(void)
{
    CEepromSaveOsdUserData();

    COsdDispClearText(ROW(18), COL(5), 17, 2);
    CScalerLoadHardwareVLCFont(tFONT_GLOBAL2ND, 0x54);
    ucOsdState = _MENU_COLOR_TEMP;
}

void COsdLeftSubTempSrgb(void)
{
    COsdDispArrowPoint(ROW(18), COL(15), ROW(18), COL(18), _MENU_SUB_TEMP_USER);
    SET_COLOR_TEMP_TYPE(4);
    CEepromLoadColorTempData();
    CAdjustContrast(stConBriData.Contrast);
}

void COsdRightSubTempSrgb(void)
{
    COsdDispArrowPoint(ROW(18), COL(15), ROW(18), COL(12), _MENU_SUB_TEMP_COLOR5800);
    SET_COLOR_TEMP_TYPE(2);
    CEepromLoadColorTempData();
    CAdjustContrast(stConBriData.Contrast);
}

void COsdExitSubTempSrgb(void)
{
    COsdMenuSubTempSrgb();
}
//----------------------------------------------------------------------------------------------------
// OSD "SubTempUser" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubTempUser(void)
{
    CEepromSaveOsdUserData();

    COsdDispClearText(ROW(18), COL(5), 17, 2);
    CScalerLoadHardwareVLCFont(tFONT_GLOBAL2ND, 0x54);
    ucOsdState = _MENU_COLOR_TEMP;
}

void COsdLeftSubTempUser(void)
{
    COsdDispArrowPoint(ROW(18), COL(18), ROW(18), COL(6), _MENU_SUB_TEMP_COLOR9300);
    SET_COLOR_TEMP_TYPE(0);
    CEepromLoadColorTempData();
    CAdjustContrast(stConBriData.Contrast);
}

void COsdRightSubTempUser(void)
{
    COsdDispArrowPoint(ROW(18), COL(18), ROW(18), COL(15), _MENU_SUB_TEMP_SRGB);
    SET_COLOR_TEMP_TYPE(3);
    CEepromLoadColorTempData();
    CAdjustContrast(stConBriData.Contrast);
}

void COsdExitSubTempUser(void)
{
    COsdMenuSubTempUser();
}


#if(_DCR_MODE != _DCR_TYPE_OFF)
//----------------------------------------------------------------------------------------------------
// OSD "ColorDCR" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorDCR(void)
{
    COsdDispClearText(ROW(19), COL(9), 16, 1);

    if(GET_DCR_STATUS())
    {
        CLR_DCR_STATUS();

#if((_DCR_MODE == _DCR_TYPE_1) || (_DCR_MODE == _DCR_TYPE_2))
        CScalerPageSelect(_PAGE7);
        CScalerSetByte(_P7_DCC_CTRL0_C7, 0x00);
#endif

        COsdFxLoadText(ROW(19), COL(9), (_DCR_TYPE_OFF), tCOLOR_TABLE[5]);
    }
    else
    {
        SET_DCR_STATUS();
        COsdFxLoadText(ROW(19), COL(9), (_DCR_MODE), tCOLOR_TABLE[5]);
    }
}

void COsdLeftColorDCR(void)
{
    COsdDispPenPoint(ROW(13), COL(3), ROW(5), COL(3), _MENU_CONTRAST);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

    COsdDispClearText(ROW(19), COL(9), 16, 1);
}

void COsdRightColorDCR(void)
{
    COsdDispPenPoint(ROW(13), COL(3), ROW(11), COL(3), _MENU_COLOR_TEMP);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

    COsdDispClearText(ROW(19), COL(9), 16, 1);
}

void COsdExitColorDCR(void)
{
    COsdExitContrast();
}

#endif // End of #if(_DCR_MODE != _DCR_TYPE_OFF)

//----------------------------------------------------------------------------------------------------
// OSD "Clock" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuClock(void)
{
    // V015 VGA Patch Note (6) Modify 20100612 Start
    // Patch Reason : Open Image Setting for YPbPr.
    /*
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
    */
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
    // V015 VGA Patch Note (6) Modify 20100612 End
    {
        ucOsdState = _MENU_SUB_CLOCK;
        COsdDispFullSlider(ROW(19), COL(5), 12, stModeUserData.Clock, COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MAX) - COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN), COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN), _CP_WHITE, _CP_WHITE);
    }
}

void COsdLeftClock(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_PHASE);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightClock(void)
{
#if(_OD_SUPPORT == _ON)
    COsdDispPenPoint(ROW(5), COL(3), ROW(15), COL(3), _MENU_OD);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#else
    COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_VPOSITION);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#endif
}

void COsdExitClock(void)
{
    COsdFxCloseWindow(WINNO(2));
    COsdDispDrawInitWindow();
    COsdFxLoadIcon(ROW(7), COL(3), tOSD_POINT_ICO);
    ucOsdState = _MENU_GAMMA_SETTING;

    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}



//----------------------------------------------------------------------------------------------------
// OSD "SubClock" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubClock(void)
{
    ucOsdState = _MENU_CLOCK;
    ucOsdEventMsg = _SAVE_EE_MODEUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 12, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftSubClock(void)
{
    SET_KEYREPEATENABLE();
    stModeUserData.Clock = COsdFxDetOverRange(stModeUserData.Clock, COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MAX), COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN), _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stModeUserData.Clock, COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MAX) - COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN), COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN), _CP_WHITE, _CP_WHITE);
#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

    CAdjustAdcClock(stModeUserData.Clock);

#else
    No Setting !!
#endif

    CTimerDelayXms(10);
}

void COsdRightSubClock(void)
{
    SET_KEYREPEATENABLE();
    stModeUserData.Clock = COsdFxDetOverRange(stModeUserData.Clock, COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MAX), COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN), _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stModeUserData.Clock, COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MAX) - COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN), COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN), _CP_WHITE, _CP_WHITE);

#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

    CAdjustAdcClock(stModeUserData.Clock);

#else
    No Setting !!
#endif

    CTimerDelayXms(10);
}

void COsdExitSubClock(void)
{
    COsdMenuSubClock();
}

//----------------------------------------------------------------------------------------------------
// OSD "Phase" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuPhase(void)
{
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_DVI) || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
    || (GET_INPUTSOURCE_TYPE() == _SOURCE_DP))
    {
    }
    else

    {
        ucOsdState = _MENU_SUB_PHASE;
        COsdDispFullSlider(ROW(19), COL(5), 12, stModeUserData.Phase, 63, 0, _CP_WHITE, _CP_WHITE);
        COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    }
}

void COsdLeftPhase(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_SHARPNESS);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightPhase(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_CLOCK);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitPhase(void)
{
    COsdExitClock();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubPhase" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubPhase(void)
{
    ucOsdState = _MENU_PHASE;
    ucOsdEventMsg = _SAVE_EE_MODEUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 12, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftSubPhase(void)
{
    SET_KEYREPEATENABLE();
    stModeUserData.Phase = COsdFxDetOverRange(stModeUserData.Phase, 63, 0, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stModeUserData.Phase, 63, 0, _CP_WHITE, _CP_WHITE);
    CAdjustPhase(stModeUserData.Phase);
}

void COsdRightSubPhase(void)
{
    SET_KEYREPEATENABLE();
    stModeUserData.Phase = COsdFxDetOverRange(stModeUserData.Phase, 63, 0, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stModeUserData.Phase, 63, 0, _CP_WHITE, _CP_WHITE);
    CAdjustPhase(stModeUserData.Phase);
}

void COsdExitSubPhase(void)
{
    COsdMenuSubPhase();
}

//----------------------------------------------------------------------------------------------------
// OSD "Sharpness" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSharpness(void)
{
    COsdFxLoadText(ROW(19), COL(6), 0, tOSD_SHARPNESSITEM_STR);

    ucOsdState = stOsdUserData.Sharpness + _MENU_SUB_SHARPNESS0;
    COsdFxHLine(ROW(18), COL(stOsdUserData.Sharpness * 2 + 7), LENGTH(1), 0x4a, _WRITE_BYTE1);

    COsdFxChange1bitColor(ROW(18), COL(7), WIDTH(9), HEIGHT(1), FGCOLOR(_CP_RED), BGCOLOR(_CP_BLACK));
    COsdFxHLine(ROW(19), COL(7), LENGTH(10), 0x8c, _WRITE_BYTE0);
    COsdDispClearText(ROW(19), COL(16), 2, 1);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdLeftSharpness(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_HPOSITION);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightSharpness(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_PHASE);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitSharpness(void)
{
    COsdExitClock();
}


//----------------------------------------------------------------------------------------------------
// OSD "SubSharpness1" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubSharpness0(void)
{
    COsdDispClearText(ROW(18), COL(7), 9, 2);
    ucOsdState = _MENU_SHARPNESS;
}

void COsdLeftSubSharpness0(void)
{
    COsdDispArrowPoint(ROW(18), COL(7), ROW(18), COL(9), _MENU_SUB_SHARPNESS1);

    stOsdUserData.Sharpness = 1;
    CAdjustSharpness(stOsdUserData.Sharpness);

}

void COsdRightSubSharpness0(void)
{

}

void COsdExitSubSharpness0(void)
{
    COsdMenuSubSharpness0();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubSharpness2" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubSharpness1(void)
{
    COsdMenuSubSharpness0();
}

void COsdLeftSubSharpness1(void)
{
    COsdDispArrowPoint(ROW(18), COL(9), ROW(18), COL(11), _MENU_SUB_SHARPNESS2);

    stOsdUserData.Sharpness = 2;
    CAdjustSharpness(stOsdUserData.Sharpness);

}

void COsdRightSubSharpness1(void)
{
    COsdDispArrowPoint(ROW(18), COL(9), ROW(18), COL(7), _MENU_SUB_SHARPNESS0);

    stOsdUserData.Sharpness = 0;
    CAdjustSharpness(stOsdUserData.Sharpness);

}

void COsdExitSubSharpness1(void)
{
    COsdMenuSubSharpness0();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubSharpness3" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubSharpness2(void)
{
    COsdMenuSubSharpness0();
}

void COsdLeftSubSharpness2(void)
{
    COsdDispArrowPoint(ROW(18), COL(11), ROW(18), COL(13), _MENU_SUB_SHARPNESS3);

    stOsdUserData.Sharpness = 3;
    CAdjustSharpness(stOsdUserData.Sharpness);
}

void COsdRightSubSharpness2(void)
{
    COsdDispArrowPoint(ROW(18), COL(11), ROW(18), COL(9), _MENU_SUB_SHARPNESS1);

    stOsdUserData.Sharpness = 1;
    CAdjustSharpness(stOsdUserData.Sharpness);
}

void COsdExitSubSharpness2(void)
{
    COsdMenuSubSharpness0();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubSharpness4" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubSharpness3(void)
{
    COsdMenuSubSharpness0();
}

void COsdLeftSubSharpness3(void)
{
    COsdDispArrowPoint(ROW(18), COL(13), ROW(18), COL(15), _MENU_SUB_SHARPNESS4);

    stOsdUserData.Sharpness = 4;
    CAdjustSharpness(stOsdUserData.Sharpness);
}

void COsdRightSubSharpness3(void)
{
    COsdDispArrowPoint(ROW(18), COL(13), ROW(18), COL(11), _MENU_SUB_SHARPNESS2);

    stOsdUserData.Sharpness = 2;
    CAdjustSharpness(stOsdUserData.Sharpness);
}

void COsdExitSubSharpness3(void)
{
    COsdMenuSubSharpness0();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubSharpness5" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubSharpness4(void)
{
    COsdMenuSubSharpness0();
}

void COsdLeftSubSharpness4(void)
{

}

void COsdRightSubSharpness4(void)
{
    COsdDispArrowPoint(ROW(18), COL(15), ROW(18), COL(13), _MENU_SUB_SHARPNESS3);

    stOsdUserData.Sharpness = 3;
    CAdjustSharpness(stOsdUserData.Sharpness);
}

void COsdExitSubSharpness4(void)
{
    COsdMenuSubSharpness0();
}

//----------------------------------------------------------------------------------------------------
// OSD "HPosition" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuHPosition(void)
{
    // V015 VGA Patch Note (6) Modify 20100612 Start
    // Patch Reason : Open Image Setting for YPbPr.
    /*
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
    */
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
    // V015 VGA Patch Note (6) Modify 20100612 End
    {
        ucOsdState = _MENU_SUB_H_POS;

        COsdDispFullSlider(ROW(19), COL(5), 12, stModeUserData.HPosition, _HPOSITION_BIAS * 2, (stModeUserCenterData.CenterHPos - _HPOSITION_BIAS), _CP_WHITE, _CP_WHITE);
    }
}

void COsdLeftHPosition(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(13), COL(3), _MENU_VPOSITION);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightHPosition(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_SHARPNESS);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitHPosition(void)
{
    COsdExitClock();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubHPosition" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubHPosition(void)
{
    CLR_KEYREPEATENABLE();
    ucOsdEventMsg = _SAVE_EE_MODEUSERDATA_MSG;
    ucOsdState = _MENU_HPOSITION;
    COsdDispClearText(ROW(18), COL(5), 12, 2);
}

void COsdLeftSubHPosition(void)
{
    SET_KEYREPEATENABLE();

    stModeUserData.HPosition = COsdFxDetOverRange(stModeUserData.HPosition, COsdFxGetHPositionRange(_GET_HPOSITIONRANGE_MAX), COsdFxGetHPositionRange(_GET_HPOSITIONRANGE_MIN), _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stModeUserData.HPosition, _HPOSITION_BIAS * 2, stModeUserCenterData.CenterHPos - _HPOSITION_BIAS, _CP_WHITE, _CP_WHITE);

    CAdjustHPosition();
}

void COsdRightSubHPosition(void)
{
    SET_KEYREPEATENABLE();

    stModeUserData.HPosition = COsdFxDetOverRange(stModeUserData.HPosition, COsdFxGetHPositionRange(_GET_HPOSITIONRANGE_MAX), COsdFxGetHPositionRange(_GET_HPOSITIONRANGE_MIN), _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stModeUserData.HPosition, _HPOSITION_BIAS * 2, stModeUserCenterData.CenterHPos - _HPOSITION_BIAS, _CP_WHITE, _CP_WHITE);

    CAdjustHPosition();
}

void COsdExitSubHPosition(void)
{
    COsdMenuSubHPosition();
}

//----------------------------------------------------------------------------------------------------
// OSD "VPosition" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuVPosition(void)
{
    // V015 VGA Patch Note (6) Modify 20100612 Start
    // Patch Reason : Open Image Setting for YPbPr.
    /*
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
    */
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
    // V015 VGA Patch Note (6) Modify 20100612 End
    {
        ucOsdState = _MENU_SUB_V_POS;
        COsdDispFullSlider(ROW(19), COL(5), 12, stModeUserData.VPosition, _VPOSITION_BIAS * 2, stModeUserCenterData.CenterVPos - _VPOSITION_BIAS, _CP_WHITE, _CP_WHITE);
    }
}

void COsdLeftVPosition(void)
{
#if(_OD_SUPPORT == _ON)
    COsdDispPenPoint(ROW(13), COL(3), ROW(15), COL(3), _MENU_OD);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#else
    COsdDispPenPoint(ROW(13), COL(3), ROW(5), COL(3), _MENU_CLOCK);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#endif
}

void COsdRightVPosition(void)
{
    COsdDispPenPoint(ROW(13), COL(3), ROW(11), COL(3), _MENU_HPOSITION);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitVPosition(void)
{
    COsdExitClock();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubVPosition" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubVPosition(void)
{
    CLR_KEYREPEATENABLE();
    ucOsdEventMsg = _SAVE_EE_MODEUSERDATA_MSG;
    ucOsdState = _MENU_VPOSITION;
    COsdDispClearText(ROW(18), COL(5), 12, 2);
}

void COsdLeftSubVPosition(void)
{
    SET_KEYREPEATENABLE();
    stModeUserData.VPosition = COsdFxDetOverRange(stModeUserData.VPosition, COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MAX), COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MIN), _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stModeUserData.VPosition, _VPOSITION_BIAS * 2, stModeUserCenterData.CenterVPos - _VPOSITION_BIAS, _CP_WHITE, _CP_WHITE);
    CAdjustVPosition();
}

void COsdRightSubVPosition(void)
{
    SET_KEYREPEATENABLE();
    stModeUserData.VPosition = COsdFxDetOverRange(stModeUserData.VPosition, COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MAX), COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MIN), _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stModeUserData.VPosition, _VPOSITION_BIAS * 2, stModeUserCenterData.CenterVPos - _VPOSITION_BIAS, _CP_WHITE, _CP_WHITE);
    CAdjustVPosition();
}

void COsdExitSubVPosition(void)
{
    COsdMenuSubVPosition();
}


#if(_OD_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// OSD "Gamma" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuOD(void)
{
    ucOsdState = _MENU_SUB_OD;

    COsdDispFullSlider(ROW(19), COL(5), 12, stSystemData.ODTable, 100, 0, _CP_WHITE, _CP_WHITE);
}

void COsdLeftOD(void)
{
    COsdDispPenPoint(ROW(15), COL(3), ROW(5), COL(3), _MENU_CLOCK);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightOD(void)
{
    COsdDispPenPoint(ROW(15), COL(3), ROW(13), COL(3), _MENU_VPOSITION);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitOD(void)
{
    COsdExitClock();
}

//----------------------------------------------------------------------------------------------------
// OSD "Gamma" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubOD(void)
{
    CLR_KEYREPEATENABLE();

    ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;

    ucOsdState = _MENU_OD;
    COsdDispClearText(ROW(18), COL(5), 12, 2);
}

void COsdLeftSubOD(void)
{
    SET_KEYREPEATENABLE();
    stSystemData.ODTable = COsdFxDetOverRange(stSystemData.ODTable, 100, 0, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stSystemData.ODTable, 100, 0, _CP_WHITE, _CP_WHITE);
    CAdjustODeltaGain(stSystemData.ODTable);
}

void COsdRightSubOD(void)
{
    SET_KEYREPEATENABLE();
    stSystemData.ODTable = COsdFxDetOverRange(stSystemData.ODTable, 100, 0, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stSystemData.ODTable, 100, 0, _CP_WHITE, _CP_WHITE);
    CAdjustODeltaGain(stSystemData.ODTable);
}

void COsdExitSubOD(void)
{
    COsdMenuSubOD();
}

#endif // End of #if(_OD_SUPPORT == _ON)


//----------------------------------------------------------------------------------------------------
// OSD "OsdHPos" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuOsdHPos(void)
{
    ucOsdState = _MENU_SUB_OSD_H_POS;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.OsdHPos, 200, 0, _CP_WHITE, _CP_WHITE);
}

void COsdLeftOsdHPos(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_OSD_V_POS);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightOsdHPos(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(11), COL(3), _MENU_OSD_LANGUAGE);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitOsdHPos(void)
{
    COsdFxCloseWindow(WINNO(2));
    COsdDispDrawInitWindow();
    COsdFxLoadIcon(ROW(9), COL(3), tOSD_POINT_ICO);
    ucOsdState = _MENU_BRIGHTNESS_SETTING;

    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

//----------------------------------------------------------------------------------------------------
// OSD "SubOsdHPos" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubOsdHPos(void)
{
    CLR_KEYREPEATENABLE();
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    ucOsdState = _MENU_OSD_H_POS;
    COsdDispClearText(ROW(18), COL(5), 12, 2);
}

void COsdLeftSubOsdHPos(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.OsdHPos = COsdFxDetOverRange(stOsdUserData.OsdHPos, 200, 0, _DET_OVERRANGE_MAX);

    // V016 System Patch Note (1) Modify 20100729 Start
    // Patch Reason : Modify OSD Set position and Draw Window Function
    /*
    COsdFxSetPosition(WIDTH(280), WIDTH(400), stOsdUserData.OsdHPos, stOsdUserData.OsdVPos, 0x01);
    */
    COsdFxSetPosition(WIDTH(280), WIDTH(440), stOsdUserData.OsdHPos, stOsdUserData.OsdVPos, 0x01);
    // V016 System Patch Note (1) Modify 20100729 End

    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.OsdHPos, 200, 0, _CP_WHITE, _CP_WHITE);
}

void COsdRightSubOsdHPos(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.OsdHPos = COsdFxDetOverRange(stOsdUserData.OsdHPos, 200, 0, _DET_OVERRANGE_MIN);

    // V016 System Patch Note (1) Modify 20100729 Start
    // Patch Reason : Modify OSD Set position and Draw Window Function
    /*
    COsdFxSetPosition(WIDTH(280), WIDTH(400), stOsdUserData.OsdHPos, stOsdUserData.OsdVPos, 0x01);
    */
    COsdFxSetPosition(WIDTH(280), WIDTH(440), stOsdUserData.OsdHPos, stOsdUserData.OsdVPos, 0x01);
    // V016 System Patch Note (1) Modify 20100729 End

    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.OsdHPos, 200, 0, _CP_WHITE, _CP_WHITE);
}

void COsdExitSubOsdHPos(void)
{
    COsdMenuSubOsdHPos();
}

//----------------------------------------------------------------------------------------------------
// OSD "OsdVPos" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuOsdVPos(void)
{
    ucOsdState = _MENU_SUB_OSD_V_POS;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.OsdVPos, 200, 0, _CP_WHITE, _CP_WHITE);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdLeftOsdVPos(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_OSD_TIME);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightOsdVPos(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_OSD_H_POS);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitOsdVPos(void)
{
    COsdExitOsdHPos();
}


//----------------------------------------------------------------------------------------------------
// OSD "SubOsdVPos" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubOsdVPos(void)
{
    CLR_KEYREPEATENABLE();
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    ucOsdState = _MENU_OSD_V_POS;
    COsdDispClearText(ROW(18), COL(5), 12, 2);
}

void COsdLeftSubOsdVPos(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.OsdVPos = COsdFxDetOverRange(stOsdUserData.OsdVPos, 200, 0, _DET_OVERRANGE_MAX);

    // V016 System Patch Note (1) Modify 20100729 Start
    // Patch Reason : Modify OSD Set position and Draw Window Function
    /*
    COsdFxSetPosition(WIDTH(280), WIDTH(400), stOsdUserData.OsdHPos, stOsdUserData.OsdVPos, 0x01);
    */
    COsdFxSetPosition(WIDTH(280), WIDTH(440), stOsdUserData.OsdHPos, stOsdUserData.OsdVPos, 0x01);
    // V016 System Patch Note (1) Modify 20100729 End

    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.OsdVPos, 200, 0, _CP_WHITE, _CP_WHITE);
}

void COsdRightSubOsdVPos(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.OsdVPos = COsdFxDetOverRange(stOsdUserData.OsdVPos, 200, 0, _DET_OVERRANGE_MIN);

    // V016 System Patch Note (1) Modify 20100729 Start
    // Patch Reason : Modify OSD Set position and Draw Window Function
    /*
    COsdFxSetPosition(WIDTH(280), WIDTH(400), stOsdUserData.OsdHPos, stOsdUserData.OsdVPos, 0x01);
    */
    COsdFxSetPosition(WIDTH(280), WIDTH(440), stOsdUserData.OsdHPos, stOsdUserData.OsdVPos, 0x01);
    // V016 System Patch Note (1) Modify 20100729 End

    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.OsdVPos, 200, 0, _CP_WHITE, _CP_WHITE);
}

void COsdExitSubOsdVPos(void)
{
    COsdMenuSubOsdVPos();
}

//----------------------------------------------------------------------------------------------------
// OSD "OsdTime" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuOsdTime(void)
{
    ucOsdState = _MENU_SUB_OSD_TIME;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.OsdTimeout, 27, 3, _CP_WHITE, _CP_WHITE);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdLeftOsdTime(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_OSD_LANGUAGE);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightOsdTime(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_OSD_V_POS);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitOsdTime(void)
{
    COsdExitOsdHPos();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubOsdTime" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubOsdTime(void)
{
    CLR_KEYREPEATENABLE();
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    ucOsdState = _MENU_OSD_TIME;
    COsdDispClearText(ROW(18), COL(5), 12, 2);
}

void COsdLeftSubOsdTime(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.OsdTimeout = COsdFxDetOverRange(stOsdUserData.OsdTimeout, 30, 3, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.OsdTimeout, 27, 3, _CP_WHITE, _CP_WHITE);
}

void COsdRightSubOsdTime(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.OsdTimeout = COsdFxDetOverRange(stOsdUserData.OsdTimeout, 30, 3, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.OsdTimeout, 27, 3, _CP_WHITE, _CP_WHITE);
}

void COsdExitSubOsdTime(void)
{
    COsdMenuSubOsdTime();
}

//----------------------------------------------------------------------------------------------------
// OSD "Language" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuLanguage(void)
{
    BYTE temp;

    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 18, 15);
    COsdFxCloseWindow(WINNO(2));

    for(temp = 0; temp < 7; temp ++)
    {
        COsdFxLoadText(ROW(5 + temp*2), COL(7), temp, tOSD_LANGUAGE_ITEM_STR);
    }

    switch (stOsdUserData.Language)
    {
        case 0:
            COsdDispPenPoint(ROW(13), COL(3), ROW(5), COL(3), _MENU_SUB_ENG);
            COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

            break;
        case 1:
            COsdDispPenPoint(ROW(13), COL(3), ROW(7), COL(3), _MENU_SUB_FRAN);
            COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
            break;
        case 2:
            COsdDispPenPoint(ROW(13), COL(3), ROW(9), COL(3), _MENU_SUB_DEUT);
            COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
            break;
        case 3:
            COsdDispPenPoint(ROW(13), COL(3), ROW(11), COL(3), _MENU_SUB_ESPA);
            COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
            break;
        case 4:
            COsdDispPenPoint(ROW(13), COL(3), ROW(13), COL(3), _MENU_SUB_CHI);
            COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
            break;
        case 5:
            COsdDispPenPoint(ROW(13), COL(3), ROW(15), COL(3), _MENU_SUB_SIMPLE_CHI);
            COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
            break;
        case 6:
            COsdDispPenPoint(ROW(13), COL(3), ROW(17), COL(3), _MENU_SUB_JAP);
            COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
            break;
    }
}

void COsdLeftLanguage(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(5), COL(3), _MENU_OSD_H_POS);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightLanguage(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_OSD_TIME);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitLanguage(void)
{
    COsdExitOsdHPos();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubEng" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubEng(void)
{
    stOsdUserData.Language = _ENGLISH;
    COsdDispLanguageBack();
}

void COsdLeftSubEng(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_SUB_FRAN);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightSubEng(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(17), COL(3), _MENU_SUB_JAP);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitSubEng(void)
{
    COsdDispLanguageBack();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubFran" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubFran(void)
{
    stOsdUserData.Language = _FRENCH;
    COsdDispLanguageBack();
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdLeftSubFran(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_SUB_DEUT);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightSubFran(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_SUB_ENG);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitSubFran(void)
{
    COsdExitSubEng();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubDeut" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubDeut(void)
{
    stOsdUserData.Language = _GERMAN;
    COsdDispLanguageBack();
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdLeftSubDeut(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_SUB_ESPA);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightSubDeut(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_SUB_FRAN);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitSubDeut(void)
{
    COsdExitSubEng();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubEspa" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubEspa(void)
{
    stOsdUserData.Language = _SPANISH;
    COsdDispLanguageBack();
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdLeftSubEspa(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(13), COL(3), _MENU_SUB_CHI);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightSubEspa(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_SUB_DEUT);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitSubEspa(void)
{
    COsdExitSubEng();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubChi" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubChi(void)
{
    CScalerLoadHardwareVLCFont(tFONT_CHI, 0x60);
    stOsdUserData.Language = _CHINESE_T;
    COsdDispLanguageBack();
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdLeftSubChi(void)
{
    COsdDispPenPoint(ROW(13), COL(3), ROW(15), COL(3), _MENU_SUB_SIMPLE_CHI);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightSubChi(void)
{
    COsdDispPenPoint(ROW(13), COL(3), ROW(11), COL(3), _MENU_SUB_ESPA);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitSubChi(void)
{
    COsdExitSubEng();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubSimpleChi" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubSimpleChi(void)
{
    CScalerLoadHardwareVLCFont(tFONT_CHI, 0x60);
    stOsdUserData.Language = _CHINESE_S;
    COsdDispLanguageBack();
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdLeftSubSimpleChi(void)
{
    COsdDispPenPoint(ROW(15), COL(3), ROW(17), COL(3), _MENU_SUB_JAP);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightSubSimpleChi(void)
{
    COsdDispPenPoint(ROW(15), COL(3), ROW(13), COL(3), _MENU_SUB_CHI);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitSubSimpleChi(void)
{
    COsdExitSubEng();
}

//----------------------------------------------------------------------------------------------------
// OSD "SubJap" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubJap(void)
{
    CScalerLoadHardwareVLCFont(tFONT_JAP, 0x60);
    stOsdUserData.Language = _JAPAN;
    COsdDispLanguageBack();
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdLeftSubJap(void)
{
    COsdDispPenPoint(ROW(17), COL(3), ROW(5), COL(3), _MENU_SUB_ENG);
    COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightSubJap(void)
{
    COsdDispPenPoint(ROW(17), COL(3), ROW(15), COL(3), _MENU_SUB_SIMPLE_CHI);
    COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdExitSubJap(void)
{
    COsdExitSubEng();
}

//----------------------------------------------------------------------------------------------------
// Singal Type "VGA" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSingalVGA(void)
{
#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    CLR_SOURCE_SEARCH_AUTO();
    stSystemData.SearchIndex = 1;   //VGA
#endif

#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)
    CSourceSwitchInputPort(_A0_INPUT_PORT);
    ucOsdEventMsg = _CHANGE_SOURCE_MSG;
#else
    No Setting !!
#endif
}

void COsdLeftSingalVGA(void)
{
#if((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_DVI_I_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_I_PORT))
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_SIGNAL_DVI);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#elif((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT))
    COsdDispPenPoint(ROW(5), COL(3), ROW(9), COL(3), _MENU_SIGNAL_HDMI);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#elif(_DP_SUPPORT == _ON)
    COsdDispPenPoint(ROW(5), COL(3), ROW(11), COL(3), _MENU_SIGNAL_DISPLAYPORT);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif
}

void COsdRightSingalVGA(void)
{
#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)

    COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_SIGNAL_AUTOSEARCH);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#else

#if(_DP_SUPPORT == _ON)
    COsdDispPenPoint(ROW(5), COL(3), ROW(11), COL(3), _MENU_SIGNAL_DISPLAYPORT);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#elif((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT))
    COsdDispPenPoint(ROW(5), COL(3), ROW(9), COL(3), _MENU_SIGNAL_HDMI);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#elif((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_DVI_I_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_I_PORT))
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_SIGNAL_DVI);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif

#endif

}

void COsdExitSingalVGA(void)
{
#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
    if(GET_SOURCE_OSD_STATUS())
    {
        COsdExitDicomSetting();
        CLR_SOURCE_OSD_STATUS();
    }
    else
#endif
    {
        COsdFxCloseWindow(WINNO(2));
        COsdDispDrawInitWindow();
        COsdFxLoadIcon(ROW(11), COL(3), tOSD_POINT_ICO);
        ucOsdState = _MENU_SIGNAL_SWITCH;
        COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    }
}

//----------------------------------------------------------------------------------------------------
// Singal Type "DVI" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSingalDVI(void)
{
#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    CLR_SOURCE_SEARCH_AUTO();
    stSystemData.SearchIndex = 0;   //DVI
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
    CSourceSwitchInputPort(_D0_INPUT_PORT);

#elif(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
    CSourceSwitchInputPort(_D1_INPUT_PORT);
#endif

    ucOsdEventMsg = _CHANGE_SOURCE_MSG;

#else
    No Setting !!
#endif
}

void COsdLeftSingalDVI(void)
{
#if(_HDMI_SUPPORT == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_SIGNAL_HDMI);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#elif(_DP_SUPPORT == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(11), COL(3), _MENU_SIGNAL_DISPLAYPORT);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#else


#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(13), COL(3), _MENU_SIGNAL_AUTOSEARCH);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#else
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_SIGNAL_VGA);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif

#endif
}

void COsdRightSingalDVI(void)
{
//    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_SIGNAL_VGA);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitSingalDVI(void)
{
#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
    if(GET_SOURCE_OSD_STATUS())
    {
        COsdExitDicomSetting();
        CLR_SOURCE_OSD_STATUS();
    }
    else
#endif
    {
        COsdExitSingalVGA();
    }
}

//----------------------------------------------------------------------------------------------------
// Singal Type "HDMI" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSingalHDMI(void)
{
#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    CLR_SOURCE_SEARCH_AUTO();
    stSystemData.SearchIndex = 0;   //HDMI
#endif


#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
    CSourceSwitchInputPort(_D0_INPUT_PORT);

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
    CSourceSwitchInputPort(_D1_INPUT_PORT);
#endif

    ucOsdEventMsg = _CHANGE_SOURCE_MSG;
//    CHdmiHotPlugProc(20);
#else
    No Setting !!
#endif
}

void COsdLeftSingalHDMI(void)
{
#if(_DP_SUPPORT != _ON)

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    COsdDispPenPoint(ROW(9), COL(3), ROW(13), COL(3), _MENU_SIGNAL_AUTOSEARCH);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#else
    COsdDispPenPoint(ROW(9), COL(3), ROW(5), COL(3), _MENU_SIGNAL_VGA);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif


#else
    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_SIGNAL_DISPLAYPORT);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif
}

void COsdRightSingalHDMI(void)
{
#if((_D0_INPUT_PORT_TYPE != _D0_DVI_PORT) && (_D0_INPUT_PORT_TYPE != _D0_DVI_I_PORT) && (_D1_INPUT_PORT_TYPE != _D1_DVI_PORT) && (_D1_INPUT_PORT_TYPE != _D1_DVI_I_PORT))
//    COsdDispPenPoint(ROW(9), COL(3), ROW(5), COL(3), _MENU_SIGNAL_VGA);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#else
    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_SIGNAL_DVI);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif
}

void COsdExitSingalHDMI(void)
{
#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
    if(GET_SOURCE_OSD_STATUS())
    {
        COsdExitDicomSetting();
        CLR_SOURCE_OSD_STATUS();
    }
    else
#endif
    {
        COsdExitSingalVGA();
    }
}

//----------------------------------------------------------------------------------------------------
// Singal Type "DisplayPort" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSingalDisplayPort(void)
{
#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    CLR_SOURCE_SEARCH_AUTO();
    stSystemData.SearchIndex = 2;   //DP
#endif


#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    CSourceSwitchInputPort(_D0_INPUT_PORT);

    SET_INPUT_SOURCE_SEARCH();

#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    CSourceSwitchInputPort(_D1_INPUT_PORT);

#endif

    ucOsdEventMsg = _CHANGE_SOURCE_MSG;
    //CDptHotplugProcess();//eagleeyes-20080317
#else
    No Setting !!
#endif

}

void COsdLeftSingalDisplayPort(void)
{

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    COsdDispPenPoint(ROW(11), COL(3), ROW(13), COL(3), _MENU_SIGNAL_AUTOSEARCH);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#else


    COsdDispPenPoint(ROW(11), COL(3), ROW(5), COL(3), _MENU_SIGNAL_VGA);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#endif

}

void COsdRightSingalDisplayPort(void)
{
#if(_HDMI_SUPPORT == _ON)
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_SIGNAL_HDMI);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#elif(_TMDS_SUPPORT == _ON)
    COsdDispPenPoint(ROW(11), COL(3), ROW(7), COL(3), _MENU_SIGNAL_DVI);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#else
    COsdDispPenPoint(ROW(11), COL(3), ROW(5), COL(3), _MENU_SIGNAL_VGA);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#endif // End of #if(_HDMI_SUPPORT == _ON)

}

void COsdExitSingalDisplayPort(void)
{
#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
    if(GET_SOURCE_OSD_STATUS())
    {
        COsdExitDicomSetting();
        CLR_SOURCE_OSD_STATUS();
    }
    else
#endif
    {
        COsdExitSingalVGA();
    }
}

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
//----------------------------------------------------------------------------------------------------
// Singal Type "DisplayPort" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSingalAutoSearch(void)
{
    SET_SOURCE_SEARCH_AUTO();
    stSystemData.SearchIndex = 0;   //HDMI
    CSourceSwitchInputPort(_D0_INPUT_PORT);
    ucOsdEventMsg = _CHANGE_SOURCE_MSG;
}

void COsdLeftSingalAutoSearch(void)
{
//    COsdDispPenPoint(ROW(13), COL(3), ROW(5), COL(3), _MENU_SIGNAL_VGA);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightSingalAutoSearch(void)
{
#if(_DP_SUPPORT == _ON)
    COsdDispPenPoint(ROW(13), COL(3), ROW(11), COL(3), _MENU_SIGNAL_DISPLAYPORT);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#elif((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT))
    COsdDispPenPoint(ROW(13), COL(3), ROW(9), COL(3), _MENU_SIGNAL_HDMI);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#elif((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_DVI_I_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_I_PORT))
    COsdDispPenPoint(ROW(13), COL(3), ROW(7), COL(3), _MENU_SIGNAL_DVI);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif
}

void COsdExitSingalAutoSearch(void)
{
#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
    if(GET_SOURCE_OSD_STATUS())
    {
        COsdExitDicomSetting();
        CLR_SOURCE_OSD_STATUS();
    }
    else
#endif
    {
        COsdExitSingalVGA();
    }
}
#endif


#if(_AUDIO_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// OSD "Volume" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuVolume(void)
{
    ucOsdState = _MENU_SUB_VOLUME;
    COsdFxHLine(ROW(19), COL(5), 12, ((_CP_WHITE & 0x0f) << 4), _WRITE_BYTE2);
    COsdFxHLine(ROW(19), COL(5), 1, 0x0d, _WRITE_BYTE1);
    COsdFxHLine(ROW(19), COL(5 + 12 - 1), 1, 0x0c, _WRITE_BYTE1);

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
    COsdFxSlider(ROW(19), COL(5 + 1), 12 - 2, stOsdUserData.Volume, 255 + 0, 0);
#else
    COsdFxSlider(ROW(19), COL(5 + 1), 12 - 2, stOsdUserData.Volume, 63 + 0, 0);
#endif

    COsdFxHLine(ROW(18), COL(5 + 12 - 3), 3, ((_CP_WHITE & 0x0f) << 4), _WRITE_BYTE2);
    COsdFxShowNumber(ROW(19), COL(19), stOsdUserData.Volume - 0, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
}

void COsdLeftVolume(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_MUTE);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(10), (GET_VOLUME_MUTE_STATUS()), tOSD_AUDIO_TABLE[2]);
}

void COsdRightVolume(void)
{
    COsdLeftVolume();
}

void COsdExitVolume(void)
{
    COsdFxCloseWindow(WINNO(2));
    COsdDispDrawInitWindow();
    COsdFxLoadIcon(ROW(13), COL(3), tOSD_POINT_ICO);
    ucOsdState = _MENU_AUDIO;
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

//----------------------------------------------------------------------------------------------------
// OSD "subVolume" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubVolume(void)
{
    ucOsdState = _MENU_VOLUME;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 15, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftSubVolume(void)
{
    SET_KEYREPEATENABLE();

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
    stOsdUserData.Volume = COsdFxDetOverRange(stOsdUserData.Volume, 255, 0, _DET_OVERRANGE_MAX);
#else
   stOsdUserData.Volume = COsdFxDetOverRange(stOsdUserData.Volume, 63, 0, _DET_OVERRANGE_MAX);
#endif

    CAdjustVolume(stOsdUserData.Volume);
    COsdFxHLine(ROW(19), COL(5), 12, ((_CP_WHITE & 0x0f) << 4), _WRITE_BYTE2);
    COsdFxHLine(ROW(19), COL(5), 1, 0x0d, _WRITE_BYTE1);
    COsdFxHLine(ROW(19), COL(5 + 12 - 1), 1, 0x0c, _WRITE_BYTE1);

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
    COsdFxSlider(ROW(19), COL(5 + 1), 12 - 2, stOsdUserData.Volume, 255 + 0, 0);
#else
    COsdFxSlider(ROW(19), COL(5 + 1), 12 - 2, stOsdUserData.Volume, 63 + 0, 0);
#endif

    COsdFxHLine(ROW(18), COL(5 + 12 - 3), 3, ((_CP_WHITE & 0x0f) << 4), _WRITE_BYTE2);
    COsdFxShowNumber(ROW(19), COL(19), stOsdUserData.Volume - 0, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
}

void COsdRightSubVolume(void)
{
    SET_KEYREPEATENABLE();

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
    stOsdUserData.Volume = COsdFxDetOverRange(stOsdUserData.Volume, 255, 0, _DET_OVERRANGE_MIN);
#else
    stOsdUserData.Volume = COsdFxDetOverRange(stOsdUserData.Volume, 63, 0, _DET_OVERRANGE_MIN);
#endif


    CAdjustVolume(stOsdUserData.Volume);
    COsdFxHLine(ROW(19), COL(5), 12, ((_CP_WHITE & 0x0f) << 4), _WRITE_BYTE2);
    COsdFxHLine(ROW(19), COL(5), 1, 0x0d, _WRITE_BYTE1);
    COsdFxHLine(ROW(19), COL(5 + 12 - 1), 1, 0x0c, _WRITE_BYTE1);


#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
    COsdFxSlider(ROW(19), COL(5 + 1), 12 - 2, stOsdUserData.Volume, 255 + 0, 0);
#else
    COsdFxSlider(ROW(19), COL(5 + 1), 12 - 2, stOsdUserData.Volume, 63 + 0, 0);
#endif

    COsdFxHLine(ROW(18), COL(5 + 12 - 3), 3, ((_CP_WHITE & 0x0f) << 4), _WRITE_BYTE2);
    COsdFxShowNumber(ROW(19), COL(19), stOsdUserData.Volume - 0, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
}

void COsdExitSubVolume(void)
{
    COsdMenuSubVolume();
}

//----------------------------------------------------------------------------------------------------
// OSD "Volume" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuMute(void)
{
    if(GET_VOLUME_MUTE_STATUS())
    {
        CLR_VOLUME_MUTE_STATUS();
    }
    else
    {
        SET_VOLUME_MUTE_STATUS();

        CScalerPageSelect(_PAGE1);

        CScalerSetByte(_P1_AOUT_CTL_F4, 0xC0); //for hdmi to vga mute
        CScalerSetByte(_P1_HPOUT_CTL_F5, 0xC0); //for hdmi to vga mute
    }

    COsdFxLoadText(ROW(19), COL(10), (GET_VOLUME_MUTE_STATUS()), tOSD_AUDIO_TABLE[2]);
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    CAdjustAudioControl(_ENABLE);
}

void COsdLeftMute(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_VOLUME);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdDispClearText(ROW(19), COL(10), 5, 1);
}

void COsdRightMute(void)
{
    COsdLeftMute();
}

void COsdExitMute(void)
{
    COsdExitVolume();
}

#endif // End of#if(_AUDIO_SUPPORT==_ON)

#if(_DDCCI_SUPPORT == _ON)
void COsdMenuDDCCIONOFF(void)
{
#if((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122))
    if(GET_DDCCI_STATUS())
    {
        CLR_DDCCI_STATUS();
#if(_DDC_CHANNEL_SEL == _VGA_DDC_CHANNEL)
        MCU_I2C_SET_SLAVE_FF27 = 0x6a;
#else
        MCU_I2C_SET_SLAVE_FF27 = 0x6b;
#endif
    }
    else
    {
        SET_DDCCI_STATUS();
        MCU_I2C_SET_SLAVE_FF27 = 0x6e;

        if((GET_INPUT_PORT(g_ucSearchIndex) == _A0_INPUT_PORT)
        || (GET_INPUT_PORT(g_ucSearchIndex) == _A1_INPUT_PORT)
        || (GET_INPUT_PORT(g_ucSearchIndex) == _VI_INPUT_PORT))
        {
            MCU_I2C_SET_SLAVE_FF27 = MCU_I2C_SET_SLAVE_FF27 & (~_BIT0);
        }
        else
        {
            MCU_I2C_SET_SLAVE_FF27 = MCU_I2C_SET_SLAVE_FF27 | (_BIT0);
        }
    }
#elif(_MCU_TYPE == _REALTEK_EMBEDDED)
    if(GET_DDCCI_STATUS())
    {
        CLR_DDCCI_STATUS();
        MCU_I2C_CHANNEL_CTRL_FF2B = 0x00;
        MCU_I2C_SET_SLAVE_FF23 = 0x6a;
        MCU_I2C_IRQ_CTRL_FF28 = 0x16;
#if(_DDC_CHANNEL_SEL == _HDMI_DDC_CHANNEL)
            MCU_HDMI_DDC_CTRL2_FF2E &= 0xFE;
#elif(_DDC_CHANNEL_SEL == _DVI_DDC_CHANNEL)
            MCU_DVI_DDC_CTRL2_FF20 &= 0xFE;
#else
            MCU_ADC_DDC_CTRL2_FF1D &= 0xFE;
#endif

#if(_DDC_CHANNEL_SEL == _HDMI_DDC_CHANNEL)
            MCU_I2C_CHANNEL_CTRL_FF2B |= 0x01;  // From HDMI DDC
#elif(_DDC_CHANNEL_SEL == _DVI_DDC_CHANNEL)
            MCU_I2C_CHANNEL_CTRL_FF2B &= 0xFE;
            MCU_I2C_SET_SLAVE_FF23 |= 0x01;     // From DVI DDC
#else
            MCU_I2C_CHANNEL_CTRL_FF2B &= 0xFE;
            MCU_I2C_SET_SLAVE_FF23 &= 0xFE;     // From ADC DDC
#endif

    }
    else
    {
        SET_DDCCI_STATUS();
        MCU_I2C_SET_SLAVE_FF23 = 0x6e;
        MCU_I2C_IRQ_CTRL_FF28 = 0x3F;

#if(_DDC_CHANNEL_SEL == _HDMI_DDC_CHANNEL)
        MCU_HDMI_DDC_CTRL2_FF2E &= 0xFE;
#elif(_DDC_CHANNEL_SEL == _DVI_DDC_CHANNEL)
        MCU_DVI_DDC_CTRL2_FF20 &= 0xFE;
#else
        MCU_ADC_DDC_CTRL2_FF1D &= 0xFE;
#endif

        if((GET_INPUT_PORT(g_ucSearchIndex) == _A0_INPUT_PORT)
        || (GET_INPUT_PORT(g_ucSearchIndex) == _A1_INPUT_PORT)
        || (GET_INPUT_PORT(g_ucSearchIndex) == _VI_INPUT_PORT))
        {
            MCU_I2C_CHANNEL_CTRL_FF2B &= (~_BIT0);
            MCU_I2C_SET_SLAVE_FF23 = MCU_I2C_SET_SLAVE_FF23 & (~_BIT0);
        }
        else if(GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT)
        {

#if(_DDC_CHANNEL_FOR_D0 == _DDC2)
            MCU_I2C_CHANNEL_CTRL_FF2B &= (~_BIT0);
            MCU_I2C_SET_SLAVE_FF23 |= _BIT0;
#else
            MCU_I2C_CHANNEL_CTRL_FF2B |= _BIT0;
            MCU_I2C_SET_SLAVE_FF23 &= (~_BIT0);
#endif

        }
        else
        {

#if(_DDC_CHANNEL_FOR_D1 == _DDC2)
            MCU_I2C_CHANNEL_CTRL_FF2B &= (~_BIT0);
            MCU_I2C_SET_SLAVE_FF23 |= _BIT0;
#else
            MCU_I2C_CHANNEL_CTRL_FF2B |= _BIT0;
            MCU_I2C_SET_SLAVE_FF23 &= (~_BIT0);
#endif

        }

    }
#endif
    COsdFxLoadText(ROW(19), COL(10), (GET_DDCCI_STATUS()), tOSDDDCCI_ON_OFF_STR);
    ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
}

void COsdLeftDDCCIONOFF(void)
{

}

void COsdRightDDCCIONOFF(void)
{

}

void COsdExitDDCCIONOFF(void)
{
    COsdFxCloseWindow(WINNO(2));
    COsdDispDrawInitWindow();
    COsdFxLoadIcon(ROW(19), COL(3), tOSD_POINT_ICO);
    ucOsdState = _MENU_DDCCI;
    COsdFxChange1bitColor(ROW(19), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}
#endif

#if(_VIVID_COLOR_FUCTION == _ON)
//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuVividColor(void)
{
    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 20, 15);

    if(GET_WINDOW_SIZE() == _VIVID_WINDOW_SIZE_DISABLE)
    {
        COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(7), FGCOLOR(_CP_GRAY), BGCOLOR(_CP_BACKGROUND));
    }
    else if(GET_DCC_MODE() != _VIVID_DCC_DISABLE)
    {
        COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(4), FGCOLOR(_CP_GRAY), BGCOLOR(_CP_BACKGROUND));
    }

    COsdFxLoadText(ROW(19), COL(9), (GET_WINDOW_SIZE()), tVIVID_COLOR_TABLE[1]);

    COsdFxLoadIcon(ROW(5), COL(7), tVIVID_COLOR_TABLE[0]);
    COsdDispPenPoint(ROW(11), COL(3), ROW(5), COL(3), _MENU_COLOR_WINODW_SIZE);
    COsdFxDrawWindow(XSTART(40), YSTART(300), XEND(250), YEND(400), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_BLACK), tOSD_WINDOW2_STYLE);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdLeftVividColor(void)
{

#if(_NON_LINEAR_SCALING_FUCTION == _ON)
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_NONLINEAR_SCALING);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(10), (GET_NON_LINEAR_SCALING_STATUS()), tOSD_AUDIO_TABLE[2]);
#elif(_ASPECT_RATIO_SUPPORT == _ON)
    COsdDispPenPoint(ROW(5), COL(3), ROW(9), COL(3), _MENU_ASPECT_RATIO);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(8), (GET_DISP_RATIO()), tOSD_ASPECT_RATIO_TYPE_STR);
#elif (_SRGB_COLOR_ENHANCE == _ON)
    COsdDispPenPoint(ROW(5), COL(3), ROW(11), COL(3), _MENU_SRGB);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#elif(_COLOR_FORMAT_CONVERT == _ON)
if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) || (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_RGB_YUV);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}
// V012 Modify 20100304 End

#endif

}

void COsdRightVividColor(void)
{
// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
/*
#if(_SRGB_COLOR_ENHANCE == _ON)
*/
#if(_COLOR_FORMAT_CONVERT == _ON)
if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) || (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_RGB_YUV);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}
#elif(_SRGB_COLOR_ENHANCE == _ON)
// V012 Modify 20100304 End

    COsdDispPenPoint(ROW(5), COL(3), ROW(11), COL(3), _MENU_SRGB);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#elif(_ASPECT_RATIO_SUPPORT == _ON)

    COsdDispPenPoint(ROW(5), COL(3), ROW(9), COL(3), _MENU_ASPECT_RATIO);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(8), (GET_DISP_RATIO()), tOSD_ASPECT_RATIO_TYPE_STR);

#elif(_NON_LINEAR_SCALING_FUCTION == _ON)

    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_NONLINEAR_SCALING);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(10), (GET_NON_LINEAR_SCALING_STATUS()), tOSD_AUDIO_TABLE[2]);

#endif
}

void COsdExitVividColor(void)
{
    COsdFxCloseWindow(WINNO(2));
    COsdDispDrawInitWindow();
    ucOsdState = _MENU_AUTO_ADJUST_SETTING;

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
/*
#if(_AUDIO_SUPPORT == _ON)
    COsdFxLoadIcon(ROW(15), COL(3), tOSD_POINT_ICO);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#else
    COsdFxLoadIcon(ROW(13), COL(3), tOSD_POINT_ICO);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif // End of #if(_AUDIO_SUPPORT==_ON)
*/
    COsdFxLoadIcon(ROW(15), COL(3), tOSD_POINT_ICO);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
// V012 Modify 20100304 End

}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Window" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindow(void)
{
    BYTE temp;

    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 20, 15);

    for(temp = 0; temp < 4; temp++)
    {
        COsdFxLoadText(ROW(5 + temp*2), COL(7), temp, tVIVID_COLOR_TABLE[1]);
    }

    COsdDispPenPoint(ROW(5), COL(3), ROW(5 + (GET_WINDOW_SIZE() * 2)), COL(3), (_MENU_COLOR_WINODW_SIZE_DISABLE + GET_WINDOW_SIZE()));
    COsdFxDrawWindow(XSTART(40), YSTART(300), XEND(250), YEND(400), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_BLACK), tOSD_WINDOW2_STYLE);
    COsdFxChange1bitColor(ROW(5 + (GET_WINDOW_SIZE() * 2)), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdLeftColorWindow(void)
{
    if(GET_WINDOW_SIZE() != _VIVID_WINDOW_SIZE_DISABLE)
    {
        COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_DCC_MODE);
        COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
        COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

        COsdDispClearText(ROW(19), COL(9), 16, 1);
        COsdFxLoadText(ROW(19), COL(9), (GET_DCC_MODE()), tVIVID_COLOR_TABLE[3]);
    }
}

void COsdRightColorWindow(void)
{
    if(GET_WINDOW_SIZE() != _VIVID_WINDOW_SIZE_DISABLE)
    {
        if(GET_DCC_MODE() == _VIVID_DCC_DISABLE)
        {

            COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_VIVID_BRIGHTNESS);
            COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
            COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

            COsdDispClearText(ROW(19), COL(9), 16, 1);
        }
        else
        {
            COsdDispPenPoint(ROW(5), COL(3), ROW(9), COL(3), _MENU_ICM_MODE);
            COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
            COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

            COsdDispClearText(ROW(19), COL(9), 16, 1);
            COsdFxLoadText(ROW(19), COL(9), (GET_ICM_MODE()), tVIVID_COLOR_TABLE[3]);
        }
    }
}

void COsdExitColorWindow(void)
{
    COsdMenuSpecial();
}


//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Window Disable" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindowDisable(void)
{
    SET_WINDOW_SIZE(ucOsdState - _MENU_COLOR_WINODW_SIZE_DISABLE);
    COsdDispVividColorHLWindow();
}

void COsdLeftColorWindowDisable(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_COLOR_WINODW_SIZE_FULL);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightColorWindowDisable(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(11), COL(3), _MENU_COLOR_WINODW_SIZE_USER);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitColorWindowDisable(void)
{
    COsdMenuVividColor();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Demo Window Full" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindowFull(void)
{
    COsdMenuColorWindowDisable();
}

void COsdLeftColorWindowFull(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_COLOR_WINODW_SIZE_DEMO);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightColorWindowFull(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_COLOR_WINODW_SIZE_DISABLE);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitColorWindowFull(void)
{
    COsdExitColorWindowDisable();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Demo Window" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindowDemo(void)
{
    COsdMenuColorWindowDisable();
}

void COsdLeftColorWindowDemo(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_COLOR_WINODW_SIZE_USER);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightColorWindowDemo(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_COLOR_WINODW_SIZE_FULL);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitColorWindowDemo(void)
{
    COsdExitColorWindowDisable();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Window User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindowUser(void)
{
    COsdMenuColorWindowDisable();

    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 20, 15);
    COsdFxLoadIcon(ROW(5), COL(7), tVIVID_COLOR_TABLE[2]);
    COsdDispPenPoint(ROW(5), COL(3), ROW(5), COL(3), _MENU_COLOR_WINODW_SIZE_USER_HPOS);
    COsdFxDrawWindow(XSTART(40), YSTART(300), XEND(250), YEND(400), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_BLACK), tOSD_WINDOW2_STYLE);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdLeftColorWindowUser(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(5), COL(3), _MENU_COLOR_WINODW_SIZE_DISABLE);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightColorWindowUser(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_COLOR_WINODW_SIZE_DEMO);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitColorWindowUser(void)
{
    COsdExitColorWindowDisable();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Window User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindowUserHPos(void)
{
    ucOsdState = _MENU_COLOR_WINODW_SIZE_USER_HPOS_ADJ;
    COsdDispFullSlider(ROW(19), COL(5), LENGTH(13), stOsdUserData.VividWinHPos, _VIVID_WINDOW_H_POSITION_MAX, _VIVID_WINDOW_H_POSITION_MIN, _CP_WHITE, _CP_WHITE);
}

void COsdLeftColorWindowUserHPos(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_COLOR_WINODW_SIZE_USER_VPOS);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightColorWindowUserHPos(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(11), COL(3), _MENU_COLOR_WINODW_SIZE_USER_VHEI);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitColorWindowUserHPos(void)
{
    BYTE temp;
    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 20, 15);

    for(temp = 0; temp < 4; temp++)
    {
        COsdFxLoadText(ROW(5 + temp*2), COL(7), temp, tVIVID_COLOR_TABLE[1]);
    }

    COsdDispPenPoint(ROW(11), COL(3), ROW(11), COL(3), _MENU_COLOR_WINODW_SIZE_USER);
    COsdFxDrawWindow(XSTART(40), YSTART(300), XEND(250), YEND(400), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_BLACK), tOSD_WINDOW2_STYLE);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Window User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindowUserHPosAdj(void)
{
    ucOsdState = _MENU_COLOR_WINODW_SIZE_USER_HPOS;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 20, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftColorWindowUserHPosAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividWinHPos = COsdFxDetOverRange(stOsdUserData.VividWinHPos, _VIVID_WINDOW_H_POSITION_MAX, _VIVID_WINDOW_H_POSITION_MIN, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), LENGTH(13), stOsdUserData.VividWinHPos, _VIVID_WINDOW_H_POSITION_MAX, _VIVID_WINDOW_H_POSITION_MIN, _CP_WHITE, _CP_WHITE);
    CAdjustHLWindowHV(stOsdUserData.VividWinHPos, stOsdUserData.VividWinHWidth, stOsdUserData.VividWinVPos, stOsdUserData.VividWinVHeight);
}

void COsdRightColorWindowUserHPosAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividWinHPos = COsdFxDetOverRange(stOsdUserData.VividWinHPos, _VIVID_WINDOW_H_POSITION_MAX, _VIVID_WINDOW_H_POSITION_MIN, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), LENGTH(13), stOsdUserData.VividWinHPos, _VIVID_WINDOW_H_POSITION_MAX, _VIVID_WINDOW_H_POSITION_MIN, _CP_WHITE, _CP_WHITE);
    CAdjustHLWindowHV(stOsdUserData.VividWinHPos, stOsdUserData.VividWinHWidth, stOsdUserData.VividWinVPos, stOsdUserData.VividWinVHeight);
}

void COsdExitColorWindowUserHPosAdj(void)
{
    COsdMenuColorWindowUserHPosAdj();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Window User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindowUserVPos(void)
{
    ucOsdState = _MENU_COLOR_WINODW_SIZE_USER_VPOS_ADJ;
    COsdDispFullSlider(ROW(19), COL(5), LENGTH(13), stOsdUserData.VividWinVPos, _VIVID_WINDOW_V_POSITION_MAX, _VIVID_WINDOW_V_POSITION_MIN, _CP_WHITE, _CP_WHITE);
}

void COsdLeftColorWindowUserVPos(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_COLOR_WINODW_SIZE_USER_HWID);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightColorWindowUserVPos(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_COLOR_WINODW_SIZE_USER_HPOS);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitColorWindowUserVPos(void)
{
    COsdExitColorWindowUserHPos();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Window User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindowUserVPosAdj(void)
{
    ucOsdState = _MENU_COLOR_WINODW_SIZE_USER_VPOS;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 20, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftColorWindowUserVPosAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividWinVPos = COsdFxDetOverRange(stOsdUserData.VividWinVPos, _VIVID_WINDOW_V_POSITION_MAX, _VIVID_WINDOW_V_POSITION_MIN, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), LENGTH(13), stOsdUserData.VividWinVPos, _VIVID_WINDOW_V_POSITION_MAX, _VIVID_WINDOW_V_POSITION_MIN, _CP_WHITE, _CP_WHITE);
    CAdjustHLWindowHV(stOsdUserData.VividWinHPos, stOsdUserData.VividWinHWidth, stOsdUserData.VividWinVPos, stOsdUserData.VividWinVHeight);
}

void COsdRightColorWindowUserVPosAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividWinVPos = COsdFxDetOverRange(stOsdUserData.VividWinVPos, _VIVID_WINDOW_V_POSITION_MAX, _VIVID_WINDOW_V_POSITION_MIN, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), LENGTH(13), stOsdUserData.VividWinVPos, _VIVID_WINDOW_V_POSITION_MAX, _VIVID_WINDOW_V_POSITION_MIN, _CP_WHITE, _CP_WHITE);
    CAdjustHLWindowHV(stOsdUserData.VividWinHPos, stOsdUserData.VividWinHWidth, stOsdUserData.VividWinVPos, stOsdUserData.VividWinVHeight);
}

void COsdExitColorWindowUserVPosAdj(void)
{
    COsdMenuColorWindowUserVPosAdj();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Window User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindowUserHWid(void)
{
    ucOsdState = _MENU_COLOR_WINODW_SIZE_USER_HWID_ADJ;
    COsdDispFullSlider(ROW(19), COL(5), LENGTH(13), stOsdUserData.VividWinHWidth, _VIVID_WINDOW_H_WIDTH_MAX, _VIVID_WINDOW_H_WIDTH_MIN, _CP_WHITE, _CP_WHITE);
}

void COsdLeftColorWindowUserHWid(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_COLOR_WINODW_SIZE_USER_VHEI);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightColorWindowUserHWid(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_COLOR_WINODW_SIZE_USER_VPOS);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitColorWindowUserHWid(void)
{
    COsdExitColorWindowUserHPos();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Window User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindowUserHWidAdj(void)
{
    ucOsdState = _MENU_COLOR_WINODW_SIZE_USER_HWID;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 20, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftColorWindowUserHWidAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividWinHWidth = COsdFxDetOverRange(stOsdUserData.VividWinHWidth, _VIVID_WINDOW_H_WIDTH_MAX, _VIVID_WINDOW_H_WIDTH_MIN, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), LENGTH(13), stOsdUserData.VividWinHWidth, _VIVID_WINDOW_H_WIDTH_MAX, _VIVID_WINDOW_H_WIDTH_MIN, _CP_WHITE, _CP_WHITE);
    CAdjustHLWindowHV(stOsdUserData.VividWinHPos, stOsdUserData.VividWinHWidth, stOsdUserData.VividWinVPos, stOsdUserData.VividWinVHeight);
}

void COsdRightColorWindowUserHWidAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividWinHWidth = COsdFxDetOverRange(stOsdUserData.VividWinHWidth, _VIVID_WINDOW_H_WIDTH_MAX, _VIVID_WINDOW_H_WIDTH_MIN, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), LENGTH(13), stOsdUserData.VividWinHWidth, _VIVID_WINDOW_H_WIDTH_MAX, _VIVID_WINDOW_H_WIDTH_MIN, _CP_WHITE, _CP_WHITE);
    CAdjustHLWindowHV(stOsdUserData.VividWinHPos, stOsdUserData.VividWinHWidth, stOsdUserData.VividWinVPos, stOsdUserData.VividWinVHeight);
}

void COsdExitColorWindowUserHWidAdj(void)
{
    COsdMenuColorWindowUserHWidAdj();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Window User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindowUserVHei(void)
{
    ucOsdState = _MENU_COLOR_WINODW_SIZE_USER_VHEI_ADJ;
    COsdDispFullSlider(ROW(19), COL(5), LENGTH(13), stOsdUserData.VividWinVHeight, _VIVID_WINDOW_V_HEIGHT_MAX, _VIVID_WINDOW_V_HEIGHT_MIN, _CP_WHITE, _CP_WHITE);
}

void COsdLeftColorWindowUserVHei(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(5), COL(3), _MENU_COLOR_WINODW_SIZE_USER_HPOS);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightColorWindowUserVHei(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_COLOR_WINODW_SIZE_USER_HWID);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitColorWindowUserVHei(void)
{
    COsdExitColorWindowUserHPos();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Window User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuColorWindowUserVHeiAdj(void)
{
    ucOsdState = _MENU_COLOR_WINODW_SIZE_USER_VHEI;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 20, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftColorWindowUserVHeiAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividWinVHeight = COsdFxDetOverRange(stOsdUserData.VividWinVHeight, _VIVID_WINDOW_V_HEIGHT_MAX, _VIVID_WINDOW_V_HEIGHT_MIN, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), LENGTH(13), stOsdUserData.VividWinVHeight, _VIVID_WINDOW_V_HEIGHT_MAX, _VIVID_WINDOW_V_HEIGHT_MIN, _CP_WHITE, _CP_WHITE);
    CAdjustHLWindowHV(stOsdUserData.VividWinHPos, stOsdUserData.VividWinHWidth, stOsdUserData.VividWinVPos, stOsdUserData.VividWinVHeight);
}

void COsdRightColorWindowUserVHeiAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividWinVHeight = COsdFxDetOverRange(stOsdUserData.VividWinVHeight, _VIVID_WINDOW_V_HEIGHT_MAX, _VIVID_WINDOW_V_HEIGHT_MIN, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), LENGTH(13), stOsdUserData.VividWinVHeight, _VIVID_WINDOW_V_HEIGHT_MAX, _VIVID_WINDOW_V_HEIGHT_MIN, _CP_WHITE, _CP_WHITE);
    CAdjustHLWindowHV(stOsdUserData.VividWinHPos, stOsdUserData.VividWinHWidth, stOsdUserData.VividWinVPos, stOsdUserData.VividWinVHeight);
}

void COsdExitColorWindowUserVHeiAdj(void)
{
    COsdMenuColorWindowUserVHeiAdj();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color DCC Mode" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuDCCMode(void)
{
    BYTE temp;

    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 20, 15);

    for(temp = 0; temp < 4; temp++)
    {
        COsdFxLoadText(ROW(5 + temp*2), COL(7), temp, tVIVID_COLOR_TABLE[3]);
    }

    COsdDispPenPoint(ROW(5), COL(3), ROW(5 + (GET_DCC_MODE() * 2)), COL(3), (_MENU_DCC_MODE_DISABLE + GET_DCC_MODE()));
    COsdFxDrawWindow(XSTART(40), YSTART(300), XEND(250), YEND(400), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_BLACK), tOSD_WINDOW2_STYLE);
    COsdFxChange1bitColor(ROW(5 + (GET_DCC_MODE() * 2)), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdLeftDCCMode(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_ICM_MODE);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

    COsdDispClearText(ROW(19), COL(9), 16, 1);
    COsdFxLoadText(ROW(19), COL(9), (GET_ICM_MODE()), tVIVID_COLOR_TABLE[3]);
}

void COsdRightDCCMode(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_COLOR_WINODW_SIZE);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

    COsdDispClearText(ROW(19), COL(9), 16, 1);
    COsdFxLoadText(ROW(19), COL(9), (GET_WINDOW_SIZE()), tVIVID_COLOR_TABLE[1]);
}

void COsdExitDCCMode(void)
{
    COsdMenuSpecial();
}


//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color DCC Mode Disable" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuDCCModeDisable(void)
{
    SET_DCC_MODE(ucOsdState - _MENU_DCC_MODE_DISABLE);
    COsdDispVividColor();
}

void COsdLeftDCCModeDisable(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_DCC_MODE_MOVIE);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightDCCModeDisable(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(11), COL(3), _MENU_DCC_MODE_GAME);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitDCCModeDisable(void)
{
    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 20, 15);

    if(GET_DCC_MODE() != _VIVID_DCC_DISABLE)
    {
        COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(4), FGCOLOR(_CP_GRAY), BGCOLOR(_CP_BACKGROUND));
    }

    COsdFxLoadText(ROW(19), COL(9), (GET_DCC_MODE()), tVIVID_COLOR_TABLE[3]);
    COsdFxLoadIcon(ROW(5), COL(7), tVIVID_COLOR_TABLE[0]);
    COsdDispPenPoint(ROW(7), COL(3), ROW(7), COL(3), _MENU_DCC_MODE);
    COsdFxDrawWindow(XSTART(40), YSTART(300), XEND(250), YEND(400), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_BLACK), tOSD_WINDOW2_STYLE);

    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color DCC Mode Movie" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuDCCModeMovie(void)
{
    COsdMenuDCCModeDisable();
}

void COsdLeftDCCModeMovie(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_DCC_MODE_PHOTO);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightDCCModeMovie(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_DCC_MODE_DISABLE);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitDCCModeMovie(void)
{
    COsdExitDCCModeDisable();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color DCC Mode Photo" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuDCCModePhoto(void)
{
    COsdMenuDCCModeDisable();
}

void COsdLeftDCCModePhoto(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_DCC_MODE_GAME);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightDCCModePhoto(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_DCC_MODE_MOVIE);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitDCCModePhoto(void)
{
    COsdExitDCCModeDisable();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color DCC Mode Game" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuDCCModeGame(void)
{
    COsdMenuDCCModeDisable();
}

void COsdLeftDCCModeGame(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(5), COL(3), _MENU_DCC_MODE_DISABLE);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightDCCModeGame(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_DCC_MODE_PHOTO);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitDCCModeGame(void)
{
    COsdExitDCCModeDisable();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMMode(void)
{
    BYTE temp;

    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 20, 15);

    for(temp = 0; temp < 5; temp++)
    {
        COsdFxLoadText(ROW(5 + temp*2), COL(7), temp, tVIVID_COLOR_TABLE[3]);
    }

    COsdDispPenPoint(ROW(5), COL(3), ROW(5 + (GET_ICM_MODE() * 2)), COL(3), (_MENU_ICM_MODE_DISABLE + GET_ICM_MODE()));
    COsdFxDrawWindow(XSTART(40), YSTART(300), XEND(250), YEND(400), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_BLACK), tOSD_WINDOW2_STYLE);
    COsdFxChange1bitColor(ROW(5 + (GET_ICM_MODE() * 2)), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdLeftICMMode(void)
{
    if(GET_DCC_MODE() == _VIVID_DCC_DISABLE)
    {
        COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_VIVID_CONTRAST);
        COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
        COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

        COsdDispClearText(ROW(19), COL(9), 16, 1);
    }
    else
    {
        COsdDispPenPoint(ROW(9), COL(3), ROW(5), COL(3), _MENU_COLOR_WINODW_SIZE);
        COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
        COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

        COsdDispClearText(ROW(19), COL(9), 16, 1);
        COsdFxLoadText(ROW(19), COL(9), (GET_WINDOW_SIZE()), tVIVID_COLOR_TABLE[1]);
    }
}

void COsdRightICMMode(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_DCC_MODE);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

    COsdDispClearText(ROW(19), COL(9), 16, 1);
    COsdFxLoadText(ROW(19), COL(9), (GET_DCC_MODE()), tVIVID_COLOR_TABLE[3]);
}

void COsdExitICMMode(void)
{
    COsdMenuSpecial();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode Disable" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeDisable(void)
{
    SET_ICM_MODE(ucOsdState - _MENU_ICM_MODE_DISABLE);
    COsdDispVividColor();
}

void COsdLeftICMModeDisable(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_ICM_MODE_MOVIE);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightICMModeDisable(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(13), COL(3), _MENU_ICM_MODE_USER);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitICMModeDisable(void)
{
    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 20, 15);

    if(GET_DCC_MODE() != _VIVID_DCC_DISABLE)
    {
        COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(4), FGCOLOR(_CP_GRAY), BGCOLOR(_CP_BACKGROUND));
    }

    COsdFxLoadText(ROW(19), COL(9), (GET_ICM_MODE()), tVIVID_COLOR_TABLE[3]);
    COsdFxLoadIcon(ROW(5), COL(7), tVIVID_COLOR_TABLE[0]);
    COsdDispPenPoint(ROW(9), COL(3), ROW(9), COL(3), _MENU_ICM_MODE);
    COsdFxDrawWindow(XSTART(40), YSTART(300), XEND(250), YEND(400), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_BLACK), tOSD_WINDOW2_STYLE);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode Movie" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeMovie(void)
{
    COsdMenuICMModeDisable();
}

void COsdLeftICMModeMovie(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_ICM_MODE_PHOTO);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightICMModeMovie(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_ICM_MODE_DISABLE);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitICMModeMovie(void)
{
    COsdExitICMModeDisable();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode Photo" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModePhoto(void)
{
    COsdMenuICMModeDisable();
}

void COsdLeftICMModePhoto(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_ICM_MODE_GAME);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightICMModePhoto(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_ICM_MODE_MOVIE);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitICMModePhoto(void)
{
    COsdExitICMModeDisable();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode Game" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeGame(void)
{
    COsdMenuICMModeDisable();
}

void COsdLeftICMModeGame(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(13), COL(3), _MENU_ICM_MODE_USER);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightICMModeGame(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_ICM_MODE_PHOTO);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitICMModeGame(void)
{
    COsdExitICMModeDisable();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUser(void)
{
    BYTE temp;

    COsdMenuICMModeDisable();

    CAdjustVividHueSat(_RED, stOsdUserData.VividICMRedHue, stOsdUserData.VividICMRedSat);
    CAdjustVividHueSat(_GREEN, stOsdUserData.VividICMGreenHue, stOsdUserData.VividICMGreenSat);
    CAdjustVividHueSat(_BLUE, stOsdUserData.VividICMBlueHue, stOsdUserData.VividICMBlueSat);

    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 20, 15);

    for(temp = 0; temp < 6; temp++)
    {
        COsdFxLoadText(ROW(5 + temp*2), COL(7), (temp + 5), tVIVID_COLOR_TABLE[3]);
    }

    COsdDispPenPoint(ROW(5), COL(3), ROW(5), COL(3), (_MENU_ICM_MODE_USER_RED_HUE));
    COsdFxDrawWindow(XSTART(40), YSTART(300), XEND(250), YEND(400), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_BLACK), tOSD_WINDOW2_STYLE);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdLeftICMModeUser(void)
{
    COsdDispPenPoint(ROW(13), COL(3), ROW(5), COL(3), _MENU_ICM_MODE_DISABLE);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightICMModeUser(void)
{
    COsdDispPenPoint(ROW(13), COL(3), ROW(11), COL(3), _MENU_ICM_MODE_GAME);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitICMModeUser(void)
{
    COsdExitICMModeDisable();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUserRedHue(void)
{
    ucOsdState = _MENU_ICM_MODE_USER_RED_HUE_ADJ;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMRedHue, _ICM_RED_HUE_MAX, _ICM_RED_HUE_MIN, _CP_RED, _CP_WHITE);
}

void COsdLeftICMModeUserRedHue(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_ICM_MODE_USER_RED_SAT);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightICMModeUserRedHue(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(15), COL(3), _MENU_ICM_MODE_USER_BLUE_SAT);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitICMModeUserRedHue(void)
{
    COsdMenuICMMode();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUserRedHueAdj(void)
{
    ucOsdState = _MENU_ICM_MODE_USER_RED_HUE;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 20, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftICMModeUserRedHueAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividICMRedHue = COsdFxDetOverRange(stOsdUserData.VividICMRedHue, _ICM_RED_HUE_MAX, _ICM_RED_HUE_MIN, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMRedHue, _ICM_RED_HUE_MAX, _ICM_RED_HUE_MIN, _CP_RED, _CP_WHITE);
    CAdjustVividHueSat(_RED, stOsdUserData.VividICMRedHue, stOsdUserData.VividICMRedSat);
}

void COsdRightICMModeUserRedHueAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividICMRedHue = COsdFxDetOverRange(stOsdUserData.VividICMRedHue, _ICM_RED_HUE_MAX, _ICM_RED_HUE_MIN, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMRedHue, _ICM_RED_HUE_MAX, _ICM_RED_HUE_MIN, _CP_RED, _CP_WHITE);
    CAdjustVividHueSat(_RED, stOsdUserData.VividICMRedHue, stOsdUserData.VividICMRedSat);
}

void COsdExitICMModeUserRedHueAdj(void)
{
    COsdMenuICMModeUserRedHueAdj();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUserRedSat(void)
{
    ucOsdState = _MENU_ICM_MODE_USER_RED_SAT_ADJ;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMRedSat, _ICM_RED_SAT_MAX, _ICM_RED_SAT_MIN, _CP_RED, _CP_WHITE);
}

void COsdLeftICMModeUserRedSat(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_ICM_MODE_USER_GREEN_HUE);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightICMModeUserRedSat(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_ICM_MODE_USER_RED_HUE);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitICMModeUserRedSat(void)
{
    COsdExitICMModeUserRedHue();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUserRedSatAdj(void)
{
    ucOsdState = _MENU_ICM_MODE_USER_RED_SAT;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 20, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftICMModeUserRedSatAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividICMRedSat = COsdFxDetOverRange(stOsdUserData.VividICMRedSat, _ICM_RED_SAT_MAX, _ICM_RED_SAT_MIN, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMRedSat, _ICM_RED_SAT_MAX, _ICM_RED_SAT_MIN, _CP_RED, _CP_WHITE);
    CAdjustVividHueSat(_RED, stOsdUserData.VividICMRedHue, stOsdUserData.VividICMRedSat);
}

void COsdRightICMModeUserRedSatAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividICMRedSat = COsdFxDetOverRange(stOsdUserData.VividICMRedSat, _ICM_RED_SAT_MAX, _ICM_RED_SAT_MIN, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMRedSat, _ICM_RED_SAT_MAX, _ICM_RED_SAT_MIN, _CP_RED, _CP_WHITE);
    CAdjustVividHueSat(_RED, stOsdUserData.VividICMRedHue, stOsdUserData.VividICMRedSat);
}

void COsdExitICMModeUserRedSatAdj(void)
{
    COsdMenuICMModeUserRedSatAdj();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUserGreenHue(void)
{
    ucOsdState = _MENU_ICM_MODE_USER_GREEN_HUE_ADJ;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMGreenHue, _ICM_GREEN_HUE_MAX, _ICM_GREEN_HUE_MIN, _CP_GREEN, _CP_WHITE);
}

void COsdLeftICMModeUserGreenHue(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_ICM_MODE_USER_GREEN_SAT);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightICMModeUserGreenHue(void)
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_ICM_MODE_USER_RED_SAT);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitICMModeUserGreenHue(void)
{
    COsdExitICMModeUserRedHue();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUserGreenHueAdj(void)
{
    ucOsdState = _MENU_ICM_MODE_USER_GREEN_HUE;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 20, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftICMModeUserGreenHueAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividICMGreenHue = COsdFxDetOverRange(stOsdUserData.VividICMGreenHue, _ICM_GREEN_HUE_MAX, _ICM_GREEN_HUE_MIN, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMGreenHue, _ICM_GREEN_HUE_MAX, _ICM_GREEN_HUE_MIN, _CP_GREEN, _CP_WHITE);
    CAdjustVividHueSat(_GREEN, stOsdUserData.VividICMGreenHue, stOsdUserData.VividICMGreenSat);
}

void COsdRightICMModeUserGreenHueAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividICMGreenHue = COsdFxDetOverRange(stOsdUserData.VividICMGreenHue, _ICM_GREEN_HUE_MAX, _ICM_GREEN_HUE_MIN, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMGreenHue, _ICM_GREEN_HUE_MAX, _ICM_GREEN_HUE_MIN, _CP_GREEN, _CP_WHITE);
    CAdjustVividHueSat(_GREEN, stOsdUserData.VividICMGreenHue, stOsdUserData.VividICMGreenSat);
}

void COsdExitICMModeUserGreenHueAdj(void)
{
    COsdMenuICMModeUserGreenHueAdj();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUserGreenSat(void)
{
    ucOsdState = _MENU_ICM_MODE_USER_GREEN_SAT_ADJ;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMGreenSat, _ICM_GREEN_SAT_MAX, _ICM_GREEN_SAT_MIN, _CP_GREEN, _CP_WHITE);
}

void COsdLeftICMModeUserGreenSat(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(13), COL(3), _MENU_ICM_MODE_USER_BLUE_HUE);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightICMModeUserGreenSat(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_ICM_MODE_USER_GREEN_HUE);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitICMModeUserGreenSat(void)
{
    COsdExitICMModeUserRedHue();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUserGreenSatAdj(void)
{
    ucOsdState = _MENU_ICM_MODE_USER_GREEN_SAT;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 20, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftICMModeUserGreenSatAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividICMGreenSat = COsdFxDetOverRange(stOsdUserData.VividICMGreenSat, _ICM_GREEN_SAT_MAX, _ICM_GREEN_SAT_MIN, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMGreenSat, _ICM_GREEN_SAT_MAX, _ICM_GREEN_SAT_MIN, _CP_GREEN, _CP_WHITE);
    CAdjustVividHueSat(_GREEN, stOsdUserData.VividICMGreenHue, stOsdUserData.VividICMGreenSat);
}

void COsdRightICMModeUserGreenSatAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividICMGreenSat = COsdFxDetOverRange(stOsdUserData.VividICMGreenSat, _ICM_GREEN_SAT_MAX, _ICM_GREEN_SAT_MIN, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMGreenSat, _ICM_GREEN_SAT_MAX, _ICM_GREEN_SAT_MIN, _CP_GREEN, _CP_WHITE);
    CAdjustVividHueSat(_GREEN, stOsdUserData.VividICMGreenHue, stOsdUserData.VividICMGreenSat);
}

void COsdExitICMModeUserGreenSatAdj(void)
{
    COsdMenuICMModeUserGreenSatAdj();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUserBlueHue(void)
{
    ucOsdState = _MENU_ICM_MODE_USER_BLUE_HUE_ADJ;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMBlueHue, _ICM_BLUE_HUE_MAX, _ICM_BLUE_HUE_MIN, _CP_BLUE, _CP_WHITE);
}

void COsdLeftICMModeUserBlueHue(void)
{
    COsdDispPenPoint(ROW(13), COL(3), ROW(15), COL(3), _MENU_ICM_MODE_USER_BLUE_SAT);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightICMModeUserBlueHue(void)
{
    COsdDispPenPoint(ROW(13), COL(3), ROW(11), COL(3), _MENU_ICM_MODE_USER_GREEN_SAT);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitICMModeUserBlueHue(void)
{
    COsdExitICMModeUserRedHue();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUserBlueHueAdj(void)
{
    ucOsdState = _MENU_ICM_MODE_USER_BLUE_HUE;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 20, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftICMModeUserBlueHueAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividICMBlueHue = COsdFxDetOverRange(stOsdUserData.VividICMBlueHue, _ICM_BLUE_HUE_MAX, _ICM_BLUE_HUE_MIN, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMBlueHue, _ICM_BLUE_HUE_MAX, _ICM_BLUE_HUE_MIN, _CP_BLUE, _CP_WHITE);
    CAdjustVividHueSat(_BLUE, stOsdUserData.VividICMBlueHue, stOsdUserData.VividICMBlueSat);
}

void COsdRightICMModeUserBlueHueAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividICMBlueHue = COsdFxDetOverRange(stOsdUserData.VividICMBlueHue, _ICM_BLUE_HUE_MAX, _ICM_BLUE_HUE_MIN, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMBlueHue, _ICM_BLUE_HUE_MAX, _ICM_BLUE_HUE_MIN, _CP_BLUE, _CP_WHITE);
    CAdjustVividHueSat(_BLUE, stOsdUserData.VividICMBlueHue, stOsdUserData.VividICMBlueSat);
}

void COsdExitICMModeUserBlueHueAdj(void)
{
    COsdMenuICMModeUserBlueHueAdj();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUserBlueSat(void)
{
    ucOsdState = _MENU_ICM_MODE_USER_BLUE_SAT_ADJ;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMBlueSat, _ICM_BLUE_SAT_MAX, _ICM_BLUE_SAT_MIN, _CP_BLUE, _CP_WHITE);
}

void COsdLeftICMModeUserBlueSat(void)
{
    COsdDispPenPoint(ROW(15), COL(3), ROW(5), COL(3), _MENU_ICM_MODE_USER_RED_HUE);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightICMModeUserBlueSat(void)
{
    COsdDispPenPoint(ROW(15), COL(3), ROW(13), COL(3), _MENU_ICM_MODE_USER_BLUE_HUE);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitICMModeUserBlueSat(void)
{
    COsdExitICMModeUserRedHue();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color ICM Mode User" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuICMModeUserBlueSatAdj(void)
{
    ucOsdState = _MENU_ICM_MODE_USER_BLUE_SAT;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 20, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftICMModeUserBlueSatAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividICMBlueSat = COsdFxDetOverRange(stOsdUserData.VividICMBlueSat, _ICM_BLUE_SAT_MAX, _ICM_BLUE_SAT_MIN, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMBlueSat, _ICM_BLUE_SAT_MAX, _ICM_BLUE_SAT_MIN, _CP_BLUE, _CP_WHITE);
    CAdjustVividHueSat(_BLUE, stOsdUserData.VividICMBlueHue, stOsdUserData.VividICMBlueSat);
}

void COsdRightICMModeUserBlueSatAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividICMBlueSat = COsdFxDetOverRange(stOsdUserData.VividICMBlueSat, _ICM_BLUE_SAT_MAX, _ICM_BLUE_SAT_MIN, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividICMBlueSat, _ICM_BLUE_SAT_MAX, _ICM_BLUE_SAT_MIN, _CP_BLUE, _CP_WHITE);
    CAdjustVividHueSat(_BLUE, stOsdUserData.VividICMBlueHue, stOsdUserData.VividICMBlueSat);
}

void COsdExitICMModeUserBlueSatAdj(void)
{
    COsdMenuICMModeUserBlueSatAdj();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Contrast" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuVividContrast(void)
{
    ucOsdState = _MENU_VIVID_CONTRAST_ADJ;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividContrast, _VIVID_CONTRAST_MAX, _VIVID_CONTRAST_MIN, _CP_WHITE, _CP_WHITE);
}

void COsdLeftVividContrast(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(13), COL(3), _MENU_VIVID_BRIGHTNESS);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdRightVividContrast(void)
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_ICM_MODE);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(9), (GET_ICM_MODE()), tVIVID_COLOR_TABLE[3]);
}

void COsdExitVividContrast(void)
{
    COsdMenuSpecial();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Contrast Adjust" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuVividContrastAdj(void)
{
    ucOsdState = _MENU_VIVID_CONTRAST;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 20, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftVividContrastAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividContrast = COsdFxDetOverRange(stOsdUserData.VividContrast, _VIVID_CONTRAST_MAX, _VIVID_CONTRAST_MIN, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividContrast, _VIVID_CONTRAST_MAX, _VIVID_CONTRAST_MIN, _CP_WHITE, _CP_WHITE);
    CAdjustHLWindowContrast(_ENABLE, stOsdUserData.VividContrast);
}

void COsdRightVividContrastAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividContrast = COsdFxDetOverRange(stOsdUserData.VividContrast, _VIVID_CONTRAST_MAX, _VIVID_CONTRAST_MIN, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividContrast, _VIVID_CONTRAST_MAX, _VIVID_CONTRAST_MIN, _CP_WHITE, _CP_WHITE);
    CAdjustHLWindowContrast(_ENABLE, stOsdUserData.VividContrast);
}

void COsdExitVividContrastAdj(void)
{
    COsdMenuVividContrastAdj();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Brightness" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuVividBrightness(void)
{
    ucOsdState = _MENU_VIVID_BRIGHTNESS_ADJ;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividBright, _VIVID_BRIGHTNESS_MAX, _VIVID_BRIGHTNESS_MIN, _CP_WHITE, _CP_WHITE);
}

void COsdLeftVividBrightness(void)
{
    COsdDispPenPoint(ROW(13), COL(3), ROW(5), COL(3), _MENU_COLOR_WINODW_SIZE);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

    COsdDispClearText(ROW(19), COL(9), 16, 1);
    COsdFxLoadText(ROW(19), COL(9), (GET_WINDOW_SIZE()), tVIVID_COLOR_TABLE[1]);
}

void COsdRightVividBrightness(void)
{
    COsdDispPenPoint(ROW(13), COL(3), ROW(11), COL(3), _MENU_VIVID_CONTRAST);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

void COsdExitVividBrightness(void)
{
    COsdMenuSpecial();
}

//----------------------------------------------------------------------------------------------------
// OSD "Vivid Color Brightness Adjust" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuVividBrightnessAdj(void)
{
    ucOsdState = _MENU_VIVID_BRIGHTNESS;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 20, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftVividBrightnessAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividBright = COsdFxDetOverRange(stOsdUserData.VividBright, _VIVID_BRIGHTNESS_MAX, _VIVID_BRIGHTNESS_MIN, _DET_OVERRANGE_MAX);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividBright, _VIVID_BRIGHTNESS_MAX, _VIVID_BRIGHTNESS_MIN, _CP_WHITE, _CP_WHITE);
    CAdjustHLWindowBrightness(_ENABLE, stOsdUserData.VividBright);
}

void COsdRightVividBrightnessAdj(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.VividBright = COsdFxDetOverRange(stOsdUserData.VividBright, _VIVID_BRIGHTNESS_MAX, _VIVID_BRIGHTNESS_MIN, _DET_OVERRANGE_MIN);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.VividBright, _VIVID_BRIGHTNESS_MAX, _VIVID_BRIGHTNESS_MIN, _CP_WHITE, _CP_WHITE);
    CAdjustHLWindowBrightness(_ENABLE, stOsdUserData.VividBright);
}

void COsdExitVividBrightnessAdj(void)
{
    COsdMenuVividBrightnessAdj();
}


#endif // End of #if(_VIVID_COLOR_FUCTION == _ON)


#if(_NON_LINEAR_SCALING_FUCTION == _ON)
//----------------------------------------------------------------------------------------------------
// OSD "NonLinear Scaling" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuNonLinearScaling(void)
{
    if(GET_NON_LINEAR_SCALING_STATUS())
    {
        CLR_NON_LINEAR_SCALING_STATUS();
    }
    else
    {
        SET_NON_LINEAR_SCALING_STATUS();
    }

#if(_AUDIO_SUPPORT == _ON)
    COsdFxLoadText(ROW(19), COL(10), (GET_NON_LINEAR_SCALING_STATUS()), tOSD_AUDIO_TABLE[2]);
#endif

    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    CModeResetMode();
}

void COsdLeftNonLinearScaling(void)
{
    COsdDispClearText(ROW(19), COL(10), LENGTH(5), 1);

#if(_ASPECT_RATIO_SUPPORT == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_ASPECT_RATIO);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(8), (GET_DISP_RATIO()), tOSD_ASPECT_RATIO_TYPE_STR);

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
/*
#elif(_VIVID_COLOR_FUCTION == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_VIVID_COLOR);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#elif(_SRGB_COLOR_ENHANCE == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(11), COL(3), _MENU_SRGB);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
*/
#elif(_SRGB_COLOR_ENHANCE == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(11), COL(3), _MENU_SRGB);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#elif(_COLOR_FORMAT_CONVERT == _ON)
if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) || (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(13), COL(3), _MENU_RGB_YUV);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}
#elif(_VIVID_COLOR_FUCTION == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_VIVID_COLOR);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
// V012 Modify 20100304 End

#endif

}

void COsdRightNonLinearScaling(void)
{
    COsdDispClearText(ROW(19), COL(10), LENGTH(5), 1);

#if(_VIVID_COLOR_FUCTION == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_VIVID_COLOR);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
/*
#elif(_ASPECT_RATIO_SUPPORT == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_ASPECT_RATIO);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(8), (GET_DISP_RATIO()), tOSD_ASPECT_RATIO_TYPE_STR);
#elif(_SRGB_COLOR_ENHANCE == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(11), COL(3), _MENU_SRGB);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
*/
#elif(_COLOR_FORMAT_CONVERT == _ON)
if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) || (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(13), COL(3), _MENU_RGB_YUV);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}
#elif(_SRGB_COLOR_ENHANCE == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(11), COL(3), _MENU_SRGB);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#elif(_ASPECT_RATIO_SUPPORT == _ON)
    COsdDispPenPoint(ROW(7), COL(3), ROW(9), COL(3), _MENU_ASPECT_RATIO);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(8), (GET_DISP_RATIO()), tOSD_ASPECT_RATIO_TYPE_STR);
// V012 Modify 20100304 End

#endif

}

void COsdExitNonLinearScaling(void)
{
    COsdFxCloseWindow(WINNO(2));
    COsdDispDrawInitWindow();
    ucOsdState = _MENU_AUTO_ADJUST_SETTING;

#if(_AUDIO_SUPPORT == _ON)
    COsdFxLoadIcon(ROW(15), COL(3), tOSD_POINT_ICO);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#else

    COsdFxLoadIcon(ROW(15), COL(3), tOSD_POINT_ICO);

    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#endif // End of #if(_AUDIO_SUPPORT==_ON)

}

#endif // End of #if(_NON_LINEAR_SCALING_FUCTION == _ON)


#if(_ASPECT_RATIO_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// OSD "NonLinear Scaling" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuAspectRatio(void)
{
#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
    if(GET_DISP_RATIO() == DISP_FULL_SCREEN)
    {
        SET_DISP_RATIO(DISP_ORIGINAL_SIZE);
    }
    else if(GET_DISP_RATIO() == DISP_ORIGINAL_SIZE)
    {
        SET_DISP_RATIO(DISP_FIXED_AR_IN);
    }
    else
    {
        SET_DISP_RATIO(DISP_FULL_SCREEN);
    }

    CEepromSaveSystemData();


    CModeResetMode();

#else

    if(GET_DISP_RATIO() == _ON)
    {
        SET_DISP_RATIO(_OFF);
    }
    else
    {
        SET_DISP_RATIO(_ON);
    }

    CAdjustBackgroundColor(0, 0, 0);
    CScalerSetBit(_VDISP_CTRL_28, 0x5f, 0x20);
    CModeSetDHWidthToDisplay();
    CTimerDelayXms(100);
    CScalerSetBit(_VDISP_CTRL_28, 0x5f, 0x00);
    COsdFxLoadText(ROW(19), COL(8), (GET_DISP_RATIO()), tOSD_ASPECT_RATIO_TYPE_STR);

#endif

}

void COsdLeftAspectRatio(void)
{
    COsdDispClearText(ROW(19), COL(5), LENGTH(15), 1);

#if (_SRGB_COLOR_ENHANCE == _ON)

    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_SRGB);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#elif(_COLOR_FORMAT_CONVERT == _ON)
if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) || (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(13), COL(3), _MENU_RGB_YUV);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}
// V012 Modify 20100304 End

#elif(_VIVID_COLOR_FUCTION == _ON)

    COsdDispPenPoint(ROW(9), COL(3), ROW(5), COL(3), _MENU_VIVID_COLOR);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#elif(_NON_LINEAR_SCALING_FUCTION == _ON)

    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_NONLINEAR_SCALING);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(10), (GET_NON_LINEAR_SCALING_STATUS()), tOSD_AUDIO_TABLE[2]);

#endif
}

void COsdRightAspectRatio(void)
{
    COsdDispClearText(ROW(19), COL(5), LENGTH(15), 1);

#if(_NON_LINEAR_SCALING_FUCTION == _ON)
    COsdDispPenPoint(ROW(9), COL(3), ROW(7), COL(3), _MENU_NONLINEAR_SCALING);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(10), (GET_NON_LINEAR_SCALING_STATUS()), tOSD_AUDIO_TABLE[2]);
#elif(_VIVID_COLOR_FUCTION == _ON)
    COsdDispPenPoint(ROW(9), COL(3), ROW(5), COL(3), _MENU_VIVID_COLOR);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#elif(_COLOR_FORMAT_CONVERT == _ON)
if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) || (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
{
    COsdDispPenPoint(ROW(9), COL(3), ROW(13), COL(3), _MENU_RGB_YUV);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}
// V012 Modify 20100304 End

#elif (_SRGB_COLOR_ENHANCE == _ON)
    COsdDispPenPoint(ROW(9), COL(3), ROW(11), COL(3), _MENU_SRGB);
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif



}

void COsdExitAspectRatio(void)
{
    COsdFxCloseWindow(WINNO(2));
    COsdDispDrawInitWindow();
    ucOsdState = _MENU_AUTO_ADJUST_SETTING;

#if(_AUDIO_SUPPORT == _ON)
    COsdFxLoadIcon(ROW(15), COL(3), tOSD_POINT_ICO);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#else

    COsdFxLoadIcon(ROW(15), COL(3), tOSD_POINT_ICO);

    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif // End of #if(_AUDIO_SUPPORT==_ON)

}

#endif // End of #if(_ASPECT_RATIO_SUPPORT == _ON)

#if (_SRGB_COLOR_ENHANCE == _ON)

void COsdMenuSrgb(void)
{
    BYTE temp;

    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 20, 15);

    for(temp = 0; temp < 2; temp++)
    {
        COsdFxLoadText(ROW(5 + temp*2), COL(7), stOsdUserData.Language, tOSD_SRGB_FUCTION_TABLE[temp]);
    }

    COsdDispPenPoint(ROW(5), COL(3), ROW(5), COL(3), _MENU_HUE);
    COsdFxDrawWindow(XSTART(40), YSTART(300), XEND(250), YEND(400), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_BLACK), tOSD_WINDOW2_STYLE);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}
void COsdLeftSrgb(void)
{
    COsdDispClearText(ROW(19), COL(5), LENGTH(15), 1);

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
/*
#if(_VIVID_COLOR_FUCTION == _ON)
*/
#if(_COLOR_FORMAT_CONVERT == _ON)
if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) || (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(13), COL(3), _MENU_RGB_YUV);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}
#elif(_VIVID_COLOR_FUCTION == _ON)
// V012 Modify 20100304 End

    COsdDispPenPoint(ROW(11), COL(3), ROW(5), COL(3), _MENU_VIVID_COLOR);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#elif(_NON_LINEAR_SCALING_FUCTION == _ON)
    COsdDispPenPoint(ROW(11), COL(3), ROW(7), COL(3), _MENU_NONLINEAR_SCALING);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(10), (GET_NON_LINEAR_SCALING_STATUS()), tOSD_AUDIO_TABLE[2]);

#elif(_ASPECT_RATIO_SUPPORT == _ON)
    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_ASPECT_RATIO);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(8), (GET_DISP_RATIO()), tOSD_ASPECT_RATIO_TYPE_STR);

#endif

}
void COsdRightSrgb(void)
{
    COsdDispClearText(ROW(19), COL(5), LENGTH(15), 1);

#if(_ASPECT_RATIO_SUPPORT == _ON)

    COsdDispPenPoint(ROW(11), COL(3), ROW(9), COL(3), _MENU_ASPECT_RATIO);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(8), (GET_DISP_RATIO()), tOSD_ASPECT_RATIO_TYPE_STR);

#elif(_NON_LINEAR_SCALING_FUCTION == _ON)

    COsdDispPenPoint(ROW(11), COL(3), ROW(7), COL(3), _MENU_NONLINEAR_SCALING);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(10), (GET_NON_LINEAR_SCALING_STATUS()), tOSD_AUDIO_TABLE[2]);

#elif(_VIVID_COLOR_FUCTION == _ON)

    COsdDispPenPoint(ROW(11), COL(3), ROW(5), COL(3), _MENU_VIVID_COLOR);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#elif(_COLOR_FORMAT_CONVERT == _ON)
if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) || (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
{
    COsdDispPenPoint(ROW(11), COL(3), ROW(13), COL(3), _MENU_RGB_YUV);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}
// V012 Modify 20100304 End

#endif
}
void COsdExitSrgb(void)
{
    COsdFxCloseWindow(WINNO(2));
    COsdDispDrawInitWindow();
    ucOsdState = _MENU_AUTO_ADJUST_SETTING;

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
/*
#if(_AUDIO_SUPPORT == _ON)

    COsdFxLoadIcon(ROW(15), COL(3), tOSD_POINT_ICO);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#else

    COsdFxLoadIcon(ROW(13), COL(3), tOSD_POINT_ICO);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif // End of #if(_AUDIO_SUPPORT==_ON)
*/
    COsdFxLoadIcon(ROW(15), COL(3), tOSD_POINT_ICO);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
// V012 Modify 20100304 End

}


//----------------------------------------------------------------------------------------------------
// OSD "Contrast" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuHue(void)
{
    ucOsdState = _MENU_SUB_HUE;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.Hue, _HUE_MAX - _HUE_MIN, _HUE_MIN, _CP_WHITE, _CP_WHITE);
}

void COsdLeftHue(void)
{
    COsdDispPenPoint(ROW(5), COL(3), ROW(7), COL(3), _MENU_SATURATION);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightHue(void)
{
    COsdLeftHue();

}

void COsdExitHue(void)
{
    COsdMenuSpecial();
}

//----------------------------------------------------------------------------------------------------
// OSD "subContrast" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubHue(void)
{
    ucOsdState = _MENU_HUE;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 12, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftSubHue(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.Hue = COsdFxDetOverRange(stOsdUserData.Hue, _HUE_MAX, _HUE_MIN, _DET_OVERRANGE_MAX);
    CAdjustSaturationHue(stOsdUserData.Hue, _FALSE);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.Hue, _HUE_MAX - _HUE_MIN, _HUE_MIN, _CP_WHITE, _CP_WHITE);
}

void COsdRightSubHue(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.Hue = COsdFxDetOverRange(stOsdUserData.Hue, _HUE_MAX, _HUE_MIN, _DET_OVERRANGE_MIN);
    CAdjustSaturationHue(stOsdUserData.Hue, _FALSE);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.Hue, _HUE_MAX - _HUE_MIN, _HUE_MIN, _CP_WHITE, _CP_WHITE);
}

void COsdExitSubHue(void)
{
    ucOsdState = _MENU_HUE;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 15, 2);
    CLR_KEYREPEATENABLE();
}


//----------------------------------------------------------------------------------------------------
// OSD "Brightness" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSaturation(void)
{
    ucOsdState = _MENU_SUB_SATURATION;
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.Sat, _SATURATION_MAX - _SATURATION_MIN, _SATURATION_MIN, _CP_WHITE, _CP_WHITE);

}

void COsdLeftSaturation(void)
{
    COsdDispPenPoint(ROW(7), COL(3), ROW(5), COL(3), _MENU_HUE);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdRightSaturation(void)
{
    COsdLeftSaturation();
}

void COsdExitSaturation(void)
{
    COsdExitHue();
}


//----------------------------------------------------------------------------------------------------
// OSD "SubBrightness" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubSaturation(void)
{
    ucOsdState = _MENU_SATURATION;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 12, 2);
    CLR_KEYREPEATENABLE();
}

void COsdLeftSubSaturation(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.Sat = COsdFxDetOverRange(stOsdUserData.Sat, _SATURATION_MAX, _SATURATION_MIN, _DET_OVERRANGE_MAX);
    CAdjustSaturationHue(stOsdUserData.Sat, _TRUE);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.Sat, _SATURATION_MAX - _SATURATION_MIN, _SATURATION_MIN, _CP_WHITE, _CP_WHITE);
}

void COsdRightSubSaturation(void)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.Sat = COsdFxDetOverRange(stOsdUserData.Sat, _SATURATION_MAX, _SATURATION_MIN, _DET_OVERRANGE_MIN);
    CAdjustSaturationHue(stOsdUserData.Sat, _TRUE);
    COsdDispFullSlider(ROW(19), COL(5), 12, stOsdUserData.Sat, _SATURATION_MAX - _SATURATION_MIN, _SATURATION_MIN, _CP_WHITE, _CP_WHITE);
}

void COsdExitSubSaturation(void)
{
    ucOsdState = _MENU_SATURATION;
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    COsdDispClearText(ROW(18), COL(5), 15, 2);
    CLR_KEYREPEATENABLE();
}
#endif

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#if(_COLOR_FORMAT_CONVERT == _ON)
//----------------------------------------------------------------------------------------------------
// OSD "RGBYUV" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuRGBYUV(void)
{
    COsdFxLoadText(ROW(19), COL(5), stOsdUserData.Language, tOSD_RGBYUV_STR);

    if(GET_COLOR_FORMAT_STATUS())
    {
        COsdDispArrowPoint(ROW(18), COL(13), ROW(18), COL(13), _MENU_SUB_YUV);
    }
    else
    {
        COsdDispArrowPoint(ROW(18), COL(7), ROW(18), COL(7), _MENU_SUB_RGB);
    }
}

void COsdLeftRGBYUV(void)
{
#if(_VIVID_COLOR_FUCTION == _ON)
    COsdDispPenPoint(ROW(13), COL(3), ROW(5), COL(3), _MENU_VIVID_COLOR);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

#elif(_NON_LINEAR_SCALING_FUCTION == _ON)
    COsdDispPenPoint(ROW(13), COL(3), ROW(7), COL(3), _MENU_NONLINEAR_SCALING);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(10), (GET_NON_LINEAR_SCALING_STATUS()), tOSD_AUDIO_TABLE[2]);

#elif(_ASPECT_RATIO_SUPPORT == _ON)
    COsdDispPenPoint(ROW(13), COL(3), ROW(9), COL(3), _MENU_ASPECT_RATIO);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(8), (GET_DISP_RATIO()), tOSD_ASPECT_RATIO_TYPE_STR);

#elif(_SRGB_COLOR_ENHANCE == _ON)
    COsdDispPenPoint(ROW(13), COL(3), ROW(11), COL(3), _MENU_SRGB);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
#endif

}

void COsdRightRGBYUV(void)
{
#if(_SRGB_COLOR_ENHANCE == _ON)
    COsdDispPenPoint(ROW(13), COL(3), ROW(11), COL(3), _MENU_SRGB);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));

#elif(_ASPECT_RATIO_SUPPORT == _ON)
    COsdDispPenPoint(ROW(13), COL(3), ROW(9), COL(3), _MENU_ASPECT_RATIO);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(9), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(8), (GET_DISP_RATIO()), tOSD_ASPECT_RATIO_TYPE_STR);

#elif(_NON_LINEAR_SCALING_FUCTION == _ON)
    COsdDispPenPoint(ROW(13), COL(3), ROW(7), COL(3), _MENU_NONLINEAR_SCALING);
    COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
    COsdFxLoadText(ROW(19), COL(10), (GET_NON_LINEAR_SCALING_STATUS()), tOSD_AUDIO_TABLE[2]);

#elif(_VIVID_COLOR_FUCTION == _ON)
    COsdDispPenPoint(ROW(13), COL(3), ROW(5), COL(3), _MENU_VIVID_COLOR);
    COsdFxChange1bitColor(ROW(13), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
#endif

}

void COsdExitRGBYUV(void)
{
    COsdFxCloseWindow(WINNO(2));
    COsdDispDrawInitWindow();
    ucOsdState = _MENU_AUTO_ADJUST_SETTING;

    COsdFxLoadIcon(ROW(15), COL(3), tOSD_POINT_ICO);
    COsdFxChange1bitColor(ROW(15), COL(5), WIDTH(15), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));
}

//----------------------------------------------------------------------------------------------------
// OSD "SUB RGB" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubRGB(void)
{
    SET_COLOR_FORMAT_STATUS(_RGB_COLOR_FORMAT);

    // V014 VGA Patch Note (6) Modify 20100527 Start
    // Patch Reason : Modify Video Mode Can't Light On
    SET_MODE_COLOR_FORMAT_FLAG(_RGB_COLOR_FORMAT);
    // V014 VGA Patch Note (6) Modify 20100527 End

    CEepromSaveSystemData();

    // V014 VGA Patch Note (6) Modify 20100527 Start
    // Patch Reason : Modify Video Mode Can't Light On
    CEepromSaveModeData(stModeInfo.ModeCurr);
    // V014 VGA Patch Note (6) Modify 20100527 End

    COsdDispClearText(ROW(18), COL(5), 17, 4);
    ucOsdState = _MENU_RGB_YUV;

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
    CModeOverScan();
#endif
// V012 Modify 20100316 End

    // V015 VGA Patch Note (12) Modify 20100625 Start
    // Patch Reason : Modify OSD Reslotion show type for vedio timing.
    COsdDispClearText(ROW(23), COL(5), WIDTH(20), HEIGHT(1));
    COSDDispTimingInfoStyle();
    // V015 VGA Patch Note (12) Modify 20100625 End
}

void COsdLeftSubRGB(void)
{
    COsdDispArrowPoint(ROW(18), COL(7), ROW(18), COL(13), _MENU_SUB_YUV);
}

void COsdRightSubRGB(void)
{
    COsdDispArrowPoint(ROW(18), COL(7), ROW(18), COL(13), _MENU_SUB_YUV);
}

void COsdExitSubRGB(void)
{
    COsdDispClearText(ROW(18), COL(5), 17, 4);
    ucOsdState = _MENU_RGB_YUV;
}

//----------------------------------------------------------------------------------------------------
// OSD "SUB YUV" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuSubYUV(void)
{
    SET_COLOR_FORMAT_STATUS(_YUV_COLOR_FORMAT);

    // V014 VGA Patch Note (6) Modify 20100527 Start
    // Patch Reason : Modify Video Mode Can't Light On
    SET_MODE_COLOR_FORMAT_FLAG(_YUV_COLOR_FORMAT);
    // V014 VGA Patch Note (6) Modify 20100527 End

    CEepromSaveSystemData();

    // V014 VGA Patch Note (6) Modify 20100527 Start
    // Patch Reason : Modify Video Mode Can't Light On
    CEepromSaveModeData(stModeInfo.ModeCurr);
    // V014 VGA Patch Note (6) Modify 20100527 End

    COsdDispClearText(ROW(18), COL(5), 17, 4);
    ucOsdState = _MENU_RGB_YUV;

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
    CModeOverScan();
#endif
// V012 Modify 20100316 End

    // V015 VGA Patch Note (12) Modify 20100625 Start
    // Patch Reason : Modify OSD Reslotion show type for vedio timing.
    COsdDispClearText(ROW(23), COL(5), WIDTH(20), HEIGHT(1));
    COSDDispTimingInfoStyle();
    // V015 VGA Patch Note (12) Modify 20100625 End
}

void COsdLeftSubYUV(void)
{
    COsdDispArrowPoint(ROW(18), COL(13), ROW(18), COL(7), _MENU_SUB_RGB);
}

void COsdRightSubYUV(void)
{
    COsdDispArrowPoint(ROW(18), COL(13), ROW(18), COL(7), _MENU_SUB_RGB);
}

void COsdExitSubYUV(void)
{
    COsdDispClearText(ROW(18), COL(5), 17, 4);
    ucOsdState = _MENU_RGB_YUV;
}
#endif  // End of #if(_COLOR_FORMAT_CONVERT == _ON)
// V012 Modify 20100304 End

//----------------------------------------------------------------------------------------------------
// OSD "Factory Mode ITEM" Operation
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
// OSD "FAutoColor" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFAutoColor(void)
{
    CAutoDoWhiteBalance();
    COsdDispShowFactoryModeValue();
}

void COsdLeftFAutoColor(void)
{
    COsdDispWindowPoint(1, _MENU_F_RESET);
}

void COsdRightFAutoColor(void)
{
    COsdDispWindowPoint(11, _MENU_F_EXIT);
}

void COsdExitFAutoColor(void)
{

}

//----------------------------------------------------------------------------------------------------
// OSD "FReset" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFReset(void)
{

}

void COsdLeftFReset(void)
{
    COsdDispWindowPoint(2, _MENU_F_OFFSET);
}

void COsdRightFReset(void)
{
    COsdDispWindowPoint(0, _MENU_F_AUTOCOLOR);
}

void COsdExitFReset(void)
{

}

//----------------------------------------------------------------------------------------------------
// OSD "FOffset" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFOffset(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 0, 12, _MENU_F_OFFSET_R);
}

void COsdLeftFOffset(void)
{
    COsdDispWindowPoint(3, _MENU_F_GAIN);
}

void COsdRightFOffset(void)
{
    COsdDispWindowPoint(1, _MENU_F_RESET);
}

void COsdExitFOffset(void)
{

}

//----------------------------------------------------------------------------------------------------
// OSD "FOffsetR" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFOffsetR(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 0, 50, _MENU_F_OFFSET_R_ADJ);
}

void COsdLeftFOffsetR(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 1, 12, _MENU_F_OFFSET_G);
}

void COsdRightFOffsetR(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 2, 12, _MENU_F_OFFSET_B);
}

void COsdExitFOffsetR(void)
{
    COsdFxCloseWindow(WINNO(2));
    ucOsdState = _MENU_F_OFFSET;
}

//----------------------------------------------------------------------------------------------------
// OSD "FOffsetR adj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFOffsetRAdj(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 0, 12, _MENU_F_OFFSET_R);
    ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
}

void COsdLeftFOffsetRAdj(void)
{
    stAdcData.AdcOffset[_RED] = COsdFxDetOverRange(stAdcData.AdcOffset[_RED], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(5), COL(17), stAdcData.AdcOffset[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustAdcOffset();
}

void COsdRightFOffsetRAdj(void)
{
    stAdcData.AdcOffset[_RED] = COsdFxDetOverRange(stAdcData.AdcOffset[_RED], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(5), COL(17), stAdcData.AdcOffset[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustAdcOffset();
}

void COsdExitFOffsetRAdj(void)
{
    COsdExitFOffsetR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FOffsetG" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFOffsetG(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 1, 50, _MENU_F_OFFSET_G_ADJ);
}

void COsdLeftFOffsetG(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 2, 12, _MENU_F_OFFSET_B);
}

void COsdRightFOffsetG(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 0, 12, _MENU_F_OFFSET_R);
}

void COsdExitFOffsetG(void)
{
    COsdExitFOffsetR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FOffsetG adj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFOffsetGAdj(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 1, 12, _MENU_F_OFFSET_G);
    ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
}

void COsdLeftFOffsetGAdj(void)
{
    stAdcData.AdcOffset[_GREEN] = COsdFxDetOverRange(stAdcData.AdcOffset[_GREEN], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(5), COL(22), stAdcData.AdcOffset[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustAdcOffset();
}

void COsdRightFOffsetGAdj(void)
{
    stAdcData.AdcOffset[_GREEN] = COsdFxDetOverRange(stAdcData.AdcOffset[_GREEN], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(5), COL(22), stAdcData.AdcOffset[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustAdcOffset();
}

void COsdExitFOffsetGAdj(void)
{
    COsdExitFOffsetR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FOffsetB" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFOffsetB(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 2, 50, _MENU_F_OFFSET_B_ADJ);
}

void COsdLeftFOffsetB(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 0, 12, _MENU_F_OFFSET_R);
}

void COsdRightFOffsetB(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 1, 12, _MENU_F_OFFSET_G);
}

void COsdExitFOffsetB(void)
{
    COsdExitFOffsetR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FOffsetBAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFOffsetBAdj(void)
{
    COsdDispWindowHPoint(ROW(2), 154, 60, 2, 12, _MENU_F_OFFSET_B);
    ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
}

void COsdLeftFOffsetBAdj(void)
{
    stAdcData.AdcOffset[_BLUE] = COsdFxDetOverRange(stAdcData.AdcOffset[_BLUE], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(5), COL(27), stAdcData.AdcOffset[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustAdcOffset();
}

void COsdRightFOffsetBAdj(void)
{
    stAdcData.AdcOffset[_BLUE] = COsdFxDetOverRange(stAdcData.AdcOffset[_BLUE], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(5), COL(27), stAdcData.AdcOffset[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustAdcOffset();
}

void COsdExitFOffsetBAdj(void)
{
    COsdExitFOffsetR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FGain" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFGain(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 0, 12, _MENU_F_GAIN_R);
}

void COsdLeftFGain(void)
{
    COsdDispWindowPoint(4, _MENU_F_COLOR9300);
    SET_COLOR_TEMP_TYPE(_CT_9300);
    COsdDispColorTempSelect();
}

void COsdRightFGain(void)
{
    COsdDispWindowPoint(2, _MENU_F_OFFSET);
}

void COsdExitFGain(void)
{

}

//----------------------------------------------------------------------------------------------------
// OSD "FGainR" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFGainR(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 0, 50, _MENU_F_GAIN_R_ADJ);
    ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
}

void COsdLeftFGainR(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 1, 12, _MENU_F_GAIN_G);
}

void COsdRightFGainR(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 2, 12, _MENU_F_GAIN_B);
}

void COsdExitFGainR(void)
{
    COsdFxCloseWindow(WINNO(2));
    ucOsdState = _MENU_F_GAIN;
}

//----------------------------------------------------------------------------------------------------
// OSD "FGainRAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFGainRAdj(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 0, 12, _MENU_F_GAIN_R);
    ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
}

void COsdLeftFGainRAdj(void)
{
    stAdcData.AdcGain[_RED] = COsdFxDetOverRange(stAdcData.AdcGain[_RED], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(7), COL(16), stAdcData.AdcGain[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustAdcGain();
}

void COsdRightFGainRAdj(void)
{
    stAdcData.AdcGain[_RED] = COsdFxDetOverRange(stAdcData.AdcGain[_RED], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(7), COL(16), stAdcData.AdcGain[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustAdcGain();
}

void COsdExitFGainRAdj(void)
{
    COsdExitFGainR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FGainG" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFGainG(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 1, 50, _MENU_F_GAIN_G_ADJ);
}

void COsdLeftFGainG(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 2, 12, _MENU_F_GAIN_B);
}

void COsdRightFGainG(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 0, 12, _MENU_F_GAIN_R);
}

void COsdExitFGainG(void)
{
    COsdExitFGainR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FGainGAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFGainGAdj(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 1, 12, _MENU_F_GAIN_G);
    ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
}

void COsdLeftFGainGAdj(void)
{
    stAdcData.AdcGain[_GREEN] = COsdFxDetOverRange(stAdcData.AdcGain[_GREEN], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(7), COL(21), stAdcData.AdcGain[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustAdcGain();
}

void COsdRightFGainGAdj(void)
{
    stAdcData.AdcGain[_GREEN] = COsdFxDetOverRange(stAdcData.AdcGain[_GREEN], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(7), COL(21), stAdcData.AdcGain[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustAdcGain();
}

void COsdExitFGainGAdj(void)
{
    COsdExitFGainR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FGainB" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFGainB(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 2, 50, _MENU_F_GAIN_B_ADJ);
}

void COsdLeftFGainB(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 0, 12, _MENU_F_GAIN_R);
}

void COsdRightFGainB(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 1, 12, _MENU_F_GAIN_G);
}

void COsdExitFGainB(void)
{
    COsdExitFGainR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FGainBAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFGainBAdj(void)
{
    COsdDispWindowHPoint(ROW(3), 154, 60, 2, 12, _MENU_F_GAIN_B);
    ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
}

void COsdLeftFGainBAdj(void)
{
    stAdcData.AdcGain[_BLUE] = COsdFxDetOverRange(stAdcData.AdcGain[_BLUE], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(7), COL(26), stAdcData.AdcGain[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustAdcGain();
}

void COsdRightFGainBAdj(void)
{
    stAdcData.AdcGain[_BLUE] = COsdFxDetOverRange(stAdcData.AdcGain[_BLUE], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(7), COL(26), stAdcData.AdcGain[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustAdcGain();
}

void COsdExitFGainBAdj(void)
{
    COsdExitFGainR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor9300" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor9300(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 0, 12, _MENU_F_COLOR9300_R);
}

void COsdLeftFColor9300(void)
{
    COsdDispWindowPoint(5, _MENU_F_COLOR6500);
    SET_COLOR_TEMP_TYPE(_CT_6500);
    COsdDispColorTempSelect();
}

void COsdRightFColor9300(void)
{
    COsdDispWindowPoint(3, _MENU_F_GAIN);
    CEepromLoadSystemData();

    COsdDispColorTempSelect();
}

void COsdExitFColor9300(void)
{

}

//----------------------------------------------------------------------------------------------------
// OSD "FColor9300R" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor9300R(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 0, 50, _MENU_F_COLOR9300_R_ADJ);
}

void COsdLeftFColor9300R(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 1, 12, _MENU_F_COLOR9300_G);
}

void COsdRightFColor9300R(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 2, 12, _MENU_F_COLOR9300_B);
}

void COsdExitFColor9300R(void)
{
    COsdFxCloseWindow(WINNO(2));
    ucOsdState = _MENU_F_COLOR9300;
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor9300RAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor9300RAdj(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 0, 12, _MENU_F_COLOR9300_R);
}

void COsdLeftFColor9300RAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_9300);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_RED] = COsdFxDetOverRange(stColorTempData.ColorTemp[_RED], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(9), COL(16), stColorTempData.ColorTemp[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFColor9300RAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_9300);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_RED] = COsdFxDetOverRange(stColorTempData.ColorTemp[_RED], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(9), COL(16), stColorTempData.ColorTemp[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFColor9300RAdj(void)
{
    COsdExitFColor9300R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor9300G" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor9300G(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 1, 50, _MENU_F_COLOR9300_G_ADJ);
}

void COsdLeftFColor9300G(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 2, 12, _MENU_F_COLOR9300_B);
}

void COsdRightFColor9300G(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 0, 12, _MENU_F_COLOR9300_R);
}

void COsdExitFColor9300G(void)
{
    COsdExitFColor9300R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor9300GAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor9300GAdj(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 1, 12, _MENU_F_COLOR9300_G);
}

void COsdLeftFColor9300GAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_9300);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_GREEN] = COsdFxDetOverRange(stColorTempData.ColorTemp[_GREEN], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(9), COL(21), stColorTempData.ColorTemp[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFColor9300GAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_9300);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_GREEN] = COsdFxDetOverRange(stColorTempData.ColorTemp[_GREEN], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(9), COL(21), stColorTempData.ColorTemp[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFColor9300GAdj(void)
{
    COsdExitFColor9300R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor9300B" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor9300B(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 2, 50, _MENU_F_COLOR9300_B_ADJ);
}

void COsdLeftFColor9300B(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 0, 12, _MENU_F_COLOR9300_R);
}

void COsdRightFColor9300B(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 1, 12, _MENU_F_COLOR9300_G);
}

void COsdExitFColor9300B(void)
{
    COsdExitFColor9300R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor9300BAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor9300BAdj(void)
{
    COsdDispWindowHPoint(ROW(4), 154, 60, 2, 12, _MENU_F_COLOR9300_B);
}

void COsdLeftFColor9300BAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_9300);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_BLUE] = COsdFxDetOverRange(stColorTempData.ColorTemp[_BLUE], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(9), COL(26), stColorTempData.ColorTemp[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFColor9300BAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_9300);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_BLUE] = COsdFxDetOverRange(stColorTempData.ColorTemp[_BLUE], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(9), COL(26), stColorTempData.ColorTemp[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFColor9300BAdj(void)
{
    COsdExitFColor9300R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor6500" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor6500(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 0, 12, _MENU_F_COLOR6500_R);
}

void COsdLeftFColor6500(void)
{
    COsdDispWindowPoint(6, _MENU_F_COLOR5800);
    SET_COLOR_TEMP_TYPE(_CT_5800);
    COsdDispColorTempSelect();
}

void COsdRightFColor6500(void)
{
    COsdDispWindowPoint(4, _MENU_F_COLOR9300);
    SET_COLOR_TEMP_TYPE(_CT_9300);
    COsdDispColorTempSelect();
}

void COsdExitFColor6500(void)
{

}

//----------------------------------------------------------------------------------------------------
// OSD "FColor6500R" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor6500R(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 0, 50, _MENU_F_COLOR6500_R_ADJ);
}

void COsdLeftFColor6500R(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 1, 12, _MENU_F_COLOR6500_G);
}

void COsdRightFColor6500R(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 2, 12, _MENU_F_COLOR6500_B);
}

void COsdExitFColor6500R(void)
{
    COsdFxCloseWindow(WINNO(2));
    ucOsdState = _MENU_F_COLOR6500;
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor6500RAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor6500RAdj(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 0, 12, _MENU_F_COLOR6500_R);
}

void COsdLeftFColor6500RAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_6500);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_RED] = COsdFxDetOverRange(stColorTempData.ColorTemp[_RED], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(11), COL(16), stColorTempData.ColorTemp[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFColor6500RAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_6500);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_RED] = COsdFxDetOverRange(stColorTempData.ColorTemp[_RED], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(11), COL(16), stColorTempData.ColorTemp[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFColor6500RAdj(void)
{
    COsdExitFColor6500R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor6500G" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor6500G(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 1, 50, _MENU_F_COLOR6500_G_ADJ);
}

void COsdLeftFColor6500G(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 2, 12, _MENU_F_COLOR6500_B);
}

void COsdRightFColor6500G(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 0, 12, _MENU_F_COLOR6500_R);
}

void COsdExitFColor6500G(void)
{
    COsdExitFColor6500R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor6500GAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor6500GAdj(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 1, 12, _MENU_F_COLOR6500_G);
}

void COsdLeftFColor6500GAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_6500);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_GREEN] = COsdFxDetOverRange(stColorTempData.ColorTemp[_GREEN], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(11), COL(21), stColorTempData.ColorTemp[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFColor6500GAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_6500);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_GREEN] = COsdFxDetOverRange(stColorTempData.ColorTemp[_GREEN], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(11), COL(21), stColorTempData.ColorTemp[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFColor6500GAdj(void)
{
    COsdExitFColor6500R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor6500B" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor6500B(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 2, 50, _MENU_F_COLOR6500_B_ADJ);
}

void COsdLeftFColor6500B(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 0, 12, _MENU_F_COLOR6500_R);
}

void COsdRightFColor6500B(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 1, 12, _MENU_F_COLOR6500_G);
}

void COsdExitFColor6500B(void)
{
    COsdExitFColor6500R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor6500BAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor6500BAdj(void)
{
    COsdDispWindowHPoint(ROW(5), 154, 60, 2, 12, _MENU_F_COLOR6500_B);
}

void COsdLeftFColor6500BAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_6500);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_BLUE] = COsdFxDetOverRange(stColorTempData.ColorTemp[_BLUE], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(11), COL(26), stColorTempData.ColorTemp[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFColor6500BAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_6500);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_BLUE] = COsdFxDetOverRange(stColorTempData.ColorTemp[_BLUE], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(11), COL(26), stColorTempData.ColorTemp[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFColor6500BAdj(void)
{
    COsdExitFColor6500R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor5800" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor5800(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 0, 12, _MENU_F_COLOR5800_R);
}

void COsdLeftFColor5800(void)
{
    COsdDispWindowPoint(7, _MENU_F_SRGB);
    SET_COLOR_TEMP_TYPE(_CT_SRGB);
    COsdDispColorTempSelect();
}

void COsdRightFColor5800(void)
{
    COsdDispWindowPoint(5, _MENU_F_COLOR6500);
    SET_COLOR_TEMP_TYPE(_CT_6500);
    COsdDispColorTempSelect();
}

void COsdExitFColor5800(void)
{

}

//----------------------------------------------------------------------------------------------------
// OSD "FColor5800R" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor5800R(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 0, 50, _MENU_F_COLOR5800_R_ADJ);
}

void COsdLeftFColor5800R(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 1, 12, _MENU_F_COLOR5800_G);
}

void COsdRightFColor5800R(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 2, 12, _MENU_F_COLOR5800_B);
}

void COsdExitFColor5800R(void)
{
    COsdFxCloseWindow(WINNO(2));
    ucOsdState = _MENU_F_COLOR5800;
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor5800RAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor5800RAdj(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 0, 12, _MENU_F_COLOR5800_R);
}

void COsdLeftFColor5800RAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_5800);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_RED] = COsdFxDetOverRange(stColorTempData.ColorTemp[_RED], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(13), COL(16), stColorTempData.ColorTemp[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFColor5800RAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_5800);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_RED] = COsdFxDetOverRange(stColorTempData.ColorTemp[_RED], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(13), COL(16), stColorTempData.ColorTemp[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFColor5800RAdj(void)
{
    COsdExitFColor5800R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor5800G" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor5800G(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 1, 50, _MENU_F_COLOR5800_G_ADJ);
}

void COsdLeftFColor5800G(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 2, 12, _MENU_F_COLOR5800_B);
}

void COsdRightFColor5800G(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 0, 12, _MENU_F_COLOR5800_R);
}

void COsdExitFColor5800G(void)
{
    COsdExitFColor5800R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor5800GAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor5800GAdj(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 1, 12, _MENU_F_COLOR5800_G);
}

void COsdLeftFColor5800GAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_5800);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_GREEN] = COsdFxDetOverRange(stColorTempData.ColorTemp[_GREEN], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(13), COL(21), stColorTempData.ColorTemp[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFColor5800GAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_5800);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_GREEN] = COsdFxDetOverRange(stColorTempData.ColorTemp[_GREEN], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(13), COL(21), stColorTempData.ColorTemp[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFColor5800GAdj(void)
{
    COsdExitFColor5800R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor5800B" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor5800B(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 2, 50, _MENU_F_COLOR5800_B_ADJ);
}

void COsdLeftFColor5800B(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 0, 12, _MENU_F_COLOR5800_R);
}

void COsdRightFColor5800B(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 1, 12, _MENU_F_COLOR5800_G);
}

void COsdExitFColor5800B(void)
{
    COsdExitFColor5800R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FColor5800BAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFColor5800BAdj(void)
{
    COsdDispWindowHPoint(ROW(6), 154, 60, 2, 12, _MENU_F_COLOR5800_B);
}

void COsdLeftFColor5800BAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_5800);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_BLUE] = COsdFxDetOverRange(stColorTempData.ColorTemp[_BLUE], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(13), COL(26), stColorTempData.ColorTemp[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFColor5800BAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_5800);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_BLUE] = COsdFxDetOverRange(stColorTempData.ColorTemp[_BLUE], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(13), COL(26), stColorTempData.ColorTemp[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFColor5800BAdj(void)
{
    COsdExitFColor5800R();
}

//----------------------------------------------------------------------------------------------------
// OSD "FSrgb" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFSrgb(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 0, 12, _MENU_F_SRGB_R);
}

void COsdLeftFSrgb(void)
{
    COsdDispWindowPoint(8, _MENU_F_USER);
    SET_COLOR_TEMP_TYPE(_CT_USER);
    COsdDispColorTempSelect();
}

void COsdRightFSrgb(void)
{
    COsdDispWindowPoint(6, _MENU_F_COLOR5800);
    SET_COLOR_TEMP_TYPE(_CT_5800);
    COsdDispColorTempSelect();
}

void COsdExitFSrgb(void)
{

}

//----------------------------------------------------------------------------------------------------
// OSD "FSrgbR" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFSrgbR(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 0, 50, _MENU_F_SRGB_R_ADJ);
}

void COsdLeftFSrgbR(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 1, 12, _MENU_F_SRGB_G);
}

void COsdRightFSrgbR(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 2, 12, _MENU_F_SRGB_B);
}

void COsdExitFSrgbR(void)
{
    COsdFxCloseWindow(WINNO(2));
    ucOsdState = _MENU_F_SRGB;
}

//----------------------------------------------------------------------------------------------------
// OSD "FSrgbRAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFSrgbRAdj(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 0, 12, _MENU_F_SRGB_R);
}

void COsdLeftFSrgbRAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_SRGB);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_RED] = COsdFxDetOverRange(stColorTempData.ColorTemp[_RED], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(15), COL(15), stColorTempData.ColorTemp[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFSrgbRAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_SRGB);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_RED] = COsdFxDetOverRange(stColorTempData.ColorTemp[_RED], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(15), COL(15), stColorTempData.ColorTemp[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFSrgbRAdj(void)
{
    COsdExitFSrgbR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FSrgbG" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFSrgbG(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 1, 50, _MENU_F_SRGB_G_ADJ);
}

void COsdLeftFSrgbG(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 2, 12, _MENU_F_SRGB_B);
}

void COsdRightFSrgbG(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 0, 12, _MENU_F_SRGB_R);
}

void COsdExitFSrgbG(void)
{
    COsdExitFSrgbR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FSrgbGAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFSrgbGAdj(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 1, 12, _MENU_F_SRGB_G);
}

void COsdLeftFSrgbGAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_SRGB);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_GREEN] = COsdFxDetOverRange(stColorTempData.ColorTemp[_GREEN], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(15), COL(20), stColorTempData.ColorTemp[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFSrgbGAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_SRGB);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_GREEN] = COsdFxDetOverRange(stColorTempData.ColorTemp[_GREEN], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(15), COL(20), stColorTempData.ColorTemp[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFSrgbGAdj(void)
{
    COsdExitFSrgbR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FSrgbB" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFSrgbB(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 2, 50, _MENU_F_SRGB_B_ADJ);
}

void COsdLeftFSrgbB(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 0, 12, _MENU_F_SRGB_R);
}

void COsdRightFSrgbB(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 1, 12, _MENU_F_SRGB_G);
}

void COsdExitFSrgbB(void)
{
    COsdExitFSrgbR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FSrgbBAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFSrgbBAdj(void)
{
    COsdDispWindowHPoint(ROW(7), 154, 60, 2, 12, _MENU_F_SRGB_B);
}

void COsdLeftFSrgbBAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_SRGB);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_BLUE] = COsdFxDetOverRange(stColorTempData.ColorTemp[_BLUE], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(15), COL(25), stColorTempData.ColorTemp[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFSrgbBAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_SRGB);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_BLUE] = COsdFxDetOverRange(stColorTempData.ColorTemp[_BLUE], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(15), COL(25), stColorTempData.ColorTemp[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;

}

void COsdExitFSrgbBAdj(void)
{
    COsdExitFSrgbR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FUser" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFUser(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 0, 12, _MENU_F_USER_R);
}

void COsdLeftFUser(void)
{
    COsdDispWindowPoint(9, _MENU_F_BRIGHT);
    CEepromLoadSystemData();

    COsdDispColorTempSelect();
}

void COsdRightFUser(void)
{
    COsdDispWindowPoint(7, _MENU_F_SRGB);
    SET_COLOR_TEMP_TYPE(_CT_SRGB);
    COsdDispColorTempSelect();
}

void COsdExitFUser(void)
{

}

//----------------------------------------------------------------------------------------------------
// OSD "FUserR" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFUserR(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 0, 50, _MENU_F_USER_R_ADJ);
}

void COsdLeftFUserR(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 1, 12, _MENU_F_USER_G);
}

void COsdRightFUserR(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 2, 12, _MENU_F_USER_B);
}

void COsdExitFUserR(void)
{
    COsdFxCloseWindow(WINNO(2));
    ucOsdState = _MENU_F_USER;
}

//----------------------------------------------------------------------------------------------------
// OSD "FUserRAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFUserRAdj(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 0, 12, _MENU_F_USER_R);
}

void COsdLeftFUserRAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_USER);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_RED] = COsdFxDetOverRange(stColorTempData.ColorTemp[_RED], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(17), COL(16), stColorTempData.ColorTemp[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFUserRAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_USER);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_RED] = COsdFxDetOverRange(stColorTempData.ColorTemp[_RED], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(17), COL(16), stColorTempData.ColorTemp[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFUserRAdj(void)
{
    COsdExitFUserR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FUserG" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFUserG(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 1, 50, _MENU_F_USER_G_ADJ);
}

void COsdLeftFUserG(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 2, 12, _MENU_F_USER_B);
}

void COsdRightFUserG(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 0, 12, _MENU_F_USER_R);
}

void COsdExitFUserG(void)
{
    COsdExitFUserR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FUserGAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFUserGAdj(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 1, 12, _MENU_F_USER_G);
}

void COsdLeftFUserGAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_USER);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_GREEN] = COsdFxDetOverRange(stColorTempData.ColorTemp[_GREEN], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(17), COL(21), stColorTempData.ColorTemp[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFUserGAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_USER);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_GREEN] = COsdFxDetOverRange(stColorTempData.ColorTemp[_GREEN], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(17), COL(21), stColorTempData.ColorTemp[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFUserGAdj(void)
{
    COsdExitFUserR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FUserB" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFUserB(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 2, 50, _MENU_F_USER_B_ADJ);
}

void COsdLeftFUserB(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 0, 12, _MENU_F_USER_R);
}

void COsdRightFUserB(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 1, 12, _MENU_F_USER_G);
}

void COsdExitFUserB(void)
{
    COsdExitFUserR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FUserBAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFUserBAdj(void)
{
    COsdDispWindowHPoint(ROW(8), 154, 60, 2, 12, _MENU_F_USER_B);
}

void COsdLeftFUserBAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_USER);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_BLUE] = COsdFxDetOverRange(stColorTempData.ColorTemp[_BLUE], 255, 0, _DET_OVERRANGE_MAX);
    COsdFxShowNumber(ROW(17), COL(26), stColorTempData.ColorTemp[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdRightFUserBAdj(void)
{
    SET_COLOR_TEMP_TYPE(_CT_USER);
    CEepromLoadColorTempData();
    stColorTempData.ColorTemp[_BLUE] = COsdFxDetOverRange(stColorTempData.ColorTemp[_BLUE], 255, 0, _DET_OVERRANGE_MIN);
    COsdFxShowNumber(ROW(17), COL(26), stColorTempData.ColorTemp[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    CAdjustContrast(stConBriData.Contrast);
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

void COsdExitFUserBAdj(void)
{
    COsdExitFUserR();
}

//----------------------------------------------------------------------------------------------------
// OSD "FBright" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFBright(void)
{
    COsdDispWindowHPoint(ROW(9), 154, 54, 0, 38, _MENU_F_BRIGHT_ADJ);
}

void COsdLeftFBright(void)
{
    COsdDispWindowPoint(10, _MENU_F_AUTO_CONFIG);
}

void COsdRightFBright(void)
{
    COsdDispWindowPoint(8, _MENU_F_USER);
    SET_COLOR_TEMP_TYPE(_CT_USER);
    COsdDispColorTempSelect();
}

void COsdExitFBright(void)
{

}

//----------------------------------------------------------------------------------------------------
// OSD "FBrightAdj" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFBrightAdj(void)
{
ucOsdState = _MENU_DICOM_SETTING;
if(GCMode==1)
ucOsdEventMsg = _SAVE_LSLUMIDATA_MSG;
else if(GCMode==2)
ucOsdEventMsg = _SAVE_PWMLUMIDATA_MSG;
}

void COsdLeftFBrightAdj(void)
{
if(GCMode==1)
{
    switch(stConBriData.Dicom)
    	{
       case 0:
COsdDispClearText(ROW(1), COL(14), 10, 1);
stLSlumiData.DICOM350= COsdFxDetOverRange(stLSlumiData.DICOM350, 2000,200, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM350, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam
COsdFxChange1bitColor(ROW(1), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 1:
COsdDispClearText(ROW(2), COL(14), 10, 1);
stLSlumiData.DICOM400= COsdFxDetOverRange(stLSlumiData.DICOM400, 2000, 200, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM400, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam	 	
COsdFxChange1bitColor(ROW(2), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 2:
COsdDispClearText(ROW(3), COL(14), 10, 1);
stLSlumiData.DICOM450= COsdFxDetOverRange(stLSlumiData.DICOM450, 2000, 200, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM450, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
COsdFxChange1bitColor(ROW(3), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 3:
COsdDispClearText(ROW(4), COL(14), 10, 1);
stLSlumiData.DICOM500= COsdFxDetOverRange(stLSlumiData.DICOM500, 2000, 200, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM500, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
COsdFxChange1bitColor(ROW(4), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 4:
COsdDispClearText(ROW(5), COL(14), 10, 1);
stLSlumiData.DICOM550= COsdFxDetOverRange(stLSlumiData.DICOM550, 2000, 200, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM550, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
COsdFxChange1bitColor(ROW(5), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 5:
COsdDispClearText(ROW(6), COL(14), 10, 1);
stLSlumiData.DICOM600= COsdFxDetOverRange(stLSlumiData.DICOM600, 2000, 200, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM600, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
COsdFxChange1bitColor(ROW(6), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 6:
COsdDispClearText(ROW(7), COL(14), 10, 1);
stLSlumiData.DICOM650= COsdFxDetOverRange(stLSlumiData.DICOM650, 2000, 200, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM650, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
COsdFxChange1bitColor(ROW(7), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 7:
COsdDispClearText(ROW(8), COL(14), 10, 1);
stLSlumiData.DICOM700= COsdFxDetOverRange(stLSlumiData.DICOM700, 2000, 200, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM700, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
COsdFxChange1bitColor(ROW(8), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	default:
            break;
	}
}
else if(GCMode==2)
{
    switch(stConBriData.Dicom)
    	{
       case 0:  	
COsdDispClearText(ROW(1), COL(14), 10, 1);
stPWMlumiData.DICOM350= COsdFxDetOverRange(stPWMlumiData.DICOM350, 3000,0, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM350, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam
COsdFxChange1bitColor(ROW(1), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
break;
	case 1:
COsdDispClearText(ROW(2), COL(14), 10, 1);
stPWMlumiData.DICOM400= COsdFxDetOverRange(stPWMlumiData.DICOM400, 3000, 0, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM400, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam	 	
COsdFxChange1bitColor(ROW(2), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 2:
COsdDispClearText(ROW(3), COL(14), 10, 1);
stPWMlumiData.DICOM450= COsdFxDetOverRange(stPWMlumiData.DICOM450, 3000, 0, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM450, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
COsdFxChange1bitColor(ROW(3), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 3:
COsdDispClearText(ROW(4), COL(14), 10, 1);
stPWMlumiData.DICOM500= COsdFxDetOverRange(stPWMlumiData.DICOM500, 3000, 0, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM500, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
COsdFxChange1bitColor(ROW(4), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 4:
COsdDispClearText(ROW(5), COL(14), 10, 1);
stPWMlumiData.DICOM550= COsdFxDetOverRange(stPWMlumiData.DICOM550, 3000, 0, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM550, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
COsdFxChange1bitColor(ROW(5), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 5:
COsdDispClearText(ROW(6), COL(14), 10, 1);
stPWMlumiData.DICOM600= COsdFxDetOverRange(stPWMlumiData.DICOM600, 3000, 0, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM600, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
COsdFxChange1bitColor(ROW(6), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 6:
COsdDispClearText(ROW(7), COL(14), 10, 1);
stPWMlumiData.DICOM650= COsdFxDetOverRange(stPWMlumiData.DICOM650, 3000, 0, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM650, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
COsdFxChange1bitColor(ROW(7), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	case 7:
COsdDispClearText(ROW(8), COL(14), 10, 1);
stPWMlumiData.DICOM700= COsdFxDetOverRange(stPWMlumiData.DICOM700, 3000, 0, _DET_OVERRANGE_MIN);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM700, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
COsdFxChange1bitColor(ROW(8), COL(1), WIDTH(18), HEIGHT(1), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
		break;
	default:
            break;
}
}
}

void COsdRightFBrightAdj(void)
{
if(GCMode==1)
	{
    switch(stConBriData.Dicom)
    	{
       case 0:
stLSlumiData.DICOM350= COsdFxDetOverRange(stLSlumiData.DICOM350, 2000, 200, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM350, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam
       	break;
	case 1:
stLSlumiData.DICOM400= COsdFxDetOverRange(stLSlumiData.DICOM400, 2000, 200, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM400, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam	 	
		break;
	case 2:
stLSlumiData.DICOM450= COsdFxDetOverRange(stLSlumiData.DICOM450, 2000, 200, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM450, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
		break;
	case 3:
stLSlumiData.DICOM500= COsdFxDetOverRange(stLSlumiData.DICOM500, 2000, 200, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM500, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
		break;
	case 4:
stLSlumiData.DICOM550= COsdFxDetOverRange(stLSlumiData.DICOM550, 2000, 200, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM550, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
		break;
	case 5:
stLSlumiData.DICOM600= COsdFxDetOverRange(stLSlumiData.DICOM600, 2000, 200, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM600, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
		break;
	case 6:
stLSlumiData.DICOM650= COsdFxDetOverRange(stLSlumiData.DICOM650, 2000, 200, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM650, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
		break;
	case 7:
stLSlumiData.DICOM700= COsdFxDetOverRange(stLSlumiData.DICOM700, 2000, 200, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stLSlumiData.DICOM700, (_ALIGN_LEFT| _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
		break;
	default:
            break;
	}
	}
else if(GCMode==2)
{
    switch(stConBriData.Dicom)
    	{
       case 0:
stPWMlumiData.DICOM350= COsdFxDetOverRange(stPWMlumiData.DICOM350, 3000, 0, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM350, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam
       	break;
	case 1:
stPWMlumiData.DICOM400= COsdFxDetOverRange(stPWMlumiData.DICOM400, 3000, 0, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM400, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam	 	
		break;
	case 2:
stPWMlumiData.DICOM450= COsdFxDetOverRange(stPWMlumiData.DICOM450, 3000, 0, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM450, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
		break;
	case 3:
stPWMlumiData.DICOM500= COsdFxDetOverRange(stPWMlumiData.DICOM500, 3000, 0, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM500, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
		break;
	case 4:
stPWMlumiData.DICOM550= COsdFxDetOverRange(stPWMlumiData.DICOM550, 3000, 0, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM550, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
		break;
	case 5:
stPWMlumiData.DICOM600= COsdFxDetOverRange(stPWMlumiData.DICOM600, 3000, 0, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM600, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
		break;
	case 6:
stPWMlumiData.DICOM650= COsdFxDetOverRange(stPWMlumiData.DICOM650, 3000, 0, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM650, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
		break;
	case 7:
stPWMlumiData.DICOM700= COsdFxDetOverRange(stPWMlumiData.DICOM700, 3000, 0, _DET_OVERRANGE_MAX);
COsdFxShowNumber(ROW(1+stConBriData.Dicom), COL(14), stPWMlumiData.DICOM700, (_ALIGN_LEFT| _FORCE_SHOW_NUMBER_OFF | _SHOW_3));//adam		
		break;
	default:
            break;
      }
	}
}

void COsdExitFBrightAdj(void)
{
    COsdMenuFBrightAdj();
}

//----------------------------------------------------------------------------------------------------
// OSD "AutoConfig" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFAutoConfig(void)
{

}

void COsdLeftFAutoConfig(void)
{
    COsdDispWindowPoint(11, _MENU_F_EXIT);
}

void COsdRightFAutoConfig(void)
{
    COsdDispWindowPoint(9, _MENU_F_BRIGHT);
}

void COsdExitFAutoConfig(void)
{

}

//----------------------------------------------------------------------------------------------------
// OSD "FExit" Operation
//----------------------------------------------------------------------------------------------------
void COsdMenuFExit(void)
{
    COsdFxDisableOsd();
    COsdMenuNone();
    COsdDispPenPoint(ROW(5), COL(3), ROW(17), COL(3), _MENU_FACTORY_RESET);
    COsdFxChange1bitColor(ROW(5), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxChange1bitColor(ROW(17), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

}

void COsdLeftFExit(void)
{
    COsdDispWindowPoint(0, _MENU_F_AUTOCOLOR);
}

void COsdRightFExit(void)
{
    COsdDispWindowPoint(10, _MENU_F_AUTO_CONFIG);
}

void COsdExitFExit(void)
{

}

#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
//--------------------------------------------------
// Description  : Load font, draw window when source from power saving
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void CWakeUpShowSource()
{
    COsdFxDisableOsd();
    CTimerCancelTimerEvent(CModeNoCableEvent);
    CTimerCancelTimerEvent(CModePowerSavingEvent);

    if(!GET_SOURCE_OSD_STATUS())
    {
        SET_SOURCE_OSD_STATUS();
    }

    if(GET_PANELPOWERSTATUS() == _OFF)
    {
       CModeResetShowOSD();
    }

    COsdDispFirstTimeLoadFont();

    COsdFxEnableOsd();
    CPowerPanelOn();
}
#endif

#endif  // End of #if(_OSD_TYPE == _REALTEK_OSD)
