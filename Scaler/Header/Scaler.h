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
// ID Code      : Scaler.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Scaler
//--------------------------------------------------

//----------------------------------------------------------------------------------------------------

#ifdef __SCALER__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE data ucVLDCnt, ucVLDTemp;
BYTE *pvldarray;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CScalerInitial(void);
void CScalerResetInFromMCU(void);
void CScalerReset(void);
void CScalerInitialDisplayInterface(void);
void CScalerInitialDisplayOutput(void);
void CScalerEnableDisplayOutput(void);
//void CScalerDisableDisplayOutput(void);
void CScalerEnableDisplayTiming(void);
void CScalerDisableDisplayTiming(void);

#if(_MCU_TYPE != _REALTEK_EMBEDDED)
void CScalerSendReadStop(void);
void CScalerSendWriteStop(void);
void CScalerSendAddr(BYTE ucAddr, bit bReadWrite, bit bAutoInc);
void CScalerSendByte(BYTE ucValue);
#endif  // End of #if(_MCU_TYPE != _REALTEK_EMBEDDED)

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
void CScalerSendAddr(BYTE ucAddr, bit bAutoInc);
void CScalerSendByte(BYTE ucValue);
#endif

void CScalerWrite(BYTE ucAddr, WORD usLength, BYTE *pArray, bit bAutoInc);
void CScalerRead(BYTE ucAddr, BYTE ucLength, BYTE *pArray, bit bAutoInc);
void CScalerWriteAmount(BYTE ucAddr, WORD usLength, BYTE ucValue, bit bAutoInc);
void CScalerSetByte(BYTE ucAddr, BYTE ucValue);
void CScalerSetDataPortByte(BYTE ucAddr, BYTE ucValue1, BYTE ucValue2);
void CScalerGetDataPortByte(BYTE ucAddr, BYTE ucValue, BYTE ucLength, BYTE *pArray, bit bAutoInc);
void CScalerSetBit(BYTE ucAddr, BYTE ucAnd, BYTE ucOr);
void CScalerSetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr);
BYTE CScalerGetBit(BYTE ucAddr, BYTE ucAnd);
//BYTE CScalerGetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd);

void CScalerCodeW(BYTE code *pArray);

void CScalerLoadHardwareVLCFont(BYTE *pArray, WORD usOffset);
void CScalerLoadFont(BYTE *pArray, WORD usOffset, WORD usLength, BYTE ucPar);
BYTE CScalerGetVLD(void);
bit CScalerGetBitVLD(void);
void CScalerPageSelect(BYTE page);

#if(_DP_SUPPORT == _ON)
void CScalerReadByteInt(BYTE ucAddr, BYTE *pArray);
void CScalerWriteInt(BYTE ucAddr, WORD usLength, BYTE *pArray, bit bAutoInc);
void CScalerSetByteInt(BYTE ucAddr, BYTE ucValue);
#endif

#if(_OSD_ROTATE_FUCTION == _ON)
void CScalerSendRotateByte(void);
#endif

void CScalerResetProcess(void);

#else


//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE data ucVLDCnt, ucVLDTemp;
extern BYTE *pvldarray;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CScalerInitial(void);
extern void CScalerResetInFromMCU(void);
extern void CScalerEnableDisplayOutput(void);
//extern void CScalerDisableDisplayOutput(void);
extern void CScalerEnableDisplayTiming(void);
extern void CScalerDisableDisplayTiming(void);

#if(_MCU_TYPE != _REALTEK_EMBEDDED)
extern void CScalerSendReadStop(void);
extern void CScalerSendWriteStop(void);
extern void CScalerSendAddr(BYTE ucAddr, bit bReadWrite, bit bAutoInc);
extern void CScalerSendByte(BYTE ucValue);
#endif  // End of #if(_MCU_TYPE != _REALTEK_EMBEDDED)

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
extern void CScalerSendAddr(BYTE ucAddr, bit bAutoInc);
extern void CScalerSendByte(BYTE ucValue);
#endif

extern void CScalerWrite(BYTE ucAddr, WORD usLength, BYTE *pArray, bit bAutoInc);
extern void CScalerRead(BYTE ucAddr, BYTE ucLength, BYTE *pArray, bit bAutoInc);
extern void CScalerWriteAmount(BYTE ucAddr, WORD usLength, BYTE ucValue, bit bAutoInc);
extern void CScalerSetByte(BYTE ucAddr, BYTE ucValue);
extern void CScalerSetDataPortByte(BYTE ucAddr, BYTE ucValue1, BYTE ucValue2);
extern void CScalerGetDataPortByte(BYTE ucAddr, BYTE ucValue, BYTE ucLength, BYTE *pArray, bit bAutoInc);
extern void CScalerSetBit(BYTE ucAddr, BYTE ucAnd, BYTE ucOr);
extern void CScalerSetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr);
extern BYTE CScalerGetBit(BYTE ucAddr, BYTE ucAnd);
//extern BYTE CScalerGetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd);

extern void CScalerCodeW(BYTE code *pArray);

extern void CScalerLoadHardwareVLCFont(BYTE *pArray, WORD usOffset);
extern void CScalerLoadFont(BYTE *pArray, WORD usOffset, WORD usLength, BYTE ucPar);
extern BYTE CScalerGetVLD(void);
extern bit CScalerGetBitVLD(void);
extern void CScalerPageSelect(BYTE page);
#if(_DP_SUPPORT == _ON)
extern void CScalerReadByteInt(BYTE ucAddr, BYTE *pArray);
extern void CScalerWriteInt(BYTE ucAddr, WORD usLength, BYTE *pArray, bit bAutoInc);
extern void CScalerSetByteInt(BYTE ucAddr, BYTE ucValue);
#endif


#if(_OSD_ROTATE_FUCTION == _ON)
extern void CScalerSendRotateByte(void);
#endif

extern void CScalerResetProcess(void);

#endif // End of #ifdef __SCALER__


//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Scaler.c
//--------------------------------------------------
#define SETSCALERSCLK()             (bSCALERSCLK = _TRUE)
#define CLRSCALERSCLK()             (bSCALERSCLK = _FALSE)

#define SETSCALERSCSB()             (bSCALERSCSB = _TRUE)
#define CLRSCALERSCSB()             (bSCALERSCSB = _FALSE)

#define SETSCALERSDIO3(x)           (bSCALERSDIO3 = x)
#define GETSCALERSDIO3()            (bSCALERSDIO3)


