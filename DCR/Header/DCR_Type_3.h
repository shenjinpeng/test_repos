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

#if(_DCR_MODE == _DCR_TYPE_3)


//--------------------------------------------------
// Definitions of Input Source
//--------------------------------------------------
#define _PWM_MIN            95
#define _PWM_LOW            135
#define _PWM_HIGH           180
#define _PWM_MAX            255
#define _ULTRA_MIN          40
#define _ACER_HIGH_ACM      _ON


#ifdef __DCR_TYPE_3__


//--------------------------------------------------
// Vivid Color Data Table
//--------------------------------------------------
code BYTE tDCC_PAGE0[] =
{
    0x00, 0x00, 0x00, 0x00,
    0x00, 0xFF, 0x00, 0x00,
    0x00,
};

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
void CDcrInitial(void);
void CDcrDcr3(void);
void CDcr5MinTimerCount(void);

BYTE xdata g_ucDcrTargetPre = 0;
BYTE xdata g_ucDcrTargetPre1 = 0;
BYTE xdata g_ucDcrTemp = 0;
BYTE xdata g_ucDcrPwm = 0;
BYTE xdata g_ucDcrCnt = 0;
WORD xdata g_usDcrStep = 0;
BYTE xdata g_ucDcrTimer = 0;
BYTE xdata g_ucDcrCtrl = 0;
BYTE xdata g_ucDcrCurrentPWM = 0;
BYTE idata g_ucDCRPercent = 100;  //Max 100
WORD idata g_usDCR5MinTimer = 0;


#else


//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern void CDcrInitial(void);
extern void CDcrDcr3(void);

extern BYTE xdata g_ucDcrTargetPre;
extern BYTE xdata g_ucDcrTargetPre1;
extern BYTE xdata g_ucDcrTemp;
extern BYTE xdata g_ucDcrPwm;
extern BYTE xdata g_ucDcrCnt;
extern WORD xdata g_usDcrStep;
extern BYTE xdata g_ucDcrTimer;
extern BYTE xdata g_ucDcrCtrl;
extern BYTE xdata g_ucDcrCurrentPWM;

extern WORD idata g_usDCR5MinTimer;
extern void CDcr5MinTimerCount(void);

#endif   //End of #ifdef __DCR_TYPE_3__


//--------------------------------------------------
// DCR of Power Status
//--------------------------------------------------
#define GET_DCR_STATUS()                        ((bit)(g_ucDcrCtrl & _BIT1))
#define SET_DCR_STATUS()                        (g_ucDcrCtrl |= _BIT1)
#define CLR_DCR_STATUS()                        (g_ucDcrCtrl &= ~_BIT1)

#define GET_DCR_ULTRA_MIN()                     ((bit)(g_ucDcrCtrl & _BIT4))
#define SET_DCR_ULTRA_MIN()                     (g_ucDcrCtrl |= _BIT4)
#define CLR_DCR_ULTRA_MIN()                     (g_ucDcrCtrl &= ~_BIT4)

#endif // End of #if(_DCR_MODE == _DCR_TYPE_3)

