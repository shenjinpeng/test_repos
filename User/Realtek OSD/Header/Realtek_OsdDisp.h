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
// ID Code      : OsdDisp.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------

#ifdef __REALTEK_OSDDISP__
//--------------------------------------------------
// Global Variables
//--------------------------------------------------
void COsdDispInitial(void);
void COsdDispColorProcess(void);
BYTE COsdDispContrastChangeover(BYTE ucSelect, BYTE ucValue);
//BYTE COsdDispBacklightChangeover(BYTE ucValue);


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void COsdDispFirstTimeLoadFont(void);
void COsdDispAutoProc(void);
void COsdDispAutoColorProc(void);
void COsdDispNoSignalProc(void);
void COsdDispNoCableProc(void);
void COsdDispNoSupportProc(void);

void COsdDispFullSlider(BYTE ucRow, BYTE ucCol, BYTE ucLength, WORD usValue, WORD usRange, WORD usMin, BYTE ucColor, BYTE ucNumColor);
void COsdDispClearIcon(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);
void COsdDispClearText(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);
void COsdDispPenPoint(BYTE ucSrcX, BYTE ucSrcY, BYTE ucDesX, BYTE ucDesY, BYTE ucState);
void COsdDispArrowPoint(BYTE ucSrcX, BYTE ucSrcY, BYTE ucDesX, BYTE ucDesY, BYTE ucState);
void COsdDispWindowPoint(BYTE ucRowNum, BYTE ucState);
void COsdDispWindowHPoint(BYTE ucRowNum, BYTE ucStart, BYTE ucInterval, BYTE ucItemNum, BYTE ucThick, BYTE ucState);
void COsdDispDrawInitWindow(void);
void COsdDispLanguageBack(void);
void COsdDispShowFactoryModeValue(void);
void COsdDispAutoProcPrevWork(void);
void COsdDispColorTempSelect(void);
BYTE COsdDispSetWindowPosDisp(BYTE ucSelect, BYTE code *pArray);
void COsdDispOsdTimerEvent(void);


#if(_VIVID_COLOR_FUCTION == _ON)
void COsdDispVividColorHLWindow(void);
void COsdDispVividColorDCCMode(void);
void COsdDispVividColor(void);
#endif

void COsdDispTimingAndInputSource(void);
BYTE COsdDispJudgeSourceType(void);

// V015 VGA Patch Note (12) Modify 20100625 Start
// Patch Reason : Modify OSD Reslotion show type for vedio timing.
bit COsdDispShowResolution(BYTE ucRow, BYTE ucCol, bit bVedioTiming, bit bInterlace);
void COSDDispTimingInfoStyle(void);
// V015 VGA Patch Note (12) Modify 20100625 End

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern void COsdDispInitial(void);
extern void COsdDispColorProcess(void);
extern BYTE COsdDispContrastChangeover(BYTE ucSelect, BYTE ucValue);
//extern BYTE COsdDispBacklightChangeover(BYTE ucValue);


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void COsdDispFirstTimeLoadFont(void);
extern void COsdDispAutoProc(void);
extern void COsdDispAutoColorProc(void);
extern void COsdDispNoSignalProc(void);
extern void COsdDispNoCableProc(void);
extern void COsdDispNoSupportProc(void);

extern void COsdDispFullSlider(BYTE ucRow, BYTE ucCol, BYTE ucLength, WORD usValue, WORD usRange, WORD usMin, BYTE ucColor, BYTE ucNumColor);
extern void COsdDispClearIcon(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);
extern void COsdDispClearText(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);
extern void COsdDispPenPoint(BYTE ucSrcX, BYTE ucSrcY, BYTE ucDesX, BYTE ucDesY, BYTE ucState);
extern void COsdDispArrowPoint(BYTE ucSrcX, BYTE ucSrcY, BYTE ucDesX, BYTE ucDesY, BYTE ucState);
extern void COsdDispWindowPoint(BYTE ucRowNum, BYTE ucState);
extern void COsdDispWindowHPoint(BYTE ucRowNum, BYTE ucStart, BYTE ucInterval, BYTE ucItemNum, BYTE ucThick, BYTE ucState);
extern void COsdDispDrawInitWindow(void);
extern void COsdDispDicomContent(BYTE ucRow, BYTE ucCol, BYTE usValue);
extern void COsdDispGammaContent(BYTE ucRow, BYTE ucCol, BYTE usValue);
extern void COsdDispSignalContent(BYTE ucRow, BYTE ucCol, BYTE usValue);
extern void COsdDisp_YES_NO(BYTE ucRow, BYTE ucCol, BYTE usValue);
extern void COsdDispLanguageBack(void);
extern void COsdDispShowFactoryModeValue(void);
extern void COsdDispAutoProcPrevWork(void);
extern void COsdDispColorTempSelect(void);
extern BYTE COsdDispSetWindowPosDisp(BYTE ucSelect, BYTE code *pArray);
extern void COsdDispOsdTimerEvent(void);

#if(_VIVID_COLOR_FUCTION == _ON)
extern void COsdDispVividColorHLWindow(void);
extern void COsdDispVividColorDCCMode(void);
extern void COsdDispVividColor(void);
#endif

#if (_DDCCI_SUPPORT == _ON)
extern BYTE COsdDispRealToPercent(WORD RealValue, WORD Max, WORD Min);
extern WORD COsdDispPercentToRealValue(BYTE PercentValue, WORD Max, WORD Min);
#endif

extern void COsdDispTimingAndInputSource(void);
extern BYTE COsdDispJudgeSourceType(void);

// V015 VGA Patch Note (12) Modify 20100625 Start
// Patch Reason : Modify OSD Reslotion show type for vedio timing.
extern bit COsdDispShowResolution(BYTE ucRow, BYTE ucCol, bit bVedioTiming, bit bInterlace);
extern void COSDDispTimingInfoStyle(void);
// V015 VGA Patch Note (12) Modify 20100625 End

#endif

