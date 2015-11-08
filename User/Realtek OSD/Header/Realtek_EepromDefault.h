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




//--------------------------------------------------
// Version Code of Eeprom/Flash
//--------------------------------------------------
#define _USER_CODE                  0x2A

#define _SOURCE_AMOUNT              ((BYTE)(_TMDS_SUPPORT) + (BYTE)(_HDMI_SUPPORT) + (BYTE)(_DP_SUPPORT) + (BYTE)(_VIDEO_SUPPORT) + (BYTE)(_YPBPR_SUPPORT) + 1)
#define _INPUTPORT_GROUP            (20 - (BYTE)(_D0_INPUT_PORT_GROUP) + (BYTE)(_D1_INPUT_PORT_GROUP) - (BYTE)(_A0_INPUT_PORT_GROUP) + (BYTE)(_A1_INPUT_PORT_GROUP) - (BYTE)(_VI_INPUT_PORT_GROUP))
#define _SEARCH_PRI                 (20 - (BYTE)(_INPUT_PORT_SEARCH_POL_0) + (BYTE)(_INPUT_PORT_SEARCH_POL_1) - (BYTE)(_INPUT_PORT_SEARCH_POL_2) + (BYTE)(_INPUT_PORT_SEARCH_POL_3) - (BYTE)(_INPUT_PORT_SEARCH_POL_4))
#define _OTHER_DEFINE               ((BYTE)(_MEMORY_LOCATION) + ((BYTE)_MAX_PRESET_MODE - 48) + (BYTE)(_FLASH_BANK))

// V013 VGA Patch Note (11) Modify 20100416 Start
// Patch Reason : Add FIFO Mode Only to save EEPROM space.
// Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
// Make sure Version Code is changed if user changes _FIFO_MODE_ONLY switch.
/*
#define _VERSION_CODE               ((BYTE)(_USER_CODE) + (BYTE)(_SOURCE_AMOUNT) + (BYTE)(_INPUTPORT_GROUP) + (BYTE)(_SEARCH_PRI) + (BYTE)(_OTHER_DEFINE) + (BYTE)(_DDCCI_SUPPORT))
*/
#define _VERSION_CODE               ((BYTE)(_USER_CODE) + (BYTE)(_SOURCE_AMOUNT) + (BYTE)(_INPUTPORT_GROUP) + (BYTE)(_SEARCH_PRI) + (BYTE)(_OTHER_DEFINE) + (BYTE)(_DDCCI_SUPPORT) + (BYTE)(_FIFO_MODE_ONLY))
// V013 VGA Patch Note (11) Modify 20100416 End

#ifdef __REALTEK_EEPROM__


//--------------------------------------------------
// System Data Default Value
//--------------------------------------------------
#if (_DDCCI_SUPPORT == _ON)
#define _MONITORFLAG                0xc0
#else
#define _MONITORFLAG                0x80
#endif

#define _SEARCHINDEX                0x00
#define _BACKLIGHT                  0x80  //0x32

// V013 VGA Patch Note (11) Modify 20100416 Start
// Patch Reason : Add FIFO Mode Only to save EEPROM space.
// Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
/*
#define _USERFIFOMODE               0x0f
*/
#if(_FIFO_MODE_ONLY == _ON)
#define _USERFIFOMODE               0x3f
#else
#define _USERFIFOMODE               0x0f
#endif
// V013 VGA Patch Note (11) Modify 20100416 End

#define _OD_SELECTED                0x40  // Delta Gain = _ODSELECTED/64

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#if(_COLOR_FORMAT_CONVERT == _ON)
#define _COLOR_SETTING              0x02
#endif
// V012 Modify 20100304 End

code StructSystemDataType tEEPROM_SYSTEM_DATA =
{
    _MONITORFLAG,
    _SEARCHINDEX,
    _BACKLIGHT,
    _USERFIFOMODE,

    _OD_SELECTED,

    // V012 Modify 20100304 Start
    // V012 Patch Note (1) : Add RGB/YUV color space convert function.
    #if(_COLOR_FORMAT_CONVERT == _ON)
    _COLOR_SETTING,
    #endif
    // V012 Modify 20100304 End

};

//--------------------------------------------------
// OSD User Data Default Value
//--------------------------------------------------
#define _OSD_SETTINGFLAG            0x00
#define _OSD_MANAGEMENTFLAG         0x00
#define _OSD_H_POSITION             0x64
#define _OSD_V_POSITION             0x64
#define _LANGUAGE                   0x00
#define _OSD_TIMEOUT                0x0a
#define _VOLUME                     0x20

#define _COLORTEMP                  0x04  //0x00
#define _SHARPNESS                  0x02

#define _VIVID_FLAG                 0x00
#define _WINDOW_SIZE_H_POSITION     0x00
#define _WINDOW_SIZE_V_POSITION     0x00
#define _WINDOW_SIZE_H_WIDTH        0x280
#define _WINDOW_SIZE_V_HEIGHT       0x200
#define _VIVID_ICM_RED_HUE          0x08
#define _VIVID_ICM_RED_SAT          0x08
#define _VIVID_ICM_GREEN_HUE        0x08
#define _VIVID_ICM_GREEN_SAT        0x08
#define _VIVID_ICM_BLUE_HUE         0x08
#define _VIVID_ICM_BLUE_SAT         0x08
#define _VIVID_BRIGHTNESS           0x96
#define _VIVID_CONTRAST             0x80
#define _VIVID_COLOR_PEAKING        0x00
#define _HUE                        ((_HUE_MAX + _HUE_MIN) / 2)
#define _SATURATION                 ((_SATURATION_MAX + _SATURATION_MIN) / 2)

code StructOsdUserDataType tEEPROM_OSDUSER_DATA =
{
    _OSD_SETTINGFLAG,
    _OSD_MANAGEMENTFLAG,
    _OSD_H_POSITION,
    _OSD_V_POSITION,
    _LANGUAGE,
    _OSD_TIMEOUT,
    _VOLUME,

    _COLORTEMP,
    _SHARPNESS,

    _VIVID_FLAG,
    _WINDOW_SIZE_H_POSITION,
    _WINDOW_SIZE_V_POSITION,
    _WINDOW_SIZE_H_WIDTH,
    _WINDOW_SIZE_V_HEIGHT,
    _VIVID_ICM_RED_HUE,
    _VIVID_ICM_RED_SAT,
    _VIVID_ICM_GREEN_HUE,
    _VIVID_ICM_GREEN_SAT,
    _VIVID_ICM_BLUE_HUE,
    _VIVID_ICM_BLUE_SAT,
    _VIVID_BRIGHTNESS,
    _VIVID_CONTRAST,
    _VIVID_COLOR_PEAKING,
    _HUE,
    _SATURATION,
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
#define _ADC_GAIN_RED               0x63
#define _ADC_GAIN_GREEN             0x5D
#define _ADC_GAIN_BLUE              0x68
#define _ADC_OFFSET_RED             0x91//sjp20111026
#define _ADC_OFFSET_GREEN           0x8A
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
#define _BRIGHTNESS_VGA             0x80
#define _CONTRAST_VGA               0x7F//sjp20110726

#define _BRIGHTNESS_DVI             0x80
#define _CONTRAST_DVI               0x80

#define _BRIGHTNESS_VIDEO8          0x80
#define _CONTRAST_VIDEO8            0x80

#define _BRIGHTNESS_YPBPR           0x80
#define _CONTRAST_YPBPR             0x80

#define _BRIGHTNESS_HDMI            0x80
#define _CONTRAST_HDMI              0x80

#define _BRIGHTNESS_DP              0x80
#define _CONTRAST_DP                0x80

code StructColorProc0DataType tEEPROM_COLOR_PROC0_DATA[] =
{
    {
        _BRIGHTNESS_VGA,
        _CONTRAST_VGA,
        0x00,
        0x00,
        80,
    },

#if(_YPBPR_SUPPORT == _ON)
    {
        _BRIGHTNESS_YPBPR,
        _CONTRAST_YPBPR,
        0x00,
        0x00,
        80,
    },
#endif

#if(_TMDS_SUPPORT == _ON)
    {
        _BRIGHTNESS_DVI,
        _CONTRAST_DVI,
        0x00,
        0x00,
        80,
    },
#endif

#if(_HDMI_SUPPORT == _ON)
    {
        _BRIGHTNESS_HDMI,
        _CONTRAST_HDMI,
        0x00,
        0x00,
        80,
    },
#endif

#if(_DP_SUPPORT == _ON)
    {
        _BRIGHTNESS_DP,
        _CONTRAST_DP,
        0x00,
        0x00,
        80,
    },
#endif

#if(_VIDEO_SUPPORT == _ON)
    {
        _BRIGHTNESS_VIDEO8,
        _CONTRAST_VIDEO8,
        0x00,
        0x00,
        80,
    },
#endif

};
//--------------------------------------------------
// LSlumiData  Default Value//sjp20110905
//--------------------------------------------------
#define lumi_DICOM350     0x1C2
#define lumi_DICOM400     0x202
#define lumi_DICOM450     0x240
#define lumi_DICOM500     0x282
#define lumi_DICOM550     0x2C0
#define lumi_DICOM600     0x2E5
#define lumi_DICOM650     0x2FE
#define lumi_DICOM700     0x317

code StructLSlumiDataType tEEPROM_LSLUMI_DATA =
{
	lumi_DICOM350,
	lumi_DICOM400,
	lumi_DICOM450,
	lumi_DICOM500,
	lumi_DICOM550,
	lumi_DICOM600,
	lumi_DICOM650,
	lumi_DICOM700,
};
//--------------------------------------------------
// PWMlumiData  Default Value//sjp20110905
//--------------------------------------------------
#define PWM_DICOM350  0x7D0
#define PWM_DICOM400  0x70E
#define PWM_DICOM450  0x638
#define PWM_DICOM500  0x567
#define PWM_DICOM550  0x47F
#define PWM_DICOM600  0x3F0
#define PWM_DICOM650  0x385
#define PWM_DICOM700  0x329

code StructPWMlumiDataType tEEPROM_PWMLUMI_DATA =
{
PWM_DICOM350,
PWM_DICOM400,
PWM_DICOM450,
PWM_DICOM500,
PWM_DICOM550,
PWM_DICOM600,
PWM_DICOM650,
PWM_DICOM700,
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
extern code  StructLSlumiDataType tEEPROM_LSLUMI_DATA;//adam20110620
extern code StructPWMlumiDataType tEEPROM_PWMLUMI_DATA;//SJP20110715
#endif

