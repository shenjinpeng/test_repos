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

#ifdef __NONE_OSDDISP__
//--------------------------------------------------
// Global Variables
//--------------------------------------------------
void COsdDispInitial(void);
void COsdDispColorProcess(void);
BYTE COsdDispContrastChangeover(BYTE ucSelect, BYTE ucValue);
BYTE COsdDispBacklightChangeover(BYTE ucValue);


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void COsdDispOsdTimerEvent(void);
void COsdDispFirstTimeLoadFont(void);
void COsdDispClearText(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);
BYTE COsdDispRealToPercent(WORD RealValue, WORD Max, WORD Min);
WORD COsdDispPercentToRealValue(BYTE PercentValue, WORD Max, WORD Min);


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern void COsdDispInitial(void);
extern void COsdDispColorProcess(void);
extern BYTE COsdDispContrastChangeover(BYTE ucSelect, BYTE ucValue);
extern BYTE COsdDispBacklightChangeover(BYTE ucValue);


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void COsdDispOsdTimerEvent(void);
extern void COsdDispFirstTimeLoadFont(void);
extern void COsdDispClearText(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);
extern BYTE COsdDispRealToPercent(WORD RealValue, WORD Max, WORD Min);
extern WORD COsdDispPercentToRealValue(BYTE PercentValue, WORD Max, WORD Min);


#endif


