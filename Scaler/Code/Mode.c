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
// ID Code      : Mode.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __MODE__

#include "Common\Header\Include.h"

#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

//--------------------------------------------------
// Description  : Mode handler, the main control flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeHandler(void)
{
    CKeyKeyPadLedControl();

    if(CPowerHandler())
    {
#if _DEBUG_MESSAGE_SUPPORT
  //      CDebugMessage("CPowerHandler_CModeHandler", 0);
#endif
        ucCurrState = _PWOFF_STATE;
//bData=0;//sjp20110730
	
    }

#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
    if(GET_SOURCE_OSD_STATUS())
    {
        return;
    }
#endif

        #if _DEBUG_MESSAGE_SUPPORT
  //       CDebugMessage("CModeHandler", 0);
  //       CDebugMessage("ucCurrState", ucCurrState);
	 #endif

    switch(ucCurrState)
    {
        /********************/
        case _PWOFF_STATE:
        /********************/

            ucCurrState = GET_POWERSTATUS() ? _INITIAL_STATE : _PWOFF_STATE;
            break;

        /********************/
        case _INITIAL_STATE:
        /********************/

            ucCurrState = _SEARCH_STATE;
            break;

        /********************/
        case _SEARCH_STATE:
        /********************/

#if((_HDMI_SUPPORT == _ON) || (_TMDS_SUPPORT == _ON))
            if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_I_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_I_PORT))
            {
                // ENC toggle (HDCP flag)
                CScalerPageSelect(_PAGE2);
                CScalerRead(_P2_HDCP_PORT_CTRL_C2, 1, pData, _NON_AUTOINC);

                if((pData[0] & 0x10) == 0x10)
                {
                    g_bHDMIHDCPFlag = 1;
                }
            }
#endif
        #if _DEBUG_MESSAGE_SUPPORT
 //       CDebugMessage("CSourceHandler __SEARCH_STATE", 0);
	 #endif

            if(CSourceHandler())
            {
        #if _DEBUG_MESSAGE_SUPPORT
        CDebugMessage("CSourceHandler true", 0);
	 #endif
 #if(_SCALER_TYPE == _RTD2545LR)
                CPowerM2PLLOn();
#endif

                // Source and sync OK
                if(CModeDetect())
                {

   #if _DEBUG_MESSAGE_SUPPORT
					   CDebugMessage("CSourceHandler true", 0);
#endif

                    // Mode stable. Initial display settings  switch to active/nosignal/nosupport state
                    SET_READYFORDISPLAY();


                    ////////////////////////////////
                    //  Mode Detect for No-Signal //
                    ////////////////////////////////

                    if(stModeInfo.ModeCurr == _MODE_NOSIGNAL)
                    {
#if(_DP_SUPPORT == _ON)
                        if((GET_INPUTSOURCE_TYPE() == _SOURCE_DP))
                        {
                            if(g_bDpDisplayPass == _TRUE)
                            {
                                ucCurrState = _NOSUPPORT_STATE;
		 #if _DEBUG_MESSAGE_SUPPORT
			CDebugMessage("_NOSUPPORT_STATE5", 0);
		#endif
                                stModeInfo.ModeCurr = _MODE_NOSUPPORT;
                            }
                            else
                            {
                                // V016 System Patch Note (29) Modify 20100902 Start
                                // Patch Reason : Fix mode handler flow issue.
                                SET_INPUTSOURCE_TYPE(_SOURCE_NONE);
                                // V016 System Patch Note (29) Modify 20100902 End

                                ucCurrState = _NOSIGNAL_STATE;
                            }
                        }
                        else
                        {
                            // V016 System Patch Note (29) Modify 20100902 Start
                            // Patch Reason : Fix mode handler flow issue.
                            SET_INPUTSOURCE_TYPE(_SOURCE_NONE);
                            // V016 System Patch Note (29) Modify 20100902 End

                            ucCurrState = _NOSIGNAL_STATE;
                        }

#else
                        // V016 System Patch Note (29) Modify 20100902 Start
                        // Patch Reason : Fix mode handler flow issue.
                        SET_INPUTSOURCE_TYPE(_SOURCE_NONE);
                        // V016 System Patch Note (29) Modify 20100902 End

                        ucCurrState = _NOSIGNAL_STATE;
#endif
                    }

                    /////////////////////////////////
                    //  Mode Detect for No-Support //
                    /////////////////////////////////

#if(_FRC_SUPPORT == _ON)
                    else if(stModeInfo.ModeCurr == _MODE_NOSUPPORT)
#else
                    else if((stModeInfo.ModeCurr == _MODE_NOSUPPORT) || (stModeInfo.IVFreq > _PANEL_MAX_FRAME_RATE))
#endif
                    {
                        CModeAutoMeasureOn();
                        ucCurrState = _NOSUPPORT_STATE;
                        #if _DEBUG_MESSAGE_SUPPORT
			   CDebugMessage("_NOSUPPORT_STATE4", 0);
                       #endif
                        stModeInfo.ModeCurr = _MODE_NOSUPPORT;
                    }

                    //////////////////////////////////
                    //  Mode Detect for Active Mode //
                    //////////////////////////////////

                    else
                    {

#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
                        CMemorySDRAMReset();
#endif

                        if(GET_INPUTSOURCE_TYPE() == _SOURCE_DVI)
                        {
                            // HDCP MP Testing Mode: CTRL=1001, to avoid trigger WD when reset Rx_en
                            CScalerPageSelect(_PAGE2);
                            CScalerSetBit(_P2_UP_DOWN_CTRL0_B5, ~(_BIT1 | _BIT0), _BIT0);

                            CScalerPageSelect(_PAGE2);
                            CScalerRead(_P2_POWER_ON_OFF_CTRL_A7, 1, pData, _NON_AUTOINC);

                            if((pData[0] & _BIT6) == _BIT6) // BR Swap: HDMI port
                            {
                                // Reset Rx_en(R & G lane)
                                CScalerPageSelect(_PAGEB);
                                CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x79);
                                CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x7F);
                            }
                            else  // no BR Swap: DVI port
                            {
                                // Reset Rx_en(R & G lane)
                                CScalerPageSelect(_PAGEB);
                                CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x7C);
                                CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x7F);
                            }

                            // Recover "HDCP MP Testing Mode" to original mode
                            CScalerPageSelect(_PAGE2);
                            CScalerSetBit(_P2_UP_DOWN_CTRL0_B5, ~_BIT0, 0);
                        }

                        CModeDisplayActiveMode();

                        if(GET_INPUTSOURCE_TYPE() == _SOURCE_NONE)
                        {
                            return;
                        }

                        // V016 System Patch Note (15) Modify 20100824 Start
                        // Patch Reason : Fix IHCount=0 issue
                        /*
                        CModeAutoMeasureOn();
                        */
                        // V016 System Patch Note (15) Modify 20100824 End

#if(_AUDIO_SUPPORT == _ON)
#if((_SCALER_TYPE == _RTD2472D))
#if(_HDMI_SUPPORT == _ON)
#if(_HDMI_FROM_DVI_CONNECT == _OFF)
                        if(CHdmiFormatDetect() && ((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT)))//Input source is the HDMI format.
#else
                        if(CHdmiFormatDetect())
#endif
                        {
                            CHdmiAudioFirstTracking();
                        }

                        CTimerActiveTimerEvent(SEC(0.5), CHdmiAudioWaitingFlagReadyEven);

#endif  // End of #if(_HDMI_SUPPORT == _ON)
#endif  // End of #if((_SCALER_TYPE == _RTD2472D))
#endif  // End of #if(_AUDIO_SUPPORT == _ON)


#if(_DCR_MODE == _DCR_TYPE_3)
                        CDcrInitial();
#endif


#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
                        if(ucCurrState == _NOSUPPORT_STATE)
                        {
                            ucCurrState = _NOSUPPORT_STATE;
		 #if _DEBUG_MESSAGE_SUPPORT
				CDebugMessage("_NOSUPPORT_STATE3", 0);
		 #endif
                        }
                        else
                        {
                            CSourceSetCountDown();
                            ucCurrState = _CHECK_STATE;
                        }
#else
                        CSourceSetCountDown();
                        ucCurrState = _CHECK_STATE;

#endif  // End of #if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
                    }
                }
                else    // Else of if(CModeDetect())
                {
                    ///////////////////////
                    //  Mode Detect Fail //
                    ///////////////////////

                    if(g_ucModeStableCount > 0)
                    {
                        // Still in search state
                        g_ucModeStableCount--;
                    }
                    else
                    {
                        CModeSyncTimeoutCountDownEvent();
                        CModeAutoMeasureOn();

                        // V013 System Patch Note (1) 20100409 Modify Start
                        // Patch Reason : Optimize code to avoid an unnecessary excution of CModeMeasureData.
                        /*
                        CModeMeasureData();

#if(_DP_SUPPORT == _ON)
                        if(CModeMeasureData() || (g_bDpDisplayPass == _TRUE))
                        {
                            ucCurrState = _NOSUPPORT_STATE;
                        }
                        else
                        {
                            ucCurrState = _NOSIGNAL_STATE;
                        }
#else
                        ucCurrState = _NOSIGNAL_STATE;
#endif
                        */
                        if(CModeMeasureData() == _TRUE)
                        {
                            ucCurrState = _NOSUPPORT_STATE;
                         #if _DEBUG_MESSAGE_SUPPORT
				CDebugMessage("_NOSUPPORT_STATE2", 0);
                         #endif
                        }
                        else
                        {
                            ucCurrState = _NOSIGNAL_STATE;
                        }
                        // V013 System Patch Note (1) 20100409 Modify End
                    }
                }

                ucEvent0 = _INACTIVE_COUNTDOWN_EVENT;

            }
            else    // Else of if(CSourceHandler())
            {
        #if _DEBUG_MESSAGE_SUPPORT
         CDebugMessage("CSourceHandler fail", 0);
	 #endif
                /////////////////////////
                //  Source Search Fail //
                /////////////////////////

                if(GET_SEARCH_FINISH())
                {

#if(_DP_SUPPORT == _ON)

                    if((g_bDpDisplayPass == _TRUE) && (g_ucDpPowerStatus != _DP_POWER_DOWN))
                    {
                        ucCurrState = _NOSUPPORT_STATE;
			#if _DEBUG_MESSAGE_SUPPORT
			CDebugMessage("_NOSUPPORT_STATE1", 0);
			#endif
                        SET_READYFORDISPLAY();
                    }
                    else
                    {
                        CModeSyncTimeoutCountDownEvent();
                    }
#else
                    CModeSyncTimeoutCountDownEvent();
                    /*
                    CLR_SEARCH_FINISH();
                    */
#endif
                    CLR_SEARCH_FINISH();
                }
            }


            break;

        /********************/
        case _CHECK_STATE:
        /********************/

            if(GET_COUNTDOWN_DP_STABLE())
            {
                CTimerActiveTimerEvent(SEC(0.5), CMiscCheckToActiveEvent);
                CLR_COUNTDOWN_DP_STABLE();
            }
            else if(GET_COUNTDOWN_HDMI_HDCP_WORSE())
            {
                CTimerActiveTimerEvent(SEC(3), CMiscCheckToActiveEvent);
                CLR_COUNTDOWN_HDMI_HDCP_WORSE();
            }
            else if(GET_COUNTDOWN_HDMI_STABLE())
            {
                CTimerActiveTimerEvent(SEC(0.3), CMiscCheckToActiveEvent);
                CLR_COUNTDOWN_HDMI_STABLE();
            }
            else if(GET_COUNTDOWN_VGA_STABLE())
            {
                CTimerActiveTimerEvent(SEC(0.1), CMiscCheckToActiveEvent);
                CLR_COUNTDOWN_VGA_STABLE();
            }

            if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_I_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_I_PORT))
            {
                if(g_bHDMIHDCPFlag != 1)            // No HDCP
                {
                    CScalerPageSelect(_PAGE2);
                    CScalerRead(_P2_HDCP_PORT_CTRL_C2, 1, pData, _NON_AUTOINC);

                    if((pData[0] & 0x10) == 0x10)   // from No HDCP ---> HDCP
                    {
                        CTimerCancelTimerEvent(CMiscCheckToActiveEvent); // cancel 0.3 secs event
                        SET_COUNTDOWN_HDMI_HDCP_WORSE();
                        g_bHDMIHDCPFlag = 1;
                    }
                }
                else // HDCP
                {
                    CScalerPageSelect(_PAGE2);
                    CScalerSetByte(_P2_HDCP_ADDR_PORT_C3, 0x08);
                    CScalerRead(_P2_HDCP_DATA_PORT_C4, 1, pData, _NON_AUTOINC);

                    if(pData[0] != 0x00)    // Ri != 0;
                    {
                        // Frame Counter
                        CScalerPageSelect(_PAGE2);
                        CScalerSetByte(_P2_HDCP_ADDR_PORT_C3, 0xC0);
                        CScalerRead(_P2_HDCP_DATA_PORT_C4, 1, pData, _NON_AUTOINC);

                        if(pData[0] != 0x00)
                        {
                            if(g_bCheckHDCP == 0)
                            {
                                CTimerCancelTimerEvent(CMiscCheckToActiveEvent); // cancel 3 secs event
                                SET_COUNTDOWN_HDMI_STABLE();
                                g_bCheckHDCP = 1;
                            }
                        }
                    }
                }
            }

            // V013 VGA Patch Note (9) Modify 20100414 Start
            // Patch Reason : Add Checking Stable Signal mechanism for VGA Signal.
            if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_VGA_PORT)
            || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_VGA_PORT)
            || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_YPBPR_PORT)
            || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_YPBPR_PORT))
            {
                if(CSyncCheckVGAIsStable() == _FALSE)
                {
                    CModeResetMode();
                    break;
                }
            }
            // V013 VGA Patch Note (9) Modify 20100414 End

            if(CModeStableDetect() == _FALSE)
            {
                CModeResetMode();
            }

            break;

        /********************/
        case _ACTIVE_STATE:
        /********************/
#if(_DDCCI_SUPPORT == _ON)
            g_ucActiveInputSourceType = GET_INPUTSOURCE_TYPE();
#endif

            if(CModeStableDetect() == _FALSE)
            {
                CModeResetMode();
            }
            else
            {

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#if(_COLOR_FORMAT_CONVERT == _ON)
                CModeColorFormatConvert();
#endif
// V012 Modify 20100304 End

                if(GET_READYFORDISPLAY() == _TRUE)
                {

#if(_AUDIO_SUPPORT == _ON)
                    CAdjustAudioControl(_ENABLE);
#endif
                    CLR_READYFORDISPLAY();
                    SET_OSD_READYFORDISPLAY();
                    CSourceSaveSearchData();
#if(_OD_SUPPORT == _ON)
                    if(CMemorySetODCompress() == _FALSE)
                    {
                        CMemorySetODOnOff(_OFF);
                    }
                    else
                    {
                        CMemorySetODFIFO();
                        CMemorySetODOnOff(_ON);
                    }
#endif

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
                    CModeOverScanAdjustPos();
#endif
// V012 Modify 20100316 End


#if((_ASPECT_RATIO_SUPPORT == _ON) && (_MEMORY_WORK_TYPE == _OD_OFF_FRC_OFF))

                    CModeSetDHWidthToDisplay();
                    CTimerDelayXms(100);

#endif // End of #if((_ASPECT_RATIO_SUPPORT == _ON) && (_MEMORY_WORK_TYPE == _OD_OFF_FRC_OFF))

                    CPowerPanelOn();

                    CScalerPageSelect(_PAGE2);
                    CScalerSetBit(_P2_TMDS_RPS_AE, ~_BIT7, 0);
                    CAdjustEnableWatchDog(_WD_ALL);

#if(_HDMI_SUPPORT == _ON)
                    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT)
                    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT)
                    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_I_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_I_PORT))//sephinroth 20080606
                    {
                        if(GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
                        {
                            CScalerPageSelect(_PAGE2);
                            CScalerRead(_P2_HDMI_SR_CB, 1, pData, _NON_AUTOINC);

                            if((bit)(pData[0] & 0x40)) // AVMute detected!
                            {
                                CAdjustDisableHDMIWatchDog(_WD_PACKET_VARIATION | _WD_SET_AVMUTE_ENABLE);  // Disable packet variation Watch Dog
                                CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, _BIT5);
                            }
                            else
                            {
                                 CAdjustEnableHDMIWatchDog(_WD_PACKET_VARIATION);   // Enable packet variation Watch Dog
                                 CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00);
                            }
                         }
                         else
                         {
                                CAdjustDisableHDMIWatchDog(_WD_PACKET_VARIATION | _WD_SET_AVMUTE_ENABLE);   // Disable packet variation Watch Dog
                                CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00);
                         }
                    }
                    else
                    {
                        CAdjustDisableHDMIWatchDog(_WD_PACKET_VARIATION | _WD_SET_AVMUTE_ENABLE);   // Disable packet variation Watch Dog
                        CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00);
                    }
#endif

#if(_DP_SUPPORT == _ON)
                    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DP_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DP_PORT))
                    {
                        CDpSinkStatusSet(_TRUE);    //! In Sync
                    }
#endif

                    // V013 VGA Patch Note (10) 20100416 Modify Start
                    // Patch Reason : Support Auto Config For Yuv Color.
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
                    if((GET_AUTO_FLAG() == 0) && ((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)))
#else
                    if((GET_AUTO_FLAG() == 0) && (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
#endif
                    // V013 VGA Patch Note (10) 20100416 Modify End

                    {
                        ucOsdEventMsg = _DO_AUTO_CONFIG;
                    }
                    else
                    {
                       CTimerReactiveTimerEvent(SEC(0), CModeOsdDisplayTimingAndInputEvent);
                    }
                }   // End of if(GET_READYFORDISPLAY() == _TRUE)

#if(_HDMI_SUPPORT == _ON)
                CHdmiAVMuteCheck();
#endif

#if((_DCR_MODE == _DCR_TYPE_1) || (_DCR_MODE == _DCR_TYPE_2))
                if(GET_DCR_STATUS())
                {
                    CDcrMeasureStartHD();
                }
                else if(!GET_DCR_STATUS())
                {
                    CDcrSlowAdjust(stSystemData.BackLight);
                }
#endif

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
#if((_HDMI_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
                if(GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
                {
                    CHdmiAudioControl();
                }
#endif // End of #if((_HDMI_SUPPORT == _ON))
#endif
            }   // End of if(CModeStableDetect() == _FALSE)

#if(_DCR_MODE == _DCR_TYPE_3)
            if(g_ucDcrTimer > 1)     // 20mSec
            {
                CDcrDcr3();
                g_ucDcrTimer = 0;
            }
#endif
            break;


        /********************/
        case _NOSUPPORT_STATE:
        /********************/


#if(_DP_SUPPORT == _ON)
            if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DP_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DP_PORT))
            {
                if(CDpNosupportCheck() == _TRUE)
                {
                    CModeResetMode();
                    break;
                }
            }
            else
            {
                if(CModeIsChange())
                {
                    CModeResetMode();
                    break;
                }
            }

            if(GET_READYFORDISPLAY() == _TRUE)
            {
                CLR_READYFORDISPLAY();
                SET_OSD_READYFORDISPLAY();
                CModeSetFreeRun();
            }
            break;
#else

            if(CModeIsChange())
            {
                CModeResetMode();
                break;
            }

            if(GET_READYFORDISPLAY() == _TRUE)
            {
                CLR_READYFORDISPLAY();
                SET_OSD_READYFORDISPLAY();
                CModeSetFreeRun();
            }
            break;

#endif //End of #if(_DP_SUPPORT == _ON)


        /********************/
        case _NOSIGNAL_STATE:
        /********************/

            if(GET_READYFORDISPLAY() == _TRUE)
            {
                CLR_READYFORDISPLAY();
                SET_OSD_READYFORDISPLAY();
                CModeSetFreeRun();

                CScalerPageSelect(_PAGE2);
                CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_SCR_00, ~(_BIT3 | _BIT2), _BIT3);
            }

#if((_TMDS_SUPPORT == _ON))
            if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_I_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_I_PORT))
            {
                // DVI/HDMI: high sensitivity then can't sleep
                CScalerPageSelect(_PAGE2);
                CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                CTimerDelayXms(5);
                CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0f);
            }
#endif
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("CSourceHandler__NOSIGNAL_STATE", 0);
#endif
/*****for source auto search 2011 0613*****/
if(stSystemData.SearchIndex>1)
	{
	stSystemData.SearchIndex=1;//sjp20111206
	CEepromSaveSystemData();	
	}
 if(stSystemData.SearchIndex==1)
	{
	g_ucSearchIndex=0;
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
    //CSourceSwitchInputPort(_D0_INPUT_PORT);
#endif
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("CSourceHandler_stSystemData.SearchIndex==1", 0);
#endif
	if(CSourceHandler())	
		{
              g_ucSearchIndex=0;
		COsdMenuSingalDVI();
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("signal switch VGA switch to DVI", 0);
#endif
		}
	else
		{
			g_ucSearchIndex=1;
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("signal switch VGA switch fail", 0);
#endif			
		}
	}
else if (stSystemData.SearchIndex==0)
{
	g_ucSearchIndex=1;
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
    //CSourceSwitchInputPort(_D0_INPUT_PORT);
#endif
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("CSourceHandler_stSystemData.SearchIndex==0", 0);
#endif
	if(CSourceHandler())	
		{
              g_ucSearchIndex=1;
		COsdMenuSingalVGA();
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("signal switch DVI switch to VGA", 0);
#endif
		}
	else
		{
			g_ucSearchIndex=0;
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("signal switch DVI switch fail", 0);
#endif		
		}	
}
/*****for source auto search 2011 0613*****/
            if(CModeConnectIsChange() || CSourceHandler())
            {
                CModeResetMode();
            }
            break;

        /********************/
        case _SLEEP_STATE:
        /********************/
        #if _DEBUG_MESSAGE_SUPPORT
       // CDebugMessage("CSourceHandler ___SLEEP_STATE", 0);
	 #endif
/*****for source auto search 2011 0613*****/

 if(stSystemData.SearchIndex==1)
	{
	g_ucSearchIndex=0;
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
    //CSourceSwitchInputPort(_D0_INPUT_PORT);
#endif
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("CSourceHandler_stSystemData.SearchIndex==1", 0);
#endif
	if(CSourceHandler())	
		{
              g_ucSearchIndex=0;
		COsdMenuSingalDVI();
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("signal switch VGA switch to DVI", 0);
#endif
		}
	else
		{
			g_ucSearchIndex=1;
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("signal switch VGA switch fail", 0);
#endif			
		}

	}
else if (stSystemData.SearchIndex==0)
{
	g_ucSearchIndex=1;
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
    //CSourceSwitchInputPort(_D0_INPUT_PORT);
#endif
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("CSourceHandler_stSystemData.SearchIndex==0", 0);
#endif
	if(CSourceHandler())	
		{
              g_ucSearchIndex=1;
		COsdMenuSingalVGA();
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("signal switch DVI switch to VGA", 0);
#endif
		}
	else
		{
			g_ucSearchIndex=0;
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("signal switch DVI switch fail", 0);
#endif
			
			
		}	




}
/*****for source auto search 2011 0613*****/


	 
            if(CModeConnectIsChange() || CSourceHandler())
            {
                CModeResetMode();
            }
            break;
        default:
            break;
    }
}

//----------------------------------------------------------------------------------------------------
// Measure Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Check measure ready process
// Input Value  : None
// Output Value : Return _TRUE if measure finished, _FALSE if timeout
//--------------------------------------------------
bit CModeMeasureReady(void)
{
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_DVI) || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI))
    {
        // V013 TMDS Patch Note (16) 20100422 Modify Start
        // Patch Reason : Solve DVI Interlace Issue
        CScalerPageSelect(_PAGE2);
        // V013 TMDS Patch Note (16) 20100422 Modify End

        if(CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7) == _BIT7)
        {
            CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, _BIT0);  // Digital Mode Measure
        }
        else
        {
            CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, 0x00);   // Analog Mode Measure
        }
    }
    else
    {
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, 0x00);       // Analog Mode Measure
    }

    CAdjustSyncProcessorMeasureStart();

// V015 VGA Patch Note (4) Modify 20100611 Start
// Patch Reason : Modify HV measurement polling time
/*
#if(_LOW_FRAME_RATE_SUPPORT == _OFF)
    if(CTimerPollingEventProc(80, CMiscModeMeasurePollingEvent))
#else
    if(CTimerPollingEventProc(120, CMiscModeMeasurePollingEvent))
#endif
*/
#if(_LOW_FRAME_RATE_SUPPORT == _OFF)
    if(CTimerPollingEventProc(_SP_AUTORUN_TIME_OUT, CMiscModeMeasurePollingEvent))
#else
    if(CTimerPollingEventProc(2 * _SP_AUTORUN_TIME_OUT, CMiscModeMeasurePollingEvent))
#endif
// V015 VGA Patch Note (4) Modify 20100611 End
    {
        return _TRUE;
    }
    else
    {
        CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT5, 0x00);
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get measure data and convert into system information
// Input Value  : None
// Output Value : Return _TRUE if success, _FALSE if the measurement result is wrong
//--------------------------------------------------
bit CModeMeasureData(void)
{
    // Read measurement status bit
    CScalerRead(_MEAS_HS_PERIOD_H_52, 3, &pData[8], _AUTOINC);

    if((bit)(pData[8] & _BIT4) || (bit)(pData[10] & _BIT4) || (bit)(pData[10] & _BIT5))
    {
#if((_LOW_FRAME_RATE_SUPPORT == _OFF) || (_SCALER_TYPE == _RTD2472D))

        if((GET_INPUTSOURCE_TYPE() == _SOURCE_DVI) || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI))
        {
            SET_INPUTSOURCE_TYPE(_SOURCE_NONE);
        }

        return _FALSE;

#else

        if(CModeCheckLowFrameRate() == _FALSE)
        {
            SET_INPUTSOURCE_TYPE(_SOURCE_NONE);
            return _FALSE;
        }

#endif
    }

    // Pop up measurement result
    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT6, _BIT6);
    CScalerSetBit(_MEAS_HS_VS_HI_SEL_58, ~_BIT0, 0x00);

    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_VGA_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_VGA_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_YPBPR_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_YPBPR_PORT))
    {
        CScalerRead(_MEAS_VS_PERIOD_H_54, 2, &pData[10], _AUTOINC);     // VTotal

        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT1, _BIT1);
        CScalerRead(_STABLE_PERIOD_H_50, 2, &pData[12], _AUTOINC);      // HCount
        CScalerRead(_STABLE_HIGH_PERIOD_H_4A, 2, &pData[14], _AUTOINC); // HSyncPulseWidth
    }
    else
    {
        CScalerRead(_MEAS_HS_PERIOD_H_52, 6, &pData[8], _AUTOINC);
    }

    // Calculate measurement result
    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_VGA_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_VGA_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_YPBPR_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_YPBPR_PORT))
    {
        ((WORD *)pData)[0] = ((pData[12] & 0x07) << 8) | pData[13];  // HCount
        ((WORD *)pData)[1] = ((pData[10] & 0x0F) << 8) | pData[11];  // Vtotal
        ((WORD *)pData)[2] = ((pData[14] & 0x07) << 8) | pData[15]; // HSyncPulseWidth
    }
    else
    {
        ((WORD *)pData)[0] = ((pData[8] & 0x0f) << 8) | pData[9];   // HCount
        ((WORD *)pData)[1] = ((pData[10] & 0x0f) << 8) | pData[11]; // Vtotal
        ((WORD *)pData)[2] = ((pData[12] & 0xf0) << 4) | pData[13]; // HSyncPulseWidth
    }

    if((((WORD *)pData)[0] == 0) || (((WORD *)pData)[1] == 0))
    {
        // The measurement result is out of range
        return _FALSE;
    }
    else
    {
        /////////////////////// Digital Measure ////////////////////////////
        if(CScalerGetBit(_SYNC_SELECT_47, _BIT0) == _BIT0)
        {
            // Save Polarity
            stModeInfo.Polarity = (pData[10] & 0xc0) >> 6;

            // V013 TMDS Patch Note (16) 20100422 Modify Start
            // Patch Reason : Solve DVI Interlace Issue
            // In digital measure HSYNC polarity is reverse of reality polarity
            stModeInfo.Polarity = (stModeInfo.Polarity | (~(bit)(stModeInfo.Polarity & _BIT0)));
            // V013 TMDS Patch Note (16) 20100422 Modify End

            // Save IH_TOTAL
            stModeInfo.IHCount = ((WORD *)pData)[0] + 1;
            stModeInfo.IHTotal = stModeInfo.IHCount;

            // Save input data enable width and height
            stModeInfo.IVTotal = ((WORD *)pData)[1] + 1;
            stModeInfo.IVHeight = stModeInfo.IVTotal;
            stModeInfo.IHWidth = ((WORD *)pData)[2] + 1;

            // V013 TMDS Patch Note (16) 20100422 Modify Start
            // Patch Reason : Solve DVI Interlace Issue
            /*
            // Get IDEN vertical Start
            CModeStartUpDVI();

            stModeInfo.IVTotal = stModeInfo.IVStartPos + stModeInfo.IVHeight + 37;

            // Measure IDEN Start Fail
            if(GET_INPUTSOURCE_TYPE() == _SOURCE_NONE)
            {
                return _FALSE;
            }
            */
            stModeInfo.IVTotal = stModeInfo.IVStartPos + stModeInfo.IVHeight + 37;
            // V013 TMDS Patch Note (16) 20100422 Modify End

            CScalerPageSelect(_PAGE2);

            // Read freq number result
            CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x28);
            CScalerRead(_P2_HDMI_DATA_PORT_CA, 1, &pData[14], _NON_AUTOINC);

            CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x29);
            CScalerRead(_P2_HDMI_DATA_PORT_CA, 1, &pData[15], _NON_AUTOINC);

            ((DWORD *)pData)[0] = (((WORD)(pData[14] & 0x07) << 8) | pData[15]);

            // Calculate IHS/IVS Frequency
            stModeInfo.IHFreq = (WORD)(((DWORD)_RTD_XTAL * 1024) * 10 * 2 / (((DWORD *)pData)[0] * stModeInfo.IHTotal));
            stModeInfo.IHFreq = (stModeInfo.IHFreq >> 1) + (stModeInfo.IHFreq & 0x01);
            stModeInfo.IVFreq = (WORD)(((DWORD)_RTD_XTAL * 1024) * 10 / (((DWORD *)pData)[0] * stModeInfo.IHTotal * (stModeInfo.IVStartPos + stModeInfo.IVHeight) / 1000));

            return _TRUE;

        }

        /////////////////////// Analog Measure ////////////////////////////
        // Store measurement results in global system variable
        stModeInfo.Polarity = (pData[10] & 0xc0) >> 6;

        stModeInfo.IHCount = ((WORD *)pData)[0] + 1;

        // V012 Modify 20100331 Start
        // V012 Patch Note (21) : Fix the sync processor compatibility problem. Replace slower XTAL clock with M2PLL.
        /*
        stModeInfo.IHFreq = (WORD)((DWORD)_RTD_XTAL * 10 * 2 / stModeInfo.IHCount);
        */
        stModeInfo.IHFreq = (WORD)((DWORD)_INTERNAL_SYSTEM_CLK * 10 * 2 / stModeInfo.IHCount);
        // V012 Modify 20100331 End

        stModeInfo.IHFreq = (stModeInfo.IHFreq >> 1) + (stModeInfo.IHFreq & 0x01);
        stModeInfo.IVTotal = ((WORD *)pData)[1] + 1;

        // V012 Modify 20100331 Start
        // V012 Patch Note (21) : Fix the sync processor compatibility problem. Replace slower XTAL clock with M2PLL.
        /*
        stModeInfo.IVFreq = (WORD)((DWORD)_RTD_XTAL * 10 * 1000 / ((DWORD)stModeInfo.IHCount * stModeInfo.IVTotal));
        */

        // V012 Modify 20100402 Start
        // V012 Patch Note (29) : Fix the inaccurate Vfreq in OSD with SOG HORV/HEORV sync type.
        /*
        stModeInfo.IVFreq = (WORD)((DWORD)_INTERNAL_SYSTEM_CLK * 10 * 1000 / ((DWORD)stModeInfo.IHCount * stModeInfo.IVTotal));
        */
        if(CScalerGetBit(_SYNC_CTRL_49, _BIT2) == _BIT2)
        {
            stModeInfo.IVFreq = (WORD)((DWORD)_INTERNAL_SYSTEM_CLK * 10 * 1000 / ((DWORD)stModeInfo.IHCount * (stModeInfo.IVTotal + g_ucCoastLineCnt)));
        }
        else
        {
            stModeInfo.IVFreq = (WORD)((DWORD)_INTERNAL_SYSTEM_CLK * 10 * 1000 / ((DWORD)stModeInfo.IHCount * stModeInfo.IVTotal));
        }
        // V012 Modify 20100402 End
        // V012 Modify 20100331 End

        stModeInfo.IHSyncPulseCount = ((WORD *)pData)[2];

        if(stModeInfo.IHSyncPulseCount > (stModeInfo.IHCount / 2))
        {
            stModeInfo.IHSyncPulseCount = stModeInfo.IHCount - stModeInfo.IHSyncPulseCount;
        }

        // Measure IVSyncPulseCount
        CScalerSetBit(_MEAS_HS_VS_HI_SEL_58, ~_BIT0, _BIT0);
        CScalerRead(_MEAS_HS_VS_HIGH_PERIOD_H_56, 2, &pData[8], _AUTOINC);

        ((WORD *)pData)[0] = ((pData[8] & 0xF0) << 4) | pData[9];

        // V013 VGA Patch Note (3) 20100409 Modify Start
        // Patch Reason : Modify VSync Pulse Width Measure Result.
        /*
        stModeInfo.IVSyncPulseCount = ((WORD *)pData)[0] + 1;
        */
        if(CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, (_BIT6 | _BIT5 | _BIT4)) == 0x60) // SS Sync Type
        {
            stModeInfo.IVSyncPulseCount = ((WORD *)pData)[0];
        }
        else
        {
            stModeInfo.IVSyncPulseCount = ((WORD *)pData)[0] + 1;
        }
        // V013 VGA Patch Note (3) 20100409 Modify End

        if(stModeInfo.IVSyncPulseCount > (stModeInfo.IVTotal / 2))
        {
            stModeInfo.IVSyncPulseCount = stModeInfo.IVTotal - stModeInfo.IVSyncPulseCount;
        }


        CScalerSetBit(_MEAS_HS_VS_HI_SEL_58, ~_BIT0, 0x00);

        return _TRUE;
    }
}

// V013 TMDS Patch Note (16) 20100422 Modify Start
// Patch Reason : Solve DVI Interlace Issue
//--------------------------------------------------
// Description  : Measure Active Region H/V Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeMeasureHVActiveStart(void)
{
    CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), 0x00);
    CScalerSetBit(_AUTO_ADJ_CTRL1_7D, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

    if(CTimerPollingEventProc(50, CMiscAutoMeasurePollingEvent))
    {
        CScalerRead(_V_START_END_H_7E, 6, pData, _AUTOINC);

        CScalerPageSelect(_PAGE2);
        // IDEN horizontal Start
        stModeInfo.IHStartPos = ((((WORD)pData[3] & 0xf0) << 4) | (WORD)pData[4]) - ((CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7) == _BIT7) ? 16 - 14 : 18 - 14);

        // IDEN vertical Start
        stModeInfo.IVStartPos = (((WORD)pData[0] & 0xf0) << 4) | (WORD)pData[1];
    }
    else
    {
        CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
        g_bDoModeResetMode = _TRUE;
    }
}
// V013 TMDS Patch Note (16) 20100422 Modify End

//----------------------------------------------------------------------------------------------------
// Mode Detect Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Mode detect process
// Input Value  : None
// Output Value : Return _TRUE if we get a stable mode
//--------------------------------------------------
bit CModeDetect(void)
{
    switch(GET_INPUTSOURCE_TYPE())
    {
        case _SOURCE_VGA:

#if(_YPBPR_SUPPORT == _ON)
        case _SOURCE_YPBPR:
#endif
            CModeInitialVGA();

            // V012 Modify 20100324 Start
            // V012 Patch Note (18) : Fix the sync processor unlock issue which causes APLL setting fail.
            if(GET_INPUTSOURCE_TYPE() == _SOURCE_NONE)
            {
                return _FALSE;
            }
            // V012 Modify 20100324 End

#if((_TMDS_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
        case _SOURCE_DVI:
        case _SOURCE_DP:
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_HDMI:
#endif

            if(CModeDetectCommon())
            {
                return _TRUE;
            }
            break;

#if(_VIDEO_SUPPORT == _ON)

        case _SOURCE_VIDEO8:
            stModeInfo.ModeCurr = _MODE_EXIST;
            return _TRUE;

#endif

    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Mode detect process for VGA and DVI
// Input Value  : None
// Output Value : Return _TRUE if we get a stable mode
//--------------------------------------------------
bit CModeDetectCommon(void)
{
    BYTE modetemp = _MODE_NOSIGNAL;
    BYTE polaritytemp;
    WORD hcount, vtotal;

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))

    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) != _D0_DP_PORT) && (GET_INPUTPORT_TYPE(g_ucSearchIndex) != _D1_DP_PORT)
        && (GET_INPUTPORT_TYPE(g_ucSearchIndex) != _A0_VGA_PORT))
    {
        // Freq Check
        if(CSyncCheckTMDSFreq() == _FALSE)
        {
            CModeResetMode();
            return _FALSE;
        }

        // BCH Error Check
        if((GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI))
        {
            CScalerPageSelect(_PAGE2);
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, 0x02, ~_BIT3, _BIT3);
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, 0x02, ~_BIT1, 0x00);
            CTimerDelayXms(5);
            CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x02);
            CScalerRead(_P2_HDMI_DATA_PORT_CA, 1, &pData[0], _NON_AUTOINC);

            if((pData[0] & 0x02) == 0x02)
            {
                CModeResetMode();
                return _FALSE;
            }
        }
    }
#endif

    if(CModeMeasureReady())
    {
        polaritytemp = stModeInfo.Polarity;
        hcount = stModeInfo.IHCount;
        vtotal = stModeInfo.IVTotal;
         #if _DEBUG_MESSAGE_SUPPORT
//		 CDebugMessage("stModeInfo.Polarity==", stModeInfo.Polarity);
 //		 CDebugMessage("stModeInfo.IHCount==", stModeInfo.IHCount);
 //		 CDebugMessage("stModeInfo.IHTotal==", stModeInfo.IHTotal);
// 		 CDebugMessage("stModeInfo.IHFreq==", stModeInfo.IHFreq);
 //		 CDebugMessage("stModeInfo.IHStartPos==", stModeInfo.IHStartPos);
 //		 CDebugMessage("stModeInfo.IHSyncPulseCount==", stModeInfo.IHSyncPulseCount);
		 
 ///		 CDebugMessage("stModeInfo.IHWidth==", stModeInfo.IHWidth);
		 
// 		 CDebugMessage("stModeInfo.IVTotal==", stModeInfo.IVTotal);
// 		 CDebugMessage("stModeInfo.IVFreq==", stModeInfo.IVFreq);
// 		 CDebugMessage("stModeInfo.IVHeight==", stModeInfo.IVHeight);
 //		 CDebugMessage("stModeInfo.IVStartPos==", stModeInfo.IVStartPos);
 //		 CDebugMessage("stModeInfo.IVSyncPulseCount==", stModeInfo.IVSyncPulseCount);
	  #endif

        // Get measure results and decide " modetemp = _MODE_NOSIGNAL/_MODE_NOSUPPORT/_MODE_EXIST "
        if(CModeMeasureData())
        {
         #if _DEBUG_MESSAGE_SUPPORT
//		 CDebugMessage("stModeInfo.Polarity==", stModeInfo.Polarity);
// 		 CDebugMessage("stModeInfo.IHCount==", stModeInfo.IHCount);
 //		 CDebugMessage("stModeInfo.IHTotal==", stModeInfo.IHTotal);
 //		 CDebugMessage("stModeInfo.IHFreq==", stModeInfo.IHFreq);
 //		 CDebugMessage("stModeInfo.IHStartPos==", stModeInfo.IHStartPos);
 //		 CDebugMessage("stModeInfo.IHSyncPulseCount==", stModeInfo.IHSyncPulseCount);
 //		 CDebugMessage("stModeInfo.IHWidth==", stModeInfo.IHWidth);
		 
 //		 CDebugMessage("stModeInfo.IVTotal==", stModeInfo.IVTotal);
 //		 CDebugMessage("stModeInfo.IVFreq==", stModeInfo.IVFreq);
 //		 CDebugMessage("stModeInfo.IVHeight==", stModeInfo.IVHeight);
 //		 CDebugMessage("stModeInfo.IVStartPos==", stModeInfo.IVStartPos);
 //		 CDebugMessage("stModeInfo.IVSyncPulseCount==", stModeInfo.IVSyncPulseCount);
	  #endif
            CSyncModifyPolarity();

            stModeInfo.ModeCurr = _MODE_NOSIGNAL;

            if(abs(stModeInfo.IHCount - hcount) <= 2)
            {
                stModeInfo.IHCount = hcount;
            }

            if(abs(stModeInfo.IVTotal - vtotal) <= 2)
            {
                stModeInfo.IVTotal = vtotal;
            }

            if((stModeInfo.IHCount != hcount) || (stModeInfo.IVTotal != vtotal) || (stModeInfo.Polarity != polaritytemp))
            {
                modetemp = _MODE_NOSIGNAL;
            }
            else
            {
                if((stModeInfo.IHFreq < _H_FREQ_MIN) || (stModeInfo.IHFreq > _H_FREQ_MAX) || (stModeInfo.IVFreq < _V_FREQ_MIN) || (stModeInfo.IVFreq > _V_FREQ_MAX))
                {
                    modetemp = _MODE_NOSUPPORT;
                }
                else
                {
                    modetemp = _MODE_EXIST;
                }
            }
        }
        else
        {
            modetemp = _MODE_NOSIGNAL;
        }

#if(_SCALER_TYPE == _RTD2472D)
        if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) ||
           (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT) ||
           (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_I_PORT) ||
           (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT) ||
           (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT) ||
           (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_I_PORT))
        {
            CTimerDelayXms(50);
        }
#endif

        // Wait mode stable and decide the mode type for current source
        if(modetemp != ucModeFound)
        {
            ucModeFound = modetemp;
            ucEvent1 = _INACTIVE_COUNTDOWN_EVENT;
            CLR_MODESTABLE();
            CTimerCountDownEventProc(&ucEvent1, 3, CModeStableCountDownEvent);

            return _FALSE;
        }
        else
        {

            CTimerCountDownEventProc(&ucEvent1, 3, CModeStableCountDownEvent);

            if(GET_MODESTABLE())
            {
                if(ucModeFound == _MODE_EXIST)
                {
                    CModeInterlaceCheck();
                    stModeInfo.ModeCurr = CModeSearchDisplayMode();

                    // Issac-0129-Fixed
                    if (GET_INPUTSOURCE_TYPE() == _SOURCE_DVI || GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
                    {
                        if (stModeInfo.IHWidth == 0 || stModeInfo.IVHeight == 0)
                        {
                            ucModeFound = _MODE_NOSIGNAL;
                            ucEvent1 = _INACTIVE_COUNTDOWN_EVENT;
                            CLR_MODESTABLE();
                            CTimerCountDownEventProc(&ucEvent1, 3, CModeStableCountDownEvent);

                            return _FALSE;
                        }
                    }
                }
                else
                {
                    stModeInfo.ModeCurr = ucModeFound;
                }

                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check if mode is changed
// Input Value  : None
// Output Value : Return _TRUE if mode is changed
//--------------------------------------------------
bit CModeIsChange(void)
{
    BYTE polaritytemp;
    WORD hcount, vtotal;
    polaritytemp = stModeInfo.Polarity;
    hcount = stModeInfo.IHCount;
    vtotal = stModeInfo.IVTotal;

#if(_VIDEO_SUPPORT == _ON)

    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VIDEO8)
    {
        if(CVideoIsChange())
        {
            return _TRUE;
        }
    }

#endif

    if((GET_DEEPCOLORMODE()) && (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI))//sephinroth 20080710
    {
        CScalerPageSelect(_PAGE2);
        CScalerRead( _P2_TMDS_DPC0_B4, 1, pData, _NON_AUTOINC);
        if( (pData[0] & 0x07) == 0x00)
        {
            return _TRUE;
        }
    }

    // V016 VGA Patch Note (4) Modify 20100803 Start
    // Patch Reason : Modify YPbPr Timing display green when changing timing.
    /*
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        if(CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT6 | _BIT5))
        {
            return _TRUE;
        }
    }
    */
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
    {
        // Report Input Source Change If Overflow,Stable Period or Stable Polarity Flag Changed.
        if((bit)(CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, (_BIT7 | _BIT6 | _BIT5))) == _TRUE)
        {
            return _TRUE;
        }
    }
    // V016 VGA Patch Note (4) Modify 20100803 End

    if(CModeMeasureData())
    {
        if(abs(stModeInfo.IHCount - hcount) <= 2)
        {
            stModeInfo.IHCount = hcount;
        }

        if(abs(stModeInfo.IVTotal - vtotal) <= 2)
        {
            stModeInfo.IVTotal = vtotal;
        }

        if((stModeInfo.IHCount != hcount) || (stModeInfo.IVTotal != vtotal) || (stModeInfo.Polarity != polaritytemp))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        return _TRUE;
    }

}

//--------------------------------------------------
// Description  : Search display mode process
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchDisplayMode(void)
{
    BYTE modetemp;

    switch(GET_INPUTSOURCE_TYPE())
    {
        case _SOURCE_VGA:

            modetemp = CModeSearchModeVGA();
            break;

#if(_YPBPR_SUPPORT == _ON)

        case _SOURCE_YPBPR:
            modetemp = CYPbPrSearchMode();
            break;

#endif

#if(_TMDS_SUPPORT == _ON)
        case _SOURCE_DVI:
        case _SOURCE_HDMI:
        case _SOURCE_DP:
            modetemp = CModeSearchModeDVI();
            break;

#endif

#if(_VIDEO_SUPPORT == _ON)
        case _SOURCE_VIDEO8:
            break;
#endif
    }

    return modetemp;
}

//--------------------------------------------------
// Description  : Search mode for VGA
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchModeVGA(void)
{
    BYTE modecnt = _MODE_NOSUPPORT;
    bit bOtherError = _FALSE;
    BYTE ucCheckModeResult = 0xFF;

    // V012 Modify 20100331 Start
    // V012 Patch Note (30) : Use mode search incorrect flag to skip SOD clock seeking in the auto stage to avoid one missing vertical line at the edge of the picture.
    g_bModeSearchIncorrectFlag = _FALSE;
    // V012 Modify 20100331 End

    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
#if(_FIFO_MODE_ONLY == _ON)
    g_ucFIFOModeNum = 0;
#endif
    // V013 VGA Patch Note (11) Modify 20100416 End

    // V012 Modify 20100322 Start
    // V012 Patch Note (8) : Add OOR Table to indicate in which modes the display could show OOR directly.
    for(modecnt = 0; modecnt < _MAX_OOR_MODE_NUMBER; modecnt++)
    {
        if(CModeSearchOORModeVGA(modecnt) == _TRUE)
        {
            return _MODE_NOSUPPORT;
        }
    }
    // V012 Modify 20100322 End

    if((CAutoMeasurePositionV(_MIN_NOISE_MARGIN) != _ERROR_SUCCESS))
    {
        g_usVStartPos = 0;
        g_usVEndPos = 0;

        // V014 VGA Patch Note (2) Modify 20100526 Start
        // Patch Reason : Use width/HTotal ratio to distinguish mode _MODE_1440x900_60HZ_RB and _MODE_1600x900_60HZ_CVR.
        g_usHStartPos = 0;
        g_usHEndPos = 0;
        // V014 VGA Patch Note (2) Modify 20100526 End
    }

    if(((g_usVEndPos - g_usVStartPos + 1) >= stModeInfo.IVTotal) || (g_usVEndPos <= g_usVStartPos - 1))
    {
        g_usVStartPos = 0;
        g_usVEndPos = 0;
    }

    // V014 VGA Patch Note (2) Modify 20100526 Start
    // Patch Reason : Use width/HTotal ratio to distinguish mode _MODE_1440x900_60HZ_RB and _MODE_1600x900_60HZ_CVR.
    if(((g_usHEndPos - g_usHStartPos + 1) >= stModeUserData.Clock) || (g_usHEndPos <= g_usHStartPos - 1))
    {
        g_usHStartPos = 0;
        g_usHEndPos = 0;
    }
    // V014 VGA Patch Note (2) Modify 20100526 End

    g_usCurrIVHeight = CModeIVHeightVerify(g_usVEndPos - g_usVStartPos + 1);

    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);

    for(modecnt = 0; modecnt < _MAX_PRESET_MODE; modecnt++)
    {
        if(CModeComparePresetModeVGA(modecnt))
        {
            ucCheckModeResult = CModeCheckModeVGA(modecnt);

            if((g_usCurrIVHeight > tINPUTMODE_PRESET_TABLE[modecnt].IVHeight)
            || ((ucCheckModeResult != _CHECK_MODE_ADC_SPEED_ERROR)
             && (ucCheckModeResult != _CHECK_MODE_SUCCESS)))
            {
                bOtherError = _TRUE;
                continue;
            }
            else if(ucCheckModeResult == _CHECK_MODE_ADC_SPEED_ERROR)
            {
                continue;
            }
            else
            {
                // V012 Modify 20100324 Start
                // V012 Patch Note (3) : Modify mode table and mode search according to SQE testing items, and to sync with Dell case.
                ucCheckModeResult = CModeSearchAcceptivePresetModeVGA(modecnt);

                if(ucCheckModeResult != modecnt)
                {
                    if(CModeCheckModeVGA(ucCheckModeResult) == _CHECK_MODE_SUCCESS)
                    {
                        modecnt = ucCheckModeResult;
                    }
                }
                // V012 Modify 20100324 End

                // V013 VGA Patch Note (11) Modify 20100416 Start
                // Patch Reason : Add FIFO Mode Only to save EEPROM space.
                // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
#if(_FIFO_MODE_ONLY == _ON)
                CModeCheckFIFOModeVGA(modecnt);
#endif
                // V013 VGA Patch Note (11) Modify 20100416 End
                return modecnt;
            }
        }
    }
    if((modecnt >= _MAX_PRESET_MODE) && (bOtherError == _FALSE) && (ucCheckModeResult == _CHECK_MODE_ADC_SPEED_ERROR))
    {
        return _MODE_NOSUPPORT;
    }

    modecnt = CModeSearchAcceptiveModeVGA();

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
    g_ucUserModeCurr = modecnt;
#endif
// V012 Modify 20100316 End

    if((modecnt == _MODE_NOSIGNAL) || (modecnt == _MODE_NOSUPPORT))
    {
        return modecnt;
    }

    SET_MODE_SEARCH_TYPE(_USER_MODE_TYPE);

    modecnt = CModeCheckFIFOModeVGA(modecnt);

    return modecnt;

}

// V012 Modify 20100324 Start
// V012 Patch Note (3) : Modify mode table and mode search according to SQE testing items, and to sync with Dell case.
/*
//--------------------------------------------------
// Description  : Compare preset VGA mode
// Input Value  : Mode number
// Output Value : Return _TRUE if the input mode number is correspondence
//--------------------------------------------------
bit CModeComparePresetModeVGA(BYTE ucModeCnt)
{
    BYTE polarity=0, polaritytemp=0;

#if(_HSYNC_DETECTION == _AUTO_RUN)
    polarity = ((stModeInfo.Polarity & ~_BIT0) | ( ! (((bit)CScalerGetBit(_SYNC_INVERT_48, _BIT3) ? 0x00 : _BIT0) ^ ((bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6) ? 0x00 : _BIT0))));
#else
    polarity = ((stModeInfo.Polarity & ~_BIT0) | ((bit)CScalerGetBit(_SYNC_INVERT_48, _BIT3) ? 0x00 : _BIT0));
#endif

    if(abs(stModeInfo.IVFreq - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreqTolerance)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IHFreq - tINPUTMODE_PRESET_TABLE[ucModeCnt].IHFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IHFreqTolerance)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IVTotal - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVTotal) > 1)
    {
        return _FALSE;
    }

    if((bit)(polarity & _BIT0))
    {
        if((bit)(polarity & _BIT1))
        {
            polaritytemp    = _SYNC_HP_VP;
        }
        else
        {
            polaritytemp    = _SYNC_HP_VN;
        }
    }
    else
    {
        if((bit)(polarity & _BIT1))
        {
            polaritytemp    = _SYNC_HN_VP;
        }
        else
        {
            polaritytemp    = _SYNC_HN_VN;
        }
    }

    if((polaritytemp & tINPUTMODE_PRESET_TABLE[ucModeCnt].PolarityFlag) == 0x00)
    {
        return _FALSE;
    }

    return _TRUE;

}
*/
//--------------------------------------------------
// Description  : Compare preset VGA mode
// Input Value  : Mode number
// Output Value : Return _TRUE if the input mode number is correspondence
//--------------------------------------------------
bit CModeComparePresetModeVGA(BYTE ucModeCnt)
{
    if(abs(stModeInfo.IVFreq - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreqTolerance)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IHFreq - tINPUTMODE_PRESET_TABLE[ucModeCnt].IHFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IHFreqTolerance)
    {
        return _FALSE;
    }

    if((ucModeCnt == _MODE_1024x768_60HZ_MAC) && (abs(stModeInfo.IVTotal - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVTotal) > 3))
    {
        return _FALSE;
    }

    if((ucModeCnt == _MODE_1280x800_60HZ) && (abs(stModeInfo.IVTotal - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVTotal) > 3))
    {
        return _FALSE;
    }

    if((ucModeCnt == _MODE_1600x1200_60HZ) && (abs(stModeInfo.IVTotal - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVTotal) > 2))
    {
        return _FALSE;
    }

    if((ucModeCnt == _MODE_1600x1200_60HZ_RB) && (abs(stModeInfo.IVTotal - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVTotal) > 3))
    {
        return _FALSE;
    }

    if((ucModeCnt == _MODE_1360x768_60HZ) && (abs(stModeInfo.IVTotal - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVTotal) > 2))
    {
        return _FALSE;
    }

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    if((ucModeCnt == _MODE_720x480_60HZ) && (abs(stModeInfo.IVTotal - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVTotal) > 2))
    */
    if((ucModeCnt == _MODE_720x480_60HZ) && (abs(stModeInfo.IVTotal - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVTotal) >= 2))
    // V013 VGA Patch Note (24) Modify 20100514 End
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IVTotal - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVTotal) > 3)
    {
        return _FALSE;
    }

    return _TRUE;
}
// V012 Modify 20100324 End

// V012 Modify 20100324 Start
// V012 Patch Note (3) : Modify mode table and mode search according to SQE testing items, and to sync with Dell case.
/*
//--------------------------------------------------
// Description  : Search an acceptive mode
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchAcceptiveModeVGA(void)
{
    BYTE acceptivemode = _MODE_NOSUPPORT;

    if(stModeInfo.IVTotal < 350)
    {

    }
    else if(stModeInfo.IVTotal < 488)              // 720x400 Mode : Vertical Line < 488
    {
        if(stModeInfo.IVFreq < 790)
        {
            acceptivemode = _MODE_720x400_70HZ;
        }
        else
        {
            acceptivemode = _MODE_720x400_85HZ;
        }
    }
    else if(stModeInfo.IVTotal < 610)              // 640x480 Mode : 488 <= Vertical Line < 610
    {

        if(stModeInfo.IVFreq < 640)
        {
            acceptivemode = _MODE_640x480_60HZ;
        }
        else if(stModeInfo.IVFreq < 690)
        {
            acceptivemode = _MODE_640x480_66HZ;
        }
        else if(stModeInfo.IVFreq < 740)
        {
            acceptivemode = _MODE_640x480_72HZ;
        }
        else if(stModeInfo.IVFreq < 790)
        {
            acceptivemode = _MODE_640x480_75HZ;
        }
        else
        {
            acceptivemode = _MODE_640x480_85HZ;
        }
    }
    else if(stModeInfo.IVTotal < 660)              // 800x600 Mode : 610 <= Vertical Line < 660
    {
        if(stModeInfo.IVFreq < 580)
        {
            acceptivemode = _MODE_800x600_56HZ;
        }
        else if(stModeInfo.IVFreq < 660)
        {
            acceptivemode = _MODE_800x600_60HZ;
        }
        else if(stModeInfo.IVFreq < 740)
        {
            acceptivemode = _MODE_800x600_72HZ;
        }
        else if(stModeInfo.IVFreq < 790)
        {
            acceptivemode = _MODE_800x600_75HZ;
        }
        else
        {
            acceptivemode = _MODE_800x600_85HZ;
        }
    }
    else if(stModeInfo.IVTotal < 732)              // 832x624 Mode : 660 <= Vertical Line < 732
    {
        if(stModeInfo.IVFreq < 740)
        {
            acceptivemode = _MODE_800x600_72HZ;
        }
        else
        {
            acceptivemode = _MODE_832x624_75HZ;
        }
    }
    else if(stModeInfo.IVTotal < 780)              // 1280x720 Mode : 732 <= Vertical Line < 780
    {
        if(stModeInfo.IVFreq < 740)
        {
            acceptivemode = _MODE_1280x720_60HZ;
        }
        else
        {
            acceptivemode = _MODE_1280x720_75HZ;
        }
    }
    else if(stModeInfo.IVTotal < 820)              // 1024x768/1280x768 Mode : 780 <= Vertical Line < 820
    {
        if(stModeInfo.IVFreq < 650)
        {
            acceptivemode = _MODE_1024x768_60HZ;//Confuse mode between 1024x768 and 1280x768
        }
            //acceptivemode = _MODE_1280x768_60HZ;
        else if(stModeInfo.IVFreq < 730)
        {
            acceptivemode = _MODE_1024x768_70HZ;
        }
        else if(stModeInfo.IVFreq < 790)
        {
            acceptivemode = _MODE_1024x768_75HZ;
        }
        else
        {
            acceptivemode = _MODE_1024x768_85HZ;
        }
    }
    else if(stModeInfo.IVTotal < 880)              // 1024x800 Mode : 820 <= Vertical Line < 880
    {
        acceptivemode = _MODE_1024x800_85HZ;
    }
    else if(stModeInfo.IVTotal < 920)              // 1152x864/870 Mode : 880 <= Vertical Line < 920
    {
        if(stModeInfo.IVFreq < 650)
        {
            acceptivemode = _MODE_1152x864_60HZ;
        }
        else if(stModeInfo.IVFreq < 740)
        {
            acceptivemode = _MODE_1152x864_70HZ;
        }
        else if(stModeInfo.IVFreq < 790)
        {
            if((stModeInfo.IHFreq > 679) && (stModeInfo.IHFreq < 697))
            {
                acceptivemode = _MODE_1152x870_75HZ;
            }
            else
            {
                acceptivemode = _MODE_1152x864_75HZ;
            }
        }
            else
        {
            acceptivemode = _MODE_1152x864_85HZ;
        }
    }
    else if(stModeInfo.IVTotal < 975)              // 1152x900/1440x900 Mode : 920 <= Vertical Line < 975
    {
        if(stModeInfo.IVFreq < 660)
        {
            acceptivemode = _MODE_1440x900_60HZ;
        }
        else if(stModeInfo.IVFreq < 700)
        {
            acceptivemode = _MODE_1152x900_66HZ;
        }
        else if(stModeInfo.IVFreq < 760)
        {
            acceptivemode = _MODE_1440x900_75HZ;
        }
        else if(stModeInfo.IVFreq < 790)
        {
            acceptivemode = _MODE_1152x900_76HZ;
        }
    }
    else if(stModeInfo.IVTotal < 1040)             // 1280x960 Mode : 975 <= Vertical Line < 1040
    {
        if(stModeInfo.IVFreq < 650)
        {
            acceptivemode = _MODE_1280x960_60HZ;
        }
        else
        {
            acceptivemode = _MODE_1280x960_75HZ;
        }
    }
    else if(stModeInfo.IVTotal < 1087)             // 1280x1024 Mode : 1040 <= Vertical Line < 1087
    {
        if(stModeInfo.IVFreq < 680)
        {
            acceptivemode = _MODE_1280x1024_60HZ;// Confuse mode between 1280x1024_60HZ and 1680x1050_60HZ_BR
        }
            //acceptivemode = _MODE_1680x1050_60HZ_BR;
        else if(stModeInfo.IVFreq < 720)
        {
            acceptivemode = _MODE_1280x1024_70HZ;
        }
        else if(stModeInfo.IVFreq < 780)
        {
            acceptivemode = _MODE_1280x1024_75HZ;
        }
        else
        {
            acceptivemode = _MODE_1280x1024_85HZ;
        }
    }
    else if(stModeInfo.IVTotal < 1110)             // 1680x1050 Mode : 1087 <= Vertical Line < 1110
    {
        if(stModeInfo.IVFreq < 640)
        {
            acceptivemode = _MODE_1680x1050_60HZ;
        }
        else
        {
            acceptivemode = _MODE_1680x1050_75HZ;
        }
    }
    else if(stModeInfo.IVTotal < 1200)             // 1920x1080 Mode : 1110 <= Vertical Line < 1200
    {
        acceptivemode = _MODE_1920x1080_60HZ;
    }
    else if(stModeInfo.IVTotal < 1300)             // 1600x1200 Mode : 1200 <= Vertical Line < 1300
    {
        if(stModeInfo.IVFreq < 630)
        {
            acceptivemode = _MODE_1600x1200_60HZ;//Confuse mode between 1600x1200 and 1920x1200
        }
        else if(stModeInfo.IVFreq < 680)
        {
            acceptivemode = _MODE_1600x1200_65HZ;
        }
        else if(stModeInfo.IVFreq < 720)
        {
            acceptivemode = _MODE_1600x1200_70HZ;
        }
        else if(stModeInfo.IVFreq < 780)
        {
            acceptivemode = _MODE_1600x1200_75HZ;
        }
        else
        {
            acceptivemode = _MODE_1600x1200_85HZ;
        }
    }

    acceptivemode = CModeAdditionalSearch(acceptivemode);

    return acceptivemode;
}
*/
//--------------------------------------------------
// Description  : Search an acceptive mode
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchAcceptiveModeVGA(void)
{
    BYTE ucAcceptiveModeIndex = _MODE_NOSUPPORT;
    BYTE ucPolarity = 0;
    BYTE ucPolaritytemp = 0;
    WORD usIHSyncpulseCnt = 0;

    // V012 Modify 20100331 Start
    // V012 Patch Note (21) : Fix the sync processor compatibility problem. Replace slower XTAL clock with M2PLL.
    /*
    usIHSyncpulseCnt = stModeInfo.IHSyncPulseCount;
    */
    usIHSyncpulseCnt = (DWORD)stModeInfo.IHSyncPulseCount * _XTAL27000K / _INTERNAL_SYSTEM_CLK;
    // V012 Modify 20100331 End

#if(_HSYNC_DETECTION == _AUTO_RUN)
    ucPolarity = ((stModeInfo.Polarity & ~_BIT0) | ( ! (((bit)CScalerGetBit(_SYNC_INVERT_48, _BIT3) ? 0x00 : _BIT0) ^ ((bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6) ? 0x00 : _BIT0))));
#else
    ucPolarity = ((stModeInfo.Polarity & ~_BIT0) | ((bit)CScalerGetBit(_SYNC_INVERT_48, _BIT3) ? 0x00 : _BIT0));
#endif

    if((bit)(ucPolarity & _BIT0))
    {
        if((bit)(ucPolarity & _BIT1))
        {
            ucPolaritytemp = _SYNC_HP_VP;
        }
        else
        {
            ucPolaritytemp = _SYNC_HP_VN;
        }
    }
    else
    {
        if((bit)(ucPolarity & _BIT1))
        {
            ucPolaritytemp = _SYNC_HN_VP;
        }
        else
        {
            ucPolaritytemp = _SYNC_HN_VN;
        }
    }


    if( stModeInfo.IVTotal < 420 )
    {

    }
    else if( stModeInfo.IVTotal < 435 )
    {
        if( stModeInfo.IVFreq < 790 )
        {
            ucAcceptiveModeIndex = _MODE_640x350_70HZ;
        }
    }
    else if(stModeInfo.IVTotal < 488)
    {
        if(ucPolaritytemp == _SYNC_HP_VN) // HP/VN
        {
            if( stModeInfo.IVFreq < 790 )
            {
                ucAcceptiveModeIndex = _MODE_640x350_70HZ;
            }
        }
        else
        {
            if( stModeInfo.IVFreq < 600 )
            {
                ucAcceptiveModeIndex = _MODE_640x400_56HZ;
            }
            else if(stModeInfo.IVFreq < 790)
            {
                ucAcceptiveModeIndex = _MODE_720x400_70HZ;
            }
            else
            {
                ucAcceptiveModeIndex = _MODE_720x400_85HZ;
            }
        }
    }
    else if(stModeInfo.IVTotal < 590) // 640x480 Mode : 488 <= Vertical Line < 610
    {
        if(ucPolaritytemp == _SYNC_HN_VP) // HN/VP
        {
            if(stModeInfo.IVFreq < 650)
            {
                if(abs(usIHSyncpulseCnt - 94) <= 10)
                {
                    ucAcceptiveModeIndex = _MODE_640x400_60HZ;
                }

                else
                {
                    ucAcceptiveModeIndex = _MODE_720x480_60HZ;
                }
            }
            else if(stModeInfo.IVFreq < 690)
            {
                ucAcceptiveModeIndex = _MODE_848x480_70HZ;
            }
            else if(stModeInfo.IVFreq < 740)
            {
                ucAcceptiveModeIndex = _MODE_848x480_72HZ;
            }
            else if(stModeInfo.IVFreq < 790)
            {
                ucAcceptiveModeIndex = _MODE_848x480_75HZ;
            }
        }
        else
        {
            if(stModeInfo.IVFreq < 530)
            {
                ucAcceptiveModeIndex = _MODE_640x480_50HZ;
            }
            else if(stModeInfo.IVFreq < 650)
            {
                if((abs(usIHSyncpulseCnt - 59) <= 10) && (ucPolaritytemp == _SYNC_HN_VN))
                {
                    ucAcceptiveModeIndex = _MODE_720x480_60HZ_GTF;
                }
                else if((abs(usIHSyncpulseCnt - 80) <= 15) && ((ucPolaritytemp == _SYNC_HP_VP) || (ucPolaritytemp == _SYNC_HN_VP)))
                {
                ucAcceptiveModeIndex = _MODE_848x480_60HZ;
                }
                else
                {
                    ucAcceptiveModeIndex = _MODE_640x480_60HZ;
                }
            }
            else if( stModeInfo.IVFreq < 690 )
            {
                ucAcceptiveModeIndex = _MODE_640x480_66HZ;
            }

            // V012 Modify 20100324 Start
            // V012 Patch Note (3) : Modify mode table and mode search according to SQE testing items, and to sync with Dell case.
            /*
            else if(stModeInfo.IVFreq < 720)
            {
                ucAcceptiveModeIndex = _MODE_640x480_70HZ;
            }
            */
            // V012 Modify 20100324 End

            else if( stModeInfo.IVFreq < 740 )
            {
                ucAcceptiveModeIndex = _MODE_640x480_72HZ;
            }
            else if( stModeInfo.IVFreq < 790 )
            {
                ucAcceptiveModeIndex = _MODE_640x480_75HZ;
            }
            else
            {
                ucAcceptiveModeIndex = _MODE_640x480_85HZ;
            }
        }
    }
    else if( stModeInfo.IVTotal < 670 ) // 800x600 Mode : 610 <= Vertical Line < 660
    {
        if(ucPolaritytemp == _SYNC_HP_VP) // HP/VP
        {
            if( stModeInfo.IVFreq < 580 )
            {
                ucAcceptiveModeIndex = _MODE_800x600_56HZ;
            }
            else if( stModeInfo.IVFreq < 660 )
            {
                ucAcceptiveModeIndex = _MODE_800x600_60HZ;
            }
            else if( stModeInfo.IVFreq < 740 )
            {
                if(abs(usIHSyncpulseCnt - 45) <= 3)
                {
                    ucAcceptiveModeIndex = _MODE_800x600_75HZ;
                }
                else
                {
                    ucAcceptiveModeIndex = _MODE_800x600_72HZ;
                }
            }
            else if( stModeInfo.IVFreq < 790 )
            {
                if(abs(usIHSyncpulseCnt - 45) <= 3)
                {
                    ucAcceptiveModeIndex = _MODE_800x600_75HZ;
                }
                else
                {
                    ucAcceptiveModeIndex = _MODE_800x600_72HZ;
                }
            }
            else
            {
                ucAcceptiveModeIndex = _MODE_800x600_85HZ;
            }
        }
        else
        {
            // V012 Modify 20100324 Start
            // V012 Patch Note (3) : Modify mode table and mode search according to SQE testing items, and to sync with Dell case.
            /*
            if(stModeInfo.IVFreq < 580)
            {
                ucAcceptiveModeIndex = _MODE_720x576_50HZ;
            }
            else if(stModeInfo.IVFreq < 660)
            */
            // V012 Modify 20100324 End

            if(stModeInfo.IVFreq < 660)
            {
                ucAcceptiveModeIndex = _MODE_720x576_60HZ;
            }
            else if(stModeInfo.IVFreq < 790)
            {
                if(abs(usIHSyncpulseCnt - 29) <= 3)
                {
                    ucAcceptiveModeIndex = _MODE_832x624_75HZ;
                }
                else
                {
                    ucAcceptiveModeIndex = _MODE_720x576_75HZ;
                }
            }
        }
    }
    else if(stModeInfo.IVTotal < 760) // 1280x720 Mode : 732 <= Vertical Line < 780
    {
        if(stModeInfo.IVFreq < 660)
        {
            ucAcceptiveModeIndex = _MODE_1280x720p_60HZ;
        }
        else if(stModeInfo.IVFreq < 710)
        {
            ucAcceptiveModeIndex = _MODE_1280x720_70HZ;
        }
        else if(stModeInfo.IVFreq < 740)
        {
            ucAcceptiveModeIndex = _MODE_1280x720_72HZ;
        }
        else
        {
            ucAcceptiveModeIndex = _MODE_1280x720_75HZ;
        }
    }
    else if(stModeInfo.IVTotal < 797)
    {
        ucAcceptiveModeIndex = _MODE_1360x768_60HZ;
    }
    else if(stModeInfo.IVTotal < 820) // 1024x768 Mode : 780 <= Vertical Line < 881
    {
        if(stModeInfo.IVFreq < 580)
        {
            if(abs(usIHSyncpulseCnt - 33) <= 5)
            {
                ucAcceptiveModeIndex = _MODE_1024x768_60HZ_MAC;
            }
            else
            {
                ucAcceptiveModeIndex = _MODE_1024x768_50HZ;
            }
        }
        else if(stModeInfo.IVFreq < 630)
        {
            if(abs(usIHSyncpulseCnt - 33) <= 5)
            {
                ucAcceptiveModeIndex = _MODE_1024x768_60HZ_MAC;
            }
            else if(abs(usIHSyncpulseCnt - 15) <= 3)
            {
                ucAcceptiveModeIndex = _MODE_1280x768_60HZ_RB;
            }
            else if(abs(usIHSyncpulseCnt - 40) <= 3)
            {
                ucAcceptiveModeIndex = _MODE_1280x768_60HZ;
            }
            else
            {
                ucAcceptiveModeIndex = _MODE_1024x768_60HZ;
            }
        }
        else if( stModeInfo.IVFreq < 670 )
        {
            ucAcceptiveModeIndex = _MODE_1024x768_66HZ;
        }
        else if( stModeInfo.IVFreq < 720 )
        {
            ucAcceptiveModeIndex = _MODE_1024x768_70HZ;
        }
        else if(stModeInfo.IVFreq < 740)
        {
            if(abs(usIHSyncpulseCnt - 33) <= 4)
            {
                ucAcceptiveModeIndex = _MODE_1024x768_75HZ;
            }
            else
            {
                ucAcceptiveModeIndex = _MODE_1024x768_72HZ;
            }
        }
        else if( stModeInfo.IVFreq < 790 )
        {
            if(ucPolaritytemp == _SYNC_HN_VN) // HN/VN
            {
                ucAcceptiveModeIndex = _MODE_1024x768_75HZ_MAC;
            }
            else
            {
                ucAcceptiveModeIndex = _MODE_1024x768_75HZ;
            }
        }
        else
        {
            if(ucPolaritytemp == _SYNC_HN_VP) // HN/VP
            {
                ucAcceptiveModeIndex = _MODE_1280x768_85HZ;
            }
            else
            {
                ucAcceptiveModeIndex = _MODE_1024x768_85HZ;
            }
        }
    }
    else if(stModeInfo.IVTotal < 850) // 1024x768 Mode : 780 <= Vertical Line < 881
    {
        if(stModeInfo.IVFreq < 670)
        {
            ucAcceptiveModeIndex = _MODE_1280x800_60HZ;
        }
        else if(stModeInfo.IVFreq < 710)
        {
            ucAcceptiveModeIndex = _MODE_1280x800_70HZ;
        }
        else if(stModeInfo.IVFreq < 740)
        {
            ucAcceptiveModeIndex = _MODE_1280x800_72HZ;
        }
        else
        {
            ucAcceptiveModeIndex = _MODE_1280x800_75HZ;
        }
    }
    else if(stModeInfo.IVTotal < 914) // 1152x864/870 Mode : 881 <= Vertical Line < 932
    {
        if( stModeInfo.IVFreq < 650 )
        {
            ucAcceptiveModeIndex = _MODE_1152x864_60HZ;
        }
        else if( stModeInfo.IVFreq < 740 )
        {
            ucAcceptiveModeIndex = _MODE_1152x864_70HZ;
        }
        else if(stModeInfo.IVFreq < 790)
        {
            ucAcceptiveModeIndex = _MODE_1152x864_75HZ;
        }
        else
        {
            ucAcceptiveModeIndex = _MODE_1152x864_85HZ;
        }
    }
    else if(stModeInfo.IVTotal < 920) // 1152x864/870 Mode : 881 <= Vertical Line < 932
    {
        ucAcceptiveModeIndex = _MODE_1152x870_75HZ;
    }

    else if(stModeInfo.IVTotal < 927)
    {
        ucAcceptiveModeIndex = _MODE_1440x900_60HZ_RB;
    }
    else if(stModeInfo.IVTotal < 935)
    {
        if( stModeInfo.IVFreq < 650)
        {
            ucAcceptiveModeIndex = _MODE_1440x900_60HZ;
        }
        else if(stModeInfo.IVFreq < 790)
        {
           ucAcceptiveModeIndex = _MODE_1440x900_75HZ;
        }
    }
    else if(stModeInfo.IVTotal < 938)
    {
        if(ucPolaritytemp == _SYNC_HN_VP)
        {
            ucAcceptiveModeIndex = _MODE_1440x900_60HZ;
        }
        else if(ucPolaritytemp == _SYNC_HP_VP)
        {
            ucAcceptiveModeIndex = _MODE_1152x900_66HZ;
        }
        else
        {
            ucAcceptiveModeIndex = _MODE_1152x900_66HZ_S;
        }
    }
    else if(stModeInfo.IVTotal < 950)
    {
        if(stModeInfo.IVFreq < 780)
        {
            ucAcceptiveModeIndex = _MODE_1440x900_75HZ;
        }
    }
    else if(stModeInfo.IVTotal < 1020) // 1280x960 Mode : 975 <= Vertical Line < 1040
    {
        if(stModeInfo.IVFreq < 660)
        {
            ucAcceptiveModeIndex = _MODE_1280x960_60HZ;
        }
        else if(stModeInfo.IVFreq < 710)
        {
            ucAcceptiveModeIndex = _MODE_1280x960_70HZ;
        }
        else if(stModeInfo.IVFreq < 730)
        {
            ucAcceptiveModeIndex = _MODE_1280x960_72HZ;
        }
        else if( stModeInfo.IVFreq < 780 )
        {
            ucAcceptiveModeIndex = _MODE_1280x960_75HZ;
        }
        else
        {
            ucAcceptiveModeIndex = _MODE_1280x960_85HZ;
        }
    }
    else if(stModeInfo.IVTotal < 1085)
    {
        if(stModeInfo.IVFreq < 660)
        {
            ucAcceptiveModeIndex = _MODE_1280x1024_60HZ;
        }
        else if(stModeInfo.IVFreq < 710)
        {
            ucAcceptiveModeIndex = _MODE_1280x1024_70HZ;
        }
        else if(stModeInfo.IVFreq < 730)
        {
            ucAcceptiveModeIndex = _MODE_1280x1024_72HZ;
        }
        else if( stModeInfo.IVFreq < 780 )
        {
            ucAcceptiveModeIndex = _MODE_1280x1024_75HZ;
        }
        else
        {
            ucAcceptiveModeIndex = _MODE_1280x1024_85HZ;
        }
    }
    else if(stModeInfo.IVTotal < 1100)
    {
        if(stModeInfo.IVFreq < 620)
        {
            if(abs(usIHSyncpulseCnt - 11) <= 4)
            {
                ucAcceptiveModeIndex = _MODE_1680x1050_60HZ_RB;
            }
            else
            {
                ucAcceptiveModeIndex = _MODE_1680x1050_60HZ;
            }
        }
        else
        {
            ucAcceptiveModeIndex = _MODE_1680x1050_75HZ;
        }
    }
    else if(stModeInfo.IVTotal < 1200)
    {
        if(stModeInfo.IVFreq < 520)
        {
            ucAcceptiveModeIndex = _MODE_1920x1080p_50Hz;
        }
        else
        {
            if(stModeInfo.IVTotal < 1110)
            {
                ucAcceptiveModeIndex = _MODE_1680x1050_60HZ;
            }
            else
            {
                // V014 VGA Patch Note (2) Modify 20100526 Start
                // Patch Reason : Mode search update
                /*
                if(stModeInfo.IVTotal < 1118)
                */
                if(stModeInfo.IVTotal < 1117)
                // V014 VGA Patch Note (2) Modify 20100526 End
                {
                    ucAcceptiveModeIndex = _MODE_1920x1080_60HZ_RB;
                }
                else
                {
                    ucAcceptiveModeIndex = _MODE_1920x1080_60HZ;
                }
            }
        }
    }
    else if(stModeInfo.IVTotal < 1248)
    {
        if(stModeInfo.IVFreq < 630)
        {
            if(abs(usIHSyncpulseCnt - 9) <= 5)
            {
                ucAcceptiveModeIndex = _MODE_1920x1200_60HZ_RB;
            }
            else
            {
                ucAcceptiveModeIndex = _MODE_1920x1200_60HZ;
            }
        }
    }
    else if(stModeInfo.IVTotal < 1300)
    {
        if( stModeInfo.IVFreq < 630 )
        {
            if(abs(usIHSyncpulseCnt - 10) <= 5)
            {
                ucAcceptiveModeIndex = _MODE_1600x1200_60HZ_RB;
            }
            else
            {
                ucAcceptiveModeIndex = _MODE_1600x1200_60HZ;
            }
        }
        else if( stModeInfo.IVFreq < 680 )
        {
            ucAcceptiveModeIndex = _MODE_1600x1200_65HZ;
        }
        else
        {
            ucAcceptiveModeIndex = _MODE_1600x1200_70HZ;
        }
    }

    ucAcceptiveModeIndex = CModeAdditionalSearch(ucAcceptiveModeIndex);

    return ucAcceptiveModeIndex;
}
// V012 Modify 20100324 End

//--------------------------------------------------
// Description  : Check FIFO mode for VGA
// Input Value  : Mode number
// Output Value : FIFO mode number
//--------------------------------------------------
BYTE CModeCheckFIFOModeVGA(BYTE ucModeCnt)
{
    BYTE cnt0, cnt1;
    StructModeUserFIFODataType stFIFOModeTemp;

    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
    /*
    for(cnt0 = 0; cnt0 < 4; cnt0++)
    {
        CEepromLoadUserFIFOModeData(cnt0, pData);

        for(cnt1 = 0; cnt1 < 4; cnt1++)
        {
            if(CModeCompareFIFOModeVGA(cnt1, ucModeCnt) == _TRUE)
            {
                return (cnt0 * 4 + cnt1);
            }
        }
    }

    if(stSystemData.UserFIFOMode >= 15)
    {
        stSystemData.UserFIFOMode = 0;
    }
    else
    {
        stSystemData.UserFIFOMode++;
    }
    */
#if(_FIFO_MODE_ONLY == _ON)
    for(cnt0 = 0; cnt0 < 16; cnt0++)
    {
        CEepromLoadUserFIFOModeData(cnt0, pData);

        for(cnt1 = 0; cnt1 < 4; cnt1++)
        {
            if(CModeCompareFIFOModeVGA(cnt1, ucModeCnt) == _TRUE)
            {
                g_ucFIFOModeNum = (cnt0 * 4 + cnt1);
                return (cnt0 * 4 + cnt1);
            }
        }
    }
#else
    for(cnt0 = 0; cnt0 < 4; cnt0++)
    {
        CEepromLoadUserFIFOModeData(cnt0, pData);

        for(cnt1 = 0; cnt1 < 4; cnt1++)
        {
            if(CModeCompareFIFOModeVGA(cnt1, ucModeCnt) == _TRUE)
            {
                return (cnt0 * 4 + cnt1);
            }
        }
    }
#endif

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
#else
    if(stSystemData.UserFIFOMode >= 15)
    {
        stSystemData.UserFIFOMode = 0;
    }
    else
    {
        stSystemData.UserFIFOMode++;
    }
#endif
    // V013 VGA Patch Note (11) Modify 20100416 End

    stFIFOModeTemp.ModeNum = ucModeCnt;
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

    stModeUserData.HPosition = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHStartPos;
    stModeUserData.VPosition = tINPUTMODE_PRESET_TABLE[ucModeCnt].IVStartPos;
    stModeUserData.Clock = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHTotal;
    stModeUserData.Phase = 0;
    CEepromSaveModeData(stSystemData.UserFIFOMode);

    CEepromSaveSystemData();

    return stSystemData.UserFIFOMode;
}

//--------------------------------------------------
// Description  : Compare mode in FIFO memory
// Input Value  : Mode number and FIFO mode number
// Output Value : _TRUE if both are correspondence
//--------------------------------------------------
bit CModeCompareFIFOModeVGA(BYTE ucNum, BYTE ucModeCnt)
{
    StructModeUserFIFODataType stFIFOModeTemp;

    stFIFOModeTemp.ModeNum = (pData[ucNum * 4]);
    stFIFOModeTemp.IHFreq = ((WORD)(pData[ucNum * 4 + 1] & 0x0f) << 8) | pData[ucNum * 4 + 2];

    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
    /*
    stFIFOModeTemp.IVFreq = ((WORD)(pData[ucNum * 4 + 1] & 0xf0) << 4) | pData[ucNum * 4 + 3];
    */
#if(_FIFO_MODE_ONLY == _ON)
    stFIFOModeTemp.IVFreq = ((WORD)(pData[ucNum * 4 + 1] & 0x70) << 4) | pData[ucNum * 4 + 3];
#else
    stFIFOModeTemp.IVFreq = ((WORD)(pData[ucNum * 4 + 1] & 0xf0) << 4) | pData[ucNum * 4 + 3];
#endif

    // V014 VGA Patch Note (2) Modify 20100528 Start
    // Patch Reason : Mode search update.
    // Mode Search Type should only be checked for FIFO Mode Only.
    /*
    if(GET_MODE_SEARCH_TYPE() != (bit)(pData[ucNum * 4 + 1] & 0x80))
    {
        return _FALSE;
    }
    */
#if(_FIFO_MODE_ONLY == _ON)
    if(GET_MODE_SEARCH_TYPE() != (bit)(pData[ucNum * 4 + 1] & 0x80))
    {
        return _FALSE;
    }
#endif
    // V014 VGA Patch Note (2) Modify 20100528 End

    // V013 VGA Patch Note (11) Modify 20100416 End

    if(stFIFOModeTemp.ModeNum != ucModeCnt)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IVFreq - stFIFOModeTemp.IVFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreqTolerance)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IHFreq - stFIFOModeTemp.IHFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IHFreqTolerance)
    {
        return _FALSE;
    }

    return _TRUE;
}

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Search mode for DVI and HDMI
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchModeDVI(void)
{
    BYTE modecnt = 0 , temp = 0;

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))


    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) != _D0_DP_PORT) && (GET_INPUTPORT_TYPE(g_ucSearchIndex) != _D1_DP_PORT))
    {
        if(CSyncCheckTMDSFreq() == _FALSE)
        {
            CModeResetMode();
            return _MODE_NOSIGNAL;
        }

        if((GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI))
        {
            CScalerPageSelect(_PAGE2);
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, 0x02, ~_BIT3, _BIT3);
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, 0x02, ~_BIT1, 0x00);
            CTimerDelayXms(5);
            CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x02);
            CScalerRead(_P2_HDMI_DATA_PORT_CA, 1, &pData[0], _NON_AUTOINC);

            if((pData[0] & 0x02) == 0x02)
            {
                CModeResetMode();
                return _MODE_NOSIGNAL;
            }
        }

        if(GET_INPUTSOURCE_TYPE() == _SOURCE_DVI)
        {
            if(CHdmiFormatDetect() == _TRUE) // HDMI
            {
                CModeResetMode();
                return _MODE_NOSIGNAL;
            }
        }
        else if(GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
        {
            if(CHdmiFormatDetect() == _FALSE) // DVI
            {
                CModeResetMode();
                return _MODE_NOSIGNAL;
            }
        }
    }
#endif

    stModeInfo.IHTotal = 0;
    stModeInfo.IVHeight = 0;
    stModeInfo.IHWidth = 0;

    CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, _BIT0); // Digital Measure
    CScalerPageSelect(_PAGE2);
    CScalerRead( _P2_TMDS_DPC0_B4, 1, &pData[3], _NON_AUTOINC);
    temp = pData[3] & 0x07;

    if(((temp == 0x05) || (temp == 0x06) || (temp == 0x07)) && (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)) // deep color mode input
    {
#if(_HDMI_SUPPORT == _ON)
        CAdjustDeepColorMode();
#endif

        CTimerDelayXms(5); //wait deep color PLL stable

        // Wait Phase Counter
        pData[15] = 0;

        do
        {
            CScalerPageSelect(_PAGE2);
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, 0x82, 0x18);
            CTimerDelayXms(1);
            CScalerGetDataPortByte(_P2_HDMI_ADDR_PORT_C9, 0x82, 1, &pData[5], _NON_AUTOINC);
            pData[15]++;

        }while(((pData[5] & 0x02) != 0) && (pData[15] < 10));

        if(pData[15] >= 10)
        {
            CModeResetMode();
            return _MODE_NOSIGNAL;
        }

        SET_DEEPCOLORMODE();

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        CAdjustDither(tDITHER_SEQ_TABLE_0, tDITHER_TABLE_10_TO_8_I_DOMAIN, tDITHER_TEMPOFFSET_TABLE, _INPUT_DITHER); //I Domain Dithering
#endif

        CScalerPageSelect(_PAGE2);
        CScalerSetByte(_P2_UP_DOWN_CTRL0_B5, 0xd8);

        CAdjustSyncProcessorMeasureStart();

        if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
        {
            CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT6, _BIT6);
            CScalerSetBit(_MEAS_HS_VS_HI_SEL_58, ~_BIT0, 0x00);
            CScalerRead(_MEAS_HS_PERIOD_H_52, 6, &pData[8], _AUTOINC);

            ((WORD *)pData)[0] = ((pData[8] & 0x0f) << 8) | pData[9];
            ((WORD *)pData)[1] = ((pData[10] & 0x0f) << 8) | pData[11];
            ((WORD *)pData)[2] = ((pData[12] & 0xf0) << 4) | pData[13];

            if((((WORD *)pData)[0] == 0) || (((WORD *)pData)[1] == 0) || (bit)(pData[10] & _BIT5))
            {
                modecnt = _MODE_NOSUPPORT;
            }
            else
            {
                // Save IH_TOTAL
                stModeInfo.IHTotal = ((WORD *)pData)[0] + 1;

                // Save input data enable width and height
                stModeInfo.IVHeight = ((WORD *)pData)[1] + 1;
                stModeInfo.IHWidth = ((WORD *)pData)[2] + 1;

                for(modecnt = 0; modecnt < _MAX_PRESET_MODE; modecnt++)
                {
                    if(CModeCompareModeDVI(modecnt))
                    {
                        break;
                    }
                }

#if(_TMDS_SHRINK_SUPPORT == _ON)
                stModeInfo.IVHeight = stModeInfo.IVHeight - (_TMDS_SHRINK_RANGE * 2);
                stModeInfo.IHWidth = stModeInfo.IHWidth - (_TMDS_SHRINK_RANGE * 2);
#endif  // End of  #if(_TMDS_SHRINK_SUPPORT == _ON)
            }
        }
        else
        {
            CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT5, 0x00);
            modecnt = _MODE_NOSUPPORT;
        }

    }
    else // 24 bit input including HDMI or DVI format !!
    {

        CLR_DEEPCOLORMODE();

        CAdjustSyncProcessorMeasureStart();

        if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
        {
            CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT6, _BIT6);
            CScalerSetBit(_MEAS_HS_VS_HI_SEL_58, ~_BIT0, 0x00);
            CScalerRead(_MEAS_HS_PERIOD_H_52, 6, &pData[8], _AUTOINC);

            ((WORD *)pData)[0] = ((pData[8] & 0x0f) << 8) | pData[9];
            ((WORD *)pData)[1] = ((pData[10] & 0x0f) << 8) | pData[11];
            ((WORD *)pData)[2] = ((pData[12] & 0xf0) << 4) | pData[13];

            if((((WORD *)pData)[0] == 0) || (((WORD *)pData)[1] == 0) || (bit)(pData[10] & _BIT5))
            {
                modecnt = _MODE_NOSUPPORT;
            }
            else
            {
                // Save IH_TOTAL
                stModeInfo.IHTotal = ((WORD *)pData)[0] + 1;

                // Save input data enable width and height
                stModeInfo.IVHeight = ((WORD *)pData)[1] + 1;
                stModeInfo.IHWidth = ((WORD *)pData)[2] + 1;

                if(stModeInfo.IVHeight >= stModeInfo.IHWidth)
                {
                    // V013 TMDS Patch Note (17) 20100422 Modify Start
                    // Patch Reason : Solve Dual Link DVI Issue.
                    /*
                    CModeResetMode();
                    */
                    if((stModeInfo.IHWidth == g_usIHWidthBackUp) && (stModeInfo.IVHeight == g_usIVHeightBackUp))
                    {
                        g_ucNoSupportCnt++;
                    }
                    else
                    {
                        g_ucNoSupportCnt = 0;
                        g_usIHWidthBackUp = stModeInfo.IHWidth;
                        g_usIVHeightBackUp = stModeInfo.IVHeight;
                    }

                    if(g_ucNoSupportCnt >= 3)
                    {
                        modecnt = _MODE_NOSUPPORT;
                    }
                    else
                    {
                        CModeResetMode();
                    }
                    // V013 TMDS Patch Note (17) 20100422 Modify End
                }

                for(modecnt = 0; modecnt < _MAX_PRESET_MODE; modecnt++)
                {
                    if(CModeCompareModeDVI(modecnt))
                    {
                        break;
                    }
                }

#if(_TMDS_SHRINK_SUPPORT == _ON)
                stModeInfo.IVHeight = stModeInfo.IVHeight - (_TMDS_SHRINK_RANGE * 2);
                stModeInfo.IHWidth = stModeInfo.IHWidth - (_TMDS_SHRINK_RANGE * 2);
#endif  // End of  #if(_TMDS_SHRINK_SUPPORT == _ON)
            }
        }
        else
        {
            CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT5, 0x00);
            modecnt = _MODE_NOSUPPORT;
        }

    }

    CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, 0x00); // Analog Measure

    // If no mode found, set to mode 0
    if(modecnt >= _MAX_PRESET_MODE)
    {
        modecnt = 0;
    }

    // We don't support input image large than 2048 active pixel or less than 240 active lines.
    // added deep color mode limitation
    if(GET_DEEPCOLORMODE())
    {
        CScalerPageSelect(_PAGE2);
        CScalerRead( _P2_TMDS_DPC0_B4, 1, &pData[3], _NON_AUTOINC);
        CTimerDelayXms(5);

        temp = pData[3] & 0x07;
        if(temp == 0x05)
        {  //30 bit 1920
            if((stModeInfo.IHWidth > 2560) || (stModeInfo.IVHeight < 240))
            {
                modecnt = _MODE_NOSUPPORT;
            }
        }
        else if(temp == 0x06)   //36 bit
        {
            if((stModeInfo.IHWidth > 3072) || (stModeInfo.IVHeight < 240))
            {
                modecnt = _MODE_NOSUPPORT;
            }
        }
        else if(temp == 0x07)     //48 bit
        {
            if((stModeInfo.IHWidth > 4096) || (stModeInfo.IVHeight < 240))
            {
                modecnt = _MODE_NOSUPPORT;
            }
        }
    }
    else
    {
        if((stModeInfo.IHWidth > 2048) || (stModeInfo.IVHeight < 240))
        {
            modecnt = _MODE_NOSUPPORT;
        }
    }

    return modecnt;
}

//--------------------------------------------------
// Description  : Compare mode for DVI
// Input Value  : Mode number
// Output Value : Retrun _TRUE if it's correspondence
//--------------------------------------------------
bit CModeCompareModeDVI(BYTE ucModeCnt)
{
    if(abs(stModeInfo.IHWidth - tINPUTMODE_PRESET_TABLE[ucModeCnt].IHWidth) > 3)
    {
        return _FALSE;
    }

    if(stModeInfo.IVHeight != tINPUTMODE_PRESET_TABLE[ucModeCnt].IVHeight)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IVFreq - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreqTolerance)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif  // End of #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)||(_DP_SUPPORT == _ON))

//----------------------------------------------------------------------------------------------------
// Mode Display Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Display active mode process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeDisplayActiveMode(void)
{
    switch(GET_INPUTSOURCE_TYPE())
    {
        case _SOURCE_VGA:

#if(_FRC_SUPPORT == _ON)
            // RGB Input
            SET_FRCRGBIN();
#endif
            CModeSetupModeVGA();
            break;

#if(_YPBPR_SUPPORT == _ON)

        case _SOURCE_YPBPR:
#if(_FRC_SUPPORT == _ON)
            // YUV Input
            CLR_FRCRGBIN();
#endif
            CYPbPrSetupMode();
            break;

#endif

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
        case _SOURCE_DVI:
        case _SOURCE_HDMI:
        case _SOURCE_DP:
#if(_FRC_SUPPORT == _ON)
            // Input source is the HDMI format
            if(!CHdmiFormatDetect())
            {
                // RGB Input
                SET_FRCRGBIN();
            }
#endif
            CModeSetupModeDVI();
            break;
#endif

#if(_VIDEO_SUPPORT == _ON)

        case _SOURCE_VIDEO8:
#if(_FRC_SUPPORT == _ON)
            // YUV Input
            CLR_FRCRGBIN();
#endif
            CVideoDisplaySet();
            break;

#endif

    }
}

//--------------------------------------------------
// Description  : Setup VGA mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupModeVGA(void)
{
    BYTE option = 0;

    // Load mode user data from eeprom
    CEepromLoadModeData(stModeInfo.ModeCurr);

    // Get information from mode table, such as IHTotal, IHStartPos, IHWidth, IVStartPos, IVHeight.
    CModeGetModeTableInfo();

    // V016 VGA Patch Note (11) Modify 20100830 Start
    // Patch Reason : Modify Color Space Load Data Position For OverScan.
#if(_COLOR_FORMAT_CONVERT == _ON)
    CModeGetCurrentModeColorFormat();
#endif
    // V016 VGA Patch Note (11) Modify 20100830 End

    // V014 VGA Patch Note (6) Modify 20100527 Start
    // Patch Reason : Modify Video Mode Can't Light On
    CModeConfirmClampPositionSetting();
    // V014 VGA Patch Note (6) Modify 20100527 End

    CModeCheckUserData();

// V012 Modify 20100317 Start
// V012 Patch Note (9) : Remove safe mode.
// Remove save mode on purpose, as there're still some issue with it.
/*
#if(_SAFE_MODE == _ON)
    if (stModeInfo.ModeCurr == _MODE_720x400_70HZ || stModeInfo.ModeCurr == _MODE_640x350_70HZ) //for 24w dos mode
    {
        CScalerSetBit(_VGIP_SIGINV_11, 0xff, 0x80);
        CScalerSetBit(_VGIP_ODD_CTRL_13, 0xff, 0x10);
    }
#endif
*/
// V012 Modify 20100317 End

    // Start up settings of VGA mode.
    CModeStartUpVGA();

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
    CModeOverScanSelect();
#endif
// V012 Modify 20100316 End

    // Get scaling option, Capture window setup, Scaling setup, Display setup
    CModeSetupDisplay();

    // Setup color processing
    CModeSetupColorProcess();

    CAdjustAdcGainOffset();

    CAdjustAdcClock(stModeUserData.Clock);

    CAdjustDcRestore();

    CAdjustHPosition();

    CAdjustVPosition();

    // V012 Modify 20100321 Start
    // V012 Patch Note (14) : Fix the issue that SOG interlace signal could not light up the display when  V sync pulse is only 1H.
    CModeCheckDVTotal();
    // V012 Modify 20100321 End

    // V013 VGA Patch Note (16) Modify 20100422 Start
    // Patch Reason : Add fineTune display position for VGA interlace mode.
    CFrameSyncAnalogFineTune();
    // V013 VGA Patch Note (16) Modify 20100422 End

#if(_FRC_SUPPORT == _ON)
    if(!GET_FRCSTATUS())
    {
        CModeSetFIFOForFrameSync();
#else
    {
#endif
        pData[0] = CFrameSyncDo();

        if(pData[0] == 2)
        {
            CModeResetMode();
            return;
        }
    }

#if((_MEMORY_WORK_TYPE == _OD_ON_FRC_ON) || (_MEMORY_WORK_TYPE == _OD_OFF_FRC_ON))
    else
    {
#if(_FIELD_MERGE_SUPPORT == _ON)
        if(GET_FIELDMERGE_MODE())
        {
            CScalerSetBit(_VGIP_SIGINV_11, ~_BIT4, _BIT4);
        }
#endif
        // Disable video compensation & IVS-to-DVS-delay control by ODD when FRC
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0);
        CScalerSetBit(_FS_DELAY_FINE_TUNING_43, ~_BIT1, 0);
    }
#endif

    CAdjustADCClamp();

    CModeSetupEtcs(_FUNCTION_ENABLE);

}

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Setup mode DVI
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupModeDVI(void)
{
    BYTE option = 0;

    // Do initial settings of DVI mode.
    CModeStartUpDVI();

    if(GET_INPUTSOURCE_TYPE() == _SOURCE_NONE)
    {
        return;
    }

// V013 TMDS Patch Note (16) 20100422 Modify Start
// Patch Reason : Solve DVI Interlace Issue.
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_DVI) || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI))
    {
        CScalerPageSelect(_PAGE2);

        if(CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7) == _BIT7) // Digital Measure
        {
            stModeInfo.IVTotal = stModeInfo.IVStartPos + stModeInfo.IVHeight + 37;
        }
    }
// V013 TMDS Patch Note (16) 20100422 Modify End

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
    CModeOverScanSelect();
#endif
// V012 Modify 20100316 End

    // Get scaling option, Capture window setup, Scaling setup, Display setup
    CModeSetupDisplay();

    // Setup color processing
    CModeSetupColorProcess();

    //Issac 2006-09-12
    if(GET_INTERLACE_MODE())
    {
// V013 TMDS Patch Note (16) 20100422 Modify Start
// Patch Reason : Solve DVI Interlace Issue.
        /*
        CScalerSetBit(_VGIP_ODD_CTRL_13, (~_BIT6 | _BIT0), _BIT6);
        */
        CScalerPageSelect(_PAGE2);

        if(CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7) == _BIT7)
        {
            CScalerSetBit(_VGIP_ODD_CTRL_13, ~(_BIT0), _BIT0);
        }
        else
        {
            CScalerSetBit(_VGIP_ODD_CTRL_13, ~(_BIT0), 0x00);
        }

        if(g_bIVSDelayOneLine == _TRUE)
        {
            CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT6, _BIT6);

            if(g_bIVSDelayOneLineInvert == _TRUE)
            {
                CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT7, _BIT7);
            }
            else
            {
                CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT7, 0x00);
            }
        }
        else
        {
            CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT6, 0x00);
        }

// V013 TMDS Patch Note (16) 20100422 Modify End

#if(_DP_SUPPORT == _ON)
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_DP)
        {
            CScalerSetBit(_SCALE_CTRL_32, ~(_BIT7 | _BIT6), _BIT7);
        }
        else
        {
            CScalerSetBit(_SCALE_CTRL_32, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
#else
        CScalerSetBit(_SCALE_CTRL_32, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif


#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        CScalerPageSelect(_PAGE5);
        CScalerSetBit(_P5_SDRF_IN1_SDR_CTRL_B9, ~_BIT7, _BIT7);//For interlace mode odd field toggle
#endif

        CFrameSyncFineTune(_EVEN);
    }

#if(_FRC_SUPPORT == _ON)
    if(!GET_FRCSTATUS())
    {
        CModeSetFIFOForFrameSync();
#else
    {
#endif
        pData[0] = CFrameSyncDo();

        if(pData[0] == 2)
        {
            CModeResetMode();
            return;
        }
    }
#if((_MEMORY_WORK_TYPE == _OD_ON_FRC_ON) || (_MEMORY_WORK_TYPE == _OD_OFF_FRC_ON))
    else
    {
#if(_FIELD_MERGE_SUPPORT == _ON)
        if(GET_FIELDMERGE_MODE())
        {
            CScalerSetBit(_VGIP_SIGINV_11, ~_BIT4, 0x00);
        }
#endif
        // Disable video compensation & IVS-to-DVS-delay control by ODD when FRC
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0x00);
        CScalerSetBit(_FS_DELAY_FINE_TUNING_43, ~_BIT1, 0x00);
    }
#endif

    CAdjustTMDSCaptureCheck();

#if(_TMDS_SHRINK_SUPPORT == _ON)
#if(_SCALER_TYPE == 2472D)
    CScalerRead(_IPH_ACT_STA_H_14, 2, pData, _AUTOINC);
    ((WORD *)pData)[1] = (((WORD)(pData[0] & 0x07)) << 8) | pData[1];
    CScalerRead(_IPV_ACT_STA_H_18, 2, pData, _AUTOINC);
    ((WORD *)pData)[2] = (((WORD)(pData[0] & 0x07)) << 8) | pData[1];
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerRead(_IPH_ACT_STA_H_14, 1, &pData[0], _NON_AUTOINC);
    CScalerRead(_IPH_ACT_WID_L_17, 1, &pData[1], _NON_AUTOINC);
    ((WORD *)pData)[1] = (((WORD)(pData[0] & 0x0F)) << 8) | pData[1];
    CScalerRead(_IPV_ACT_STA_H_18, 1, &pData[0], _NON_AUTOINC);
    CScalerRead(_IPV_ACT_LEN_L_1B, 1, &pData[1], _NON_AUTOINC);
    ((WORD *)pData)[2] = (((WORD)(pData[0] & 0x0F)) << 8) | pData[1];
#else
    No Setting !!
#endif // End of #if(_SCALER_TYPE == _RTD2472D)

    ((WORD *)pData)[1] = ((WORD *)pData)[1] + _TMDS_SHRINK_RANGE;
    ((WORD *)pData)[2] = ((WORD *)pData)[2] + _TMDS_SHRINK_RANGE;
#if(_SCALER_TYPE == 2472D)
    CScalerSetByte(_IPH_ACT_STA_H_14, pData[2] & 0x07);
    CScalerSetByte(_IPH_ACT_STA_L_15, pData[3]);
    CScalerSetBit(_IPV_ACT_STA_H_18, ~(_BIT2 | _BIT1 | _BIT0), pData[4] & 0x07);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerSetByte(_IPH_ACT_STA_H_14, pData[2] & 0x0F);
    CScalerSetByte(_IPH_ACT_STA_L_15, pData[3]);
    CScalerSetBit(_IPV_ACT_STA_H_18, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), pData[4] & 0x0F);
#else
    No Setting !!
#endif // End of #if(_SCALER_TYPE == _RTD2472D)

    CScalerSetByte(_IPV_ACT_STA_L_19, pData[5]);

    CScalerSetByte(_IVS2DVS_DELAY_LINES_40, _TMDS_SHRINK_RANGE);

#endif  // End of #if(_TMDS_SHRINK_SUPPORT == _ON)

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))
    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) != _D0_DP_PORT) && (GET_INPUTPORT_TYPE(g_ucSearchIndex) != _D1_DP_PORT))
    {
        if(CSyncCheckTMDSFreq() == _FALSE)
        {
            CModeResetMode();
            return;
        }

        if((GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI))
        {
            CScalerPageSelect(_PAGE2);
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, 0x02, ~_BIT3, _BIT3);
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, 0x02, ~_BIT1, 0x00);
            CTimerDelayXms(5);
            CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x02);
            CScalerRead(_P2_HDMI_DATA_PORT_CA, 1, &pData[0], _NON_AUTOINC);

            if((pData[0] & 0x02) == 0x02)
            {
                CModeResetMode();
                return;
            }
        }
    }
#endif

    CModeSetupEtcs(_FUNCTION_DISABLE);

}
#endif  // End of #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)||(_DP_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Setup display
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupDisplay(void)
{
    BYTE option = 0;

    // Get scaling option
    option = CModeGetScaleSetting();

    // Capture window setup
    CModeSetCaptureWindow(option);

    // Scaling setup
    CModeSetScaling(option);

    // Display setup
    CModeSetDisplay(option);
}

//--------------------------------------------------
// Description  : Setup contrast and brightness
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupColorProcess(void)
{
#if(_YPBPR_SUPPORT == _ON)
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
#else
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
#endif
    {
        CEepromLoadAdcData();
	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage("CEepromLoadAdcData", 0);
	CDebugMessage("stAdcData.AdcGain.[_RED]",stAdcData.AdcGain[_RED]);
	CDebugMessage("stAdcData.AdcGain.[_GREEN]",stAdcData.AdcGain[_GREEN]);
	CDebugMessage("stAdcData.AdcGain.[_BLUE]",stAdcData.AdcGain[_BLUE]);
	
	CDebugMessage("stAdcData.AdcOffset.[_RED]",stAdcData.AdcOffset[_RED]);
	CDebugMessage("stAdcData.AdcOffset.[_GREEN]",stAdcData.AdcOffset[_GREEN]);
	CDebugMessage("stAdcData.AdcOffset.[_BLUE]",stAdcData.AdcOffset[_BLUE]);
	#endif
    }


#if(_SWITCH_INPUT_SOURCE == _OFF)

    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        CScalerSetDataPortBit(_HW_ACCESS_PORT_60, _HW_WINDOW_CTRL0_0C, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT2));
        CScalerSetDataPortBit(_HW_ACCESS_PORT_60, _HW_WINDOW_CTRL1_0D, ~(_BIT7 | _BIT6), _BIT6);
    }

#endif

    COsdDispColorProcess();

}

//--------------------------------------------------
// Description  : Setup other setings for display
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupEtcs(BYTE ucPar)
{
    CMiscEnableDoubleBuffer();
#if(_FRC_SUPPORT == _ON)
    if(GET_FRCSTATUS())
    {
        CScalerSetBit(_WATCH_DOG_CTRL0_0C, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
        CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00);
    }
    else
#endif
    {
        if((bit)CScalerGetBit(_VDISP_CTRL_28, _BIT3))
        {
            CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00);
        }
    }

    CAdjustDigitalFilter(_PHASE_ACCESS_PORT, _PHASE_THD_0, _DIV_VALUE_2, ucPar);
    CAdjustDigitalFilter(_NEG_SMEAR_ACCESS_PORT, _SMEAR_RING_THD_4, _DIV_VALUE_1, ucPar); //KEN 2005/09/23
    CAdjustDigitalFilter(_MISMATCH_ACCESS_PORT, _MISMATCH_THD_0, _DIV_VALUE_0, ucPar);
    CAdjustDigitalFilter(_NOISE_REDUCTION_PORT, _NOISE_REDUCTION_THD_7, _DIV_VALUE_0, ucPar);

    CAdjustDigitalFilter(_YPBPR_ACCESS_PORT, _YPBPR_ENABLE, _DIV_VALUE_0, ucPar);

    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
    {
        g_usVTotalTemp = stModeInfo.IVTotal;
        g_ucVSyncPulseWidthTemp = stModeInfo.IVSyncPulseCount;
    }

    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
    {
        if(CScalerGetBit(_SYNC_CTRL_49, _BIT2) == 0x00)
        {
            // Select Hsync Measure Source to DeHS or SeHS.
            CScalerSetBit(_SYNC_CTRL_49, ~_BIT2, _BIT2);

            if(CModeMeasureReady())
            {
                CModeMeasureData();

                // V012 Modify 20100402 Start
                // V012 Patch Note (29) : Fix the inaccurate Vfreq in OSD with SOG HORV/HEORV sync type.
                g_ucCoastLineCnt = (BYTE)(abs(g_usVTotalTemp - stModeInfo.IVTotal));
                // V012 Modify 20100402 End
            }
        }

        // V013 VGA Patch Note (7) Modify 20100412 Start
        // Patch Reason : Adjust Coast Region.
        CAdjustCoastRegion();
        // V013 VGA Patch Note (7) Modify 20100412 End
    }


    // V013 VGA Patch Note (28) Modify 20100518 Start
    // Patch Reason : Change the CMiscClearStatusRegister() to be use timing.
    /*
    CMiscClearStatusRegister();
    */
    // V013 VGA Patch Note (28) Modify 20100518 End

// V016 VGA Patch Note (11) Modify 20100830 Start
// Patch Reason : Modify Color Space Load Data Position For OverScan.
/*
// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#if(_COLOR_FORMAT_CONVERT == _ON)
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) || (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
        {
            g_bColorFormatStatus = _YUV_COLOR_FORMAT;
        }
        else
        {
            g_bColorFormatStatus = _RGB_COLOR_FORMAT;
        }
    }

    // V014 VGA Patch Note (6) Modify 20100527 Start
    // Patch Reason : Modify Video Mode Can't Light On
    CModeGetCurrentModeColorFormat();
    // V014 VGA Patch Note (6) Modify 20100527 End

#endif
// V012 Modify 20100304 End
*/
// V016 VGA Patch Note (11) Modify 20100830 End

    // V016 System Patch Note (31) Modify 20100909 Start
    // Patch Reason : Open Spread Spectrum after display setting.
    CAdjustDclkSpreadSpectrumRange(_DCLK_SPREAD_RANGE);
    // V016 System Patch Note (31) Modify 20100909 End

    // V013 VGA Patch Note (28) Modify 20100518 Start
    // Patch Reason : Change the CMiscClearStatusRegister() to be use timing.
    CMiscClearStatusRegister();
    // V013 VGA Patch Note (28) Modify 20100518 End
}

//--------------------------------------------------
// Description  : Get mode information from mode table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeGetModeTableInfo(void)
{
    BYTE modetemp;

    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        modetemp = stModeInfo.ModeCurr;
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);

        modetemp = pData[(stModeInfo.ModeCurr % 4) * 4];
    }

    // V016 VGA Patch Note (3) Modify 20100730 Start
    // Patch Reason : Modify 640x350_70 Timing to show blank on top and buttom.
    if(modetemp == _MODE_640x350_70HZ)
    {
        modetemp = _MODE_720x400_70HZ;
    }
    // V016 VGA Patch Note (3) Modify 20100730 End

    stModeInfo.IHTotal = tINPUTMODE_PRESET_TABLE[modetemp].IHTotal;
    stModeInfo.IHStartPos = tINPUTMODE_PRESET_TABLE[modetemp].IHStartPos;
    stModeInfo.IHWidth = tINPUTMODE_PRESET_TABLE[modetemp].IHWidth;

    stModeInfo.IVStartPos = tINPUTMODE_PRESET_TABLE[modetemp].IVStartPos;
    stModeInfo.IVHeight = tINPUTMODE_PRESET_TABLE[modetemp].IVHeight;

    CEepromLoadCenterModeData(stModeInfo.ModeCurr);
}

//--------------------------------------------------
// Description  : Startup settings for VGA
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeStartUpVGA(void)
{
    WORD pixelclock;

    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    CScalerSetBit(_P2_TMDS_OUTPUT_CTRL_A6, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // To imporve the FIFO efficiency only when input data rate is slow, and display data rate is high.
    CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Calculate pixel clock rate (round to MHz)
    pixelclock = (((DWORD)stModeInfo.IHFreq * (DWORD)stModeInfo.IHTotal) * 2 / (1000 * 10));
    pixelclock = (pixelclock >> 1) + (pixelclock & 0x01);

    // ADC differential mode and Set ADC bandwidth to reduce high frequency noise
    CScalerPageSelect(_PAGE0);
    if(pixelclock < 38)
    {
        CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);                    //75MHz
    }
    else if(pixelclock < 68)
    {
        CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));          //150MHz
    }
    else if(pixelclock < 160)
    {
        CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));          //300MHz
    }
    else
    {
        CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));  //500MHz
    }

    if(pixelclock < 50)
    {
        // V012 Modify 20100329 Start
        // V012 Patch Note (28) : Fix ADC configurations to reduce noise.
        /*
        CScalerSetByte(_P0_ADC_I_BAIS3_CA, 0x76);
        */
        CScalerSetByte(_P0_ADC_I_BAIS3_CA, 0x5A);
        // V012 Modify 20100329 End

    }
    else if(pixelclock < 200)
    {
        CScalerSetByte(_P0_ADC_I_BAIS3_CA, 0x5C);
    }
    else
    {
        CScalerSetByte(_P0_ADC_I_BAIS3_CA, 0x5E);
    }

    // V012 Modify 20100329 Start
    // V012 Patch Note (28) : Fix ADC configurations to reduce noise.
    // PGA Input GM Current 700uA
    CScalerSetBit(_P0_ADC_I_BAIS0_C7, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    CScalerSetBit(_P0_ADC_I_BAIS1_C8, ~(_BIT7 | _BIT6), _BIT7);
    // PGA Input offset Current 480uA
    CScalerSetBit(_P0_ADC_V_BIAS0_CC, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6));
    // V012 Modify 20100329 End

    CScalerPageSelect(_PAGE1);
    // Phase interpolation control load modified.   Marvin 0812
    if(pixelclock < 50)
    {
        CScalerSetBit(_P1_PLL_PHASE_INTERPOLATION_B5, ~(_BIT7 | _BIT6), 0x00);
    }
    else
    {
        CScalerSetBit(_P1_PLL_PHASE_INTERPOLATION_B5, ~(_BIT7 | _BIT6), _BIT6);
    }

    // Fine-tune R/G/B delay and enable the ADC frame-modulation
    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_RED_CTL_CF, ~(_BIT2 | _BIT1 | _BIT0), (_ADC_FINE_TUNE_DELAY_RED & 0x07));
    CScalerSetBit(_P0_ADC_GREEN_CTL_D0, ~(_BIT2 | _BIT1 | _BIT0), (_ADC_FINE_TUNE_DELAY_GREEN & 0x07));

    CScalerSetBit(_P0_ADC_BLUE_CTL_D1, ~(_BIT2 | _BIT1 | _BIT0), (_ADC_FINE_TUNE_DELAY_BLUE & 0x07));

#if(_SCALER_TYPE == _RTD2472D)
    CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);
    CScalerSetByte(_YUV_RGB_ACCESS_9D, 0x00);

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerSetByte(_YUV_RGB_CTRL_9C, 0x00);
    CScalerSetByte(_YUV_RGB_COEF_DATA_9D, 0x00);
#else
    No Setting !!
#endif // End of #if(_SCALER_TYPE == _RTD2472D)

    // HSYNC positive/negtive tracking
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_PLL_DIV_CTRL_A0, ~_BIT7, 0x00);
}

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Startup settings for DVI
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeStartUpDVI(void)
{
// V013 TMDS Patch Note (16) 20100422 Modify Start
// Patch Reason : Solve DVI Interlace Issue.
    WORD usIVStartPos = 0;
    WORD usIVEndPos = 0;
    WORD usIVHieghtEven = 0;
    WORD usIVHieghtOdd = 0;
    WORD usIVBoundary = 0;
// V013 TMDS Patch Note (16) 20100422 Modify End

    CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, 0x00);

    CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT0), (_BIT2 | _BIT0));

    CTimerWaitForEvent(_EVENT_IVS);

// V013 TMDS Patch Note (16) 20100422 Modify Start
// Patch Reason : Solve DVI Interlace Issue.
    CScalerSetBit(_AUTO_ADJ_CTRL1_7D, ~_BIT0, 0x00); // Clear Auto
// V013 TMDS Patch Note (16) 20100422 Modify End

    // V015 System Patch Note (6) Modify 20100630 Start
    // Patch Reason : Correct measure boundary extract bit setting according to each spec.
    /*
    pData[0] = HIBYTE(stModeInfo.IHTotal - 2);
    pData[1] = 0x02;
    pData[2] = LOBYTE(stModeInfo.IHTotal - 2);
    pData[3] = HIBYTE(stModeInfo.IVTotal - 2);
    pData[4] = 0x02;
    pData[5] = LOBYTE(stModeInfo.IVTotal - 2);
    */
    pData[0] = (HIBYTE(stModeInfo.IHTotal - 2) & 0x0F);
    pData[1] = 0x02;
    pData[2] = LOBYTE(stModeInfo.IHTotal - 2);
    pData[3] = (HIBYTE(stModeInfo.IVTotal - 2) & 0x0F);
    pData[4] = 0x02;
    pData[5] = LOBYTE(stModeInfo.IVTotal - 2);
    // V015 System Patch Note (6) Modify 20100630 End

// V013 TMDS Patch Note (16) 20100422 Modify Start
// Patch Reason : Solve DVI Interlace Issue.
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_DVI) || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI))
    {
        CScalerPageSelect(_PAGE2);
        if(CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7) == _BIT7) // DE only mode: use Digital Measure
        {
            CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, 0x00); // Analog Mode Measure

            CAdjustSyncProcessorMeasureStart();
            if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
            {
                // Pop up measurement result
                CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT6, _BIT6);
                CScalerSetBit(_MEAS_HS_VS_HI_SEL_58, ~_BIT0, 0x00);

                CScalerRead(_MEAS_VS_PERIOD_H_54, 2, &pData[10], _AUTOINC);
                ((WORD *)pData)[4] = ((pData[10] & 0x0f) << 8) | pData[11]; // Vtotal

                usIVBoundary = (((WORD *)pData)[4] + 1);

                // V015 System Patch Note (6) Modify 20100630 Start
                // Patch Reason : Correct measure boundary extract bit setting according to each spec.
                /*
                pData[3] = HIBYTE(usIVBoundary - 2);
                */
                pData[3] = (HIBYTE(usIVBoundary - 2) & 0x0F);
                // V015 System Patch Note (6) Modify 20100630 End

                pData[5] = LOBYTE(usIVBoundary - 2);

                CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, _BIT0);   // Digital Mode Measure
            }
            else
            {
                CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT5, 0x00);
                CModeResetMode();
            }
        }
    }

    // Set Auto Function Horizontal & Vertical Boundary
    CScalerWrite(_H_BOUNDARY_H_70, 6, pData, _AUTOINC);

    // Get stModeInfo.IHStartPos & stModeInfo.IVStartPos
    if(((GET_INPUTSOURCE_TYPE() == _SOURCE_DVI) || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)) && (GET_INTERLACE_MODE()))
    {
        // Disable interlace compensation function
        CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT6, 0x00);
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0x00);
        CScalerSetBit(_FS_DELAY_FINE_TUNING_43, ~_BIT1, 0x00);

        // Auto function only active when ODD signal is "0"
        CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), _BIT7);

        // Start Auto Function Tracking Function
        CScalerSetBit(_AUTO_ADJ_CTRL1_7D, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Wait for finish:
        // Worst case: (1 / 50Hz = 20ms) x 4(Frames) = 80ms + 5ms Tolerance
        if(CTimerPollingEventProc(85, CMiscAutoMeasurePollingEvent))
        {

            CScalerRead(_V_START_END_H_7E, 6, pData, _AUTOINC);

            CScalerPageSelect(_PAGE2);
            // IDEN horizontal Start
            stModeInfo.IHStartPos = ((((WORD)pData[3] & 0xf0) << 4) | (WORD)pData[4]) - ((CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7) == _BIT7) ? 16 - 14 : 18 - 14);

            // IDEN vertical Start
            stModeInfo.IVStartPos = (((WORD)pData[0] & 0xf0) << 4) | (WORD)pData[1];

            // IDEN vertical End
            usIVEndPos = (((WORD)pData[0] & 0x0f) << 8) | (WORD)pData[2];

            // IVHeight = IVEndPos  - IVStartPos
            usIVHieghtEven = usIVEndPos - stModeInfo.IVStartPos;
        }
        else
        {
            CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
            CModeResetMode();
        }

        // Auto function only active when ODD signal is "1"
        CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT7 | _BIT6));

        // Start Auto Function Tracking Function
        CScalerSetBit(_AUTO_ADJ_CTRL1_7D, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Wait for finish:
        // Worst case: (1 / 50Hz = 20ms) x 4(Frames) = 80ms + 5ms Tolerance
        if(CTimerPollingEventProc(85, CMiscAutoMeasurePollingEvent))
        {
            CScalerRead(_V_START_END_H_7E, 6, pData, _AUTOINC);

            // IDEN vertical Start
            usIVStartPos = (((WORD)pData[0] & 0xf0) << 4) | (WORD)pData[1];

            // IDEN vertical End
            usIVEndPos = (((WORD)pData[0] & 0x0f) << 8) | (WORD)pData[2];

            // IVHeight = IVEndPos  - IVStartPos
            usIVHieghtOdd = usIVEndPos - usIVStartPos;

            // Select min(stModeInfo.IVStartPos, usIVStartPos)
            if(stModeInfo.IVStartPos > usIVStartPos) // 0x80 > 0xC0 -> delay one line & No invert
            {
                CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
                stModeInfo.IVStartPos = usIVStartPos;
                g_bIVSDelayOneLine = _TRUE;
                g_bIVSDelayOneLineInvert = _FALSE;

            }
            else if(stModeInfo.IVStartPos < usIVStartPos) // 0x80 < 0xC0 -> delay one line & Invert
            {
                CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), _BIT7);
                g_bIVSDelayOneLine = _TRUE;
                g_bIVSDelayOneLineInvert = _TRUE;
            }
            else // 0x80 = 0xC0 -> No need to delay one line
            {
                g_bIVSDelayOneLine = _FALSE;
                g_bIVSDelayOneLineInvert = _FALSE;
            }

            // Select min(usIVHieght_1, usIVHieght_2)
            if(usIVHieghtEven < usIVHieghtOdd)
            {
                stModeInfo.IVHeight = usIVHieghtEven + 1;
            }
            else if(usIVHieghtEven >= usIVHieghtOdd)
            {
                stModeInfo.IVHeight = usIVHieghtOdd + 1;
            }
        }
        else
        {
            CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
            CModeResetMode();
        }
    }
    else // Else of if(GET_INTERLACE_MODE())
    {
        // Measure Active Region H/V Start
        CModeMeasureHVActiveStart();

        if(g_bDoModeResetMode == _TRUE)
        {
            CModeResetMode();
        }
    }

    /*
    if(CTimerPollingEventProc(50, CMiscAutoMeasurePollingEvent))
    {
        CScalerRead(_V_START_END_H_7E, 6, pData, _AUTOINC);

        // IDEN horizontal Start
        CScalerPageSelect(_PAGE2);
        stModeInfo.IHStartPos = ((((WORD)pData[3] & 0xf0) << 4) | (WORD)pData[4]) - ((CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7) == _BIT7) ? 16 - 14 : 18 - 14);

        // IDEN vertical Start
        stModeInfo.IVStartPos = (((WORD)pData[0] & 0xf0) << 4) | (WORD)pData[1];
    }
    else
    {
        CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
        CModeResetMode();
    }
    */
// V013 TMDS Patch Note (16) 20100422 Modify End
}
#endif  // End of #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)||(_DP_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Get scaling information
// Input Value  : None
// Output Value : Scaling information
//--------------------------------------------------
BYTE CModeGetScaleSetting(void)
{
    BYTE  option = 0;
    DWORD  ivheight;

#if(_DISP_INFO_BY_MODE == _ON)

    BYTE modetemp;

    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        modetemp = stModeInfo.ModeCurr;
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);

        modetemp = pData[(stModeInfo.ModeCurr % 4) * 4];
    }

    stDisplayInfo = tDISPLAY_PRESET_TABLE[modetemp];

#else

    stDisplayInfo.DHWidth = _PANEL_DH_WIDTH;
    stDisplayInfo.DVHeight = _PANEL_DV_HEIGHT;
    stDisplayInfo.DHTotal = _PANEL_DH_TOTAL;

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
/*
#if (_HDMI_OVERSCAN == _ON)

    ucOverScanH = 0;
    ucOverScanV = 0;

    if ((GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI) ||
        (GET_INPUTSOURCE_TYPE() == _SOURCE_DVI) &&
        (CHdmiFormatDetect()))
    {
        // Decide V overscan
        if (stModeInfo.IVHeight == (480 / 2))
        {
            ucOverScanV = 4;    // Just for example
        }
        else if (stModeInfo.IVHeight == (576 / 2))
        {
            ucOverScanV = 5;    // Just for example
        }
        else if (stModeInfo.IVHeight == (480))
        {
            ucOverScanV = 8;    // Just for example
        }
        else if (stModeInfo.IVHeight == (576))
        {
            ucOverScanV = 10;   // Just for example
        }
        else if (stModeInfo.IVHeight == (720))
        {
            ucOverScanV = 12;   // Just for example
        }
        else if (stModeInfo.IVHeight == (1080 / 2))
        {
            ucOverScanV = 9;    // Just for example
        }
        else if (stModeInfo.IVHeight == (1080))
        {
            ucOverScanV = 18;   // Just for example
        }

        // Decide H overscan
        if (stModeInfo.IHWidth == (720))
        {
            ucOverScanH = 12;   // Just for example
        }
        else if (stModeInfo.IHWidth == (1280))
        {
            ucOverScanH = 22;   // Just for example
        }
        else if (stModeInfo.IHWidth == (1440))
        {
            ucOverScanH = 24;   // Just for example
        }
        else if (stModeInfo.IHWidth == (1920))
        {
            ucOverScanH = 32;   // Just for example
        }
        else if (stModeInfo.IHWidth == (2880))
        {
            ucOverScanH = 64;   // Just for example
        }

#if(_MEMORY_WORK_TYPE != _OD_OFF_FRC_OFF)
        if(ucOverScanH % 8)
        {
            ucOverScanH = ((ucOverScanH + 8) >> 3) << 3;
        }
#endif

        // Code below is for checking if overscan setting is reasonable.
        // You can remove it if you have confidence that overscan setting is always suitable
        if (ucOverScanH > (stModeInfo.IHWidth / 32))
        {
            ucOverScanH = stModeInfo.IHWidth / 32;
        }
        if (ucOverScanV > (stModeInfo.IVHeight / 32))
        {
            ucOverScanV = stModeInfo.IVHeight / 32;
        }

        while (ucOverScanV != 0)
        {
            ((DWORD *)pData)[0] = (DWORD)(stDisplayInfo.DHTotal) * (DWORD)stModeInfo.IHFreq * (DWORD)(stDisplayInfo.DVHeight) / (stModeInfo.IVHeight - (2 * ucOverScanV)) / 10;

            if (((DWORD *)pData)[0] >= (DWORD)_PANEL_PIXEL_CLOCK_MAX * 1000)
            {
                ucOverScanV -= 1;
            }
            else
            {
                break;
            }
        }
        // End of checking

        stModeInfo.IHWidth  = stModeInfo.IHWidth - (2 * ucOverScanH);
        stModeInfo.IVHeight = stModeInfo.IVHeight - (2 * ucOverScanV);
    }
#endif  // End of #if (_HDMI_OVERSCAN == _ON)
*/
// V012 Modify 20100316 End

#endif  // End of #if(_DISP_INFO_BY_MODE == _ON)


    CFrameSyncModifyDVStartPos(_DVSTART_POS_ADJUSTING);

    // Modify OSD Reference Position
    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_OSD_REFERENCE_DEN_21, stDisplayInfo.DVStartPos - 4);

#if((_ASPECT_RATIO_SUPPORT == _OFF) && (_MEMORY_WORK_TYPE != _OD_OFF_FRC_OFF))

#if(_FRC_SUPPORT == _ON)
        CMemoryWorkingTypeDecide();
#endif

#elif((_ASPECT_RATIO_SUPPORT == _ON) && (_MEMORY_WORK_TYPE != _OD_OFF_FRC_OFF))

        if (GET_DISP_RATIO() == DISP_ORIGINAL_SIZE)
        {
            if(stModeInfo.IHWidth < stDisplayInfo.DHWidth)
            {
                stDisplayInfo.DHWidth = stModeInfo.IHWidth;
            }

            if(GET_INTERLACE_MODE() && (stModeInfo.IVHeight < (stModeInfo.IHWidth / 2)))
            {
                if((stModeInfo.IVHeight * 2) < stDisplayInfo.DVHeight)
                {
                    stDisplayInfo.DVHeight = (stModeInfo.IVHeight * 2);
                }
                else if((stModeInfo.IVHeight * 1) < stDisplayInfo.DVHeight)
                {
                    stDisplayInfo.DVHeight = stModeInfo.IVHeight;
                }
            }
            else
            {
                if((stModeInfo.IVHeight * 1) < stDisplayInfo.DVHeight)
                {
                    stDisplayInfo.DVHeight = stModeInfo.IVHeight;
                }
            }
        }
        else if (GET_DISP_RATIO() == DISP_FIXED_AR_IN)
        {
            ((DWORD *)pData)[0] = (DWORD)stModeInfo.IHWidth * _PANEL_DV_HEIGHT / stModeInfo.IVHeight;
            ((DWORD *)pData)[1] = (DWORD)stModeInfo.IVHeight * _PANEL_DH_WIDTH / stModeInfo.IHWidth;

            if(GET_INTERLACE_MODE() && (stModeInfo.IVHeight < (stModeInfo.IHWidth / 2)))
            {
                ((DWORD *)pData)[0] = ((DWORD *)pData)[0] / 2;
                ((DWORD *)pData)[1] = ((DWORD *)pData)[1] * 2;
            }

            if (((DWORD *)pData)[0] <= _PANEL_DH_WIDTH)
            {
                // Screen is wider than image (FRC may be no need)
                stDisplayInfo.DHWidth = ((DWORD *)pData)[0];
                stDisplayInfo.DVHeight = _PANEL_DV_HEIGHT;

                stDisplayInfo.DHWidth &= 0xFFFE;   // For dual-port panel
            }
            else if (((DWORD *)pData)[1] <= _PANEL_DV_HEIGHT)
            {
                // Image is wider than screen (FRC needed)
                stDisplayInfo.DHWidth = _PANEL_DH_WIDTH;
                stDisplayInfo.DVHeight = ((DWORD *)pData)[1];
            }
            else
            {
                // Image is too big!!
            }
        }

#if(_FRC_SUPPORT == _ON)
        CMemoryWorkingTypeDecide();
#endif

        // Unable to do original-size-display, restore setting to full-screen-display
        if ((stDisplayInfo.DVHeight < _PANEL_DV_HEIGHT) && (!GET_FRCSTATUS()))
        {
            stDisplayInfo.DHWidth = _PANEL_DH_WIDTH;
            stDisplayInfo.DVHeight = _PANEL_DV_HEIGHT;
        }

        // Change DVStartPos to image V start position
        if (stDisplayInfo.DVHeight < _PANEL_DV_HEIGHT)
        {
            stDisplayInfo.DVStartPos += (_PANEL_DV_HEIGHT - stDisplayInfo.DVHeight) / 2;
        }

#endif // End of #if((_ASPECT_RATIO_SUPPORT == _OFF) && (_MEMORY_WORK_TYPE != _OD_OFF_FRC_OFF))

#if(_FIELD_MERGE_SUPPORT == _ON)
        if(GET_FIELDMERGE_MODE())
        {
            ivheight = stModeInfo.IVHeight * 2;
        }
        else
        {
            ivheight = stModeInfo.IVHeight;
        }
#else
        ivheight = stModeInfo.IVHeight;
#endif

//    if(stModeInfo.IVHeight < stDisplayInfo.DVHeight)        option |= _BIT0;    // bit 0 : V scale-up
//    if(stModeInfo.IVHeight > stDisplayInfo.DVHeight)        option |= _BIT1;    // bit 1 : V scale-down
      if(ivheight < stDisplayInfo.DVHeight)
      {
          option |= _BIT0;    // bit 0 : V scale-up
      }
      if(ivheight > stDisplayInfo.DVHeight)
      {
          option |= _BIT1;    // bit 1 : V scale-down
      }

    if(stModeInfo.IHWidth < stDisplayInfo.DHWidth)
    {
        option |= _BIT2;    // bit 2 : H scale-up
    }
    if(stModeInfo.IHWidth > stDisplayInfo.DHWidth)
    {
        option |= _BIT3;    // bit 3 : H scale-down
    }

    return option;
}

//--------------------------------------------------
// Description  : Set capture window
// Input Value  : Scaling information
// Output Value : None
//--------------------------------------------------
void CModeSetCaptureWindow(BYTE ucOption)
{
    WORD usTemp = 0;

    // Calculate IHS delay and H Capture Start
    switch(GET_INPUTSOURCE_TYPE())
    {
        case _SOURCE_VGA:
#if(_YPBPR_SUPPORT == _ON)
        case _SOURCE_YPBPR:
#endif
            // Cal H Capture Start as AdjustPhase
            if(stModeUserCenterData.CenterHPos < (_IHS_START_BIAS * 4))
            {
                g_usHStartBias = (stModeUserCenterData.CenterHPos) / 2 - 2;
                usTemp = (stModeUserCenterData.CenterHPos) / 2 + (stModeUserCenterData.CenterHPos % 2);
            }
            else
            {
                g_usHStartBias = _IHS_START_BIAS * 2;
                usTemp = (stModeUserCenterData.CenterHPos - g_usHStartBias) - 2;
            }
            break;

        case _SOURCE_DVI:
        case _SOURCE_HDMI:
        case _SOURCE_DP:
        default:
            g_usHStartBias = _IHS_START_BIAS;
            usTemp = stModeInfo.IHStartPos + _CAPTURE_HDELAY - (g_usHStartBias + _PROGRAM_HDELAY);

            // IHS delay must be less than IHS Start otherwise Input Hsync Error (CR[02]-Bit[5]) will be occurred.
            if(g_usHStartBias > (stModeInfo.IHStartPos + _CAPTURE_HDELAY - _PROGRAM_HDELAY - 16))
            {
                g_usHStartBias = (stModeInfo.IHStartPos + _CAPTURE_HDELAY - _PROGRAM_HDELAY - 16);
            }

            break;
    }

#if(_FRC_SUPPORT == _ON)

    // Get IVS delay
    if(GET_FRCSTATUS())
    {
        g_ucVStartBias = stModeInfo.IVStartPos > (_PROGRAM_VDELAY + 4) ? stModeInfo.IVStartPos - (_PROGRAM_VDELAY + 4) : 0;
    }
    else
    {
        g_ucVStartBias = 0;
        g_ucVStartBias = CAdjustIVS2DVSDelay(ucOption);
    }

#else

    // Get IVS delay
    g_ucVStartBias = 0;
    g_ucVStartBias = CAdjustIVS2DVSDelay(ucOption);

#endif  // End of #if(_FRC_SUPPORT == _ON)

    // IVS delay must be less than IVS Start otherwise Input Vsync Error (CR[02]-Bit[6]) will be occurred.
    if(g_ucVStartBias > stModeInfo.IVStartPos)
    {
        g_ucVStartBias = stModeInfo.IVStartPos;
    }

#if(_SCALER_TYPE == _RTD2472D)
    // Set H Capture window
    CScalerSetBit(_IPH_ACT_STA_H_14, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(usTemp) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_STA_L_15, LOBYTE(usTemp));
    CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(stModeInfo.IHWidth) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_WID_L_17, LOBYTE(stModeInfo.IHWidth));
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    // Set H Capture window
    CScalerSetBit(_IPH_ACT_STA_H_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usTemp) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_STA_L_15, LOBYTE(usTemp));
    CScalerSetBit(_IPH_ACT_STA_H_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (HIBYTE(stModeInfo.IHWidth) << 4));
    CScalerSetByte(_IPH_ACT_WID_L_17, LOBYTE(stModeInfo.IHWidth));
#else
    No Setting !!
#endif

    g_usCaptureStart = usTemp;

    // Calculate V Capture Start
    usTemp = stModeInfo.IVStartPos - (g_ucVStartBias + _PROGRAM_VDELAY);

    if((CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT0)) == _BIT0) // Capture Window Unlock
    {
        if((usTemp <= _ADJUST_APLL_STABLE_COUNT))
        {
            if(g_ucVStartBias >= (_ADJUST_APLL_STABLE_COUNT + 1 - usTemp))
            {
                g_ucVStartBias = g_ucVStartBias - (_ADJUST_APLL_STABLE_COUNT + 1 - usTemp);
                usTemp = stModeInfo.IVStartPos - (g_ucVStartBias + _PROGRAM_VDELAY);
            }
        }
    }

#if(_SCALER_TYPE == _RTD2472D)
    // Set V Capture window
    CScalerSetBit(_IPV_ACT_STA_H_18, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(usTemp) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_STA_L_19, LOBYTE(usTemp));
    CScalerSetBit(_IPV_ACT_LEN_H_1A, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(stModeInfo.IVHeight) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_LEN_L_1B, LOBYTE(stModeInfo.IVHeight));
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    // Set V Capture window
    CScalerSetBit(_IPV_ACT_STA_H_18, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usTemp) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_STA_L_19, LOBYTE(usTemp));
    CScalerSetBit(_IPV_ACT_STA_H_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (HIBYTE(stModeInfo.IVHeight) << 4));
    CScalerSetByte(_IPV_ACT_LEN_L_1B, LOBYTE(stModeInfo.IVHeight));
#endif

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
    g_usCaptureStartV = usTemp;
#endif
// V012 Modify 20100316 End

    // Set internal input H sync delay
    CAdjustIHSDelay(g_usHStartBias + _PROGRAM_HDELAY);

    // Set internal input V sync delay
    CAdjustIVSDelay(g_ucVStartBias + _PROGRAM_VDELAY);

}

//--------------------------------------------------
// Description  : Set scaling factor settings
// Input Value  : Scaling information
// Output Value : None
//--------------------------------------------------
void CModeSetScaling(BYTE ucOption)
{

#if(_FIELD_MERGE_SUPPORT == _ON)
    if(GET_FIELDMERGE_MODE())
    {
        stModeInfo.IVHeight = stModeInfo.IVHeight * 2;
    }
#endif

    // Set window size before scale up
    if(ucOption & _BIT3)
    {
        // H scale-down
#if(_SCALER_TYPE == _RTD2472D)
        pData[0] = (BYTE)((stDisplayInfo.DHWidth >> 4) & 0x70);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        pData[0] = (BYTE)((stDisplayInfo.DHWidth >> 4) & 0xF0);

#else
    No Setting !!

#endif// End of #if(_SCALER_TYPE == _RTD2472D)

        pData[1] = LOBYTE(stDisplayInfo.DHWidth);
    }
    else
    {
        // No H scale-down
#if(_SCALER_TYPE == _RTD2472D)
        pData[0] = (BYTE)((stModeInfo.IHWidth >> 4) & 0x70);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        pData[0] = (BYTE)((stModeInfo.IHWidth >> 4) & 0xF0);

#else
    No Setting !!

#endif // End of #if(_SCALER_TYPE == _RTD2472D)
        pData[1] = LOBYTE(stModeInfo.IHWidth);
    }

    if(ucOption & _BIT1)
    {
        // V scale-down
#if(_SCALER_TYPE == _RTD2472D)
        pData[0] = pData[0] | (HIBYTE(stDisplayInfo.DVHeight) & 0x07);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        pData[0] = pData[0] | (HIBYTE(stDisplayInfo.DVHeight) & 0x0F);

#else
    No Setting !!

#endif  // End of #if(_SCALER_TYPE == _RTD2472D)
        pData[2] = LOBYTE(stDisplayInfo.DVHeight);
    }
    else
    {
        // No V scale-down
#if(_SCALER_TYPE == _RTD2472D)
        pData[0] = pData[0] | (HIBYTE(stModeInfo.IVHeight) & 0x07);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        pData[0] = pData[0] | (HIBYTE(stModeInfo.IVHeight) & 0x0F);

#else
    No Setting !!

#endif // End of #if(_SCALER_TYPE == _RTD2472D)
        pData[2] = LOBYTE(stModeInfo.IVHeight);
    }

    CScalerSetByte(_FIFO_ACCESS_PORT_30, _FIFO_DWRWL_H_BSU_00);
    CScalerWrite(_FIFO_DATA_PORT_31, 3, pData, _NON_AUTOINC);

#if(_FRC_SUPPORT == _ON)
    ((WORD *)pData)[2] = ((pData[0] & 0xf0) << 4) | pData[1];
    ((WORD *)pData)[3] = ((pData[0] & 0x0f) << 8) | pData[2];

    if(GET_FRCSTATUS())
    {
#if(_FIELD_MERGE_SUPPORT == _ON)
        if(GET_FIELDMERGE_MODE())
        {
            CMemoryControlForFRC(((WORD *)pData)[2], ((WORD *)pData)[3] / 2);
        }
        else
        {
            CMemoryControlForFRC(((WORD *)pData)[2], ((WORD *)pData)[3]);
        }
#else
        CMemoryControlForFRC(((WORD *)pData)[2], ((WORD *)pData)[3]);
#endif
    }
    else
    {
        CScalerPageSelect(_PAGE5);
        CScalerSetByte(_P5_SDRF_MN_PRERD_VST_H_BC, 0x00);
        CScalerSetByte(_P5_SDRF_MN_PRERD_VST_L_BD, 0x00);
        // Issac-03-30 (Very Important!!)
        CScalerSetByte(_P5_SDRF_MN_PXL_NUM_H_BE, 0x00);
        CScalerSetByte(_P5_SDRF_MN_PXL_NUM_L_BF, 0x00);
    }
#endif

    // Write sharpness coefficient for scale-up
    CAdjustSharpness(stOsdUserData.Sharpness);

    // Config scaling
    if(ucOption & _BIT1)
    {
        CScalerSetBit(_SCALE_DOWN_CTRL_23, ~_BIT0, _BIT0);          // Turn on V scale-down
    }
    else
    {
        CScalerSetBit(_SCALE_DOWN_CTRL_23, ~_BIT0, 0x00);           // Turn off V scale-down
    }

    if(ucOption & _BIT3)
    {
        CScalerSetBit(_SCALE_DOWN_CTRL_23, ~_BIT1, _BIT1);          // Turn on H scale-down
    }
    else
    {
        CScalerSetBit(_SCALE_DOWN_CTRL_23, ~_BIT1, 0x00);           // Turn off H scale-down
    }

    if(ucOption & _BIT0)
    {
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT1, _BIT1);               // Turn on V scale-up
    }
    else
    {
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT1, 0x00);                // Turn off V scale-up
    }

    if(ucOption & _BIT2)
    {
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT0, _BIT0);               // Turn on H scale-up
    }
    else
    {
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT0, 0x00);                // Turn off H scale-up
    }



 // Set scale-down coefficient for RTD2472D
    if(ucOption & _BIT3)    // H scale-down
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)1 * 1048576 * stModeInfo.IHWidth;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] % stDisplayInfo.DHWidth) ? ((((DWORD *)pData)[3] / stDisplayInfo.DHWidth) + 1) : (((DWORD *)pData)[3] / stDisplayInfo.DHWidth);

        // H scale-down factor
        pData[4] = ((((DWORD *)pData)[3] * 16 / 1048576 - 16) & 0x3f);
        pData[5] = ((((DWORD *)pData)[3] >> 16) & 0xff);
        pData[6] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[7] = ((((DWORD *)pData)[3]) & 0xff);

    }
    else
    {
        pData[4] = 0x00;
        pData[5] = 0x10;
        pData[6] = 0x00;
        pData[7] = 0x00;
    }

    if(ucOption & _BIT1)    // V scale-down
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)2 * 131072 * stModeInfo.IVHeight / stDisplayInfo.DVHeight;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] >> 1) + (((DWORD *)pData)[3] & 0x01);

        // V scale-down factor
        pData[0] = ((((DWORD *)pData)[3] * 16 / 131072 - 16) & 0x3f);
        pData[1] = ((((DWORD *)pData)[3] >> 16) & 0x07);
        pData[2] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[3] = ((((DWORD *)pData)[3]) & 0xff);

        CScalerSetBit(_SCALE_DOWN_CTRL_23, ~_BIT2, 0x00);    // Diable V scale-down compensation
    }
    else
    {
        pData[0] = 0x00;
        pData[1] = 0x02;
        pData[2] = 0x00;
        pData[3] = 0x00;

        CScalerSetBit(_SCALE_DOWN_CTRL_23, ~_BIT2, 0x00);    // Diable V scale-down compensation
    }

    CScalerSetByte(_SD_ACCESS_PORT_24, 0x80);
    CScalerWrite(_SD_DATA_PORT_25, 8, pData, _NON_AUTOINC);
    CScalerSetByte(_SD_ACCESS_PORT_24, 0x00);


    // Set scale-up coefficient
    if(ucOption & _BIT2)    // H scale-up
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)2 * 1048576 * stModeInfo.IHWidth / stDisplayInfo.DHWidth;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] >> 1) + (((DWORD *)pData)[3] & 0x01);

        pData[0] = ((((DWORD *)pData)[3] >> 16) & 0x0f);
        pData[1] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[2] = ((((DWORD *)pData)[3]) & 0xff);
    }
    else
    {
        pData[0] = 0x0f;
        pData[1] = 0xff;
        pData[2] = 0xff;
    }

    if(ucOption & _BIT0)    // V scale-up
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)2 * 1048576 * stModeInfo.IVHeight / stDisplayInfo.DVHeight;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] >> 1) + (((DWORD *)pData)[3] & 0x01);

        pData[3] = ((((DWORD *)pData)[3] >> 16) & 0x0f);
        pData[4] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[5] = ((((DWORD *)pData)[3]) & 0xff);
    }
    else
    {
        pData[3] = 0x0f;
        pData[4] = 0xff;
        pData[5] = 0xff;
    }

    CScalerSetByte(_SU_ACCESS_PORT_33, 0x80);
    CScalerWrite(_SU_DATA_PORT_34, 6, pData, _NON_AUTOINC);
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x00);


#if(_NON_LINEAR_SCALING_FUCTION == _ON)

    CScalerDisableNonlinearScaleUp();

    if(GET_NON_LINEAR_SCALING_STATUS())
    {
        CTimerWaitForEvent(_EVENT_DEN_STOP);
        CScalerNonlinearScaleUp();
    }

#endif

    CScalerPageSelect(_PAGE0);
}

//--------------------------------------------------
// Description  : Set display
// Input Value  : Scaling information
// Output Value : None
//--------------------------------------------------
void CModeSetDisplay(BYTE ucOption)
{
    DWORD ulFreq;
    // Disable spread spectrum
    CAdjustDclkSpreadSpectrumRange(0);

    // Calculate and set display clock frequency for frame sync mode
    ((DWORD *)pData)[0] = (DWORD)(stDisplayInfo.DHTotal) * (DWORD)stModeInfo.IHFreq * (DWORD)(stDisplayInfo.DVHeight) / stModeInfo.IVHeight / 10;



#if(_FRC_SUPPORT == _ON)
    if(GET_FRCSTATUS())
    {
        // Calculate and set display clock frequency for FRC mode
        ((DWORD *)pData)[0] = (DWORD)(stDisplayInfo.DHTotal) * (DWORD)stModeInfo.IHFreq * (DWORD)(_PANEL_DV_TOTAL) / stModeInfo.IVTotal / 10;

        if(stModeInfo.IVFreq > _PANEL_MAX_FRAME_RATE)
        {
            // Issac-04-16 Begin
            WORD usDisplayRate;

            //((DWORD *)pData)[0] = (DWORD)(_PANEL_DH_TOTAL) * (_PANEL_DV_TOTAL) * (_PANEL_MAX_FRAME_RATE / 10) / 1000;

            //The 1440x900_75Hz mode is failed when doing Auto function in FRC mode.
            /*
            usDisplayRate = (((DWORD)_MEMORY_SPEED * 1000000 / stModeInfo.IHWidth / 24 * _MEMORY_BUS_WIDTH / 10 * 84)
                          - ((DWORD)stModeInfo.IVFreq * stModeInfo.IVTotal))
                          / _PANEL_DV_TOTAL * stDisplayInfo.DVHeight / stModeInfo.IVHeight;
            */
            usDisplayRate = (((DWORD)_MEMORY_SPEED * 1000000 / stModeInfo.IHWidth / 24 * _MEMORY_BUS_WIDTH / 10 * 83)
                          - ((DWORD)stModeInfo.IVFreq * stModeInfo.IVTotal))
                          / _PANEL_DV_TOTAL * stDisplayInfo.DVHeight / stModeInfo.IVHeight;

            if (usDisplayRate >= _PANEL_MAX_FRAME_RATE)
            {
                usDisplayRate = _PANEL_MAX_FRAME_RATE;
            }

            ((DWORD *)pData)[0] = (DWORD)(_PANEL_DH_TOTAL) * (_PANEL_DV_TOTAL) * (usDisplayRate / 10) / 1000;
            // Issac-04-16 End

            CAdjustPLL(_DPLL, ((DWORD *)pData)[0]);
        }
        else if(((DWORD *)pData)[0] >= (DWORD)_PANEL_PIXEL_CLOCK_MAX * 1000)
        {
            ((DWORD *)pData)[0] = (DWORD)_PANEL_PIXEL_CLOCK_MAX * 1000;
            CAdjustPLL(_DPLL, (DWORD)_PANEL_PIXEL_CLOCK_MAX * 1000);
        }
        else
        {
           ((DWORD *)pData)[0] -= 100;
            CAdjustPLL(_DPLL, ((DWORD *)pData)[0] - 100);
        }
    }
    else if(ucCurrState == _NOSUPPORT_STATE)
    {
//        CAdjustPLL(_DPLL, (DWORD)_PANEL_PIXEL_CLOCK_MAX * 1000);
        CAdjustPLL(_DPLL, (DWORD)_PANEL_PIXEL_CLOCK * 1000);
    }
    else
    {
        CAdjustPLL(_DPLL, ((DWORD *)pData)[0]);
    }
#else
    CAdjustPLL(_DPLL, ((DWORD *)pData)[0]);
#endif
    ulFreq = ((DWORD *)pData)[0];
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage(" ulFreq==", ulFreq);
//CDebugMessage(" stDisplayInfo.DHTotal==", stDisplayInfo.DHTotal);
///CDebugMessage(" stDisplayInfo.DHWidth==", stDisplayInfo.DHWidth);
//CDebugMessage(" stDisplayInfo.DVHeight==", stDisplayInfo.DVHeight);
//CDebugMessage(" stDisplayInfo.DVHeight==", stDisplayInfo.DVStartPos);
#endif
    // Set DH_TOTAL
    pData[0] = (HIBYTE(stDisplayInfo.DHTotal - 4) & 0x0f);
    pData[1] = (LOBYTE(stDisplayInfo.DHTotal - 4));
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DH_TOTAL_H_00);
    CScalerWrite(_DISP_DATA_PORT_2B, 2, pData, _NON_AUTOINC);

    // Calculate DV_TOTAL setting for watchdog
#if(_FRC_SUPPORT == _ON)
    if(GET_FRCSTATUS())
    {
        ((WORD *)pData)[2] = _PANEL_DV_TOTAL + 64;
    }
    else
#endif
        ((WORD *)pData)[2] = (DWORD)stModeInfo.IVTotal * (DWORD)(stDisplayInfo.DVHeight) / stModeInfo.IVHeight + 64;

    pData[0] = (HIBYTE(((WORD *)pData)[2]) & 0x0f);
    pData[1] = (LOBYTE(((WORD *)pData)[2]));
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DV_TOTAL_H_0B);
    CScalerWrite(_DISP_DATA_PORT_2B, 2, pData, _NON_AUTOINC);

    // Display horizontal start/end
    ((WORD *)pData)[4] = (_PANEL_DH_WIDTH - stDisplayInfo.DHWidth) / 2 + _PANEL_DH_START;
    ((WORD *)pData)[5] = ((WORD *)pData)[4] + stDisplayInfo.DHWidth;

    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DH_ACT_STA_H_05);
    CScalerWrite(_DISP_DATA_PORT_2B, 4, &pData[8], _NON_AUTOINC);

    // Display vertical
    ((WORD *)pData)[0] = stDisplayInfo.DVStartPos - ((_PANEL_DV_HEIGHT - stDisplayInfo.DVHeight) / 2);
    ((WORD *)pData)[1] = stDisplayInfo.DVStartPos;
    ((WORD *)pData)[2] = ((WORD *)pData)[1] + stDisplayInfo.DVHeight;
    ((WORD *)pData)[3] = ((WORD *)pData)[0] + _PANEL_DV_HEIGHT;

    CScalerSetByte(_DISP_ACCESS_PORT_2A, (0x80 | _DISP_DV_BKGD_STA_H_0E));
    CScalerWrite(_DISP_DATA_PORT_2B, 8, pData, _NON_AUTOINC);
    CScalerSetByte(_DISP_ACCESS_PORT_2A, 0x00);

    // Turn off full-line buffer
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT4, 0x00);

#if(_FRC_SUPPORT == _ON)
    if(GET_FRCSTATUS())
    {
        // Enable display timing
        if(GET_FRCDOUBLEFRAME())
        {
            CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));
        }
        else
        {
            CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT1 | _BIT0));//Anderson 080422 to Solve Frame Tear
        }


        // Enable the spread spectrum function
        CAdjustDclkSpreadSpectrumRange(_DCLK_SPREAD_RANGE);
        CMemoryAdjustIVS2DVSDelay(ulFreq);
    }
    else
#endif
    {
        CAdjustIVS2DVSDelay(ucOption);
        // Enable display timing
        CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT1 | _BIT0));
    }
    CMiscClearStatusRegister();
}

//----------------------------------------------------------------------------------------------------
// Other Mode Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Reset scalar setting before show OSD at no signal
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
void CModeResetShowOSD(void)
{
    CScalerSetBit(_HOST_CTRL_01, ~_BIT1, 0x00);

    CModeSetFreeRun();

    CScalerEnableDisplayTiming();
}
#endif

//--------------------------------------------------
// Description  : Reset mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeResetMode(void)
{
    // V014 System Patch Note (9) Modify 20100604 Start
    // Patch Reason : Turn off the backlight at the very beginning of mode reset procedure to avoid showing garbage.
    /////////////////////////////////////////////////////////////////////////////////
    // Please make sure turning off the backlight is the first step of mode reset. //
    /////////////////////////////////////////////////////////////////////////////////
    CPowerLightPowerOff();
    // V014 System Patch Note (9) Modify 20100604 End

// V013 TMDS Patch Note (16) 20100422 Modify Start
// Patch Reason : Solve DVI Interlace Issue.
    g_bDoModeResetMode = _FALSE;
// V013 TMDS Patch Note (16) 20100422 Modify End

#if(_DP_SUPPORT == _ON)

    g_bDpDisplayPass = _FALSE;

    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DP_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DP_PORT))
    {
        CDpSinkStatusSet(_FALSE);    //! Sink out of sync

#if(_DP_POWER_MANAGEMENT == _ON)
        if((g_ucDpPowerStatus != _DP_POWER_DOWN) && (CDpLinkStatusCheck() == _TRUE))
        {


            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_END;
            g_bDpSearchTimesReset = 1;
        }
        else if(g_ucDpPowerStatus == _DP_POWER_DOWN)
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_NONE;
        }
#else
        g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_END;
        g_bDpSearchTimesReset = 1;
#endif

        }
#endif

    // V014 System Patch Note (9) Modify 20100604 Start
    // Patch Reason : Turn off the backlight at the very beginning of mode reset procedure to avoid showing garbage.
    /*
    CPowerLightPowerOff();
    */
    // V014 System Patch Note (9) Modify 20100604 End

#if (_PANEL_TYPE == _CMO_LVDS_22_WSXGA_PLUS)
    CPowerPanelOff();
#endif

    CAdjustDisableWatchDog(_WD_ALL);

#if(_HDMI_SUPPORT == _ON)
    CScalerPageSelect(_PAGE2);
    CAdjustDisableHDMIWatchDog(_WD_AUDIO_FOR_TMDS_CLOCK | _WD_PACKET_VARIATION);

    //cyc:For 2880 input width.
//    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VCR_50, 0xf0, 0x00);
//    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_ACRCR_51, ~_BIT2, 0x00);

#if((_SCALER_TYPE == _RTD2472D))
    CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AOCR_62, 0x00);//Disable SPDIF/I2S Output
#endif

    SET_VIDEOMODECHANGE();
#endif

    if(ucCurrState == _SLEEP_STATE)
    {
        if(CScalerGetBit(_HOST_CTRL_01, _BIT1))
        {
            CScalerSetBit(_HOST_CTRL_01, ~_BIT1, 0x00);
            CTimerDelayXms(2); // wait for H/W stable
        }

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
        CMcuSelectFlashClk(_FLASH_CLK);
#endif
    }

    CScalerResetProcess();

#if(_SCALER_TYPE == _RTD2545LR)

#if((_HDCP_SUPPORT == _ON) && (_EMBEDDED_HDCP_KEY == _ON))
        CScalerPageSelect(_PAGE2);
        CScalerSetByte(_P2_HDCP_CTRL_C0, 0x06);

        CAdjustWriteHDCPKey(_P2_DEVICE_KEY_ACCESS_PORT_C1, 1, _NON_AUTOINC);

        CTimerDelayXms(30);
        CScalerSetByte(_P2_HDCP_CTRL_C0, 0x01);
#endif

#endif

#if(_OD_SUPPORT == _ON)
    CMemorySetODOnOff(_OFF);
#endif
    CModeSetFreeRun();

    if(GET_PANELPOWERSTATUS() == _OFF)
    {
        CScalerEnableDisplayTiming();
    }

    COsdFxDisableOsd();
    CModeAutoMeasureOff();
    CAdjustTMDSErrorCorrectionOn();
    CPowerPWMOn();
    CMiscClearStatusRegister();

    CTimerCancelTimerEvent(CMiscCheckToActiveEvent);

    CTimerCancelTimerEvent(CModeNoSignalEvent);
    CTimerCancelTimerEvent(CModeNoCableEvent);
    CTimerCancelTimerEvent(CModeNoSupportEvent);
    CTimerCancelTimerEvent(CModePowerSavingEvent);
    COsdBankSwitchCancelTimer();

#if(_DCR_MODE == _DCR_TYPE_3)
    g_usDCR5MinTimer = 0;
    CLR_DCR_ULTRA_MIN();
#endif

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))
    // do nothing
#else
    g_usTMDSFreq = 0;
#endif

    CLR_FIRST_ADCCLOCK();
    CLR_USE_TRANSITION_RESULT();
    CLR_FRAMESYNCSTATUS();
    CLR_MODESTABLE();
    CLR_INTERLACE_MODE();
#if(_FRC_SUPPORT == _ON)
    CLR_FRCSTATUS();
    CLR_FRC422STATUS();
#if(_FIELD_MERGE_SUPPORT == _ON)
    CLR_FIELDMERGE_MODE();
#endif
#endif
//avoid abnormal OD state on screen.
#if(_OD_SUPPORT == _ON)
    CLR_READYFORDISPLAY();
#endif

#if(_HDMI_SUPPORT == _ON)
    CLR_HDMIINPUT();

#if((_SCALER_TYPE == _RTD2472D))
    CLR_AUDIOPLLLOCKREADY();
    CLR_AVRESUME();
    CLR_AUDIOWAITINGTIMEOUT();
#endif

    CLR_DEEPCOLORMODE();
#endif

#if(_AUDIO_SUPPORT == _ON)
    CAdjustAudioControl(_DISABLE);
#endif

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
#if((_HDMI_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
    {

        CScalerPageSelect(_PAGE2);

        // Disable SPDIF/I2S Output
        CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AOCR_62, 0x00);

        // Disable N & CTS Tracking, FIFO Trend/boundary
        CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_PSCR_15, 0x00);

        // Update Double Buffer
        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_CMCR_10, ~_BIT4, _BIT4);

        // Disable PLL
        CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_DPCR0_38, 0x80);

        g_usHDMILockedFreq = 0;
        SET_HDMIAUDIOUNTRACKED();
        CLR_HDMIAUDIOTRACKED();

    }
#endif
#endif  // End of #if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))

    CSourceInitialConnect();

#if(_OVERSCAN_SUPPORT == _ON)
    CLR_OVERSCAN_STATUS();
    CLR_OVERSCAN_SUCCESS_STATUS();
    CLR_OVERSCAN_CAPTURE_BACKUP_VALUE();
    CLR_OVERSCAN_IV2DVDELAY_BACKUP_VALUE();
    g_ucOverScanH = 0;
    g_ucOverScanV = 0;
    g_usCaptureStartH = 0;
    g_usCaptureStartV = 0;
    g_usOldIHWidth = 0;
    g_usOldIVHeight = 0;
    g_ucUserModeCurr = 0;
    g_ucIv2DvModify = 0;
#endif

    stModeInfo.ModeCurr = _MODE_NOSIGNAL;
    ucModeFound = _MODE_FIRST;
    ucEvent0 = _INACTIVE_COUNTDOWN_EVENT;
    ucEvent1 = _INACTIVE_COUNTDOWN_EVENT;
    ucOsdState = _MENU_NONE;
    ucOsdEventMsg = _NONE_MSG;

    stModeInfo.Polarity = 0;
    stModeInfo.IHCount = 0;
    stModeInfo.IHFreq = 0;
    stModeInfo.IVTotal = 0;
    stModeInfo.IVFreq = 0;
    stModeInfo.IHWidth = 0;
    stModeInfo.IVHeight = 0;
    stModeInfo.IHSyncPulseCount = 0;

    // V013 System Patch Note (3) 20100429 Modify Start
    // Patch Reason : Initial stModeInfo XDATA variables.
    stModeInfo.IHStartPos = 0;
    stModeInfo.IHTotal = 0;
    // V013 System Patch Note (3) 20100429 Modify End

    // V013 TMDS Patch Note (16) 20100422 Modify Start
    // Patch Reason : Solve DVI Interlace Issue.
    stModeInfo.IVStartPos = 0;
    // V013 TMDS Patch Note (16) 20100422 Modify End

    stModeInfo.IVSyncPulseCount = 0;
    g_usAdcClockLimit = _PIXEL_WIDTH_LIMIT;
    g_usCaptureStart = 0;

    g_usVTotalTemp = 0;
    g_ucVSyncPulseWidthTemp = 0;

    // V012 Modify 20100402 Start
    // V012 Patch Note (29) : Fix the inaccurate Vfreq in OSD with SOG HORV/HEORV sync type.
    g_ucCoastLineCnt = 0;
    // V012 Modify 20100402 End

    // V012 Modify 20100331 Start
    // V012 Patch Note (30) : Use mode search incorrect flag to skip SOD clock seeking in the auto stage to avoid one missing vertical line at the edge of the picture.
    g_bModeSearchIncorrectFlag = _FALSE;
    // V012 Modify 20100331 Start

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
    g_bYuvRgbFlag = _FALSE;
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End

    if(ucCurrState != _SEARCH_STATE)
    {
        g_ucSearchIndex = stSystemData.SearchIndex;
#if _DEBUG_MESSAGE_SUPPORT
     CDebugMessage("stSystemData.SearchIndex_modereset", stSystemData.SearchIndex) ;
#endif
        g_ucSearchTimes = GET_INPUTPORT_SEARCH_TIMES(g_ucSearchIndex);
        g_ucSearchFinish = 0;

        CLR_SEARCH_FINISH();

        SET_SEARCH_INITIAL();

#if(_SWITCH_INPUT_SOURCE == _ON)
        if(GET_SOURCE_STATE() == _SWITCH_INPUT_SOURCE_STATE)
        {
            SET_SOURCE_STATE(_SOURCE_AUTO_CHANGE_STATE);
        }
#endif
        if((GET_INPUT_SOURCE_SEARCH() == _FALSE) && (GET_SOURCE_STATE() == _SOURCE_AUTO_CHANGE_STATE))
        {
            SET_FIRST_INPUT_PORT_SEARCH();
        }

        if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_VGA_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_VGA_PORT))
        {
            if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
            {
                if(ucCurrState == _ACTIVE_STATE)
                {
                    g_ucSearchTimes = g_ucSearchTimes + 60;
                }
                else
                {
                    g_ucSearchTimes = g_ucSearchTimes + 5;
                }
            }
        }
    }

    g_bCheckHDCP = 0;

    ucCurrState = _SEARCH_STATE;
    SET_INPUTSOURCE_TYPE(_SOURCE_NONE);
    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);

}

//--------------------------------------------------
// Description  : Free run mode setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetFreeRun(void)
{

    CMiscDisableDoubleBuffer();

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

    CAdjustPLL(_MPLL, (DWORD)_MEMORY_SPEED * 1000); // Enable MPLL
    CAdjustOdFrcPerformance(); //Set MCLK spread spectrum range & SDRAM Phase

#endif //End of #if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

    CAdjustPLL(_DPLL, (DWORD)_PANEL_PIXEL_CLOCK * 1000);

    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    pData[0] = (HIBYTE(_PANEL_DH_TOTAL - 4) & 0x0f);
    pData[1] = (LOBYTE(_PANEL_DH_TOTAL - 4));
    pData[2] = (_PANEL_DH_SYNC_WIDTH);
    pData[3] = (HIBYTE(_PANEL_DH_START) & 0x0f);
    pData[4] = (LOBYTE(_PANEL_DH_START));
    pData[5] = (HIBYTE(_PANEL_DH_START) & 0x0f);
    pData[6] = (LOBYTE(_PANEL_DH_START));
    pData[7] = (HIBYTE(_PANEL_DH_END) & 0x0f);
    pData[8] = (LOBYTE(_PANEL_DH_END));
    pData[9] = (HIBYTE(_PANEL_DH_END) & 0x0f);
    pData[10] = (LOBYTE(_PANEL_DH_END));

    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DH_TOTAL_H_00);
    CScalerWrite(_DISP_DATA_PORT_2B, 11, pData, _NON_AUTOINC);

    pData[0] = (HIBYTE(_PANEL_DV_TOTAL) & 0x0f);
    pData[1] = (LOBYTE(_PANEL_DV_TOTAL));
    pData[2] = (_PANEL_DV_SYNC_HEIGHT);
    pData[3] = (HIBYTE(_PANEL_DV_START) & 0x0f);
    pData[4] = (LOBYTE(_PANEL_DV_START));
    pData[5] = (HIBYTE(_PANEL_DV_START) & 0x0f);
    pData[6] = (LOBYTE(_PANEL_DV_START));
    pData[7] = (HIBYTE(_PANEL_DV_END) & 0x0f);
    pData[8] = (LOBYTE(_PANEL_DV_END));
    pData[9] = (HIBYTE(_PANEL_DV_END) & 0x0f);
    pData[10] = (LOBYTE(_PANEL_DV_END));

    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DV_TOTAL_H_0B);
    CScalerWrite(_DISP_DATA_PORT_2B, 11, pData, _NON_AUTOINC);

    // V015 VGA Patch Note (9) Modify 20100623 Start
    // Patch Reason : Correct OSD Reference DEN for Free Run Mode.
    pData[0] = (_PANEL_DV_START <= 6) ? 6 : _PANEL_DV_START;
    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_OSD_REFERENCE_DEN_21, pData[0] - 4);
    // V015 VGA Patch Note (9) Modify 20100623 End

    pData[0] = ((_PANEL_DH_TOTAL >> 4) & 0xf0) | (HIBYTE(_PANEL_DV_TOTAL) & 0x0f);
    pData[1] = LOBYTE(_PANEL_DV_TOTAL);
    pData[2] = LOBYTE(_PANEL_DH_TOTAL);

    CScalerPageSelect(_PAGE1);
    CScalerWrite(_P1_EVEN_FIX_LASTLINE_DVTOTAL_M_C7, 3, pData, _AUTOINC);
    stDisplayInfo.DHWidth = _PANEL_DH_END - _PANEL_DH_START;
    stDisplayInfo.DVHeight = _PANEL_DV_HEIGHT - _PANEL_DV_START;

}

//--------------------------------------------------
// Description  : Check if the connector status is changed
// Input Value  : None
// Output Value : Return _TRUE if the connector status changed
//--------------------------------------------------
bit CModeConnectIsChange(void)
{
#if(_CABLE_CONNECT_CHECK)

    bit status = 0;

    switch(GET_INPUTPORT_TYPE(g_ucSearchIndex))
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)

#ifdef _A0_PORT
        case _A0_INPUT_PORT_TYPE:
            if(bA0_CONNECT != GET_PRE_A0_CONNECT())
            {
                SET_PRE_A0_CONNECT(bA0_CONNECT);
                status = 1;
            }

            SET_PRE_A0_CONNECT(bA0_CONNECT);
            break;
#endif

#endif // End of #if(_A1_INPUT_PORT_TYPE != _A1_NO_PORT)

#if(_A1_INPUT_PORT_TYPE != _A1_NO_PORT)

#ifdef _A1_PORT
        case _A1_INPUT_PORT_TYPE:
            if(bA1_CONNECT != GET_PRE_A1_CONNECT())
            {
                SET_PRE_A1_CONNECT(bA1_CONNECT);
                status = 1;
            }

            SET_PRE_A1_CONNECT(bA1_CONNECT);
            break;
#endif

#endif // End of #if(_A1_INPUT_PORT_TYPE != _A1_NO_PORT)

#if((_HDMI_SUPPORT == _ON) || (_TMDS_SUPPORT == _ON))

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#ifdef _D0_PORT

#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
        case _D0_INPUT_PORT_TYPE:
            if(CDpAuxPinCableConnect() != GET_PRE_D0_CONNECT())
            {
                SET_PRE_D0_CONNECT(CDpAuxPinCableConnect());
                status = 1;
            }

            SET_PRE_D0_CONNECT(CDpAuxPinCableConnect());
            break;

#else
        case _D0_INPUT_PORT_TYPE:
            if(bD0_CONNECT != GET_PRE_D0_CONNECT())
            {
                SET_PRE_D0_CONNECT(bD0_CONNECT);
                status = 1;
            }

            SET_PRE_D0_CONNECT(bD0_CONNECT);
            break;
#endif

#endif

#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

#ifdef _D1_PORT
        case _D1_INPUT_PORT_TYPE:
            if(bD1_CONNECT != GET_PRE_D1_CONNECT())
            {
                SET_PRE_D1_CONNECT(bD1_CONNECT);
                status = 1;
            }

            SET_PRE_D1_CONNECT(bD1_CONNECT);
            break;
#endif

#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

#endif  // End of #if((_HDMI_SUPPORT == _ON) || (_TMDS_SUPPORT == _ON))
    }

    if(status)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
#else
        return _FALSE;

#endif
}

//--------------------------------------------------
// Description  : Enable online measure
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeAutoMeasureOn(void)
{
    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT7, _BIT7);
    CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent);
}

//--------------------------------------------------
// Description  : Disable online measure
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeAutoMeasureOff(void)
{
    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT7, 0x00);
}

//----------------------------------------------------------------------------------------------------
// Mode Events
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : No signal timeout count down event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSyncTimeoutCountDownEvent(void)
{
    ucCurrState = _NOSIGNAL_STATE;
    stModeInfo.ModeCurr = _MODE_NOSIGNAL;
    SET_READYFORDISPLAY();
}

//--------------------------------------------------
// Description  : Mode stable count down event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeStableCountDownEvent(void)
{
    SET_MODESTABLE();
}

//--------------------------------------------------
// Description  : No signal event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeNoSignalEvent(void)
{
    ucOsdEventMsg = _SHOW_NOSIGNAL_MSG;
}

//--------------------------------------------------
// Description  : No cable event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeNoCableEvent(void)
{
    ucOsdEventMsg = _SHOW_NOCABLE_MSG;
}

//--------------------------------------------------
// Description  : No support event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeNoSupportEvent(void)
{
    ucOsdEventMsg = _SHOW_NOSUPPORT_MSG;
}

//--------------------------------------------------
// Description  : Display timing and input source event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeOsdDisplayTimingAndInputEvent(void)
{
   ucOsdEventMsg = _SHOW_TIMINGINPUT_MSG;
}

//--------------------------------------------------
// Description  : Power saving event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModePowerSavingEvent(void)
{
    CScalerPageSelect(_PAGE2);

    CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    CScalerSetBit(_P2_TMDS_OUTPUT_CTRL_A6, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

    // Audio PLL power down when power saving
    CScalerSetBit(_P2_HDMI_APC_C8, ~_BIT0, 0x00);
    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_DPCR0_38, ~_BIT7, _BIT7);
#if(_AUDIO_SUPPORT == _ON)
    CAdjustAudioControl(_DISABLE);
#endif
    CPowerPanelOff();
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT3 | _BIT0), 0x00);

    CPowerADCAPLLOff();
    CPowerLVDSOff();
    CPowerDPLLOff();

    CPowerPWMOff();

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
    CMcuSelectFlashClk(_XTAL_CLK);
    CTimerDelayXms(10);
#endif

    CPowerM2PLLOff();
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CPowerMPLLOff();
#endif

    CScalerDisableDisplayTiming();
    CScalerSetBit(_HOST_CTRL_01, ~_BIT1, _BIT1);

#if(_DP_SUPPORT == _ON)

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    if(GET_SOURCE_SEARCH_AUTO() == _TRUE)   // for Auto Source
    {


        CScalerPageSelect(_PAGEB);
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);

        CScalerPageSelect(_PAGEC);
        CScalerSetByte(_PC_DP_CTL_A1, 0x20);

        // Turn off output CLK
        CScalerSetBit(_PC_DP_OUTPUT_CTL_A2, ~_BIT4, 0x00);

        // Turn off SCLK PLL
        CScalerSetDataPortBit(_PC_DP_ACCESS_PORT_B3, 0x70, ~_BIT7, _BIT7);
    }
    else                                    // for Single Source
#endif
    {
        if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DP_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DP_PORT)) //DP
        {
            if(((g_ucDpPowerStatus == _DP_POWER_DOWN) || (g_bDpPowerDown == _TRUE)) && (g_ucDisplayPortLtPreStatus == _TRAINING_PATTERN_NONE))
            {


                CScalerPageSelect(_PAGEB);
                CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);

                CScalerPageSelect(_PAGEC);
                CScalerSetByte(_PC_DP_CTL_A1, 0x20);

                // Turn off output CLK
                CScalerSetBit(_PC_DP_OUTPUT_CTL_A2, ~_BIT4, 0x00);

                // Turn off SCLK PLL
                CScalerSetDataPortBit(_PC_DP_ACCESS_PORT_B3, 0x70, ~_BIT7, _BIT7);
            }
            else
            {
                //do nothing
            }
        }
        else //HDMI/DVI/VGA
        {
            CScalerPageSelect(_PAGEB);
            CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);

            CScalerPageSelect(_PAGEC);
            CScalerSetByte(_PC_DP_CTL_A1, 0x20);

            // Turn off output CLK
            CScalerSetBit(_PC_DP_OUTPUT_CTL_A2, ~_BIT4, 0x00);

            // Turn off SCLK PLL
            CScalerSetDataPortBit(_PC_DP_ACCESS_PORT_B3, 0x70, ~_BIT7, _BIT7);
        }
    }
#else

    CScalerPageSelect(_PAGEB);
    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);
#endif

    CScalerPageSelect(_PAGE1);
    CScalerSetByte(_P1_BB_POWER0_F0, 0x00);
    CScalerSetByte(_P1_BB_POWER1_F1, 0x00);

    ucCurrState = _SLEEP_STATE;
}


#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check HDMI Input Status
// Input Value  : None
// Output Value : return _FALSE if it will do CModeResetMode
//--------------------------------------------------
bit CModeHdmiStablePolling(void)
{
#if(_HDMI_FROM_DVI_CONNECT == _OFF)
    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) != _D0_HDMI_PORT) && (GET_INPUTPORT_TYPE(g_ucSearchIndex) != _D1_HDMI_PORT))
#else
    if(0)
#endif
    {
        if(CHdmiFormatDetect())
        {
            return _FALSE;
        }
    }
#if(_HDMI_FROM_DVI_CONNECT == _OFF)
    else if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT))
#else
    else if(1)
#endif
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)//ming080221
        {
            if(CHdmiFormatDetect())//Input source is the HDMI format.
            {
                if(GET_READYFORDISPLAY())
                {
                    CHdmiVideoSetting();
                }

                if(!GET_HDMIINPUT())
                {
                    return _FALSE;
                }

#if(_AUDIO_SUPPORT == _ON)
#if((_SCALER_TYPE == _RTD2472D))
                else
                {
                    if(GET_AUDIOWAITINGTIMEOUT())
                    {
                        CHdmiEnableAudioOutput();
                    }
#if(_AUDIO_OUTPUT_TYPE == _I2S)
                    CScalerPageSelect(_PAGE2);
                    CScalerRead(_P2_HDMI_SR_CB, 1, pData, _NON_AUTOINC);
                    CScalerGetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AOCR_62, 1, &pData[1], _NON_AUTOINC); //Read I2S Output
                    if((pData[0] & 0x16) == 0x00) //LPCM & no overflow/underflow in Audio FIFO
                    {
                        if((pData[1] & 0x0f) != 0x0f)
                        {
                            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AOCR_62, 0x0f);//Enable I2S Output
                        }
                    }
                    else
                    {
                        if((pData[1] & 0x0F) != 0x00)
                        {
                            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AOCR_62, 0x00);//Disable I2S Output
                        }
                    }
#endif
                }
#endif
#endif  // End of #if(_AUDIO_SUPPORT == _ON)
            }
            else
            {
                if(GET_HDMIINPUT())
                {
                    return _FALSE;
                }
            }
        }
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Check input signal for interlace mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeInterlaceCheck(void)
{
    switch(GET_INPUTSOURCE_TYPE())
    {
        case _SOURCE_VGA:
#if(_YPBPR_SUPPORT == _ON)
        case _SOURCE_YPBPR:
#endif
            CLR_INTERLACE_MODE();

            /// for generate clk to interlace flag toggle
            //stModeInfo.IHTotal = 1000;
            //CAdjustAdcClock(stModeInfo.IHTotal,0);
            CScalerPageSelect(_PAGE1);
            CScalerSetByte(_P1_PLL_WD_AF, 0x08);


            CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT1), 0);

            CScalerSetBit(_IPV_ACT_LEN_H_1A, ~_BIT5, _BIT5);
            CTimerDelayXms(80);
            CScalerRead(_IPV_ACT_LEN_H_1A, 1, pData, _NON_AUTOINC);
            if(pData[0] & 0x20)
            {
                SET_INTERLACE_MODE();
            }


            break;

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON) || (_VIDEO_SUPPORT == _ON) || (_DP_SUPPORT))

#if(_VIDEO_SUPPORT == _ON)
        case _SOURCE_VIDEO8:
            CScalerSetByte(_STATUS0_02, 0x00);                      // Clear Status
            CTimerDelayXms(80);
            CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);       // Read status
            if (pData[0] & 0x10)
            {
                SET_INTERLACE_MODE();
            }
            else
            {
                CLR_INTERLACE_MODE();
            }

            break;
#endif

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        case _SOURCE_DVI:
        case _SOURCE_HDMI:
#endif
// V013 TMDS Patch Note (16) 20100422 Modify Start
// Patch Reason : Solve DVI Interlace Issue.
            CScalerPageSelect(_PAGE2);
            if(CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7) == _BIT7)
            {
                // Internal ODD Signal Selection: Internal Field Detection ODD Signal
                CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT0, _BIT0);

                // Input pixel format: Embeded TMDS
                CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2), _BIT2);

                // Clear "Internal Fiel Detection ODD Toggle Happened" flag
                CScalerSetBit(_IPV_ACT_LEN_H_1A, ~_BIT5, _BIT5);

                // Wait even/odd toggle
                CTimerWaitForEvent(_EVENT_IVS);
                CTimerWaitForEvent(_EVENT_IVS);
                CTimerWaitForEvent(_EVENT_IVS);
                CTimerWaitForEvent(_EVENT_IVS);

                // Detect "Internal Fiel Detection ODD Toggle Happened" flag
                CScalerRead(_IPV_ACT_LEN_H_1A, 1, pData, _NON_AUTOINC);

                if((pData[0] & 0x20) == 0x20)
                {
                    SET_INTERLACE_MODE();
                }
                else
                {
                    CLR_INTERLACE_MODE();
                }
            }
            else
            {
                CScalerPageSelect(_PAGE2);
                CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VCR_50, ~_BIT6, _BIT6);

                // Wait even/odd toggle
                CTimerWaitForEvent(_EVENT_IVS);
                CTimerDelayXms(5);

                CScalerGetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VCR_50, 1, pData, _NON_AUTOINC);
                if((pData[0] & 0x40) == 0x40)
                {
                    SET_INTERLACE_MODE();
                }
                else
                {
                    CLR_INTERLACE_MODE();
                }
            }

            /*
            CScalerPageSelect(_PAGE2);
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VCR_50, ~_BIT6, _BIT6);
            */

            /*
            CTimerWaitForEvent(_EVENT_IVS);
            CTimerDelayXms(5);
            */

            /*
            CScalerGetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VCR_50, 1, pData, _NON_AUTOINC);
            if((pData[0] & 0x40) == 0x40)
            {
                SET_INTERLACE_MODE();
            }
            else
            {
                CLR_INTERLACE_MODE();
            }
            */
// V013 TMDS Patch Note (16) 20100422 Modify End

            break;

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            CScalerPageSelect(_PAGEC);
            CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x01, 1, pData, _NON_AUTOINC);
            if((pData[0]&0x04) == 0x04)
            {
                SET_INTERLACE_MODE();
            }
            else
            {
                CLR_INTERLACE_MODE();
            }

            break;
#endif

#endif
    }
}
//--------------------------------------------------
// Description  : Display FIFO Setting for Frame Sync Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#if(_FRC_SUPPORT == _ON)
void CModeSetFIFOForFrameSync(void)
{
    CScalerPageSelect(_PAGE5);
    CScalerSetByte(_P5_SDRF_MN_DISP_CTRL_CF, 0x05);
    CTimerDelayXms(100);
    CScalerSetByte(_P5_SDRF_MN_SDR_STATUS_D0, 0x10);
}
#endif


#if(_NON_LINEAR_SCALING_FUCTION == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerNonlinearScaleUp(void)
{
    BYTE FlatSuFac = 0;
    BYTE InitSuFac = 0;
    WORD w1;            // segment1 pixel
    WORD w2;            // segment2 pixel
    WORD w3;            // segment3 pixel
    BYTE SU_Waighting;  //range from 35 ~ 45

    w1 = stDisplayInfo.DHWidth / 5 + 71;
    w2 = w1 - 71; //w2
    w3 = stDisplayInfo.DHWidth - SHL(w1, 1) - SHL(w2, 1); //w3

    SU_Waighting = 35 + 4; //+ GET_NONLINEAR_VALUE();

    //Set the initial scale up factor equal to average scale up factor * 0.2
    //Calculate the scaling factor normalize to 255
    ((DWORD*)pData)[0] = (DWORD)255 * stModeInfo.IHWidth / stDisplayInfo.DHWidth;
    InitSuFac = SHR(((DWORD*)pData)[0]*3, 2);

    //Fsu > Csu
    //Fsu - Csu > 0
    //Fsu - [Xm - Su(w1 + 1) - Fsu(1 + w2 + w3)]/(w1 + w2) > 0
    //Fsu(w1 + w2) - [Xm - Su(w1 + 1) - Fsu(1 + w2 + w3)] > 0
    //Fsu(1 + w1 + 2w2 + w3) - Xm + Su(w1 + 1) > 0
    //Fsu > [Xm - Su(w1 + 1)]/(1 + w1 + 2w2 + w3)

    ((DWORD*)pData)[3] = 255 * ((DWORD)(stModeInfo.IHWidth - 1) - (DWORD)w1 * InitSuFac / 255) / (w1 + SHL(w2, 1) + w3 - 8);
    if (((DWORD*)pData)[3] > 254)
    {
        return;
    }
    else
    {
        //FlatSuFac = (SHR(((DWORD*)pData)[0] * 3, 1) > 255) ? 255 : SHR(((DWORD*)pData)[0] * 3, 1);
        FlatSuFac = (SHR(((DWORD*)pData)[0] * SU_Waighting, 5) > 255) ? 255 : SHR(((DWORD*)pData)[0] * SU_Waighting, 5);
    }

    //((DWORD *) pData)[3] = 16777216 * (DWORD) InitSuFac / 255 + 0x00000008;
    ((DWORD *) pData)[3] = 1048576 * (DWORD) InitSuFac / 255;

    CTimerWaitForEvent(_EVENT_DEN_STOP);
    pData[0] = ((((DWORD *) pData)[3] >> 16) & 0x0f);
    pData[1] = ((((DWORD *) pData)[3] >> 8) & 0xff);
    pData[2] = ((((DWORD *) pData)[3]) & 0xff);

    CScalerSetByte(_SU_ACCESS_PORT_33, 0x80); //don't remove this code thus the value can be fill in register
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x80);
    CScalerWrite(_SU_DATA_PORT_34, 3, pData, _NON_AUTOINC);
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x00);

    //Calculate Csu = (Xm - Su(w1 + 1) - Fsu(1 + w2 + w3))/(w1 + w2)
    ((DWORD*)pData)[2] = 1048576 * ((DWORD)stModeInfo.IHWidth -
    (DWORD)InitSuFac * w1 / 255 -
    (DWORD)FlatSuFac * (w2 + w3 - 1) / 255) / (w1 + w2 - 2);

    //Calculate SU
    ((DWORD*)pData)[3] = SHR((2097152 * (DWORD)InitSuFac / 255) + 1, 1);

    if (((unsigned long *)pData)[3] > ((unsigned long *) pData)[2])
    {
        ((unsigned long *) pData)[3] = 0 - (((unsigned long *) pData)[3] - ((unsigned long *) pData)[2]) / (DWORD)w1; //The MSB is sign bit
    }
    else
    {
        if (((unsigned long *)pData)[3] > ((unsigned long *) pData)[2])
        {
            ((unsigned long *) pData)[3] = 0 - (((unsigned long *) pData)[3] - ((unsigned long *) pData)[2]) / (DWORD)w1; //The MSB is sign bit
        }
        else
        {
            //Calculate d1
            ((DWORD*) pData)[3] = (((DWORD*)pData)[2] - ((DWORD*)pData)[3]) / (DWORD)w1;
        }

        pData[6] = ((((DWORD *) pData)[3] >> 8) & 0xff);
        pData[7] = (((DWORD *) pData)[3]  & 0xff);

        //Calculate Fsu
        ((DWORD*)pData)[3] = SHR((2097152 * (DWORD)FlatSuFac / 255) + 1, 1);

        if (((unsigned long *) pData)[3] > ((unsigned long *) pData)[2])
        {
            ((DWORD*)pData)[3] = (((DWORD*)pData)[3] - ((DWORD*)pData)[2]) / (DWORD)w2;
        }
        else
        {
            ((unsigned long *) pData)[3] = 0 - (((unsigned long *) pData)[2] - ((unsigned long *) pData)[3]) / (DWORD)w2;
        }
    }

    pData[8] = ((((DWORD *) pData)[3] >> 8) & 0xff);
    pData[9] = (((DWORD *) pData)[3] & 0xff);

    w1 -= 1;
    w2 -= 1;
    w3 -= 1;

    pData[0] = AND(HIBYTE(w1), 0x07);
    pData[1] = LOBYTE(w1);
    pData[2] = AND(HIBYTE(w2), 0x07);
    pData[3] = LOBYTE(w2);
    pData[4] = AND(HIBYTE(w3), 0x07);
    pData[5] = LOBYTE(w3);

    CScalerSetByte(_SU_ACCESS_PORT_33, 0x86);  //don't remove this code thus the value can be fill in register
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x86);
    CScalerWrite(_SU_DATA_PORT_34, 10, pData, _NON_AUTOINC);
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x00);
    CTimerDelayXms(120);
    CScalerSetByte(_STATUS0_02, 0x00);

}

#endif  //#if(_NON_LINEAR_SCALING_FUCTION == _ON)



#if((_ASPECT_RATIO_SUPPORT == _ON) && (_MEMORY_WORK_TYPE == _OD_OFF_FRC_OFF))
//--------------------------------------------------
// Description  : Set DHWidth to display
// Input Value  : DHWidth
// Output Value : Return _TRUE if sucess
//--------------------------------------------------
bit CModeSetDHWidthToDisplay(void)
{
    BYTE option = 0;
    WORD usDHWidth = 0;

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
    stModeInfo.IHWidth = g_usOldIHWidth - (2 * g_ucOverScanH);
    stModeInfo.IVHeight = g_usOldIVHeight - (2 * g_ucOverScanV);
#endif
// V012 Modify 20100316 End

    if(GET_DISP_RATIO() == _ON)
    {
       usDHWidth = (DWORD)stModeInfo.IHWidth * _PANEL_DV_HEIGHT / stModeInfo.IVHeight;
    }
    else
    {
       usDHWidth = _PANEL_DH_WIDTH;
    }

    if(usDHWidth <= _PANEL_DH_WIDTH)
    {
        CAdjustDisableWatchDog(_WD_ALL);
        CMiscDisableDoubleBuffer();

        stDisplayInfo.DHWidth = usDHWidth;

        if(stModeInfo.IVHeight < stDisplayInfo.DVHeight)
        {
            option |= _BIT0;    // bit 0 : V scale-up
        }
        if(stModeInfo.IVHeight > stDisplayInfo.DVHeight)
        {
            option |= _BIT1;    // bit 1 : V scale-down
        }
        if(stModeInfo.IHWidth < stDisplayInfo.DHWidth)
        {
            option |= _BIT2;    // bit 2 : H scale-up
        }
        if(stModeInfo.IHWidth > stDisplayInfo.DHWidth)
        {
            option |= _BIT3;    // bit 3 : H scale-down
        }

        // Scaling setup
        CModeSetScaling(option);

        if(usDHWidth < _PANEL_DH_WIDTH)
        {
            ((WORD *)pData)[0] = ((_PANEL_DH_WIDTH - stDisplayInfo.DHWidth) / 2 + _PANEL_DH_START);
            ((WORD *)pData)[1] = (((WORD *)pData)[0] + stDisplayInfo.DHWidth);
        }
        else
        {
            ((WORD *)pData)[0] = (_PANEL_DH_START & 0x0fff);
            ((WORD *)pData)[1] = (_PANEL_DH_END & 0x0fff);
        }

        CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DH_ACT_STA_H_05);
        CScalerWrite(_DISP_DATA_PORT_2B, 4, pData, _NON_AUTOINC);


        CTimerWaitForEvent(_EVENT_DVS);
        CMiscClearStatusRegister();
        CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);
        if((pData[0] & 0x03) != 0)
        {
            pData[0] = CFrameSyncDo();
            if(pData[0] == 2)
            {
                CModeResetMode();
                return _FALSE;
            }

            CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);
            if((pData[0] & 0x03) != 0)
            {
                return _FALSE;
            }
        }

        CMiscEnableDoubleBuffer();
        CAdjustEnableWatchDog(_WD_ALL);
    }

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
    stModeInfo.IHWidth = g_usOldIHWidth;
    stModeInfo.IVHeight = g_usOldIVHeight;
#endif
// V012 Modify 20100316 End

    return _TRUE;
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerDisableNonlinearScaleUp(void)
{
    ((DWORD*) pData)[0] = 0; //Disable non linear scale up first

    CScalerSetByte(_SU_ACCESS_PORT_33, 0x8c);
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x8c);
    CScalerWrite(_SU_DATA_PORT_34, 4, pData, _NON_AUTOINC);
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x00);
}

#endif // End of #if((_ASPECT_RATIO_SUPPORT==_ON) && (_MEMORY_WORK_TYPE == _OD_OFF_FRC_OFF))


//--------------------------------------------------
// Description  : Mode Stable Detect
// Input Value  : None
// Output Value : return _FALSE if it will do CModeResetMode
//--------------------------------------------------
bit CModeStableDetect(void)
{
    if(CFrameSyncDetect())
    {
        return _FALSE;
    }

    if(CModeIsChange())
    {
        return _FALSE;
    }

#if(_DP_SUPPORT == _ON)
    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DP_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DP_PORT))
    {
        //Sink CRC Test
        CDpCRCTest();

        if(CDpActiveCheckFail() == _TRUE)
        {
            return _FALSE;
        }
    }
#endif

#if(_HDMI_SUPPORT == _ON)
    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_I_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_I_PORT))
    {
        if(CModeHdmiStablePolling() == _FALSE)
        {
            return _FALSE;
        }
    }
#endif

    return _TRUE;
}


#if(_LOW_FRAME_RATE_SUPPORT == _ON)

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
//--------------------------------------------------
// Description  : Check Low Frame Rate
// Input Value  : None
// Output Value : return _TRUE if it is low frame rate
//--------------------------------------------------
bit CModeCheckLowFrameRate(void)
{
    bit bOrgM2PLLState = 0;
    BYTE ucSyncType = 0;
    BYTE ucStatus1 = 0xFF;
    BYTE ucStatus2 = 0xFF;

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
    CMcuSelectFlashClk(_XTAL_CLK);
#endif

    CScalerPageSelect(_PAGE1);

    // Record M2PLL State
    if((bit)CScalerGetBit(_P1_M2PLL_WD_E5, _BIT0))
    {
        CScalerSetBit(_P1_M2PLL_WD_E5, ~_BIT0, 0x00);
        bOrgM2PLLState = _TRUE;
    }

    // Switch to M2PLL Frequency
    CScalerSetByte(_P1_M2PLL_M_E0, 0x59);
    CScalerSetByte(_P1_M2PLL_N_E1, 0x13);
    CScalerSetBit(_FIFO_FREQUENCY_22, ~_BIT2, _BIT2);

    // Delay for M2PLL stable
    CTimerDelayXms(50);

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
    CMcuSelectFlashClk(_FLASH_CLK);
#endif

    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_VGA_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_VGA_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_YPBPR_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_YPBPR_PORT))
    {
        // Enable Hsync Type Detection Auto Run
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);
        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT6 | _BIT5), 0x00);
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);

        // V012 Modify 20100329 Start
        // V012 Patch Note (19) : Adjust polling time of Auto Run Typer according to different Crystal frequency.
        /*
        // Check the result of Auto Run
        if(CTimerPollingEventProc(180, CMiscHsyncTypeAutoRunFlagPollingEvent))
        */
        // Check the result of Auto Run
        if(CTimerPollingFlagProc(_SP_AUTORUN_TIME_OUT, _PAGE_COMMON, _VSYNC_COUNTER_LEVEL_MSB_4C, _BIT7, _TRUE) == _TRUE)
        // V012 Modify 20100329 End
        {
            ucSyncType = (CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, 0xff) & 0x70) >> 4;

            if((ucSyncType != _NO_SIGNAL) && (ucSyncType != _NOT_SUPPORT) && (ucSyncType != _HSYNC_WITHOUT_VS))
            {
                // Read measurement status bit
                if(CModeMeasureReady())
                {
                    CScalerRead(_MEAS_HS_PERIOD_H_52, 1, &ucStatus1, _NON_AUTOINC);
                    CScalerRead(_MEAS_VS_PERIOD_H_54, 1, &ucStatus2, _NON_AUTOINC);
                }
            }
        }
    }
    else
    {
        // Read measurement status bit
        if(CModeMeasureReady())
        {
            CScalerRead(_MEAS_HS_PERIOD_H_52, 1, &ucStatus1, _NON_AUTOINC);
            CScalerRead(_MEAS_VS_PERIOD_H_54, 1, &ucStatus2, _NON_AUTOINC);
        }

    }   // End of if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
    CMcuSelectFlashClk(_XTAL_CLK);
#endif

    // Switch to Xtal Frequency
    CScalerPageSelect(_PAGE1);

    // V012 Modify 20100331 Start
    // V012 Patch Note (21) : Fix the sync processor compatibility problem. Replace slower XTAL clock with M2PLL.
    /*
    CScalerSetByte(_P1_M2PLL_M_E0, 0x69);
    CScalerSetByte(_P1_M2PLL_N_E1, 0x13);
    CScalerSetBit(_FIFO_FREQUENCY_22, ~_BIT2, 0x00);
    */
    CScalerSetByte(_P1_M2PLL_M_E0, (_M2PLL_PLL_M-2));
    CScalerSetByte(_P1_M2PLL_N_E1, (((_M2PLL_PLL_O >> 1) << 4) | (_M2PLL_PLL_N-2)));

    // V013 VGA Patch Note (6) Modify 20100428 Start
    // Patch Reason : Update V012 Patch Note (21) use m2pll/10 as internal clock just in analog source.
    /*
    CScalerSetBit(_FIFO_FREQUENCY_22, ~_BIT2, _INTERNAL_CLK_FLAG);
    */
    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_VGA_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_YPBPR_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_VGA_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_YPBPR_PORT))
    {

        if(bOrgM2PLLState)
        {
            CScalerSetBit(_FIFO_FREQUENCY_22, ~_BIT2, 0x00);
        }
        else
        {
            CScalerSetBit(_FIFO_FREQUENCY_22, ~_BIT2, _INTERNAL_CLK_FLAG);
        }
        // V013 VGA Patch Note (6) Modify 20100428 End
    }
    else
    {
        CScalerSetBit(_FIFO_FREQUENCY_22, ~_BIT2, 0x00);
    }
    // V013 VGA Patch Note (6) Modify 20100428 End

    // V012 Modify 20100331 End

    // Reset M2PLL State
    if(bOrgM2PLLState == _TRUE)
    {
        CScalerSetBit(_P1_M2PLL_WD_E5, ~_BIT0, _BIT0);
    }

    // Delay for M2PLL stable
    CTimerDelayXms(50);

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
    CMcuSelectFlashClk(_FLASH_CLK);
#endif

    // Reset Sync Processor Auto Run
    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_VGA_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_VGA_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_YPBPR_PORT)
    || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_YPBPR_PORT))
    {
        // Enable Hsync Type Detection Auto Run
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);
        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT6 | _BIT5), 0x00);
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);

        // V016 VGA Patch Note (14) Modify 20100831 Start
        // Patch Reason : Wait for 0x4C-bit7 after start Auto Run.
        CTimerPollingFlagProc(_SP_AUTORUN_TIME_OUT, _PAGE_COMMON, _VSYNC_COUNTER_LEVEL_MSB_4C, _BIT7, _TRUE);
        // V016 VGA Patch Note (14) Modify 20100831 End

        // Clear Hsync Type Detection Flag
        CScalerSetByte(_HSYNC_TYPE_DETECTION_FLAG_4E, 0xFF);
    }

    // Check Vsync Time Out Flag
    if((bit)(ucStatus1 & _BIT4) || (bit)(ucStatus2 & _BIT4) || (bit)(ucStatus2 & _BIT5))
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif  // End of #if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

#endif  // End of #if(_LOW_FRAME_RATE_SUPPORT == _ON)


//--------------------------------------------------
// Description  : Check if the picked mode frame sync
// Input Value  : Mode table information
// Output Value : _TRUE, Frame Sync OK
//                _FALSE, Frame Sync NG
//--------------------------------------------------
BYTE CModeCheckModeVGA(BYTE ucModeIndex)
{
    if(ucModeIndex >= _MAX_PRESET_MODE)
    {
        return _CHECK_MODE_INDEX_ERROR;
    }

    // Check IHTotal due to ADC Clock Limit
    if(tINPUTMODE_PRESET_TABLE[ucModeIndex].IHTotal > g_usAdcClockLimit)
    {
        return _CHECK_MODE_ADC_SPEED_ERROR;
    }

    if(tINPUTMODE_PRESET_TABLE[ucModeIndex].IHTotal < (tINPUTMODE_PRESET_TABLE[ucModeIndex].IHStartPos + tINPUTMODE_PRESET_TABLE[ucModeIndex].IHWidth))
    {
        return _CHECK_MODE_TABLE_INFO_ERROR;
    }

#if(_FRC_SUPPORT == _OFF)

    stModeInfo.IVStartPos = tINPUTMODE_PRESET_TABLE[ucModeIndex].IVStartPos;
    stModeInfo.IVHeight = tINPUTMODE_PRESET_TABLE[ucModeIndex].IVHeight;
    stDisplayInfo.DVHeight = _PANEL_DV_HEIGHT;

    CFrameSyncModifyDVStartPos(_DVSTART_POS_ADJUSTING);

    // Calculate DVStart due to display ratio
    ((DWORD *)pData)[3] = (DWORD)stDisplayInfo.DVStartPos * 10 * stModeInfo.IVHeight / stDisplayInfo.DVHeight;

    // Check Frame Sync Formula : IVToDVdelay = IVStart + 2.5 - DVStart > 1
    if((stModeInfo.IVStartPos * 10 + 15) < ((DWORD *)pData)[3])
    {
        return _CHECK_MODE_FRAME_SYNC_ERROR;
    }

    // New IVStart = Original IVStart - IVToDVdelay => DVStart - 2.5
    // Measured IVTotal must be greater than (New IVStart + IVHeight)
    if((stModeInfo.IVTotal * 10) < ((((DWORD *)pData)[3] - 25) + (stModeInfo.IVHeight * 10)))
    {
        return _CHECK_MODE_FRAME_SYNC_ERROR;
    }

#endif

    return _CHECK_MODE_SUCCESS;
}

//--------------------------------------------------
// Description  : Additional Search after acceptive
//                search with result checking.
// Input Value  : Mode Table Count
// Output Value : Mode Index
//--------------------------------------------------
BYTE CModeAdditionalSearch(BYTE ucModeIndex)
{
    BYTE ucModeCnt = 0;
    BYTE ucResult = 0xFF;
    WORD usIHWidth = 0;
    WORD usIVHeight = 0;

    ucResult = CModeCheckModeVGA(ucModeIndex);

    if((g_usCurrIVHeight > tINPUTMODE_PRESET_TABLE[ucModeIndex].IVHeight)
    || ((ucResult != _CHECK_MODE_SUCCESS) && (ucResult != _CHECK_MODE_ADC_SPEED_ERROR)))
    {
        ucModeIndex = _MODE_NOSUPPORT;

        for(ucModeCnt = 0; ucModeCnt < _MAX_PRESET_MODE; ucModeCnt++)
        {
            if(tINPUTMODE_PRESET_TABLE[ucModeCnt].IVHeight >= g_usCurrIVHeight)
            {
                if(CModeCheckModeVGA(ucModeCnt) == _CHECK_MODE_SUCCESS)
                {
                    if(stModeInfo.IVHeight >= usIVHeight)
                    {
                        if(tINPUTMODE_PRESET_TABLE[ucModeCnt].IHWidth >= usIHWidth)
                        {
                            usIHWidth = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHWidth;
                            usIVHeight = stModeInfo.IVHeight;
                            ucModeIndex = ucModeCnt;
                        }
                    }
                }
            }
        }
    }
    else if(ucResult == _CHECK_MODE_ADC_SPEED_ERROR)
    {
        usIVHeight = tINPUTMODE_PRESET_TABLE[ucModeIndex].IVHeight;
        ucModeIndex = _MODE_NOSUPPORT;

        for(ucModeCnt = 0; ucModeCnt < _MAX_PRESET_MODE; ucModeCnt++)
        {
            if(tINPUTMODE_PRESET_TABLE[ucModeCnt].IVHeight == usIVHeight)
            {
                if(CModeCheckModeVGA(ucModeCnt) == _CHECK_MODE_SUCCESS)
                {
                    if(tINPUTMODE_PRESET_TABLE[ucModeCnt].IHWidth >= usIHWidth)
                    {
                        usIHWidth = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHWidth;
                        ucModeIndex = ucModeCnt;
                    }
                }
            }
        }
    }

    return ucModeIndex;
}

//--------------------------------------------------
// Description  : VGA Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeInitialVGA(void)
{
    // V014 VGA Patch Note (6) Modify 20100527 Start
    // Patch Reason : Modify Video Mode Can't Light On
    /*
    // V013 VGA Patch Note (23) Modify 20100513 Start
    // Patch Reason : For Video Mode Clamp Position Setting Flow
    bit bVideoModeFlg = _FALSE;
    // V013 VGA Patch Note (23) Modify 20100513 End
    */
    // V014 VGA Patch Note (6) Modify 20100527 End

    if(GET_VGA_INITIAL() == _TRUE)
    {
        // Calculate IH Frequency
        CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
        stModeInfo.IHCount = ((pData[0] & 0x07) << 8) | pData[1];

        // V012 Modify 20100331 Start
        // V012 Patch Note (21) : Fix the sync processor compatibility problem. Replace slower XTAL clock with M2PLL.
        /*
        stModeInfo.IHFreq = (WORD)((DWORD)_RTD_XTAL * 10 * 2 / stModeInfo.IHCount);
        */
        stModeInfo.IHFreq = (WORD)((DWORD)_INTERNAL_SYSTEM_CLK * 10 * 2 / stModeInfo.IHCount);
        // V012 Modify 20100331 End

        stModeInfo.IHFreq = (stModeInfo.IHFreq >> 1) + (stModeInfo.IHFreq & 0x01);

        // Calculate ADC Clock by Frequency
        g_usAdcClockLimit = (WORD)(((DWORD)_ADC_SAMPLE_CLOCK_LIMIT / stModeInfo.IHFreq / 4) * 4);

        // Check ADC Clock Limit
        if(g_usAdcClockLimit > _PIXEL_WIDTH_LIMIT)
        {
            g_usAdcClockLimit = _PIXEL_WIDTH_LIMIT;
        }

        // V014 VGA Patch Note (6) Modify 20100527 Start
        // Patch Reason : Modify Video Mode Can't Light On
        /*
        // V013 VGA Patch Note (23) Modify 20100513 Start
        // Patch Reason : For Video Mode Clamp Position Setting Flow
        if(stModeInfo.ModeCurr < _MAX_YPBPR_MODE) // Current Mode Is Video Mode
        {
            bVideoModeFlg = _TRUE;
            // Update Video Mode Clamp Position
            CYPbPrModeClampPositionSetting();
        }
        else
        {
            bVideoModeFlg = _FALSE;
            stModeInfo.ModeCurr = 0;
        }
        // V013 VGA Patch Note (23) Modify 20100513 End
        */
        // V014 VGA Patch Note (6) Modify 20100527 End

#if(_YPBPR_SUPPORT == _ON)
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
        {
            stModeUserData.Clock = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IHTotal;
            CAdjustAdcClock(stModeUserData.Clock);
        }
        else
#endif
        {
            // V014 VGA Patch Note (6) Modify 20100527 Start
            // Patch Reason : Modify Video Mode Can't Light On
            /*
            // V013 VGA Patch Note (23) Modify 20100513 Start
            // Patch Reason : For Video Mode Clamp Position Setting Flow
            /*
            stModeUserData.Clock = g_usAdcClockLimit;
            * /
            if(bVideoModeFlg == _TRUE)
            {
                stModeUserData.Clock = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IHTotal;
            }
            else
            {
                stModeUserData.Clock = g_usAdcClockLimit;
            }
            // V013 VGA Patch Note (23) Modify 20100513 End
            */
            stModeUserData.Clock = g_usAdcClockLimit;
            // V014 VGA Patch Note (6) Modify 20100527 End

            CAdjustAdcClock(stModeUserData.Clock);
        }

        // Adjust ADC Setting (Include Clamp Enable)
        CAdjustADCSetting();

        // bit3~bit2: Set input pixel format, bit1: select analog or digtal input
        CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT1), 0);

        CScalerPageSelect(_PAGE0);

        if(((bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6) ^ (bit)CScalerGetBit(_SYNC_INVERT_48, _BIT3)) == _TRUE)
        {
            // As negative HS,we must clear CR[P0_F4] BIT6 and set schmitt trigger by high level to avoid noise
            CScalerSetBit(_P0_HS_SCHMITT_TRIGGER_CTRL_F4, ~_BIT6, 0x00);
        }
        else
        {
            CScalerSetBit(_P0_HS_SCHMITT_TRIGGER_CTRL_F4, ~_BIT6, _BIT6);
        }

        // Wait for ADC clamp stable and interlace flag update
        CTimerWaitForEvent(_EVENT_IVS);
        CTimerWaitForEvent(_EVENT_IVS);
        CTimerWaitForEvent(_EVENT_IVS);

        if(CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT0) == _BIT0)
        {
            // Select Hsync Measure Source to ADC_HS
            CScalerSetBit(_SYNC_CTRL_49, ~_BIT2, 0x00);
        }

        CLR_VGA_INITIAL();
    }
}

//--------------------------------------------------
// Description  : Check if the height measured is OK
//                This function also modify the height if
//                the measured height is abnormal.
// Input Value  : Measured Height
// Output Value : Verified Height
//--------------------------------------------------
WORD CModeIVHeightVerify(WORD usIVHeight)
{
    BYTE i = 0;

    ((WORD *)pData)[0] = 0; // Reference height to get from the mode table
    ((WORD *)pData)[1] = 0xFFFF; // Min difference value for recording
    ((WORD *)pData)[2] = (WORD)((DWORD)stModeInfo.IVTotal * _MAX_IVHEIGHT_RATIO / 1000); // IVHeight limit

    for(i = 0; i < _MAX_PRESET_MODE; i++)
    {
        if((tINPUTMODE_PRESET_TABLE[i].IVHeight < ((WORD *)pData)[2]) && (abs(usIVHeight - tINPUTMODE_PRESET_TABLE[i].IVHeight) < ((WORD *)pData)[1]))
        {
            ((WORD *)pData)[1] = abs(usIVHeight - tINPUTMODE_PRESET_TABLE[i].IVHeight);
            ((WORD *)pData)[0] = tINPUTMODE_PRESET_TABLE[i].IVHeight;
        }
    }

    if(usIVHeight < ((WORD *)pData)[2])
    {
        if(abs(usIVHeight - ((WORD *)pData)[0]) > _MODE_IVHEIGHT_TOLERANCE)
        {
            return usIVHeight;
        }
        else
        {
            return ((WORD *)pData)[0];
        }
    }

    return ((WORD *)pData)[0];
}

//--------------------------------------------------
// Description  : Check stored user data for frame sync
//                Reset user data and centered data if frame sync failed
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeCheckUserData(void)
{
    BYTE ucModeTemp = 0;

    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        ucModeTemp = stModeInfo.ModeCurr;
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);
        ucModeTemp = pData[(stModeInfo.ModeCurr % 4) * 4];
    }

    stDisplayInfo.DVHeight = _PANEL_DV_HEIGHT;

    CFrameSyncModifyDVStartPos(_DVSTART_POS_ADJUSTING);

    // Calculate DVStart due to display ratio
    ((DWORD *)pData)[3] = (DWORD)stDisplayInfo.DVStartPos * 10 * tINPUTMODE_PRESET_TABLE[ucModeTemp].IVHeight / stDisplayInfo.DVHeight;

    if((stModeUserCenterData.CenterClock > g_usAdcClockLimit) ||
       (stModeUserData.Clock > g_usAdcClockLimit) ||
       (CAutoCheckCaptureStart(stModeUserCenterData.CenterHPos, stModeUserData.Clock) == _FALSE) ||
       (CAutoCheckCaptureStart(stModeUserCenterData.CenterHPos, stModeUserCenterData.CenterClock) == _FALSE) ||

       // V013 VGA Patch Note (26) Modify 20100517 Start
       // Patch Reason : Fix if clock is too large and causes over large picture.
       // As the timing table lists, all the modes have stModeInfo.IHWidth / stModeUserData.Clock > 70%.

       // V014 VGA Patch Note (3) Modify 20100526 Start
       // Patch Reason : Change the compare ratio to 60%, as 720p50 was found to have about 65% of width/HTotal ratio.
       /*
       ((DWORD)stModeUserData.Clock * 7 > (DWORD)stModeInfo.IHWidth * 10) ||
       ((DWORD)stModeUserCenterData.CenterClock * 7 > (DWORD)stModeInfo.IHWidth * 10) ||
        */
       ((DWORD)stModeUserData.Clock * 6 > (DWORD)stModeInfo.IHWidth * 10) ||
       ((DWORD)stModeUserCenterData.CenterClock * 6 > (DWORD)stModeInfo.IHWidth * 10) ||
       // V014 VGA Patch Note (3) Modify 20100526 End

       // V013 VGA Patch Note (26) Modify 20100517 End

       ((stModeUserData.VPosition * 10 + 15) < ((DWORD *)pData)[3])) // Check Frame Sync Formula : IVToDVdelay = IVStart + 2.5 - DVStart > 1
    {
        // Load default user data
        CLR_AUTO_FLAG();
        CLR_AUTO_FAIL_COUNT();

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
#if(_COLOR_FORMAT_CONVERT == _ON)
        CLR_MODE_COLOR_FORMAT_FLAG();
#endif
// V014 VGA Patch Note (6) Modify 20100527 End

        stModeUserData.HPosition = tINPUTMODE_PRESET_TABLE[ucModeTemp].IHStartPos;
        stModeUserData.VPosition = tINPUTMODE_PRESET_TABLE[ucModeTemp].IVStartPos;
        stModeUserData.Clock = tINPUTMODE_PRESET_TABLE[ucModeTemp].IHTotal;
        stModeUserData.Phase = 0;
        CEepromSaveModeData(stModeInfo.ModeCurr);

        // Load default center data
        stModeUserCenterData.CenterClock = tINPUTMODE_PRESET_TABLE[ucModeTemp].IHTotal;
        stModeUserCenterData.CenterHPos = tINPUTMODE_PRESET_TABLE[ucModeTemp].IHStartPos;
        stModeUserCenterData.CenterVPos = tINPUTMODE_PRESET_TABLE[ucModeTemp].IVStartPos;
        stModeUserCenterData.CenterPhase = 0;
        CEepromSaveCenterModeData(stModeInfo.ModeCurr);
    }
}

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#if(_COLOR_FORMAT_CONVERT == _ON)
//--------------------------------------------------
// Description  : Color Format Convert for RGB/YUV
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeColorFormatConvert(void)
{
    // V013 VGA Patch Note (2) 20100407 Modify Start
    // Patch Reason : Load ADC Gain/Offset value as color space conversion
    BYTE ucTemp = 0;
    // V013 VGA Patch Note (2) 20100407 Modify End

    if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) || (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
    {
        if(GET_COLOR_FORMAT_STATUS() == g_bColorFormatStatus)
        {
            return;
        }

        if(GET_COLOR_FORMAT_STATUS() == _YUV_COLOR_FORMAT)
        {
            CModeSetRGBToYUV();

            // V013 VGA Patch Note (2) 20100407 Modify Start
            // Patch Reason : Load ADC Gain/Offset value as color space conversion
            ucTemp = GET_INPUTSOURCE_TYPE();
            SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);
            // V013 VGA Patch Note (2) 20100407 Modify End
        }
        else
        {
            CModeSetYUVToRGB();

            // V013 VGA Patch Note (2) 20100407 Modify Start
            // Patch Reason : Load ADC Gain/Offset value as color space conversion
            ucTemp = GET_INPUTSOURCE_TYPE();
            SET_INPUTSOURCE_TYPE(_SOURCE_VGA);
            // V013 VGA Patch Note (2) 20100407 Modify End
        }

        // V013 VGA Patch Note (2) 20100407 Modify Start
        // Patch Reason : Load ADC Gain/Offset value as color space conversion
        CEepromLoadAdcData();
        SET_INPUTSOURCE_TYPE(ucTemp);
        CAdjustAdcGain();
        CAdjustAdcOffset();
#if _DEBUG_MESSAGE_SUPPORT
		
		CDebugMessage("CModeColorFormatConvert", 0);
		CDebugMessage("stAdcData.AdcGain.[_RED]",stAdcData.AdcGain[_RED]);
		CDebugMessage("stAdcData.AdcGain.[_GREEN]",stAdcData.AdcGain[_GREEN]);
		CDebugMessage("stAdcData.AdcGain.[_BLUE]",stAdcData.AdcGain[_BLUE]);
		
		CDebugMessage("stAdcData.AdcOffset.[_RED]",stAdcData.AdcOffset[_RED]);
		CDebugMessage("stAdcData.AdcOffset.[_GREEN]",stAdcData.AdcOffset[_GREEN]);
		CDebugMessage("stAdcData.AdcOffset.[_BLUE]",stAdcData.AdcOffset[_BLUE]);
		
		
		
		
		
#endif
        // V013 VGA Patch Note (2) 20100407 Modify End

        g_bColorFormatStatus = GET_COLOR_FORMAT_STATUS();
    }
}

//--------------------------------------------------
// Description  : RGB to YUV Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetRGBToYUV()
{
    CScalerCodeW(tYPBPR_TABLE_SET_SCALER);
    CAdjustBrightness(stConBriData.Brightness);
    CAdjustContrast(stConBriData.Contrast);
}

//--------------------------------------------------
// Description  : YUV to RGB Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetYUVToRGB()
{
#if(_SCALER_TYPE == _RTD2472D)

    CScalerSetByte(_YUV2RGB_CTRL_9C, 0x02);
    CScalerSetByte(_YUV_RGB_ACCESS_9D, 0x00);
    CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

    CScalerPageSelect(_PAGE7);
    CScalerSetByte(_P7_YUV2RGB_CTRL_BF, 0x02);
    CScalerSetByte(_P7_YUV2RGB_ACCESS_C0, 0x00);
    CScalerSetByte(_P7_YUV2RGB_CTRL_BF, 0x00);

#endif

    CScalerPageSelect(_PAGE0);
    CScalerSetByte(_P0_ADC_V_BIAS1_CD, 0x09);

    // V015 VGA Patch Note (1) Modify 20100607 Start
    // Patch Reason : Write register by set bit method
    /*
    CScalerSetByte(_P0_ADC_RED_CTL_CF, 0x40);
    CScalerSetByte(_P0_ADC_GREEN_CTL_D0, 0x40);
    CScalerSetByte(_P0_ADC_BLUE_CTL_D1, 0x40);
    */
    CScalerSetBit(_P0_ADC_RED_CTL_CF, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);
    CScalerSetBit(_P0_ADC_GREEN_CTL_D0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);
    CScalerSetBit(_P0_ADC_BLUE_CTL_D1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);
    // V015 VGA Patch Note (1) Modify 20100607 End
}

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
//--------------------------------------------------
// Description  : Color Format Convert for RGB/YUV By User Setting Last Time
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeGetCurrentModeColorFormat(void)
{
    // V016 VGA Patch Note (11) Modify 20100830 Start
    // Patch Reason : Modify Color Space Load Data Position For OverScan.
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) || (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
        {
            g_bColorFormatStatus = _YUV_COLOR_FORMAT;
        }
        else
        {
            g_bColorFormatStatus = _RGB_COLOR_FORMAT;
        }
    }
    // V016 VGA Patch Note (11) Modify 20100830 End

    // Check current mode color format
    if(GET_MODE_COLOR_FORMAT_FLAG() == _YUV_COLOR_FORMAT)
    {
        SET_COLOR_FORMAT_STATUS(_YUV_COLOR_FORMAT);
    }
    else
    {
        SET_COLOR_FORMAT_STATUS(_RGB_COLOR_FORMAT);
    }
}
// V014 VGA Patch Note (6) Modify 20100527 End

#endif  // End of #if(_COLOR_FORMAT_CONVERT == _ON)
// V012 Modify 20100304 End

// V013 VGA Patch Note (10) 20100416 Modify Start
// Patch Reason : Support Auto Config For Yuv Color.
//--------------------------------------------------
// Description  : Switch Yuv to Rgb For Auto
// Input Value  : Color Space Type
// Output Value : None
//--------------------------------------------------
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
void CModeYuvRgbSwitch(BYTE ucColorType)
{
    BYTE ucSourceTemp = _SOURCE_NONE;

#if(_YPBPR_SUPPORT == _ON)
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
#else
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
#endif
    {
        if(ucColorType == _RGB_COLOR_FORMAT)
        {
            if(CModeGetColorSpaceType() == _YUV_COLOR_FORMAT)
            {
                // Switch to RGB Color Type
                CScalerPageSelect(_PAGE0);

                // V015 VGA Patch Note (1) Modify 20100607 Start
                // Patch Reason : Write register by set bit method
                /*
                CScalerSetByte(_P0_ADC_RED_CTL_CF, _BIT6);
                CScalerSetByte(_P0_ADC_GREEN_CTL_D0, _BIT6);
                CScalerSetByte(_P0_ADC_BLUE_CTL_D1, _BIT6);
                */
                CScalerSetBit(_P0_ADC_RED_CTL_CF, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);
                CScalerSetBit(_P0_ADC_GREEN_CTL_D0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);
                CScalerSetBit(_P0_ADC_BLUE_CTL_D1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);
                // V015 VGA Patch Note (1) Modify 20100607 End

                // Adjust RGB Gain And Offset
                ucSourceTemp = GET_INPUTSOURCE_TYPE();
                SET_INPUTSOURCE_TYPE(_SOURCE_VGA);
                CEepromLoadAdcData();
                SET_INPUTSOURCE_TYPE(ucSourceTemp);
                CAdjustAdcGain();
                CAdjustAdcOffset();

                g_bYuvRgbFlag = _TRUE;
            }
            else
            {
                g_bYuvRgbFlag = _FALSE;
            }
        }
        else
        {
            if(g_bYuvRgbFlag == _TRUE)
            {
                // Switch to YUV Color Type
                CScalerPageSelect(_PAGE0);

                // V015 VGA Patch Note (1) Modify 20100607 Start
                // Patch Reason : Write register by set bit method
                /*
                CScalerSetByte(_P0_ADC_RED_CTL_CF, _BIT6 | _BIT7);
                CScalerSetByte(_P0_ADC_GREEN_CTL_D0, _BIT6);
                CScalerSetByte(_P0_ADC_BLUE_CTL_D1, _BIT6 | _BIT7);
                */
                CScalerSetBit(_P0_ADC_RED_CTL_CF, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6 | _BIT7);
                CScalerSetBit(_P0_ADC_GREEN_CTL_D0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);
                CScalerSetBit(_P0_ADC_BLUE_CTL_D1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6 | _BIT7);
                // V015 VGA Patch Note (1) Modify 20100607 End

                // Adjust RGB Gain And Offset
                ucSourceTemp = GET_INPUTSOURCE_TYPE();
                SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);
                CEepromLoadAdcData();
                SET_INPUTSOURCE_TYPE(ucSourceTemp);
                CAdjustAdcGain();
                CAdjustAdcOffset();

                g_bYuvRgbFlag = _FALSE;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get Color Space Type
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
BYTE CModeGetColorSpaceType(void)
{
    CScalerPageSelect(_PAGE0);
    CScalerRead(_P0_ADC_RED_CTL_CF, 1, pData, _NON_AUTOINC);

    if((pData[0] & _BIT7) == _BIT7)
    {
        return _YUV_COLOR_FORMAT; // YUV Color Space
    }
    else
    {
        return _RGB_COLOR_FORMAT; // RGB Color Space
    }
}
#endif
// V013 VGA Patch Note (10) 20100416 Modify End

// V012 Modify 20100322 Start
// V012 Patch Note (8) : Add OOR Table to indicate in which modes the display could show OOR directly.
//--------------------------------------------------
// Description  : Search fit OOR Mode
// Input Value  : OOR Input Mode Table Index
// Output Value : _TRUE : is OOR Mode
//                _FALSE: not OOR Mode
//--------------------------------------------------
bit CModeSearchOORModeVGA(BYTE ucModeCnt)
{
    if(abs(stModeInfo.IHFreq - tOORINPUT_MODE_TABLE[ucModeCnt].IHFreq) > _HFREQ_TOLERANCE)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IVFreq - tOORINPUT_MODE_TABLE[ucModeCnt].IVFreq) > _VFREQ_TOLERANCE)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IVTotal - tOORINPUT_MODE_TABLE[ucModeCnt].IVTotal) > 1)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IVSyncPulseCount - tOORINPUT_MODE_TABLE[ucModeCnt].IVSyncPulse) > 1)
    {
        return _FALSE;
    }

    return _TRUE;
}
// V012 Modify 20100322 End

// V012 Modify 20100324 Start
// V012 Patch Note (3) : Modify mode table and mode search according to SQE testing items, and to sync with Dell case.
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchAcceptivePresetModeVGA(BYTE ucModeCnt)
{
    BYTE ucPolarity = 0;
    BYTE ucPolaritTtemp = 0;
    WORD usIHSyncpulseCnt = 0;

    // V012 Modify 20100331 Start
    // V012 Patch Note (21) : Fix the sync processor compatibility problem. Replace slower XTAL clock with M2PLL.
    /*
    usIHSyncpulseCnt = stModeInfo.IHSyncPulseCount;
    */
    usIHSyncpulseCnt = (DWORD)stModeInfo.IHSyncPulseCount * _XTAL27000K / _INTERNAL_SYSTEM_CLK;
    // V012 Modify 20100331 End

#if(_HSYNC_DETECTION == _AUTO_RUN)
    ucPolarity = ((stModeInfo.Polarity & ~_BIT0) | ( ! (((bit)CScalerGetBit(_SYNC_INVERT_48, _BIT3) ? 0x00 : _BIT0) ^ ((bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6) ? 0x00 : _BIT0))));
#else
    ucPolarity = ((stModeInfo.Polarity & ~_BIT0) | ((bit)CScalerGetBit(_SYNC_INVERT_48, _BIT3) ? 0x00 : _BIT0));
#endif

    if((bit)(ucPolarity & _BIT0))
    {
        if((bit)(ucPolarity & _BIT1))
        {
            ucPolaritTtemp = _SYNC_HP_VP;
        }
        else
        {
            ucPolaritTtemp = _SYNC_HP_VN;
        }
    }
    else
    {
        if((bit)(ucPolarity & _BIT1))
        {
            ucPolaritTtemp = _SYNC_HN_VP;
        }
        else
        {
            ucPolaritTtemp = _SYNC_HN_VN;
        }
    }

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    if((ucModeCnt == _MODE_640x350_70HZ) && (ucPolaritTtemp == _SYNC_HN_VP))
    {
        ucModeCnt = _MODE_720x400_70HZ;
    }
    else if((ucModeCnt == _MODE_1024x768_75HZ) && (ucPolaritTtemp == _SYNC_HN_VP))
    */

    // V016 VGA Patch Note (3) Modify 20100730 Start
    // Patch Reason : Modify 640x350_70 Timing to show blank on top and buttom.
    /*
    if((ucModeCnt == _MODE_640x350_70HZ))
    {
        if(CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, (_BIT6 | _BIT5 | _BIT4)) == 0x60) // SS Sync Type
        {
            if(ucPolaritTtemp == _SYNC_HN_VP)
            {
                ucModeCnt = _MODE_720x400_70HZ;
            }
        }
        else
        {
            // V015 VGA Patch Note (8) Modiy 20100624 Start
            // Patch Reason : Mode search updates.
            / *
            if(g_usCurrIVHeight > 350)
            {
                ucModeCnt = _MODE_720x400_70HZ;
            }
            * /
            // As height decision dependes on the picture content, which would probably make SQE confuse.
            // Always use 720x400@70 for the CS/SOG situation.
            ucModeCnt = _MODE_720x400_70HZ;
            // V015 VGA Patch Note (8) Modiy 20100624 End
        }
    }
    else if((ucModeCnt == _MODE_1024x768_75HZ) && (stModeInfo.IVSyncPulseCount > 5))
    */
    if((ucModeCnt == _MODE_1024x768_75HZ) && (stModeInfo.IVSyncPulseCount > 5))
    // V016 VGA Patch Note (3) Modify 20100730 End

    // V013 VGA Patch Note (24) Modify 20100514 End
    {
        ucModeCnt = _MODE_1280x768_75HZ;
    }

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    else if((ucModeCnt == _MODE_1280x768_60HZ) && (ucPolaritTtemp == _SYNC_HP_VP))
    {
        if(stModeInfo.IVSyncPulseCount < 5)
        {
            ucModeCnt = _MODE_1366x768_60HZ;
        }
        else if(stModeInfo.IVSyncPulseCount < 7)
        {
            ucModeCnt = _MODE_1360x768_60HZ;
        }
    }
    */
    else if(ucModeCnt == _MODE_1280x768_60HZ)
    {
        if(stModeInfo.IVSyncPulseCount < 5)
        {
            ucModeCnt = _MODE_1366x768_60HZ;
        }
        else if(stModeInfo.IVTotal <= 796)
        {
            ucModeCnt = _MODE_1360x768_60HZ;
        }
    }
    // V013 VGA Patch Note (24) Modify 20100514 End

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    else if((ucModeCnt == _MODE_720x400_85HZ) && (ucPolaritTtemp == _SYNC_HP_VN))
    {
        ucModeCnt = _MODE_640x350_85HZ;
    }
    else if((ucModeCnt == _MODE_1024x768_85HZ) && (ucPolaritTtemp == _SYNC_HN_VP))
    {
        ucModeCnt = _MODE_1280x768_85HZ;
    }
    */
    // V013 VGA Patch Note (24) Modify 20100514 End

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    else if((ucModeCnt == _MODE_640x480_75HZ) && (stModeInfo.IVTotal > 501))
    {
        ucModeCnt = _MODE_848x480_75HZ;
    }
    // V013 VGA Patch Note (24) Modify 20100514 End

    if((ucModeCnt == _MODE_640x480_60HZ) && (stModeInfo.IVSyncPulseCount > 4))
    {
        ucModeCnt = _MODE_720x480p_60HZ;
    }
    else if((ucModeCnt == _MODE_640x480_60HZ) && (abs(usIHSyncpulseCnt - 59) <= 4))
    {
        ucModeCnt = _MODE_720x480_60HZ_GTF;
    }

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    else if((ucModeCnt == _MODE_1280x768_60HZ) && (abs(usIHSyncpulseCnt - 15) <= 10))
    */
    else if((ucModeCnt == _MODE_1280x768_60HZ) && (usIHSyncpulseCnt <= 28))
    // V013 VGA Patch Note (24) Modify 20100514 End

    {
        ucModeCnt = _MODE_1280x768_60HZ_RB;
    }
    else if((ucModeCnt == _MODE_1024x768_60HZ_MAC) && (abs(usIHSyncpulseCnt - 36) <= 1))
    {
        ucModeCnt = _MODE_1360x768_60HZ;
    }
    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    else if((ucModeCnt == _MODE_1280x768_60HZ_RB) && (usIHSyncpulseCnt >= 27))
    {
        ucModeCnt = _MODE_1280x768_60HZ;
    }
    */
    // V013 VGA Patch Note (24) Modify 20100514 End

    // V015 VGA Patch Note (8) Modiy 20100624 Start
    // Patch Reason : Mode search updates.
    /*
    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    else if((ucModeCnt == _MODE_1920x1200_60HZ) && (stModeInfo.IVSyncPulseCount < 5))
    {
        ucModeCnt = _MODE_1600x1200_60HZ;
    }
    // V013 VGA Patch Note (24) Modify 20100514 End
    */
    else if((ucModeCnt == _MODE_1920x1200_60HZ) && (stModeInfo.IVSyncPulseCount < 5) && (stModeInfo.IVTotal < 1240))
    {
        ucModeCnt = _MODE_1600x1200_60HZ;
    }
    // V015 VGA Patch Note (8) Modiy 20100624 End

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    else if((ucModeCnt == _MODE_1920x1200_60HZ) && (usIHSyncpulseCnt <= 12))
    */

    else if((ucModeCnt == _MODE_1920x1200_60HZ) && (usIHSyncpulseCnt <= 16))
    // V013 VGA Patch Note (24) Modify 20100514 End

    {
        ucModeCnt = _MODE_1920x1200_60HZ_RB;
    }

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    else if((ucModeCnt == _MODE_1600x1200_60HZ_RB) && (stModeInfo.IVSyncPulseCount >= 5))
    {
        ucModeCnt = _MODE_1920x1200_60HZ_RB;
    }
    else if((ucModeCnt == _MODE_1920x1080_60HZ_XBOX) && (stModeInfo.IVSyncPulseCount <= 5))
    {
        ucModeCnt = _MODE_1920x1080_60HZ_RB;
    }
    */
    else if((ucModeCnt == _MODE_1600x1200_60HZ_RB) && (stModeInfo.IVSyncPulseCount > 5))
    {
        ucModeCnt = _MODE_1920x1200_60HZ_RB;
    }
    // V013 VGA Patch Note (24) Modify 20100514 End

    else if(ucModeCnt == _MODE_640x400_70HZ)
    {
        ucModeCnt = _MODE_720x400_70HZ;
    }

    // V014 VGA Patch Note (2) Modify 20100526 Start
    // Patch Reason : Use width/HTotal ratio to distinguish mode _MODE_1440x900_60HZ_RB and _MODE_1600x900_60HZ_CVR.
    /*
    else if((ucModeCnt == _MODE_1440x900_60HZ_RB) && (stModeInfo.IVSyncPulseCount <= 5))
    {
        ucModeCnt = _MODE_1600x900_60HZ_CVR;
    }
    */
    else if(ucModeCnt == _MODE_1440x900_60HZ_RB)
    {
        if(labs((DWORD)(g_usHEndPos + 1 - g_usHStartPos) * tINPUTMODE_PRESET_TABLE[_MODE_1600x900_60HZ_CVR].IHTotal - (DWORD)tINPUTMODE_PRESET_TABLE[_MODE_1600x900_60HZ_CVR].IHWidth * stModeUserData.Clock) < (DWORD)5 * stModeUserData.Clock * tINPUTMODE_PRESET_TABLE[_MODE_1600x900_60HZ_CVR].IHTotal / 1000)
        {
            ucModeCnt = _MODE_1600x900_60HZ_CVR;
        }
        else if(labs((DWORD)(g_usHEndPos + 1 - g_usHStartPos) * tINPUTMODE_PRESET_TABLE[_MODE_1440x900_60HZ_RB].IHTotal - (DWORD)tINPUTMODE_PRESET_TABLE[_MODE_1440x900_60HZ].IHWidth * stModeUserData.Clock) < (DWORD)5 * stModeUserData.Clock * tINPUTMODE_PRESET_TABLE[_MODE_1440x900_60HZ].IHTotal / 1000)
        {
            ucModeCnt = _MODE_1440x900_60HZ_RB;
        }
        else if(stModeInfo.IVSyncPulseCount <= 5)
        {
            ucModeCnt = _MODE_1600x900_60HZ_CVR;
        }
    }
   // V014 VGA Patch Note (2) Modify 20100526 End

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    else if((ucModeCnt == _MODE_1280x720p_60HZ) && (usIHSyncpulseCnt > 32))
    */
    else if((ucModeCnt == _MODE_1280x720p_60HZ) && (usIHSyncpulseCnt >= 30))
    // V013 VGA Patch Note (24) Modify 20100514 End

    {
        ucModeCnt = _MODE_1280x720_60HZ_2;
    }

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    else if((ucModeCnt == _MODE_1280x960_60HZ) && (usIHSyncpulseCnt <= 24))
    */
    else if((ucModeCnt == _MODE_1280x960_60HZ) && (usIHSyncpulseCnt <= 23))

    // V013 VGA Patch Note (24) Modify 20100514 End

    {
        ucModeCnt = _MODE_1600x900_60HZ_RB;
    }
    else if((ucModeCnt == _MODE_1024x768_75HZ) && (stModeInfo.IVSyncPulseCount > 5))
    {
        ucModeCnt = _MODE_1280x768_75HZ;
    }
    else if((ucModeCnt == _MODE_1440x900_75HZ) && (stModeInfo.IHFreq > 712))
    {
        ucModeCnt = _MODE_1152x900_76HZ;
    }

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    else if((ucModeCnt == _MODE_720x576p_50Hz) && (stModeInfo.IVSyncPulseCount > 12))
    {
        ucModeCnt = _MODE_1920x1080i_50HZ_2;
    }
    */
    else if((ucModeCnt == _MODE_720x576p_50Hz) && (GET_INTERLACE_MODE() == 1))
    {
        ucModeCnt = _MODE_1920x1080i_50HZ_2;
    }
    // V013 VGA Patch Note (24) Modify 20100514 End

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    // _MODE_1600x900_60HZ is a non-RB mode, suggested by Y.C., which could solve
    // Graphic Card issue.
    else if((ucModeCnt == _MODE_1440x900_60HZ) && (stModeInfo.IVSyncPulseCount < 5))
    {
        ucModeCnt = _MODE_1600x900_60HZ;
    }
    // V013 VGA Patch Note (24) Modify 20100514 End

    // V016 VGA Patch Note (6) Modify 20100806 Start
    // Patch Reason : Solve Intel G43(VOSTRO) catpure 1280x768x75 timing mode error to 1024x768x75 timing mode
    else if((ucModeCnt == _MODE_1024x768_75HZ) && (stModeInfo.IVTotal > 801) && (stModeInfo.IVTotal < 803))
    {
        ucModeCnt = _MODE_1280x768_75HZ;
    }
    // V016 VGA Patch Note (6) Modify 20100806 End

    // V016 VGA Patch Note (16) Modify 20100901 Start
    // Patch Reason : Solve Chroma2233B at 1360x768x60 error to 1280x768x60_RB timing mode
    if((ucModeCnt == _MODE_1280x768_60HZ_RB) && (stModeInfo.IVTotal > 792) && (stModeInfo.IVTotal < 794) && (usIHSyncpulseCnt) > 30)
    {
        ucModeCnt = _MODE_1360x768_60HZ;
    }
    // V016 VGA Patch Note (16) Modify 20100901 End

    // V012 Modify 20100331 Start
    // V012 Patch Note (30) : Use mode search incorrect flag to skip SOD clock seeking in the auto stage to avoid one missing vertical line at the edge of the picture.
    // Use this flag to tell auto clock never to do the SOD clock seeking if a 1400x1050 is searched as 1680x1050 (SQE requires 1400x1050 is searched as 1680x1050.
    if(((ucModeCnt == _MODE_1680x1050_60HZ) || (ucModeCnt == _MODE_1680x1050_60HZ_RB) || (ucModeCnt == _MODE_1680x1050_75HZ)) && (stModeInfo.IVSyncPulseCount < 5))
    {
        g_bModeSearchIncorrectFlag = _TRUE;
    }
    // V012 Modify 20100331 End

    return ucModeCnt;
}
// V012 Modify 20100324 End

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Overscan Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeOverScanSelect(void)
{
    CLR_OVERSCAN_STATUS();
    CLR_OVERSCAN_SUCCESS_STATUS();

    g_ucOverScanH = 0;
    g_ucOverScanV = 0;

    if(GET_OVERSCAN_CAPTURE_BACKUP_VALUE() == _FALSE)
    {
        g_usOldIHWidth = stModeInfo.IHWidth;
        g_usOldIVHeight = stModeInfo.IVHeight;
        SET_OVERSCAN_CAPTURE_BACKUP_VALUE();
    }

    if(CModeOverScanSourceSelect() == _FALSE)
    {
        return;
    }

// V016 System Patch Note (25) Modify 20100831 Start
// Patch Reason : Modify Overscan Effect Condition.
/*
    if(CModeOverScanTimingSelect() == _TRUE)
*/
    if(CModeOverScanConditionSwitch() == _TRUE)
// V016 System Patch Note (25) Modify 20100831 End
    {
        CModeDecideOverScanValue();
    }

    stModeInfo.IHWidth = g_usOldIHWidth - (2 * g_ucOverScanH);
    stModeInfo.IVHeight = g_usOldIVHeight - (2 * g_ucOverScanV);

    if(CModeOverScanCheckCaptureWindow() == _FALSE)
    {
        stModeInfo.IHWidth = g_usOldIHWidth;
        stModeInfo.IVHeight = g_usOldIVHeight;
        return;
    }

    SET_OVERSCAN_STATUS();
    SET_OVERSCAN_SUCCESS_STATUS();
}

//--------------------------------------------------
// Description  : Overscan Adjust Pos Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeOverScanAdjustPos(void)
{
     // Backup IVS2DVS Delay Value By g_ucIv2DvModify
    if(GET_OVERSCAN_IV2DVDELAY_BACKUP_VALUE() == _FALSE)
    {
        CScalerRead(_IVS2DVS_DELAY_LINES_40, 1, &g_ucIv2DvModify, _NON_AUTOINC);
        SET_OVERSCAN_IV2DVDELAY_BACKUP_VALUE();
    }

    if(GET_OVERSCAN_STATUS() == _FALSE)
    {
        return;
    }
    else
    {
        CLR_OVERSCAN_STATUS();
    }

    CModeOverScanSetCaptureStart();

    if((g_ucOverScanH == 0) || (g_ucOverScanV == 0))
    {
        CLR_OVERSCAN_SUCCESS_STATUS();
    }

    stModeInfo.IHWidth = g_usOldIHWidth;
    stModeInfo.IVHeight = g_usOldIVHeight;
}

//--------------------------------------------------
// Description  : Decide Overscan Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeDecideOverScanValue(void)
{
    BYTE cnt = 0;
    BYTE ucModeIndex = 0;

    g_ucOverScanH = 0;
    g_ucOverScanV = 0;

    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        ucModeIndex = stModeInfo.ModeCurr;
    }
    else
    {
        ucModeIndex = g_ucUserModeCurr;
    }

    stDisplayInfo.DVHeight = _PANEL_DV_HEIGHT;
    stDisplayInfo.DHTotal = _PANEL_DH_TOTAL;

    ((DWORD *)pData)[0] = ((DWORD)stDisplayInfo.DHTotal * stModeInfo.IHFreq * stDisplayInfo.DVHeight);

    // ((DWORD *)pData)[1] is the minimal result of IVHeight for over scan
    //  D clock = DHTotal * IHFreq * DVHeight / IVHeight
    if((((DWORD *)pData)[0] % ((DWORD)_PANEL_PIXEL_CLOCK_MAX * 10000)) != 0)
    {
        ((DWORD *)pData)[1] = ((DWORD *)pData)[0] / ((DWORD)_PANEL_PIXEL_CLOCK_MAX * 10000) + 1;
    }
    else
    {
        ((DWORD *)pData)[1] = ((DWORD *)pData)[0] / ((DWORD)_PANEL_PIXEL_CLOCK_MAX * 10000);
    }

    if(stModeInfo.IVHeight <= ((DWORD *)pData)[1])
    {
        return;
    }

    // The max value of OverScanV is bigger than 255
    if((stModeInfo.IVHeight - ((DWORD *)pData)[1]) >= (0xFF * 2))
    {
        pData[15] = 0xFC; // Max OverScanV Value for BYTE type
    }
    else
    {
        pData[15] = ((stModeInfo.IVHeight - ((DWORD *)pData)[1]) / 2) & 0xFC; // Max OverScanV Value
    }

#if(_TMDS_SUPPORT == _ON)
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    || (GET_INPUTSOURCE_TYPE() == _SOURCE_DVI)

#if(_HDMI_SUPPORT == _ON)
    || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
#endif

#if(_DP_SUPPORT == _ON)
    || (GET_INPUTSOURCE_TYPE() == _SOURCE_DP)
#endif
    )
#else // Else #if(_TMDS_SUPPORT == _ON)
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
#endif // End of #if(_TMDS_SUPPORT == _ON)
    {
        do
        {
            if(tOVERSCAN_DISPLAY_TABLE[cnt].ucModeIndex == ucModeIndex)
            {
                g_ucOverScanH = ((BYTE)((DWORD)stModeInfo.IHWidth * tOVERSCAN_DISPLAY_TABLE[cnt].usIHWidthRatio / 1000));
                g_ucOverScanV = ((BYTE)((DWORD)stModeInfo.IVHeight * tOVERSCAN_DISPLAY_TABLE[cnt].usIVHeightRatio / 1000));
                ucModeIndex = 0xFE; // UcModeIndex = 0xFE means a mode was found, as this variable was not initialized to 0xFE
                break;
            }

            cnt++;
        }
        while((tOVERSCAN_DISPLAY_TABLE[cnt].ucModeIndex != 0xFF) && (cnt < _MAX_PRESET_MODE));

        if(ucModeIndex != 0xFE) // Not Find a mode from tOVERSCAN_DISPLAY_TABLE
        {
            g_ucOverScanH = ((BYTE)((DWORD)stModeInfo.IHWidth * _OVERSCAN_RATIO / 1000));
            g_ucOverScanV = ((BYTE)((DWORD)stModeInfo.IVHeight * _OVERSCAN_RATIO / 1000));
        }
    }

#if(_YPBPR_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        do
        {
            if(tOVERSCAN_YPBPR_DISPLAY_TABLE[cnt].ucModeIndex == ucModeIndex)
            {
                g_ucOverScanH = ((BYTE)((DWORD)stModeInfo.IHWidth * tOVERSCAN_YPBPR_DISPLAY_TABLE[cnt].usIHWidthRatio / 1000));
                g_ucOverScanV = ((BYTE)((DWORD)stModeInfo.IVHeight * tOVERSCAN_YPBPR_DISPLAY_TABLE[cnt].usIVHeightRatio / 1000));
                ucModeIndex = 0xFE; // UcModeIndex = 0xFE means a mode was found, as this variable was not initialized to 0xFE
                break;
            }

            cnt++;
        }
        while((tOVERSCAN_YPBPR_DISPLAY_TABLE[cnt].ucModeIndex != 0xFF) && (cnt < _MAX_YPBPR_MODE));

        if(ucModeIndex != 0xFE) // Not Find a mode from tOVERSCAN_YPBPR_DISPLAY_TABLE
        {
            g_ucOverScanH = ((BYTE)((DWORD)stModeInfo.IHWidth * _OVERSCAN_RATIO / 1000));
            g_ucOverScanV = ((BYTE)((DWORD)stModeInfo.IVHeight * _OVERSCAN_RATIO / 1000));
        }
    }
#endif

    if((g_ucOverScanH % 4) != 0)
    {
        g_ucOverScanH = ((g_ucOverScanH + 2) >> 2) << 2;
    }

    if((g_ucOverScanV % 4) != 0)
    {
        g_ucOverScanV = ((g_ucOverScanV + 2) >> 2) << 2;
    }

    // OverScanV is bigger than max value
    if(g_ucOverScanV > pData[15])
    {
        g_ucOverScanV = pData[15];
    }

    if((g_ucOverScanH == 0) || (g_ucOverScanV == 0))
    {
        g_ucOverScanH = 0;
        g_ucOverScanV = 0;
    }
}


// V016 System Patch Note (25) Modify 20100831 Start
// Patch Reason : Modify Overscan Effect Condition.
/*
//--------------------------------------------------
// Description  : Check Mode Number for using Overscan
// Input Value  : None
// Output Value : return _TRUE if video mode
//--------------------------------------------------
bit CModeOverScanTimingSelect()
{
    BYTE ucMode = 0;

#if(_YPBPR_SUPPORT == _ON)
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        return _TRUE;
    }
#endif

    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        ucMode = stModeInfo.ModeCurr;
    }
    else
    {
        ucMode = g_ucUserModeCurr;
    }

    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        switch(ucMode)
        {
            // V013 VGA Patch Note (24) Modify 20100514 Start
            // Patch Reason : Mode search updates.
            /*
            case _MODE_720x480i_60Hz:
            case _MODE_720x576i_50Hz:
            * /
            case _MODE_1440x480i_60HZ:
            case _MODE_1440x576i_50Hz:
            // V013 VGA Patch Note (24) Modify 20100514 End

            case _MODE_1920x1080i_50Hz:
            case _MODE_1920x1080i_60HZ:
                return _TRUE;
                break;

            case _MODE_640x480_60HZ:
            case _MODE_720x480p_60HZ:
            case _MODE_720x576p_50Hz:
            case _MODE_1280x720p_50HZ:
            case _MODE_1280x720p_60HZ:
            case _MODE_1920x1080p_50Hz:
            case _MODE_1920x1080p_60HZ:

#if(_COLOR_FORMAT_CONVERT == _ON)
                if(GET_COLOR_FORMAT_STATUS() != _YUV_COLOR_FORMAT)
                {
                    return _FALSE;
                }
#endif
                return _TRUE;
                break;

            default:
                return _FALSE;
                break;
        }
    }   // End of if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)

#if(_TMDS_SUPPORT == _ON)
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_DVI)

#if(_HDMI_SUPPORT == _ON)
    || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
#endif

#if(_DP_SUPPORT == _ON)
    || (GET_INPUTSOURCE_TYPE() == _SOURCE_DP)
#endif
    )
    {
        switch(ucMode)
        {
            // V013 VGA Patch Note (24) Modify 20100514 Start
            // Patch Reason : Mode search updates.
            /*
            case _MODE_720x480i_60Hz:
            case _MODE_720x576i_50Hz:
            * /
            case _MODE_1440x480i_60HZ:
            case _MODE_1440x576i_50Hz:
            // V013 VGA Patch Note (24) Modify 20100514 End

            case _MODE_1920x1080i_50Hz:
            case _MODE_1920x1080i_60HZ:
            case _MODE_640x480_60HZ:
            case _MODE_1280x720p_60HZ:
            case _MODE_720x480p_60HZ:
            case _MODE_720x576p_50Hz:
            case _MODE_1280x720p_50HZ:
            case _MODE_1280x720_60HZ_2:
            case _MODE_1920x1080p_50Hz:
            case _MODE_1920x1080p_60HZ:
                return _TRUE;
                break;

            default:
                return _FALSE;
                break;
        }
    }
#endif

    return _FALSE;
}
*/
//--------------------------------------------------
// Description  : Check Whether Overscan
// Input Value  : None
// Output Value : return _TRUE if Overscan
//--------------------------------------------------
bit CModeOverScanConditionSwitch(void)
{
    BYTE ucMode = 0;

#if(_OVERSCAN_VGA_SUPPORT == _ON)
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
        {
            ucMode = stModeInfo.ModeCurr;
        }
        else
        {
            ucMode = g_ucUserModeCurr;
        }

        switch(ucMode)
        {
            case _MODE_720x480_60HZ:
            case _MODE_720x480_60HZ_GTF:
            case _MODE_720x576_60HZ:
            case _MODE_1920x1080_60HZ_XBOX:
            case _MODE_1920x1080_60HZ_RB:
            case _MODE_1920x1080_60HZ:
            case _MODE_1920x1080_50HZ_2:
            case _MODE_1280x720_60HZ_2:
            case _MODE_720x480p_60HZ:
            case _MODE_720x576p_50Hz:
            case _MODE_1280x720p_50HZ:
            case _MODE_1280x720p_60HZ:
            case _MODE_1920x1080p_50Hz:
            case _MODE_1920x1080p_60HZ:

#if(_COLOR_FORMAT_CONVERT == _ON)
                if(GET_COLOR_FORMAT_STATUS() != _YUV_COLOR_FORMAT)
                {
                    return _FALSE;
                }
#endif

                return _TRUE;
                break;

            default:
                break;
        }

        return _TRUE;
    }   // End of if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
#endif

#if((_YPBPR_SUPPORT == _ON) && (_OVERSCAN_YPBPR_SUPPORT == _ON))
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        switch(stModeInfo.ModeCurr)
        {
            case _VIDEO_720x576p_50HZ:
            case _VIDEO_720x480p_60HZ:
            case _VIDEO_1280x720p_50HZ:
            case _VIDEO_1280x720p_60HZ:
            case _VIDEO_1920x1080p_50HZ:
            case _VIDEO_1920x1080p_60HZ:

#if(_COLOR_FORMAT_CONVERT == _ON)
                if(GET_COLOR_FORMAT_STATUS() != _YUV_COLOR_FORMAT)
                {
                    return _FALSE;
                }
#endif

                return _TRUE;
                break;

            default:
                break;
        }

        return _TRUE;
    }
#endif

    return _TRUE;
}
// V016 System Patch Note (25) Modify 20100831 End

//--------------------------------------------------
// Description  : Overscan Source Select
// Input Value  : None
// Output Value : TRUE/FALSE
//--------------------------------------------------
bit CModeOverScanSourceSelect(void)
{
// V016 System Patch Note (25) Modify 20100831 Start
// Patch Reason : Modify Overscan Effect Condition.
/*
#if(_FRC_SUPPORT == _ON)
    if(GET_FRCSTATUS())
    {
        return _FALSE;
    }
#endif

    switch(GET_INPUTSOURCE_TYPE())
    {
#if(_OVERSCAN_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            if(CScalerGetBit(_SYNC_SELECT_47, _BIT4) == 0)
            {
                return _FALSE;
            }

            return _TRUE;
            break;
#endif

#if(_TMDS_SUPPORT == _ON)

#if(_OVERSCAN_DVI_SUPPORT == _ON)
        case _SOURCE_DVI:
            return _TRUE;
            break;
#endif

#if((_HDMI_SUPPORT == _ON) && (_OVERSCAN_HDMI_SUPPORT == _ON))
        case _SOURCE_HDMI:
            return _TRUE;
            break;
#endif

#if((_DP_SUPPORT == _ON) && (_OVERSCAN_DP_SUPPORT == _ON))
        case _SOURCE_DP:
            return _TRUE;
            break;
#endif

#endif // End of #if(_TMDS_SUPPORT == _ON)

#if((_YPBPR_SUPPORT == _ON) && (_OVERSCAN_YPBPR_SUPPORT == _ON))
        case _SOURCE_YPBPR:

            if(CScalerGetBit(_SYNC_SELECT_47, _BIT4) == 0)
            {
                return _FALSE;
            }

            return _TRUE;
            break;
#endif

        default:
            break;
    }

    return _FALSE;
*/
    BYTE ucMode = 0;

#if(_FRC_SUPPORT == _ON)
    if(GET_FRCSTATUS() == _TRUE)
    {
        return _FALSE;
    }
#endif

#if(_OVERSCAN_VGA_SUPPORT == _ON)
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
        {
            ucMode = stModeInfo.ModeCurr;
        }
        else
        {
            ucMode = g_ucUserModeCurr;
        }

        switch(ucMode)
        {
            case _MODE_1920x1080i_50Hz:
            case _MODE_1920x1080i_60HZ:
            case _MODE_1440x480i_60HZ:
            case _MODE_1440x576i_50Hz:
            case _MODE_1920x1080i_50HZ_2:
                return _TRUE;
                break;

            case _MODE_720x480_60HZ:
            case _MODE_720x480_60HZ_GTF:
            case _MODE_720x576_60HZ:
            case _MODE_1920x1080_60HZ_XBOX:
            case _MODE_1920x1080_60HZ_RB:
            case _MODE_1920x1080_60HZ:
            case _MODE_1920x1080_50HZ_2:
            case _MODE_1280x720_60HZ_2:
            case _MODE_720x480p_60HZ:
            case _MODE_720x576p_50Hz:
            case _MODE_1280x720p_50HZ:
            case _MODE_1280x720p_60HZ:
            case _MODE_1920x1080p_50Hz:
            case _MODE_1920x1080p_60HZ:

                if(CScalerGetBit(_SYNC_SELECT_47, _BIT4) == 0)
                {
                    return _FALSE;
                }

                return _TRUE;
                break;

            default:
                break;
        }

        return _FALSE;
    }
#endif

#if((_YPBPR_SUPPORT == _ON) && (_OVERSCAN_YPBPR_SUPPORT == _ON))
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        switch(stModeInfo.ModeCurr)
        {
            case _VIDEO_1440x576i_50HZ:
            case _VIDEO_1440x480i_60HZ:
            case _VIDEO_1920x1080i_50HZ:
            case _VIDEO_1920x1080i_60HZ:
            case _VIDEO_1920x1080i_50HZ_2:
                return _TRUE;
                break;

            case _VIDEO_720x576p_50HZ:
            case _VIDEO_720x480p_60HZ:
            case _VIDEO_1280x720p_50HZ:
            case _VIDEO_1280x720p_60HZ:
            case _VIDEO_1920x1080p_50HZ:
            case _VIDEO_1920x1080p_60HZ:

                if(CScalerGetBit(_SYNC_SELECT_47, _BIT4) == 0)
                {
                    return _FALSE;
                }

                return _TRUE;
                break;

            default:
                break;
        }

        return _FALSE;
    }
#endif

#if(((_OVERSCAN_HDMI_SUPPORT == _ON) || (_OVERSCAN_DP_SUPPORT == _ON) || (_OVERSCAN_DVI_SUPPORT == _ON)) && (_TMDS_SUPPORT == _ON))

    switch(GET_INPUTSOURCE_TYPE())
    {
#if(_OVERSCAN_DVI_SUPPORT == _ON)
        case _SOURCE_DVI:
#endif

#if((_HDMI_SUPPORT == _ON) && (_OVERSCAN_HDMI_SUPPORT == _ON))
        case _SOURCE_HDMI:
#endif

#if((_DP_SUPPORT == _ON) && (_OVERSCAN_DP_SUPPORT == _ON))
        case _SOURCE_DP:
#endif
            if(GET_INTERLACE_MODE() == _TRUE)
            {
                return _TRUE;
            }

#if(_OVERSCAN_DVI_SUPPORT == _ON)
            if(GET_INPUTSOURCE_TYPE() == _SOURCE_DVI)
            {
                return _FALSE;
            }
#endif

#if(((_HDMI_SUPPORT == _ON) && (_OVERSCAN_HDMI_SUPPORT == _ON)) || ((_DP_SUPPORT == _ON) && (_OVERSCAN_DP_SUPPORT == _ON)))
            ucMode = 0;

            while(tOverscanDigitalEnTable[ucMode][0] != 0)
            {
                if((abs(g_usOldIHWidth - tOverscanDigitalEnTable[ucMode][0]) <= 2) &&
                   (g_usOldIVHeight == tOverscanDigitalEnTable[ucMode][1]) &&
                   (abs(stModeInfo.IVFreq - tOverscanDigitalEnTable[ucMode][2]) <= _VFREQ_TOLERANCE))
                {
                    break;
                }

                ucMode++;
            }

            if(tOverscanDigitalEnTable[ucMode][0] == 0)
            {
                return _FALSE;
            }
#endif

#if((_HDMI_SUPPORT == _ON) && (_OVERSCAN_HDMI_SUPPORT == _ON))
            if(GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
            {
                CScalerPageSelect(_PAGE2);
                CScalerSetBit(_P2_HDMI_APC_C8, ~_BIT0, _BIT0);
                CScalerGetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_ACRCR_51, 1, pData, _NON_AUTOINC);

                if(((pData[0] & (_BIT5 | _BIT4)) == _BIT4) || ((pData[0] & (_BIT5 | _BIT4)) == _BIT5)) // YUV Format
                {
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }
            else
#endif

#if((_DP_SUPPORT == _ON) && (_OVERSCAN_DP_SUPPORT == _ON))
            if(GET_INPUTSOURCE_TYPE() == _SOURCE_DP)
            {
                CScalerPageSelect(_PAGEC);
                CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x02, 1, pData, _NON_AUTOINC);

                if(((pData[0] & (_BIT2 | _BIT1)) == _BIT1) || ((pData[0] & (_BIT2 | _BIT1)) == _BIT2)) // YUV Format
                {
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }
            else
#endif
            {
                return _FALSE;
            }

            return _FALSE;
            break;

        default:
            break;
    }
#endif

    return _FALSE;
// V016 System Patch Note (25) Modify 20100831 End
}

//--------------------------------------------------
// Description  : Set Capture Start for Overscan
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeOverScanSetCaptureStart(void)
{
    if(GET_OVERSCAN_SUCCESS_STATUS() == _FALSE)
    {
        return;
    }

    CAdjustDisableWatchDog(_WD_ALL);

#if(_YPBPR_SUPPORT == _ON)
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
#else
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
#endif
    {
#if(_SCALER_TYPE == _RTD2472D)

        // Set H/V Capture Start
        CScalerSetBit(_IPH_ACT_STA_H_14, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(g_usCaptureStartH + g_ucOverScanH) & (_BIT2 | _BIT1 | _BIT0));
        CScalerSetByte(_IPH_ACT_STA_L_15, LOBYTE(g_usCaptureStartH + g_ucOverScanH));
        CScalerSetBit(_IPV_ACT_STA_H_18, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(g_usCaptureStartV + g_ucOverScanV) & (_BIT2 | _BIT1 | _BIT0));

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

        // Set H/V Capture Start
        CScalerSetBit(_IPH_ACT_STA_H_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(g_usCaptureStartH + g_ucOverScanH) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        CScalerSetByte(_IPH_ACT_STA_L_15, LOBYTE(g_usCaptureStartH + g_ucOverScanH));
        CScalerSetBit(_IPV_ACT_STA_H_18, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(g_usCaptureStartV + g_ucOverScanV) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

#endif

        CScalerSetByte(_IPV_ACT_STA_L_19, LOBYTE(g_usCaptureStartV + g_ucOverScanV));
        CScalerSetByte(_IVS2DVS_DELAY_LINES_40, (g_ucIv2DvModify + g_ucOverScanV));
    }

#if(_TMDS_SUPPORT == _ON)

    else if((GET_INPUTSOURCE_TYPE() == _SOURCE_DVI)
#if(_HDMI_SUPPORT == _ON)
    || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
#endif

#if(_DP_SUPPORT == _ON)
    || (GET_INPUTSOURCE_TYPE() == _SOURCE_DP)
#endif
    )
    {
        CScalerSetBit(_VGIP_CTRL_10, ~_BIT1, _BIT1);

#if(_SCALER_TYPE == _RTD2472D)
        CScalerSetBit(_IPH_ACT_STA_H_14, 0xf8, 0x00);
        CScalerSetByte(_IPH_ACT_STA_L_15, g_ucOverScanH);
        CScalerSetByte(_IPV_ACT_STA_H_18, 0x00);

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        CScalerSetBit(_IPH_ACT_STA_H_14, 0xf0, 0x00); // Input Video Horizontal Active Start[11:8]=4'b0000
        CScalerSetByte(_IPH_ACT_STA_L_15, g_ucOverScanH);
        CScalerSetBit(_IPV_ACT_STA_H_18, 0xf0, 0x00); // Input Video Vertical Active Start[11:8]=4'b0000

#else
        No Setting !!

#endif // End of #if(_SCALER_TYPE == _RTD2472D)

        CScalerSetByte(_IPV_ACT_STA_L_19, g_ucOverScanV);
        CScalerSetByte(_IVS2DVS_DELAY_LINES_40, (g_ucIv2DvModify + g_ucOverScanV));
    }
#endif

    CMiscApplyDoubleBuffer();
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CTimerWaitForEvent(_EVENT_DEN_START);

    // Waiting for clearing the Status Register
    for(pData[15] = 0; pData[15] < 5; pData[15]++)
    {
        CMiscClearStatusRegister();

        CTimerWaitForEvent(_EVENT_DVS);                         // Wait for Frame End
        CTimerWaitForEvent(_EVENT_DVS);                         // Wait for Frame End

        CScalerRead(_STATUS0_02, 1, &pData[1], _NON_AUTOINC);
        CScalerRead(_STATUS1_03, 1, &pData[2], _NON_AUTOINC);

        if(((pData[1] & 0x03) == 0x00) && (pData[2] == 0x3F))
        {
            break;
        }
    }

    if((pData[1] & 0x03) != 0x00)
    {
        CFrameSyncDo();

        CMiscClearStatusRegister();
        CTimerWaitForEvent(_EVENT_DVS);
        CTimerWaitForEvent(_EVENT_DVS);
    }

    CAdjustEnableWatchDog(_WD_ALL);
}

//--------------------------------------------------
// Description  : Check Capture Window Setting
// Input Value  : None
// Output Value : return _TRUE means it should be do Overscan
//--------------------------------------------------
bit CModeOverScanCheckCaptureWindow(void)
{
#if(_SCALER_TYPE == _RTD2472D)

    CScalerRead(_IPH_ACT_WID_H_16, 2, pData, _AUTOINC);
    ((WORD *)pData)[1] = (((WORD)(pData[0] & 0x07) << 8) | pData[1]);

    if(stModeInfo.IHWidth == ((WORD *)pData)[1])
    {
        return _FALSE;
    }

    CScalerRead(_IPV_ACT_LEN_H_1A, 2, pData, _AUTOINC);
    ((WORD *)pData)[1] = (((WORD)(pData[0] & 0x07) << 8) | pData[1]);

    if(stModeInfo.IVHeight == ((WORD *)pData)[1])
    {
        return _FALSE;
    }

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

    CScalerRead(_IPH_ACT_STA_H_14, 1, pData, _AUTOINC);
    CScalerRead(_IPH_ACT_WID_L_17, 1, &pData[1], _AUTOINC);
    ((WORD *)pData)[1] = (((WORD)(pData[0] & 0xf0) << 4) | pData[1]);

    if(stModeInfo.IHWidth == ((WORD *)pData)[1])
    {
        return _FALSE;
    }

    CScalerRead(_IPV_ACT_STA_H_18, 1, pData, _AUTOINC);
    CScalerRead(_IPV_ACT_LEN_L_1B, 1, &pData[1], _AUTOINC);
    ((WORD *)pData)[1] = (((WORD)(pData[0] & 0xf0) << 4) | pData[1]);

    if(stModeInfo.IVHeight == ((WORD *)pData)[1])
    {
        return _FALSE;
    }

#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Overscan Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeOverScan(void)
{
    CModeOverScanSelect();

    if(GET_OVERSCAN_STATUS() == _FALSE)
    {
        return;
    }

    // V013 System Patch Note (12) Modify 20100412 Start
    // Patch Reason : Overscan function updates.
    LIGHTPOWER_DOWN();
    // V013 System Patch Note (12) Modify 20100412 End

    CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, _BIT5);

    CAdjustDisableWatchDog(_WD_ALL);
    CMiscDisableDoubleBuffer();

    CModeSetupDisplay();
    CModeOverscanFrameSyncFineTune();
    CModeOverScanAdjustPos();

    // V013 System Patch Note (12) Modify 20100412 Start
    // Patch Reason : Overscan function updates.
    /*
    CAdjustHPosition();
    CAdjustVPosition();
    */
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
    {
        CAdjustHPosition();
        CAdjustVPosition();
    }
    // V013 System Patch Note (12) Modify 20100412 End

    CMiscEnableDoubleBuffer();
    CAdjustEnableWatchDog(_WD_ALL);

#if((_ASPECT_RATIO_SUPPORT == _ON) && (_MEMORY_WORK_TYPE == _OD_OFF_FRC_OFF))
    if(GET_READYFORDISPLAY() == _FALSE)
    {
        CModeSetDHWidthToDisplay();
        CTimerDelayXms(100);
    }
#endif

    CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00);

    // V013 System Patch Note (12) Modify 20100412 Start
    // Patch Reason : Overscan function updates.
    LIGHTPOWER_UP();
    // V013 System Patch Note (12) Modify 20100412 End
}

//--------------------------------------------------
// Description  : CFrameSyncFineTune
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeOverscanFrameSyncFineTune(void)
{
#if(_YPBPR_SUPPORT == _ON)
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        switch(stModeInfo.ModeCurr)
        {
            // V013 VGA Patch Note (5) 20100409 Modify Start
            // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
            /*
            case _VIDEO_720x576i_50HZ:  //576i
            case _VIDEO_720x480i_60HZ:  //480i
            */
            case _VIDEO_1440x576i_50HZ:
            case _VIDEO_1440x480i_60HZ:
            // V013 VGA Patch Note (5) 20100409 Modify End

            case _VIDEO_1920x1080i_50HZ: //1080i 50Hz
            case _VIDEO_1920x1080i_60HZ: //1080i 60Hz
                CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, _BIT7);
                CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT0, _BIT0);
                CFrameSyncFineTune(_ODD);
                break;
        }

        return;
    }
#endif

#if(_VIDEO_SUPPORT == _ON)
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VIDEO8)
    {
        CFrameSyncFineTune(_ODD);
        return;
    }
#endif

#if(_TMDS_SUPPORT == _ON)
        if((GET_INPUTSOURCE_TYPE() == _SOURCE_DVI)

#if(_HDMI_SUPPORT == _ON)
          || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
#endif

#if(_DP_SUPPORT == _ON)
          || (GET_INPUTSOURCE_TYPE() == _SOURCE_DP)
#endif
        )
        {
            if(GET_INTERLACE_MODE() == _TRUE)
            {
                CFrameSyncFineTune(_EVEN);
            }
        }
#endif
}
#endif  // End of #if(_OVERSCAN_SUPPORT == _ON)
// V012 Modify 20100316 End

// V012 Modify 20100321 Start
// V012 Patch Note (14) : Fix the issue that SOG interlace signal could not light up the display when  V sync pulse is only 1H.
//--------------------------------------------------
// Description  : Check DVTotal Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeCheckDVTotal(void)
{
    WORD usDVTotal = 0;
    WORD usDVideal = 0;

    // Read DVTotal
    CScalerSetBit(_LAST_LINE_H_44, ~_BIT7, _BIT7);
    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    pData[0] &= 0x0F;
    usDVTotal = ((WORD *)pData)[0];

    // V015 System Patch Note (5) Modify 20100629 Start
    // Patch Reason : Replace calculating DVTotal by reading DVTotal setting from register.
    // Read DVTotal Limit
    /*
    // Read DVTotal Limit
    ((WORD *)pData)[2] = ((DWORD)stModeInfo.IVTotal * stDisplayInfo.DVHeight) / stModeInfo.IVHeight + 64;
    */
    // Read DVTotal Limit
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DV_TOTAL_H_0B);
    CScalerRead(_DISP_DATA_PORT_2B, 2, &pData[4], _NON_AUTOINC);
    // V015 System Patch Note (5) Modify 20100629 End

    if(usDVTotal > ((WORD *)pData)[2])
    {
        // Ideal DVTotal
        usDVideal = ((WORD *)pData)[2] - 64;

        // Current DVTotal > (Ideal DVTotal * 2)
        if((((DWORD)usDVTotal * 1000) / usDVideal) > 1900)
        {
            // Get Stable Period
            CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
            pData[0] &= 0x07;

            // Disable Hsync Type Detection Auto Run
            CScalerSetBit(_SYNC_SELECT_47, ~(_BIT6 | _BIT5), 0x00);

            // Set Vsync Counter Level = (Stable Period / 4)
            CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~(_BIT2 | _BIT1 | _BIT0), (BYTE)(((WORD *)pData)[0] >> 10) & 0x07);
            CScalerSetByte(_VSYNC_COUNTER_LEVEL_LSB_4D, (BYTE)(((WORD *)pData)[0] >> 2));

            // Enable Hsync Type Detection Auto Run
            CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);

            // V012 Modify 20100329 Start
            // V012 Patch Note (19) : Adjust polling time of Auto Run Typer according to different Crystal frequency.
            /*
            // Wait for Auto Run Finish
            CTimerPollingEventProc(180, CMiscHsyncTypeAutoRunFlagPollingEvent);
            */
            // Wait for Auto Run Finish
            CTimerPollingFlagProc(_SP_AUTORUN_TIME_OUT, _PAGE_COMMON, _VSYNC_COUNTER_LEVEL_MSB_4C, _BIT7, _TRUE);
            // V012 Modify 20100329 End

            // Delay 2 frame for System Stable
            CTimerWaitForEvent(_EVENT_IVS);
            CTimerWaitForEvent(_EVENT_IVS);
            CTimerWaitForEvent(_EVENT_IVS);
        }
    }

    CScalerSetBit(_LAST_LINE_H_44, ~_BIT7, 0x00);
}
// V012 Modify 20100321 End

// V013 VGA Patch Note (23) Modify 20100513 Start
// Patch Reason : For Video Mode Clamp Position Setting Flow
//--------------------------------------------------
// Description  : Check Current Mode Is Video Mode
// Input Value  : None
// Output Value : Return _TRUE If Yes, _FALSE if No
//--------------------------------------------------
bit CModeCheckVideoMode(void)
{
    // V014 VGA Patch Note (6) Modify 20100527 Start
    // Patch Reason : Modify Video Mode Can't Light On
    /*
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    */
    if((GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE) && (GET_INPUTSOURCE_TYPE() == _SOURCE_VGA))
    // V014 VGA Patch Note (6) Modify 20100527 End
    {
        if(tINPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].PolarityFlag & (_VIDEO_MODE_GROUP1 | _VIDEO_MODE_GROUP2))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
// V013 VGA Patch Note (23) Modify 20100513 End

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
//--------------------------------------------------
// Description  : Recheck Clamp Position Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeConfirmClampPositionSetting(void)
{
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        switch(tINPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].PolarityFlag &  (_VIDEO_MODE_GROUP1 | _VIDEO_MODE_GROUP2))
        {
            case _VIDEO_MODE_GROUP1:
                pData[0] = 0x08;
                pData[1] = 0x16;
                pData[2] = 0x08;
                pData[3] = 0x16;

                break;

            case _VIDEO_MODE_GROUP2:
                pData[0] = 0x20;
                pData[1] = 0x38;
                pData[2] = 0x20;
                pData[3] = 0x38;

                break;

            default:
                pData[0] = 0x04;
                pData[1] = 0x10;
                pData[2] = 0x04;
                pData[3] = 0x10;

                break;
        }

    }
    else // User Mode Need Set Default Clamp Position.
    {
        pData[0] = 0x04;
        pData[1] = 0x10;
        pData[2] = 0x04;
        pData[3] = 0x10;
    }

    // Setting clamp position.
    CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C, 0x00);
    CScalerWrite(_SYNC_PROC_DATA_PORT_5D, 4, &pData[0], _NON_AUTOINC);
}
// V014 VGA Patch Note (6) Modify 20100527 End
#endif  // End of #if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

