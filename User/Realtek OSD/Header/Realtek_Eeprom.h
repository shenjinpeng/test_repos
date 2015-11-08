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
// ID Code      : Eeprom.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of EEPROM 2404/2416
//--------------------------------------------------
#define _EEPROM_ADDRESS                 0xA0

// V012 Modify 20100309 Start
// V012 Patch Note (10) : Adjust EEPROM mode data structure to save space.
//--------------------------------------------------
// Definitions of Eeprom Data Size
//--------------------------------------------------
#define _MODE_USER_DATA_SIZE            6
#define _MODE_CENTER_DATA_SIZE          6
// V012 Modify 20100309 End

//--------------------------------------------------
// Definitions of Eeprom Data Address
//--------------------------------------------------
#define _EEPROM_PAGE0_BANK0             0
#define _EEPROM_PAGE0_BANK1             128
#define _EEPROM_PAGE1_BANK0             256
#define _EEPROM_PAGE1_BANK1             384
#define _EEPROM_PAGE2_BANK0             512
#define _EEPROM_PAGE2_BANK1             640
#define _EEPROM_PAGE3_BANK0             768
#define _EEPROM_PAGE3_BANK1             896
#define _EEPROM_PAGE4_BANK0             1024
#define _EEPROM_PAGE4_BANK1             1152
#define _EEPROM_PAGE5_BANK0             1280
#define _EEPROM_PAGE5_BANK1             1408
#define _EEPROM_PAGE6_BANK0             1536
#define _EEPROM_PAGE6_BANK1             1664
#define _EEPROM_PAGE7_BANK0             1792
#define _EEPROM_PAGE7_BANK1             1920

#define _VERSION_CODE_ADDRESS           (_EEPROM_PAGE0_BANK0)
#define _MODE_DATA_0_ADDRESS            (_EEPROM_PAGE0_BANK0 + 1)                                // 0

// V013 VGA Patch Note (11) Modify 20100416 Start
// Patch Reason : Add FIFO Mode Only to save EEPROM space.
// Activate FIFO Mode Only to save EEPROM space with 63 FIFO modes only.
/*

// V012 Modify 20100309 Start
// V012 Patch Note (10) : Adjust EEPROM mode data structure to save space.
/*
#define _USER_FIFO_MODE_DATA_0_ADDRESS  (_MODE_DATA_0_ADDRESS + (_MAX_PRESET_MODE * 8))             // 600 =   0 + (75 * 8)
* /
#define _USER_FIFO_MODE_DATA_0_ADDRESS  (_MODE_DATA_0_ADDRESS + (_MAX_PRESET_MODE * _MODE_USER_DATA_SIZE)) // 600 =   0 + (75 * 8)
// V012 Modify 20100309 End


#define _USER_FIFO_MODE_DATA_1_ADDRESS  (_USER_FIFO_MODE_DATA_0_ADDRESS + (16 * 4))              // 664 = 600 + (16 * 4)

// V012 Modify 20100309 Start
// V012 Patch Note (10) : Adjust EEPROM mode data structure to save space.
/*
#define _MODE_CENTER_DATA_ADDRESS       (_USER_FIFO_MODE_DATA_1_ADDRESS + (16 * 8))              // 792 = 664 + (16 * 8)
* /
#define _MODE_CENTER_DATA_ADDRESS       (_USER_FIFO_MODE_DATA_1_ADDRESS + (16 * _MODE_USER_DATA_SIZE))     // 792 = 664 + (16 * 8)
// V012 Modify 20100309 End

// V012 Modify 20100309 Start
// V012 Patch Note (10) : Adjust EEPROM mode data structure to save space.
/*
#define _USER_DATA_ADDRESS              (_MODE_CENTER_DATA_ADDRESS + ((_MAX_PRESET_MODE + 16) * 8)) //1392 = 664 + (91 * 8)
* /
#define _USER_DATA_ADDRESS              (_MODE_CENTER_DATA_ADDRESS + ((_MAX_PRESET_MODE + 16) * _MODE_CENTER_DATA_SIZE)) // 1392 = 664 + (91 * 8)
*/
#if(_FIFO_MODE_ONLY == _ON)
#define _USER_FIFO_MODE_DATA_0_ADDRESS  (_MODE_DATA_0_ADDRESS + (_MAX_FIFO_MODE_INDEX + 1) * sizeof(StructModeUserDataType))
#define _MODE_CENTER_DATA_ADDRESS       (_USER_FIFO_MODE_DATA_0_ADDRESS + (_MAX_FIFO_MODE_INDEX + 1) * 4)

// V013 VGA Patch Note (10) 20100416 Modify Start
// Patch Reason : Support Auto Config For Yuv Color.
/*
#define _USER_DATA_ADDRESS              (_MODE_CENTER_DATA_ADDRESS + (_MAX_FIFO_MODE_INDEX + 1) * sizeof(StructModeUserCenterDataType))
*/
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
#define _MODE_DATA_YPBPR_ADDRESS        (_MODE_CENTER_DATA_ADDRESS + (_MAX_FIFO_MODE_INDEX + 1) * sizeof(StructModeUserCenterDataType))//0xC2
#define _MODE_CENTER_DATA_YPBPR_ADDRESS (_MODE_DATA_YPBPR_ADDRESS + _MAX_YPBPR_MODE * sizeof(StructModeUserDataType))//0X22
#define _USER_DATA_ADDRESS              (_MODE_CENTER_DATA_YPBPR_ADDRESS + _MAX_YPBPR_MODE * sizeof(StructModeUserCenterDataType))//0X75
#else
#define _USER_DATA_ADDRESS              (_MODE_CENTER_DATA_ADDRESS + (_MAX_FIFO_MODE_INDEX + 1) * sizeof(StructModeUserCenterDataType))
#endif
// V013 VGA Patch Note (10) 20100416 Modify End

#else
#define _USER_FIFO_MODE_DATA_0_ADDRESS  (_MODE_DATA_0_ADDRESS + (_MAX_PRESET_MODE * _MODE_USER_DATA_SIZE))
#define _USER_FIFO_MODE_DATA_1_ADDRESS  (_USER_FIFO_MODE_DATA_0_ADDRESS + (16 * 4))
#define _MODE_CENTER_DATA_ADDRESS       (_USER_FIFO_MODE_DATA_1_ADDRESS + (16 * _MODE_USER_DATA_SIZE))

#define _USER_DATA_ADDRESS              (_MODE_CENTER_DATA_ADDRESS + ((_MAX_PRESET_MODE + 16) * _MODE_CENTER_DATA_SIZE))
#endif
// V013 VGA Patch Note (11) Modify 20100416 End

#define _SYSTEM_DATA_ADDRESS            (_USER_DATA_ADDRESS + 0)//0X69
#define _OSDUSER_DATA_ADDRESS           (_SYSTEM_DATA_ADDRESS + sizeof(StructSystemDataType))
#define _OSDRESERVE_DATA_ADDRESS        (_OSDUSER_DATA_ADDRESS + sizeof(StructOsdUserDataType))
#define _ADC_DATA_ADDRESS               (_OSDRESERVE_DATA_ADDRESS + sizeof(StructOsdReserveDataType))
#define _COLOR_PROC0_ADDRESS            (_ADC_DATA_ADDRESS + (sizeof(StructAdcDataType)) * 2 + 2)
#define _COLORTEMP_DATA_ADDRESS         (_COLOR_PROC0_ADDRESS + (sizeof(StructColorProc0DataType)) * _SOURCE_AMOUNT)
#define _FACTORY_DATA_ADDRESS           (_COLORTEMP_DATA_ADDRESS + (sizeof(StructColorTempDataType)) * _SOURCE_AMOUNT)
#define _LSLUMI_DATA_ADDRESS              (_ADC_DATA_ADDRESS +(_MAX_FIFO_MODE_INDEX + 1) *9)//adam20110620
#define _PWMLUMI_DATA_ADDRESS          ( _LSLUMI_DATA_ADDRESS+32)//SJP20110721

#ifdef __REALTEK_EEPROM__


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CEepromStartupCheck(void);
void CEepromLoadDefault(void);

bit CEepromWrite(WORD usAddr, WORD usLength, BYTE *pWriteArray);
bit CEepromRead(WORD usAddr, WORD usLength, BYTE *pReadArray);

void CEepromSaveModeData(BYTE ucMode);
void CEepromLoadModeData(BYTE ucMode);
void CEepromInitialModeData(void);

void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode);
void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray);
void CEepromInitialUserFIFOModeData(void);

void CEepromSaveCenterModeData(BYTE ucMode);
void CEepromLoadCenterModeData(BYTE ucMode);
void CEepromInitialCenterModeData(void);

void CEepromSaveSystemData(void);
void CEepromLoadSystemData(void);
void CEepromLoadSystemDataDefault(void);

void CEepromSaveOsdUserData(void);
void CEepromLoadOsdUserData(void);
void CEepromLoadOsdUserDataDefault(void);

void CEepromSaveOsdReserveData(void);
void CEepromLoadOsdReserveData(void);
void CEepromLoadOsdReserveDataDefault(void);

void CEepromSaveAdcData(void);
void CEepromLoadAdcData(void);
void CEepromLoadAdcDataDefault(void);

extern void CEepromSaveLSlumiData(void);//sjp20110625
extern void CEepromLoadLSlumiData(void);//sjp20110625
extern void CEepromLoadLSlumiDataDefault(void);//sjp20110625

extern void CEepromSavePWMlumiData(void);//SJP20110715
extern void CEepromLoadPWMlumiData(void);//SJP20110715
extern void CEepromLoadPWMlumiDataDefault(void);//SJP20110715

void CEepromSaveBriConData(void);
void CEepromLoadBriConData(void);
void CEepromLoadBriConDataDefault(void);

void CEepromSaveColorTempData(void);
void CEepromLoadColorTempData(void);
void CEepromLoadColorTempDataDefault(void);
//void CEepromLoadLSlumiDataDefault(void);//sjp20110625
void CEepromLoadDDCData(void);

#if(_DDCCI_SUPPORT == _ON)
void CEepromLoadBackLightDefault(void);
#endif

#else


//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CEepromStartupCheck(void);
extern void CEepromLoadDefault(void);

extern bit CEepromWrite(WORD usAddr, WORD usLength, BYTE *pWriteArray);
extern bit CEepromRead(WORD usAddr, WORD usLength, BYTE *pReadArray);

extern void CEepromSaveModeData(BYTE ucMode);
extern void CEepromLoadModeData(BYTE ucMode);
extern void CEepromInitialModeData(void);

extern void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode);
extern void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray);
extern void CEepromInitialUserFIFOModeData(void);

extern void CEepromSaveCenterModeData(BYTE ucMode);
extern void CEepromLoadCenterModeData(BYTE ucMode);
extern void CEepromInitialCenterModeData(void);

extern void CEepromSaveSystemData(void);
extern void CEepromLoadSystemData(void);
extern void CEepromLoadSystemDataDefault(void);

extern void CEepromSaveOsdUserData(void);
extern void CEepromLoadOsdUserData(void);
extern void CEepromLoadOsdUserDataDefault(void);

extern void CEepromSaveOsdReserveData(void);
extern void CEepromLoadOsdReserveData(void);
extern void CEepromLoadOsdReserveDataDefault(void);

extern void CEepromSaveAdcData(void);
extern void CEepromLoadAdcData(void);
extern void CEepromLoadAdcDataDefault(void);

extern void CEepromSaveLSlumiData(void);//sjp20110625
extern void CEepromLoadLSlumiData(void);//sjp20110625
extern void CEepromLoadLSlumiDataDefault(void);//sjp20110625

extern void CEepromSavePWMlumiData(void);//SJP20110715
extern void CEepromLoadPWMlumiData(void);//SJP20110715
extern void CEepromLoadPWMlumiDataDefault(void);//SJP20110715

extern void CEepromSaveBriConData(void);
extern void CEepromLoadBriConData(void);
extern void CEepromLoadBriConDataDefault(void);

extern void CEepromSaveColorTempData(void);
extern void CEepromLoadColorTempData(void);
extern void CEepromLoadColorTempDataDefault(void);

extern void CEepromLoadDDCData(void);

#if(_DDCCI_SUPPORT == _ON)
extern void CEepromLoadBackLightDefault(void);
#endif

#endif


//----------------------------------------------------------------------------------------------------

