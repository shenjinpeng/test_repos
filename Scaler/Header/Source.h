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
// ID Code      : Source.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Input Source
//--------------------------------------------------
#define _NO_PORT                            0

#define _SEARCH_POL_0                       0
#define _SEARCH_POL_1                       1
#define _SEARCH_POL_2                       2
#define _SEARCH_POL_3                       3
#define _SEARCH_POL_4                       4
#define _SEARCH_POL_5                       5
#define _SEARCH_POL_6                       6
#define _SEARCH_POL_7                       7

//----------------------------------------------------------------------------------------------------

#ifdef __SOURCE__

//--------------------------------------------------
// Input Port Data Table
//--------------------------------------------------
BYTE code tINPUT_PORT[] =
{
    _D0_INPUT_PORT,
    _D1_INPUT_PORT,
    _A0_INPUT_PORT,
    _A1_INPUT_PORT,
    _VI_INPUT_PORT,
};

BYTE code tINPUT_PORT_TYPE[] =
{
    _D0_INPUT_PORT_TYPE,
    _D1_INPUT_PORT_TYPE,
    _A0_INPUT_PORT_TYPE,
    _A1_INPUT_PORT_TYPE,
    _VI_INPUT_PORT_TYPE,
};

BYTE code tINPUT_PORT_GROUP[] =
{
    _D0_INPUT_PORT_GROUP,
    _D1_INPUT_PORT_GROUP,
    _A0_INPUT_PORT_GROUP,
    _A1_INPUT_PORT_GROUP,
    _VI_INPUT_PORT_GROUP,
};

BYTE code tINPUT_PORT_SEARCH_TIMES[] =
{
    _D0_INPUT_PORT_SEARCH_TIMES,
    _D1_INPUT_PORT_SEARCH_TIMES,
    _A0_INPUT_PORT_SEARCH_TIMES,
    _A1_INPUT_PORT_SEARCH_TIMES,
    _VI_INPUT_PORT_SEARCH_TIMES,
};

BYTE code tINPUT_PORT_SEARCH_POLARITY[] =
{
    _INPUT_PORT_SEARCH_POL_0,
    _INPUT_PORT_SEARCH_POL_1,
    _INPUT_PORT_SEARCH_POL_2,
    _INPUT_PORT_SEARCH_POL_3,
    _INPUT_PORT_SEARCH_POL_4,
};


//--------------------------------------------------
// Global Variables
//--------------------------------------------------

BYTE xdata g_ucInputInfo = 0;
BYTE xdata g_ucInputConnect = 0;
BYTE xdata g_ucSearchIndex = 0;
BYTE xdata g_ucSearchTimes = 0;
BYTE xdata g_ucSearchFinish = 0;
BYTE xdata g_ucModeStableCount = 0;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bit CSourceHandler(void);
bit CSourceScanHandler(void);
bit CSourceScanInputPort(void);
void CSourceInitialSetting(void);
void CSourceInitialConnect(void);
void CSourceSwitchPortSetting(void);
void CSourceSwitchFirstInputPort(void);
bit CSourceSwitchInputPort(BYTE inputport);
void CSourceSwitchInputSource(void);
void CSourceSaveSearchData(void);
void CSourceSetCountDown(void);

#else


//--------------------------------------------------
// Extern Input Port Data Table
//--------------------------------------------------
extern BYTE code tINPUT_PORT[5];
extern BYTE code tINPUT_PORT_TYPE[];
extern BYTE code tINPUT_PORT_GROUP[];
extern BYTE code tINPUT_PORT_SEARCH_POLARITY[];
extern BYTE code tINPUT_PORT_SEARCH_TIMES[];


//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------

extern BYTE xdata g_ucInputInfo;
extern BYTE xdata g_ucInputConnect;
extern BYTE xdata g_ucSearchIndex;
extern BYTE xdata g_ucSearchTimes;
extern BYTE xdata g_ucSearchFinish;
extern BYTE xdata g_ucModeStableCount;

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern bit CSourceHandler(void);
extern void CSourceInitialSetting(void);
extern void CSourceInitialConnect(void);
extern bit CSourceSwitchInputPort(BYTE inputport);
extern void CSourceSwitchInputSource(void);
extern void CSourceSaveSearchData(void);
extern void CSourceSetCountDown(void);


#endif // End of #ifdef __SOURCE__


//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Getting Input Source
//--------------------------------------------------
#define GET_INPUT_PORT(x)               (tINPUT_PORT[tINPUT_PORT_SEARCH_POLARITY[x]])

//--------------------------------------------------
// Macro of Getting Input Port Type
//--------------------------------------------------
#define GET_INPUTPORT_TYPE(x)           (tINPUT_PORT_TYPE[tINPUT_PORT_SEARCH_POLARITY[x]])

//--------------------------------------------------
// Macro of Getting Input Port Group Type
//--------------------------------------------------
#define GET_INPUTPORT_GROUP(x)          (tINPUT_PORT_GROUP[tINPUT_PORT_SEARCH_POLARITY[x]])

//--------------------------------------------------
// Macro of Getting Input Port Search Times
//--------------------------------------------------
#define GET_INPUTPORT_SEARCH_TIMES(x)   (tINPUT_PORT_SEARCH_TIMES[tINPUT_PORT_SEARCH_POLARITY[x]])

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Initial Search
//--------------------------------------------------
#define CLR_INPUT_SEARCH_INITIAL()      (g_ucInputInfo &= 0x00)

//--------------------------------------------------
// Macro of Source State
//--------------------------------------------------
#define GET_SOURCE_STATE()              (g_ucInputInfo & (_BIT1 | _BIT0))
#define SET_SOURCE_STATE(x)             (g_ucInputInfo = ((g_ucInputInfo & ~(_BIT1 | _BIT0)) | (x & 0x03)))

//--------------------------------------------------
// Macro of Input Source Search
//--------------------------------------------------
#define GET_INPUT_SOURCE_SEARCH()       ((bit)(g_ucInputInfo & _BIT2))
#define SET_INPUT_SOURCE_SEARCH()       (g_ucInputInfo |= _BIT2)
#define CLR_INPUT_SOURCE_SEARCH()       (g_ucInputInfo &= ~_BIT2)

//--------------------------------------------------
// Macro of the First Input Port Search
//--------------------------------------------------
#define GET_FIRST_INPUT_PORT_SEARCH()   ((bit)(g_ucInputInfo & _BIT3))
#define SET_FIRST_INPUT_PORT_SEARCH()   (g_ucInputInfo |= _BIT3)
#define CLR_FIRST_INPUT_PORT_SEARCH()   (g_ucInputInfo &= ~_BIT3)

//--------------------------------------------------
// Macro of Search Finish
//--------------------------------------------------
#define GET_SEARCH_FINISH()             ((bit)(g_ucInputInfo & _BIT4))
#define SET_SEARCH_FINISH()             (g_ucInputInfo |= _BIT4)
#define CLR_SEARCH_FINISH()             (g_ucInputInfo &= ~_BIT4)

/*
//--------------------------------------------------
// Macro of Interlace Mode Check
//--------------------------------------------------
#define GET_INTERLACE_MODE()            ((bit)(g_ucInputInfo & _BIT5))
#define SET_INTERLACE_MODE()            (g_ucInputInfo |= _BIT5)
#define CLR_INTERLACE_MODE()            (g_ucInputInfo &= ~_BIT5)
*/

//--------------------------------------------------
// Macro of Input Source Search
//--------------------------------------------------
#define GET_SEARCH_INITIAL()            ((bit)(g_ucInputInfo & _BIT5))
#define SET_SEARCH_INITIAL()            (g_ucInputInfo |= _BIT5)
#define CLR_SEARCH_INITIAL()            (g_ucInputInfo &= ~_BIT5)

//--------------------------------------------------
// Macro of Field Merge Check
//--------------------------------------------------
#define GET_FIELDMERGE_MODE(x)          ((bit)(g_ucInputInfo & _BIT6))
#define SET_FIELDMERGE_MODE(x)          (g_ucInputInfo |= _BIT6)
#define CLR_FIELDMERGE_MODE(x)          (g_ucInputInfo &= ~_BIT6)

//--------------------------------------------------
// Macro of Field TMDS Initial Check
//--------------------------------------------------
#define GET_TMDS_INITIAL()              ((bit)(g_ucInputInfo & _BIT7))
#define SET_TMDS_INITIAL()              (g_ucInputInfo |= _BIT7)
#define CLR_TMDS_INITIAL()              (g_ucInputInfo &= ~_BIT7)

//--------------------------------------------------
// Macro of A0 Connect Port
//--------------------------------------------------
#define GET_PRE_A0_CONNECT()            ((bit)(g_ucInputConnect & _BIT0))
#define SET_PRE_A0_CONNECT(x)           (g_ucInputConnect = (g_ucInputConnect & ~_BIT0) | ((BYTE)x << 0))

//--------------------------------------------------
// Macro of A1 Connect Port
//--------------------------------------------------
#define GET_PRE_A1_CONNECT()            ((bit)(g_ucInputConnect & _BIT1))
#define SET_PRE_A1_CONNECT(x)           (g_ucInputConnect = (g_ucInputConnect & ~_BIT1) | ((BYTE)x << 1))

//--------------------------------------------------
// Macro of D0 Connect Port
//--------------------------------------------------
#define GET_PRE_D0_CONNECT()            ((bit)(g_ucInputConnect & _BIT2))
#define SET_PRE_D0_CONNECT(x)           (g_ucInputConnect = (g_ucInputConnect & ~_BIT2) | ((BYTE)x << 2))

//--------------------------------------------------
// Macro of D1 Connect Port
//--------------------------------------------------
#define GET_PRE_D1_CONNECT()            ((bit)(g_ucInputConnect & _BIT3))
#define SET_PRE_D1_CONNECT(x)           (g_ucInputConnect = (g_ucInputConnect & ~_BIT3) | ((BYTE)x << 3))

