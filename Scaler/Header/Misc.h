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
// ID Code      : Misc.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------
//----------------------------------------------------------------------------------------------------

#ifdef __MISC__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
#if((_DEBUG_TOOL == _ISP_FOR_RTD2120) || (_DEBUG_TOOL == _ISP_FOR_EMBEDDED))

BYTE g_ucDdcciCommandNumber = 0;


BYTE TxBUF = 0;
bit bRunCommand = 0;

BYTE idata ucDdcciData[4] = {0};

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
#if((_EDID_PRO == _ON) && (_MEMORY_LOCATION == _FLASH) && (_MCU_TYPE == _REALTEK_EMBEDDED))
BYTE idata g_ucEdidProFlag = 0;
#endif
// V015 System Patch Note (7) Modify 20100630 End

#endif
//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bit CMiscScalerResetEvent(void);
bit CMiscStableFlagPollingEvent(void);

// V012 Modify 20100329 Start
// V012 Patch Note (19) : Adjust polling time of Auto Run Typer according to different Crystal frequency.
/*
bit CMiscHsyncTypeAutoRunFlagPollingEvent(void);
*/
// V012 Modify 20100329 End

bit CMiscModeMeasurePollingEvent(void);
bit CMiscAutoMeasurePollingEvent(void);
bit CMiscApplyDoubleBufferPollingEvent(void);
bit CMiscDVSStartPollingEvent(void);
void CMiscCheckToActiveEvent(void);
void CMiscEnableDoubleBuffer(void);
void CMiscDisableDoubleBuffer(void);
void CMiscApplyDoubleBuffer(void);
void CMiscClearStatusRegister(void);
void CMiscSetPinShare(void);
void CMiscIspack(void);
void CMiscIspDebugProc(void);

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
void CMiscEdidPoc(void);
*/
#if((_EDID_PRO == _ON) && ((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122)))
void CMiscEdidPoc(void);
#endif

#if((_EDID_PRO == _ON) && (_MEMORY_LOCATION == _FLASH) && (_MCU_TYPE == _REALTEK_EMBEDDED))
void CMiscEdidPoc(void);
bit CMiscSaveDDCToFlashEvent(void);
#endif

void CMiscConfigureFlashWPPinHigh(void);
void CMiscConfigureFlashWPPinLow(void);
// V015 System Patch Note (7) Modify 20100630 End

#if((_DEBUG_TOOL == _ISP_FOR_RTD2120) || (_DEBUG_TOOL == _ISP_FOR_EMBEDDED) || (_DEBUG_TOOL == _RS232))
void CDdcciInitial(void);
#endif

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------

#if((_DEBUG_TOOL == _ISP_FOR_RTD2120) || (_DEBUG_TOOL == _ISP_FOR_EMBEDDED))
extern BYTE g_ucDdcciCommandNumber;
extern bit bRunCommand;
extern idata BYTE ucDdcciData[4];
extern BYTE TxBUF;
#endif
//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern bit CMiscScalerResetEvent(void);
extern bit CMiscStableFlagPollingEvent(void);

// V012 Modify 20100329 Start
// V012 Patch Note (19) : Adjust polling time of Auto Run Typer according to different Crystal frequency.
/*
extern bit CMiscHsyncTypeAutoRunFlagPollingEvent(void);
*/
// V012 Modify 20100329 End

extern bit CMiscModeMeasurePollingEvent(void);
extern bit CMiscAutoMeasurePollingEvent(void);
extern bit CMiscDVSStartPollingEvent(void);
extern void CMiscCheckToActiveEvent(void);
extern void CMiscEnableDoubleBuffer(void);
extern void CMiscDisableDoubleBuffer(void);
extern void CMiscApplyDoubleBuffer(void);
extern void CMiscClearStatusRegister(void);
extern void CMiscSetPinShare(void);
extern void CMiscIspDebugProc(void);

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
extern void CMiscEdidPoc(void);
*/
extern void CMiscConfigureFlashWPPinHigh(void);
extern void CMiscConfigureFlashWPPinLow(void);
// V015 System Patch Note (7) Modify 20100630 End

#if((_DEBUG_TOOL == _ISP_FOR_RTD2120) || (_DEBUG_TOOL == _ISP_FOR_EMBEDDED) || (_DEBUG_TOOL == _RS232))
extern void CDdcciInitial(void);
#endif


#endif // End of #ifdef __MISC__

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
//--------------------------------------------------
// Macro of EDID PRO
//--------------------------------------------------
#define GET_EDIDPROSTATUS()                     ((bit)(g_ucEdidProFlag & _BIT0))
#define SET_EDIDPROSTATUS()                     (g_ucEdidProFlag |= _BIT0)
#define CLR_EDIDPROSTATUS()                     (g_ucEdidProFlag &= (~_BIT0))

#define GET_ADCDDCSTATUS()                      ((bit)(g_ucEdidProFlag & _BIT7))
#define GET_DVIDDCSTATUS()                      ((bit)(g_ucEdidProFlag & _BIT6))
#define SET_ADCDVIDDCSTATUS(x)                  (g_ucEdidProFlag |= (x & (_BIT7 | _BIT6)))
#define CLR_ADCDVIDDCSTATUS()                   (g_ucEdidProFlag &= (~(_BIT7 | _BIT6)))

#define GET_HDMIDDCSTATUS()                     ((bit)(g_ucEdidProFlag & _BIT5))
#define SET_HDMIDDCSTATUS(x)                    (g_ucEdidProFlag |= ((x & _BIT0) << 5))
#define CLR_HDMIDDCSTATUS()                     (g_ucEdidProFlag &= (~_BIT5))
// V015 System Patch Note (7) Modify 20100630 End

//----------------------------------------------------------------------------------------------------

