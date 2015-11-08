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
// ID Code      : Mode.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Active State Tolerance
//--------------------------------------------------
#define _DP_ERROR_TOLERANCE         3      // for Active State Error Tolerance //20090212 wuzanne for autosearch No.029

//--------------------------------------------------
// ACD Sampling Limitation
//--------------------------------------------------
#if(_SCALER_TYPE == _RTD247xRD)
#define _ADC_SAMPLE_CLOCK_LIMIT         2500000
#else
#define _ADC_SAMPLE_CLOCK_LIMIT         2100000
#endif

// HW ADC Max dot clock by SPEC (Hz * 10), don't touch it until HW/IC is changed
#if(_SCALER_TYPE == _RTD247xRD)
#define _HW_ADC_SAMPLE_CLOCK_LIMIT      2500000
#else
#define _HW_ADC_SAMPLE_CLOCK_LIMIT      2100000
#endif

#if(_ADC_SAMPLE_CLOCK_LIMIT > _HW_ADC_SAMPLE_CLOCK_LIMIT)
#error User defined Max ADC Clock is over IC max clock!
#endif
#define _PIXEL_WIDTH_LIMIT              3200

//--------------------------------------------------
// IVHeight Verification Tolerance
//--------------------------------------------------
#define _MODE_IVHEIGHT_TOLERANCE        5

//--------------------------------------------------
// Check Mode VGA Result Enum
//--------------------------------------------------
enum CheckModeVGAResult
{
    _CHECK_MODE_SUCCESS = 0,
    _CHECK_MODE_INDEX_ERROR,
    _CHECK_MODE_ADC_SPEED_ERROR,
    _CHECK_MODE_TABLE_INFO_ERROR,
    _CHECK_MODE_FRAME_SYNC_ERROR,
};

//--------------------------------------------------
// Definitions of Auto Function, (0.1%) for each unit
//--------------------------------------------------
#define _MAX_IVHEIGHT_RATIO               980


#ifdef __MODE__

// V016 System Patch Note (25) Modify 20100831 Start
// Patch Reason : Modify Overscan Effect Condition.
#if(((_HDMI_SUPPORT == _ON) && (_OVERSCAN_HDMI_SUPPORT == _ON)) || ((_DP_SUPPORT == _ON) && (_OVERSCAN_DP_SUPPORT == _ON)))
// Digital timing overscan enable table
WORD code tOverscanDigitalEnTable[][3] =
{
    // HWidth, VHeight, VFreq,
    {640, 480, 600},    // 640x480-60
    {720, 480, 600},    // 480p
    {1440, 480, 600},   // 480p
    {720, 576, 500},    // 576p
    {1440, 576, 500},   // 576p
    {1280, 720, 500},   // 720p
    {1280, 720, 600},   // 720p

    // Don't delete it, and place it at last.
    {0, 0, 0},
};
#endif
// V016 System Patch Note (25) Modify 20100831 End

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE xdata ucCurrState = _PWOFF_STATE;
BYTE xdata ucModeControl = 0;
BYTE xdata g_ucTimerCnt = 0;

BYTE xdata ucEvent0 = 255;
BYTE xdata ucEvent1 = 255;

bit idata g_bCheckHDCP = 0;

BYTE xdata ucModeFound = 0;
WORD xdata g_usHStartBias = 0;
BYTE xdata g_ucVStartBias = 0;

BYTE xdata ucSourceControl = 0;

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
/*
#if (_HDMI_OVERSCAN == _ON)
BYTE xdata ucOverScanH = 0;
BYTE xdata ucOverScanV = 0;
#endif
*/
#if(_OVERSCAN_SUPPORT == _ON)
BYTE xdata g_ucOverScanFlag = 0;
BYTE xdata g_ucOverScanH = 0;
BYTE xdata g_ucOverScanV = 0;

WORD xdata g_usCaptureStartH = 0;
BYTE xdata g_usCaptureStartV = 0;

WORD xdata g_usOldIHWidth = 0;
WORD xdata g_usOldIVHeight = 0;

BYTE xdata g_ucUserModeCurr = 0;
BYTE xdata g_ucIv2DvModify = 0;
#endif
// V012 Modify 20100316 End

WORD xdata g_usAdcClockLimit = _PIXEL_WIDTH_LIMIT;
WORD xdata g_usCaptureStart = 0;
WORD xdata g_usCurrIVHeight = 0;


// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#if(_COLOR_FORMAT_CONVERT == _ON)
bit idata g_bColorFormatStatus = 0;
#endif
// V012 Modify 20100304 End

// V012 Modify 20100402 Start
// V012 Patch Note (29) : Fix the inaccurate Vfreq in OSD with SOG HORV/HEORV sync type.
BYTE xdata g_ucCoastLineCnt = 0;
// V012 Modify 20100402 End

// V013 TMDS Patch Note (16) 20100422 Modify Start
// Patch Reason : Solve DVI Interlace Issue.
bit idata g_bIVSDelayOneLine = 0;
bit idata g_bIVSDelayOneLineInvert = 0;
bit idata g_bDoModeResetMode = _FALSE;
// V013 TMDS Patch Note (16) 20100422 Modify End

// V012 Modify 20100331 Start
// V012 Patch Note (30) : Use mode search incorrect flag to skip SOD clock seeking in the auto stage to avoid one missing vertical line at the edge of the picture.
bit data g_bModeSearchIncorrectFlag = _FALSE;
// V012 Modify 20100331 End

// V013 TMDS Patch Note (17) 20100422 Modify Start
// Patch Reason : Solve Dual Link DVI Issue.
BYTE xdata g_ucNoSupportCnt = 0;
WORD xdata g_usIHWidthBackUp = 0;
WORD xdata g_usIVHeightBackUp = 0;
// V013 TMDS Patch Note (17) 20100422 Modify End

// V013 VGA Patch Note (11) Modify 20100416 Start
// Patch Reason : Add FIFO Mode Only to save EEPROM space.
// Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
#if(_FIFO_MODE_ONLY == _ON)
BYTE xdata g_ucFIFOModeNum = 0;
#endif
// V013 VGA Patch Note (11) Modify 20100416 End

// V013 VGA Patch Note (10) 20100416 Modify Start
// Patch Reason : Support Auto Config For Yuv Color.
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
bit g_bYuvRgbFlag = _FALSE;
#endif
// V013 VGA Patch Note (10) 20100416 Modify End

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CModeHandler(void);
bit CModeMeasureReady(void);
bit CModeMeasureData(void);
bit CModeDetect(void);
bit CModeDetectCommon(void);
bit CModeIsChange(void);
BYTE CModeSearchDisplayMode(void);
BYTE CModeSearchModeVGA(void);
bit CModeComparePresetModeVGA(BYTE ucModeCnt);
BYTE CModeSearchAcceptiveModeVGA(void);
BYTE CModeCheckFIFOModeVGA(BYTE ucModeCnt);
bit CModeCompareFIFOModeVGA(BYTE ucNum, BYTE ucModeCnt);
BYTE CModeSearchModeDVI(void);
bit CModeCompareModeDVI(BYTE ucModeCnt);
void CModeDisplayActiveMode(void);
void CModeSetupModeVGA(void);
void CModeSetupModeDVI(void);
void CModeSetupDisplay(void);
void CModeSetupColorProcess(void);
void CModeSetupEtcs(BYTE ucPar);
void CModeGetModeTableInfo(void);
void CModeStartUpVGA(void);
void CModeStartUpDVI(void);
BYTE CModeGetScaleSetting(void);
void CModeSetCaptureWindow(BYTE ucOption);
void CModeSetScaling(BYTE ucOption);
void CModeSetDisplay(BYTE ucOption);
void CModeResetMode(void);
void CModeSetFreeRun(void);
bit CModeConnectIsChange(void);
void CModeAutoMeasureOn(void);
void CModeAutoMeasureOff(void);
void CModeSyncTimeoutCountDownEvent(void);
void CModeStableCountDownEvent(void);
void CModePowerSavingEvent(void);
void CModeNoSignalEvent(void);
void CModeNoCableEvent(void);
void CModeNoSupportEvent(void);
//Anderson 080130 for FRC Support Start
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))//cyyeh 20080611
void CModeSetFIFOForFrameSync(void);
#endif

void CModeOsdDisplayTimingAndInputEvent(void);
bit CModeHdmiStablePolling(void);


void CModeInterlaceCheck(void);
void CModeDeInterlaceSetting(void);

#if(_NON_LINEAR_SCALING_FUCTION == _ON)
void CScalerNonlinearScaleUp(void);
void CScalerDisableNonlinearScaleUp(void);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
bit CModeSetDHWidthToDisplay(void);
#endif

void CModeHDCPCheck(void);

#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
void CModeResetShowOSD(void);
#endif

bit CModeStableDetect(void);


#if(_LOW_FRAME_RATE_SUPPORT == _ON)

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
bit CModeCheckLowFrameRate(void);
#endif

#endif

BYTE CModeCheckModeVGA(BYTE ucModeIndex);
BYTE CModeAdditionalSearch(BYTE ucModeIndex);
void CModeInitialVGA(void);
WORD CModeIVHeightVerify(WORD usIVHeight);
void CModeCheckUserData(void);


// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#if(_COLOR_FORMAT_CONVERT == _ON)
void CModeColorFormatConvert(void);
void CModeSetRGBToYUV();
void CModeSetYUVToRGB();

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
void CModeGetCurrentModeColorFormat(void);

// V016 VGA Patch Note (1) 20100803 Modify Start
// Patch Reason : Modify for mistake, get the function out of the complier condition.
/*
void CModeConfirmClampPositionSetting(void);
*/
// V016 VGA Patch Note (1) 20100803 Modify End

// V014 VGA Patch Note (6) Modify 20100527 End

#endif
// V012 Modify 20100304 End

// V016 VGA Patch Note (1) 20100803 Modify Start
// Patch Reason : Modify for mistake, get the function out of the complier condition.
void CModeConfirmClampPositionSetting(void);
// V016 VGA Patch Note (1) 20100803 Modify End

// V012 Modify 20100322 Start
// V012 Patch Note (8) : Add OOR Table to indicate in which modes the display could show OOR directly.
bit CModeSearchOORModeVGA(BYTE ucModeCnt);
// V012 Modify 20100322 End

// V012 Modify 20100324 Start
// V012 Patch Note (3) : Modify mode table and mode search according to SQE testing items, and to sync with Dell case.
BYTE CModeSearchAcceptivePresetModeVGA(BYTE ucModeCnt);
// V012 Modify 20100324 End

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
void CModeOverScanSelect(void);
void CModeOverScanAdjustPos(void);
void CModeDecideOverScanValue(void);

// V016 System Patch Note (25) Modify 20100831 Start
// Patch Reason : Modify Overscan Effect Condition.
/*
bit CModeOverScanTimingSelect();
*/
bit CModeOverScanConditionSwitch(void);
// V016 System Patch Note (25) Modify 20100831 End

bit CModeOverScanSourceSelect(void);
void CModeOverScanSetCaptureStart(void);
bit CModeOverScanCheckCaptureWindow(void);
void CModeOverScan(void);
void CModeOverscanFrameSyncFineTune(void);
#endif
// V012 Modify 20100316 End

// V012 Modify 20100321 Start
// V012 Patch Note (14) : Fix the issue that SOG interlace signal could not light up the display when  V sync pulse is only 1H.
void CModeCheckDVTotal(void);
// V012 Modify 20100321 End

// V013 VGA Patch Note (23) Modify 20100513 Start
// Patch Reason : For Video Mode Clamp Position Setting Flow
bit CModeCheckVideoMode(void);
// V013 VGA Patch Note (23) Modify 20100513 End

// V013 VGA Patch Note (10) 20100416 Modify Start
// Patch Reason : Support Auto Config For Yuv Color.
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
void CModeYuvRgbSwitch(BYTE ucColorType);
BYTE CModeGetColorSpaceType(void);
#endif
// V013 VGA Patch Note (10) 20100416 Modify End

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
// V016 System Patch Note (25) Modify 20100831 Start
// Patch Reason : Modify Overscan Effect Condition.
#if(((_HDMI_SUPPORT == _ON) && (_OVERSCAN_HDMI_SUPPORT == _ON)) || ((_DP_SUPPORT == _ON) && (_OVERSCAN_DP_SUPPORT == _ON)))
extern WORD code tOverscanDigitalEnTable[][3];
#endif
// V016 System Patch Note (25) Modify 20100831 End

extern BYTE xdata ucCurrState;
extern BYTE xdata ucModeControl;
extern BYTE xdata ucEvent0;
extern BYTE xdata ucEvent1;
extern BYTE xdata ucModeFound;
extern BYTE xdata g_ucTimerCnt;
extern bit idata g_bCheckHDCP;
extern WORD xdata g_usHStartBias;
extern BYTE xdata g_ucVStartBias;
extern BYTE xdata ucSourceControl;

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
/*
#if (_HDMI_OVERSCAN == _ON)
extern BYTE xdata ucOverScanH;
extern BYTE xdata ucOverScanV;
#endif
*/
#if(_OVERSCAN_SUPPORT == _ON)
extern BYTE xdata g_ucOverScanFlag;
extern BYTE xdata g_ucOverScanH;
extern BYTE xdata g_ucOverScanV;

extern WORD xdata g_usCaptureStartH;
extern BYTE xdata g_usCaptureStartV;

extern WORD xdata g_usOldIHWidth;
extern WORD xdata g_usOldIVHeight;

extern BYTE xdata g_ucUserModeCurr;
extern BYTE xdata g_ucIv2DvModify;
#endif
// V012 Modify 20100316 End

extern WORD xdata g_usAdcClockLimit;
extern WORD xdata g_usCaptureStart;

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#if(_COLOR_FORMAT_CONVERT == _ON)
extern bit idata g_bColorFormatStatus;
#endif
// V012 Modify 20100304 End

// V013 TMDS Patch Note (16) 20100422 Modify Start
// Patch Reason : Solve DVI Interlace Issue.
extern bit idata g_bIVSDelayOneLine;
extern bit idata g_bIVSDelayOneLineInvert;
extern bit idata g_bDoModeResetMode;
// V013 TMDS Patch Note (16) 20100422 Modify End

// V012 Modify 20100402 Start
// V012 Patch Note (29) : Fix the inaccurate Vfreq in OSD with SOG HORV/HEORV sync type.
extern xdata g_ucCoastLineCnt;
// V012 Modify 20100402 End

// V012 Modify 20100331 Start
// V012 Patch Note (30) : Use mode search incorrect flag to skip SOD clock seeking in the auto stage to avoid one missing vertical line at the edge of the picture.
extern bit data g_bModeSearchIncorrectFlag;
// V012 Modify 20100331 End

// V013 VGA Patch Note (11) Modify 20100416 Start
// Patch Reason : Add FIFO Mode Only to save EEPROM space.
// Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
#if(_FIFO_MODE_ONLY == _ON)
extern BYTE xdata g_ucFIFOModeNum;
#endif
// V013 VGA Patch Note (11) Modify 20100416 End

// V013 VGA Patch Note (10) 20100416 Modify Start
// Patch Reason : Support Auto Config For Yuv Color.
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
extern bit g_bYuvRgbFlag;
#endif
// V013 VGA Patch Note (10) 20100416 Modify End

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CModeHandler(void);
extern bit CModeMeasureReady(void);
extern bit CModeMeasureData(void);
extern bit CModeDetect(void);
extern bit CModeDetectCommon(void);
extern bit CModeIsChange(void);

// V016 System Patch Note (15) Modify 20100824 Start
// Patch Reason : Fix IHCount=0 issue
extern void CModeAutoMeasureOn(void);
extern void CModeAutoMeasureOff(void);
// V016 System Patch Note (15) Modify 20100824 End

extern void CModeSetScaling(BYTE ucOption);
extern void CModeResetMode(void);
extern void CModeSetFreeRun(void);
extern void CModeSyncTimeoutCountDownEvent(void);
extern void CModeStableCountDownEvent(void);
extern void CModeSetupDisplay(void);
extern void CModeSetupColorProcess(void);
extern void CModeSetupEtcs(BYTE ucPar);
extern void CModeStartUpVGA(void);
extern void CModePowerSavingEvent(void);
extern void CModeNoSignalEvent(void);
extern void CModeNoCableEvent(void);
extern void CModeNoSupportEvent(void);
extern bit CModeHdmiStablePolling(void);
extern void CModeOsdDisplayTimingAndInputEvent(void);
extern void CModeInterlaceCheck(void);
extern void CModeSetCaptureWindow(BYTE ucOption);
extern void CModeSetDisplay(BYTE ucOption);
// FRC Support Start
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
extern void CModeSetFIFOForFrameSync(void);
#endif
// FRC Support End

extern void CModeDeInterlaceSetting(void);

#if(_NON_LINEAR_SCALING_FUCTION == _ON)
extern void CScalerNonlinearScaleUp(void);
extern void CScalerDisableNonlinearScaleUp(void);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
extern bit CModeSetDHWidthToDisplay(void);
#endif

extern void CModeHDCPCheck(void);

#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
extern void CModeResetShowOSD(void);
#endif

extern bit CModeStableDetect(void);

#if(_LOW_FRAME_RATE_SUPPORT == _ON)

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
extern bit CModeCheckLowFrameRate(void);
#endif

#endif

extern bit CModeComparePresetModeVGA(BYTE ucModeCnt);


// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#if(_COLOR_FORMAT_CONVERT == _ON)
extern void CModeColorFormatConvert(void);
extern void CModeSetRGBToYUV();
extern void CModeSetYUVToRGB();

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
extern void CModeGetCurrentModeColorFormat(void);

// V016 VGA Patch Note (1) 20100803 Modify Start
// Patch Reason : Modify for mistake, get the function out of the complier condition.
/*
extern void CModeConfirmClampPositionSetting(void);
*/
// V016 VGA Patch Note (1) 20100803 Modify End

// V014 VGA Patch Note (6) Modify 20100527 End

#endif
// V012 Modify 20100304 End

// V016 VGA Patch Note (1) 20100803 Modify Start
// Patch Reason : Modify for mistake, get the function out of the complier condition.
extern void CModeConfirmClampPositionSetting(void);
// V016 VGA Patch Note (1) 20100803 Modify End

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
extern void CModeOverScanSelect(void);
extern void CModeOverScanAdjustPos(void);
extern void CModeDecideOverScanValue(void);

// V016 System Patch Note (25) Modify 20100831 Start
// Patch Reason : Modify Overscan Effect Condition.
/*
extern bit CModeOverScanTimingSelect();
*/
extern bit CModeOverScanConditionSwitch(void);
// V016 System Patch Note (25) Modify 20100831 End

extern bit CModeOverScanSourceSelect(void);
extern void CModeOverScanSetCaptureStart(void);
extern bit CModeOverScanCheckCaptureWindow(void);
extern void CModeOverScan(void);
extern void CModeOverscanFrameSyncFineTune(void);
#endif
// V012 Modify 20100316 End

// V012 Modify 20100321 Start
// V012 Patch Note (14) : Fix the issue that SOG interlace signal could not light up the display when  V sync pulse is only 1H.
extern void CModeCheckDVTotal(void);
// V012 Modify 20100321 End

// V013 VGA Patch Note (22) Modify 20100511 Start
// Patch Reason : Modify Capture Window Size for HEORV/OR Sync Type
extern void CModeInitialVGA();
// V013 VGA Patch Note (22) Modify 20100511 End

// V013 VGA Patch Note (23) Modify 20100513 Start
// Patch Reason : For Video Mode Clamp Position Setting Flow
extern bit CModeCheckVideoMode(void);
// V013 VGA Patch Note (23) Modify 20100513 End

// V013 VGA Patch Note (10) 20100416 Modify Start
// Patch Reason : Support Auto Config For Yuv Color.
#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
extern void CModeYuvRgbSwitch(BYTE ucColorType);
extern BYTE CModeGetColorSpaceType(void);
#endif
// V013 VGA Patch Note (10) 20100416 Modify End

#endif // End of #ifdef __MODE__

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Sync Processor Measure Ready Flag
//--------------------------------------------------
#define GET_VIDEOMODECHANGE()                   (bit)(ucModeControl & _BIT0)
#define SET_VIDEOMODECHANGE()                   (ucModeControl |= _BIT0)
#define CLR_VIDEOMODECHANGE()                   (ucModeControl &= ~_BIT0)

//--------------------------------------------------
// Macro of Start Display for OSD Flow
//--------------------------------------------------
#define GET_OSD_READYFORDISPLAY()               (bit)(ucModeControl & _BIT1)
#define SET_OSD_READYFORDISPLAY()               (ucModeControl |= _BIT1)
#define CLR_OSD_READYFORDISPLAY()               (ucModeControl &= ~_BIT1)

//--------------------------------------------------
// Macro of Mode Stable Flag
//--------------------------------------------------
#define GET_MODESTABLE()                        ((bit)(ucModeControl & _BIT2))
#define SET_MODESTABLE()                        (ucModeControl |= _BIT2)
#define CLR_MODESTABLE()                        (ucModeControl &= ~_BIT2)

//--------------------------------------------------
// Macro of Frame Sync Status
//--------------------------------------------------
#define GET_FRAMESYNCSTATUS()                   ((bit)(ucModeControl & _BIT3))
#define SET_FRAMESYNCSTATUS()                   (ucModeControl |= _BIT3)
#define CLR_FRAMESYNCSTATUS()                   (ucModeControl &= ~_BIT3)

//--------------------------------------------------
// Macro of Start Display
//--------------------------------------------------
#define GET_DEEPCOLORMODE()                     ((bit)(ucModeControl & _BIT4))
#define SET_DEEPCOLORMODE()                     (ucModeControl |= _BIT4)
#define CLR_DEEPCOLORMODE()                     (ucModeControl &= ~_BIT4)

//--------------------------------------------------
// Macro of Interlace Mode Check
//--------------------------------------------------
#define GET_INTERLACE_MODE()                    ((bit)(ucModeControl & _BIT5))
#define SET_INTERLACE_MODE()                    (ucModeControl |= _BIT5)
#define CLR_INTERLACE_MODE()                    (ucModeControl &= ~_BIT5)

//--------------------------------------------------
// Macro of Dp Hotplug
//--------------------------------------------------
#define GET_DPHOTPLUG()                         ((bit)(ucModeControl & _BIT6))
#define SET_DPHOTPLUG()                         (ucModeControl |= _BIT6)
#define CLR_DPHOTPLUG()                         (ucModeControl &= ~_BIT6)

//--------------------------------------------------
// Macro of Start Display
//--------------------------------------------------
#define GET_READYFORDISPLAY()                   ((bit)(ucModeControl & _BIT7))
#define SET_READYFORDISPLAY()                   (ucModeControl |= _BIT7)
#define CLR_READYFORDISPLAY()                   (ucModeControl &= ~_BIT7)

//--------------------------------------------------
// Macro of HDMI Check to Active State Time Flag _ 3s
//--------------------------------------------------
#define GET_COUNTDOWN_HDMI_HDCP_WORSE()         (bit)(g_ucTimerCnt & _BIT0)
#define SET_COUNTDOWN_HDMI_HDCP_WORSE()         (g_ucTimerCnt |= _BIT0)
#define CLR_COUNTDOWN_HDMI_HDCP_WORSE()         (g_ucTimerCnt &= ~_BIT0)

//--------------------------------------------------
// Macro of HDMI Check to Active State Time Flag _ 0.3s
//--------------------------------------------------
#define GET_COUNTDOWN_HDMI_STABLE()               (bit)(g_ucTimerCnt & _BIT1)
#define SET_COUNTDOWN_HDMI_STABLE()               (g_ucTimerCnt |= _BIT1)
#define CLR_COUNTDOWN_HDMI_STABLE()               (g_ucTimerCnt &= ~_BIT1)

//--------------------------------------------------
// Macro of DP Check to Active State Time Flag _ 0.5s
//--------------------------------------------------
#define GET_COUNTDOWN_DP_STABLE()               (bit)(g_ucTimerCnt & _BIT2)
#define SET_COUNTDOWN_DP_STABLE()               (g_ucTimerCnt |= _BIT2)
#define CLR_COUNTDOWN_DP_STABLE()               (g_ucTimerCnt &= ~_BIT2)

//--------------------------------------------------
// Macro of VGA Check to Active State Time Flag _ 0.1s
//--------------------------------------------------
#define GET_COUNTDOWN_VGA_STABLE()              (bit)(g_ucTimerCnt & _BIT3)
#define SET_COUNTDOWN_VGA_STABLE()              (g_ucTimerCnt |= _BIT3)
#define CLR_COUNTDOWN_VGA_STABLE()              (g_ucTimerCnt &= ~_BIT3)

//--------------------------------------------------
// Macro of Power Status
//--------------------------------------------------
#define GET_POWERSTATUS()                       ((bit)(stSystemData.MonitorFlag & _BIT7))
#define SET_POWERSTATUS()                       (stSystemData.MonitorFlag |= _BIT7)// Power Up
#define CLR_POWERSTATUS()                       (stSystemData.MonitorFlag &= ~_BIT7)// Power Down

//--------------------------------------------------
// Macro of Input Source Type
//--------------------------------------------------
#define GET_INPUTSOURCE_TYPE()                  (ucSourceControl & (_BIT2 | _BIT1 | _BIT0))
#define SET_INPUTSOURCE_TYPE(x)                 (ucSourceControl = ((ucSourceControl & ~(_BIT2 | _BIT1 | _BIT0)) | (x & 0x07)))

//--------------------------------------------------
// Macro of VGA Initial
//--------------------------------------------------
#define GET_VGA_INITIAL()                       (bit)(ucSourceControl & _BIT7)
#define SET_VGA_INITIAL()                       (ucSourceControl |= _BIT7)
#define CLR_VGA_INITIAL()                       (ucSourceControl &= ~_BIT7)

//--------------------------------------------------
// Macro of DDCCI Function On/Off flag
//--------------------------------------------------
#define GET_DDCCI_STATUS()                      ((bit)(stSystemData.MonitorFlag & _BIT6))
#define SET_DDCCI_STATUS()                      (stSystemData.MonitorFlag |= _BIT6)
#define CLR_DDCCI_STATUS()                      (stSystemData.MonitorFlag &= ~_BIT6)

#if(_NON_LINEAR_SCALING_FUCTION == _ON)
//--------------------------------------------------
// Macro of _NON_LINEAR_SCALING Function On/Off flag
//--------------------------------------------------
#define GET_NON_LINEAR_SCALING_STATUS()         ((bit)(stSystemData.MonitorFlag & _BIT2))
#define SET_NON_LINEAR_SCALING_STATUS()         (stSystemData.MonitorFlag |= _BIT2)
#define CLR_NON_LINEAR_SCALING_STATUS()         (stSystemData.MonitorFlag &= ~_BIT2)
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
//--------------------------------------------------
// Macro of Aspect Ratio fuction
//--------------------------------------------------
#define DISP_FULL_SCREEN                        0   // Full screen display
#define DISP_ORIGINAL_SIZE                      1   // Original size display
#define DISP_FIXED_AR_IN                        2   // Fixed-aspect-ratio display (all image inside screen)

#define GET_DISP_RATIO()                        ((stSystemData.MonitorFlag & (_BIT5 | _BIT4)) >> 4)
#define SET_DISP_RATIO(x)                       (stSystemData.MonitorFlag = ((stSystemData.MonitorFlag & ~(_BIT5 | _BIT4)) | (x << 4)))
#endif

#if(_OSD_ROTATE_FUCTION == _ON)
//--------------------------------------------------
// Macro of Rotate Function On/Off flag
//--------------------------------------------------
#define GET_ROTATE_STATUS()                     ((bit)(stSystemData.MonitorFlag & _BIT3))
#define SET_ROTATE_STATUS()                     (stSystemData.MonitorFlag |= _BIT3)
#define CLR_ROTATE_STATUS()                     (stSystemData.MonitorFlag &= ~_BIT3)
#endif

#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
//--------------------------------------------------
// Macro of Function On/Off flag
//--------------------------------------------------
#define GET_SOURCE_OSD_STATUS()                     ((bit)(stSystemData.MonitorFlag & _BIT1))
#define SET_SOURCE_OSD_STATUS()                     (stSystemData.MonitorFlag |= _BIT1)
#define CLR_SOURCE_OSD_STATUS()                     (stSystemData.MonitorFlag &= ~_BIT1)
#endif

//--------------------------------------------------
// Macro of Color Temperature
//--------------------------------------------------

#define GET_COLOR_TEMP_TYPE()                   (stOsdUserData.ColorTemp & (_BIT3 | _BIT2 | _BIT1 | _BIT0))
#define SET_COLOR_TEMP_TYPE(x)                  (stOsdUserData.ColorTemp = ((stOsdUserData.ColorTemp & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | x))


// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.

// V016 VGA Patch Note (5) 20100803 Modify Start
// Patch Reason : Modify for mistake as _COLOR_FORMAT_CONVERT == _OFF.
/*
#if(_COLOR_FORMAT_CONVERT == _ON)
*/
// V016 VGA Patch Note (5) 20100803 Modify End

//--------------------------------------------------
// Macro of Color Format Convert
//--------------------------------------------------
#define GET_COLOR_FORMAT_STATUS()               ((bit)(stSystemData.ColorSetting & (_BIT0 << GET_INPUTSOURCE_TYPE())))   // 0 -> RGB, 1 -> YUV
#define SET_COLOR_FORMAT_STATUS(x)              (stSystemData.ColorSetting = ((stSystemData.ColorSetting & ~((_BIT0 << GET_INPUTSOURCE_TYPE()))) | (x << GET_INPUTSOURCE_TYPE())))

// V016 VGA Patch Note (5) 20100803 Modify Start
// Patch Reason : Modify for mistake as _COLOR_FORMAT_CONVERT == _OFF.
/*
#endif
*/
// V016 VGA Patch Note (5) 20100803 Modify End

// V012 Modify 20100304 End

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Macro of Overscan Status
//--------------------------------------------------
#define GET_OVERSCAN_STATUS()                   ((bit)(g_ucOverScanFlag & _BIT0))
#define SET_OVERSCAN_STATUS()                   (g_ucOverScanFlag |= _BIT0)
#define CLR_OVERSCAN_STATUS()                   (g_ucOverScanFlag &= ~_BIT0)

//--------------------------------------------------
// Macro of Overscan Capture BackUp Value
//--------------------------------------------------
#define GET_OVERSCAN_CAPTURE_BACKUP_VALUE()     ((bit)(g_ucOverScanFlag & _BIT1))
#define SET_OVERSCAN_CAPTURE_BACKUP_VALUE()     (g_ucOverScanFlag |= _BIT1)
#define CLR_OVERSCAN_CAPTURE_BACKUP_VALUE()     (g_ucOverScanFlag &= ~_BIT1)

//--------------------------------------------------
// Macro of Overscan Success  Status
//--------------------------------------------------
#define GET_OVERSCAN_SUCCESS_STATUS()           ((bit)(g_ucOverScanFlag & _BIT2))
#define SET_OVERSCAN_SUCCESS_STATUS()           (g_ucOverScanFlag |= _BIT2)
#define CLR_OVERSCAN_SUCCESS_STATUS()           (g_ucOverScanFlag &= ~_BIT2)

//--------------------------------------------------
// Macro of Overscan IV2DVDelay BackUp Value
//--------------------------------------------------
#define GET_OVERSCAN_IV2DVDELAY_BACKUP_VALUE()  ((bit)(g_ucOverScanFlag & _BIT3))
#define SET_OVERSCAN_IV2DVDELAY_BACKUP_VALUE()  (g_ucOverScanFlag |= _BIT3)
#define CLR_OVERSCAN_IV2DVDELAY_BACKUP_VALUE()  (g_ucOverScanFlag &= ~_BIT3)

#endif
// V012 Modify 20100316 End
