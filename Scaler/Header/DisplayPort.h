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
// ID Code      : DisplayPort.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// StreamClk Regenerator DPLLMode
// Recommand function: VS Tracking mode
//--------------------------------------------------
#define _XTAL                           0
#define _LINKCLK                        1

#define _DP_DPLL_INPUT_SEL              _XTAL

//--------------------------------------------------
// Tracking  Mode
// recommand function: VS Tracking mode
//--------------------------------------------------
#define _NONE_TRACKING                  0
#define _MNTRACKING                     1
#define _VSTRACKING                     2
#define _VS_AND_MN_TRACKING             3

#define _TRACKING_MODE                  _MNTRACKING

//--------------------------------------------------
//Tracking  FIFO overflow underflow Mode
//--------------------------------------------------
#define _FRONT_PORCH_REGENERATOR        _ON

//--------------------------------------------------
// Display Format
// recommand function: full last line mode
//--------------------------------------------------
#define _FRAME_SYNC_MODE                0
#define _FULL_LAST_LINE                 1

#define _DP_DISPLAY_FORMAT_SEL          _FRAME_SYNC_MODE

//--------------------------------------------------
// Definations of Display Interlace Setting
//--------------------------------------------------
#define _DP_INTERLACE                   _ON

//--------------------------------------------------
// Definations of Display Cable Times
//--------------------------------------------------
#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
#define _DP_CABLE_TIME                  30
#define _DP_CABLE_TIMESTEP              10
#endif

//--------------------------------------------------
// Regenerator StreamClk Style
//--------------------------------------------------
#define _BY_MN_VALUE                    0
#define _BY_MEASUREMENT                 1

#define _DP_STREAM_CLOCK_SEL            _BY_MN_VALUE

//--------------------------------------------------
// YCbCr mode transfer to RGB Mode table enable or disable
//--------------------------------------------------
/*
#define _YPBPR_TABLE_SET_SCALER        _ON        // DP support YCbCr mode
*/

//--------------------------------------------------
// Power Management Function
//--------------------------------------------------
#define _DP_POWER_MANAGEMENT           _ON

//--------------------------------------------------
// FIFO TRACKING TIMES
//_BOUNDARY_CHECK_NUM: Adjust BStoVSDelay for different the Vertical Blanking(VBID[0]) Start Position [unit:1-Line]
//_SEARCH_RANGE: from Minmum value to Maxmum non-overflow/underflow check times (step 0x18 link clk)
//_TIMEOUT_NUM: In this range, If can't search the Minimum value, program will drop out to search state
//_PHY_DETECT_MODE_SEARCH_TIMES: after aux channel handshaking, PHY need to re-detect D10.2 sync pattern to fine the speed bandwidth
//--------------------------------------------------

#define _BOUNDARY_CHECK_NUM             1  // (for nVidia case)
#define _TIMEOUT_NUM                    6
#define _SEARCH_RANGE                   2
#define _HWIDTH_BUFFER_RATIO            2


#ifdef __DISPLAYPORT__

BYTE code tDP_NO_PORT_WARNING[] = { 0x00,};

//--------------------------------------------------
// Global Variables
//--------------------------------------------------

BYTE xdata g_ucDisplayPortCtrl = 0;
BYTE xdata g_ucDisplayPortStatus = 0;
BYTE xdata g_ucDisplayPortLtPreStatus = 0;

BYTE xdata g_ucLane01Status = 0;
BYTE xdata g_ucLane23Status = 0;
BYTE xdata g_ucAdjustRequestL01 = 0;
BYTE xdata g_ucAdjustRequestL23 = 0;

BYTE xdata g_ucDpPowerStatus = 0;

BYTE xdata g_ucFifoFailCount = 0;
BYTE xdata g_ucPhyUnstableCount = 0;
BYTE xdata g_ucMisAlignCount = 0;
BYTE xdata g_ucChangeDisplayCount = 0;
BYTE xdata g_ucDpResetCount = 0;

DWORD xdata g_ulDpMvidValue = 0;
WORD xdata g_usDpHactive = 0;
WORD xdata g_usDpVactive = 0;
BYTE xdata g_ucDpMsaMisc = 0;

BYTE xdata g_ucDpTPStatus = 0;
BYTE xdata g_ucDpRate = 0;
BYTE xdata g_ucDpLaneCount = 0;
BYTE xdata g_ucTP1Error = 0;
BYTE xdata g_ucTP1Decode = 0;
BYTE xdata g_ucTP1Decode1 = 0;
BYTE xdata g_ucTP1Decode2 = 0;
BYTE xdata g_ucCrcLane1 = 0;
BYTE xdata g_ucCrcLane2 = 0;
BYTE xdata g_ucTrainingLaneSet = 0;
BYTE xdata g_ucButInt = 0;
BYTE xdata g_ucAlignStatus = 0;


BYTE xdata g_ucRegPageBackUp = 0;
BYTE xdata g_ucRegIntBackUp = 0;
BYTE xdata g_ucRegAddrBackUp = 0;
BYTE xdata g_ucRegPortBackUp[4] = 0;

bit idata g_bDpFakeLT = 0;
bit idata g_bFakeTP1Pass = 0;
bit idata g_bFakeTP2Pass = 0;
bit idata g_bFakeTPEndPass = 0;

bit idata g_bHDCPFail = 0;
bit idata g_bDpSearchTimesReset = 0;
bit idata g_bDpCRCStart = 0;
bit idata g_bDpDisplayPass = 0;
bit idata g_bDpPowerDown = 0;
bit idata g_bDpPlug = 0;

bit idata g_bDpCPIRQ = 0;
bit idata g_bLTLane0FirstPass = 0;
bit idata g_bLTLane1FirstPass = 0;
bit idata g_bLTLane2FirstPass = 0;
bit idata g_bLTLane3FirstPass = 0;
bit idata g_bLT2Lane0FirstPass = 0;
bit idata g_bLT2Lane1FirstPass = 0;
bit idata g_bLT2Lane2FirstPass = 0;
bit idata g_bLT2Lane3FirstPass = 0;


//--------------------------------------------------
// Display port Table
//--------------------------------------------------

BYTE code tDISP_PORT_IRQCLEAR[] =
{
    // SDRAM Setting
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGEC,
    4,  _NON_AUTOINC,   _PC_DP_ACCESS_PORT_B3,          0xcc,
    4,  _NON_AUTOINC,   _PC_DP_DATA_PORT_B4,            0x80,
    4,  _NON_AUTOINC,   _PC_AUX_IRQ_STATUS_DC,          0xff,

    _END

};

BYTE code tDP_DPCD_INITIAL[] =
{
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGEC,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x02,0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x03,0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x04,0x80,

    // ATI Dos mode bug
    4,  _NON_AUTOINC,   _PC_AUX_MODE_SET_D0,            0xE1,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x01,0x00,0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x01,0x01,0x00,
    4,  _NON_AUTOINC,   _PC_AUX_MODE_SET_D0,            0xE3,

    _END
};

BYTE code tDP_HDCP_BKSV_KEY[] =
{
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGEC,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x06,0x80,0x00,0xB7,
    5,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_L_C3,      0x01,0x28,
    5,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_L_C3,      0x02,0xA9,
    5,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_L_C3,      0x03,0x51,
    5,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_L_C3,      0x04,0xD6,

    _END
};

#if(_DP_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// DP HDCD Table
//----------------------------------------------------------------------------------------------------

BYTE code tDP_DPCD_TABLE[] =
{
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGEC,

    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x00,0x11, // 10=Ver 1.0, 11=Ver 1.1

#if (_LINK_CLK_RATE == _LOW_SPEED_162Mhz)
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x01,0x06,
#elif (_LINK_CLK_RATE == _HIGH_SPEED_270Mhz)
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x01,0x0A,
#endif

#if (_MAIN_LINK_LANES == _ONE_LANE)
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x02,0x81,
#elif (_MAIN_LINK_LANES == _TWO_LANE)
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x02,0x82,
#elif (_MAIN_LINK_LANES == _FOUR_LANE)
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x02,0x84,
#endif

    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x03,0x01, // dpcd fcchang old 0x00
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x04,0x01,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x05,0x00,
    4,  _NON_AUTOINC,   _PC_AUX_MODE_SET_D0,            0xE1,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x06,0x01,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x07,0x01, // dpcd fcchang old 0x00
    4,  _NON_AUTOINC,   _PC_AUX_MODE_SET_D0,            0xE3,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x08,0x02,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x09,0x00,

    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x0A, 0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x00,0x0B, 0x00,

    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x00, 0x41, // dpcd fcchang old 0x00
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x01, 0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x05, 0x00, // for sink status report (03->00)
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x08, 0x00,

    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x09, 0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x0A, 0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x0B, 0x00,

    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x10, 0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x11, 0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x12, 0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x13, 0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x14, 0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x15, 0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x16, 0x00,

    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x17, 0x00,
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x02,0x46, 0x20,

    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x04,0x00, 0x4C, // dpcd fcchang old 0x00 IEEE OUI realtek
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x04,0x01, 0xE0, // dpcd fcchang old 0x00 IEEE OUI realtek
    7,  _AUTOINC,       _PC_DPCD_ACCESS_PORT_H_C1,      0x00,0x04,0x02, 0x00, // dpcd fcchang old 0x00 IEEE OUT realtek

    _END
};

#endif //(_DP_SUPPORT == _ON)

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CDpTrainPattern1(void);
void CDpTrainPattern2(void);
void CDpTrainPatternEnd(void);
void CDpTrainPatternNone(void);

void CDpInitial(void);
void CDpPowerDown(void);
void CDpInterruptInitial(void);
void CDpHotPlugProc(BYTE ms);
bit CDpIsDisplayPortPhyStable(void);
DWORD CDpGetVsyncFrontPorch(void);
DWORD CDpGetHsyncFrontPorch(void);
void CDpDisplayFormatInitial(void);
bit CDpIsFifoUnderOverFlow(void);
void CDpMacInitial(void);
void CDpAdjustVsyncDelayCount(void);
void CDpVideoSetting(void);
bit CDpStreamClkRegeneratByMN(void);
bit CDpStreamClkRegeneratByHVtotal(void);
bit CDpStartupSetting(void);
void CDpMacInitial(void);

bit CDpDisplayFormatChange(void);
bit CDpIsDisplayPortVideoStream(void);
bit CDpAlignCheck(void);

void CDpMacReset(void);
void CDpSinkStatusSet(bit);
void CDpShortHotPlugProc(BYTE ms);
bit CDpMsaIsChange(void);
void CDpGetMsaValue(void);

#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
bit CDpCableConnect(void);
#endif

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

#if (_DP_PHYCTS_STEPBYSTEP == _ON)
void CDPPHYCTSSTEP(void);
#endif

#endif

void CDpFakeTrainPattern1(void);
void CDpFakeTrainPattern2(void);
void CDpFakeTrainPatternEnd(void);

void CDpFastlinktrainSet(void);

bit CDpHDCPStatus(void);

void CDpAdjustHDCP(void);

void CDpCRCTest(void);


void CDpTP1Lane0Check(void);
void CDpTP1Lane1Check(void);
void CDpTP1Lane2Check(void);
void CDpTP1Lane3Check(void);

void CDpTP21LaneCheck(void);
void CDpTP22LaneCheck(void);
void CDpTP24LaneCheck(void);

bit CDpActiveCheckFail(void);
bit CDpNosupportCheck(void);

void CDpHDCPReset(void);

void CDpCPIRQ(BYTE ms);

#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
bit CDpAuxPinCableConnect(void);
#endif

bit CDpLinkStatusCheck(void);

//-------------------------------------------------
//  Macro of One Lane Flag
//--------------------------------------------------
#define GET_DP_ONE_LANE_INPUT()             (bit)(g_ucDisplayPortCtrl & _BIT0)
#define SET_DP_ONE_LANE_INPUT()             (g_ucDisplayPortCtrl |= _BIT0)
#define CLR_DP_ONE_LANE_INPUT()             (g_ucDisplayPortCtrl &= ~_BIT0)


//--------------------------------------------------
// Macro of Two Lane Flag
//--------------------------------------------------
#define GET_DP_TWO_LANE_INPUT()             (bit)(g_ucDisplayPortCtrl & _BIT1)
#define SET_DP_TWO_LANE_INPUT()             (g_ucDisplayPortCtrl |= _BIT1)
#define CLR_DP_TWO_LANE_INPUT()             (g_ucDisplayPortCtrl &= ~_BIT1)


//--------------------------------------------------
//  Macro of Four Lane Flag
//--------------------------------------------------
#define GET_DP_FOUR_LANE_INPUT()            (bit)(g_ucDisplayPortCtrl & _BIT2)
#define SET_DP_FOUR_LANE_INPUT()            (g_ucDisplayPortCtrl |= _BIT2)
#define CLR_DP_FOUR_LANE_INPUT()            (g_ucDisplayPortCtrl &= ~_BIT2)


//--------------------------------------------------
// Macro of Enhancement Mode
//--------------------------------------------------
#define GET_DP_ENHANCEMENT_MODE()           (bit)(g_ucDisplayPortCtrl & _BIT3)
#define SET_DP_ENHANCEMENT_MODE()           (g_ucDisplayPortCtrl |= _BIT3)
#define CLR_DP_ENHANCEMENT_MODE()           (g_ucDisplayPortCtrl &= ~_BIT3)


//--------------------------------------------------
// Macro of Scrambling Mode
//--------------------------------------------------
#define GET_DP_SCRAMB_MODE()                (bit)(g_ucDisplayPortCtrl & _BIT4)
#define SET_DP_SCRAMB_MODE()                (g_ucDisplayPortCtrl |= _BIT4)
#define CLR_DP_SCRAMB_MODE()                (g_ucDisplayPortCtrl &= ~_BIT4)


//--------------------------------------------------
// Macro of 0.5% Down Spreading
//--------------------------------------------------
#define GET_DP_DOWN_SPREADING()             (bit)(g_ucDisplayPortCtrl & _BIT5)
#define SET_DP_DOWN_SPREADING()             (g_ucDisplayPortCtrl |= _BIT5)
#define CLR_DP_DOWN_SPREADING()             (g_ucDisplayPortCtrl &= ~_BIT5)

//--------------------------------------------------
// Macro of 33Khz Modulation
//--------------------------------------------------
#define GET_DP_33KHZ_MODULATION()           (bit)(g_ucDisplayPortCtrl & _BIT6)
#define SET_DP_33KHZ_MODULATION()           (g_ucDisplayPortCtrl |= _BIT6)
#define CLR_DP_33KHZ_MODULATION()           (g_ucDisplayPortCtrl &= ~_BIT6)

//--------------------------------------------------
// Macro of 2.7G Data rate
//--------------------------------------------------
#define GET_DP_HIGH_SPEED_RATE()            (bit)(g_ucDisplayPortCtrl & _BIT7)
#define SET_DP_HIGH_SPEED_RATE()            (g_ucDisplayPortCtrl |= _BIT7)
#define CLR_DP_HIGH_SPEED_RATE()            (g_ucDisplayPortCtrl &= ~_BIT7)


#else
//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE xdata g_ucScalerAddr;
extern BYTE xdata g_ucDisplayPortCtrl;
extern BYTE xdata g_ucDisplayPortStatus;
extern BYTE xdata g_ucDisplayPortLtPreStatus;

// interrupt
extern BYTE xdata g_ucTP1_times;
extern BYTE xdata g_ucTP2_times;
extern BYTE xdata g_ucLane01Status;
extern BYTE xdata g_ucLane23Status;

extern BYTE xdata g_ucAdjustRequestL01;
extern BYTE xdata g_ucAdjustRequestL23;

extern BYTE xdata g_ucDpPowerStatus;
extern BYTE xdata g_ucFifoFailCount;
extern BYTE code tDP_NO_PORT_WARNING[];

extern BYTE xdata g_ucDpResetCount;
extern BYTE xdata g_ucPhyUnstableCount;
extern BYTE xdata g_ucMisAlignCount;
extern BYTE xdata g_ucChangeDisplayCount;

extern DWORD xdata g_ulDpMvidValue;
extern WORD xdata g_usDpHactive;
extern WORD xdata g_usDpVactive;
extern BYTE xdata g_ucDpMsaMisc;

extern BYTE xdata g_ucDpTPStatus;
extern BYTE xdata g_ucDpRate;
extern BYTE xdata g_ucDpLaneCount;
extern BYTE xdata g_ucTP1Error;
extern BYTE xdata g_ucTP1Decode;
extern BYTE xdata g_ucTP1Decode1;
extern BYTE xdata g_ucTP1Decode2;
extern BYTE xdata g_ucCrcLane1;
extern BYTE xdata g_ucCrcLane2;
extern BYTE xdata g_ucTrainingLaneSet;
extern BYTE xdata g_ucButInt;
extern BYTE xdata g_ucAlignStatus;

extern BYTE xdata g_ucRegPageBackUp;
extern BYTE xdata g_ucRegIntBackUp;
extern BYTE xdata g_ucRegAddrBackUp;
extern BYTE xdata g_ucRegPortBackUp[4];

extern bit idata g_bDpFakeLT;
extern bit idata g_bFakeTP1Pass;
extern bit idata g_bFakeTP2Pass;
extern bit idata g_bFakeTPEndPass;

extern bit idata g_bHDCPFail;
extern bit idata g_bDpSearchTimesReset;
extern bit idata g_bDpCRCStart;
extern bit idata g_bDpDisplayPass;
extern bit idata g_bDpPowerDown;
extern bit idata g_bDpPlug;

extern bit idata g_bDpCPIRQ;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CDpTrainPattern1(void);
extern void CDpTrainPattern2(void);
extern void CDpTrainPatternEnd(void);
extern void CDpTrainPatternNone(void);

extern void CDpInitial(void);
extern void CDpPowerDown(void);
extern void CDpInterruptInitial(void);
extern void CDpHotPlugProc(BYTE ms);
extern bit CDpIsDisplayPortPhyStable(void);
extern DWORD CDpGetVsyncFrontPorch(void);
extern DWORD CDpGetHsyncFrontPorch(void);
extern void CDpDisplayFormatInitial(void);
extern bit CDpIsFifoUnderOverFlow(void);
extern void CDpMacInitial(void);
extern void CDpAdjustVsyncDelayCount(void);
extern void CDpVideoSetting(void);
extern bit CDpStreamClkRegeneratByMN(void);
extern bit CDpStreamClkRegeneratByHVtotal(void);
extern bit CDpStartupSetting(void);
extern void CDpMacInitial(void);
extern bit CDpIsDisplayPortVideoStream(void);
extern bit CDpAlignCheck(void);

extern bit CDpDisplayFormatChange(void);
extern void CDpMacReset(void);
extern void CDpSinkStatusSet(bit);
extern void CDpShortHotPlugProc(BYTE ms);
extern bit CDpMsaIsChange(void);
extern void CDpGetMsaValue(void);

#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
extern bit CDpCableConnect(void);
#endif

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

#if (_DP_PHYCTS_STEPBYSTEP == _ON)
extern void CDPPHYCTSSTEP(void);
#endif

#endif

extern void CDpFakeTrainPattern1(void);
extern void CDpFakeTrainPattern2(void);
extern void CDpFakeTrainPatternEnd(void);
extern void CDpFastlinktrainSet(void);
extern bit CDpHDCPStatus(void);
extern void CDpAdjustHDCP(void);
extern void CDpCRCTest(void);

extern void CDpTP1Lane0Check(void);
extern void CDpTP1Lane1Check(void);
extern void CDpTP1Lane2Check(void);
extern void CDpTP1Lane3Check(void);

extern void CDpTP21LaneCheck(void);
extern void CDpTP22LaneCheck(void);
extern void CDpTP24LaneCheck(void);

extern bit CDpActiveCheckFail(void);
extern bit CDpNosupportCheck(void);

extern void CDpHDCPReset(void);

extern void CDpCPIRQ(BYTE ms);

#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
extern bit CDpAuxPinCableConnect(void);
#endif

extern bit CDpLinkStatusCheck(void);

#endif // End of #ifdef __DISPLAYPORT__
