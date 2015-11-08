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


#if(_DDCCI_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// ID Code      : Realtek_DDCCI.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define _DDC2B_CLEAR                            0
#define _DDC2B_SRCADDRESS                       1
#define _DDC2B_COMMAND                          2
#define _DDC2B_RECBODY                          3
#define _DDC2B_WAITFORCK                        4
#define _DDC2B_COMPLETED                        5

#define _DDC2B_DEST_ADDRESS                     0x6e
#define _DDC2B_SRC_ADDRESS                      0x51
#define _DDC2Bi_PROTOCOL_ID                     0x01
#define _DDC2Bi_CONTROL_STATUS_FLAG             0x80

#define _FIRMWARE_VERSION                       0x01

#define _INITRxCK                               (_DDC2B_SRC_ADDRESS ^ _DDC2B_DEST_ADDRESS)
#define _INITTxCK                               (0x50 ^ _DDC2B_DEST_ADDRESS)

#define _GETVCP_PARAM                           6

//--------------------------------------------------
// Audio Fuction
//--------------------------------------------------
#define _DDCCI_AUDIO_SUPPORT                    _DISABLE
#define _DDCCI_FUNCTION                         _ON

//--------------------------------------------------
//
//--------------------------------------------------
#define _DDC_SOURCE                             0
#define _DDC_LENGTH                             1
#define _COMMAND                                2       //FoxconnFactoryCommand:Slave
#define _PARAMETER                              3       //FoxconnFactoryCommand:Function
#define _ITEM                                   4       //FoxconnFactoryCommand:Item
#define _VALUE                                  5       //FoxconnFactoryCommand:Value
#define _SETVCP_PARAM                           _VALUE

#define _DDC2B_CMD_GetVCPFeature                0x01
#define _DDC2B_CMD_GetVCPFeature_Reply          0x02
#define _DDC2B_CMD_SetVCPFeature                0x03
#define _DDC2B_CMD_GetTimingReport              0x07
#define _DDC2B_CMD_SaveCurrentSettings          0x0C
#define _DDC2B_CMD_CapabilitiesRequest_Reply    0xE3
#define _DDC2B_CMD_CapabilitiesRequest          0xF3

// RC
#define _DDC2B_CMD_GetVCP_RC_NoError            0x00
#define _DDC2B_CMD_GetVCP_RC_Unsupported        0x01

// TP
#define _DDC2B_CMD_GetVCP_TP_SetParameter       0x00
#define _DDC2B_CMD_GetVCP_TP_Momentary          0x01

//--------------------------------------------------
// DDCCI Command
//--------------------------------------------------
#define _DDC2B_CMD_VCP_NewControlValue          0x02
#define _DDC2B_CMD_VCP_FactoryReset             0x04
#define _DDC2B_CMD_VCP_RecallBriCon             0x05
#define _DDC2B_CMD_VCP_GeometryReset            0x06
#define _DDC2B_CMD_VCP_ColorReset               0x08
#define _DDC2B_CMD_VCP_ColorTempIncrement       0x0B
#define _DDC2B_CMD_VCP_ColorTempRequest         0x0C
#define _DDC2B_CMD_VCP_Clock                    0x0E
#define _DDC2B_CMD_VCP_Brightness               0x10
#define _DDC2B_CMD_VCP_Contrast                 0x12
#define _DDC2B_CMD_VCP_SelectColorPreset        0x14
#define _DDC2B_CMD_VCP_RedGain                  0x16
#define _DDC2B_CMD_VCP_GreenGain                0x18
#define _DDC2B_CMD_VCP_BlueGain                 0x1A
#define _DDC2B_CMD_VCP_AutoSetUp                0x1E
#define _DDC2B_CMD_VCP_AutoColor                0x1F
#define _DDC2B_CMD_VCP_HPosition                0x20
#define _DDC2B_CMD_VCP_VPosition                0x30

#define _DDC2B_CMD_VCP_ClockPhase               0x3E
#define _DDC2B_CMD_VCP_ActiveControl            0x52
#define _DDC2B_CMD_VCP_ColorTemp                0x54
#define _DDC2B_CMD_VCP_InputSource              0x60
#define _DDC2B_CMD_VCP_AudioVolume              0x62

#define _DDC2B_CMD_VCP_RedBlackLevel            0x6C
#define _DDC2B_CMD_VCP_GreenBlackLevel          0x6E
#define _DDC2B_CMD_VCP_BlueBlackLevel           0x70
#define _DDC2B_CMD_VCP_PRODUCTKEY               0x7E
#define _DDC2B_CMD_VCP_Sharpness                0x87
#define _DDC2B_CMD_VCP_TVSaturation             0x8A
#define _DDC2B_CMD_VCP_TVSharpness              0x8C
#define _DDC2B_CMD_VCP_RED                      0x9B
#define _DDC2B_CMD_VCP_YELLOW                   0x9C
#define _DDC2B_CMD_VCP_GREEN                    0x9D
#define _DDC2B_CMD_VCP_CYAN                     0x9E
#define _DDC2B_CMD_VCP_BLUE                     0x9F
#define _DDC2B_CMD_VCP_MAGENDA                  0xA0
#define _DDC2B_CMD_VCP_SyncType                 0xA8
#define _DDC2B_CMD_VCP_HFreq                    0xAC
#define _DDC2B_CMD_VCP_VFreq                    0xAE
#define _DDC2B_CMD_VCP_PanelType                0xB2
#define _DDC2B_CMD_VCP_RGBodering               0xB4
#define _DDC2B_CMD_VCP_MonitorType              0xB6
#define _DDC2B_CMD_VCP_UsageTime                0xC0
#define _DDC2B_CMD_VCP_ApplicationEnable        0xC6
#define _DDC2B_CMD_VCP_ControllerType           0xC8
#define _DDC2B_CMD_VCP_FWLevel                  0xC9
#define _DDC2B_CMD_VCP_OSDOnOff                 0xCA
#define _DDC2B_CMD_VCP_OSDLanguage              0xCC
#define _DDC2B_CMD_VCP_PowerMode                0xD6

#define _DDC2B_CMD_VCP_DISPLAY_APPLICATION      0xDC

#define _DDC2B_CMD_VCP_Version                  0xDF
#define _DDC2B_CMD_VCP_ControlLock              0xE3

#define _DDC2B_CMD_VCP_Manufacturer             0xFD

#define _DDCCI_RXBUF_LENGTH                     40
#define _DDCCI_TXBUF_LENGTH                     40

#define _DDC2Bi_VIRTUAL_HOST_ADDRESS            0x50

#define _DDCCI_BlACKLEVEL_DEFAULT               0x50
#define _DDCCI_USER_COLOR_DEFAULT               0x80



#ifdef _REALTEK_DDCCI_

BYTE code tCP_STRING_DSUB[] =
{
    "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 0E 10 12 14(01 02 04 05 08) 16 18 1A 1E 1F 20 30 3E 52 60(01 03 0F) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF FD FF)mswhql(1)asset_eep(40)mccs_ver(2.1))"
};

#if(_TMDS_SUPPORT == _ON)
BYTE code sCP_STRING_DVI[] =
{
    "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 10 12 14(01 02 04 05 08) 16 18 1A 52 60(01 03 0F) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF FD FF)mswhql(1)asset_eep(40)mccs_ver(2.1))"
};
#endif

#if(_DP_SUPPORT == _ON)
unsigned char code stCapabilitiesStringDisplayPort[] =
{
    "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 10 12 14(01 02 04 05 08) 16 18 1A 52 60(01 03 0F) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF FD FF)mswhql(1)asset_eep(40)mccs_ver(2.1))"
};
#endif


BYTE code tCOLORPRESET_VALUE[] = {0x08, 0x05, 0x04, 0x01, 0x02};
BYTE code tINPUTSOURCEPORT[] = {0x03, 0x01, 0x0F};
BYTE code tLANGUAGEDEFINE[] = {0x02, 0x03, 0x04, 0x0a, 0x01, 0x0d, 0x06};

#define _CREQLEN_DSUB   sizeof(tCP_STRING_DSUB)
#if(_TMDS_SUPPORT == _ON)
#define _CREQLEN_DVI    sizeof(sCP_STRING_DVI)
#endif

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE xdata g_ucDdcciRxBuf[_DDCCI_RXBUF_LENGTH] = {0};
BYTE xdata g_ucDdcciTxBuf[_DDCCI_TXBUF_LENGTH] = {0};

BYTE xdata g_ucDdcciRedBlackLevel = _DDCCI_BlACKLEVEL_DEFAULT;
BYTE xdata g_ucDdcciGreenBlackLevel = _DDCCI_BlACKLEVEL_DEFAULT;
BYTE xdata g_ucDdcciBlueBlackLevel = _DDCCI_BlACKLEVEL_DEFAULT;

BYTE xdata g_ucDdcciTxCount = 0;
BYTE xdata g_ucDdcciNewControlValue = 1;

BYTE xdata g_ucDdcciActiveValue = 0;

BYTE xdata g_ucColorTempUnSupport = 0;
BYTE xdata g_RxStatus = _DDC2B_CLEAR;

BYTE xdata g_ucDdcciDP_Ready = 0;
BYTE xdata ucDdcciDP_Pending = 0;
BYTE xdata ucDdcciDP_PreVCP = 1;
BYTE xdata ucDdcciDP_Read = 0;
BYTE xdata ucDdcciDP_ReplyDone = 0;
BYTE xdata ucDdcciDP_ReSend = 0;
BYTE xdata ucDdcciDP_PreOP = 0;
BYTE xdata ucDdcciDP_OverRead = 0;

// QD unstable behavior for sending command
BYTE xdata g_ucActiveInputSourceType = 0;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
BYTE CDdcDDCCI_CalCheckSum(BYTE sum);

void CDdcDDCCI_InitRx(void);
void CDDC2Bi_InitTx(void);
void CDdcDDCCI_Command(void);

void CDdcTxCommandReady(void);

void CDdcGetVCPFeature();

void CDdcciGetVCPFeature(BYTE opcode, WORD Max, WORD Present);
void CDdcGetVPC_HFreq(BYTE BaseAddr);
void GetVPC_DisplayApplication(BYTE BaseAddr);

void CDdcSetVCPFeature();
void SetVPC_NewControlValue(BYTE ucValue);
void SetVPC_FactoryReset(BYTE ucValue);
void SetVPC_RecallBriCon(BYTE ucValue);
void SetVPC_GeometryReset(BYTE ucValue);
void SetVPC_ColorReset(BYTE ucValue);
void SetVPC_ColorTempRequest(BYTE ucValue);
void SetVPC_Clock(BYTE ucValue);
void SetVPC_Bright(BYTE ucValue);
void SetVPC_Contrast(BYTE ucValue);
void SetVPC_SelectColorPreset(BYTE ucValue);
void SetVPC_RedGain(BYTE ucValue);
void SetVPC_GreenGain(BYTE ucValue);
void SetVPC_BlueGain(BYTE ucValue);
void SetVPC_AutoSetUp(BYTE ucValue);
void SetVPC_AutoColor(BYTE ucValue);
void SetVPC_HPosition(BYTE ucValue);
void SetVPC_VPosition(BYTE ucValue);
void SetVPC_Phase(BYTE ucValue);

#if (_DDCCI_AUDIO_SUPPORT == _ENABLE)
void SetVPC_AudioVolume(BYTE ucValue);
#endif
void GetVPC_ActiveControl(BYTE BaseAddr);
void GetVPC_InputSource(BYTE BaseAddr);
void SetVPC_RedBlackLevel(BYTE ucValue);
void SetVPC_GreenBlackLevel(BYTE ucValue);
void SetVPC_BlueBlackLevel(BYTE ucValue);
void CDdcGetVPC_PRODUCTKEY(BYTE BaseAddr);
void SetVPC_OSDOnOff(BYTE ucValue);
void SetVPC_OSDLanguage(BYTE ucValue);
void SetVPC_PowerMode(BYTE ucValue);
void CDdcDDCCI_GetTimingReport();
void CDdcDDCCI_SaveSetting();
void CDdcDDCCI_GetCapabilitiesRequest();
void GetVPC_Sharpness(BYTE BaseAddr);
void GetVPC_ColorTempRequest(BYTE BaseAddr);
void CDdcDdcciResetAllSettings(void);
void CDdcDdcciColorReset(void);
void CDdcDdcciRecallBriCon(void);
bit CDdcDdcciSetVCPCheck(void);

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE xdata g_ucDdcciRxBuf[_DDCCI_RXBUF_LENGTH];
extern BYTE xdata g_ucDdcciTxBuf[_DDCCI_TXBUF_LENGTH];
extern BYTE xdata g_ucDdcciRedBlackLevel;
extern BYTE xdata g_ucDdcciGreenBlackLevel;
extern BYTE xdata g_ucDdcciBlueBlackLevel;
extern BYTE xdata g_ucDdcciTxCount;
extern BYTE xdata g_ucDdcciNewControlValue;
extern BYTE xdata g_ucDdcciActiveValue;

extern BYTE xdata g_ucColorTempUnSupport;
extern BYTE xdata g_RxStatus;
extern BYTE xdata g_ucDdcciDP_Ready;
extern BYTE xdata ucDdcciDP_Pending;
extern BYTE xdata ucDdcciDP_PreVCP;
extern BYTE xdata ucDdcciDP_Read;
extern BYTE xdata ucDdcciDP_ReplyDone;
extern BYTE xdata ucDdcciDP_ReSend;
extern BYTE xdata ucDdcciDP_PreOP;
extern BYTE xdata ucDdcciDP_OverRead;

// QD unstable behavior for sending command
extern BYTE xdata g_ucActiveInputSourceType;

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CDdcDDCCI_Command(void);
extern void CDdcTxCommandReady(void);
extern void CDDC2Bi_InitTx(void);

extern void  CDdcDDCCI_GetCapabilitiesRequest(void);
extern void CDdcDdcciResetAllSettings(void);
extern void CDdcDdcciColorReset(void);
extern void CDdcDdcciRecallBriCon(void);
extern bit CDdcDdcciSetVCPCheck(void);

#endif  // End of #ifdef __DELL_ULTRASHARP_DDCCI__

#endif  // End of #if 0


