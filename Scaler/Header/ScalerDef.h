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
// ID Code      : ScalerDef.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of  Control Register Address
//--------------------------------------------------

//--------------------------------------------------
// Global Event Flag
//--------------------------------------------------
#define _ID_REG_00                          0x00        // ID Code Register
#define _HOST_CTRL_01                       0x01        // Host Control Register
#define _STATUS0_02                         0x02        // Status0 Register
#define _STATUS1_03                         0x03        // Status1 Register
#define _IRQ_CTRL0_04                       0x04        // IRQ Control Register0
#define _HDMI_STATUS0_05                    0x05        // HDMI Status0 Register
#define _HDMI_STATUS1_06                    0x06        // HDMI Status1 Register
#define _NEW_ADDED_STATUS0_07               0x07        // NEW Added Status0 Register
#define _NEW_ADDED_STATUS1_08               0x08        // NEW Added Status1 Register
//#define _RESERVED_09                        0x09        // Reserved 09
//#define _RESERVED_0A                        0x0A        // Reserved 0A
//#define _RESERVED_0B                        0x0B        // Reserved 0B
#define _WATCH_DOG_CTRL0_0C                 0x0C        // Watch Dog Control Register0
#define _WATCH_DOG_CTRL1_0D                 0x0D        // Watch Dog Control Register1
//#define _RESERVED_0E                        0x0E        // Reserved 0E
//#define _RESERVED_0F                        0x0F        // Reserved 0F
#define _VGIP_CTRL_10                       0x10        // Video Graphic Input Port(VGIP) Control Register
#define _VGIP_SIGINV_11                     0x11        // Input Control Signal Inverted Register
#define _VGIP_DELAY_CTRL_12                 0x12        // VGIP Delay Control Register
#define _VGIP_ODD_CTRL_13                   0x13        // VGIP Odd Control Register

//--------------------------------------------------
// Input Frame Window
//--------------------------------------------------
#define _IPH_ACT_STA_H_14                   0x14        // Input Horizontal Active Start HByte
#define _IPH_ACT_STA_L_15                   0x15        // Input Horizontal Active Start LByte
#define _IPH_ACT_WID_H_16                   0x16        // Input Horizontal Active Width HByte
#define _IPH_ACT_WID_L_17                   0x17        // Input Horizontal Active Width LByte
#define _IPV_ACT_STA_H_18                   0x18        // Input Vertical Active Start HByte
#define _IPV_ACT_STA_L_19                   0x19        // Input Vertical Active Start LByte
#define _IPV_ACT_LEN_H_1A                   0x1A        // Input Vertical Active Length HByte
#define _IPV_ACT_LEN_L_1B                   0x1B        // Input Vertical Active Length LByte
#define _IVS_DELAY_1C                       0x1C        // Internal Input Vertical Sync(VS) Delay Control Register
#define _IHS_DELAY_1D                       0x1D        // Internal Input Horizontal Sync(HS) Delay Control Register
#define _VGIP_HV_DELAY_1E                   0x1E        // VGIP HS/VS Delay
#define _V8_YUV_CONVERSION_1F               0x1F        // V8 Source Select and YUV 422 to 444 Conversion
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _V8CLK_SEL_20                       0x20        // V8clk Selection Setting
#endif
//#define _RESERVED_20                        0x20        // Reserved 20
//#define _RESERVED_21                        0x21        // Reserved 21

//--------------------------------------------------
// FIFO Frequency
//--------------------------------------------------
#define _FIFO_FREQUENCY_22                  0x22        // FIFO Frequency

//--------------------------------------------------
// Input Pattern Generator 

#define _PAGE7_DSIP_PG_R_CTRL                       0xF0

#define _PAGE7_DSIP_PG_R_Initial                   0xF3
#define _PAGE7_DSIP_PG_G_Initial                   0xF4
#define _PAGE7_DSIP_PG_B_Initial                   0xF5


//--------------------------------------------------
#define _SCALE_DOWN_CTRL_23                 0x23        // Scale Down Control Register
#define _SD_ACCESS_PORT_24                  0x24        // Scaling Down Access Port
#define _SD_DATA_PORT_25                    0x25        // Scaling Down Data Port
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _I_YUV444to422_26                   0x26        // I Domain YUV444To422 Control
#endif
//#define _RESERVED_26                        0x26        // Reserved 26
//#define _RESERVED_27                        0x27        // Reserved 27

//--------------------------------------------------
// Display Format(Port)
//--------------------------------------------------
#define _VDISP_CTRL_28                      0x28        // Video Display Control Register
#define _VDISP_SIGINV_29                    0x29        // Display Control Signal Inverted Register
#define _DISP_ACCESS_PORT_2A                0x2A        // Display Format Access Port
#define _DISP_DATA_PORT_2B                  0x2B        // Display Format Data Port
#define _OP_CRC_CTRL_2C                     0x2C        // Output CRC Control Register
#define _OP_CRC_CHECKSUM_2D                 0x2D        // Output CRC Checksum
//#define _RESERVED_2E                        0x2E        // Reserved 2E
//#define _RESERVED_2F                        0x2F        // Reserved 2F

//--------------------------------------------------
// FIFO Window(Port)
//--------------------------------------------------
#define _FIFO_ACCESS_PORT_30                0x30        // FIFO Window Address Port
#define _FIFO_DATA_PORT_31                  0x31        // FIFO Window Data Port

//--------------------------------------------------
// Scale Up Function(Port)
//--------------------------------------------------
#define _SCALE_CTRL_32                      0x32        // Scale Control Register
#define _SU_ACCESS_PORT_33                  0x33        // Scale Up Factor Access Port
#define _SU_DATA_PORT_34                    0x34        // Scale Up Factor Data Port
#define _FILTER_CTRL_35                     0x35        // Filter Control Register
#define _FILTER_ACCESS_PORT_36              0x36        // User Defined Filter Access Port
//Address: 37~3F Reserved

//--------------------------------------------------
// Frame Sync Fine Tune
//--------------------------------------------------
#define _IVS2DVS_DELAY_LINES_40             0x40        // IVS to DVS Delay Lines
#define _IV_DV_DELAY_CLK_ODD_41             0x41        // Frame Sync Delay Fine Tuning ODD
#define _IV_DV_DELAY_CLK_EVEN_42            0x42        // Frame Sync Delay Fine Tuning EVEN
#define _FS_DELAY_FINE_TUNING_43            0x43        // Frame Sync Delay Fine Tuning Control Register
#define _LAST_LINE_H_44                     0x44        // Last Line HByte
#define _LAST_LINE_L_45                     0x45        // Last Line LByte
//#define _RESERVED_46                        0x46        // Reserved 46

//--------------------------------------------------
// Sync Processor(Port)
//--------------------------------------------------
#define _SYNC_SELECT_47                     0x47        // Sync Select Control Register
#define _SYNC_INVERT_48                     0x48        // Sync Invert Control Register
#define _SYNC_CTRL_49                       0x49        // Sync Processor Control Register
#define _STABLE_HIGH_PERIOD_H_4A            0x4A        // Stable High Period HByte
#define _STABLE_HIGH_PERIOD_L_4B            0x4B        // Stable High Period LByte
#define _VSYNC_COUNTER_LEVEL_MSB_4C         0x4C        // Vertical Sync Counter Level MSB
#define _VSYNC_COUNTER_LEVEL_LSB_4D         0x4D        // Vertical Sync Counter Level LSB
#define _HSYNC_TYPE_DETECTION_FLAG_4E       0x4E        // Hsync Type Detection Flag
#define _STABLE_MEASURE_4F                  0x4F        // Stable Measure
#define _STABLE_PERIOD_H_50                 0x50        // Stable Period HByte
#define _STABLE_PERIOD_L_51                 0x51        // Stable Period LByte
#define _MEAS_HS_PERIOD_H_52                0x52        // HSync Period Measured Result HByte
#define _MEAS_HS_PERIOD_L_53                0x53        // HSync Period Measured Result LByte
#define _MEAS_VS_PERIOD_H_54                0x54        // VSync Period Measured Result HByte
#define _MEAS_VS_PERIOD_L_55                0x55        // VSync Period Measured Result LByte
#define _MEAS_HS_VS_HIGH_PERIOD_H_56        0x56        // HSync and VSync High Period Measured Results HByte
#define _MEAS_HS_VS_HIGH_PERIOD_L_57        0x57        // HSync and VSync High Period Measured Results LByte
#define _MEAS_HS_VS_HI_SEL_58               0x58        // HSync and VSync High Period Measured Select
#define _MEAS_ACTIVE_REGION_59              0x59        // Active Region Measured by Crystal Clock
#define _SYNC_TEST_MISC_5A                  0x5A        // Sync Test MISC Register
//#define _RESERVED_5B                        0x5B        // Reserved 5B
#define _SYNC_PROC_ACCESS_PORT_5C           0x5C        // Sync Processor Access Port Address
#define _SYNC_PROC_DATA_PORT_5D             0x5D        // Sync Processor Access Port Data
//#define _RESERVED_5E                        0x5E        // Reserved 5E
//#define _RESERVED_5F                        0x5F        // Reserved 5F

//--------------------------------------------------
// Hightlight Window(Port)
//--------------------------------------------------
#define _HW_ACCESS_PORT_60                  0x60        // Highlight Window Access Port
#define _HW_DATA_PORT_61                    0x61        // Highlight Window Data Port

//--------------------------------------------------
// Color Processor Control(Port)
//--------------------------------------------------
#define _COLOR_CTRL_62                      0x62        // Color Processor Control Register
#define _SRGB_ACCESS_PORT_63                0x63        // sRGB Access Port
#define _CB_ACCESS_PORT_64                  0x64        // Contrast/Brightness Access Port
#define _CB_DATA_PORT_65                    0x65        // Contrast/Brightness Data Port

//--------------------------------------------------
// Gamma Control
//--------------------------------------------------
#define _GAMMA_PORT_66                      0x66        // Gamma Access Port
#define _GAMMA_CTRL_67                      0x67        // Gamma Control Register
#define _GAMMA_BIST_68                      0x68        // Gamma BIST Control Register

//--------------------------------------------------
// Dithering Control (D domain)
//--------------------------------------------------
#define _DITHERING_DATA_ACCESS_69           0x69        // Dithering Table DATA ACCESS (D Domain)
#if(_SCALER_TYPE == _RTD2472D)
#define _DITHERING_CTRL_6A                  0x6A        // Dithering Control Register
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _DITHERING_CTRL1_6A                 0x6A        // Dithering Control Register
#define _DITHERING_CTRL2_6B                 0x6B        // Dithering Table Reference
#else
    No Setting !!
#endif  //End of #if(_SCALER_TYPE == _RTD2472D)
//#define _RESERVED_6B                        0x6B        // Reserved 6B

//--------------------------------------------------
// Overlay/Color Palette/Background Color Control
//--------------------------------------------------
#define _OVERLAY_CTRL_6C                    0x6C        // Overlay Display Control Register
#define _BGND_COLOR_CTRL_6D                 0x6D        // Background Color Control Register
#define _OVERLAY_LUT_ADDR_6E                0x6E        // Overlay Look Up Table (LUT) Address
#define _COLOR_LUT_PORT_6F                  0x6F        // Color LUT Access Port

//--------------------------------------------------
// Image Auto Function
//--------------------------------------------------
#define _H_BOUNDARY_H_70                    0x70        // Horizontal Start/End Boundary HByte
#define _H_BOUNDARY_STA_L_71                0x71        // Horizontal Start Boundary HByte
#define _H_BOUNDARY_END_L_72                0x72        // Horizontal End Boundary HByte
#define _V_BOUNDARY_H_73                    0x73        // Vertical Start/End Boundary HByte
#define _V_BOUNDARY_STA_L_74                0x74        // Vertical Start Boundary LByte
#define _V_BOUNDARY_END_L_75                0x75        // Vertical End Boundary LByte
#define _RED_NOISE_MARGIN_76                0x76        // Red Noise Margin Control Register
#define _GRN_NOISE_MARGIN_77                0x77        // Green Noise Margin Control Register
#define _BLU_NOISE_MARGIN_78                0x78        // Blue Noise Margin Control Register
#define _DIFF_THRESHOLD_79                  0x79        // Difference Threshold
#define _AUTO_ADJ_CTRL0_7A                  0x7A        // Auto Adjusting Control Register 0
#define _HW_AUTO_PHASE_CTRL0_7B             0x7B        // Hardware Auto Phase Control Register 0
#define _HW_AUTO_PHASE_CTRL1_7C             0x7C        // Hardware Auto Phase Control Register 1
#define _AUTO_ADJ_CTRL1_7D                  0x7D        // Auto Adjusting Control Register 1
#define _V_START_END_H_7E                   0x7E        // Active Region Vertical Start/End HByte
#define _V_START_L_7F                       0x7F        // Active Region Vertical Start LByte
#define _V_END_L_80                         0x80        // Active Region Vertical End LByte
#define _H_START_END_H_81                   0x81        // Active Region Horizontal Start/End HByte
#define _H_START_L_82                       0x82        // Active Region Horizontal Start LByte
#define _H_END_L_83                         0x83        // Active Region Horizontal End LByte
#define _AUTO_PHASE_3_84                    0x84        // Auto Phase Result Register Byte 3
#define _AUTO_PHASE_2_85                    0x85        // Auto Phase Result Register Byte 2
#define _AUTO_PHASE_1_86                    0x86        // Auto Phase Result Register Byte 1
#define _AUTO_PHASE_0_87                    0x87        // Auto Phase Result Register Byte 0

//--------------------------------------------------
// Dithering Control (I domain)
//--------------------------------------------------
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _DITHERING_DATA_ACCESS_88           0x88        // Dithering Table DATA ACCESS (I Domain)
#define _DITHERING_CTRL1_89                 0x89        // Dithering Control Register
#endif
//#define _RESERVED_88                        0x88        // Reserved 88
//#define _RESERVED_89                        0x89        // Reserved 89
//#define _RESERVED_8A                        0x8A        // Reserved 8A

//--------------------------------------------------
// Embedded Timing Controller(Port)
//--------------------------------------------------
#define _TCON_ADDR_PORT_8B                  0x8B        // TCON Address Port for Embedded TCON Access
#define _TCON_DATA_PORT_8C                  0x8C        // TCON Data Port for Embedded TCON Access

//--------------------------------------------------
// Pin Configuration & Test Function(Port)
//--------------------------------------------------
#define _PS_ACCESS_PORT_8D                  0x8D        // Pin Share Access Port
#define _PS_DATA_PORT_8E                    0x8E        // Pin Share Data Port
//#define _RESERVED_8F                        0x8F        // Reserved 8F

//--------------------------------------------------
// Embedded OSD
//--------------------------------------------------
#define _OSD_ADDR_MSB_90                    0x90        // OSD Address MSB
#define _OSD_ADDR_LSB_91                    0x91        // OSD Address LSB
#define _OSD_DATA_PORT_92                   0x92        // OSD Data Port
#define _OSD_SCRAMBLE_93                    0x93        // OSD Scramble
#define _OSD_TEST_94                        0x94        // OSD Test
//#define _RESERVED_95                        0x95        // Reserved 95
//#define _RESERVED_96                        0x96        // Reserved 96
//#define _RESERVED_97                        0x97        // Reserved 97

//--------------------------------------------------
// Digital Filter
//--------------------------------------------------
#define _DIGITAL_FILTER_CTRL_98             0x98        // Digital Filter Control Register
#define _DIGITAL_FILTER_PORT_99             0x99        // Digital Filter Port

//--------------------------------------------------
// VBI(Port)
//--------------------------------------------------
#if((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _VBI_ACCESS_PORT_9A                 0x9A        // VBI Access Port
#define _VBI_DATA_PORT_9B                   0x9B        // VBI Data Port
#endif

//--------------------------------------------------
// Video Color Space Conversion
//--------------------------------------------------
#if(_SCALER_TYPE == _RTD2472D)
#define _YUV2RGB_CTRL_9C                    0x9C        // YUV to RGB Control Register
#define _YUV_RGB_ACCESS_9D                  0x9D        // YUV to RGB Access
#define _YUV_RGB_COEF_DATA_9E               0x9E        // YUV to RGB Coefficient Data Port
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _YUV_RGB_CTRL_9C                    0x9C        // YUV<->RGB Control Register
#define _YUV_RGB_COEF_DATA_9D               0x9D        // YUV<->RGB Coefficient Data
//#define _RESERVED_9E                        0x9E        // Reserved 9E
#else
   No Setting !!
#endif//End of #if(_SCALER_TYPE == _RTD2472D)

//OLD
//--------------------------------------------------
// Peaking Filter and Coring Control(Port)
//--------------------------------------------------
#define _PC_ACCESS_PORT_9A                  0x9A        // Peaking/Coring Access Port
#define _PC_DATA_PORT_9B                    0x9B        // Peaking/Coring Data Port


//##############################################################################################//
//##############################################################################################//
//##########################################     PAGE     ######################################//
//##############################################################################################//
//##############################################################################################//

//--------------------------------------------------
// Paged Control Register
//--------------------------------------------------
#define _PAGE_SELECT_9F                     0x9F        // Page Selector (CR[A0] ~ CR[FF])

/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page 0: Embedded ADC///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------
// ADC (Page0)
//--------------------------------------------------
#define _P0_ADC_POWER_SOG_SOY_CTL_BA        0xBA        // ADC Power for SOG /SOY
#define _P0_ADC_2X_SAMPLE_BB                0xBB        // ADC 2X Sample Clock Select
#define _P0_ADC_CLOCK_BC                    0xBC        // ADC Clock Output Select
#define _P0_ADC_TEST_BD                     0xBD        // ADC Test Function
#define _P0_ADC_RGB_GAIN_LSB_BE             0xBE        // ADC RGB Gain LSB
#define _P0_ADC_RGB_OFFSET_LSB_BF           0xBF        // ADC RGB Offset LSB
#define _P0_RED_GAIN_C0                     0xC0        // ADC Red Channel Gain Adjust
#define _P0_GRN_GAIN_C1                     0xC1        // ADC Green Channel Gain Adjust
#define _P0_BLU_GAIN_C2                     0xC2        // ADC Blue Channel Gain Adjust
#define _P0_RED_OFFSET_C3                   0xC3        // ADC Red Channel Offset Adjust
#define _P0_GRN_OFFSET_C4                   0xC4        // ADC Green Channel Offset Adjust
#define _P0_BLU_OFFSET_C5                   0xC5        // ADC Blue Channel Offset Adjust
#define _P0_ADC_POWER_C6                    0xC6        // ADC Power Control Register
#define _P0_ADC_I_BAIS0_C7                  0xC7        // ADC Bais Current Control Register0
#define _P0_ADC_I_BAIS1_C8                  0xC8        // ADC Bais Current Control Register1
#define _P0_ADC_I_BAIS2_C9                  0xC9        // ADC Bais Current Control Register2
#define _P0_ADC_I_BAIS3_CA                  0xCA        // ADC Bais Current Control Register3
#define _P0_ADC_I_BAIS4_CB                  0xCB        // ADC Bais Current Control Register4
#define _P0_ADC_V_BIAS0_CC                  0xCC        // ADC Bais Voltage Control Register0
#define _P0_ADC_V_BIAS1_CD                  0xCD        // ADC Bais Voltage Control Register1
#define _P0_ADC_RGB_CTRL_CE                 0xCE        // ADC RGB Control Register
#define _P0_ADC_RED_CTL_CF                  0xCF        // ADC Red Channel Control Register
#define _P0_ADC_GREEN_CTL_D0                0xD0        // ADC Green Channel Control Register
#define _P0_ADC_BLUE_CTL_D1                 0xD1        // ADC Blue Channel Control Register
#define _P0_ADC_SOG_CMP_D2                  0xD2        // ADC SOG Input Mux Select
#define _P0_ADC_DCR_CTRL_D3                 0xD3        // ADC DCR Reference Control Register
#define _P0_ADC_CLAMP_CTRL0_D4              0xD4        // ADC Clamp Control Register0
#define _P0_ADC_CLAMP_CTRL1_D5              0xD5        // ADC Clamp Control Register1
#define _P0_ADC_CLAMP_CTRL2_D6              0xD6        // ADC Clamp Control Register2
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _P0_ADC_SOG_DAC_SOY_CONTROL_D7      0xD7        // ADC SOG0 DAC Control
#define _P0_TEST_PTN_POS_H_D8               0xD8        // Test Pattern H/V Position HByte
#define _P0_TEST_PTN_VPOS_L_D9              0xD9        // Assign the test pattern digitized position(LByte) in line after V_Start.
#define _P0_TEST_PTN_HPOS_L_DA              0xDA        // Assign the test pattern digitized position(LByte) in line after H_Start.
#define _P0_TEST_PTN_RD_DB                  0xDB        // Test Pattern Red Channel Digitized Result
#define _P0_TEST_PTN_GD_DC                  0xDC        // Test Pattern Green Channel Digitized Result
#define _P0_TEST_PTN_BD_DD                  0xDD        // Test Pattern Blue Channel Digitized Result
#define _P0_TEST_PTN_CTRL_DE                0xDE        // Test Pattern Control
#if(_SCALER_TYPE == _RTD2545LR)
#define _P0_EBD_REGLATOR_VOL_DF             0xDF        // Embedded Regulator Control
#endif
#endif
//#define _P0_TEST_PTN_POS_H_D7               0xD7        // Test Pattern H/V Position HByte
//#define _P0_TEST_PTN_VPOS_L_D8              0xD8        // Assign the test pattern digitized position(LByte) in line after V_Start.
//#define _P0_TEST_PTN_HPOS_L_D9              0xD9        // Assign the test pattern digitized position(LByte) in line after H_Start.
//#define _P0_TEST_PTN_RD_DA                  0xDA        // Test Pattern Red Channel Digitized Result
//#define _P0_TEST_PTN_GD_DB                  0xDB        // Test Pattern Green Channel Digitized Result
//#define _P0_TEST_PTN_BD_DC                  0xDC        // Test Pattern Blue Channel Digitized Result

//--------------------------------------------------
// Auto Black Level (Page0)
//--------------------------------------------------
#define _P0_ABL_CTRL1_E2                    0xE2        // Auto Black Level Control Register1
#define _P0_ABL_CTRL2_E3                    0xE3        // Auto Black Level Control Register2
#define _P0_ABL_CTRL3_E4                    0xE4        // Auto Black Level Control Register3
#define _P0_ABL_CTRL4_E5                    0xE5        // Auto Black Level Control Register4
#define _P0_ABL_CTRL5_E6                    0xE6        // Auto Black Level Control Register5
#define _P0_ABL_CTRL6_E7                    0xE7        // Auto Black Level Control Register6
#define _P0_ABL_CTRL7_E8                    0xE8        // Auto Black Level Control Register6
//#define _P0_ABL_R_VALUE_E9                  0xE9        // Auto Black Level Value of Red Channel in Test Mode
//#define _P0_ABL_G_VALUE_EA                  0xEA        // Auto Black Level Value of Green Channel in Test Mode
//#define _P0_ABL_B_VALUE_EB                  0xEB        // Auto Black Level Value of Blue Channel in Test Mode
//#define _P0_ABL_R_NOISE_VALUE_EC            0xEC        // Auto Black Level Noise Value of Red Channel in Test Mode
//#define _P0_ABL_G_NOISE_VALUE_ED            0xED        // Auto Black Level Noise Value of Green Channel in Test Mode
//#define _P0_ABL_B_NOISE_VALUE_EE            0xEE        // Auto Black Level Noise Value of Blue Channel in Test Mode
//Address: P0-EF ~ P0-F2 Reserved

//--------------------------------------------------
// Low Voltage Reset (Page0)
//--------------------------------------------------
#define _P0_POWER_ON_RESET_F3               0xF3        // Negative Threshold Value For Power On Reset

//--------------------------------------------------
// Schmitt Trigger Control (Page0)
//--------------------------------------------------
#define _P0_HS_SCHMITT_TRIGGER_CTRL_F4      0xF4        // Schmitt Trigger Control Register
//Address: P0-F5 ~ P0-FF Reserved

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
//--------------------------------------------------
// Memory PLL (Page0)
//--------------------------------------------------
#define _P0_MPLL_M_F5                       0xF5        // MPLL M Code
#define _P0_MPLL_N_F6                       0xF6        // MPLL N Code
#define _P0_MPLL_CRNT_F7                    0xF7        // MPLL Current Control
#define _P0_MPLL_WD_F8                      0xF8        // MPLL WatchDog Control
#define _P0_MPLL_CAL_F9                     0xF9        // MPLL Calibration

//--------------------------------------------------
// MCLK Spread Spectrum (Page0)
//--------------------------------------------------
#define _P0_MCLK_FINE_TUNE_OFFSET_MSB_FA    0xFA        // MCLK Offset MSB
#define _P0_MCLK_FINE_TUNE_OFFSET_LSB_FB    0xFB        // MCLK Offset LSB
#define _P0_MCLK_SPREAD_SPECTRUM_FC         0xFC        // MCLK Spreading Range
#define _P0_MPLL_RESULT_FD                  0xFD        // MPLL Calibration Result
//Address: P0-FE ~ P0-FF Reserved
#endif // End of #if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))


/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page 1: PLL////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// DDS Setting For ADC PLL (Page1)
//--------------------------------------------------
#define _P1_PLL_DIV_CTRL_A0                 0xA0        // PLL DIV Control Register
#define _P1_I_CODE_M_A1                     0xA1        // I Code MByte
#define _P1_I_CODE_L_A2                     0xA2        // I Code LByte
#define _P1_P_CODE_A3                       0xA3        // P Code

#define _P1_PFD_CALIBRATED_RESULTS_H_A4     0xA4        // PFD Calibrated Result HByte
#define _P1_PFD_CALIBRATED_RESULTS_L_A5     0xA5        // PFD Calibrated Result LByte
#define _P1_PE_MEASURE_H_A6                 0xA6        // Phase Error Measure HByte
#define _P1_PE_MEASURE_L_A7                 0xA7        // Phase Error Measure LByte
#define _P1_PE_MAX_MEASURE_H_A8             0xA8        // Phase Error Max MEasure HByte
#define _P1_PE_MAX_MEASURE_L_A9             0xA9        // Phase Error Max MEasure LByte
#define _P1_FAST_PLL_CTRL_AA                0xAA        // Fast PLL Control Register
#define _P1_FAST_PLL_SUM_I_AB               0xAB        // Fast PLL SUM_I

//--------------------------------------------------
// ADC PLL (Page1)
//--------------------------------------------------
#define _P1_PLL_M_AC                        0xAC        // PLL M code
#define _P1_PLL_N_AD                        0xAD        // PLL N Code
#define _P1_PLL_CRNT_AE                     0xAE        // PLL Current/Resistor Register
#define _P1_PLL_WD_AF                       0xAF        // PLL Watch Dog Register
#define _P1_MIX_B0                          0xB0        // PLL Mix Register
#define _P1_PLLDIV_H_B1                     0xB1        // PLL DIV HByte
#define _P1_PLLDIV_L_B2                     0xB2        // PLL DIV LByte
//#define _P1_PLLPHASE_CTRL0_B3               0xB3        // PLL Phase Control Register0
#define _P1_PLLPHASE_CTRL1_B4               0xB4        // PLL Phase Control Register1
#define _P1_PLL_PHASE_INTERPOLATION_B5      0xB5        // PLL Phase Interpolation
#define _P1_P_CODE_MAPPING_METHOD_B6        0xB6        // P Code Mapping Method
#define _P1_PE_TRACKING_METHOD_B7           0xB7        // PE Tracking Method
#define _P1_DDS_MIX_1_B8                    0xB8        // DDS Mix 1
#define _P1_DDS_MIX_2_B9                    0xB9        // DDS Mix 2
#define _P1_DDS_MIX_3_BA                    0xBA        // DDS Mix 3
#define _P1_DDS_MIX_4_BB                    0xBB        // DDS Mix 4
#define _P1_DDS_MIX_5_BC                    0xBC        // DDS Mix 5
//#define _P1_DDS_MIX_6_BD                    0xBD        // DDS Mix 6
//#define _P1_DDS_MIX_7_BE                    0xBE        // DDS Mix 7

//--------------------------------------------------
// DPLL (Page1)
//--------------------------------------------------
#define _P1_DPLL_M_BF                       0xBF        // DPLL M Divider
#define _P1_DPLL_N_C0                       0xC0        // DPLL N Divider
#define _P1_DPLL_CRNT_C1                    0xC1        // DPLL Current/Resistor Register

//--------------------------------------------------
// DCLK Spread Spectrum (Page1)
//--------------------------------------------------
#define _P1_DPLL_WD_C2                      0xC2        // DPLL Watch Dog Register
#if(_SCALER_TYPE == _RTD2472D)
#define _P1_DPLL_OTHER_C3                   0xC3        // DPLL Other Register
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _P1_DPLL_CAL_C3                     0xC3        // DPLL Calibration
#else
   No Setting !
#endif //End of #if(_SCALER_TYPE == _RTD2472D)
#define _P1_DCLK_FINE_TUNE_OFFSET_MSB_C4    0xC4        // Display Clock Fine Tune Offset MSB
#define _P1_DCLK_FINE_TUNE_OFFSET_LSB_C5    0xC5        // Display Clock Fine Tune Offset LSB
#define _P1_DCLK_SPREAD_SPECTRUM_C6         0xC6        // Display Clock Spread Spectrum
#define _P1_EVEN_FIX_LASTLINE_DVTOTAL_M_C7  0xC7        // Even Fixed Last Line MSB
#define _P1_EVEN_FIX_LASTLINE_DVTOTAL_L_C8  0xC8        // Even Fixed Last Line DVTotal LSB
#define _P1_EVEN_FIX_LASTLINE_LENGTH_L_C9   0xC9        // Even Fixed Last Line Length LSB
#define _P1_EVEN_FIXED_LAST_LINE_CTRL_CA    0xCA        // Fixed Last Line Control Register
//#define _P1_ODD_FIX_LASTLINE_DVTOTAL_M_CB           0xCB        // Odd Fixed Last Line MSB
//#define _P1_ODD_FIX_LASTLINE_DVTOTAL_L_CC   0xCC        // Odd Fixed Last Line DVTotal LSB
#if(_SCALER_TYPE == _RTD2472D)
#define _P1_ODD_FIX_LASTLINE_LENGTH_L_CD    0xCD        // Odd Fixed Last Line Length LSB
#define _P1_DCLK_SPREAD_SPECTRUM_CE         0xCE        // Dclk Spread Spectrum
#define _P1_PHASE_RESULT_MSB_CF             0xCF        // Phase Result MSB
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _P1_MCLK_FINE_TUNE_OFFSET_MSB_CD       0xCD        // Mclk offset MSB
#define _P1_MCLK_FINE_TUNE_OFFSET_LSB_CE       0xCE        // Mclk offset LSB
#define _P1_MCLK_SPREAD_SPECTRUM_CF            0xCF        // Mclk Spread Spectrum
#else
   No Setting !!
#endif //End of #if(_SCALER_TYPE == _RTD2472D)

//#define _P1_PHASE_LINE_LSB_D0               0xD0        // Phase Line LSB
//#define _P1_PHASE_PIXEL_LSB_D1              0xD1        // Phase Pixel LSB
//#define _P1_TARGET_DCLK_TUNE_OFFSET_MSB_D2  0xD2        // Target Dclk Tune Offset MSB
//#define _P1_TARGET_DCLK_TUNE_OFFSET_LSB_D3  0xD3        // Target Dclk Tune Offset LSB
//Address: P1-D4 ~ P1-DF Reserved
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _P1_DPLL_RESULT_D4                    0xD4        // DPLL Calibration Result
//Address: P1-D5 ~ P1-DF Reserved
#endif

//--------------------------------------------------
// Multiply PLL For Input Crystal (Page1)
//--------------------------------------------------
#if(_SCALER_TYPE == _RTD2472D)
#define _P1_MULTIPLY_PLL_CTRL0_E0           0xE0        // M2PLL Control Register0
#define _P1_MULTIPLY_PLL_CTRL1_E1           0xE1        // M2PLL Control Register1
//#define _P1_RESERVED_E2                     0xE2        // P1 Reserved E2
//#define _P1_RESERVED_E3                     0xE3        // P1 Reserved E3
#define _P1_MULTIPLY_PLL_CTRL2_E4           0xE4        // M2PLL Control Register2
#define _P1_MULTIPLY_PLL_CTRL3_E5           0xE5        // M2PLL Control Register3
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _P1_M2PLL_M_E0                      0xE0        // M2PLL M Code
#define _P1_M2PLL_N_E1                      0xE1        // M2PLL N Code
//#define _P1_RESERVED_E2                     0xE2        // P1 Reserved E2
//#define _P1_RESERVED_E3                     0xE3        // P1 Reserved E3
#define _P1_M2PLL_CRNT_E4                   0xE4        // M2PLL Curent Control
#define _P1_M2PLL_WD_E5                     0xE5        // M2PLL Watch Dog
#else
    No Setting !!
#endif //End of #if(_SCALER_TYPE == _RTD2472D)
//Address: P1-E6 ~ P1-EF Reserved

//--------------------------------------------------
// Audio DAC (Page1)
//--------------------------------------------------
#define _P1_BB_POWER0_F0                    0xF0        // DAC Power Control0
#define _P1_BB_POWER1_F1                    0xF1        // DAC Power Control1
#define _P1_AIN_CTL_F2                      0xF2        // DAC AIN Control
#define _P1_DAC_CTL_F3                      0xF3        // DAC Output Volume Control
#define _P1_AOUT_CTL_F4                     0xF4        // DAC AOUT Control
#define _P1_HPOUT_CTL_F5                    0xF5        // DAC HPOUT Control
#define _P1_MBIAS_CTL0_F6                   0xF6        // DAC Bias Current Control0
#define _P1_MBIAS_CTL1_F7                   0xF7        // DAC Bias Current Control1
#define _P1_VREF_CTL_F8                     0xF8        // DAC Reference Voltage Control
#define _P1_MODULATOR_CTL_F9                0xF9        // DAC Modulator Control
//#define _P1_BIST_CTL_FA                     0xFA        // DAC Bist Control
//Address: P1-FB ~ P1-FF Reserved


/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page 2: TMDS/HDCP/HDMI/////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// TMDS Receiver (Page2)
//--------------------------------------------------
//#define _P2_RESERVED_A0                     0xA0        // P2 Reserved A0
#define _P2_TMDS_MEAS_SELECT_A1             0xA1        // TMDS Measure Select
#define _P2_TMDS_MEAS_RESULT0_A2            0xA2        // TMDS Measure Result0
#define _P2_TMDS_MEAS_RESULT1_A3            0xA3        // TMDS Measure Result1
#define _P2_TMDS_CTRL_A4                    0xA4        // TMDS Control Register
#define _P2_CRC_OUTPUT_BYTE_2_A5            0xA5        // CRC Output Byte2
#define _P2_TMDS_OUTPUT_CTRL_A6             0xA6        // TMDS Output Control Register
#define _P2_POWER_ON_OFF_CTRL_A7            0xA7        // TMDS Power On/Off Control Register
#define _P2_TMDS_ACC0_A8                    0xA8
#define _P2_DIGITAL_APR_A9                  0xA9

//Address: P2-A8 ~ P2-AB Reserved

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))

#define _P2_MAC_MEASURE_FREQ_AB             0xAB
#endif

#define _P2_Z0CC2_AC                        0xAC        // TMDS Z0 CC2
#define _P2_CPS_AD                          0xAD        // TMDS CPS

#define _P2_TMDS_RPS_AE                     0xAE        // TMDS RPS
//Address: P2-AF Reserved
//Address: P2-B0 ~ P2-B3 Reserved
#define _P2_TMDS_DPC0_B4                    0xB4        // PP & CD Value of Deep Color Mode
#define _P2_UP_DOWN_CTRL0_B5                0xB5        // Up/Down Control Register 0
#define _P2_UP_DOWN_CTRL1_B6                0xB6        // Up/Down Control Register 1
#define _P2_UP_DOWN_CTRL2_B7                0xB7        // Up/Down Control Register 2
#define _P2_TMDS_DPC1_B8                    0xB8        // Phase Select of Deep Coloe Mode
//#define _P2_ADAPTIVE_EQUALIZER3_B9          0xB9        // Adaptive Equalizer continuous threshold (LPF2)
//#define _P2_ADAPTIVE_EQUALIZE4_BA           0xBA        // Adaptive Equalizer auto stop threshold

#if(_SCALER_TYPE == _RTD2472D)
//--------------------------------------------------
// HDCP1.1(Port) (Page2)
//--------------------------------------------------
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
//--------------------------------------------------
// HDCP1.3(Port) (Page2)
//--------------------------------------------------
#endif
#define _P2_HDCP_CTRL_C0                    0xC0        // HDCP Control Register
#define _P2_DEVICE_KEY_ACCESS_PORT_C1       0xC1        // Device Key Access Port
#define _P2_HDCP_PORT_CTRL_C2               0xC2        // HDCP Port Control Register
#define _P2_HDCP_ADDR_PORT_C3               0xC3        // HDCP Address Port
#define _P2_HDCP_DATA_PORT_C4               0xC4        // HDCP Data Port
//Address: P2-C5 ~ P2-C7 Reserved

//--------------------------------------------------
// HDMI(Port) (Page2)
//--------------------------------------------------
#define _P2_HDMI_APC_C8                     0xC8        //
#define _P2_HDMI_ADDR_PORT_C9               0xC9        // HDMI Address Port
#define _P2_HDMI_DATA_PORT_CA               0xCA        // HDMI Data Port
#define _P2_HDMI_SR_CB                      0xCB        // HDMI Status Register
#define _P2_HDMI_GPVS_CC                    0xCC        // HDMI Packet Variation Status Register
#define _P2_HDMI_PSAP_CD                    0xCD        // HDMI Address For Packet Storage SRAM
#define _P2_HDMI_DSDP_CE                    0xCE        // HDMI Data For Packet Storage SRAM
//Address: P2-CF ~ P2-FF Reserved


#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page 3: LiveShow Control///////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// LiveShow Control (Page3)
//--------------------------------------------------
#define _P3_LS_CTRL0_A1                     0xA1        // Live Show Control Register0
#define _P3_LS_CTRL1_A2                     0xA2        // Live Show Control Register1
//Address: P3-A3 Reserved
#define _P3_LS_CPRS_CTRL_A4                 0xA4        // Live Show Compression Type Control Register
#define _P3_LS_TG_SIZE_H_A5                 0xA5        // Live Show Target Size For Compression HByte
#define _P3_LS_TG_SIZE_L_A6                 0xA6        // Live Show Target Size For Compression LByte
#define _P3_LS_GRP_NUM_H_A7                 0xA7        // Live Show Number Of Pixel Per Group To Be Analyzed And Compressed HByte
#define _P3_LS_GRP_NUM_L_A8                 0xA8        // Live Show Number Of Pixel Per Group To Be Analyzed And Compressed LByte
#define _P3_LS_FAIL_CNT_H_A9                0xA9        // Live Show The Count Of Compression Fail HByte
#define _P3_LS_FAIL_CNT_L_AA                0xAA        // Live Show The Count Of Compression Fail LByte
//Address: P3-AB~P3-AD Reserved
#define _P3_LS_LUT_ROW_ADDR_AE              0xAE        // Live Show LUT Row Address
#define _P3_LS_LUT_COL_ADDR_AF              0xAF        // Live Show LUT Colunm Address
#define _P3_LS_LUT_DATA_B0                  0xB0        // Live Show LUT Data Port
#define _P3_LS_DELTA_GAIN_B1                0xB1        // Live Show Delta Gain Setting
#define _P3_LS_UDST_THD_B2                  0xB2        // Live Show Undershoot Threshold(2's Complement)
#define _P3_LS_OVST_THD_B3                  0xB3        // Live Show Overshoot Threshold
#define _P3_LS_UDST_GAIN_B4                 0xB4        // Live Show Undershoot Gain
#define _P3_LS_OVST_GAIN_B5                 0xB5        // Live Show Overshoot Gain
#define _P3_LS_STATUS0_B6                   0xB6        // Live Show Status Register0 (Buffer Status)
#define _P3_LS_STATUS1_B7                   0xB7        // Live Show Status Register1 (FIFO Status)
//Address: P3-B8~P3-BF Reserved
#define _P3_LS_WTLVL_W_C0                   0xC0        // Live Show Water Level Write Register
#define _P3_LS_WTLVL_R_C1                   0xC1        // Live Show Water Level Read Register
#define _P3_LS_MEM_FIFO_RW_NUM_H_C2         0xC2        // The Read/Write Times Of Total Memory Access HByte
#define _P3_LS_MEM_FIFO_RW_NUM_L_C3         0xC3        // The Read/Write Times Of Total Memory Access LByte
#define _P3_LS_MEM_FIFO_RW_LEN_C4           0xC4        // The Read/Write Number Of Words In Each Memory Access
#define _P3_LS_MEM_FIFO_RW_REMAIN_C5        0xC5        // The Read/Write Number Of Words At The Last Access. This Register Must Be 4X
#define _P3_LS_MEM_START_ADDR_H_C6          0xC6        // Start Address Of Live Show Memory Block HByte(Total 22/23 bits)
#define _P3_LS_MEM_START_ADDR_M_C7          0xC7        // Start Address Of Live Show Memory Block MByte(Total 22/23 bits)
#define _P3_LS_MEM_START_ADDR_L_C8          0xC8        // Start Address Of Live Show Memory Block LByte(Total 22/23 bits)
#define _P3_LS_BIST_CTRL_C9                 0xC9        // Live Show BIST Control Register
#define _P3_LS_COMP_CHK_CA                  0xCA        // Live Show Decompression Previous Buffer Status Check
#define _P3_LS_COMP_REOVFW_CB               0xCB        // Reorder Buffer Overflow By Group Dummy Purge LSB
#define _P3_LS_FRAME0_CC                    0xCC        // Live Show Current Frame Control Register0
#define _P3_LS_FRAME1_CD                    0xCD        // Live Show Current Frame Control Register1
#define _P3_LS_FRAME2_CE                    0xCE        // Live Show Current Frame Control Register2
//Address: P3-CF~P3-FF Reserved


/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page 4: SDRAM Control//////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//#define _P4_RESERVED_A0                     0xA0        // P4 Reserved A0
#define _P4_SDR_CTRL0_A1                    0xA1        // SDRAM Control Register0
#define _P4_SDR_CTRL1_A2                    0xA2        // SDRAM Control Register1
#define _P4_SDR_AREF_TIME_A3                0xA3        // SDRAM Auto Refresh Time
#define _P4_SDR_PRCG_A4                     0xA4        // SDRAM Precharge Control Register
#define _P4_SDR_MEM_TYPE_A5                 0xA5        // SDRAM Memory Size Select
#define _P4_SDR_SLEW_RATE_A6                0xA6        // SDRAM Slew Rate Control Register
#define _P4_SDR_AREF_CNT_A7                 0xA7        // Number Of Auto Refresh
//Address: P4-A8~P4-A9 Reserved
#define _P4_SDR_RSC_AREF_AA                 0xAA        // SDRAM Arbiter Token Ring For Auto Refresh
#define _P4_SDR_RSC_MCU_AB                  0xAB        // SDRAM Arbiter Token Ring For MCU
#define _P4_SDR_RSC_CAP1_AC                 0xAC        // SDRAM Arbiter Token Ring For CAP1
//Address: P4-AD Reserved
#define _P4_SDR_RSC_MAIN_AE                 0xAE        // SDRAM Arbiter Token Ring For Main
//Address: P4-AF Reserved
#define _P4_SDR_RSC_RD_B0                   0xB0        // SDRAM Arbiter Token Ring For RD
#define _P4_SDR_RSC_WR_B1                   0xB1        // SDRAM Arbiter Token Ring For WR
//Address: P4-B2~P4-B3 Reserved
#define _P4_SDR_ABTR_STATUS0_B4             0xB4        // SDRAM Arbiter Status Register0
#define _P4_SDR_ABTR_STATUS1_B5             0xB5        // SDRAM Arbiter Status Register1
//Address: P4-B6~P4-B7 Reserved
#define _P4_SDR_ADDR_H_B8                   0xB8        // SDRAM Access Address HByte
#define _P4_SDR_ADDR_M_B9                   0xB9        // SDRAM Access Address MByte
#define _P4_SDR_ADDR_L_BA                   0xBA        // SDRAM Access Address LByte
#define _P4_SDR_ACCESS_CMD_BB               0xBB        // SDRAM Access Command
#define _P4_SDR_DATA_BUF_BC                 0xBC        // SDRAM Data Buffer
#define _P4_SDR_MCU_RD_LEN_BD               0xBD        // SDRAM MCU Read SdRAM Lengh
#define _P4_SDR_PHASE_CAL_BE                0xBE        // SDRAM Phase Calibration
#define _P4_SDR_CAL_RESULT_BF               0xBF        // SDRAM Calibration Result
#define _P4_SDR_CLK_DLY1_C0                 0xC0        // SDRAM Mclk Output
#define _P4_SDR_CLK_DLY2_C1                 0xC1        // SDRAM Mclk Delay Fine Tune
#define _P4_DQS0_DLY1_C2                    0xC2        // SDRAM DQS0 Coarse Delay
#define _P4_DQS0_DLY2_C3                    0xC3        // SDRAM DQS0 Data Fine Delay
#define _P4_DQS1_DLY1_C4                    0xC4        // SDRAM DQS1 Coarse Delay
#define _P4_DQS1_DLY2_C5                    0xC5        // SDRAM DQS1 Data Fine Delay
#define _P4_DQS2_DLY1_C6                    0xC6        // SDRAM DQS2 Coarse Delay
#define _P4_DQS2_DLY2_C7                    0xC7        // SDRAM DQS2 Data Fine Delay
#define _P4_DQS3_DLY1_C8                    0xC8        // SDRAM DQS3 Coarse Delay
#define _P4_DQS3_DLY2_C9                    0xC9        // SDRAM DQS3 Data Fine Delay
#define _P4_SEC_DQS0_DLY_CA                 0xCA        // SDRAM DQS0 Second Data Fine Delay
#define _P4_SEC_DQS1_DLY_CB                 0xCB        // SDRAM DQS1 Second Data Fine Delay
#define _P4_SEC_DQS2_DLY_CC                 0xCC        // SDRAM DQS2 Second Data Fine Delay
#define _P4_SEC_DQS3_DLY_CD                 0xCD        // SDRAM DQS3 Second Data Fine Delay
//Address: P4-CE~P4-FB Reserved
#define _P4_EXTENDED_MODE_H_FC              0xFC        // SDRAM Extended Mode Register HByte
#define _P4_EXTENDED_MODE_L_FD              0xFD        // SDRAM Extended Mode Register LByte
#define _P4_RANDOM_GENERATOR_FE             0xFE        // SDRAM Random Generator
#define _P4_CRC_DATA_PORT_FF                0xFF        // SDRAM CRC Data Port


/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page 5: SDR_FIFO Control///////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//#define _P5_RESERVED_A0                     0xA0        // P5 Reserved A0
#define _P5_SDRF_IN1_FIFO_STATUS_A1         0xA1        // SDRAM IN1 FIFO Status Register
#define _P5_SDRF_MAIN_FIFO_STATUS_A2        0xA2        // SDRAM MAIN FIFO Status Register
#define _P5_SDRF_IN1_SFIFO_STATUS_A3        0xA3        // SDRAM IN1 SFIFO Status Register
//Address: P5-A4~P5-A7 Reserved
#define _P5_SDRF_IN1_WATER_LEVEL_A8         0xA8        // SDRAM FIFO IN1 Water Level Register
#define _P5_SDRF_IN1_WR_NUM_H_A9            0xA9        // Number Of Length To Fill In The SDR Memory HByte
#define _P5_SDRF_IN1_WR_NUM_L_AA            0xAA        // Number Of Length To Fill In The SDR Memory LByte
#define _P5_SDRF_IN1_WR_LEN_AB              0xAB        // Length Of Data To Fill In The SDR Memory Once (unit : 64 bit)
#define _P5_SDRF_IN1_WR_REMAIN_AC           0xAC        // The Remained Part That Can't Make A Complete Length (unit : 64 bit)
#define _P5_SDRF_IN1_MEM_ADDR_H_AD          0xAD        // The Initial Write Address Of SDR Memory HByte
#define _P5_SDRF_IN1_MEM_ADDR_M_AE          0xAE        // The Initial Write Address Of SDR Memory MByte
#define _P5_SDRF_IN1_MEM_ADDR_L_AF          0xAF        // The Initial Write Address Of SDR Memory LByte
#define _P5_SDRF_IN1_LINE_STEP_H_B0         0xB0        // The Distance Between Two Lines Of SDR Memory HByte
#define _P5_SDRF_IN1_LINE_STEP_L_B1         0xB1        // The Distance Between Two Lines Of SDR Memory LByte
#define _P5_SDRF_IN1_BLOCK_STEP_H_B2        0xB2        // The Distance Between Two Blocks Of SDR Memory HByte
#define _P5_SDRF_IN1_BLOCK_STEP_L_B3        0xB3        // The Distance Between Two Blocks Of SDR Memory LByte
#define _P5_SDRF_IN1_BL2_ADDR_H_B4          0xB4        // Second Block Of SDR To Progress The Double Buffer. The Given Address Is The Absolute One HByte
#define _P5_SDRF_IN1_BL2_ADDR_M_B5          0xB5        // Second Block Of SDR To Progress The Double Buffer. The Given Address Is The Absolute One MByte
#define _P5_SDRF_IN1_BL2_ADDR_L_B6          0xB6        // Second Block Of SDR To Progress The Double Buffer. The Given Address Is The Absolute One LByte
#define _P5_SDRF_IN1_LINE_NUM_H_B7          0xB7        // The Total Line Number Of One Image HByte (Total 12 bits)
#define _P5_SDRF_IN1_LINE_NUM_L_B8          0xB8        // The Total Line Number Of One Image LByte (Total 12 bits)
#define _P5_SDRF_IN1_SDR_CTRL_B9            0xB9        // SDRAM IN1 FIFO Control Register
//Address: P5-BA Reserved
#define _P5_SDRF_IN1_SDR_STATUS_BB          0xBB        // SDRAM IN1 Status Register
#define _P5_SDRF_MN_PRERD_VST_H_BC          0xBC        // Vertical Start Line Of MAIN To Pre-Read Input Data HByte (Total 11-bits)
#define _P5_SDRF_MN_PRERD_VST_L_BD          0xBD        // Vertical Start Line Of MAIN To Pre-Read Input Data LByte (Total 11-bits)
#define _P5_SDRF_MN_PXL_NUM_H_BE            0xBE        // Pixel Number Of One Line, For FIFO To Clear Garbage From Capture Side HByte (Total 11-bits)
#define _P5_SDRF_MN_PXL_NUM_L_BF            0xBF        // Pixel Number Of One Line, For FIFO To Clear Garbage From Capture Side LByte (Total 11-bits)
#define _P5_SDRF_MN_WTLVL_C0                0xC0        // When FIFO Depth Is Under Water Level, FIFO Requests Data
//Address: P5-C1 Reserved
#define _P5_SDRF_MN_READ_NUM_H_C2           0xC2        // Number Of Length To Read From SDR In One Line HByte
#define _P5_SDRF_MN_READ_NUM_L_C3           0xC3        // Number Of Length To Read From SDR In One Line LByte
#define _P5_SDRF_MN_READ_LEN_C4             0xC4        // The Length Of Data To Read From SDR Once
#define _P5_SDRF_MN_READ_REMAIN_C5          0xC5        // The Remain Part That Can't Be A Complete Length In One Line
#define _P5_SDRF_MN_READ_ADDR_H_C6          0xC6        // The Initial Read Address Of SDR HByte (Total 23-bits)
#define _P5_SDRF_MN_READ_ADDR_M_C7          0xC7        // The Initial Read Address Of SDR MByte (Total 23-bits)
#define _P5_SDRF_MN_READ_ADDR_L_C8          0xC8        // The Initial Read Address Of SDR LByte (Total 23-bits)
#define _P5_SDRF_MN_LINE_STEP_H_C9          0xC9        // Line Step Indicates The Distance Between Two Lines HByte (Total 12 bits)
#define _P5_SDRF_MN_LINE_STEP_L_CA          0xCA        // Line Step Indicates The Distance Between Two Lines LByte (Total 12 bits)
#define _P5_SDRF_MN_BLOCK_STEP_H_CB         0xCB        // The Distance Between Two Blocks Of SDR HByte (Total 12-bits)
#define _P5_SDRF_MN_BLOCK_STEP_L_CC         0xCC        // The Distance Between Two Blocks Of SDR LByte (Total 12-bits)
#define _P5_SDRF_MN_LINE_NUM_H_CD           0xCD        // The Total Line Number Of One Image HByte (Total 12 bits)
#define _P5_SDRF_MN_LINE_NUM_L_CE           0xCE        // The Total Line Number Of One Image LByte (Total 12 bits)
#define _P5_SDRF_MN_DISP_CTRL_CF            0xCF        // SDRAM FIFO MAIN Display Control Register
#define _P5_SDRF_MN_SDR_STATUS_D0           0xD0        // SDRAM Status Register
//Address: P5-D1~P5-D5 Reserved
#define _P5_SDRF_ADC_TEST_D6                0xD6        // For ADC Test Usage
//Address: P5-D7~P5-E2 Reserved
#define _P5_SDRF_MN_FIFO_422_SET_E3         0xE3        // Output 444 Format(Only Work in FIFO 422 In Mode)
//Address: P5-E4~P5-FF Reserved


/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////   Page 6: Reserved   ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

#elif(_SCALER_TYPE == _RTD2472D)
/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////   Page 3: Reserved   ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//Reserved Page (Page 3)


/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////   Page 4: Reserved   ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//Reserved Page (Page 4)


/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////   Page 5: Reserved   ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//Reserved Page (Page 5)


/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page 6: Auto SOY///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// Auto SOY (Page6)
//--------------------------------------------------
#define _P6_SOY_CH0_CFG0_C0                 0xC0        // Auto Soy Channel 0 Control Register 0
#define _P6_SOY_CH0_CFG1_C1                 0xC1        // Auto Soy Channel 0 Control Register 1
#define _P6_SOY_CH0_CFG2_C2                 0xC2        // Auto Soy Channel 0 Control Register 2
#define _P6_SOY_CH0_CFG3_C3                 0xC3        // Auto Soy Channel 0 Control Register 3
#define _P6_SOY_CH0_CFG4_C4                 0xC4        // Auto Soy Channel 0 Control Register 4
#define _P6_SOY_CH0_CFG5_C5                 0xC5        // Auto Soy Channel 0 Control Register 5
#define _P6_SOY_CH0_CFG6_C6                 0xC6        // Auto Soy Channel 0 Control Register 6
#define _P6_SOY_CH0_CFG7_C7                 0xC7        // Auto Soy Channel 0 Control Register 7
#define _P6_SOY_CH0_CFG8_C8                 0xC8        // Auto Soy Channel 0 Control Register 8
#define _P6_SOY_CH0_CFG9_C9                 0xC9        // Auto Soy Channel 0 Control Register 9
#define _P6_SOY_CH0_CFGA_CA                 0xCA        // Auto Soy Channel 0 Control Register A
#define _P6_SOY_CH0_CFGB_CB                 0xCB        // Auto Soy Channel 0 Control Register B
#define _P6_SOY_CH0_CFGC_CC                 0xCC        // Auto Soy Channel 0 Control Register C
//#define _P6_RESERVED_CD                     0xCD        // PB Reserved CD
//#define _P6_RESERVED_CE                     0xCE        // PB Reserved CE
//#define _P6_RESERVED_CF                     0xCF        // PB Reserved CF

#define _P6_SOY_CH1_CFG0_D0                 0xD0        // Auto Soy Channel 1 Control Register 0
#define _P6_SOY_CH1_CFG1_D1                 0xD1        // Auto Soy Channel 1 Control Register 1
#define _P6_SOY_CH1_CFG2_D2                 0xD2        // Auto Soy Channel 1 Control Register 2
#define _P6_SOY_CH1_CFG3_D3                 0xD3        // Auto Soy Channel 1 Control Register 3
#define _P6_SOY_CH1_CFG4_D4                 0xD4        // Auto Soy Channel 1 Control Register 4
#define _P6_SOY_CH1_CFG5_D5                 0xD5        // Auto Soy Channel 1 Control Register 5
#define _P6_SOY_CH1_CFG6_D6                 0xD6        // Auto Soy Channel 1 Control Register 6
#define _P6_SOY_CH1_CFG7_D7                 0xD7        // Auto Soy Channel 1 Control Register 7
#define _P6_SOY_CH1_CFG8_D8                 0xD8        // Auto Soy Channel 1 Control Register 8
#define _P6_SOY_CH1_CFG9_D9                 0xD9        // Auto Soy Channel 1 Control Register 9
#define _P6_SOY_CH1_CFGA_DA                 0xDA        // Auto Soy Channel 1 Control Register A
#define _P6_SOY_CH1_CFGB_DB                 0xDB        // Auto Soy Channel 1 Control Register B
#define _P6_SOY_CH1_CFGC_DC                 0xDC        // Auto Soy Channel 1 Control Register C
//#define _P6_RESERVED_CD                     0xDD        // PB Reserved DD
//#define _P6_RESERVED_CE                     0xDE        // PB Reserved DE
//#define _P6_RESERVED_CF                     0xDF        // PB Reserved DF

#define _P6_SOY_CH0_CALI_CFG0_E0            0xE0        // Auto Soy Channel 0 Calibration Control Register 0
#define _P6_SOY_CH0_CALI_CFG1_E1            0xE1        // Auto Soy Channel 0 Calibration Control Register 0
#define _P6_SOY_CH0_CALI_CFG2_E2            0xE2        // Auto Soy Channel 0 Calibration Control Register 0
//#define _P6_RESERVED_E3                     0xE3        // PB Reserved E3
#define _P6_SOY_CH0_CALI_ADDR_PORT_E4       0xE4        // Auto Soy Channel 0 Calibration Address Port
#define _P6_SOY_CH0_CALI_DATA_PORT_E5       0xE5        // Auto Soy Channel 0 Calibration Data Port
//Address: P6-E6 ~ P6-EF Reserved

#define _P6_SOY_CH1_CALI_CFG0_F0            0xF0        // Auto Soy Channel 1 Calibration Control Register 0
#define _P6_SOY_CH1_CALI_CFG1_F1            0xF1        // Auto Soy Channel 1 Calibration Control Register 0
#define _P6_SOY_CH1_CALI_CFG2_F2            0xF2        // Auto Soy Channel 1 Calibration Control Register 0
//#define _P6_RESERVED_F3                     0xF3        // PB Reserved F3
#define _P6_SOY_CH1_CALI_ADDR_PORT_F4       0xF4        // Auto Soy Channel 1 Calibration Address Port
#define _P6_SOY_CH1_CALI_DATA_PORT_F5       0xF5        // Auto Soy Channel 1 Calibration Data Port
//Address: P6-F6 ~ P6-FF Reserved
#endif // End of #if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))


/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page 7: Vivid Color////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//Address: P7-A0 ~ P7-BE Reserved

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
//--------------------------------------------------
// Vivid Color - YUV2RGB (Page7)
//--------------------------------------------------
#define _P7_YUV2RGB_CTRL_BF                 0xBF        // YUV2RGB Control
#define _P7_YUV2RGB_ACCESS_C0               0xC0        // YUV2RGB Coefficient Access Port
#define _P7_YUV2RGB_COEF_DATA_C1            0xC1        // YUV2RGB Coefficient Data Port
//Address: P7-C2 ~ P7-C6 Reserved
#endif // End of #if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

//--------------------------------------------------
// Vivid Color - DCC (Page7)
//--------------------------------------------------
#define _P7_DCC_CTRL0_C7                    0xC7        // DCC Control Register 0
#define _P7_DCC_CTRL1_C8                    0xC8        // DCC Control Register 1
#define _P7_DCC_ACCESS_PORT_C9              0xC9        // DCC Access Port
#define _P7_DCC_DATA_PORT_CA                0xCA        // DCC Data Port
//Address: P7-CB ~ P7-CF Reserved

//--------------------------------------------------
// Vivid Color - ICM (Page7)
//--------------------------------------------------
#define _P7_ICM_CTRL_D0                     0xD0        // ICM Control Register
#define _P7_ICM_SEL_D1                      0xD1        // ICM Accessing Through Data Port Select
#define _P7_ICM_ACCESS_PORT_D2              0xD2        // ICM Access Port
#define _P7_ICM_DATA_PORT_D3                0xD3        // ICM Data Port
//Address: P7-D4 ~ P7-D5 Reserved
#define _P7_PKING_ACCESS_PORT_D6            0xD6        // Y Peaking Coring Access Port
#define _P7_PKING_DATA_PORT_D7              0xD7        // Y Peaking Coring Data Port
#define _P7_DCR_ACCESS_PORT_D8              0xD8        // DCR Access Port
#define _P7_DCR_DATA_PORT_D9                0xD9        // DCR Data Port
//Address: P7-DA ~ P7-EF Reserved

//--------------------------------------------------
// Vivid Color - Pattern Gen. in D Domain (Page7)
//--------------------------------------------------
#define _P7_DISP_PG_R_CTRL_F0               0xF0        // Display Pattern Gen. R Control
#define _P7_DISP_PG_G_CTRL_F1               0xF1        // Display Pattern Gen. G Control
#define _P7_DISP_PG_B_CTRL_F2               0xF2        // Display Pattern Gen. B Control
#define _P7_DISP_PG_R_INITIAL_F3            0xF3        // Display Pattern Gen. R Initial Value
#define _P7_DISP_PG_G_INITIAL_F4            0xF4        // Display Pattern Gen. G Initial Value
#define _P7_DISP_PG_B_INITIAL_F5            0xF5        // Display Pattern Gen. B Initial Value
#define _P7_DISP_PG_PIXEL_DELTA_F6          0xF6        // Pixel Delta Value for Incremental
#define _P7_DISP_PG_LINE_DELTA_F7           0xF7        // Line Delta Value for Incremental
#define _P7_DISP_PG_PIXEL_STEP_MSB_F8       0xF8        // Pixel Step for Toggle/Incremental(MSB)
#define _P7_DISP_PG_LINE_STEP_MSB_F9        0xF9        // Line Step for Toggle/Incremental(MSB)
#define _P7_DISP_PG_STEP_LSB_FA             0xFA        // Pixel/Line Step for Toggle/Incremental(LSB)
//Address: P7-FB ~ P7-FF Reserved


/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////   Page 8: Reserved   ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//Reserved Page (Page 8)


/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////   Page 9: Reserved   ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//Reserved Page (Page 9)


/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////   Page A: Reserved   ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//Reserved Page (Page A)


/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page B: Display Port///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#define _PB_DP_CDR_00_A0                    0xA0        // VCO Band Selection
#define _PB_DP_CDR_01_A1                    0xA1        // VCO Divider
#define _PB_DP_CDR_02_A2                    0xA2        // CDR CP Current Selection
#define _PB_DP_CDR_03_A3                    0xA3        // Bias Current Selection
#define _PB_DP_FLD_00_A4                    0xA4        // DP Rate Count Code
#define _PB_DP_FLD_01_A5                    0xA5        // VDD50 Test
#define _PB_DP_FLD_02_A6                    0xA6        // Offset Test/FLD CP Test
#define _PB_DP_FLD_03_A7                    0xA7        // DVCO Divider
#define _PB_DP_FLD_04_A8                    0xA8        // CDR Data Ready
#define _PB_DP_FLD_05_A9                    0xA9        // VCO Divider MOD Decision Code0
#define _PB_DP_FLD_06_AA                    0xAA        // VCO Divider MOD Decision Code1
#define _PB_DP_FLD_07_AB                    0xAB        // VCO Divider MOD Decision Code2
#define _PB_DP_FLD_08_AC                    0xAC        // Reserved
#define _PB_DP_FLD_09_AD                    0xAD        // Adaptive Equalizer
#define _PB_DP_RXMISC_01_AE                 0xAE        // CDR CP Vref
#define _PB_DP_RXMISC_02_AF                 0xAF        // Calibration Time

#define _PB_DP_OOBS_RXAMP_B0                0xB0        // OOBS Clock Source Selection
#define _PB_DP_OOBS_SGN_DET_B1              0xB1        // OOBS Signal Detect Amplitude Selection
#define _PB_DP_ADP_EQ_B2                    0xB2        // Adaptive Equalizer Setting
#define _PB_DP_AUX_00_B3                    0xB3        // OOBS Manual
#define _PB_DP_PWR_CTL_B4                   0xB4        // Power Control For Rx Channel and PLL
#define _PB_DP_2D_SWITCH_B5                 0xB5        // DP and  HDMI Switch
#define _PB_DP_Z0_CALIBRATION_B6            0xB6        // Z0 Calibration Register
#define _PB_DP_CEC_B7                       0xB7        // CEC Control Register
#define _PB_DP_AUX_01_B8                    0xB8        // CEC Driver Slew Rate Control
#define _PB_DP_AUX_02_B9                    0xB9        // Aux Attachment Detection
#define _PB_DP_RESERVED_00_BA               0xBA        // Offset Adjustment
#define _PB_DP_RESERVED_01_BB               0xBB        // BG Enable
#define _PB_DP_RESERVED_02_BC               0xBC        // AUX/CEC Test Enable
#define _PB_DP_RESERVED_03_BD               0xBD        // AUX Debug Signal
#define _PB_DP_RESERVED_04_BE               0xBE        // CEC Debug Signal
#define _PB_DP_RESERVED_05_BF               0xBF        // Enable Equalizer Boost2

#define _PB_CMU_00_C0                       0xC0        // PLL1 Loop Filter R/C1/C2
#define _PB_CMU_01_C1                       0xC1        // PLL1 Charge Pump Current Select
#define _PB_CMU_02_C2                       0xC2        // PLL2 Loop Filter R/C1/C2
#define _PB_CMU_03_C3                       0xC3        // PLL2 Charge Pump Current Select
#define _PB_CMU_04_C4                       0xC4        // Divide Number of Pre-Divider
#define _PB_CMU_05_C5                       0xC5        // Divide Number of PLL1
#define _PB_CMU_06_C6                       0xC6        // Divide Number of PLL1
#define _PB_CMU_07_C7                       0xC7        // Divide Number of PLL2
#define _PB_CMU_08_C8                       0xC8        // Divide Number of 3RD Divider
#define _PB_TX_C9                           0xC9        // Pre-Emphasis Control Register
#define _PB_SSCG_CA                         0xCA        // SSCG
#define _PB_TX_Z0_CALIBRATION_CB            0xCB        // TX Z0 Calibration
#define _PB_DP_RESERVED_06_CC               0xCC        // Sample Edge Selector Of Each Lane
#define _PB_DP_RESERVED_07_CD               0xCD        // Select the Data Mapping Between Physical Lane and MAC Lane
//#define _PB_DP_RESERVED_08_CE             0xCE        // Reserved
//#define _PB_DP_RESERVED_09_CF             0xCF        // Reserved

#define _PB_RX_BIST_00_D0                   0xD0        // Frequency Setting LSB
#define _PB_RX_BIST_01_D1                   0xD1        // Frequency Setting MSB
#define _PB_RX_BIST_02_D2                   0xD2        // Amplitude Setting
#define _PB_RX_BIST_03_D3                   0xD3        // Clock Phase Selection
#define _PB_RX_BIST_04_D4                   0xD4        // Reciprocal Bias Current Trim
#define _PB_RX_BIST_05_D5                   0xD5        // Analog I/O Select
#define _PB_TX_BIST_00_D6                   0xD6        // Time Stamp
#define _PB_TX_BIST_01_D7                   0xD7        // Data Vertical Value
#define _PB_TX_BIST_02_D8                   0xD8        // PLL Setting
#define _PB_TX_BIST_03_D9                   0xD9        // ADC Full Scale Adjust
#define _PB_TX_BIST_04_DA                   0xDA        // ADC Full Scale Adjust
#define _PB_TX_BIST_05_DB                   0xDB        // PLL Setting 1
#define _PB_TX_BIST_06_DC                   0xDC        // PLL Setting 2
#define _PB_TX_BIST_07_DD                   0xDD        // PLL Setting 3
//Address: PB-DE ~ PB-DF Reserved

#define _PB_DIG00_E0                        0xE0        // Select Primary Control Signal
#define _PB_DIG01_E1                        0xE1        // Inverse DP Clock
#define _PB_DIG02_E2                        0xE2        // Comma Number Selector
#define _PB_DIG03_E3                        0xE3        // Rx BIST Source Selection
#define _PB_DIG04_E4                        0xE4        // BIST Seed Pattern
#define _PB_DIG05_E5                        0xE5        // Rx Digital Debug
#define _PB_DIG06_E6                        0xE6        // Received Packet Number MSB
#define _PB_DIG07_E7                        0xE7        // Received Packet Number LSB
#define _PB_DIG08_E8                        0xE8        // Received Error Counter
#define _PB_SSCG_DIG_E9                     0xE9        // SSCG Control Register
#define _PB_DIG_TX_00_EA                    0xEA        // Tx BIST Mode Selector
#define _PB_DIG_TX_01_EB                    0xEB        // BIST Packet Length
#define _PB_DIG_TX_02_EC                    0xEC        // BIST Packet Number
#define _PB_DIG_TX_03_ED                    0xED        // Force Error Period
#define _PB_DP_RESERVED_0A_EF               0xEF        // GPI Pad Input Enable

//#define _PB_DP_RESERVED_0B_F              0xF0        // Reserved
//#define _PB_DP_RESERVED_0C_F1             0xF1        // Reserved
//#define _PB_DP_RESERVED_0D_F2             0xF2        // Reserved
//#define _PB_DP_RESERVED_0E_F3             0xF3        // Reserved
//#define _PB_DP_RESERVED_0F_F4             0xF4        // Reserved
//Address: PB-F5 ~ PB-FF Reserved


/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page C: Display Port///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------
// DisplayPort - MAC Control (PageC)
//--------------------------------------------------
//#define _PC_RESERVED_A0                     0xA0        // PC Reserved A0
#define _PC_DP_CTL_A1                       0xA1        // DP General Control
#define _PC_DP_OUTPUT_CTL_A2                0xA2        // DP General Output Control
#define _PC_DP_OUTPUT_CLK_CTL_A3            0xA3        // DP Output Clock Control
#define _PC_LANE_SWAP_A4                    0xA4        // DP Lane Swap
#define _PC_DP_LANE_VALID_A5                0xA5        // DP Lane Valid Control(write 1 clear)
#define _PC_DP_LANE_LOCK_A6                 0xA6        // DP Lane Lock Control (write 1 clear)
#define _PC_DP_LANE_CLK_INV_A7              0xA7        // DP Lane Clock Inverse Control
#define _PC_MIN_DE_SKEW_A8                  0xA8        // Minimize The De-Skew Between Lanes
#define _PC_MN_ERRC_A9                      0xA9        // Video/ Audio Error Correction
#define _PC_MN_ERRC_CTL_AA                  0xAA        // Video/ Audio Error Correction Control
#define _PC_DP_CRC_AB                       0xAB        // CRC Control Register
#define _PC_DP_CRC_R_H_AC                   0xAC        // CRC Result High Byte for R channel
#define _PC_DP_CRC_R_L_AD                   0xAD        // CRC Result Low Byte for R channel
#define _PC_DP_CRC_G_H_AE                   0xAE        // CRC Result High Byte for G channel
#define _PC_DP_CRC_G_L_AF                   0xAF        // CRC Result Low Byte for G channel

#define _PC_DP_CRC_B_H_B0                   0xB0        // CRC Result High Byte for B channel
#define _PC_DP_CRC_B_L_B1                   0xB1        // CRC Result Low Byte for B channel
#define _PC_DP_MEM_BIST_B2                  0xB2        // Memory Bist Control Register
#define _PC_DP_ACCESS_PORT_B3               0xB3        // DP Access Port
#define _PC_DP_DATA_PORT_B4                 0xB4        // DP Data Port
#define _PC_DP_DEBUG_SEL0_B5                0xB5        // Debug Output Selector
#define _PC_DP_DEBUG_SEL1_B6                0xB6        // AUX-CH/Display Format Debug Output Selector
#define _PC_DP_DEBUG_SEL2_B7                0xB7        // SCK Gen./Channel Recovery Debug Output Selector
#define _PC_DP_INFO_FM_ADR_B8               0xB8        // Info-Frame Memory Address Port
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _PC_DP_INFO_FM_DAT_B9               0xB9        // Info-Frame Memory Data Port
#endif

#define _PC_DP_RESERVE0_BA                  0xBA        // DP Reserve 0
#define _PC_DP_RESERVE1_BB                  0xBB        // DP Reserve 1
#define _PC_DP_RESERVE2_BC                  0xBC        // DP Reserve 2
#define _PC_DP_RESERVE3_BD                  0xBD        // DP Reserve 3
#define _PC_DP_RESERVE4_BE                  0xBE        // DP Reserve 4
#define _PC_DP_RESERVE5_BF                  0xBF        // DP Reserve 5
#define _PC_DPCD_CTL_C0                     0xC0        // DPCD Control Register
#define _PC_DPCD_ACCESS_PORT_H_C1           0xC1        // DPCD Access Port High Byte
#define _PC_DPCD_ACCESS_PORT_M_C2           0xC2        // DPCD Access Port Middle Byte
#define _PC_DPCD_ACCESS_PORT_L_C3           0xC3        // DPCD Access Port Low Byte
#define _PC_DPCD_DATA_PORT_L_C4             0xC4        // DPCD Data Port Low Byte
#define _PC_AUX_RESERVE0_C5                 0xC5        // DP AUX Reserve 0
#define _PC_AUX_RESERVE1_C6                 0xC6        // DP AUX Reserve 1
#define _PC_AUX_RESERVE2_C7                 0xC7        // DP AUX Reserve 2
#define _PC_AUX_RESERVE3_C8                 0xC8        // DP AUX Reserve 3
#define _PC_AUX_RESERVE4_C9                 0xC9        // DP AUX Reserve 4
#define _PC_READ_RESERVE0_CA                0xCA        // DP Read Reserve 0
#define _PC_READ_RESERVE1_CB                0xCB        // DP Read Reserve 1
#define _PC_READ_RESERVE2_CC                0xCC        // DP Read Reserve 2

//Address: PC-C5 ~ PC-CF Reserved

#define _PC_AUX_MODE_SET_D0                 0xD0        // AUX Channel Control Register
#define _PC_AUX_IIC_SET_D1                  0xD1        // IIC Setting for AUX Channel
#define _PC_AUX_RX_CMD_D2                   0xD2        // RX Command for AUX Channel and Reveived Address High Byte
#define _PC_AUX_RX_ADDR_M_D3                0xD3        // RX AUX Channel Reveived Address Middle Byte
#define _PC_AUX_RX_ADDR_L_D4                0xD4        // RX AUX Channel Reveived Address Low Byte
#define _PC_AUX_RX_LEN_D5                   0xD5        // RX AUX Channel Reveived Length
#define _PC_AUX_RX_DATA_D6                  0xD6        // RX AUX Channel Reveived Data Port
#define _PC_AUX_TX_CMD_D7                   0xD7        // TX Command for AUX Channel
#define _PC_AUX_TX_LEN_D8                   0xD8        // TX AUX Channel Reveived Length
#define _PC_AUX_TX_DATA_D9                  0xD9        // TX AUX Channel Reveived Data Port
#define _PC_AUX_FIFO_RST_DA                 0xDA         // FIFO ResetRegister
#define _PC_AUX_STATUS_DB                   0xDB         // AUX Channel Status Register
#define _PC_AUX_IRQ_STATUS_DC               0xDC         // AUX Channel IRQ Status Register
#define _PC_AUX_IRQ_STATUS_EN_DD            0xDD         // AUX Channel IRQ Status Enable Register
#define _PC_DPCD_REG_GROUP_DE               0xDE         // DPCD Register Group
//Address: PC-DF Reserved

//--------------------------------------------------
// DisplayPort - HDCP1.3(PageC)
//--------------------------------------------------
#define _PC_DP_HDCP_CONTROL_E0                  0xE0        // HDCP Control Register
#define _PC_DP_HDCP_KEY_DOWNLOAD_PORT_E1    0xE1        // HDCP Key Download Port
#define _PC_DP_HDCP_KEY_OUTPUT_E2           0xE2        // HDCP Key Output
#define _PC_DP_HDCP_IRQ_E3                  0xE3        // HDCP IRQ Control
#define _PC_DP_HDCP_INTGT_VRF_E4            0xE4        // HDCP Link Integrity
#define _PC_DP_HDCP_INTGT_VRF_PAT_MSB_E5    0xE5        // Setting of Integrity Pattern(MSB)
#define _PC_DP_HDCP_INTGT_VRF_PAT_LSB_E6    0xE6        // Setting of Integrity Pattern(LSB)
#define _PC_DP_HDCP_INTGT_VRF_ANS_MSB_E7    0xE7        // Real Calculation Result of Integrity Pattern(MSB)
#define _PC_DP_HDCP_INTGT_VRF_ANS_LSB_E8    0xE8        // Real Calculation Result of Integrity Pattern(LSB)
#define _PC_DP_HDCP_BIST_E9                 0xE9        // HDCP BIST Control
#define _PC_DP_HDCP_DEBUG_EAS_EA            0xEA        // HDCP Debug Mode Control
#define _PC_DP_RI_BYTE_MSB_EB               0xEB        // Ri MSB
#define _PC_DP_RI_BYTE_LSB_EC               0xEC        // Ri LSB
#define _PC_DP_KM_BYTE_6_ED                 0xED        // Km[55:48] Value
#define _PC_DP_KM_BYTE_5_EE                 0xED        // Km[47:40] Value
#define _PC_DP_KM_BYTE_4_EF                 0xED        // Km[39:32] Value

#define _PC_DP_KM_BYTE_3_F0                 0xF0        // Km[31:24] Value
#define _PC_DP_KM_BYTE_2_F1                 0xF1        // Km[23:16] Value
#define _PC_DP_KM_BYTE_1_F2                 0xF2        // Km[15:8] Value
#define _PC_DP_KM_BYTE_0_F3                 0xF3        // Km[7:0] Value
//Address: PC-F4 ~ PC-FF Reserved

/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page D: Register1//////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#if(_SCALER_TYPE == _RTD2545LR)
//--------------------------------------------------
// Interrupt Control(Page D)
//--------------------------------------------------
#define _PD_IRQ_STATUS_A0                   0xA0        // IRQ Status
//Address: PD-A1 ~ PD-B8 Reserved

//--------------------------------------------------
// DDC(Page D)
//--------------------------------------------------
#define _PD_ADC_SEGMENT_ADDRESS_B9          0xB9        // ADC DDC Slave Address for Segment Control
#define _PD_ADC_SEGMENT_DATA_BA             0xBA        // Data Access for Slave ID
#define _PD_ADC_DCC_ENABLE_BB               0xBB        // ADC DDC Channel Control
#define _PD_ADC_DCC_CONTROL_1_BC            0xBC        // ADC DDC Control Register 1
#define _PD_ADC_DCC_CONTROL_2_BD            0xBC        // ADC DDC Control Register 2
#define _PD_DVI_DCC_ENABLE_BE               0xBE        // DVI DDC Channel Control
#define _PD_DVI_DCC_CONTROL_1_BF            0xBF        // DVI DDC Control Register 1

#define _PD_DVI_DCC_CONTROL_2_C0            0xC0        // DVI DDC Control Register 2
#define _PD_DDCRAM_PARTITION_C1             0xC1        // DDC RAM Partition
#define _PD_VSYNC_SEL_C2                    0xC2        // VSYNC Signal Selection


//--------------------------------------------------
// DDC-CI(Page D)
//--------------------------------------------------
#define _PD_IIC_SET_SLAVE_C3                0xC3        // IIC Slave Address to Decode
#define _PD_IIC_SUB_IN_C4                   0xC4        // IIC Sub-Address Received
#define _PD_IIC_DATA_IN_C5                  0xC5        // IIC Data Recieved
#define _PD_IIC_DATA_OUT_C6                 0xC6        // IIC Data to be Transmitted
#define _PD_IIC_STATUS_C7                   0xC7        // IIC Status Register 1
#define _PD_IIC_IRQ_CONTROL_C8              0xC8        // IIC IRQ Control Register 1
#define _PD_IIC_STATUS2_C9                  0xC9        // IIC Status Register 2
#define _PD_IIC_IRQ_CONTROL2_CA             0xCA        // IIC IRQ Control Register 2
#define _PD_IIC_CHANNEL_CONTROL_CB          0xCB        // IIC Data Setup Time Control
//Address: PD-CC ~ PD-CE Reserved
#define _PD_ADC_DDC_INDEX_CF                0xCF        // ADC DDC SRAM R/W Index
#define _PD_ADC_DDC_ACCESS_PORT_D0          0xD0        // ADC DDC SRAM R/W Port
#define _PD_DVI_DDC_INDEX_D1                0xD1        // DVI DDC SRAM R/W Index
#define _PD_DVI_DDC_ACCESS_PORT_D2          0xD2        // DVI DDC SRAM R/W Port
//Address: PD-D3 ~ PD-D4 Reserved
#define _PD_DDCCI_REMAIN_DATA_D5            0xD5        // DDCCI Remaining Data Length
#define _PD_DVI_SEGMENT_ADDRESS_D6          0xD6        // DVI DDC Slave Address for Segment Control
#define _PD_DVI_SEGMENT_DATA_D7             0xD7        // Data Access for Slave ID
//Address: PD-D8 ~ PD-D9 Reserved


//--------------------------------------------------
// PWM(Page D)
//--------------------------------------------------
#define _PD_PWM_CK_SEL_DA                   0xDA        // PWMx Clock Generator Input Source
#define _PD_PWM03_M_DB                      0xDB        // PWMx Clock First Stage Divider
#define _PD_PWM45_M_DC                      0xDC        // PWMx Dummy Register
#define _PD_PWM01_N_MSB_DD                  0xDD        // PWMx Clock Second Stage Divider MSB
#define _PD_PWM0_N_LSB_DE                   0xDE        // PWM0 Clock Second Stage Divider LSB
#define _PD_PWM1_N_LSN_DF                   0xDF        // PWM1 Clock Second Stage Divider LSB
#define _PD_PWM23_N_MSB_E0                  0xE0        // PWM2 Clock Second Stage Divider MSB
#define _PD_PWM2_N_LSB_E1                   0xE1        // PWM2 Clock Second Stage Divider LSB
//Address: PD-E2 ~ PD-E5 Reserved
#define _PD_PWML_E6                         0xE6        // PWMx Active L Control
#define _PD_VS_CTRL_E7                      0xE7        // Enable PWMx Reset by DVS
#define _PD_PWM_EN_E8                       0xE8        // PWMx Output Enable
#define _PD_PWM_CK_E9                       0xE9        // Select First/Second Stage Output
#define _PD_PWM0H_DUT_EA                    0xEA        // PWM0 Duty Width[11:4]
#define _PD_PWM1H_DUT_EB                    0xEB        // PWM1 Duty Width[11:4]
#define _PD_PWM01L_DUT_EC                   0xEC        // PWM0/PWM1 Duty Width[3:0]
#define _PD_PWM2H_DUT_ED                    0xED        // PWM2 Duty Width[11:4]
//Address: PD-EE Reserved
#define _PD_PWM23L_DUT_EF                   0xEF        // PWM2 Duty Width[3:0]
//Address: PD-F0 ~ PD-FF Reserved


/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page E: Register2//////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//Address: PE-DF ~ PE-E9 Reserved

//--------------------------------------------------
// CEC Contol Register(Page E)
//--------------------------------------------------
#define _PE_CEC_CR_1_EA                     0xEA        // Initial Address
#define _PE_CEC_CR0_EB                      0xEB        // CEC Control Register 0
#define _PE_CEC_CR1_EC                      0xEC        // CEC Control Register 1
#define _PE_CEC_CR2_ED                      0xED        // CEC Control Register 2
#define _PE_CEC_CR3_EE                      0xEE        // CEC Control Register 3
#define _PE_CEC_RT0_EF                      0xEF        // CEC Retry Register 0
#define _PE_CEC_RT1_F0                      0xF0        // CEC Retry Register 1
#define _PE_CEC_RX0_F1                      0xF1        // CEC Rx Control Register 0
#define _PE_CEC_RX1_F2                      0xF2        // CEC Rx Control Register 1
#define _PE_CEC_TX1_F3                      0xF3        // CEC Tx Control Register 0
#define _PE_CEC_TX1_F4                      0xF4        // CEC Tx Control Register 1
#define _PE_CEC_TX_FIFO_F5                  0xF5        // CEC Tx FIFO Data Output Port
#define _PE_CEC_RX_FIFO_F6                  0xF6        // CEC Rx FIFO Data Output Port
#define _PE_CRC_RX_START0_F7                0xF7        // Min Width (3.5ms)
#define _PE_CRC_RX_START1_F8                0xF8        // Min Width (4.7ms)
#define _PE_CRC_RX_DATA0_F9                 0xF9        // Sample Time (1.05ms)
#define _PE_CRC_RX_DATA1_FA                 0xFA        // Min Data Bit Width (2.05ms)
#define _PE_CRC_TX_START0_FB                0xFB        // 3.7ms
#define _PE_CRC_TX_START1_FC                0xFC        // 0.8ms
#define _PE_CRC_TX_DATA0_FD                 0xFD        // 0.6ms
#define _PE_CRC_TX_DATA1_FE                 0xFE        // 0.9ms
#define _PE_CRC_TX_DATA2_FF                 0xFF        // 0.9ms


/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page F: Register3//////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------
// CEC Analog Function(Page F)
//--------------------------------------------------
//Address: PF-A0 ~ PF-C6 Reserved
#define _PF_AUT_OK_CONTROL_C7               0xC7        // CEC 27K Pull Up Resistor Control
#define _PF_CEC_ANALOG_R_C8                 0xC8        // CEC Block Debug Signal Out
#define _PF_REV_DUMMY4_C9                   0xC9        // Dummy4
//Address: PF-CA ~ PF-CC Reserved
#define _PF_MCU_CONTORL_CD                  0xCD        // SPI-Flash Clock Divider
#define _PF_MCU_CLOCK_CONTROL_CE            0xCE        // MCU Clock Control
//#define _PF_MCU_RAM_TEST_CF                   0xCF        // Start BIST Function for MCU External RAM
//Address: PF-D0 ~ PF-DF Reserved
#endif // End of #if(_SCALER_TYPE == _RTD2545LR)


//--------------------------------------------------
// Pin-Share(Page E)
//--------------------------------------------------
//Address: PE-A0 ~ PD-D3 Reserved
#define _PE_PIN_SHARE_CTRL00_D4             0xD4        // V8 Source Select, SDRAM Control and Package Type Selection
#define _PE_PIN_SHARE_CTRL01_D5             0xD5        // SDR DQM and Pin-Share of {43~44}[48pin]/{57~58}[64pin]
#define _PE_PIN_SHARE_CTRL02_D6             0xD6        // Pin-Share of {26~28, 55~56}[64pin]
#define _PE_PIN_SHARE_CTRL03_D7             0xD7        // Pin-Share of {42}[48pin]/{30,54,59}[64pin]
#define _PE_PIN_DRIVING_CTRL10_D8           0xD8        // Driving Current Control Register 0
#define _PE_PIN_DRIVING_CTRL11_D9           0xD9        // Driving Current Control Register 1
#define _PE_PIN_DRIVING_CTRL12_DA           0xDA        // Driving Current Control Register 2
#define _PE_PIN_DRIVING_CTRL13_DB           0xDB        // Driving Current Control Register 3
#define _PE_PIN_DRIVING_CTRL14_DC           0xDC        // Driving Current Control Register 4
#define _PE_PIN_DRIVING_CTRL15_DD           0xDD        // Driving Current Control Register 5
#define _PE_PIN_DRIVING_CTRL16_DE           0xDE        // Driving Current Control Register 6


#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Page 10: Register4/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------
// Pin Share(Page 10)
//--------------------------------------------------
#define _P10_PIN_SHARE_CTRL00_A0            0xA0        // Pin 31~34 of QFP 128
#define _P10_PIN_SHARE_CTRL01_A1            0xA1        // Pin 35~37, Pin 41 of QFP 128
#define _P10_PIN_SHARE_CTRL02_A2            0xA2        // Pin 42~44 of QFP 128
#define _P10_PIN_SHARE_CTRL03_A3            0xA3        // Pin 45~48 of QFP 128
#define _P10_PIN_SHARE_CTRL04_A4            0xA4        // Pin 50~51, Pin 55 of QFP 128
#define _P10_PIN_SHARE_CTRL05_A5            0xA5        // Pin 52, Pin 65~66 of QFP 128
#define _P10_PIN_SHARE_CTRL06_A6            0xA6        // Pin 53, Pin 67~68 of QFP 128
#define _P10_PIN_SHARE_CTRL07_A7            0xA7        // Pin 54, Pin 69~70 of QFP 128
#define _P10_PIN_SHARE_CTRL08_A8            0xA8        // Pin 56~57 of QFP 128
#define _P10_PIN_SHARE_CTRL09_A9            0xA9        // Pin 58~59 of QFP 128
#define _P10_PIN_SHARE_CTRL0A_AA            0xAA        // Pin 63~64 of QFP 128
#define _P10_PIN_SHARE_CTRL0B_AB            0xAB        // Pin 71~72, Pin 74~83 of QFP 128
#define _P10_PIN_SHARE_CTRL0C_AC            0xAC        // Pin 99~100, Pin 102 of QFP 128
#define _P10_PIN_SHARE_CTRL0D_AD            0xAD        // Pin 96, Pin 103~104 of QFP 128
#define _P10_PIN_SHARE_CTRL0E_AE            0xAE        // Pin 97, Pin 105, Pin 108 of QFP 128
#define _P10_PIN_SHARE_CTRL0F_AF            0xAF        // Pin 109~114 of QFP 128
#define _P10_PIN_SHARE_CTRL10_B0            0xB0        // Pin 98, Pin 111~112 of QFP 128
#define _P10_PIN_SHARE_CTRL11_B1            0xB1        // Pin 101, Pin 113~114 of QFP 128
#define _P10_PIN_SHARE_CTRL12_B2            0xB2        // Pin 119, Pin 121~122 of QFP 128
#define _P10_PIN_SHARE_CTRL13_B3            0xB3        // Pin 123~124 and Pin 126 of QFP 128
#define _P10_PIN_DRIVING_CTRL0_B4           0xB4        // Pin Driving Control Register 0
#define _P10_PIN_DRIVING_CTRL1_B5           0xB5        // Pin Driving Control Register 1
#define _P10_PIN_PULLUP_CTRL0_B6            0xB6        // Pull Up Control Register 0
#define _P10_PIN_SHARE_CTRL14_B7            0xB7        // SDRAM Control
#define _P10_PIN_SHARE_CTRL15_B8            0xB8        // SDRAM DQM Control
#define _P10_PIN_DRIVING_CTRL2_B9           0xB9        // Pin Driving Control Register 2
#define _P10_PIN_DRIVING_CTRL3_BA           0xBA        // Pin Driving Control Register 3
#define _P10_PIN_DRIVING_CTRL4_BB           0xBB        // Pin Driving Control Register 4
#define _P10_PIN_DRIVING_CTRL5_BC           0xBC        // Pin Driving Control Register 5
#define _P10_LINE_IN_CONTORL_BD             0xBD        // LINE IN Control
#endif

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// DDC Special Function Access(DDC/CI)
//--------------------------------------------------
#define _DDC_SET_SLAVE_F4                   0xF4        // DDC Set Slave Address
#define _DDC_SUB_IN_F5                      0xF5        // DDC Sub Address Received
#define _DDC_DATA_IN_F6                     0xF6        // DDC Data Received
#define _DDC_CTRL_F7                        0xF7        // DDC Control Register
#define _DDC_STATUS_F8                      0xF8        // DDC Status
#define _DDC_IRQ_CTRL_F9                    0xF9        // DDC IRQ Control Register

//--------------------------------------------------
// DDC Channel (ADC/DVI)
//--------------------------------------------------
#define _DDC_ENABLE_FA                      0xFA        // DDC Channel Enable Control Register
#define _DDC_INDEX_FB                       0xFB        // DDC SRAM R/W Index Register
#define _DDC_ACCESS_PORT_FC                 0xFC        // DDC Channel Access Port
#define _DDC_DVI_ENABLE_FD                  0xFD        // DDC DVI Channel Enable Control Register
#define _DDC_DVI_INDEX_FE                   0xFE        // DDC DVI SRAM R/W Index Register
#define _DDC_DVI_ACCESS_PORT_FF             0xFF        // DDC DVI Channel Access Port

//--------------------------------------------------
// Scale Down Port
//--------------------------------------------------
//#define _SD_V_SCALE_INIT_00                 0x00        // Vertical Scale Down Initial Select
//#define _SD_V_SCALE_FACTOR_H_01             0x01        // Vertical Scale Down Factor HByte
//#define _SD_V_SCALE_FACTOR_M_02             0x02        // Vertical Scale Down Factor MByte
//#define _SD_V_SCALE_FACTOR_L_03             0x03        // Vertical Scale Down Factor LByte
//#define _SD_H_SCALE_INIT_04                 0x04        // Horizontal Scale Down Initial Select
//#define _SD_H_SCALE_FACTOR_H_05             0x05        // Horizontal Scale Down Factor HByte
//#define _SD_H_SCALE_FACTOR_M_06             0x06        // Horizontal Scale Down Factor MByte
//#define _SD_H_SCALE_FACTOR_L_07             0x07        // Horizontal Scale Down Factor LByte
//#define _SD_H_SCALE_ACCH_08                 0x08        // Horizontal Scale Down Accumulated Factor HByte
//#define _SD_H_SCALE_ACCL_09                 0x09        // Horizontal Scale Down Accumulated Factor LByte
//#define _SD_ACC_WIDTHH_0A                   0x0A        // Horizontal Scale Down Accumulated Width HByte
//#define _SD_ACC_WIDTHL_0B                   0x0B        // Horizontal Scale Down Accumulated Width LByte
//#define _SD_FLAT_WIDTHH_0C                  0x0C        // Horizontal Scale Down Flat Width HByte
//#define _SD_FLAT_WIDTHL_0D                  0x0D        // Horizontal Scale Down Flat Width LByte
//Address: 25-0E~25-0F Reserved
//#define _SD_INPUT_PAT_GEN_CTRL0_10          0x10        // Input Pattern Generator Control Register0
//#define _SD_INPUT_PAT_GEN_CTRL1_11          0x11        // Input Pattern Generator Control Register1
//#define _SD_INPUT_PAT_GEN_RED_12            0x12        // Input Pattern Generator RED Initial Value
//#define _SD_INPUT_PAT_GEN_GREEN_13          0x13        // Input Pattern Generator GREEN Initial Value
//#define _SD_INPUT_PAT_GEN_BLUE_14           0x14        // Input Pattern Generator BLUE Initial Value

//--------------------------------------------------
// Display Format Port
//--------------------------------------------------
#define _DISP_DH_TOTAL_H_00                 0x00        // Display Horizontal Total Pixels HByte
#define _DISP_DH_TOTAL_L_01                 0x01        // Display Horizontal Total Pixels LByte
#define _DISP_DHS_END_02                    0x02        // Display Horizontal Sync End Pixels
#define _DISP_DH_BKGD_STA_H_03              0x03        // Display Horizontal Background Start HByte
#define _DISP_DH_BKGD_STA_L_04              0x04        // Display Horizontal Background Start LByte
#define _DISP_DH_ACT_STA_H_05               0x05        // Display Horizontal Active Start HByte
#define _DISP_DH_ACT_STA_L_06               0x06        // Display Horizontal Active Start LByte
#define _DISP_DH_ACT_END_H_07               0x07        // Display Horizontal Active End HByte
#define _DISP_DH_ACT_END_L_08               0x08        // Display Horizontal Active End LByte
#define _DISP_DH_BKGD_END_H_09              0x09        // Display Horizontal Background End HByte
#define _DISP_DH_BKGD_END_L_0A              0x0A        // Display Horizontal Background End LByte
#define _DISP_DV_TOTAL_H_0B                 0x0B        // Display Vertical Total Lines HByte
#define _DISP_DV_TOTAL_L_0C                 0x0C        // Display Vertical Total Lines LByte
#define _DISP_DVS_END_0D                    0x0D        // Display Vertical Sync End Lines
#define _DISP_DV_BKGD_STA_H_0E              0x0E        // Display Vertical Background Start HByte
#define _DISP_DV_BKGD_STA_L_0F              0x0F        // Display Vertical Background Start LByte
#define _DISP_DV_ACT_STA_H_10               0x10        // Display Vertical Active Start HByte
#define _DISP_DV_ACT_STA_L_11               0x11        // Display Vertical Active Start LByte
#define _DISP_DV_ACT_END_H_12               0x12        // Display Vertical Active End HByte
#define _DISP_DV_ACT_END_L_13               0x13        // Display Vertical Active End LByte
#define _DISP_DV_BKGD_END_H_14              0x14        // Display Vertical Background End HByte
#define _DISP_DV_BKGD_END_L_15              0x15        // Display Vertical Background End LByte
//Address: 2B-16~2B-1F Reserved
#define _DISP_TIMING_20                     0x20        // Display Clock Fine Tuning Register
#define _DISP_OSD_REFERENCE_DEN_21          0x21        // Position Of Reference DEN for OSD
#define _DISP_NEW_DV_CTRL_22                0x22        // New DV Control Register
#define _DISP_NEW_DV_DLY_23                 0x23        // New DV Delay

//--------------------------------------------------
// FIFO Window Port
//--------------------------------------------------
#define _FIFO_DWRWL_H_BSU_00                0x00        // Display Window Read Width/Length HByte Before Scaling Up
#define _FIFO_DWRW_L_BSU_01                 0x01        // Display Window Read Width LByte Before Scaling Up
#define _FIFO_DWRL_L_BSU_02                 0x02        // Display Window Read Length LByte Before Scaling Up

//--------------------------------------------------
// Scale Up Port
//--------------------------------------------------
//#define _SU_H_SCALE_FACTOR_H_00             0x00        // Horizontal Scale Up Factor HByte
//#define _SU_H_SCALE_FACTOR_M_01             0x01        // Horizontal Scale Up Factor MByte
//#define _SU_H_SCALE_FACTOR_L_02             0x02        // Horizontal Scale Up Factor LByte
//#define _SU_V_SCALE_FACTOR_H_03             0x03        // Vertical Scale Up Factor HByte
//#define _SU_V_SCALE_FACTOR_M_04             0x04        // Vertical Scale Up Factor MByte
//#define _SU_V_SCALE_FACTOR_L_05             0x05        // Vertical Scale Up Factor LByte
//#define _SU_H_SF_SEGMENT_1PIXEL_H_06        0x06        // Horizontal Scale Up Factor Segment 1 Pixel HByte
//#define _SU_H_SF_SEGMENT_1PIXEL_L_07        0x07        // Horizontal Scale Up Factor Segment 1 Pixel LByte
//#define _SU_H_SF_SEGMENT_2PIXEL_H_08        0x08        // Horizontal Scale Up Factor Segment 2 Pixel HByte
//#define _SU_H_SF_SEGMENT_2PIXEL_L_09        0x09        // Horizontal Scale Up Factor Segment 2 Pixel LByte
//#define _SU_H_SF_SEGMENT_3PIXEL_H_0A        0x0A        // Horizontal Scale Up Factor Segment 3 Pixel HByte
//#define _SU_H_SF_SEGMENT_3PIXEL_L_0B        0x0B        // Horizontal Scale Up Factor Segment 3 Pixel LByte
//#define _SU_H_SF_DELTA_1PIXEL_H_0C          0x0C        // Horizontal Scale Up Factor DELTA 1 Pixel HByte
//#define _SU_H_SF_DELTA_1PIXEL_L_0D          0x0D        // Horizontal Scale Up Factor DELTA 1 Pixel LByte
//#define _SU_H_SF_DELTA_2PIXEL_H_0E          0x0E        // Horizontal Scale Up Factor DELTA 2 Pixel HByte
//#define _SU_H_SF_DELTA_2PIXEL_L_0F          0x0F        // Horizontal Scale Up Factor DELTA 2 Pixel LByte
//#define _SU_H_COEF_INI_VALUE_10             0x10        // Accumulate Horizontal Filter Coefficient Initial Value
//#define _SU_V_COEF_INI_VALUE_11             0x11        // Accumulate Vertical Filter Coefficient Initial value

//--------------------------------------------------
// Sync Processor Port
//--------------------------------------------------
#define _SYNC_G_CLAMP_START_00              0x00        // G/Y Channle Clamp Signal Output Start
#define _SYNC_G_CLAMP_END_01                0x01        // G/Y Channle Clamp Signal Output End
#define _SYNC_BR_CLAMP_START_02             0x02        // B/Pb & R/Pr Channle Clamp Signal Output Start
#define _SYNC_BR_CLAMP_END_03               0x03        // B/Pb & R/Pr Channle Clamp Signal Output End
#define _SYNC_CLAMP_CTRL0_04                0x04        // Clamp Signal Control Register 0
#define _SYNC_CLAMP_CTRL1_05                0x05        // Clamp Signal Control Register 1
#define _SYNC_CLAMP_CTRL2_06                0x06        // Clamp Signal Control Register 2
#define _SYNC_CAPTURE_WINDOW_SET_07         0x07        // Capture Window Setting
#define _SYNC_DETECT_TOLERANCE_SET_08       0x08        // Detection Tolerance Setting
//Address: 5D-08~5D-0F Reserved
#define _SYNC_MACRO_VISION_CTRL_10          0x10        // Macro Vision Control Register
#define _SYNC_MV_START_LINE_EVEN_11         0x11        // Macro Vision Start Line in Even Field
#define _SYNC_MV_END_LINE_EVEN_12           0x12        // Macro Vision End Line in Even Field
#define _SYNC_MV_START_LINE_ODD_13          0x13        // Macro Vision Start Line in Odd Field
#define _SYNC_MV_END_LINE_ODD_14            0x14        // Macro Vision End Line in Odd Field

//--------------------------------------------------
// Hightlight Window Port
//--------------------------------------------------
#define _HW_H_START_H_00                    0x00        // Highlight Window Horizontal Start HByte
#define _HW_H_START_L_01                    0x01        // Highlight Window Horizontal Start LByte
#define _HW_H_END_H_02                      0x02        // Highlight Window Horizontal End HByte
#define _HW_H_END_L_03                      0x03        // Highlight Window Horizontal End LByte
#define _HW_V_START_H_04                    0x04        // Highlight Window Vertical Start HByte
#define _HW_V_START_L_05                    0x05        // Highlight Window Vertical Start LByte
#define _HW_V_END_H_06                      0x06        // Highlight Window Vertical End HByte
#define _HW_V_END_L_07                      0x07        // Highlight Window Vertical End LByte
//#define _HW_BORDER_WIDTH_08                 0x08        // Highlight Window Border Width
//#define _HW_BORDER_COLOR_R_09               0x09        // Highlight Window Border Red Color MSB 6bit (Red Color 2-bit LSB = 00)
//#define _HW_BORDER_COLOR_G_0A               0x0A        // Highlight Window Border Green Color MSB 6bit (Red Color 2-bit LSB = 00)
//#define _HW_BORDER_COLOR_B_0B               0x0B        // Highlight Window Border Blue Color MSB 6bit (Red Color 2-bit LSB = 00)
#define _HW_WINDOW_CTRL0_0C                 0x0C        // Highlight Window Control Register0
#define _HW_WINDOW_CTRL1_0D                 0x0D        // Highlight Window Control Register1

//--------------------------------------------------
// Contrast/Brightness Coefficient Port
//--------------------------------------------------
//#define _CB_BRI_R_COEF_A_00                 0x00        // Brightness Red Coefficient Set.A
//#define _CB_BRI_G_COEF_A_01                 0x01        // Brightness Green Coefficient Set.A
//#define _CB_BRI_B_COEF_A_02                 0x02        // Brightness Blue Coefficient Set.A
//#define _CB_CTS_R_COEF_A_03                 0x03        // Contrast Red Coefficient Set.A
//#define _CB_CTS_G_COEF_A_04                 0x04        // Contrast Green Coefficient Set.A
//#define _CB_CTS_B_COEF_A_05                 0x05        // Contrast Blue Coefficient Set.A
//#define _CB_BRI_R_COEF_B_06                 0x06        // Brightness Red Coefficient Set.B
//#define _CB_BRI_G_COEF_B_07                 0x07        // Brightness Green Coefficient Set.B
//#define _CB_BRI_B_COEF_B_08                 0x08        // Brightness Blue Coefficient Set.B
//#define _CB_CTS_R_COEF_B_09                 0x09        // Contrast Red Coefficient Set.B
//#define _CB_CTS_G_COEF_B_0A                 0x0A        // Contrast Green Coefficient Set.B
//#define _CB_CTS_B_COEF_B_0B                 0x0B        // Contrast Blue Coefficient Set.B

//--------------------------------------------------
// Timing Controller Port
//--------------------------------------------------
#define _TCON_CTRL0_00                      0x00        // Timing Controller Control Register0
#define _TCON_CTRL1_01                      0x01        // Timing Controller Control Register1
#define _TCON_PIXEL_THRESHOLD_MSB_02        0x02        // Pixel Threshold High Value for Smart Polarity
#define _TCON_PIXEL_THRESHOLD1_LSB_03       0x03        // 2 Line Sum of Difference Threshold 1 Value: bit [7:0], ie:TH1 (Also refer to CR8C-02[7])
#define _TCON_PIXEL_THRESHOLD2_LSB_04       0x04        // 2 Line Sum of Difference Threshold 2 Value: bit [7:0], ie:TH2 (Also refer to CR8C-02[6])
#define _TCON_LINE_THRESHOLD_05             0x05        // Line Threshold Value for Smart Polarity
//Address: 8C-06~8C-07 Reserved to 0
#define _TCON_TCON0_V_STA_LSB_08            0x08        // TCON[0] Vertical Start LSB Register
//#define _TCON_TCON0_V_SE_MSB_09             0x09        // TCON[0] Vertical Start/End MSB Register
//#define _TCON_TCON0_V_END_LSB_0A            0x0A        // TCON[0] Vertical End LSB Register
//#define _TCON_TCON0_H_STA_LSB_0B            0x0B        // TCON[0] Horizontal Start LSB Register
//#define _TCON_TCON0_H_SE_MSB_0C             0x0C        // TCON[0] Horizontal Start/End MSB Register
//#define _TCON_TCON0_H_END_LSB_0D            0x0D        // TCON[0] Horizontal End LSB Register
//#define _TCON_TCON0_CTRL_0E                 0x0E        // TCON[0] Control Register
//#define _TCON_TCON0_RESERVED_0F             0x0F        // TCON[0] Reserved Register(TCON[0]~TCON[9] Have This Register)
#define _TCON_TCON1_V_STA_LSB_10            0x10        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON2_V_STA_LSB_18            0x18        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON3_V_STA_LSB_20            0x20        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON4_V_STA_LSB_28            0x28        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON5_V_STA_LSB_30            0x30        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON6_V_STA_LSB_38            0x38        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON7_V_STA_LSB_40            0x40        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON8_V_STA_LSB_48            0x48        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON9_V_STA_LSB_50            0x50        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON10_V_STA_LSB_58           0x58        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON11_V_STA_LSB_60           0x60        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON12_V_STA_LSB_68           0x68        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON13_V_STA_LSB_70           0x70        // TCON[13] Vertical Start LSB Register
//TCON[0]:08~0F    //TCON[1]:10~17    //TCON[2]:18~1F   //TCON[3]:20~27    //TCON[4]:28~2F
//TCON[5]:30~37    //TCON[6]:38~3F    //TCON[7]:40~47   //TCON[8]:48~4F    //TCON[9]:50~57
//TCON[10]:58~5F   //TCON[11]:60~67   //TCON[12]:68~6F  //TCON[13]:70~77

//##################################################
// Dot Masking
//##################################################
//#define _TCON_TCON10_DOT_MASK_CTRL_5F     0x5F        // TCON[10] Dot Masking Control Register
//#define _TCON_TCON11_DOT_MASK_CTRL_67     0x67        // TCON[11] Dot Masking Control Register
//#define _TCON_TCON12_DOT_MASK_CTRL_6F     0x6F        // TCON[12] Dot Masking Control Register
//#define _TCON_TCON13_DOT_MASK_CTRL_77     0x77        // TCON[13] Dot Masking Control Register
//Address: 8C-78~8C-9F Reserved

//##################################################
// Control For LVDS
//##################################################
#define _TCON_LVDS_CTRL0_A0                 0xA0        // LVDS Control Register0
#define _TCON_LVDS_CTRL1_A1                 0xA1        // LVDS Control Register1
#define _TCON_LVDS_CTRL2_A2                 0xA2        // LVDS Control Register2
#define _TCON_LVDS_CTRL3_A3                 0xA3        // LVDS Control Register3
#define _TCON_LVDS_CTRL4_A4                 0xA4        // LVDS Control Register4
#define _TCON_LVDS_CTRL5_A5                 0xA5        // LVDS Control Register5
//Address: 8C-A6~8C-BF Reserved

//##################################################
// Control For RSDS
//##################################################
#define _TCON_RSDS_OUTPUT_CTRL0_C0          0xC0        // RSDS Output Control Register
#define _TCON_RSDS_INTERLEAVING_H_C1        0xC1        // RSDS Display Data Bus Interleaving Line Buffer Length High Byte
#define _TCON_RSDS_INTERLEAVING_L_C2        0xC2        // RSDS Display Data Bus Interleaving Line Buffer Length Low Byte
#define _TCON_RSDS_PWR_CTL_C3               0xC3        // RSDS Even /Odd Port Power Control
//--------------------------------------------------
// Pin Configuration Port
//--------------------------------------------------
#define _PS_CTRL00_00                       0x00        // Pin Share Control Register0
//#define _PS_CTRL01_01                       0x01        // Pin Share Control Register1
//#define _PS_CTRL02_02                       0x02        // Pin Share Control Register2
//#define _PS_CTRL03_03                       0x03        // Pin Share Control Register3
//#define _PS_CTRL04_04                       0x04        // Pin Share Control Register4
//#define _PS_CTRL05_05                       0x05        // Pin Share Control Register5
//#define _PS_CTRL06_06                       0x06        // Pin Share Control Register6
//#define _PS_CTRL07_07                       0x07        // Pin Share Control Register7
//#define _PS_CTRL08_08                       0x08        // Pin Share Control Register8
//#define _PS_CTRL09_09                       0x09        // Pin Share Control Register9
//#define _PS_CTRL0A_0A                       0x0A        // Pin Share Control RegisterA
//#define _PS_CTRL0B_0B                       0x0B        // Pin Share Control RegisterB
//#define _PS_CTRL0C_0C                       0x0C        // Pin Share Control RegisterC
//#define _PS_CTRL0D_0D                       0x0D        // Pin Share Control RegisterD
//#define _PS_CTRL0E_0E                       0x0E        // Pin Share Control RegisterE
//Address: 8E-0F~8E-1F Reserved

//##################################################
// Pin Driving
//##################################################
#define _PS_PIN_DRIVING_CTRL0_20            0x20        // Pin Driving Current Control Register0
//#define _PS_PIN_DRIVING_CTRL1_21            0x21        // Pin Driving Current Control Register1
//#define _PS_PIN_DRIVING_CTRL2_22            0x22        // Pin Driving Current Control Register2
//#define _PS_PIN_DRIVING_CTRL3_23            0x23        // Pin Driving Current Control Register3
//#define _PS_PIN_DRIVING_CTRL4_24            0x24        // Pin Driving Current Control Register4
//#define _PS_PIN_DRIVING_CTRL5_25            0x25        // Pin Driving Current Control Register5
//#define _PS_PIN_DRIVING_CTRL6_26            0x26        // Pin Driving Current Control Register6
//#define _PS_PIN_DRIVING_CTRL7_27            0x27        // Pin Driving Current Control Register7
//#define _PS_PIN_DRIVING_CTRL8_28            0x28        // Pin Driving Current Control Register8
//Address: 8E-29~8E-2F Reserved

//##################################################
// Configuration Of Test Pin
//##################################################
//#define _PS_TEST_PIN_CTRL0_30               0x30        // Test Pin Control Register0
//#define _PS_TEST_PIN_CTRL1_31               0x31        // Test Pin Control Register1
//#define _PS_TEST_PIN_CTRL2_32               0x32        // Test Pin Control Register2
//#define _PS_TEST_PIN_CTRL3_33               0x33        // Test Pin Control Register3

//--------------------------------------------------
// Peaking and Coring Port
//--------------------------------------------------
//#define _PC_PEAKING_COEF0_00                0x00        // Coefficient C0 of Peaking filter
//#define _PC_PEAKING_COEF1_01                0x01        // Coefficient C1 of Peaking filter
//#define _PC_PEAKING_COEF2_02                0x02        // Coefficient C2 of Peaking filter
//#define _PC_CORING_MIN_03                   0x03        // Coring Minimum value
//#define _PC_CORING_MAX_POS_04               0x04        // Coring Maximum Positive value
//#define _PC_CORING_MAX_NEG_05               0x05        // Coring Maximum Negitive value (2's complement)

//--------------------------------------------------
// ICM Port
//--------------------------------------------------
//#define _ICM_MST_HUE_HB_00                  0x00        // High Byte Of Master Hue For Chroma Modifier N
//#define _ICM_MST_HUE_LB_01                  0x01        // Low Byte Of Master Hue For Chroma Modifier N
//#define _ICM_HUE_SET_02                     0x02        // ICM HUE Setting
//#define _ICM_U_OFFSET_03                    0x03        // U Offset 00, -128~127
//#define _ICM_V_OFFSET_04                    0x04        // V Offset 00, -128~127
// From E3-0x03 To E3-0x32 Is U/V Offset

//--------------------------------------------------
// CMDI Port
//--------------------------------------------------
//#define _CMDI_H_DISP_MSB_00                 0x00        // CMDI Horizontal Display MSB
//#define _CMDI_H_DISP_LSB_01                 0x01        // CMDI Horizontal Display LSB
///////////////////////////////////////////////////////////////////////////////////////////
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
///////////////////////////////////////////////////////////////////////////////////////////





//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
//////////////////////////////         Page + Port         ////////////////////////////////
//PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT

//--------------------------------------------------
// {Page2} HDCP Acess Port
//--------------------------------------------------
//#define _P2_HDCP_FRAME_COUNTER_C0           0xC0        // HDCP Frame Counter Register
//#define _P2_HDCP_SYS_INFO_C1                0xC1        // HDCP System Information Register

//--------------------------------------------------
// {Page2} HDMI Acess Port
//--------------------------------------------------
//Port C9&CA Referance To Specification
//Following Register is Assigned By Port CD&CE
#define _P2_HDMI_SCR_00                     0x00        // HDMI Switch Control Register
//#define _P2_HDMI_N_VAL_01                   0x01        // HDMI N Value Register
#define _P2_HDMI_BCHCR_02                   0x02        // HDMI BCH Control Register
#define _P2_HDMI_AFCR_03                    0x03        // HDMI Audio FIFO Control Register
#define _P2_HDMI_AFSR_04                    0x04        // HDMI Audio FIFO BIST Start Register
#define _P2_HDMI_MAGCR0_05                  0x05        // HDMI Maunal Gain Control Register0

//#define _P2_HDMI_MAGCR1_06                  0x06        // HDMI Maunal Gain Control Register1
//Address: P2-CE-07 ~ P2-CE-0F Reserved
#define _P2_HDMI_CMCR_10                    0x10        // HDMI Input Clock MUX Control Register
#define _P2_HDMI_MCAPR_11                   0x11        // HDMI M code
#define _P2_HDMI_SCAPR_12                   0x12        // HDMI S code
#define _P2_HDMI_DCAPR0_13                  0x13        // HDMI D code HByte
#define _P2_HDMI_DCAPR1_14                  0x14        // HDMI D code LByte
#define _P2_HDMI_PSCR_15                    0x15        // HDMI Phase Tracking Enable Control Register
#define _P2_HDMI_FTR_1A                     0x1A        // HDMI Target Time For Summation Of One Trent To Decide The Trent
#define _P2_HDMI_FBR_1B                     0x1B        // HDMI Target FIFO Depth and Boundary Address Distance
#define _P2_HDMI_ICTPSR1_21                 0x21        // HDMI I Code of Trend
#define _P2_HDMI_ICBPSR1_25                 0x25        // HDMI I Code of Boundary
#define _P2_HDMI_PCBPSR0_26                 0x26        // HDMI P Code of Boundary HByte
#define _P2_HDMI_PCBPSR1_27                 0x27        // HDMI P Code of Boundary LByte
#define _P2_HDMI_NTX1024TR0_28              0x28        // HDMI Masure the length of 1024 TV by Crystal
#define _P2_HDMI_STBPR_2A                   0x2A        // HDMI Boundary Tracking Update Response Time
#define _P2_HDMI_AAPNR_2D                   0x2D        // HDMI Phase Swallow Enable Control Register
#define _P2_HDMI_AVMCR_30                   0x30        // HDMI Audio/Video Mute Control Register
#define _P2_HDMI_WDCR0_31                   0x31        // HDMI Watch Dog Control Register0
#define _P2_HDMI_WDCR1_32                   0x32        // HDMI Watch Dog Control Register1
#define _P2_HDMI_WDCR2_33                   0x33        // HDMI Watch Dog Control Register2
#define _P2_HDMI_DBCR_34                    0x34        // HDMI Auto Load Double Buffer Enable
#define _P2_HDMI_DPCR0_38                   0x38        // HDMI DPLL Control Register0
#define _P2_HDMI_DPCR1_39                   0x39        // HDMI DPLL Control Register1
#define _P2_HDMI_DPCR2_3A                   0x3A        // HDMI DPLL Control Register2
#define _P2_HDMI_DPCR3_3B                   0x3B        // HDMI DPLL Control Register3
#define _P2_HDMI_VWDSR_41                   0x41        // HDMI Video Watch Dog For Packet Variation Status
#define _P2_HDMI_PVGCR0_45                  0x45        // HDMI Packet Variation Status Enable Control Register0
#define _P2_HDMI_VCR_50                     0x50        // HDMI Video Mode Control Register
#define _P2_HDMI_ACRCR_51                   0x51        // HDMI Color Space Control Register0
#define _P2_HDMI_ACRSR0_52                  0x52        // HDMI CTS in usage Register(CTS[19:12])
#define _P2_HDMI_AOCR_62                    0x62        // HDMI SPDIF/I2S Switch Control Register
///////////////////////////////////////////////////////////////////////////////////////////
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
///////////////////////////////////////////////////////////////////////////////////////////

//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
//////////////////////////////         Page + Port         ////////////////////////////////
//PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT





//PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT
//----------------------------   DCC Acess Port + Page     --------------------------------
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE

//--------------------------------------------------
// Page 0 (For Histogram / Ymin-max / Soft-Clamping / Scene-Change)
//--------------------------------------------------
#define _DCC_P0_NOR_FACTOR_H_00             0x00        // DCC Normalized Factor HByte
//#define _DCC_P0_NOR_FACTOR_M_01             0x01        // DCC Normalized Factor MByte
//#define _DCC_P0_NOR_FACTOR_L_02             0x02        // DCC Normalized Factor LByte
//#define _DCC_P0_BBE_CTRL_03                 0x03        // DCC Black Background Exception Control Register
//#define _DCC_P0_NFLT_CTRL_04                0x04        // DCC Noise Filter Control Register
//#define _DCC_P0_HIST_CTRL_05                0x05        // DCC Histogram Control Register
//#define _DCC_P0_SOFT_CLAMP_06               0x06        // DCC Slope Of Soft Clamping
//#define _DCC_P0_Y_MAX_LB_07                 0x07        // DCC Lower Bound Of Y_MAX
//#define _DCC_P0_Y_MIN_HB_08                 0x08        // DCC Higher Bound Of Y_MIN
//#define _DCC_P0_SCG_PERIOD_09               0x09        // DCC Scene Change Mode Period
//#define _DCC_P0_SCG_LB_0A                   0x0A        // SCG_DIFF Lower Bound For Exiting Scene Change Mode
//#define _DCC_P0_SCG_HB_0B                   0x0B        // SCG_DIFF Higher Bound For Exiting Scene Change Mode
//#define _DCC_P0_POPUP_CTRL_0C               0x0C        // DCC POP Up Status Register
//#define _DCC_P0_SCG_DIFF_0D                 0x0D        // (Histogram Difference Between Current Frame And Average)/8
//#define _DCC_P0_Y_MAX_VAL_0E                0x0E        // Max{Y_MAX_LB,(Y Maximum In Current Frame/4)}
//#define _DCC_P0_Y_MIN_VAL_0F                0x0F        // Min{Y_MIN_HB,(Y Minimum In Current Frame/4)}
//#define _DCC_P0_S0_VALUE_10                 0x10        // Normalized Histogram S0 Value
//#define _DCC_P0_S1_VALUE_11                 0x11        // Normalized Histogram S1 Value
//#define _DCC_P0_S2_VALUE_12                 0x12        // Normalized Histogram S2 Value
//#define _DCC_P0_S3_VALUE_13                 0x13        // Normalized Histogram S3 Value
//#define _DCC_P0_S4_VALUE_14                 0x14        // Normalized Histogram S4 Value
//#define _DCC_P0_S5_VALUE_15                 0x15        // Normalized Histogram S5 Value
//#define _DCC_P0_S6_VALUE_16                 0x16        // Normalized Histogram S6 Value

//--------------------------------------------------
// Page 1 (for Y-Curve / WBL Expansion)
//--------------------------------------------------
//#define _DCC_P1_DEF_CRV01_00                0x00        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV02_01                0x01        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV03_02                0x02        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV04_03                0x03        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV05_04                0x04        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV06_05                0x05        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV07_06                0x06        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV08_07                0x07        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV09_08                0x08        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV10_09                0x09        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV11_0A                0x0A        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV12_0B                0x0B        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV13_0C                0x0C        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV14_0D                0x0D        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV15_0E                0x0E        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_Y_BL_BIAS_0F                0x0F        // Y Offset For Black Level Expansion
//#define _DCC_P1_Y_WL_BIAS_10                0x10        // Y Offset For While Level Expansion
//#define _DCC_P1_BLD_UB_11                   0x11        // Upper Bound Of Blending Factor
//#define _DCC_P1_BLD_LB_12                   0x12        // Lower Bound Of Blending Factor
//#define _DCC_P1_DEV_FACTOR_13               0x13        // Deviation Weighting Factor
//#define _DCC_P1_BLD_VAL_14                  0x14        // Blending Factor Value = Max{BLD_UB - [(DEV_VAL*DEV_FACTOR)/256], BLD_LB}
//#define _DCC_P1_DEV_VAL_HI_15               0x15        // Deviation Value HByte
//#define _DCC_P1_DEV_VAL_LO_16               0x16        // Deviation Value LByte

//--------------------------------------------------
// Page 2 (for Calculation Parameter)
//--------------------------------------------------
// E7-00 ~ E7-8F of Page2 is SRAM initial value
//#define _DCC_P3_SRAM_00                     0x00        // SRAM Initial Value In Register 0x00

//--------------------------------------------------
// Page 3 (for Testing and Debug)
//--------------------------------------------------
//#define _DCC_P3_SRAM_BIST_00                0x00        // DCC SRAM BIST Control Register

//PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT
//----------------------------   DCC Acess Port + Page     --------------------------------
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE


/*
#if(_MCU_TYPE == _REALTEK_RTD2120)

//--------------------------------------------------
// DDC Special Function Access(DDC/CI)
//--------------------------------------------------
#define _DDC_SET_SLAVE_F4                   0xF4        // DDC Set Slave Address
#define _DDC_SUB_IN_F5                      0xF5        // DDC Sub Address Received
#define _DDC_DATA_IN_F6                     0xF6        // DDC Data Received
#define _DDC_CTRL_F7                        0xF7        // DDC Control Register
#define _DDC_STATUS_F8                      0xF8        // DDC Status
#define _DDC_IRQ_CTRL_F9                    0xF9        // DDC IRQ Control Register

//--------------------------------------------------
// DDC Channel (ADC/DVI)
//--------------------------------------------------
#define _DDC_ENABLE_FA                      0xFA        // DDC Channel Enable Control Register
#define _DDC_INDEX_FB                       0xFB        // DDC SRAM R/W Index Register
#define _DDC_ACCESS_PORT_FC                 0xFC        // DDC Channel Access Port
#define _DDC_DVI_ENABLE_FD                  0xFD        // DDC DVI Channel Enable Control Register
#define _DDC_DVI_INDEX_FE                   0xFE        // DDC DVI SRAM R/W Index Register
#define _DDC_DVI_ACCESS_PORT_FF             0xFF        // DDC DVI Channel Access Port


#endif  // End of #if(_MCU_TYPE == _REALTEK_RTD2120)
*/
