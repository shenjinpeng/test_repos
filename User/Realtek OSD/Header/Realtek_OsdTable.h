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
// ID Code      : OsdTable.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

extern code void (*OperationTable[][4])(void);
extern BYTE code  tOSD_DICOM_STR[];
extern  WORD xdata  tOSD_DICOMlumi[11];//sjp2007015
//extern WORD code  tBKLIT_DICOMlumi[];
extern BYTE code  tOSD_SIGNAL_STR[];
extern BYTE code  tOSD_AUTO_ADJUST_STR[];

extern BYTE  code * tOSD_DICOM_STR2[];
extern BYTE code  tOSD_GAMMA_STR[];
extern BYTE code  *tOSD_GAMMA_STR2[];

extern BYTE code  tOSD_DSA_STR[];
extern BYTE code  tOSD_DSI_STR[];
extern BYTE code  tOSD_CT_STR[];
extern BYTE code  tOSD_MRI_STR[];//SJP 110530 


extern BYTE code  *tOSD_SIGNAL_TYPE[];
extern BYTE code  tOSD_YES[];
extern BYTE code  tOSD_NO[];

//--------------------------------------------------
// RGB Settings for Colors
//--------------------------------------------------
#define _RGB_BLACK                                0,  0,  0
#define _RGB_WHITE                              255,255,255
#define _RGB_RED                                255,  0,  0
#define _RGB_GREEN                                0,255,  0
#define _RGB_BLUE                                 0,  0,255
#define _RGB_YELLOW                             255,255,  0
#define _RGB_GRAY                               128,128,128
#define _RGB_DARKBLUE                            64, 64,255
#define _RGB_LIGHTBLUE                          128,128,255
#define _RGB_SELECTBOTTOM                        58, 70, 80
#define _RGB_PINK                               255,128,255


#ifdef __ADJUST__

//--------------------------------------------------
// Color Palette Table
//--------------------------------------------------
BYTE code tPALETTE_0[] =
{
    _RGB_BLACK,
    _RGB_WHITE,
    _RGB_RED,
    _RGB_GREEN,
    _RGB_BLUE,
    _RGB_YELLOW,
    _RGB_GRAY,
    _RGB_DARKBLUE,
    _RGB_LIGHTBLUE,

    _RGB_SELECTBOTTOM,
    _RGB_PINK,

    _RGB_RED,
    _RGB_GREEN,
    _RGB_BLUE,
    _RGB_YELLOW,
    _RGB_GRAY,
};


//----------------------------------------------------------------------------------------------------
// Filter Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
#if(_EXTEND_TABLE_SUPPORT == _ON)

BYTE xdata tSU_COEF_0[_SU_COEF_EXTEND]                  _at_ _SU_COEF_0_EXTEND_ADDRESS;
BYTE xdata tSU_COEF_1[_SU_COEF_EXTEND]                  _at_ _SU_COEF_1_EXTEND_ADDRESS;
BYTE xdata tSU_COEF_2[_SU_COEF_EXTEND]                  _at_ _SU_COEF_2_EXTEND_ADDRESS;
BYTE xdata tSU_COEF_3[_SU_COEF_EXTEND]                  _at_ _SU_COEF_3_EXTEND_ADDRESS;
BYTE xdata tSU_COEF_4[_SU_COEF_EXTEND]                  _at_ _SU_COEF_4_EXTEND_ADDRESS;

#else

BYTE code tSU_COEF_0[] =
{
    0x0B,0x00,0x0B,0x00,0x0A,0x00,0x08,0x00,0x06,0x00,0x05,0x00,0x02,0x00,0xFF,0x0F,
    0xFA,0x0F,0xF5,0x0F,0xF0,0x0F,0xE9,0x0F,0xE2,0x0F,0xDA,0x0F,0xD2,0x0F,0xC8,0x0F,
    0x74,0x0F,0x87,0x0F,0x9B,0x0F,0xB8,0x0F,0xD5,0x0F,0xFA,0x0F,0x1F,0x00,0x4C,0x00,
    0x7A,0x00,0xAF,0x00,0xE3,0x00,0x1F,0x01,0x59,0x01,0x9A,0x01,0xD8,0x01,0x1D,0x02,
    0x18,0x05,0x0E,0x05,0xFF,0x04,0xE6,0x04,0xCA,0x04,0xA3,0x04,0x7C,0x04,0x4B,0x04,
    0x19,0x04,0xDF,0x03,0xA6,0x03,0x66,0x03,0x27,0x03,0xE3,0x02,0xA2,0x02,0x5D,0x02,
    0x69,0x0F,0x60,0x0F,0x5C,0x0F,0x5A,0x0F,0x5B,0x0F,0x5E,0x0F,0x63,0x0F,0x6A,0x0F,
    0x73,0x0F,0x7D,0x0F,0x87,0x0F,0x92,0x0F,0x9E,0x0F,0xA9,0x0F,0xB4,0x0F,0xBE,0x0F,
};

BYTE code tSU_COEF_1[] =
{
    0x02,0x00,0x04,0x00,0x03,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0xFD,0x0F,0xFA,0x0F,
    0xF6,0x0F,0xF1,0x0F,0xED,0x0F,0xE7,0x0F,0xE0,0x0F,0xDA,0x0F,0xD3,0x0F,0xCB,0x0F,
    0x9E,0x0F,0xB1,0x0F,0xC6,0x0F,0xE2,0x0F,0xFF,0x0F,0x21,0x00,0x45,0x00,0x6F,0x00,
    0x9B,0x00,0xCC,0x00,0xFC,0x00,0x34,0x01,0x69,0x01,0xA5,0x01,0xDD,0x01,0x1C,0x02,
    0xCE,0x04,0xC3,0x04,0xB5,0x04,0x9E,0x04,0x85,0x04,0x63,0x04,0x3F,0x04,0x14,0x04,
    0xE6,0x03,0xB3,0x03,0x7F,0x03,0x45,0x03,0x0E,0x03,0xCF,0x02,0x95,0x02,0x56,0x02,
    0x92,0x0F,0x88,0x0F,0x82,0x0F,0x7E,0x0F,0x7C,0x0F,0x7C,0x0F,0x7F,0x0F,0x83,0x0F,
    0x89,0x0F,0x90,0x0F,0x98,0x0F,0xA0,0x0F,0xA9,0x0F,0xB2,0x0F,0xBB,0x0F,0xC3,0x0F,
};

BYTE code tSU_COEF_2[] =
{
    0xFB,0x0F,0xFE,0x0F,0xFD,0x0F,0xFC,0x0F,0xFB,0x0F,0xFA,0x0F,0xF7,0x0F,0xF5,0x0F,
    0xF1,0x0F,0xED,0x0F,0xE9,0x0F,0xE4,0x0F,0xDE,0x0F,0xD9,0x0F,0xD3,0x0F,0xCD,0x0F,
    0xC7,0x0F,0xDB,0x0F,0xF0,0x0F,0x0C,0x00,0x27,0x00,0x49,0x00,0x6B,0x00,0x93,0x00,
    0xBC,0x00,0xEA,0x00,0x16,0x01,0x49,0x01,0x7A,0x01,0xB0,0x01,0xE3,0x01,0x1C,0x02,
    0x84,0x04,0x78,0x04,0x6C,0x04,0x57,0x04,0x42,0x04,0x23,0x04,0x04,0x04,0xDC,0x03,
    0xB4,0x03,0x86,0x03,0x59,0x03,0x26,0x03,0xF4,0x02,0xBD,0x02,0x89,0x02,0x50,0x02,
    0xBA,0x0F,0xAF,0x0F,0xA7,0x0F,0xA1,0x0F,0x9C,0x0F,0x9A,0x0F,0x9A,0x0F,0x9C,0x0F,
    0x9F,0x0F,0xA3,0x0F,0xA8,0x0F,0xAD,0x0F,0xB4,0x0F,0xBA,0x0F,0xC1,0x0F,0xC7,0x0F,
};

BYTE code tSU_COEF_3[] =
{
    0xF7,0x0F,0xFB,0x0F,0xFA,0x0F,0xF9,0x0F,0xF8,0x0F,0xF7,0x0F,0xF4,0x0F,0xF2,0x0F,
    0xEF,0x0F,0xEB,0x0F,0xE7,0x0F,0xE3,0x0F,0xDD,0x0F,0xD9,0x0F,0xD4,0x0F,0xCF,0x0F,
    0xDC,0x0F,0xF0,0x0F,0x05,0x00,0x21,0x00,0x3C,0x00,0x5D,0x00,0x7E,0x00,0xA5,0x00,
    0xCC,0x00,0xF8,0x00,0x23,0x01,0x54,0x01,0x82,0x01,0xB6,0x01,0xE6,0x01,0x1B,0x02,
    0x5F,0x04,0x52,0x04,0x47,0x04,0x33,0x04,0x1F,0x04,0x03,0x04,0xE6,0x03,0xC1,0x03,
    0x9B,0x03,0x71,0x03,0x46,0x03,0x15,0x03,0xE8,0x02,0xB3,0x02,0x82,0x02,0x4D,0x02,
    0xCE,0x0F,0xC3,0x0F,0xBA,0x0F,0xB3,0x0F,0xAD,0x0F,0xA9,0x0F,0xA8,0x0F,0xA8,0x0F,
    0xAA,0x0F,0xAC,0x0F,0xB0,0x0F,0xB4,0x0F,0xB9,0x0F,0xBE,0x0F,0xC4,0x0F,0xC9,0x0F,
};

BYTE code tSU_COEF_4[] =
{
    0xE0,0x0F,0xE9,0x0F,0xE8,0x0F,0xE9,0x0F,0xE8,0x0F,0xE7,0x0F,0xE4,0x0F,0xE3,0x0F,
    0xE1,0x0F,0xDF,0x0F,0xDC,0x0F,0xDB,0x0F,0xD8,0x0F,0xD7,0x0F,0xD5,0x0F,0xD5,0x0F,
    0x4C,0x00,0x61,0x00,0x78,0x00,0x92,0x00,0xAC,0x00,0xC9,0x00,0xE6,0x00,0x06,0x01,
    0x26,0x01,0x48,0x01,0x69,0x01,0x8D,0x01,0xAF,0x01,0xD4,0x01,0xF6,0x01,0x1B,0x02,
    0x9A,0x03,0x8B,0x03,0x84,0x03,0x75,0x03,0x68,0x03,0x56,0x03,0x44,0x03,0x2D,0x03,
    0x15,0x03,0xFA,0x02,0xE0,0x02,0xC0,0x02,0xA3,0x02,0x81,0x02,0x61,0x02,0x3C,0x02,
    0x3A,0x00,0x2B,0x00,0x1C,0x00,0x10,0x00,0x04,0x00,0xFA,0x0F,0xF2,0x0F,0xEA,0x0F,
    0xE4,0x0F,0xDF,0x0F,0xDB,0x0F,0xD8,0x0F,0xD6,0x0F,0xD4,0x0F,0xD4,0x0F,0xD4,0x0F,
};

#endif // End of #if(_EXTEND_TABLE_SUPPORT == _ON)

code BYTE *tSCALE_COEF_TABLE[] =
{
    tSU_COEF_0,     tSU_COEF_1,     tSU_COEF_2,     tSU_COEF_3,     tSU_COEF_4,
};

#if(_VIVID_COLOR_FUCTION == _ON)
//----------------------------------------------------------------------------------------------------
// Vivid Color Table
//----------------------------------------------------------------------------------------------------
BYTE code tEmpty_Table[] =
{
    0x00,
};

#if(_EXTEND_TABLE_SUPPORT == _ON)

BYTE xdata tDCC_CONTROL_MOVIE[_DCC_CONTROL_EXTEND]                      _at_ _DCC_CONTROL_MOVIE_EXTEND_ADDRESS;
BYTE xdata tDCC_CONTROL_PHOTO[_DCC_CONTROL_EXTEND]                      _at_ _DCC_CONTROL_PHOTO_EXTEND_ADDRESS;
BYTE xdata tDCC_CONTROL_GAME[_DCC_CONTROL_EXTEND]                       _at_ _DCC_CONTROL_GAME_EXTEND_ADDRESS;

BYTE xdata tDCC_USERCURVE_MOVIE[_DCC_USERCURVE_EXTEND]                  _at_ _DCC_USERCURVE_MOVIE_EXTEND_ADDRESS;
BYTE xdata tDCC_USERCURVE_PHOTO[_DCC_USERCURVE_EXTEND]                  _at_ _DCC_USERCURVE_PHOTO_EXTEND_ADDRESS;
BYTE xdata tDCC_USERCURVE_GAME[_DCC_USERCURVE_EXTEND]                   _at_ _DCC_USERCURVE_GAME_EXTEND_ADDRESS;

BYTE xdata tICM_MOVIE0[_ICM_TABLE_EXTEND]                               _at_ _ICM_MOVIE0_EXTEND_ADDRESS;
BYTE xdata tICM_MOVIE1[_ICM_TABLE_EXTEND]                               _at_ _ICM_MOVIE1_EXTEND_ADDRESS;
BYTE xdata tICM_MOVIE2[_ICM_TABLE_EXTEND]                               _at_ _ICM_MOVIE2_EXTEND_ADDRESS;
BYTE xdata tICM_MOVIE3[_ICM_TABLE_EXTEND]                               _at_ _ICM_MOVIE3_EXTEND_ADDRESS;

BYTE xdata tICM_PHOTO0[_ICM_TABLE_EXTEND]                               _at_ _ICM_PHOTO0_EXTEND_ADDRESS;
BYTE xdata tICM_PHOTO1[_ICM_TABLE_EXTEND]                               _at_ _ICM_PHOTO1_EXTEND_ADDRESS;
BYTE xdata tICM_PHOTO2[_ICM_TABLE_EXTEND]                               _at_ _ICM_PHOTO2_EXTEND_ADDRESS;
BYTE xdata tICM_PHOTO3[_ICM_TABLE_EXTEND]                               _at_ _ICM_PHOTO3_EXTEND_ADDRESS;

BYTE xdata tICM_GAME0[_ICM_TABLE_EXTEND]                                _at_ _ICM_GAME0_EXTEND_ADDRESS;
BYTE xdata tICM_GAME1[_ICM_TABLE_EXTEND]                                _at_ _ICM_GAME1_EXTEND_ADDRESS;
BYTE xdata tICM_GAME2[_ICM_TABLE_EXTEND]                                _at_ _ICM_GAME2_EXTEND_ADDRESS;
BYTE xdata tICM_GAME3[_ICM_TABLE_EXTEND]                                _at_ _ICM_GAME3_EXTEND_ADDRESS;

#else

//----------------------------------------------------------------------------------------------------
// DCC Table
//----------------------------------------------------------------------------------------------------
BYTE code tDCC_CONTROL_MOVIE[] =
{
    0x86, 0x66, 0xc3,
    0xb4, 0xce, 0x1e,
    0x10, 0x0c, 0x18,
};

BYTE code tDCC_CONTROL_PHOTO[] =
{
    0x86, 0x66, 0xc3,
    0xb4, 0xce, 0x1e,
    0x10, 0x0c, 0x18,
};

BYTE code tDCC_CONTROL_GAME[] =
{
    0x84, 0xaa, 0xc3,
    0xb4, 0xce, 0x1e,
    0x10, 0x0c, 0x18,
};

BYTE code tDCC_USERCURVE_MOVIE[] =
{
    0x04, 0x0c, 0x1a, 0x2b,
    0x41, 0x57, 0x6d, 0x80,
    0x95, 0xa9, 0xbd, 0xd0,
    0xe2, 0xf2, 0xfc, 0x00,
    0x10, 0x00, 0x00,
    0x80, 0x14, 0x34, 0x00,
};

BYTE code tDCC_USERCURVE_PHOTO[] =
{
    0x15, 0x1f, 0x2f, 0x3f,
    0x4f, 0x5f, 0x6f, 0x80,
    0x91, 0xa1, 0xb1, 0xc1,
    0xd1, 0xe1, 0xf1, 0x00,
    0x10, 0x00, 0x00,
    0x00, 0x14, 0x00, 0x00,
};

BYTE code tDCC_USERCURVE_GAME[] =
{
    0x0a, 0x18, 0x26, 0x36,
    0x46, 0x58, 0x6a, 0x80,
    0x96, 0xa8, 0xba, 0xca,
    0xd8, 0xe8, 0xf6, 0x00,
    0x10, 0x00, 0x00,
    0x64, 0x14, 0x32, 0x00
};

//----------------------------------------------------------------------------------------------------
// ICM Table
//----------------------------------------------------------------------------------------------------
BYTE code tICM_MOVIE0[] =
{
    0x00, 0x00, 0xcc,
    0x1f, 0x00, 0x3f, 0x00, 0x5f, 0x00, 0x7f, 0x00,
    0x5f, 0x00, 0x3f, 0x00, 0x1f, 0x00, 0x00, 0x00,
    0x14, 0xec, 0x2a, 0xd6, 0x3f, 0xc1, 0x54, 0xac,
    0x40, 0xc0, 0x2a, 0xd6, 0x14, 0xec, 0x00, 0x00,
    0x14, 0x14, 0x2a, 0x2a, 0x3f, 0x3f, 0x54, 0x54,
    0x40, 0x40, 0x2a, 0x2a, 0x14, 0x14, 0x00, 0x00,
};

BYTE code tICM_MOVIE1[] =
{
    0x04, 0x00, 0xcc,
    0x00, 0x1f, 0x00, 0x3f, 0x00, 0x5f, 0x00, 0x7f,
    0x00, 0x5f, 0x00, 0x3f, 0x00, 0x1f, 0x00, 0x00,
    0x14, 0x14, 0x2a, 0x2a, 0x3f, 0x3f, 0x54, 0x54,
    0x40, 0x40, 0x2a, 0x2a, 0x14, 0x14, 0x00, 0x00,
    0xec, 0x14, 0xd6, 0x2a, 0xc1, 0x3f, 0xac, 0x54,
    0xc0, 0x40, 0xd6, 0x2a, 0xec, 0x14, 0x00, 0x00,
};

BYTE code tICM_MOVIE2[] =
{
    0x08, 0x00, 0xcc,
    0xe1, 0x00, 0xc1, 0x00, 0xa1, 0x00, 0x81, 0x00,
    0xa1, 0x00, 0xc1, 0x00, 0xe1, 0x00, 0x00, 0x00,
    0xec, 0x14, 0xd6, 0x2a, 0xc1, 0x3f, 0xac, 0x54,
    0xc0, 0x40, 0xd6, 0x2a, 0xec, 0x14, 0x00, 0x00,
    0xec, 0xec, 0xd6, 0xd6, 0xc1, 0xc1, 0xac, 0xac,
    0xc0, 0xc0, 0xd6, 0xd6, 0xec, 0xec, 0x00, 0x00,
};

BYTE code tICM_MOVIE3[] =
{
    0x0c, 0x00, 0xcc,
    0x00, 0xe1, 0x00, 0xc1, 0x00, 0xa1, 0x00, 0x81,
    0x00, 0xa1, 0x00, 0xc1, 0x00, 0xe1, 0x00, 0x00,
    0xec, 0xec, 0xd6, 0xd6, 0xc1, 0xc1, 0xac, 0xac,
    0xc0, 0xc0, 0xd6, 0xd6, 0xec, 0xec, 0x00, 0x00,
    0x14, 0xec, 0x2a, 0xd6, 0x3f, 0xc1, 0x54, 0xac,
    0x40, 0xc0, 0x2a, 0xd6, 0x14, 0xec, 0x00, 0x00,
};

BYTE code tICM_PHOTO0[] =
{
    0x00, 0x00, 0xcc,
    0x0c, 0x00, 0x19, 0x00, 0x25, 0x00, 0x32, 0x00,
    0x25, 0x00, 0x19, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x08, 0xf8, 0x11, 0xef, 0x19, 0xe7, 0x21, 0xdf,
    0x19, 0xe7, 0x11, 0xef, 0x08, 0xf8, 0x00, 0x00,
    0x08, 0x08, 0x11, 0x11, 0x19, 0x19, 0x21, 0x21,
    0x19, 0x19, 0x11, 0x11, 0x08, 0x08, 0x00, 0x00,
};

BYTE code tICM_PHOTO1[] =
{
    0x04, 0x00, 0xcc,
    0x00, 0x0c, 0x00, 0x19, 0x00, 0x25, 0x00, 0x32,
    0x00, 0x25, 0x00, 0x19, 0x00, 0x0c, 0x00, 0x00,
    0x08, 0x08, 0x11, 0x11, 0x19, 0x19, 0x21, 0x21,
    0x19, 0x19, 0x11, 0x11, 0x08, 0x08, 0x00, 0x00,
    0xf8, 0x08, 0xef, 0x11, 0xe7, 0x19, 0xdf, 0x21,
    0xe7, 0x19, 0xef, 0x11, 0xf8, 0x08, 0x00, 0x00,
};

BYTE code tICM_PHOTO2[] =
{
    0x08, 0x00, 0xcc,
    0xf4, 0x00, 0xe7, 0x00, 0xdb, 0x00, 0xce, 0x00,
    0xdb, 0x00, 0xe7, 0x00, 0xf4, 0x00, 0x00, 0x00,
    0xf8, 0x08, 0xef, 0x11, 0xe7, 0x19, 0xdf, 0x21,
    0xe7, 0x19, 0xef, 0x11, 0xf8, 0x08, 0x00, 0x00,
    0xf8, 0xf8, 0xef, 0xef, 0xe7, 0xe7, 0xdf, 0xdf,
    0xe7, 0xe7, 0xef, 0xef, 0xf8, 0xf8, 0x00, 0x00,
};

BYTE code tICM_PHOTO3[] =
{
    0x0c, 0x00, 0xcc,
    0x00, 0xf4, 0x00, 0xe7, 0x00, 0xdb, 0x00, 0xce,
    0x00, 0xdb, 0x00, 0xe7, 0x00, 0xf4, 0x00, 0x00,
    0xf8, 0xf8, 0xef, 0xef, 0xe7, 0xe7, 0xdf, 0xdf,
    0xe7, 0xe7, 0xef, 0xef, 0xf8, 0xf8, 0x00, 0x00,
    0x08, 0xf8, 0x11, 0xef, 0x19, 0xe7, 0x21, 0xdf,
    0x19, 0xe7, 0x11, 0xef, 0x08, 0xf8, 0x00, 0x00,
};

BYTE code tICM_GAME0[] =
{
    0x00, 0x00, 0xcc,
    0xe0, 0x00, 0xc0, 0x00, 0xa0, 0x00, 0x80, 0x00,
    0xa0, 0x00, 0xc0, 0x00, 0xe0, 0x00, 0x00, 0x00,
    0xea, 0x16, 0xd6, 0x2a, 0xc0, 0x40, 0xaa, 0x56,
    0xc0, 0x40, 0xd5, 0x2b, 0xea, 0x16, 0x00, 0x00,
    0xea, 0xea, 0xd6, 0xd6, 0xc0, 0xc0, 0xaa, 0xaa,
    0xc0, 0xc0, 0xd5, 0xd5, 0xea, 0xea, 0x00, 0x00,
};

BYTE code tICM_GAME1[] =
{
    0x04, 0x00, 0xcc,
    0x00, 0xe0, 0x00, 0xc0, 0x00, 0xa0, 0x00, 0x80,
    0x00, 0xa0, 0x00, 0xc0, 0x00, 0xe0, 0x00, 0x00,
    0xea, 0xea, 0xd6, 0xd6, 0xc0, 0xc0, 0xaa, 0xaa,
    0xc0, 0xc0, 0xd5, 0xd5, 0xea, 0xea, 0x00, 0x00,
    0x16, 0xea, 0x2a, 0xd6, 0x40, 0xc0, 0x56, 0xaa,
    0x40, 0xc0, 0x2b, 0xd5, 0x16, 0xea, 0x00, 0x00,
};

BYTE code tICM_GAME2[] =
{
    0x08, 0x00, 0xcc,
    0x20, 0x00, 0x40, 0x00, 0x60, 0x00, 0x7f, 0x00,
    0x60, 0x00, 0x40, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x16, 0xea, 0x2a, 0xd6, 0x40, 0xc0, 0x56, 0xaa,
    0x40, 0xc0, 0x2b, 0xd5, 0x16, 0xea, 0x00, 0x00,
    0x16, 0x16, 0x2a, 0x2a, 0x40, 0x40, 0x56, 0x56,
    0x40, 0x40, 0x2b, 0x2b, 0x16, 0x16, 0x00, 0x00,
};

BYTE code tICM_GAME3[] =
{
    0x0c, 0x00, 0xcc,
    0x00, 0x20, 0x00, 0x40, 0x00, 0x60, 0x00, 0x7f,
    0x00, 0x60, 0x00, 0x40, 0x00, 0x20, 0x00, 0x00,
    0x16, 0x16, 0x2a, 0x2a, 0x40, 0x40, 0x56, 0x56,
    0x40, 0x40, 0x2b, 0x2b, 0x16, 0x16, 0x00, 0x00,
    0xea, 0x16, 0xd6, 0x2a, 0xc0, 0x40, 0xaa, 0x56,
    0xc0, 0x40, 0xd5, 0x2b, 0xea, 0x16, 0x00, 0x00,
};

#endif // End of #if(_EXTEND_TABLE_SUPPORT == _ON)

code BYTE *tDCC_CONTROL[] =
{
    tDCC_CONTROL_MOVIE,     tDCC_CONTROL_PHOTO,         tDCC_CONTROL_GAME
};

code BYTE  *tDCC_USERCURVE[] =
{
    tDCC_USERCURVE_MOVIE,   tDCC_USERCURVE_PHOTO,       tDCC_USERCURVE_GAME
};

code BYTE  *tICM_TABLE[] =
{
    tICM_MOVIE0,        tICM_MOVIE1,        tICM_MOVIE2,        tICM_MOVIE3,        tEmpty_Table,       tEmpty_Table,
    tICM_PHOTO0,        tICM_PHOTO1,        tICM_PHOTO2,        tICM_PHOTO0,        tEmpty_Table,       tEmpty_Table,
    tICM_GAME0,         tICM_GAME1,         tICM_GAME2,         tICM_GAME3,         tEmpty_Table,       tEmpty_Table,
};

#endif // End of #if(_VIVID_COLOR_FUCTION == _ON)

#else // Else of #ifdef __ADJUST__

extern BYTE code tPALETTE_0[];
extern code BYTE *tSCALE_COEF_TABLE[];

#if(_VIVID_COLOR_FUCTION == _ON)
extern code BYTE *tDCC_CONTROL[];
extern code BYTE  *tDCC_USERCURVE[];
extern code BYTE  *tICM_TABLE[];
#endif

#endif // End of #ifdef __ADJUST__



#ifdef __REALTEK_OSD__

//--------------------------------------------------
// Text Width Table Used by COsdFxLoadText()
//--------------------------------------------------
BYTE code tOSD_CHARWIDTH_TABLE_GLOBAL[][2] =
{
    {_A_, (8 << 4) | 12},
    {_B_, (8 << 4) | 12},
    {_C_, (8 << 4) | 12},
    {_D_, (8 << 4) | 12},
    {_E_, (8 << 4) | 11},
    {_F_, (8 << 4) | 10},
    {_G_, (8 << 4) | 12},
    {_H_, (8 << 4) | 12},
    {_I_, (8 << 4) | 4},
    {_J_, (8 << 4) | 10},
    {_K_, (8 << 4) | 12},
    {_L_, (8 << 4) | 12},
    {_M_, (8 << 4) | 12},
    {_N_, (8 << 4) | 12},
    {_O_, (8 << 4) | 12},
    {_P_, (8 << 4) | 12},
    {_Q_, (8 << 4) | 12},
    {_R_, (8 << 4) | 12},
    {_S_, (8 << 4) | 10},
    {_T_, (8 << 4) | 12},
    {_U_, (8 << 4) | 12},
    {_V_, (8 << 4) | 12},
    {_W_, (8 << 4) | 12},
    {_X_, (8 << 4) | 12},
    {_Y_, (8 << 4) | 12},
    {_Z_, (8 << 4) | 9},

    {_a_, (8 << 4) | 10},
    {_b_, (8 << 4) | 10},
    {_c_, (8 << 4) | 9},
    {_d_, (8 << 4) | 10},
    {_e_, (8 << 4) | 9},
    {_f_, (8 << 4) | 8},
    {_g_, (8 << 4) | 10},
    {_h_, (8 << 4) | 10},
    {_i_, (8 << 4) | 4},
    {_j_, (8 << 4) | 5},
    {_k_, (8 << 4) | 9},
    {_l_, (8 << 4) | 4},
    {_m_, (8 << 4) | 12},
    {_n_, (8 << 4) | 10},
    {_o_, (8 << 4) | 10},
    {_p_, (8 << 4) | 10},
    {_q_, (8 << 4) | 10},
    {_r_, (8 << 4) | 7},
    {_s_, (8 << 4) | 9},
    {_t_, (8 << 4) | 7},
    {_u_, (8 << 4) | 10},
    {_v_, (8 << 4) | 9},
    {_w_, (8 << 4) | 12},
    {_x_, (8 << 4) | 9},
    {_y_, (8 << 4) | 11},
    {_z_, (8 << 4) | 9},

    {___, (8 << 4) | 12},
    {_0_, (8 << 4) | 10},
    {_1_, (8 << 4) | 10},
    {_2_, (8 << 4) | 10},
    {_3_, (8 << 4) | 10},
    {_4_, (8 << 4) | 10},
    {_5_, (8 << 4) | 10},
    {_6_, (8 << 4) | 10},
    {_7_, (8 << 4) | 10},
    {_8_, (8 << 4) | 10},
    {_9_, (8 << 4) | 10},

    {_END_, _END_},
};

BYTE code tOSD_CHARWIDTH_TABLE_0[][2] =
{
    {_END_, _END_},
};

BYTE code tOSD_CHARWIDTH_TABLE_1[][2] =
{
    {_END_, _END_},
};

BYTE code tOSD_CHARWIDTH_TABLE_2[][2] =
{
    {_END_, _END_},
};

BYTE code tOSD_CHARWIDTH_TABLE_3[][2] =
{
    {_END_, _END_},
};

BYTE code tOSD_CHARWIDTH_TABLE_4[][2] =
{
    {_END_, _END_},
};

BYTE code tOSD_CHARWIDTH_TABLE_5[][2] =
{
    {_END_, _END_},
};

BYTE code tOSD_CHARWIDTH_TABLE_6[][2] =
{
    {_END_, _END_},
};

BYTE code tOSD_CHARWIDTH_TABLE_7[][2] =
{
    {_END_, _END_},
};

code BYTE *tOSD_CHARWIDTH_TABLE[9] =
{
    tOSD_CHARWIDTH_TABLE_GLOBAL,
    tOSD_CHARWIDTH_TABLE_0,     tOSD_CHARWIDTH_TABLE_1,     tOSD_CHARWIDTH_TABLE_2,     tOSD_CHARWIDTH_TABLE_3,
    tOSD_CHARWIDTH_TABLE_4,     tOSD_CHARWIDTH_TABLE_5,     tOSD_CHARWIDTH_TABLE_6,     tOSD_CHARWIDTH_TABLE_7,
};

//--------------------------------------------------
// OSD Char Commands Map Information (Rows, Cols)
//--------------------------------------------------
WORD code tOSD_OSDMAP_INF[][2] =
{
    {24, 41},
    {24, 30},
    {7, 30},
    {0, 0},
    {0, 0},
    {25, 28},
};

//--------------------------------------------------
// OSD Row Command Table
//--------------------------------------------------
BYTE code tOSD_ROW_COMMAND0[] =
{
    FONTBYTE0(0x000),
    0x80, _REPEAT_, 24, _NEXT_,

    FONTBYTE1(0x000),
    0x88, _REPEAT_, 24, _NEXT_,

    FONTBYTE2(0x000),
    41, _REPEAT_, 24, _NEXT_,// zhangpin 20101109 

    FONTBYTE0(24),
    0x00,

    _END_
};

BYTE code tOSD_ROW_COMMAND1[] =
{
    FONTBYTE0(0x000),
    0x80, _REPEAT_, 24, _NEXT_,

    FONTBYTE1(0x000),
    0x88, _REPEAT_, 24, _NEXT_,

    FONTBYTE2(0x000),
    30, _REPEAT_, 24, _NEXT_,

    FONTBYTE0(24),
    0x00,

    _END_
};

BYTE code tOSD_ROW_COMMAND2[] =
{
    FONTBYTE0(0x000),
    0x80, _REPEAT_, 7, _NEXT_,

    FONTBYTE1(0x000),
    0x88, _REPEAT_, 7, _NEXT_,

    FONTBYTE2(0x000),
    30, _REPEAT_, 7, _NEXT_,

    FONTBYTE0(7),
    0x00,

    _END_
};


//--------------------------------------------------
// Window Command Table Used by COsdFxDrawWindow()
//--------------------------------------------------
BYTE code tOSD_WINDOW0_STYLE[] =
{
    WINNO(0),
    0x1B,                               // Byte 0 of 100h
    (_CP_WHITE << 4) | _CP_SELECTBOTTOM, // Byte 1 of 100h
    0x36,                               // Byte 2 of 100h
    0x00,                               // Byte 0 of 103h
    0x10 | _CP_BLACK,                   // Byte 1 of 103h
    0x59                                // Byte 2 of 103h

};

BYTE code tOSD_WINDOW1_STYLE[] =
{
    WINNO(1),
    0x00,                               // Byte 0 of 104h
    (_CP_BLACK << 4) | _CP_WHITE,        // Byte 1 of 104h
    0xf9,                               // Byte 2 of 104h
    0x00,                               // Byte 0 of 107h
    0x20 | _CP_BLACK,                   // Byte 1 of 107h
    0x51                                // Byte 2 of 107h
};

BYTE code tOSD_WINDOW2_STYLE[] =
{
    WINNO(2),
    0x09,                               // Byte 0 of 108h
    (_CP_WHITE << 4) | _CP_WHITE,        // Byte 1 of 108h
    0x00,                               // Byte 2 of 108h
    0x00,                               // Byte 0 of 10bh
    0x20 | _CP_BLACK,                   // Byte 1 of 10bh
    0x19                                // Byte 2 of 10bh
};

BYTE code tOSD_WINDOW3_STYLE[] =
{
    WINNO(3),
    0x3f,                               // Byte 0 of 10ch
    (_CP_BLACK << 4) | _CP_WHITE,        // Byte 1 of 10ch
    0xfc,                               // Byte 2 of 10ch
    0x00,                               // Byte 0 of 10fh
    0x70 | _CP_BLACK,                   // Byte 1 of 10fh
    0x01                                // Byte 2 of 10fh
};

BYTE code tOSD_WINDOW4_STYLE[] =
{
    WINNO(4),
    0x24,                               // Byte 0 of 110h
    (_CP_BLACK << 4) | _CP_WHITE,        // Byte 1 of 110h
    0xf9,                               // Byte 2 of 110h
    0x00,                               // Byte 0 of 113h
    0x20 | _CP_BLACK,                   // Byte 1 of 113h
    0x51                                // Byte 2 of 113h
};

BYTE code tOSD_WINDOW5_STYLE[] =
{
    WINNO(5),
    0x09,                               // Byte 0 of 100h
    (_CP_WHITE << 4) | _CP_WHITE,        // Byte 1 of 100h
    0x00,                               // Byte 2 of 100h
    0x00,                               // Byte 0 of 103h
    0x20 | _CP_BLACK,                   // Byte 1 of 103h
    0x1d                                // Byte 2 of 103h

};

BYTE code tOSD_WINDOW6_STYLE[] =
{
    WINNO(6),
    0x3f,                               // Byte 0 of 118h
    (_CP_BLACK << 4) | _CP_WHITE,        // Byte 1 of 118h
    0xfc,                               // Byte 2 of 118h
    0x00,                               // Byte 0 of 11bh
    0x70 | _CP_BLACK,                   // Byte 1 of 11bh
    0x01                                // Byte 2 of 11bh
};

BYTE code tOSD_WINDOW6_ACC_STYLE[] =
{
    WINNO(6),
    0x1b,                               // Byte 0 of 118h
    (_CP_RED << 4) | _CP_GREEN,        // Byte 1 of 118h
    0xfc,                               // Byte 2 of 118h
    0x00,                               // Byte 0 of 11bh
    0x70 | _CP_BLUE,                   // Byte 1 of 11bh
    0x01                                // Byte 2 of 11bh
};

BYTE code tOSD_WINDOW7_STYLE[] =
{
    WINNO(7),
    0x3f,                               // Byte 0 of 11ch
    (_CP_BLACK << 4) | _CP_WHITE,        // Byte 1 of 11ch
    0xfc,                               // Byte 2 of 11ch
    0x00,                               // Byte 0 of 11fh
    0x40 | _CP_BLACK,                   // Byte 1 of 11fh
    0x01                                // Byte 2 of 11fh
};

//--------------------------------------------------
// Main Menu Text Table
//--------------------------------------------------
BYTE code tOSD_COLOR_STR[] =
{
    _C_, _o_, _l_, _o_, _r_, _END_,
    _C_, _o_, _u_, _l_, _e_, _u_, _r_, _END_,
    _F_, _a_, _r_, _b_, _e_, _END_,
    _C_, _o_, _l_, _o_, _r_, _END_,
    0x60, 0x00, 0x61, 0x00, 0x62, 0x00, 0x63, _END_,
    0x60, 0x00, 0x61, 0x00, 0x8b, 0x00, 0x63, _END_,
    0x60, 0x00, 0x61, 0x00, 0x62, 0x00, 0x63, 0x00, 0x64, _END_,
    _C_, _o_, _l_, _o_, _r_, _END_,
};

BYTE code tOSD_IMGCONTROL_STR[] =
{
    _I_, _m_, _a_, _g_, _e_, 0x00, _S_, _e_, _t_, _t_, _i_, _n_, _g_, _END_,
    _I_, _m_, _a_, _g_, _e_, 0x00, _S_, _e_, _t_, _t_, _i_, _n_, _g_, _END_,
    _B_, _i_, _l_, _d_, _e_, _END_,
    _I_, _m_, _a_, _g_, _e_, _n_, _END_,
    0x64, 0x00, 0x65, 0x00, 0x62, 0x00, 0x63, _END_,
    0x64, 0x00, 0x65, 0x00, 0x8b, 0x00, 0x63, _END_,
    0x65, 0x00, 0x66, 0x00, 0x63, 0x00, 0x64, _END_,
    _I_, _m_, _a_, _g_, _e_, 0x00, _S_, _e_, _t_, _t_, _i_, _n_, _g_, _END_,
};

BYTE code tOSD_OSD_STR[] =
{
    _O_, _S_, _D_, ___, _M_, _e_, _n_, _u_, _END_,
    _M_, _e_, _n_, _u_, 0x00, _O_, _S_, _D_, _END_,
    _O_, _S_, _D_, 0X00, _M_, _e_, _n_, 0x4b, _END_,
    _M_, _e_, _n_, 0x4e, 0x00, _d_, _e_, _O_, _S_, _D_, _END_,
    0x68, 0x00, 0x69, 0x00, 0x62, 0x00, 0x63, _END_,
    0x8c, 0x00, 0x8d, 0x00, 0x8b, 0x00, 0x63, _END_,
    0x69, 0x00, 0x6a, 0x00, 0x62, 0x00, 0x63, 0x00, 0x64, _END_,
    _O_, _S_, _D_, _END_,
};

BYTE code tOSD_SIGNAL_STR[] =
{
	_S_, _I_, _G_, _N_, _A_, _L_, 0x00, _S_, _W_, _I_, _T_, _C_, _H_, _END_,
	_S_, _I_, _G_, _N_, _A_, _L_, 0x00, _S_, _W_, _I_, _T_, _C_, _H_, _END_,
	_S_, _I_, _G_, _N_, _A_, _L_, 0x00, _S_, _W_, _I_, _T_, _C_, _H_, _END_,
	_S_, _I_, _G_, _N_, _A_, _L_, 0x00, _S_, _W_, _I_, _T_, _C_, _H_, _END_,
	_S_, _I_, _G_, _N_, _A_, _L_, 0x00, _S_, _W_, _I_, _T_, _C_, _H_, _END_,
	_S_, _I_, _G_, _N_, _A_, _L_, 0x00, _S_, _W_, _I_, _T_, _C_, _H_, _END_,
	_S_, _I_, _G_, _N_, _A_, _L_, 0x00, _S_, _W_, _I_, _T_, _C_, _H_, _END_,						
    /*0x88, 0x00, 0x99, 0x00, 0x8c, 0x00, 0x91, _END_,
    _S_, _i_, _g_, _n_, _a_, _l_, 0x00, _S_, _o_, _u_, _r_, _c_, _e_, _END_,
    _E_, _n_, _t_, _r_, 0x52, _e_, _END_,
    _S_, _i_, _g_, _n_, _a_, _l_, _e_, _i_, _n_, _g_, _a_, _n_, _g_, _END_,
    _E_, _n_, _t_, _r_, _a_, _d_, _a_, _END_,
    0x88, 0x00, 0x89, 0x00, 0x68, 0x00, 0x6c, _END_,
    0x89, 0x00, 0x8a, 0x00, 0x8b, 0x00, 0x62, 0x00, 0x73, _END_,
    _S_, _i_, _g_, _n_, _a_, _l_, 0x00, _S_, _o_, _u_, _r_, _c_, _e_, _END_,*/
};

BYTE code tOSD_SIGNAL_DVI[] =
{
    _D_,_V_,_I_,_END_,
    _D_,_V_,_I_,_END_,
		
};

BYTE code tOSD_SIGNAL_VGA[] =
{
    _V_,_G_,_A_,_END_,
    _D_,_V_,_I_,_END_,
};


BYTE code *tOSD_SIGNAL_TYPE[] =
{
  tOSD_SIGNAL_VGA,   tOSD_SIGNAL_DVI
};

BYTE code tOSD_YES[] =
{
       0x60,_END_,
    _Y_,_E_,_S_,_END_,

    
};
BYTE code tOSD_NO[] =
{
       0x61,_END_,
     _N_,_O_,_END_,

};


BYTE code tOSD_AUDIO_STR[] =
{
    0x92, 0x00, 0x74,0x00,0x76, _END_,
    _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _END_,
    _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _e_, _END_,
    _K_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _END_,
    _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _e_, _END_,
    0x73, 0x00, 0x74, _END_,
    0x70, 0x00, 0x71, 0x00, 0x72, 0x00, 0x61, 0x00, 0x73, 0x00, 0x72, _END_,
    _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _END_,
};

BYTE code tOSD_SPECIAL_STR[] =
{
    _S_, _p_, _e_, _c_, _i_, _a_, _l_, _END_,
    _S_, _p_, _e_, _c_, _i_, _a_, _l_, _END_,
    _S_, _p_, _e_, _c_, _i_, _a_, _l_, _END_,
    _S_, _p_, _e_, _c_, _i_, _a_, _l_, _END_,
    _S_, _p_, _e_, _c_, _i_, _a_, _l_, _END_,
    _S_, _p_, _e_, _c_, _i_, _a_, _l_, _END_,
    _S_, _p_, _e_, _c_, _i_, _a_, _l_, _END_,
    _S_, _p_, _e_, _c_, _i_, _a_, _l_, _END_,

};

BYTE code tOSD_FACTORY_MODE_STR[] =
{
    0x6F, 0x00, 0x70, 0x00, 0x71, 0x00, 0x72, _END_,
    _F_, _a_, _c_, _t_, _o_, _r_, _y_, 0x00, _M_, _o_, _d_, _e_, _END_,
    _F_, _a_, _c_, _t_, _o_, _r_, _y_, 0x00, _M_, _o_, _d_, _e_, _END_,
    _F_, _a_, _c_, _t_, _o_, _r_, _y_, 0x00, _M_, _o_, _d_, _e_, _END_,
    _F_, _a_, _c_, _t_, _o_, _r_, _y_, 0x00, _M_, _o_, _d_, _e_, _END_,
    _F_, _a_, _c_, _t_, _o_, _r_, _y_, 0x00, _M_, _o_, _d_, _e_, _END_,
    _F_, _a_, _c_, _t_, _o_, _r_, _y_, 0x00, _M_, _o_, _d_, _e_, _END_,
    _F_, _a_, _c_, _t_, _o_, _r_, _y_, 0x00, _M_, _o_, _d_, _e_, _END_,
};

#if(_DDCCI_SUPPORT == _ON)
BYTE code tOSD_DDCCISUPPORT_STR[] =
{
    _D_,_D_,_C_,_C_,_I_,0x00,_S_,_u_,_p_,_p_,_o_,_r_,_t_,_END_,
    _D_,_D_,_C_,_C_,_I_,0x00,_S_,_u_,_p_,_p_,_o_,_r_,_t_,_END_,
    _D_,_D_,_C_,_C_,_I_,0x00,_S_,_u_,_p_,_p_,_o_,_r_,_t_,_END_,
    _D_,_D_,_C_,_C_,_I_,0x00,_S_,_u_,_p_,_p_,_o_,_r_,_t_,_END_,
    _D_,_D_,_C_,_C_,_I_,0x00,_S_,_u_,_p_,_p_,_o_,_r_,_t_,_END_,
    _D_,_D_,_C_,_C_,_I_,0x00,_S_,_u_,_p_,_p_,_o_,_r_,_t_,_END_,
    _D_,_D_,_C_,_C_,_I_,0x00,_S_,_u_,_p_,_p_,_o_,_r_,_t_,_END_,
    _D_,_D_,_C_,_C_,_I_,0x00,_S_,_u_,_p_,_p_,_o_,_r_,_t_,_END_,
};
#endif

BYTE code tOSD_DICOM_STR[] =
{
    _D_, _I_, _C_, _O_, _M_,  _END_,
    _D_, _I_, _C_, _O_, _M_,  _END_,
    _D_, _I_, _C_, _O_, _M_,  _END_,
    _D_, _I_, _C_, _O_, _M_,  _END_,
    _D_, _I_, _C_, _O_, _M_,  _END_,
    _D_, _I_, _C_, _O_, _M_,  _END_,
    _D_, _I_, _C_, _O_, _M_,  _END_,
    _D_, _I_, _C_, _O_, _M_,  _END_,
};

 WORD xdata  tOSD_DICOMlumi[11] ;/*=
{
   2255,2033,1787,1049,1310,1052,697,347,1049,1049,1049	//1049 DICOM 500	
};
/*
WORD code  tBKLIT_DICOMlumi[] =
{
    0x03FD,0x0452,0x04A8,0x04D8,0x04FB,0x0554,0x05A2,0x05A9
};
*/
BYTE code tOSD_DICOM_350[]=
{
   _3_,_5_,_0_,_END_,
   
};

BYTE code tOSD_DICOM_400[]=
{
  _4_,_0_,_0_,_END_,
};
BYTE code tOSD_DICOM_450[]=
{
  _4_,_5_,_0_,_END_,
};
BYTE code tOSD_DICOM_500[]=
{
  _5_,_0_,_0_,_END_,
};
BYTE code tOSD_DICOM_550[]=
{
  _5_,_5_,_0_,_END_,
};
BYTE code tOSD_DICOM_600[]=
{
  _6_,_0_,_0_,_END_,
};
BYTE code tOSD_DICOM_650[]=
{
  _6_,_5_,_0_,_END_,
};
BYTE code tOSD_DICOM_700[]=
{
  _7_,_0_,_0_,_END_,
};

BYTE code tOSD_DICOM_NOT_USED[]=
{
  0x6a,0x00,0x6c,0x00,_END_,
};


BYTE code* tOSD_DICOM_STR2[]=
{
   tOSD_DICOM_350,   tOSD_DICOM_400,  tOSD_DICOM_450,   tOSD_DICOM_500,
   
   tOSD_DICOM_550,   tOSD_DICOM_600,  tOSD_DICOM_650,  tOSD_DICOM_700,tOSD_DICOM_NOT_USED
};


BYTE code tOSD_GAMMA_STR[] =
{
    _G_, _A_, _M_, _M_, _A_, _END_,
    _G_, _A_, _M_, _M_, _A_, _END_,
    _G_, _A_, _M_, _M_, _A_, _END_,
    _G_, _A_, _M_, _M_, _A_, _END_,
    _G_, _A_, _M_, _M_, _A_, _END_,
    _G_, _A_, _M_, _M_, _A_, _END_,
    _G_, _A_, _M_, _M_, _A_, _END_,
    _G_, _A_, _M_, _M_, _A_, _END_,
};


BYTE code tOSD_DSA_STR[]=
{_D_, _S_, _A_,  _END_,
_D_, _S_, _A_,  _END_,
_D_, _S_, _A_,  _END_,
_D_, _S_, _A_,  _END_,
};
BYTE code tOSD_DSI_STR[]=
{_D_, _S_, _I_,  _END_,
_D_, _S_, _I_,  _END_,
_D_, _S_, _I_,  _END_,
_D_, _S_, _I_,  _END_,
};
BYTE code tOSD_CT_STR[]=// sjp 110530
{
_C_, _T_, _END_,
_C_, _T_, _END_,
_C_, _T_, _END_,
_C_, _T_, _END_,
};

BYTE code tOSD_MRI_STR[]=//sjp 110530
{
_M_, _R_,_I_ ,0x00,_J_,_U_,_S_,_H_,_A_, _END_,
_M_, _R_,_I_ ,0x00,_J_,_U_,_S_,_H_,_A_, _END_,
_M_, _R_,_I_ ,0x00,_J_,_U_,_S_,_H_,_A_, _END_,
_M_, _R_,_I_ , 0x00,_J_,_U_,_S_,_H_,_A_, _END_,
};



BYTE code tOSD_GAMMA_20[] =
{
    _2_,0x0b,_2_, _END_,
};

BYTE code tOSD_GAMMA_22[] =
{
    _2_,0x0b,_4_, _END_,
};

BYTE code tOSD_GAMMA_24[] =
{
    _2_,0x0b,_6_, _END_,
};

BYTE code *tOSD_GAMMA_STR2[] =
{
tOSD_GAMMA_20, tOSD_GAMMA_22, tOSD_GAMMA_24
};


BYTE code tOSD_BRIGHTNESS_STR[] =
{
    0x75, 0x00, 0x76, _END_,
    _B_, _r_, _i_, _g_, _h_, _t_, _n_, _e_, _s_, _s_, _END_,
    _L_, _u_, _m_, _i_, _n_, _o_, _s_, _i_, _t_, 0x52, _END_,
    _H_, _e_, _l_, _l_, _i_, _g_, _k_, _e_, _i_, _t_, _END_,
    _B_, _r_, _i_, _l_, _l_, _o_, _END_,
    0x75, 0x00, 0x76, _END_,
    _B_, _r_, _i_, _g_, _h_, _t_, _n_, _e_, _s_, _s_, _END_,
    0x74, 0x00, 0x61, 0x00, 0x75, 0x00, 0x72, 0x00, 0x76, 0x00, 0x73, _END_,
};

BYTE code tOSD_AUTO_ADJUST_STR[] =
{
   // 0x68, 0x00, 0x69, 0x00, 0x62, 0x00, 0x63,  _END_,
    _A_, _U_, _T_, _O_, 0x00,_A_, _D_,_J_,_U_,_S_,_T_,_END_,
    _A_, _U_, _T_, _O_, 0x00,_A_, _D_,_J_,_U_,_S_,_T_,_END_,
    _A_, _U_, _T_, _O_, 0x00,_A_, _D_,_J_,_U_,_S_,_T_,_END_,
    _A_, _U_, _T_, _O_, 0x00,_A_, _D_,_J_,_U_,_S_,_T_,_END_,
    _A_, _U_, _T_, _O_, 0x00,_A_, _D_,_J_,_U_,_S_,_T_,_END_,
    _A_, _U_, _T_, _O_, 0x00,_A_, _D_,_J_,_U_,_S_,_T_,_END_,
    _A_, _U_, _T_, _O_, 0x00,_A_, _D_,_J_,_U_,_S_,_T_,_END_,
    _A_, _U_, _T_, _O_, 0x00,_A_, _D_,_J_,_U_,_S_,_T_,_END_,
};



#if(_DDCCI_SUPPORT == _ON)
code BYTE *tTEXT_TABLE[] =
{
    tOSD_COLOR_STR,     tOSD_IMGCONTROL_STR,    tOSD_OSD_STR,       tOSD_SIGNAL_STR,
    tOSD_AUDIO_STR,     tOSD_SPECIAL_STR,       tOSD_FACTORY_MODE_STR,
    tOSD_DDCCISUPPORT_STR
};
#else
/*
code BYTE *tTEXT_TABLE[] =
{
    tOSD_BRIGHTNESS_STR,     tOSD_CONTRAST_STR,    tOSD_OSD_STR,       tOSD_SIGNAL_STR,
    tOSD_AUDIO_STR,     tOSD_SPECIAL_STR,       tOSD_FACTORY_MODE_STR
};

*/
code BYTE *tTEXT_TABLE[] =
{
   tOSD_DICOM_STR,     tOSD_GAMMA_STR,     tOSD_BRIGHTNESS_STR,    tOSD_AUDIO_STR,  
  tOSD_SIGNAL_STR ,   tOSD_AUTO_ADJUST_STR,       tOSD_FACTORY_MODE_STR
};


#endif

//--------------------------------------------------
// Menu Icon Table
//--------------------------------------------------
BYTE code tOSD_POINT_ICO[] =
{
    0x6a, 0x6b, _END_,
};

BYTE code tOSD_POS0_ICO[] =
{
    0x50, 0x51, 0x52, _NEXT_,
    0x53, 0x54, 0x55, _END_,
};

BYTE code tOSD_POS1_ICO[] =
{
    0x56, 0x57, 0x58, _NEXT_,
    0x59, 0x5a, 0x5b, _END_,
};

BYTE code tOSD_POS2_ICO[] =
{
    0x5c, 0x5d, 0x5e, _NEXT_,
    0x5f, 0x60, 0x61, _END_,
};

BYTE code tOSD_POS3_ICO[] =
{
    0x62, 0x63, 0x64, _NEXT_,
    0x65, 0x66, 0x67, _END_,
};

BYTE code tOSD_POSITION0_ICO[] =
{
    0x80, 0x81, 0x82, _NEXT_,
    0x83, 0x84, 0x85, _END_,
};

BYTE code tOSD_POSITION1_ICO[] =
{
    0x86, 0x87, 0x88, _NEXT_,
    0x89, 0x8a, 0x8b, _END_,
};

BYTE code tOSD_POSITION2_ICO[] =
{
    0x8c, 0x8d, 0x8e, _NEXT_,
    0x8f, 0x90, 0x91, _END_,
};

BYTE code tOSD_POSITION3_ICO[] =
{
    0x92, 0x93, 0x94, _NEXT_,
    0x95, 0x96, 0x97, _END_,
};

BYTE code tOSD_POSITION4_ICO[] =
{
    0x98, 0x99, 0x9a, _NEXT_,
    0x9b, 0x9c, 0x9d, _END_,
};

BYTE code tOSD_POSITION5_ICO[] =
{
    0x9e, 0x9f, 0xa0, _NEXT_,
    0xa1, 0xa2, 0xa3, _END_,
};

BYTE code tOSD_POSITION6_ICO[] =
{
    0xa4, 0xa5, 0xa6, _NEXT_,
    0xa7, 0xa8, 0xa9, _END_,
};

BYTE code tOSD_RT_MARK_ICO1[] =
{
    0x6c, 0x6d, 0x6e, 0x6f,0x70,0x71,0x72,0x73,_NEXT_,
    0x74, 0x75, 0x76, 0x77,0x78,0x79,0x7A,0x7B,0x7C, 0x7D,  _END_,
};

BYTE code tOSD_RT_MARK_ICO2[] =
{
    0x6c, 0x6d, 0x6e, _NEXT_,
    0x78, 0x70, 0x79, 0x69, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, _END_,
};

BYTE code tOSD_BACK_ICO[] =
{
    0x7a, 0x7b, 0x7c, _NEXT_,
    0x7d, 0x7e, 0x7f, _END_,
};


//--------------------------------------------------
// Hotkey function Table
//--------------------------------------------------
BYTE code tOSD_AUTO_ICO[] =
{
    0x60, 0x61, 0x62, _NEXT_,
    0x63, 0x64, 0x65, _END_,
};

BYTE code tOSD_AUTO_STR[] =
{
	_A_, _u_, _t_, _o_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, 0x0b, 0x0b, 0x0b, _END_,
	_A_, _u_, _t_, _o_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, 0x0b, 0x0b, 0x0b, _END_,
	_A_, _u_, _t_, _o_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, 0x0b, 0x0b, 0x0b, _END_,
	_A_, _u_, _t_, _o_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, 0x0b, 0x0b, 0x0b, _END_,
	_A_, _u_, _t_, _o_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, 0x0b, 0x0b, 0x0b, _END_,
	_A_, _u_, _t_, _o_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, 0x0b, 0x0b, 0x0b, _END_,
 /*   0x66, 0x00, 0x68, 0x00, 0x6b, 0x00, 0x6a, 0x0b, 0x0b, 0x0b, _END_,
    _A_, _u_, _t_, _o_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, 0x0b, 0x0b, 0x0b, _END_,
    _A_, _u_, _t_, _o_, _r_, 0x52, _g_, _l_, _a_, _g_, _e_, 0x0b, 0x0b, 0x0b, _END_,
    _A_, _u_, _t_, _o_, _m_, 0x0b, _A_, _b_, _g_, _l_, 0x0b, 0x0b, 0x0b, _END_,
    _A_, _u_, _t_, _o_, _a_, _j_, _u_, _s_, _t_, _e_, 0x0b, 0x0b, 0x0b, _END_,
    0x66, 0x00, 0x67, 0x00, 0x69, 0x00, 0x6a, 0x0b, 0x0b, 0x0b, _END_,
    0x66, 0x00, 0x67, 0x00, 0x69, 0x00, 0x6a, 0x0b, 0x0b, 0x0b, _END_,*/
};

BYTE code tOSD_AUTOCOLOR_STR[] =
{
	_C_, _o_, _l_, _o_, _r_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, _END_,
	_C_, _o_, _l_, _o_, _r_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, _END_,
	_C_, _o_, _l_, _o_, _r_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, _END_,
	_C_, _o_, _l_, _o_, _r_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, _END_,
	_C_, _o_, _l_, _o_, _r_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, _END_,
	_C_, _o_, _l_, _o_, _r_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, _END_,
	_C_, _o_, _l_, _o_, _r_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, _END_,
   /* 0x66, 0x00, 0x67, 0x00, 0x6a, 0x00, 0x69, _END_,
    _C_, _o_, _l_, _o_, _r_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, _END_,
    _C_, _o_, _u_, _l_, _e_, _u_, _r_, 0x00, _R_, 0x52, _g_, _l_, _a_, _g_, _e_, _END_,
    _F_, _a_, _r_, _b_, _e_, _i_, _n_, _s_, _t_, _e_, _l_, _l_, _u_, _n_, _g_, _e_, _n_, _END_,
    _A_, _j_, _u_, _s_, _t_, _e_, 0x00, _d_, _e_, 0x00, _c_, _o_, _l_, _o_, _r_, _END_,
    0x66, 0x00, 0x67, 0x00, 0x68, 0x00, 0x69, _END_,
    0x6b, 0x00, 0x6c, 0x00, 0x6d, 0x00, 0x68, 0x00, 0x69, _END_,*/
};

BYTE code tOSD_NOSIGNAL_ICO[] =
{
    0x61, 0x62, 0x63, _NEXT_,
    0x64, 0x65, 0x66, _END_,
};

BYTE code tOSD_NOSIGNAL_STR[] =
{
    0x60, 0x67, 0x68, 0x60, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, _END_,
    0x60, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x60, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, _END_,
    0x60, 0x73, 0x74, 0x75, 0x60, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, _END_,
    0x60, 0x76, 0x77, 0x60, 0x78, 0x79, 0x7a, 0x7b, _END_,
    0x60, 0x7c, 0x60, 0x7e, 0x60, 0x7f, _END_,
    0x60, 0x7d, 0x60, 0x7e, 0x60, 0x80, _END_,
    0x60, 0x7e, 0x60, 0x80, 0x60, 0x81, 0x60, 0x82, _END_,
};

BYTE code tOSD_NOCABLE_ICO[] =
{
    0x61, 0x62, 0x63, _NEXT_,
    0x64, 0x65, 0x66, _END_,
};

BYTE code tOSD_NOCABLE_STR[] =
{
    _N_, _o_, 0x00, _C_, _a_, _b_, _l_, _e_, _END_,
    _N_, _o_, 0x00, _C_, _a_, _b_, _l_, _e_, _END_,
    _N_, _o_, 0x00, _C_, _a_, _b_, _l_, _e_, _END_,
    _N_, _o_, 0x00, _C_, _a_, _b_, _l_, _e_, _END_,
    _N_, _o_, 0x00, _C_, _a_, _b_, _l_, _e_, _END_,
    _N_, _o_, 0x00, _C_, _a_, _b_, _l_, _e_, _END_,
    _N_, _o_, 0x00, _C_, _a_, _b_, _l_, _e_, _END_,
};

BYTE code tOSD_NOSUPPORT_ICO[] =
{
    0x60, 0x61, 0x62, _NEXT_,
    0x63, 0x64, 0x65, _END_,
};
BYTE code tOSD_NOSUPPORT_STR[] =
{
    _O_, _u_, _t_, 0x00, _o_, _f_, 0x00, _R_, _a_, _n_, _g_, _e_, _END_,
    _H_, _o_, _r_, _s_, 0x00, _d_, _e_, 0x00, _p_, _o_, _r_, _t_, 0x52, _e_, _END_,
    _A_, _u_, 0x66, _e_, _r_, _h_, _a_, _l_, _b_, 0x00, _d_, _e_, _s_, 0x00, _B_, _e_, _r_, _e_, _i_, _c_, _h_, _s_, _END_,
    _F_, _u_, _e_, _r_, _a_, 0x00, _d_, _e_, 0x00, _r_, _a_, _n_, _g_, _o_, _END_,
    0x67, 0x00, 0x68, 0x00, 0x69, 0x00, 0x6a, 0x00, 0x6b, 0x00, 0x6c, _END_,
    0x6d, 0x00, 0x68, 0x00, 0x69, 0x00, 0x6a, 0x00, 0x6e, 0x00, 0x6f, _END_,
    0x70, 0x00, 0x71, 0x00, 0x72, 0x00, 0x73, 0x00, 0x74, 0x00, 0x75, 0x00, 0x76, 0x00, 0x77, _END_,
};

//--------------------------------------------------
// Color Subitem Text Table
//--------------------------------------------------
BYTE code tOSD_CONTRAST_STR[] =
{
    _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _END_,
    _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _e_, _END_,
    _K_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _END_,
    _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _e_, _END_,
    0x73, 0x00, 0x74, _END_,
    0x92, 0x00, 0x74, _END_,
    0x70, 0x00, 0x71, 0x00, 0x72, 0x00, 0x61, 0x00, 0x73, 0x00, 0x72, _END_,
    _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _END_,
};


BYTE code tOSD_COLORADJ_STR[] =
{
    _C_, _o_, _l_, _o_, _r_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, _END_,
    _R_, 0x52, _g_, _l_, _a_, _g_, _e_, 0x00, _C_, _o_, _u_, _l_, _e_, _u_, _r_, _END_,
    _F_, _a_, _r_, _b_, _w_, _a_, _h_, _l_, _w_, _e_, _r_, _t_, _END_,
    _A_, _j_, _u_, _s_, _t_, 0x00, _d_, _e_, _l_, 0x00, _C_, _o_, _l_, _o_, _r_, _END_,
    0x60, 0x00, 0x61, 0x00, 0x66, 0x00, 0x77, _END_,
    0x60, 0x00, 0x61, 0x00, 0x66, 0x00, 0x94, _END_,
    0x79, 0x00, 0x7b, 0x00, 0x7c, _END_,
    _C_, _o_, _l_, _o_, _r_, 0x00, _A_, _d_, _j_, _u_, _s_, _t_, _END_,
};

BYTE code tOSD_COLORTEMP_STR[] =
{
    _C_, _o_, _l_, _o_, _r_, 0x00, _T_, _e_, _m_, _p_, _END_,
    _C_, _o_, _l_, _o_, _r_, 0x00, _T_, _e_, _m_, _p_, _END_,
    _C_, _o_, _l_, _o_, _r_, 0x00, _T_, _e_, _m_, _p_, _END_,
    _C_, _o_, _l_, _o_, _r_, 0x00, _T_, _e_, _m_, _p_, _END_,
    0x60, 0x00, 0x7b, _END_,
    0x60, 0x00, 0x7b, _END_,
    0x79, 0x00, 0x7a, _END_,
    _C_, _o_, _l_, _o_, _r_, 0x00, _T_, _e_, _m_, _p_, _END_,
};

BYTE code tOSD_RGB_STR[] =
{
    0x00, _R_, _e_, _d_, 0x00, _G_, _r_, _e_, _e_, _n_, 0x00, _B_, _l_, _u_, _e_, _END_,
    _R_, _o_, _u_, _g_, _e_, 0x00, _V_, _e_, _r_, _t_, 0x00, _B_, _l_, _e_, _u_, _END_,
    0x00, _R_, _o_, _t_, 0x00, _G_, _r_, 0x4b, _n_, 0x00, _B_, _l_, _a_, _u_, _END_,
    _R_, _o_, _j_, _o_, 0x00, _V_, _e_, _r_, _d_, _e_, 0x00, _A_, _z_, _u_, _l_, _END_,
    0x00, 0x78, 0x60, 0x00, 0x00, 0x79, 0x60, 0x00, 0x00, 0x7a, 0x60, _END_,
    0x00, 0x78, 0x60, 0x00, 0x00, 0x79, 0x60, 0x00, 0x00, 0x95, 0x60, _END_,
    0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x84, _END_,
    _R_, _e_, _d_, _END_,
};

BYTE code tOSD_COLORTEMP_ITEM_ICO[] =
{
    0x54, 0x55, 0x00, 0x56, 0x57, 0x00, 0x58, 0x59, 0x00, 0x5a, 0x5b, 0x00, 0x5c, 0x5d, _END_,
};

BYTE code tOSD_DCR_STR[] =
{
    _D_, _C_, _R_, _END_,
    _D_, _C_, _R_, _END_,
    _D_, _C_, _R_, _END_,
    _D_, _C_, _R_, _END_,
    _D_, _C_, _R_, _END_,
    _D_, _C_, _R_, _END_,
    _D_, _C_, _R_, _END_,
    _D_, _C_, _R_, _END_,
};

BYTE code tOSD_DCR_TYPE_STR[] =
{
    _D_, _C_, _R_, ___, _O_, _F_, _F_, _END_,
    _D_, _C_, _R_, ___, _T_, _y_, _p_, _e_, _1_, _END_,
    _D_, _C_, _R_, ___, _T_, _y_, _p_, _e_, _2_, _END_,
    _D_, _C_, _R_, ___, _T_, _y_, _p_, _e_, _3_, _END_,
};

code BYTE *tCOLOR_TABLE[] =
{
    tOSD_CONTRAST_STR,      tOSD_BRIGHTNESS_STR,        tOSD_COLORADJ_STR,
    tOSD_COLORTEMP_STR,     tOSD_DCR_STR,               tOSD_DCR_TYPE_STR
};

//--------------------------------------------------
// Image Subitem Text Table
//--------------------------------------------------
BYTE code tOSD_CLOCK_STR[] =
{
    _C_, _l_, _o_, _c_, _k_, _END_,
    _H_, _o_, _r_, _l_, _o_, _g_, _e_, _END_,
    _T_, _a_, _k_, _t_, _END_,
    _R_, _e_, _l_, _o_, _j_, _END_,
    0x7c, 0x00, 0x7d, _END_,
    0x96, 0x00, 0x97, _END_,
    0x96, 0x00, 0x97, 0x00, 0x8e, 0x00, 0x96, _END_,
    _C_, _l_, _o_, _c_, _k_, _END_,
};

BYTE code tOSD_PHASE_STR[] =
{
    _P_, _h_, _a_, _s_, _e_, _END_,
    _P_, _h_, _a_, _s_, _e_, _END_,
    _P_, _h_, _a_, _s_, _e_, _END_,
    _F_, _a_, _s_, _e_, _END_,
    0x7e, 0x00, 0x66, _END_,
    0x7e, 0x00, 0x66, _END_,
    0x94, 0x00, 0x62, 0x00, 0x95, _END_,
    _P_, _h_, _a_, _s_, _e_, _END_,
};

BYTE code tOSD_SHARPNESS_STR[] =
{
    _S_, _h_, _a_, _r_, _p_, _n_, _e_, _s_, _s_, _END_,
    _N_, _e_, _t_, _t_, _e_, _t_, 0x52, _END_,
    _S_, _c_, _h_, 0x53, _r_, _f_, _e_, _END_,
    _N_, _i_, _t_, _i_, _d_, _e_, _z_, _END_,
    0x81, 0x00, 0x82, 0x00, 0x76, _END_,
    0x81, 0x00, 0x82, 0x00, 0x76, _END_,
    0x98, 0x00, 0x62, 0x00, 0x99, 0x00, 0x76, 0x00, 0x73, _END_,
    _S_, _h_, _a_, _r_, _p_, _n_, _e_, _s_, _s_, _END_,
};

BYTE code tOSD_SHARPNESSITEM_STR[] =
{
    ___, _0_, ___, _1_, ___, _2_, ___, _3_, ___, _4_, _END_,
};

BYTE code tOSD_HPOSITION_STR[] =
{
    _H_, 0x0b, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
    _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, 0x00, _H_, _END_,
    _H_, 0x0b, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
    _P_, _o_, _s_, _i_, _c_, _i_, 0x4f, _n_, 0x00, _H_, _END_,
    0x83, 0x00, 0x84, 0x00, 0x66, 0x00, 0x67, _END_,
    0x83, 0x00, 0x84, 0x00, 0x66, 0x00, 0x67, _END_,
    0x7d, 0x00, 0x7e, 0x00, 0x91, 0x00, 0x92, 0x00, 0x93, 0x00, 0x71, _END_,
    _H_, 0x0b, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tOSD_VPOSITION_STR[] =
{
    _V_, 0x0b, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
    _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, 0x00, _V_, _END_,
    _V_, 0x0b, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
    _P_, _o_, _s_, _i_, _c_, _i_, 0x4f, _n_, 0x00, _V_, _END_,
    0x85, 0x00, 0x86, 0x00, 0x66, 0x00, 0x67, _END_,
    0x85, 0x00, 0x86, 0x00, 0x66, 0x00, 0x67, _END_,
    0x7f, 0x00, 0x80, 0x00, 0x91, 0x00, 0x92, 0x00, 0x93, 0x00, 0x71, _END_,
    _V_, 0x0b, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tOSD_OD_STR[] =
{
    _O_, _D_, ___, _D_, _e_, _l_, _t_, _a_, ___, _G_, _a_, _i_, _n_, _END_,
    _O_, _D_, ___, _D_, _e_, _l_, _t_, _a_, ___, _G_, _a_, _i_, _n_, _END_,
    _O_, _D_, ___, _D_, _e_, _l_, _t_, _a_, ___, _G_, _a_, _i_, _n_, _END_,
    _O_, _D_, ___, _D_, _e_, _l_, _t_, _a_, ___, _G_, _a_, _i_, _n_, _END_,
    _O_, _D_, ___, _D_, _e_, _l_, _t_, _a_, ___, _G_, _a_, _i_, _n_, _END_,
    _O_, _D_, ___, _D_, _e_, _l_, _t_, _a_, ___, _G_, _a_, _i_, _n_, _END_,
    _O_, _D_, ___, _D_, _e_, _l_, _t_, _a_, ___, _G_, _a_, _i_, _n_, _END_,
    _O_, _D_, ___, _D_, _e_, _l_, _t_, _a_, ___, _G_, _a_, _i_, _n_, _END_,
};

code BYTE *tIMG_TABLE[] =
{
    tOSD_CLOCK_STR,         tOSD_PHASE_STR,         tOSD_SHARPNESS_STR,
    tOSD_HPOSITION_STR,     tOSD_VPOSITION_STR,     tOSD_OD_STR
};

//--------------------------------------------------
// OSD Subitem Text Table
//--------------------------------------------------
BYTE code tOSD_OSDHPOS_STR[] =
{
    _O_, _S_, _D_, 0x00, _H_, 0x0b, _P_, _o_, _s_, 0x0b, _END_,
    _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, 0x00, _H_, 0x0b, _O_, _S_, _D_, _END_,
    _H_, 0x0b, _P_, _o_, _s_, 0x0b, _O_, _S_, _D_, _END_,
    _P_, _o_, _s_, _i_, _c_, _i_, 0x4f, _n_, 0x00, _H_, 0x0b, _O_, _S_, _D_, _END_,
    0x83, 0x00, 0x84, 0x00, 0x66, 0x00, 0x67, _END_,
    0x83, 0x00, 0x84, 0x00, 0x66, 0x00, 0x67, _END_,
    0x7d, 0x00, 0x7e, 0x00, 0x91, 0x00, 0x92, 0x00, 0x93, 0x00, 0x71, _END_,
    _H_, 0x0b, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tOSD_OSDVPOS_STR[] =
{
    _O_, _S_, _D_, 0x00, _V_, 0x0b, _P_, _o_, _s_, 0x0b, _END_,
    _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, 0x00, _V_, 0x0b, _O_, _S_, _D_, _END_,
    _V_, 0x0b, _P_, _o_, _s_, 0x0b, _O_, _S_, _D_, _END_,
    _P_, _o_, _s_, _i_, _c_, _i_, 0x4f, _n_, 0x00, _V_, 0x0b, _O_, _S_, _D_, _END_,
    0x85, 0x00, 0x86, 0x00, 0x66, 0x00, 0x67, _END_,
    0x85, 0x00, 0x86, 0x00, 0x66, 0x00, 0x67, _END_,
    0x7f, 0x00, 0x80, 0x00, 0x91, 0x00, 0x92, 0x00, 0x93, 0x00, 0x71, _END_,
    _V_, 0x0b, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tOSD_OSDTIME_STR[] =
{
    _O_, _S_, _D_, 0x00, _T_, _i_, _m_, _e_, _r_, _END_,
    _D_, _u_, _r_, 0x52, _e_, 0x00, _a_, _f_, _f_, _i_, _c_, _h_, _a_, _g_, _e_, _END_,
    _A_, _n_, _z_, _e_, _i_, _g_, _e_, _z_, _e_, _i_, _t_, _e_, 0x0d, _O_, _S_, _D_, _END_,
    _T_, _i_, _e_, _m_, _p_, _o_, 0x00, _e_, _n_, 0x00, _p_, _a_, _n_, _t_, 0x0b, _END_,
    0x68, 0x00, 0x69, 0x00, 0x7c, 0x00, 0x87, _END_,
    0x8c, 0x00, 0x8d, 0x00, 0x96, 0x00, 0x98, _END_,
    0x69, 0x00, 0x6a, 0x00, 0x62, 0x00, 0x81, 0x00, 0x75, 0x00, 0x78, 0x00, 0x62, _END_,
    _D_, _i_, _s_, _p_, _l_, _a_, _y_, 0x00, _T_, _i_, _m_, _e_, _END_,
};

BYTE code tOSD_LANGUAGE_STR[] =
{
    _L_, _a_, _n_, _g_, _u_, _a_, _g_, _e_, _END_,
    _L_, _a_, _n_, _g_, _u_, _e_, _END_,
    _S_, _p_, _r_, _a_, _c_, _h_, _e_, _END_,
    _L_, _e_, _n_, _g_, _u_, _a_, _j_, _e_, _END_,
    0x6a, 0x00, 0x6b, 0x00, 0x68, 0x00, 0x6c, _END_,
    0x90, 0x00, 0x6b, 0x00, 0x8c, 0x00, 0x91, _END_,
    0x85, 0x00, 0x86, 0x00, 0x87, 0x00, 0x88, _END_,
    _L_, _a_, _n_, _g_, _u_, _a_, _g_, _e_, _END_,
};

//--------------------------------------------------
// Language Subitem Text Table
//--------------------------------------------------
BYTE code tOSD_LANGUAGE_ITEM_STR[] =
{
    _E_, _n_, _g_, _l_, _i_, _s_, _h_, _END_,
    _F_, _r_, _a_, _n_, 0x4d, _a_, _i_, _s_, _END_,
    _D_, _e_, _u_, _t_, _s_, _c_, _h_, _END_,
    _E_, _s_, _p_, _a_, 0x4c, _o_, _l_, _END_,
    0x2c, 0x00, 0x2d, 0x00, 0x2a, 0x00, 0x2b, _END_,
    0x2e, 0x00, 0x2f, 0x00, 0x2a, 0x00, 0x2b, _END_,
    0x5b, 0x00, 0x5c, 0x00, 0x5d, _END_,
};

code BYTE *tOSD_TABLE[] =
{
    tOSD_OSDHPOS_STR, tOSD_OSDVPOS_STR, tOSD_OSDTIME_STR, tOSD_LANGUAGE_STR
};

BYTE code tOSD_INPUT_SOURCE_STR[] =
{
    _I_, _n_, _p_, _u_, _t_, 0x54,   _END_,
    _I_, _n_, _p_, _u_, _t_, 0x54,   _END_,
    _I_, _n_, _p_, _u_, _t_, 0x54,   _END_,
    _I_, _n_, _p_, _u_, _t_, 0x54,   _END_,
    _I_, _n_, _p_, _u_, _t_, 0x54,   _END_,
    _I_, _n_, _p_, _u_, _t_, 0x54,   _END_,
    _I_, _n_, _p_, _u_, _t_, 0x54,   _END_,
};

BYTE code tOSD_SOURCE_STR[][13] =
{
    {
        _D_, 0x0d, _S_, _U_, _B_, _END_,
    },

    {
        _D_, _V_, _I_, _END_,
    },

    {
        _H_, _D_, _M_, _I_, _END_,
    },

    {
        _D_, _i_, _s_, _p_, _l_, _a_, _y_, ___, _P_, _o_, _r_, _t_,  _END_,
    },

    {
        _V_, _i_, _d_, _e_, _o_, _8_, _END_,
    },
};

//--------------------------------------------------
// Singal Type Text Table
//--------------------------------------------------
BYTE code tOSD_SINGAL_STR[] =
{
    _D_, 0x0d, _S_, _U_, _B_, _NEXT_,
    _NEXT_,
    _D_, _V_, _I_, _NEXT_,
    _NEXT_,
    _H_, _D_, _M_, _I_, _NEXT_,
    _NEXT_,

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    _D_, _i_, _s_, _p_, _l_, _a_, _y_, ___, _P_, _o_, _r_, _t_,  _NEXT_,
    _NEXT_,
    _A_, _u_, _t_, _o_, ___, _S_, _e_, _a_, _r_, _c_, _h_, _END_,

#else

    _D_, _i_, _s_, _p_, _l_, _a_, _y_, ___, _P_, _o_, _r_, _t_, _END_,

#endif

};


#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Volume Text Table
//--------------------------------------------------
BYTE code tOSD_VOLUME_STR[] =
{
    _V_, _o_, _l_, _u_, _m_, _e_, _END_,
    _V_, _o_, _l_, _u_, _m_, _e_, _END_,
    _V_, _o_, _l_, _u_, _m_, _e_, _END_,
    _V_, _o_, _l_, _u_, _m_, _e_, _END_,
    _V_, _o_, _l_, _u_, _m_, _e_, _END_,
    _V_, _o_, _l_, _u_, _m_, _e_, _END_,
    _V_, _o_, _l_, _u_, _m_, _e_, _END_,
    _V_, _o_, _l_, _u_, _m_, _e_, _END_,
};

BYTE code tOSD_MUTE_STR[] =
{
    _M_, _u_, _t_, _e_, _END_,
    _M_, _u_, _t_, _e_, _END_,
    _M_, _u_, _t_, _e_, _END_,
    _M_, _u_, _t_, _e_, _END_,
    _M_, _u_, _t_, _e_, _END_,
    _M_, _u_, _t_, _e_, _END_,
    _M_, _u_, _t_, _e_, _END_,
    _M_, _u_, _t_, _e_, _END_,
};

BYTE code tOSD_ON_OFF_STR[] =
{
    _O_, _F_, _F_, _END_,
    _O_, _N_, ___, _END_,
};

code BYTE *tOSD_AUDIO_TABLE[] =
{
    tOSD_VOLUME_STR, tOSD_MUTE_STR, tOSD_ON_OFF_STR
};

#endif // End cf #if(_AUDIO_SUPPORT==_ON)


//--------------------------------------------------
// Special Fuction Text Table
//--------------------------------------------------
BYTE code tOSD_VIVID_COLOR_STR[] =
{
    _V_, _i_, _v_, _i_, _d_, ___, _C_, _o_, _l_, _o_, _r_, _END_,
    _V_, _i_, _v_, _i_, _d_, ___, _C_, _o_, _l_, _o_, _r_, _END_,
    _V_, _i_, _v_, _i_, _d_, ___, _C_, _o_, _l_, _o_, _r_, _END_,
    _V_, _i_, _v_, _i_, _d_, ___, _C_, _o_, _l_, _o_, _r_, _END_,
    _V_, _i_, _v_, _i_, _d_, ___, _C_, _o_, _l_, _o_, _r_, _END_,
    _V_, _i_, _v_, _i_, _d_, ___, _C_, _o_, _l_, _o_, _r_, _END_,
    _V_, _i_, _v_, _i_, _d_, ___, _C_, _o_, _l_, _o_, _r_, _END_,
    _V_, _i_, _v_, _i_, _d_, ___, _C_, _o_, _l_, _o_, _r_, _END_,
};

BYTE code tOSD_NONLINEAR_SCALING_STR[] =
{
    _N_, _o_, _n_, _L_, _i_, _n_, _e_, _a_, _r_, ___, _S_, _c_, _a_, _l_, _i_, _n_, _g_, _END_,
    _N_, _o_, _n_, _L_, _i_, _n_, _e_, _a_, _r_, ___, _S_, _c_, _a_, _l_, _i_, _n_, _g_, _END_,
    _N_, _o_, _n_, _L_, _i_, _n_, _e_, _a_, _r_, ___, _S_, _c_, _a_, _l_, _i_, _n_, _g_, _END_,
    _N_, _o_, _n_, _L_, _i_, _n_, _e_, _a_, _r_, ___, _S_, _c_, _a_, _l_, _i_, _n_, _g_, _END_,
    _N_, _o_, _n_, _L_, _i_, _n_, _e_, _a_, _r_, ___, _S_, _c_, _a_, _l_, _i_, _n_, _g_, _END_,
    _N_, _o_, _n_, _L_, _i_, _n_, _e_, _a_, _r_, ___, _S_, _c_, _a_, _l_, _i_, _n_, _g_, _END_,
    _N_, _o_, _n_, _L_, _i_, _n_, _e_, _a_, _r_, ___, _S_, _c_, _a_, _l_, _i_, _n_, _g_, _END_,
    _N_, _o_, _n_, _L_, _i_, _n_, _e_, _a_, _r_, ___, _S_, _c_, _a_, _l_, _i_, _n_, _g_, _END_,
};

BYTE code tOSD_ASPECT_RATIO_STR[] =
{
    _A_, _s_, _p_, _e_, _c_, _t_, ___, _R_, _a_, _t_, _i_, _o_, _END_,
    _A_, _s_, _p_, _e_, _c_, _t_, ___, _R_, _a_, _t_, _i_, _o_, _END_,
    _A_, _s_, _p_, _e_, _c_, _t_, ___, _R_, _a_, _t_, _i_, _o_, _END_,
    _A_, _s_, _p_, _e_, _c_, _t_, ___, _R_, _a_, _t_, _i_, _o_, _END_,
    _A_, _s_, _p_, _e_, _c_, _t_, ___, _R_, _a_, _t_, _i_, _o_, _END_,
    _A_, _s_, _p_, _e_, _c_, _t_, ___, _R_, _a_, _t_, _i_, _o_, _END_,
    _A_, _s_, _p_, _e_, _c_, _t_, ___, _R_, _a_, _t_, _i_, _o_, _END_,
    _A_, _s_, _p_, _e_, _c_, _t_, ___, _R_, _a_, _t_, _i_, _o_, _END_,
};

BYTE code tOSD_HUE_STR[] =
{
    _H_, _u_, _e_, _END_,
    _H_, _u_, _e_, _END_,
    _H_, _u_, _e_, _END_,
    _H_, _u_, _e_, _END_,
    _H_, _u_, _e_, _END_,
    _H_, _u_, _e_, _END_,
    _H_, _u_, _e_, _END_,
    _H_, _u_, _e_, _END_,
};

BYTE code tOSD_SATURATION_STR[] =
{
    _S_, _a_, _t_, _u_, _r_, _a_, _t_, _i_, _o_, _n_, _END_,
    _S_, _a_, _t_, _u_, _r_, _a_, _t_, _i_, _o_, _n_, _END_,
    _S_, _a_, _t_, _u_, _r_, _a_, _t_, _i_, _o_, _n_, _END_,
    _S_, _a_, _t_, _u_, _r_, _a_, _t_, _i_, _o_, _n_, _END_,
    _S_, _a_, _t_, _u_, _r_, _a_, _t_, _i_, _o_, _n_, _END_,
    _S_, _a_, _t_, _u_, _r_, _a_, _t_, _i_, _o_, _n_, _END_,
    _S_, _a_, _t_, _u_, _r_, _a_, _t_, _i_, _o_, _n_, _END_,
    _S_, _a_, _t_, _u_, _r_, _a_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tOSD_SRGB_STR[] =
{
    _S_, _r_, _g_, _b_, _END_,
    _S_, _r_, _g_, _b_, _END_,
    _S_, _r_, _g_, _b_, _END_,
    _S_, _r_, _g_, _b_, _END_,
    _S_, _r_, _g_, _b_, _END_,
    _S_, _r_, _g_, _b_, _END_,
    _S_, _r_, _g_, _b_, _END_,
    _S_, _r_, _g_, _b_, _END_,
};

#if(_ASPECT_RATIO_SUPPORT == _ON)

BYTE code tOSD_ASPECT_RATIO_TYPE_STR[] =
{
#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
    _F_, _u_, _l_, _l_, ___, _S_, _c_, _r_, _e_, _e_, _n_, ___, _END_,
    _O_, _r_, _i_, _g_, _i_, _n_, _l_, ___, _S_, _i_, _z_, _e_, _END_,
    _F_, _i_, _x_, _e_, _d_, ___, _A_, _s_, _p_, _e_, _c_, _t_, _END_,

#else
    ___, ___, _O_, _F_, _F_, _END_,
    ___, ___, _O_, _N_, ___, _END_,
#endif
};

#endif // End of #if(_ASPECT_RATIO_SUPPORT == _ON)

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
BYTE code tOSD_RGB_YUV[] =
{
    _C_, _o_, _l_,_o_,_r_,0x00,_F_, _o_, _r_,_m_,_a_,_t_,_END_,
    _C_, _o_, _l_,_o_,_r_,0x00,_F_, _o_, _r_,_m_,_a_,_t_,_END_,
    _C_, _o_, _l_,_o_,_r_,0x00,_F_, _o_, _r_,_m_,_a_,_t_,_END_,
    _C_, _o_, _l_,_o_,_r_,0x00,_F_, _o_, _r_,_m_,_a_,_t_,_END_,
    _C_, _o_, _l_,_o_,_r_,0x00,_F_, _o_, _r_,_m_,_a_,_t_,_END_,
    _C_, _o_, _l_,_o_,_r_,0x00,_F_, _o_, _r_,_m_,_a_,_t_,_END_,
    _C_, _o_, _l_,_o_,_r_,0x00,_F_, _o_, _r_,_m_,_a_,_t_,_END_,
    _C_, _o_, _l_,_o_,_r_,0x00,_F_, _o_, _r_,_m_,_a_,_t_,_END_,
};

#if(_COLOR_FORMAT_CONVERT == _ON)
BYTE code tOSD_RGBYUV_STR[] =
{
    0x00, _R_, _G_, _B_, 0x00, 0x00, 0x00, _Y_, _U_, _V_,  _END_,
    0x00, _R_, _G_, _B_, 0x00, 0x00, 0x00, _Y_, _U_, _V_,  _END_,
    0x00, _R_, _G_, _B_, 0x00, 0x00, 0x00, _Y_, _U_, _V_,  _END_,
    0x00, _R_, _G_, _B_, 0x00, 0x00, 0x00, _Y_, _U_, _V_,  _END_,
    0x00, _R_, _G_, _B_, 0x00, 0x00, 0x00, _Y_, _U_, _V_,  _END_,
    0x00, _R_, _G_, _B_, 0x00, 0x00, 0x00, _Y_, _U_, _V_,  _END_,
    0x00, _R_, _G_, _B_, 0x00, 0x00, 0x00, _Y_, _U_, _V_,  _END_,
    0x00, _R_, _G_, _B_, 0x00, 0x00, 0x00, _Y_, _U_, _V_,  _END_,
};
#endif
// V012 Modify 20100304 End

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
/*
code BYTE *tOSD_SPECTIAL_FUCTION_TABLE[] =
{
    tOSD_VIVID_COLOR_STR, tOSD_NONLINEAR_SCALING_STR, tOSD_ASPECT_RATIO_STR, tOSD_SRGB_STR
};
*/
code BYTE *tOSD_SPECTIAL_FUCTION_TABLE[] =
{
    tOSD_VIVID_COLOR_STR, tOSD_NONLINEAR_SCALING_STR, tOSD_ASPECT_RATIO_STR, tOSD_SRGB_STR, tOSD_RGB_YUV
};
// V012 Modify 20100304 End

code BYTE *tOSD_SRGB_FUCTION_TABLE[] =
{
    tOSD_HUE_STR, tOSD_SATURATION_STR
};

#if(_VIVID_COLOR_FUCTION == _ON)
//--------------------------------------------------
// Vivid Color Text Table
//--------------------------------------------------
BYTE code tOSD_VIVID_MODE_STR[] =
{
    _W_, _i_, _n_, _d_, _o_, _w_, _s_, ___, _S_, _i_, _z_, _e_, _NEXT_,
    _NEXT_,
    _D_, _C_, _C_, ___, _M_, _o_, _d_, _e_, _NEXT_,
    _NEXT_,
    _I_, _C_, _M_, ___, _M_, _o_, _d_, _e_, _NEXT_,
    _NEXT_,
    _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _NEXT_,
    _NEXT_,
    _B_, _r_, _i_, _g_, _h_, _t_, _n_, _e_, _s_, _s_, _END_,
};

BYTE code tOSD_WINDOW_SIZE_STR[] =
{
    _D_, _i_, _s_, _a_, _b_, _l_, _e_, _END_,
    _F_, _u_, _l_, _l_, _END_,
    _D_, _e_, _m_, _o_, _END_,
    _U_, _s_, _e_, _r_, _END_,
};

BYTE code tOSD_USER_WINDOW_STR[] =
{
    _H_, ___, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _NEXT_,
    _NEXT_,
    _V_, ___, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _NEXT_,
    _NEXT_,
    _H_, ___, _W_, _i_, _d_, _t_, _h_, _NEXT_,
    _NEXT_,
    _V_, ___, _H_, _e_, _i_, _g_, _h_, _t_, _END_,
};

BYTE code tOSD_DCC_ICM_MODE_STR[] =
{
    _D_, _i_, _s_, _a_, _b_, _l_, _e_, _END_,
    _M_, _o_, _v_, _i_, _e_, _END_,
    _P_, _h_, _o_, _t_, _o_, _END_,
    _G_, _a_, _m_, _e_, _END_,
    _U_, _s_, _e_, _r_, _END_,
    _R_, _e_, _d_, ___, _H_, _u_, _e_, _END_,
    _R_, _e_, _d_, ___, _S_, _a_, _t_, _END_,
    _G_, _r_, _e_, _e_, _n_, ___, _H_, _u_, _e_, _END_,
    _G_, _r_, _e_, _e_, _n_, ___, _S_, _a_, _t_, _END_,
    _B_, _l_, _u_, _e_, ___, _H_, _u_, _e_, _END_,
    _B_, _l_, _u_, _e_, ___, _S_, _a_, _t_, _END_,
};

BYTE code tOSD_ICM_MODE_STR[] =
{
    _R_, _e_, _d_, _NEXT_,
    _NEXT_,
    _G_, _r_, _e_, _e_, _n_, _NEXT_,
    _NEXT_,
    _B_, _l_, _u_, _e_, _END_,
};

BYTE code tOSD_VIVID_ADJUST_STR[] =
{
    _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _NEXT_,
    _NEXT_,
    _B_, _r_, _i_, _g_, _h_, _n_, _e_, _s_, _s_, _END_,
};

BYTE code tOSD_VIVID_OTHER_STR[] =
{
    _O_, _F_, _F_, _END_,
    _O_, _N_, _END_,
    _O_, _F_, _F_, _END_,
    _O_, _F_, _F_, _END_,
};

code BYTE *tVIVID_COLOR_TABLE[] =
{
    tOSD_VIVID_MODE_STR,    tOSD_WINDOW_SIZE_STR,   tOSD_USER_WINDOW_STR,
    tOSD_DCC_ICM_MODE_STR,  tOSD_ICM_MODE_STR,      tOSD_VIVID_ADJUST_STR,
    tOSD_VIVID_OTHER_STR
};

#endif // End of #if(_VIVID_COLOR_FUCTION == _ON)



//--------------------------------------------------
// Factory Text Table
//--------------------------------------------------
BYTE code tOSD_FACTORY_ITEM_STR[] =
{
    0x00, _A_, _u_, _t_, _o_, 0x00, _C_, _o_, _l_, _o_, _r_, _END_,
    0x00, _R_, _e_, _s_, _e_, _t_, _END_,
    0x00, _A_, _D_, _C_, 0x00, _O_, _f_, _f_, _s_, _e_, _t_, _END_,
    0x00, _A_, _D_, _C_, 0x00, _G_, _a_, _i_, _n_, _END_,
    0x00, _9_, _3_, _0_, _0_, _K_, _END_,
    0x00, _6_, _5_, _0_, _0_, _K_, _END_,
    0x00, _5_, _8_, _0_, _0_, _K_, _END_,
    0x00, _s_, _R_, _G_, _B_, _END_,
    0x00, _U_, _s_, _e_, _r_, _END_,
    0x00, _B_, _r_, _i_, _g_, _h_, _t_, _n_, _e_, _s_, _s_, _END_,
    0x00, _A_, _u_, _t_, _o_, 0x00, _C_, _o_, _n_, _f_, _i_, _g_, _END_,
    0x00, _E_, _x_, _i_, _t_, _END_,
};

BYTE code tOSD_FACTORY_CONTENT_STR[] =
{
    0x00, 0x00, _R_, 0x00, _REPEAT_, 4, _G_, 0x00, _REPEAT_, 4, _B_, 0x00, _REPEAT_, 4, _END_,
};

#if(_DDCCI_SUPPORT == _ON)
BYTE code tOSD_DDCCI_STR[] =
{
    _D_,_D_,_C_,_C_,_I_,_END_,
    _D_,_D_,_C_,_C_,_I_,_END_,
    _D_,_D_,_C_,_C_,_I_,_END_,
    _D_,_D_,_C_,_C_,_I_,_END_,
    _D_,_D_,_C_,_C_,_I_,_END_,
    _D_,_D_,_C_,_C_,_I_,_END_,
    _D_,_D_,_C_,_C_,_I_,_END_,
    _D_,_D_,_C_,_C_,_I_,_END_,
};

BYTE code tOSDDDCCI_ON_OFF_STR[] =
{
    _O_,_F_,_F_,_END_,
    _O_,_N_,___,_END_,
};

code BYTE *tOSD_DDCCIONOFF_TABLE[] =
{
    tOSD_DDCCI_STR,  tOSDDDCCI_ON_OFF_STR
};
#endif

//--------------------------------------------------
// Icon&Text order Table
//--------------------------------------------------

code BYTE *tICONPOS_TABLE[4] =
{
    tOSD_POS0_ICO, tOSD_POS1_ICO, tOSD_POS2_ICO, tOSD_POS3_ICO
};

code BYTE *tLONGICONPOS_TABLE[7] =
{
    tOSD_POSITION0_ICO, tOSD_POSITION1_ICO, tOSD_POSITION2_ICO, tOSD_POSITION3_ICO, tOSD_POSITION4_ICO, tOSD_POSITION5_ICO, tOSD_POSITION6_ICO
};


//--------------------------------------------------
// DCC/ICM
//--------------------------------------------------
BYTE code tOSD_ROW_COMMAND5[] =
{
    FONTBYTE0(0x000),
    0x80,_REPEAT_,25,_NEXT_,

    FONTBYTE1(0x000),
    0x88,_REPEAT_,25,_NEXT_,

    FONTBYTE2(0x000),
    28,_REPEAT_,25,_NEXT_,

    FONTBYTE0(25),
    0x00,

    _END_
};

#else

extern code BYTE *tOSD_CHARWIDTH_TABLE[9];
extern WORD code tOSD_OSDMAP_INF[][2];

extern BYTE code tOSD_ROW_COMMAND0[];
extern BYTE code tOSD_ROW_COMMAND1[];
extern BYTE code tOSD_ROW_COMMAND2[];

extern BYTE code tOSD_POINT_ICO[];
extern BYTE code tOSD_WINDOW0_STYLE[];
extern BYTE code tOSD_WINDOW1_STYLE[];
extern BYTE code tOSD_WINDOW2_STYLE[];
extern BYTE code tOSD_WINDOW3_STYLE[];
extern BYTE code tOSD_WINDOW4_STYLE[];
extern BYTE code tOSD_WINDOW5_STYLE[];
extern BYTE code tOSD_WINDOW6_STYLE[];
extern BYTE code tOSD_WINDOW7_STYLE[];
extern BYTE code tOSD_RT_MARK_ICO1[];
extern BYTE code tOSD_RT_MARK_ICO2[];
extern BYTE code tOSD_FACTORY_ITEM_STR[];

extern BYTE code tOSD_AUTO_ICO[];
extern BYTE code tOSD_AUTO_STR[];
extern BYTE code tOSD_AUTOCOLOR_STR[];
extern BYTE code tOSD_NOSIGNAL_ICO[];
extern BYTE code tOSD_NOSIGNAL_STR[];
extern BYTE code tOSD_NOCABLE_ICO[];
extern BYTE code tOSD_NOCABLE_STR[];
extern BYTE code tOSD_NOSUPPORT_ICO[];
extern BYTE code tOSD_NOSUPPORT_STR[];

extern code BYTE *tICONPOS_TABLE[4];
extern code BYTE *tLONGICONPOS_TABLE[7];

extern code BYTE *tTEXT_TABLE[];
extern code BYTE *tCOLOR_TABLE[];
extern code BYTE *tIMG_TABLE[];
extern code BYTE *tOSD_TABLE[];
extern BYTE code tOSD_SINGAL_STR[];

#if(_AUDIO_SUPPORT == _ON)
extern code BYTE *tOSD_AUDIO_TABLE[];
#endif

extern code BYTE *tOSD_SPECTIAL_FUCTION_TABLE[];
extern code BYTE *tOSD_SRGB_FUCTION_TABLE[];

#if(_VIVID_COLOR_FUCTION == _ON)
code BYTE *tVIVID_COLOR_TABLE[];
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
extern BYTE code tOSD_ASPECT_RATIO_TYPE_STR[];
#endif




//--------------------------------------------------
// Icon&Text order Table
//--------------------------------------------------
extern BYTE code tOSD_ROW_COMMAND5[];
extern BYTE code tOSD_MZ_TITLE_STR[];
extern BYTE code tOSD_MOVIE_STR[];
extern BYTE code tOSD_TEXT_STR[];
extern BYTE code tOSD_USER_STR[];
extern BYTE code tOSD_NORMAL_STR[];
extern BYTE code tOSD_User_Mode_DCC[];
extern BYTE code tOSD_User_Mode_ICM[];
extern BYTE code tOSD_User_Mode_Exit[];
extern code BYTE tUSER_MODE_LEVEL0[];
extern code BYTE tUSER_MODE_LEVEL1[];
extern code BYTE tUSER_MODE_LEVEL2[];
extern code BYTE tUSER_MODE_LEVEL3[];
extern BYTE code tVOLUME_NOSUPPORT_STR[];
extern BYTE code tDCR_NOSUPPORT_STR[];
extern BYTE code tOSD_INPUT_SOURCE_STR[];
extern BYTE code tOSD_SOURCE_STR[][13];

#endif


