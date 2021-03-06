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
// ID Code      : Video.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_VIDEO_SUPPORT == _ON)

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------
#define _VIDEO_DEVICE               0x42    //SAA7114 & SAA7118
#define _VIDEO_50HZ                 0
#define _VIDEO_60HZ                 1
#define _AV_CHANNEL                 0
#define _SV_CHANNEL                 1
#define _VIDEO_NOT_EXIST            _MODE_NOSIGNAL
#define _VIDEO_EXIST                _MODE_EXIST

#define _AV_PORT                     0xc5    // Refer to SAA7114 Spec
#define _SV_PORT                     0xc7    // Refer to SAA7114 Spec


//----------------------------------------------------------------------------------------------------

#ifdef __VIDEO__

//--------------------------------------------------
// Video Tables
//--------------------------------------------------
BYTE code tVIDEO_TABLE_COLOR_STANDARD[2][2][5][9] =             // Color standard setting
{
    // SAA7114 from 0x08
    {
        {
            // AV 50HZ
            {0x98,0x40,0x80,0x3E,0x40,0x00,0x01,0x2A,0x06},     // _PAL_BGDHI
            {0x98,0x40,0x80,0x3E,0x40,0x00,0x19,0x2A,0x0e},     // _NTSC_443_50
            {0x98,0x40,0x80,0x3E,0x40,0x00,0x21,0x2A,0x06},     // _PAL_N
            {0x98,0x40,0x80,0x3E,0x40,0x00,0x39,0x2A,0x0e},     // _NTSC_N
            {0x98,0x3B,0x80,0x3E,0x40,0x00,0x58,0x80,0x00},     // _SECAM
        },

        {
            // AV 60HZ
            {0xD8,0x40,0x80,0x3E,0x40,0x00,0x09,0x2A,0x0e},     // _NTSC_M
            {0xD8,0x40,0x80,0x3E,0x40,0x00,0x11,0x2A,0x06},     // _PAL_443
            {0xD8,0x40,0x80,0x3E,0x40,0x00,0x29,0x2A,0x0e},     // _NTSC_443_60
            {0xD8,0x40,0x80,0x3E,0x40,0x00,0x31,0x2A,0x06},     // _PAL_M
            {0xD8,0x40,0x80,0x3E,0x40,0x00,0x49,0x2A,0x0e},     // _NTSC_JAPAN
        },
    },

    {
        {
            // SV 50HZ
            {0x98,0x80,0x80,0x3E,0x40,0x00,0x00,0x2A,0x06},     // _PAL_BGDHI
            {0x98,0x80,0x80,0x3E,0x40,0x00,0x18,0x2A,0x0e},     // _NTSC_443_50
            {0x98,0x80,0x80,0x3E,0x40,0x00,0x20,0x2A,0x06},     // _PAL_N
            {0x98,0x80,0x80,0x3E,0x40,0x00,0x38,0x2A,0x0e},     // _NTSC_N
            {0x98,0xAB,0x80,0x3E,0x40,0x00,0x58,0x80,0x00},     // _SECAM
        },

        {
            // SV 60HZ
            {0xD8,0x80,0x80,0x3E,0x40,0x00,0x08,0x2A,0x0e},     // _NTSC_M
            {0xD8,0x80,0x80,0x3E,0x40,0x00,0x10,0x2A,0x06},     // _PAL_443
            {0xD8,0x80,0x80,0x3E,0x40,0x00,0x28,0x2A,0x0e},     // _NTSC_443_60
            {0xD8,0x80,0x80,0x3E,0x40,0x00,0x30,0x2A,0x06},     // _PAL_M
            {0xD8,0x80,0x80,0x3E,0x40,0x00,0x48,0x2A,0x0e},     // _NTSC_JAPAN
        },
    },
};

BYTE code tVIDEO_TABLE_INITIAL_SAA7114[] =
{
    // 0x00~0x0f
    0x00,0x08,0xc9,0x00,0x90,0x90,0xeb,0xe0,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,


    // 0x10~0x1f
/*
    0x0e,0x00,0xd9,0x10,0x24,0x00,0x10,0x00,
    0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
*/
    0x0e,0x00,0xc9,0x10,0x24,0x00,0x10,0x00,
    0x40,0x80,0x00,0x00,0x00,0x00,0x00,0xc8,

    // 0x20~0x2f
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    // 0x30~0x3f
    0xbc,0xdf,0x02,0x00,0xcd,0xcc,0x3a,0x00,
    0x03,0x20,0x03,0x00,0x00,0x00,0x00,0x00,

    // 0x40~0x4f
    0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    // 0x50~0x5f
    0x00,0x00,0x00,0x00,0x5f,0xff,0xff,0xff,
    0x00,0x47,0x06,0x03,0x00,0x00,0x00,0x00,

    // 0x60~0x6f
    0x00,0x05,0xa0,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    // 0x70~0x7f
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    // 0x80~0x8f
    0x12,0x00,0x00,0x01,0x01,0x04,0x45,0x01, //0x83
    0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    // 0x90~0x9f
/*
    0x00,0x08,0x09,0x40,0x08,0x00,0xbc,0x02,
    0x00,0x00,0xf0,0x00,0xbc,0x02,0xf0,0x00,
*/
    0x00,0x08,0x09,0xc0,0x08,0x00,0xd0,0x02,
    0x10,0x00,0xf0,0x00,0xd0,0x02,0xf0,0x00,

    // 0xa0~0xaf
    0x01,0x00,0x00,0x00,0x80,0x40,0x40,0x00,
    0x00,0x04,0x00,0x00,0x00,0x02,0x00,0x00,

    // 0xb0~0xbf
    0x00,0x04,0x00,0x04,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    // 0xc0~0xcf
    0x00,0x08,0x10,0x81,0x10,0x00,0xd0,0x02,
    0x0a,0x00,0x20,0x01,0xd0,0x02,0x20,0x01,

    // 0xd0~0xdf
    0x01,0x00,0x00,0x00,0x80,0x40,0x40,0x00,
    0x00,0x04,0x00,0x00,0x00,0x02,0x00,0x00,

    // 0xe0~0xef
    0x00,0x04,0x00,0x04,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

BYTE code tVIDEO_TABLE_FIELD[][6] =
{
    // SAA7114 from 0x9A
    {0x38,0x01,0xbc,0x02,0x38,0x01},    // 50hz
    {0x04,0x01,0xbc,0x02,0x04,0x01},    // 60hz
};

BYTE code tVIDEO_TABLE_SET_SCALER[] =
{

    7,  _AUTOINC,       _VGIP_CTRL_10,                  0x09,0x01,0x00,0x47,

    4,  _NON_AUTOINC,   _IPH_ACT_WID_H_16,              0x08,
#if(_SCALER_TYPE == _RTD2472D)
    4,  _NON_AUTOINC,   _IPV_ACT_STA_H_18,              0x00,
#endif
    4,  _NON_AUTOINC,   _SCALE_CTRL_32,                 0x80,
    4,  _NON_AUTOINC,   _SYNC_CTRL_49,                  0x05,


#if(_SCALER_TYPE == _RTD2472D)
    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,            0x02,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x0C,0x04,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x1C,0xa8,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x2C,0x06,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x3C,0x62,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x4C,0x01,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x5C,0x91,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x6C,0x03,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x7C,0x40,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x8C,0x08,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x9C,0x12,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xAC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xBC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xCC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xDC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xEC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xFC,0x00,
    4,  _NON_AUTOINC,   _YUV_RGB_ACCESS_9D,          0x0c,
    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,            0x01,

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    //4,    _NON_AUTOINC,   _V8_YUV_CONVERSION_1F,       0x08, // 422->444

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,             _PAGE7,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,         0x02,  // Enable Coefficient Access
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x00,0x04,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x08,0xa8,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x10,0x06,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x18,0x62,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x20,0x01,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x28,0x91,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x30,0x03,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x38,0x40,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x40,0x08,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x48,0x12,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x50,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x58,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x60,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x68,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x70,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x78,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x80,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x88,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x90,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x98,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0xA0,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0xA8,0x00,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_ACCESS_C0,       0x06,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,         0x01,

#else
    No Setting !!
#endif

    _END
};

WORD code tVIDEO_TABLE_INPUT_INFO[][5] =
{
    // IHTotal, IHStart, IHWidth, IVStart, IVHeight
    {    864,     159,     672,     27,     274 },  // 50HZ
    {    858,     141,     704,     27,     236 },  // 60HZ
//    {    1716,     282,     1440,     54,     236 },  // 60HZ

};

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
bit bVideoType;


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CVideoInitial(void);
bit CVideoColorFormatProc(void);
bit CVideoIsExist(void);
bit CVideoIsChange(void);
void CVideoDisplaySet(void);


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern bit bVideoType;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CVideoInitial(void);
extern bit CVideoIsExist(void);
extern bit CVideoIsChange(void);
extern void CVideoDisplaySet(void);


#endif // End of #ifdef __VIDEO__



//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Input Sync Type
//--------------------------------------------------
#define ADDRESS(x)                  (x)
#define CHECK60HZ()                 (bVideoType == _VIDEO_60HZ)
#define CHECK50HZ()                 (bVideoType == _VIDEO_50HZ)
#define SET60HZ()                   (bVideoType = _VIDEO_60HZ)
#define SET50HZ()                   (bVideoType = _VIDEO_50HZ)


#endif  // #if(_VIDEO_SUPPORT == _ON)
