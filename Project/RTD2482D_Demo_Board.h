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
// ID Code      : Project.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_PROJECT == _RTD2472D_DEMO_BOARD)

#define _PCB_VERSION_C                          _ON

//--------------------------------------------------
// Setting
//--------------------------------------------------
/************************************************************/
/*   If user wants to change _EXTEND_TABLE_SUPPORT status,  */
/*   please remember to modify Misc. controls setting.      */
/************************************************************/
#define _EXTEND_TABLE_SUPPORT                   _OFF

#define _BJT_SUPPORT                            _OFF


//--------------------------------------------------
//PCB Type
//--------------------------------------------------
#define _RTD2472D_QA_PCB                        0     // Code ID : 0x01
#define _RTD2472D_DEMO_PCB                      1     // Code ID : 0x01
#define _RTD2545LR_QA_PCB                       2     // Code ID : 0x51
#define _RTD2545LR_DEMO_PCB                     3     // Code ID : 0x51
#define _RTD2472RD_QA_PCB                       4     // Code ID : 0x08
#define _RTD2472RD_DEMO_PCB                     5     // Code ID : 0x08

#define _PCB_TYPE                               _RTD2472D_DEMO_PCB


//--------------------------------------------------
//  PreDefine OSD Type
//--------------------------------------------------
#define _NONE_OSD                               0
#define _REALTEK_OSD                            1

#define _OSD_TYPE                               _REALTEK_OSD


//--------------------------------------------------
// Panel Type
//--------------------------------------------------
#define _CMO_LVDS_17                            0      // 1280 x 1024
#define _AU_RSDS_17                             1      // 1280 x 1024
#define _AU_LVDS_15                             2      // 1024 x  768
#define _AU_LVDS_20_WSXGA                       3      // 1680 x 1050
#define _AU_LVDS_20_UXGA                        4      // 1600 x 1200
#define _SAMSUNG_LVDS_19_WXGA                   5      // 1440 x  900
#define _CMO_LVDS_20_SXGA_PLUS                  6      // 1400 x 1050
#define _CMO_LVDS_19_WXGA                       7      // 1280 x  1024
#define _CMO_LVDS_22_WSXGA_PLUS                 8      // 1680 x 1050
#define _AU_LVDS_22_WSXGA                       9      // 1680 x 1050
#define _AU_LVDS_23_WUXGA                       10     // 1920 x 1200
#define _AU_LVDS_21_5_WUXGA                     11     // 1920 x 1080
#define _AU_LVDS_24_WUXGA                       12     // 1920 x 1080

#define _PANEL_TYPE                       _AU_LVDS_20_UXGA// _CMO_LVDS_19_WXGA//_AU_LVDS_20_UXGA//  _CMO_LVDS_19_WXGA//  _AU_LVDS_20_UXGA//_CMO_LVDS_19_WXGA//_AU_LVDS_20_UXGA//_AU_LVDS_22_WSXGA//20101104 zhangping


//--------------------------------------------------
// Support Multi-Function Modularize
//--------------------------------------------------
#define _GAMMA_FUNCTION                       _OFF//_ON// // _ON//_OFF
#define _VIVID_COLOR_FUCTION                    _OFF
#define _DDCCI_SUPPORT                          _OFF//_ON
#define _AUDIO_SUPPORT                          _OFF
#define _NON_LINEAR_SCALING_FUCTION             _OFF
#define _ASPECT_RATIO_SUPPORT                 _ON  //_OFF//for EMC ZP 20110704

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
/*
#define _HDMI_OVERSCAN                          _OFF
*/
// V012 Modify 20100316 End

#define _SRGB_COLOR_ENHANCE                     _OFF

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#define _COLOR_FORMAT_CONVERT                   _ON
// V012 Modify 20100304 End

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#define _OVERSCAN_VGA_SUPPORT                   _ON
#define _OVERSCAN_DVI_SUPPORT                   _ON
#define _OVERSCAN_HDMI_SUPPORT                  _ON
#define _OVERSCAN_DP_SUPPORT                    _ON
#define _OVERSCAN_YPBPR_SUPPORT                 _ON

#define _OVERSCAN_SUPPORT                       (_OVERSCAN_VGA_SUPPORT | _OVERSCAN_DVI_SUPPORT | _OVERSCAN_HDMI_SUPPORT | _OVERSCAN_DP_SUPPORT | _OVERSCAN_YPBPR_SUPPORT)
// V012 Modify 20100316 End

//--------------------------------------------------
// Dymanic Contrast Ratio (DCR)
//--------------------------------------------------
#define _DCR_TYPE_OFF                           0
#define _DCR_TYPE_1                             1
#define _DCR_TYPE_2                             2
#define _DCR_TYPE_3                             3

#define _DCR_MODE                               _DCR_TYPE_OFF


//--------------------------------------------------
// OD/FRC Function Supprot / SDRAM Working Type
//--------------------------------------------------
#define _OD_OFF_FRC_OFF                         0
#define _OD_OFF_FRC_ON                          1
#define _OD_ON_FRC_OFF                          2
#define _OD_ON_FRC_ON                           3

#define _MEMORY_WORK_TYPE                       _OD_OFF_FRC_OFF


//--------------------------------------------------
// Support Timing
//--------------------------------------------------
#define _H_FREQ_MAX                             1100            // Unit in 0.1 kHZ
#define _H_FREQ_MIN                             100             // Unit in 0.1 kHZ

// V012 Modify 20100319 Start
// V012 Patch Note (7) : Support 83Hz VFreq at max according to SQE testing items.
/*
#define _V_FREQ_MAX                             880             // Unit in 0.1 HZ
*/
#define _V_FREQ_MAX                             830             // Unit in 0.1 HZ
// V012 Modify 20100319 End

#define _V_FREQ_MIN                             490             // Unit in 0.1 HZ


#endif //End of #if(_PROJECT == _RTD2472DEMO)








