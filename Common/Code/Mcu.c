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
// ID Code      : Mcu.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __MCU__

#include  "Common\Header\Include.h"

#if(_MCU_TYPE == _REALTEK_EMBEDDED)

//--------------------------------------------------
// RTD Embeded MCU Initial
//--------------------------------------------------
void CMcuInitial(void)
{
    IE = 0x00;                         // Disable all interrupts
    TMOD = 0x11;                         // Program Timer0 & Timer1 to Mode#1
    TR0 = 0;                            // Stop Timer0
    TF0 = 0;                            // Clear Timer0 Overflow Bit
    TL0 = _TIMER0_COUNT_LBYTE;          // Load Timer0 low-byte   (for 1ms)
    TH0 = _TIMER0_COUNT_HBYTE;          // Load Timer0 high-byte  (for 1ms)
    TR1 = 0;                            // Stop Timer1
    TF1 = 0;                            // Clear Timer1 Overflow Bit
    IE = 0x82;                         // Enable interrupts of Timer0
    IP |= 0x02;                        // Set Interrupt Priority (Timer0)

    CKCON = 0x00;

    // Enable Program OP Code
    MCU_PROG_OP_CODE_FF6D = 0x02;

    // V015 System Patch Note (7) Modify 20100630 Start
    // Patch Reason : New EEPROM emulation process.
#if(_AUTO_DETECT_FLASH_TYPE == _ON)
    CFlashCheckFlashType();  // FW Auto Detect Flash type
#else
    g_ucFlashType = _FLASH_TYPE - 1;
#endif
    // V015 System Patch Note (7) Modify 20100630 End

#if(_SCALER_TYPE == _RTD2472D)
    MCU_REV_DUMMY2_FF19 = 0x60; // for S53 DVD player
#endif

    MCU_COMM_INST_EN_FF60 = 0x42;
    MCU_COMM_OP_CODE_FF61 = 0x05;
    MCU_COMM_INST_EN_FF60 = 0x43;
    MCU_WREN_OP_CODE_FF62 = 0x06;

    pData[0] = MCU_COMM_INST_READ_P0_FF67;

    if(pData[0] != 0x9C)
    {
        // V015 System Patch Note (7) Modify 20100630 Start
        // Patch Reason : New EEPROM emulation process.
        /*
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
        CScalerSetBit(_P10_PIN_SHARE_CTRL0E_AE, ~(_BIT2 | _BIT1 | _BIT0), 0x01);

        HW_PROTECT_PIN_HIGH();
#endif

        MCU_COMM_INST_EN_FF60 = 0x68;
        */
        CMiscConfigureFlashWPPinHigh();

        // Write 1 instruction after WREN
        if(GET_FLASH_TYPE_INDEX() == _FLASH_SST25LF020A)
        {
            MCU_COMM_INST_EN_FF60 = 0x88;
        }
        else
        {
            MCU_COMM_INST_EN_FF60 = 0x68;
        }
        // V015 System Patch Note (7) Modify 20100630 End

        MCU_COMM_OP_CODE_FF61 = 0x01;

        // V015 System Patch Note (7) Modify 20100630 Start
        // Patch Reason : New EEPROM emulation process.
        /*
        MCU_FLASH_PROG_ISP0_FF64 = 0x9C; //SRP, BP0 ~ BP2

        MCU_COMM_INST_EN_FF60 = 0x69;
        */
        // Protect all memory address
        MCU_FLASH_PROG_ISP0_FF64 = CFlashGetFlashDetailedInfo(g_ucFlashType, _FLASH_INFO_WRSR_PROTECT);

        // Write 1 instruction after WREN, common instruction enable
        MCU_COMM_INST_EN_FF60 = MCU_COMM_INST_EN_FF60 | _BIT0;
        // V015 System Patch Note (7) Modify 20100630 End
    }

    // Disable Program OP Code
    MCU_PROG_OP_CODE_FF6D = 0xFF;

    // Disable OP code
    MCU_COMM_OP_CODE_FF61 = 0xFF;

    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_POWER_ON_RESET_F3, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

// Set LVDS default current = 3.5mA , the IC default is 2.5mA.
#if(_SCALER_TYPE == _RTD2472D)
    MCU_PIN_DRIV_CTRL11_FFA7 = 0x08;
#elif((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerPageSelect(_PAGE10);
    CScalerSetByte(_P10_PIN_DRIVING_CTRL0_B4, 0x04);
#elif(_SCALER_TYPE == _RTD2545LR)
    CScalerPageSelect(_PAGEE);
    CScalerSetByte(_PE_PIN_DRIVING_CTRL10_D8, 0x20);
#else
    No Setting !!
#endif // End of #if(_SCALER_TYPE == _RTD2472D)

    MCU_ADC_DDC_CTRL1_FF1C = 0xF0;

#if(_D0_INPUT_PORT_TYPE != _D0_DP_PORT)
    MCU_DVI_DDC_CTRL1_FF1F = 0xF0;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_DP_PORT)
    MCU_HDMI_DDC_CTRL1_FF2D = 0xF0;
#endif


    MCU_DDCRAM_PART_FF21 = 0x16; // ddc1 128, ddc2 256, ddc3 256

    // cec setting
    MCU_CEC_CR0_FFAB = 0x5f;

    MCU_WATCHDOG_TIMER_FFEA |= 0x80;         //enable wdt, V009_20080822
    MCU_WATCHDOG_TIMER_FFEA |= 0x40;         //clr wdt.


    MCU_CTRL_FFED = 0x80;          //FlashDIV=1
#if(_EMBEDDED_EDID == _ON)
    MCU_ADC_DDC_ENA_FF1B = 0x02;
    MCU_DVI_DDC_ENA_FF1E = 0x02;
    MCU_HDMI_DDC_ENA_FF2C = 0x02;
#else
    MCU_ADC_DDC_ENA_FF1B = 0xe2;
#if(((_DDC_CHANNEL_FOR_D0 == _DDC2) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)) || ((_DDC_CHANNEL_FOR_D1 == _DDC2) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)))
    MCU_DVI_DDC_ENA_FF1E = 0x02;
    MCU_HDMI_DDC_ENA_FF2C = 0xe2;
#else
    MCU_DVI_DDC_ENA_FF1E = 0xe2;
    MCU_HDMI_DDC_ENA_FF2C = 0x02;
#endif
#endif

    MCU_BANK_SWITCH_CTRL_FFFC = 0x0F;   // enable global XFR (For Bank Switching System)

    // V015 System Patch Note (7) Modify 20100630 Start
    // Patch Reason : New EEPROM emulation process.
    /*
    MCU_BANK_START_FFFD = 0x02;                                 // Xdata_Bstart
    MCU_BANK_SEL_FFFE = (_FLASH_BANK - MCU_BANK_START_FFFD);    // Xdata_bank_sel, Bank0
    */
    MCU_BANK_START_FFFD = _XDATA_START_BANK; // Xdata_Bstart
    MCU_BANK_SEL_FFFE = (_FLASH_BANK - _XDATA_START_BANK); // Xdata_bank_sel, Bank3
    // V015 System Patch Note (7) Modify 20100630 End


    MCU_CLOCK_CTRL_FFEE |= 0x40;        // non-stop timer when spi flash access

#if(_FAST_READ == _ON)

    //   M2PLL Enable
    MCU_SCA_INF_CTRL_FFF3 = 0x20; //BWR data enable, Non_INC
    MCU_SCA_INF_ADDR_FFF4 = 0x9f; //DDC_addr
    MCU_SCA_INF_DATA_FFF5 = 0x01; //DDC_data, page-1
    MCU_SCA_INF_ADDR_FFF4 = 0xE0; //M2-PLL Reg Ctrl Address
    MCU_SCA_INF_DATA_FFF5 = 0x10; //Enable M code =18
    MCU_SCA_INF_ADDR_FFF4 = 0xE4; //M2-PLL Reg Ctrl Address
    MCU_SCA_INF_DATA_FFF5 = 0x01; //Enable P code= 2

    //  Power-saving mode Enable ?
    MCU_SCA_INF_ADDR_FFF4 = 0x01; //DDC_addr - Host Ctrl
    MCU_SCA_INF_DATA_FFF5 = 0x00; //DDC_data - Disable power-saving mode

    //  M2PLL output enable
    MCU_SCA_INF_ADDR_FFF4 = 0xE5; //M2-PLL Reg Ctrl Address
    MCU_SCA_INF_DATA_FFF5 = 0x09; //Enable M2PLL


    //  Enable FastRead mode
    MCU_CEN_CTRL_FF76 = ( ((0x3) << 4) | ((0x1) << 2) | ((0x1) << 0) );  //ChipEnable Timing Setup

#if (_TURBO_MODE == _ON)
    MCU_FAST_READ_OP_CODE_FF6B = 0x3B;  //Fast Dual data read for winbond flash only
    MCU_READ_INSTRUCTION_FF6C |= ( ((0x2) << 6) | ((0x1) << 5) | ((0x0) << 4) | ((0x0) << 2) | ((0x0) << 0) ); //Fast Read mode, DI@half cycle, Dout@one cycle
#else
    MCU_FAST_READ_OP_CODE_FF6B = 0x0B;  //Fast Read for all kind of flash
    MCU_READ_INSTRUCTION_FF6C |= ( ((0x1) << 6) | ((0x1) << 5) | ((0x0) << 4) | ((0x0) << 2) | ((0x0) << 0) ); //Fast Read mode, DI@half cycle, Dout@one cycle
#endif // End of #if (_TURBO_MODE==_ON)

//  CMcuSelectFlashClk(_FLASH_CLK);

#endif // End of #if(_FAST_READ == _ON)

// GPIO Control By PCB Type
#if((_PCB_TYPE == _RTD2472D_DEMO_PCB) || (_PCB_TYPE == _RTD2472RD_DEMO_PCB) || (_PCB_TYPE == _RTD2472D_QA_PCB) || (_PCB_TYPE == _RTD2472RD_QA_PCB))

    MCU_PORTC_PIN_REG_FFE6 = 0xC0;
    MCU_PORT_READ_CTRL_FFC0 = 0xfd;     //read All GPIO value from bus,except p3

//PWM 0
    MCU_PWM_CK_SEL_FF3A = 0x01;  // PWM0 PLL output
    MCU_PWM03_M_FF3B = 0x00;     // PWM0 first stage Divider [1:0]
    MCU_PWM01_N_MSB_FF3D = 0x05; // PWM0 second stage Divider MSB [11:8]
    MCU_PWM0_N_LSB_FF3E = 0x00;  // PWM0 second stage Divider LSB [7:0]
    MCU_PWM_VS_CTRL_FF47 = 0x01; // Enable PWM0 reset by DVS
    MCU_PWM_EN_FF48 = 0x81;      // PWM0 output Enable
    MCU_PWM_CK_FF49 = 0x01;      // PWM0 second stage output

#else
    No Setting !!

#endif

}

//--------------------------------------------------
// RTD Embeded MCU Setting
//-------------------------------------------------
/*
#if(_FAST_READ == _ON)
*/
void CMcuFlashClkDiv(BYTE clkdiv) // _FlashClkDiv(x=0-15): SPI Flash Clock Generator (OSC/PLL°£¥HDIV:from 0~15)
{
    clkdiv &= 0x0F;
    clkdiv = (clkdiv << 2);
    clkdiv |= (MCU_CTRL_FFED & 0xC3);
    MCU_CTRL_FFED = clkdiv;
}

void CMcuClkDiv(BYTE clkdiv)  // _MCUClkDiv(x=0-15): 8051 Clock Generator (Flash_Clk/DIV:from 0~15)
{
    clkdiv &= 0x0F;
    clkdiv = (clkdiv << 2);
    clkdiv |= (MCU_CLOCK_CTRL_FFEE & 0xC3);
    MCU_CLOCK_CTRL_FFEE = clkdiv;
}

void CMcuSelectFlashClk(bit select)
{
    if(select)//flash clk
    {
        CPowerM2PLLOn();
        CTimerDelayXms(10);

        CMcuFlashClkDiv(_FLASH_CLK_DIV);     // Flash CLK
        CMcuClkDiv(_MCU_CLK_DIV);            // MCUCLK = FLASH CLK / [( FLASH CLK > 48MHz ) ? _DIV_2 : _DIV_1 )]
        MCU_CTRL_FFED |= 0x02;               // Switch to PLL
    }
    else  // Xtal clock
    {
        MCU_CTRL_FFED &= 0xc1;//eric0108,set SPI-flash clk from xtal
        CMcuFlashClkDiv(_DIV_1);
        CMcuClkDiv(_DIV_1);
    }
}
/*
#endif //End of #if(_FAST_READ == _ON)
*/
#endif  // End of #if(_MCU_TYPE == _REALTEK_EMBEDDED)


//--------------------------------------------------
// RTD2120 MCU Initial
//--------------------------------------------------
#if((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122))
void CMcuInitial(void)
{
    IE = 0x00;                         // Disable all interrupts
    TMOD = 0x11;                         // Program Timer0 & Timer1 to Mode#1
    TR0 = 0;                            // Stop Timer0
    TF0 = 0;                            // Clear Timer0 Overflow Bit
    TL0 = _TIMER0_COUNT_LBYTE;          // Load Timer0 low-byte   (for 1ms)
    TH0 = _TIMER0_COUNT_HBYTE;          // Load Timer0 high-byte  (for 1ms)
    TR1 = 0;                            // Stop Timer1
    TF1 = 0;                            // Clear Timer1 Overflow Bit
    IE = 0x8a;                         // Enable interrupts of Timer0
    CKCON = 0x00;                         // Stretch Memory Cycle = 0     // For EDID issue


    // We should modify the LVR voltage in RTD2120 series due to ISP fail issue.
    MCU_LVRST_CTRL_FF0A = 0xc0;             // LVR voltage = 2.4V.

    // To solve the data loss issue when using page erase in ISP mode.
    MCU_FC_PAGE_ERASE1_FF91 = 0x7f;         // Page address for page erase.


//----------------------------------------------------------------------------------------------------
// RTD2472D QA Board & RTD2545LR QA Board
//----------------------------------------------------------------------------------------------------
#if((_PCB_TYPE == _RTD2472D_QA_PCB) || (_PCB_TYPE == _RTD2545LR_QA_PCB) || (_PCB_TYPE == _RTD2472RD_QA_PCB))

//--------IO Config -----------------------

    MCU_PIN_SHARE0_FF00 = 0x40;
    MCU_PIN_SHARE1_FF01 = 0x41;
//    MCU_PIN_SHARE2_FF02         = 0x01;
    MCU_PIN_SHARE2_FF02 = 0x10;

#if(_HDCP_SUPPORT == _ON)
    MCU_PORT5_OE_FF03 = 0x30;
#else
    MCU_PORT5_OE_FF03 = 0x20;
#endif

    MCU_PORT6_OE_FF04 = 0xf0;
    MCU_PORT7_OE_FF05 = 0xc0;
    MCU_PORT1_TYPE_FF09 = 0x00;

    MCU_ADC_DDC_ENA_FF20 = 0x07;
    MCU_DVI_DDC_ENA_FF23 = 0x07;

#if(_MCU_TYPE == _REALTEK_RTD2122)
    MCU_BANK_SWITCH_CTRL_FFFC = 0x02; // Using Pbank Switch
    MCU_BANK_SEL_FFFE = 0x00;         // Xdata_bank_sel, Bank0
#endif


//--------End IO Config -------------------

#endif  // End of #if((_PCB_TYPE == _RTD2472D_QA_PCB) || (_PCB_TYPE == _RTD2545LR_QA_PCB))

#if(_PCB_TYPE == _RTD2545LR_QA_PCB)

//--------IO Config -----------------------

    MCU_PIN_SHARE0_FF00 = 0x00;
    MCU_PIN_SHARE1_FF01 = 0x41;
//    MCU_PIN_SHARE2_FF02         = 0x01;
    MCU_PIN_SHARE2_FF02 = 0x10;

#if(_HDCP_SUPPORT == _ON)
    MCU_PORT5_OE_FF03 = 0xB0;
#else
    MCU_PORT5_OE_FF03 = 0xA0;
#endif

    MCU_PORT6_OE_FF04 = 0xf0;
    MCU_PORT7_OE_FF05 = 0xc0;
    MCU_PORT1_TYPE_FF09 = 0x00;

    MCU_ADC_DDC_ENA_FF20 = 0x07;
    MCU_DVI_DDC_ENA_FF23 = 0x07;

#if(_MCU_TYPE == _REALTEK_RTD2122)
    MCU_BANK_SWITCH_CTRL_FFFC = 0x02; // Using Pbank Switch
    MCU_BANK_SEL_FFFE = 0x00;         // Xdata_bank_sel, Bank0
#endif

#endif
//----------------------------------------------------------------------------------------------------
// RTD2545LR Demo Board
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RTD2545LR_DEMO_PCB)

//--------IO Config -----------------------

    MCU_PIN_SHARE0_FF00 = 0x40;
    MCU_PIN_SHARE1_FF01 = 0x41;
    MCU_PIN_SHARE2_FF02 = 0x16;
    MCU_PORT5_OE_FF03 = 0x3D;
    MCU_PORT6_OE_FF04 = 0xd8;
    MCU_PORT7_OE_FF05 = 0x40;
    MCU_PORT1_TYPE_FF09 = 0x00;

    MCU_ADC_DDC_ENA_FF20 = 0x07;
    MCU_DVI_DDC_ENA_FF23 = 0x07;


#if(_MCU_TYPE == _REALTEK_RTD2122)
    MCU_BANK_SWITCH_CTRL_FFFC = 0x02; // Using Pbank Switch
    MCU_BANK_SEL_FFFE = 0x00;         // Xdata_bank_sel, Bank0
#endif
//--------End IO Config -------------------

#endif  // End of #if(_PCB_TYPE == _RTD2545LR_DEMO_PCB)

}

#endif  // End of #if((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122))

