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
// ID Code      : Video.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __VIDEO__

#include "Common\Header\Include.h"

#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

#if(_VIDEO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Video initialize
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CVideoInitial(void)
{
    CI2cWrite(NVRAM_LINE,_VIDEO_DEVICE, ADDRESS(0x00), sizeof(tVIDEO_TABLE_INITIAL_SAA7114), tVIDEO_TABLE_INITIAL_SAA7114);
}

//--------------------------------------------------
// Description  : Check if color locked
// Input Value  : ucColorStandard --> Color standard
// Output Value : Return _TRUE if color is locked, otherwise _FALSE
//--------------------------------------------------
bit CVideoIsColorLocked(BYTE ucColorStandard)
{
    BYTE temp;

    temp = 0x09 | ((ucColorStandard & 0x07) << 4);
    CI2cWrite(NVRAM_LINE,_VIDEO_DEVICE, ADDRESS(0x0E), LENGTH(1), &temp);
    CTimerDelayXms(60);
    CI2cRead(NVRAM_LINE,_VIDEO_DEVICE, ADDRESS(0x1F), LENGTH(1), &pData);

    if((temp & _BIT0) == _BIT0)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Polling to get a locked color standard
// Input Value  : None
// Output Value : Return _TRUE if color locked
//--------------------------------------------------
bit CVideoColorFormatProc(void)
{
    BYTE i = 0;
    BYTE cnt = 5;

    while((CVideoIsColorLocked(i) == _FALSE) && (--cnt > 0))
    {
        i++;

        if(CHECK60HZ())
        {
            if(i == 5)
            {
                i = 0;
            }
        }

        if(CHECK50HZ())
        {
            if(i == 4)
            {
                i = 5;
            }
            if(i == 6)
            {
                i = 0;
            }
        }
    }

    if(cnt == 0)
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Check Video Channel if Signal Exist
// Input Value  : None
// Output Value : Return _TRUE if video signal exist, otherwise _FALSE
//--------------------------------------------------
bit CVideoIsExist(void)
{
    BYTE temp, cnt;

    CScalerCodeW(tVIDEO_TABLE_SET_SCALER);

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerSetBit(_IPV_ACT_STA_H_18, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    CScalerSetBit(_P2_Z0CC2_AC, ~_BIT6, _BIT6);

    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), _BIT0);

    if(GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT)
    {

    }
    else if(GET_INPUT_PORT(g_ucSearchIndex) == _A1_INPUT_PORT)
    {


        CScalerPageSelect(_PAGE0);
        CScalerSetBit(_P0_ADC_POWER_C6, ~_BIT6, _BIT6);

#if(_FRC_SUPPORT == _OFF)
        CScalerSetByte (_V8_YUV_CONVERSION_1F, 0x08);
#else
        SET_FRC16BITSIN();
#if(_FRC_YUV_MODE_SUPPORT == _ON)
        CScalerPageSelect(_PAGE5);
        CScalerSetByte(_P5_SDRF_MN_FIFO_422_SET_E3, 0x02); //Enable FRC 422->444
#endif
#endif


#if(_SCALER_TYPE == _RTD2472D)
        CScalerPageSelect(_PAGE0);
        CScalerSetBit(_P0_ADC_POWER_SOG_SOY_CTL_BA, ~_BIT0, _BIT0);
#endif


    }
    else if(GET_INPUT_PORT(g_ucSearchIndex) == _VI_INPUT_PORT)
    {


#if((_FRC_SUPPORT == _ON) && (_FRC_YUV_MODE_SUPPORT == _ON))

#if((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        CScalerSetByte(_V8_YUV_CONVERSION_1F, 0x40);//V8 From Pin 41~48
#elif(_SCALER_TYPE == _RTD2545LR)
        CScalerSetByte(_V8_YUV_CONVERSION_1F, 0x00);//Enable 422->444 and Interpolation
#else
    No Setting !!
#endif//End of #if((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        SET_FRC16BITSIN();
        CScalerPageSelect(_PAGE5);
        CScalerSetByte(_P5_SDRF_MN_FIFO_422_SET_E3, 0x02); //Enable FRC 422->444
#else

#if((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        CScalerSetByte(_V8_YUV_CONVERSION_1F, 0x48);//V8 From Pin 41~48 and 422->444 Interpolation
#elif(_SCALER_TYPE == _RTD2545LR)
        CScalerSetByte(_V8_YUV_CONVERSION_1F, 0x08);//Enable 422->444 and Interpolation
#else
    No Setting !!
#endif//End of #if((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))


#endif//End of #if((_FRC_SUPPORT == _ON) && (_FRC_YUV_MODE_SUPPORT == _ON))
    }


    if(!((bit)CScalerGetBit(_STATUS0_02, _BIT3)))
    {
        return _FALSE;
    }

    temp = 0x01;
    CI2cWrite(NVRAM_LINE,_VIDEO_DEVICE, ADDRESS(0x83), LENGTH(1), &temp);

    if((_V8_TYPE_SELECT == _AV_ONLY) || (_V8_TYPE_SELECT == _AV_WITH_SV))
    {
        temp = _AV_PORT;
    }
    else if((_V8_TYPE_SELECT == _SV_ONLY) || (_V8_TYPE_SELECT == _SV_WITH_AV))
    {
        temp = _SV_PORT;
    }

    for(cnt = 0; cnt < 2; cnt++)
    {
        CI2cWrite(NVRAM_LINE,_VIDEO_DEVICE, ADDRESS(0x02), LENGTH(1), &temp);

        CTimerDelayXms(60);

        CI2cRead(NVRAM_LINE,_VIDEO_DEVICE, ADDRESS(0x1f), LENGTH(1), &temp);

        if((temp & _BIT5) == _BIT5)
        {
            SET60HZ();
        }
        else
        {
            SET50HZ();
        }

        if((temp & _BIT6) == 0x00)
        {
            if(CVideoColorFormatProc())
            {
                CI2cRead(NVRAM_LINE,_VIDEO_DEVICE, ADDRESS(0x0e), LENGTH(1), &temp);
                if(((temp & 0x70) == 0x50) && CHECK50HZ())
                {
                    temp = 4;
                }
                else
                {
                    temp = (temp & 0x70) >> 4;
                }

                CI2cWrite(NVRAM_LINE,_VIDEO_DEVICE, ADDRESS(0x08), LENGTH(9), tVIDEO_TABLE_COLOR_STANDARD[temp == _AV_PORT ? 0 : 1][bVideoType][temp]);

                if(CModeMeasureReady())
                {
                    if(CModeMeasureData())
                    {
                        stModeInfo.ModeCurr = _VIDEO_EXIST;
                        SET_INPUTSOURCE_TYPE(_SOURCE_VIDEO8);

                        return _TRUE;
                    }
                }
            }
        }

        if(_V8_TYPE_SELECT == _AV_WITH_SV)
        {
            temp = _SV_PORT;
        }
        else if(_V8_TYPE_SELECT == _SV_WITH_AV)
        {
            temp = _AV_PORT;
        }
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if video signal is changed
// Input Value  : None
// Output Value : Return _TRUE if video signal is changed
//--------------------------------------------------
bit CVideoIsChange(void)
{
    BYTE temp;

    CI2cRead(NVRAM_LINE,_VIDEO_DEVICE, ADDRESS(0x1f), LENGTH(1), &temp);

    if(CHECK60HZ() && ((temp & _BIT5) == 0x00))             //60hz-->50hz
    {
        return _TRUE;
    }
    else if(CHECK50HZ() && ((temp & _BIT5) == _BIT5))       //50hz-->60hz
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Display video set process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CVideoDisplaySet(void)
{
    BYTE field;

    field = (BYTE)bVideoType;

    CI2cWrite(NVRAM_LINE,_VIDEO_DEVICE, ADDRESS(0x9A), LENGTH(6), tVIDEO_TABLE_FIELD[field]);

    stModeInfo.IHTotal = tVIDEO_TABLE_INPUT_INFO[field][0];
    stModeInfo.IHStartPos = tVIDEO_TABLE_INPUT_INFO[field][1];
    stModeInfo.IHWidth = tVIDEO_TABLE_INPUT_INFO[field][2];
    stModeInfo.IVStartPos = tVIDEO_TABLE_INPUT_INFO[field][3];
    stModeInfo.IVHeight = tVIDEO_TABLE_INPUT_INFO[field][4];

    stDisplayInfo.DHWidth = _PANEL_DH_WIDTH;
    stDisplayInfo.DVHeight = _PANEL_DV_HEIGHT;
    stDisplayInfo.DHTotal = _PANEL_DH_TOTAL;

#if(_FRC_SUPPORT == _ON)
    CMemoryWorkingTypeDecide();
#endif

    stModeInfo.IHFreq = 157;    // For PAL and NTSC. We can use sync processor to measure the actual value.

    CFrameSyncModifyDVStartPos(_DVSTART_POS_ADJUSTING);

    CModeSetCaptureWindow(0x05); // 0x05: ALL scale-up
    CModeSetScaling(0x05);
    CModeSetDisplay(0x05);

    CEepromLoadBriConData();
    CEepromLoadColorTempData();
    CAdjustContrast(stConBriData.Contrast);
    CAdjustBrightness(stConBriData.Brightness);
    CAdjustBacklight(stSystemData.BackLight);
    CPowerADCAPLLOff();


    CFrameSyncFineTune(_ODD);

#if(_FRC_SUPPORT == _ON)
    if(!GET_FRCSTATUS())
    {
        CModeSetFIFOForFrameSync();
#else
    {
#endif
        pData[0] = CFrameSyncDo();
    }

    if(pData[0] == 2)
    {
        CModeResetMode();
        return;
    }

// Issac-04-12 Begin
#if((_MEMORY_WORK_TYPE == _OD_ON_FRC_ON) || (_MEMORY_WORK_TYPE == _OD_OFF_FRC_ON))
    if(GET_FRCSTATUS())
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
// Issac-04-12 End

    SET_MODESTABLE();
    CModeSetupEtcs(_FUNCTION_DISABLE);
}

#endif  // End of #if(_VIDEO_SUPPORT == _ON)

#endif  // End of #if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

