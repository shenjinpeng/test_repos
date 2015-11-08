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
// ID Code      : Power.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __POWER__

#include "Common\Header\Include.h"

#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

//--------------------------------------------------
// Description  : Check if the power status changed
// Input Value  : None
// Output Value : Return _TRUE if power status is changed, _FALSE if not
//--------------------------------------------------
bit CPowerHandler(void)
{
    if(GET_POWERSWITCH())
    {
        CPowerControl();
        CLR_POWERSWITCH();

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Execute power up/down process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerControl(void)
{
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("CModeResetMode_CPowerControl", 0);
#endif
	CModeResetMode();

    if(GET_POWERSTATUS())       // Power Down Process
    {
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("power _off l", 0);
#endif
    
        g_usDVITMDSFreq = 0;

#if((_SCALER_TYPE == _RTD2545LR) && ((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122)))
        CScalerPageSelect(_PAGE0);
        //ADC Clock/SOG0/S0G1/Bandgap Power Off
        CScalerSetBit(_P0_ADC_POWER_C6, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0);

        //Pin_share Setting, XOUT (P6.6) GPIO Pin
        MCU_PIN_SHARE2_FF02 = 0x0E;
#endif

#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
        CLR_SOURCE_OSD_STATUS();
#endif

        CLR_POWERSTATUS();
        CPowerPanelOff();
        CPowerADCAPLLOff();
        CPowerLVDSOff();
        CPowerDPLLOff();
        CPowerPWMOff();
        CScalerDisableDisplayTiming();
        CPowerTMDSOff();

        CScalerPageSelect(_PAGE1);
        CScalerSetByte(_P1_BB_POWER0_F0, 0x00);
        CScalerSetByte(_P1_BB_POWER1_F1, 0x00);
        CScalerPageSelect(_PAGE0);
        CScalerSetBit(_P0_ADC_POWER_C6, ~(_BIT6 | _BIT5 | _BIT4 ), _BIT3);
        CScalerPageSelect(_PAGEB);
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x00);

        // Disable HDCP
        CScalerPageSelect(_PAGE2);
        CScalerSetByte(_P2_HDCP_CTRL_C0, 0x00);

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
      //CMcuSelectFlashClk(_XTAL_CLK);// for DC off high frequency noise issue 2011 0611 zhangping
      //    CTimerDelayXms(10);
#endif

        CPowerM2PLLOff();
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        CPowerMPLLOff();
#endif


#if(_SCALER_TYPE == _RTD2472D)

        CScalerPageSelect(_PAGEB);
        CScalerSetByte(_PB_DP_Z0_CALIBRATION_B6, 0x00);

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

        CScalerPageSelect(_PAGEB);
        CScalerSetByte(_PB_DP_Z0_CALIBRATION_B6, 0xF4);
#endif

        CScalerSetByte(_HOST_CTRL_01, 0x46);
        CEepromSaveSystemData();

#if(_AUDIO_SUPPORT == _ON)
        CAdjustAudioControl(_DISABLE);
#endif


#if(_DP_SUPPORT == _ON)

// HPD to Low
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    D0_HPD_LOW();
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    D1_HPD_LOW();
#endif

#endif //! end if (_DP_SUPPORT == _ON)

    }
    else    // Power Up Process
    {


bWatchDogResetCtrl=_TRUE;
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("bWatchDogResetCtrl=true", bWatchDogResetCtrl);
#endif

#if((_SCALER_TYPE == _RTD2545LR) && ((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122)))
        //Pin_share Setting, XOUT (P6.6) Clock Pin
        MCU_PIN_SHARE2_FF02 = 0x1E;
#endif

        SET_POWERSTATUS();
        CScalerInitial();

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
        MCU_SCA_INF_ADDR_FFF4 = 0x01; //DDC_addr- Host Ctrl
        MCU_SCA_INF_DATA_FFF5 = 0x00; //DDC_data - Disable power-saving mode
        CTimerDelayXms(10);
        CMcuSelectFlashClk(_FLASH_CLK);
#endif

        CEepromSaveSystemData();
#if(_DP_SUPPORT == _ON)
        SET_INPUT_SOURCE_SEARCH();
#endif //End of #if(_DP_SUPPORT == _ON)
    }
}

//--------------------------------------------------
// Description  : Set panel on process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPanelOn(void)
{
    if(GET_PANELPOWERSTATUS() == _OFF)
    {
#if(_PANEL_TYPE == _CMO_LVDS_22_WSXGA_PLUS)
        CPowerDisplayPortOn();
        CTimerDelayXms(40);
        CScalerEnableDisplayOutput();

        CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, _BIT5);
        CAdjustBackgroundColor(255, 255, 255);
        CTimerDelayXms(40);
        CPowerPanelPowerOn();
        CTimerDelayXms(250);

#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
        if((bit)CScalerGetBit(_VDISP_CTRL_28, _BIT3) || GET_FRCSTATUS())
        {
            CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00);
        }
#endif

       // CAdjustBackgroundColor(0,0,0);//Bug 2006_10_01
#else
        CPowerPanelPowerOn();
        CTimerDelayXms(_PANEL_POWER_ON_T1);
        CPowerDisplayPortOn();
        CScalerEnableDisplayOutput();
        CTimerDelayXms(_PANEL_POWER_ON_T3);
#endif
    }

    CPowerLightPowerOn();
    CMiscClearStatusRegister();
	//bData=0;
	bTimer01minCtrl= _FALSE ;// for power bug 20110804_sjp
}

//--------------------------------------------------
// Description  : Set panel off process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPanelOff(void)
{
    CPowerLightPowerOff();

#if((_PANEL_STYLE == _PANEL_TTL) || (_PANEL_STYLE == _PANEL_LVDS))

    CTimerDelayXms(_PANEL_POWER_OFF_T4);
    //     CScalerDisableDisplayOutput();

    CPowerDisplayPortOff();
    CTimerDelayXms(_PANEL_POWER_OFF_T5);
    CPowerPanelPowerOff();

#endif // End of #if((_PANEL_STYLE == _PANEL_TTL) || (_PANEL_STYLE == _PANEL_LVDS))


#if(_PANEL_STYLE == _PANEL_RSDS)

    //--- BACKLIGHT OFF TO DATA OFF TIME ---------------
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, _BIT5);
    CAdjustBackgroundColor(255, 255, 255);
    CTimerDelayXms(200);
    CScalerSetBit(_VDISP_CTRL_28, 0xDF, 0x20);//MUTE ON
    // CScalerDisableDisplayOutput();
    CPowerPanelPowerOff();
    CPowerDisplayPortOff();
    //--- DATA OFF TO PANEL OFF TIME ---------------
    CScalerSetBit(_VDISP_CTRL_28, 0xDF, 0x00);//MUTE OFF

#endif

    // The delay below is to prevent from short period between panel OFF and next ON
    CTimerDelayXms(_PANEL_POWER_OFF_T6);
}

//--------------------------------------------------
// Description  : Set panel power on
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPanelPowerOn(void)
{
    PANELPOWER_UP();
    SET_PANELPOWERSTATUS();
}

//--------------------------------------------------
// Description  : Set panel power off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPanelPowerOff(void)
{
    PANELPOWER_DOWN();
    CLR_PANELPOWERSTATUS();
}

//--------------------------------------------------
// Description  : Set backlight power on
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerLightPowerOn(void)
{
#ifdef _DEBUG_MESSAGE_SUPPORT
CDebugMessage("LIGHTPOWER_UP_CPowerLightPowerOn",0);
#endif

    LIGHTPOWER_UP();
    SET_LIGHTPOWERSTATUS();
}

//--------------------------------------------------
// Description  : Set backlight power off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerLightPowerOff(void)
{
    LIGHTPOWER_DOWN();
    CLR_LIGHTPOWERSTATUS();
}

//--------------------------------------------------
// Description  : Power on display port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerDisplayPortOn(void)
{

#if((_PANEL_STYLE == _PANEL_TTL) || (_PANEL_STYLE == _PANEL_LVDS))

    CPowerLVDSOn();

#endif

#if(_PANEL_STYLE == _PANEL_RSDS)

    CPowerRSDSOn();

#endif

}

//--------------------------------------------------
// Description  : Power off display port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerDisplayPortOff(void)
{

#if((_PANEL_STYLE == _PANEL_TTL) || (_PANEL_STYLE == _PANEL_LVDS))

    CPowerLVDSOff();

#endif // End of #if(_PANEL_STYLE == _PANEL_TTL)


#if(_PANEL_STYLE == _PANEL_RSDS)

    CPowerRSDSOff();

#endif // End of #if(_PANEL_STYLE == _PANEL_RSDS)

}

//--------------------------------------------------
// Description  : Power on LVDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerLVDSOn(void)
{
    if((bit)(_DISP_OUTPUT_PORT))
    {
        CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_LVDS_CTRL0_A0, 0x70);
    }
    else
    {
        //LVDS from even port, if from odd port, the below value should be 0x20
        CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_LVDS_CTRL0_A0, 0x70);
    }

}

//--------------------------------------------------
// Description  : Power off LVDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerLVDSOff(void)
{
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_LVDS_CTRL0_A0, 0x40);

}

#if(_PANEL_STYLE == _PANEL_RSDS)
//--------------------------------------------------
// Description  : Power on RSDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerRSDSOn(void)
{
    CPowerLVDSOn();
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 0xc6);//for 8-bit RSDS panel
    CTimerDelayXms(40);
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 0x86);
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_RSDS_PWR_CTL_C3, 0x03);
   //2007_09_05_Edward
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_LVDS_CTRL0_A0, 0x70);
}

//--------------------------------------------------
// Description  : Power off RSDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerRSDSOff(void)
{
    //Issac 2007-01-05
    CPowerLVDSOff();
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT1, _BIT1); // Force HS/VS/DEN/Data to 0
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_RSDS_PWR_CTL_C3, 0x00); //Even,Odd Port Power Off
    CTimerDelayXms(40);
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 0x48); // TTL output 0
    CTimerDelayXms(40);
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 0x42); // Back to HZ

    CScalerSetBit(_VDISP_CTRL_28, ~_BIT1, 0); // Release force
    //2007_09_05_Edward
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_LVDS_CTRL0_A0, 0x00);
}

#endif // End of #if(_PANEL_STYLE == _PANEL_RSDS)

//--------------------------------------------------
// Description  : Power on ADC and APLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerADCAPLLOn(void)
{
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_PLL_WD_AF, ~_BIT0, 0x00);     // Power up PLL

    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_POWER_C6, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));    // Power up ADC
}

//--------------------------------------------------
// Description  : Power off ADC and APLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerADCAPLLOff(void)
{
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_PLL_WD_AF, ~_BIT0, _BIT0);     // Power down PLL

    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_POWER_C6, ~(_BIT2 | _BIT1 | _BIT0), 0x00);    // Power down ADC
}

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Power on TMDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerTMDSOn(void)
{
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), 0x00);
}
#endif

//--------------------------------------------------
// Description  : Power off TMDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerTMDSOff(void)
{
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_TMDS_OUTPUT_CTRL_A6, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
}

//--------------------------------------------------
// Description  : Power off DPLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerDPLLOff(void)
{
    CScalerPageSelect(_PAGE1);
#if(_SCALER_TYPE == _RTD2472D)
    CScalerSetBit(_P1_DPLL_N_C0, ~_BIT7, _BIT7); // Power down DPLL
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerSetBit(_P1_DPLL_WD_C2, ~_BIT0, _BIT0); // Power down DPLL
#else
    No Setting !!
#endif  // End of #if(_SCALER_TYPE == _RTD2472D)
}

//--------------------------------------------------
// Description  : Power on M2PLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerM2PLLOn(void)
{
    CScalerSetBit(_HOST_CTRL_01, ~_BIT1, 0x00);

    CScalerPageSelect(_PAGE1);

#if(_SCALER_TYPE == _RTD2472D)
    CScalerSetBit(_P1_MULTIPLY_PLL_CTRL3_E5, ~_BIT0, _BIT0); // Power up M2PLL
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerSetBit(_P1_M2PLL_WD_E5, ~_BIT0, 0); // Power up M2PLL
#else
    No Setting !!
#endif
}

//--------------------------------------------------
// Description  : Power off M2PLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerM2PLLOff(void)
{
#if(_MCU_TYPE == _REALTEK_EMBEDDED)
    CMcuSelectFlashClk(_XTAL_CLK);   // for DC off high frequency noise issue 2011 0611 zhangping
    CTimerDelayXms(10);

#endif
    CScalerPageSelect(_PAGE1);

#if(_SCALER_TYPE == _RTD2472D)
    CScalerSetBit(_P1_MULTIPLY_PLL_CTRL3_E5, ~_BIT0, 0x00); // Power down M2PLL
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerSetBit(_P1_M2PLL_WD_E5, ~_BIT0, _BIT0); // Power down M2PLL
#else
   No Setting !!
#endif  // End of #if(_SCALER_TYPE == _RTD2472D)

    // V013 VGA Patch Note (6) Modify 20100428 Start
    // Patch Reason : Use M2PLL as internal clock in analog source.
   CScalerSetBit(_FIFO_FREQUENCY_22, ~_BIT2, 0x00);
    // V013 VGA Patch Note (6) Modify 20100428 End
}

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
//--------------------------------------------------
// Description  : Power off MPLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerMPLLOff(void)
{
    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_MPLL_WD_F8, ~(_BIT0), _BIT0);
}
#endif //End of if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

//--------------------------------------------------
// Description  : Power on PWM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPWMOn(void)
{
#if(_SCALER_TYPE == _RTD2545LR)
    pData[0] = 0x40;
    pData[1] = 0x02;
    pData[2] = 0x10;
    CScalerWrite(_OSD_ADDR_MSB_90, 3, pData, _AUTOINC);

#elif((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    MCU_PWM_EN_FF48 |= (((BYTE)_PWM5_EN << 5) | ((BYTE)_PWM4_EN << 4) | ((BYTE)_PWM3_EN << 3) | ((BYTE)_PWM2_EN << 2) | ((BYTE)_PWM1_EN << 1) | ((BYTE)_PWM0_EN));

#endif
}

//--------------------------------------------------
// Description  : Power off PWM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPWMOff(void)
{
#if(_SCALER_TYPE == _RTD2545LR)
    pData[0] = 0x40;
    pData[1] = 0x02;
    pData[2] = 0x00;
    CScalerWrite(_OSD_ADDR_MSB_90, 3, pData, _AUTOINC);

#elif((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    MCU_PWM_EN_FF48 &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);

#endif
}

#endif  // End of #if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)


