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
// ID Code      : Uart.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DEBUG_TOOL == _RS232)

//--------------------------------------------------
// Definitions of
//--------------------------------------------------


//----------------------------------------------------------------------------------------------------

#ifdef __UART__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
bit idata bUartCommandStart = _FALSE;
bit idata bUartCommandSuccess = _FALSE;
bit idata bDebugModeEnable = _FALSE;
BYTE xdata ucUartCommandNum = 0;
BYTE xdata pUartData[8] = 0;
BYTE xdata ucPageInfo = 0;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CUartInitial(void);
void CUartHandler(void);
void CUartPutCharToScr(BYTE ch);
void TxRxShow(void);

void CUartEnable(void);
void CUartDisable(void);
void CUartTransferNumToScr(WORD ch, BYTE mode);
BYTE DebugPrintf(const BYTE code* pstr, WORD value);

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern bit idata bUartCommandStart;
extern bit idata bUartCommandSuccess;
extern bit idata bDebugModeEnable;
extern BYTE xdata ucUartCommandNum;
extern BYTE xdata pUartData[8];
extern BYTE xdata ucPageInfo;

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CUartInitial(void);
extern void CUartHandler(void);
extern void CUartEnable(void);
extern void CUartDisable(void);
extern void CUartTransferNumToScr(WORD ch, BYTE mode);
extern BYTE DebugPrintf(const BYTE code* pstr, WORD value);
#endif

//----------------------------------------------------------------------------------------------------

#endif  // End of #if(_DEBUG_TOOL == _RS232)
