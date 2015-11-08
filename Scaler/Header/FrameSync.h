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
// ID Code      : FrameSync.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Offset_Step is the DCLK frequency step for searching frame-sync.
//--------------------------------------------------
#define _OFFSET_STEP    24
#define _SEARCH_TIME    24


//----------------------------------------------------------------------------------------------------

#ifdef __FRAMESYNC__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bit CFrameSyncDetect(void);
bit CFrameSyncLastLineFinetune(WORD *pDelta);
BYTE CFrameSyncSpreadSpectrumFinetune(WORD *pDelta);
WORD CFrameSyncFastDo(void);
bit CFrameSyncTestSync(WORD usOffset);
BYTE CFrameSyncDo(void);
void CFrameSyncModifyDVStartPos(bit enable);
void CFrameSyncFineTune(bit field);

// V013 VGA Patch Note (16) Modify 20100422 Start
// Patch Reason : Add fineTune display position for VGA interlace mode.
void CFrameSyncAnalogFineTune(void);
// V013 VGA Patch Note (16) Modify 20100422 End

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern bit CFrameSyncDetect(void);
extern BYTE CFrameSyncDo(void);
extern void CFrameSyncModifyDVStartPos(bit enable);
extern void CFrameSyncFineTune(bit field);

// V013 VGA Patch Note (16) Modify 20100422 Start
// Patch Reason : Add fineTune display position for VGA interlace mode.
extern void CFrameSyncAnalogFineTune(void);
// V013 VGA Patch Note (16) Modify 20100422 End

#endif // End of #ifdef __FRAMESYNC__



//----------------------------------------------------------------------------------------------------
