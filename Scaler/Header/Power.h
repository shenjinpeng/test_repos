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
// ID Code      : Power.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------


//----------------------------------------------------------------------------------------------------

#ifdef __POWER__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------

BYTE xdata ucPowerControl = 0;


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bit CPowerHandler(void);
void CPowerControl(void);
void CPowerPanelOn(void);
void CPowerPanelOff(void);
void CPowerPanelPowerOn(void);
void CPowerPanelPowerOff(void);
void CPowerLightPowerOn(void);
void CPowerLightPowerOff(void);
void CPowerDisplayPortOn(void);
void CPowerDisplayPortOff(void);
void CPowerADCAPLLOn(void);
void CPowerADCAPLLOff(void);
void CPowerTMDSOn(void);
void CPowerTMDSOff(void);
void CPowerDPLLOff(void);

void CPowerM2PLLOn(void);
void CPowerM2PLLOff(void);

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
void CPowerMPLLOff(void);
#endif
void CPowerPWMOn(void);
void CPowerPWMOff(void);

#if((_PANEL_STYLE == _PANEL_TTL) || (_PANEL_STYLE == _PANEL_LVDS))
void CPowerLVDSOn(void);
void CPowerLVDSOff(void);
#endif

#if(_PANEL_STYLE == _PANEL_RSDS)
void CPowerRSDSOn(void);
void CPowerRSDSOff(void);
#endif


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE xdata ucPowerControl;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern bit CPowerHandler(void);
extern void CPowerControl(void);
extern void CPowerPanelOn(void);
extern void CPowerPanelOff(void);
extern void CPowerPanelPowerOn(void);
extern void CPowerPanelPowerOff(void);
extern void CPowerLightPowerOn(void);
extern void CPowerLightPowerOff(void);
extern void CPowerADCAPLLOn(void);
extern void CPowerADCAPLLOff(void);
extern void CPowerTMDSOn(void);
extern void CPowerTMDSOff(void);
extern void CPowerDPLLOff(void);

extern void CPowerM2PLLOn(void);
extern void CPowerM2PLLOff(void);

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
extern void CPowerMPLLOff(void);
#endif
extern void CPowerPWMOn(void);
extern void CPowerPWMOff(void);
extern void CPowerLVDSOn(void);
extern void CPowerLVDSOff(void);


#if(_PANEL_STYLE == _PANEL_RSDS)
extern void CPowerRSDSOn(void);
extern void CPowerRSDSOff(void);
#endif



#endif // End of #ifdef __POWER__



//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Power Switch Flag
//--------------------------------------------------
#define GET_POWERSWITCH()                       ((bit)(ucPowerControl & _BIT0))
#define SET_POWERSWITCH()                       (ucPowerControl |= _BIT0)
#define CLR_POWERSWITCH()                       (ucPowerControl &= ~_BIT0)


//--------------------------------------------------
// Macro of Panel Power Status
//--------------------------------------------------
#define GET_PANELPOWERSTATUS()                  ((bit)(ucPowerControl & _BIT1))
#define SET_PANELPOWERSTATUS()                  (ucPowerControl |= _BIT1)                   // Power Up
#define CLR_PANELPOWERSTATUS()                  (ucPowerControl &= ~_BIT1)                  // Power Down


//--------------------------------------------------
// Macro of Backlight Power Status
//--------------------------------------------------
#define GET_LIGHTPOWERSTATUS()                  ((bit)(ucPowerControl & _BIT2))
#define SET_LIGHTPOWERSTATUS()                  (ucPowerControl |= _BIT2)
#define CLR_LIGHTPOWERSTATUS()                  (ucPowerControl &= ~_BIT2)


//--------------------------------------------------
// Macro of Load Font at First Power Up
//--------------------------------------------------
#define GET_FIRST_LOADFONT()                    ((bit)(ucPowerControl & _BIT3))
#define SET_FIRST_LOADFONT()                    (ucPowerControl |= _BIT3)
#define CLR_FIRST_LOADFONT()                    (ucPowerControl &= ~_BIT3)


//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
#define PANELPOWER_UP()                         (bPANELPOWER = _PANEL_ON)
#define PANELPOWER_DOWN()                       (bPANELPOWER = _PANEL_OFF)


//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#define LIGHTPOWER_UP()                         (bLIGHTPOWER = _LIGHT_ON)
#define LIGHTPOWER_DOWN()                       (bLIGHTPOWER = _LIGHT_OFF)


