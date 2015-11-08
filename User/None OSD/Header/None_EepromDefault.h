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
// ID Code      : EepromDefault.h No.0001
// Update Note  :
//----------------------------------------------------------------------------------------------------

#ifdef __NONE_EEPROM__


//--------------------------------------------------
// Eeprom/Flash Version Code
//--------------------------------------------------
#define _VERSION_CODE               0x14


//--------------------------------------------------
// System Data Default Value
//--------------------------------------------------
#define _MONITORFLAG                0x80
#define _SEARCHINDEX                0x00
#define _BACKLIGHT                  0x80  //0x32
#define _COLORTEMP                  0x04  //0x00
#define _SHARPNESS                  0x02
#define _USERFIFOMODE               0x0f
#define _OD_SELECTED                0x40  // Delta Gain = _ODSELECTED/64

code StructSystemDataType tEEPROM_SYSTEM_DATA =
{
    _MONITORFLAG,
    _SEARCHINDEX,
    _BACKLIGHT,
    _COLORTEMP,
    _SHARPNESS,
    _USERFIFOMODE,
    _OD_SELECTED,
};

//--------------------------------------------------
// OSD User Data Default Value
//--------------------------------------------------
#define _OSD_SETTINGFLAG            0x00
#define _OSD_MANAGEMENTFLAG         0x00
#define _OSD_H_POSITION             0x64
#define _OSD_V_POSITION             0x64
#define _LANGUAGE                   0x00
#define _OSD_TIMEOUT                0x0a//0x0a
#define _VOLUME                     0xc0


code StructOsdUserDataType tEEPROM_OSDUSER_DATA =
{
    _OSD_SETTINGFLAG,
    _OSD_MANAGEMENTFLAG,
    _OSD_H_POSITION,
    _OSD_V_POSITION,
    _LANGUAGE,
    _OSD_TIMEOUT,
    _VOLUME,
};

//--------------------------------------------------
// OSD Factory Data Default Value
//--------------------------------------------------
#define _RESERVE_SETTINGFLAG        0x44


code StructOsdReserveDataType tEEPROM_OSDRESERVE_DATA =
{
    _RESERVE_SETTINGFLAG,
};


//--------------------------------------------------
// ADC Gain/Offset Default Value
//--------------------------------------------------
#define _ADC_GAIN_RED               0x80
#define _ADC_GAIN_GREEN             0x80
#define _ADC_GAIN_BLUE              0x80
#define _ADC_OFFSET_RED             0x80
#define _ADC_OFFSET_GREEN           0x80
#define _ADC_OFFSET_BLUE            0x80

code StructAdcDataType tEEPROM_ADC_DATA =
{
    _ADC_GAIN_RED,
    _ADC_GAIN_GREEN,
    _ADC_GAIN_BLUE,
    _ADC_OFFSET_RED,
    _ADC_OFFSET_GREEN,
    _ADC_OFFSET_BLUE,
};

//--------------------------------------------------
// Brightness/Contrast Default Value
//--------------------------------------------------
#define _BRIGHTNESS_VGA             0x82
#define _CONTRAST_VGA               0x80

#define _BRIGHTNESS_DVI             0x82
#define _CONTRAST_DVI               0x80

#define _BRIGHTNESS_VIDEO8          0x80
#define _CONTRAST_VIDEO8            0x80

#define _BRIGHTNESS_YPBPR           0x80
#define _CONTRAST_YPBPR             0x80

#define _BRIGHTNESS_VIDEO16         0x80
#define _CONTRAST_VIDEO16           0x80

#define _BRIGHTNESS_VIDEO16         0x80
#define _CONTRAST_VIDEO16           0x80

#define _BRIGHTNESS_HDMI            0x80
#define _CONTRAST_HDMI              0x80

#define _BRIGHTNESS_DP              0x80
#define _CONTRAST_DP                0x80

code StructColorProc0DataType tEEPROM_COLOR_PROC0_DATA[] =
{
    {
        _BRIGHTNESS_VGA,
        _CONTRAST_VGA,
    },

    {
        _BRIGHTNESS_DVI,
        _CONTRAST_DVI,
    },

    {
        _BRIGHTNESS_VIDEO8,
        _CONTRAST_VIDEO8,
    },

    {
        _BRIGHTNESS_YPBPR,
        _CONTRAST_YPBPR,
    },

    {
        _BRIGHTNESS_VIDEO16,
        _CONTRAST_VIDEO16,
    },

    {
        _BRIGHTNESS_HDMI,
        _CONTRAST_HDMI,
    },

    {
        _BRIGHTNESS_DP,
        _CONTRAST_DP,
    },
};


//--------------------------------------------------
// Color Temperature Default Value
//--------------------------------------------------
#define _CT9300_RED_VGA             0x62
#define _CT9300_GREEN_VGA           0x68
#define _CT9300_BLUE_VGA            0x6F
#define _CT6500_RED_VGA             0x71
#define _CT6500_GREEN_VGA           0x70
#define _CT6500_BLUE_VGA            0x68
#define _CT5800_RED_VGA             0x7A
#define _CT5800_GREEN_VGA           0x77
#define _CT5800_BLUE_VGA            0x69
#define _CTSRGB_RED_VGA             0x80
#define _CTSRGB_GREEN_VGA           0x80
#define _CTSRGB_BLUE_VGA            0x80
#define _CTUSER_RED_VGA             0x80
#define _CTUSER_GREEN_VGA           0x80
#define _CTUSER_BLUE_VGA            0x80

#define _CT9300_RED_DVI             0x62
#define _CT9300_GREEN_DVI           0x68
#define _CT9300_BLUE_DVI            0x6F
#define _CT6500_RED_DVI             0x71
#define _CT6500_GREEN_DVI           0x70
#define _CT6500_BLUE_DVI            0x68
#define _CT5800_RED_DVI             0x7A
#define _CT5800_GREEN_DVI           0x77
#define _CT5800_BLUE_DVI            0x69
#define _CTSRGB_RED_DVI             0x80
#define _CTSRGB_GREEN_DVI           0x80
#define _CTSRGB_BLUE_DVI            0x80
#define _CTUSER_RED_DVI             0x80
#define _CTUSER_GREEN_DVI           0x80
#define _CTUSER_BLUE_DVI            0x80

#define _CT9300_RED_VIDEO8          0x80
#define _CT9300_GREEN_VIDEO8        0x80
#define _CT9300_BLUE_VIDEO8         0x80
#define _CT6500_RED_VIDEO8          0x80
#define _CT6500_GREEN_VIDEO8        0x80
#define _CT6500_BLUE_VIDEO8         0x80
#define _CT5800_RED_VIDEO8          0x80
#define _CT5800_GREEN_VIDEO8        0x80
#define _CT5800_BLUE_VIDEO8         0x80
#define _CTSRGB_RED_VIDEO8          0x80
#define _CTSRGB_GREEN_VIDEO8        0x80
#define _CTSRGB_BLUE_VIDEO8         0x80
#define _CTUSER_RED_VIDEO8          0x80
#define _CTUSER_GREEN_VIDEO8        0x80
#define _CTUSER_BLUE_VIDEO8         0x80

#define _CT9300_RED_YPBPR           0x80
#define _CT9300_GREEN_YPBPR         0x80
#define _CT9300_BLUE_YPBPR          0x80
#define _CT6500_RED_YPBPR           0x80
#define _CT6500_GREEN_YPBPR         0x80
#define _CT6500_BLUE_YPBPR          0x80
#define _CT5800_RED_YPBPR           0x80
#define _CT5800_GREEN_YPBPR         0x80
#define _CT5800_BLUE_YPBPR          0x80
#define _CTSRGB_RED_YPBPR           0x80
#define _CTSRGB_GREEN_YPBPR         0x80
#define _CTSRGB_BLUE_YPBPR          0x80
#define _CTUSER_RED_YPBPR           0x80
#define _CTUSER_GREEN_YPBPR         0x80
#define _CTUSER_BLUE_YPBPR          0x80

#define _CT9300_RED_VIDEO16         0x80
#define _CT9300_GREEN_VIDEO16       0x80
#define _CT9300_BLUE_VIDEO16        0x80
#define _CT6500_RED_VIDEO16         0x80
#define _CT6500_GREEN_VIDEO16       0x80
#define _CT6500_BLUE_VIDEO16        0x80
#define _CT5800_RED_VIDEO16         0x80
#define _CT5800_GREEN_VIDEO16       0x80
#define _CT5800_BLUE_VIDEO16        0x80
#define _CTSRGB_RED_VIDEO16         0x80
#define _CTSRGB_GREEN_VIDEO16       0x80
#define _CTSRGB_BLUE_VIDEO16        0x80
#define _CTUSER_RED_VIDEO16         0x80
#define _CTUSER_GREEN_VIDEO16       0x80
#define _CTUSER_BLUE_VIDEO16        0x80

#define _CT9300_RED_HDMI            0x62
#define _CT9300_GREEN_HDMI          0x68
#define _CT9300_BLUE_HDMI           0x6F
#define _CT6500_RED_HDMI            0x71
#define _CT6500_GREEN_HDMI          0x70
#define _CT6500_BLUE_HDMI           0x68
#define _CT5800_RED_HDMI            0x7A
#define _CT5800_GREEN_HDMI          0x77
#define _CT5800_BLUE_HDMI           0x69
#define _CTSRGB_RED_HDMI            0x80
#define _CTSRGB_GREEN_HDMI          0x80
#define _CTSRGB_BLUE_HDMI           0x80
#define _CTUSER_RED_HDMI            0x80
#define _CTUSER_GREEN_HDMI          0x80
#define _CTUSER_BLUE_HDMI           0x80

#define _CT9300_RED_DP              0x62
#define _CT9300_GREEN_DP            0x68
#define _CT9300_BLUE_DP             0x6F
#define _CT6500_RED_DP              0x71
#define _CT6500_GREEN_DP            0x70
#define _CT6500_BLUE_DP             0x68
#define _CT5800_RED_DP              0x7A
#define _CT5800_GREEN_DP            0x77
#define _CT5800_BLUE_DP             0x69
#define _CTSRGB_RED_DP              0x80
#define _CTSRGB_GREEN_DP            0x80
#define _CTSRGB_BLUE_DP             0x80
#define _CTUSER_RED_DP              0x80
#define _CTUSER_GREEN_DP            0x80
#define _CTUSER_BLUE_DP             0x80

code StructColorTempDataType tEEPROM_COLORTEMP_DATA[] =
{
    {
        _CT9300_RED_VGA,
        _CT9300_GREEN_VGA,
        _CT9300_BLUE_VGA,
        _CT6500_RED_VGA,
        _CT6500_GREEN_VGA,
        _CT6500_BLUE_VGA,
        _CT5800_RED_VGA,
        _CT5800_GREEN_VGA,
        _CT5800_BLUE_VGA,
        _CTSRGB_RED_VGA,
        _CTSRGB_GREEN_VGA,
        _CTSRGB_BLUE_VGA,
        _CTUSER_RED_VGA,
        _CTUSER_GREEN_VGA,
        _CTUSER_BLUE_VGA,
    },

    {
        _CT9300_RED_DVI,
        _CT9300_GREEN_DVI,
        _CT9300_BLUE_DVI,
        _CT6500_RED_DVI,
        _CT6500_GREEN_DVI,
        _CT6500_BLUE_DVI,
        _CT5800_RED_DVI,
        _CT5800_GREEN_DVI,
        _CT5800_BLUE_DVI,
        _CTSRGB_RED_DVI,
        _CTSRGB_GREEN_DVI,
        _CTSRGB_BLUE_DVI,
        _CTUSER_RED_DVI,
        _CTUSER_GREEN_DVI,
        _CTUSER_BLUE_DVI,
    },

    {
        _CT9300_RED_VIDEO8,
        _CT9300_GREEN_VIDEO8,
        _CT9300_BLUE_VIDEO8,
        _CT6500_RED_VIDEO8,
        _CT6500_GREEN_VIDEO8,
        _CT6500_BLUE_VIDEO8,
        _CT5800_RED_VIDEO8,
        _CT5800_GREEN_VIDEO8,
        _CT5800_BLUE_VIDEO8,
        _CTSRGB_RED_VIDEO8,
        _CTSRGB_GREEN_VIDEO8,
        _CTSRGB_BLUE_VIDEO8,
        _CTUSER_RED_VIDEO8,
        _CTUSER_GREEN_VIDEO8,
        _CTUSER_BLUE_VIDEO8,
    },

    {
        _CT9300_RED_YPBPR,
        _CT9300_GREEN_YPBPR,
        _CT9300_BLUE_YPBPR,
        _CT6500_RED_YPBPR,
        _CT6500_GREEN_YPBPR,
        _CT6500_BLUE_YPBPR,
        _CT5800_RED_YPBPR,
        _CT5800_GREEN_YPBPR,
        _CT5800_BLUE_YPBPR,
        _CTSRGB_RED_YPBPR,
        _CTSRGB_GREEN_YPBPR,
        _CTSRGB_BLUE_YPBPR,
        _CTUSER_RED_YPBPR,
        _CTUSER_GREEN_YPBPR,
        _CTUSER_BLUE_YPBPR,
    },

    {
        _CT9300_RED_VIDEO16,
        _CT9300_GREEN_VIDEO16,
        _CT9300_BLUE_VIDEO16,
        _CT6500_RED_VIDEO16,
        _CT6500_GREEN_VIDEO16,
        _CT6500_BLUE_VIDEO16,
        _CT5800_RED_VIDEO16,
        _CT5800_GREEN_VIDEO16,
        _CT5800_BLUE_VIDEO16,
        _CTSRGB_RED_VIDEO16,
        _CTSRGB_GREEN_VIDEO16,
        _CTSRGB_BLUE_VIDEO16,
        _CTUSER_RED_VIDEO16,
        _CTUSER_GREEN_VIDEO16,
        _CTUSER_BLUE_VIDEO16,
    },
    {
        _CT9300_RED_HDMI,
        _CT9300_GREEN_HDMI,
        _CT9300_BLUE_HDMI,
        _CT6500_RED_HDMI,
        _CT6500_GREEN_HDMI,
        _CT6500_BLUE_HDMI,
        _CT5800_RED_HDMI,
        _CT5800_GREEN_HDMI,
        _CT5800_BLUE_HDMI,
        _CTSRGB_RED_HDMI,
        _CTSRGB_GREEN_HDMI,
        _CTSRGB_BLUE_HDMI,
        _CTUSER_RED_HDMI,
        _CTUSER_GREEN_HDMI,
        _CTUSER_BLUE_HDMI,
    },
    {

        _CT9300_RED_DP,
        _CT9300_GREEN_DP,
        _CT9300_BLUE_DP,
        _CT6500_RED_DP,
        _CT6500_GREEN_DP,
        _CT6500_BLUE_DP,
        _CT5800_RED_DP,
        _CT5800_GREEN_DP,
        _CT5800_BLUE_DP,
        _CTSRGB_RED_DP,
        _CTSRGB_GREEN_DP,
        _CTSRGB_BLUE_DP,
        _CTUSER_RED_DP,
        _CTUSER_GREEN_DP,
        _CTUSER_BLUE_DP,

    },
};


code BYTE tEEPROM_USER_FIFO_MODE_DEFAULT[] =
{
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

#else

extern code StructSystemDataType tEEPROM_SYSTEM_DATA;
extern code StructOsdUserDataType tEEPROM_OSDUSER_DATA;
extern code StructOsdReserveDataType tEEPROM_OSDRESERVE_DATA;
extern code StructAdcDataType tEEPROM_ADC_DATA;
extern code StructColorProc0DataType tEEPROM_COLOR_PROC0_DATA[];
extern code StructColorTempDataType tEEPROM_COLORTEMP_DATA[];
extern code BYTE tEEPROM_USER_FIFO_MODE_DEFAULT[];

#endif

