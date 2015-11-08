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
// ID Code      : Misc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __MISC__

#include "Common\Header\Include.h"

#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

//----------------------------------------------------------------------------------------------------
// Polling Events
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Stable flag polling event
// Input Value  : None
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit CMiscStableFlagPollingEvent(void)
{
    if((bit)CScalerGetBit(_STABLE_MEASURE_4F, _BIT7))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

// V012 Modify 20100329 Start
// V012 Patch Note (19) : Adjust polling time of Auto Run Typer according to different Crystal frequency.
/*
#if(_HSYNC_DETECTION == _AUTO_RUN)
//--------------------------------------------------
// Description  : Hsync Type Detection Auto Run flag polling event
// Input Value  : None
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit CMiscHsyncTypeAutoRunFlagPollingEvent(void)
{
    if((bit)CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, _BIT7))
    {
       return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif
*/
// V012 Modify 20100329 End

//--------------------------------------------------
// Description  : Measure start/end polling event
// Input Value  : None
// Output Value : Return _TRUE if measure finished
//--------------------------------------------------
bit CMiscModeMeasurePollingEvent(void)
{
    if((bit)CScalerGetBit(_MEAS_HS_PERIOD_H_52, _BIT7))
    {
        if(!(bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT7))
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
        if(!(bit)CScalerGetBit(_MEAS_HS_PERIOD_H_52, _BIT5))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
}

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Auto measure start/end polling event
// Input Value  : None
// Output Value : Return _TRUE if auto measure finished
//--------------------------------------------------
bit CMiscAutoMeasurePollingEvent(void)
{
    if(!(bit)CScalerGetBit(_AUTO_ADJ_CTRL1_7D, _BIT0))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : Apply double buffer polling event
// Input Value  : None
// Output Value : Return _TRUE if apply double buffer finished
//--------------------------------------------------
bit CMiscApplyDoubleBufferPollingEvent(void)
{
    if(!(bit)CScalerGetBit(_VGIP_CTRL_10, _BIT5))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DVS start polling event
// Input Value  : None
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit CMiscDVSStartPollingEvent(void)
{
    if((bit)CScalerGetBit(_STATUS1_03, _BIT3))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check State to Active state
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscCheckToActiveEvent(void)
{
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
    {
        ucCurrState = _ACTIVE_STATE;
    }
    else
    {
#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))
        if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_I_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_I_PORT))
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

        ucCurrState = _ACTIVE_STATE;

        // V016 System Patch Note (15) Modify 20100824 Start
        // Patch Reason : Fix IHCount=0 issue
        CModeAutoMeasureOn();
        CTimerPollingEventProc(120, CMiscModeMeasurePollingEvent);
        // V016 System Patch Note (15) Modify 20100824 End

    }
}


//----------------------------------------------------------------------------------------------------
// Misc Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Enable double buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscEnableDoubleBuffer(void)
{
    CScalerSetBit(_VGIP_CTRL_10, ~_BIT4, _BIT4);
}

//--------------------------------------------------
// Description  : Disable double buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscDisableDoubleBuffer(void)
{
    CScalerSetBit(_VGIP_CTRL_10, ~_BIT4, 0x00);
}

//--------------------------------------------------
// Description  : Apply double buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscApplyDoubleBuffer(void)
{
    if((bit)CScalerGetBit(_VGIP_CTRL_10, _BIT4))
    {
        CScalerSetBit(_VGIP_CTRL_10, ~_BIT5, _BIT5);
        CTimerPollingEventProc(60, CMiscApplyDoubleBufferPollingEvent);
    }
}

//--------------------------------------------------
// Description  : Clear status Reg[02] and Reg[03]
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscClearStatusRegister(void)
{
    CScalerSetByte(_STATUS0_02, 0x00);
    CScalerSetByte(_STATUS1_03, 0x00);
}

//--------------------------------------------------
// Description  : Set pin share
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscSetPinShare(void)
{
    // V016 System Patch Note (17) Modify 20100825 Start
    // Patch Reason : Select CR[1F]-bit5:4 to Pin Share Part.
    if(CScalerGetBit(_V8_YUV_CONVERSION_1F, _BIT5 | _BIT4) != 0x10)
    {
        CScalerSetBit(_V8_YUV_CONVERSION_1F, ~(_BIT5 | _BIT4), _BIT5);
    }
    // V016 System Patch Note (17) Modify 20100825 End

#if(_SCALER_TYPE == _RTD2472D)
#if(_MCU_TYPE == _REALTEK_EMBEDDED)

    MCU_PIN_SHARE_CTRL00_FF94 = (((BYTE)_PIN_41 << 6) | (_PIN_42 << 4) | (_PIN_43 << 2) | (_PIN_54));
    MCU_PIN_SHARE_CTRL01_FF95 = (((BYTE)_PIN_45 << 6) | (_PIN_119 << 3) | (_PIN_126));
    MCU_PIN_SHARE_CTRL02_FF96 = (((BYTE)_PIN_58_59_DDC1_ENABLE << 7) | (_PIN_58 << 4) | (_PIN_59 << 1));
    MCU_PIN_SHARE_CTRL03_FF97 = (((BYTE)_PIN_46 << 6) | (_PIN_51 << 4) | (_PIN_64));
    MCU_PIN_SHARE_CTRL04_FF98 = (((BYTE)_PIN_52 << 6) | (_PIN_66 << 3) | (_PIN_67));
    MCU_PIN_SHARE_CTRL05_FF99 = (((BYTE)_PIN_53 << 6) | (_PIN_69 << 3) | (_PIN_70));
    MCU_PIN_SHARE_CTRL06_FF9A = (((BYTE)_PIN_47 << 6) | (_PIN_55 << 3) | (_PIN_63));
    MCU_PIN_SHARE_CTRL07_FF9B = (((BYTE)_PIN_48 << 6) | (_PIN_68 << 3) | (_PIN_71));
    MCU_PIN_SHARE_CTRL08_FF9C = (((BYTE)_PIN_44 << 5) | (_PIN_96 << 3) | (_PIN_97));
    MCU_PIN_SHARE_CTRL09_FF9D = (((BYTE)_PIN_74to83 << 6) | (_PIN_99 << 3) | (_PIN_100));
    MCU_PIN_SHARE_CTRL0A_FF9E = (((BYTE)_PIN_98 << 6) | (_PIN_102 << 3) | (_PIN_105));
    MCU_PIN_SHARE_CTRL0B_FF9F = (((BYTE)_PIN_50 << 5) | (_PIN_101 << 3) | (_PIN_108));
    MCU_PIN_SHARE_CTRL0C_FFA0 = (((BYTE)_PIN_103 << 4) | (_PIN_104 << 1));
    MCU_PIN_SHARE_CTRL0D_FFA1 = (((BYTE)_PIN_109 << 4) | (_PIN_110));
    MCU_PIN_SHARE_CTRL0E_FFA2 = (((BYTE)_PIN_111 << 4) | (_PIN_112));
    MCU_PIN_SHARE_CTRL0F_FFA3 = (((BYTE)_PIN_56_57_IIC_ENABLE << 7) | (_PIN_56 << 4) | (_PIN_57 << 1));
    MCU_PIN_SHARE_CTRL10_FFA4 = (((BYTE)_PIN_113 << 5) | (_PIN_121_122_DDC3_ENABLE << 4) | (_PIN_121 << 2) | (_PIN_122));
    MCU_PIN_SHARE_CTRL11_FFA5 = (((BYTE)_PIN_65 << 5) | (_PIN_123_124_DDC2_ENABLE << 4) | (_PIN_123 << 2) | (_PIN_124));
    MCU_PIN_SHARE_CTRL12_FFA6 = (((BYTE)_PIN_72 << 5) | (_PIN_114 << 2));
#else
    pData[0] = (((BYTE)_PIN_41 << 6) | (_PIN_42 << 4) | (_PIN_43 << 2) | (_PIN_54));
    pData[1] = (((BYTE)_PIN_45 << 6) | (_PIN_119 << 3) | (_PIN_126));
    pData[2] = (((BYTE)_PIN_58_59_DDC1_ENABLE << 7) | (_PIN_58 << 4) | (_PIN_59 << 1));

    CScalerPageSelect(_PAGEE);
    CScalerWrite(_PE_PIN_SHARE_CTRL00_D4, 3, pData, _AUTOINC);

    pData[0] = (((BYTE)_PIN_46 << 6) | (_PIN_51 << 4) | (_PIN_64));
    pData[1] = (((BYTE)_PIN_52 << 6) | (_PIN_66 << 3) | (_PIN_67));
    pData[2] = (((BYTE)_PIN_53 << 6) | (_PIN_69 << 3) | (_PIN_70));
    pData[3] = (((BYTE)_PIN_47 << 6) | (_PIN_55 << 3) | (_PIN_63));
    pData[4] = (((BYTE)_PIN_48 << 6) | (_PIN_68 << 3) | (_PIN_71));
    pData[5] = (((BYTE)_PIN_44 << 5) | (_PIN_96 << 3) | (_PIN_97));
    pData[6] = (((BYTE)_PIN_74to83 << 6) | (_PIN_99 << 3) | (_PIN_100));
    pData[7] = (((BYTE)_PIN_98 << 6) | (_PIN_102 << 3) | (_PIN_105));
    pData[8] = (((BYTE)_PIN_50 << 5) | (_PIN_101 << 3) | (_PIN_108));
    pData[9] = (((BYTE)_PIN_103 << 4) | (_PIN_104 << 1));
    pData[10] = (((BYTE)_PIN_109 << 4) | (_PIN_110));
    pData[11] = (((BYTE)_PIN_111 << 4) | (_PIN_112));
    pData[12] = (((BYTE)_PIN_56_57_IIC_ENABLE << 7) | (_PIN_56 << 4) | (_PIN_57 << 1));
    pData[13] = (((BYTE)_PIN_113 << 5) | (_PIN_121_122_DDC3_ENABLE << 4) | (_PIN_121 << 2) | (_PIN_122));
    pData[14] = (((BYTE)_PIN_65 << 5) | (_PIN_123_124_DDC2_ENABLE << 4) | (_PIN_123 << 2) | (_PIN_124));
    pData[15] = (((BYTE)_PIN_72 << 5) | (_PIN_114 << 2));

    CScalerPageSelect(_PAGEE);
    CScalerWrite(_PE_PIN_SHARE_CTRL03_D7, 16, pData, _AUTOINC);
#endif
#elif((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    pData[0] = (((BYTE)_PIN_31 << 6) | (_PIN_32 << 4) | (_PIN_33 << 2) | (_PIN_34)); // Page 10-A0
    pData[1] = (((BYTE)_PIN_35 << 6) | (_PIN_36_37 << 4) | (_PIN_41)); // Page 10-A1
    pData[2] = (((BYTE)_PIN_42 << 5) | (_PIN_43 << 3) | (_PIN_44)); // Page 10-A2
    pData[3] = (((BYTE)_PIN_45 << 6) | (_PIN_46 << 4) | (_PIN_47 << 2) | (_PIN_48)); // Page 10-A3
    pData[4] = (((BYTE)_PIN_50 << 5) | (_PIN_51 << 3) | (_PIN_55)); // Page 10-A4
    pData[5] = (((BYTE)_PIN_52 << 6) | (_PIN_65 << 3) | (_PIN_66)); // Page 10-A5
    pData[6] = (((BYTE)_PIN_53 << 6) | (_PIN_67 << 3) | (_PIN_68)); // Page 10-A6
    pData[7] = (((BYTE)_PIN_54 << 6) | (_PIN_69 << 3) | (_PIN_70)); // Page 10-A7
    pData[8] = (((BYTE)_PIN_56_57_IIC_ENABLE << 6) | (_PIN_56 << 3) | (_PIN_57)); // Page 10-A8
    pData[9] = (((BYTE)_PIN_58_59_DDC1_ENABLE << 6) | (_PIN_58 << 3) | (_PIN_59)); // Page 10-A9
    pData[10] = (((BYTE)_PIN_63 << 4) | (_PIN_64)); // Page 10-AA
    pData[11] = (((BYTE)_PIN_71 << 5) | (_PIN_72 << 2) | (_PIN_74to83)); // Page 10-AB
    pData[12] = (((BYTE)_PIN_99 << 5) | (_PIN_100 << 3) | (_PIN_102)); // Page 10-AC
    pData[13] = (((BYTE)_PIN_96 << 6) | (_PIN_103 << 3) | (_PIN_104)); // Page 10-AD
    pData[14] = (((BYTE)_PIN_97 << 6) | (_PIN_105 << 3) | (_PIN_108)); // Page 10-AE
    pData[15] = (((BYTE)_PIN_109 << 4) | (_PIN_110to114_MIRROR << 3) | (_PIN_110)); // Page 10-AF

    CScalerPageSelect(_PAGE10);
    CScalerWrite(_P10_PIN_SHARE_CTRL00_A0, 16, pData, _AUTOINC);

    pData[0] = (((BYTE)_PIN_98 << 6) | (_PIN_111 << 3) | (_PIN_112)); // Page 10-B0
    pData[1] = (((BYTE)_PIN_101 << 6) | (_PIN_113 << 3) | (_PIN_114)); // Page 10-B1
    pData[2] = (((BYTE)_PIN_119 << 5) | (_PIN_121_122_DDC3_ENABLE << 4) | (_PIN_121 << 2) | (_PIN_122)); // Page 10-B2
    pData[3] = (((BYTE)_PIN_123_124_DDC2_ENABLE << 7) | (_PIN_123 << 5) | (_PIN_124 << 3) | (_PIN_126)); // Page 10-B3

    CScalerPageSelect(_PAGE10);
    CScalerWrite(_P10_PIN_SHARE_CTRL10_B0, 4, pData, _AUTOINC);

#elif(_SCALER_TYPE == _RTD2545LR)
    pData[0] = (((BYTE)_PIN_44 << 2) | (_PIN_43));

    CScalerPageSelect(_PAGEE);
    CScalerWrite(_PE_PIN_SHARE_CTRL01_D5, 1, pData, _AUTOINC);
#else
    No Setting  !!
#endif  // End of #if(_SCALER_TYPE == _RTD2472D)

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
#if(_PCB_TYPE == _RTD2472D_DEMO_PCB) // For 6048
    // Output Enable
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0xC3);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x02);
    HW_PROTECT_PIN_LOW();
#elif(_PCB_TYPE == _RTD2472RD_DEMO_PCB) // For 6049
    HW_PROTECT_PIN_LOW();
#endif
*/
    CMiscConfigureFlashWPPinLow();
// V015 System Patch Note (7) Modify 20100630 End
}

//----------------------------------------------------------------------------------------------------
// Debug Functions
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// Description  : ISP process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscIspack(void)
{
#if(_DEBUG_TOOL == _ISP_FOR_RTD2120)

    BYTE halt = 0;

    do
    {
        if(bRunCommand)
        {
            switch(ucDdcciData[0])
            {
                case 0x80:
                    halt = ucDdcciData[1];

                    break;

                case 0x41:
                    CScalerRead(ucDdcciData[1], 1, pData, _NON_AUTOINC);
                    TxBUF = pData[0];
                    MCU_I2C_DATA_OUT_FF2A = pData[0];
                    break;

                case 0x44:
                    CI2cRead(NVRAM_LINE,ucDdcciData[2], ucDdcciData[1], 1, pData);
                    TxBUF = pData[0];
                    MCU_I2C_DATA_OUT_FF2A = pData[0];
                    break;

                default:
                    switch (ucDdcciData[0] & 0x0F)          //Write command
                    {
                        case 0x00:
                            CScalerSetByte(ucDdcciData[2], ucDdcciData[1]);
                            break;

                        case 0x01:
                        case 0x02:                          // for RTD & I2c Device
                            ucDdcciData[2] = ucDdcciData[1];
                            break;

                        case 0x06:
                        case 0x03:                          //for I2c Device
                            ucDdcciData[3] = ucDdcciData[1];
                            break;

                        case 0x04:                         //for I2c Device
                            CI2cWrite(NVRAM_LINE,ucDdcciData[2], ucDdcciData[1], 1, ucDdcciData + 3);
                            break;
                    }
                    break;
            }

            bRunCommand = 0;
            g_ucDdcciCommandNumber = 0;
        }
    }
    while(halt != 0);

#endif  // End of #if(_DEBUG_TOOL == _ISP_FOR_RTD2120)


#if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
    BYTE halt = 0;
    BYTE cnt = 0;

    // V015 System Patch Note (7) Modify 20100630 Start
    // Patch Reason : New EEPROM emulation process.
#if((_MEMORY_LOCATION == _FLASH) && ((_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH) || (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH)))
#if(_FLASH_XDATA_ACCESS == _ON)
    BYTE xdata *pFlashData = 0x0000;
#endif
#endif
    // V015 System Patch Note (7) Modify 20100630 End

#if(_DDCCI_SUPPORT == _ON)
    if(GET_DDCCI_STATUS())
    {
        return;
    }
#endif

    do
    {
        if(bRunCommand)
        {
            cnt = 0;
            switch(ucDdcciData[0])
            {
                case 0x80:
                    halt = ucDdcciData[1];
                    break;

                case 0x41:
                    MCU_I2C_IRQ_CTRL2_FF2A |= 0x20;
                    /*
                    MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                    */
                    CScalerRead(ucDdcciData[1], 1, pData, _NON_AUTOINC);
                    /*
                    TxBUF= pData[0];
                    MCU_I2C_DATA_OUT_FF26 = pData[0];
                    */
                    do
                    {
                        MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                        MCU_I2C_DATA_OUT_FF26 = pData[0];

                    }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                    break;

                case 0x44:
                    MCU_I2C_IRQ_CTRL2_FF2A |= 0x20;
                    /*
                    MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                    */
                    CI2cRead(NVRAM_LINE,ucDdcciData[2], ucDdcciData[1], 1, pData);
                    /*
                    TxBUF= pData[0];
                    MCU_I2C_DATA_OUT_FF26 = pData[0];
                    */
                    do
                    {
                        MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                        MCU_I2C_DATA_OUT_FF26 = pData[0];

                    }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                    break;

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
                case 0x2F:  //Debug Message Event finsih
                    MCU_I2C_IRQ_CTRL2_FF2A |= 0x20;
                    do
                    {
                        MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                        MCU_I2C_IRQ_CTRL2_FF2A &= 0xBF; //Reset IIC Data Buffer
                        MCU_I2C_DATA_OUT_FF26 = 0xF5;

                    }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));

                    MCU_I2C_IRQ_CTRL2_FF2A &= 0xDF;
                    g_bDebugMessageStart = 0;
                    g_bFwHalt = _FALSE;
                    g_bDebugMessageEven = 0;
                    break;
#endif  // End of #if(_DEBUG_MESSAGE_SUPPORT == _ON)

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
#if((_MEMORY_LOCATION == _FLASH) && ((_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH) || (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH)))
#if(_FLASH_XDATA_ACCESS == _ON)
                case 0x35:
                    TxBUF = _START_PAGE;
                    MCU_I2C_DATA_OUT_FF26 = _START_PAGE;
                    break;

                case 0x36:
                    TxBUF = _MISC_PAGE;
                    MCU_I2C_DATA_OUT_FF26 = _MISC_PAGE;
                    break;

                case 0x37:
                    // Initial _MISC_PAGE
                    CFlashInitialMISCPageStart();
                    break;

                case 0x38:
                    // Restore _MISC_PAGE
                    CFlashInitialMISCPageEnd();
                    break;

                    ////////////////0x3A command define////////////////////////////////////////////
                    // g_ucDdcciData[1] (Bit7 ~ Bit3 = page number,    Bit2 ~ Bit0 = index number) //
                    // g_ucDdcciData[2] (Bit7 ~ Bit1 = ID number,      Bit0 Reserved )             //
                    // address = page * 1024 + ID * 8 + index                                    //
                    ///////////////////////////////////////////////////////////////////////////////

                case 0x3A:
                    TxBUF = pFlashData[(ucDdcciData[2] << 8) + ucDdcciData[1]];
                    MCU_I2C_DATA_OUT_FF26 = pFlashData[(ucDdcciData[2] << 8) + ucDdcciData[1]];
                    break;

                case 0x3B:
                    CFlashWREN((BYTE)(ucDdcciData[2] >> 4));
                    pFlashData[(ucDdcciData[2] << 8) + ucDdcciData[1]] = ucDdcciData[3];
                    CFlashWRDis();
                    break;
#endif // End of #if(_FLASH_XDATA_ACCESS == _ON)
#endif // End of #if((_MEMORY_LOCATION == _FLASH) && ((_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH) || (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH)))
// V015 System Patch Note (7) Modify 20100630 End

                default:
                    switch (ucDdcciData[0] & 0x0F)          //Write command
                    {
                        case 0x00:
                            CScalerSetByte(ucDdcciData[2], ucDdcciData[1]);
                            break;

                        case 0x01:
                        case 0x02:                          // for RTD & I2c Device
                            ucDdcciData[2] = ucDdcciData[1];
                            break;

                        case 0x06:
                        case 0x03:                          //for I2c Device
                            ucDdcciData[3] = ucDdcciData[1];
                            break;

                        case 0x04:                         //for I2c Device
// for RTD TOOL WRITE AND READ 24C16 SJP20110629
#if((_PCB_TYPE == _RTD2472D_DEMO_PCB) || (_PCB_TYPE == _RTD2472RD_DEMO_PCB) || (_PCB_TYPE == _RTD2545LR_QA_PCB) || (_PCB_TYPE == _RTD2472RD_DEMO_PCB) || (_PCB_TYPE == _RTD2472RD_QA_PCB)) //||(_PCB_TYPE == _RTD2472D_QA_PCB)||(_PCB_TYPE == _RTD2472RD_QA_PCB))
    bEEPROM_WRITE_PROTECT = _LOW;
#endif
                            CI2cWrite(NVRAM_LINE,ucDdcciData[2], ucDdcciData[1], 1, ucDdcciData + 3);
CI2cWritePolling(NVRAM_LINE,ucDdcciData[2]);
CEepromLoadLSlumiData();//sjp20110715
CEepromLoadPWMlumiData();//SJP20110715
#if((_PCB_TYPE == _RTD2472D_DEMO_PCB) || (_PCB_TYPE == _RTD2472RD_DEMO_PCB) || (_PCB_TYPE == _RTD2545LR_QA_PCB) || (_PCB_TYPE == _RTD2472RD_DEMO_PCB) || (_PCB_TYPE == _RTD2472RD_QA_PCB)) //||(_PCB_TYPE == _RTD2472D_QA_PCB)||(_PCB_TYPE == _RTD2472RD_QA_PCB))
    bEEPROM_WRITE_PROTECT = _HIGH;
#endif						
     //                       CI2cWrite(NVRAM_LINE,ucDdcciData[2], ucDdcciData[1], 1, ucDdcciData + 3);
                            break;
                    }
                    break;
            }

            bRunCommand = 0;

            g_ucDdcciCommandNumber = 0;

            // V012 Modify 20100324 Start
            // V012 Patch Note (23) : Fix the issue that DDC debug could not read in power saving.
            // Host write Enable
            MCU_I2C_IRQ_CTRL2_FF2A &= (~_BIT5);
            // V012 Modify 20100324 End

#if(_DDC_CHANNEL_SEL == _HDMI_DDC_CHANNEL)
            MCU_HDMI_DDC_CTRL2_FF2E &= 0xFE;
#elif(_DDC_CHANNEL_SEL == _DVI_DDC_CHANNEL)
            MCU_DVI_DDC_CTRL2_FF20 &= 0xFE;
#else
            MCU_ADC_DDC_CTRL2_FF1D &= 0xFE;
#endif
        }
    }
    while(halt != 0);
#endif  // End of #if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
}


#if(_DEBUG_TOOL == _ISP_FOR_RTD2120)
//--------------------------------------------------
// Description  : ISP for RTD2120 Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcciInitial(void)
{
#if(_DDCCI_SUPPORT == _ON)
    MCU_I2C_SET_SLAVE_FF27 = 0x6e;
#elif(_DDC_CHANNEL_SEL == _VGA_DDC_CHANNEL)

    MCU_I2C_SET_SLAVE_FF27 = 0x6a;
#else
    MCU_I2C_SET_SLAVE_FF27 = 0x6b;
#endif

    MCU_I2C_IRQ_CTRL_FF2C = 0x3f;
    MCU_PIN_SHARE1_FF01 = MCU_PIN_SHARE1_FF01 | 0x01;
    MCU_OPTION_FF38 = 0x80;

    //CScalerSetByte(_DDC_SET_SLAVE_F4 , 0x00);
    EA = 1;
    EX0 = 1;
    IE = 0x8e;

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    CDebugMessage("######    F/W START    ######", _NO_VALUE);
#endif

    CScalerSetByte(_DDC_SET_SLAVE_F4, 0x00);
}
#endif  // End of #if(_DEBUG_TOOL == _ISP_FOR_RTD2120)


#if((_DEBUG_TOOL == _ISP_FOR_EMBEDDED) || (_DEBUG_TOOL == _RS232))
//--------------------------------------------------
// Description  : ISP for RTD Embeded MCU Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDdcciInitial(void)
{
#if(_DDCCI_SUPPORT == _ON)
    MCU_I2C_SET_SLAVE_FF23 = 0x6e & (~_BIT0);
#else
    MCU_I2C_SET_SLAVE_FF23 = 0x6a;
#endif

#if((_DEBUG_TOOL == _ISP_FOR_EMBEDDED) && (_DDCCI_SUPPORT == _OFF))
    MCU_I2C_IRQ_CTRL_FF28 = 0x16;
#elif(_DDCCI_SUPPORT == _ON)
    MCU_I2C_IRQ_CTRL_FF28 = 0x3F;
#else
    MCU_I2C_IRQ_CTRL_FF28 = 0x3F;
#endif

    MCU_IRQ_PRIORITY_FF01 = 0x01;     //assign int1 (IRQ2)

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
#if(_EMBEDDED_EDID == _ON)
    MCU_ADC_DDC_ENA_FF1B = 0x07;
    MCU_DVI_DDC_ENA_FF1E = 0x07;
    MCU_HDMI_DDC_ENA_FF2C = 0x07;
#else
    MCU_ADC_DDC_ENA_FF1B = 0xe2;
#if(((_DDC_CHANNEL_FOR_D0 == _DDC2) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)) || ((_DDC_CHANNEL_FOR_D1 == _DDC2) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)))
    MCU_DVI_DDC_ENA_FF1E = 0x07;
    MCU_HDMI_DDC_ENA_FF2C = 0xe7;

#elif (((_DDC_CHANNEL_FOR_D0 == _DDC3) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)) || ((_DDC_CHANNEL_FOR_D1 == _DDC3) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)))
    MCU_DVI_DDC_ENA_FF1E = 0xe7;
    MCU_HDMI_DDC_ENA_FF2C = 0x07;
#else
    MCU_DVI_DDC_ENA_FF1E = 0xe7;
    MCU_HDMI_DDC_ENA_FF2C = 0xe7;

#endif
#endif
*/
#if(_EMBEDDED_EDID == _ON)
#if(_EDID_PRO == _ON)
    MCU_ADC_DDC_ENA_FF1B = 0x07;
    MCU_DVI_DDC_ENA_FF1E = 0x07;
    MCU_HDMI_DDC_ENA_FF2C = 0x07;
#else
    MCU_ADC_DDC_ENA_FF1B = 0x03;
    MCU_DVI_DDC_ENA_FF1E = 0x03;
    MCU_HDMI_DDC_ENA_FF2C = 0x03;
#endif // End of #if(_EDID_PRO == _ON)

#else // else of #if(_EMBEDDED_EDID == _ON)
    MCU_ADC_DDC_ENA_FF1B = 0xe2;
#if(((_DDC_CHANNEL_FOR_D0 == _DDC2) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)) || ((_DDC_CHANNEL_FOR_D1 == _DDC2) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)))
    MCU_DVI_DDC_ENA_FF1E = 0x07;
    MCU_HDMI_DDC_ENA_FF2C = 0xe7;
#elif (((_DDC_CHANNEL_FOR_D0 == _DDC3) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)) || ((_DDC_CHANNEL_FOR_D1 == _DDC3) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)))
    MCU_DVI_DDC_ENA_FF1E = 0xe7;
    MCU_HDMI_DDC_ENA_FF2C = 0x07;
#else
    MCU_DVI_DDC_ENA_FF1E = 0xe2;
    MCU_HDMI_DDC_ENA_FF2C = 0xe2;

#endif
#endif // End of #if(_EMBEDDED_EDID == _ON)
// V015 System Patch Note (7) Modify 20100630 End

#if(_DDC_CHANNEL_SEL == _HDMI_DDC_CHANNEL)
    MCU_I2C_CHANNEL_CTRL_FF2B |= 0x01;  // From HDMI DDC
#elif(_DDC_CHANNEL_SEL == _DVI_DDC_CHANNEL)
    MCU_I2C_CHANNEL_CTRL_FF2B &= 0xFE;
    MCU_I2C_SET_SLAVE_FF23 |= 0x01;     // From DVI DDC
#else
    MCU_I2C_CHANNEL_CTRL_FF2B &= 0xFE;
    MCU_I2C_SET_SLAVE_FF23 &= 0xFE;     // From ADC DDC
#endif

    // V012 Modify 20100324 Start
    // V012 Patch Note (23) : Fix the issue that DDC debug could not read in power saving.
    /*
    MCU_I2C_IRQ_CTRL2_FF2A = 0x80; //host write/read enable
    */
#if(_DDCCI_SUPPORT == _ON)
    MCU_I2C_IRQ_CTRL2_FF2A = 0x80;
#else
    MCU_I2C_IRQ_CTRL2_FF2A = 0xC0;
    MCU_I2C_STATUS_FF27 = 0;
#endif
    // V012 Modify 20100324 End

    MCU_CTRL_FFED |= 0x80;
    EA = 1;

    // Enable interrupts of External INT1
    IE |= 0x04;


#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    CDebugMessage("######    F/W START    ######", _NO_VALUE);
#endif

}
#endif  // End of #if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)


//--------------------------------------------------
// Description  : Debug tool process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscIspDebugProc(void)
{
    CMiscIspack();//uart zp0704

#if(_DEBUG_TOOL == _RS232)
    CUartHandler();
#endif


//CUartEnable();//uart zp0704
//CUartTransferNumToScr('a', 0);//uart zp0704


// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
#if((_EDID_PRO == _ON) && ((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122)))
    CMiscEdidPoc();
#endif
*/
#if((_MEMORY_LOCATION == _FLASH) && (_EDID_PRO == _ON))
    CMiscEdidPoc();
#endif
// V015 System Patch Note (7) Modify 20100630 End
}

#if((_EDID_PRO == _ON) && ((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122)))
//--------------------------------------------------
// Description  : EDID process
//               (F/W will update EDID in Eeprom or Flash
//                if DDCRAM of MCU has been modified.)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscEdidPoc(void)
{
    BYTE cnt;

    pData[0] = MCU_I2C_STATUS_FF2B;

    if(pData[0] & 0xc0) //ADC DDC Change bit
    {
        MCU_I2C_STATUS_FF2B = pData[0] & 0x3f;

        do
        {
            MCU_I2C_STATUS_FF2B &= 0x3f;
            CTimerDelayXms(100);
        }
        while(MCU_I2C_STATUS_FF2B & 0xc0);

        pData[1] = 0;

        for(cnt = 0; cnt < 128; cnt++)
        {
            if(pData[0] & 0x80)
            {
                pData[1] = (BYTE)(MCU_DDCRAM_VGA[cnt] + pData[1]);
            }
            else if(pData[0] & 0x40)
            {
                pData[1] = (BYTE)(MCU_DDCRAM_DVI[cnt] + pData[1]);
            }
        }

        if(pData[1] == 0)  //updata
        {
        /*
#if((_EDID_PRO == _ON) && (_MEMORY_LOCATION == _EEPROM))
            CEepromSaveEDIDData();
#elif((_EDID_PRO == _ON) && (_MEMORY_LOCATION == _FLASH))
            CEepromSaveEDIDToFlash();
#endif*/
        }

    }
}
#endif  // End of #if((_EDID_PRO == _ON) && ((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122)))

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
#if((_EDID_PRO == _ON) && (_MEMORY_LOCATION == _FLASH) && (_MCU_TYPE == _REALTEK_EMBEDDED))
//--------------------------------------------------
// Description  : EDID process
//               (F/W will update EDID in Eeprom or Flash
//                if DDCRAM of MCU has been modified.)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscEdidPoc(void)
{
    if(GET_EDIDPROSTATUS() == _FALSE)
    {
        SET_ADCDVIDDCSTATUS(MCU_I2C_STATUS_FF27); // Bit7 ADC DDC write bit, bit6 DVI DDC write bit.
        SET_HDMIDDCSTATUS(MCU_I2C_STATUS2_FF29); // Bit0 HDMI DDC write bit.

        if((GET_ADCDDCSTATUS() == _TRUE) || (GET_DVIDDCSTATUS() == _TRUE) || (GET_HDMIDDCSTATUS() == _TRUE)) // DDC write bit
        {
            MCU_I2C_STATUS_FF27 &= (~(_BIT7 | _BIT6));
            MCU_I2C_STATUS2_FF29 &= (~_BIT0);
            SET_EDIDPROSTATUS();

            CTimerActiveTimerEvent(SEC(0.1), CMiscSaveDDCToFlashEvent);
        }
    }
}

//--------------------------------------------------
// Description  : EDID process
//               (F/W will update EDID in Flash
//                if DDCRAM of MCU has been modified.)
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit CMiscSaveDDCToFlashEvent(void)
{
    // DDC write bit is not zero and cnt is zero, can not save EDID.
    if(((MCU_I2C_STATUS2_FF29 & _BIT0) != 0) || ((MCU_I2C_STATUS_FF27 & (_BIT7 | _BIT6)) != 0))
    {
        SET_ADCDVIDDCSTATUS(MCU_I2C_STATUS_FF27); // Bit7 ADC DDC write bit, bit6 DVI DDC write bit.
        SET_HDMIDDCSTATUS(MCU_I2C_STATUS2_FF29); // Bit0 HDMI DDC write bit.

        MCU_I2C_STATUS_FF27 &= (~(_BIT7 | _BIT6));
        MCU_I2C_STATUS2_FF29 &= (~_BIT0);

        CLR_EDIDPROSTATUS();

        return _FALSE;
    }

    if((GET_ADCDDCSTATUS() == _TRUE) || (GET_DVIDDCSTATUS() == _TRUE) || (GET_HDMIDDCSTATUS() == _TRUE))
    {
        CFlashSaveDDCData();
    }

    CLR_EDIDPROSTATUS();
    CLR_ADCDVIDDCSTATUS();
    CLR_HDMIDDCSTATUS();

    return _TRUE;
}

#endif //  End of #if((_EDID_PRO == _ON) && (_MEMORY_LOCATION == _FLASH) && (_MCU_TYPE == _REALTEK_EMBEDDED))

//--------------------------------------------------
// Description  : Configure pin share for the flash WP#
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscConfigureFlashWPPinHigh(void)
{
#if(_PCB_TYPE == _RTD2472D_DEMO_PCB) // For 6048
    // This is a reference configuration for _RTD2472D_DEMO_PCB,
    // WP# connected with pin108
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0xC3);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x02);

    MCU_PIN_SHARE_CTRL0B_FF9F = 0x01;

    HW_PROTECT_PIN_HIGH();
#elif(_PCB_TYPE == _RTD2472RD_DEMO_PCB) // For 6049
    // This is a reference configuration for _RTD2472RD_DEMO_PCB,
    // WP# connected with pin108
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0xC3);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x02);

    CScalerPageSelect(_PAGE10);

    // V016 System Patch Note (27) Modify 20100831 Start
    // Patch Reason : Modify Flash WP pin define
    /*
    CScalerSetBit(_P10_PIN_SHARE_CTRL0E_AE, ~(_BIT2 | _BIT1 | _BIT0), 0x01);
    */
    CScalerSetBit(_P10_PIN_SHARE_CTRL0E_AE, ~(_BIT2 | _BIT1 | _BIT0), _PIN_108);
    // V016 System Patch Note (27) Modify 20100831 End

    HW_PROTECT_PIN_HIGH();
#endif
}

//--------------------------------------------------
// Description  : Configure flash WP# pin to LOW
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscConfigureFlashWPPinLow(void)
{
#if(_PCB_TYPE == _RTD2472D_DEMO_PCB) // For 6048
    // Output Enable
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0xC3);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x02);
    HW_PROTECT_PIN_LOW();
#elif(_PCB_TYPE == _RTD2472RD_DEMO_PCB) // For 6049
    HW_PROTECT_PIN_LOW();
#endif
}
// V015 System Patch Note (7) Modify 20100630 End


#endif  // End of #if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

