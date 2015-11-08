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
// ID Code      : DCR.h No.0000
// Update Note  : //
//----------------------------------------------------------------------------------------------------

#if(_DCR_MODE == _DCR_TYPE_1)


#ifdef __DCR_TYPE_1__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
void CDcrMeasureStartHD(void);
void CDcrDcr1(void);
void CDcrSlowAdjust(BYTE ucValue);

WORD xdata g_usHorBoundary = 0;
WORD xdata g_usVerBoundary = 0;
WORD xdata g_usRGBInfo = 0;
WORD xdata g_ucPreBacklightPWM = 255;
BYTE xdata g_ucPreDCCLum = 0;
BYTE xdata g_ucDcrCtrl = 0;
BYTE xdata g_ucDCRPercent = 100;  // Max 100

#else


//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern void CDcrMeasureStartHD(void);
extern void CDcrSlowAdjust(BYTE ucValue);
extern BYTE xdata g_ucDcrCtrl;
extern WORD xdata g_usHorBoundary;
extern WORD xdata g_usVerBoundary;
extern WORD xdata g_usRGBInfo;
extern WORD xdata g_ucPreBacklightPWM;
extern BYTE xdata g_ucPreDCCLum;
extern BYTE xdata g_ucDCRPercent;

#endif //End of #ifdef __DCR_TYPE_1__


//--------------------------------------------------
// DCR of Power Status
//--------------------------------------------------
#define GET_DCR_STATUS()                        ((bit)(g_ucDcrCtrl & _BIT1))
#define SET_DCR_STATUS()                        (g_ucDcrCtrl |= _BIT1)
#define CLR_DCR_STATUS()                        (g_ucDcrCtrl &= ~_BIT1)

#endif // End of #if(_DCR_MODE == _DCR_TYPE_1)

