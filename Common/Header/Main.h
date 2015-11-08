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
// ID Code      : Main.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------


//----------------------------------------------------------------------------------------------------

#ifdef __MAIN__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE data pData[16];
WORD xdata TempLumValue;
bit bAgeModeOn=_FALSE;
bit bAgeModeWhiteFlag=_FALSE;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CMainUserInitial(void);
void CMainIOInitial(void);
bit CMainDetectSystemPower(void);
bit CMainResetCheck(void);
void CMainGlobalVarInitial(void);
void CMainGetIDCode(void);
void CMainSystemInitial(void);
void CMainIspDebugProc(void); // Debug Message Support
void LSHandler(void);
void LSIintial(void);
#if(_DDCCI_SUPPORT == _ON)
void CDebugInitial(void);
#endif

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE data pData[16];
extern WORD xdata TempLumValue;

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CMainIspDebugProc(void); // Debug Message Support
extern void LSHandler(void);
extern void CMainSystemInitial(void);
extern void LSIintial(void);

#endif
extern bit bAgeModeOn;
extern bit bAgeModeWhiteFlag;


//----------------------------------------------------------------------------------------------------

