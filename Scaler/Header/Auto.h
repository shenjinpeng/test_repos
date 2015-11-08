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
// ID Code      : Auto.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Minumum Noise Margin
//--------------------------------------------------
#define _MIN_NOISE_MARGIN               0x40

//--------------------------------------------------
// Set Adjusting Hsync Boundary Range (%) by the porch length
//--------------------------------------------------
#define _H_BOUND_RANGE_R                50

//--------------------------------------------------
// Set Clock Non-adjusting Range (%) by the active region
//--------------------------------------------------
// V013 VGA Patch Note (13) Modify 20100420 Start
// Patch Reason : Change clock range a little bit to pass SQE's verification.
/*
#define _AUTO_CLOCK_RANGE               94
*/
#define _AUTO_CLOCK_RANGE               95
// V013 VGA Patch Note (13) Modify 20100420 End

//--------------------------------------------------
// Set Center Position Non-adjusting Range (%) by IHWidth
//--------------------------------------------------
#define _AUTO_POSITION_CENTER_H_RANGE   85

//--------------------------------------------------
// Set Center Position Non-adjusting Range (%) by IVHeight
//--------------------------------------------------
#define _AUTO_POSITION_CENTER_V_RANGE   50

#if(_AUTO_CLOCK_RANGE <= _AUTO_POSITION_CENTER_H_RANGE)
    #error _AUTO_CLOCK_RANGE should > _AUTO_POSITION_CENTER_H_RANGE !
#endif

//--------------------------------------------------
// Active Region Percentage Threshold (%)
//--------------------------------------------------
#define _ACTIVE_REGION_PERCENTAGE_THD   ((100 - _AUTO_CLOCK_RANGE) / 2)

//--------------------------------------------------
// Definition of max auto faulure count
//--------------------------------------------------
#define _MAX_AUTO_FAIL_COUNT            3

#if((_MAX_AUTO_FAIL_COUNT > 3) || (_MAX_AUTO_FAIL_COUNT < 1))
#error Max Auto Fail Count should between [1, 3]!
#endif

// V012 Modify 20100323 Start
// V012 Patch Note (5) : Auto function modifications.
//--------------------------------------------------
// Definition of the threshold to trigger SOD in auto clock
//--------------------------------------------------
#define _AUTO_CLOCK_SOD_TRIGGER_TRESH   4


//--------------------------------------------------
// Definition of switch of doing auto position the picture is in the active region
//--------------------------------------------------
// This is an optional procedure to do the position for the picture in active region
#define _AUTO_POSITION_FOR_IN_REGION    _OFF
// V012 Modify 20100323 End

//--------------------------------------------------
// Noise width definitions
//--------------------------------------------------
#define _NOISE_WIDTH_AFTER_HSYNC        0x3C
#define _NOISE_WIDTH_BEFORE_HSYNC       0x0A
#define _NOISE_WIDTH_AFTER_VSYNC        0x01

// V013 VGA Patch Note (10) 20100416 Modify Start
// Patch Reason : Support Auto Config For Yuv Color.
//--------------------------------------------------
// Clamp Width Definitions For YUV Auto LBoundary
//--------------------------------------------------
#define _LBOUNDARY_CAL_CLAMP_RATIO      67
// V013 VGA Patch Note (10) 20100416 Modify End

//--------------------------------------------------
// Set IHS Start Bias (Should be less than 200)
//--------------------------------------------------
#define _IHS_START_BIAS                 50


//--------------------------------------------------
// Set IHS Capture Start (Minimum)
//--------------------------------------------------
#define _IHS_CAPTURE_START              4


//--------------------------------------------------
// Color Source Select for Detection
//--------------------------------------------------
#define _COLORS_BLUE                    0x00
#define _COLORS_GREEN                   0x01
#define _COLORS_RED                     0x02
#define _COLORS_ALL                     0x03

#define _COLOR_SELECT                   _COLORS_ALL


//--------------------------------------------------
// Definations of Measure Color
//--------------------------------------------------
#define _MEASURE_COLORS_MIN             0x00
#define _MEASURE_COLORS_MAX             0x01


//--------------------------------------------------
// White Balance Max/Min Level Settings
//--------------------------------------------------
#define _WHITEBALANCE_MAX_LEVEL         250
#define _WHITEBALANCE_MIN_LEVEL         2

// V012 Modify 20100317 Start
// V012 Patch Note (6) : Modify YPbPr ADC setting and auto color.
/*
#define _WHITEBALANCE_BR_MIN_LEVEL      128
*/
#if(_YPBPR_SUPPORT == _ON)
#define _WHITEBALANCE_Y_MAX_LEVEL      235
#define _WHITEBALANCE_Y_MIN_LEVEL      16
#define _WHITEBALANCE_PBPR_MAX_LEVEL   240
#define _WHITEBALANCE_PBPR_MIN_LEVEL   128
#endif

#define _ABL_HSTART_AFTER_CLAMPPOS      4   // ABL HStart after clamp position
// V012 Modify 20100317 End


//--------------------------------------------------
// Setting of Auto Black Level
//--------------------------------------------------
#define _MEASURE_PIXELS_METHOD          0   // (0): Average Value. (1): Minimum Value.
#define _EQUAL_MARGIN                   1   // (0): 0, (1): 1

// V013 VGA Patch Note (1) Modify 20100407 Start
// Patch Reason : Modify ABL Function Equal Condition.
//--------------------------------------------------
// Equal Condition (Off-line mode)
//--------------------------------------------------
#define _EQUAL_UNTIL_MAXCOUNT           0   // To trigger status until measurement achieve Max Frame/Field Count.
#define _EQUAL_ONCE_REARCHTAR           1   // To trigger status once if |Black level - target Value| <= EQ_MGN. (default)
// V013 VGA Patch Note (1) Modify 20100407 End

//--------------------------------------------------
// Gain / Offset default value
//--------------------------------------------------
#define _ADJUST_GAIN_DEFAULT_VALUE      0x80
#define _ADJUST_OFFSET_DEFAULT_VALUE    0x80

//--------------------------------------------------
// Hardware Auto Phase Step
//--------------------------------------------------
#define _HWAUTO_STEP_1                  0x00
#define _HWAUTO_STEP_2                  0x01
#define _HWAUTO_STEP_4                  0x02
#define _HWAUTO_STEP_8                  0x03
#define _HWAUTO_STEP_16                 0x04

#define _HWAUTO_STEP                    _HWAUTO_STEP_2


//--------------------------------------------------
// Auto Clock Precision (Unit in Clock Number)
//--------------------------------------------------
#define _AUTO_CLOCK_PRECISION_1         1
#define _AUTO_CLOCK_PRECISION_2         2
#define _AUTO_CLOCK_PRECISION           _AUTO_CLOCK_PRECISION_1

//--------------------------------------------------
// Definitions of Auto Function
//--------------------------------------------------
#define _ERROR_SUCCESS                  0x00
#define _ERROR_FINISH                   0x40
#define _ERROR_ABORT                    0x80
#define _ERROR_INPUT                    0xff
#define _ERROR_PHASE                    0xfe


//----------------------------------------------------------------------------------------------------


#ifdef __AUTO__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
WORD idata g_usHStartPos = 0;
WORD idata g_usHEndPos = 0;
WORD idata g_usVStartPos = 0;
WORD idata g_usVEndPos = 0;
BYTE idata g_ucAdcPGA = 0;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
BYTE CAutoDoAutoConfig(void);
bit CAutoCheckActiveRegion(void);
BYTE CAutoWaitFinish(void);
BYTE CAutoWaitForIVS(BYTE ucTimes);
BYTE CAutoMeasurePositionH(BYTE ucNoiseMarginH);
BYTE CAutoMeasurePositionV(BYTE ucNoiseMarginV);
DWORD CAutoPhaseSearch(BYTE ucSelColor, BYTE ucSelStep, BYTE ucSelStepNum, BYTE ucSelStepStart, BYTE *ucPhaseResult);
BYTE CAutoReadPhaseInfo(BYTE ucColor);
BYTE CAutoDoAutoClock(void);
BYTE CAutoDoAutoPhase(void);
BYTE CAutoDoAutoPosition(void);
BYTE CAutoDoWhiteBalance(void);
BYTE CAutoTuneBalance(void);
BYTE CAutoMeasureColor(BYTE ucColor, BYTE ucPar, BYTE *pMargin);
BYTE CAutoTuneAdcGain(BYTE ucColor, BYTE *pMargin);
BYTE CAutoTuneAdcOffset(BYTE ucColor, BYTE *pMargin);
BYTE CAutoChangeAdcGain(BYTE ucColor, BYTE ucDelta, BYTE ucInc);
BYTE CAutoChangeAdcOffset(BYTE ucColor, BYTE ucDelta, BYTE ucInc);

#if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW)
BYTE CAutoAdjustAdcOffsetByHW(void);
BYTE CAutoAdjustAdcGainByFW(void);

#endif

bit CAutoCheckClock(WORD usClock);
bit CAutoCheckCaptureStart(WORD usHPos, WORD usClock);
void CAutoFailCountProc(BYTE ucResult);

#else


//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern WORD idata g_usHStartPos;
extern WORD idata g_usHEndPos;
extern WORD idata g_usVStartPos;
extern WORD idata g_usVEndPos;
extern BYTE idata g_ucAdcPGA;

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern BYTE CAutoDoAutoConfig(void);
extern BYTE CAutoDoWhiteBalance(void);

#if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW)
extern BYTE CAutoAdjustAdcOffsetByHW(void);
extern BYTE CAutoAdjustAdcGainByFW(void);

#endif

extern BYTE CAutoMeasurePositionH(BYTE ucNoiseMarginH);
extern BYTE CAutoMeasurePositionV(BYTE ucNoiseMarginV);
extern bit CAutoCheckClock(WORD usClock);
extern bit CAutoCheckCaptureStart(WORD usHPos, WORD usClock);

#endif // End of #ifdef __AUTO__


//----------------------------------------------------------------------------------------------------

#define HWAUTOSTEPNUM(x)                    (x)
#define HWAUTOSTEPSTART(x)                  (x)

//--------------------------------------------------
// Macro for Auto Flag and Auto Fail Count
//--------------------------------------------------
#define CLR_AUTO_FLAG()                     (stModeUserData.FirstAuto = (stModeUserData.FirstAuto & ~_BIT0))
#define SET_AUTO_FLAG()                     (stModeUserData.FirstAuto = ((stModeUserData.FirstAuto & ~_BIT0) | _BIT0))
#define GET_AUTO_FLAG()                     ((bit)(stModeUserData.FirstAuto & _BIT0))

#define CLR_AUTO_FAIL_COUNT()               (stModeUserData.FirstAuto = (stModeUserData.FirstAuto & ~(_BIT7 | _BIT6)))
#define GET_AUTO_FAIL_COUNT()               ((stModeUserData.FirstAuto & (_BIT7 | _BIT6)) >> 6)
#define INC_AUTO_FAIL_COUNT()               (stModeUserData.FirstAuto = ((stModeUserData.FirstAuto & ~(_BIT7 | _BIT6)) | ((GET_AUTO_FAIL_COUNT() + 1) << 6)))

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
#if(_COLOR_FORMAT_CONVERT == _ON)
#define CLR_MODE_COLOR_FORMAT_FLAG()         (stModeUserData.FirstAuto = (stModeUserData.FirstAuto & ~_BIT5))
#define SET_MODE_COLOR_FORMAT_FLAG(x)        (stModeUserData.FirstAuto = ((stModeUserData.FirstAuto & ~_BIT5) | (x << 5))) // x: 0 -> RGB, 1 -> YUV
#define GET_MODE_COLOR_FORMAT_FLAG()         ((bit)(stModeUserData.FirstAuto & _BIT5))
#endif
// V014 VGA Patch Note (6) Modify 20100527 End

