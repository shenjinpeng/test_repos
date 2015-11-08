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
// Advance Settings
//----------------------------------------------------------------------------------------------------

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
#define _EMBEDDED_EDID                          _ON
*/
#if((_MEMORY_LOCATION == _FLASH) && (_EDID_PRO == _ON))
#define _EMBEDDED_EDID                          _ON // Force Embedded EDID on when EDID Pro is on.
#else
#define _EMBEDDED_EDID                          _OFF
#endif
// V015 System Patch Note (7) Modify 20100630 End

#define _EMBEDDED_HDCP_KEY                      _ON

// V013 VGA Patch Note (11) Modify 20100416 Start
// Patch Reason : Add FIFO Mode Only to save EEPROM space.
// Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
#if(_MEMORY_LOCATION == _EEPROM)
#define _FIFO_MODE_ONLY                         _ON
#else
#define _FIFO_MODE_ONLY                         _OFF // EEPROM Emulation has enough space, OFF.
#endif

#if(_FIFO_MODE_ONLY == _ON)
//--------------------------------------------------
// Definitions of Maximum FIFO Mode Index For _FIFO_MODE_ONLY
//--------------------------------------------------
#define _MAX_FIFO_MODE_INDEX                    63

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
#else

#define _MAX_FIFO_MODE_INDEX                    15
// V015 System Patch Note (7) Modify 20100630 End

#endif
// V013 VGA Patch Note (11) Modify 20100416 End

//----------------------------------------------------------------------------------------------------
// Scaler Series
//----------------------------------------------------------------------------------------------------
#define _RTD2472D_SERIES                        0


#if((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
#define _SCALER_SERIES_TYPE                     _RTD2472D_SERIES
#else
    No Setting !!
#endif

//--------------------------------------------------
// Definations of SPI Flash CLOCK,
// Note: Winbond Flash Support _TURBO_MODE=_ON.
//       Otherwise Set _TURBO_MODE=_OFF.
//--------------------------------------------------

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
#define _M2PLL_PLL_M                            (105 + 2)  // Page1 0xE0[7:0] default value = 0x69
#define _M2PLL_PLL_N                            (3 + 2)    // Page1 0xE1[3:0] default value = 0x3
#define _M2PLL_PLL_O                             2       // Page1 0xE1[5:4] default value = 0x1

#define _M2PLL_CLK_MHZ                          ((((_RTD_XTAL / 1000) * _M2PLL_PLL_M) / _M2PLL_PLL_N) / _M2PLL_PLL_O)
#elif(_SCALER_TYPE == _RTD2472D)
#define _M2PLL_CLK_MHZ                          243
#endif // End Of #if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

// V012 Modify 20100331 Start
// V012 Patch Note (21) : Fix the sync processor compatibility problem. Replace slower XTAL clock with M2PLL.

// V013 VGA Patch Note (6) Modify 20100428 Start
// Patch Reason : Update V012 Patch Note (21) use m2pll/10 as internal clock just in analog source.
/*
// Choose the larger clock as the Internal Clock
#define _INTERNAL_CLK_FLAG                  (((_M2PLL_CLK_MHZ * 1000 / 10) > _RTD_XTAL) ? _BIT2 : 0x00)

// Internal Clock Frequency(k)
#define _INTERNAL_SYSTEM_CLK                (CScalerGetBit(_FIFO_FREQUENCY_22, _BIT2) ? (_M2PLL_CLK_MHZ * 1000 / 10) : _RTD_XTAL)
*/
// Choose the larger clock as the Internal Clock
#define _INTERNAL_CLK_FLAG                  ((((DWORD)_M2PLL_CLK_MHZ * 1000 / 10) > _RTD_XTAL) ? _BIT2 : 0x00)

// Internal Clock Frequency(k)
#define _INTERNAL_SYSTEM_CLK                (CScalerGetBit(_FIFO_FREQUENCY_22, _BIT2) ? ((DWORD)_M2PLL_CLK_MHZ * 1000 / 10) : _RTD_XTAL)
// V013 VGA Patch Note (6) Modify 20100428 End

// V012 Modify 20100331 End

//--------------------------------------------------
// Definations of SPI Flash CLOCK,
// Note: Winbond Flash Support _TURBO_MODE=_ON.
//       Otherwise Set _TURBO_MODE=_OFF.
//--------------------------------------------------
#if(_MCU_TYPE == _REALTEK_EMBEDDED)

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _FLASH_CLK_72MHZ                        (_M2PLL_CLK_MHZ / 72)
#define _FLASH_CLK_57MHZ                        (_M2PLL_CLK_MHZ / 57)
#define _FLASH_CLK_48MHZ                        (_M2PLL_CLK_MHZ / 48)
#define _FLASH_CLK_36MHZ                        (_M2PLL_CLK_MHZ / 36)
#define _FLASH_CLK_28MHZ                        (_M2PLL_CLK_MHZ / 28)

#define _FLASH_CLK_DIV                          _FLASH_CLK_57MHZ
#define _TURBO_MODE                             _OFF

#if(_FLASH_CLK_DIV == _FLASH_CLK_28MHZ)
#define _FAST_READ                              _OFF
#else
#define _FAST_READ                              _ON
#endif

#if(_FLASH_CLK_DIV >= _FLASH_CLK_48MHZ)
#define _MCU_CLK_DIV                            _DIV_1
#else
#define _MCU_CLK_DIV                            _DIV_2
#endif


#elif(_SCALER_TYPE == _RTD2472D)
#define _FLASH_CLK_80MHZ                        (_M2PLL_CLK_MHZ / 80)
#define _FLASH_CLK_60MHZ                        (_M2PLL_CLK_MHZ / 60)
#define _FLASH_CLK_48MHZ                        (_M2PLL_CLK_MHZ / 48)
#define _FLASH_CLK_34MHZ                        (_M2PLL_CLK_MHZ / 34)
#define _FLASH_CLK_27MHZ                        (_M2PLL_CLK_MHZ / 27)

#define _FLASH_CLK_DIV                          _FLASH_CLK_60MHZ
#define _TURBO_MODE                             _OFF

#if(_FLASH_CLK_DIV == _FLASH_CLK_27MHZ)
#define _FAST_READ                              _OFF
#else
#define _FAST_READ                              _ON
#endif

#if(_FLASH_CLK_DIV >= _FLASH_CLK_48MHZ)
#define _MCU_CLK_DIV                            _DIV_1
#else
#define _MCU_CLK_DIV                            _DIV_2
#endif

#else
    No setting!!

#endif  // End of #if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#endif  // End of #if(_MCU_TYPE == _REALTEK_EMBEDDED)

//--------------------------------------------------
// Bank Switching Supported
//--------------------------------------------------
#if(_MCU_TYPE == _REALTEK_RTD2122 || _MCU_TYPE == _REALTEK_EMBEDDED)
#define _BANK_SWITCHING_SUPPORT                 _ON
#else
#define _BANK_SWITCHING_SUPPORT                 _OFF
#endif

//--------------------------------------------------
// DDC Channel Select
//--------------------------------------------------
#define _VGA_DDC_CHANNEL                        0
#define _DVI_DDC_CHANNEL                        1
#define _HDMI_DDC_CHANNEL                       2

#define _DDC_CHANNEL_SEL                        _VGA_DDC_CHANNEL

//--------------------------------------------------
// Debug Message Supported
//--------------------------------------------------
#define _DEBUG_MESSAGE_SUPPORT             _ON// _OFF//_ON//   _OFF//_ON//_OFF//_ON//_OFF// _ON//_OFF //uart zp0704

//--------------------------------------------------
// Debug Message Polling Method
//--------------------------------------------------
#define _POLLING_BY_1BYTE                       0
#define _POLLING_BY_16BYTE                      1

#define _POLLING_MESSAGE_NBYTES                 _POLLING_BY_16BYTE

//--------------------------------------------------
// Initial Message ACK
//--------------------------------------------------
#define _INITIAL_MESSAGE_ACK                    _OFF // Set _ON if you don't want to lose any message
                                                     // in the initial state and you should press the
                                                     // "Start" key of Debug Message Tool when power-on.

//--------------------------------------------------
// Definitions of DVStartPos adjusting
// Note: _ON  => F/W will adjust DVStartPos automatically.
//       _OFF => F/W will set DVStartPos by panel.h.
//--------------------------------------------------
#define _DVSTART_POS_ADJUSTING                  _ON

//--------------------------------------------------
// Definitions for Display Signal
//--------------------------------------------------
#define _DISPLAY_INVERT                         (_DVS_INVERT | _DHS_INVERT | _DEN_INVERT)

//--------------------------------------------------
// Definitions for Display Control
//--------------------------------------------------
#define _DISPLAY_CTRL                           (_DHS_MASK | _DISPLAY_INVERT)

//--------------------------------------------------
// Definitions of APLL1 M/N Code
//--------------------------------------------------
#define _APLL_M_CODE                            25   //default = 25
#define _APLL_N_CODE                            3    //default = 3

//--------------------------------------------------
// APLL New Mode Support
//--------------------------------------------------
#define _APLL_NEW_MODE_SUPPORT                  _OFF

//--------------------------------------------------
// Definitions of DDS P Code
//--------------------------------------------------
#define _DDS_P_CODE                             23  //default = 23

//--------------------------------------------------
// Definitions of MPLL N Code
//--------------------------------------------------
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _MPLL_N_CODE                            5


//--------------------------------------------------
// Set MClk Spread Spectrum Range
//--------------------------------------------------
#define _MCLK_SPREAD_RANGE                      0   //0~15, 0¡÷disable, 15¡÷7.5%
#endif

//--------------------------------------------------
// Definitions of M2PLL
//--------------------------------------------------
#define _M2PLL_USE                              _OFF
#define _XTAL12000K                             12000
#define _M2PLL_XTAL                             _XTAL12000K
#define _RTD_M2PLL_RATIO                        (_RTD_XTAL / _M2PLL_XTAL)


//--------------------------------------------------
// Audio PLL Lock Mode
//--------------------------------------------------
#define _HARDWARE_TRACKING                      0
#define _N_CTS                                  1

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
#define _AUDIO_LOCK_MODE                        _HARDWARE_TRACKING
#else
#define _AUDIO_LOCK_MODE                        _N_CTS
#endif

//--------------------------------------------------
// Set Adjusting Vertical Position Direction Method
//--------------------------------------------------
#define _V_POSITION_METHOD_0                    0
#define _V_POSITION_METHOD_1                    1

#define _V_POSITION_DIRECTION                   _V_POSITION_METHOD_1

//--------------------------------------------------
// Definitions for Panel Settings
//--------------------------------------------------
#define _PANEL_CMO                              0
#define _PANEL_AUO                              1
#define _PANEL_SAMSUNG                          2
#define _PANEL_INNOLUX                          3
#define _PANEL_CPT                              4

//--------------------------------------------------
// Definitions for Panel Settings
//--------------------------------------------------
#define _PANEL_TTL                              0
#define _PANEL_LVDS                             1
#define _PANEL_RSDS                             2

//--------------------------------------------------
// TMDS Supported
//--------------------------------------------------
#if((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_DVI_I_PORT) || \
    (_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || \
    (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || \
    (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
#define _TMDS_SUPPORT                           _ON
#else
#define _TMDS_SUPPORT                           _OFF
#endif

//--------------------------------------------------
// HDCP Supported
//--------------------------------------------------
#if(_TMDS_SUPPORT == _ON)
#define _HDCP_SUPPORT                           _ON
#else
#define _HDCP_SUPPORT                           _OFF
#endif

//--------------------------------------------------
// HDMI Supported
//--------------------------------------------------
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_HDMI_FROM_DVI_CONNECT == _ON))
#define _HDMI_SUPPORT                           _ON
#else
#define _HDMI_SUPPORT                           _OFF
#endif

//--------------------------------------------------
// DP Supported
//--------------------------------------------------
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
#define _DP_SUPPORT                             _ON
#else
#define _DP_SUPPORT                             _OFF
#endif

//--------------------------------------------------
// Video Supported
//--------------------------------------------------
#if((_D0_INPUT_PORT_TYPE == _D0_VIDEO8_PORT) || (_A1_INPUT_PORT_TYPE == _A1_VIDEO8_PORT) || (_VI_INPUT_PORT_TYPE == _VI_VIDEO8_PORT))
#define _VIDEO_SUPPORT                          _ON
#else
#define _VIDEO_SUPPORT                          _OFF
#endif

//--------------------------------------------------
// YPbPr Supported
//--------------------------------------------------
#if((_A0_INPUT_PORT_TYPE == _A0_YPBPR_PORT) || (_A1_INPUT_PORT_TYPE == _A1_YPBPR_PORT) || (_HSYNC_TYPE_SELECT == _HSYNC_WITH_SOG_SOY))
#define _YPBPR_SUPPORT                          _ON

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#elif(_COLOR_FORMAT_CONVERT == _ON)
#define _YPBPR_SUPPORT                          _ON
// V012 Modify 20100304 End

#else
#define _YPBPR_SUPPORT                          _OFF
#endif

//--------------------------------------------------
// Definitions of Input Source Type
//--------------------------------------------------
enum SourceTytpeDef
{
    _SOURCE_VGA = 0,

#if(_YPBPR_SUPPORT == _ON)
    _SOURCE_YPBPR,
#endif

//#if(_TMDS_SUPPORT == _ON)
    _SOURCE_DVI,
//#endif

//#if(_HDMI_SUPPORT == _ON)
    _SOURCE_HDMI,
//#endif

//#if(_DP_SUPPORT == _ON)
    _SOURCE_DP,
//#endif

#if(_VIDEO_SUPPORT == _ON)
    _SOURCE_VIDEO8,
#endif
    _SOURCE_NONE
};


//--------------------------------------------------
// Ext DAC Chip Supported
//--------------------------------------------------
#define _EXT_DAC_SUPPORT                        _OFF

//--------------------------------------------------
// Embeded DAC Chip Supported
//--------------------------------------------------
#if((_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
#define _EMB_DAC_SUPPORT                        _ON
#else
#define _EMB_DAC_SUPPORT                        _OFF
#endif

//--------------------------------------------------
// Audio Output Type of HDMI
//--------------------------------------------------
#define _I2S                                    0
#define _SPDIF                                  1

#define _AUDIO_OUTPUT_TYPE                      _I2S

//--------------------------------------------------
// Config of Over Driving Supported & FRC Supported
//--------------------------------------------------
#if(_MEMORY_WORK_TYPE == _OD_OFF_FRC_OFF)
#define _OD_SUPPORT                             _OFF
#define _FRC_SUPPORT                            _OFF
#elif(_MEMORY_WORK_TYPE == _OD_OFF_FRC_ON)
#define _OD_SUPPORT                             _OFF
#define _FRC_SUPPORT                            _ON
#elif(_MEMORY_WORK_TYPE == _OD_ON_FRC_OFF)
#define _OD_SUPPORT                             _ON
#define _FRC_SUPPORT                            _OFF
#elif(_MEMORY_WORK_TYPE == _OD_ON_FRC_ON)
#define _OD_SUPPORT                             _ON
#define _FRC_SUPPORT                            _ON
#endif

//--------------------------------------------------
// Config of FRC YUV Mode
//--------------------------------------------------
#define _FRC_YUV_MODE_SUPPORT                   _OFF
//--------------------------------------------------
// Config of OD Highlight Window Mode
//--------------------------------------------------
#if(_MEMORY_WORK_TYPE == _OD_ON_FRC_ON)
#define _OD_HW_MODE_SUPPORT                     _ON
#else
#define _OD_HW_MODE_SUPPORT                     _OFF
#endif


//--------------------------------------------------
// Input Port Search Times
//--------------------------------------------------
#if((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_DVI_I_PORT))
#define _D0_INPUT_PORT_SEARCH_TIMES             _SOURCE_DVI_SEARCH_TIMES

#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
#define _D0_INPUT_PORT_SEARCH_TIMES             _SOURCE_HDMI_SEARCH_TIMES

#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define _D0_INPUT_PORT_SEARCH_TIMES             _SOURCE_DP_SEARCH_TIMES

#elif(_D0_INPUT_PORT_TYPE == _D0_VIDEO8_PORT)
#define _D0_INPUT_PORT_SEARCH_TIMES             _SOURCE_VIDEO8_SEARCH_TIMES

#else
#define _D0_INPUT_PORT_SEARCH_TIMES             0
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_I_PORT))
#define _D1_INPUT_PORT_SEARCH_TIMES             _SOURCE_DVI_SEARCH_TIMES

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
#define _D1_INPUT_PORT_SEARCH_TIMES             _SOURCE_HDMI_SEARCH_TIMES

#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define _D1_INPUT_PORT_SEARCH_TIMES             _SOURCE_DP_SEARCH_TIMES

#else
#define _D1_INPUT_PORT_SEARCH_TIMES             0
#endif

#if((_A0_INPUT_PORT_TYPE == _A0_VGA_PORT) || (_A0_INPUT_PORT_TYPE == _A0_YPBPR_PORT))
#define _A0_INPUT_PORT_SEARCH_TIMES             _SOURCE_VGA_SEARCH_TIMES

#else
#define _A0_INPUT_PORT_SEARCH_TIMES             0
#endif

#if((_A1_INPUT_PORT_TYPE == _A1_VGA_PORT) || (_A1_INPUT_PORT_TYPE == _A1_YPBPR_PORT))
#define _A1_INPUT_PORT_SEARCH_TIMES             _SOURCE_VGA_SEARCH_TIMES

#elif(_A1_INPUT_PORT_TYPE == _A1_VIDEO8_PORT)
#define _A1_INPUT_PORT_SEARCH_TIMES             _SOURCE_VIDEO8_SEARCH_TIMES

#else
#define _A1_INPUT_PORT_SEARCH_TIMES             0
#endif


#if(_VI_INPUT_PORT_TYPE == _VI_VIDEO8_PORT)
#define _VI_INPUT_PORT_SEARCH_TIMES             _SOURCE_VIDEO8_SEARCH_TIMES

#else
#define _VI_INPUT_PORT_SEARCH_TIMES             0
#endif


//----------------------------------------------------------------------------------------------------
// RTD2120 Advance Settings
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// RTD2120 Watchdog Timer Support
//--------------------------------------------------
#define _WATCHDOG_TIMER                         _OFF

//--------------------------------------------------
// Field Merge Supported (Only supported in FRC mode)
//--------------------------------------------------
#if(_FRC_SUPPORT == _OFF)
#define _FIELD_MERGE_SUPPORT                    _OFF
#else
#define _FIELD_MERGE_SUPPORT                    _OFF
#endif

//--------------------------------------------------
// Config of FRC LINE or FRAME Mode
//--------------------------------------------------
#define _LINE_MODE                              0
#define _FRAME_MODE                             1

#if(_FIELD_MERGE_SUPPORT == _ON)
#define _FRC_MODE                               _LINE_MODE
#else
#define _FRC_MODE                               _FRAME_MODE
#endif

#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
//--------------------------------------------------
// Memory Size
//--------------------------------------------------
#define _MEMORY_16MB                            16
#define _MEMORY_32MB                            32
#define _MEMORY_64MB                            64
#define _MEMORY_128MB                           128


//--------------------------------------------------
// Config of Memory Bus Width & Memory Size
//--------------------------------------------------
#if(_MEMORY_CONFIG == _NO_MEMORY)
#define _MEMORY_BUS_WIDTH                       0
#define _MEMORY_SIZE                            0
#define _MEMORY_BIT_NUM                         0
#elif(_MEMORY_CONFIG == _1M_16BIT_1PCE)
#define _MEMORY_BUS_WIDTH                       16
#define _MEMORY_SIZE                            _MEMORY_16MB
#define _MEMORY_BIT_NUM                         16
#elif(_MEMORY_CONFIG == _1M_16BIT_2PCE)
#define _MEMORY_BUS_WIDTH                       32
#define _MEMORY_SIZE                            _MEMORY_32MB
#define _MEMORY_BIT_NUM                         16
#elif(_MEMORY_CONFIG == _2M_32BIT_1PCE)
#define _MEMORY_BUS_WIDTH                       32
#define _MEMORY_SIZE                            _MEMORY_64MB
#define _MEMORY_BIT_NUM                         32
#elif(_MEMORY_CONFIG == _2M_32BIT_2PCE)
#define _MEMORY_BUS_WIDTH                       64
#define _MEMORY_SIZE                            _MEMORY_128MB
#define _MEMORY_BIT_NUM                         32
#endif


//--------------------------------------------------
// Compress On or Off
//--------------------------------------------------
#if(_MEMORY_SIZE == _MEMORY_16MB)

#if(_PANEL_TYPE == _AU_LVDS_15)
#define _OD_COMPRESSION                         _OFF
#else
#define _OD_COMPRESSION                         _ON
#endif

#elif(_MEMORY_SIZE == _MEMORY_32MB)

#if(_PANEL_TYPE == _AU_LVDS_20_UXGA)
#define _OD_COMPRESSION                         _ON
#else
#define _OD_COMPRESSION                         _OFF
#endif

#else

#define _OD_COMPRESSION                         _OFF

#endif


//--------------------------------------------------
// Definitions of SDRAM Latency
//--------------------------------------------------
#define _YC_OD_PIXDIFFVAL                       16  //range: 0~63


//--------------------------------------------------
// Definitions of SDRAM Latency
//--------------------------------------------------
#define _ROW_WR_DELAY                           2  //0~1:Resered, 2~5:2~5 MCLK, 6~7:Resered
#define _ROW_RD_DELAY                           2  //0~1:Resered, 2~5:2~5 MCLK, 6~7:Resered

#define _SDR_ROW_DELAY                          ((_ROW_WR_DELAY << 3) | (_ROW_RD_DELAY))

#define _SDR_COL_DELAY                          ((3 << 5) | 0x04)  //0~1:Resered, 2~3:2~3 MCLK, 4~7:Resered


//--------------------------------------------------
// Definitions of Clock/Latch Delay
//--------------------------------------------------
#define _CLOCK_INV                              0x00  //Bit3:Inversion bit
#define _CLOCK_DELAY                            0     //Bit0~2:0~7 CLK Delay.

#define _SDR_CLOCK_DELAY                        (_CLOCK_INV | _CLOCK_DELAY)

#endif // End of #if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))

//--------------------------------------------------
// Definations of Input Source OSD
//--------------------------------------------------
#define _SWITCH_INPUT_SOURCE_OSD                _ON


//--------------------------------------------------
// Definations of Hsync Type Detection
//--------------------------------------------------
#define _AUTO_RUN                               0
#define _NORMAL_RUN                             1

#define _HSYNC_DETECTION                        _AUTO_RUN

//--------------------------------------------------
// Set Adjusting ADC offset Method
//--------------------------------------------------
#define _ADJUST_BY_FW                           0               // Adjust ADC offset by F/W
#define _ADJUST_BY_HW                           1               // Adjust ADC offset by H/W

#define _ADC_OFFSET_ADJUSTING                   _ADJUST_BY_HW


//--------------------------------------------------
// OSD select Auto search or Fixed source
//--------------------------------------------------
#define _SOURCE_SEARCH_TYPE_BY_OSD              _ON

//--------------------------------------------------
// Low Frame Rate Setting
//--------------------------------------------------
#define _LOW_FRAME_RATE_SUPPORT                 _OFF

//--------------------------------------------------
// Auto Config Setting
//--------------------------------------------------
#define _AUTO_CLOCK_MOIRE_SMEAR_EFFECT          _OFF

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Set Overscan Ratio (0.1 %)
//--------------------------------------------------
#define _OVERSCAN_RATIO                         30

#if(_OVERSCAN_RATIO >= 500)
#error Too large overscan ratio!
#endif
#endif
// V012 Modify 20100316 End

// V013 VGA Patch Note (10) 20100416 Modify Start
// Patch Reason : Support Auto Config For Yuv Color.
//----------------------------------------------------------------------------------------------------
// YUV AUTO DEFINE
//----------------------------------------------------------------------------------------------------
#if(_YPBPR_SUPPORT == _ON)
#define _YUV_AUTO_CONFIG_SUPPORT                _ON
#else
#define _YUV_AUTO_CONFIG_SUPPORT                _OFF
#endif
// V013 VGA Patch Note (10) 20100416 Modify End
