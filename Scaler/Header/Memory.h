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
// ID Code      : Memory.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------


#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
//--------------------------------------------------
// Definitions of OD & FRC Memory Confirm
//--------------------------------------------------
#define _OD_CONFIRM                     0
#define _FRC_CONFIRM                    1

//--------------------------------------------------
// Definitions of Compress Group Number
//--------------------------------------------------
#define _COMPRESS_GROUP_NUMBER          0x320   //800 pixel

//--------------------------------------------------
// Definitions of OD start address
//--------------------------------------------------
#define _OD_START_ADDRESS               0x000000

//--------------------------------------------------
// Definitions of FRC address
//--------------------------------------------------
#define _FRC_1ST_BLOCK_STA_ADDR         0x000000
#if(_MEMORY_SIZE < _MEMORY_64MB)
#define _FRC_2ND_BLOCK_STA_ADDR         0x200000
#else
#define _FRC_2ND_BLOCK_STA_ADDR         0x400000
#endif

//--------------------------------------------------
// Definitions of Low Bit Noise Reduction Threshold
//--------------------------------------------------
#define _OD_LBNRT_ENABLE                _ON
#define _OD_LBNRT_MODE                  _NEWMODE
#define _OD_LBNRT_LEVEL                 1   // level-6

//--------------------------------------------------
// Definitions of OD Channel
//--------------------------------------------------
#define _OD_TABLE_SINGLY                0
#define _OD_TABLE_COMMON                3
#define _OD_TABLE_MIDDLE                0

#endif // End of #if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))

//----------------------------------------------------------------------------------------------------


#ifdef __MEMORY__

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// FRC Color Conversion Table
//--------------------------------------------------
BYTE code tFRC_TABLE_RGB2YUV[] =
{
    4,  _NON_AUTOINC,   _YUV_RGB_CTRL_9C,           0x08,
   21,  _NON_AUTOINC,   _YUV_RGB_COEF_DATA_9D,      0x01,0x32,0x02,0x59,0x00,0x74,
                                                    0xff,0x6a,0xfe,0xd9,0x01,0xbe,
                                                    0x02,0x75,0xfd,0xf1,0xff,0x9a,
    4,  _NON_AUTOINC,   _YUV_RGB_CTRL_9C,           0x51,

    _END
};

BYTE code tFRC_TABLE_YUV2RGB[] =
{
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,            _PAGE7,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,        0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x06,0x04,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x0E,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x16,0x04,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x1E,0x8f,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x26,0x01,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x2E,0x95,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x36,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x3E,0x52,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x46,0x08,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x4E,0x20,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x56,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x5E,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x66,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x6E,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x76,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x7E,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x86,0x02, // R Gain HByte
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x8E,0x00, // R Gain LByte
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x96,0x02, // G Gain HByte
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0x9E,0x00, // G Gain LByte
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0xA6,0x02, // B Gain HByte
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,      0xAE,0x00, // B Gain LByte
    4,  _NON_AUTOINC,   _P7_YUV2RGB_ACCESS_C0,      0x06,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,        0x01,

    _END
};
#endif  // End of #if(_FRC_SUPPORT == _ON)

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
BYTE xdata g_ucMemoryCtrl = 0;
#endif

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
BYTE CMemorySDRAMConfirm(bit bControl);
void CMemorySDRAMReset(void);
DWORD CMemoryCalculateNumberAndRemain(DWORD ulTotalSize, BYTE ucLength, bit bDummy);

#if(_OD_SUPPORT == _ON)
void CMemoryLoadODLUT(BYTE ucColor);
void CMemoryLoadODTable(BYTE *pChannelArray);
void CMemorySetODOnOff(BYTE ucSelect);
bit CMemorySetODCompress(void);
void CMemorySetODFIFO(void);
#endif

#if(_FRC_SUPPORT == _ON)
void CMemoryControlForFRC(WORD usHorSize, WORD usVerSize);
void CMemoryCtrlForFRCInput(WORD usHorSize, WORD usVerSize);
void CMemoryCtrlForFRCDisplay(WORD usHorSize, WORD usVerSize);
BYTE CMemoryAdjustIVS2DVSDelay(DWORD ulFreq);
DWORD CMemoryCalculateLineStepAndBlockStep(WORD usHorSize, WORD usVerSize);
void CMemoryWorkingTypeDecide(void);
#endif


#else


//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
extern BYTE xdata g_ucMemoryCtrl;
#endif


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern BYTE CMemorySDRAMConfirm(bit bControl);
extern void CMemorySDRAMReset(void);
extern DWORD CMemoryCalculateNumberAndRemain(DWORD ulTotalSize, BYTE ucLength, bit bDummy);

#if(_OD_SUPPORT == _ON)
extern void CMemoryLoadODLUT(BYTE ucColor);
extern void CMemoryLoadODTable(BYTE *pChannelArray);
extern void CMemorySetODOnOff(BYTE ucSelect);
extern bit CMemorySetODCompress(void);
extern void CMemorySetODFIFO(void);
#endif

#if(_FRC_SUPPORT == _ON)
extern void CMemoryControlForFRC(WORD usHorSize, WORD usVerSize);
extern void CMemoryCtrlForFRCInput(WORD usHorSize, WORD usVerSize);
extern void CMemoryCtrlForFRCDisplay(WORD usHorSize, WORD usVerSize);
extern BYTE CMemoryAdjustIVS2DVSDelay(DWORD ulFreq);
extern DWORD CMemoryCalculateLineStepAndBlockStep(WORD usHorSize, WORD usVerSize);
extern void CMemoryWorkingTypeDecide(void);
#endif


#endif // End of #ifdef __MEMORY__

//----------------------------------------------------------------------------------------------------


//--------------------------------------------------
// Macro of FRC Status
//--------------------------------------------------
#define GET_FRCSTATUS()             (bit)(g_ucMemoryCtrl & _BIT0)
#define SET_FRCSTATUS()             (g_ucMemoryCtrl |= _BIT0)
#define CLR_FRCSTATUS()             (g_ucMemoryCtrl &= ~_BIT0)

//--------------------------------------------------
// Macro of FRC 444->422 Enable
//--------------------------------------------------
#define GET_FRC422STATUS()          (bit)(g_ucMemoryCtrl & _BIT1)
#define SET_FRC422STATUS()          (g_ucMemoryCtrl |= _BIT1)
#define CLR_FRC422STATUS()          (g_ucMemoryCtrl &= ~_BIT1)

//--------------------------------------------------
// Marco of FRC 16 bits In
//--------------------------------------------------
#define GET_FRC16BITSIN()           (bit)(g_ucMemoryCtrl & _BIT2)
#define SET_FRC16BITSIN()           (g_ucMemoryCtrl |= _BIT2)
#define CLR_FRC16BITSIN()           (g_ucMemoryCtrl &= ~_BIT2)

//--------------------------------------------------
// Marco of FRC RGB In
//--------------------------------------------------
#define GET_FRCRGBIN()              (bit)(g_ucMemoryCtrl & _BIT3)
#define SET_FRCRGBIN()              (g_ucMemoryCtrl |= _BIT3)
#define CLR_FRCRGBIN()              (g_ucMemoryCtrl &= ~_BIT3)

//--------------------------------------------------
// Marco of FRC Enable
//--------------------------------------------------
#define GET_FRCENABLE()             (bit)(g_ucMemoryCtrl & _BIT4)
#define SET_FRCENABLE()             (g_ucMemoryCtrl |= _BIT4)
#define CLR_FRCENABLE()             (g_ucMemoryCtrl &= ~_BIT4)

//--------------------------------------------------
// Marco of FRC Enable
//--------------------------------------------------
#define GET_FRCDOUBLEFRAME()        (bit)(g_ucMemoryCtrl & _BIT5)
#define SET_FRCDOUBLEFRAME()        (g_ucMemoryCtrl |= _BIT5)
#define CLR_FRCDOUBLEFRAME()        (g_ucMemoryCtrl &= ~_BIT5)


//----------------------------------------------------------------------------------------------------

