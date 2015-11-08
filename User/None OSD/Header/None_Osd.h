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
#define _OSD_FONT_START_POSITION                745
#define _OSD_FONT_START_POSITION_ROTATE         0


//--------------------------------------------------
// Definitions of Clock Settings Used by COsdFxGetAdcClockRange()
//--------------------------------------------------
#define _CLOCK_BIAS                             50
#define _GET_CLOCKRANGE_MAX                     0
#define _GET_CLOCKRANGE_MIN                     1


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

#define _GET_VPOSITIONRANGE_MAX                 0
#define _GET_VPOSITIONRANGE_MIN                 1


//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#define _CONTRAST_MAX                           178
#define _CONTRAST_MIN                           78


//--------------------------------------------------
// Definitions of Backlight Range
//--------------------------------------------------
#define _BACKLIGHT_MAX                          255
#define _BACKLIGHT_MIN                          0


//--------------------------------------------------
// Definitions of OSD Position
//--------------------------------------------------
#define _OSD_HPOSITION_RANGE                    200
#define _OSD_VPOSITION_RANGE                    200
#define _OSD_HPOSITION_OFFSET                   8
#define _OSD_VPOSITION_OFFSET                   5


//--------------------------------------------------
// Definitions of OSD Show Number Function Used by COsdFxShowNumber()
//--------------------------------------------------
#define _ALIGN_LEFT                             0
#define _ALIGN_RIGHT                            1

#define _FORCE_SHOW_NUMBER_OFF                  (0 << 1)
#define _FORCE_SHOW_NUMBER_ON                   (1 << 1)

#define _SHOW_1                                 (0 << 4)
#define _SHOW_2                                 (1 << 4)
#define _SHOW_3                                 (2 << 4)
#define _SHOW_4                                 (3 << 4)
#define _SHOW_5                                 (4 << 4)


//--------------------------------------------------
// Definitions of Checking Max or Min Value Used by COsdFxDetOverRange()
//--------------------------------------------------
#define _DET_OVERRANGE_MAX                      0
#define _DET_OVERRANGE_MIN                      1


//--------------------------------------------------
//
//--------------------------------------------------
#define _TEXTWITH                               0
#define _PIECE                                  1
#define _LENGTH                                 2


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
    _FRENCH,
    _GERMAN,
    _SPANISH,
    _CHINESE_T,
    _CHINESE_S,
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

    _CT_COLORTEMP_AMOUNT,

};

//--------------------------------------------------
// Definitions of Color Palette
//--------------------------------------------------
enum OSDColorPaletteDef
{
    _CP_BLACK,
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
    _CP_COLOR15,
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
    _z_,

};


//----------------------------------------------------------------------------------------------------

#ifdef __NONE_OSD__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE idata ucOsdState = 0;
BYTE idata ucOsdEventMsg = 0;
BYTE idata ucOsdMap = 0;


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE idata ucOsdState;
extern BYTE idata ucOsdEventMsg;
extern BYTE idata ucOsdMap;


#endif


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


//--------------------------------------------------
// Definitions of OSD Flow
//--------------------------------------------------
typedef enum
{
    _MENU_NONE = 0,

};


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void COsdHandler(void);
extern void COsdSystemFlowProc(void);
extern void COsdEventMsgProc(void);

extern void COsdNone(void);

extern void COsdMenuNone(void);
extern void COsdLeftNone(void);
extern void COsdRightNone(void);
extern void COsdExitNone(void);


