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
// ID Code      : OsdFunc.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of OsdFnc.h
//--------------------------------------------------

//----------------------------------------------------------------------------------------------------

#ifdef __NONE_OSDFX__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void COsdFxApplyMapSetting(BYTE ucOsdmaptype);
void COsdFxSetFrameCtrlCommand(void);
void COsdFxSetCharCommandMap(void);
void COsdFxEnableOsd(void);
void COsdFxDisableOsd(void);
void COsdFxChangeWindowColor(BYTE ucWindowColor, BYTE *pStyle);
void COsdFxCloseWindow(BYTE ucWinNumber);
void COsdFxSlider(BYTE ucRow, BYTE ucCol, BYTE ucLength, WORD usValue, WORD usMax, WORD usMin);
void COsdFxShowNumber(BYTE ucRow, BYTE ucCol, WORD usValue, BYTE ucPar);
void COsdFxShowNorm100Number(BYTE ucRow, BYTE ucCol, WORD usValue, WORD usMax, WORD usMin, BYTE ucPar);
void COsdFxCodeWrite(BYTE code *pArray);
void COsdFxCalcStartAddress(BYTE ucRow, BYTE ucCol, BYTE ucIndicate);
void COsdFxLoadText(BYTE ucRow, BYTE ucCol, BYTE ucSelect, BYTE code *pArray);
WORD COsdFxGetColWithinText(BYTE ucPos, BYTE ucSelect, BYTE *pArray, BYTE ucType);
void COsdFxLoadIcon(BYTE ucRow, BYTE ucCol, BYTE code *pArray);
void COsdFxChange1bitColor(BYTE ucRow, BYTE ucCol, BYTE ucSizeW, BYTE ucSizeH, BYTE ucForegroundColor, BYTE ucBackgroundColor);
void COsdFxChange2bitColor(BYTE ucRow, BYTE ucCol, BYTE ucSizeW, BYTE ucSizeH, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
void COsdFxChange4bitLUTColor(BYTE ucRow, BYTE ucCol, BYTE ucSizeW, BYTE ucSizeH, BYTE ucColor0);
void COsdFxDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE *pStyle);

void COsdFxHLine(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucValue, BYTE ucIndicate);
void COsdFxVLine(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucValue, BYTE ucIndicate);
void COsdFxSetPosition(WORD usOsdActWidth, WORD usOsdActHeight, BYTE ucHPos, BYTE ucVPos, BYTE ucPar);
WORD COsdFxGetAdcClockRange(BYTE ucPar);
WORD COsdFxGetHPositionRange(BYTE ucPar);
WORD COsdFxGetVPositionRange(BYTE ucPar);
WORD COsdFxDetOverRange(WORD ucValue, WORD ucMax, WORD ucMin, BYTE ucSymbol);


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void COsdFxApplyMapSetting(BYTE ucOsdmaptype);
extern void COsdFxSetFrameCtrlCommand(void);
extern void COsdFxSetCharCommandMap(void);
extern void COsdFxEnableOsd(void);
extern void COsdFxDisableOsd(void);
extern void COsdFxChangeWindowColor(BYTE ucWindowColor, BYTE *pStyle);
extern void COsdFxCloseWindow(BYTE ucWinNumber);
extern void COsdFxSlider(BYTE ucRow, BYTE ucCol, BYTE ucLength, WORD usValue, WORD usMax, WORD usMin);
extern void COsdFxShowNumber(BYTE ucRow, BYTE ucCol, WORD usValue, BYTE ucPar);
extern void COsdFxShowNorm100Number(BYTE ucRow, BYTE ucCol, WORD usValue, WORD usMax, WORD usMin, BYTE ucPar);
extern void COsdFxCodeWrite(BYTE code *pArray);
extern void COsdFxCalcStartAddress(BYTE ucRow, BYTE ucCol, BYTE ucIndicate);
extern void COsdFxLoadText(BYTE ucRow, BYTE ucCol, BYTE ucSelect, BYTE code *pArray);
extern WORD COsdFxGetColWithinText(BYTE ucPos, BYTE ucSelect, BYTE *pArray, BYTE ucType);
extern void COsdFxLoadIcon(BYTE ucRow, BYTE ucCol, BYTE code *pArray);
extern void COsdFxChange1bitColor(BYTE ucRow, BYTE ucCol, BYTE ucSizeW, BYTE ucSizeH, BYTE ucForegroundColor, BYTE ucBackgroundColor);
extern void COsdFxChange2bitColor(BYTE ucRow, BYTE ucCol, BYTE ucSizeW, BYTE ucSizeH, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
extern void COsdFxChange4bitLUTColor(BYTE ucRow, BYTE ucCol, BYTE ucSizeW, BYTE ucSizeH, BYTE ucColor0);
extern void COsdFxDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE *pStyle);
extern void COsdFxHLine(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucValue, BYTE ucIndicate);
extern void COsdFxVLine(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucValue, BYTE ucIndicate);
extern void COsdFxSetPosition(WORD usOsdActWidth, WORD usOsdActHeight, BYTE ucHPos, BYTE ucVPos, BYTE ucPar);
extern WORD COsdFxGetAdcClockRange(BYTE ucPar);
extern WORD COsdFxGetHPositionRange(BYTE ucPar);
extern WORD COsdFxGetVPositionRange(BYTE ucPar);
extern WORD COsdFxDetOverRange(WORD ucValue, WORD ucMax, WORD ucMin, BYTE ucSymbol);


#endif


//----------------------------------------------------------------------------------------------------
