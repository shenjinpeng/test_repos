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
// ID Code      : Osd.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//--------------------------------------------------
// Definitions of Font Start Position
//--------------------------------------------------
#define _OSD_FONT_START_POSITION                (1139)
#define _OSD_FONT_START_POSITION_ROTATE         (0)


//--------------------------------------------------
// Definitions of Clock Settings Used by COsdFxGetAdcClockRange()
//--------------------------------------------------
#define _CLOCK_BIAS                             (50)
#define _GET_CLOCKRANGE_MAX                     (0)
#define _GET_CLOCKRANGE_MIN                     (1)


//--------------------------------------------------
// Definitions of Hor. Position Settings Used by COsdFxGetHPositionRange()
//--------------------------------------------------
#define _HPOSITION_BIAS                         ((g_usHStartBias >= _IHS_START_BIAS) ? _IHS_START_BIAS : g_usHStartBias)

#define _GET_HPOSITIONRANGE_MAX                 (0)
#define _GET_HPOSITIONRANGE_MIN                 (1)


//--------------------------------------------------
// Definitions of Ver. Position Settings Used by COsdFxGetVPositionRange()
//--------------------------------------------------
#define _VPOSITION_BIAS                         (g_ucVStartBias - abs(stModeInfo.IVStartPos - stModeUserCenterData.CenterVPos))

#define _GET_VPOSITIONRANGE_MAX                 (0)
#define _GET_VPOSITIONRANGE_MIN                 (1)


//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#define _CONTRAST_MAX                           (178)
#define _CONTRAST_MIN                           (78)


//--------------------------------------------------
// Definitions of Backlight Range
//--------------------------------------------------
#define _BACKLIGHT_MAX                          (255)
#define _BACKLIGHT_MIN                          (0)


//--------------------------------------------------
// Definitions of OSD Position
//--------------------------------------------------
#define _OSD_HPOSITION_RANGE                    (200)
#define _OSD_VPOSITION_RANGE                    (200)

// V016 System Patch Note (1) Modify 20100729 Start
// Patch Reason : Modify OSD Set position and Draw Window Function
/*
#define _OSD_HPOSITION_OFFSET                   (8)
#define _OSD_VPOSITION_OFFSET                   (5)
*/
#define _OSD_HPOSITION_OFFSET                   10
#define _OSD_VPOSITION_OFFSET                   4
// V016 System Patch Note (1) Modify 20100729 End

//--------------------------------------------------
// Definitions of OSD Show Number Function Used by COsdFxShowNumber()
//--------------------------------------------------
#define _ALIGN_LEFT                             (0)
#define _ALIGN_RIGHT                            (1)

#define _FORCE_SHOW_NUMBER_OFF                  (0 << 1)
#define _FORCE_SHOW_NUMBER_ON                   (1 << 1)

#define _SHOW_1                                 (0 << 4)
#define _SHOW_2                                 (1 << 4)
#define _SHOW_3                                 (2 << 4)
#define _SHOW_4                                 (3 << 4)
#define _SHOW_5                                 (4 << 4)


//--------------------------------------------------
// Definitions of OSD Slider Function Used by COsdFxSlider()
//--------------------------------------------------
#define _SLIDER_RESOLUTION                      (7)
#define _SLIDER_START_ADDRESS                   (0x54)
#define _L_BAR                                  (0x0f)
#define _0_BAR                                  (0x00 + _SLIDER_START_ADDRESS)      // Empty Icon
#define _1_BAR                                  (0x01 + _SLIDER_START_ADDRESS)
#define _2_BAR                                  (0x02 + _SLIDER_START_ADDRESS)
#define _3_BAR                                  (0x03 + _SLIDER_START_ADDRESS)
#define _4_BAR                                  (0x04 + _SLIDER_START_ADDRESS)
#define _5_BAR                                  (0x05 + _SLIDER_START_ADDRESS)
#define _6_BAR                                  (0x06 + _SLIDER_START_ADDRESS)      // Full Icon
#define _LEFT_ICON                           (0x07 + _SLIDER_START_ADDRESS) 
#define _RIGHT_ICON                         (0x08 + _SLIDER_START_ADDRESS) 
#define _R_BAR                                  (0x27)


//--------------------------------------------------
// Definitions of Checking Max or Min Value Used by COsdFxDetOverRange()
//--------------------------------------------------
#define _DET_OVERRANGE_MAX                      (0)
#define _DET_OVERRANGE_MIN                      (1)

//--------------------------------------------------
// Definitions of Saturation Range (Real Value)
//--------------------------------------------------
#define _SATURATION_MAX                         (100)  //do not change
#define _SATURATION_MIN                         (0)

//--------------------------------------------------
// Definitions of Hue Range (Real Value)
//--------------------------------------------------
#define _HUE_MAX                                (254)  //do not chante
#define _HUE_MIN                                (0)

//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#if(_DDCCI_SUPPORT == _ON)
#define _COLORTEMP_USER_MAX                  255//   128
#define _COLORTEMP_USER_MIN                  0   //38
#endif

// V015 VGA Patch Note (12) Modify 20100625 Start
// Patch Reason : Modify OSD Reslotion show type for vedio timing.
//--------------------------------------------------
// Definitions of Interlace or Progress Timing Flag
//--------------------------------------------------
#define _PROGRESS_TIMING                     0
#define _INTERLACE_TIMING                    1
// V015 VGA Patch Note (12) Modify 20100625 End

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of OSD Event Message
//--------------------------------------------------
enum OSDEvenMassage
{
    _NONE_MSG = 0,
    _SHOW_NOSIGNAL_MSG,
    _SHOW_NOCABLE_MSG,
    _SHOW_NOSUPPORT_MSG,
    _SAVE_EE_MODEUSERDATA_MSG,
    _SAVE_EE_SYSTEMDATA_MSG,
    _SAVE_EE_OSDUSERDATA_MSG,
    _SAVE_EE_OSDRESERVEDATA_MSG,
    _SAVE_EE_ADCDATA_MSG,
    _SAVE_EE_COLORPROC0_MSG,
    _SAVE_EE_COLORPROC1_MSG,
    _ENTER_FACTORY_MODE_MSG,
    _CHANGE_SOURCE_MSG,
    _DO_AUTO_CONFIG,
    _SHOW_TIMINGINPUT_MSG,
    _SAVE_LSLUMIDATA_MSG,
    _SAVE_PWMLUMIDATA_MSG,
};


//--------------------------------------------------
// Definitions of Different OSD Map Type
//--------------------------------------------------
#define _OSD_MAP0                               0
#define _OSD_MAP1                               1
#define _OSD_MAP2                               2
#define _OSD_MAP3                               3
#define _OSD_MAP4                               4
#define _OSD_MAP5                               5
#define _OSD_MAP6                               6


//--------------------------------------------------
// Definations of Write Byte
//--------------------------------------------------
#define _WRITE_BYTE0                            0
#define _WRITE_BYTE1                            1
#define _WRITE_BYTE2                            2
#define _WRITE_BYTEALL                          3


//--------------------------------------------------
// Definations of OSD Function
//--------------------------------------------------
#define _EXT_                                   0xfc
#define _REPEAT_                                0xfd
#define _NEXT_                                  0xfe
#define _END_                                   0xff


//--------------------------------------------------
// Definitions of Vivid Color
//--------------------------------------------------
#if(_VIVID_COLOR_FUCTION == _ON)

#define _VIVID_WINDOW_SIZE_DISABLE              0
#define _VIVID_WINDOW_SIZE_FULL                 1
#define _VIVID_WINDOW_SIZE_DEMO                 2
#define _VIVID_WINDOW_SIZE_USER                 3

#define _VIVID_WINDOW_H_POSITION_MAX            (stDisplayInfo.DHWidth - stOsdUserData.VividWinHWidth)
#define _VIVID_WINDOW_H_POSITION_MIN            0
#define _VIVID_WINDOW_V_POSITION_MAX            (stDisplayInfo.DVHeight - stOsdUserData.VividWinVHeight)
#define _VIVID_WINDOW_V_POSITION_MIN            0
#define _VIVID_WINDOW_H_WIDTH_MAX               (stDisplayInfo.DHWidth - stOsdUserData.VividWinHPos)
#define _VIVID_WINDOW_H_WIDTH_MIN               1
#define _VIVID_WINDOW_V_HEIGHT_MAX              (stDisplayInfo.DVHeight - stOsdUserData.VividWinVPos)
#define _VIVID_WINDOW_V_HEIGHT_MIN              1

#define _VIVID_DCC_DISABLE                      0
#define _VIVID_DCC_MOVIE                        1
#define _VIVID_DCC_PHOTO                        2
#define _VIVID_DCC_GAME                         3

#define _VIVID_ICM_DISABLE                      0
#define _VIVID_ICM_MOVIE                        1
#define _VIVID_ICM_PHOTO                        2
#define _VIVID_ICM_GAME                         3
#define _VIVID_ICM_USER                         4

#define _VIVID_BRIGHTNESS_MAX                   255
#define _VIVID_BRIGHTNESS_MIN                   0
#define _VIVID_CONTRAST_MAX                     255
#define _VIVID_CONTRAST_MIN                     0
#define _VIVID_PEAKING_MAX                      126
#define _VIVID_PEAKING_MIN                      0

#define _ICM_CM0                                _BIT4
#define _ICM_CM1                                _BIT3
#define _ICM_CM2                                _BIT2
#define _ICM_CM3                                _BIT1
#define _ICM_CM4                                _BIT0
#define _ICM_CM5                                _BIT7 //

#define _ICM_RED                                0
#define _ICM_GREEN                              1
#define _ICM_BLUE                               2

#define _ICM_RED_HUE_MAX                        16
#define _ICM_RED_HUE_MIN                        0
#define _ICM_RED_SAT_MAX                        16
#define _ICM_RED_SAT_MIN                        0
#define _ICM_GREEN_HUE_MAX                      16
#define _ICM_GREEN_HUE_MIN                      0
#define _ICM_GREEN_SAT_MAX                      16
#define _ICM_GREEN_SAT_MIN                      0
#define _ICM_BLUE_HUE_MAX                       16
#define _ICM_BLUE_HUE_MIN                       0
#define _ICM_BLUE_SAT_MAX                       16
#define _ICM_BLUE_SAT_MIN                       0

#endif

//--------------------------------------------------
// Definitions of Language
//--------------------------------------------------
enum OSDLanguageDef
{
    _ENGLISH = 0,
    _CHINESE_S,
    _CHINESE_T,
    _FRENCH,
    _GERMAN,
    _SPANISH,
    _JAPAN,

    _LANGUAGE_AMOUNT
};

//--------------------------------------------------
// Definitions of Color Temperature
//--------------------------------------------------
enum OSDColortemptureDef
{
    _CT_9300 = 0,
    _CT_6500,
    _CT_5800,
    _CT_SRGB,
    _CT_USER,
    _CT_COLORTEMP_AMOUNT
};


//--------------------------------------------------
// Definitions of Color Palette
//--------------------------------------------------

enum OSDColorPaletteDef
{
    _CP_BACKGROUND = 0,
    _CP_BLACK = 0,
    _CP_WHITE,
    _CP_RED,
    _CP_GREEN,
    _CP_BLUE,
    _CP_YELLOW,
    _CP_GRAY,
    _CP_DARKBLUE,
    _CP_LIGHTBLUE,
    _CP_SELECTBOTTOM,
    _CP_PINK,
    _CP_COLOR11,
    _CP_COLOR12,
    _CP_COLOR13,
    _CP_COLOR14,
    _CP_COLOR15
};

//--------------------------------------------------
// Char Alias
//--------------------------------------------------
enum OSDFontDef
{
    ___ = 0x00,

    _0_,
    _1_,
    _2_,
    _3_,
    _4_,
    _5_,
    _6_,
    _7_,
    _8_,
    _9_,

    _A_ = 0x10,
    _B_,
    _C_,
    _D_,
    _E_,
    _F_,
    _G_,
    _H_,
    _I_,
    _J_,
    _K_,
    _L_,
    _M_,
    _N_,
    _O_,
    _P_,
    _Q_,
    _R_,
    _S_,
    _T_,
    _U_,
    _V_,
    _W_,
    _X_,
    _Y_,
    _Z_,

    _a_ = 0x30,
    _b_,
    _c_,
    _d_,
    _e_,
    _f_,
    _g_,
    _h_,
    _i_,
    _j_,
    _k_,
    _l_,
    _m_,
    _n_,
    _o_,
    _p_,
    _q_,
    _r_,
    _s_,
    _t_,
    _u_,
    _v_,
    _w_,
    _x_,
    _y_,
    _z_

};



//----------------------------------------------------------------------------------------------------

#ifdef __REALTEK_OSD__

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CWakeUpShowSource();

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE idata ucOsdState = 0;
BYTE idata ucOsdEventMsg = 0;
BYTE idata ucOsdMap = 0;
BYTE idata GCMode =0;//adam20110620
BYTE idata bData = 0;//sjp20110726
#else

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CWakeUpShowSource();

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE idata ucOsdState;
extern BYTE idata ucOsdEventMsg;
extern BYTE idata ucOsdMap;
extern BYTE idata GCMode;//adam20110620
extern BYTE idata bData;//sjp 20110726
#endif


//--------------------------------------------------
// Macro of Volume Mute Status
//--------------------------------------------------
#define GET_VOLUME_MUTE_STATUS()                ((bit)(stOsdUserData.OsdSettingFlag & _BIT0))
#define SET_VOLUME_MUTE_STATUS()                (stOsdUserData.OsdSettingFlag |= _BIT0)
#define CLR_VOLUME_MUTE_STATUS()                (stOsdUserData.OsdSettingFlag &= ~_BIT0)

//--------------------------------------------------
// Macro of Vivid Color Window Size Status
//--------------------------------------------------
#define GET_WINDOW_SIZE()                       ((stOsdUserData.VividFlag & (_BIT0 | _BIT1)) >> 0)
#define SET_WINDOW_SIZE(x)                      (stOsdUserData.VividFlag = ((stOsdUserData.VividFlag & ~(_BIT0 | _BIT1)) | (x << 0)))


//--------------------------------------------------
// Macro of Vivid Color DCC Status
//--------------------------------------------------
#define GET_DCC_MODE()                          ((stOsdUserData.VividFlag & (_BIT2 | _BIT3 | _BIT4)) >> 2)
#define SET_DCC_MODE(x)                         (stOsdUserData.VividFlag = ((stOsdUserData.VividFlag & ~(_BIT2 | _BIT3 | _BIT4)) | (x << 2)))


//--------------------------------------------------
// Macro of Vivid Color DCC Status
//--------------------------------------------------
#define GET_ICM_MODE()                          ((stOsdUserData.VividFlag & (_BIT5 | _BIT6 | _BIT7)) >> 5)
#define SET_ICM_MODE(x)                         (stOsdUserData.VividFlag = ((stOsdUserData.VividFlag & ~(_BIT5 | _BIT6 | _BIT7)) | (x << 5)))


//--------------------------------------------------
// Macro of OSD
//--------------------------------------------------
#define FONTBYTE0(x)                            HIBYTE(0x1000 | x),LOBYTE(0x1000 | x)
#define FONTBYTE1(x)                            HIBYTE(0x5000 | x),LOBYTE(0x5000 | x)
#define FONTBYTE2(x)                            HIBYTE(0x9000 | x),LOBYTE(0x9000 | x)
#define FONTALLBYTE(x)                          HIBYTE(0xD000 | x),LOBYTE(0xD000 | x)
#define WINDOWBYTE0(x)                          HIBYTE(0x0000 | x),LOBYTE(0x0000 | x)
#define WINDOWBYTE1(x)                          HIBYTE(0x4000 | x),LOBYTE(0x4000 | x)
#define WINDOWBYTE2(x)                          HIBYTE(0x8000 | x),LOBYTE(0x8000 | x)
#define WINDOWALLBYTE(x)                        HIBYTE(0xC000 | x),LOBYTE(0xC000 | x)
#define FRAMEBYTE0(x)                           WINDOWBYTE0(x)
#define FRAMEBYTE1(x)                           WINDOWBYTE1(x)
#define FRAMEBYTE2(x)                           WINDOWBYTE2(x)
#define FRAMEALLBYTE(x)                         WINDOWALLBYTE(x)
#define WINNO(x)                                x
#define ROW(x)                                  x
#define COL(x)                                  x
#define WIDTH(x)                                x
#define HEIGHT(x)                               x
#define LENGTH(x)                               x
#define FGCOLOR(x)                              x
#define BGCOLOR(x)                              x
#define COLOR00(x)                              x
#define COLOR01(x)                              x
#define COLOR10(x)                              x
#define COLOR11(x)                              x
#define XSTART(x)                               x
#define YSTART(x)                               x
#define XEND(x)                                 x
#define YEND(x)                                 x

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
//--------------------------------------------------
// Macro of Source Search Auto
//--------------------------------------------------
#define GET_SOURCE_SEARCH_AUTO()                  ((bit)(stOsdUserData.OsdManagementFlag & _BIT0))
#define SET_SOURCE_SEARCH_AUTO()                  (stOsdUserData.OsdManagementFlag |= _BIT0)
#define CLR_SOURCE_SEARCH_AUTO()                  (stOsdUserData.OsdManagementFlag &= ~_BIT0)
#endif

//--------------------------------------------------
// Definitions of OSD Flow
//--------------------------------------------------
typedef enum
{
    _MENU_NONE = 0,
    _MENU_DICOM_SETTING,
    _MENU_GAMMA_SETTING,
    _MENU_BRIGHTNESS_SETTING,
    _MENU_CONTRAST_SETTING,
     _MENU_SIGNAL_SWITCH,
   
//#if(_AUDIO_SUPPORT == _ON)
    _MENU_AUTO_ADJUST_SETTING,
//#endif

 //   _MENU_SPECIAL_FUCTION,
    _MENU_FACTORY_RESET,

#if(_DDCCI_SUPPORT == _ON)
    _MENU_DDCCI,
#endif

    _MENU_SUB_DICOM,
    _MENU_SUB_GAMMA,
    _MENU_SUB_BRIGHTNESS,
    _MENU_SUB_CONTRAST,//NO NEED
    _MENU_SIGNAL_SELECT,
    _MENU_SUB_AUTO_ADJUST,
    _MENU_SUB_FACTORY_RESET,
    _MENU_COLOR_ADJ,
    _MENU_SUB_ADJ_R,
    _MENU_SUB_ADJ_G,
    _MENU_SUB_ADJ_B,
    _MENU_ADJ_R,
    _MENU_ADJ_G,
    _MENU_ADJ_B,
    _MENU_COLOR_TEMP,
    _MENU_SUB_TEMP_COLOR9300,
    _MENU_SUB_TEMP_COLOR6500,
    _MENU_SUB_TEMP_COLOR5800,
    _MENU_SUB_TEMP_SRGB,
    _MENU_SUB_TEMP_USER,

#if(_DCR_MODE != _DCR_TYPE_OFF)
    _MENU_COLOR_DCR,
#endif

    _MENU_CLOCK,
    _MENU_SUB_CLOCK,
    _MENU_PHASE,
    _MENU_SUB_PHASE,
    _MENU_SHARPNESS,
    _MENU_SUB_SHARPNESS0,
    _MENU_SUB_SHARPNESS1,
    _MENU_SUB_SHARPNESS2,
    _MENU_SUB_SHARPNESS3,
    _MENU_SUB_SHARPNESS4,
    _MENU_HPOSITION,
    _MENU_SUB_H_POS,
    _MENU_VPOSITION,
    _MENU_SUB_V_POS,

#if(_OD_SUPPORT == _ON)
    _MENU_OD,
    _MENU_SUB_OD,
#endif

    _MENU_OSD_H_POS,
    _MENU_SUB_OSD_H_POS,
    _MENU_OSD_V_POS,
    _MENU_SUB_OSD_V_POS,
    _MENU_OSD_TIME,
    _MENU_SUB_OSD_TIME,
    _MENU_OSD_LANGUAGE,
    _MENU_SUB_ENG,
    _MENU_SUB_FRAN,
    _MENU_SUB_DEUT,
    _MENU_SUB_ESPA,
    _MENU_SUB_CHI,
    _MENU_SUB_SIMPLE_CHI,
    _MENU_SUB_JAP,

    _MENU_SIGNAL_DVI,
    _MENU_SIGNAL_HDMI,
    _MENU_SIGNAL_DISPLAYPORT,

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    _MENU_SIGNAL_AUTOSEARCH,
#endif

#if(_AUDIO_SUPPORT == _ON)
    _MENU_VOLUME,
    _MENU_SUB_VOLUME,
    _MENU_MUTE,
#endif

#if(_DDCCI_SUPPORT == _ON)
   _MENU_DDCCIONOFF,
#endif

#if(_VIVID_COLOR_FUCTION == _ON)
    _MENU_VIVID_COLOR,
    _MENU_COLOR_WINODW_SIZE,
    _MENU_COLOR_WINODW_SIZE_DISABLE,
    _MENU_COLOR_WINODW_SIZE_FULL,
    _MENU_COLOR_WINODW_SIZE_DEMO,
    _MENU_COLOR_WINODW_SIZE_USER,
    _MENU_COLOR_WINODW_SIZE_USER_HPOS,
    _MENU_COLOR_WINODW_SIZE_USER_HPOS_ADJ,
    _MENU_COLOR_WINODW_SIZE_USER_VPOS,
    _MENU_COLOR_WINODW_SIZE_USER_VPOS_ADJ,
    _MENU_COLOR_WINODW_SIZE_USER_HWID,
    _MENU_COLOR_WINODW_SIZE_USER_HWID_ADJ,
    _MENU_COLOR_WINODW_SIZE_USER_VHEI,
    _MENU_COLOR_WINODW_SIZE_USER_VHEI_ADJ,
    _MENU_DCC_MODE,
    _MENU_DCC_MODE_DISABLE,
    _MENU_DCC_MODE_MOVIE,
    _MENU_DCC_MODE_PHOTO,
    _MENU_DCC_MODE_GAME,
    _MENU_ICM_MODE,
    _MENU_ICM_MODE_DISABLE,
    _MENU_ICM_MODE_MOVIE,
    _MENU_ICM_MODE_PHOTO,
    _MENU_ICM_MODE_GAME,
    _MENU_ICM_MODE_USER,
    _MENU_ICM_MODE_USER_RED_HUE,
    _MENU_ICM_MODE_USER_RED_HUE_ADJ,
    _MENU_ICM_MODE_USER_RED_SAT,
    _MENU_ICM_MODE_USER_RED_SAT_ADJ,
    _MENU_ICM_MODE_USER_GREEN_HUE,
    _MENU_ICM_MODE_USER_GREEN_HUE_ADJ,
    _MENU_ICM_MODE_USER_GREEN_SAT,
    _MENU_ICM_MODE_USER_GREEN_SAT_ADJ,
    _MENU_ICM_MODE_USER_BLUE_HUE,
    _MENU_ICM_MODE_USER_BLUE_HUE_ADJ,
    _MENU_ICM_MODE_USER_BLUE_SAT,
    _MENU_ICM_MODE_USER_BLUE_SAT_ADJ,
    _MENU_VIVID_CONTRAST,
    _MENU_VIVID_CONTRAST_ADJ,
    _MENU_VIVID_BRIGHTNESS,
    _MENU_VIVID_BRIGHTNESS_ADJ,
#endif

#if(_NON_LINEAR_SCALING_FUCTION == _ON)
    _MENU_NONLINEAR_SCALING,
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
    _MENU_ASPECT_RATIO,
#endif

#if (_SRGB_COLOR_ENHANCE == _ON)
    _MENU_SRGB,
    _MENU_HUE,
    _MENU_SUB_HUE,
    _MENU_SATURATION,
    _MENU_SUB_SATURATION,
#endif

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#if(_COLOR_FORMAT_CONVERT == _ON)
    _MENU_RGB_YUV,
    _MENU_SUB_RGB,
    _MENU_SUB_YUV,
#endif
// V012 Modify 20100304 End

    _MENU_F_AUTOCOLOR,
    _MENU_F_RESET,
    _MENU_F_OFFSET,
    _MENU_F_OFFSET_R,
    _MENU_F_OFFSET_R_ADJ,
    _MENU_F_OFFSET_G,
    _MENU_F_OFFSET_G_ADJ,
    _MENU_F_OFFSET_B,
    _MENU_F_OFFSET_B_ADJ,
    _MENU_F_GAIN,
    _MENU_F_GAIN_R,
    _MENU_F_GAIN_R_ADJ,
    _MENU_F_GAIN_G,
    _MENU_F_GAIN_G_ADJ,
    _MENU_F_GAIN_B,
    _MENU_F_GAIN_B_ADJ,
    _MENU_F_COLOR9300,
    _MENU_F_COLOR9300_R,
    _MENU_F_COLOR9300_R_ADJ,
    _MENU_F_COLOR9300_G,
    _MENU_F_COLOR9300_G_ADJ,
    _MENU_F_COLOR9300_B,
    _MENU_F_COLOR9300_B_ADJ,
    _MENU_F_COLOR6500,
    _MENU_F_COLOR6500_R,
    _MENU_F_COLOR6500_R_ADJ,
    _MENU_F_COLOR6500_G,
    _MENU_F_COLOR6500_G_ADJ,
    _MENU_F_COLOR6500_B,
    _MENU_F_COLOR6500_B_ADJ,
    _MENU_F_COLOR5800,
    _MENU_F_COLOR5800_R,
    _MENU_F_COLOR5800_R_ADJ,
    _MENU_F_COLOR5800_G,
    _MENU_F_COLOR5800_G_ADJ,
    _MENU_F_COLOR5800_B,
    _MENU_F_COLOR5800_B_ADJ,
    _MENU_F_SRGB,
    _MENU_F_SRGB_R,
    _MENU_F_SRGB_R_ADJ,
    _MENU_F_SRGB_G,
    _MENU_F_SRGB_G_ADJ,
    _MENU_F_SRGB_B,
    _MENU_F_SRGB_B_ADJ,
    _MENU_F_USER,
    _MENU_F_USER_R,
    _MENU_F_USER_R_ADJ,
    _MENU_F_USER_G,
    _MENU_F_USER_G_ADJ,
    _MENU_F_USER_B,
    _MENU_F_USER_B_ADJ,
    _MENU_F_BRIGHT,
    _MENU_F_BRIGHT_ADJ,
    _MENU_F_AUTO_CONFIG,
    _MENU_F_EXIT

};


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void COsdHandler(void);
extern void COsdSystemFlowProc(void);
extern void COsdEventMsgProc(void);

extern void COsdMenuNone(void);
extern void COsdLeftNone(void);
extern void COsdRightNone(void);
extern void COsdExitNone(void);

extern void COsdMenuDicomSetting(void);
extern void COsdLeftDicomSetting(void);
extern void COsdRightDicomSetting(void);
extern void COsdExitDicomSetting(void);

extern void COsdMenuGammaSetting(void);
extern void COsdLeftGammaSetting(void);
extern void COsdRightGammaSetting(void);
extern void COsdExitGammaSetting(void);

extern void COsdMenuBrightnessSetting(void);
extern void COsdLeftBrightnessSetting(void);
extern void COsdRightBrightnessSetting(void);
extern void COsdExitBrightnessSetting(void);

extern void COsdMenuSignalSource(void);
extern void COsdLeftSignalSource(void);
extern void COsdRightSignalSource(void);
extern void COsdExitSignalSource(void);

//#if(_AUDIO_SUPPORT == _ON)
extern void COsdMenuContrastSetting(void);
extern void COsdLeftContrastSetting(void);
extern void COsdRightContrastSetting(void);
extern void COsdExitContrastSetting(void);
//#endif // End of #if(_AUDIO_SUPPORT==_ON)

extern void COsdMenuAutoAdjust(void);
extern void COsdLeftAutoAdjust(void);
extern void COsdRightAutoAdjust(void);
extern void COsdExitAutoAdjust(void);

extern void COsdMenuFactory(void);
extern void COsdLeftFactory(void);
extern void COsdRightFactory(void);
extern void COsdExitFactory(void);

#if(_DDCCI_SUPPORT == _ON)
extern void COsdMenuDDCCI(void);
extern void COsdLeftDDCCI(void);
extern void COsdRightDDCCI(void);
extern void COsdExitDDCCI(void);
#endif

extern void COsdMenuContrast(void);
extern void COsdLeftContrast(void);
extern void COsdRightContrast(void);
extern void COsdExitContrast(void);

extern void COsdMenuSubDicom(void);
extern void COsdLeftSubDicom(void);
extern void COsdRightSubDicom(void);
extern void COsdExitSubDicom(void);

extern void COsdMenuSubGamma(void);
extern void COsdLeftSubGamma(void);
extern void COsdRightSubGamma(void);
extern void COsdExitSubGamma(void);

extern void COsdMenuSubContrast(void);
extern void COsdLeftSubContrast(void);
extern void COsdRightSubContrast(void);
extern void COsdExitSubContrast(void);

extern void COsdMenuBrightness(void);
extern void COsdLeftBrightness(void);
extern void COsdRightBrightness(void);
extern void COsdExitBrightness(void);

extern void COsdMenuSubBrightness(void);
extern void COsdLeftSubBrightness(void);
extern void COsdRightSubBrightness(void);
extern void COsdExitSubBrightness(void);

extern void COsdMenuSignalSelect(void);
extern void COsdLeftSignalSelect(void);
extern void COsdRightSignalSelect(void);
extern void COsdExitSignalSelect(void);

extern void COsdMenuSubAutoAdjust(void);
extern void COsdLeftSubAutoAdjust(void);
extern void COsdRightSubAutoAdjust(void);
extern void COsdExitSubAutoAdjust(void);

extern void COsdMenuSubFacReset(void);
extern void COsdLeftSubFacReset(void);
extern void COsdRightSubFacReset(void);
extern void COsdExitSubFacReset(void);

extern void COsdMenuColorAdj(void);
extern void COsdLeftColorAdj(void);
extern void COsdRightColorAdj(void);
extern void COsdExitColorAdj(void);


extern void COsdMenuSubColorAdjR(void);
extern void COsdLeftSubColorAdjR(void);
extern void COsdRightSubColorAdjR(void);
extern void COsdExitSubColorAdjR(void);

extern void COsdMenuSubColorAdjG(void);
extern void COsdLeftSubColorAdjG(void);
extern void COsdRightSubColorAdjG(void);
extern void COsdExitSubColorAdjG(void);

extern void COsdMenuSubColorAdjB(void);
extern void COsdLeftSubColorAdjB(void);
extern void COsdRightSubColorAdjB(void);
extern void COsdExitSubColorAdjB(void);

extern void COsdMenuAdjR(void);
extern void COsdLeftAdjR(void);
extern void COsdRightAdjR(void);
extern void COsdExitAdjR(void);

extern void COsdMenuAdjG(void);
extern void COsdLeftAdjG(void);
extern void COsdRightAdjG(void);
extern void COsdExitAdjG(void);

extern void COsdMenuAdjB(void);
extern void COsdLeftAdjB(void);
extern void COsdRightAdjB(void);
extern void COsdExitAdjB(void);

extern void COsdMenuColorTemp(void);
extern void COsdLeftColorTemp(void);
extern void COsdRightColorTemp(void);
extern void COsdExitColorTemp(void);


extern void COsdMenuSubTempColor9300(void);
extern void COsdLeftSubTempColor9300(void);
extern void COsdRightSubTempColor9300(void);
extern void COsdExitSubTempColor9300(void);

extern void COsdMenuSubTempColor6500(void);
extern void COsdLeftSubTempColor6500(void);
extern void COsdRightSubTempColor6500(void);
extern void COsdExitSubTempColor6500(void);

extern void COsdMenuSubTempColor5800(void);
extern void COsdLeftSubTempColor5800(void);
extern void COsdRightSubTempColor5800(void);
extern void COsdExitSubTempColor5800(void);

extern void COsdMenuSubTempSrgb(void);
extern void COsdLeftSubTempSrgb(void);
extern void COsdRightSubTempSrgb(void);
extern void COsdExitSubTempSrgb(void);

extern void COsdMenuSubTempUser(void);
extern void COsdLeftSubTempUser(void);
extern void COsdRightSubTempUser(void);
extern void COsdExitSubTempUser(void);

#if(_DCR_MODE != _DCR_TYPE_OFF)

extern void COsdMenuColorDCR(void);
extern void COsdLeftColorDCR(void);
extern void COsdRightColorDCR(void);
extern void COsdExitColorDCR(void);

#endif

extern void COsdMenuClock(void);
extern void COsdLeftClock(void);
extern void COsdRightClock(void);
extern void COsdExitClock(void);

extern void COsdMenuSubClock(void);
extern void COsdLeftSubClock(void);
extern void COsdRightSubClock(void);
extern void COsdExitSubClock(void);

extern void COsdMenuPhase(void);
extern void COsdLeftPhase(void);
extern void COsdRightPhase(void);
extern void COsdExitPhase(void);

extern void COsdMenuSubPhase(void);
extern void COsdLeftSubPhase(void);
extern void COsdRightSubPhase(void);
extern void COsdExitSubPhase(void);

extern void COsdMenuSharpness(void);
extern void COsdLeftSharpness(void);
extern void COsdRightSharpness(void);
extern void COsdExitSharpness(void);

extern void COsdMenuSubSharpness0(void);
extern void COsdLeftSubSharpness0(void);
extern void COsdRightSubSharpness0(void);
extern void COsdExitSubSharpness0(void);

extern void COsdMenuSubSharpness1(void);
extern void COsdLeftSubSharpness1(void);
extern void COsdRightSubSharpness1(void);
extern void COsdExitSubSharpness1(void);

extern void COsdMenuSubSharpness2(void);
extern void COsdLeftSubSharpness2(void);
extern void COsdRightSubSharpness2(void);
extern void COsdExitSubSharpness2(void);

extern void COsdMenuSubSharpness3(void);
extern void COsdLeftSubSharpness3(void);
extern void COsdRightSubSharpness3(void);
extern void COsdExitSubSharpness3(void);

extern void COsdMenuSubSharpness4(void);
extern void COsdLeftSubSharpness4(void);
extern void COsdRightSubSharpness4(void);
extern void COsdExitSubSharpness4(void);

extern void COsdMenuHPosition(void);
extern void COsdLeftHPosition(void);
extern void COsdRightHPosition(void);
extern void COsdExitHPosition(void);

extern void COsdMenuSubHPosition(void);
extern void COsdLeftSubHPosition(void);
extern void COsdRightSubHPosition(void);
extern void COsdExitSubHPosition(void);

extern void COsdMenuVPosition(void);
extern void COsdLeftVPosition(void);
extern void COsdRightVPosition(void);
extern void COsdExitVPosition(void);

extern void COsdMenuSubVPosition(void);
extern void COsdLeftSubVPosition(void);
extern void COsdRightSubVPosition(void);
extern void COsdExitSubVPosition(void);

#if(_OD_SUPPORT == _ON)
extern void COsdMenuOD(void);
extern void COsdLeftOD(void);
extern void COsdRightOD(void);
extern void COsdExitOD(void);

extern void COsdMenuSubOD(void);
extern void COsdLeftSubOD(void);
extern void COsdRightSubOD(void);
extern void COsdExitSubOD(void);
#endif

extern void COsdMenuOsdHPos(void);
extern void COsdLeftOsdHPos(void);
extern void COsdRightOsdHPos(void);
extern void COsdExitOsdHPos(void);

extern void COsdMenuSubOsdHPos(void);
extern void COsdLeftSubOsdHPos(void);
extern void COsdRightSubOsdHPos(void);
extern void COsdExitSubOsdHPos(void);

extern void COsdMenuOsdVPos(void);
extern void COsdLeftOsdVPos(void);
extern void COsdRightOsdVPos(void);
extern void COsdExitOsdVPos(void);

extern void COsdMenuSubOsdVPos(void);
extern void COsdLeftSubOsdVPos(void);
extern void COsdRightSubOsdVPos(void);
extern void COsdExitSubOsdVPos(void);

extern void COsdMenuOsdTime(void);
extern void COsdLeftOsdTime(void);
extern void COsdRightOsdTime(void);
extern void COsdExitOsdTime(void);

extern void COsdMenuSubOsdTime(void);
extern void COsdLeftSubOsdTime(void);
extern void COsdRightSubOsdTime(void);
extern void COsdExitSubOsdTime(void);

extern void COsdMenuLanguage(void);
extern void COsdLeftLanguage(void);
extern void COsdRightLanguage(void);
extern void COsdExitLanguage(void);

extern void COsdMenuSubEng(void);
extern void COsdLeftSubEng(void);
extern void COsdRightSubEng(void);
extern void COsdExitSubEng(void);

extern void COsdMenuSubFran(void);
extern void COsdLeftSubFran(void);
extern void COsdRightSubFran(void);
extern void COsdExitSubFran(void);

extern void COsdMenuSubDeut(void);
extern void COsdLeftSubDeut(void);
extern void COsdRightSubDeut(void);
extern void COsdExitSubDeut(void);

extern void COsdMenuSubEspa(void);
extern void COsdLeftSubEspa(void);
extern void COsdRightSubEspa(void);
extern void COsdExitSubEspa(void);

extern void COsdMenuSubChi(void);
extern void COsdLeftSubChi(void);
extern void COsdRightSubChi(void);
extern void COsdExitSubChi(void);

extern void COsdMenuSubSimpleChi(void);
extern void COsdLeftSubSimpleChi(void);
extern void COsdRightSubSimpleChi(void);
extern void COsdExitSubSimpleChi(void);

extern void COsdMenuSubJap(void);
extern void COsdLeftSubJap(void);
extern void COsdRightSubJap(void);
extern void COsdExitSubJap(void);

extern void COsdMenuSingalVGA(void);
extern void COsdLeftSingalVGA(void);
extern void COsdRightSingalVGA(void);
extern void COsdExitSingalVGA(void);

extern void COsdMenuSingalDVI(void);
extern void COsdLeftSingalDVI(void);
extern void COsdRightSingalDVI(void);
extern void COsdExitSingalDVI(void);

extern void COsdMenuSingalHDMI(void);
extern void COsdLeftSingalHDMI(void);
extern void COsdRightSingalHDMI(void);
extern void COsdExitSingalHDMI(void);

extern void COsdMenuSingalDisplayPort(void);
extern void COsdLeftSingalDisplayPort(void);
extern void COsdRightSingalDisplayPort(void);
extern void COsdExitSingalDisplayPort(void);

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
extern void COsdMenuSingalAutoSearch(void);
extern void COsdLeftSingalAutoSearch(void);
extern void COsdRightSingalAutoSearch(void);
extern void COsdExitSingalAutoSearch(void);
#endif

#if(_AUDIO_SUPPORT == _ON)
extern void COsdMenuVolume(void);
extern void COsdLeftVolume(void);
extern void COsdRightVolume(void);
extern void COsdExitVolume(void);

extern void COsdMenuSubVolume(void);
extern void COsdLeftSubVolume(void);
extern void COsdRightSubVolume(void);
extern void COsdExitSubVolume(void);

extern void COsdMenuMute(void);
extern void COsdLeftMute(void);
extern void COsdRightMute(void);
extern void COsdExitMute(void);
#endif // End of #if(_AUDIO_SUPPORT==_ON)

#if(_DDCCI_SUPPORT == _ON)
extern void COsdMenuDDCCIONOFF(void);
extern void COsdLeftDDCCIONOFF(void);
extern void COsdRightDDCCIONOFF(void);
extern void COsdExitDDCCIONOFF(void);
#endif

extern void COsdMenuHue(void);
extern void COsdLeftHue(void);
extern void COsdRightHue(void);
extern void COsdExitHue(void);
extern void COsdMenuSubHue(void);
extern void COsdLeftSubHue(void);
extern void COsdRightSubHue(void);
extern void COsdExitSubHue(void);
extern void COsdMenuSaturation(void);
extern void COsdLeftSaturation(void);
extern void COsdRightSaturation(void);
extern void COsdExitSaturation(void);
extern void COsdMenuSubSaturation(void);
extern void COsdLeftSubSaturation(void);
extern void COsdRightSubSaturation(void);
extern void COsdExitSubSaturation(void);


#if(_VIVID_COLOR_FUCTION == _ON)
extern void COsdMenuVividColor(void);
extern void COsdLeftVividColor(void);
extern void COsdRightVividColor(void);
extern void COsdExitVividColor(void);

extern void COsdMenuColorWindow(void);
extern void COsdLeftColorWindow(void);
extern void COsdRightColorWindow(void);
extern void COsdExitColorWindow(void);

extern void COsdMenuColorWindowDisable(void);
extern void COsdLeftColorWindowDisable(void);
extern void COsdRightColorWindowDisable(void);
extern void COsdExitColorWindowDisable(void);

extern void COsdMenuColorWindowFull(void);
extern void COsdLeftColorWindowFull(void);
extern void COsdRightColorWindowFull(void);
extern void COsdExitColorWindowFull(void);

extern void COsdMenuColorWindowDemo(void);
extern void COsdLeftColorWindowDemo(void);
extern void COsdRightColorWindowDemo(void);
extern void COsdExitColorWindowDemo(void);

extern void COsdMenuColorWindowUser(void);
extern void COsdLeftColorWindowUser(void);
extern void COsdRightColorWindowUser(void);
extern void COsdExitColorWindowUser(void);

extern void COsdMenuColorWindowUserHPos(void);
extern void COsdLeftColorWindowUserHPos(void);
extern void COsdRightColorWindowUserHPos(void);
extern void COsdExitColorWindowUserHPos(void);

extern void COsdMenuColorWindowUserHPosAdj(void);
extern void COsdLeftColorWindowUserHPosAdj(void);
extern void COsdRightColorWindowUserHPosAdj(void);
extern void COsdExitColorWindowUserHPosAdj(void);

extern void COsdMenuColorWindowUserVPos(void);
extern void COsdLeftColorWindowUserVPos(void);
extern void COsdRightColorWindowUserVPos(void);
extern void COsdExitColorWindowUserVPos(void);

extern void COsdMenuColorWindowUserVPosAdj(void);
extern void COsdLeftColorWindowUserVPosAdj(void);
extern void COsdRightColorWindowUserVPosAdj(void);
extern void COsdExitColorWindowUserVPosAdj(void);

extern void COsdMenuColorWindowUserHWid(void);
extern void COsdLeftColorWindowUserHWid(void);
extern void COsdRightColorWindowUserHWid(void);
extern void COsdExitColorWindowUserHWid(void);

extern void COsdMenuColorWindowUserHWidAdj(void);
extern void COsdLeftColorWindowUserHWidAdj(void);
extern void COsdRightColorWindowUserHWidAdj(void);
extern void COsdExitColorWindowUserHWidAdj(void);

extern void COsdMenuColorWindowUserVHei(void);
extern void COsdLeftColorWindowUserVHei(void);
extern void COsdRightColorWindowUserVHei(void);
extern void COsdExitColorWindowUserVHei(void);

extern void COsdMenuColorWindowUserVHeiAdj(void);
extern void COsdLeftColorWindowUserVHeiAdj(void);
extern void COsdRightColorWindowUserVHeiAdj(void);
extern void COsdExitColorWindowUserVHeiAdj(void);

extern void COsdMenuDCCMode(void);
extern void COsdLeftDCCMode(void);
extern void COsdRightDCCMode(void);
extern void COsdExitDCCMode(void);

extern void COsdMenuDCCModeDisable(void);
extern void COsdLeftDCCModeDisable(void);
extern void COsdRightDCCModeDisable(void);
extern void COsdExitDCCModeDisable(void);

extern void COsdMenuDCCModeMovie(void);
extern void COsdLeftDCCModeMovie(void);
extern void COsdRightDCCModeMovie(void);
extern void COsdExitDCCModeMovie(void);

extern void COsdMenuDCCModePhoto(void);
extern void COsdLeftDCCModePhoto(void);
extern void COsdRightDCCModePhoto(void);
extern void COsdExitDCCModePhoto(void);

extern void COsdMenuDCCModeGame(void);
extern void COsdLeftDCCModeGame(void);
extern void COsdRightDCCModeGame(void);
extern void COsdExitDCCModeGame(void);

extern void COsdMenuICMMode(void);
extern void COsdLeftICMMode(void);
extern void COsdRightICMMode(void);
extern void COsdExitICMMode(void);

extern void COsdMenuICMModeDisable(void);
extern void COsdLeftICMModeDisable(void);
extern void COsdRightICMModeDisable(void);
extern void COsdExitICMModeDisable(void);

extern void COsdMenuICMModeMovie(void);
extern void COsdLeftICMModeMovie(void);
extern void COsdRightICMModeMovie(void);
extern void COsdExitICMModeMovie(void);

extern void COsdMenuICMModePhoto(void);
extern void COsdLeftICMModePhoto(void);
extern void COsdRightICMModePhoto(void);
extern void COsdExitICMModePhoto(void);

extern void COsdMenuICMModeGame(void);
extern void COsdLeftICMModeGame(void);
extern void COsdRightICMModeGame(void);
extern void COsdExitICMModeGame(void);

extern void COsdMenuICMModeUser(void);
extern void COsdLeftICMModeUser(void);
extern void COsdRightICMModeUser(void);
extern void COsdExitICMModeUser(void);

extern void COsdMenuICMModeUserRedHue(void);
extern void COsdLeftICMModeUserRedHue(void);
extern void COsdRightICMModeUserRedHue(void);
extern void COsdExitICMModeUserRedHue(void);

extern void COsdMenuICMModeUserRedHueAdj(void);
extern void COsdLeftICMModeUserRedHueAdj(void);
extern void COsdRightICMModeUserRedHueAdj(void);
extern void COsdExitICMModeUserRedHueAdj(void);

extern void COsdMenuICMModeUserRedSat(void);
extern void COsdLeftICMModeUserRedSat(void);
extern void COsdRightICMModeUserRedSat(void);
extern void COsdExitICMModeUserRedSat(void);

extern void COsdMenuICMModeUserRedSatAdj(void);
extern void COsdLeftICMModeUserRedSatAdj(void);
extern void COsdRightICMModeUserRedSatAdj(void);
extern void COsdExitICMModeUserRedSatAdj(void);

extern void COsdMenuICMModeUserGreenHue(void);
extern void COsdLeftICMModeUserGreenHue(void);
extern void COsdRightICMModeUserGreenHue(void);
extern void COsdExitICMModeUserGreenHue(void);

extern void COsdMenuICMModeUserGreenHueAdj(void);
extern void COsdLeftICMModeUserGreenHueAdj(void);
extern void COsdRightICMModeUserGreenHueAdj(void);
extern void COsdExitICMModeUserGreenHueAdj(void);

extern void COsdMenuICMModeUserGreenSat(void);
extern void COsdLeftICMModeUserGreenSat(void);
extern void COsdRightICMModeUserGreenSat(void);
extern void COsdExitICMModeUserGreenSat(void);

extern void COsdMenuICMModeUserGreenSatAdj(void);
extern void COsdLeftICMModeUserGreenSatAdj(void);
extern void COsdRightICMModeUserGreenSatAdj(void);
extern void COsdExitICMModeUserGreenSatAdj(void);

extern void COsdMenuICMModeUserBlueHue(void);
extern void COsdLeftICMModeUserBlueHue(void);
extern void COsdRightICMModeUserBlueHue(void);
extern void COsdExitICMModeUserBlueHue(void);

extern void COsdMenuICMModeUserBlueHueAdj(void);
extern void COsdLeftICMModeUserBlueHueAdj(void);
extern void COsdRightICMModeUserBlueHueAdj(void);
extern void COsdExitICMModeUserBlueHueAdj(void);

extern void COsdMenuICMModeUserBlueSat(void);
extern void COsdLeftICMModeUserBlueSat(void);
extern void COsdRightICMModeUserBlueSat(void);
extern void COsdExitICMModeUserBlueSat(void);

extern void COsdMenuICMModeUserBlueSatAdj(void);
extern void COsdLeftICMModeUserBlueSatAdj(void);
extern void COsdRightICMModeUserBlueSatAdj(void);
extern void COsdExitICMModeUserBlueSatAdj(void);

extern void COsdMenuVividContrast(void);
extern void COsdLeftVividContrast(void);
extern void COsdRightVividContrast(void);
extern void COsdExitVividContrast(void);

extern void COsdMenuVividContrastAdj(void);
extern void COsdLeftVividContrastAdj(void);
extern void COsdRightVividContrastAdj(void);
extern void COsdExitVividContrastAdj(void);

extern void COsdMenuVividBrightness(void);
extern void COsdLeftVividBrightness(void);
extern void COsdRightVividBrightness(void);
extern void COsdExitVividBrightness(void);

extern void COsdMenuVividBrightnessAdj(void);
extern void COsdLeftVividBrightnessAdj(void);
extern void COsdRightVividBrightnessAdj(void);
extern void COsdExitVividBrightnessAdj(void);

#endif

#if(_NON_LINEAR_SCALING_FUCTION == _ON)
extern void COsdMenuNonLinearScaling(void);
extern void COsdLeftNonLinearScaling(void);
extern void COsdRightNonLinearScaling(void);
extern void COsdExitNonLinearScaling(void);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
extern void COsdMenuAspectRatio(void);
extern void COsdLeftAspectRatio(void);
extern void COsdRightAspectRatio(void);
extern void COsdExitAspectRatio(void);
#endif

#if (_SRGB_COLOR_ENHANCE == _ENABLE)
extern void COsdMenuSrgb(void);
extern void COsdLeftSrgb(void);
extern void COsdRightSrgb(void);
extern void COsdExitSrgb(void);
extern void COsdMenuHue(void);
extern void COsdLeftHue(void);
extern void COsdRightHue(void);
extern void COsdExitHue(void);
extern void COsdMenuSubHue(void);
extern void COsdLeftSubHue(void);
extern void COsdRightSubHue(void);
extern void COsdExitSubHue(void);
extern void COsdMenuSaturation(void);
extern void COsdLeftSaturation(void);
extern void COsdRightSaturation(void);
extern void COsdExitSaturation(void);
extern void COsdMenuSubSaturation(void);
extern void COsdLeftSubSaturation(void);
extern void COsdRightSubSaturation(void);
extern void COsdExitSubSaturation(void);
#endif

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#if(_COLOR_FORMAT_CONVERT == _ON)
extern void COsdMenuRGBYUV(void);
extern void COsdLeftRGBYUV(void);
extern void COsdRightRGBYUV(void);
extern void COsdExitRGBYUV(void);
extern void COsdMenuSubRGB(void);
extern void COsdLeftSubRGB(void);
extern void COsdRightSubRGB(void);
extern void COsdExitSubRGB(void);
extern void COsdMenuSubYUV(void);
extern void COsdLeftSubYUV(void);
extern void COsdRightSubYUV(void);
extern void COsdExitSubYUV(void);
#endif
// V012 Modify 20100304 End

extern void COsdMenuFAutoColor(void);
extern void COsdLeftFAutoColor(void);
extern void COsdRightFAutoColor(void);
extern void COsdExitFAutoColor(void);

extern void COsdMenuFReset(void);
extern void COsdLeftFReset(void);
extern void COsdRightFReset(void);
extern void COsdExitFReset(void);

extern void COsdMenuFOffset(void);
extern void COsdLeftFOffset(void);
extern void COsdRightFOffset(void);
extern void COsdExitFOffset(void);

extern void COsdMenuFOffsetR(void);
extern void COsdLeftFOffsetR(void);
extern void COsdRightFOffsetR(void);
extern void COsdExitFOffsetR(void);

extern void COsdMenuFOffsetRAdj(void);
extern void COsdLeftFOffsetRAdj(void);
extern void COsdRightFOffsetRAdj(void);
extern void COsdExitFOffsetRAdj(void);

extern void COsdMenuFOffsetG(void);
extern void COsdLeftFOffsetG(void);
extern void COsdRightFOffsetG(void);
extern void COsdExitFOffsetG(void);

extern void COsdMenuFOffsetGAdj(void);
extern void COsdLeftFOffsetGAdj(void);
extern void COsdRightFOffsetGAdj(void);
extern void COsdExitFOffsetGAdj(void);

extern void COsdMenuFOffsetB(void);
extern void COsdLeftFOffsetB(void);
extern void COsdRightFOffsetB(void);
extern void COsdExitFOffsetB(void);

extern void COsdMenuFOffsetBAdj(void);
extern void COsdLeftFOffsetBAdj(void);
extern void COsdRightFOffsetBAdj(void);
extern void COsdExitFOffsetBAdj(void);

extern void COsdMenuFGain(void);
extern void COsdLeftFGain(void);
extern void COsdRightFGain(void);
extern void COsdExitFGain(void);

extern void COsdMenuFGainR(void);
extern void COsdLeftFGainR(void);
extern void COsdRightFGainR(void);
extern void COsdExitFGainR(void);

extern void COsdMenuFGainRAdj(void);
extern void COsdLeftFGainRAdj(void);
extern void COsdRightFGainRAdj(void);
extern void COsdExitFGainRAdj(void);

extern void COsdMenuFGainG(void);
extern void COsdLeftFGainG(void);
extern void COsdRightFGainG(void);
extern void COsdExitFGainG(void);

extern void COsdMenuFGainGAdj(void);
extern void COsdLeftFGainGAdj(void);
extern void COsdRightFGainGAdj(void);
extern void COsdExitFGainGAdj(void);

extern void COsdMenuFGainB(void);
extern void COsdLeftFGainB(void);
extern void COsdRightFGainB(void);
extern void COsdExitFGainB(void);

extern void COsdMenuFGainBAdj(void);
extern void COsdLeftFGainBAdj(void);
extern void COsdRightFGainBAdj(void);
extern void COsdExitFGainBAdj(void);

extern void COsdMenuFColor9300(void);
extern void COsdLeftFColor9300(void);
extern void COsdRightFColor9300(void);
extern void COsdExitFColor9300(void);

extern void COsdMenuFColor9300R(void);
extern void COsdLeftFColor9300R(void);
extern void COsdRightFColor9300R(void);
extern void COsdExitFColor9300R(void);

extern void COsdMenuFColor9300RAdj(void);
extern void COsdLeftFColor9300RAdj(void);
extern void COsdRightFColor9300RAdj(void);
extern void COsdExitFColor9300RAdj(void);

extern void COsdMenuFColor9300G(void);
extern void COsdLeftFColor9300G(void);
extern void COsdRightFColor9300G(void);
extern void COsdExitFColor9300G(void);

extern void COsdMenuFColor9300GAdj(void);
extern void COsdLeftFColor9300GAdj(void);
extern void COsdRightFColor9300GAdj(void);
extern void COsdExitFColor9300GAdj(void);

extern void COsdMenuFColor9300B(void);
extern void COsdLeftFColor9300B(void);
extern void COsdRightFColor9300B(void);
extern void COsdExitFColor9300B(void);

extern void COsdMenuFColor9300BAdj(void);
extern void COsdLeftFColor9300BAdj(void);
extern void COsdRightFColor9300BAdj(void);
extern void COsdExitFColor9300BAdj(void);

extern void COsdMenuFColor6500(void);
extern void COsdLeftFColor6500(void);
extern void COsdRightFColor6500(void);
extern void COsdExitFColor6500(void);

extern void COsdMenuFColor6500R(void);
extern void COsdLeftFColor6500R(void);
extern void COsdRightFColor6500R(void);
extern void COsdExitFColor6500R(void);

extern void COsdMenuFColor6500RAdj(void);
extern void COsdLeftFColor6500RAdj(void);
extern void COsdRightFColor6500RAdj(void);
extern void COsdExitFColor6500RAdj(void);

extern void COsdMenuFColor6500G(void);
extern void COsdLeftFColor6500G(void);
extern void COsdRightFColor6500G(void);
extern void COsdExitFColor6500G(void);

extern void COsdMenuFColor6500GAdj(void);
extern void COsdLeftFColor6500GAdj(void);
extern void COsdRightFColor6500GAdj(void);
extern void COsdExitFColor6500GAdj(void);

extern void COsdMenuFColor6500B(void);
extern void COsdLeftFColor6500B(void);
extern void COsdRightFColor6500B(void);
extern void COsdExitFColor6500B(void);

extern void COsdMenuFColor6500BAdj(void);
extern void COsdLeftFColor6500BAdj(void);
extern void COsdRightFColor6500BAdj(void);
extern void COsdExitFColor6500BAdj(void);

extern void COsdMenuFColor5800(void);
extern void COsdLeftFColor5800(void);
extern void COsdRightFColor5800(void);
extern void COsdExitFColor5800(void);

extern void COsdMenuFColor5800R(void);
extern void COsdLeftFColor5800R(void);
extern void COsdRightFColor5800R(void);
extern void COsdExitFColor5800R(void);

extern void COsdMenuFColor5800RAdj(void);
extern void COsdLeftFColor5800RAdj(void);
extern void COsdRightFColor5800RAdj(void);
extern void COsdExitFColor5800RAdj(void);

extern void COsdMenuFColor5800G(void);
extern void COsdLeftFColor5800G(void);
extern void COsdRightFColor5800G(void);
extern void COsdExitFColor5800G(void);

extern void COsdMenuFColor5800GAdj(void);
extern void COsdLeftFColor5800GAdj(void);
extern void COsdRightFColor5800GAdj(void);
extern void COsdExitFColor5800GAdj(void);

extern void COsdMenuFColor5800B(void);
extern void COsdLeftFColor5800B(void);
extern void COsdRightFColor5800B(void);
extern void COsdExitFColor5800B(void);

extern void COsdMenuFColor5800BAdj(void);
extern void COsdLeftFColor5800BAdj(void);
extern void COsdRightFColor5800BAdj(void);
extern void COsdExitFColor5800BAdj(void);

extern void COsdMenuFSrgb(void);
extern void COsdLeftFSrgb(void);
extern void COsdRightFSrgb(void);
extern void COsdExitFSrgb(void);

extern void COsdMenuFSrgbR(void);
extern void COsdLeftFSrgbR(void);
extern void COsdRightFSrgbR(void);
extern void COsdExitFSrgbR(void);

extern void COsdMenuFSrgbRAdj(void);
extern void COsdLeftFSrgbRAdj(void);
extern void COsdRightFSrgbRAdj(void);
extern void COsdExitFSrgbRAdj(void);

extern void COsdMenuFSrgbG(void);
extern void COsdLeftFSrgbG(void);
extern void COsdRightFSrgbG(void);
extern void COsdExitFSrgbG(void);

extern void COsdMenuFSrgbGAdj(void);
extern void COsdLeftFSrgbGAdj(void);
extern void COsdRightFSrgbGAdj(void);
extern void COsdExitFSrgbGAdj(void);

extern void COsdMenuFSrgbB(void);
extern void COsdLeftFSrgbB(void);
extern void COsdRightFSrgbB(void);
extern void COsdExitFSrgbB(void);

extern void COsdMenuFSrgbBAdj(void);
extern void COsdLeftFSrgbBAdj(void);
extern void COsdRightFSrgbBAdj(void);
extern void COsdExitFSrgbBAdj(void);

extern void COsdMenuFUser(void);
extern void COsdLeftFUser(void);
extern void COsdRightFUser(void);
extern void COsdExitFUser(void);

extern void COsdMenuFUserR(void);
extern void COsdLeftFUserR(void);
extern void COsdRightFUserR(void);
extern void COsdExitFUserR(void);

extern void COsdMenuFUserRAdj(void);
extern void COsdLeftFUserRAdj(void);
extern void COsdRightFUserRAdj(void);
extern void COsdExitFUserRAdj(void);

extern void COsdMenuFUserG(void);
extern void COsdLeftFUserG(void);
extern void COsdRightFUserG(void);
extern void COsdExitFUserG(void);

extern void COsdMenuFUserGAdj(void);
extern void COsdLeftFUserGAdj(void);
extern void COsdRightFUserGAdj(void);
extern void COsdExitFUserGAdj(void);

extern void COsdMenuFUserB(void);
extern void COsdLeftFUserB(void);
extern void COsdRightFUserB(void);
extern void COsdExitFUserB(void);

extern void COsdMenuFUserBAdj(void);
extern void COsdLeftFUserBAdj(void);
extern void COsdRightFUserBAdj(void);
extern void COsdExitFUserBAdj(void);


extern void COsdMenuFBright(void);
extern void COsdLeftFBright(void);
extern void COsdRightFBright(void);
extern void COsdExitFBright(void);

extern void COsdMenuFBrightAdj(void);
extern void COsdLeftFBrightAdj(void);
extern void COsdRightFBrightAdj(void);
extern void COsdExitFBrightAdj(void);


extern void COsdMenuFAutoConfig(void);
extern void COsdLeftFAutoConfig(void);
extern void COsdRightFAutoConfig(void);
extern void COsdExitFAutoConfig(void);

extern void COsdMenuFExit(void);
extern void COsdLeftFExit(void);
extern void COsdRightFExit(void);
extern void COsdExitFExit(void);


