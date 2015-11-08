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
// ID Code      : FrameSync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __FRAMESYNC__

#include "Common\Header\Include.h"
#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

//--------------------------------------------------
// Description  : Detect frame sync status
// Input Value  : None
// Output Value : Return _FALSE if frame sync is ok, _TRUE while PLL mislock, buffer underflow/overflow
//--------------------------------------------------
bit CFrameSyncDetect(void)
{
    if(GET_POWERSTATUS() && GET_MODESTABLE())
    {
        CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);

        if((pData[0] & 0x63) == 0)
        {

#if(_YPBPR_SUPPORT == _ON)
            if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
            {
                return _FALSE;
            }
#endif

// APLL miss-lock must be checked even in FRC mode
#if(_FRC_SUPPORT == _ON)
            if(((pData[0] & 0x03) == 0) || GET_FRCSTATUS())
#endif
            {
                return _FALSE;
            }
        }
    }

    CLR_FRAMESYNCSTATUS();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Finetune last line problem
// Input Value  : Dclk offset
// Output Value : Return _TRUE if there is no timing change
//--------------------------------------------------
bit CFrameSyncLastLineFinetune(WORD *pDelta)
{
#if(_LAST_LINE_FINETUNE == _LAST_LINE_METHOD_NONE)

    if(CFrameSyncTestSync(*pDelta))
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }

#endif

#if(_LAST_LINE_FINETUNE == _LAST_LINE_METHOD_0)

    // Formula: Tne DEN End to DEN Start Length must be (1280*N)
    // CPT's Panels.

    WORD dvtotal;
    DWORD dclktotal = 0;

    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_NEW_DV_CTRL_22, 0x00);

    CScalerSetByte(_LAST_LINE_H_44, 0x00);

    if(CFrameSyncTestSync(*pDelta))
    {
        return _FALSE;
    }

    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    dclktotal = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];

    CScalerSetByte(_LAST_LINE_H_44, 0x80);
    CTimerDelayXms(40);
    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    dvtotal = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];

    dclktotal = dclktotal + (DWORD)stDisplayInfo.DHTotal * (dvtotal + 1 - stDisplayInfo.DVHeight);

    dvtotal = dclktotal / 1280;
    dvtotal = dclktotal - ((DWORD)dvtotal * 1280);

    *pDelta = (dvtotal > (1280 - 128)) ? (*pDelta + 3) : ((dvtotal < 128) ? (*pDelta - 3) : *pDelta);

    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_NEW_DV_CTRL_22, 0xa0);

    return _TRUE;

#endif

#if(_LAST_LINE_FINETUNE == _LAST_LINE_METHOD_1)

    // Formula: Tne DEN End to DEN Start Length must be (4096*N + 128)
    // Samsung's Panels.

    WORD dvtotal;
    DWORD dclktotal = 0;

    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_NEW_DV_CTRL_22, 0x00);

    CScalerSetByte(_LAST_LINE_H_44, 0x00);

    if(CFrameSyncTestSync(*pDelta))
    {
        return _FALSE;
    }

    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    dclktotal = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];

    CScalerSetByte(_LAST_LINE_H_44, 0x80);
    CTimerDelayXms(40);
    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    dvtotal = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];

    dclktotal = dclktotal + (DWORD)stDisplayInfo.DHTotal * (dvtotal + 1 - stDisplayInfo.DVHeight) - 128;

    dvtotal = dclktotal / 4096;
    dvtotal = dclktotal - ((DWORD)dvtotal * 4096);

    *pDelta = (dvtotal > (4096 - 128)) ? (*pDelta + 3) : ((dvtotal < 128) ? (*pDelta - 3) : *pDelta);

    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_NEW_DV_CTRL_22, 0xa0);

    return _TRUE;

#endif

#if(_LAST_LINE_FINETUNE == _LAST_LINE_METHOD_2)

    // Formula: Fixed to target last line pixels

    DWORD dclktotal;
    DWORD dclktarget;
    WORD dvtotal;
    WORD lastlinepixels;
    SWORD offsetnew;

    // Turn off new timing method
    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_NEW_DV_CTRL_22, 0x00);

    // Measure DVTotal
    CScalerSetByte(_LAST_LINE_H_44, 0x80);
    if(CFrameSyncTestSync(*pDelta))
    {
        return _FALSE;
    }
    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    dvtotal = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];

    // Measure last line clock numbers
    CScalerSetByte(_LAST_LINE_H_44, 0x00);
    if(CFrameSyncTestSync(*pDelta))
    {
        return _FALSE;
    }
    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    lastlinepixels = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];

    // Calculate total display clock numbers in a frame
    dclktotal = (DWORD)stDisplayInfo.DHTotal * dvtotal + lastlinepixels;

    // Calculate mininum path of target clock numbers
    if(lastlinepixels > _LAST_LINE_TARGET)
    {
        if((lastlinepixels - _LAST_LINE_TARGET) > (stDisplayInfo.DHTotal / 2))
        {
            dclktarget = (DWORD)stDisplayInfo.DHTotal * (dvtotal + 1) + _LAST_LINE_TARGET;  // +
        }
        else
        {
            dclktarget = (DWORD)stDisplayInfo.DHTotal * (dvtotal) + _LAST_LINE_TARGET;  // -
        }
    }
    else
    {
        if((_LAST_LINE_TARGET - lastlinepixels) > (stDisplayInfo.DHTotal / 2))
        {
            dclktarget = (DWORD)stDisplayInfo.DHTotal * (dvtotal - 1) + _LAST_LINE_TARGET;  // -
        }
        else
        {
            dclktarget = (DWORD)stDisplayInfo.DHTotal * (dvtotal) + _LAST_LINE_TARGET;  // +
        }
    }

    // Calculate and apply new offset
    offsetnew = (((SDWORD)dclktotal - (SDWORD)dclktarget) * ((SDWORD)32768 - (SDWORD)*pDelta)) * 2 / (SDWORD)dclktotal;
    offsetnew = (offsetnew / 2) + ((offsetnew > 0) ? (offsetnew & 0x01) : -(offsetnew & 0x01));
    offsetnew = offsetnew + *pDelta;
    if(CFrameSyncTestSync(offsetnew))
    {
        return _FALSE;
    }

    // Check underflow/overflow. If failed, try another side.
    if(pData[0])
    {
        if(pData[0] & 0x02)
        {
            dclktarget = dclktarget + stDisplayInfo.DHTotal;
        }
        else
        {
            dclktarget = dclktarget - stDisplayInfo.DHTotal;
        }

        offsetnew = (((SDWORD)dclktotal - (SDWORD)dclktarget) * ((SDWORD)32768 - (SDWORD)*pDelta)) * 2 / (SDWORD)dclktotal;
        offsetnew = (offsetnew / 2) + ((offsetnew > 0) ? (offsetnew & 0x01) : -(offsetnew & 0x01));
        offsetnew = offsetnew + *pDelta;
        if(CFrameSyncTestSync(offsetnew))
        {
            return _FALSE;
        }
    }

    *pDelta = offsetnew;

    return _TRUE;

#endif
}

//--------------------------------------------------
// Description  : Finetune Dclk offset for spread spectrum
// Input Value  : Dclk offset
// Output Value : Return _FALSE if there is no timing change
//--------------------------------------------------
BYTE CFrameSyncSpreadSpectrumFinetune(WORD *pDelta)
{
    // Enable the spread spectrum function
    CAdjustDclkSpreadSpectrumRange(_DCLK_SPREAD_RANGE);

    *pDelta = *pDelta + tDCLK_OFFSET[_DCLK_SPREAD_RANGE];

    if(CFrameSyncTestSync(*pDelta))
    {
        return 2;
    }

    if(pData[0])
    {
        // Fine-tune DCLK offset
        if(CFrameSyncTestSync((pData[0] & 0x02) ? (*pDelta - 1) : (*pDelta + 1)))
        {
            return 2;
        }

        if(pData[0] & 0x03)
        {
            return 1;   //Frame sync fail!
        }
    }

    return 0;
}

//--------------------------------------------------
// Description  : Calculate the suitable framesync point
// Input Value  : None
// Output Value : Return Dclk offset
//--------------------------------------------------
WORD CFrameSyncFastDo(void)
{
    DWORD aclkcnt = 0;
    DWORD offset;
    BYTE mcode, div;

    CScalerSetBit(_SYNC_SELECT_47, ~(_BIT1 | _BIT0), 0x00);
    CScalerSetBit(_STABLE_PERIOD_H_50, ~_BIT4, _BIT4);
    CAdjustSyncProcessorMeasureStart();

    // V016 System Patch Note (15) Modify 20100824 Start
    // Patch Reason : Fix IHCount=0 issue
    if(CScalerGetBit(_MEAS_HS_PERIOD_H_52, _BIT7) == _BIT7) // Auto Measure Enable
    {
        // We should wait 1 frame due to the measured result of next frame.
        if(CScalerGetBit(_SYNC_SELECT_47, _BIT1) == 0x00)   // Measure Input Active Region
        {
            CTimerWaitForEvent(_EVENT_IVS);
            CTimerWaitForEvent(_EVENT_IVS);
        }
        else         // Measure Display Active Region
        {
            CTimerWaitForEvent(_EVENT_DVS);
            CTimerWaitForEvent(_EVENT_DVS);
        }
    }
    // // V016 System Patch Note (15) Modify 20100824 End

    if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
    {
        CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT6, _BIT6);
        CScalerSetByte(_MEAS_ACTIVE_REGION_59, 0x00);

        pData[0] = 0;
        CScalerRead(_MEAS_ACTIVE_REGION_59, 3, &pData[1], _NON_AUTOINC);

        aclkcnt = ((DWORD *)pData)[0];

        // V016 System Patch Note (15) Modify 20100824 Start
        // Patch Reason : Fix IHCount=0 issue
        /*
        CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~(_BIT7 | _BIT5), 0x00);
        */
        // V016 System Patch Note (15) Modify 20100824 End

        CScalerPageSelect(_PAGE1);
        CScalerRead(_P1_DPLL_M_BF, 1, &mcode, _NON_AUTOINC);
        mcode += 2;

        CScalerRead(_P1_DPLL_N_C0, 1, &div, _NON_AUTOINC);
        div = 0x01 << ((div & 0x30) >> 4);

        offset = (DWORD)32768 * div * 2 * _DPLL_N_CODE * stDisplayInfo.DHTotal / aclkcnt * stDisplayInfo.DVHeight / mcode;

        offset = 32768 - offset;

//        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT1 | _BIT0), _BIT1);

    }
    else
    {
        offset = 0xffff;
    }

    CScalerSetBit(_STABLE_PERIOD_H_50, ~_BIT4, 0x00);
    return (WORD)offset;
}

//--------------------------------------------------
// Description  : Apply Dclk frequency and get the overflow/underflow information
// Input Value  : Dclk offset
// Output Value : Return _FALSE if there is no timing change
//--------------------------------------------------
bit CFrameSyncTestSync(WORD usOffset)
{
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_DVI) || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI))
    {
        CScalerPageSelect(_PAGE2);
        if(CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7) == _BIT7)
        {
            CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, _BIT0);  // Digital Mode Measure
        }
    }
    else
    {
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, 0x00);       // Analog Mode Measure
    }

    CAdjustSyncProcessorMeasureStart();

    // Apply Dclk frequency setting
    CAdjustDclkOffset(usOffset);

    CScalerSetByte(_STATUS0_02, 0x00);                      // Clear Status

    CTimerWaitForEvent(_EVENT_DVS);                         // Wait for Frame End

    CTimerWaitForEvent(_EVENT_DVS);                         // Wait for Frame End

    // Issac added for interlaced mode 2006-08-29
    CTimerWaitForEvent(_EVENT_DVS);                         // Wait for Frame End

    // V016 System Patch Note (15) Modify 20100824 Start
    // Patch Reason : Fix IHCount=0 issue
    /*
    if(CModeIsChange())
    {
        return _TRUE;
    }
    */
    if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
    {
        if(CModeIsChange())
        {
            return _TRUE;
        }
    }
    // V016 System Patch Note (15) Modify 20100824 End

    CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC); // Read status

    // Input timing changed
    if(((pData[0] & 0x20) == 0x20) || ((pData[0] & 0x40) == 0x40))
    {
        return _TRUE;
    }

    // Save underflow/overflow information into pData[0]
    pData[0] &= 0x03;

    return _FALSE;                                          // Success
}

//--------------------------------------------------
// Description  : Adjust Dclk offset to meet frame sync
// Input Value  : None
// Output Value : Return 0 if sucess
//--------------------------------------------------
BYTE CFrameSyncDo(void)
{
    WORD buffer, delta;
    BYTE fine, result = 0;

    // Read the DCLK offset
    CScalerPageSelect(_PAGE1);
    CScalerRead(_P1_DCLK_FINE_TUNE_OFFSET_MSB_C4, 2, pData, _AUTOINC);
    buffer = (((WORD)pData[0] & 0x0f) << 8) | pData[1];

    // Disable the Fixed DVTOTAL & Last Line Length Fucntion
    CScalerSetBit(_P1_EVEN_FIXED_LAST_LINE_CTRL_CA, ~_BIT1, 0x00);

    // Disable spread spectrum
    CAdjustDclkSpreadSpectrumRange(0);

    // Fast Framesync method
    delta = CFrameSyncFastDo();

    if(CFrameSyncTestSync(delta))
    {
        return 2;
    }

    if(pData[0] == 0)
    {
        result |= _BIT0;

        if(CFrameSyncTestSync(delta + _OFFSET_STEP))
        {
            return 2;
        }
        if(pData[0] == 0)
        {
            result |= _BIT1;
        }

        if(CFrameSyncTestSync(delta - _OFFSET_STEP))
        {
            return 2;
        }
        if(pData[0] == 0)
        {
            result |= _BIT2;
        }

        if(result == (_BIT0 | _BIT1))
        {
            delta += _OFFSET_STEP / 2;
        }
        else if(result == (_BIT0 | _BIT2))
        {
            delta -= _OFFSET_STEP / 2;
        }
    }

    if(result == 0)     // Fast search fail, do iteration search
    {
        // Apply Dclk frequency setting
        CAdjustDclkOffset(buffer);

        // Search first satisfied DCLK setting for frame-sync
        result = 0x00;
        fine = _SEARCH_TIME;
        do
        {
            if(CFrameSyncTestSync(buffer))
            {
                return 2;
            }

            if(pData[0] == 0)
            {
                break;
            }

            if(pData[0] & 0x02)
            {
                buffer -= (result & 0x01) ? (_OFFSET_STEP / 2) : _OFFSET_STEP;
            }
            else
            {
                buffer += (result & 0x02) ? (_OFFSET_STEP / 2) : _OFFSET_STEP;
            }

            result = pData[0];
        }
        while(--fine);

        if(fine == 0x00)
        {
            return 1;
        }

        // If default offset is OK....
        if(result == 0x00)
        {
            if(CFrameSyncTestSync(buffer + _OFFSET_STEP))
            {
                return 2;
            }
            result = pData[0] ? pData[0] : 0x01;
        }

        // Search most satisfied DCLK setting for frame-sync
        delta = buffer;
        fine = 4;
        do
        {
            WORD temp = (result & 0x01) ? delta + (_OFFSET_STEP / 2) : delta - (_OFFSET_STEP / 2);

            if(CFrameSyncTestSync(temp))
            {
                return 2;
            }

            if(pData[0])
            {
                break;
            }

            delta = temp;
        }
        while(--fine);

        delta = (buffer + delta) >> 1;
    }

    if(!CFrameSyncLastLineFinetune(&delta))
    {
        return 2;
    }

    result = CFrameSyncSpreadSpectrumFinetune(&delta);
    if(result != 0)
    {
        return result;
    }

    SET_FRAMESYNCSTATUS();

    return 0;
}

//--------------------------------------------------
// Description  : Modify Display Vertical Start Position
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void CFrameSyncModifyDVStartPos(bit enable)
{
    if(enable)
    {
        stDisplayInfo.DVStartPos = (DWORD)35 * 2 * stDisplayInfo.DVHeight / stModeInfo.IVHeight / 10;
        stDisplayInfo.DVStartPos = ((stDisplayInfo.DVStartPos >> 1) + (stDisplayInfo.DVStartPos & 0x01));
        if(stDisplayInfo.DVStartPos < 6)
        {
            stDisplayInfo.DVStartPos = 6;
        }
    }
    else
    {
        stDisplayInfo.DVStartPos = (LOBYTE(_PANEL_DV_START));
    }
}

#if((_TMDS_SUPPORT == _ON) || (_YPBPR_SUPPORT == _ON) || (_VIDEO_SUPPORT == _ON) )
//--------------------------------------------------
// Description  : Set Frame Sync Fine Tune for Even/Odd field
// Input Value  : Even field before or after odd filed
// Output Value : None
//--------------------------------------------------
void CFrameSyncFineTune(bit field)
{
    WORD ustemp;

    CScalerRead(_IV_DV_DELAY_CLK_ODD_41, LENGTH(1), pData, _NON_AUTOINC);
    ustemp = (WORD)pData[0] * 16 + 16;

    if(field)   // Even field before Odd field
    {
        if(ustemp > (stModeInfo.IHTotal / 2))
        {
            ustemp -= stModeInfo.IHTotal / 2;
            CScalerSetByte(_IV_DV_DELAY_CLK_EVEN_42, (ustemp - 16) / 16);
        }
        else
        {
            CScalerSetByte(_IPV_ACT_STA_L_19, CScalerGetBit(_IPV_ACT_STA_L_19, 0xff) + 1);
            ustemp += stModeInfo.IHTotal;
            CScalerSetByte(_IV_DV_DELAY_CLK_ODD_41, (ustemp - 16) / 16);
            ustemp -= stModeInfo.IHTotal / 2;
            CScalerSetByte(_IV_DV_DELAY_CLK_EVEN_42, (ustemp - 16) / 16);

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
            g_usCaptureStartV++;
#endif
// V012 Modify 20100316 End
        }
    }
    else    // Even field after Odd field
    {
        ustemp += stModeInfo.IHTotal / 2;
        CScalerSetByte(_IV_DV_DELAY_CLK_EVEN_42, ((ustemp + 8) / 16) - 1);
    }

    CScalerSetBit(_FS_DELAY_FINE_TUNING_43, ~(_BIT1), _BIT1);
}
#endif  // End of #if((_TMDS_SUPPORT == _ON) || (_YPBPR_SUPPORT == _ON) || (_VIDEO_SUPPORT == _ON) )

// V013 VGA Patch Note (16) Modify 20100422 Start
// Patch Reason : Add fineTune display position for VGA interlace mode.
//--------------------------------------------------
// Description  : Set Frame Sync Fine Tune for Even/Odd field For Analog
// Input Value  : Even field before or after odd filed
// Output Value : None
//--------------------------------------------------
void CFrameSyncAnalogFineTune(void)
{
    BYTE ucModeIndex = 0;

    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
        {
            ucModeIndex = stModeInfo.ModeCurr;
        }
        else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
        {
            CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);

            ucModeIndex = pData[(stModeInfo.ModeCurr % 4) * 4];
        }

        switch(ucModeIndex)
        {
            case _MODE_1440x480i_60HZ:
            case _MODE_1440x576i_50Hz:
            case _MODE_1920x1080i_50Hz:
            case _MODE_1920x1080i_50HZ_2:
            case _MODE_1920x1080i_60HZ:

                CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, _BIT7);
                CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT0, _BIT0);
                CFrameSyncFineTune(_ODD);
                break;

            default:
                break;
        }
    }
#if(_YPBPR_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        switch(stModeInfo.ModeCurr)
        {
            case _VIDEO_1440x576i_50HZ: // 576i
            case _VIDEO_1440x480i_60HZ: // 480i
            case _VIDEO_1920x1080i_50HZ: // 1080i 50Hz
            case _VIDEO_1920x1080i_60HZ: // 1080i 60Hz
            case _VIDEO_1920x1080i_50HZ_2: // 1080i 50Hz_2

                CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, _BIT7);
                CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT0, _BIT0);
                CFrameSyncFineTune(_ODD);
                break;

            default:
                break;
        }
    }
#endif
}
// V013 VGA Patch Note (16) Modify 20100422 End

#endif  // End of #if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)


