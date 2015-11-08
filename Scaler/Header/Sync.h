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
// ID Code      : Sync.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------
#if(_DVI_DE_ONLY_SUPPORT == _ON)
#define _DVI_DE_SUPPORT_ON                      1
#define _DVI_DE_SUPPORT_OFF                     0
#endif

#if(_TMDS_SUPPORT == _ON)
#define _TMDS_Freq_Right_Count                  25

#define _TMDS_Freq_SLEEP_Right_Count            25 //SLEEP_Right_Count= 15 -> ~52ms

#endif

// V015 VGA Patch Note (3) Modify 20100611 Start
// Patch Reason : Solve SOG mistaken when enter white pattern in separate signal.
#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _MAX_VSYNC_HIGH_PERIOD                  12 // Unit capture window
#endif
// V015 VGA Patch Note (3) Modify 20100611 End

//----------------------------------------------------------------------------------------------------

#ifdef __SYNC__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
bit idata g_bHDMISearchTimesResetFlag = 0;
bit idata g_bHDMIHDCPFlag = 0;
WORD xdata g_usTMDSFreq = 0;
BYTE xdata g_ucFormerSearchPort = 0;
WORD xdata g_usTMDSFreq0 = 0;
WORD xdata g_usTMDSFreq1 = 0;
WORD xdata g_usDVITMDSFreq = 0;
bit idata g_bNoResetPhyFlag = 0;
BYTE xdata g_ucIDCode = 0;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
bit CSyncScanInputPortDVI(void);
void CSyncModeSetPhy(void);

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))
WORD CSyncMeasurePhyFreq(bit bFlag);
bit CSyncPhyFreqForRightCount(BYTE ucCountNum, BYTE ucDelayTime);
void CSyncPhyZ0PowerOff(void);
bit CSyncCheckTMDSFreq(void);
#endif

bit CSyncTMDSWakeUpDetect(void);
void CSyncInputPort2DInitial(void);
void CSyncInputPort2DSwitch(void);
#endif  // End of #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))


#if(_DP_SUPPORT == _ON)
bit CSyncScanInputPortDP(void);
#endif

// V013 VGA Patch Note (9) Modify 20100414 Start
// Patch Reason : Add Checking Stable Signal mechanism for VGA Signal.
bit CSyncCheckVGAIsStable(void);
// V013 VGA Patch Note (9) Modify 20100414 End

bit CSyncScanInputPortVGA(void);

#if(_HSYNC_DETECTION == _AUTO_RUN)

// V013 VGA Patch Note (22) Modify 20100511 Start
// Patch Reason : Modify Capture Window Size for HEORV/OR Sync Types
void CSyncSetCaptureWindowfForHEORV(void);
// V013 VGA Patch Note (22) Modify 20100511 End

BYTE CSyncGetSyncTypeAutoRun(void);
#else
BYTE CSyncGetSyncTypeNormalRun(BYTE ucSourceSel);
#endif

void CSyncModifyPolarity(void);
BYTE CSyncDistinguishSogSoy(void);

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern bit idata g_bHDMISearchTimesResetFlag;
extern bit idata g_bHDMIHDCPFlag;
extern WORD xdata g_usTMDSFreq;
extern BYTE xdata g_ucFormerSearchPort;
extern WORD xdata g_usTMDSFreq0;
extern WORD xdata g_usTMDSFreq1;
extern WORD xdata g_usDVITMDSFreq;
extern bit idata g_bNoResetPhyFlag;
extern BYTE xdata g_ucIDCode;

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
extern bit CSyncScanInputPortDVI(void);
#endif

// V013 VGA Patch Note (9) Modify 20100414 Start
// Patch Reason : Add Checking Stable Signal mechanism for VGA Signal.
extern bit CSyncCheckVGAIsStable(void);
// V013 VGA Patch Note (9) Modify 20100414 End

extern bit CSyncScanInputPortVGA(void);
extern void CSyncModifyPolarity(void);
extern bit CSyncCheckTMDSFreq(void);
extern bit CSyncTMDSWakeUpDetect(void);
extern void CSyncInputPort2DInitial(void);
extern void CSyncInputPort2DSwitch(void);

#if(_DP_SUPPORT == _ON)
extern bit CSyncScanInputPortDP(void);
#endif

extern BYTE CSyncDistinguishSogSoy(void);

#endif // End of #ifdef __SYNC__

//----------------------------------------------------------------------------------------------------
