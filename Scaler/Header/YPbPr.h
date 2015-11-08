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
// ID Code      : YPbPr.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_YPBPR_SUPPORT == _ON)

//--------------------------------------------------
// Definitions of
//--------------------------------------------------

// V013 VGA Patch Note (5) 20100409 Modify Start
// Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
/*
#define _MAX_YPBPR_MODE             10
*/
#define _MAX_YPBPR_MODE             11
// V013 VGA Patch Note (5) 20100409 Modify End

// V012 Modify 20100320 Start
// V012 Patch Note (12) : Show video timing info in OSD.
//--------------------------------------------------
// Preset Mode
//--------------------------------------------------
enum YpbprPresetModeDef
{
    // V013 VGA Patch Note (5) 20100409 Modify Start
    // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
    /*
    _VIDEO_720x576i_50HZ = 0,        // Mode 0:
    _VIDEO_720x480i_60HZ,            // Mode 1:
    */
    _VIDEO_1440x576i_50HZ = 0,       // Mode 0:
    _VIDEO_1440x480i_60HZ,           // Mode 1:
    // V013 VGA Patch Note (5) 20100409 Modify End

    _VIDEO_720x576p_50HZ,            // Mode 2:
    _VIDEO_720x480p_60HZ,            // Mode 3:
    _VIDEO_1280x720p_60HZ,           // Mode 4:
    _VIDEO_1920x1080i_50HZ,          // Mode 5:
    _VIDEO_1920x1080i_60HZ,          // Mode 6:
    _VIDEO_1280x720p_50HZ,           // Mode 7:
    _VIDEO_1920x1080p_50HZ,          // Mode 8:
    _VIDEO_1920x1080p_60HZ,          // Mode 9:

    // V013 VGA Patch Note (5) 20100409 Modify Start
    // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
    _VIDEO_1920x1080i_50HZ_2,        // Mode 10:
    // V013 VGA Patch Note (5) 20100409 Modify End
};
// V012 Modify 20100320 End

//----------------------------------------------------------------------------------------------------

#ifdef __YPBPR__

// V012 Modify 20100324 Start
// V012 Patch Note (3) : Modify mode table and mode search according to SQE testing items, and to sync with Dell case.
/*
//--------------------------------------------------
// YPbPr Tables
//--------------------------------------------------
ModeTableType code tYPBPR_MODE_TABLE[_MAX_YPBPR_MODE] =
{
    //--------------------------------------------------
    // YPbPr Modes
    //--------------------------------------------------
    {   // Mode 0 : 720 x 576i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        704, 272,                                                           // InputWidth, InputHeight,
        156, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        864, 312,                                                           // HTotal, VTotal,
        143, 31,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 1 : 720 x 480i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        704, 224,                                                           // InputWidth, InputHeight,
        157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        858, 262,                                                           // HTotal, VTotal,
        129, 27,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 2 : 720 x 576p x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        704, 560,                                                           // InputWidth, InputHeight,
        312, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        864, 624,                                                           // HTotal, VTotal,
        141, 48,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 3 : 720 x 480p x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        704, 464,                                                           // InputWidth, InputHeight,
        315, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        858, 526,                                                           // HTotal, VTotal,
        131, 45,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 4 : 1280 x 720p x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1248, 704,                                                          // InputWidth, InputHeight,
        450, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1650, 750,                                                          // HTotal, VTotal,
        311, 33,                                                            // HStartPos, VStartPos,
    },
/*
    {   // Mode 5 : 1920 x 1080i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 524,                                                          // InputWidth, InputHeight,
        281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1760, 562,                                                          // HTotal, VTotal,
        165, 27,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 6 : 1920 x 1080i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280, 524,                                                          // InputWidth, InputHeight,
        337, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1466, 562,                                                          // HTotal, VTotal,
        179, 27,                                                            // HStartPos, VStartPos,
    },
* /
    {   // Mode 5 : 1920 x 1080i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920, 524,                                                          // InputWidth, InputHeight,
        281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2640, 562,                                                          // HTotal, VTotal,
        237, 33,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 6 : 1920 x 1080i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920, 524,                                                           // InputWidth, InputHeight,
        337, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2200, 562,                                                           // HTotal, VTotal,
        237, 33,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 7 : 1280 x 720p x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1248, 704,                                                          // InputWidth, InputHeight,
        376, 502,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1980, 750,                                                          // HTotal, VTotal,
        300, 25,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 8 : 1920 x 1080p x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
        563, 501,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2640, 1125,                                                         // HTotal, VTotal,
        237, 41,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 9 : 1920 x 1080p x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
        675, 601,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2200, 1125,                                                         // HTotal, VTotal,
        235, 39,                                                            // HStartPos, VStartPos,
    },

};
*/
//--------------------------------------------------
// YPbPr Tables
//--------------------------------------------------
ModeTableType code tYPBPR_MODE_TABLE[_MAX_YPBPR_MODE] =
{
    // V013 VGA Patch Note (5) 20100409 Modify Start
    // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
    /*
    {   // Mode 0 : 720 x 576i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
         720,  288,                                                         // InputWidth, InputHeight,
         156,  500,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
         864,  312,                                                         // HTotal, VTotal,

         // V013 VGA Patch Note (4) 20100409 Modify Start
         // Patch Reason : Modify YPbPr Timing HVStart position parameter for full frame displays.
         /*
         132,   23,                                                         // HStartPos, VStartPos,
         * /
         137,   21,                                                         // HStartPos, VStartPos,
         // V013 VGA Patch Note (4) 20100409 Modify End
    },

    {   // Mode 1 : 720 x 480i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
         720,  240,                                                         // InputWidth, InputHeight,
         157,  600,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
         858,  262,                                                         // HTotal, VTotal,

         // V013 VGA Patch Note (4) 20100409 Modify Start
         // Patch Reason : Modify YPbPr Timing HVStart position parameter for full frame displays.
         /*
         119,   21,                                                         // HStartPos, VStartPos,
         * /
         124,   18,                                                         // HStartPos, VStartPos,
         // V013 VGA Patch Note (4) 20100409 Modify End
    },
    */
    {   // Mode 0 : 1440 x 576i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1440, 288,                                                          // InputWidth, InputHeight,
        157, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1728, 312,                                                           // HTotal, VTotal,
        269, 21,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 1 : 1440 x 480i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP,                        // Polarity Flags,
        1440, 240,                                                          // InputWidth, InputHeight,
        157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1716, 262,                                                          // HTotal, VTotal,
        243, 18,                                                            // HStartPos, VStartPos,
    },
    // V013 VGA Patch Note (5) 20100409 Modify End

    {   // Mode 2 : 720 x 576p x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
         720,  576,                                                         // InputWidth, InputHeight,
         312,  500,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
         864,  625,                                                         // HTotal, VTotal,

         // V013 VGA Patch Note (4) 20100409 Modify Start
         // Patch Reason : Modify YPbPr Timing HVStart position parameter for full frame displays.
         /*
         132,   44,                                                         // HStartPos, VStartPos,
         */
         137,   42,                                                         // HStartPos, VStartPos,
         // V013 VGA Patch Note (4) 20100409 Modify End
    },

    {   // Mode 3 : 720 x 480p x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
         720,  480,                                                         // InputWidth, InputHeight,
         315,  600,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
         858,  525,                                                         // HTotal, VTotal,

         // V013 VGA Patch Note (4) 20100409 Modify Start
         // Patch Reason : Modify YPbPr Timing HVStart position parameter for full frame displays.
         /*
         122,   36,                                                         // HStartPos, VStartPos,
         */
         127,   34,                                                         // HStartPos, VStartPos,
         // V013 VGA Patch Note (4) 20100409 Modify End
    },

    {   // Mode 4 : 1280 x 720p x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280,  720,                                                         // InputWidth, InputHeight,
         450,  600,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1650,  750,                                                         // HTotal, VTotal,

         // V013 VGA Patch Note (4) 20100409 Modify Start
         // Patch Reason : Modify YPbPr Timing HVStart position parameter for full frame displays.
         /*
         260,   25,                                                         // HStartPos, VStartPos,
         */
         264,   23,                                                         // HStartPos, VStartPos,
         // V013 VGA Patch Note (4) 20100409 Modify End
    },

    {   // Mode 5 : 1920 x 1080i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920,  540,                                                         // InputWidth, InputHeight,
         281,  500,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2640,  562,                                                         // HTotal, VTotal,

         // V013 VGA Patch Note (4) 20100409 Modify Start
         // Patch Reason : Modify YPbPr Timing HVStart position parameter for full frame displays.
         /*
         192,   21,                                                         // HStartPos, VStartPos,
         */
         196,   18,                                                         // HStartPos, VStartPos,
         // V013 VGA Patch Note (4) 20100409 Modify End
    },

    {   // Mode 6 : 1920 x 1080i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920,  540,                                                         // InputWidth, InputHeight,
         337,  600,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2200,  562,                                                         // HTotal, VTotal,

         // V013 VGA Patch Note (4) 20100409 Modify Start
         // Patch Reason : Modify YPbPr Timing HVStart position parameter for full frame displays.
         /*
         192,   21,                                                         // HStartPos, VStartPos,
         */
         196,   18,                                                         // HStartPos, VStartPos,
         // V013 VGA Patch Note (4) 20100409 Modify End
    },

    {   // Mode 7 : 1280 x 720p x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1280,  720,                                                         // InputWidth, InputHeight,
         375,  500,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1980,  750,                                                         // HTotal, VTotal,

         // V013 VGA Patch Note (4) 20100409 Modify Start
         // Patch Reason : Modify YPbPr Timing HVStart position parameter for full frame displays.
         /*
         260,   25,                                                         // HStartPos, VStartPos,
         */
         264,   23,                                                         // HStartPos, VStartPos,
         // V013 VGA Patch Note (4) 20100409 Modify End
    },

    {   // Mode 8 : 1920 x 1080p x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
         562,  500,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2640, 1125,                                                         // HTotal, VTotal,

         // V013 VGA Patch Note (4) 20100409 Modify Start
         // Patch Reason : Modify YPbPr Timing HVStart position parameter for full frame displays.
         /*
         192,   41,                                                         // HStartPos, VStartPos,
         */
         195,   39,                                                         // HStartPos, VStartPos,
         // V013 VGA Patch Note (4) 20100409 Modify End
    },

    {   // Mode 9 : 1920 x 1080p x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920, 1080,                                                         // InputWidth, InputHeight,
         675,  600,                                                         // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2200, 1125,                                                         // HTotal, VTotal,

         // V013 VGA Patch Note (4) 20100409 Modify Start
         // Patch Reason : Modify YPbPr Timing HVStart position parameter for full frame displays.
         /*
         192,   41,                                                         // HStartPos, VStartPos,
         */
         195,   39,                                                         // HStartPos, VStartPos,
         // V013 VGA Patch Note (4) 20100409 Modify End
    },

    // V013 VGA Patch Note (5) 20100409 Modify Start
    // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
    {   // Mode 10 : 1920 x 1080i x 50 Hz _2
        0 | _SYNC_HN_VN | _SYNC_HN_VP | _SYNC_HP_VP | _SYNC_HP_VN,          // Polarity Flags,
        1920, 540,                                                          // InputWidth, InputHeight,
        313, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2304, 625,                                                          // HTotal, VTotal,
        356,  78,                                                            // HStartPos, VStartPos,
    },
    // V013 VGA Patch Note (5) 20100409 Modify End
};
// V012 Modify 20100324 End

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
OverScanRatioType code tOVERSCAN_YPBPR_DISPLAY_TABLE[] =
{
    // V013 VGA Patch Note (5) 20100409 Modify Start
    // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
    /*
    {
        _VIDEO_720x576i_50HZ,                                               // Mode 0 : 720 x 576i x 50 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _VIDEO_720x480i_60HZ,                                               // Mode 1 : 720 x 480i x 60 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },
    */
    {
        _VIDEO_1440x576i_50HZ,                                               // Mode 0 : 720 x 576i x 50 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _VIDEO_1440x480i_60HZ,                                              // Mode 1 : 1440 x 480i x 60 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },
    // V013 VGA Patch Note (5) 20100409 Modify End

    {
        _VIDEO_720x576p_50HZ,                                               // Mode 2 : 720 x 576p x 50 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _VIDEO_720x480p_60HZ,                                               // Mode 3 : 720 x 480p x 60 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _VIDEO_1280x720p_60HZ,                                              // Mode 4 : 1280 x 720p x 60 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _VIDEO_1920x1080i_50HZ,                                             // Mode 5 : 1920 x 1080i x 50 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _VIDEO_1920x1080i_60HZ,                                             // Mode 6 : 1920 x 1080i x 60 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _VIDEO_1280x720p_50HZ,                                              // Mode 7 : 1280 x 720p x 50 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _VIDEO_1920x1080p_50HZ,                                             // Mode 8 : 1920 x 1080p x 50 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    {
        _VIDEO_1920x1080p_60HZ,                                             // Mode 9 : 1920 x 1080p x 60 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },

    // V013 VGA Patch Note (5) 20100409 Modify Start
    // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
    {
        _VIDEO_1920x1080i_50HZ_2,                                           // Mode 10 : 1920 x 1080i x 50 Hz
        _OVERSCAN_RATIO, _OVERSCAN_RATIO,                                   // IHWidthRatio, IVHeightRatio,
    },
    // V013 VGA Patch Note (5) 20100409 Modify End

    {   // This is the last item, and never delete it.
        // Add your new items before this last item.
        0xFF,
        0, 0,
    },
};
#endif
// V012 Modify 20100316 End

BYTE code tYPBPR_CLAMP_POSITION_TABLE[] =
{
    // V013 VGA Patch Note (5) 20100409 Modify Start
    // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
    /*
    0x08,0x16, // Mode 0 : 720 x 576i x 50 Hz
    0x08, 0x16, // Mode 1 : 720 x 480i x 60 Hz
    */
    0x20, 0x38, // Mode 0 : 1440 x 576i x 50 Hz
    0x20, 0x38, // Mode 1 : 1440 x 480i x 60 Hz
    // V013 VGA Patch Note (5) 20100409 Modify End

     0x08,0x16, // Mode 2 : 720 x 576p x 50 Hz
     0x08,0x16, // Mode 3 : 720 x 480p x 60 Hz
     0x20,0x38, // Mode 4 : 1280 x 720p x 60 Hz
     0x20,0x38, // Mode 5 : 1920 x 1080i x 50 Hz (1080i25)
     0x20,0x38, // Mode 6 : 1920 x 1080i x 60 Hz (1080i30)
     0x20,0x38, // Mode 7 : 1280 x 720p x 50 Hz
     0x20,0x38, // Mode 8 : 1920 x 1080p x 50 Hz
     0x20,0x38, // Mode 9 : 1920 x 1080p x 60 Hz

     // V013 VGA Patch Note (5) 20100409 Modify Start
     // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
     0x20, 0x38, // Mode 10 : 1920 x 1080i x 50 Hz _2 (1080i25)
     // V013 VGA Patch Note (5) 20100409 Modify End
};


BYTE code tYPBPR_TABLE_SET_SCALER[] =
{
    4,  _NON_AUTOINC,   _CB_ACCESS_PORT_64,             0x80,
    9,  _NON_AUTOINC,   _CB_DATA_PORT_65,               0x7e,0x7e,0x7e,0x80,0x80,0x80,
    4,  _NON_AUTOINC,   _CB_ACCESS_PORT_64,             0x00,
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

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,             0x07,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,         0x02,// Enable Coefficient Access
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


    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE0,

    // V012 Modify 20100317 Start
    // V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
    /*
    4,  _NON_AUTOINC,   _P0_ADC_V_BIAS1_CD,             0x29,
    6,  _AUTOINC,       _P0_ADC_RED_CTL_CF,             0xc0,0xc0,0xc0,
    */
    4,  _NON_AUTOINC,   _P0_ADC_V_BIAS1_CD,             0x09,
    6,  _AUTOINC,       _P0_ADC_RED_CTL_CF,             0xc0,0x40,0xc0,
    // V012 Modify 20100317 End

    _END
};

//--------------------------------------------------
// Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
BYTE CYPbPrSearchMode(void);
bit CYPbPrCompareMode(BYTE ucModeCnt);
void CYPbPrGetModeInfo(void);
void CYPbPrStartUp(void);
void CYPbPrSetupMode(void);

// V013 VGA Patch Note (5) 20100409 Modify Start
// Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
BYTE CYPbPrSearchAcceptiveMode(BYTE ucModeCnt);
// V013 VGA Patch Note (5) 20100409 Modify End

// V013 VGA Patch Note (23) Modify 20100513 Start
// Patch Reason : For Video Mode Clamp Position Setting Flow
void CYPbPrModeClampPositionSetting(void);
// V013 VGA Patch Note (23) Modify 20100513 End

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern BYTE CYPbPrSearchMode(void);
extern void CYPbPrSetupMode(void);
extern void CYPbPrStartUp(void);

// V013 VGA Patch Note (23) Modify 20100513 Start
// Patch Reason : For Video Mode Clamp Position Setting Flow
extern void CYPbPrModeClampPositionSetting(void);
// V013 VGA Patch Note (23) Modify 20100513 End

extern BYTE code tYPBPR_TABLE_SET_SCALER[];
extern BYTE code tYPBPR_CLAMP_POSITION_TABLE[];
extern ModeTableType code tYPBPR_MODE_TABLE[_MAX_YPBPR_MODE];

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
extern OverScanRatioType code tOVERSCAN_YPBPR_DISPLAY_TABLE[];
#endif
// V012 Modify 20100316 End

#endif // End of #ifdef __YPBPR__

//----------------------------------------------------------------------------------------------------

#endif  // End of #if(_YPBPR_SUPPORT == _ON)
