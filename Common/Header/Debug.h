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
// ID Code      : Debug.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DEBUG_MESSAGE_SUPPORT == _ON) && ((_DEBUG_TOOL == _ISP_FOR_RTD2120) || (_DEBUG_TOOL == _ISP_FOR_EMBEDDED)))
#define _NO_VALUE                       0xEFFFFFFF
#endif

#if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
#define _DATA_OUT_COUNT                       0x05

#define _TIME_OUT_COUNT                       2000


#endif

//----------------------------------------------------------------------------------------------------

#ifdef __Debug__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
#if((_DEBUG_MESSAGE_SUPPORT == _ON) && ((_DEBUG_TOOL == _ISP_FOR_RTD2120) || (_DEBUG_TOOL == _ISP_FOR_EMBEDDED)))

bit idata g_bDebugMessageEven = _INITIAL_MESSAGE_ACK;
bit idata g_bDebugMessageStart = _FALSE;
BYTE xdata pDebugMessageBUF[4] = 0;
#endif

#if((_DEBUG_MESSAGE_SUPPORT == _ON) && ((_DEBUG_TOOL == _ISP_FOR_RTD2120)))

BYTE xdata TxTemp = 0; // TxTemp is the register of TxBUF.
bit idata bDataOutEnd = _FALSE;
#endif

#if((_DEBUG_MESSAGE_SUPPORT == _ON) && ((_DEBUG_TOOL == _ISP_FOR_EMBEDDED)))
bit idata g_bFwHalt = 0;
WORD xdata g_usFilterPro = 0;
#endif

#if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
WORD xdata g_usDebugCount = 0;
#endif

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
void CDebugMessage(BYTE *pArray1, DWORD pArray2);
#endif

#if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
void CDebugCheckTimeOut(void);
#endif
#else
//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------

#if((_DEBUG_MESSAGE_SUPPORT == _ON) && ((_DEBUG_TOOL == _ISP_FOR_RTD2120) || (_DEBUG_TOOL == _ISP_FOR_EMBEDDED)))

extern bit idata g_bDebugMessageEven;
extern bit idata g_bDebugMessageStart;
extern BYTE xdata pDebugMessageBUF[4];

#endif

#if((_DEBUG_MESSAGE_SUPPORT == _ON) && ((_DEBUG_TOOL == _ISP_FOR_RTD2120)))
extern BYTE xdata TxTemp;
extern bit idata bDataOutEnd;
#endif

#if((_DEBUG_MESSAGE_SUPPORT == _ON) && ((_DEBUG_TOOL == _ISP_FOR_EMBEDDED)))
extern bit idata g_bFwHalt;
extern WORD xdata g_usFilterPro;

#endif

#if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
extern WORD xdata g_usDebugCount;
#endif


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
extern void CDebugMessage(BYTE *pArray1, DWORD pArray2);
#endif

#if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
extern void CDebugCheckTimeOut(void);
#endif

#endif  // End of #else of #ifdef __Debug__

