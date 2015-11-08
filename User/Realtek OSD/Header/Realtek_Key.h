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
// ID Code      : Key.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Key Repeat Start Time (Unit in sec)
//--------------------------------------------------
#define _KEY_REPEAT_START_TIME      0.5


//--------------------------------------------------
// Definitions of Key Mask
//--------------------------------------------------
#define _POWER_KEY_MASK             0x01
#define _MENU_KEY_MASK              0x02
#define _RIGHT_KEY_MASK             0x04
#define _LEFT_KEY_MASK              0x08
#define _EXIT_KEY_MASK              0x10
#define _KEY5_MASK                  0x20
#define _KEY6_MASK                  0x40
#define _KEY7_MASK                  0x80
#define _LSLUMI_MASK                0x18//SJP20110625
#define _PWMLUMI_MASK            0x14//sjp20110715
#define _AUTOCOLOR_MASK        0x30//sjp20110809
#define _AGE_MODE_MASK         _RIGHT_KEY_MASK|_MENU_KEY_MASK

#define _POWER_RIGHT_KEY_MASK       (_POWER_KEY_MASK | _RIGHT_KEY_MASK)
#define _POWER_MENU_KEY_MASK        (_POWER_KEY_MASK | _MENU_KEY_MASK)
#define _POWER_LEFT_RIGHT_KEY_MASK  (_POWER_KEY_MASK | _LEFT_KEY_MASK | _RIGHT_KEY_MASK)


//--------------------------------------------------
// Definitions of Key Message
//--------------------------------------------------
#define _MENU_KEY_MESSAGE           0
#define _RIGHT_KEY_MESSAGE          1
#define _LEFT_KEY_MESSAGE           2
#define _EXIT_KEY_MESSAGE           3
#define _5_KEY_MESSAGE              4
#define _6_KEY_MESSAGE              5
#define _AUTOCOLOR_MESSAGE     6                   //_7_KEY_MESSAGE              6
//#define _AUTOCOLOR_MESSAGE     6                   //_7_KEY_MESSAGE              6

#define _AGE_MODE_MESSAGE     10                  //_7_KEY_MESSAGE              6
#define _NONE_KEY_MESSAGE           7
#define _LSLUMI_MESSAGE      8// FOR lslumi OSD SJP20110625
#define _PWMLUMI_MESSAGE       9//For PWMlumi OSD sjp20110715
#define _KEY_AMOUNT                 4


//----------------------------------------------------------------------------------------------------

#ifdef __REALTEK_KEY__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------

BYTE xdata ucKeyControl = 0;
BYTE xdata ucKeyMessage = 0;
BYTE xdata ucKeyStatePrev = 0;
BYTE xdata ucKeyStateCurr = 0;


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CKeyHandler(void);
void CKeyCheckPowerKey(void);
void CKeyInitial(void);
bit CKeyScanReady(void);
void CKeyScanReadyTimerEvent(void);
void CKeyRepeatEnableTimerEvent(void);
void CKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg);
BYTE CKeyScan(void);
void CKeyPowerKeyMix(void);
bit CKeyPowerKeyProc(void);
void CKeyMessageProc(void);
void CKeyKeyPadLedControl(void);


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE xdata ucKeyControl;
extern BYTE xdata ucKeyMessage;
extern BYTE xdata ucKeyStatePrev;
extern BYTE xdata ucKeyStateCurr;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CKeyHandler(void);
extern void CKeyCheckPowerKey(void);
extern void CKeyInitial(void);
extern void CKeyKeyPadLedControl(void);


#endif


//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Key Scan Ready Flag
//--------------------------------------------------
#define GET_KEYSCANREADY()          ((bit)(ucKeyControl & _BIT0))
#define SET_KEYSCANREADY()          (ucKeyControl |= _BIT0)
#define CLR_KEYSCANREADY()          (ucKeyControl &= ~_BIT0)


//--------------------------------------------------
// Macro of Key Scan Start Flag
//--------------------------------------------------
#define GET_KEYSCANSTART()          ((bit)(ucKeyControl & _BIT1))
#define SET_KEYSCANSTART()          (ucKeyControl |= _BIT1)
#define CLR_KEYSCANSTART()          (ucKeyControl &= ~_BIT1)


//--------------------------------------------------
// Macro of Key Repeat Start
//--------------------------------------------------
#define GET_KEYREPEATSTART()        (bit)(ucKeyControl & _BIT2)
#define SET_KEYREPEATSTART()        (ucKeyControl |= _BIT2)
#define CLR_KEYREPEATSTART()        (ucKeyControl &= ~_BIT2)


//--------------------------------------------------
// Macro of Key Repeat Function Enable
// If you want to use repeat function, please set this flag. If not, please clear it.
//--------------------------------------------------
#define GET_KEYREPEATENABLE()       (bit)(ucKeyControl & _BIT3)
#define SET_KEYREPEATENABLE()       (ucKeyControl |= _BIT3)
#define CLR_KEYREPEATENABLE()       (ucKeyControl &= ~_BIT3)


//----------------------------------------------------------------------------------------------------

