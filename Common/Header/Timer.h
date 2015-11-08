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
// ID Code      : Timer.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Timer.c
//--------------------------------------------------
#define _MAX_EVENT_AMOUNT                       7
#define _INACTIVE_TIMER_EVENT                   0xFFFF
#define _INACTIVE_COUNTDOWN_EVENT               0xFF


//----------------------------------------------------------------------------------------------------

#ifdef __TIMER__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
struct CTimerEventTable idata TimerEvent[_MAX_EVENT_AMOUNT];
BYTE data ucTimer0Cnt = 0;
BYTE xdata ucTimer0Cnt3 = 100;
BYTE data ucTimer0Cnt2 = 30;//sjp for power bug 20110804
WORD xdata ucTimer0Cnt1 = 600;
//WORD data ucTimer0Cnt3 = 65535;

bit bWatchDogResetCtrl=_FALSE;
bit bNotifyTimer0Int;
bit bTimer0Ctrl = _FALSE;
bit bTimer01minCtrl = _FALSE;

bit bTimerAgeModeCtrl=_FALSE;
//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CTimerHandler(void);
void CTimerActiveTimerEvent(WORD usTime, void (*Event)());
void CTimerReactiveTimerEvent(WORD usTime, void (*Event)());
void CTimerCancelTimerEvent(void (*Event)());
void CTimerInitialTimerEvent(void);
void CTimerDecreaseTimerCnt(void);
void CTimerCountDownEventProc(BYTE *pEventCnt, BYTE ucWaitCnt, void (*Event)(void));
bit CTimerPollingEventProc(BYTE ucTimeout, bit (*Event)(void));
void CTimerDelayXms(WORD usNum);
bit CTimerWaitForEvent(BYTE ucEvent);

bit CTimerPollingFlagProc(WORD usTimeout, BYTE ucPage, BYTE ucRegister, BYTE ucBit, bit bSuccess);

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
bit CTimerPollingFlagProcForMcu(WORD usTimeout, BYTE *pucAddress, BYTE ucBit, bit bSuccess);
*/
// V015 System Patch Note (7) Modify 20100630 End

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern struct CTimerEventTable idata TimerEvent[_MAX_EVENT_AMOUNT];
extern BYTE data ucTimer0Cnt;
extern BYTE data ucTimer0Cnt2;
extern WORD xdata ucTimer0Cnt1;
extern BYTE xdata ucTimer0Cnt3; 
//extern BYTE data ucTimer0Cnt3;

extern bit bNotifyTimer0Int;
extern bit bTimer0Ctrl;
extern bit bTimer01minCtrl;
extern bit bTimerAgeModeCtrl;



//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CTimerHandler(void);
extern void CTimerActiveTimerEvent(WORD usTime, void (*Event)());
extern void CTimerReactiveTimerEvent(WORD usTime, void (*Event)());
extern void CTimerCancelTimerEvent(void (*Event)());
extern void CTimerInitialTimerEvent(void);
extern void CTimerDecreaseTimerCnt(void);
extern void CTimerCountDownEventProc(BYTE *pEventCnt, BYTE ucWaitCnt, void (*Event)(void));
extern bit CTimerPollingEventProc(BYTE ucTimeout, bit (*Event)(void));
extern void CTimerDelayXms(WORD usNum);
extern bit CTimerWaitForEvent(BYTE ucEvent);

extern bit CTimerPollingFlagProc(WORD usTimeout, BYTE ucPage, BYTE ucRegister, BYTE ucBit, bit bSuccess);

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
extern bit CTimerPollingFlagProcForMcu(WORD usTimeout, BYTE *pucAddress, BYTE ucBit, bit bSuccess);
*/
// V015 System Patch Note (7) Modify 20100630 End

#endif
extern bit bWatchDogResetCtrl;




//----------------------------------------------------------------------------------------------------

