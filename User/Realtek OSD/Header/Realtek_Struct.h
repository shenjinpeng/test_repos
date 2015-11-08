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
// ID Code      : Struct.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Xdata Address
//--------------------------------------------------

//--------------------------------------------------
// Struct Type
//--------------------------------------------------
typedef struct
{
    BYTE PolarityFlag;              //
    WORD IHWidth;                   // Input Horizontal Width
    WORD IVHeight;                  // Input Vertical Height
    WORD IHFreq;                    // Input Horizontal Frequency
    WORD IVFreq;                    // Input Vertical Frequency
    BYTE IHFreqTolerance;           // Input Horizontal Frequency Tolerance
    BYTE IVFreqTolerance;           // Input Vertical Frequency Tolerance
    WORD IHTotal;                   // Input Horizontal Total Length
    WORD IVTotal;                   // Input Vertical Total Length
    WORD IHStartPos;                // Input Horizontal Start Position
    WORD IVStartPos;                // Input Vertical Start Position

} ModeTableType;

// V012 Modify 20100322 Start
// V012 Patch Note (8) : Add OOR Table to indicate in which modes the display could show OOR directly.
typedef struct
{
    WORD IHFreq;                    // Input Horizontal Frequency
    WORD IVFreq;                    // Input Vertical Frequency
    WORD IVTotal;                   // Input Vertical Total Length
    WORD IVSyncPulse;               // Input Vertical High Pulse Width
}OORModeTableType;
// V012 Modify 20100322 End

typedef struct
{
    WORD DHTotal;                   // Display Horizontal Total Length
    WORD DHWidth;                   // Display Horizontal Width
    WORD DVHeight;                  // Display Vertical Height
    WORD DVStartPos;                // Display Vertical Start Position

} DisplayTableType;

typedef struct
{
    BYTE ModeCurr;                  // Input Mode
    BYTE Polarity;                  // BIT0: H Polarity, Bit1: V Polarity
    WORD IHFreq;                    // Input Horizontal Frequency
    WORD IVFreq;                    // Input Vertical Frequency
    WORD IHTotal;                   // Input Horizontal Total Length
    WORD IVTotal;                   // Input Vertical Total Length
    WORD IHWidth;                   // Input Horizontal Width
    WORD IVHeight;                  // Input Vertical Height
    WORD IHStartPos;                // Input Horizontal Start Position
    WORD IVStartPos;                // Input Vertical Start Position
    WORD IHCount;                   // Input Horizontal Count Numbers
    WORD IHSyncPulseCount;          // Input Horizontal Sync Pulse Count Numbers
    WORD IVSyncPulseCount;          // Input Horizontal Sync Pulse Count Numbers
} ModeInformationType;

typedef struct
{
    BYTE FirstAuto;                 // First Auto
    WORD HPosition;                 // Horizontal Position
    WORD VPosition;                 // Vertical Position
    WORD Clock;                     // Clock Adjust
    BYTE Phase;                     // Phase Adjust

} StructModeUserDataType;

typedef struct
{
    BYTE ModeNum;                   // Mode Number
    WORD IHFreq;                    // Input Horizontal Frequency
    WORD IVFreq;                    // Input Vertical Frequency

} StructModeUserFIFODataType;

typedef struct
{
    WORD CenterHPos;                // Horizontal Position
    WORD CenterVPos;                // Vertical Position
    WORD CenterClock;               // Clock Adjust
    BYTE CenterPhase;               // Phase Adjust
} StructModeUserCenterDataType;

typedef struct
{
    BYTE MonitorFlag;               // Bit 7: Monitor Power Status
                                    // Bit 6: DDC/CI Status
                                    // Bit 5 ~ 4: Aspect Ratio
                                    // Bit 3: OSD Rotate Fuction
                                    // Bit 2: Non Linear Scaling
                                    // Bit 1: Reserved
                                    // Bit 0: Reserved

    BYTE SearchIndex;               // Search Index
    WORD BackLight;                 // Back Light Adjust
    BYTE UserFIFOMode;              // User FIFO Mode
    BYTE ODTable;                   // OD Table

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.

// V016 VGA Patch Note (5) 20100803 Modify Start
// Patch Reason : Modify for mistake as _COLOR_FORMAT_CONVERT == _OFF.
/*
#if(_COLOR_FORMAT_CONVERT == _ON)
*/
// V016 VGA Patch Note (5) 20100803 Modify End

    BYTE ColorSetting;              // Bit 7: Can not be used !!
                                    // Bit 6: VIDEO8 RGB/YUV Switch
                                    // Bit 5: DP RGB/YUV Switch
                                    // Bit 3: HDMI RGB/YUV Switch
                                    // Bit 2: DVI RGB/YUV Switch
                                    // Bit 1: YPBPR RGB/YUV Switch
                                    // Bit 0: VGA RGB/YUV Switch

// V016 VGA Patch Note (5) 20100803 Modify Start
// Patch Reason : Modify for mistake as _COLOR_FORMAT_CONVERT == _OFF.
/*
#endif
*/
// V016 VGA Patch Note (5) 20100803 Modify End

// V012 Modify 20100304 End

} StructSystemDataType;

typedef struct
{
    BYTE OsdSettingFlag;            // Bit 7: Reserved
                                    // Bit 6: Reserved
                                    // Bit 5: Reserved
                                    // Bit 4: Reserved
                                    // Bit 3: Reserved
                                    // Bit 2: Reserved
                                    // Bit 1: Reserved
                                    // Bit 0: Reserved

    BYTE OsdManagementFlag;         // Bit 7: Reserved
                                    // Bit 6: Reserved
                                    // Bit 5: Reserved
                                    // Bit 4: Reserved
                                    // Bit 3: Reserved
                                    // Bit 2: Reserved
                                    // Bit 1: Reserved
                                    // Bit 0: GET_SOURCE_SEARCH_AUTO

    BYTE OsdHPos;
    BYTE OsdVPos;
    BYTE Language;
    BYTE OsdTimeout;
    BYTE Volume;
    BYTE ColorTemp;
    BYTE Sharpness;

    BYTE VividFlag;
    WORD VividWinHPos;
    WORD VividWinVPos;
    WORD VividWinHWidth;
    WORD VividWinVHeight;
    BYTE VividICMRedHue;
    BYTE VividICMRedSat;
    BYTE VividICMGreenHue;
    BYTE VividICMGreenSat;
    BYTE VividICMBlueHue;
    BYTE VividICMBlueSat;
    BYTE VividBright;
    BYTE VividContrast;
    BYTE VividPeaking;
    BYTE Hue;
    BYTE Sat;

} StructOsdUserDataType;


typedef struct
{
    BYTE OsdReserveFlag;            // Bit 7: Reserved

} StructOsdReserveDataType;

typedef struct
{
    BYTE AdcGain[3];
    BYTE AdcOffset[3];
/*
    WORD AdcGain[3];
    WORD AdcOffset[3];
*/
} StructAdcDataType;

typedef struct
{
    BYTE Brightness;
    BYTE Contrast;
    BYTE Dicom;
    BYTE Gamma;	
    BYTE DicomLumi;

	
} StructColorProc0DataType;

typedef struct
{
    BYTE ColorTemp[3];

} StructColorProc1DataType;

typedef struct
{
	WORD DICOM350;
	WORD DICOM400;
	WORD DICOM450;
	WORD DICOM500;
	WORD DICOM550;
	WORD DICOM600;
	WORD DICOM650;
	WORD DICOM700;
} StructLSlumiDataType;

typedef struct
{
	WORD DICOM350;
	WORD DICOM400;
	WORD DICOM450;
	WORD DICOM500;
	WORD DICOM550;
	WORD DICOM600;
	WORD DICOM650;
	WORD DICOM700;
}StructPWMlumiDataType;

typedef struct
{
    BYTE ColorTemp9300Red;
    BYTE ColorTemp9300Green;
    BYTE ColorTemp9300Blue;
    BYTE ColorTemp6500Red;
    BYTE ColorTemp6500Green;
    BYTE ColorTemp6500Blue;
    BYTE ColorTemp5800Red;
    BYTE ColorTemp5800Green;
    BYTE ColorTemp5800Blue;
    BYTE ColorTempsRGBRed;
    BYTE ColorTempsRGBGreen;
    BYTE ColorTempsRGBBlue;
    BYTE ColorTempUserRed;
    BYTE ColorTempUserGreen;
    BYTE ColorTempUserBlue;

} StructColorTempDataType;

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
typedef struct
{
    BYTE ucModeIndex;                      // Mode Index
    WORD usIHWidthRatio;                   // Input Horizontal OverScan Ratio
    WORD usIVHeightRatio;                  // Input Vertical OverScan Ratio

} OverScanRatioType;
#endif
// V012 Modify 20100316 End

//--------------------------------------------------
// Timer Struct
//--------------------------------------------------
struct CTimerEventTable
{
    WORD Time;
    void (*Event)(void);
};

//--------------------------------------------------
// Extern Global Struct Variables
//--------------------------------------------------
extern StructModeUserDataType        xdata   stModeUserData;
extern StructModeUserCenterDataType  xdata   stModeUserCenterData;
extern StructSystemDataType          xdata   stSystemData;
extern StructOsdUserDataType         xdata   stOsdUserData;
extern StructOsdReserveDataType      xdata   stOsdReserveData;
extern StructAdcDataType             xdata   stAdcData;
extern StructLSlumiDataType          xdata   stLSlumiData;
extern StructPWMlumiDataType         xdata   stPWMlumiData;
extern StructColorProc0DataType      xdata   stConBriData;
extern StructColorProc1DataType      xdata   stColorTempData;
extern ModeInformationType           xdata   stModeInfo;
extern DisplayTableType              xdata   stDisplayInfo;
