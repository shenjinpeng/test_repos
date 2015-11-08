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

#if(_DCR_MODE == _DCR_TYPE_2)


#ifdef __DCR_TYPE_2__

//--------------------------------------------------
// Vivid Color Data Table
//--------------------------------------------------
#if(_VIVID_COLOR_FUCTION == _ON)
code BYTE tDCR_USERCURVE0[] =
{
    0x0a, 0x20, 0x30, 0x40,
    0x50, 0x60, 0x70, 0x80,
    0x90, 0xa0, 0xb0, 0xc0,
    0xd0, 0xe0, 0xf0,
};

code BYTE tDCR_USERCURVE255[] =
{
    0x10, 0x20, 0x37, 0x4a,
    0x5a, 0x6a, 0x7a, 0x8a,
    0x9a, 0xaa, 0xba, 0xca,
    0xda, 0xe8, 0xf8,
};
#endif  // End of #if(_VIVID_COLOR_FUCTION == _ON)

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
void CDcrMeasureStartHD(void);
void CDcrDcr2(void);
void CAdjustDCRFillDCCTable( BYTE ucValue);
void CDcrSlowAdjust(WORD ucValue);

WORD xdata g_usHorBoundary = 0;
WORD xdata g_usVerBoundary = 0;
WORD xdata g_usRGBInfo = 0;
WORD xdata g_ucPreBacklightPWM = 255;
BYTE xdata g_ucPreDCCLum = 0;
BYTE xdata g_ucDcrCtrl = 0;
BYTE xdata g_ucDCRPercent = 100;  //Max 100

#else


//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern void CDcrMeasureStartHD(void);
extern void CDcrSlowAdjust(WORD ucValue);
extern BYTE xdata g_ucDcrCtrl;
extern WORD xdata g_usHorBoundary;
extern WORD xdata g_usVerBoundary;
extern WORD xdata g_usRGBInfo;
extern BYTE xdata g_ucPreBacklightPWM;
extern BYTE xdata g_ucPreDCCLum;
extern BYTE xdata g_ucDCRPercent;

#endif //End of #ifdef __DCR_TYPE_2__


//--------------------------------------------------
// DCR of Power Status
//--------------------------------------------------
#define GET_DCR_STATUS()                        ((bit)(g_ucDcrCtrl & _BIT1))
#define SET_DCR_STATUS()                        (g_ucDcrCtrl |= _BIT1)
#define CLR_DCR_STATUS()                        (g_ucDcrCtrl &= ~_BIT1)

#endif // End of #if(_DCR_MODE == _DCR_TYPE_2)


