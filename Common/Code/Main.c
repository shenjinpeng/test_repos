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
// ID Code      : Main.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


#define __MAIN__

#include "Common\Header\Include.h"

//--------------------------------------------------
// Main Process
//--------------------------------------------------

void LSIintial(void)
{

pData[0]=0x03;		
CI2cWrite(LS_LINE, 0x92, 0x00, 1, pData);
pData[0]=0;

CI2cRead(LS_LINE, 0x92, 0x00, 1, pData);

#if  _DEBUG_MESSAGE_SUPPORT

CDebugMessage("pdata[0]_0", pData[0]);
#endif
pData[0]=0;

}

void LSHandler(void)
{
	WORD Lumdelta=0;
	BYTE i,j;
	WORD tBKLIT_DICOMlumi[11];//LSLUMITABLE SJP20110625
	tBKLIT_DICOMlumi[0] = stLSlumiData.DICOM350;
	tBKLIT_DICOMlumi[1]=	stLSlumiData.DICOM400;
	tBKLIT_DICOMlumi[2]=	stLSlumiData.DICOM450;
	tBKLIT_DICOMlumi[3]=stLSlumiData.DICOM500;
	tBKLIT_DICOMlumi[4]=stLSlumiData.DICOM550;
	tBKLIT_DICOMlumi[5]=stLSlumiData.DICOM600;
	tBKLIT_DICOMlumi[6]=stLSlumiData.DICOM650;
	tBKLIT_DICOMlumi[7]=	stLSlumiData.DICOM700;
	tBKLIT_DICOMlumi[8]=stLSlumiData.DICOM500;
	tBKLIT_DICOMlumi[9]=stLSlumiData.DICOM500;
	tBKLIT_DICOMlumi[10]=stLSlumiData.DICOM500;
	
	CI2cRead(LS_LINE, 0x92, 0x0C, 1, pData);
	TempLumValue=pData[0];
	pData[1]=pData[0];
	pData[0]=0;
	CI2cRead(LS_LINE, 0x92, 0x0D, 1, pData);
	TempLumValue=pData[0]<<8|TempLumValue;
	
	
#if  _DEBUG_MESSAGE_SUPPORT
					   
//								   CDebugMessage("_time_pdata[0]", pData[0]);
//								   CDebugMessage("pData[0]",pData[0]);
#endif
	
	pData[0]=0;
	pData[1]=0;
	
#if  _DEBUG_MESSAGE_SUPPORT
		 CDebugMessage("TempLumValue", TempLumValue);
		 CDebugMessage("stSystemData.BackLight_original", stSystemData.BackLight);
		 CDebugMessage("tBKLIT_DICOMlumi[stConBriData.Dicom]",tBKLIT_DICOMlumi[stConBriData.Dicom]);								 
#endif
if(bData<20)
{
if(TempLumValue<100)
	{	
			bData++;
			if(bData==10)
		{	
			CModeResetMode();
		}
		
	}
}
if(TempLumValue>100)
{
	if(TempLumValue<tBKLIT_DICOMlumi[stConBriData.Dicom])

	       {
			Lumdelta=tBKLIT_DICOMlumi[stConBriData.Dicom]-TempLumValue;
#if  _DEBUG_MESSAGE_SUPPORT
					 
//			CDebugMessage("LumdeltaLumdelta<", Lumdelta);								 
#endif
			if(Lumdelta>1)//sjp20110804
				{
					if(stSystemData.BackLight>0x02)
						{
						if(Lumdelta>500&&stSystemData.BackLight>60)
							{
							stSystemData.BackLight=stSystemData.BackLight-40;
							COsdLeftSubBrightness();
							}
						else if(Lumdelta>200&&stSystemData.BackLight>32)
							{
							stSystemData.BackLight=stSystemData.BackLight-30;
							COsdLeftSubBrightness();
							}
						
						else if(Lumdelta>100&&stSystemData.BackLight>16)
							{
							stSystemData.BackLight=stSystemData.BackLight-8;
							COsdLeftSubBrightness();
							}
							
						else if(Lumdelta>50&&stSystemData.BackLight>10)
							{
							stSystemData.BackLight=stSystemData.BackLight-3;
							COsdRightSubBrightness();
							if(ucCurrState==_ACTIVE_STATE)
								   for(j=0;j<30;j++)
									{
													
									for(i=0;i<20;i++)	
										{
											Delay5us(); 							
											Delay5us(); 							
											Delay5us(); 							
											Delay5us();
											Delay5us();
											Delay5us();
											Delay5us(); 							
											
										}
									}



							
							}
							
						else 
							{
							stSystemData.BackLight=stSystemData.BackLight-1;
							COsdRightSubBrightness();
							if(ucCurrState==_ACTIVE_STATE)
								   for(j=0;j<50;j++)
									{
													
									for(i=0;i<20;i++)	
										{
											Delay5us(); 							
											Delay5us(); 							
											Delay5us(); 							
											Delay5us();
											Delay5us();
										}
									}

							
							}
#if  _DEBUG_MESSAGE_SUPPORT
//			 
//						 CDebugMessage("stSystemData.BackLight", stSystemData.BackLight);														 
#endif
                                                
						COsdRightSubBrightness();
						if(ucCurrState==_ACTIVE_STATE)
				                       for(j=0;j<20;j++)
				                       	{
												
								for(i=0;i<20;i++)	
									{
										Delay5us();								
										Delay5us();								
										Delay5us();								
										Delay5us();
										Delay5us();
										Delay5us();
										Delay5us(); 							
										
									}
				                       	}
				                       	

						}
					}
					
			/*	else if(Lumdelta<=1)//sjp20110812
					{
	                                          
						ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
					}	*/			
	}
	
	else 
	{

		Lumdelta=TempLumValue-tBKLIT_DICOMlumi[stConBriData.Dicom];
#if  _DEBUG_MESSAGE_SUPPORT
							 
//										 CDebugMessage("LumdeltaLumdelta>", Lumdelta);										 
#endif
		if(Lumdelta>1)//sjp20110812
			{
			/*if((stSystemData.BackLight==0)&&(TempLumValue<tBKLIT_DICOMlumi[7]))
				{
				;
				
				} 
				
		else
				{*/
			        if(stSystemData.BackLight<4093)
					{
						if(Lumdelta>400&&stSystemData.BackLight<4051)	
							{
							stSystemData.BackLight=stSystemData.BackLight+40;
							COsdLeftSubBrightness();
							}
						
						else if(Lumdelta>200&&stSystemData.BackLight<4051)
							{
							stSystemData.BackLight=stSystemData.BackLight+30;
							COsdLeftSubBrightness();
							}
						
						else if(Lumdelta>100&&stSystemData.BackLight<4075)
							{
							stSystemData.BackLight=stSystemData.BackLight+8;
							COsdLeftSubBrightness();
							}
                                                
						else if(Lumdelta>50&&stSystemData.BackLight<4085)
							{
							stSystemData.BackLight=stSystemData.BackLight+3;
						 	COsdLeftSubBrightness();

							if(ucCurrState==_ACTIVE_STATE)
							for(j=0;j<30;j++)
							{
									
								for(i=0;i<20;i++)	
								{
									Delay5us(); 							
									Delay5us(); 							
									Delay5us(); 							
									Delay5us();
									Delay5us(); 							
									Delay5us();
									Delay5us();
								}
							}

							}
						
						else 
							{
							stSystemData.BackLight=stSystemData.BackLight+1;
						 	COsdLeftSubBrightness();

							if(ucCurrState==_ACTIVE_STATE)
							for(j=0;j<50;j++)
							{
									
								for(i=0;i<20;i++)	
								{
									Delay5us(); 							
									Delay5us(); 							
									Delay5us(); 							
									Delay5us();
									Delay5us(); 							
									Delay5us();
									Delay5us();
								}
							}
							}



		//			COsdLeftSubBrightness();
					
					if(ucCurrState==_ACTIVE_STATE)
					for(j=0;j<20;j++)
					{
							
						for(i=0;i<20;i++)	
						{
							Delay5us(); 							
							Delay5us(); 							
							Delay5us(); 							
							Delay5us();
							Delay5us(); 	
							Delay5us();
							Delay5us(); 							
						}
					}

					}
				   
		        //}
		        }
	/*	else if(Lumdelta<=1)//sjp20110812
			{
				ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;
			}*/



	}
}

}



void main(void)
{
    do
    {
        CMainSystemInitial();
	 LSIintial();
	 
#if _DEBUG_MESSAGE_SUPPORT
//	 CDebugMessage("stSystemData.SearchIndex_main", stSystemData.SearchIndex);
#endif
#if _DEBUG_MESSAGE_SUPPORT
//		 CDebugMessage("stSystemData.SearchIndex_maindefault", stSystemData.SearchIndex);
#endif
#if _DEBUG_MESSAGE_SUPPORT
//		 CDebugMessage("stSystemData.SearchIndex_load", stSystemData.SearchIndex);
//		CDebugMessage("stSystemData.BackLight_load", stSystemData.BackLight);
#endif
#if _DEBUG_MESSAGE_SUPPORT
	 CDebugMessage("V4.1_2012 02 29", 0);

#endif


        while(CMainDetectSystemPower() && CMainResetCheck())
        {
        
            CMiscIspDebugProc();

            CTimerHandler();
            CKeyHandler();
	//MCU_WATCHDOG_TIMER_FFEA |= 0x40;
//	    CDebugMessage("ucTimer0Cnt2=", ucTimer0Cnt2);
		if(!bAgeModeOn)
			CModeHandler();
			
            COsdHandler();



#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

#if (_DP_PHYCTS_STEPBYSTEP == _ON)
            CDPPHYCTSSTEP();
#endif

#endif


#if(_DDCCI_SUPPORT == _ON)
            CDdcDDCCI_Command();
#endif

	   if((ucCurrState==_ACTIVE_STATE)&&(bTimer01minCtrl==_TRUE))	
	   	{
	   	#if _DEBUG_MESSAGE_SUPPORT
		//CDebugMessage("111111111111111",bData);
		#endif
		   LSHandler();
		//bTimer01minCtrl=_FALSE;
	   	}

        }
    }
    while(_TRUE);
}


//--------------------------------------------------
// Global Variable Initial
//--------------------------------------------------
void CMainGlobalVarInitial(void)
{
    //===============================//
    //      xData of Adjust.h        //
    //===============================//
    ucAdjustCtrl = 0;
    usPEValue = 120;
    g_bAutoPositionH = _FALSE;
    g_ulPllIHTotal = 0;
    g_ulPllDivider = 0;
    sAdjustHue = 0;
    sAdjustSat = 0;

    //===============================//
    //      xData of Uart.h          //
    //===============================//
#if(_DEBUG_TOOL == _RS232)
    bUartCommandStart = _FALSE;
    bUartCommandSuccess = _FALSE;
    bDebugModeEnable = _FALSE;
    ucUartCommandNum = 0;
    pUartData[0] = 0;
    pUartData[1] = 0;
    pUartData[2] = 0;
    pUartData[3] = 0;
    pUartData[4] = 0;
    pUartData[5] = 0;
    pUartData[6] = 0;
    pUartData[7] = 0;
    ucPageInfo = 0;
#endif

    //===============================//
    //      xData of Auto.h          //
    //===============================//
    g_usHStartPos = 0;
    g_usHEndPos = 0;
    g_usVStartPos = 0;
    g_usVEndPos = 0;
    g_ucAdcPGA = 0;

    //===============================//
    //      xData of Hdmi.h          //
    //===============================//
#if(_HDMI_SUPPORT == _ON)
    ucHdmiCtrl = 0;
    ucAudioRate = 0;

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
#if(_AUDIO_SUPPORT == _ON)
    g_usHDMILockedFreq = 0;
#endif
#endif

#endif

    //===============================//
    //      xData of Memory.h        //
    //===============================//
#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
    g_ucMemoryCtrl = 0;
#endif

    //===============================//
    //      xData of Sync.h          //
    //===============================//
    g_ucIDCode = 0;
    g_usTMDSFreq = 0;
    g_usTMDSFreq0 = 0;
    g_usTMDSFreq1 = 0;
    g_usDVITMDSFreq = 0;

    //===============================//
    //      xData of Mode.h          //
    //===============================//
    ucCurrState = _PWOFF_STATE;
    ucModeControl = 0;
    ucEvent0 = 255;
    ucEvent1 = 255;
    g_bCheckHDCP = _FALSE;
    ucModeFound = 0;
    g_usHStartBias = 0;
    g_ucVStartBias = 0;
    ucSourceControl = 0;
    g_ucTimerCnt = 0;

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
/*
#if(_HDMI_OVERSCAN == _ON)
    ucOverScanH  = 0;
    ucOverScanV  = 0;
#endif
*/
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
    g_ucIv2DvModify = 0;
#endif
// V012 Modify 20100316 End

    //===============================//
    //      xData of Power.h         //
    //===============================//
    ucPowerControl = 0;

    //===============================//
    //      xData of Source.h        //
    //===============================//
    g_ucInputInfo = 0;
    g_ucInputConnect = 0;
    g_ucSearchIndex = 0;
    g_ucSearchTimes = 0;
    g_ucSearchFinish = 0;
    g_ucModeStableCount = 0;

    //===============================//
    //      xData of Realtek_Key.h   //
    //===============================//
#if(_OSD_TYPE == _REALTEK_OSD)
    ucKeyControl = 0;
    ucKeyMessage = 0;
    ucKeyStatePrev = 0;
    ucKeyStateCurr = 0;
#endif

    //===============================//
    //      xData of Debug.h         //
    //===============================//
#if((_DEBUG_MESSAGE_SUPPORT == _ON) && ((_DEBUG_TOOL == _ISP_FOR_RTD2120) || (_DEBUG_TOOL == _ISP_FOR_EMBEDDED)))
    /*
    g_bDebugMessageEven = _FALSE;
    */
    g_bDebugMessageEven = _INITIAL_MESSAGE_ACK;
    g_bDebugMessageStart = _FALSE;
    pDebugMessageBUF[0] = 0;
    pDebugMessageBUF[1] = 0;
    pDebugMessageBUF[2] = 0;
    pDebugMessageBUF[3] = 0;
#endif

#if((_DEBUG_MESSAGE_SUPPORT == _ON) && ((_DEBUG_TOOL == _ISP_FOR_RTD2120)))
    TxTemp = 0;
    bDataOutEnd = _FALSE;
#endif

#if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
    g_usDebugCount = 0;
#endif

#if((_DEBUG_MESSAGE_SUPPORT == _ON) && ((_DEBUG_TOOL == _ISP_FOR_EMBEDDED)))
    g_bFwHalt = _FALSE;
    g_usFilterPro = 0;
#endif

    //===============================//
    //      xData of DisplayPort.h   //
    //===============================//
#if(_DP_SUPPORT == _ON)
    g_ucDisplayPortCtrl = 0;
    g_ucDisplayPortStatus = 0;
    g_ucDisplayPortLtPreStatus = 10;

    g_ucLane01Status = 0;
    g_ucLane23Status = 0;
    g_ucAdjustRequestL01 = 0;
    g_ucAdjustRequestL23 = 0;

    g_ucDpPowerStatus = 0;

    g_ucFifoFailCount = 0;
    g_ucPhyUnstableCount = 0;
    g_ucMisAlignCount = 0;
    g_ucChangeDisplayCount = 0;
    g_ucDpResetCount = 0;

    g_ulDpMvidValue = 0;
    g_usDpHactive = 0;
    g_usDpVactive = 0;
    g_ucDpMsaMisc = 0;
    g_ucDpRate = 0;
    g_ucDpLaneCount = 0;
    g_ucTP1Error = 0;
    g_ucTP1Decode = 0;
    g_ucTP1Decode1 = 0;
    g_ucTP1Decode2 = 0;
    g_ucCrcLane1 = 0;
    g_ucCrcLane2 = 0;
    g_ucTrainingLaneSet = 0;
    g_ucButInt = 0;
    g_ucAlignStatus = 0;

    g_ucRegPageBackUp = 0;
    g_ucRegIntBackUp = 0;
    g_ucRegAddrBackUp = 0;
    g_ucRegPortBackUp[0] = 0;
    g_ucRegPortBackUp[1] = 0;
    g_ucRegPortBackUp[2] = 0;
    g_ucRegPortBackUp[3] = 0;
#endif // End of #if(_DP_SUPPORT == _ON)

    //===============================//
    //      xData of DCR.h           //
    //===============================//
#if(_DCR_MODE == _DCR_TYPE_1)
    g_usHorBoundary = 0;
    g_usVerBoundary = 0;
    g_usRGBInfo = 0;
    g_ucPreBacklightPWM = 255;
    g_ucPreDCCLum = 0;
    g_ucDcrCtrl = 0;
    g_ucDCRPercent = 100;  // Max 100

#elif(_DCR_MODE == _DCR_TYPE_2)
    g_usHorBoundary = 0;
    g_usVerBoundary = 0;
    g_usRGBInfo = 0;
    g_ucPreBacklightPWM = 255;
    g_ucPreDCCLum = 0;
    g_ucDcrCtrl = 0;
    g_ucDCRPercent = 100;  // Max 100

#elif(_DCR_MODE == _DCR_TYPE_3)
    g_ucDcrTargetPre = 0;
    g_ucDcrTargetPre1 = 0;
    g_ucDcrTemp = 0;
    g_ucDcrPwm = 0;
    g_ucDcrCnt = 0;
    g_usDcrStep = 0;
    g_ucDcrTimer = 0;
    g_ucDcrCtrl = 0;
    g_ucDcrCurrentPWM = 0;

    g_ucDCRPercent = 100;
    g_usDCR5MinTimer = 0;

#endif //End of #if(_DCR_MODE == _DCR_TYPE_1)


    //===============================//
    //    xData of Realtek_Ddc.h     //
    //===============================//
#if(_DDCCI_SUPPORT == _ON)
    for(pData[0] = 0; pData[0] < _DDCCI_RXBUF_LENGTH; pData[0]++)
    {
        g_ucDdcciRxBuf[pData[0]] = 0;
    }

    for(pData[0] = 0; pData[0] < _DDCCI_TXBUF_LENGTH; pData[0]++)
    {
        g_ucDdcciTxBuf[pData[0]] = 0;
    }

    g_ucDdcciRedBlackLevel = 0x50;
    g_ucDdcciGreenBlackLevel = 0x50;
    g_ucDdcciBlueBlackLevel = 0x50;
    g_ucDdcciTxCount = 0;
    g_ucDdcciNewControlValue = 1;
    g_ucColorTempUnSupport = 0;
    g_RxStatus = _DDC2B_CLEAR;

    g_ucDdcciDP_Ready = 0;
    ucDdcciDP_Pending = 0;
    ucDdcciDP_PreVCP = 1;
    ucDdcciDP_Read = 0;
    ucDdcciDP_ReplyDone = 0;
    ucDdcciDP_ReSend = 0;
    ucDdcciDP_PreOP = 0;
    ucDdcciDP_OverRead = 0;
    g_ucActiveInputSourceType = 0;
#endif //End of #if(_DDCCI_SUPPORT == _ON)

    // V013 System Patch Note (3) 20100429 Modify Start
    // Patch Reason : Initial stModeInfo XDATA variables.

// V013 TMDS Patch Note (16) 20100422 Modify Start
// Patch Reason : Solve DVI Interlace Issue.
    stModeInfo.Polarity = 0;
    stModeInfo.IHCount = 0;
    stModeInfo.IHFreq = 0;
    stModeInfo.IVTotal = 0;
    stModeInfo.IVFreq = 0;
    stModeInfo.IHWidth = 0;
    stModeInfo.IVHeight = 0;
    stModeInfo.IHSyncPulseCount = 0;
    stModeInfo.IHStartPos = 0;
    stModeInfo.IVStartPos = 0;
    stModeInfo.IVSyncPulseCount = 0;
// V013 TMDS Patch Note (16) 20100422 Modify End

    stModeInfo.ModeCurr = _MODE_NOSIGNAL;

    stModeInfo.IHTotal = 0;
    // V013 System Patch Note (3) 20100429 Modify End

    // V012 Modify 20100402 Start
    // V012 Patch Note (29) : Fix the inaccurate Vfreq in OSD with SOG HORV/HEORV sync type.
    g_usCaptureStart = 0;
    g_usVTotalTemp = 0;
    g_ucVSyncPulseWidthTemp = 0;
    g_ucCoastLineCnt = 0;
    // V012 Modify 20100402 End

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
    g_bYuvRgbFlag = _FALSE;
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End
}

//--------------------------------------------------
// System Initial
//--------------------------------------------------
void CMainSystemInitial(void)
{
    // Initial MCU
    CMcuInitial();

    // Initial Xdata value
    CMainGlobalVarInitial();

    // Initial DDC/CI settings
#if((_DEBUG_TOOL == _ISP_FOR_RTD2120) || (_DEBUG_TOOL == _ISP_FOR_EMBEDDED) || (_DEBUG_TOOL == _RS232))
    CDdcciInitial();
#endif


#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    D0_HPD_LOW();
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    D1_HPD_LOW();
#endif

    // Initial I/O state
    CMainIOInitial();

    // Initial timer events
    CTimerInitialTimerEvent();

// Check Eeprom or Flash and load default settings
#if(_MEMORY_LOCATION == _FLASH)
    CFlashStartupCheck();
#else
    CEepromStartupCheck();
#endif

    // If system power detection is fail, we will be locked here.
    while(!CMainDetectSystemPower())
    {
        ;
    }

    // Initial source settings
    CSourceInitialSetting();

    // Initial scaler settings
    CScalerInitial();

    // Get ID Code
    CMainGetIDCode();


    // Initial key scan status
    CKeyInitial();

    // Initial user settings
    CMainUserInitial();

    // Initial video settings
#if(_VIDEO_SUPPORT == _ON)
    CVideoInitial();
#endif


    // Initial uart settings
#if(_DEBUG_TOOL == _RS232)
    CUartInitial();
#endif

#if(_DCR_MODE == _DCR_TYPE_3)
    CDcrInitial();
#endif

#if(_DDCCI_SUPPORT == _ON)
    CDebugInitial();
#endif
}

//--------------------------------------------------
// Description  : I/O Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMainIOInitial(void)
{
    CMiscSetPinShare();
    CPowerPanelPowerOff();
    CPowerLightPowerOff();

//#if(_PANEL_STYLE == _PANEL_RSDS)
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_RSDS_PWR_CTL_C3, 0x03);
//#endif

#if(((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122)) && (_WATCHDOG_TIMER == _ON) && (_SYSTEMPOWER_DETECT_SUPPORT == _ON))
    MCU_WATCHDOG_TIMER_FF36 = 0x87;
#endif

}

//--------------------------------------------------
// Description  : Get ID Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMainGetIDCode(void)
{
    BYTE i = 0, ucCount = 0;

    for(i = 0; i < 10; i++)
    {
        // Get ID Code
        CScalerRead(_ID_REG_00, 1, pData, _NON_AUTOINC);

        if(g_ucIDCode != pData[0])
        {
            g_ucIDCode = pData[0];
            ucCount = 0;
        }
        else
        {
            ucCount++;
        }

        if(ucCount == 2)
        {
            break;
        }
    }

    if(i >= 10)
    {
        g_ucIDCode = 0;
    }
}


//--------------------------------------------------
// Description  : User Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMainUserInitial(void)
{
#if((_SCALER_TYPE == _RTD2545LR) && ((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122)))
    CScalerPageSelect(_PAGE0);
    //ADC Clock/SOG0/S0G1/Bandgap Power Off
    CScalerSetBit(_P0_ADC_POWER_C6, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0);

    // Pin_share Setting, XOUT (P6.6) GPIO Pin
    if(GET_POWERSTATUS())
    {
        MCU_PIN_SHARE2_FF02 |= 0x10;
    }
    else
    {
        MCU_PIN_SHARE2_FF02 &= 0xEF;
    }

#endif

    COsdDispInitial();

    // User can make some initial settings at firmware startup
    CLR_PANELPOWERSTATUS();
    CLR_LIGHTPOWERSTATUS();
    CLR_FRAMESYNCSTATUS();
    CLR_POWERSWITCH();
    CLR_FIRST_ADCCLOCK();
    CLR_KEYREPEATENABLE();

#if(_HDMI_SUPPORT == _ON)
    CLR_HDMIINPUT();

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
    // reserved
#else
    CLR_AUDIOPLLLOCKREADY();
    CLR_AVRESUME();
    CLR_AUDIOWAITINGTIMEOUT();
#endif

#endif

    SET_FIRST_LOADFONT();
    CLR_INTERLACE_MODE();

#if(_FRC_SUPPORT == _ON)
    CLR_FRCSTATUS();
    CLR_FRC422STATUS();
#if(_FIELD_MERGE_SUPPORT == _ON)
    CLR_FIELDMERGE_MODE();
#endif
#endif // End of #if(_FRC_SUPPORT == _ON)

    CLR_USE_TRANSITION_RESULT();
    ucCurrState = _PWOFF_STATE;
}

//--------------------------------------------------
// Description  : System Power Detect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit CMainDetectSystemPower(void)
{
    bit flag = 1;

#if(_SYSTEMPOWER_DETECT_SUPPORT == _ON)

    // It's an example F/W for RTD2120.
    MCU_ADC_CTRL_FF0B = 0x80;
    while((MCU_ADC_CTRL_FF0B & _BIT7) != 0x00)
    {

#if(((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122)) && (_WATCHDOG_TIMER == _ON))
        CTimerDelayXms(20);
        MCU_WATCHDOG_TIMER_FF36 = MCU_WATCHDOG_TIMER_FF36 | 0x40;
#endif
    }

    if((bSYSTEMPOWERDETECT & 0x01) == 0x01)
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

#endif // End of #if(_SYSTEMPOWER_DETECT_SUPPORT == _ON)


#if(((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122)) && (_WATCHDOG_TIMER == _ON) && (_SYSTEMPOWER_DETECT_SUPPORT == _ON))

    if(flag)
    {
        MCU_WATCHDOG_TIMER_FF36 = 0x00;
        return _TRUE;

    }
    else
    {
        CTimerDelayXms(20);
        MCU_WATCHDOG_TIMER_FF36 = MCU_WATCHDOG_TIMER_FF36 | 0x40;
        return _FALSE;
    }

#else

    if(flag)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }

#endif  // End of #if(((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122)) && (_WATCHDOG_TIMER == _ON) && (_SYSTEMPOWER_DETECT_SUPPORT == _ON))

}

//--------------------------------------------------
// Description  : Reset Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit CMainResetCheck(void)
{
#if(_RESET_CHECK_SUPPORT == _ON)

    while(!GETSCALERSDIO3())
    {
        if(bSCALERSCLK)
        {
            CLRSCALERSCLK();
        }
        else
        {
            SETSCALERSCLK();
        }
    }

    CScalerRead(_ID_REG_00, 1, pData, _NON_AUTOINC);

#if(_SCALER_TYPE == _RTD2545LR)
    if((pData[0] != 0x51) || (!((bit)CScalerGetBit(_HOST_CTRL_01, _BIT6))))

#elif(_SCALER_TYPE == _RTD2472D)
    if((pData[0] != 0x01) || (!((bit)CScalerGetBit(_HOST_CTRL_01, _BIT6))))

#elif((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    if((pData[0] != 0x08) || (!((bit)CScalerGetBit(_HOST_CTRL_01, _BIT6))))

#else
     No Setting !!

#endif
        return _FALSE;

#endif  // End of #if(_RESET_CHECK_SUPPORT == _ON)

    return _TRUE;
}


#if(_DDCCI_SUPPORT == _ON)
//--------------------------------------------------
// Debug initial Process
//--------------------------------------------------
void CDebugInitial(void)
{
#if(_DEBUG_TOOL == _ISP_FOR_RTD2120)
                if(GET_DDCCI_STATUS())
                {
                    MCU_I2C_SET_SLAVE_FF27 = 0x6e;
                }
                else
                {
#if(_DDC_CHANNEL_SEL == _VGA_DDC_CHANNEL)
                    MCU_I2C_SET_SLAVE_FF27 = 0x6a;
#else
                    MCU_I2C_SET_SLAVE_FF27 = 0x6b;
#endif
                }
#endif

#if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
                if(GET_DDCCI_STATUS())
                {
                    MCU_I2C_SET_SLAVE_FF23 = 0x6e & (~_BIT0);
                    MCU_I2C_IRQ_CTRL_FF28 = 0x3F;
                }
                else
                {

#if(_DDC_CHANNEL_SEL == _VGA_DDC_CHANNEL)
                    MCU_I2C_SET_SLAVE_FF23 = 0x6a;
#else
                    MCU_I2C_SET_SLAVE_FF23 = 0x6b;
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

                    MCU_I2C_IRQ_CTRL_FF28 = 0x16;
                }
#endif  // End of #if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)

}
#endif  // End of #if(_DDCCI_SUPPORT == _ON)





/*
void LSHandler(void)
{

 
 CI2cRead(LS_LINE, 0x52, 0x0C, 1, pData);
 pData[1]=pData[0];
 CI2cRead(LS_LINE, 0x52, 0x0D, 1, pData);
 //LSData=pData[0];// |LSData; 
  
#if  _DEBUG_MESSAGE_SUPPORT
 
 CDebugMessage("pdata[0]", pData[0]);
 CDebugMessage("pdata[1]", pData[1]); 
#endif

}
*/


