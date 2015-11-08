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
// ID Code      : Global.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Data Type Redefine
//--------------------------------------------------
typedef unsigned char BYTE;
typedef char          SBYTE;
typedef unsigned int  WORD;
typedef int           SWORD;
typedef unsigned long DWORD;
typedef long          SDWORD;


//--------------------------------------------------
// Definations of Physical Boolean
//--------------------------------------------------
#define _TRUE                           1
#define _FALSE                          0
#define _HIGH                           1
#define _LOW                            0
#define _ENABLE                         1
#define _DISABLE                        0
#define _READ                           1
#define _WRITE                          0
#define _ON                             1
#define _OFF                            0
#define _SUCCESS                        1
#define _FAIL                           0
#define _STABLE                         1
#define _UNSTABLE                       0
#define _POSITIVE                       1
#define _NEGATIVE                       0
#define _NEWMODE                        1
#define _OLDMODE                        0
#define _ODD                            1
#define _EVEN                           0


//--------------------------------------------------
// Definitions of Page
//--------------------------------------------------
#define _PAGE0                          0
#define _PAGE1                          1
#define _PAGE2                          2
#define _PAGE3                          3
#define _PAGE4                          4
#define _PAGE5                          5
#define _PAGE6                          6
#define _PAGE7                          7
#define _PAGE8                          8
#define _PAGE9                          9
#define _PAGEA                          10
#define _PAGEB                          11
#define _PAGEC                          12
#define _PAGED                          13
#define _PAGEE                          14
#define _PAGEF                          15
#define _PAGE10                         16
#define _PAGE_COMMON                    255


//--------------------------------------------------
// Definitions of Bits
//--------------------------------------------------
#define _BIT0                           0x0001
#define _BIT1                           0x0002
#define _BIT2                           0x0004
#define _BIT3                           0x0008
#define _BIT4                           0x0010
#define _BIT5                           0x0020
#define _BIT6                           0x0040
#define _BIT7                           0x0080
#define _BIT8                           0x0100
#define _BIT9                           0x0200
#define _BIT10                          0x0400
#define _BIT11                          0x0800
#define _BIT12                          0x1000
#define _BIT13                          0x2000
#define _BIT14                          0x4000
#define _BIT15                          0x8000


//--------------------------------------------------
// Definitions of SourceHandler State
//--------------------------------------------------
#define _SOURCE_AUTO_CHANGE_STATE       0
#define _CLR_AUTO_CHANGE_STATE          1
#define _SWITCH_INPUT_SOURCE_STATE      2


//--------------------------------------------------
// Definitions for 24/18 Bit, Temporal Dithering On/Off,
// Display Single/Double Port, Even/Odd Swap, Red/Blue Swap,
// MSB/LSB Swap, DVS/DHS/DEN Output Invert.
//--------------------------------------------------
#define _DISP_24_BIT                    0
#define _DISP_18_BIT                    1
#define _DISP_SINGLE_PORT               0
#define _DISP_DOUBLE_PORT               1


//--------------------------------------------------
// Definitions of ModeHandler State
//--------------------------------------------------
#define _PWOFF_STATE                    0
#define _INITIAL_STATE                  1
#define _SEARCH_STATE                   2
#define _ACTIVE_STATE                   3
#define _NOSUPPORT_STATE                4
#define _NOSIGNAL_STATE                 5
#define _SLEEP_STATE                    6
#define _CHECK_STATE                    7


//--------------------------------------------------
// Definitions of Hsync Type Detection Auto Run Result
//--------------------------------------------------
#define _NO_SIGNAL                      0
#define _NOT_SUPPORT                    1
#define _YPBPR_SYNC                     2
#define _SERRATION_CS                   3
#define _XOR_OR_TYPE_CS_WITH_EQR        4
#define _XOR_OR_TYPE_CS_WITHOUT_EQR     5
#define _SEPARATE_HSYNC                 6
#define _HSYNC_WITHOUT_VS               7

//--------------------------------------------------
// Definitions of Hsync Source Type
//--------------------------------------------------
#define _SOURCE_FROM_NONE               0
#define _SOURCE_FROM_HS_RAW             1
#define _SOURCE_FROM_SOG                2
#define _SOURCE_FROM_YPBPR              3

//--------------------------------------------------
// Definitions of Input Sync Type State
//--------------------------------------------------
#define _NO_SYNC_STATE                  0
#define _SS_STATE                       1
#define _CS_STATE                       2
#define _SOG_STATE                      3
#define _SOY_STATE                      4
#define _DSS_STATE                      5
#define _VIDEO8_STATE                   6


//--------------------------------------------------
// Definitions of Mode Search Type
//--------------------------------------------------
#define _PRESET_MODE_TYPE               0
#define _USER_MODE_TYPE                 1


//--------------------------------------------------
// Definitions of Waiting Events
//--------------------------------------------------
#define _EVENT_IVS                      0x01
#define _EVENT_IEN_START                0x02
#define _EVENT_IEN_STOP                 0x04
#define _EVENT_DVS                      0x08
#define _EVENT_DEN_START                0x10
#define _EVENT_DEN_STOP                 0x20
#define _EVENT_UNDERFLOW                0x40
#define _EVENT_OVERFLOW                 0x80


//--------------------------------------------------
// Definations of Scaler Write/Read Type
//--------------------------------------------------
#define _NON_AUTOINC                    1
#define _AUTOINC                        0
#define _BURST                          2
#define _END                            0


//--------------------------------------------------
// Definations of Load OSD Font Table Type
//--------------------------------------------------
#define _NORMAL_FONT                    0x00
#define _COMPRESS_FONT                  0x01


//--------------------------------------------------
// Definations of Red/Green/Blue
//--------------------------------------------------
#define _RED                            0
#define _GREEN                          1
#define _BLUE                           2

//--------------------------------------------------
// Definations of PLL Type
//--------------------------------------------------
#define _DPLL                           0
#define _MPLL                           1

//--------------------------------------------------
// Definations of DDC Channel
//--------------------------------------------------
#define _DDC2                           0
#define _DDC3                           1
#define _NO_DDC                         2


//--------------------------------------------------
// Definations of SOG Input MUX Select
//--------------------------------------------------
#define _SOG1                           0
#define _B1                             1
#define _G1                             2
#define _R1                             3
#define _SOG0                           4
#define _B0                             5
#define _G0                             6
#define _R0                             7


//--------------------------------------------------
// Definations of Scaling
//--------------------------------------------------
#define _SCALE_DOWN                     0
#define _SCALE_UP                       1


//--------------------------------------------------
// Definitions of Display Delay
//--------------------------------------------------
#define _CAPTURE_HDELAY                 3
#define _PROGRAM_HDELAY                 10
#define _PROGRAM_VDELAY                 2

#define _MEASURE_HDEALY                 7


//--------------------------------------------------
// Definitions of MCU Clock Divider Number
//--------------------------------------------------
#define _DIV_1                          1
#define _DIV_2                          2
#define _DIV_3                          3
#define _DIV_4                          4
#define _DIV_5                          5
#define _DIV_6                          6
#define _DIV_7                          7
#define _DIV_8                          8
#define _DIV_9                          9


//--------------------------------------------------
// Definitions of Panel Resolution
//--------------------------------------------------
enum PanelResolutionDef
{
    _1024_768 = 0,
    _1280_720,
    _1280_1024,
    _1440_900,
    _1680_1050,
    _1600_1200,
    _1400_1050,
    _1920_1200
};


//--------------------------------------------------
// Global Macros
//--------------------------------------------------
#define LOBYTE(w)                       ((BYTE)(w))
#define HIBYTE(w)                       ((BYTE)(((WORD)(w) >> 8) & 0x00FF))
#define SEC(x)                          (100 * x)

#define MAXOF(a, b)                     (((a) > (b)) ? (a) : (b))
#define MINOF(a, b)                     (((a) < (b)) ? (a) : (b))

#define SHL(x, y)                       ((x) << (y))
#define SHR(x, y)                       ((x) >> (y))
#define AND(n1, n2)                     ((n1) & (n2))

#define ABSDWORD(x, y)                  ((x > y) ? (x - y) : (y - x))


//--------------------------------------------------
// Link training status
//--------------------------------------------------
#define _TRAINING_PATTERN_END               0
#define _TRAINING_PATTERN1                  1
#define _TRAINING_PATTERN2                  2
#define _TRAINING_PATTERN1_PASS             3
#define _TRAINING_PATTERN1_FAIL             4
#define _TRAINING_PATTERN2_PASS             5
#define _TRAINING_PATTERN2_FAIL             6
#define _TRAINING_PATTERN_NONE              7
#define _TRAINING_PATTERN_FAIL              8


//--------------------------------------------------
// DisplayPort Power status
//--------------------------------------------------
#define _DP_POWER_INITIAL                   0
#define _DP_POWER_NORMAL                    1
#define _DP_POWER_DOWN                      2

//--------------------------------------------------
// reserved for pin define
//--------------------------------------------------
#define MCU_EMPTY_PIN_ASSIGN_ADDRESS        0

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
//--------------------------------------------------
// reserved for pin define
//--------------------------------------------------
#define _RGB_COLOR_FORMAT                   0
#define _YUV_COLOR_FORMAT                   1
// V012 Modify 20100304 End
#define  DefaultCurveFactor                   1
