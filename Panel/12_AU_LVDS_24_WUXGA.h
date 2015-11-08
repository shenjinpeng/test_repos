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

#if(_PANEL_TYPE == _AU_LVDS_24_WUXGA)
//----------------------------------------------------------------------------------------------------
// ID Code      : Panel.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Maximum Panel Frame Rate
//--------------------------------------------------
#define _PANEL_MAX_FRAME_RATE                   860                 // Unit in 0.1 HZ


//--------------------------------------------------
// Definitions of DPLL N Code
//--------------------------------------------------
#if(_SCALER_TYPE == _RTD2472D)
#define _DPLL_N_CODE                    8   //16
#else
#define _DPLL_N_CODE                    5
#endif


//--------------------------------------------------
// Safe Mode (Slow down input frame rate)
//--------------------------------------------------
#define _SAFE_MODE                              _OFF



//--------------------------------------------------
// Set Last Line Finetune Method
//--------------------------------------------------
#define _LAST_LINE_METHOD_NONE                  0
#define _LAST_LINE_METHOD_0                     1                   // Formula: Tne DEN End to DEN Start Length must be (1280*N)
#define _LAST_LINE_METHOD_1                     2                   // Formula: Tne DEN End to DEN Start Length must be (4096*N + 128)
#define _LAST_LINE_METHOD_2                     3                   // Formula: Set to target last line.

#define _LAST_LINE_FINETUNE                     _LAST_LINE_METHOD_NONE
#define _LAST_LINE_TARGET                       400                 // For _LAST_LINE_METHOD_2


//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_AUO         // _PANEL_CMO or _PANEL_AUO or _PANEL_SAMSUNG or _PANEL_INNOLUX or _PANEL_CPT


//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_LVDS         // _PANEL_LVDS or _PANEL_RSDS or _PANEL_TTL
#define _LVDS_TABLE_TYPE                        1


//--------------------------------------------------
// Definitions for Panel Configuration
//--------------------------------------------------
#define _DISP_OUTPUT_PORT                       _DISP_DOUBLE_PORT   // _DISP_DOUBLE_PORT or _DISP_SINGLE_PORT
#define _DISP_BIT_MODE                          _DISP_24_BIT        // _DISP_24_BIT or _DISP_18_BIT

#define _DHS_MASK                               _DISABLE            // Definitions for First DHS Masking
#define _DISP_SKEW                              _DISABLE            // Definitions for Skew Display Data Output

#define _TEMP_DITHER                            _ENABLE             // Definations of Temporal Dithering


//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         32                  // Display Horizontal Start Position
#define _PANEL_DH_WIDTH                         1920                // Display Horizontal Width
#define _PANEL_DH_END                           1952                // Display Horizontal End Position

#define _PANEL_DH_TOTAL                         2100                // Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MAX                     4056                // Maxinum Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MIN                     2048                // Mininum Display Horizontal Total Clock Number in One Display Line

#define _PANEL_DV_START                         6                   // Display Vertical Start Position
#define _PANEL_DV_HEIGHT                        1080                // Display Vertical Width
#define _PANEL_DV_END                           1086                // Display Vertical End Position

#define _PANEL_DV_TOTAL                         1150                // Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MAX                     1600                // Maxinum Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MIN                     1061                // Mininum Display Vertical Total Clock Number in One Display Line

#define _PANEL_DH_SYNC_WIDTH                    1                   // Display Horizontal Sync Width
#define _PANEL_DV_SYNC_HEIGHT                   3                   // Display Vertical Sync Height

#define _PANEL_PIXEL_CLOCK                      128                 // Typical Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MAX                  160                 // Maxinum Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MIN                  100                 // Mininum Pixel Clock in MHz


#define _PANEL_POWER_ON_T1                      100                  // Panel Power On T1 (ms)
#define _PANEL_POWER_ON_T2                      137                  // Panel Power On T2 (ms)29
#define _PANEL_POWER_ON_T3                      250                 // Panel Power On T3 (ms)240

#define _PANEL_POWER_OFF_T4                     220                  // Panel Power Off T4 (ms)254
#define _PANEL_POWER_OFF_T5                     10                  // Panel Power Off T5 (ms)236
#define _PANEL_POWER_OFF_T6                     250                 // Panel Power Off T6 (ms)


#ifdef __ADJUST__


//----------------------------------------------------------------------------------------------------
// Dithering Table
//----------------------------------------------------------------------------------------------------
BYTE code tDITHER_SEQ_TABLE_0[] =
{
    0xe4,0xa2,0x05,0x37,0xf6,0x31,0x69,0xcb,0x1f,0xd2,0xb0,0xe6,
    0x45,0x1b,0x87,0xc6,0x9e,0xb4,0xc6,0x38,0xd4,0xdb,0x12,0x1b,
};


BYTE code tDITHER_TABLE_10_TO_6[] =
{
#if(1)
    0x07,0xf8,0x69,0x1e,0xad,0x52,0xc3,0xb4,
    0xad,0x52,0xc3,0xb4,0x07,0xf8,0x69,0x1e,
    0xad,0x52,0x69,0x1e,0xc3,0xb4,0x07,0xf8,
#elif(0)
    // 10 --> 6
    0x04,0x59,0xc8,0x1d,0xae,0xf3,0x62,0xb7,0x04,0x59,0xc8,0x1d,
    0xae,0xf3,0x62,0xb7,0x04,0x59,0xc8,0x1d,0xae,0xf3,0x62,0xb7,
#else
     0x0f,0xa5,0xa5,0xf0,0xf0,0x5a,0x5a,0x0f,0x0f,0xa5,0xa5,0xf0,
     0xf0,0x5a,0x5a,0x0f,0x0f,0xa5,0xa5,0xf0,0xf0,0x5a,0x5a,0x0f,
#endif
};


BYTE code tDITHER_TABLE_10_TO_8_D_DOMAIN[] =
{
#if(1)
    // 10 --> 8
    0x01,0x32,0x12,0x03,0x23,0x10,0x30,0x21,
    0x23,0x10,0x30,0x21,0x01,0x32,0x12,0x03,
    0x30,0x21,0x01,0x32,0x12,0x03,0x23,0x10,
#elif(0)
    // 10 --> 8
    0x20,0x02,0x31,0x13,0x02,0x20,0x13,0x31,
    0x31,0x13,0x02,0x20,0x13,0x31,0x20,0x02,
    0x20,0x02,0x31,0x13,0x02,0x20,0x13,0x31,
#else
    // 10 --> 8(AUO FRC 6 bit Panel)
    0x20,0x02,0x31,0x13,0x02,0x20,0x13,0x31,
    0x31,0x13,0x02,0x20,0x13,0x31,0x20,0x02,
    0x20,0x02,0x31,0x13,0x02,0x20,0x13,0x31,
#endif
};

//Hudson add Temporal offset table setting start 20080725
BYTE code tDITHER_TEMPOFFSET_TABLE[] =
{
    0xe4, 0xe4, 0xe4, 0xe4,  //0xe4 can be a default setting
};
//Hudson add Temporal offset table setting end 20080725

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
BYTE code tDITHER_TABLE_10_TO_8_I_DOMAIN[] =
{
    // 10 --> 8
    0x12,0x03,0x23,0x10,0x30,0x21,0x01,0x32,
    0x01,0x32,0x12,0x03,0x23,0x10,0x30,0x21,
    0x23,0x10,0x30,0x21,0x01,0x32,0x12,0x03,
};
#endif


//----------------------------------------------------------------------------------------------------
// Gamma Table
//----------------------------------------------------------------------------------------------------

#if(_GAMMA_FUNCTION == _ON)

#if(_SCALER_TYPE == _RTD2472D)

BYTE code tGAMMA_TABLE_RED[] =
{
    0x00, 0x01, 0x02,
    0x00, 0xC6, 0x07,
    0x04, 0x05, 0x04,
    0x06, 0x44, 0x05,
    0x08, 0x84, 0x05,
    0x0A, 0xC3, 0x04,
    0x0C, 0x84, 0x05,
    0x0E, 0xC5, 0x04,
    0x11, 0x04, 0x03,
    0x12, 0xC4, 0x04,
    0x14, 0xC5, 0x04,
    0x17, 0x04, 0x04,
    0x19, 0x04, 0x05,
    0x1B, 0x44, 0x04,
    0x1D, 0x44, 0x05,
    0x1F, 0x84, 0x04,
    0x21, 0x84, 0x03,
    0x23, 0x44, 0x04,
    0x25, 0x44, 0x05,
    0x27, 0x84, 0x04,
    0x29, 0x84, 0x04,
    0x2B, 0x84, 0x04,
    0x2D, 0x84, 0x04,
    0x2F, 0x84, 0x04,
    0x31, 0x84, 0x04,
    0x33, 0x84, 0x04,
    0x35, 0x84, 0x04,
    0x37, 0x84, 0x04,
    0x39, 0x84, 0x03,
    0x3B, 0x45, 0x05,
    0x3D, 0xC3, 0x04,
    0x3F, 0x84, 0x04,
    0x41, 0x83, 0x04,
    0x43, 0x45, 0x04,
    0x45, 0x85, 0x04,
    0x47, 0xC3, 0x04,
    0x49, 0x84, 0x04,
    0x4B, 0x84, 0x03,
    0x4D, 0x44, 0x04,
    0x4F, 0x44, 0x04,
    0x51, 0x44, 0x04,
    0x53, 0x43, 0x04,
    0x55, 0x05, 0x04,
    0x57, 0x44, 0x05,
    0x59, 0x83, 0x04,
    0x5B, 0x44, 0x04,
    0x5D, 0x44, 0x03,
    0x5F, 0x04, 0x04,
    0x61, 0x04, 0x04,
    0x63, 0x04, 0x04,
    0x65, 0x04, 0x04,
    0x67, 0x04, 0x03,
    0x68, 0xC4, 0x04,
    0x6A, 0xC4, 0x05,
    0x6D, 0x03, 0x03,
    0x6E, 0x85, 0x04,
    0x70, 0xC4, 0x05,
    0x73, 0x04, 0x03,
    0x74, 0xC5, 0x04,
    0x77, 0x03, 0x03,
    0x78, 0x84, 0x05,
    0x7A, 0xC4, 0x04,
    0x7C, 0xC4, 0x03,
    0x7E, 0x84, 0x04,
    0x80, 0x85, 0x03,
    0x82, 0x84, 0x05,
    0x84, 0xC4, 0x05,
    0x87, 0x04, 0x03,
    0x88, 0xC4, 0x04,
    0x8A, 0xC5, 0x04,
    0x8D, 0x03, 0x04,
    0x8E, 0xC4, 0x04,
    0x90, 0xC5, 0x04,
    0x93, 0x03, 0x04,
    0x94, 0xC4, 0x05,
    0x97, 0x04, 0x04,
    0x99, 0x05, 0x04,
    0x9B, 0x44, 0x03,
    0x9D, 0x04, 0x05,
    0x9F, 0x44, 0x04,
    0xA1, 0x44, 0x03,
    0xA3, 0x04, 0x04,
    0xA5, 0x04, 0x05,
    0xA7, 0x44, 0x04,
    0xA9, 0x44, 0x04,
    0xAB, 0x44, 0x04,
    0xAD, 0x44, 0x05,
    0xAF, 0x84, 0x04,
    0xB1, 0x84, 0x04,
    0xB3, 0x84, 0x07,
    0xB6, 0x44, 0x05,
    0xB8, 0x84, 0x04,
    0xBA, 0x84, 0x04,
    0xBC, 0x84, 0x04,
    0xBE, 0x83, 0x06,
    0xC0, 0xC4, 0x04,
    0xC2, 0xC5, 0x03,
    0xC4, 0xC4, 0x04,
    0xC6, 0xC4, 0x03,
    0xC8, 0x84, 0x04,
    0xCA, 0x83, 0x06,
    0xCC, 0xC5, 0x03,
    0xCE, 0xC5, 0x03,
    0xD0, 0xC5, 0x05,
    0xD3, 0x43, 0x05,
    0xD5, 0x42, 0x05,
    0xD7, 0x03, 0x06,
    0xD9, 0x42, 0x05,
    0xDB, 0x03, 0x05,
    0xDD, 0x05, 0x03,
    0xDF, 0x05, 0x03,
    0xE1, 0x05, 0x03,
    0xE3, 0x06, 0x04,
    0xE5, 0x83, 0x03,
    0xE7, 0x05, 0x05,
    0xE9, 0x84, 0x06,
    0xEC, 0x05, 0x03,
    0xEE, 0x03, 0x06,
    0xF0, 0x43, 0x05,
    0xF2, 0x43, 0x03,
    0xF3, 0xC4, 0x03,
    0xF5, 0x84, 0x04,
    0xF7, 0x84, 0x03,
    0xF9, 0x43, 0x03,
    0xFA, 0xC2, 0x02,
    0xFB, 0xC2, 0x02,
    0xFC, 0xC5, 0x03,
    0xFE, 0xC1, 0x00,
};

BYTE code tGAMMA_TABLE_GREEN[] =
{
    0x00, 0x02, 0x05,
    0x01, 0xC4, 0x05,
    0x04, 0x06, 0x04,
    0x06, 0x85, 0x05,
    0x09, 0x04, 0x04,
    0x0B, 0x05, 0x04,
    0x0D, 0x43, 0x04,
    0x0F, 0x04, 0x05,
    0x11, 0x44, 0x04,
    0x13, 0x44, 0x04,
    0x15, 0x45, 0x05,
    0x17, 0xC4, 0x04,
    0x19, 0xC5, 0x04,
    0x1C, 0x04, 0x04,
    0x1E, 0x04, 0x04,
    0x20, 0x04, 0x04,
    0x22, 0x04, 0x03,
    0x23, 0xC5, 0x06,
    0x26, 0x83, 0x04,
    0x28, 0x44, 0x04,
    0x2A, 0x44, 0x04,
    0x2C, 0x45, 0x05,
    0x2E, 0xC3, 0x04,
    0x30, 0x86, 0x04,
    0x33, 0x03, 0x04,
    0x34, 0xC4, 0x05,
    0x37, 0x04, 0x04,
    0x39, 0x04, 0x03,
    0x3A, 0xC4, 0x04,
    0x3C, 0xC5, 0x04,
    0x3F, 0x04, 0x03,
    0x40, 0xC4, 0x03,
    0x42, 0x83, 0x04,
    0x44, 0x44, 0x03,
    0x46, 0x05, 0x04,
    0x48, 0x44, 0x04,
    0x4A, 0x44, 0x04,
    0x4C, 0x44, 0x04,
    0x4E, 0x44, 0x05,
    0x50, 0x84, 0x04,
    0x52, 0x84, 0x04,
    0x54, 0x84, 0x05,
    0x56, 0xC4, 0x04,
    0x58, 0xC4, 0x04,
    0x5A, 0xC5, 0x03,
    0x5C, 0xC4, 0x05,
    0x5F, 0x04, 0x04,
    0x61, 0x04, 0x04,
    0x63, 0x05, 0x04,
    0x65, 0x43, 0x05,
    0x67, 0x44, 0x03,
    0x69, 0x04, 0x04,
    0x6B, 0x04, 0x04,
    0x6D, 0x04, 0x04,
    0x6F, 0x04, 0x04,
    0x71, 0x04, 0x04,
    0x73, 0x04, 0x04,
    0x75, 0x04, 0x04,
    0x77, 0x04, 0x04,
    0x79, 0x04, 0x05,
    0x7B, 0x44, 0x04,
    0x7D, 0x43, 0x05,
    0x7F, 0x43, 0x04,
    0x81, 0x05, 0x04,
    0x83, 0x44, 0x04,
    0x85, 0x44, 0x04,
    0x87, 0x44, 0x04,
    0x89, 0x44, 0x03,
    0x8B, 0x04, 0x05,
    0x8D, 0x44, 0x05,
    0x8F, 0x84, 0x04,
    0x91, 0x84, 0x03,
    0x93, 0x44, 0x04,
    0x95, 0x45, 0x04,
    0x97, 0x84, 0x04,
    0x99, 0x83, 0x04,
    0x9B, 0x44, 0x05,
    0x9D, 0x84, 0x04,
    0x9F, 0x84, 0x03,
    0xA1, 0x44, 0x05,
    0xA3, 0x84, 0x04,
    0xA5, 0x84, 0x05,
    0xA7, 0xC4, 0x04,
    0xA9, 0xC5, 0x03,
    0xAB, 0xC3, 0x05,
    0xAD, 0xC4, 0x04,
    0xAF, 0xC4, 0x05,
    0xB2, 0x03, 0x05,
    0xB4, 0x04, 0x04,
    0xB6, 0x05, 0x03,
    0xB8, 0x05, 0x04,
    0xBA, 0x44, 0x04,
    0xBC, 0x45, 0x04,
    0xBE, 0x84, 0x05,
    0xC0, 0xC4, 0x05,
    0xC3, 0x03, 0x05,
    0xC5, 0x03, 0x06,
    0xC7, 0x45, 0x02,
    0xC9, 0x03, 0x06,
    0xCB, 0x45, 0x03,
    0xCD, 0x44, 0x04,
    0xCF, 0x45, 0x03,
    0xD1, 0x44, 0x04,
    0xD3, 0x44, 0x04,
    0xD5, 0x45, 0x04,
    0xD7, 0x84, 0x04,
    0xD9, 0x84, 0x05,
    0xDB, 0xC3, 0x04,
    0xDD, 0x83, 0x05,
    0xDF, 0x84, 0x04,
    0xE1, 0x84, 0x04,
    0xE3, 0x85, 0x03,
    0xE5, 0x85, 0x04,
    0xE7, 0xC3, 0x04,
    0xE9, 0x85, 0x03,
    0xEB, 0x84, 0x05,
    0xED, 0xC4, 0x04,
    0xEF, 0xC3, 0x05,
    0xF1, 0xC5, 0x04,
    0xF4, 0x04, 0x03,
    0xF5, 0xC3, 0x04,
    0xF7, 0x84, 0x03,
    0xF9, 0x43, 0x03,
    0xFA, 0xC3, 0x03,
    0xFC, 0x41, 0x02,
    0xFD, 0x03, 0x02,
    0xFE, 0x41, 0x01,
    0xFE, 0xC1, 0x00,
};

BYTE code tGAMMA_TABLE_BLUE[] =
{
    0x00, 0x01, 0x03,
    0x01, 0x06, 0x05,
    0x03, 0xC5, 0x03,
    0x05, 0xC4, 0x04,
    0x07, 0xC6, 0x03,
    0x0A, 0x03, 0x04,
    0x0B, 0xC5, 0x04,
    0x0E, 0x02, 0x05,
    0x0F, 0xC3, 0x05,
    0x11, 0xC4, 0x05,
    0x14, 0x03, 0x05,
    0x16, 0x03, 0x04,
    0x17, 0xC3, 0x03,
    0x19, 0x45, 0x04,
    0x1B, 0x86, 0x03,
    0x1D, 0xC4, 0x04,
    0x1F, 0xC4, 0x04,
    0x21, 0xC3, 0x04,
    0x23, 0x84, 0x04,
    0x25, 0x84, 0x03,
    0x27, 0x44, 0x04,
    0x29, 0x44, 0x05,
    0x2B, 0x83, 0x03,
    0x2D, 0x05, 0x03,
    0x2F, 0x05, 0x03,
    0x31, 0x03, 0x05,
    0x33, 0x03, 0x05,
    0x35, 0x03, 0x05,
    0x37, 0x03, 0x05,
    0x39, 0x03, 0x05,
    0x3B, 0x03, 0x05,
    0x3D, 0x03, 0x04,
    0x3E, 0xC4, 0x04,
    0x40, 0xC3, 0x03,
    0x42, 0x44, 0x04,
    0x44, 0x44, 0x06,
    0x46, 0xC3, 0x03,
    0x48, 0x43, 0x06,
    0x4A, 0x84, 0x03,
    0x4C, 0x42, 0x05,
    0x4E, 0x05, 0x02,
    0x4F, 0xC5, 0x03,
    0x51, 0xC5, 0x04,
    0x54, 0x03, 0x03,
    0x55, 0x85, 0x04,
    0x57, 0xC5, 0x03,
    0x59, 0xC4, 0x03,
    0x5B, 0x85, 0x04,
    0x5D, 0xC3, 0x03,
    0x5F, 0x45, 0x04,
    0x61, 0x84, 0x03,
    0x63, 0x44, 0x03,
    0x65, 0x05, 0x04,
    0x67, 0x43, 0x04,
    0x69, 0x03, 0x05,
    0x6B, 0x04, 0x03,
    0x6C, 0xC4, 0x05,
    0x6F, 0x03, 0x04,
    0x70, 0xC5, 0x04,
    0x73, 0x03, 0x04,
    0x74, 0xC5, 0x03,
    0x76, 0xC4, 0x03,
    0x78, 0x85, 0x04,
    0x7A, 0xC3, 0x05,
    0x7C, 0xC4, 0x03,
    0x7E, 0x83, 0x04,
    0x80, 0x45, 0x03,
    0x82, 0x44, 0x05,
    0x84, 0x84, 0x03,
    0x86, 0x43, 0x04,
    0x88, 0x03, 0x06,
    0x8A, 0x43, 0x04,
    0x8C, 0x05, 0x04,
    0x8E, 0x43, 0x04,
    0x90, 0x04, 0x05,
    0x92, 0x44, 0x03,
    0x94, 0x03, 0x06,
    0x96, 0x43, 0x04,
    0x98, 0x04, 0x03,
    0x99, 0xC6, 0x03,
    0x9C, 0x04, 0x03,
    0x9D, 0xC4, 0x04,
    0x9F, 0xC4, 0x04,
    0xA1, 0xC4, 0x04,
    0xA3, 0xC6, 0x04,
    0xA6, 0x44, 0x04,
    0xA8, 0x44, 0x04,
    0xAA, 0x44, 0x04,
    0xAC, 0x44, 0x04,
    0xAE, 0x44, 0x04,
    0xB0, 0x44, 0x04,
    0xB2, 0x44, 0x04,
    0xB4, 0x44, 0x04,
    0xB6, 0x44, 0x04,
    0xB8, 0x44, 0x04,
    0xBA, 0x45, 0x04,
    0xBC, 0x84, 0x04,
    0xBE, 0x84, 0x05,
    0xC0, 0xC4, 0x04,
    0xC2, 0xC5, 0x04,
    0xC5, 0x03, 0x04,
    0xC6, 0xC5, 0x04,
    0xC9, 0x04, 0x04,
    0xCB, 0x05, 0x04,
    0xCD, 0x44, 0x05,
    0xCF, 0x84, 0x04,
    0xD1, 0x85, 0x04,
    0xD3, 0xC5, 0x03,
    0xD5, 0xC5, 0x04,
    0xD8, 0x05, 0x04,
    0xDA, 0x46, 0x04,
    0xDC, 0xC6, 0x03,
    0xDF, 0x04, 0x05,
    0xE1, 0x45, 0x05,
    0xE3, 0xC4, 0x04,
    0xE5, 0xC3, 0x06,
    0xE8, 0x04, 0x04,
    0xEA, 0x04, 0x06,
    0xEC, 0x85, 0x05,
    0xEF, 0x05, 0x03,
    0xF1, 0x04, 0x05,
    0xF3, 0x44, 0x04,
    0xF5, 0x44, 0x05,
    0xF7, 0x85, 0x04,
    0xF9, 0xC3, 0x03,
    0xFB, 0x43, 0x02,
    0xFC, 0x84, 0x06,
    0xFF, 0x00, 0x00,
};

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

BYTE code tLUTGAMMA_TABLE_RED[] =
{
    0x00, 0x00, 0x00, //R 0, 1
    0x00, 0x10, 0x02, //R 2, 3
    0x00, 0x40, 0x07, //R 4, 5
    0x00, 0xA0, 0x0E, //R 6, 7
    0x01, 0x20, 0x16, //R 8, 9
    0x01, 0xB0, 0x22, //R 10, 11
    0x02, 0x80, 0x2E, //R 12, 13
    0x03, 0x40, 0x39, //R 14, 15
    0x03, 0xE0, 0x44, //R 16, 17
    0x04, 0x80, 0x4E, //R 18, 19
    0x05, 0x40, 0x59, //R 20, 21
    0x05, 0xE0, 0x65, //R 22, 23
    0x06, 0x90, 0x6E, //R 24, 25
    0x07, 0x50, 0x78, //R 26, 27
    0x07, 0xD0, 0x81, //R 28, 29
    0x08, 0x60, 0x8B, //R 30, 31
    0x08, 0xF0, 0x95, //R 32, 33
    0x09, 0x90, 0x9E, //R 34, 35
    0x0A, 0x30, 0xA8, //R 36, 37
    0x0A, 0xC0, 0xB0, //R 38, 39
    0x0B, 0x30, 0xB8, //R 40, 41
    0x0B, 0xD0, 0xC0, //R 42, 43
    0x0C, 0x40, 0xC8, //R 44, 45
    0x0C, 0xC0, 0xD1, //R 46, 47
    0x0D, 0x50, 0xD8, //R 48, 49
    0x0D, 0xD0, 0xE0, //R 50, 51
    0x0E, 0x50, 0xE9, //R 52, 53
    0x0E, 0xC0, 0xF0, //R 54, 55
    0x0F, 0x30, 0xF7, //R 56, 57
    0x0F, 0xA0, 0xFD, //R 58, 59
    0x10, 0x01, 0x03, //R 60, 61
    0x10, 0x71, 0x0B, //R 62, 63
    0x10, 0xE1, 0x12, //R 64, 65
    0x11, 0x61, 0x18, //R 66, 67
    0x11, 0xB1, 0x1F, //R 68, 69
    0x12, 0x21, 0x26, //R 70, 71
    0x12, 0x91, 0x2D, //R 72, 73
    0x13, 0x11, 0x36, //R 74, 75
    0x13, 0x91, 0x3C, //R 76, 77
    0x14, 0x01, 0x43, //R 78, 79
    0x14, 0x71, 0x4B, //R 80, 81
    0x14, 0xE1, 0x52, //R 82, 83
    0x15, 0x61, 0x59, //R 84, 85
    0x15, 0xD1, 0x61, //R 86, 87
    0x16, 0x51, 0x68, //R 88, 89
    0x16, 0xD1, 0x71, //R 90, 91
    0x17, 0x51, 0x78, //R 92, 93
    0x17, 0xC1, 0x81, //R 94, 95
    0x18, 0x51, 0x89, //R 96, 97
    0x18, 0xD1, 0x92, //R 98, 99
    0x19, 0x61, 0x9A, //R 100, 101
    0x19, 0xE1, 0xA2, //R 102, 103
    0x1A, 0x71, 0xAB, //R 104, 105
    0x1B, 0x01, 0xB4, //R 106, 107
    0x1B, 0x81, 0xBD, //R 108, 109
    0x1C, 0x11, 0xC6, //R 110, 111
    0x1C, 0xB1, 0xCF, //R 112, 113
    0x1D, 0x41, 0xD8, //R 114, 115
    0x1D, 0xD1, 0xE2, //R 116, 117
    0x1E, 0x61, 0xEB, //R 118, 119
    0x1F, 0x01, 0xF4, //R 120, 121
    0x1F, 0x91, 0xFE, //R 122, 123
    0x20, 0x22, 0x07, //R 124, 125
    0x20, 0xB2, 0x11, //R 126, 127
    0x21, 0x52, 0x1A, //R 128, 129
    0x21, 0xE2, 0x23, //R 130, 131
    0x22, 0x82, 0x2D, //R 132, 133
    0x23, 0x22, 0x36, //R 134, 135
    0x23, 0xB2, 0x3F, //R 136, 137
    0x24, 0x42, 0x49, //R 138, 139
    0x24, 0xE2, 0x53, //R 140, 141
    0x25, 0x82, 0x5C, //R 142, 143
    0x26, 0x12, 0x66, //R 144, 145
    0x26, 0xB2, 0x70, //R 146, 147
    0x27, 0x42, 0x79, //R 148, 149
    0x27, 0xF2, 0x82, //R 150, 151
    0x28, 0x62, 0x8A, //R 152, 153
    0x28, 0xF2, 0x93, //R 154, 155
    0x29, 0x82, 0x9C, //R 156, 157
    0x2A, 0x02, 0xA4, //R 158, 159
    0x2A, 0x92, 0xAE, //R 160, 161
    0x2B, 0x22, 0xB5, //R 162, 163
    0x2B, 0x92, 0xBE, //R 164, 165
    0x2C, 0x22, 0xC6, //R 166, 167
    0x2C, 0xA2, 0xCE, //R 168, 169
    0x2D, 0x22, 0xD6, //R 170, 171
    0x2D, 0xA2, 0xDE, //R 172, 173
    0x2E, 0x22, 0xE6, //R 174, 175
    0x2E, 0xA2, 0xEE, //R 176, 177
    0x2F, 0x22, 0xF6, //R 178, 179
    0x2F, 0xA2, 0xFE, //R 180, 181
    0x30, 0x23, 0x06, //R 182, 183
    0x30, 0xA3, 0x0D, //R 184, 185
    0x31, 0x13, 0x15, //R 186, 187
    0x31, 0x93, 0x1D, //R 188, 189
    0x32, 0x13, 0x25, //R 190, 191
    0x32, 0x93, 0x2C, //R 192, 193
    0x33, 0x03, 0x34, //R 194, 195
    0x33, 0x83, 0x3C, //R 196, 197
    0x34, 0x03, 0x43, //R 198, 199
    0x34, 0x73, 0x4A, //R 200, 201
    0x34, 0xE3, 0x52, //R 202, 203
    0x35, 0x63, 0x59, //R 204, 205
    0x35, 0xD3, 0x61, //R 206, 207
    0x36, 0x43, 0x67, //R 208, 209
    0x36, 0xC3, 0x70, //R 210, 211
    0x37, 0x33, 0x76, //R 212, 213
    0x37, 0xB3, 0x7F, //R 214, 215
    0x38, 0x23, 0x86, //R 216, 217
    0x38, 0x93, 0x8D, //R 218, 219
    0x39, 0x13, 0x95, //R 220, 221
    0x39, 0x83, 0x9C, //R 222, 223
    0x39, 0xF3, 0xA3, //R 224, 225
    0x3A, 0x73, 0xAB, //R 226, 227
    0x3A, 0xF3, 0xB2, //R 228, 229
    0x3B, 0x63, 0xBA, //R 230, 231
    0x3B, 0xD3, 0xC1, //R 232, 233
    0x3C, 0x53, 0xC9, //R 234, 235
    0x3C, 0xD3, 0xD1, //R 236, 237
    0x3D, 0x53, 0xDA, //R 238, 239
    0x3D, 0xC3, 0xDF, //R 240, 241
    0x3E, 0x13, 0xE4, //R 242, 243
    0x3E, 0x63, 0xE9, //R 244, 245
    0x3E, 0xC3, 0xEE, //R 246, 247
    0x3F, 0x13, 0xF3, //R 248, 249
    0x3F, 0x63, 0xF9, //R 250, 251
    0x3F, 0x93, 0xFA, //R 252, 253
    0x3F, 0xB3, 0xFC, //R 254, 255
    0x3F, 0xF0,       //R 256
};

BYTE code tLUTGAMMA_TABLE_GREEN[] =
{
    0x00, 0x00, 0x00, //G 0, 1
    0x00, 0x10, 0x03, //G 2, 3
    0x00, 0x60, 0x0A, //G 4, 5
    0x00, 0xF0, 0x14, //G 6, 7
    0x01, 0x90, 0x20, //G 8, 9
    0x02, 0x60, 0x2D, //G 10, 11
    0x03, 0x20, 0x38, //G 12, 13
    0x03, 0xD0, 0x43, //G 14, 15
    0x04, 0x80, 0x4E, //G 16, 17
    0x05, 0x30, 0x58, //G 18, 19
    0x05, 0xE0, 0x63, //G 20, 21
    0x06, 0x80, 0x6D, //G 22, 23
    0x07, 0x20, 0x78, //G 24, 25
    0x07, 0xE0, 0x81, //G 26, 27
    0x08, 0x60, 0x8B, //G 28, 29
    0x08, 0xF0, 0x93, //G 30, 31
    0x09, 0x80, 0x9C, //G 32, 33
    0x0A, 0x10, 0xA5, //G 34, 35
    0x0A, 0xA0, 0xAE, //G 36, 37
    0x0B, 0x20, 0xB7, //G 38, 39
    0x0B, 0xB0, 0xBF, //G 40, 41
    0x0C, 0x30, 0xCA, //G 42, 43
    0x0C, 0xC0, 0xD1, //G 44, 45
    0x0D, 0x50, 0xD9, //G 46, 47
    0x0D, 0xD0, 0xE2, //G 48, 49
    0x0E, 0x60, 0xEA, //G 50, 51
    0x0E, 0xF0, 0xF3, //G 52, 53
    0x0F, 0x70, 0xFB, //G 54, 55
    0x0F, 0xE1, 0x01, //G 56, 57
    0x10, 0x41, 0x08, //G 58, 59
    0x10, 0xC1, 0x0F, //G 60, 61
    0x11, 0x21, 0x16, //G 62, 63
    0x11, 0x91, 0x1E, //G 64, 65
    0x12, 0x11, 0x24, //G 66, 67
    0x12, 0x81, 0x2B, //G 68, 69
    0x12, 0xF1, 0x32, //G 70, 71
    0x13, 0x61, 0x39, //G 72, 73
    0x13, 0xE1, 0x41, //G 74, 75
    0x14, 0x51, 0x49, //G 76, 77
    0x14, 0xC1, 0x51, //G 78, 79
    0x15, 0x41, 0x58, //G 80, 81
    0x15, 0xC1, 0x5F, //G 82, 83
    0x16, 0x41, 0x68, //G 84, 85
    0x16, 0xC1, 0x6F, //G 86, 87
    0x17, 0x31, 0x77, //G 88, 89
    0x17, 0xB1, 0x80, //G 90, 91
    0x18, 0x41, 0x88, //G 92, 93
    0x18, 0xC1, 0x90, //G 94, 95
    0x19, 0x41, 0x98, //G 96, 97
    0x19, 0xC1, 0xA0, //G 98, 99
    0x1A, 0x41, 0xA9, //G 100, 101
    0x1A, 0xD1, 0xB1, //G 102, 103
    0x1B, 0x51, 0xBA, //G 104, 105
    0x1B, 0xE1, 0xC2, //G 106, 107
    0x1C, 0x71, 0xCB, //G 108, 109
    0x1C, 0xF1, 0xD4, //G 110, 111
    0x1D, 0x81, 0xDD, //G 112, 113
    0x1E, 0x11, 0xE6, //G 114, 115
    0x1E, 0xA1, 0xEE, //G 116, 117
    0x1F, 0x21, 0xF7, //G 118, 119
    0x1F, 0xB1, 0xFF, //G 120, 121
    0x20, 0x62, 0x0C, //G 122, 123
    0x21, 0x22, 0x17, //G 124, 125
    0x21, 0xC2, 0x21, //G 126, 127
    0x22, 0x62, 0x2C, //G 128, 129
    0x23, 0x02, 0x34, //G 130, 131
    0x23, 0x92, 0x3E, //G 132, 133
    0x24, 0x32, 0x48, //G 134, 135
    0x24, 0xD2, 0x52, //G 136, 137
    0x25, 0x72, 0x5B, //G 138, 139
    0x26, 0x02, 0x66, //G 140, 141
    0x26, 0xB2, 0x70, //G 142, 143
    0x27, 0x52, 0x79, //G 144, 145
    0x27, 0xD2, 0x83, //G 146, 147
    0x28, 0x62, 0x8A, //G 148, 149
    0x29, 0x02, 0x94, //G 150, 151
    0x29, 0x82, 0x9D, //G 152, 153
    0x2A, 0x12, 0xA6, //G 154, 155
    0x2A, 0xA2, 0xAE, //G 156, 157
    0x2B, 0x32, 0xB6, //G 158, 159
    0x2B, 0xA2, 0xBF, //G 160, 161
    0x2C, 0x32, 0xC8, //G 162, 163
    0x2C, 0xC2, 0xD0, //G 164, 165
    0x2D, 0x42, 0xD8, //G 166, 167
    0x2D, 0xC2, 0xE1, //G 168, 169
    0x2E, 0x42, 0xE8, //G 170, 171
    0x2E, 0xD2, 0xF0, //G 172, 173
    0x2F, 0x42, 0xF8, //G 174, 175
    0x2F, 0xC2, 0xFF, //G 176, 177
    0x30, 0x33, 0x07, //G 178, 179
    0x30, 0xB3, 0x0E, //G 180, 181
    0x31, 0x23, 0x15, //G 182, 183
    0x31, 0x93, 0x1D, //G 184, 185
    0x32, 0x13, 0x25, //G 186, 187
    0x32, 0x83, 0x2C, //G 188, 189
    0x33, 0x13, 0x34, //G 190, 191
    0x33, 0x83, 0x3C, //G 192, 193
    0x34, 0x03, 0x44, //G 194, 195
    0x34, 0x73, 0x4B, //G 196, 197
    0x34, 0xE3, 0x52, //G 198, 199
    0x35, 0x63, 0x5A, //G 200, 201
    0x35, 0xE3, 0x62, //G 202, 203
    0x36, 0x53, 0x6A, //G 204, 205
    0x36, 0xE3, 0x72, //G 206, 207
    0x37, 0x53, 0x78, //G 208, 209
    0x37, 0xD3, 0x81, //G 210, 211
    0x38, 0x53, 0x89, //G 212, 213
    0x38, 0xC3, 0x8F, //G 214, 215
    0x39, 0x33, 0x96, //G 216, 217
    0x39, 0xA3, 0x9D, //G 218, 219
    0x3A, 0x03, 0xA4, //G 220, 221
    0x3A, 0x73, 0xAC, //G 222, 223
    0x3A, 0xE3, 0xB1, //G 224, 225
    0x3B, 0x43, 0xB7, //G 226, 227
    0x3B, 0xA3, 0xBD, //G 228, 229
    0x3C, 0x03, 0xC3, //G 230, 231
    0x3C, 0x73, 0xCA, //G 232, 233
    0x3C, 0xD3, 0xD0, //G 234, 235
    0x3D, 0x33, 0xD6, //G 236, 237
    0x3D, 0xA3, 0xDD, //G 238, 239
    0x3D, 0xF3, 0xE1, //G 240, 241
    0x3E, 0x33, 0xE5, //G 242, 243
    0x3E, 0x73, 0xEA, //G 244, 245
    0x3E, 0xC3, 0xEE, //G 246, 247
    0x3F, 0x03, 0xF3, //G 248, 249
    0x3F, 0x53, 0xF7, //G 250, 251
    0x3F, 0x93, 0xFA, //G 252, 253
    0x3F, 0xB3, 0xFC, //G 254, 255
    0x3F, 0xF0,       //G 256
};

BYTE code tLUTGAMMA_TABLE_BLUE[] =
{
    0x00, 0x00, 0x00, //B 0, 1
    0x00, 0x10, 0x02, //B 2, 3
    0x00, 0x40, 0x06, //B 4, 5
    0x00, 0xA0, 0x0D, //B 6, 7
    0x01, 0x10, 0x15, //B 8, 9
    0x01, 0x80, 0x1D, //B 10, 11
    0x02, 0x30, 0x28, //B 12, 13
    0x02, 0xD0, 0x32, //B 14, 15
    0x03, 0x80, 0x3C, //B 16, 17
    0x04, 0x10, 0x45, //B 18, 19
    0x04, 0xA0, 0x4F, //B 20, 21
    0x05, 0x40, 0x5A, //B 22, 23
    0x05, 0xE0, 0x63, //B 24, 25
    0x06, 0x80, 0x6C, //B 26, 27
    0x07, 0x20, 0x76, //B 28, 29
    0x07, 0xB0, 0x80, //B 30, 31
    0x08, 0x60, 0x8B, //B 32, 33
    0x09, 0x00, 0x94, //B 34, 35
    0x09, 0x80, 0x9C, //B 36, 37
    0x0A, 0x10, 0xA5, //B 38, 39
    0x0A, 0x90, 0xAE, //B 40, 41
    0x0B, 0x20, 0xB7, //B 42, 43
    0x0B, 0xB0, 0xBF, //B 44, 45
    0x0C, 0x30, 0xC7, //B 46, 47
    0x0C, 0xB0, 0xCF, //B 48, 49
    0x0D, 0x40, 0xD8, //B 50, 51
    0x0D, 0xC0, 0xE0, //B 52, 53
    0x0E, 0x40, 0xE8, //B 54, 55
    0x0E, 0xC0, 0xF0, //B 56, 57
    0x0F, 0x40, 0xF8, //B 58, 59
    0x0F, 0xC1, 0x00, //B 60, 61
    0x10, 0x51, 0x09, //B 62, 63
    0x10, 0xD1, 0x11, //B 64, 65
    0x11, 0x41, 0x18, //B 66, 67
    0x11, 0xC1, 0x20, //B 68, 69
    0x12, 0x41, 0x28, //B 70, 71
    0x12, 0xC1, 0x30, //B 72, 73
    0x13, 0x31, 0x36, //B 74, 75
    0x13, 0xA1, 0x3E, //B 76, 77
    0x14, 0x11, 0x45, //B 78, 79
    0x14, 0x91, 0x4C, //B 80, 81
    0x14, 0xF1, 0x53, //B 82, 83
    0x15, 0x81, 0x5B, //B 84, 85
    0x15, 0xE1, 0x63, //B 86, 87
    0x16, 0x71, 0x6B, //B 88, 89
    0x16, 0xF1, 0x72, //B 90, 91
    0x17, 0x61, 0x7A, //B 92, 93
    0x17, 0xE1, 0x82, //B 94, 95
    0x18, 0x51, 0x89, //B 96, 97
    0x18, 0xD1, 0x91, //B 98, 99
    0x19, 0x41, 0x98, //B 100, 101
    0x19, 0xC1, 0xA0, //B 102, 103
    0x1A, 0x51, 0xA9, //B 104, 105
    0x1A, 0xD1, 0xB1, //B 106, 107
    0x1B, 0x51, 0xB9, //B 108, 109
    0x1B, 0xD1, 0xC2, //B 110, 111
    0x1C, 0x61, 0xCA, //B 112, 113
    0x1C, 0xE1, 0xD3, //B 114, 115
    0x1D, 0x81, 0xDC, //B 116, 117
    0x1E, 0x11, 0xE5, //B 118, 119
    0x1E, 0xA1, 0xEE, //B 120, 121
    0x1F, 0x31, 0xF8, //B 122, 123
    0x1F, 0xD2, 0x02, //B 124, 125
    0x20, 0x62, 0x0C, //B 126, 127
    0x21, 0x12, 0x16, //B 128, 129
    0x21, 0xA2, 0x1F, //B 130, 131
    0x22, 0x42, 0x2A, //B 132, 133
    0x22, 0xE2, 0x34, //B 134, 135
    0x23, 0x82, 0x3E, //B 136, 137
    0x24, 0x22, 0x48, //B 138, 139
    0x24, 0xD2, 0x53, //B 140, 141
    0x25, 0x82, 0x5D, //B 142, 143
    0x26, 0x32, 0x67, //B 144, 145
    0x26, 0xC2, 0x72, //B 146, 147
    0x27, 0x62, 0x7D, //B 148, 149
    0x28, 0x12, 0x84, //B 150, 151
    0x28, 0x82, 0x8E, //B 152, 153
    0x29, 0x32, 0x97, //B 154, 155
    0x29, 0xD2, 0xA1, //B 156, 157
    0x2A, 0x52, 0xAA, //B 158, 159
    0x2A, 0xF2, 0xB4, //B 160, 161
    0x2B, 0x82, 0xBC, //B 162, 163
    0x2C, 0x12, 0xC5, //B 164, 165
    0x2C, 0xA2, 0xCE, //B 166, 167
    0x2D, 0x32, 0xD7, //B 168, 169
    0x2D, 0xB2, 0xDF, //B 170, 171
    0x2E, 0x42, 0xE8, //B 172, 173
    0x2E, 0xC2, 0xF0, //B 174, 175
    0x2F, 0x42, 0xF8, //B 176, 177
    0x2F, 0xC3, 0x00, //B 178, 179
    0x30, 0x43, 0x09, //B 180, 181
    0x30, 0xC3, 0x10, //B 182, 183
    0x31, 0x43, 0x18, //B 184, 185
    0x31, 0xC3, 0x1F, //B 186, 187
    0x32, 0x33, 0x27, //B 188, 189
    0x32, 0xA3, 0x2E, //B 190, 191
    0x33, 0x23, 0x36, //B 192, 193
    0x33, 0xA3, 0x3E, //B 194, 195
    0x34, 0x13, 0x44, //B 196, 197
    0x34, 0x83, 0x4C, //B 198, 199
    0x35, 0x03, 0x53, //B 200, 201
    0x35, 0x63, 0x5A, //B 202, 203
    0x35, 0xE3, 0x61, //B 204, 205
    0x36, 0x53, 0x68, //B 206, 207
    0x36, 0xC3, 0x6F, //B 208, 209
    0x37, 0x33, 0x76, //B 210, 211
    0x37, 0xA3, 0x7D, //B 212, 213
    0x38, 0x03, 0x84, //B 214, 215
    0x38, 0x83, 0x8B, //B 216, 217
    0x38, 0xF3, 0x92, //B 218, 219
    0x39, 0x53, 0x99, //B 220, 221
    0x39, 0xC3, 0xA0, //B 222, 223
    0x3A, 0x33, 0xA7, //B 224, 225
    0x3A, 0xA3, 0xAD, //B 226, 227
    0x3B, 0x03, 0xB3, //B 228, 229
    0x3B, 0x73, 0xBA, //B 230, 231
    0x3B, 0xD3, 0xC1, //B 232, 233
    0x3C, 0x53, 0xC7, //B 234, 235
    0x3C, 0xC3, 0xCF, //B 236, 237
    0x3D, 0x23, 0xD4, //B 238, 239
    0x3D, 0x63, 0xD9, //B 240, 241
    0x3D, 0xC3, 0xDE, //B 242, 243
    0x3E, 0x13, 0xE4, //B 244, 245
    0x3E, 0x73, 0xE9, //B 246, 247
    0x3E, 0xC3, 0xEF, //B 248, 249
    0x3F, 0x13, 0xF4, //B 250, 251
    0x3F, 0x73, 0xFA, //B 252, 253
    0x3F, 0xB3, 0xFC, //B 254, 255
    0x3F, 0xF0,       //B 256
};

#endif//#if(_SCALER_TYPE == _RTD2472D)

#endif//#if(_GAMMA_FUNCTION == _ON)



#else


extern BYTE code tDITHER_SEQ_TABLE_0[];
extern BYTE code tDITHER_TABLE_10_TO_6[];
extern BYTE code tDITHER_TABLE_10_TO_8_D_DOMAIN[];
extern BYTE code tDITHER_TEMPOFFSET_TABLE[];//Hudson add Temporal offset table setting 20080725

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
extern BYTE code tDITHER_TABLE_10_TO_8_I_DOMAIN[];
#endif


#if(_GAMMA_FUNCTION == _ON)
#if(_SCALER_TYPE == _RTD2472D)
extern BYTE code tGAMMA_TABLE_RED[];
extern BYTE code tGAMMA_TABLE_GREEN[];
extern BYTE code tGAMMA_TABLE_BLUE[];
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
extern BYTE code tLUTGAMMA_TABLE_RED[];    //20080422 +Sharon
extern BYTE code tLUTGAMMA_TABLE_GREEN[];
extern BYTE code tLUTGAMMA_TABLE_BLUE[];
#endif
#endif // End of #if(_GAMMA_FUNCTION == _ON)


#endif // End of #ifdef _ADJUST__


//----------------------------------------------------------------------------------------------------
// OD Table
//----------------------------------------------------------------------------------------------------

#if(_OD_SUPPORT == _ON)

#ifdef __MEMORY__

BYTE code tOD_TABLE_MIDDLE[] =
{
    0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, // ( 0)
    0x03, 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, // ( 1)
    0x04, 0x03, 0x00, 0xfe, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, // ( 2)
    0x06, 0x04, 0x03, 0x00, 0xfe, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, // ( 3)
    0x09, 0x06, 0x05, 0x03, 0x00, 0xfe, 0xff, 0xff, 0x00, 0xff, 0xfe, 0xfa, 0xfa, 0xfa, 0xfd, 0xfd, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfd, 0xfd, 0xfa, 0xfa, 0xfa, 0xfd, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, // ( 4)
    0x0b, 0x09, 0x06, 0x04, 0x03, 0x00, 0xfe, 0xff, 0x00, 0xfd, 0xfd, 0xfd, 0xfd, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, // ( 5)
    0x11, 0x0b, 0x07, 0x05, 0x04, 0x02, 0x00, 0xfe, 0xff, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf5, 0xf7, 0xf2, 0xf0, // ( 6)
    0x15, 0x11, 0x0b, 0x06, 0x06, 0x03, 0x02, 0x00, 0xfd, 0xfd, 0xfb, 0xfb, 0xfb, 0xfb, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf5, 0xf5, 0xf0, 0xf0, 0xeb, 0xe8, // ( 7)
    0x17, 0x15, 0x0f, 0x0c, 0x09, 0x06, 0x04, 0x03, 0x00, 0xfd, 0xfd, 0xfa, 0xfa, 0xfa, 0xfb, 0xfa, 0xf4, 0xf4, 0xf4, 0xf4, 0xf4, 0xf4, 0xf4, 0xf4, 0xf4, 0xf3, 0xf1, 0xf4, 0xed, 0xec, 0xe7, 0xe7, 0xe4, // ( 8)
    0x19, 0x17, 0x12, 0x0e, 0x0b, 0x09, 0x06, 0x04, 0x02, 0x00, 0xff, 0xfd, 0xfc, 0xfa, 0xfa, 0xf8, 0xf8, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf1, 0xf0, 0xee, 0xee, 0xeb, 0xeb, 0xeb, 0xe4, 0xe2, 0xdf, // ( 9)
    0x1b, 0x19, 0x14, 0x11, 0x0d, 0x0b, 0x08, 0x06, 0x03, 0x02, 0x00, 0xff, 0xfd, 0xfa, 0xfa, 0xf8, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf1, 0xf0, 0xee, 0xee, 0xeb, 0xe9, 0xec, 0xe4, 0xe4, 0xdd, 0xdd, 0xda, // (10)
    0x1d, 0x1b, 0x17, 0x13, 0x10, 0x0d, 0x0b, 0x08, 0x06, 0x04, 0x03, 0x00, 0xfe, 0xfd, 0xfa, 0xfa, 0xf3, 0xf3, 0xf3, 0xf3, 0xf1, 0xf0, 0xee, 0xec, 0xec, 0xe9, 0xe8, 0xe8, 0xe4, 0xdd, 0xdc, 0xdc, 0xd9, // (11)
    0x21, 0x1c, 0x18, 0x16, 0x12, 0x10, 0x0d, 0x0b, 0x08, 0x07, 0x04, 0x03, 0x00, 0xfe, 0xfd, 0xfa, 0xf8, 0xf3, 0xf3, 0xf3, 0xf1, 0xf0, 0xee, 0xeb, 0xe9, 0xe9, 0xe5, 0xe4, 0xe2, 0xdc, 0xd6, 0xd8, 0xd4, // (12)
    0x24, 0x20, 0x1a, 0x19, 0x15, 0x12, 0x11, 0x0e, 0x0c, 0x09, 0x07, 0x06, 0x03, 0x00, 0xfe, 0xfc, 0xfa, 0xf8, 0xf3, 0xf3, 0xf3, 0xf0, 0xee, 0xeb, 0xe9, 0xe5, 0xe5, 0xe4, 0xe1, 0xd6, 0xd6, 0xd4, 0xd0, // (13)
    0x27, 0x21, 0x1c, 0x1c, 0x1b, 0x17, 0x14, 0x11, 0x0f, 0x0c, 0x0a, 0x08, 0x05, 0x03, 0x00, 0xfd, 0xfc, 0xfa, 0xf8, 0xf3, 0xf3, 0xf1, 0xef, 0xec, 0xe9, 0xe5, 0xe3, 0xe3, 0xe1, 0xd6, 0xd6, 0xd3, 0xce, // (14)
    0x29, 0x24, 0x1e, 0x1e, 0x1e, 0x1b, 0x18, 0x13, 0x11, 0x11, 0x0d, 0x0b, 0x09, 0x06, 0x03, 0x00, 0xfd, 0xfb, 0xf9, 0xf8, 0xf3, 0xf3, 0xf0, 0xee, 0xe9, 0xe5, 0xe3, 0xe2, 0xdf, 0xd6, 0xd5, 0xd3, 0xce, // (15)
    0x2b, 0x25, 0x21, 0x20, 0x20, 0x20, 0x1e, 0x16, 0x16, 0x16, 0x12, 0x10, 0x0d, 0x0b, 0x07, 0x03, 0x00, 0xfd, 0xfc, 0xf9, 0xf7, 0xf3, 0xf1, 0xee, 0xeb, 0xe5, 0xe3, 0xe2, 0xdf, 0xd5, 0xd5, 0xd1, 0xcc, // (16)
    0x2c, 0x27, 0x23, 0x22, 0x22, 0x22, 0x1e, 0x18, 0x18, 0x18, 0x17, 0x14, 0x11, 0x0d, 0x0a, 0x07, 0x06, 0x00, 0xfd, 0xfc, 0xf7, 0xf7, 0xf2, 0xf0, 0xec, 0xe8, 0xe2, 0xe1, 0xdf, 0xd6, 0xd5, 0xd1, 0xcc, // (17)
    0x2f, 0x2b, 0x25, 0x25, 0x25, 0x23, 0x21, 0x1b, 0x1b, 0x1b, 0x1b, 0x18, 0x14, 0x12, 0x0e, 0x0b, 0x08, 0x03, 0x00, 0xfd, 0xfa, 0xf7, 0xf3, 0xf1, 0xec, 0xe8, 0xe2, 0xe1, 0xde, 0xd6, 0xd6, 0xd0, 0xcb, // (18)
    0x31, 0x2d, 0x27, 0x25, 0x25, 0x22, 0x20, 0x1d, 0x1d, 0x1d, 0x1e, 0x1b, 0x18, 0x15, 0x12, 0x10, 0x0b, 0x08, 0x05, 0x00, 0xfd, 0xfa, 0xf7, 0xf2, 0xee, 0xe8, 0xe2, 0xe1, 0xde, 0xd7, 0xd6, 0xd1, 0xcc, // (19)
    0x32, 0x2e, 0x27, 0x25, 0x25, 0x23, 0x21, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1b, 0x18, 0x15, 0x12, 0x0f, 0x0c, 0x08, 0x04, 0x00, 0xfd, 0xfa, 0xf5, 0xf0, 0xeb, 0xe5, 0xe2, 0xde, 0xd7, 0xd6, 0xd1, 0xcc, // (20)
    0x32, 0x2b, 0x27, 0x25, 0x25, 0x24, 0x23, 0x1f, 0x1f, 0x1f, 0x1f, 0x1e, 0x1b, 0x18, 0x17, 0x14, 0x11, 0x0e, 0x0b, 0x09, 0x04, 0x00, 0xfd, 0xfd, 0xf2, 0xee, 0xe8, 0xe2, 0xdf, 0xd9, 0xd7, 0xd2, 0xce, // (21)
    0x2e, 0x27, 0x26, 0x25, 0x25, 0x25, 0x23, 0x21, 0x21, 0x21, 0x1f, 0x1e, 0x1b, 0x19, 0x18, 0x15, 0x12, 0x0e, 0x0f, 0x0b, 0x08, 0x03, 0x00, 0xfc, 0xf7, 0xf1, 0xe9, 0xe5, 0xdf, 0xd7, 0xd7, 0xd3, 0xd0, // (22)
    0x2b, 0x26, 0x24, 0x24, 0x25, 0x25, 0x24, 0x20, 0x20, 0x20, 0x20, 0x1e, 0x1c, 0x1b, 0x18, 0x17, 0x13, 0x0e, 0x0d, 0x0d, 0x0a, 0x08, 0x05, 0x00, 0xfd, 0xf4, 0xee, 0xe6, 0xe2, 0xdb, 0xd9, 0xd7, 0xd2, // (23)
    0x29, 0x25, 0x24, 0x23, 0x24, 0x24, 0x23, 0x20, 0x20, 0x20, 0x20, 0x1e, 0x1e, 0x1b, 0x19, 0x18, 0x15, 0x12, 0x10, 0x0f, 0x0d, 0x0b, 0x08, 0x06, 0x00, 0xfa, 0xf3, 0xee, 0xe1, 0xdc, 0xdc, 0xd9, 0xd4, // (24)
    0x26, 0x23, 0x22, 0x22, 0x22, 0x22, 0x21, 0x1f, 0x1f, 0x1f, 0x1e, 0x1e, 0x1c, 0x1b, 0x1b, 0x19, 0x16, 0x14, 0x13, 0x12, 0x0f, 0x0e, 0x0c, 0x09, 0x05, 0x00, 0xfa, 0xf3, 0xeb, 0xdf, 0xdf, 0xdc, 0xd9, // (25)
    0x24, 0x21, 0x21, 0x20, 0x20, 0x1f, 0x1f, 0x1d, 0x1d, 0x1d, 0x1d, 0x1d, 0x1b, 0x1a, 0x19, 0x18, 0x17, 0x15, 0x14, 0x13, 0x12, 0x0f, 0x0d, 0x0c, 0x09, 0x06, 0x00, 0xfa, 0xf3, 0xe5, 0xe4, 0xe0, 0xdd, // (26)
    0x21, 0x1e, 0x1c, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1a, 0x1a, 0x19, 0x18, 0x17, 0x15, 0x13, 0x12, 0x11, 0x0f, 0x0e, 0x0d, 0x0a, 0x08, 0x06, 0x00, 0xf9, 0xee, 0xe9, 0xe4, 0xe1, // (27)
    0x1b, 0x19, 0x17, 0x19, 0x19, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x15, 0x17, 0x17, 0x17, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0e, 0x0d, 0x0c, 0x0a, 0x09, 0x09, 0x06, 0x00, 0xfa, 0xf0, 0xeb, 0xe6, // (28)
    0x15, 0x14, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x10, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x10, 0x10, 0x10, 0x0f, 0x0e, 0x0d, 0x0c, 0x0c, 0x0a, 0x09, 0x09, 0x09, 0x07, 0x00, 0xf7, 0xf0, 0xee, // (29)
    0x11, 0x0d, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0a, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0a, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0a, 0x09, 0x09, 0x09, 0x08, 0x07, 0x00, 0xf6, 0xf1, // (30)
    0x0b, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0xf7, // (31)
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, // (32)
};

code BYTE *tOD_TABLE[] =
{
    tOD_TABLE_MIDDLE,
};

#else

extern code BYTE *tOD_TABLE[];

#endif // End of #ifdef __MEMORY__

#endif // End of #if(_OD_SUPPORT == _ON)

#endif  // End of #if(_PANEL_TYPE == _AU_LVDS_24_WUXGA)