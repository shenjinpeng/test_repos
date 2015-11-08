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

#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)

//----------------------------------------------------------------------------------------------------
// Basic Settings
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Scalar Type
//--------------------------------------------------
#define _RTD2472D                               0    // Code ID : 0x01
#define _RTD247xRD                              1    // Code ID : 0x08
#define _RTD248xRD                              2    // Code ID : 0x08
#define _RTD2545LR                              3    // Code ID : 0x51

#define _SCALER_TYPE                            _RTD247xRD

//--------------------------------------------------
// MCU Type
//--------------------------------------------------
#define _REALTEK_EMBEDDED                       0
#define _REALTEK_RTD2120                        1
#define _REALTEK_RTD2122                        2

#define _MCU_TYPE                               _REALTEK_EMBEDDED

//--------------------------------------------------
// Definations of RTD/MCU Crystal Frequency in KHz
//--------------------------------------------------
#define _XTAL27000K                             27000
#define _XTAL24000K                             24000

#define _RTD_XTAL                               _XTAL27000K
#if(_MCU_TYPE == _REALTEK_EMBEDDED)
#define _MCU_XTAL                               _XTAL27000K
#else
#define _MCU_XTAL                               _XTAL24000K
#endif

//--------------------------------------------------
// Debug Tool
//--------------------------------------------------
#define _NONE                                   0
#define _ISPACK                                 1
#define _RS232                                  2
#define _ISP_FOR_RTD2120                        3
#define _ISP_FOR_EMBEDDED                       4

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
#define _DEBUG_TOOL                             _ISP_FOR_EMBEDDED
#else
#define _DEBUG_TOOL                             _ISP_FOR_RTD2120
#endif


//----------------------------------------------------------------------------------------------------
// Input Port Settings
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definations of Digital Input Port 0
//--------------------------------------------------
#define _D0_NO_PORT                             0
#define _D0_DVI_PORT                            1
#define _D0_DVI_I_PORT                          2
#define _D0_HDMI_PORT                           3
#define _D0_DP_PORT                             4
#define _D0_VIDEO8_PORT                         5

#define _D0_INPUT_PORT_TYPE                     _D0_DP_PORT

//--------------------------------------------------
// Definations of Digital Input Port 1
//--------------------------------------------------
#define _D1_NO_PORT                             0
#define _D1_DVI_PORT                            11  // 1
#define _D1_DVI_I_PORT                          12  // 2
#define _D1_HDMI_PORT                           13  // 3
#define _D1_DP_PORT                             14  // 4

#define _D1_INPUT_PORT_TYPE                     _D1_HDMI_PORT

//--------------------------------------------------
// Definations of Analog Input Port 0
//--------------------------------------------------
#define _A0_NO_PORT                             0
#define _A0_VGA_PORT                            21  // 1
#define _A0_YPBPR_PORT                          22  // 2

#define _A0_INPUT_PORT_TYPE                     _A0_VGA_PORT

//--------------------------------------------------
// Definations of Analog Input Port 1
//--------------------------------------------------
#define _A1_NO_PORT                             0
#define _A1_VGA_PORT                            31  // 1
#define _A1_YPBPR_PORT                          32  // 2
#define _A1_VIDEO8_PORT                         33  // 3

#define _A1_INPUT_PORT_TYPE                     _A1_NO_PORT

//--------------------------------------------------
// Definations of External Video Input Port
//--------------------------------------------------
#define _VI_NO_PORT                             0
#define _VI_VIDEO8_PORT                         41  // 1

#define _VI_INPUT_PORT_TYPE                     _VI_NO_PORT

//--------------------------------------------------
// Definations of Input Port Groups
//--------------------------------------------------
#define _INPUT_PORT_GROUP_0                     0
#define _INPUT_PORT_GROUP_1                     1
#define _INPUT_PORT_GROUP_2                     2
#define _INPUT_PORT_GROUP_3                     3
#define _INPUT_PORT_GROUP_4                     4

#define _D0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _A0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _A1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_2
#define _VI_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_2

//--------------------------------------------------
// Definations of Input Port Search Priority
//--------------------------------------------------
#define _D0_INPUT_PORT                          0
#define _D1_INPUT_PORT                          1
#define _A0_INPUT_PORT                          2
#define _A1_INPUT_PORT                          3
#define _VI_INPUT_PORT                          4

#define _INPUT_PORT_SEARCH_POL_0                _D1_INPUT_PORT
#define _INPUT_PORT_SEARCH_POL_1                _A0_INPUT_PORT
#define _INPUT_PORT_SEARCH_POL_2                _D0_INPUT_PORT
#define _INPUT_PORT_SEARCH_POL_3                _A1_INPUT_PORT
#define _INPUT_PORT_SEARCH_POL_4                _VI_INPUT_PORT


//----------------------------------------------------------------------------------------------------
// Input Port Advance Settings
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Aanlog Port Definations of DVI-I Connect
//--------------------------------------------------
#define _DVI_A0_PORT                            0
#define _DVI_A1_PORT                            1

#define _ANALOG_PORT_OF_DVI_I_0                 _DVI_A1_PORT
#define _ANALOG_PORT_OF_DVI_I_1                 _DVI_A0_PORT

//--------------------------------------------------
// Definations of DVI-I Connect Search Priority
//--------------------------------------------------
#define _VGA_FIRST                              0
#define _DVI_FIRST                              1

#define _DVI_I_SEARCH                           _DVI_FIRST

//--------------------------------------------------
// DVI Connect Support HDMI Format
//--------------------------------------------------
#define _HDMI_FROM_DVI_CONNECT                  _OFF

//--------------------------------------------------
// DVI DE-Only Supported
//--------------------------------------------------
#define _DVI_DE_ONLY_SUPPORT                    _OFF

//--------------------------------------------------
// Video8 Type Select
//--------------------------------------------------
#define _SV_ONLY                                0
#define _AV_ONLY                                1
#define _SV_WITH_AV                             2
#define _AV_WITH_SV                             3

#define _V8_TYPE_SELECT                         _AV_WITH_SV

//--------------------------------------------------
// Hsync Type Detection Select of Input VGA Port
//--------------------------------------------------
#define _HSYNC_ONLY                             0
#define _HSYNC_WITH_SOG                         1
#define _HSYNC_WITH_SOG_SOY                     2

#define _HSYNC_TYPE_SELECT                      _HSYNC_WITH_SOG_SOY  //The setting only for _A0_VGA_PORT or _A1_VGA_PORT

//--------------------------------------------------
// A0 and A1 Hsync Source Swap
//--------------------------------------------------
#define _HSYNC_SOURCE_SWAP                      _OFF

//--------------------------------------------------
// Input Source Search Times
//--------------------------------------------------
#define _SOURCE_VGA_SEARCH_TIMES                3
#define _SOURCE_DVI_SEARCH_TIMES                150
#define _SOURCE_HDMI_SEARCH_TIMES               200
#define _SOURCE_VIDEO8_SEARCH_TIMES             10
#define _SOURCE_YPBPR_SEARCH_TIMES              10
#define _SOURCE_DP_SEARCH_TIMES                 30

//----------------------------------------------------------------------------------------------------
// General Advance Settings
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions for Backlight PWM Setting
//--------------------------------------------------
#define _SCALER_PWM0                            0
#define _SCALER_PWM1                            1
#define _SCALER_PWM2                            2

#define _MCU_PWM0                               3
#define _MCU_PWM1                               4
#define _MCU_PWM2                               5

#define _EMBEDDED_PWM0                          6
#define _EMBEDDED_PWM1                          7
#define _EMBEDDED_PWM2                          8
#define _EMBEDDED_PWM3                          9
#define _EMBEDDED_PWM4                          10
#define _EMBEDDED_PWM5                          11

#define _BACKLIGHT_PWM                          _EMBEDDED_PWM0
#define _BACKLIGHT_PWM_INVERSE                  _DISABLE

//--------------------------------------------------
// PWM Type Settings
//--------------------------------------------------
#define _PWM0_EN                                _ON
#define _PWM1_EN                                _OFF
#define _PWM2_EN                                _OFF
#define _PWM3_EN                                _OFF
#define _PWM4_EN                                _OFF
#define _PWM5_EN                                _OFF

//--------------------------------------------------
// Definitions of ADC Fine Tune Delay (Value == 0 ~ 7)
//--------------------------------------------------
#define _ADC_FINE_TUNE_DELAY_RED                0   //default = 0
#define _ADC_FINE_TUNE_DELAY_GREEN              0   //default = 0
#define _ADC_FINE_TUNE_DELAY_BLUE               0   //default = 0

//--------------------------------------------------
// Definitions of ADC Input Swap Settings
//--------------------------------------------------
#define _ADC_INPUT_SWAP_RG                      _OFF
#define _ADC_INPUT_SWAP_RB                      _OFF
#define _ADC_INPUT_SWAP_GB                      _OFF

//--------------------------------------------------
// Set Different Display Information by Mode
//--------------------------------------------------
#define _DISP_INFO_BY_MODE                      _OFF

//--------------------------------------------------
// TMDS Shrink Support
//--------------------------------------------------
#define _TMDS_SHRINK_SUPPORT                    _OFF
#define _TMDS_SHRINK_RANGE                      10

//--------------------------------------------------
// Set DClk Spread Spectrum Range
//--------------------------------------------------
#define _DCLK_SPREAD_RANGE                      0   //0~15, 0¡÷disable, 15¡÷7.5%

//--------------------------------------------------
// System Power Detection Support
//--------------------------------------------------
#define _SYSTEMPOWER_DETECT_SUPPORT             _OFF

//--------------------------------------------------
// Reset Check Support for EMI
//--------------------------------------------------
#define _RESET_CHECK_SUPPORT                    _OFF

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
//--------------------------------------------------
// Flah Type Information
//--------------------------------------------------
#define _FLASH_PFLASH_2M                        1
#define _FLASH_WINBOARD_2M                      2

#define _FLASH_TYPE                             _FLASH_PFLASH_2M

// V013 System Patch Note (4) Modify 20100428 Start
// Patch Reason : Make sure that flash type changed.
#if(_FLASH_TYPE != _FLASH_PFLASH_2M)
#error Are you sure changing flash type?
#endif
// V013 System Patch Note (4) Modify 20100428 End
*/
#define _FLASH_Pm25LV020                        1
#define _FLASH_W25X20A                          2
#define _FLASH_MX25L2026                        3
#define _FLASH_EN25F20                          4

// Insert newly supported flash types here!
#define _FLASH_Pm25LD020                        5
#define _FLASH_MX25L2025                        6
#define _FLASH_SST25LF020A                      7

// Make sure _FLASH_SUPPORTED_COUNT is correct after flash type was updated.
#define _FLASH_SUPPORTED_COUNT                  _FLASH_SST25LF020A

#define _FLASH_TYPE                             _FLASH_Pm25LV020

#define _AUTO_DETECT_FLASH_TYPE                 _OFF

#define _FLASH_XDATA_ACCESS                     _OFF

//--------------------------------------------------
// GAMMA_LUT Location Definition
//--------------------------------------------------
#define _GAMMA_LUT_LOCATION_CODE                (0)
#define _GAMMA_LUT_LOCATION_FLASH               (1)

#define _GAMMA_LUT_LOCATION                     _GAMMA_LUT_LOCATION_CODE

//--------------------------------------------------
// HDCP Key Location Definition
//--------------------------------------------------
#define _HDCP_LOCATION_CODE                     (0)
#define _HDCP_LOCATION_FLASH                    (1)

#define _HDCP_KEY_LOCATION                      _HDCP_LOCATION_FLASH//_HDCP_LOCATION_CODE
// V015 System Patch Note (7) Modify 20100630 End

//--------------------------------------------------
// Memory Location at Eeprom or Flash of RTD2120
//--------------------------------------------------
#define _EEPROM                                 0
#define _FLASH                                  1

#define _MEMORY_LOCATION                        _EEPROM

//--------------------------------------------------
// EDID Process Support
//--------------------------------------------------
#define _EDID_PRO                               _OFF

//--------------------------------------------------
// Switch Input Source by Hot Key
//--------------------------------------------------
#define _SWITCH_INPUT_SOURCE                    _OFF


//----------------------------------------------------------------------------------------------------
// DISPLAY PORT Advance Settings
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
//DP Enhance Mode
//
//--------------------------------------------------
#define _ENHANCE_MODE                           _ON

//--------------------------------------------------
//DP SCRAMB Mode
//In normal mode (connect with grafic-card) or BIST mode: please enable scramb mode
//In test mode: disable scramb mode
//--------------------------------------------------
#define _SCRAMB_MODE                            _ON

//--------------------------------------------------
//DP Link Clock Rate
//If select this function, Link Speed will be set in DPCD table, before training with TX.
//--------------------------------------------------
#define _HIGH_SPEED_270Mhz                      0   //270Mhz
#define _LOW_SPEED_162Mhz                       1   //162Mhz

#define _LINK_CLK_RATE                          _HIGH_SPEED_270Mhz

//--------------------------------------------------
// DP Main Link
//--------------------------------------------------
#define _ONE_LANE                               0
#define _TWO_LANE                               1
#define _FOUR_LANE                              2

#define _MAIN_LINK_LANES                        _FOUR_LANE

//--------------------------------------------------
// PHY CTS Automatic for PRBS7 Bit error rate
//--------------------------------------------------
#define _DP_PHY_CTS_AUTO                        _OFF

//--------------------------------------------------
//DP AUX Channel Switch
//AUX0 mapping to DDC2 in Pin defined.
//AUX1 mapping to DDC3 in Pin defined.
//--------------------------------------------------
#define _AUX_MAP_DDC2_PIN                       0
#define _AUX_MAP_DDC3_PIN                       1

#define _AUX_SWITCH                             _AUX_MAP_DDC3_PIN

//--------------------------------------------------
//DP Link-Training Process Select
//--------------------------------------------------
#define _LINK_CTS                               0       // Unigraf P.G. CTS Process
#define _NORMAL_GRAPH_CARD                      1       // For AMD DOS Mdoe bug and Alignment Issue

#define _LT_PROCEDURE                           _NORMAL_GRAPH_CARD

//--------------------------------------------------
//DP PHY CTS Process On
//--------------------------------------------------
#define _DP_PHYCTS_STEPBYSTEP                   _OFF


//--------------------------------------------------
//Hot Plug using Type (short or long)
//--------------------------------------------------
#define _HPD_SHORT                              0
#define _HPD_LONG                               1
#define _HPD_BOTH                               2

#define _HPD_TYPE                               _HPD_BOTH

//--------------------------------------------------
// Definitions for Connect Port
//--------------------------------------------------
#define _CABLE_CONNECT_CHECK                    _ON


#define _A0_PORT                                bA0_CONNECT
#define _A1_PORT                                bA1_CONNECT
#define _D0_PORT                                bD0_CONNECT
#define _D1_PORT                                bD1_CONNECT

//--------------------------------------------------
// Definitions for GPIO Control
//--------------------------------------------------
#define _PANEL_ON                               0       // Power on  state for LCD panel
#define _PANEL_OFF                              1       // Power off state for LCD panel

#define _LIGHT_ON                               0       // Power on  state for backlight inverter
#define _LIGHT_OFF                              1       // Power off state for backlight inverter

#define _VDC_ON                                 1       // Power on  state for video decoder
#define _VDC_OFF                                0       // Power off state for video decoder

#define _LVDS_ON                                0       // Power on  state for LVDS Tx
#define _LVDS_OFF                               1       // Power off state for LVDS Tx

#define _LED_ON                                 1       // Power on  state for LED
#define _LED_OFF                                0       // Power off state for LED

#define _DDC_CHANNEL_FOR_D0                     _DDC2   // DDC Channel SEL for digital input 0
#define _DDC_CHANNEL_FOR_D1                     _DDC3   // DDC Channel SEL for digital input 1


#define _HDMI_BR_SWAP                           _ON     // TMDS B/R channel swap for HDMI input port
#define _HDMI_PN_SWAP                           _ON     // TMDS P/N swap for HDMI input port

#define _DVI_BR_SWAP                            _OFF    // TMDS B/R channel swap for DVI input port
#define _DVI_PN_SWAP                            _OFF    // TMDS P/N swap for DVI input port

#define _HDCP_HOT_PLUG_ON                       _HIGH   // HDMI DDC Channel Source (_DDC2 or _DDC3)

#define _SOG0_INPUT_SELECTT                     _SOG0   // SOG Input MUX Select for analog input 0
#define _SOG1_INPUT_SELECTT                     _SOG1   // SOG Input MUX Select for analog input 1

//--------------------------------------------------
// RTD2472RD Pin Share
//--------------------------------------------------
#define _PIN_31                                 (0 & 0x03)  // 0 ~ 2 (0: PDD0i, 1: PDD0o<open-drain>, 2: PDD0o<push-pull>)
#define _PIN_32                                 (0 & 0x03)  // 0 ~ 2 (0: PDD1i, 1: PDD1o<open-drain>, 2: PDD1o<push-pull>)
#define _PIN_33                                 (0 & 0x03)  // 0 ~ 2 (0: PDD2i, 1: PDD2o<open-drain>, 2: PDD2o<push-pull>)
#define _PIN_34                                 (0 & 0x03)  // 0 ~ 2 (0: PDD3i, 1: PDD3o<open-drain>, 2: PDD3o<push-pull>)
#define _PIN_35                                 (0 & 0x03)  // 0 ~ 2 (0: PDD4i, 1: PDD4o<open-drain>, 2: PDD4o<push-pull>)
#define _PIN_36_37                              (0 & 0x03)  // 0 ~ 2 (0: PDD5i & PDD6i, 1: PDD5o<open-drain> & PDD6o<open-drain>, 2: PDD5o<push-pull> & PDD6o<push-pull>)

#define _PIN_41                                 (0 & 0x03)  // 0 ~ 3 (0: PBD0i, 1: PBD0o<open-drain>, 2: PBD0o<push-pull>,)
#define _PIN_42                                 (0 & 0x03)  // 0 ~ 3 (0: PBD1i, 1: PBD1o<open-drain>, 2: PBD1o<push-pull>,3:IICSCL <open-drain>)
#define _PIN_43                                 (0 & 0x03)  // 0 ~ 3 (0: PBD2i, 1: PBD2o<open-drain>, 2: PBD2o<push-pull>,3:IICSDA <open-drain>)
#define _PIN_44                                 (0 & 0x07)  // 0 ~ 4 (0: PBD3i, 1: PBD3o<open-drain>, 2: PBD3o<push-pull>,3:WS, 4:SPDIF3 )
#define _PIN_45                                 (1 & 0x03)  // 0 ~ 3 (0: PBD4i, 1: PBD4o<open-drain>, 2: PBD4o<push-pull>,3:SCK)
#define _PIN_46                                 (1 & 0x03)  // 0 ~ 3 (0: PBD5i, 1: PBD5o<open-drain>, 2: PBD5o<push-pull>,3:MCK)
#define _PIN_47                                 (0 & 0x03)  // 0 ~ 3 (0: PBD6i, 1: PBD6o<open-drain>, 2: PBD6o<push-pull>,3:SD0)
#define _PIN_48                                 (0 & 0x03)  // 0 ~ 3 (0: PBD7i, 1: PBD7o<open-drain>, 2: PBD7o<push-pull>,3:PWM0)

#define _PIN_50                                 (0 & 0x07)  // 0 ~ 5 (0: P6D0i, 1: P6D0o<open-drain>, 2: P6D0o<push-pull>, 3: ADCA0, 4: reserved, 5: VCLK)
#define _PIN_51                                 (3 & 0x03)  // 0 ~ 3 (0: P6D1i, 1: P6D1o<open-drain>, 2: P6D1o<push-pull>, 3: ADCA1)
#define _PIN_52                                 (3 & 0x03)  // 0 ~ 3 (0: P6D2i, 1: P6D2o<open-drain>, 2: P6D2o<push-pull>, 3: ADCA2)

#define _PIN_53                                 (0 & 0x03)  // 0 ~ 3 (0: P6D3i, 1: P6D3o<open-drain>, 2: P6D3o<push-pull>, 3: ADCA3)

#define _PIN_54                                 (0 & 0x03)  // 0 ~ 3 (0: P6D4i, 1: P6D4o<open-drain>, 2: P6D4o<push-pull>, 3: ADCA4)

#define _PIN_55                                 (1 & 0x07)  // 0 ~ 7 (0: P6D5i, 1: P6D5o<open-drain>, 2: P6D5o<push-pull>, 3: ADCB0, 4: PWM1, 5: PWM5, 6:TCON0, 7:TCON5)

#define _PIN_56_57_IIC_ENABLE                   (0 & 0x01)  // 0 ~ 1 (0: Disable, 1: Enable) Pin56,57 for IIC
#define _PIN_56                                 (1 & 0x07)  // 0 ~ 5 (0: P6D6i, 1: P6D6o<open-drain>, 2: P6D6o<push-pull>, 3: ADCB1, 4:TCON1, 5:TCON4) Effective only if _PIN_56_57_IIC_ENABLE = Disable.
#define _PIN_57                                 (1 & 0x07)  // 0 ~ 5 (0: P6D7i, 1: P6D7o<open-drain>, 2: P6D7o<push-pull>, 3: ADCB2, 4:TCON9, 5:TCON11) Effective only if _PIN_56_57_IIC_ENABLE = Disable.

#define _PIN_58_59_DDC1_ENABLE                  (0 & 0x01)  // 0 ~ 1 (0: Enable, 1: Disable) Pin58,59 for DDC1
#define _PIN_58                                 (0 & 0x07)  // 0 ~ 6 (0: P3D0i, 1: P3D0o<open-drain>, 2: P3D0o<push-pull>, 3: RXD<open-drain>, 4:TCON7, 5;TCON10) Effective only if _PIN_58_59_DDC1_ENABLE = Disable.
#define _PIN_59                                 (0 & 0x07)  // 0 ~ 6 (0: P3D1i, 1: P3D1o<open-drain>, 2: P3D1o<push-pull>, 3: TXD<open-drain>, 4:TCON3, 5:TCON5) Effective only if _PIN_58_59_DDC1_ENABLE = Disable.

#define _PIN_63                                 (1 & 0x07)  // 0 ~ 5 (0: PCD0i, 1: PCD0o<open-drain>, 2: PCD0o<push-pull>, 3: PWM2, 4: TCON1, 5: TCON8)
#define _PIN_64                                 (1 & 0x0F)  // 0 ~ 8 (0: P1D0i, 1: P1D0o<open-drain>, 2: P1D0o<push-pull>, 3: T2, 4: SD0, 5: SPDIF0, 6: TCON[0], 7: IrDA, 8:TCON[7])
#define _PIN_65                                 (1 & 0x07)  // 0 ~ 6 (0: P1D1i, 1: P1D1o<gpo>       , 2: PWM1, 3: T2EX, 4: TCON[1], 5: TCON[7], 6: WS,)
#define _PIN_66                                 (1 & 0x07)  // 0 ~ 6 (0: P1D2i, 1: P1D2o<gpo>       , 2: reserved, 3: CLKO, 4: SCK, 5: TCON[2], 6: TCON[4]) Effective only if 8-bit TTL Disable.
#define _PIN_67                                 (0 & 0x07)  // 0 ~ 5 (0: P1D3i, 1: P1D3o<gpo>       , 2: reserved, 3: MCK, 4: TCON[5], 5: TCON[9]) Effective only if 8-bit TTL Disable.
#define _PIN_68                                 (1 & 0x07)  // 0 ~ 6 (0: P1D4i, 1: P1D4o<gpo>       , 2: reserved, 3: SD0, 4: TCON[3], 5: TCON[13], 6: SPDIF0) Effective only if 8-bit TTL Disable.
#define _PIN_69                                 (1 & 0x07)  // 0 ~ 7 (0: P1D5i, 1: P1D5o<gpo>       , 2: reserved, 3: SD1, 4: TCON[3], 5: TCON[7], 6: SPDIF1, 7: IICSCL) Effective only if 8-bit TTL Disable.
#define _PIN_70                                 (1 & 0x07)  // 0 ~ 7 (0: P1D6i, 1: P1D6o<gpo>       , 2: reserved, 3: SD2, 4: TCON[9], 5: TCON[11], 6: SPDIF2, 7: IICSDA) Effective only if 8-bit TTL Disable.
#define _PIN_71                                 (1 & 0x07)  // 0 ~ 7 (0: P1D7i, 1: P1D7o<gpo>       , 2: PWM5, 3: SD3, 4: TCON[8], 5: TCON[10], 6: SPDIF3, 7: PWM1,) Effective only if 8-bit TTL Disable.
#define _PIN_72                                 (0 & 0x07)  // 0 ~ 4 (0: PCD1i, 1: PCD1o<gpo>       , 2: TCON[6], 3:TCON[12], 4: PWM3)

#define _PIN_74to83                             (0 & 0x03)  // 0 ~ 3 (0: None,  1: GPI, 2: GPO, 3:reserved) Effective only if single-port LVDS without E/O swap.

#define _PIN_96                                 (0 & 0x03)  // 0 ~ 3 (0: P5D2i, 1: P5D2o<gpo>       , 2: DCLK, 3: PWM0,)
#define _PIN_97                                 (0 & 0x07)  // 0 ~ 4 (0: P5D3i, 1: P5D3o<gpo>       , 2: reserved, 3: PWM1, 4: DVS)
#define _PIN_98                                 (1 & 0x03)  // 0 ~ 3 (0: P5D4i, 1: P5D4o<gpo>       , 2: reserved, 3: PWM2)
#define _PIN_99                                 (0 & 0x07)  // 0 ~ 5 (0: P5D5i, 1: P5D5o<gpo>       , 2: reserved, 3: PWM3, 4: TCON[6], 5: TCON[11])
#define _PIN_100                                (3 & 0x07)  // 0 ~ 5 (0: P5D6i, 1: P5D6o<gpo>       , 2: reserved, 3: PWM4, 4: TCON[3], 5: TCON[12])
#define _PIN_101                                (1 & 0x03)  // 0 ~ 3 (0: P5D7i, 1: P5D7o<gpo>       , 2: TCON0, 3: PWM5,)
#define _PIN_102                                (3 & 0x07)  // 0 ~ 6 (0: P7D6i, 1: P7D6o<gpo>       , 2: reserved, 3: PWM0, 4: SD3, 5: SPDIF3, 6: TCON[10])
#define _PIN_103                                (1 & 0x07)  // 0 ~ 7 (0: P7D5i, 1: P7D5o<gpo>       , 2: reserved, 3: PWM1, 4: SD2, 5: SPDIF2, 6: TCON[8], 7: IICSCL)
#define _PIN_104                                (1 & 0x07)  // 0 ~ 7 (0: P7D4i, 1: P7D4o<gpo>       , 2: reserved, 3: SD1, 4: IRQ, 5: TCON[5], 6: SPDIF1, 7: IICSDA)
#define _PIN_105                                (0 & 0x07)  // 0 ~ 5 (0: P8D0i, 1: P8D0o<gpo>       , 2: reserved, 3: TCON[9], 4: SD0, 5: SPDIF0)

#define _PIN_108                                (1 & 0x07)  // 0 ~ 5 (0: P8D1i, 1: P8D1o<gpo>       , 2: reserved, 3: CLKO, 4: MCK, 5: TCON[7])
#define _PIN_109                                (0 & 0x07)  // 0 ~ 5 (0: P3D2i, 1: P3D2o<gpo>       , 2: reserved, 3: INT0, 4: TCON[3], 5: SCK)
#define _PIN_110to114_MIRROR                    (0 & 0x01)  // 0 ~ 1 (0: pin110 WS, pin111 SD0, pin112 SD1, pin113 SD2, pin114 SD3, 1: pin110 SD1, pin111 SD0, pin112 WS, pin113 SCK, pin114 MCK)

#define _PIN_110                                (2 & 0x07)  // 0 ~ 7 (0: P3D3i, 1: P3D3o<open-drain>, 2: P3D3o<push-pull>, 3: INT1, 4: TCON[6], 5: WS, 6:TCON[2], 7:TCON[7])
#define _PIN_111                                (1 & 0x07)  // 0 ~ 7 (0: P3D4i, 1: P3D4o<open-drain>, 2: P3D4o<push-pull>, 3: T0, 4: TCON[4], 5: SD0, 6: SPDIF0, 7:TCON[7])
#define _PIN_112                                (1 & 0x07)  // 0 ~ 6 (0: P3D5i, 1: P3D5o<open-drain>, 2: P3D5o<push-pull>, 3: T1, 4: TCON[9], 5: SD1, 6: SPDIF1, 7:TCON[5])
#define _PIN_113                                (1 & 0x07)  // 0 ~ 7 (0: P3D6i, 1: P3D6o<open-drain>, 2: P3D6o<push-pull>, 3: TCON[1], 4: SD2, 5: SPDIF2, 6: IrDA, 7:TCON[11])
#define _PIN_114                                (1 & 0x07)  // 0 ~ 7 (0: P3D7i, 1: P3D7o<open-drain>, 2: P3D7o<push-pull>, 3: TCON[13], 4: SD3, 5: SPDIF3, 6: PWM4, 7:TCON[0])

#define _PIN_119                                (1 & 0x07)  // 0 ~ 4 (0: PCD2i, 1: PCD2o<open-drain>, 2: PCD2o<push-pull>, 3: PWM5, 4: SPIF1,)

#define _PIN_121_122_DDC3_ENABLE                (0 & 0x01)  // 0 ~ 1 (0: Enable, 1: Disable) Pin121,122 for DDC3
#define _PIN_121                                (1 & 0x03)  // 0 ~ 3 (0: P7D3i,  1: P7D3o<open-drain>, 2: P7D3o<push-pull>, 3:AUX_CH-N1)
#define _PIN_122                                (1 & 0x03)  // 0 ~ 3 (0: P7D2i,  1: P7D2o<open-drain>, 2: P7D2o<push-pull>, 3:AUX_CH-P1)
#define _PIN_123_124_DDC2_ENABLE                (1 & 0x01)  // 0 ~ 1 (0: Enable, 1: Disable) Pin123,124 for DDC2
#define _PIN_123                                (3 & 0x03)  // 0 ~ 3 (0: P7D1i,  1: P7D1o<open-drain>, 2: P7D1o<push-pull>, 3:AUX_CH-N0)
#define _PIN_124                                (3 & 0x03)  // 0 ~ 3 (0: P7D0i,  1: P7D0o<open-drain>, 2: P7D0o<push-pull>, 3:AUX_CH-P0)
#define _PIN_126                                (4 & 0x07)  // 0 ~ 5 (0: PCD3i, 1: PCD3o<open-drain>, 2: PCD3o<push-pull>, 3: PWM1, 4: CEC, 5:SPDIF2)


//--------------------------------------------------
// MCU Pin Assignment
//--------------------------------------------------

#if(_MCU_TYPE == _REALTEK_EMBEDDED)

//--------------------------------------------------
sbit bEEPROM_WRITE_PROTECT                      = P3 ^ 4;

#define bI2CSCL                                 (MCU_PORT67_PIN_REG_FFCE)
#define bI2CSDA                                 (MCU_PORT66_PIN_REG_FFCD)

//--------------------------------------------------
#define bA0_CONNECT                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bA1_CONNECT                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

// DP Pin15(Aux_P cable detect pin)
#define bDP_Pin15_CONNECT                       (MCU_PORT63_PIN_REG_FFCA)

// DP Pin17(Aux_N cable detect pin)
#define bDP_Pin17_CONNECT                       (MCU_PORT64_PIN_REG_FFCB)

// DP Pin16(DP spec.1.0 cable detect pin)
sbit bDP_PIN16_CONNECT                          = P3 ^ 2;

#define bD1_CONNECT                             (MCU_PORT60_PIN_REG_FFC7)

sbit bHPD_D0                                    = P3 ^ 3;
sbit bHPD_D1                                    = P3 ^ 7;
#define D0_HPD_LOW()                            (bHPD_D0 = 0)
#define D0_HPD_HIGH()                           (bHPD_D0 = 1)
#define D1_HPD_LOW()                            (bHPD_D1 = 0)
#define D1_HPD_HIGH()                           (bHPD_D1 = 1)

sbit bHDCP_SCL                                  = P3 ^ 4;
sbit bHDCP_SDA                                  = P3 ^ 5;

//--------------------------------------------------
#define bPANELPOWER                             (MCU_PORT65_PIN_REG_FFCC)
#define bLIGHTPOWER                             (MCU_PORT57_PIN_REG_FFC6)

#define bSYSTEMPOWERDETECT                      (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bLED1                                   (MCU_PORT74_PIN_REG_FFD3)
#define bLED2                                   (MCU_PORT75_PIN_REG_FFD4)
#define bLED3                                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bLED4                                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bLED5                                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define AD_KEY0                                 (MCU_ADC2_RESULT_FF0B)
#define AD_KEY1                                 (MCU_ADC1_RESULT_FF0A)
#define AD_KEY2                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bPOWER_KEY                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bMENU_KEY                               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bEXIT_KEY                               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bLEFT_KEY                               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bRIGHT_KEY                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

//--------------------------------------------------
sbit bAUDIO_PWR                                 = P1 ^ 5;
sbit bSHDN_AMP                                  = P1 ^ 6;

//--------------------------------------------------
// Hardware Flash WP# Pin Assignment
//--------------------------------------------------
// This is a reference configuration for _RTD2472RD_DEMO_PCB,
// WP# connected with pin108
#define bHW_PROTECT_PIN                         (MCU_PORT81_PIN_REG_FFD7)
#define HW_PROTECT_PIN_LOW()                    (bHW_PROTECT_PIN &= ~_BIT0)
#define HW_PROTECT_PIN_HIGH()                   (bHW_PROTECT_PIN |= _BIT0)


#endif  // End of #if(_MCU_TYPE == _REALTEK_EMBEDDED)

//--------------------------------------------------
// PCB Interface Pin Assignment
//--------------------------------------------------
#define _DISP_EO_SWAP                           _DISABLE            // Display Data Port Even/Odd Data Swap

#define _DISP_RB_SWAP                           _DISABLE            // Display Data Port Red/Blue Data Swap
#define _DISP_ML_SWAP                           _DISABLE            // Display Data Port MSB/LSB Data Swap

#define _DISP_DVS_INVERT                        _DISABLE            // DVS Output Invert Enable
#define _DISP_DHS_INVERT                        _DISABLE            // DHS Output Invert Enable
#define _DISP_DEN_INVERT                        _DISABLE            // DEN Output Invert Enable

#define _RSDS_GC_SWAP                           _DISABLE            // RSDS Green/Clock Pair Swap
#define _RSDS_HL_SWAP                           _DISABLE            // RSDS High/Low Bit Swap
#define _RSDS_PN_SWAP                           _DISABLE            // RSDS Differential Pair PN Swap

#endif  // End of #if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
