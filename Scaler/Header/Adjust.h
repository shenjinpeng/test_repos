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
// ID Code      : Adjust.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Digital Filter
//--------------------------------------------------
#define _DISABLE_PORT                   0
#define _PHASE_ACCESS_PORT              1
#define _NEG_SMEAR_ACCESS_PORT          2
#define _POS_SMEAR_ACCESS_PORT          3
#define _NEG_RING_ACCESS_PORT           4
#define _POS_RING_ACCESS_PORT           5
#define _MISMATCH_ACCESS_PORT           6
#define _YPBPR_ACCESS_PORT              7
#define _NOISE_REDUCTION_PORT           8

#define _YPBPR_DISABLE                  0
#define _YPBPR_ENABLE                   7

#define _FUNCTION_DISABLE               0
#define _FUNCTION_ENABLE                1

#define _PHASE_THD_0                    0
#define _PHASE_THD_1                    1
#define _PHASE_THD_2                    2
#define _PHASE_THD_3                    3
#define _PHASE_THD_4                    4
#define _PHASE_THD_5                    5
#define _PHASE_THD_6                    6
#define _PHASE_THD_7                    7

#define _SMEAR_RING_THD_0               0
#define _SMEAR_RING_THD_1               1
#define _SMEAR_RING_THD_2               2
#define _SMEAR_RING_THD_3               3
#define _SMEAR_RING_THD_4               4
#define _SMEAR_RING_THD_5               5
#define _SMEAR_RING_THD_6               6
#define _SMEAR_RING_THD_7               7

#define _MISMATCH_THD_0                 0
#define _MISMATCH_THD_1                 1

#define _NOISE_REDUCTION_THD_0          0
#define _NOISE_REDUCTION_THD_1          1
#define _NOISE_REDUCTION_THD_2          2
#define _NOISE_REDUCTION_THD_3          3
#define _NOISE_REDUCTION_THD_4          4
#define _NOISE_REDUCTION_THD_5          5
#define _NOISE_REDUCTION_THD_6          6
#define _NOISE_REDUCTION_THD_7          7

#define _DIV_VALUE_0                    0
#define _DIV_VALUE_1                    1
#define _DIV_VALUE_2                    2
#define _DIV_VALUE_3                    3


//--------------------------------------------------
// Definitions of Coring Type
//--------------------------------------------------
#define _CORING_MIN                     3   // (0~5)
#define _CORING_MAX_POS                 50  // (50~60)
#define _CORING_MAX_NEG                 -50 // (-50~-60)


//--------------------------------------------------
// Definitions of Gamma Table Type
//--------------------------------------------------
#define _COMPACT_GAMMA_NORMAL_TABLE     0
#define _FULL_GAMMA_NORMAL_TABLE        1
#define _COMPACT_GAMMA_COMPRESS_TABLE   2
#define _FULL_GAMMA_COMPRESS_TABLE      3


//--------------------------------------------------
// Definitions of Dithering Type
//--------------------------------------------------
#define _INPUT_DITHER                   0
#define _OUTPUT_DITHER                  1


//--------------------------------------------------
// Definitions of TMDS Measurement
//--------------------------------------------------
#define _TMDS_MEASURE_HSYNC_BE          0x00
#define _TMDS_MEASURE_HSYNC_AF          0x01
#define _TMDS_MEASURE_DE_BE             0x02
#define _TMDS_MEASURE_DE_AF             0x03

#define _TMDS_MEASURE_AVE               0x00
#define _TMDS_MEASURE_MAX               0x01
#define _TMDS_MEASURE_MIN               0x02

#define _MEASURE_HSYNC                  0
#define _MEASURE_DE                     1


//--------------------------------------------------
// Definations of Watch Dogs
//--------------------------------------------------
#define _WD_DV_TIMEOUT                  0x20
#define _WD_FRAMESYNC                   0x08
#define _WD_IH_IV_ERROR                 0x80
#define _WD_IH_IV_TIMEOUT_OVERFLOW      0x40
#define _WD_DV_TIMEOUT_APLL_NONLOCK     (_WD_DV_TIMEOUT | 0)
#define _WD_FRAMESYNC_APLL_NONLOCK      (0 | _WD_FRAMESYNC)
#define _WD_INPUT_SYNC_ERROR            (_WD_IH_IV_ERROR | _WD_IH_IV_TIMEOUT_OVERFLOW)
#define _WD_ALL                         ((_WD_DV_TIMEOUT | 0 | _WD_FRAMESYNC | _WD_INPUT_SYNC_ERROR) & 0xEF)

//--------------------------------------------------
// Definations of HDMI Watch Dog Control
//--------------------------------------------------
#define _WD_SET_AVMUTE_ENABLE           0x01
#define _WD_AUDIO_FOR_TMDS_CLOCK        0x02
#define _WD_PACKET_VARIATION            0x04
#define _WD_AUDIO_FIFO                  0x08
#define _WD_HDMI_ALL                    (_WD_SET_AVMUTE_ENABLE | _WD_AUDIO_FOR_TMDS_CLOCK | _WD_PACKET_VARIATION | _WD_AUDIO_FIFO)

//--------------------------------------------------
// Definations of APLL _G_VALUE_DIVIDER
//--------------------------------------------------
#define _G_VALUE_DIVIDER_0  4
#define _G_VALUE_DIVIDER_1  16
#define _G_VALUE_DIVIDER_2  64
#define _G_VALUE_DIVIDER_3  128
#define _G_VALUE_DIVIDER_4  256
#define _G_VALUE_DIVIDER_5  512


//--------------------------------------------------
// Definations of Adjust ADC Clock Control
//--------------------------------------------------
#define _APLL_INITIAL                   0
#define _APLL_FAST_LOCK                 1
#define _APLL_SUM_I_READ_COUNT          3


/*
//--------------------------------------------------
// Definations of HDMI Watch Dog Control Register0
//--------------------------------------------------
#define _WD_SET_AVMUTE_ENABLE               0x80
#define _WD_AUDIO_FOR_AUDIO_CODING_TYPE     0x10
#define _WD_AUDIO_PLL_NONLOCK_AV            0x08
#define _WD_AUDIO_FOR_AUDIO_FIFO_OVERFLOW   0x04
#define _WD_AUDIO_FOR_AUDIO_FIFO_UNDERFLOW  0x02
#define _WD_HDMI_CR0_ALL                    (_WD_SET_AVMUTE_ENABLE | _WD_AUDIO_FOR_AUDIO_CODING_TYPE | _WD_AUDIO_PLL_NONLOCK_AV | _WD_AUDIO_FOR_AUDIO_FIFO_OVERFLOW | _WD_AUDIO_FOR_AUDIO_FIFO_UNDERFLOW)

//--------------------------------------------------
// Definations of HDMI Watch Dog Control Register1
//--------------------------------------------------
#define _WD_AUDIO_FOR_TMDS_CLOCK            0x80
#define _WD_AUDIO_FOR_LAYOUT_FIELD          0x40
#define _WD_AUDIO_FOR_VIDEO_CLOCK           0x20
#define _WD_VIDEO_FOR_AUDIO_CODING_TYPE     0x10
#define _WD_HDMI_CR1_ALL                    (_WD_AUDIO_FOR_TMDS_CLOCK | _WD_AUDIO_FOR_LAYOUT_FIELD | _WD_AUDIO_FOR_VIDEO_CLOCK | _WD_VIDEO_FOR_AUDIO_CODING_TYPE)

//--------------------------------------------------
// Definations of HDMI Watch Dog Control Register2
//--------------------------------------------------
#define _WD_AUDIO_PLL_NONLOCK_FOR_VIDEO     0x80
#define _WD_VIDEO_FOR_LAYOUT_FIELD          0x40
#define _WD_VIDEO_FOR_AUDIO_FIFO_OVERFLOW   0x20
#define _WD_VIDEO_FOR_AUDIO_FIFO_UNDERFLOW  0x10
#define _WD_HDMI_CR2_ALL                    (_WD_AUDIO_PLL_NONLOCK_FOR_VIDEO | _WD_VIDEO_FOR_LAYOUT_FIELD | _WD_AUDIO_PLL_NONLOCK | _WD_VIDEO_FOR_AUDIO_FIFO_OVERFLOW | _WD_VIDEO_FOR_AUDIO_FIFO_UNDERFLOW)
*/

//--------------------------------------------------
// Definations of Adjust ADC Clamp Tolerance, double pixel
//--------------------------------------------------
#define _ADC_CLAMP_DISTANCE_TOLERANCE   5
#define _ADC_CLAMP_MIN_WIDTH            4
#define _ADC_CLAMP_START_DEFAULT        0x04
#define _ADC_CLAMP_END_DEFAULT          0x10

//--------------------------------------------------
// Definations of V Sync Pulse Width Compensate, APLL Stable Count
//--------------------------------------------------
#define _V_SYNC_PULSE_WIDTH_COMPENSATE  1
#define _ADJUST_APLL_STABLE_COUNT       2


#ifdef __ADJUST__


//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE xdata ucAdjustCtrl = 0;
WORD xdata usPEValue = 120;
bit  idata g_bAutoPositionH = 0;

WORD xdata g_ulPllIHTotal = 0;
DWORD xdata g_ulPllDivider = 0;
SWORD xdata sAdjustHue = 0;
SWORD xdata sAdjustSat = 0;

WORD xdata g_usVTotalTemp = 0;
BYTE xdata g_ucVSyncPulseWidthTemp = 0;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------

bit CAdjustAdcClock(WORD usClock);
bit CAdjustAPLLInitial(WORD usClock);
bit CAdjustAPLLInitial_2(WORD usClock);
bit CAdjustAPLLFastLock(WORD usClock);
BYTE CAdjustGetAPLLGValue(WORD *pDelta);

void CAdjustIHSDelay(WORD usIHSDelay);
void CAdjustIVSDelay(WORD usIVSDelay);
void CAdjustDclkOffset(WORD usDclkOffset);
void CAdjustDclkSpreadSpectrumRange(BYTE ucSpreadRange);
//for MCLK Offset & Spread Spectrum Range
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
void CAdjustMclkOffset(WORD usMclkOffset);
void CAdjustMclkSpreadSpectrumRange(BYTE ucSpreadRange);
void CAdjustSdramPhase(BYTE *pSdramPhaseTable);
void CAdjustOdFrcPerformance(void);
#endif
void CAdjustSyncProcessorMeasureStart(void);
void CAdjustTMDSErrorCorrectionOn(void);
void CAdjustTMDSErrorCorrectionOff(void);

void CAdjustSetDigitalCapture(void);
void CAdjustTMDSCaptureCheck(void);
void CAdjustEnableWatchDog(BYTE ucPar);
void CAdjustDisableWatchDog(BYTE ucPar);
void CAdjustEnableHDMIWatchDog(BYTE ucPar);
void CAdjustDisableHDMIWatchDog(BYTE ucPar);

void CAdjustSRGB(void);

#if(_HDCP_SUPPORT == _ON)
void CAdjustHDCP(void);
#endif

#if(_GAMMA_FUNCTION == _ON)
#if(_SCALER_TYPE == _RTD2472D)
void CAdjustGamma(BYTE ucGammaTableType, BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB);

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
//void CAdjustGamma(BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB);//20080422 -Sharon
void CAdjustLUTGamma(BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB); //20080422 +Sharon

#else
    No Setting !!

#endif // End of #if(_SCALER_TYPE == _RTD2472D)
#endif // End of #if(_GAMMA_FUNCTION == _ON)

#if(_SCALER_TYPE == _RTD2472D)
void CAdjustDither(BYTE *pDitherSeqTable, BYTE * pDitherTable, BYTE *pDitherTempoffsetTable);//Hudson V008_20080806

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
void CAdjustDither(BYTE *pDitherSeqTable, BYTE * pDitherTable, BYTE *pDitherTempoffsetTable, bit bDitherType);//Hudson V008_20080806

#else
    No Setting !!

#endif

void CAdjustSharpness(BYTE ucSharpness);
void CAdjustSetSharpnessTable(bit scaling, BYTE *pArray0, BYTE *pArray1);
void CAdjustBrightness(BYTE ucBrightness);
void CAdjustContrast(BYTE ucContrast);
void CAdjustBacklight(WORD ucBacklight);

void CAdjustAdcGain(void);
void CAdjustAdcOffset(void);
void CAdjustAdcGainLsb(void);
void CAdjustAdcOffsetLsb(void);
void CAdjustAdcGainOffset(void);

void CAdjustBackgroundColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
void CAdjustColorPalette(BYTE *pColorPaletteArray);
BYTE CAdjustIVS2DVSDelay(BYTE ucOption);
void CAdjustPLL(bit ucSelection, DWORD ulFreq);
void CAdjustUpdateCenterData(void);
bit CAdjustCheckAdcClockRange(WORD usClock, WORD *delta);

void CAdjustPhase(BYTE ucPhase);
void CAdjustHPosition(void);
void CAdjustVPosition(void);

// V013 VGA Patch Note (7) Modify 20100412 Start
// Patch Reason : Adjust Coast Region.
void CAdjustCoastRegion(void);
// V013 VGA Patch Note (7) Modify 20100412 End

void CAdjustADCSetting(void);
void CAdjustDigitalFilter(BYTE ucAccess, BYTE ucOffset, BYTE ucDiv, BYTE ucEnable);

#if((_VIVID_COLOR_FUCTION == _ON) || (_DCR_MODE == _DCR_TYPE_3))
void CAdjustNormalizeFactor(WORD usHWidth, WORD usVHeight);
#endif

#if(_VIVID_COLOR_FUCTION == _ON)
void CAdjustHLWindowHV(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
void CAdjustHLWindowHVBorder(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
void CAdjustHLWindowBrightness(BYTE ucSelect, BYTE ucValue);
void CAdjustHLWindowContrast(BYTE ucSelect, BYTE ucValue);
void CAdjustEnableHLWindow(BYTE ucSelect);
void CAdjustFillDCCTable(BYTE ucNum);
void CAdjustEnableDCC(BYTE ucSelect);
void CAdjustFillICMTable(BYTE ucNum);
void CAdjustEnableICM(BYTE ucSelect);

int CAdjustColorGammaCal(BYTE ucSat, BYTE n);
void CAdjustHueSatSet(BYTE ucSat, BYTE color, SWORD TempU1, SWORD TempU2, SWORD TempV1, SWORD TempV2);
void CAdjustVividComboHueSat(BYTE ucSat, BYTE ucHue, SWORD sTempU1, SWORD sTempV1, SWORD sConst0, SWORD sConst1, SWORD sConst2, SWORD sConst3, BYTE ucPar);
void CAdjustVividHueSat(BYTE ucColor, BYTE ucHue, BYTE ucSat);
#endif // End of #if(_VIVID_COLOR_FUCTION == _ON)

#if(_HDMI_SUPPORT == _ON)
void CAdjustDeepColorMode(void);
#endif

#if(_AUDIO_SUPPORT == _ON)
void CAdjustVolume(BYTE ucVolume);
void CAdjustAudioControl(bit ucSelect);

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
void CAdjustDisableAudio(void);
#endif

#endif

#if(_OD_SUPPORT == _ON)
void CAdjustODeltaGain(BYTE ucValue);
#endif
#if(_SRGB_COLOR_ENHANCE == _ON)
void CAdjustSaturationHue(BYTE  ucValue, bit bSaturationIndex);
SWORD CAdjustCosine(SWORD fDegree);
SWORD CAdjustSine(SWORD fDegree);
void CAdjustMatrixMultiply(SWORD (*arrayA)[3], SWORD (*arrayB)[3], SWORD (*arrayC)[3]);
void CAdjustSetYpbprRhue(void);
void CAdjustSetYpbprGhue(void);
void CAdjustSetYpbprBhue(void);
#endif

#if(_EMBEDDED_HDCP_KEY == _ON)
void CAdjustWriteHDCPKey(BYTE ucAddr, WORD usLength, bit bAutoInc);

// V016 System Patch Note (26) Modify 20100831 Start
// Patch Reason : Extend HDCP KEY Length to 325Byte including CTRL Key
void CAdjustWriteHDCPCtrl(void);
// V016 System Patch Note (26) Modify 20100831 End

#endif

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
#if((_EMBEDDED_HDCP_KEY == _ON) && (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH) && (_MEMORY_LOCATION == _FLASH))
void CAdjustGetDefaultHDCPKeyDatafromTable(void);
#endif

#if((_GAMMA_FUNCTION == _ON) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH) && (_MEMORY_LOCATION == _FLASH))
void CAdjustGetDefaultLUTTableDatafromTable(void);
#endif
// V015 System Patch Note (7) Modify 20100630 End

bit CAdjustADCClamp(void);

void CAdjustDcRestore(void);


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE xdata ucAdjustCtrl;
extern WORD xdata usPEValue;
extern bit idata g_bAutoPositionH;

extern DWORD xdata g_ulPllDivider;
extern WORD xdata g_ulPllIHTotal;
extern SWORD xdata sAdjustHue;
extern SWORD xdata sAdjustSat;

extern WORD xdata g_usVTotalTemp;
extern BYTE xdata g_ucVSyncPulseWidthTemp;

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------

extern bit CAdjustAdcClock(WORD usClock);
extern bit CAdjustAPLLInitial(WORD usClock);
extern bit CAdjustAPLLInitial_2(WORD usClock);
extern bit CAdjustAPLLFastLock(WORD usClock);

extern void CAdjustIHSDelay(WORD usIHSDelay);
extern void CAdjustIVSDelay(WORD usIVSDelay);
extern void CAdjustDclkOffset(WORD usDclkOffset);
extern void CAdjustDclkSpreadSpectrumRange(BYTE ucSpreadRange);

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
extern void CAdjustMclkOffset(WORD usMclkOffset);
extern void CAdjustMclkSpreadSpectrumRange(BYTE ucSpreadRange);
extern void CAdjustSdramPhase(BYTE *pSdramPhaseTable);
extern void CAdjustOdFrcPerformance(void);
#endif

extern void CAdjustSyncProcessorMeasureStart(void);
extern void CAdjustTMDSErrorCorrectionOn(void);
extern void CAdjustTMDSErrorCorrectionOff(void);

extern void CAdjustSetDigitalCapture(void);
extern void CAdjustTMDSCaptureCheck(void);
extern void CAdjustEnableWatchDog(BYTE ucPar);
extern void CAdjustDisableWatchDog(BYTE ucPar);
extern void CAdjustEnableHDMIWatchDog(BYTE ucPar);
extern void CAdjustDisableHDMIWatchDog(BYTE ucPar);

extern void CAdjustHDCP(void);
extern void CAdjustSRGB(void);

#if(_GAMMA_FUNCTION == _ON)
#if(_SCALER_TYPE == _RTD2472D)
extern void CAdjustGamma(BYTE ucGammaTableType, BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB);

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
//extern void CAdjustGamma(BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB); //20080422 -Sharon
extern void CAdjustLUTGamma(BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB); //20080422 +Sharon

#else
    No Setting !!

#endif // End of #if(_SCALER_TYPE == _RTD2472D)
#endif // End of #if(_GAMMA_FUNCTION == _ON)

#if(_SCALER_TYPE == _RTD2472D)
extern void CAdjustDither(BYTE  *pDitherSeqTable, BYTE * pDitherTable, BYTE *pDitherTempoffsetTable);//Hudson V008_20080806

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
extern void CAdjustDither(BYTE *pDitherSeqTable, BYTE * pDitherTable, BYTE *pDitherTempoffsetTable, bit bDitherType);//Hudson V008_20080806

#else
    No Setting !!

#endif

extern void CAdjustSharpness(BYTE ucSharpness);
extern void CAdjustSetSharpnessTable(bit scaling, BYTE *pArray0, BYTE *pArray1);
extern void CAdjustBrightness(BYTE ucBrightness);
extern void CAdjustContrast(BYTE ucContrast);
extern void CAdjustBacklight(WORD ucBacklight);

extern void CAdjustAdcGain(void);
extern void CAdjustAdcOffset(void);
extern void CAdjustAdcGainLsb(void);
extern void CAdjustAdcOffsetLsb(void);
extern void CAdjustAdcGainOffset(void);

extern void CAdjustBackgroundColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
extern void CAdjustColorPalette(BYTE *pColorPaletteArray);
extern BYTE CAdjustIVS2DVSDelay(BYTE ucOption);
extern void CAdjustPLL(bit ucSelection, DWORD ulFreq);
extern void CAdjustUpdateCenterData(void);
extern bit CAdjustCheckAdcClockRange(WORD usClock, WORD *delta);

extern void CAdjustPhase(BYTE ucPhase);
extern void CAdjustHPosition(void);
extern void CAdjustVPosition(void);

// V013 VGA Patch Note (7) Modify 20100412 Start
// Patch Reason : Adjust Coast Region.
extern void CAdjustCoastRegion(void);
// V013 VGA Patch Note (7) Modify 20100412 End

extern void CAdjustADCSetting(void);
extern void CAdjustDigitalFilter(BYTE ucAccess, BYTE ucOffset, BYTE ucDiv, BYTE ucEnable);

#if((_VIVID_COLOR_FUCTION == _ON) || (_DCR_MODE == _DCR_TYPE_3))
extern void CAdjustNormalizeFactor(WORD usHWidth, WORD usVHeight);
#endif

#if(_VIVID_COLOR_FUCTION == _ON)
extern void CAdjustHLWindowHV(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
extern void CAdjustHLWindowHVBorder(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
extern void CAdjustHLWindowBrightness(BYTE ucSelect, BYTE ucValue);
extern void CAdjustHLWindowContrast(BYTE ucSelect, BYTE ucValue);
extern void CAdjustEnableHLWindow(BYTE ucSelect);
extern void CAdjustFillDCCTable(BYTE ucNum);
extern void CAdjustEnableDCC(BYTE ucSelect);
extern void CAdjustFillICMTable(BYTE ucNum);
extern void CAdjustEnableICM(BYTE ucSelect);
extern int CAdjustColorGammaCal(BYTE ucSat, BYTE n);
extern void CAdjustHueSatSet(BYTE ucSat, BYTE color, SWORD TempU1, SWORD TempU2, SWORD TempV1, SWORD TempV2);
extern void CAdjustVividComboHueSat(BYTE ucSat, BYTE ucHue, SWORD sTempU1, SWORD sTempV1, SWORD sConst0, SWORD sConst1, SWORD sConst2, SWORD sConst3, BYTE ucPar);
extern void CAdjustVividHueSat(BYTE ucColor, BYTE ucHue, BYTE ucSat);
#endif // End of #if(_VIVID_COLOR_FUCTION == _ON)

#if(_HDMI_SUPPORT == _ON)
extern void CAdjustDeepColorMode(void);
#endif

#if(_AUDIO_SUPPORT == _ON)
extern void CAdjustVolume(BYTE ucVolume);
extern void CAdjustAudioControl(bit ucSelect);

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
extern void CAdjustDisableAudio(void);
#endif

#endif

#if(_OD_SUPPORT == _ON)
extern void CAdjustODeltaGain(BYTE ucValue);
#endif

#if(_SRGB_COLOR_ENHANCE == _ON)
extern void CAdjustSaturationHue(BYTE  ucValue, bit bSaturationIndex);
#endif//_SRGB_COLOR_ENHANCE

#if(_EMBEDDED_HDCP_KEY == _ON)
extern void CAdjustWriteHDCPKey(BYTE ucAddr, WORD usLength, bit bAutoInc);

// V016 System Patch Note (26) Modify 20100831 Start
// Patch Reason : Extend HDCP KEY Length to 325Byte including CTRL Key
extern void CAdjustWriteHDCPCtrl(void);
// V016 System Patch Note (26) Modify 20100831 End

#endif

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
#if((_EMBEDDED_HDCP_KEY == _ON) && (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH) && (_MEMORY_LOCATION == _FLASH))
extern void CAdjustGetDefaultHDCPKeyDatafromTable(void);
#endif

#if((_GAMMA_FUNCTION == _ON) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH) && (_MEMORY_LOCATION == _FLASH))
extern void CAdjustGetDefaultLUTTableDatafromTable(void);
#endif
// V015 System Patch Note (7) Modify 20100630 End

extern bit CAdjustADCClamp(void);
extern void CAdjustDcRestore(void);

#endif // End of #ifdef __ADJUST__


//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Start Display
//--------------------------------------------------
#define GET_FIRST_ADCCLOCK()        ((bit)(ucAdjustCtrl & _BIT0))
#define SET_FIRST_ADCCLOCK()        (ucAdjustCtrl |= _BIT0)
#define CLR_FIRST_ADCCLOCK()        (ucAdjustCtrl &= ~_BIT0)


//--------------------------------------------------
// Macro of Mode Search Type
//--------------------------------------------------
#define GET_MODE_SEARCH_TYPE()      ((bit)(ucAdjustCtrl & _BIT1))
#define SET_MODE_SEARCH_TYPE(x)     (ucAdjustCtrl = ((ucAdjustCtrl & ~(_BIT1)) | (x << 1)))


//--------------------------------------------------
// Macro of DVI Use Transition Result Flag
//--------------------------------------------------
#define GET_USE_TRANSITION_RESULT() ((bit)(ucAdjustCtrl & _BIT2))
#define SET_USE_TRANSITION_RESULT() (ucAdjustCtrl |= _BIT2)
#define CLR_USE_TRANSITION_RESULT() (ucAdjustCtrl &= ~_BIT2)

// V012 Modify 20100324 Start
// V012 Patch Note (18) : Fix the sync processor unlock issue which causes APLL setting fail.
//--------------------------------------------------
// Macro of APLL Process Flag
//--------------------------------------------------
#define GET_APLL_PROCESS()          ((bit)(ucAdjustCtrl & _BIT3))
#define SET_APLL_PROCESS()          (ucAdjustCtrl |= _BIT3)
#define CLR_APLL_PROCESS()          (ucAdjustCtrl &= ~_BIT3)
// V012 Modify 20100324 End

/////////////gamma///////////
//******************************************************************************
//#if(_GAMMA_FUNCTION == _ON)
#if(_SCALER_TYPE == _RTD2472D)
void RTD_WriteGamma(BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB);
void UpdateGammaBlock(BYTE gamma);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
//void CAdjustGamma(BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB);//20080422 -Sharon
void CAdjustLUTGamma(BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB); //20080422 +Sharon

#else
    No Setting !!

#endif // End of #if(_SCALER_TYPE == _RTD2472D)
//#endif // End of #if(_GAMMA_FUNCTION == _ON)




//#if(_GAMMA_FUNCTION == _ON)
#if(_SCALER_TYPE == _RTD2472D)
extern void Write_LUTtable(BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB);
extern void Adjust_LUTtable(BYTE gamma);
extern void LSHandler();//sjp20110623

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
//extern void CAdjustGamma(BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB); //20080422 -Sharon
extern void CAdjustLUTGamma(BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB); //20080422 +Sharon

#else
    No Setting !!

#endif // End of #if(_SCALER_TYPE == _RTD2472D)
//#endif // End of #if(_GAMMA_FUNCTION == _ON)

//--------------------------------------------------

extern BYTE cCurGamma;

extern BYTE cCurModule;




