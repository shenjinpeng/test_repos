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

#if(_PCB_TYPE == _RTD2545LR_DEMO_PCB)

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

#define _SCALER_TYPE                            _RTD2545LR

//--------------------------------------------------
// MCU Type
//--------------------------------------------------
#define _REALTEK_EMBEDDED                       0
#define _REALTEK_RTD2120                        1
#define _REALTEK_RTD2122                        2

#define _MCU_TYPE                               _REALTEK_RTD2120

//--------------------------------------------------
// Definations of RTD/MCU Crystal Frequency in KHz
//--------------------------------------------------
#define _XTAL27000K                             27000
#define _XTAL24000K                             24000

#define _RTD_XTAL                               _XTAL24000K
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

#if(_MCU_TYPE != _REALTEK_EMBEDDED)
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

#define _D0_INPUT_PORT_TYPE                     _D0_DVI_PORT

//--------------------------------------------------
// Definations of Digital Input Port 1
//--------------------------------------------------
#define _D1_NO_PORT                             0
#define _D1_DVI_PORT                            11  // 1
#define _D1_DVI_I_PORT                          12  // 2
#define _D1_HDMI_PORT                           13  // 3
#define _D1_DP_PORT                             14  // 4

#define _D1_INPUT_PORT_TYPE                     _D1_NO_PORT

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
#define _A1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _VI_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0

//--------------------------------------------------
// Definations of Input Port Search Priority
//--------------------------------------------------
#define _D0_INPUT_PORT                          0
#define _D1_INPUT_PORT                          1
#define _A0_INPUT_PORT                          2
#define _A1_INPUT_PORT                          3
#define _VI_INPUT_PORT                          4

#define _INPUT_PORT_SEARCH_POL_0                _A0_INPUT_PORT
#define _INPUT_PORT_SEARCH_POL_1                _D0_INPUT_PORT
#define _INPUT_PORT_SEARCH_POL_2                _D1_INPUT_PORT
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
//The setting only for _A0_VGA_PORT or _A1_VGA_PORT
#define _HSYNC_ONLY                             0
#define _HSYNC_WITH_SOG                         1
#define _HSYNC_WITH_SOG_SOY                     2

#define _HSYNC_TYPE_SELECT                      _HSYNC_WITH_SOG_SOY

//--------------------------------------------------
// A0 and A1 Hsync Source Swap
//--------------------------------------------------
#define _HSYNC_SOURCE_SWAP                      _OFF

//--------------------------------------------------
// Input Source Search Times
//--------------------------------------------------
#define _SOURCE_VGA_SEARCH_TIMES                3
#define _SOURCE_DVI_SEARCH_TIMES                10
#define _SOURCE_HDMI_SEARCH_TIMES               10
#define _SOURCE_VIDEO8_SEARCH_TIMES             10
#define _SOURCE_YPBPR_SEARCH_TIMES              10
#define _SOURCE_DP_SEARCH_TIMES                 80


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

#define _BACKLIGHT_PWM                          _MCU_PWM0
#define _BACKLIGHT_PWM_INVERSE                  _DISABLE

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

//--------------------------------------------------
// Flah Type Information
//--------------------------------------------------
#define _FLASH_PFLASH_2M                        1
#define _FLASH_WINBOARD_2M                      2

#define _FLASH_TYPE                             _FLASH_PFLASH_2M

// V013 System Patch Note (4) Modify 20100428 Start
// Patch Reason : Make sure that flash type changed.
#if(_FLASH_TYPE != _FLASH_PFLASH_2M)
#error Are you sure changing flash type ?
#endif
// V013 System Patch Note (4) Modify 20100428 End

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
#define _DP_PHY_CTS_AUTO  _OFF

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
//Hot Plug using Type (short or long)
//--------------------------------------------------
#define _HPD_SHORT                              0
#define _HPD_LONG                               1
#define _HPD_BOTH                               2

#define _HPD_TYPE                               _HPD_SHORT

//--------------------------------------------------
// Definitions for Connect Port
//--------------------------------------------------
#define _CABLE_CONNECT_CHECK                    _OFF


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


#define _HDMI_BR_SWAP                           _OFF    // TMDS B/R channel swap for HDMI input port
#define _HDMI_PN_SWAP                           _OFF    // TMDS P/N swap for HDMI input port

#define _DVI_BR_SWAP                            _OFF    // TMDS B/R channel swap for DVI input port
#define _DVI_PN_SWAP                            _OFF    // TMDS P/N swap for DVI input port

#define _HDCP_HOT_PLUG_ON                       _HIGH   // HDMI DDC Channel Source (_DDC2 or _DDC3)

#define _SOG0_INPUT_SELECTT                     _SOG0   // SOG Input MUX Select for analog input 0
#define _SOG1_INPUT_SELECTT                     _SOG1   // SOG Input MUX Select for analog input 1

//--------------------------------------------------
// RTD2545LR Pin Share
//--------------------------------------------------
#if(_D0_INPUT_PORT == _D0_DP_PORT)
#define _PIN_43                                 (3 & 0x03)  // 0 ~ 3 (0: DDCSDA<open-drain>, 1: PWM0, 2: TCON7, 3: AUX-CH_P0)
#define _PIN_44                                 (3 & 0x03)  // 0 ~ 3 (0: DDCSCL<open-drain>, 1: PWM1, 2: TCON9, 3: AUX-CH_N0/IRQ)
#else
#define _PIN_43                                 (0 & 0x03)  // 0 ~ 3 (0: DDCSDA<open-drain>, 1: PWM0, 2: TCON7, 3: AUX-CH_P0)
#define _PIN_44                                 (0 & 0x03)  // 0 ~ 3 (0: DDCSCL<open-drain>, 1: PWM1, 2: TCON9, 3: AUX-CH_N0/IRQ)
#endif

#if((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122))
//--------------------------------------------------
// MCU Pin Assignment
//--------------------------------------------------
sbit bSCALERSCLK                                = P1 ^ 7; // Scaler Read/Write
#define bSCALERSCSB                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
sbit bSCALERSDIO3                               = P1 ^ 6; // Scaler Read/Write
#define bSCALERRESET                            (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

//--------------------------------------------------
#define bEEPROM_WRITE_PROTECT                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS) // Write Protection

sbit bDDCSCL                                    = P3 ^ 0;
#define bDDCSCLDVI                              (MCU_PORT50_FF50[6] & 0x01)

sbit bI2CSCL                                    = P3 ^ 2;
sbit bI2CSDA                                    = P3 ^ 3;

//--------------------------------------------------
#define bA0_CONNECT                             (MCU_PORT60_FF58[5])
#define bA1_CONNECT                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bD0_CONNECT                             (MCU_PORT76_77_FF60[1])
#define bD1_CONNECT                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bHPD_D0                                 (MCU_PORT50_FF50[1])
#define bHPD_D1                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define D0_HPD_LOW()                            (bHPD_D0 = 0)
#define D0_HPD_HIGH()                           (bHPD_D0 = 1)
#define D1_HPD_LOW()                            (bHPD_D1 = 0)
#define D1_HPD_HIGH()                           (bHPD_D1 = 1)

#define bHDCP_SCL                               (MCU_PORT50_FF50[6])
#define bHDCP_SDA                               (MCU_PORT50_FF50[7])

//--------------------------------------------------
#define bPANELPOWER                             (MCU_PORT50_FF50[0])
#define bLIGHTPOWER                             (MCU_PORT50_FF50[2])

#define bSYSTEMPOWERDETECT                      (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bLED1                                   (MCU_PORT60_FF58[4])
#define bLED2                                   (MCU_PORT60_FF58[3])
#define bLED3                                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bLED4                                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bLED5                                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define AD_KEY0                                 (MCU_ADC2_RESULT_FF0E)
#define AD_KEY1                                 (MCU_ADC1_RESULT_FF0D)
#define AD_KEY2                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bPOWER_KEY                              (MCU_PORT50_FF50[4] & 0x01)
#define bMENU_KEY                               (MCU_PORT50_FF50[3] & 0x01)
#define bEXIT_KEY                               (MCU_PORT50_FF50[2] & 0x01)
#define bLEFT_KEY                               (MCU_PORT50_FF50[1] & 0x01)
#define bRIGHT_KEY                              (MCU_PORT50_FF50[0] & 0x01)

//--------------------------------------------------
#define bAUDIO_PWR                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSHDN_AMP                               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#endif  // End of #if((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122))

//--------------------------------------------------
// PCB Interface Pin Assignment
//--------------------------------------------------
#define _DISP_EO_SWAP                           _ENABLE             // Display Data Port Even/Odd Data Swap

#define _DISP_RB_SWAP                           _DISABLE            // Display Data Port Red/Blue Data Swap
#define _DISP_ML_SWAP                           _DISABLE            // Display Data Port MSB/LSB Data Swap

#define _DISP_DVS_INVERT                        _DISABLE            // DVS Output Invert Enable
#define _DISP_DHS_INVERT                        _DISABLE            // DHS Output Invert Enable
#define _DISP_DEN_INVERT                        _DISABLE            // DEN Output Invert Enable

#define _RSDS_GC_SWAP                           _DISABLE            // RSDS Green/Clock Pair Swap
#define _RSDS_HL_SWAP                           _DISABLE            // RSDS High/Low Bit Swap
#define _RSDS_PN_SWAP                           _DISABLE            // RSDS Differential Pair PN Swap

#endif  // End of #if(_PCB_TYPE == _RTD2545LR_DEMO_PCB)
