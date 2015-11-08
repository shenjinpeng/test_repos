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
// ID Code      :  Realtek_DDCCI.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------
#define _REALTEK_DDCCI_

#include "Common\Header\Include.h"

#if(_DDCCI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Called by Main
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcDDCCI_Command(void)
{
    if(GET_DDCCI_STATUS())
    {
        if(g_RxStatus == _DDC2B_COMPLETED)
        {
            if(g_ucDdcciRxBuf[_COMMAND] == _DDC2B_CMD_GetVCPFeature)
            {
                CDdcGetVCPFeature();
            }
            else if(g_ucDdcciRxBuf[_COMMAND] == _DDC2B_CMD_SetVCPFeature)
            {
                CDdcSetVCPFeature();
            }
            else if(g_ucDdcciRxBuf[_COMMAND] == _DDC2B_CMD_GetTimingReport)
            {
                CDdcDDCCI_GetTimingReport();
            }
            else if(g_ucDdcciRxBuf[_COMMAND] == _DDC2B_CMD_SaveCurrentSettings)
            {
                CDdcDDCCI_SaveSetting();
            }
            else if(g_ucDdcciRxBuf[_COMMAND] == _DDC2B_CMD_CapabilitiesRequest)
            {
                CDdcDDCCI_GetCapabilitiesRequest();
            }
            else
            {
                CDDC2Bi_InitTx();
            }

            CDdcDDCCI_InitRx();
        }
    }
}

//--------------------------------------------------
// Description  : Initial RX variables
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcDDCCI_InitRx(void)
{
    // clear the rxState...
    g_RxStatus = _DDC2B_CLEAR;

    // ...and the current buffer for a new message
    for(g_ucDdcciCommandNumber = 0; g_ucDdcciCommandNumber < _DDCCI_RXBUF_LENGTH; g_ucDdcciCommandNumber++)
    {
        g_ucDdcciRxBuf[g_ucDdcciCommandNumber] = 0;
    }

    g_ucDdcciCommandNumber = 0;
}

//--------------------------------------------------
// Description  : Initial TX variables
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDDC2Bi_InitTx(void)
{
    // Send Null-Message
    g_ucDdcciTxCount = 0;

    g_ucDdcciTxBuf[0] = _DDC2B_DEST_ADDRESS;
    g_ucDdcciTxBuf[1] = 0x80;
    g_ucDdcciTxBuf[2] = 0xbe;

#if((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    MCU_I2C_IRQ_CTRL2_FF2A = (MCU_I2C_IRQ_CTRL2_FF2A | _BIT6) & (~_BIT5);
#endif
    CDdcTxCommandReady();
}

//--------------------------------------------------
// Description  : Tx command is Ready
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcTxCommandReady()
{
    g_ucDdcciTxCount = 0;

#if(_MCU_TYPE == _REALTEK_EMBEDDED)

    /*
    if(GET_INPUTSOURCE_TYPE() != _SOURCE_DP)
    */
    // QD unstable behavior for sending command
    if(g_ucActiveInputSourceType != _SOURCE_DP)
    {
        MCU_I2C_IRQ_CTRL2_FF2A |= 0xa0;
        MCU_I2C_DATA_OUT_FF26 = g_ucDdcciTxBuf[g_ucDdcciTxCount];
        MCU_I2C_IRQ_CTRL2_FF2A &= 0xDF;
    }

    /*
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_DP) && ((MCU_I2C_STATUS2_FF29 & 0x02) != 0))
    */
    // QD unstable behavior for sending command
    if((g_ucActiveInputSourceType == _SOURCE_DP) && ((MCU_I2C_STATUS2_FF29 & 0x02) != 0))
    {
        #if((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
            MCU_I2C_IRQ_CTRL2_FF2A = (MCU_I2C_IRQ_CTRL2_FF2A | _BIT6); //reset data buffer
        #endif

        MCU_I2C_IRQ_CTRL2_FF2A |= 0xa0;
        MCU_I2C_DATA_OUT_FF26 = g_ucDdcciTxBuf[g_ucDdcciTxCount];
    }

#else
    MCU_I2C_DATA_OUT_FF2A = g_ucDdcciTxBuf[g_ucDdcciTxCount];

#endif
}

//--------------------------------------------------
// Description  : Caculater checksum
// Input Value  :
// Output Value : Checksum value
//--------------------------------------------------
BYTE CDdcDDCCI_CalCheckSum(BYTE sum)
{
    BYTE cnt = 0, ucLen = 0;

    ucLen = (g_ucDdcciTxBuf[_DDC_LENGTH] & 0x7f) + 2;

    for(cnt = 0; cnt < ucLen; cnt++)
    {
        sum = sum ^ g_ucDdcciTxBuf[cnt];
    }
    return sum;
}

//--------------------------------------------------
// Description  : Load value from FW to g_ucDdcciTxBuf
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcGetVCPFeature(void)
{
    g_ucDdcciTxBuf[_DDC_SOURCE] = _DDC2B_DEST_ADDRESS;
    g_ucDdcciTxBuf[_DDC_LENGTH] = _DDC2Bi_CONTROL_STATUS_FLAG | 0x08;
    g_ucDdcciTxBuf[_COMMAND] = _DDC2B_CMD_GetVCPFeature_Reply;
    g_ucDdcciTxBuf[_PARAMETER] = _DDC2B_CMD_GetVCP_RC_NoError;
    g_ucDdcciTxBuf[_ITEM] = g_ucDdcciRxBuf[_PARAMETER];
    g_ucDdcciTxBuf[5] = _DDC2B_CMD_GetVCP_TP_SetParameter;

    switch(g_ucDdcciRxBuf[_PARAMETER])
    {
        case _DDC2B_CMD_VCP_NewControlValue:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0x0002, g_ucDdcciNewControlValue);
            break;

        case _DDC2B_CMD_VCP_FactoryReset:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_Momentary, 0x0001, 0x00);
            break;

        case _DDC2B_CMD_VCP_RecallBriCon:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_Momentary, 0x0001, 0x00);
            break;

        case _DDC2B_CMD_VCP_GeometryReset:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_Momentary, 0x0001, 0x00);
            break;

        case _DDC2B_CMD_VCP_ColorReset:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_Momentary, 0x0001, 0x00);
            break;

        case _DDC2B_CMD_VCP_ColorTempIncrement:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0x0000, 100);
            break;

        case _DDC2B_CMD_VCP_ColorTempRequest:
            GetVPC_ColorTempRequest(_GETVCP_PARAM);
            break;

        case _DDC2B_CMD_VCP_Clock:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 100
, (WORD)COsdDispRealToPercent(stModeUserData.Clock, COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MAX)
, COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN)));
            break;

        case _DDC2B_CMD_VCP_Brightness:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 100
, (WORD)COsdDispRealToPercent(stSystemData.BackLight, _BACKLIGHT_MAX, _BACKLIGHT_MIN));
            break;

        case _DDC2B_CMD_VCP_Contrast:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 100
, (WORD)COsdDispRealToPercent(stConBriData.Contrast, _CONTRAST_MAX, _CONTRAST_MIN));
            break;

        case _DDC2B_CMD_VCP_SelectColorPreset:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0x000B, tCOLORPRESET_VALUE[stOsdUserData.ColorTemp]);
            break;

        case _DDC2B_CMD_VCP_RedGain:
        case _DDC2B_CMD_VCP_GreenGain:
        case _DDC2B_CMD_VCP_BlueGain:
            {
                pData[10] = GET_COLOR_TEMP_TYPE();

                if(GET_COLOR_TEMP_TYPE() != _CT_USER)
                {
                    SET_COLOR_TEMP_TYPE(_CT_USER);
                    CEepromLoadColorTempData();
                }

                pData[0] = COsdDispRealToPercent(stColorTempData.ColorTemp[(g_ucDdcciRxBuf[_PARAMETER] -_DDC2B_CMD_VCP_RedGain)/2]
, _COLORTEMP_USER_MAX, _COLORTEMP_USER_MIN);

                CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 100, pData[0]);

                SET_COLOR_TEMP_TYPE(pData[10]);
                CEepromLoadColorTempData();
            }
            break;

        case _DDC2B_CMD_VCP_AutoSetUp:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_Momentary, 0x0001, 0x00);
            break;

        case _DDC2B_CMD_VCP_AutoColor:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0x01, 0x01);
            break;

        case _DDC2B_CMD_VCP_HPosition:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 100
, (WORD)COsdDispRealToPercent(stModeUserData.HPosition
, COsdFxGetHPositionRange(_GET_HPOSITIONRANGE_MAX), COsdFxGetHPositionRange(_GET_HPOSITIONRANGE_MIN)));
            break;

        case _DDC2B_CMD_VCP_VPosition:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 100
, (WORD)COsdDispRealToPercent(stModeUserData.VPosition
, COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MAX), COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MIN)));
            break;

        case _DDC2B_CMD_VCP_ClockPhase:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 100
, (WORD)COsdDispRealToPercent(stModeUserData.Phase, 63, 0));
            break;

        case _DDC2B_CMD_VCP_ActiveControl:
            /*
            CDdcciGetVCPFeature(_CMD_GET_VCP_TP_SETPARAMETER, 0x00ff, g_ucDdcciActiveValue); // Mark follow Arkin
            */
            break;

        case _DDC2B_CMD_VCP_InputSource:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0x03, tINPUTSOURCEPORT[stSystemData.SearchIndex]);
            break;

#if(_DDCCI_AUDIO_SUPPORT == _ENABLE)
        case _DDC2B_CMD_VCP_AudioVolume:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 100, stOsdUserData.Volume);
            break;
#endif

        case _DDC2B_CMD_VCP_RedBlackLevel:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 100, g_ucDdcciRedBlackLevel);
            break;

        case _DDC2B_CMD_VCP_GreenBlackLevel:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 100, g_ucDdcciGreenBlackLevel);
            break;

        case _DDC2B_CMD_VCP_BlueBlackLevel:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 100, g_ucDdcciBlueBlackLevel);
            break;

        case _DDC2B_CMD_VCP_PRODUCTKEY:
            CDdcGetVPC_PRODUCTKEY(_DDC_LENGTH);
            break;

        case _DDC2B_CMD_VCP_HFreq:
            CDdcGetVPC_HFreq(_GETVCP_PARAM);
            break;

        case _DDC2B_CMD_VCP_VFreq:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0xffff, stModeInfo.IVFreq*10);
            break;

        case _DDC2B_CMD_VCP_PanelType:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0x01, 1);
            break;

        case _DDC2B_CMD_VCP_MonitorType:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0x05, 3);
            break;

        case _DDC2B_CMD_VCP_ApplicationEnable:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0xff, 0x5a);
            break;

        case _DDC2B_CMD_VCP_ControllerType:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0x0000, 0x0009);
            break;

        case _DDC2B_CMD_VCP_FWLevel:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0xffff, _FIRMWARE_VERSION);
            break;

        case _DDC2B_CMD_VCP_OSDOnOff:
            if(CScalerGetBit(_OVERLAY_CTRL_6C, 0x01))
            {
               pData[0] = 2;
            }
            else
            {
               pData[0] = 1;
            }
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0x02, pData[0]);
            break;

        case _DDC2B_CMD_VCP_OSDLanguage:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0x0D, tLANGUAGEDEFINE[stOsdUserData.Language]);
            break;

        case _DDC2B_CMD_VCP_PowerMode:
            if(ucCurrState == _PWOFF_STATE)
            {
                pData[0] = 5;
            }
            else if(ucCurrState == _SLEEP_STATE)
            {
                pData[0] = 4;
            }
            else
            {
                pData[0] = 1;
            }
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0x0005, pData[0]);
            break;

        case _DDC2B_CMD_VCP_Version:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0xffff, 0x0201);
            break;

        case _DDC2B_CMD_VCP_Sharpness:
            CDdcciGetVCPFeature(_DDC2B_CMD_GetVCP_TP_SetParameter, 0x0004, stOsdUserData.Sharpness);
            break;

        default:
            g_ucDdcciTxBuf[3] = _DDC2B_CMD_GetVCP_RC_Unsupported;               // RC cmd not support
            break;

    }
    g_ucDdcciTxBuf[_GETVCP_PARAM + 4] = CDdcDDCCI_CalCheckSum(_DDC2Bi_VIRTUAL_HOST_ADDRESS);

    CDdcTxCommandReady();
}

//--------------------------------------------------
// Description  : Load Color Temp to g_ucDdcciTxBuf
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void GetVPC_ColorTempRequest(BYTE BaseAddr)
{
    g_ucDdcciTxBuf[BaseAddr] = HIBYTE(93 - 30);
    g_ucDdcciTxBuf[BaseAddr + 1] = LOBYTE(93 - 30);

    if((stOsdUserData.ColorTemp & 0x0f) == _CT_SRGB)
    {
        g_ucDdcciTxBuf[BaseAddr + 2] = HIBYTE(40 - 30);
        g_ucDdcciTxBuf[BaseAddr + 3] = LOBYTE(40 - 30);
    }
    else if((stOsdUserData.ColorTemp & 0x0f) == _CT_9300)
    {
        g_ucDdcciTxBuf[BaseAddr + 2] = HIBYTE(93 - 30);
        g_ucDdcciTxBuf[BaseAddr + 3] = LOBYTE(93 - 30);
    }
    else if((stOsdUserData.ColorTemp & 0x0f) == _CT_6500)
    {
        g_ucDdcciTxBuf[BaseAddr + 2] = HIBYTE(65 - 30);
        g_ucDdcciTxBuf[BaseAddr + 3] = LOBYTE(65 - 30);
    }
     else if((stOsdUserData.ColorTemp & 0x0f) == _CT_USER)
    {
        g_ucDdcciTxBuf[BaseAddr + 2] = HIBYTE(g_ucColorTempUnSupport - 30);
        g_ucDdcciTxBuf[BaseAddr + 3] = LOBYTE(g_ucColorTempUnSupport - 30);
    }
    else
    {
        g_ucDdcciTxBuf[BaseAddr + 2] = HIBYTE(65 - 30);
        g_ucDdcciTxBuf[BaseAddr + 3] = LOBYTE(65 - 30);
    }
}

//--------------------------------------------------
// Description  : Load productkey to g_ucDdcciTxBuf
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcGetVPC_PRODUCTKEY(BYTE BaseAddr)
{
    g_ucDdcciTxBuf[BaseAddr] = 0x89;
    g_ucDdcciTxBuf[BaseAddr + 1] = 0x02;
}

//--------------------------------------------------
// Description  : Load op to g_ucDdcciTxBuf
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcciGetVCPFeature(BYTE opcode, WORD Max, WORD Present)
{
    g_ucDdcciTxBuf[5] = opcode;
    g_ucDdcciTxBuf[6] = HIBYTE(Max);
    g_ucDdcciTxBuf[7] = LOBYTE(Max);
    g_ucDdcciTxBuf[8] = HIBYTE(Present);
    g_ucDdcciTxBuf[9] = LOBYTE(Present);
}

//--------------------------------------------------
// Description  : Load Hfreq to g_ucDdcciTxBuf
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcGetVPC_HFreq(BYTE BaseAddr)
{
    ((DWORD *)pData)[0] = (DWORD)stModeInfo.IHFreq * 100;

    g_ucDdcciTxBuf[BaseAddr] = pData[0];
    g_ucDdcciTxBuf[BaseAddr + 1] = pData[1];
    g_ucDdcciTxBuf[BaseAddr + 2] = pData[2];
    g_ucDdcciTxBuf[BaseAddr + 3] = pData[3];
}

//--------------------------------------------------
// Description  : Set g_ucDdcciRxBuf to FW
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcSetVCPFeature(void)
{
    if(CDdcDdcciSetVCPCheck() == _FALSE)
    {
        CDDC2Bi_InitTx();
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_NewControlValue)
    {
        if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 0x01)
        {
            g_ucDdcciNewControlValue = 0x01;
        }
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_Sharpness)
    {
        if(g_ucDdcciRxBuf[_SETVCP_PARAM] > 4)
        {
            g_ucDdcciRxBuf[_SETVCP_PARAM] = 4;
        }

        stOsdUserData.Sharpness = g_ucDdcciRxBuf[_SETVCP_PARAM];
        CAdjustSharpness(stOsdUserData.Sharpness);
        CEepromSaveOsdUserData();
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_InputSource)
    {
        if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 0x01)
        {
            CSourceSwitchInputPort(_A0_INPUT_PORT);
            ucOsdEventMsg = _CHANGE_SOURCE_MSG;
        }
        else if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 0x03)
        {
            CSourceSwitchInputPort(_D1_INPUT_PORT);
            ucOsdEventMsg = _CHANGE_SOURCE_MSG;
        }
        else if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 0x0F)
        {
            CSourceSwitchInputPort(_D0_INPUT_PORT);
            ucOsdEventMsg = _CHANGE_SOURCE_MSG;
        }
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_FactoryReset)
    {
        if(g_ucDdcciRxBuf[_SETVCP_PARAM] != 0)
        {
            CDdcDdcciResetAllSettings();

            if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
            {
                CAutoDoAutoConfig();
            }
        }
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_RecallBriCon)
    {
        if(g_ucDdcciRxBuf[_SETVCP_PARAM] != 0)
        {
            CDdcDdcciRecallBriCon();
            ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
        }
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_GeometryReset)
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
        {
            if(g_ucDdcciRxBuf[_SETVCP_PARAM])
            {
                stModeUserData.HPosition = stModeUserCenterData.CenterHPos;
                stModeUserData.VPosition = stModeUserCenterData.CenterVPos;
                CAdjustHPosition();
                CAdjustVPosition();
                CAutoDoAutoConfig();
             }
        }
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_ColorReset)
    {
        if(g_ucDdcciRxBuf[_SETVCP_PARAM] != 0)
        {
           CDdcDdcciColorReset();
           ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
        }
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_ColorTempRequest)
    {
        g_ucColorTempUnSupport = (g_ucDdcciRxBuf[_SETVCP_PARAM] + 30);
        if(g_ucColorTempUnSupport >= 93)
        {
            SET_COLOR_TEMP_TYPE(_CT_9300);
        }
        else if((g_ucColorTempUnSupport < 75) && (g_ucColorTempUnSupport >= 65))
        {
            SET_COLOR_TEMP_TYPE(_CT_6500);
        }
        else if((g_ucColorTempUnSupport < 54) && (g_ucColorTempUnSupport >= 40))
        {
            SET_COLOR_TEMP_TYPE(_CT_SRGB);
        }
        else
        {
             SET_COLOR_TEMP_TYPE(_CT_USER);
        }

        CEepromLoadColorTempData();
        if(GET_COLOR_TEMP_TYPE() != _CT_SRGB)
        {
            CAdjustContrast(stConBriData.Contrast);
        }

        ucOsdState = _MENU_NONE;
        COsdFxDisableOsd();
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_Clock)
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
        {
            if( g_ucDdcciRxBuf[_SETVCP_PARAM] > 100)
            {
                g_ucDdcciRxBuf[_SETVCP_PARAM] = 100;
            }

            stModeUserData.Clock = COsdDispPercentToRealValue(g_ucDdcciRxBuf[_SETVCP_PARAM]
, COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MAX), COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN));
            CAdjustAdcClock(stModeUserData.Clock);
            ucOsdEventMsg = _SAVE_EE_MODEUSERDATA_MSG;
        }
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_Brightness)
    {
        if(g_ucDdcciRxBuf[_SETVCP_PARAM] > 100)
        {
            g_ucDdcciRxBuf[_SETVCP_PARAM] = 100;
        }

        stSystemData.BackLight = COsdDispPercentToRealValue(g_ucDdcciRxBuf[_SETVCP_PARAM], _BACKLIGHT_MAX, _BACKLIGHT_MIN);
        CAdjustBacklight(stSystemData.BackLight);
        CEepromSaveBriConData();
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_Contrast)
    {
        if(g_ucDdcciRxBuf[_SETVCP_PARAM] > 100)
        {
            g_ucDdcciRxBuf[_SETVCP_PARAM] = 100;
        }

        stConBriData.Contrast = COsdDispPercentToRealValue(g_ucDdcciRxBuf[_SETVCP_PARAM], _CONTRAST_MAX, _CONTRAST_MIN);

        CAdjustContrast(stConBriData.Contrast);
        CEepromSaveBriConData();
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_SelectColorPreset)
    {
        if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 0x02)
        {
            SET_COLOR_TEMP_TYPE(_CT_USER);
        }
        else if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 0x05)
        {
            SET_COLOR_TEMP_TYPE(_CT_6500);
        }
        else if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 0x08)
        {
            SET_COLOR_TEMP_TYPE(_CT_9300);
        }
        else if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 0x01)
        {
            SET_COLOR_TEMP_TYPE(_CT_SRGB);
        }
        else if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 0x04)
        {
            SET_COLOR_TEMP_TYPE(_CT_5800);
        }

        CEepromLoadColorTempData();
        CAdjustContrast(stConBriData.Contrast);

        COsdFxDisableOsd();
        ucOsdState = _MENU_NONE;
        ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_RedGain)
    {
        if(GET_COLOR_TEMP_TYPE() != _CT_USER)
        {
            SET_COLOR_TEMP_TYPE(_CT_USER);
            CEepromLoadColorTempData();
        }

        stColorTempData.ColorTemp[_RED] = COsdDispPercentToRealValue(g_ucDdcciRxBuf[_SETVCP_PARAM]
, _COLORTEMP_USER_MAX, _COLORTEMP_USER_MIN);
        CAdjustContrast(stConBriData.Contrast);
        CEepromSaveColorTempData();
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_GreenGain)
    {
        if(GET_COLOR_TEMP_TYPE() != _CT_USER)                                   // only write at customer color
        {
            SET_COLOR_TEMP_TYPE(_CT_USER);
            CEepromLoadColorTempData();
        }

        stColorTempData.ColorTemp[_GREEN] = COsdDispPercentToRealValue(g_ucDdcciRxBuf[_SETVCP_PARAM]
, _COLORTEMP_USER_MAX, _COLORTEMP_USER_MIN);
        CAdjustContrast(stConBriData.Contrast);
        CEepromSaveColorTempData();
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_BlueGain)
    {
        if(GET_COLOR_TEMP_TYPE() != _CT_USER)                                   // only write at customer color
        {
            SET_COLOR_TEMP_TYPE(_CT_USER);
            CEepromLoadColorTempData();
        }

        stColorTempData.ColorTemp[_BLUE] = COsdDispPercentToRealValue(g_ucDdcciRxBuf[_SETVCP_PARAM]
, _COLORTEMP_USER_MAX, _COLORTEMP_USER_MIN);
        CAdjustContrast(stConBriData.Contrast);
        CEepromSaveColorTempData();
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_AutoSetUp)
    {
        // V013 VGA Patch Note (10) 20100416 Modify Start
        // Patch Reason : Support Auto Config For Yuv Color.
        /*
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
        */
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
        if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
#else
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
#endif
        // V013 VGA Patch Note (10) 20100416 Modify End
        {
            if(g_ucDdcciRxBuf[_SETVCP_PARAM] != 0)
            {
                ucOsdEventMsg = _DO_AUTO_CONFIG;
            }
        }
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_HPosition)
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
        {
            stModeUserData.HPosition = COsdDispPercentToRealValue(g_ucDdcciRxBuf[_SETVCP_PARAM]
, COsdFxGetHPositionRange(_GET_HPOSITIONRANGE_MAX), COsdFxGetHPositionRange(_GET_HPOSITIONRANGE_MIN));
            CAdjustHPosition();
            CEepromSaveModeData(stModeInfo.ModeCurr);
        }
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_VPosition)
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
        {
            stModeUserData.VPosition = COsdDispPercentToRealValue(g_ucDdcciRxBuf[_SETVCP_PARAM]
, COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MAX), COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MIN));
            CAdjustVPosition();
            CEepromSaveModeData(stModeInfo.ModeCurr);
        }
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_ClockPhase)
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
        {
            // V012 Modify 20100318 Start
            // V012 Patch Note (4) : Adjust the max phase value for DDCCI software adjusting.
            /*
            if(g_ucDdcciRxBuf[_SETVCP_PARAM] > 63)
            {
                g_ucDdcciRxBuf[_SETVCP_PARAM] = 63;
            }
            */
            if(g_ucDdcciRxBuf[_SETVCP_PARAM] > 100)
            {
                g_ucDdcciRxBuf[_SETVCP_PARAM] = 100;
            }
            // V012 Modify 20100318 End

            stModeUserData.Phase = COsdDispPercentToRealValue(g_ucDdcciRxBuf[_SETVCP_PARAM], 63, 0);
            CAdjustPhase(stModeUserData.Phase);
            CEepromSaveModeData(stModeInfo.ModeCurr);
        }
    }
    else if(ucDdcciData[_PARAMETER] == _DDC2B_CMD_VCP_ActiveControl)
    {
        g_ucDdcciActiveValue = g_ucDdcciRxBuf[_SETVCP_PARAM];
    }
#if(_AUDIO_SUPPORT == _ON)
   else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_AudioVolume)
   {
        if(g_ucDdcciRxBuf[_SETVCP_PARAM] > 100)
        {
            g_ucDdcciRxBuf[_SETVCP_PARAM] = 100;
        }

        stOsdUserData.Volume = g_ucDdcciRxBuf[_SETVCP_PARAM];
        CAdjustVolume(stOsdUserData.Volume);
   }
#endif // End of #if(_AUDIO_SUPPORT == _ON)
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_RedBlackLevel)
    {
        g_ucDdcciRedBlackLevel = g_ucDdcciRxBuf[_SETVCP_PARAM];
        //CAdjustBrightness(g_ucDdcciRedBlackLevel);                            // Please don't delete
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_GreenBlackLevel)
    {
        g_ucDdcciGreenBlackLevel = g_ucDdcciRxBuf[_SETVCP_PARAM];
        //CAdjustBrightness(ucDDCCI_RedBlackLevel);                             // Please don't delete
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_BlueBlackLevel)
    {
        g_ucDdcciBlueBlackLevel = g_ucDdcciRxBuf[_SETVCP_PARAM];
        //CAdjustBrightness(ucDDCCI_RedBlackLevel);                             // Please don't delete
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_PowerMode)
    {
        if(((g_ucDdcciRxBuf[_SETVCP_PARAM] == 5) && (ucCurrState != _PWOFF_STATE))
        || ((g_ucDdcciRxBuf[_SETVCP_PARAM] == 1) && (ucCurrState == _PWOFF_STATE)))
        {
            SET_POWERSWITCH();
        }
        else if((g_ucDdcciRxBuf[_SETVCP_PARAM] == 1) && (ucCurrState == _SLEEP_STATE))
        {
            CModeResetMode();
        }
        else if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 4)
        {
            CModePowerSavingEvent();
        }
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_OSDLanguage)
    {
        switch(g_ucDdcciRxBuf[_SETVCP_PARAM])
        {
            case 0x01:
                stOsdUserData.Language = _CHINESE_T;
                break;

            case 0x02:
                stOsdUserData.Language = _ENGLISH;
                break;

            case 0x03:
                stOsdUserData.Language = _FRENCH;
                break;

            case 0x04:
                stOsdUserData.Language = _GERMAN;
                break;

            case 0x0A:
                stOsdUserData.Language = _SPANISH;
                break;

            case 0x06:
                stOsdUserData.Language = _JAPAN;
                break;

            case 0x0D:
                stOsdUserData.Language = _CHINESE_S;
                break;

            default:
                break;
        }
        COsdFxDisableOsd();
        ucOsdState = _MENU_NONE;
        ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
    }
    else if(g_ucDdcciRxBuf[_PARAMETER] == _DDC2B_CMD_VCP_OSDOnOff)
    {
        if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 1)
        {
            CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, 0x00);
        }
        else if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 2)
        {
            CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, _BIT0);
        }
    }
    else
    {
        CDDC2Bi_InitTx();
    }
}


//--------------------------------------------------
// Description  : Load timing info to g_ucDdcciTxBuf
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcDDCCI_GetTimingReport(void)
{
    // V015 System Patch Note (4) Modify 20100628 Start
    // Patch Reason : Get polarity correctly for ddcci communication.
    BYTE ucPolarity = 0;

#if(_HSYNC_DETECTION == _AUTO_RUN)
    ucPolarity = ((stModeInfo.Polarity & ~_BIT0) | ( !(((bit)CScalerGetBit(_SYNC_INVERT_48, _BIT3) ? 0x00 : _BIT0) ^ ((bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6) ? 0x00 : _BIT0))));
#else
    ucPolarity = ((stModeInfo.Polarity & ~_BIT0) | ((bit)CScalerGetBit(_SYNC_INVERT_48, _BIT3) ? 0x00 : _BIT0));
#endif
    // V015 System Patch Note (4) Modify 20100628 End

    // V012 Modify 20100331 Start
    // V012 Patch Note (21) : Fix the sync processor compatibility problem. Replace slower XTAL clock with M2PLL.
    /*
    stModeInfo.IHFreq = (WORD)((DWORD)_RTD_XTAL * 10 * 2 / stModeInfo.IHCount);
    */
    stModeInfo.IHFreq = (WORD)((DWORD)_INTERNAL_SYSTEM_CLK * 10 * 2 / stModeInfo.IHCount);
    // V012 Modify 20100331 End

    stModeInfo.IHFreq = (stModeInfo.IHFreq >> 1) + (stModeInfo.IHFreq & 0x01);

    g_ucDdcciTxBuf[_DDC_SOURCE] = 0x6e;
    g_ucDdcciTxBuf[_DDC_LENGTH] = 0x06;
    g_ucDdcciTxBuf[_COMMAND] = 0x4e;
    g_ucDdcciTxBuf[3] = 0x00;

    //out range :Bit 7 = 1 Sync.Freq .out of range
    if(_MODE_NOSUPPORT == stModeInfo.ModeCurr)
    {
        g_ucDdcciTxBuf[3] |= 0x80;
    }

    // V015 System Patch Note (4) Modify 20100628 Start
    // Patch Reason : Get polarity correctly for ddcci communication.
    /*
    if((stModeInfo.Polarity & 0x02) == 0x00)
    {
        g_ucDdcciTxBuf[3] |= 0x02;                                              //H sync pol :Bit 1 = 1:positive H-sync polarity
    }

    if((stModeInfo.Polarity & 0x01) == 0x00)
    {
        g_ucDdcciTxBuf[3] |= 0x01;                                              //V sync pol :Bit 0 = 1:positive V-sync polarity
    }
    */
    if((bit)(ucPolarity & _BIT0))
    {
        g_ucDdcciTxBuf[3] |= 0x02;                                              // H sync pol :Bit 1 = 1:positive H-sync polarity
    }

    if((bit)(ucPolarity & _BIT1))
    {
        g_ucDdcciTxBuf[3] |= 0x01;                                              // V sync pol :Bit 0 = 1:positive V-sync polarity
    }
    // V015 System Patch Note (4) Modify 20100628 End

    g_ucDdcciTxBuf[4] = HIBYTE(stModeInfo.IHFreq * 10);
    g_ucDdcciTxBuf[5] = LOBYTE(stModeInfo.IHFreq * 10);
    g_ucDdcciTxBuf[6] = HIBYTE(stModeInfo.IVFreq * 10);
    g_ucDdcciTxBuf[7] = LOBYTE(stModeInfo.IVFreq * 10);
    g_ucDdcciTxBuf[8] = CDdcDDCCI_CalCheckSum(_DDC2Bi_VIRTUAL_HOST_ADDRESS);

    g_ucDdcciTxCount = (g_ucDdcciTxBuf[_DDC_LENGTH] & 0x7f) + 3;
    CDdcTxCommandReady();
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcDDCCI_SaveSetting(void)
{
    CDDC2Bi_InitTx();
}

//--------------------------------------------------
// Description  : Load DDCCI Capability Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcDDCCI_GetCapabilitiesRequest(void)
{
    BYTE ucCount = 0, ucSendLen = 0;
    WORD usOffset = 0;

    usOffset = ((WORD)(g_ucDdcciRxBuf[3] << 8) | (g_ucDdcciRxBuf[4]));

    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
        if(usOffset >= _CREQLEN_DSUB)
        {
            ucSendLen = 0;
        }
        else if(_CREQLEN_DSUB > (usOffset + _DDCCI_TXBUF_LENGTH - 6))     // 6 means 0x6e, length, 0xe3, offset_H, offset_L, Checksum
        {
            ucSendLen = _DDCCI_TXBUF_LENGTH - 6;
        }
        else
        {
            ucSendLen = _CREQLEN_DSUB - usOffset;
        }
    }

#if(_TMDS_SUPPORT == _ON)
    if(( GET_INPUTSOURCE_TYPE() == _SOURCE_DVI) || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI))
    {
        if(usOffset >= _CREQLEN_DVI)
        {
            ucSendLen = 0;
        }
        else if(_CREQLEN_DVI > (usOffset + _DDCCI_TXBUF_LENGTH - 6))      // 6 means 0x6e, length, 0xe3, offset_H, offset_L, Checksum
        {
            ucSendLen = _DDCCI_TXBUF_LENGTH - 6;
        }
        else
        {
            ucSendLen = _CREQLEN_DVI - usOffset;
        }
    }
#endif

#if(_DP_SUPPORT == _ON)
    /*
    if( GET_INPUTSOURCE_TYPE()==_SOURCE_DP)
    */
    // QD unstable behavior for sending command
    if(g_ucActiveInputSourceType == _SOURCE_DP)
    {
        if( usOffset >= sizeof(stCapabilitiesStringDisplayPort) )
        {
            ucSendLen = 0;
        }

        else if(sizeof(stCapabilitiesStringDisplayPort) > (usOffset+_DDCCI_TXBUF_LENGTH - 8) )
        {
            ucSendLen = _DDCCI_TXBUF_LENGTH - 8;
        }

        else
        {
            ucSendLen = sizeof(stCapabilitiesStringDisplayPort) - usOffset;
        }
    }
#endif


    g_ucDdcciTxBuf[0] = _DDC2B_DEST_ADDRESS;
    g_ucDdcciTxBuf[1] = _DDC2Bi_CONTROL_STATUS_FLAG | (ucSendLen + 3);
    g_ucDdcciTxBuf[2] = _DDC2B_CMD_CapabilitiesRequest_Reply;
    g_ucDdcciTxBuf[3] = g_ucDdcciRxBuf[3];
    g_ucDdcciTxBuf[4] = g_ucDdcciRxBuf[4];

    for(ucCount = 0; ucCount < ucSendLen; ucCount++)
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
        {
            g_ucDdcciTxBuf[5 + ucCount] = tCP_STRING_DSUB[ucCount + usOffset];
        }
#if(_TMDS_SUPPORT == _ON)
    if(( GET_INPUTSOURCE_TYPE() == _SOURCE_DVI) || (GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI))
        {
            g_ucDdcciTxBuf[5 + ucCount] = sCP_STRING_DVI[ucCount + usOffset];
        }
#endif

#if(_DP_SUPPORT == _ON)
        /*
        if( GET_INPUTSOURCE_TYPE()==_SOURCE_DP )
        */
        // QD unstable behavior for sending command
        if(g_ucActiveInputSourceType == _SOURCE_DP)
        {
            g_ucDdcciTxBuf[5 + ucCount] = stCapabilitiesStringDisplayPort[ucCount + usOffset];
        }
#endif

    }

    g_ucDdcciTxBuf[5 + ucSendLen] = CDdcDDCCI_CalCheckSum(_DDC2Bi_VIRTUAL_HOST_ADDRESS);

    CDdcTxCommandReady();

/*    g_ucDdcciTxCount = 0;

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
    MCU_I2C_IRQ_CTRL2_FF2A |= 0xa0;

    MCU_I2C_DATA_OUT_FF26 = g_ucDdcciTxBuf[g_ucDdcciTxCount];

    MCU_I2C_IRQ_CTRL2_FF2A &= (~_BIT5);

#else
    MCU_I2C_DATA_OUT_FF2A = g_ucDdcciTxBuf[g_ucDdcciTxCount];

#endif // End of _MCU_TYPE
*/
}

//--------------------------------------------------
// Description  : Reset monitor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcDdcciResetAllSettings(void)
{
    // V015 System Patch Note (7) Modify 20100630 Start
    // Patch Reason : New EEPROM emulation process.
    /*
    StructModeUserFIFODataType stFIFOModeTemp;

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
    BYTE ucModeType = 0;
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End

    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
    /*
    if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < 16))
    * /
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
    CEepromLoadSystemDataDefault();
    CEepromLoadOsdUserDataDefault();

#if((_OSD_TYPE == _REALTEK_OSD) && (_MEMORY_LOCATION == _EEPROM))
    CEepromLoadOsdReserveDataDefault();
#else

#endif

    CSourceSaveSearchData();

    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
    ucModeType = GET_INPUTSOURCE_TYPE();
    SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);
    CEepromLoadModeData(stModeInfo.ModeCurr);
    SET_INPUTSOURCE_TYPE(ucModeType);
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End

    // V013 VGA Patch Note (11) Modify 20100416 Start
    // Patch Reason : Add FIFO Mode Only to save EEPROM space.
    // Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
    /*
    if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < 16))
    * /
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
        * /
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
    else if((GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE) && (stModeInfo.ModeCurr < _MAX_PRESET_MODE))
    {
        CEepromLoadModeData(stModeInfo.ModeCurr);
    }

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    SET_SOURCE_SEARCH_AUTO();
#endif
    */
    CEepromLoadDefault();
    // V015 System Patch Note (7) Modify 20100630 End

    CDdcDdcciColorReset();
}

//--------------------------------------------------
// Description  : Reset color to default
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcDdcciColorReset(void)
{
    BYTE cnt = 0;
    BYTE ucSourceTemp = _SOURCE_VGA;

    ucSourceTemp = GET_INPUTSOURCE_TYPE();

    g_ucDdcciRedBlackLevel = _DDCCI_BlACKLEVEL_DEFAULT;
    g_ucDdcciGreenBlackLevel = _DDCCI_BlACKLEVEL_DEFAULT;
    g_ucDdcciBlueBlackLevel = _DDCCI_BlACKLEVEL_DEFAULT;

    stColorTempData.ColorTemp[_RED] = _DDCCI_USER_COLOR_DEFAULT;
    stColorTempData.ColorTemp[_GREEN] = _DDCCI_USER_COLOR_DEFAULT;
    stColorTempData.ColorTemp[_BLUE] = _DDCCI_USER_COLOR_DEFAULT;

    SET_COLOR_TEMP_TYPE(_CT_USER);

    for(cnt = 0; cnt < _SOURCE_AMOUNT; cnt++)
    {
        SET_INPUTSOURCE_TYPE(cnt);
        CEepromSaveColorTempData();
    }

    SET_INPUTSOURCE_TYPE(ucSourceTemp);
    CEepromLoadColorTempData();
    CEepromSaveOsdUserData();
    CDdcDdcciRecallBriCon();
}

//--------------------------------------------------
// Description  : Reset Brightness and contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcDdcciRecallBriCon(void)
{
    CEepromLoadBriConDataDefault();
    CEepromLoadBackLightDefault();
    stSystemData.BackLight=tOSD_DICOMlumi[stConBriData.Dicom] ;
    CAdjustBacklight(stSystemData.BackLight);
    CAdjustContrast(stConBriData.Contrast);
    CAdjustBrightness(stConBriData.Brightness);
}

//--------------------------------------------------
// Description  : Check DDCCI Command valid
// Input Value  : None
// Output Value : Return _FALSE while invalid
//--------------------------------------------------
bit CDdcDdcciSetVCPCheck(void)
{
    switch(g_ucDdcciRxBuf[_PARAMETER])
    {
        case _DDC2B_CMD_VCP_FactoryReset:
        case _DDC2B_CMD_VCP_RecallBriCon:
        case _DDC2B_CMD_VCP_GeometryReset:
        case _DDC2B_CMD_VCP_ColorReset:

            if(g_ucDdcciRxBuf[_SETVCP_PARAM] == 0)
            {
                return _FALSE;
            }

            break;

        case _DDC2B_CMD_VCP_NewControlValue:
        case _DDC2B_CMD_VCP_AutoSetUp:
        case _DDC2B_CMD_VCP_AutoColor:

            if((g_ucDdcciRxBuf[_SETVCP_PARAM] == 0) || (g_ucDdcciRxBuf[_SETVCP_PARAM] >= 3))
            {
                return _FALSE;
            }

            break;

        case _DDC2B_CMD_VCP_SelectColorPreset:

            if((g_ucDdcciRxBuf[_SETVCP_PARAM] == 0) || (g_ucDdcciRxBuf[_SETVCP_PARAM] >= 0x0E))
            {
                return _FALSE;
            }

            break;

        case _DDC2B_CMD_VCP_OSDLanguage:

            if((g_ucDdcciRxBuf[_SETVCP_PARAM] == 0) || (g_ucDdcciRxBuf[_SETVCP_PARAM] >= 0x26))
            {
                return _FALSE;
            }

            break;

        case _DDC2B_CMD_VCP_PowerMode:

            if((g_ucDdcciRxBuf[_SETVCP_PARAM] == 0) || (g_ucDdcciRxBuf[_SETVCP_PARAM] >= 0x06))
            {
                return _FALSE;
            }

            break;
    }

    return _TRUE;
}

#endif // End of #if(_DDCCI_SUPPORT == _ON)

