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
// ID Code      : ModeTable.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

// V012 Modify 20100322 Start
// V012 Patch Note (8) : Add OOR Table to indicate in which modes the display could show OOR directly.

// V013 VGA Patch Note (24) Modify 20100518 Start
// Patch Reason : Mode Search Updates.
/*
#define _MAX_OOR_MODE_NUMBER        5
*/
#define _MAX_OOR_MODE_NUMBER        6
// V013 VGA Patch Note (24) Modify 20100518 End

// V012 Modify 20100322 End

//--------------------------------------------------
// Mode Define
// We have two kind of mode set. One is Preset mode
// and another is User mode. If you have to add a new
// mode, please add it into "Preset Mode" and modify
// the defination of _MAX_PRESET_MODE.
//--------------------------------------------------

// V012 Modify 20100324 Start
// V012 Patch Note (3) : Modify mode table and mode search according to SQE testing items, and to sync with Dell case.
/*
#define _MAX_PRESET_MODE            88
*/
// V012 Modify 20100324 End

#define _MODE_FIRST                 252
#define _MODE_EXIST                 253
#define _MODE_NOSUPPORT             254
#define _MODE_NOSIGNAL              255

// V012 Modify 20100324 Start
// V012 Patch Note (3) : Modify mode table and mode search according to SQE testing items, and to sync with Dell case.
/*
//--------------------------------------------------
// Preset Mode
//--------------------------------------------------
enum PresetModeDef
{
    _MODE_640x350_70HZ = 0,         // Mode 00: 640x350_70Hz, 720x350_70Hz
    _MODE_640x350_85HZ,             // Mode 01: 640x350_85Hz
    _MODE_720x400_70HZ,             // Mode 02: 640x400_70Hz, 720x400_70Hz
    _MODE_720x400_85HZ,             // Mode 03: 640x400_85Hz, 720x400_85Hz
    _MODE_640x480_60HZ,             // Mode 04:
    _MODE_640x480_66HZ,             // Mode 05:
    _MODE_640x480_72HZ,             // Mode 06:
    _MODE_640x480_75HZ,             // Mode 07:
    _MODE_640x480_85HZ,             // Mode 08:
    _MODE_800x600_56HZ,             // Mode 09:
    _MODE_800x600_60HZ,             // Mode 10:
    _MODE_800x600_72HZ,             // Mode 11:
    _MODE_800x600_75HZ,             // Mode 12:
    _MODE_800x600_85HZ,             // Mode 13:
    _MODE_832x624_75HZ,             // Mode 14:
    _MODE_1024x768_60HZ,            // Mode 15:
    _MODE_1024x768_70HZ,            // Mode 16:
    _MODE_1024x768_75HZ,            // Mode 17:
    _MODE_1024x768_85HZ,            // Mode 18:
    _MODE_1024x800_85HZ,            // Mode 19:
    _MODE_1152x864_60HZ,            // Mode 20:
    _MODE_1152x864_70HZ,            // Mode 21:
    _MODE_1152x864_75HZ,            // Mode 22:
    _MODE_1152x864_85HZ,            // Mode 23:
    _MODE_1152x870_75HZ,            // Mode 24:
    _MODE_1152x900_66HZ,            // Mode 25:
    _MODE_1152x900_76HZ,            // Mode 26:
    _MODE_1280x720_60HZ,            // Mode 27:
    _MODE_1280x720_75HZ,            // Mode 28:
    _MODE_1280x768_60HZ,            // Mode 29:
    _MODE_1280x768_70HZ,            // Mode 30:
    _MODE_1280x768_75HZ,            // Mode 31:
    _MODE_1280x800_60HZ,            // Mode 32:
    _MODE_1280x960_60HZ,            // Mode 33:
    _MODE_1280x960_75HZ,            // Mode 34:
    _MODE_1280x960_85HZ,            // Mode 35:
    _MODE_1280x1024_60HZ,           // Mode 36:
    _MODE_1280x1024_70HZ,           // Mode 37:
    _MODE_1280x1024_75HZ,           // Mode 38:
    _MODE_1280x1024_85HZ,           // Mode 39:
    _MODE_1440x900_60HZ,            // Mode 40:
    _MODE_1440x900_60HZ_RB,         // Mode 41:
    _MODE_1440x900_75HZ,            // Mode 42:
    _MODE_1600x1200_60HZ,           // Mode 43:
    _MODE_1600x1200_65HZ,           // Mode 44:
    _MODE_1600x1200_70HZ,           // Mode 45:
    _MODE_1600x1200_75HZ,           // Mode 46:
    _MODE_1600x1200_85HZ,           // Mode 47:
    _MODE_1680x1050_60HZ,           // Mode 48:
    _MODE_1680x1050_60HZ_RB,        // Mode 49:
    _MODE_1680x1050_75HZ,           // Mode 50:
    _MODE_1680x1050_75HZ_RB,        // Mode 51:
    _MODE_1920x1200_60HZ,           // Mode 52:
    _MODE_1920x1200_60HZ_RB,        // Mode 53:
    _MODE_1920x1200_75HZ,           // Mode 54:
    _MODE_1920x1440_60HZ,           // Mode 55:
    _MODE_1440x480i_60HZ,           // Mode 56:
    _MODE_1920x1080i_60HZ,          // Mode 57:
    _MODE_1920x1080p_60HZ,          // Mode 58:
    _MODE_1920x1080_60HZ,           // Mode 59:
    _MODE_1920x1080_60HZ_RB,        // Mode 60:
    _MODE_720x480i_60Hz,            // Mode 61:
    _MODE_720x576i_50Hz,            // Mode 62:
    _MODE_720x576p_50Hz,            // Mode 63:
    _MODE_1920x1080i_50Hz,          // Mode 64:
    _MODE_1280x720p_50Hz,           // Mode 65:
    _MODE_1440x576i_50Hz,           // Mode 66:
    _MODE_1440x576p_50Hz,           // Mode 67:
    _MODE_1920x1080_75Hz,           // Mode 68:
    _MODE_640x480_50HZ,             //Mode 69:
    _MODE_848x480_70HZ,             //Mode 70:
    _MODE_848x480_72HZ,             //Mode 71:
    _MODE_848x480_75HZ,             //Mode 72:
    _MODE_848x480_60HZ,             //Mode 73:
    _MODE_1280x720p_60HZ,           //Mode 74:
    _MODE_1024x768_60HZ_MAC,        //Mode 75:
    _MODE_1280x800_60HZ_RB,         //Mode 76:
    _MODE_1360x768_60HZ,            //Mode 77:
    _MODE_1366x768_60HZ,            //Mode 78:
    _MODE_1024x768_75HZ_MAC,        //Mode 79:
    _MODE_1280x800_75HZ,            //Mode 80:
    _MODE_1280x800_85HZ,            //Mode 81:
    _MODE_1440x900_85HZ,            //Mode 82:
    _MODE_1680x1050_85HZ,           //Mode 83:
    _MODE_1920x1080p_50HZ,          //Mode 84:
    _MODE_1792x1344_60HZ,           //Mode 85:
    _MODE_1856x1392_60HZ,           //Mode 86:
    _MODE_1280x768_60HZ_R,          //Mode 87:
};
*/
//--------------------------------------------------
// Preset Mode
//--------------------------------------------------
enum PresetModeDef
{
    _MODE_640x350_70HZ = 0,         // Mode 00:
    _MODE_640x350_70HZ_QD,          // Mode 01:
    _MODE_640x400_56HZ,             // Mode 02:
    _MODE_640x400_60HZ,             // Mode 03:
    _MODE_720x400_70HZ,             // Mode 04:
    _MODE_640x400_70HZ,             // Mode 05:
    _MODE_720x400_85HZ,             // Mode 06:
    _MODE_640x400_85HZ,             // Mode 07:
    _MODE_640x480_50HZ,             // Mode 08:
    _MODE_640x480_60HZ,             // Mode 09:
    _MODE_640x480_66HZ,             // Mode 10:
    _MODE_640x480_72HZ,             // Mode 11:
    _MODE_640x480_75HZ,             // Mode 12:
    _MODE_640x480_85HZ,             // Mode 13:
    _MODE_720x480_60HZ,             // Mode 14:
    _MODE_720x480_60HZ_GTF,         // Mode 15:
    _MODE_720x576_60HZ,             // Mode 16:
    _MODE_720x576_75HZ,             // Mode 17:
    _MODE_800x600_56HZ,             // Mode 18:
    _MODE_800x600_60HZ,             // Mode 19:
    _MODE_800x600_70HZ,             // Mode 20:
    _MODE_800x600_72HZ,             // Mode 21:
    _MODE_800x600_75HZ,             // Mode 22:
    _MODE_800x600_85HZ,             // Mode 23:
    _MODE_832x624_75HZ,             // Mode 24:
    _MODE_848x480_60HZ,             // Mode 25:
    _MODE_848x480_70HZ,             // Mode 26:
    _MODE_848x480_72HZ,             // Mode 27:
    _MODE_848x480_75HZ,             // Mode 28:
    _MODE_1024x768_50HZ,            // Mode 29:
    _MODE_1024x768_60HZ,            // Mode 30:
    _MODE_1024x768_60HZ_MAC,        // Mode 31:
    _MODE_1024x768_66HZ,            // Mode 32:
    _MODE_1024x768_70HZ,            // Mode 33:
    _MODE_1024x768_72HZ,            // Mode 34:
    _MODE_1024x768_75HZ,            // Mode 35:
    _MODE_1024x768_75HZ_MAC,        // Mode 36:
    _MODE_1024x768_85HZ,            // Mode 37:
    _MODE_1152x864_60HZ,            // Mode 38:
    _MODE_1152x864_70HZ,            // Mode 39:
    _MODE_1152x864_75HZ,            // Mode 40:
    _MODE_1152x864_85HZ,            // Mode 41:
    _MODE_1152x870_75HZ,            // Mode 42:
    _MODE_1152x900_66HZ,            // Mode 43:
    _MODE_1152x900_66HZ_S,          // Mode 44:
    _MODE_1280x720p_60HZ,           // Mode 45:
    _MODE_1280x720_70HZ,            // Mode 46:
    _MODE_1280x720_72HZ,            // Mode 47:
    _MODE_1280x720_75HZ,            // Mode 48:
    _MODE_1280x768_50HZ,            // Mode 49:
    _MODE_1280x768_60HZ,            // Mode 50:
    _MODE_1280x768_60HZ_RB,         // Mode 51:
    _MODE_1280x768_70HZ,            // Mode 52:
    _MODE_1280x768_75HZ,            // Mode 53:
    _MODE_1280x768_85HZ,            // Mode 54:
    _MODE_1280x800_60HZ,            // Mode 55:
    _MODE_1280x800_60HZ_RB,         // Mode 56:
    _MODE_1280x800_70HZ,            // Mode 57:
    _MODE_1280x800_72HZ,            // Mode 58:
    _MODE_1280x800_75HZ,            // Mode 59:
    _MODE_1280x960_60HZ,            // Mode 60:
    _MODE_1280x960_70HZ,            // Mode 61:
    _MODE_1280x960_72HZ,            // Mode 62:
    _MODE_1280x960_75HZ,            // Mode 63:
    _MODE_1280x960_85HZ,            // Mode 64:
    _MODE_1280x1024_60HZ,           // Mode 65:
    _MODE_1280x1024_70HZ,           // Mode 66:
    _MODE_1280x1024_70HZ_1,         // Mode 67:
    _MODE_1280x1024_72HZ,           // Mode 68:
    _MODE_1280x1024_75HZ,           // Mode 69:
    _MODE_1280x1024_85HZ,           // Mode 70:
    _MODE_1360x768_60HZ,            // Mode 71:
    _MODE_1366x768_60HZ,            // Mode 72:
    _MODE_1440x900_60HZ,            // Mode 73:
    _MODE_1440x900_60HZ_RB,         // Mode 74:
    _MODE_1440x900_75HZ,            // Mode 75:
    _MODE_1600x1200_60HZ,           // Mode 76:
    _MODE_1600x1200_60HZ_RB,        // Mode 77:
    _MODE_1600x1200_65HZ,           // Mode 78:
    _MODE_1600x1200_70HZ,           // Mode 79:
    _MODE_1680x1050_60HZ,           // Mode 80:
    _MODE_1680x1050_60HZ_RB,        // Mode 81:
    _MODE_1680x1050_75HZ,           // Mode 82:
    _MODE_1920x1200_60HZ,           // Mode 83:
    _MODE_1920x1200_60HZ_RB,        // Mode 84:
    _MODE_1920x1440_60HZ,           // Mode 85:

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    _MODE_720x480i_60Hz,            // Mode 86:
    _MODE_720x576i_50Hz,            // Mode 87:
    */
    // V013 VGA Patch Note (24) Modify 20100514 End

    _MODE_720x576p_50Hz,            // Mode 86:
    _MODE_1440x480i_60HZ,           // Mode 87:
    _MODE_1920x1080i_50Hz,          // Mode 88:
    _MODE_1920x1080i_60HZ,          // Mode 89:
    _MODE_1920x1080p_50Hz,          // Mode 90:
    _MODE_1920x1080_60HZ,           // Mode 91:
    _MODE_1152x900_76HZ,            // Mode 92:
    _MODE_1600x1000_60HZ,           // Mode 93:
    _MODE_1600x1000_60HZ_RB,        // Mode 94:
    _MODE_1600x1000_75HZ,           // Mode 95:
    _MODE_1440x576i_50Hz,           // Mode 96:
    _MODE_1920x1080_60HZ_XBOX,      // Mode 97:
    _MODE_1920x1080_60HZ_RB,        // Mode 98:
    _MODE_1176x664_60HZ,            // Mode 99:
    _MODE_1176x664_72HZ,            // Mode 100:
    _MODE_640x500_58Hz_NN,          // Mode 101:
    _MODE_848x480_60HZ_PP,          // Mode 102:
    _MODE_1600x900_60HZ_CVR,        // Mode 103:
    _MODE_1680x1050_75HZ_RB,        // Mode 104:
    _MODE_1280x1024_76HZ,           // Mode 105:
    _MODE_640x500_58HZ,             // Mode 106:
    _MODE_1600x900_60HZ_RB,         // Mode 107:
    _MODE_2048x1152_60HZ_RB,        // Mode 108:
    _MODE_1280x720_60HZ_2,          // Mode 109:
    _MODE_1920x1080_50HZ_2,         // Mode 110:
    _MODE_1920x1200_50HZ_RB,        // Mode 111:
    _MODE_2048x1152_60HZ,           // Mode 112:
    _MODE_1920x1080p_60HZ,          // Mode 113:
    _MODE_640x350_85HZ,             // Mode 114:
    _MODE_1920x1440_60HZ_RB,        // Mode 115:
    _MODE_2048x1152_60HZ_RB_2,      // Mode 116:
    _MODE_1152x864_85HZ_2,          // Mode 117:
    _MODE_1600x1280_60HZ,           // Mode 118:
    _MODE_720x480p_60HZ,            // Mode 119:
    _MODE_1280x720p_50HZ,           // Mode 120:
    _MODE_1600x1000_60HZ_2,         // Mode 121:
    _MODE_1920x1080i_50HZ_2,        // Mode 122:

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    // _MODE_1600x900_60HZ is a non-RB mode, suggested by Y.C., which could solve
    // Graphic Card issue.
    _MODE_1600x900_60HZ,            // Mode 123;
    // V013 VGA Patch Note (24) Modify 20100514 End

    _MAX_PRESET_MODE,
};
// V012 Modify 20100324 End


//--------------------------------------------------
// Defination of Mode Detection Tolerance
//--------------------------------------------------
#define _HFREQ_TOLERANCE            10      // kHz. Ex: 1.5kHz ==> 15
#define _VFREQ_TOLERANCE            10      // Hz.  Ex: 1.5Hz ==> 15


//--------------------------------------------------
// Defination of Mode Polarity
//--------------------------------------------------
#define _SYNC_HN_VN                 0x01
#define _SYNC_HP_VN                 0x02
#define _SYNC_HN_VP                 0x04
#define _SYNC_HP_VP                 0x08

// V013 VGA Patch Note (23) Modify 20100513 Start
// Patch Reason : For Video Mode Clamp Position Setting Flow
#define _VIDEO_MODE_GROUP1          0x10
#define _VIDEO_MODE_GROUP2          0x20
// V013 VGA Patch Note (23) Modify 20100513 End

#ifdef __MAIN__

// V012 Modify 20100324 Start
// V012 Patch Note (3) : Modify mode table and mode search according to SQE testing items, and to sync with Dell case.
/*
ModeTableType code tINPUTMODE_PRESET_TABLE[_MAX_PRESET_MODE] =
{
    //--------------------------------------------------
    // Preset Modes
    //--------------------------------------------------

    {   // Mode 0 : 640 x 350 x 70 Hz
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        640, 350,                                                           // InputWidth, InputHeight,
        315, 700,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        800, 449,                                                           // IHTotal, IVTotal,
        144, 62,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 1 : 640 x 350 x 85 Hz
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        640, 350,                                                           // InputWidth, InputHeight,
        378, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE + 5, _VFREQ_TOLERANCE + 5,                         // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        832, 445,                                                           // IHTotal, IVTotal,
        160, 63,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 2 : 720 x 400 x 70 Hz
        //0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        0 | _SYNC_HN_VP | _SYNC_HP_VP | _SYNC_HN_VN,                        // Polarity Flags,
        720, 400,                                                           // InputWidth, InputHeight,
        315, 700,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        900, 449,                                                           // IHTotal, IVTotal,
        162, 37,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 3 : 720 x 400 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        720, 400,                                                           // InputWidth, InputHeight,
        380, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE + 5, _VFREQ_TOLERANCE + 5,                         // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        936, 446,                                                           // IHTotal, IVTotal,
        180, 45,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 4 : 640 x 480 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        640, 480,                                                           // InputWidth, InputHeight,
        315, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        800, 525,                                                           // IHTotal, IVTotal,
        136, 27,                                                            // IHStartPos, IVStartPos,

    },

    {   // Mode 5 : 640 x 480 x 66 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        640, 480,                                                           // InputWidth, InputHeight,
        350, 666,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        864, 525,                                                           // HTotal, VTotal,
        160, 42,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 6 : 640 x 480 x 72 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        640, 480,                                                           // InputWidth, InputHeight,
        378, 728,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        832, 520,                                                           // HTotal, VTotal,
        160, 23,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 7 : 640 x 480 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        640, 480,                                                           // InputWidth, InputHeight,
        375, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        840, 500,                                                           // IHTotal, IVTotal,
        184, 19,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 8 : 640 x 480 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        640, 480,                                                           // InputWidth, InputHeight,
        433, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        832, 510,                                                           // IHTotal, IVTotal,
        136, 28,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 9 : 800 x 600 x 56 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        800, 600,                                                           // InputWidth, InputHeight,
        351, 562,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1024, 625,                                                          // HTotal, VTotal,
        200, 24,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 10 : 800 x 600 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        800, 600,                                                           // InputWidth, InputHeight,
        378, 603,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1056, 628,                                                          // IHTotal, IVTotal,
        216, 27,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 11 : 800 x 600 x 72 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        800, 600,                                                           // InputWidth, InputHeight,
        480, 720,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1040, 666,                                                          // HTotal, VTotal,
        184, 29,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 12 : 800 x 600 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        800, 600,                                                           // InputWidth, InputHeight,
        468, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1056, 625,                                                          // IHTotal, IVTotal,
        240, 24,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 13 : 800 x 600 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        800, 600,                                                           // InputWidth, InputHeight,
        536, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1048, 631,                                                          // IHTotal, IVTotal,
        216, 30,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 14 : 832 x 624 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        832, 624,                                                           // InputWidth, InputHeight,
        497, 745,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1152, 667,                                                          // IHTotal, IVTotal,
        288, 42,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 15 : 1024 x 768 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HP_VP,                        // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        483, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1344, 806,                                                          // IHTotal, IVTotal,
        296, 35,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 16 : 1024 x 768 x 70 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HP_VP,                        // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        564, 700,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1328, 806,                                                          // HTotal, VTotal,
        280, 35,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 17 : 1024 x 768 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HP_VP,                        // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        600, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1312, 800,                                                          // IHTotal, IVTotal,
        272, 31,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 18 : 1024 x 768 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        682, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1376, 808,                                                          // IHTotal, IVTotal,
        304, 39,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 19 : 1024 x 800 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1024, 800,                                                          // InputWidth, InputHeight,
        715, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1320, 837,                                                          // IHTotal, IVTotal,
        280, 35,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 20 : 1152 x 864 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1152, 864,                                                          // InputWidth, InputHeight,
        537, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1512, 894,                                                          // HTotal, VTotal,
        300, 30,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 21 : 1152 x 864 x 70 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1152, 864,                                                          // InputWidth, InputHeight,
        642, 702,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1472, 914,                                                          // HTotal, VTotal,
        288, 49,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 22 : 1152 x 864 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1152, 864,                                                          // InputWidth, InputHeight,
        675, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1600, 900,                                                          // IHTotal, IVTotal,
        384, 35,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 23 : 1152 x 864 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1152, 864,                                                          // InputWidth, InputHeight,
        770, 850,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1576, 907,                                                          // HTotal, VTotal,
        360, 42,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 24 : 1152 x 870 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1152, 870,                                                          // InputWidth, InputHeight,
        686, 750,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1456, 915,                                                          // HTotal, VTotal,
        272, 42,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 25 : 1152 x 900 x 66 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1152, 900,                                                          // InputWidth, InputHeight,
        618, 660,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1528, 937,                                                          // HTotal, VTotal,
        336, 35,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 26 : 1152 x 900 x 76 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1152, 900,                                                          // InputWidth, InputHeight,
        718, 766,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1504, 937,                                                          // HTotal, VTotal,
        320, 35,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 27 : 1280 x 720 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 720,                                                          // InputWidth, InputHeight,
        447, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1656, 746,                                                          // HTotal, VTotal,
        339, 25,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 28 : 1280 x 720 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 720,                                                          // InputWidth, InputHeight,
        564, 750,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1688, 751,                                                          // HTotal, VTotal,
        340, 31,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 29 : 1280 x 768 x 60 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1280, 768,                                                          // InputWidth, InputHeight,
        477, 598,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1664, 798,                                                          // IHTotal, IVTotal,
        320, 27,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 30 : 1280 x 768 x 70 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1280, 768,                                                          // InputWidth, InputHeight,
        560, 700,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1692, 799,                                                          // HTotal, VTotal,
        336, 31,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 31 : 1280 x 768 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 768,                                                          // InputWidth, InputHeight,
        601, 750,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1696, 805,                                                          // HTotal, VTotal,
        346, 33,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 32 : 1280 x 800 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 800,                                                          // InputWidth, InputHeight,
        497, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1680, 831,                                                          // IHTotal, IVTotal,
        328, 28,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 33 : 1280 x 960 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 960,                                                          // InputWidth, InputHeight,
        600, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1800, 1000,                                                         // IHTotal, IVTotal,
        424, 39,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 34 : 1280 x 960 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 960,                                                          // InputWidth, InputHeight,
        750, 750,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1680, 1000,                                                         // HTotal, VTotal,
        368, 39,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 35 : 1280 x 960 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 960,                                                          // InputWidth, InputHeight,
        860, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1728, 1011,                                                         // IHTotal, IVTotal,
        384, 50,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 36 : 1280 x 1024 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 1024,                                                         // InputWidth, InputHeight,
        640, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1688, 1066,                                                         // IHTotal, IVTotal,
        360, 41,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 37 : 1280 x 1024 x 70 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 1024,                                                         // InputWidth, InputHeight,
        746, 700,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1722, 1065,                                                         // HTotal, VTotal,
        359, 40,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 38 : 1280 x 1024 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 1024,                                                         // InputWidth, InputHeight,
        800, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1688, 1066,                                                         // IHTotal, IVTotal,
        392, 41,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 39 : 1280 x 1024 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 1024,                                                         // InputWidth, InputHeight,
        911, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1728, 1072,                                                         // IHTotal, IVTotal,
        384, 47,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 40 : 1440 x 900 x 60 Hz
        0 | _SYNC_HN_VP | _SYNC_HN_VN | _SYNC_HP_VP,                        // Polarity Flags,
        1440, 900,                                                          // InputWidth, InputHeight,
        559, 598,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1904, 934,                                                          // HTotal, VTotal,
        384, 31,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 41 : 1440 x 900 x 60 Hz  (Reduced Blanking)
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1440, 900,                                                          // InputWidth, InputHeight,
        557, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1600, 926,                                                          // HTotal, VTotal,
        112, 23,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 42 : 1440 x 900 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1440, 900,                                                          // InputWidth, InputHeight,
        706, 750,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1936, 942,                                                          // HTotal, VTotal,
        400, 39,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 43 : 1600 x 1200 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HP_VP,                        // Polarity Flags,
        1600, 1200,                                                         // InputWidth, InputHeight,
        750, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE - 5, _VFREQ_TOLERANCE,                             // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2160, 1250,                                                         // HTotal, VTotal,
        496, 49,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 44 : 1600 x 1200 x 65 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1600, 1200,                                                         // InputWidth, InputHeight,
        812, 650,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2160, 1250,                                                         // HTotal, VTotal,
        496, 49,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 45 : 1600 x 1200 x 70 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1600, 1200,                                                         // InputWidth, InputHeight,
        875, 700,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2160, 1250,                                                         // HTotal, VTotal,
        496, 49,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 46 : 1600 x 1200 x 75 Hz
        0 | _SYNC_HP_VN | _SYNC_HP_VP,                                      // Polarity Flags,
        1600, 1200,                                                         // InputWidth, InputHeight,
        937, 750,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2160, 1250,                                                         // HTotal, VTotal,
        496, 49,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 47 : 1600 x 1200 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1600, 1200,                                                         // InputWidth, InputHeight,
        1062, 850,                                                          // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2160, 1250,                                                         // HTotal, VTotal,
        496, 49,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 48 : 1680 x 1050 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1680, 1050,                                                         // InputWidth, InputHeight,
        653, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2240, 1089,                                                         // HTotal, VTotal,
        456, 36,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 49 : 1680 x 1050 x 60 Hz (Reduced Blanking)
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1680, 1050,                                                         // InputWidth, InputHeight,
        647, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1840, 1080,                                                         // HTotal, VTotal,
        112, 27,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 50 : 1680 x 1050 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1680, 1050,                                                         // InputWidth, InputHeight,
        823, 750,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2272, 1099,                                                         // HTotal, VTotal,
        472, 46,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 51 : 1680 x 1050 x 75 Hz (Reduced Blanking)
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1680, 1050,                                                         // InputWidth, InputHeight,
        815, 750,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1840, 1088,                                                         // HTotal, VTotal,
        112, 35,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 52 : 1920 x 1200 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920, 1200,                                                         // InputWidth, InputHeight,
        746, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2592, 1245,                                                         // HTotal, VTotal,
        536, 42,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 53 : 1920 x 1200 x 60 Hz (Reduced Blanking)
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1920, 1200,                                                         // InputWidth, InputHeight,
        740, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2080, 1235,                                                         // HTotal, VTotal,
        112, 32,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 54 : 1920 x 1200 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP,                                      // Polarity Flags,
        1920, 1200,                                                         // InputWidth, InputHeight,
        940, 750,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2608, 1255,                                                         // HTotal, VTotal,
        552, 52,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 55 : 1920 x 1440 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1920, 1440,                                                         // InputWidth, InputHeight,
        900, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2600, 1500,                                                         // HTotal, VTotal,
        552, 59,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 56 : 1440 x 480i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1440, 240,                                                          // InputWidth, InputHeight,
        157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1716, 525,                                                          // HTotal, VTotal,
        238, 18,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 57 : 1920 x 1080i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1920, 540,                                                          // InputWidth, InputHeight,
        337, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2200, 562,                                                          // HTotal, VTotal,
        192, 20,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 58 : 1920 x 1080P x 60 Hz(1080P)
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
        675, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2200, 1125,                                                         // HTotal, VTotal,
        192, 41,
    },

    {    // Mode 59 : 1920 x 1080 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
        672, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2576, 1120,                                                         // HTotal, VTotal,
        528, 37,
    },

    {   // Mode 60 : 1920 x 1080 x 60 Hz (Reduced Blanking)
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
        666, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2080, 1111,                                                         // HTotal, VTotal,
        112, 29,
    },

    {   // Mode 61 : 720 x 480i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        720, 240,                                                           // InputWidth, InputHeight,
        157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        858, 262,                                                           // HTotal, VTotal,
        119, 18,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 62 : 720 x 576i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        720, 288,                                                           // InputWidth, InputHeight,
        156, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        864, 312,                                                           // HTotal, VTotal,

        132, 21,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 63 : 720 x 576p x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        720, 576,                                                           // InputWidth, InputHeight,
        312, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        864, 625,                                                           // HTotal, VTotal,
        132, 44,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 64 : 1920 x 1080i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1920, 540,                                                          // InputWidth, InputHeight,
        281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2640, 562,                                                          // HTotal, VTotal,
        192, 20,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 65 : 1280 x 720p x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VP,                                      // Polarity Flags,
        1280, 720,                                                          // InputWidth, InputHeight,
        375, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1980, 750,                                                          // HTotal, VTotal,
        318, 25,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 66 : 1440 x 576i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1440, 288,                                                          // InputWidth, InputHeight,
        156, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1728, 625,                                                          // HTotal, VTotal,
        264, 21,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 67 : 1440 x 576p x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1440, 576,                                                          // InputWidth, InputHeight,
        313, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1728, 625,                                                          // HTotal, VTotal,
        264, 44,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 68 : 1920 x 1080 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
        846, 749,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2608, 1130,                                                         // HTotal, VTotal,
        552, 47,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 69 : 640 x 480 x 50 Hz
        0 | _SYNC_HN_VN,                                                    // Polarity Flags,
        640, 480,                                                           // InputWidth, InputHeight,
        246, 496,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        800, 497,                                                           // IHTotal, IVTotal,
        144, 14,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 70 : 848 x 480 x 70 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        848, 480,                                                           // InputWidth, InputHeight,
        350, 700,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1072,500,                                                           // IHTotal, IVTotal,
        190, 19,                                                            // IHStartPos, IVStartPos,
    },

    {    // Mode 71 : 848 x 480 x 72 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        848, 480,                                                           // InputWidth, InputHeight,
        361, 720,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1088, 501,                                                          // IHTotal, IVTotal,
        208, 20,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 72 : 848 x 480 x 75 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        848,480,                                                            // InputWidth, InputHeight,
        377, 748,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1088,504,                                                           // IHTotal, IVTotal,
        200, 21,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 73 : 848 x 480 x 60 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        848, 480,                                                           // InputWidth, InputHeight,
        310, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1088, 517,                                                          // IHTotal, IVTotal,
        224, 31,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 74 : 1280 x 720p x 60 Hz (720p60)
        0 | _SYNC_HN_VN,                                      // Polarity Flags,
        1280, 720,                                                          // InputWidth, InputHeight,
        450, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1650, 750,                                                          // IHTotal, IVTotal,
        260, 25,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 75 : 1024 x 768 x 60 Hz _MAC
        0 | _SYNC_HN_VN | _SYNC_HP_VP,                                      // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        483, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1320, 813,                                                          // IHTotal, IVTotal,
        218, 6,                                                             // IHStartPos, IVStartPos,
    },

    {   // Mode 76 : 1280 x 800 x 60 Hz (RB)
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1280,  800,                                                         // InputWidth, InputHeight,
        493, 599,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1440,  823,                                                         // IHTotal, IVTotal,
        112, 20,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 77 : 1360 x 768 x 60 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        1360, 768,                                                          // InputWidth, InputHeight,
        477, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1792, 795,                                                          // IHTotal, IVTotal,
        368, 24,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 78 : 1366 x 768 x 60 Hz (1080i60)
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        1366, 768,                                                          // InputWidth, InputHeight,
        477, 578,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1792,  798,                                                         // IHTotal, IVTotal,
        356, 27,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 79 : 1024 x 768 x 75 Hz _MAC
        0 | _SYNC_HN_VN,                                                    // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        601, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1328, 804,                                                          // IHTotal, IVTotal,
        272, 32,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 80 : 1280 x 800 x 75 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1280, 800,                                                          // InputWidth, InputHeight,
        627, 749,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1696, 838,                                                          // IHTotal, IVTotal,
        336, 35,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 81 : 1280 x 800 x 85 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1280, 800,                                                          // InputWidth, InputHeight,
        715, 848,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1712, 843,                                                          // IHTotal, IVTotal,
        352, 40,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 82 : 1440 x 900 x 85 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1440, 900,                                                          // InputWidth, InputHeight,
        804, 848,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1952, 948,                                                          // IHTotal, IVTotal,
        408, 45,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 83 : 1680 x 1050 x 85 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1680, 1050,                                                         // InputWidth, InputHeight,
        938, 849,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        2288, 1105,                                                         // IHTotal, IVTotal,
        480, 52,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 84 : 1920 x 1080p x 50 Hz (1080p50)
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP,                        // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
        563, 500,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        2640, 1125,                                                         // IHTotal, IVTotal,
        192, 41,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 85 : 1792 x 1344 x 60 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1792, 1344,                                                         // InputWidth, InputHeight,
        836, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        2448, 1394,                                                         // IHTotal, IVTotal,
        528, 49,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 86 : 1856 x 1392 x 60 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1856, 1392,                                                         // InputWidth, InputHeight,
        863, 599,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        2528, 1439,                                                         // IHTotal, IVTotal,
        576, 46,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 87 : 1280 x 768 x 60 Hz (Reduced Blanking)

        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1280, 768,                                                          // InputWidth, InputHeight,
        474, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1440, 790,                                                          // HTotal, VTotal,
        112, 18,                                                            // HStartPos, VStartPos,
    },
};
*/
ModeTableType code tINPUTMODE_PRESET_TABLE[_MAX_PRESET_MODE] =
{
    //--------------------------------------------------
    // Preset Modes
    //--------------------------------------------------

    {   // Mode 0 : 640 x 350 x 70 Hz
        0 | _SYNC_HP_VN ,                                                   // Polarity Flags,
        640, 350,                                                           // InputWidth, InputHeight,
        315, 700,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        800, 449,                                                           // IHTotal, IVTotal,
        144, 61,                                                             // IHStartPos, IVStartPos,
    },

    {   // Mode 1 : 640 x 350 x 70 Hz_QD
        0 | _SYNC_HN_VN ,                                                   // Polarity Flags,
        640, 350,                                                           // InputWidth, InputHeight,
        315, 700,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        800, 449,                                                           // IHTotal, IVTotal,
        144, 67,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 2 : 640 x 400 x 56 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VP,                                       // Polarity Flags,
        640, 400,                                                           // InputWidth, InputHeight,
        248, 564,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        848, 440,                                                           // IHTotal, IVTotal,
        145, 32,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 3 : 640 x 400 x 60 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        640, 400,                                                           // InputWidth, InputHeight,
        315, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        800, 440,                                                           // IHTotal, IVTotal,
        144, 42,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 4 : 720 x 400 x 70 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        720, 400,                                                           // InputWidth, InputHeight,
        315, 700,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        900, 449,                                                           // IHTotal, IVTotal,
        166,45,                                                             // IHStartPos, IVStartPos,
    },

    {   // Mode 5 : 640 x 400 x 70 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        640, 400,                                                           // InputWidth, InputHeight,
        315, 700,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        800, 449,                                                           // IHTotal, IVTotal,
        145, 36,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 6 : 720 x 400 x 85 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        720, 400,                                                           // InputWidth, InputHeight,
        380, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        936, 446,                                                           // IHTotal, IVTotal,
        181, 44,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 7 : 640 x 400 x 85 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        640, 400,                                                           // InputWidth, InputHeight,
        380, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE , _VFREQ_TOLERANCE,                                // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        832, 446,                                                           // IHTotal, IVTotal,
        160, 44,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 8 : 640 x 480 x 50 Hz
        0 | _SYNC_HN_VN,                                                    // Polarity Flags,
        640, 480,                                                           // InputWidth, InputHeight,
        246, 496,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        800, 497,                                                           // IHTotal, IVTotal,
        144, 14,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 9 : 640 x 480 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP,
        640, 480,                                                           // InputWidth, InputHeight,
        315, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        800, 525,                                                           // IHTotal, IVTotal,
        147, 34,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 10 : 640 x 480 x 66 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP,                        // Polarity Flags,
        640, 480,                                                           // InputWidth, InputHeight,
        350, 667,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        864, 525,                                                           // HTotal, VTotal,
        160, 41,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 11 : 640 x 480 x 72 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP,
        640, 480,                                                           // InputWidth, InputHeight,
        378, 728,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        832, 520,                                                           // HTotal, VTotal,
        171, 30,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 12 : 640 x 480 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP,                                       // Polarity Flags,
        640, 480,                                                           // InputWidth, InputHeight,
        375, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        840, 500,                                                           // IHTotal, IVTotal,
        187, 18,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 13 : 640 x 480 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        640, 480,                                                           // InputWidth, InputHeight,
        433, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        832, 510,                                                           // IHTotal, IVTotal,
        137, 27,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 14 : 720 x 480 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VP | _SYNC_HN_VP | _SYNC_HP_VN,          // Polarity Flags,
        720, 480,                                                           // InputWidth, InputHeight,
        298, 599,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        896, 497,                                                           // IHTotal, IVTotal,
        160, 16,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 15 : 720 x 480 x 60 Hz GTF
        0 | _SYNC_HN_VN,                                                    // Polarity Flags,
        720, 480,                                                           // InputWidth, InputHeight,
        315, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        856, 525,                                                           // IHTotal, IVTotal,
        124, 36,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 16 : 720 x 576 x 60 Hz
        0 | _SYNC_HP_VN | _SYNC_HP_VP | _SYNC_HN_VN | _SYNC_HN_VP,           // Polarity Flags,
        720, 576,                                                           // InputWidth, InputHeight,
        358, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        912, 600,                                                           // IHTotal, IVTotal,
        169, 22,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 17 : 720 x 576 x 75 Hz
        0 | _SYNC_HP_VN | _SYNC_HN_VN | _SYNC_HN_VP,                       // Polarity Flags,
        720, 576,                                                           // InputWidth, InputHeight,
        455, 756,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        944, 602,                                                           // IHTotal, IVTotal,
        142, 22,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 18 : 800 x 600 x 56 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        800, 600,                                                           // InputWidth, InputHeight,
        351, 562,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1024, 625,                                                          // HTotal, VTotal,
        204,  23,                                                           // IHStartPos, IVStartPos,
    },

    {   // Mode 19 : 800 x 600 x 60 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        800, 600,                                                           // InputWidth, InputHeight,
        378, 603,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1056, 628,                                                          // IHTotal, IVTotal,
        220,  26,                                                           // IHStartPos, IVStartPos,
    },

    {   // Mode 20: 800 x 600 x 70Hz
         0 | _SYNC_HP_VP | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HN_VN,          // Polarity Flags,
         800,600,                                                           // InputWidth, InputHeight,
         440, 700,                                                          // HFreq in kHz, VFreq in Hz,
         _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                // HFreqTolerance in kHz, VFreqTolerance in Hz,
         1040, 624,                                                         // HTotal, VTotal,
         190, 29,                                                           // HStartPos, VStartPos,
    },

    {   // Mode 21 : 800 x 600 x 72 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        800, 600,                                                           // InputWidth, InputHeight,
        481, 722,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1040, 666,                                                          // HTotal, VTotal,
        188,  28,                                                           // IHStartPos, IVStartPos,
    },

    {   // Mode 22 : 800 x 600 x 75 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        800, 600,                                                           // InputWidth, InputHeight,
        468, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1056, 625,                                                          // IHTotal, IVTotal,
        244,  23,                                                           // IHStartPos, IVStartPos,
    },

    {   // Mode 23 : 800 x 600 x 85 Hz
        0 | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        800, 600,                                                           // InputWidth, InputHeight,
        536, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1048, 631,                                                          // IHTotal, IVTotal,
        217, 29,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 24 : 832 x 624 x 75 Hz
        0 | _SYNC_HN_VN,                                                    // Polarity Flags,
        832, 624,                                                           // InputWidth, InputHeight,
        497, 745,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1152, 667,                                                          // IHTotal, IVTotal,
        288, 41,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 25 : 848 x 480 x 60 Hz
        0 | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        848, 480,                                                           // InputWidth, InputHeight,
        310, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1088, 517,                                                          // IHTotal, IVTotal,
        224, 31,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 26 : 848 x 480 x 70 Hz
        0 | _SYNC_HP_VP | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HN_VN,          // Polarity Flags,
        848, 480,                                                           // InputWidth, InputHeight,
        350, 700,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1072, 500,                                                          // IHTotal, IVTotal,
        200, 18,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 27 : 848 x 480 x 72 Hz
        0 | _SYNC_HP_VP | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HN_VN,          // Polarity Flags,
        848, 480,                                                           // InputWidth, InputHeight,
        360, 720,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1090, 501,                                                          // IHTotal, IVTotal,
        207, 20,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 28 : 848 x 480 x 75 Hz
        0 | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        848, 480,                                                           // InputWidth, InputHeight,
        376, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1090, 502,                                                          // IHTotal, IVTotal,
        200, 21,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 29 : 1024 x 768 x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        396, 500,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1312, 793,                                                          // IHTotal, IVTotal,
        248, 25,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 30 : 1024 x 768 x 60 Hz
        0 | _SYNC_HN_VN,                                                    // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        483, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1344, 806,                                                          // IHTotal, IVTotal,
        296, 34,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 31 : 1024 x 768 x 60 Hz MAC
        0 | _SYNC_HN_VN | _SYNC_HP_VP,                                      // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        483, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1320, 813,                                                          // IHTotal, IVTotal,
         218, 6,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 32 : 1024 x 768 x 66 Hz
        0 | _SYNC_HN_VN,                                                    // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        540, 661,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1328, 816,                                                          // IHTotal, IVTotal,
        288, 39,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 33 : 1024 x 768 x 70 Hz
        0 | _SYNC_HN_VN,                                                    // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        565, 700,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1328, 806,                                                          // HTotal, VTotal,
        280, 34,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 34 : 1024 x 768 x 72 Hz
        0 | _SYNC_HP_VN | _SYNC_HP_VP | _SYNC_HN_VP | _SYNC_HN_VN,           // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        577, 720,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1360, 801,                                                          // IHTotal, IVTotal,
        280, 31,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 35 : 1024 x 768 x 75 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        600, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1312, 803,                                                          // IHTotal, IVTotal,
        272, 30,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 36 : 1024 x 768 x 75 Hz/MAC
        0 | _SYNC_HN_VN,                                                    // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        601, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1328, 804,                                                          // IHTotal, IVTotal,
        272, 32,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 37 : 1024 x 768 x 85 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        1024, 768,                                                          // InputWidth, InputHeight,
        682, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1376, 808,                                                          // IHTotal, IVTotal,
        304, 38,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 38 : 1152 x 864 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                         // Polarity Flags,
        1152, 864,                                                          // InputWidth, InputHeight,
        537, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1512, 894,                                                          // HTotal, VTotal,
        300, 30,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 39 : 1152 x 864 x 70 Hz
        0 | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1152, 864,                                                          // InputWidth, InputHeight,
        642, 702,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1480, 912,                                                          // HTotal, VTotal,
        296, 46,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 40 : 1152 x 864 x 75 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        1152, 864,                                                          // InputWidth, InputHeight,
        675, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1600, 900,                                                          // IHTotal, IVTotal,
        384, 34,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 41 : 1152 x 864 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HP_VP,                        // Polarity Flags,
        1152, 864,                                                          // InputWidth, InputHeight,
         770, 850,                                                          // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1576, 907,                                                          // HTotal, VTotal,
         360, 42,                                                           // HStartPos, VStartPos,
    },

    {   // Mode 42 : 1152 x 870 x 75 Hz
        0 | _SYNC_HN_VN,                                                    // Polarity Flags,
        1152, 870,                                                          // InputWidth, InputHeight,
         687, 750,                                                          // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1456, 915,                                                          // HTotal, VTotal,
         272, 41,                                                           // HStartPos, VStartPos,
    },

    {   // Mode 43 : 1152 x 900 x 66 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        1152, 900,                                                          // InputWidth, InputHeight,
         618, 660,                                                          // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1504, 937,                                                          // HTotal, VTotal,
         323, 35,                                                           // HStartPos, VStartPos,
    },

    {   // Mode 44 : 1152 x 900 x 66 Hz S
        0 | _SYNC_HP_VN | _SYNC_HN_VN,                                      // Polarity Flags,
        1152, 900,                                                          // InputWidth, InputHeight,
         618, 660,                                                          // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1504, 937,                                                          // HTotal, VTotal,
         320, 34,                                                           // HStartPos, VStartPos,
    },

    {   // Mode 45 : 1280 x 720 x 60 Hz

        // V013 VGA Patch Note (23) Modify 20100513 Start
        // Patch Reason : For Video Mode Clamp Position Setting Flow
        /*
        0 | _SYNC_HP_VP | _SYNC_HN_VP,                                      // Polarity Flags,
        */
        0 | _SYNC_HP_VP | _SYNC_HN_VP | _VIDEO_MODE_GROUP2,                 // Polarity Flags,
        // V013 VGA Patch Note (23) Modify 20100513 End

        1280, 720,                                                          // InputWidth, InputHeight,
        450, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1650, 750,                                                          // HTotal, VTotal,
        303,   23,                                                          // HStartPos, VStartPos,
    },

    {   // Mode 46 : 1280 x 720 x 70 Hz
        0 | _SYNC_HP_VP | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP,          // Polarity Flags,
        1280, 720,                                                          // InputWidth, InputHeight,
        525, 700,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1683, 750,                                                          // HTotal, VTotal,
        339, 29,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 47 : 1280 x 720 x 72 Hz
        0 | _SYNC_HP_VP | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP,          // Polarity Flags,
        1280, 720,                                                          // InputWidth, InputHeight,
        540, 720,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1700, 751,                                                          // HTotal, VTotal,
        344, 30,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 48 : 1280 x 720 x 75 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 720,                                                          // InputWidth, InputHeight,
        564, 750,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1696, 755,                                                          // HTotal, VTotal,
        336, 32,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 49 : 1280 x 768 x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 768,                                                          // InputWidth, InputHeight,
        396, 499,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1648, 793,                                                          // IHTotal, IVTotal,
        312, 21,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 50 : 1280 x 768 x 60 Hz
        0 | _SYNC_HN_VP | _SYNC_HP_VN,                                      // Polarity Flags,
        1280, 768,                                                          // InputWidth, InputHeight,
        478, 599,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1664, 798,                                                          // HTotal, VTotal,
        320, 26,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 51 : 1280 x 768 x 60 Hz (Reduced Blanking)
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1280, 768,                                                          // InputWidth, InputHeight,
        474, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1440, 790,                                                          // HTotal, VTotal,
        112, 18,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 52 : 1280 x 768 x 70 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1280, 768,                                                          // InputWidth, InputHeight,
        560, 700,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1692, 799,                                                          // HTotal, VTotal,
        336, 31,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 53 : 1280 x 768 x 75 Hz
        0 | _SYNC_HN_VP | _SYNC_HP_VN | _SYNC_HP_VP,                        // Polarity Flags,
        1280, 768,                                                          // InputWidth, InputHeight,
        603, 749,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1696, 805,                                                          // HTotal, VTotal,
        336, 33,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 54 : 1280 x 768 x 85 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1280, 768,                                                          // InputWidth, InputHeight,
         686, 848,                                                          // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1712, 809,                                                          // HTotal, VTotal,
         351,  37,                                                          // HStartPos, VStartPos,
    },

    {   // Mode 55 : 1280 x 800 x 60 Hz
        0 | _SYNC_HP_VP | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HN_VN,          // Polarity Flags,
        1280, 800,                                                          // InputWidth, InputHeight,
        497, 598,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1680,831,                                                           // HTotal, VTotal,
        328,26,                                                             // HStartPos, VStartPos,
    },

   {   //Mode 56 : 1280 x 800 x 60 Hz R
        0 | _SYNC_HP_VP | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HN_VN,
        1280, 800,                                                          // InputWidth, InputHeight,
        491,590,                                                            // HFreq in kHz, VFreq in Hz, Janson 20080703
        _HFREQ_TOLERANCE+3, _VFREQ_TOLERANCE+5,                             // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1440, 823,                                                          // HTotal, VTotal,
        112, 20,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 57 : 1280 x 800 x 70 Hz
        0 | _SYNC_HP_VP | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HN_VN,          // Polarity Flags,
        1280, 800,                                                          // InputWidth, InputHeight,
        584, 699,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1696, 833,                                                          // HTotal, VTotal,
        344, 32,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 58 : 1280 x 800 x 72 Hz
        0 | _SYNC_HP_VP | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HN_VN,          // Polarity Flags,
        1280, 800,                                                          // InputWidth, InputHeight,
        602, 719,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1712, 834,                                                          // HTotal, VTotal,
        352, 33,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 59 : 1280 x 800 x 75 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1280, 800,                                                          // InputWidth, InputHeight,
        627, 748,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1696, 838,                                                          // HTotal, VTotal,
        328, 34,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 60 : 1280 x 960 x 60 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        1280, 960,                                                          // InputWidth, InputHeight,
        600, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1800, 1000,                                                         // IHTotal, IVTotal,
        424, 38,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 61 : 1280 x 960 x 70 Hz
        0 | _SYNC_HP_VP | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HN_VN,           // Polarity Flags,
        1280, 960,                                                          // InputWidth, InputHeight,
        699, 700,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1727, 999,                                                          // HTotal, VTotal,
        359, 38,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 62 : 1280 x 960 x 72 Hz
        0 | _SYNC_HP_VP | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HN_VN,           // Polarity Flags,
        1280, 960,                                                          // InputWidth, InputHeight,
        699, 720,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1700, 990,                                                          // HTotal, VTotal,
        359, 40,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 63 : 1280 x 960 x 75 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        1280, 960,                                                          // InputWidth, InputHeight,
        746, 744,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1728, 1002,                                                         // HTotal, VTotal,
        360, 38,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 64 : 1280 x 960 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 960,                                                          // InputWidth, InputHeight,
        860, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1728, 1011,                                                         // IHTotal, IVTotal,
        384, 50,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 65 : 1280 x 1024 x 60 Hz
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        1280, 1024,                                                         // InputWidth, InputHeight,
        640, 600,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1688, 1066,                                                         // IHTotal, IVTotal,
        360,40,                                                             // IHStartPos, IVStartPos,
    },

    {   // Mode 66 : 1280 x 1024 x 70 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1280, 1024,                                                         // InputWidth, InputHeight,
        746, 700,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1696, 1072,                                                         // HTotal, VTotal,
        384,  33,                                                           // HStartPos, VStartPos,
    },

    {   // Mode 67 : 1280 x 1024 x 70_1 Hz
        0 | _SYNC_HN_VN,                                                    // Polarity Flags,
        1280, 1024,                                                         // InputWidth, InputHeight,
        746, 700,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1678, 1064,                                                         // HTotal, VTotal,
        328,    26,                                                         // HStartPos, VStartPos,
    },

    {   // Mode 68 : 1280 x 1024 x 72 Hz
        0 | _SYNC_HP_VP | _SYNC_HN_VP | _SYNC_HP_VN | _SYNC_HN_VP,              // Polarity Flags,
        1280, 1024,                                                         // InputWidth, InputHeight,
        770,720,                                                            // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1728,1082,                                                          // HTotal, VTotal,
        360,   44,                                                          // HStartPos, VStartPos,
    },

    {   // Mode 69 : 1280 x 1024 x 75 Hz
        0 | _SYNC_HP_VP | _SYNC_HP_VN,                                       // Polarity Flags,
        1280, 1024,                                                         // InputWidth, InputHeight,
        800, 750,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1688,1066,                                                          // IHTotal, IVTotal,
        394, 40,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 70 : 1280 x 1024 x 85 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 1024,                                                         // InputWidth, InputHeight,
        911, 850,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1728, 1072,                                                         // IHTotal, IVTotal,
        384, 47,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 71 : 1360 x 768 x 60 Hz

    #if((_PANEL_DH_WIDTH == 1366) && (_PANEL_DV_HEIGHT == 768))
        0 | _SYNC_HN_VP | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HP_VP,          // Polarity Flags,
        1366, 768,                                                          // InputWidth, InputHeight,
        477, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1792, 795,                                                          // HTotal, VTotal,
        368, 23,                                                            // HStartPos, VStartPos,

    #else
        0 | _SYNC_HP_VP | _SYNC_HN_VP,                                      // Polarity Flags,
        1360, 768,                                                          // InputWidth, InputHeight,
        477, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1792, 795,                                                          // HTotal, VTotal,
        368, 24,                                                            // HStartPos, VStartPos,

    #endif // End of #if((_PANEL_DH_WIDTH == 1366) && (_PANEL_DV_HEIGHT == 768))
    },

    {   // Mode 72 : 1366 x 768 x 60 Hz
        0 | _SYNC_HP_VP ,                                                   // Polarity Flags,
        1366, 768,                                                          // InputWidth, InputHeight,
        477, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1792, 798,                                                          // HTotal, VTotal,
        356, 27,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 73 : 1440 x 900 x 60 Hz
        0 | _SYNC_HN_VP | _SYNC_HN_VN | _SYNC_HP_VP,                        // Polarity Flags,
        1440, 900,                                                          // InputWidth, InputHeight,
        559, 598,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1904, 934,                                                          // HTotal, VTotal,
        385, 30,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 74 : 1440 x 900 x 60 Hz (Reduced Blanking)
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1440, 900,                                                          // InputWidth, InputHeight,
        555, 599,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1600, 926,                                                          // HTotal, VTotal,
        112, 22,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 75 : 1440 x 900 x 75 Hz
        0 | _SYNC_HN_VP | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HP_VP,          // Polarity Flags,
        1440, 900,                                                          // InputWidth, InputHeight,
        706, 745,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE+4,                               // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1936, 942,                                                          // HTotal, VTotal,
        398, 38,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 76 : 1600 x 1200 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VP,                                      // Polarity Flags,
        1600, 1200,                                                         // InputWidth, InputHeight,
        750, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2160, 1250,                                                         // HTotal, VTotal,
        496, 49,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 77 : 1600 x 1200 x 60 Hz RB
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1600, 1200,                                                         // InputWidth, InputHeight,
        740,  599,                                                          // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1760, 1235,                                                         // HTotal, VTotal,
        112,31,                                                             // HStartPos, VStartPos,
    },

    {   // Mode 78 : 1600 x 1200 x 65 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1600, 1200,                                                         // InputWidth, InputHeight,
        812, 650,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2160, 1250,                                                         // HTotal, VTotal,
        496, 49,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 79 : 1600 x 1200 x 70 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1600, 1200,                                                         // InputWidth, InputHeight,
        875, 700,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2160, 1250,                                                         // HTotal, VTotal,
        496, 49,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 80 : 1680 x 1050 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1680, 1050,                                                         // InputWidth, InputHeight,
        653, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2240, 1089,                                                         // HTotal, VTotal,
        456, 35,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 81 : 1680 x 1050 x 60 Hz (Reduced Blanking)
        0 | _SYNC_HP_VN | _SYNC_HP_VP,                                      // Polarity Flags,
        1680, 1050,                                                         // InputWidth, InputHeight,
        647, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1840, 1080,                                                         // HTotal, VTotal,
        112, 26,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 82 : 1680 x 1050 x 75 Hz
        0 | _SYNC_HN_VP,                                                     // Polarity Flags,
        1680, 1050,                                                         // InputWidth, InputHeight,
        828, 753,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2272, 1099,                                                         // HTotal, VTotal,
        472, 46,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 83 : 1920 x 1200 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP,                                      // Polarity Flags,
        1920, 1200,                                                         // InputWidth, InputHeight,
        746, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2592, 1245,                                                         // HTotal, VTotal,
        536, 42,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 84 : 1920 x 1200 x 60 Hz (Reduced Blanking)
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1920, 1200,                                                         // InputWidth, InputHeight,
        740, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2080, 1235,                                                         // HTotal, VTotal,
        112, 32,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 85 : 1920 x 1440 x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1920, 1440,                                                         // InputWidth, InputHeight,
        900, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2600, 1500,                                                         // HTotal, VTotal,
        552, 59,                                                            // HStartPos, VStartPos,
    },

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    {   // Mode 86 : 720 x 480i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        720, 240,                                                           // InputWidth, InputHeight,
        157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        858, 262,                                                           // HTotal, VTotal,
        123,  16,                                                           // HStartPos, VStartPos,
    },

    {   // Mode 87 : 720 x 576i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        720, 288,                                                           // InputWidth, InputHeight,
        157, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        864, 312,                                                           // HTotal, VTotal,
        136,  20,                                                           // HStartPos, VStartPos,
    },
    */
    // V013 VGA Patch Note (24) Modify 20100514 End

    {   // Mode 86 : 720 x 576p x 50 Hz

        // V013 VGA Patch Note (23) Modify 20100513 Start
        // Patch Reason : For Video Mode Clamp Position Setting Flow
        /*
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        */
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP | _VIDEO_MODE_GROUP1,   // Polarity Flags,
        // V013 VGA Patch Note (23) Modify 20100513 End

        720, 576,                                                           // InputWidth, InputHeight,
        312, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        864, 625,                                                           // HTotal, VTotal,
        135,  42,                                                           // HStartPos, VStartPos,
    },

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    {   // Mode 89 : 1440 x 480i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1440, 240,                                                          // InputWidth, InputHeight,
        157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1716, 525,                                                          // HTotal, VTotal,
        276, 59,                                                            // HStartPos, VStartPos,
    },
    */
    {   // Mode 87 : 1440 x 480i x 60 Hz

        // V013 VGA Patch Note (23) Modify 20100513 Start
        // Patch Reason : For Video Mode Clamp Position Setting Flow
        /*
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        */
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP | _VIDEO_MODE_GROUP2,   // Polarity Flags,
        // V013 VGA Patch Note (23) Modify 20100513 End

        1440, 240,                                                          // InputWidth, InputHeight,
        157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1716, 262,                                                          // HTotal, VTotal,
        238, 20,                                                            // HStartPos, VStartPos,
    },
    // V013 VGA Patch Note (24) Modify 20100514 End

    {   // Mode 88 : 1920 x 1080i x 50 Hz

        // V013 VGA Patch Note (23) Modify 20100513 Start
        // Patch Reason : For Video Mode Clamp Position Setting Flow
        /*
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP | _SYNC_HP_VN,          // Polarity Flags,
        */
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP | _SYNC_HP_VN | _VIDEO_MODE_GROUP2, // Polarity Flags,
        // V013 VGA Patch Note (23) Modify 20100513 End

        1920, 540,                                                          // InputWidth, InputHeight,
        281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2640, 562,                                                          // HTotal, VTotal,
        242,   21,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 89 : 1920 x 1080i x 60 Hz

        // V013 VGA Patch Note (23) Modify 20100513 Start
        // Patch Reason : For Video Mode Clamp Position Setting Flow
        /*
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP | _SYNC_HP_VN,           // Polarity Flags,
        */
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP | _SYNC_HP_VN | _VIDEO_MODE_GROUP2, // Polarity Flags,
        // V013 VGA Patch Note (23) Modify 20100513 End

        1920, 540,                                                          // InputWidth, InputHeight,
        337, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2200, 562,                                                          // HTotal, VTotal,
        242,   21,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 90 : 1920 x 1080p x 50 Hz

        // V013 VGA Patch Note (23) Modify 20100513 Start
        // Patch Reason : For Video Mode Clamp Position Setting Flow
        /*
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        */
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP | _VIDEO_MODE_GROUP2,   // Polarity Flags,
        // V013 VGA Patch Note (23) Modify 20100513 End

        1920, 1080,                                                         // InputWidth, InputHeight,
        562, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2640, 1125,                                                         // HTotal, VTotal,
        239,   39,                                                          // HStartPos, VStartPos,
    },

    {   // Mode 91 : 1920 x 1080 x 60 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
        672, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2576, 1120,                                                         // HTotal, VTotal,
        528, 37,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 92 : 1152 x 900 x 76 Hz
        0 | _SYNC_HN_VP | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HP_VP,          // Polarity Flags,
        1152, 900,                                                          // InputWidth, InputHeight,
        717, 760,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1472, 943,                                                          // HTotal, VTotal,
        304, 40,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 93 : 1600 x 1000 x 60 Hz
        0 | _SYNC_HN_VP ,                                                   // Polarity Flags,
        1600, 1000,                                                         // InputWidth, InputHeight,
        622, 599,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2128, 1038,                                                         // HTotal, VTotal,
        432, 35,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 94 : 1600 x 1000 x 60_RB Hz
        0 | _SYNC_HN_VP | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HP_VP,          // Polarity Flags,
        1600, 1000,                                                         // InputWidth, InputHeight,
        616, 599,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1760, 1029,                                                         // HTotal, VTotal,
        112, 26,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 95 : 1600 x 1000 x 75 Hz
        0 | _SYNC_HN_VP | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HP_VP,          // Polarity Flags,
        1600, 1000,                                                         // InputWidth, InputHeight,
        784, 748,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2160, 1047,                                                         // HTotal, VTotal,
        448, 44,                                                            // HStartPos, VStartPos,
    },

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    {   // Mode 98 : 1440 x 576i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1440, 288,                                                          // InputWidth, InputHeight,
        157, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        864, 312,                                                           // HTotal, VTotal,
        132, 22,                                                            // HStartPos, VStartPos,
    },
    */
    {   // Mode 96 : 1440 x 576i x 50 Hz

        // V013 VGA Patch Note (23) Modify 20100513 Start
        // Patch Reason : For Video Mode Clamp Position Setting Flow
        /*
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        */
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP | _VIDEO_MODE_GROUP2,   // Polarity Flags,
        // V013 VGA Patch Note (23) Modify 20100513 End

        1440, 288,                                                          // InputWidth, InputHeight,
        157, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1728, 312,                                                           // HTotal, VTotal,
        264, 24,                                                            // HStartPos, VStartPos,
    },
    // V013 VGA Patch Note (24) Modify 20100514 End

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    {   // Mode 97 : _MODE_1920x1080_60HZ_XBOX
        0 |_SYNC_HP_VN,                                                     // Polarity Flags,
        1680, 1080,                                                         // InputWidth, InputHeight,
        669, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1840, 1109,                                                         // HTotal, VTotal,
        112, 27,                                                            // HStartPos, VStartPos,
    },
    */
    {   // Mode 97 : _MODE_1920x1080_60HZ_XBOX
        0 | _SYNC_HP_VN,                                                     // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
        675, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2200, 1125,                                                         // HTotal, VTotal,
        192, 41,                                                            // HStartPos, VStartPos,
    },
    // V013 VGA Patch Note (24) Modify 20100514 End

    {   // Mode 98 : 1920 x 1080 x 60_RBHz
        0 | _SYNC_HP_VN | _SYNC_HP_VP,                                        // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
        666, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2080, 1111,                                                         // HTotal, VTotal,
        112, 28,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 99 : 1176 x 664 x 60Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1176, 664,                                                          // InputWidth, InputHeight,
        417, 604,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1512, 690,                                                          // HTotal, VTotal,
        288, 23,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 100 : 1176 x 664 x 72Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1176, 664,                                                          // InputWidth, InputHeight,
        500, 725,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE+15, _VFREQ_TOLERANCE+20,                           // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1512, 690,                                                          // HTotal, VTotal,
        288, 23,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 101 : 640x 500 x 58Hz NN
        0 | _SYNC_HN_VN,                                                    // Polarity Flags,
        640, 500,                                                           // InputWidth, InputHeight,
        310, 577,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        808, 541,                                                           // HTotal, VTotal,
        148,12,                                                             // HStartPos, VStartPos,
    },

    {   // Mode 102 : 848 x 480 x 60 Hz_PP
        0 | _SYNC_HN_VP ,                                                  // Polarity Flags,
        848, 480,                                                           // InputWidth, InputHeight,
        298, 597,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1056, 500,                                                          // IHTotal, IVTotal,
        184, 17,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 103 : 1600 x 900 x 60 Hz_CVR (QD CVR 1659H)
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1600, 900,                                                          // InputWidth, InputHeight,
        555, 599,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1760, 926,                                                          // HTotal, VTotal,
        115, 22,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 104 : 1680 x 1050 x 75 Hz(Reduce Blanking)
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        1680, 1050,                                                         // InputWidth, InputHeight,
        815, 749,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1840, 1088,                                                         // HTotal, VTotal,
        112, 35,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 105 : 1280 x 1024 x 76 Hz
        0 | _SYNC_HN_VN ,                                                   // Polarity Flags,
        1280, 1024,                                                         // InputWidth, InputHeight,
        811, 761,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        1664,1066,                                                          // IHTotal, IVTotal,
        352, 40,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 106 : 640 x 500 x 58 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP,
        640, 500,                                                           // InputWidth, InputHeight,
        315, 580,                                                           // IHFreq in kHz, IVFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // IHFreqTolerance in kHz, IVFreqTolerance in Hz,
        808, 537,                                                           // IHTotal, IVTotal,
        144, 13,                                                            // IHStartPos, IVStartPos,
    },

    {   // Mode 107 : 1600 x 900 x 60 Hz (Reduce Blanking )(OD CVR 1660H)
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        1600, 900,                                                          // InputWidth, InputHeight,
        600, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1800, 1000,                                                         // HTotal, VTotal,
        176, 99,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 108 : 2048 x 1152 x 60 Hz (Reduce Blanking )(CVT2060H)
        0 | _SYNC_HP_VP | _SYNC_HP_VN,                                       // Polarity Flags,
        2048, 1152,                                                         // InputWidth, InputHeight,
        720, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2250, 1200,                                                         // HTotal, VTotal,
        176, 47,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 109 : 1280 x 720 x 60 Hz (CVT1260B)
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1280,  720,                                                         // InputWidth, InputHeight,
         448,  599,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1664,  748,                                                         // HTotal, VTotal,
         320,   24,                                                         // HStartPos, VStartPos,
    },

    {   // Mode 110 : 1920 x 1080 x 50 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
        556, 499,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2544, 1114,                                                         // HTotal, VTotal,
        512, 31,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 111 : 1920 x 1200 x 50 Hz (Reduce Blanking )
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1920, 1200,                                                         // InputWidth, InputHeight,
        614, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2080, 1229,                                                         // HTotal, VTotal,
        112, 26,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 112 : 2048 x 1152 x 60 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        2048, 1152,                                                         // InputWidth, InputHeight,
        716, 599,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2752, 1195,                                                         // HTotal, VTotal,
        568, 40,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 113 : 1920 x 1080 x 60_DMT Hz

        // V013 VGA Patch Note (23) Modify 20100513 Start
        // Patch Reason : For Video Mode Clamp Position Setting Flow
        /*
        0 | _SYNC_HP_VP,                                                    // Polarity Flags,
        */
        0 | _SYNC_HP_VP | _VIDEO_MODE_GROUP2,                               // Polarity Flags,
        // V013 VGA Patch Note (23) Modify 20100513 End

        1920, 1080,                                                         // InputWidth, InputHeight,
        675, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2200, 1125,                                                         // HTotal, VTotal,
        239,   39,                                                          // HStartPos, VStartPos,
    },

    {   // Mode 114 : 640 x 350 x 85 Hz
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        640, 350,                                                           // InputWidth, InputHeight,
        379, 851,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        832, 445,                                                           // HTotal, VTotal,
        160, 63,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 115 : 1920 x 1440 x 60 Hz (Reduced Blanking)
        0 | _SYNC_HP_VN,                                                    // Polarity Flags,
        1920, 1440,                                                         // InputWidth, InputHeight,
        888, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2080, 1481,                                                         // HTotal, VTotal,
        112, 38,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 116 : 2048 x 1152 x 60 Hz (Reduce Blanking )(CVR2060H)
        0 | _SYNC_HP_VN,                            // Polarity Flags,
        2048, 1152,                                                         // InputWidth, InputHeight,
        710, 599,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2208, 1185,                                                         // HTotal, VTotal,
        112, 30,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 117 : 1152 x 864 x 85 Hz A
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1152, 864,                                                          // InputWidth, InputHeight,
         770, 850,                                                          // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1552, 910,                                                          // HTotal, VTotal,
         320, 43,                                                           // HStartPos, VStartPos,
    },

    {   // Mode 118 : 1600 x 1280 x 60 Hz
        0 | _SYNC_HN_VP,                                                    // Polarity Flags,
        1600, 1280,                                                         // InputWidth, InputHeight,
         795, 599,                                                          // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2160, 1327,                                                         // HTotal, VTotal,
         448, 44,                                                           // HStartPos, VStartPos,
    },

    {   // Mode 119 : 720 x 480p x 60 Hz

        // V013 VGA Patch Note (23) Modify 20100513 Start
        // Patch Reason : For Video Mode Clamp Position Setting Flow
        /*
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        */
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP | _VIDEO_MODE_GROUP1, // Polarity Flags,
        // V013 VGA Patch Note (23) Modify 20100513 End

         720,  480,                                                         // InputWidth, InputHeight,
         315,  600,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
         858,  525,                                                         // HTotal, VTotal,
         127,   34,                                                         // HStartPos, VStartPos,
    },

    {   // Mode 120 : 1280 x 720p x 50 Hz

        // V013 VGA Patch Note (23) Modify 20100513 Start
        // Patch Reason : For Video Mode Clamp Position Setting Flow
        /*
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        */
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP | _VIDEO_MODE_GROUP2, // Polarity Flags,
        // V013 VGA Patch Note (23) Modify 20100513 End

        1280,  720,                                                         // InputWidth, InputHeight,
         375,  500,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1980,  750,                                                         // HTotal, VTotal,
         303,   23,                                                         // HStartPos, VStartPos,
    },

    {   // Mode 121 : 1600 x 1000 x 60 Hz _2
        0 | _SYNC_HN_VP ,                                                   // Polarity Flags,
        1600, 1000,                                                         // InputWidth, InputHeight,
        612, 585,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2160, 1047,                                                         // HTotal, VTotal,
        448, 34,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 122 : 1920 x 1080i x 50 Hz _2

        // V013 VGA Patch Note (23) Modify 20100513 Start
        // Patch Reason : For Video Mode Clamp Position Setting Flow
        /*
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP | _SYNC_HP_VN,          // Polarity Flags,
        */
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP | _SYNC_HP_VN | _VIDEO_MODE_GROUP2, // Polarity Flags,
        // V013 VGA Patch Note (23) Modify 20100513 End

        1920, 540,                                                          // InputWidth, InputHeight,
        313, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2304, 625,                                                          // HTotal, VTotal,
        352,  80,                                                            // HStartPos, VStartPos,
    },

    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    // _MODE_1600x900_60HZ is a non-RB mode, suggested by Y.C., which could solve
    // Graphic Card issue.
    {   // Mode 123 : 1600 x 900 x 60 Hz
        0 | _SYNC_HP_VN | _SYNC_HP_VP | _SYNC_HN_VN | _SYNC_HN_VP,           // Polarity Flags,
        1600, 900,                                                          // InputWidth, InputHeight,
        559, 599,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2112, 934,                                                          // HTotal, VTotal,
        424, 31,                                                            // HStartPos, VStartPos,
    },
    // V013 VGA Patch Note (24) Modify 20100514 End
};
// V012 Modify 20100324 End

#if(_DISP_INFO_BY_MODE == _ON)

DisplayTableType code tDISPLAY_PRESET_TABLE[_MAX_PRESET_MODE] =
{
    //--------------------------------------------------
    // Preset Modes
    //--------------------------------------------------
    {   // Mode 0 : 640 x 350 x 70 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 1 : 640 x 350 x 85 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 2 : 720 x 400 x 70 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 3 : 720 x 400 x 85 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 4 : 640 x 480 x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 5 : 640 x 480 x 66 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 6 : 640 x 480 x 72 Hz
        1688,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 7 : 640 x 480 x 75 Hz
        1688,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 8 : 640 x 480 x 85 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 9 : 800 x 600 x 56 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 10 : 800 x 600 x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 11 : 800 x 600 x 72 Hz
        1688,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 12 : 800 x 600 x 75 Hz
        1688,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 13 : 800 x 600 x 85 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 14 : 832 x 624 x 75 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 15 : 1024 x 768 x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 16 : 1024 x 768 x 70 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 17 : 1024 x 768 x 75 Hz
        1688,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 18 : 1024 x 768 x 85 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 19 : 1024 x 800 x 73 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 20 : 1024 x 800 x 85 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 21 : 1152 x 864 x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 22 : 1152 x 864 x 70 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 23 : 1152 x 864 x 75 Hz
        1688,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 24 : 1152 x 864 x 85 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 25 : 1152 x 870 x 75 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 26 : 1152 x 900 x 66 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 27 : 1152 x 900 x 76 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 28 : 1280 x 720 x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 29 : 1280 x 720 x 75 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 30 : 1280 x 768 x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 31 : 1280 x 768 x 70 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 32 : 1280 x 768 x 75 Hz
        1688,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 33 : 1280 x 960 x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 34 : 1280 x 960 x 75 Hz
        1688,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 35 : 1280 x 960 x 85 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 36 : 1280 x 1024 x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 37 : 1280 x 1024 x 70 Hz
        1688,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 38 : 1280 x 1024 x 75 Hz
        1688,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 39 : 1280 x 1024 x 85 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 40 : 1440 x 900 x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 41 : 1440 x 900 x 60 Hz (Reduced Blanking)
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 42 : 1440 x 900 x 75 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 43 : 1600 x 1200 x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 44 : 1600 x 1200 x 65 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 45 : 1600 x 1200 x 70 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 46 : 1600 x 1200 x 75 Hz
        1688,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 47 : 1600 x 1200 x 85 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 48 : 1680 x 1050 x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 49 : 1680 x 1050 x 60 Hz (Reduced Blanking)
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 50 : 1680 x 1050 x 75 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 51 : 1680 x 1050 x 75 Hz (Reduced Blanking)
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 52 : 1920 x 1200 x 60 Hz
        1512,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 53 : 1920 x 1200 x 60 Hz (Reduced Blanking)
        1512,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 54 : 1920 x 1200 x 75 Hz
        1512,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 55 : 1920 x 1440 x 60 Hz
        1688,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 56 : 1440 x 480i x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 57 : 1920 x 1080i x 60 Hz
        1408,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 58 : 1920 x 1080 x 60 Hz
        1512,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },

    {   // Mode 59 : 1920 x 1080 x 60 Hz (Reduced Blanking)
        1512,                                                               // DHTotal,
        1280, 1024,                                                         // DHWidth, DVHeight,
    },
};
#endif  // End of #if(_DHTOTAL_BY_MODE == _ON)

// V012 Modify 20100322 Start
// V012 Patch Note (8) : Add OOR Table to indicate in which modes the display could show OOR directly.
OORModeTableType code tOORINPUT_MODE_TABLE[_MAX_OOR_MODE_NUMBER] =
{
    {   // Mode 0 : 1400 x 1050 85Hz
        939,  850,                                                          // IHFreq, IVFreq,
        1105, 4,                                                            // IVTotal, IVSyncPulse,
    },

    {   // Mode 1 : 1680 x 1050 85Hz
        939,  850,                                                          // IHFreq, IVFreq,
        1105, 6,                                                            // IVTotal, IVSyncPulse,
    },

    {   // Mode 2 : 1600 x 1200 85Hz
        1062, 850,                                                          // IHFreq, IVFreq,
        1250, 3,                                                            // IVTotal, IVSyncPulse,
    },

    {   // Mode 3 : 1920 x 1200 75Hz
        940,  749,                                                          // IHFreq, IVFreq,
        1255, 3,                                                            // IVTotal, IVSyncPulse,
    },

    {   // Mode 4 : 1800 x 1440 60Hz
        894,  599,                                                          // IHFreq, IVFreq,
        1493, 7,                                                            // IVTotal, IVSyncPulse,
    },

    // V013 VGA Patch Note (24) Modify 20100518 Start
    // Patch Reason : Mode Search Updates.
    {   // Mode 5 : 1920 x 1440 60Hz
        900,  600,                                                          // IHFreq, IVFreq,
        1493, 4,                                                            // IVTotal, IVSyncPulse,
    },
    // V013 VGA Patch Note (24) Modify 20100518 End
};
// V012 Modify 20100322 End

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
OverScanRatioType code tOVERSCAN_DISPLAY_TABLE[] =
{
    // V013 VGA Patch Note (24) Modify 20100514 Start
    // Patch Reason : Mode search updates.
    /*
    {
        _MODE_720x480i_60Hz,                                                // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _MODE_720x576i_50Hz,                                                // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },
    */
    {
        _MODE_1440x480i_60HZ,                                                // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _MODE_1440x576i_50Hz,                                               // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },
    // V013 VGA Patch Note (24) Modify 20100514 End

    {
        _MODE_640x480_60HZ,                                                 // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _MODE_720x480p_60HZ,                                                // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _MODE_720x576p_50Hz,                                                // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _MODE_1280x720p_50HZ,                                               // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _MODE_1280x720p_60HZ,                                                // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _MODE_1280x720_60HZ_2,                                               // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _MODE_1920x1080i_50Hz,                                              // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _MODE_1920x1080i_60HZ,                                              // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _MODE_1920x1080p_50Hz,                                              // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _MODE_1920x1080p_60HZ,                                              // ModeIndex,
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {   // This is the last item, and never delete it.
        // Add your new items before this last item.
        0xFF,
        0, 0,
    },
};
#endif
// V012 Modify 20100316 End

#else


extern ModeTableType code tINPUTMODE_PRESET_TABLE[_MAX_PRESET_MODE];

#if(_DISP_INFO_BY_MODE == _ON)

extern DisplayTableType code tDISPLAY_PRESET_TABLE[_MAX_PRESET_MODE];

#endif

// V012 Modify 20100322 Start
// V012 Patch Note (8) : Add OOR Table to indicate in which modes the display could show OOR directly.
extern OORModeTableType code tOORINPUT_MODE_TABLE[_MAX_OOR_MODE_NUMBER];
// V012 Modify 20100322 End

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
extern OverScanRatioType code tOVERSCAN_DISPLAY_TABLE[];
#endif
// V012 Modify 20100316 End

#endif
