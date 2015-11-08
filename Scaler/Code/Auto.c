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
// ID Code      : Auto.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __AUTO__

#include "Common\Header\Include.h"

#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)
//--------------------------------------------------
// Description  : Auto clock, phase and H,V position
// Input Value  : None
// Output Value : _ERROR_SUCCESS if succeed
//--------------------------------------------------
BYTE CAutoDoAutoConfig(void)
{
    bit autoposition = _SUCCESS;
    bit autoclock = _SUCCESS;
    bit autophase = _SUCCESS;

    // V012 Modify 20100323 Start
    // V012 Patch Note (5) : Auto function modifications.
    /*
    BYTE ucResult = 0xFF;
    */
    BYTE ucResult = _ERROR_ABORT;
    // V012 Modify 20100323 End

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
    CModeYuvRgbSwitch(_RGB_COLOR_FORMAT);
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End

    // Clear the HW auto status to prevent some un-expected event happened
    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);

    CMiscClearStatusRegister();

    // Check Input Active Region
    if(CAutoCheckActiveRegion())
    {
        // Do Auto Phase (if active region has been captured, we only do Auto Phase.)
        if(CAutoDoAutoPhase() != _ERROR_SUCCESS)
        {
            stModeUserData.Phase = stModeUserCenterData.CenterPhase;
            CAdjustPhase(stModeUserData.Phase);
        }

// V012 Modify 20100323 Start
// V012 Patch Note (5) : Auto function modifications.
#if(_AUTO_POSITION_FOR_IN_REGION == _ON)
// V012 Modify 20100323 End

        // Do Auto Position
        if(CAutoDoAutoPosition() != _ERROR_SUCCESS)
        {
            if(CAutoCheckCaptureStart(stModeUserCenterData.CenterHPos, stModeUserData.Clock) == _TRUE)
            {
                stModeUserData.HPosition = stModeUserCenterData.CenterHPos;
                CAdjustHPosition();
            }

            stModeUserData.VPosition = stModeUserCenterData.CenterVPos;
            CAdjustVPosition();
        }

        CAdjustUpdateCenterData();
        CEepromSaveCenterModeData(stModeInfo.ModeCurr);
        CAutoFailCountProc(_ERROR_ABORT);

        // V013 VGA Patch Note (10) 20100416 Modify Start
        // Patch Reason : Support Auto Config For Yuv Color.
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
        CModeYuvRgbSwitch(_YUV_COLOR_FORMAT);
#endif
        // V013 VGA Patch Note (10) 20100416 Modify End

        return ucResult;

// V012 Modify 20100323 Start
// V012 Patch Note (5) : Auto function modifications.
#else
        CAutoFailCountProc(_ERROR_ABORT);

        // V013 VGA Patch Note (10) 20100416 Modify Start
        // Patch Reason : Support Auto Config For Yuv Color.
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
        CModeYuvRgbSwitch(_YUV_COLOR_FORMAT);
#endif
        // V013 VGA Patch Note (10) 20100416 Modify End

        return _ERROR_ABORT;
#endif
// V012 Modify 20100323 End
    }

    // Do Auto Position
    if(CAutoDoAutoPosition() != _ERROR_SUCCESS)
    {
        if(CAutoCheckCaptureStart(stModeUserCenterData.CenterHPos, stModeUserData.Clock) == _TRUE)
        {
            stModeUserData.HPosition = stModeUserCenterData.CenterHPos;
            CAdjustHPosition();
        }

        stModeUserData.VPosition = stModeUserCenterData.CenterVPos;
        CAdjustVPosition();
        autoposition = _FAIL;
    }

    // Do Auto Clock
    if(CAutoDoAutoClock() != _ERROR_SUCCESS)
    {
        if(CAutoCheckClock(stModeUserCenterData.CenterClock) == _TRUE)
        {
            stModeUserData.Clock = stModeUserCenterData.CenterClock;
            CAdjustAdcClock(stModeUserData.Clock);
        }

        autoclock = _FAIL;
    }

    // Do Auto Phase
    if(CAutoDoAutoPhase() != _ERROR_SUCCESS)
    {
        stModeUserData.Phase = stModeUserCenterData.CenterPhase;
        CAdjustPhase(stModeUserData.Phase);
        autophase = _FAIL;
    }

    // Do Auto Position
    if(CAutoDoAutoPosition() != _ERROR_SUCCESS)
    {
        if(CAutoCheckCaptureStart(stModeUserCenterData.CenterHPos, stModeUserData.Clock) == _TRUE)
        {
            stModeUserData.HPosition = stModeUserCenterData.CenterHPos;
            CAdjustHPosition();
        }

        stModeUserData.VPosition = stModeUserCenterData.CenterVPos;
        CAdjustVPosition();
        autoposition = _FAIL;
    }

    // V013 VGA Patch Note (12) Modify 20100416 Start
    // Patch Reason : Fix unnecessary auto fail count saving, and CAutoDoAutoConfig return value as well.
    // Set First Auto Flag
    /*
    if((GET_AUTO_FLAG() == 0) && (autoposition == _SUCCESS) && ((autoclock == _SUCCESS) || (stModeInfo.IHWidth <= 720)))
    {
        ucResult = _ERROR_SUCCESS;
    }
    else
    {
        ucResult = _ERROR_ABORT;
    }
    */
    // Set Auto Config Result
    if((autoposition == _SUCCESS) && ((autoclock == _SUCCESS) || (stModeInfo.IHWidth <= 720)))
    {
        ucResult = _ERROR_SUCCESS;
    }
    else
    {
        ucResult = _ERROR_ABORT;
    }
    // V013 VGA Patch Note (12) Modify 20100416 End

    // Save auto result after checking frame-sync status.
    CScalerSetByte(_STATUS0_02, 0x00);
    CTimerWaitForEvent(_EVENT_DVS);
    CTimerWaitForEvent(_EVENT_DVS);
    CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);

    if((pData[0] & 0x63) == 0x00)
    {
        CAdjustUpdateCenterData();

        // V013 VGA Patch Note (10) 20100416 Modify Start
        // Patch Reason : Support Auto Config For Yuv Color.
        /*
        CEepromSaveCenterModeData(stModeInfo.ModeCurr);
        CEepromSaveSystemData();
        */
#if((_FIFO_MODE_ONLY == _OFF) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
        if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) && (g_bYuvRgbFlag == _FALSE))
#endif
        {
            CEepromSaveCenterModeData(stModeInfo.ModeCurr);
            CEepromSaveSystemData();
        }
        // V013 VGA Patch Note (10) 20100416 Modify End

        CMiscClearStatusRegister();
    }
    else
    {
        ucResult = _ERROR_ABORT;
    }

    CAutoFailCountProc(ucResult);

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
    CModeOverScanSetCaptureStart();
#endif
// V012 Modify 20100316 End

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
    CModeYuvRgbSwitch(_YUV_COLOR_FORMAT);
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End

    return ucResult;
}

//--------------------------------------------------
// Description  : Check active region which should be under the capture window.
// Input Value  : None
// Output Value : Return _TRUE if active region has been captured, we only do Auto Phase.
//--------------------------------------------------
bit CAutoCheckActiveRegion(void)
{
    // Check VPosition Active Region
    if(_ERROR_SUCCESS != CAutoMeasurePositionV(_MIN_NOISE_MARGIN))
    {
        return _FALSE;
    }

    // Check HPosition Active Region
    if(_ERROR_SUCCESS != CAutoMeasurePositionH(_MIN_NOISE_MARGIN))
    {
        return _FALSE;
    }

    if(g_usHStartPos <= (stModeUserCenterData.CenterHPos + (WORD)((DWORD)(stModeInfo.IHWidth) * _ACTIVE_REGION_PERCENTAGE_THD / 100)))
    {
        return _FALSE;
    }
    else if(g_usHEndPos >= (stModeUserCenterData.CenterHPos + stModeInfo.IHWidth - (WORD)((DWORD)(stModeInfo.IHWidth) * _ACTIVE_REGION_PERCENTAGE_THD / 100)))
    {
        return _FALSE;
    }
    else
    {
        // The below code is used to adjust image in the center H-position when the active region has been captured.
        /*
        ((WORD *)pData)[0] = g_usHStartPos - ((stModeInfo.IHWidth - (g_usHEndPos - g_usHStartPos + 1)) / 2);

        if(abs(((WORD *)pData)[0] - stModeUserCenterData.CenterHPos) >= 2)
        {
            stModeUserCenterData.CenterHPos = ((WORD *)pData)[0];
        }

        stModeUserData.HPosition = stModeUserCenterData.CenterHPos;
        */
        return _TRUE;
    }

}

//--------------------------------------------------
// Description  : Auto color ( white balance )
// Input Value  : None
// Output Value : _ERROR_SUCCESS if succeed
//--------------------------------------------------
BYTE CAutoDoWhiteBalance(void)
{
    BYTE result = 0;

    // V015 VGA Patch Note (10) Modify 20100623 Start
    // Patch Reason : Correct BandWidth Setting.
    /*
    BYTE ucPixelClock = 0;
    */
    BYTE ucBandWidthTemp = 0;
    // V015 VGA Patch Note (10) Modify 20100623 End

    // V013 VGA Patch Note (27) 20100518 Modify Start
    // Patch Reason : Set Right Source Type Before Auto Color
    #if(_COLOR_FORMAT_CONVERT == _ON)
    BYTE  ucTemp = GET_INPUTSOURCE_TYPE();

    if(GET_COLOR_FORMAT_STATUS() == _YUV_COLOR_FORMAT)
    {
        SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);
    }
    else
    {
        SET_INPUTSOURCE_TYPE(_SOURCE_VGA);
    }
    #endif
    // V013 VGA Patch Note (27) 20100518 Modify End

    CScalerPageSelect(_PAGE0);

    // V015 VGA Patch Note (10) Modify 20100623 Start
    // Patch Reason : Correct BandWidth Setting.
    CScalerRead(_P0_ADC_RGB_CTRL_CE, 1, &ucBandWidthTemp, _NON_AUTOINC);
    // V015 VGA Patch Note (10) Modify 20100623 End

    CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);  //75MHz

    result = CAutoTuneBalance();
#if _DEBUG_MESSAGE_SUPPORT
#endif
    if(result == _ERROR_SUCCESS)
    {

#if _DEBUG_MESSAGE_SUPPORT
				CDebugMessage("CEepromSaveAdcData_ori2", 0);
				
				CDebugMessage("stAdcData.AdcOffset.[_RED]",stAdcData.AdcOffset[_RED]);
				CDebugMessage("stAdcData.AdcOffset.[_GREEN]",stAdcData.AdcOffset[_GREEN]);
				CDebugMessage("stAdcData.AdcOffset.[_BLUE]",stAdcData.AdcOffset[_BLUE]);
#endif
	
        stAdcData.AdcGain[_RED] = stAdcData.AdcGain[_RED] -4;//adc data adjust sjp20110902
        stAdcData.AdcGain[_GREEN] = stAdcData.AdcGain[_GREEN]-4;
        stAdcData.AdcGain[_BLUE] =stAdcData.AdcGain[_BLUE] -4;
	CAdjustAdcGainOffset();
        CEepromSaveAdcData();
    }
    else
    {
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("333333333333",0);
#endif
	
        CEepromLoadAdcDataDefault();
    }

    // V015 VGA Patch Note (10) Modify 20100623 Start
    // Patch Reason : Correct BandWidth Setting.
    /*
    // Calculate pixel clock rate (round to MHz)
    ucPixelClock = (((DWORD)stModeInfo.IHFreq * (DWORD)stModeInfo.IHTotal) * 2 / (1000 * 10));
    ucPixelClock = (ucPixelClock >> 1) + (ucPixelClock & 0x01);

    CScalerPageSelect(_PAGE0);
    if(ucPixelClock < 38)
    {
        CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);   //75MHz
    }
    else if(ucPixelClock < 68)
    {
        CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));  //150MHz
    }
    else if(ucPixelClock < 160)
    {
        CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));  //300MHz
    }
    else
    {
        CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));  //500MHz
    }
    */
    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | (ucBandWidthTemp & (_BIT1 | _BIT0))));
    // V015 VGA Patch Note (10) Modify 20100623 End

    // V013 VGA Patch Note (27) 20100518 Modify Start
    // Patch Reason : Set Right Source Type Before Auto Color
    #if(_COLOR_FORMAT_CONVERT == _ON)
    SET_INPUTSOURCE_TYPE(ucTemp);
    #endif
    // V013 VGA Patch Note (27) 20100518 Modify End

    return result;
}

//--------------------------------------------------
// Description  : Wait auto measure process completed
// Input Value  : None
// Output Value : Return result _ERROR_INPUT, _ERROR_SUCCESS
//--------------------------------------------------
BYTE CAutoWaitFinish(void)
{
    BYTE timeoutcnt = 0, ivsevent = 0;

    // V012 Modify 20100317 Start
    // V012 Patch Note (9) : Remove safe mode.
    BYTE ucModeNum = 0;
    // V012 Modify 20100317 End

    CMiscClearStatusRegister();

    // Auto timeout
    timeoutcnt = (CScalerGetBit(_AUTO_ADJ_CTRL0_7A, _BIT1 | _BIT0) == 0x03) ? 150 : 50;

    // IVS timeout
    ivsevent = 25;

// V012 Modify 20100317 Start
// V012 Patch Note (9) : Remove safe mode.
// Remove save mode on purpose, as there're still some issue with it.
/*
#if(_SAFE_MODE == _ON)
    if (stModeInfo.ModeCurr == _MODE_720x400_70HZ || stModeInfo.ModeCurr == _MODE_640x350_70HZ) //for 24w dos mode
    {
        timeoutcnt *= 2;
        ivsevent *= 2;
    }
#endif
*/
// V012 Modify 20100317 End

    do
    {
        CTimerDelayXms(1);

        CScalerRead(_STATUS1_03, 1, pData, _NON_AUTOINC);

        if(pData[0] & _EVENT_IVS)
        {
            CScalerSetByte(_STATUS1_03, 0x00);
            ivsevent = 25;

// V012 Modify 20100317 Start
// V012 Patch Note (9) : Remove safe mode.
// Remove save mode on purpose, as there're still some issue with it.
/*
#if(_SAFE_MODE == _ON)
            if (stModeInfo.ModeCurr == _MODE_720x400_70HZ || stModeInfo.ModeCurr == _MODE_640x350_70HZ) //for 24w dos mode
            {
                ivsevent *= 2;
            }
#endif
*/
// V012 Modify 20100317 End

        }
        else
        {
            ivsevent = ivsevent - 1;
        }

        if(ucCurrState != _ACTIVE_STATE)
        {
            if(ivsevent == 0)
            {
                return _ERROR_INPUT;
            }
        }
        else
        {
            if((ivsevent == 0) || (pData[0] & (_EVENT_UNDERFLOW | _EVENT_OVERFLOW)))
            {
                return _ERROR_INPUT;
            }
        }

        // Power off while auto config--------
        CKeyCheckPowerKey();

        if(GET_POWERSWITCH())
        {
            return _ERROR_INPUT;
        }
        //------------------------------------

        CScalerRead(_AUTO_ADJ_CTRL1_7D, 1, pData, _NON_AUTOINC);
    }
    while((pData[0] & 0x01) && (--timeoutcnt));

    CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);
    CScalerSetByte(_STATUS0_02, 0x00);

    // Return non-zero value in Data[0] if :
    // 1. IVS or IHS changed
    // 2. Auto-Phase Tracking timeout

    if(ucCurrState != _ACTIVE_STATE)
    {
        return (0 == timeoutcnt) ? _ERROR_INPUT : _ERROR_SUCCESS;
    }
    else
    {
        return ((pData[0] & 0x63) || (0 == timeoutcnt)) ? _ERROR_INPUT : _ERROR_SUCCESS;
    }

}

//--------------------------------------------------
// Description  : Wait for IVS process
// Input Value  : ucTimes   --> frames
// Output Value : Return underflow/overflow status
//--------------------------------------------------
BYTE CAutoWaitForIVS(BYTE ucTimes)
{
    BYTE timeoutcnt = 25;

    CScalerSetByte(_STATUS1_03, 0x00);
    do
    {
        CTimerDelayXms(1);

        CScalerRead(_STATUS1_03, 1, pData, _NON_AUTOINC);

        pData[0] &= (_EVENT_IVS | _EVENT_UNDERFLOW | _EVENT_OVERFLOW);

        if(((pData[0] & _EVENT_IVS) == _EVENT_IVS) && (ucTimes != 0))
        {
            CScalerSetByte(_STATUS1_03, 0x00);
            ucTimes--;
            timeoutcnt = 25;
        }
    }
    while((ucTimes != 0) && (--timeoutcnt) && ((pData[0] & (_EVENT_UNDERFLOW | _EVENT_OVERFLOW)) == 0));

    return pData[0];
}

//--------------------------------------------------
// Description  : Measure position H
// Input Value  : ucNoiseMarginH    --> Noise margin for H
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoMeasurePositionH(BYTE ucNoiseMarginH)
{
    WORD lbound = 0, rbound = 0;
    BYTE ucOffset = 0;

    CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, 0x50);
    CScalerRead(_VGIP_HV_DELAY_1E, 1, pData, _NON_AUTOINC);

    ////////////////////////////////////////////////////////////////
    //  _VGIP_HV_DELAY_1E (BIT7,6)     |        ucOffset          //
    // --------------------------------+------------------------- //
    //            00                   |           0              //
    //            01                   |           32             //
    //            10                   |           64             //
    //            11                   |           96             //
    ////////////////////////////////////////////////////////////////

    ucOffset = ((pData[0] >> 6) & 0x03) * 32;

    /////////////////////////////////////////////////////////////////////////////////////////
    // Horizontal Boundary Start of Auto Function                                          //
    // ucHOffset: Reference CR[1E] bit7~bit6: Delay clock counts,                          //
    //                                                                                     //
    // (((DWORD)stModeUserData.Clock * stModeInfo.IHSyncPulseCount) / stModeInfo.IHCount)  //
    // => Clock counts  of H-Sync high pulse in setting clock                              //
    //                                                                                     //
    // (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_AFTER_HSYNC) / g_usAdcClockLimit)      //
    // => Noise width counts near to H-Sync in back porch                                  //
    //                                                                                     //
    // (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_BEFORE_HSYNC) / g_usAdcClockLimit)     //
    // => Noise width counts near to H-Sync in front porch                                 //
    /////////////////////////////////////////////////////////////////////////////////////////

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
    /*
    lbound = (((DWORD)stModeUserData.Clock * stModeInfo.IHSyncPulseCount) / stModeInfo.IHCount) + (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_AFTER_HSYNC) / _PIXEL_WIDTH_LIMIT);
    */
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
#if(_YPBPR_SUPPORT == _ON)
    if(((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4) == 1) && ((CModeCheckVideoMode() == _TRUE) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)))
#else
    if(((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4) == 1) && (CModeCheckVideoMode() == _TRUE))
#endif
    {
        CScalerGetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_G_CLAMP_START_00, 2, pData, _NON_AUTOINC);
        CScalerGetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL2_06, 1, &pData[8], _NON_AUTOINC);

        // usLbound BackUp for _SYNC_G_CLAMP_START_00
        lbound = pData[0];

        // usRbound BackUp for _SYNC_G_CLAMP_End_01
        rbound = pData[1];

        if((pData[8] & _BIT6) == 0) // Double Pixels
        {
            lbound = lbound * 2;
            rbound = rbound * 2;
        }

        // Calc width of clamp
        rbound = rbound - lbound + 1;

        // _SYNC_G_CLAMP_End_01 must be large than _SYNC_G_CLAMP_START_00
        // Clamp width * _LBOUNDARY_CAL_CLAMP_RATIO / 100 + clamp start > _NOISE_WIDTH_AFTER_HSYNC
        if((pData[1] > pData[0])
        && ((((rbound * _LBOUNDARY_CAL_CLAMP_RATIO) / 100) + lbound) > (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_AFTER_HSYNC) / _PIXEL_WIDTH_LIMIT)))
        {
            lbound = (((DWORD)stModeUserData.Clock * stModeInfo.IHSyncPulseCount) / stModeInfo.IHCount) + (((rbound * _LBOUNDARY_CAL_CLAMP_RATIO) / 100) + lbound);
        }
        else
        {
            lbound = (((DWORD)stModeUserData.Clock * stModeInfo.IHSyncPulseCount) / stModeInfo.IHCount) + (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_AFTER_HSYNC) / _PIXEL_WIDTH_LIMIT);
        }
    }
    else
    {
        lbound = (((DWORD)stModeUserData.Clock * stModeInfo.IHSyncPulseCount) / stModeInfo.IHCount) + (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_AFTER_HSYNC) / _PIXEL_WIDTH_LIMIT);
    }
#else
    lbound = (((DWORD)stModeUserData.Clock * stModeInfo.IHSyncPulseCount) / stModeInfo.IHCount) + (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_AFTER_HSYNC) / _PIXEL_WIDTH_LIMIT);
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End

    // V012 Modify 20100323 Start
    // V012 Patch Note (5) : Auto function modifications.
    /*
    if(ucCurrState == _ACTIVE_STATE)
    {
        rbound = (WORD)((DWORD)(stModeUserCenterData.CenterClock - stModeUserCenterData.CenterHPos - stModeInfo.IHWidth) * _H_BOUND_RANGE_R / 100);
        rbound = stModeUserCenterData.CenterHPos + stModeInfo.IHWidth + rbound;
    }
    else
    {
        rbound = stModeUserData.Clock - (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_BEFORE_HSYNC) / _PIXEL_WIDTH_LIMIT);
    }
    */
    rbound = stModeUserData.Clock - (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_BEFORE_HSYNC) / _PIXEL_WIDTH_LIMIT);
    // V012 Modify 20100323 End

    if(lbound < ucOffset)
    {
        CScalerRead(_VGIP_HV_DELAY_1E, 1, &pData[0], _NON_AUTOINC);
        CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, (pData[0] & 0x3F));
        ucOffset = 0;
    }
    else
    {
        lbound = lbound - ucOffset;
        rbound = rbound - ucOffset;
    }

    ucNoiseMarginH &= 0xfc;
    CScalerSetBit(_AUTO_ADJ_CTRL1_7D, ~_BIT0, 0x00);

#if(_SCALER_TYPE == _RTD2472D)
    pData[0] = ((lbound >> 4) & 0x70) | (HIBYTE(rbound) & 0x0f);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    pData[0] = ((lbound >> 4) & 0xF0) | (HIBYTE(rbound) & 0x0f);
#else
    No Setting !!
#endif

    // Vsync Lbound : 0x02
    // Vsync Rbound : stModeInfo.IVTotal - 1 + 3
    /*
    pData[1]    = (LOBYTE(lbound));
    pData[2]    = (LOBYTE(rbound));
    pData[3]    = (HIBYTE(stModeInfo.IVTotal - 1 + 3) & 0x0f);
    pData[4]    = (0x02);
    pData[5]    = (LOBYTE(stModeInfo.IVTotal - 1 + 3));
    CScalerWrite(_H_BOUNDARY_H_70, 6, pData, _AUTOINC);
    */
    pData[1] = (LOBYTE(lbound));
    pData[2] = (LOBYTE(rbound));
    CScalerWrite(_H_BOUNDARY_H_70, 3, pData, _AUTOINC);

    pData[0] = ucNoiseMarginH;
    pData[1] = ucNoiseMarginH;
    pData[2] = ucNoiseMarginH;
    CScalerWrite(_RED_NOISE_MARGIN_76, 3, pData, _AUTOINC);

    // CR[7A]-Bit3~2:00, 1 pixel over threshold (Default)
    // CR[7A]-Bit1~0:00, Color source slect, Setting B channel (Default)
    // CR[7A]-Bit4, can not be used in color measure
    CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    CScalerSetBit(_AUTO_ADJ_CTRL1_7D, ~(_BIT7 | _BIT0), _BIT0);

    pData[0] = CAutoWaitFinish();

    if(pData[0] != _ERROR_SUCCESS)
    {
        return pData[0];
    }

    CScalerRead(_H_START_END_H_81, 3, &pData[8], _AUTOINC);

    g_usHStartPos = (((WORD)(pData[8] & 0xf0 ) << 4) | (WORD)pData[9]) + ucOffset;
    g_usHEndPos = (((WORD)(pData[8] & 0x0f ) << 8) | (WORD)pData[10]) + ucOffset;

    if((g_usHEndPos < g_usHStartPos) || (g_usHEndPos == ucOffset) || (g_usHStartPos == ucOffset))
    {
        g_usHStartPos = 0;
        g_usHEndPos = 0;
        return _ERROR_ABORT;
    }

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Measure position V
// Input Value  : ucNoiseMarginV    --> Noise margin for V
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoMeasurePositionV(BYTE ucNoiseMarginV)
{
    BYTE ucHOffset = 0;
    BYTE ucVOffset = 0;
    WORD lbound = 0, rbound = 0;

    CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, 0x50);
    CScalerRead(_VGIP_HV_DELAY_1E, 1, pData, _NON_AUTOINC);

    ////////////////////////////////////////////////////////////////
    //  _VGIP_HV_DELAY_1E (BIT7,6)     |       ucHOffset          //
    // --------------------------------+------------------------- //
    //            00                   |           0              //
    //            01                   |           32             //
    //            10                   |           64             //
    //            11                   |           96             //
    ////////////////////////////////////////////////////////////////

    ucHOffset = ((pData[0] >> 6) & 0x03) * 32;

    ////////////////////////////////////////////////////////////////
    //  _VGIP_HV_DELAY_1E (BIT5,4)     |       ucVOffset          //
    // --------------------------------+------------------------- //
    //            00                   |           0              //
    //            01                   |           3              //
    //            10                   |           7              //
    //            11                   |           15             //
    ////////////////////////////////////////////////////////////////

    ucVOffset = (1 << (((pData[0] >> 4) & 0x03) + 1)) - 1;
    ucVOffset = (ucVOffset == 1) ? 0 : ucVOffset;

    /////////////////////////////////////////////////////////////////////////////////////////
    // Horizontal Boundary Start of Auto Function                                          //
    // ucHOffset: Reference CR[1E] bit7~bit6: Delay clock counts,                          //
    //                                                                                     //
    // (((DWORD)stModeUserData.Clock * stModeInfo.IHSyncPulseCount) / stModeInfo.IHCount)  //
    // => Clock counts  of H-Sync high pulse in setting clock                              //
    //                                                                                     //
    // (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_AFTER_HSYNC) / g_usAdcClockLimit)      //
    // => Noise width counts near to H-Sync in back porch                                  //
    //                                                                                     //
    // (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_BEFORE_HSYNC) / g_usAdcClockLimit)     //
    // => Noise width counts near to H-Sync in front porch                                 //
    /////////////////////////////////////////////////////////////////////////////////////////

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
    /*
    lbound = (((DWORD)stModeUserData.Clock * stModeInfo.IHSyncPulseCount) / stModeInfo.IHCount) + (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_AFTER_HSYNC) / _PIXEL_WIDTH_LIMIT);
    */
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
#if(_YPBPR_SUPPORT == _ON)
    if(((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4) == 1) && ((CModeCheckVideoMode() == _TRUE) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)))
#else
    if(((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4) == 1) && (CModeCheckVideoMode() == _TRUE))
#endif
    {
        CScalerGetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_G_CLAMP_START_00, 2, pData, _NON_AUTOINC);
        CScalerGetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL2_06, 1, &pData[8], _NON_AUTOINC);

        // usLbound BackUp for _SYNC_G_CLAMP_START_00
        lbound = pData[0];

        // usRbound BackUp for _SYNC_G_CLAMP_End_01
        rbound = pData[1];

        if((pData[8] & _BIT6) == 0) // Double Pixels
        {
            lbound = lbound * 2;
            rbound = rbound * 2;
        }

        // Calc width of clamp
        rbound = rbound - lbound + 1;

        // _SYNC_G_CLAMP_End_01 must be large than _SYNC_G_CLAMP_START_00
        // Clamp width * _LBOUNDARY_CAL_CLAMP_RATIO / 100 + clamp start > _NOISE_WIDTH_AFTER_HSYNC
        if((pData[1] > pData[0])
        && ((((rbound * _LBOUNDARY_CAL_CLAMP_RATIO) / 100) + lbound) > (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_AFTER_HSYNC) / _PIXEL_WIDTH_LIMIT)))
        {
            lbound = (((DWORD)stModeUserData.Clock * stModeInfo.IHSyncPulseCount) / stModeInfo.IHCount) + (((rbound * _LBOUNDARY_CAL_CLAMP_RATIO) / 100) + lbound);
        }
        else
        {
            lbound = (((DWORD)stModeUserData.Clock * stModeInfo.IHSyncPulseCount) / stModeInfo.IHCount) + (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_AFTER_HSYNC) / _PIXEL_WIDTH_LIMIT);
        }
    }
    else
    {
        lbound = (((DWORD)stModeUserData.Clock * stModeInfo.IHSyncPulseCount) / stModeInfo.IHCount) + (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_AFTER_HSYNC) / _PIXEL_WIDTH_LIMIT);
    }
#else
    lbound = (((DWORD)stModeUserData.Clock * stModeInfo.IHSyncPulseCount) / stModeInfo.IHCount) + (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_AFTER_HSYNC) / _PIXEL_WIDTH_LIMIT);
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End

    // V012 Modify 20100323 Start
    // V012 Patch Note (5) : Auto function modifications.
    /*
    if(ucCurrState == _ACTIVE_STATE)
    {
        rbound = (WORD)((DWORD)(stModeUserCenterData.CenterClock - stModeUserCenterData.CenterHPos - stModeInfo.IHWidth) * _H_BOUND_RANGE_R / 100);
        rbound = stModeUserCenterData.CenterHPos + stModeInfo.IHWidth + rbound;
    }
    else
    {
        rbound = stModeUserData.Clock - (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_BEFORE_HSYNC) / _PIXEL_WIDTH_LIMIT);
    }
    */
    rbound = stModeUserData.Clock - (((DWORD)stModeUserData.Clock * _NOISE_WIDTH_BEFORE_HSYNC) / _PIXEL_WIDTH_LIMIT);
    // V012 Modify 20100323 End

    if(lbound <= ucHOffset)
    {
        CScalerRead(_VGIP_HV_DELAY_1E, 1, &pData[0], _NON_AUTOINC);
        CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, (pData[0] & 0x3F));
        ucHOffset = 0;
    }
    else
    {
        lbound = lbound - ucHOffset;
        rbound = rbound - ucHOffset;
    }

    if((stModeInfo.IVSyncPulseCount + _NOISE_WIDTH_AFTER_VSYNC) <= ucVOffset)
    {
        CScalerRead(_VGIP_HV_DELAY_1E, 1, &pData[0], _NON_AUTOINC);
        CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, (pData[0] & 0xCF));
        ucVOffset = 0;
    }

    ucNoiseMarginV &= 0xfc;
    CScalerSetBit(_AUTO_ADJ_CTRL1_7D, ~_BIT0, 0x00);

#if(_SCALER_TYPE == _RTD2472D)
    pData[0] = ((lbound >> 4) & 0x70) | (HIBYTE(rbound) & 0x0f);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    pData[0] = ((lbound >> 4) & 0xF0) | (HIBYTE(rbound) & 0x0f);
#else
    No Setting !!
#endif

    pData[1] = (LOBYTE(lbound));
    pData[2] = (LOBYTE(rbound));

    // V012 Modify 20100403 Start
    // V012 Patch Note (31) : Fix non-full-frame issue with large IVSyncPulseWidth on SOG/CS sync type signals.
    /*
    pData[3] = (HIBYTE(stModeInfo.IVTotal - 1 - ucVOffset) & 0x0f);
    */
    if(((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)) && (g_usVTotalTemp > 0))
    {
        pData[3] = (HIBYTE(g_usVTotalTemp - 1 - ucVOffset) & 0x0f);
    }
    else
    {
        pData[3] = (HIBYTE(stModeInfo.IVTotal - 1 - ucVOffset) & 0x0f);
    }
    // V012 Modify 20100403 End

    // Vsync Rbound : stModeInfo.IVTotal - ucVOffset + _NOISE_WIDTH_AFTER_VSYNC
    pData[4] = (BYTE)(stModeInfo.IVSyncPulseCount + _NOISE_WIDTH_AFTER_VSYNC - ucVOffset);

    // V012 Modify 20100403 Start
    // V012 Patch Note (31) : Fix non-full-frame issue with large IVSyncPulseWidth on SOG/CS sync type signals.
    /*
    pData[5] = (LOBYTE(stModeInfo.IVTotal - 1 - ucVOffset));
    */
    if(((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)) && (g_usVTotalTemp > 0))
    {
        pData[5] = (LOBYTE(g_usVTotalTemp - 1 - ucVOffset));
    }
    else
    {
        pData[5] = (LOBYTE(stModeInfo.IVTotal - 1 - ucVOffset));
    }
    // V012 Modify 20100403 End

    CScalerWrite(_H_BOUNDARY_H_70, 6, pData, _AUTOINC);

    pData[0] = ucNoiseMarginV;
    pData[1] = ucNoiseMarginV;
    pData[2] = ucNoiseMarginV;
    CScalerWrite(_RED_NOISE_MARGIN_76, 3, pData, _AUTOINC);

    // CR[7A]-Bit3~2:00, 1 pixel over threshold (Default)
    // CR[7A]-Bit1~0:00, Color source slect, Setting B channel (Default)
    // CR[7A]-Bit4, can not be used in color measure
    CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    CScalerSetBit(_AUTO_ADJ_CTRL1_7D, ~(_BIT7 | _BIT0), _BIT0);

    pData[0] = CAutoWaitFinish();

    if(pData[0] != _ERROR_SUCCESS)
    {
        return pData[0];
    }

    // Read out measure horizontal range
    CScalerRead(_H_START_END_H_81, 3, &pData[8], _AUTOINC);

    g_usHStartPos = (((WORD)(pData[8] & 0xf0 ) << 4) | (WORD)pData[9]) + ucHOffset;
    g_usHEndPos = (((WORD)(pData[8] & 0x0f ) << 8) | (WORD)pData[10]) + ucHOffset;

    if(g_usHEndPos <= g_usHStartPos)
    {
        g_usHStartPos = 0;
        g_usHEndPos = 0;

        return  _ERROR_ABORT;
    }

    // Read out measure vertical range
    CScalerRead(_V_START_END_H_7E, 3, &pData[8], _AUTOINC);

    g_usVStartPos = (((WORD)(pData[8] & 0xf0) << 4) | (WORD)pData[9]) + ucVOffset;
    g_usVEndPos = (((WORD)(pData[8] & 0x0f) << 8) | (WORD)pData[10]) + ucVOffset;

    // Check all black
    if((g_usVEndPos == ucVOffset) || (g_usVStartPos == ucVOffset) || (g_usVEndPos <= g_usVStartPos))
    {
        g_usVEndPos = 0;
        g_usVStartPos = 0;

        return  _ERROR_ABORT;
    }

    // Update auto-tracking window vertical range
#if(_SCALER_TYPE == _RTD2472D)
    pData[0] = (pData[8] & 0x7f);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    pData[0] = (pData[8] & 0xff);
#else
    No Setting !!
#endif

    pData[1] = pData[9];
    pData[2] = pData[10];
    CScalerWrite(_V_BOUNDARY_H_73, 3, pData, _AUTOINC);

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto phase search function
// Input Value  :
// Output Value :
//--------------------------------------------------
DWORD CAutoPhaseSearch(BYTE ucSelColor, BYTE ucSelStep, BYTE ucSelStepNum, BYTE ucSelStepStart, BYTE *ucPhaseResult)
{
    DWORD maxsum = 0;
    BYTE  count = 0, best = 0;

    // Read difference threshold
    CScalerRead(_DIFF_THRESHOLD_79, 1, &count, _NON_AUTOINC);

    // Get difference threshold for Phase Search
    if(count == 0)
    {
        count = 0x80;
    }

    best = CAutoMeasurePositionV(_MIN_NOISE_MARGIN);
    if(_ERROR_SUCCESS != best)
    {
        return best;
    }

    best = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);
    if(_ERROR_SUCCESS != best)
    {
        return best;
    }

    // Set difference threshold
    CScalerSetByte(_DIFF_THRESHOLD_79, count);

    best = 0;

    // V015 System Patch Note (6) Modify 20100630 Start
    // Patch Reason : Correct measure boundary extract bit setting according to each spec.
    /*
    ((WORD *)pData)[4] = g_usHStartPos - 1;   // Hsync Lbound
    ((WORD *)pData)[5] = g_usHEndPos + 1;     // Hsync Rbound
    ((WORD *)pData)[6] = g_usVStartPos - 1;   // Vsync Lbound
    ((WORD *)pData)[7] = g_usVEndPos;         // Vsync Rbound

    pData[0] = ((pData[8] << 4) & 0x70) | (pData[10] & 0x0f);
    pData[1] = pData[9];
    pData[2] = pData[11];
    pData[3] = ((pData[12] << 4) & 0x70) | (pData[14] & 0x0f);
    pData[4] = pData[13];
    pData[5] = pData[15];
    */
#if(_SCALER_TYPE == _RTD2472D)
    pData[0] = (((g_usHStartPos - 1) >> 4) & 0x70) | (HIBYTE(g_usHEndPos + 1) & 0x0F);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    pData[0] = (((g_usHStartPos - 1) >> 4) & 0xF0) | (HIBYTE(g_usHEndPos + 1) & 0x0F);
#else
    No Setting !!
#endif

    pData[1] = (LOBYTE(g_usHStartPos - 1));
    pData[2] = (LOBYTE(g_usHEndPos + 1));

#if(_SCALER_TYPE == _RTD2472D)
    pData[3] = (((g_usVStartPos - 1) >> 4) & 0x70) | (HIBYTE(g_usVEndPos) & 0x0F);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    pData[3] = (((g_usVStartPos - 1) >> 4) & 0xF0) | (HIBYTE(g_usVEndPos) & 0x0F);
#else
    No Setting !!
#endif

    pData[4] = (LOBYTE(g_usVStartPos - 1));
    pData[5] = (LOBYTE(g_usVEndPos));
    // V015 System Patch Note (6) Modify 20100630 End

    CScalerWrite(_H_BOUNDARY_H_70, 6, pData, _AUTOINC);
    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
    CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT1 | _BIT0), ucSelColor & 0x03);

    // Issac : Because H/W auto phase search may cause underflow at start and stop,
    //         frame-sync watch-dog must be disabled.
    //CAdjustDisableWatchDog(_WD_ALL);

    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 1000)
    {
        ucSelStep += 1;
        ucSelStepStart *= 2;

        if(ucSelStepStart >= 64)
        {
            CScalerPageSelect(_PAGE1);
            CScalerSetBit(_P1_MIX_B0, ~_BIT1, _BIT1);
        }
    }

    CScalerSetByte(_HW_AUTO_PHASE_CTRL0_7B, (ucSelStep & 0x07) | (((ucSelStepNum - 1) & 0x1f) << 3));
    CScalerSetByte(_HW_AUTO_PHASE_CTRL1_7C, 0x00 | (ucSelStepStart & 0x3f));

    ucSelStep = (0x01 << ucSelStep);
    ucSelColor = ucSelStepStart + (ucSelStepNum) * ucSelStep;
    count = ucSelStepStart;
    maxsum = 0;
    best = 0;

    // Issac : Using Wait_For_Event(EVENT_IVS) instead of Wait_For_IVS().
    //         Because H/W auto phase search may cause underflow at start and stop.
    //         Wait_For_Event() will not check underflow/overflow.

    if(CScalerGetBit(_AUTO_ADJ_CTRL0_7A, _BIT1 | _BIT0) == 0x03)
    {
        CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT4 | _BIT1 | _BIT0), _BIT4);
    }
    else
    {
        CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~_BIT4, _BIT4);
    }

    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x7b);

    CAutoWaitForIVS(1);

    do
    {
        if(CAutoWaitForIVS(((CScalerGetBit(_AUTO_ADJ_CTRL0_7A, _BIT1 | _BIT0) == 0x03) ? 3 : 1)) & (_EVENT_UNDERFLOW | _EVENT_OVERFLOW))
        {
            CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
            CScalerPageSelect(_PAGE1);
            CScalerSetBit(_P1_MIX_B0, ~_BIT1, 0x00);

            return 0xffffffff;
        }

        CScalerRead(_AUTO_PHASE_3_84, 3, pData, _AUTOINC);

        pData[3] = 0;

        if(((DWORD *)pData)[0] > maxsum)
        {
            maxsum = ((DWORD *)pData)[0];
            best = count;
        }

        count += ucSelStep;
    }
    while(count < ucSelColor);

    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_MIX_B0, ~_BIT1, 0x00);

    CTimerWaitForEvent(_EVENT_IVS);

    pData[0] = CAutoWaitFinish();

    if(pData[0] != _ERROR_SUCCESS)
    {
        return 0xffffffff;
    }

    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 1000)
    {
        *ucPhaseResult = best / 2;
    }
    else
    {
        *ucPhaseResult = best;
    }

    return maxsum;
}

//--------------------------------------------------
// Description  : Get phase SOD information
// Input Value  : ucColor   --> Color we measure
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoReadPhaseInfo(BYTE ucColor)
{
    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
    CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT1 | _BIT0), ucColor & 0x03);
    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x3b);

    pData[0] = CAutoWaitFinish();

    if(_ERROR_SUCCESS != pData[0])
    {
        CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
        return pData[0];
    }

    CScalerRead(_AUTO_PHASE_3_84, 4, pData, _AUTOINC);

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto clock process
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoDoAutoClock(void)
{
    BYTE result = 0, phase = 0;
    WORD count = 0, delta = 0, stop = 0;
    DWORD maxval = 0;

    bit bReachClockLimit = _FALSE;
    bit bReturPoint = _FALSE;
    WORD usMinDiff = 0xFFFF;
    DWORD ulThreshold = 0;

    // V015 VGA Patch Note (13) Modify 20100708 Start
    // Patch Reason : Remove unnecessary phase search and adjustment to improve auto clock speed.
    /*
    maxval = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_8, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART(0), &result);

    if((maxval != 0xffffffffL) && (maxval != 0))
    {
        CAdjustPhase(stModeUserData.Phase);
    }
    */
    // V015 VGA Patch Note (13) Modify 20100708 End

    result = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);

    if(result != _ERROR_SUCCESS)
    {
        return result;
    }

    g_usHEndPos = g_usHEndPos + 1 - g_usHStartPos;

    // V013 VGA Patch Note (14) Modify 20100420 Start
    // Patch Reason : Fix for higher accuracy.
    /*
    if((DWORD)g_usHEndPos * 100 / stModeUserData.Clock < ((DWORD)stModeInfo.IHWidth * _AUTO_CLOCK_RANGE / stModeInfo.IHTotal))
    */
    //    (Measure Width / User Clock < IHWidth) * (_AUTO_CLOCK_RANGE / IHTotal)
    // => (Measure Width * IHTotal) < (IHWidth * _AUTO_CLOCK_RANGE * User Clock)
    if(((DWORD)g_usHEndPos * 100 * stModeInfo.IHTotal) < ((DWORD)stModeInfo.IHWidth * _AUTO_CLOCK_RANGE * stModeUserData.Clock))
    // V013 VGA Patch Note (14) Modify 20100420 End
    {
        return _ERROR_ABORT;
    }

    maxval = stModeUserData.Clock; // Backup the currect clcok to maxval

    if(stModeInfo.IHTotal >= stModeUserCenterData.CenterClock)
    {
        stModeUserData.Clock = stModeInfo.IHTotal;
    }
    else
    {
        stModeUserData.Clock = stModeUserCenterData.CenterClock;
    }

    if(CAutoCheckClock(stModeUserData.Clock) == _FALSE)
    {
        if(CAutoCheckClock(g_usAdcClockLimit) == _FALSE)
        {
            stModeUserData.Clock = maxval;
            return _ERROR_ABORT;
        }
        else
        {
            stModeUserData.Clock = g_usAdcClockLimit;
        }
    }

    stModeUserData.Clock &= 0xfffc;

    CAdjustAdcClock(stModeUserData.Clock);

    result = CAutoMeasurePositionV(_MIN_NOISE_MARGIN);

    if(result != _ERROR_SUCCESS)
    {
        return result;
    }

    delta = (stModeInfo.IHTotal - stModeInfo.IHWidth * 8 / 10) / 2;

    stop = 0;
    count = 10;

    do
    {
        result = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);

        if(result != _ERROR_SUCCESS)
        {
            return result;
        }

        g_usHEndPos = g_usHEndPos + 1 - g_usHStartPos;

        if(g_usHEndPos == stModeInfo.IHWidth)
        {
            break;
        }

        // V015 VGA Patch Note (15) Modify 20100713 Start
        // Patch Reason : Modify compensation of calculation rounding errors for bettern understanding to user.
        /*
        if((g_usHEndPos + 0xFFFF / 2 - stModeInfo.IHWidth + usMinDiff) == 0xFFFE)
        {
            bReturPoint = _TRUE;
        }
        else
        {
            usMinDiff = g_usHEndPos + 0xFFFF / 2 - stModeInfo.IHWidth;
        }
        */
        if((g_usHEndPos + usMinDiff) == (stModeInfo.IHWidth * 2))
        {
            bReturPoint = _TRUE;
        }
        else
        {
            usMinDiff = g_usHEndPos;
        }
        // V015 VGA Patch Note (15) Modify 20100713 End

        if(abs((DWORD)g_usHEndPos * stModeInfo.IHTotal - (DWORD)stModeInfo.IHWidth * stModeUserData.Clock) >= ((DWORD)delta * 2 * stModeUserData.Clock))
        {
            stop = 1;
        }
        else
        {
            ////////////////////////////////////////////////////////
            // g_usHStartPos is the target clock                  //
            //                                                    //
            //  Measured_Width     ModeTable_Width                //
            // ---------------- = -----------------               //
            //  Current_Clock       Target_Clock                  //
            //                                                    //
            //                 ModeTable_Width * Current_Clock    //
            // Target_Clock = ---------------------------------   //
            //                        Measured_Width              //
            ////////////////////////////////////////////////////////

            if(bReturPoint == _TRUE)
            {
                g_usHStartPos = (((DWORD)stModeInfo.IHWidth * stModeUserData.Clock + (g_usHEndPos / 2)) / g_usHEndPos + stModeUserData.Clock) / 2;
            }
            else
            {
                g_usHStartPos = ((DWORD)stModeInfo.IHWidth * stModeUserData.Clock + (g_usHEndPos / 2)) / g_usHEndPos;
            }

            if(g_usHStartPos == stModeUserData.Clock)
            {
                break;
            }

            if(g_usHEndPos < stModeInfo.IHWidth)
            {
                if(g_usHStartPos > (delta + stModeInfo.IHTotal))
                {
                    stop = 1;
                }
                else
                {
                    stModeUserData.Clock = g_usHStartPos;
                }
            }
            else
            {
                if((abs(g_usHStartPos - stModeUserData.Clock) + stModeInfo.IHTotal) > (delta + stModeUserData.Clock))
                {
                    stop = 1;
                }
                else
                {
                    if(CAutoCheckClock(g_usHStartPos) == _FALSE)
                    {
                        stop = 1;
                    }
                    else
                    {
                        stModeUserData.Clock = g_usHStartPos;
                    }
                }
            }
        }

        if(stModeUserData.Clock >= g_usAdcClockLimit)
        {
            if(_TRUE == bReachClockLimit)
            {
                stop = 1;
            }
            else
            {
                if(CAutoCheckClock(g_usAdcClockLimit) == _TRUE)
                {
                    stModeUserData.Clock = g_usAdcClockLimit;
                    bReachClockLimit = _TRUE;
                }
                else
                {
                    stop = 1;
                }
            }
        }
        else
        {
            bReachClockLimit = _FALSE;
        }

        if(stop)
        {
            break;
        }

        CAdjustAdcClock(stModeUserData.Clock);
    }
    while(--count);

    if((count == 0) || (stop == 1))
    {
        return _ERROR_ABORT;
    }

#if(_AUTO_CLOCK_MOIRE_SMEAR_EFFECT == _ON)

    // Prevent from 1/2-line moire and smear effect.
    if((g_usHEndPos >= stModeInfo.IHWidth && (stModeUserData.Clock - stModeInfo.IHTotal) == 4)
       || (g_usHEndPos < stModeInfo.IHWidth && (stModeInfo.IHTotal - stModeUserData.Clock) == 4))
    {
        maxval = stModeUserData.Clock; // Backup the currect clcok to maxval

        if(stModeInfo.IHTotal >= stModeUserCenterData.CenterClock)
        {
            stModeUserData.Clock = stModeInfo.IHTotal;
        }
        else
        {
            stModeUserData.Clock = stModeUserCenterData.CenterClock;
        }

        if(CAutoCheckClock(stModeUserData.Clock) == _FALSE)
        {
            if(CAutoCheckClock(g_usAdcClockLimit) == _FALSE)
            {
                stModeUserData.Clock = maxval; // Backup the currect clcok to maxval
                return _ERROR_ABORT;
            }
            else
            {
                stModeUserData.Clock = g_usAdcClockLimit;
            }
        }

        CAdjustAdcClock(stModeUserData.Clock);

        result = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);

        if(result != _ERROR_SUCCESS)
        {
            return result;
        }

        g_usHEndPos = g_usHEndPos + 1 - g_usHStartPos;
    }

#endif // (_AUTO_CLOCK_MOIRE_SMEAR_EFFECT == _ON)

    // V012 Modify 20100331 Start
    // V012 Patch Note (30) : Use mode search incorrect flag to skip SOD clock seeking in the auto stage to avoid one missing vertical line at the edge of the picture.
    if(g_bModeSearchIncorrectFlag == _TRUE)
    {
        return _ERROR_SUCCESS;
    }
    // V012 Modify 20100331 Start

#if(_AUTO_CLOCK_PRECISION < 4)

    // V016 VGA Patch Note (9) Modify 20100813 Start
    // Patch Reason : Modify the fine tune clock to avoid out of the srceen issue.
    /*
    // V012 Modify 20100323 Start
    // V012 Patch Note (5) : Auto function modifications.
    result = 0;

    // To avoid SOD clock seeking, there are curtain conditions must both be met:
    // (1). there are mutiple modes with different width but the same height;
    // (2). adjusted clock with satisfied width goes out of the specified clock range.
    // This modification is for the issue:
    // Mode: 1152x864@70Hz of nVidia graphic card
    // IHTotal = 1536; IHWidth = 1152; HSyncWidth = 120; HBP = 192;
    // IVTotal = 900; IVHeight = 864; VSyncWidth = 3; VBP = 32;
    // This mode happens to be quite different with our mode 42 in the mode table.
    // Consider the fact that 864 has only one kind of width ( 1152 ) in the mode table,
    // I add this condition to force SOD clock seeking for such modes.

    // Check if current mode has unique width in the mode table to decide whether SOD is worth doing (Condition 1).
    for(stop = 0; stop < _MAX_PRESET_MODE; stop++)
    {
        if((tINPUTMODE_PRESET_TABLE[stop].IVHeight == stModeInfo.IVHeight)
        && (tINPUTMODE_PRESET_TABLE[stop].IHWidth != stModeInfo.IHWidth))
        {
            result = 1; // Found different width but same height mode.
            break; // No need to seek any more.
        }
    }

    /////////////////////////////////////////////////////////////////////
    // We consider the difference 4 pixel images of non-full frame     //
    //                                                                 //
    //      stModeInfo.Width - 4       stModeInfo.Width                //
    //     ---------------------- = ---------------------              //
    //      stModeInfo.IHTotal       stModeUserData.Clock              //
    //                                                                 //
    /////////////////////////////////////////////////////////////////////
    if((result == 1)
    && (abs(stModeUserData.Clock - stModeInfo.IHTotal) > ((stModeInfo.IHTotal * _AUTO_CLOCK_SOD_TRIGGER_TRESH  + (stModeInfo.IHWidth - _AUTO_CLOCK_SOD_TRIGGER_TRESH) / 2) / (stModeInfo.IHWidth - _AUTO_CLOCK_SOD_TRIGGER_TRESH))))
    {
        return _ERROR_SUCCESS;
    }
    // V012 Modify 20100323 End
    */
    if(abs(stModeUserData.Clock - stModeInfo.IHTotal) > ((stModeInfo.IHTotal * _AUTO_CLOCK_SOD_TRIGGER_TRESH  + (stModeInfo.IHWidth - _AUTO_CLOCK_SOD_TRIGGER_TRESH) / 2) / (stModeInfo.IHWidth - _AUTO_CLOCK_SOD_TRIGGER_TRESH)))
    {
        return _ERROR_SUCCESS;
    }
    // V016 VGA Patch Note (9) Modify 20100813 End


    stModeUserData.Clock = (stModeUserData.Clock + 1) & ~_BIT0;
    stop = stModeUserData.Clock;

    // Set threshold for Clock Search
    CScalerSetByte(_DIFF_THRESHOLD_79, 0x18);

    count = stop;
    maxval = 0;
    result = 0;

    // Decide SOD effective threshold
    if(_COLOR_SELECT == _COLORS_ALL)
    {
        ulThreshold = ((DWORD)stModeInfo.IHWidth * stModeInfo.IVHeight * 3) << 3;
    }
    else
    {
        ulThreshold = ((DWORD)stModeInfo.IHWidth * stModeInfo.IVHeight) << 3;
    }

    // Direction determination
    for(delta = 0; delta < 3; delta++)
    {
        if(delta == 0)
        {
            stModeUserData.Clock = stop;
        }
        else if(delta == 1)
        {
            stModeUserData.Clock = stop - 2;

            if(CAutoCheckClock(stModeUserData.Clock) == _FALSE)
            {
                continue;
            }
        }
        else
        {
            stModeUserData.Clock = stop + 2;
        }

        CAdjustAdcClock(stModeUserData.Clock);

        ((DWORD *)pData)[3] = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_8, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART(0), &phase);


        if(((DWORD *)pData)[3] < ulThreshold)
        {
            ((DWORD *)pData)[3] = 0;
        }

        if(delta == 0)
        {
            maxval = ((DWORD *)pData)[3];
            result = delta;
            count = stModeUserData.Clock;
        }
        else
        {
            if(((DWORD *)pData)[3] > maxval)
            {
                maxval = ((DWORD *)pData)[3];
                result = delta;
                count = stModeUserData.Clock;

                // V012 Modify 20100323 Start
                // V012 Patch Note (5) : Auto function modifications.
                /*
                break;
                */
                // V012 Modify 20100323 End
            }
        }
    }

    // Further seeking
    if(result == 0)
    {
        count = stop;
    }
    else
    {
        for(delta = 0; delta < 2; delta++)
        {
            stModeUserData.Clock = (result == 1) ? (stop - 4 - delta * 2) : (stop + 4 + delta * 2);

            if(result == 1)
            {
                if(CAutoCheckClock(stModeUserData.Clock) == _FALSE)
                {
                    count = stop;
                    break;
                }
            }

            CAdjustAdcClock(stModeUserData.Clock);

            phase = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);

            if(phase != _ERROR_SUCCESS)
            {
                return phase;
            }

            ((DWORD *)pData)[3] = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_8, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART(0), &phase);

            g_usHEndPos = g_usHEndPos + 1 - g_usHStartPos;

            ((DWORD *)pData)[0] = abs(g_usHEndPos - stModeInfo.IHWidth);

            if(((DWORD *)pData)[0] < (4 * _AUTO_CLOCK_PRECISION))
            {
                if(((DWORD *)pData)[3] > maxval)
                {
                    count = stModeUserData.Clock;
                    maxval = ((DWORD *)pData)[3];
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    stModeUserData.Clock = count;

    CAdjustAdcClock(stModeUserData.Clock);

#endif  // End of #if(_AUTO_CLOCK_PRECISION < 4)

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto phase process
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoDoAutoPhase(void)
{
    BYTE  result = 0, phase = 0, best = 0;
    DWORD maxsum = 0, temp0 = 0, temp1 = 0, temp2 = 0;

    result = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);
    if(_ERROR_SUCCESS != result)
    {
        return result;
    }

    CScalerSetByte(_DIFF_THRESHOLD_79, 0x80);

    temp0 = 0;

    maxsum = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_8, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART(0), &result);

    if(maxsum == 0xffffffffL)
    {
        return _ERROR_INPUT;
    }

    if(maxsum == 0)
    {
        return _ERROR_ABORT;
    }

    if(maxsum < ((DWORD)stModeInfo.IVHeight * 1024 * 3 / 4))
    {
        // Decrease threshold to 0x40 for Phase Search
        CScalerSetByte(_DIFF_THRESHOLD_79, 0x40);

        maxsum = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_8, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART(0), &result);

        if(maxsum == 0xffffffffL)
        {
            return _ERROR_INPUT;
        }

        if(maxsum == 0)
        {
            return _ERROR_ABORT;
        }

        if(maxsum < ((DWORD)stModeInfo.IVHeight * 1024 * 3 / 4))
        {
            return _ERROR_PHASE;
        }
    }

    phase = (result - 12) & 0x3f;
    maxsum = 0;
    best = (result + 8) & 0x3f;

    do
    {
        phase = (phase + 4) & 0x3f;
        CAdjustPhase(phase);

        if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))
        {
            return _ERROR_INPUT;
        }

        if(((DWORD *)pData)[0] > maxsum)
        {
            maxsum = ((DWORD *)pData)[0];
            result = phase & 0x3f;
        }
    }
    while(phase != best);

    if(maxsum == 0)
    {
        return _ERROR_ABORT;
    }

    phase = (result - 4) & 0x3f;
    best = 0;


    // Issac:
    // Please do not delete these backup code below.
/*
    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530)
    {
        BYTE  count, ucSelStep, ucSelColor;

        CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);

        ucSelStep   = (0x01 << _HWAUTO_STEP_2);
        count       = ((result - 8) & 0x3f);
        ucSelColor  = count + (8 * ucSelStep);
        maxsum      = 0;
        best        = 0;

        do
        {
            CAdjustPhase(count);

            if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))   return _ERROR_INPUT;

            if(((DWORD *)pData)[0] > maxsum)
            {
                maxsum  = ((DWORD *)pData)[0];
                best    = count;
            }

            count += ucSelStep;
        }
        while(count < ucSelColor);

        CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);

        result = best & 0x3f;
    }
    else
    {
        maxsum  = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_2, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART((result - 8) & 0x3f), &result);

        if(maxsum == 0xffffffffL)
        {
            return _ERROR_INPUT;
        }

        if(maxsum == 0)
        {
            return _ERROR_ABORT;
        }
    }
*/

    CAdjustPhase(phase);

    if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))
    {
        return _ERROR_INPUT;
    }

    // V012 Modify 20100323 Start
    // V012 Patch Note (5) : Auto function modifications.
    /*
    temp0 = ((DWORD *)pData)[0];
    */
    // ">> 2" for avoid variable overflow caused by too large SOD.
    temp0 = ((DWORD *)pData)[0] >> 2;
    // V012 Modify 20100323 End

    phase = phase + 1;
    CAdjustPhase(phase);

    if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))
    {
        return _ERROR_INPUT;
    }

    // V012 Modify 20100323 Start
    // V012 Patch Note (5) : Auto function modifications.
    /*
    temp1 = ((DWORD *)pData)[0];
    */
    // ">> 2" for avoid variable overflow caused by too large SOD.
    temp1 = ((DWORD *)pData)[0] >> 2;
    // V012 Modify 20100323 End

    result = (result + 4) & 0x3f;

    maxsum = 0;

    do
    {
        phase = (phase + 1) & 0x3f;
        CAdjustPhase(phase);

        if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))
        {
            return _ERROR_INPUT;
        }

        // V012 Modify 20100323 Start
        // V012 Patch Note (5) : Auto function modifications.
        /*
        temp2   = ((DWORD *)pData)[0];

        // Search phase by weighting SOD
        ((DWORD *)pData)[0] = temp2 + temp1 + temp0
                              - ((temp1 > temp0 ? temp1 - temp0 : temp0 - temp1) / 2)
                              - ((temp1 > temp2 ? temp1 - temp2 : temp2 - temp1) / 2);

        if(((DWORD *)pData)[0] > maxsum)
        {
            maxsum  = ((DWORD *)pData)[0];
            best    = (phase - 1) & 0x3f;
        }
        */
        // ">> 2" for avoid variable overflow caused by too large SOD.
        temp2 = ((DWORD *)pData)[0] >> 2;

        // Search phase by weighting SOD
        ((DWORD *)pData)[0] = temp2 + temp1 + temp0- (labs(temp1 - temp0) + labs(temp1 - temp2)) / 2;

        if(((DWORD *)pData)[0] > maxsum)
        {
            maxsum = ((DWORD *)pData)[0];
            best = (phase - 1) & 0x3f;
        }
        // V012 Modify 20100323 End

        temp0 = temp1;
        temp1 = temp2;
    }
    while(phase != result);

    stModeUserData.Phase = best;
    CAdjustPhase(stModeUserData.Phase);

    // V016 VGA Patch Note (9) Modify 20100813 Start
    // Patch Reason : Modify the fine tune clock to avoid out of the srceen issue.
    best = 2;

    do
    {
        CAutoMeasurePositionH(_MIN_NOISE_MARGIN);
        temp0 = (WORD)(g_usHEndPos + 1 - g_usHStartPos);

        if(temp0 > (stModeInfo.IHWidth + 1))
        {
            stModeUserData.Clock = ((DWORD)stModeUserData.Clock * stModeInfo.IHWidth + (temp0 / 2)) / temp0;
            CAdjustAdcClock(stModeUserData.Clock);
        }
        else
        {
            break;
        }
    }
    while(best--);
    // V016 VGA Patch Note (9) Modify 20100813 End

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto position process
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoDoAutoPosition(void)
{
    BYTE result = 0;
    SWORD dtemp = 0, ctemp = 0, atemp = 0;

    result = CAutoMeasurePositionV(_MIN_NOISE_MARGIN);
    if(_ERROR_SUCCESS != result)
    {
        return result;
    }

    result = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);
    if(_ERROR_SUCCESS != result)
    {
        return result;
    }

    /////////////////////////////////
    // Calculate Vertical Position //
    /////////////////////////////////
    CScalerRead(_IPV_ACT_STA_H_18, 2, pData, _AUTOINC);

#if(_SCALER_TYPE == _RTD2472D)
    ctemp = (((WORD)(pData[0] & 0x07)) << 8) | pData[1];
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    ctemp = (((WORD)(pData[0] & 0x0F)) << 8) | pData[1];
#else
    No Setting !!
#endif

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
    ctemp -= g_ucOverScanV;
#endif
// V012 Modify 20100316 End

    CScalerRead(_IVS_DELAY_1C, 1, pData, _AUTOINC);
    CScalerRead(_VGIP_HV_DELAY_1E, 1, &pData[1], _AUTOINC);
    dtemp = (((WORD)(pData[1] & _BIT1)) << 8) | pData[0];
    dtemp = g_usVStartPos - dtemp;
    atemp = (stModeInfo.IVHeight - (g_usVEndPos - g_usVStartPos + 1));

    if(atemp > 3)
    {
        atemp = abs(g_usVEndPos - g_usVStartPos + 1 - stModeInfo.IVHeight) / 2;
    }
    else
    {
        atemp = 0;
    }

    if(abs(stModeUserData.VPosition - (ctemp - dtemp) - stModeInfo.IVStartPos - atemp) <= g_ucVStartBias)
    {
        stModeUserData.VPosition -= ctemp - dtemp + atemp;
    }
    else if(abs(stModeUserData.VPosition - (ctemp - dtemp) - stModeInfo.IVStartPos + 0) <= g_ucVStartBias)
    {
        stModeUserData.VPosition -= ctemp - dtemp + 0;
    }
    else if((abs(stModeInfo.IVHeight - (g_usVEndPos - g_usVStartPos + 1)) < 2) && ((g_usVStartPos + stModeInfo.IVHeight) <= stModeInfo.IVTotal))
    {
        stModeUserData.VPosition -= ctemp - dtemp + atemp;
    }
    else
    {
        stModeUserData.VPosition = stModeInfo.IVStartPos;
    }

// V012 Modify 20100317 Start
// V012 Patch Note (9) : Remove safe mode.
// Remove save mode on purpose, as there're still some issue with it.
/*
#if(_SAFE_MODE == _ON)
    if (stModeInfo.ModeCurr == _MODE_720x400_70HZ || stModeInfo.ModeCurr == _MODE_640x350_70HZ)
    {
        stModeUserData.VPosition = stModeInfo.IVStartPos - g_ucVStartBias;
    }
#endif
*/
// V012 Modify 20100317 End

    CAdjustVPosition();


    ///////////////////////////////////
    // Calculate Horizontal Position //
    ///////////////////////////////////

    for(dtemp = 0; dtemp < 5; dtemp++)
    {
        switch(dtemp)
        {
            case 0: // Cancel Position Case
                if(g_usHStartPos <= (_IHS_CAPTURE_START * 2)) // Check if start position is lower than minimum value
                {
                    stModeUserData.HPosition = stModeUserCenterData.CenterHPos;
                    result = _ERROR_FINISH;
                }
                else
                {
                    continue;
                }

                break;

            case 1: // Left Position Case
                if(((DWORD)(g_usHEndPos + 1 - g_usHStartPos) * 100 / stModeUserData.Clock >= ((DWORD)stModeInfo.IHWidth * _AUTO_CLOCK_RANGE / stModeInfo.IHTotal))
                   || ((g_usHStartPos <= (stModeUserCenterData.CenterHPos + (WORD)((DWORD)(stModeInfo.IHWidth) * _ACTIVE_REGION_PERCENTAGE_THD / 100)))
                   && ((DWORD)(g_usHEndPos + 1 - g_usHStartPos) * 100 / stModeUserData.Clock < ((DWORD)stModeInfo.IHWidth * _AUTO_POSITION_CENTER_H_RANGE / stModeInfo.IHTotal))))
                {
                    stModeUserData.HPosition = g_usHStartPos;
                    result = _ERROR_SUCCESS;
                }
                else
                {
                    continue;
                }

                break;

            case 2: // Right Position Case
                if((g_usHEndPos >= (stModeUserCenterData.CenterHPos + stModeInfo.IHWidth - (WORD)((DWORD)(stModeInfo.IHWidth) * _ACTIVE_REGION_PERCENTAGE_THD / 100)))
                   && ((DWORD)(g_usHEndPos + 1 - g_usHStartPos) * 100 / stModeUserData.Clock < ((DWORD)stModeInfo.IHWidth * _AUTO_POSITION_CENTER_H_RANGE / stModeInfo.IHTotal)))
                {
                    stModeUserData.HPosition = (g_usHEndPos > stModeInfo.IHWidth - 1) ? (g_usHEndPos - stModeInfo.IHWidth + 1) : (_IHS_CAPTURE_START * 2);
                    result = _ERROR_SUCCESS;
                }
                else
                {
                    continue;
                }

                break;

            case 3: // Center Position Case
                if(((DWORD)(g_usHEndPos + 1 - g_usHStartPos) * 100 / stModeUserData.Clock >= ((DWORD)stModeInfo.IHWidth * _AUTO_POSITION_CENTER_H_RANGE / stModeInfo.IHTotal))
                   && ((DWORD)(g_usHEndPos + 1 - g_usHStartPos) * 100 / stModeUserData.Clock < ((DWORD)stModeInfo.IHWidth * _AUTO_CLOCK_RANGE / stModeInfo.IHTotal))
                   && ((DWORD)(g_usVEndPos + 1 - g_usVStartPos) * 100 > (DWORD)stModeInfo.IVHeight * _AUTO_POSITION_CENTER_V_RANGE))
                {
                    stModeUserData.HPosition = (g_usHStartPos > ((stModeInfo.IHWidth - (g_usHEndPos + 1 - g_usHStartPos)) / 2)) ? (g_usHStartPos - ((stModeInfo.IHWidth - (g_usHEndPos + 1 - g_usHStartPos)) / 2)) : (_IHS_CAPTURE_START * 2);
                    result = _ERROR_SUCCESS;
                }
                else
                {
                    continue;
                }

                break;

            default:
                stModeUserData.HPosition = stModeUserCenterData.CenterHPos;
                result = _ERROR_FINISH;
                break;
        }

        if(CAutoCheckCaptureStart(stModeUserData.HPosition, stModeUserData.Clock) == _TRUE)
        {
            break;
        }
        else if(dtemp == 0)
        {
            return _ERROR_ABORT;
        }
    }

    if(dtemp >= 5)
    {
        return _ERROR_ABORT;
    }

    if(result == _ERROR_SUCCESS)
    {
        stModeUserCenterData.CenterHPos = stModeUserData.HPosition;
    }

    g_bAutoPositionH = 1;

    CAdjustHPosition();

    g_bAutoPositionH = 0;

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto Fail Count Process Function
// Input Value  : Auto Result
// Output Value : None
//--------------------------------------------------
void CAutoFailCountProc(BYTE ucResult)
{
    // V013 VGA Patch Note (12) Modify 20100416 Start
    // Patch Reason : Fix unnecessary auto fail count saving, and CAutoDoAutoConfig return value as well.
    /*
    if((ucResult == _ERROR_ABORT) && (GET_AUTO_FAIL_COUNT() < (_MAX_AUTO_FAIL_COUNT - 1)))
    {
        INC_AUTO_FAIL_COUNT();
    }
    else
    {
        SET_AUTO_FLAG();
        CLR_AUTO_FAIL_COUNT();
    }

    // Save stModeUserData
    CEepromSaveModeData(stModeInfo.ModeCurr);
    */
    if(ucResult == _ERROR_SUCCESS)
    {
        if(GET_AUTO_FLAG() == _FALSE)
        {
            SET_AUTO_FLAG();

            // Modify data saving procedure to make sure the data is saved
            // even if last auto adjustment is successful.
        }

        // Modify data saving procedure to make sure the data is saved
        // even if last auto adjustment is successful.
        CLR_AUTO_FAIL_COUNT();
        CEepromSaveModeData(stModeInfo.ModeCurr);
    }
    else
    {
        if(GET_AUTO_FAIL_COUNT() == (_MAX_AUTO_FAIL_COUNT - 1))
        {
            SET_AUTO_FLAG();
            CLR_AUTO_FAIL_COUNT();
        }
        else
        {
            INC_AUTO_FAIL_COUNT();
        }

        CEepromSaveModeData(stModeInfo.ModeCurr);
    }
    // V013 VGA Patch Note (12) Modify 20100416 End
}

//--------------------------------------------------
// Description  : Tune ADC gain and offset
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoTuneBalance(void)
{
    BYTE rev = 0, result0 = 0, result1 = 0, color = 0, count = 0;
    bit flag = 1;

    // V012 Modify 20100317 Start
    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
    BYTE ucMeasureColorMax = 0;
    BYTE ucMeasureColorMin = 0;
    // V012 Modify 20100317 End

    for(count = 0; count < 3; count++)
    {
        stAdcData.AdcGain[count] = _ADJUST_GAIN_DEFAULT_VALUE;
        stAdcData.AdcOffset[count] = _ADJUST_OFFSET_DEFAULT_VALUE;
    }

    CAdjustAdcGainOffset();

    // V012 Modify 20100317 Start
    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
    /*
    rev = CAutoMeasurePositionV(_MIN_NOISE_MARGIN);
    if(rev != _ERROR_SUCCESS)
    {
        return rev;
    }

    rev = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);
    if(rev != _ERROR_SUCCESS)
    {
        return rev;
    }
    */
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        rev = CAutoMeasurePositionV(_MIN_NOISE_MARGIN);

	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage(" rev 1 ", rev);
	#endif
        if(rev != _ERROR_SUCCESS)
        {
	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage(" rev 2", rev);
	#endif
            return rev;
        }

        rev = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);
	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage(" rev 3", rev);
	#endif
        if(rev != _ERROR_SUCCESS)
        {
	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage(" rev 4", rev);
	#endif
		
            return rev;
        }
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        g_usHStartPos = stModeInfo.IHStartPos;
        g_usHEndPos = g_usHStartPos + stModeInfo.IHWidth;
        g_usVStartPos = stModeInfo.IVStartPos;
        g_usVEndPos = g_usVStartPos + stModeInfo.IVHeight;
    }
#endif
    else
    {
        return _ERROR_ABORT;
    }
    // V012 Modify 20100317 End

    if(CAutoMeasureColor(_BLUE, _MEASURE_COLORS_MAX, &rev) != _ERROR_SUCCESS)
    {
    	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage(" CAutoMeasureColor 1", rev);
	#endif

        return _ERROR_ABORT;
    }

    if(rev < 0x60)
    {
    	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage(" CAutoMeasureColor1 <0x60 ", rev);
	#endif

	
        return _ERROR_ABORT;
    }

    if(CAutoMeasureColor(_GREEN, _MEASURE_COLORS_MAX, &rev) != _ERROR_SUCCESS)
    {

	    	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage(" CAutoMeasureColor 2", rev);
	#endif

        return _ERROR_ABORT;
    }

    if(rev < 0x60)
    {
    	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage(" CAutoMeasureColor2 <0x60 ", rev);
	#endif
        return _ERROR_ABORT;
    }

    if(CAutoMeasureColor(_RED, _MEASURE_COLORS_MAX, &rev) != _ERROR_SUCCESS)
    {

	    	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage(" CAutoMeasureColor 3", rev);
	#endif
        return _ERROR_ABORT;
    }

    if(rev < 0x60)
    {
    	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage(" CAutoMeasureColor3 <0x60 ", rev);
	#endif
        return _ERROR_ABORT;
    }

    g_ucAdcPGA = 8;

    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_RGB_CTRL_CE, 0x0F, (g_ucAdcPGA << 4) & 0xF0);
    CTimerDelayXms(1);
    color = _BLUE;

    // V012 Modify 20100317 Start
    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        ucMeasureColorMax = _WHITEBALANCE_MAX_LEVEL; // 250
        ucMeasureColorMin = _WHITEBALANCE_MIN_LEVEL; // 2
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        ucMeasureColorMax = _WHITEBALANCE_PBPR_MAX_LEVEL; // 240
        ucMeasureColorMin = _WHITEBALANCE_PBPR_MIN_LEVEL; // 128
    }
#endif
    else
    {
        return _ERROR_ABORT;
    }
    // V012 Modify 20100317 End

    while(flag)
    {
        count = 0x30;

        do
        {
            rev = CAutoTuneAdcGain(color, &result0);
    	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage("  rev =  CAutoTuneAdcGain   ", rev);
	#endif
            if(rev == _ERROR_ABORT)
            {
                return rev;
            }

            if(rev == _ERROR_FINISH)
            {
                break;
            }

// V012 Modify 20100317 Start
// V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
/*

#if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW)

            if(result0 == _WHITEBALANCE_MAX_LEVEL)
            {
                break;
            }

             if((count > 8) && (result0 <= (_WHITEBALANCE_MAX_LEVEL + 1)) && (result0 >= (_WHITEBALANCE_MAX_LEVEL - 1)))
            {
                count = 8;
            }

#else
            rev = CAutoTuneAdcOffset(color, &result1);

            if(rev == _ERROR_ABORT)
            {
                return rev;
            }

            //YPbPr Auto Color Start

            if((result0 == _WHITEBALANCE_MAX_LEVEL) && (result1 == rev))
            {
                break;
            }

            if((count > 8) && (result0 <= (_WHITEBALANCE_MAX_LEVEL + 1)) && (result0 >= (_WHITEBALANCE_MAX_LEVEL - 1))
                && (result1 <= (rev + 1)) && (result1 >= (rev - 1)))
            {
                count = 8;
            }
            //YPbPr Auto Color End

#endif  // End of #if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW)
*/
#if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW)

            if(result0 == ucMeasureColorMax)
            {
                break;
            }

             if((count > 8) && (result0 <= (ucMeasureColorMax + 1)) && (result0 >= (ucMeasureColorMax - 1)))
            {
                count = 8;
            }

#else
            rev = CAutoTuneAdcOffset(color, &result1);

            if(rev == _ERROR_ABORT)
            {
                return rev;
            }

            if((result0 == ucMeasureColorMax) && (result1 == ucMeasureColorMin))
            {
                break;
            }

            if((count > 8) && (result0 <= (ucMeasureColorMax + 1)) && (result0 >= (ucMeasureColorMax - 1))
                && (result1 <= (ucMeasureColorMin + 1)) && (result1 >= (ucMeasureColorMin - 1)))
            {
                count = 8;
            }

#endif  // End of #if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW)
// V012 Modify 20100317 End

        }
        while(--count);

#if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW)
        if(stAdcData.AdcGain[color] > 230)
#elif(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_FW)
        if(stAdcData.AdcGain[color] > 240)
#endif
        {
            if(g_ucAdcPGA == 10)
            {
                if(color == _BLUE)
                {
                    color = _GREEN;

                    // V012 Modify 20100317 Start
                    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
                    #if(_YPBPR_SUPPORT == _ON)
                    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
                    {
                        ucMeasureColorMax = _WHITEBALANCE_Y_MAX_LEVEL; // 235
                        ucMeasureColorMin = _WHITEBALANCE_Y_MIN_LEVEL; // 16
                    }
                    #endif
                    // V012 Modify 20100317 End

                }
                else if(color == _GREEN)
                {
                    color = _RED;

                    // V012 Modify 20100317 Start
                    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
                    #if(_YPBPR_SUPPORT == _ON)
                    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
                    {
                        ucMeasureColorMax = _WHITEBALANCE_PBPR_MAX_LEVEL; // 240
                        ucMeasureColorMin = _WHITEBALANCE_PBPR_MIN_LEVEL; // 128
                    }
                    #endif
                    // V012 Modify 20100317 End
                }
                else
                {
                    flag = 0;
                }
            }
            else
            {
                color = _BLUE;
                g_ucAdcPGA = g_ucAdcPGA + 1;
            }

            CScalerPageSelect(_PAGE0);
            CScalerSetBit(_P0_ADC_RGB_CTRL_CE, 0x0F, (g_ucAdcPGA << 4) & 0xF0);
            CTimerDelayXms(1);
        }
#if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW)
        else if(stAdcData.AdcGain[color] < 40)
#elif(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_FW)
        else if(stAdcData.AdcGain[color] < 30)
#endif
        {
            if(g_ucAdcPGA == 6)
            {
                if(color == _BLUE)
                {
                    color = _GREEN;

                    // V012 Modify 20100317 Start
                    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
                    #if(_YPBPR_SUPPORT == _ON)
                    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
                    {
                        ucMeasureColorMax = _WHITEBALANCE_Y_MAX_LEVEL; // 235
                        ucMeasureColorMin = _WHITEBALANCE_Y_MIN_LEVEL; // 16
                    }
                    #endif
                    // V012 Modify 20100317 End
                }
                else if(color == _GREEN)
                {
                    color = _RED;

                    // V012 Modify 20100317 Start
                    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
                    #if(_YPBPR_SUPPORT == _ON)
                    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
                    {
                        ucMeasureColorMax = _WHITEBALANCE_PBPR_MAX_LEVEL; // 240
                        ucMeasureColorMin = _WHITEBALANCE_PBPR_MIN_LEVEL; // 128
                    }
                    #endif
                    // V012 Modify 20091210 End
                }
                else
                {
                    flag = 0;
                }
            }
            else
            {
                color = _BLUE;
                g_ucAdcPGA = g_ucAdcPGA - 1;
            }

            CScalerPageSelect(_PAGE0);
            CScalerSetBit(_P0_ADC_RGB_CTRL_CE, 0x0F, (g_ucAdcPGA << 4) & 0xF0);
            CTimerDelayXms(1);
        }
        else
        {
            if(color == _BLUE)
            {
                color = _GREEN;

                // V012 Modify 20100317 Start
                // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
                #if(_YPBPR_SUPPORT == _ON)
                if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
                {
                    ucMeasureColorMax = _WHITEBALANCE_Y_MAX_LEVEL; // 235
                    ucMeasureColorMin = _WHITEBALANCE_Y_MIN_LEVEL; // 16
                }
                #endif
                // V012 Modify 20100317 End
            }
            else if(color == _GREEN)
            {
                color = _RED;

                // V012 Modify 20100317 Start
                // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
                #if(_YPBPR_SUPPORT == _ON)
                if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
                {
                    ucMeasureColorMax = _WHITEBALANCE_PBPR_MAX_LEVEL; // 240
                    ucMeasureColorMin = _WHITEBALANCE_PBPR_MIN_LEVEL; // 128
                }
                #endif
                // V012 Modify 20100317 End
            }
            else
            {
                flag = 0;
            }
        }
    }

#if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW)
    count = ((_ADJUST_OFFSET_DEFAULT_VALUE / 14) + 1);

    do
    {
        if(CAutoAdjustAdcOffsetByHW() == _ERROR_SUCCESS)
        {
            break;
        }
        else if(count <= 1)
        {
            return _ERROR_ABORT;
        }
    }
    while(count--);

    if(CAutoAdjustAdcGainByFW() == _ERROR_ABORT)
    {
        return _ERROR_ABORT;
    }

#endif  // End of #if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW)

    if((stAdcData.AdcGain[_RED] == 0x00) || (stAdcData.AdcGain[_GREEN] == 0x00) || (stAdcData.AdcGain[_BLUE] == 0x00))
    {
        return _ERROR_ABORT;
    }
    else
    {
        return _ERROR_SUCCESS;
    }
}

//--------------------------------------------------
// Description  : Get max or min color value
// Input Value  : Measure information
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoMeasureColor(BYTE ucColor, BYTE ucPar, BYTE *pMargin)
{
    CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT2 | _BIT1 | _BIT0), (ucColor == 3) ? ucColor : ( 2 - ucColor));
    CScalerSetBit(_AUTO_ADJ_CTRL1_7D, ~_BIT0, 0x00);

    if(ucPar == _MEASURE_COLORS_MIN)
    {
        pData[0] = 0x12;
        pData[1] = 0x80;
        pData[2] = 0x00;
        pData[3] = 0x00;
        pData[4] = ((g_usVStartPos / 2) > 8) ? 8 : ((g_usVStartPos / 2) + 1);
        pData[5] = pData[4] + 1;
    }
    else
    {
#if(_SCALER_TYPE == _RTD2472D)
        pData[0] = ((g_usHStartPos >> 4) & 0x70) | (HIBYTE(g_usHEndPos) & 0x0f);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        pData[0] = ((g_usHStartPos >> 4) & 0xf0) | (HIBYTE(g_usHEndPos) & 0x0f);
#else
    No Setting !!
#endif //End of #if(_SCALER_TYPE == _RTD2472D)

        pData[1] = (LOBYTE(g_usHStartPos));
        pData[2] = (LOBYTE(g_usHEndPos));
        pData[3] = ((g_usVStartPos >> 4) & 0x70) | (HIBYTE(g_usVEndPos) & 0x0f);
        pData[4] = (LOBYTE(g_usVStartPos));
        pData[5] = (LOBYTE(g_usVEndPos));
    }

    CScalerWrite(_H_BOUNDARY_H_70, 6, pData, _AUTOINC);
    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x01 | ((ucPar & 0x01) << 5));

    pData[0] = CAutoWaitFinish();

    if(pData[0] != _ERROR_SUCCESS)
    {
        return pData[0];
    }

    CScalerRead(_AUTO_PHASE_0_87, 1, pMargin, _AUTOINC);

    if(ucPar == _MEASURE_COLORS_MIN)
    {
        *pMargin ^= 0xff;
    }

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Adjust ADC gain
// Input Value  : Adjusting setting
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoTuneAdcGain(BYTE ucColor, BYTE *pMargin)
{
    BYTE temp = 0;

    // V012 Modify 20100317 Start
    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
    BYTE ucMeasureColorMax = 0;
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        ucMeasureColorMax = _WHITEBALANCE_MAX_LEVEL; // 250
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        if(ucColor == _GREEN)
        {
            ucMeasureColorMax = _WHITEBALANCE_Y_MAX_LEVEL; // 235
        }
        else
        {
            ucMeasureColorMax = _WHITEBALANCE_PBPR_MAX_LEVEL; // 240
        }
    }
#endif
    else
    {
        return _ERROR_ABORT;
    }
    // V012 Modify 20100317 End


    if(CAutoMeasureColor(ucColor, _MEASURE_COLORS_MAX, pMargin) != _ERROR_SUCCESS)
    {
        return _ERROR_ABORT;
    }

    // V012 Modify 20100317 Start
    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
    /*
    if(*pMargin > _WHITEBALANCE_MAX_LEVEL)
    {
        temp = *pMargin - _WHITEBALANCE_MAX_LEVEL;
    */
    if(*pMargin > ucMeasureColorMax)
    {
        temp = *pMargin - ucMeasureColorMax;
    // V012 Modify 20100317 End

        // for ADC Input Range 0.25 ~ 1.25V Start Need to Confrim
        temp = (BYTE)((((WORD)temp * 7 + 3) / 10) & 0x00FF); // make auto more precisely.

        // Non-zero return value of Change_ADC_Gain() means ADC gain reaches maximum.
        if(CAutoChangeAdcGain(ucColor, temp, 0)) // Increase Gain; Decrease Contrast
        {
            if(CAutoChangeAdcOffset(ucColor, 4, 0)) // Increase Offset; Decrease Brightness
            {
                return _ERROR_FINISH;
            }
        }
    }

    // V012 Modify 20100317 Start
    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
    /*
    else if(*pMargin < _WHITEBALANCE_MAX_LEVEL)
    {
        temp = _WHITEBALANCE_MAX_LEVEL - *pMargin;
    */
    else if(*pMargin < ucMeasureColorMax)
    {
        temp = ucMeasureColorMax - *pMargin;
    // V012 Modify 20100317 End

        // for ADC Input Range 0.25 ~ 1.25V Start Need to Confrim
        temp = (BYTE)((((WORD)temp * 7 + 3) / 10) & 0x00FF); // make auto more precisely.

        // Non-zero return value of Change_ADC_Gain() means ADC gain reaches minimum.
        if(CAutoChangeAdcGain(ucColor, temp, 1)) // Decrease Gain; Increase Contrast
        {
            if(CAutoChangeAdcOffset(ucColor, 4, 1)) // Decrease Offset; Increase Brightness
            {
                return _ERROR_FINISH;
            }
        }
    }

    return _ERROR_SUCCESS;
}

#if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_FW)
//--------------------------------------------------
// Description  : Adjust ADC offset
// Input Value  : Adjusting setting
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoTuneAdcOffset(BYTE ucColor, BYTE *pMargin)
{
    BYTE temp = 0, level = 0;

// V012 Modify 20100317 Start
// V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
/*
#if(_YPBPR_SUPPORT == _ON)
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) && (ucColor != _GREEN))
    {
        level = _WHITEBALANCE_BR_MIN_LEVEL;
    }
    else
    {
        level = _WHITEBALANCE_MIN_LEVEL;
    }
#else
    level = _WHITEBALANCE_MIN_LEVEL;
#endif
*/
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        level = _WHITEBALANCE_MIN_LEVEL; // 2
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        if(ucColor == _GREEN)
        {
            level = _WHITEBALANCE_Y_MIN_LEVEL; // 16
        }
        else
        {
            level = _WHITEBALANCE_PBPR_MIN_LEVEL; // 128
        }
    }
#endif
    else
    {
        return _ERROR_ABORT;
    }
// V012 Modify 20100317 End

    if(CAutoMeasureColor(ucColor, _MEASURE_COLORS_MIN, pMargin) != _ERROR_SUCCESS)
    {
        return _ERROR_ABORT;
    }

    if(*pMargin > level)
    {
        temp = *pMargin - level;
        CAutoChangeAdcOffset(ucColor, ((temp > 8) ? 8 : temp), 0); // Increase Offset; Decrease Brightness
    }
    else if(*pMargin < level)
    {
        temp = level - *pMargin;

#if(_YPBPR_SUPPORT == _ON)
        if((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) && (ucColor != _GREEN))
        {
            CAutoChangeAdcOffset(ucColor, ((temp > 8) ? 8 : temp), 1);
        }
        else
        {
            if(*pMargin == 0)
            {
                CAutoChangeAdcOffset(ucColor, temp + 4, 1); // Decrease Offset; Increase Brightness
            }
            else
            {
                CAutoChangeAdcOffset(ucColor, temp, 1);     // Decrease Offset; Increase Brightness
            }
        }
#else
        if(*pMargin == 0)
        {
            CAutoChangeAdcOffset(ucColor, temp + 4, 1); // Decrease Offset; Increase Brightness
        }
        else
        {
            CAutoChangeAdcOffset(ucColor, temp, 1);     // Decrease Offset; Increase Brightness
        }
#endif
    }

    return _ERROR_SUCCESS;
}
#endif  // End of #if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_FW)

//--------------------------------------------------
// Description  : Change ADC gain
// Input Value  : Input information
// Output Value : Return 1 if overrange
//--------------------------------------------------
BYTE CAutoChangeAdcGain(BYTE ucColor, BYTE ucDelta, BYTE ucInc)
{
    BYTE overrange = 0;

    if(ucInc)
    {
        if(stAdcData.AdcGain[ucColor] >= ucDelta)
        {
            stAdcData.AdcGain[ucColor] -= ucDelta;
        }
        else
        {
            stAdcData.AdcGain[ucColor] = 0;
            overrange = 1;
        }
    }
    else
    {
        if((0xff - ucDelta) >= stAdcData.AdcGain[ucColor])
        {
            stAdcData.AdcGain[ucColor] += ucDelta;
        }
        else
        {
            stAdcData.AdcGain[ucColor] = 0xff;
            overrange = 1;
        }
    }

    CAdjustAdcGain();

    return overrange;
}

//--------------------------------------------------
// Description  : Change ADC offset
// Input Value  : Input information
// Output Value : Return 1 if overrange
//--------------------------------------------------
BYTE CAutoChangeAdcOffset(BYTE ucColor, BYTE ucDelta, BYTE ucInc)
{
    BYTE overrange = 0;

    if(ucInc)
    {
        if(stAdcData.AdcOffset[ucColor] >= ucDelta)
        {
            stAdcData.AdcOffset[ucColor] -= ucDelta;
        }
        else
        {
            stAdcData.AdcOffset[ucColor] = 0;
            overrange = 1;
        }
    }
    else
    {
        if((0xff - ucDelta) >= stAdcData.AdcOffset[ucColor])
        {
            stAdcData.AdcOffset[ucColor] += ucDelta;
        }
        else
        {
            stAdcData.AdcOffset[ucColor] = 0xff;
            overrange = 1;
        }
    }
#if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("adjustAdcData", 0);
CDebugMessage("stAdcData.AdcGain.[_RED]",stAdcData.AdcGain[_RED]);
CDebugMessage("stAdcData.AdcGain.[_GREEN]",stAdcData.AdcGain[_GREEN]);
CDebugMessage("stAdcData.AdcGain.[_BLUE]",stAdcData.AdcGain[_BLUE]);

CDebugMessage("stAdcData.AdcOffset.[_RED]",stAdcData.AdcOffset[_RED]);
CDebugMessage("stAdcData.AdcOffset.[_GREEN]",stAdcData.AdcOffset[_GREEN]);
CDebugMessage("stAdcData.AdcOffset.[_BLUE]",stAdcData.AdcOffset[_BLUE]);





#endif
    CAdjustAdcOffset();

    return overrange;
}

#if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW)
//--------------------------------------------------
// Description  : H/W Auto Adjust ADC offset
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoAdjustAdcOffsetByHW(void)
{
    // Disable ABL
    CScalerSetBit(_P0_ABL_CTRL1_E2, ~_BIT0, 0x00);

    // Start position of ABL in each line
    // V012 Modify 20100317 Start
    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
    /*
    pData[13] = ((g_usHStartPos / 4) > 32) ? (g_usHStartPos / 4) : 32;
    */
    CScalerGetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, 0x01, 1, &pData[0], _NON_AUTOINC);
    CScalerGetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, 0x03, 1, &pData[1], _NON_AUTOINC);

    if(pData[1] > pData[0])
    {
        pData[0] = pData[1];
    }

    CScalerGetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, 0x06, 1, &pData[1], _NON_AUTOINC);

    if((pData[1] & _BIT6) == _BIT6)     // ADC Clamp Counter Unit: single pixels
    {
        (pData[0] >= 0xFF - _ABL_HSTART_AFTER_CLAMPPOS) ? (pData[13] = 0xFF) : (pData[13] = pData[0] + _ABL_HSTART_AFTER_CLAMPPOS);
    }
    else                                // ADC Clamp Counter Unit: double pixels
    {
        (pData[0] >= (0xFF - _ABL_HSTART_AFTER_CLAMPPOS) / 2) ? (pData[13] = 0xFF) : (pData[13] = pData[0] * 2 + _ABL_HSTART_AFTER_CLAMPPOS);
    }
    // V012 Modify 20100317 End

    // Start line of ABL after the leading edge of Vsync
    pData[14] = ((g_usVStartPos / 2) > 8) ? 8 : ((g_usVStartPos / 2) + 1);

    // The last line of ABL which is counted by double-line
    pData[15] = (pData[14] + 64);


    // ABL Setting
#if(_YPBPR_SUPPORT == _ON)
    pData[0] = (((((GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR) ? 1 : 0) << 7) | (0x03 << 4)) & 0xB0);
#else
    /*
    pData[0] = (((_OFF_LINE_ABL_MODE << 6) | (0x03 << 4)) & 0x30);
    */
    pData[0] = ((0x03 << 4) & 0x30);
#endif

    pData[1] = (pData[14] & 0x1F);

    // V012 Modify 20100317 Start
    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
    /*
    pData[2] = ((((_WHITEBALANCE_MIN_LEVEL - 1) & 0x03) << 4) & 0xF0);
    */
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        pData[2] = ((((_WHITEBALANCE_MIN_LEVEL - 1) & 0x0F) << 4) & 0xF0);
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        pData[2] = ((((_WHITEBALANCE_Y_MIN_LEVEL - 1)& 0x0F) << 4) & 0xF0);
    }
#endif
    else
    {
        return _ERROR_ABORT;
    }

    pData[3] = pData[15];
    pData[4] = pData[13];
    pData[5] = 0x30;

    // V013 VGA Patch Note (1) Modify 20100407 Start
    // Patch Reason : Modify ABL Function Equal Condition.
    /*
    pData[6] = (((_MEASURE_PIXELS_METHOD << 5) | (0x01 << 2) | (_EQUAL_MARGIN)) & 0x67);
    */
    pData[6] = (((_EQUAL_ONCE_REARCHTAR << 6) | (_MEASURE_PIXELS_METHOD << 5) | (0x01 << 2) | (_EQUAL_MARGIN)) & 0x67);
    // V013 VGA Patch Note (1) Modify 20100407 End

    CScalerPageSelect(_PAGE0);
    CScalerWrite(_P0_ABL_CTRL1_E2, 7, pData, _AUTOINC);

    // Enable ABL
    CScalerSetBit(_P0_ABL_CTRL1_E2, ~_BIT0, _BIT0);

    if(CTimerPollingFlagProc(255, _PAGE0, _P0_ABL_CTRL1_E2, _BIT0, 0))
    {
        if(CScalerGetBit(_P0_ABL_CTRL1_E2, _BIT3 | _BIT2 | _BIT1) == 0x0E)
        {
            CScalerRead(_P0_RED_OFFSET_C3, 3, &pData[7], _AUTOINC);

            stAdcData.AdcOffset[_RED] = pData[7];
            stAdcData.AdcOffset[_GREEN] = pData[8];
            stAdcData.AdcOffset[_BLUE] = pData[9];

            return _ERROR_SUCCESS;
        }
        else
        {
            return _ERROR_ABORT;
        }
    }
    else
    {
        return _ERROR_ABORT;
    }
}

//--------------------------------------------------
// Description  : Adjust ADC Gain after H/W Auto Adjust ADC offset
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoAdjustAdcGainByFW(void)
{
    BYTE rev = 0, count = 0, color = 0, result = 0;

    // V012 Modify 20100317 Start
    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
    /*
    for(color=_RED; color<=_BLUE; color++)
    {
        if(_WHITEBALANCE_MAX_LEVEL >= 255)
        {
            count = 25;
        }
        else
        {
            count = (25 / (255 - _WHITEBALANCE_MAX_LEVEL));
        }

        do
        {
            rev = CAutoTuneAdcGain(color, &result);

            if(rev == _ERROR_ABORT)
            {
                return _ERROR_ABORT;
            }

            if(rev == _ERROR_FINISH)
            {
                break;
            }

            if(result == _WHITEBALANCE_MAX_LEVEL)
            {
                break;
            }
        }
        while(count--);
    }
    */
    BYTE ucMeasureColorMax = 0;

    for(color = _RED; color <= _BLUE; color++)
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
        {
            ucMeasureColorMax = _WHITEBALANCE_MAX_LEVEL; // 250
        }
#if(_YPBPR_SUPPORT == _ON)
        else if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
        {
            if(color == _GREEN)
            {
                ucMeasureColorMax = _WHITEBALANCE_Y_MAX_LEVEL; // 235
            }
            else
            {
                ucMeasureColorMax = _WHITEBALANCE_PBPR_MAX_LEVEL; // 240
            }
        }
#endif
        else
        {
            return _ERROR_ABORT;
        }

        if(ucMeasureColorMax >= 255)
        {
            count = 25;
        }
        else
        {
            count = (25 / (255 - ucMeasureColorMax));
        }

        do
        {
            rev = CAutoTuneAdcGain(color, &result);

            if(rev == _ERROR_ABORT)
            {
                return _ERROR_ABORT;
            }

            if(rev == _ERROR_FINISH)
            {
                break;
            }

            if(result == ucMeasureColorMax)
            {
                break;
            }
        }
        while(count--);
    }
    // V012 Modify 20100317 End

    return _ERROR_SUCCESS;
}

#endif  // End of #if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW)

//--------------------------------------------------
// Description  : Check new clock
// Input Value  : Clock value
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit CAutoCheckClock(WORD usClock)
{
    if((g_usCaptureStart + stModeInfo.IHWidth + _CAPTURE_HDELAY) <= usClock)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check new capture start
// Input Value  : Clock value
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit CAutoCheckCaptureStart(WORD usHPos, WORD usClock)
{
    // Cal H Capture Start as AdjustPhase
    if(usHPos < (_IHS_START_BIAS * 4))
    {
        ((WORD *)pData)[5] = usHPos / 2 + (usHPos % 2);
    }
    else
    {
        ((WORD *)pData)[5] = (usHPos - (_IHS_START_BIAS * 2)) - 2;
    }

    if((((WORD *)pData)[5] + stModeInfo.IHWidth + _CAPTURE_HDELAY) <= usClock)
    {
        return _TRUE;
    }

    return _FALSE;
}

#endif  // End of #if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)


