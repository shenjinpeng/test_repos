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
// ID Code      : Flash.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------


// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.


//--------------------------------------------------
// Definitions of whether emulation flash space will be in code space
//--------------------------------------------------
#define _MERGE_EMULATION_TO_CODE                _OFF


//--------------------------------------------------
// Definitions of Flash Bank Location
//--------------------------------------------------
#if(_MERGE_EMULATION_TO_CODE == _ON)
#define _FLASH_BANK                             2
#else
#define _FLASH_BANK                             3
#endif


//--------------------------------------------------
// Definitions of Flash Type which requires WREN for every single BYTE writing
//--------------------------------------------------
#define _WREN_FOR_SINGLE_BYTE                   (_FLASH_TYPE == _FLASH_MX25L2026)


//--------------------------------------------------
// Definitions of Flash Page Configuration
//--------------------------------------------------
#define _START_PAGE                             12
#define _END_PAGE                               14 // Last page 15 can not be defined
#define _MISC_PAGE                              (_END_PAGE + 1)


//--------------------------------------------------
// Definitions of Flash Space
//--------------------------------------------------
#define _FLASH_DATA_SPACE                       ((_END_PAGE - _START_PAGE + 1) * _PAGE_SIZE)
#define _MISC_SPACE                             0x0900
#define _FLASH_SPACE                            (_FLASH_DATA_SPACE + _MISC_SPACE)
#define _FLASH_VERSION_CODE_PAGE_ADDR           (_MISC_SPACE - 1)


//--------------------------------------------------
// Definitions of EDID and EDID PRO
//--------------------------------------------------
#define _ADC_EDID_SIZE                          128
#define _DDC2_EDID_SIZE                         256
#define _DDC3_EDID_SIZE                         256

#define _EDID_TOTAL_SIZE                        (_ADC_EDID_SIZE + _DDC2_EDID_SIZE + _DDC3_EDID_SIZE)
//#define _EDID_ITEM_TOTAL_COUNT                  (_EDID_TOTAL_SIZE / _EDID_ITEM_LENGTH)
//#define _EDID_ADDR_LIMIT                        ((_MISC_SPACE - 256) / _EDID_TOTAL_SIZE * _EDID_ITEM_TOTAL_COUNT)


//--------------------------------------------------
// Definitions of HDCP KEY in Misc Page
//--------------------------------------------------
// V016 System Patch Note (26) Modify 20100831 Start
// Patch Reason : Extend HDCP KEY Length to 325Byte including CTRL Key
/*
#define _HDCP_KEY_SIZE                          (320)
#define _MCU_FLASH_HDCP_KEY                     (&MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE])
*/

#define _HDCP_CTRL_SIZE                         (5)
#define _HDCP_KEY_SIZE                          (320 + _HDCP_CTRL_SIZE)

#define _MCU_FLASH_HDCP_CTRL                    (&MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE])
#define _MCU_FLASH_HDCP_KEY                     (&MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE + _HDCP_CTRL_SIZE])
// V016 System Patch Note (26) Modify 20100831 End


//--------------------------------------------------
// Definitions of LUT in Misc Page
//--------------------------------------------------
#define _GAMMA_LUT_FLASH_START_PAGE             (_MISC_PAGE)
#define _GAMMA_LUT_FLASH_START_ADDR             (_PAGE_SIZE * _GAMMA_LUT_FLASH_START_PAGE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE)
#define _GAMMA_LUT_FLASH_CHANNEL_SIZE           (387)

#define _MCU_FLASH_GAMMA_LUT_R                  (&MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE])
#define _MCU_FLASH_GAMMA_LUT_G                  (&MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE + 1 * _GAMMA_LUT_FLASH_CHANNEL_SIZE])
#define _MCU_FLASH_GAMMA_LUT_B                  (&MCU_FLASH[_FLASH_DATA_SPACE + _EDID_TOTAL_SIZE + _HDCP_KEY_SIZE + 2 * _GAMMA_LUT_FLASH_CHANNEL_SIZE])

#define _FLASH_LUT_SIZE                         (_GAMMA_LUT_FLASH_CHANNEL_SIZE * 3)


//--------------------------------------------------
// Macro of Get Flash Type Index
//--------------------------------------------------
#define GET_FLASH_TYPE_INDEX()                  (g_ucFlashType + 1)


//--------------------------------------------------
// Definitions of Default Supported Flash TYPE
//--------------------------------------------------
#define _FLASH_TYPE_NO_SUPPORT                  0xFF
#define _FLASH_TYPE_DEFAULT_SUPPORT             _FLASH_TYPE


//--------------------------------------------------
// Definitions of Flash INFO such as supported flash count
//--------------------------------------------------
enum FlashSupportInfoContentIndex
{
    _FLASH_SUPPORT_INFO_SUPPORT_COUNT,
    _FLASH_SUPPORT_INFO_GROUP_SIZE,
};


//--------------------------------------------------
// Definitions of Detailed Flash INFO Content
//--------------------------------------------------
enum FlashInfoContentIndex
{
    _FLASH_INFO_JEDEC_ID_CODE_0,
    _FLASH_INFO_JEDEC_ID_CODE_1,
    _FLASH_INFO_JEDEC_ID_CODE_2,
    _FLASH_INFO_0x90_ID_CODE_0,
    _FLASH_INFO_0x90_ID_CODE_1,
    _FLASH_INFO_0x90_ID_CODE_2,
    _FLASH_INFO_0xAB_ID_CODE_0,
    _FLASH_INFO_0xAB_ID_CODE_1,
    _FLASH_INFO_0xAB_ID_CODE_2,
    _FLASH_INFO_WREN_OPCODE,
    _FLASH_INFO_WRDIS_OPCODE,
    _FLASH_INFO_SECTOR_ERASE_OPCODE,
    _FLASH_INFO_WRSR_UNPROTECT,
    _FLASH_INFO_WRSR_PROTECT,

    _FLASH_INFO_GROUP_SIZE,
};


//--------------------------------------------------
// Definitions of Flash Page Index
//--------------------------------------------------
enum FlashPageDef
{
    _MODE = 0,
    _GLOBAL,
    _NUMBER_OF_PAGES,
    _MISC = _NUMBER_OF_PAGES,
};


//--------------------------------------------------
// Definitions of Flash Item Length For Each Page
//--------------------------------------------------
#define _MODE_ITEM_LENGTH                       16 // This size can never be modified.
#define _GLOBAL_ITEM_LENGTH                     16

//#define _EDID_ITEM_LENGTH                       8  // This size can never be modified.


//--------------------------------------------------
// Definitions of Version Code related Infor.
//--------------------------------------------------
#define _RTK_HIGH_BYTE                          0x4A
#define _RTK_LOW_BYTE                           0x8B
#define _RSL_HIGH_BYTE                          0x4A
#define _RSL_LOW_BYTE                           0x6C


//--------------------------------------------------
// Definitions of Length of Parts in Item
//--------------------------------------------------
#define _ITEM_CHECKSUM_LENGTH                   1
#define _ITEM_ID_CODE_LENGTH                    1


//--------------------------------------------------
// Definitions of Length of Information Item in Each Page
//--------------------------------------------------
#define _PAGE_INFO_LENGTH                       8


//--------------------------------------------------
// Definitions of MISC page content type
//--------------------------------------------------
#define _DEFAULT_MISC                           0
#define _FLASH_MISC                             1


//--------------------------------------------------
// Definitions of DDCRAM Type Index
//--------------------------------------------------
#define _VGA_EDID                               0
#define _DDC2_EDID                              1
#define _DDC3_EDID                              2


//--------------------------------------------------
// Definitions of Flash Page Size
//--------------------------------------------------
#define _SECTOR_SIZE                            4  // (K Byte)
#define _1K_SIZE                                1024
#define _PAGE_SIZE                              (_SECTOR_SIZE * _1K_SIZE)


//--------------------------------------------------
// Definitions of Misc Page Space Limitation
//--------------------------------------------------
#define _FLASH_MISC_CONTENT_SPACE               (_EDID_TOTAL_SIZE + _HDCP_KEY_SIZE + _FLASH_LUT_SIZE)

#if((_FLASH_MISC_CONTENT_SPACE + _PAGE_INFO_LENGTH) > _MISC_SPACE)
#error !Misc Page Over Sized!!!
#endif


//----------------------------------------------------------------------------------------------------

#ifdef __REALTEK_FLASH__


//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE xdata g_ucFlashType = 0xFF; // Variable of current Flash type


//----------------------------------------------------------------
// Flash INFO Supported by FW such as supported flash type count
//----------------------------------------------------------------
BYTE code tFLASH_SUPPORT_INFO[] =
{
    _FLASH_SUPPORTED_COUNT,
    _FLASH_INFO_GROUP_SIZE,
};


//--------------------------------------------------
// Detailed Flash INFO Supported by FW
//--------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////
//  Please do not change the order of below Flash detailed INFO tables arbitrarily //
/////////////////////////////////////////////////////////////////////////////////////
BYTE code tFLASH_DETAILED_INFO[_FLASH_SUPPORTED_COUNT][_FLASH_INFO_GROUP_SIZE] =
{
    // Flash Type   : PMC _FLASH_Pm25LV020
    {
        0x7F, 0x9D, 0x7D,   // Flash JEDEC (0x9F) ID Code
        0x00, 0x00, 0x00,   // Flash (0x90) ID Code
        0x9D, 0x7D, 0x7F,   // Flash (0xAB) ID Code
        0x26,               // Flash WREN OP Code
        0x24,               // Flash WRDis OP Code
        0xD7,               // Flash Sector Erase OP Code
        0x00,               // Flash Unprotect WRSR status
        0x9C                // Flash Protect WRSR status
    },

    // Flash Type   : Winbond _FLASH_W25X20A
    {
        0xEF, 0x30, 0x12,   // Flash JEDEC (0x9F) ID Code
        0xEF, 0x11, 0x00,   // Flash (0x90) ID Code
        0x11, 0x00, 0x00,   // Flash (0xAB) ID Code
        0x06,               // Flash WREN OP Code
        0x04,               // Flash WRDis OP Code
        0x20,               // Flash Sector Erase OP Code
        0x28,               // Flash Unprotect WRSR status
        0xBC                // Flash Protect WRSR status
    },

    // Flash Type   : MXIC _FLASH_MX25L2026
    {
        0xC2, 0x20, 0x12,   // Flash JEDEC (0x9F) ID Code
        0xC2, 0x03, 0x00,   // Flash (0x90) ID Code
        0x03, 0x00, 0x00,   // Flash (0xAB) ID Code
        0x06,               // Flash WREN OP Code
        0x04,               // Flash WRDis OP Code
        0x20,               // Flash Sector Erase OP Code
        0x02,               // Flash Unprotect WRSR status
        0xFC                // Flash Protect WRSR status
    },

    // Flash Type   : EON _FLASH_EN25F20
    {
        0x1C, 0x31, 0x12,   // Flash JEDEC (0x9F) ID Code
        0x1C, 0x11, 0x00,   // Flash (0x90) ID Code
        0x11, 0x00, 0x00,   // Flash (0xAB) ID Code
        0x06,               // Flash WREN OP Code
        0x04,               // Flash WRDis OP Code
        0x20,               // Flash Sector Erase OP Code
        0x02,               // Flash Unprotect WRSR status
        0x9C                // Flash Protect WRSR status
    },

    // Flash Type   : PMC _FLASH_Pm25LD020
    {
        0x7F, 0x9D, 0x22,   // Flash JEDEC (0x9F) ID Code
        0x9D, 0x11, 0x7F,   // Flash (0x90) ID Code
        0x11, 0x11, 0x11,   // Flash (0xAB) ID Code
        0x26,               // Flash WREN OP Code
        0x24,               // Flash WRDis OP Code
        0xD7,               // Flash Sector Erase OP Code
        0x00,               // Flash Unprotect WRSR status
        0x9C                // Flash Protect WRSR status
    },

    // Flash Type   : MXIC _FLASH_MX25L2025
    {
        0xC2, 0x20, 0x12,   // Flash JEDEC (0x9F) ID Code
        0xC2, 0x11, 0x00,   // Flash (0x90) ID Code
        0x11, 0x00, 0x00,   // Flash (0xAB) ID Code
        0x06,               // Flash WREN OP Code
        0x04,               // Flash WRDis OP Code
        0x20,               // Flash Sector Erase OP Code
        0x02,               // Flash Unprotect WRSR status
        0x8C                // Flash Protect WRSR status
    },

    // Flash Type   : SST _FLASH_SST25LF020A
    {
        0x00, 0x00, 0x00,   // Flash JEDEC (0x9F) ID Code
        0xBF, 0x43, 0x00,   // Flash (0x90) ID Code
        0xBF, 0x43, 0x00,   // Flash (0xAB) ID Code
        0x06,               // Flash WREN OP Code
        0x04,               // Flash WRDis OP Code
        0x20,               // Flash Sector Erase OP Code
        0x02,               // Flash Unprotect WRSR status
        0x9C                // Flash Protect WRSR status
    },
};


#if(_MEMORY_LOCATION == _FLASH)

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE xdata MCU_FLASH[_FLASH_SPACE] _at_ (_START_PAGE * _PAGE_SIZE);

BYTE xdata g_ucFlashFreePage = 0;
BYTE xdata g_ucFlashPage[_NUMBER_OF_PAGES] = {0};
BYTE idata g_ucFlashTemp[16] = {0};
WORD xdata g_usFlashAddr[_NUMBER_OF_PAGES] = {0};
DWORD xdata g_ulFlashMovePage = 0;

BYTE code tFLASHCODE[_NUMBER_OF_PAGES] = {_MODE, _GLOBAL};
BYTE code tFLASHSIZE[_NUMBER_OF_PAGES] = {_MODE_ITEM_LENGTH, _GLOBAL_ITEM_LENGTH};


//-------------------------------------------------------------------
// Definitions of Flash Data ID Code for saving data in _GLOGAL page
//-------------------------------------------------------------------
enum GlobalIDCode
{
    _FLASH_SYSTEM_DATA,                         // 0
    _FLASH_ADC_DATA_VGA,                        // 1
    _FLASH_ADC_DATA_YPBPR,                      // 2
    _FLASH_BRI_CON_DATA_VGA,                    // 3
    _FLASH_BRI_CON_DATA_DVI,                    // 4
    _FLASH_BRI_CON_DATA_VIDEO8,                 // 5
    _FLASH_BRI_CON_DATA_YPBPR,                  // 6
    _FLASH_BRI_CON_DATA_DP,                     // 7
    _FLASH_BRI_CON_DATA_VIN,                    // 8
    _FLASH_BRI_CON_DATA_HDMI,                   // 9
    _FLASH_BRI_CON_DATA_NONE,                   // 10
    _FLASH_COLOR_TEMP_DATA_VGA_9300,            // 11
    _FLASH_COLOR_TEMP_DATA_VGA_6500,            // 12
    _FLASH_COLOR_TEMP_DATA_VGA_5800,            // 13
    _FLASH_COLOR_TEMP_DATA_VGA_SRGB,            // 14
    _FLASH_COLOR_TEMP_DATA_VGA_USER,            // 15
    _FLASH_COLOR_TEMP_DATA_DVI_9300,            // 16
    _FLASH_COLOR_TEMP_DATA_DVI_6500,            // 17
    _FLASH_COLOR_TEMP_DATA_DVI_5800,            // 18
    _FLASH_COLOR_TEMP_DATA_DVI_SRGB,            // 19
    _FLASH_COLOR_TEMP_DATA_DVI_USER,            // 20
    _FLASH_COLOR_TEMP_DATA_VIDEO8_9300,         // 21
    _FLASH_COLOR_TEMP_DATA_VIDEO8_6500,         // 22
    _FLASH_COLOR_TEMP_DATA_VIDEO8_5800,         // 23
    _FLASH_COLOR_TEMP_DATA_VIDEO8_SRGB,         // 24
    _FLASH_COLOR_TEMP_DATA_VIDEO8_USER,         // 25
    _FLASH_COLOR_TEMP_DATA_YPBPR_9300,          // 26
    _FLASH_COLOR_TEMP_DATA_YPBPR_6500,          // 27
    _FLASH_COLOR_TEMP_DATA_YPBPR_5800,          // 28
    _FLASH_COLOR_TEMP_DATA_YPBPR_SRGB,          // 29
    _FLASH_COLOR_TEMP_DATA_YPBPR_USER,          // 30
    _FLASH_COLOR_TEMP_DATA_NONE_9300,           // 31
    _FLASH_COLOR_TEMP_DATA_NONE_6500,           // 32
    _FLASH_COLOR_TEMP_DATA_NONE_5800,           // 33
    _FLASH_COLOR_TEMP_DATA_NONE_SRGB,           // 34
    _FLASH_COLOR_TEMP_DATA_NONE_USER,           // 35
    _FLASH_OSD_USER_DATA_1,                     // 36
    _FLASH_OSD_USER_DATA_2,                     // 37
    _FLASH_OSD_USER_DATA_3,                     // 38
    _FLASH_OSD_USER_DATA_4,                     // 39
    _FLASH_OSD_USER_DATA_5,                     // 40
    _FLASH_OSD_USER_DATA_END,                   // 41
    _FLASH_ITEM_NUMBER,                         // 42
};

#define _FLASH_INITIAL                          0xFE


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CFlashStartupCheck(void);
bit CFlashInitial(void);
void CFlashInitialAddr(void);
BYTE CFlashSearchPage();
WORD CFlashSearchPageAddr(BYTE ucPageID);
BYTE CFlashSearchFreePage(BYTE FreePage);
void CFlashLoadPageModeDefault(void);
void CFlashLoadPageDefault(BYTE ucPageID);
void CEepromLoadDefault(void);
void CFlashStartLoadDefault(BYTE ucPageID);
void CFlashFinishLoadDefault(BYTE ucPageID);
void CFlashCheckLoadDefault(BYTE ucPageID);
BYTE CFlashFreePageLocateAtStartup(void);
void CFlashInitialPage(BYTE ucPageID, BYTE ucFreePage);

void CEepromSaveModeData(BYTE ucMode);
void CEepromLoadModeData(BYTE ucMode);
void CEepromInitialModeData(void);
void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode);
void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray);
void CEepromInitialUserFIFOModeData(void);
void CEepromSaveCenterModeData(BYTE ucMode);
void CEepromLoadCenterModeData(BYTE ucMode);

void CEepromSaveSystemData(void);
void CEepromLoadSystemData(void);
void CEepromLoadSystemDataDefault(void);
void CEepromSaveOsdUserData(void);
void CEepromLoadOsdUserData(void);
void CEepromLoadOsdUserDataDefault(void);
void CEepromSaveAdcData(void);
void CEepromLoadAdcData(void);
void CEepromLoadAdcDataDefault(void);
void CEepromSaveBriConData(void);
void CEepromLoadBriConData(void);
void CEepromLoadBriConDataDefault(void);
void CEepromSaveColorTempData(void);
void CEepromLoadColorTempData(void);
void CEepromLoadColorTempDataDefault(void);

#if(_DDCCI_SUPPORT == _ON)
void CEepromLoadBackLightDefault(void);
#endif

void CFlashWrite(BYTE ucPage, BYTE ucIndex, BYTE ucLength, BYTE *pWriteArray);
bit CFlashRead(BYTE ucPage, BYTE ucIndex, BYTE ucLength, BYTE *pWriteArray);
void CFlashSaveData(BYTE ucPageID, BYTE *pArray);
bit CFlashLoadData(BYTE ucPageID, BYTE ucIndex, BYTE *pArray);
bit CFlashMoveData(BYTE ucPageID);
bit CFlashSearchItem(BYTE ucPageID, WORD usStartAddr, BYTE ucItemCode);
BYTE CFlashBufferChecksum(BYTE ucLength);
BYTE CFlashCalculateItemChecksum(BYTE ucPageID, WORD usItemAddr);

#endif // End of #if(_MEMORY_LOCATION == _FLASH)

BYTE CFlashGetFlashDetailedInfo(BYTE ucFlashType, BYTE ucIndex);

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
BYTE CFlashGetFlashSupportInfo(BYTE ucIndex);
bit  CFlashCheckFlashType();
BYTE CFlashCheckFWSupportFlashType();
bit  CFlashReadFlashIDCode(BYTE RDIDOPCode, BYTE *pReadID0Array, BYTE *pReadID1Array, BYTE *pReadID2Array);
bit  CFlashMatchFlashIDCode(BYTE RDIDOPCode, BYTE *pReadID0Array, BYTE *pReadID1Array, BYTE *pReadID2Array);
#endif

#if(_MEMORY_LOCATION == _FLASH)
bit CFlashErase(BYTE ucPage);
bit CFlashWREN(BYTE ucPage);
bit CFlashWRDis(void);

#if((_AUTO_DETECT_FLASH_TYPE == _ON) || (_FLASH_TYPE == _FLASH_W25X20A) \
    || (_FLASH_TYPE == _FLASH_MX25L2026) || (_FLASH_TYPE == _FLASH_EN25F20) \
    || (_FLASH_TYPE == _FLASH_MX25L2025) || (_FLASH_TYPE == _FLASH_SST25LF020A))
bit CFlashSetWREN(BYTE ucOpCode, WORD usTimeOut);
bit CFlashSetWRSR(BYTE ucWRSR, WORD usTimeOut, BYTE ucIsSST);
#endif

#if((_EDID_PRO == _ON) || (_FLASH_XDATA_ACCESS == _ON))
void CFlashInitialMISCPageStart();
void CFlashInitialMISCPageEnd();
bit  CFlashCheckIsAllFF(BYTE *pArray, WORD usSize);
void CFlashBackupMISCPage(void);
#endif // End of #if(_FLASH_XDATA_ACCESS == _ON)

void CFlashRecoverMISCPage(BYTE ucFreePage);
void CFlashLoadMISCPageDefault(void);
#endif // End of #if(_MEMORY_LOCATION == _FLASH)

#if((_MEMORY_LOCATION == _FLASH) && (_EDID_PRO == _ON))
void CFlashSaveDDCData(void);
bit  CFlashVerifyDDCRAMEDID(BYTE * pDDCRAM, WORD usSize);
void CFlashLoadEDIDData(BYTE ucTable, BYTE ucFreePage);
void CFlashSaveDDCRAM2MISCPage(void);
void CFlashSaveEDIDDDCRAM2MISCPage(BYTE ucDDCRAMType);
void CFlashLoadMISCPage2DDCRAM(void);
void CFlashLoadMISCPage2EDIDDDCRAM(BYTE ucDDCRAMType);
#endif // End of #if(_EDID_PRO == _ON)

// V016 System Patch Note (3) Modify 20100803 Start
// Patch Reason : Modify CFlashLoadDDCData to avoid complie warning.
/*
#if(_EMBEDDED_EDID == _OFF)
*/
#if((_MEMORY_LOCATION == _FLASH) && (_EMBEDDED_EDID == _OFF))
// V016 System Patch Note (3) Modify 20100803 End

void CFlashLoadDDCData(void);
#endif

#if((_MEMORY_LOCATION == _FLASH) && (_EMBEDDED_HDCP_KEY == _ON) && (_HDCP_KEY_LOCATION == _HDCP_LOCATION_FLASH))
void CFlashLoadHDCPKeyData(BYTE ucTable, BYTE ucFreePage);
#endif

#if((_MEMORY_LOCATION == _FLASH) && (_GAMMA_FUNCTION == _ON) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH))
void CFlashLoadLUTTableData(BYTE ucTable, BYTE ucFreePage);
#endif


//--------------------------------------------------
// Macro of Mode Number for Preset and User Mode
//--------------------------------------------------
#if(_FIFO_MODE_ONLY == _ON)

#define GET_FIFO_MODE_ITEM_CODE(ucModeNum)      (ucModeNum) // ucModeNum is FIFO index
#define GET_FIFO_MODE_FIFO_ITEM_CODE(ucModeNum) ((_MAX_FIFO_MODE_INDEX + 1) + ucModeNum) // ucModeNum is FIFO index

#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
#define GET_YPBPR_MODE_ITEM_CODE(ucModeNum)     ((_MAX_FIFO_MODE_INDEX + 1) * 2 + ucModeNum) // ucModeNum is YPbPr Mode Table Index
#endif

#else

#define GET_PRESET_MODE_ITEM_CODE(ucModeNum)    (16 * 2 + ucModeNum) // ucModeNum is preset mode index
#define GET_FIFO_MODE_ITEM_CODE(ucModeNum)      (ucModeNum) // ucModeNum is user mode index
#define GET_FIFO_MODE_FIFO_ITEM_CODE(ucModeNum) (16 + ucModeNum) // ucModeNum is user mode index

#if(_YUV_AUTO_CONFIG_SUPPORT == _ON)
#define GET_YPBPR_MODE_ITEM_CODE(ucModeNum)     (16 * 2 + _MAX_PRESET_MODE + ucModeNum) // ucModeNum is YPbPr Mode Table Index
#endif

#endif


//--------------------------------------------------
// Macro of Absolute Page ID and Relative Page ID
//--------------------------------------------------
#define GET_ABSOLUTE_PAGE_NUM(ucPageID)         (ucPageID + _START_PAGE)
#define GET_RELATIVE_PAGE_NUM(ucPageID)         (ucPageID - _START_PAGE)


#else // Else of #ifdef __REALTEK_FLASH__

extern BYTE xdata g_ucFlashType;

#if(_MEMORY_LOCATION == _FLASH)
//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE xdata MCU_FLASH[_FLASH_SPACE];


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CFlashStartupCheck(void);
extern bit CFlashInitial(void);
extern bit CFlashErase(BYTE ucPage);
extern void CFlashInitialAddr(void);
extern WORD CFlashSearchPageAddr(BYTE ucPageID);
extern BYTE CFlashSearchFreePage(BYTE FreePage);
extern void CEepromLoadDefault(void);
extern void CFlashStartLoadDefault(BYTE ucPageID);
extern void CFlashFinishLoadDefault(BYTE ucPageID);
extern void CFlashCheckLoadDefault(BYTE ucPageID);

extern void CEepromSaveModeData(BYTE ucMode);
extern void CEepromLoadModeData(BYTE ucMode);
extern void CEepromInitialModeData(void);
extern void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode);
extern void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray);
extern void CEepromInitialUserFIFOModeData(void);
extern void CEepromSaveCenterModeData(BYTE ucMode);
extern void CEepromLoadCenterModeData(BYTE ucMode);

extern void CEepromSaveSystemData(void);
extern void CEepromLoadSystemData(void);
extern void CEepromLoadSystemDataDefault(void);
extern void CEepromSaveOsdUserData(void);
extern void CEepromLoadOsdUserData(void);
extern void CEepromLoadOsdUserDataDefault(void);
extern void CEepromSaveAdcData(void);
extern void CEepromLoadAdcData(void);
extern void CEepromLoadAdcDataDefault(void);
extern void CEepromSaveBriConData(void);
extern void CEepromLoadBriConData(void);
extern void CEepromLoadBriConDataDefault(void);
extern void CEepromSaveColorTempData(void);
extern void CEepromLoadColorTempData(void);
extern void CEepromLoadColorTempDataDefault(void);

#if(_DDCCI_SUPPORT == _ON)
extern void CEepromLoadBackLightDefault(void);
#endif

extern void CFlashInitialMISCPageStart();
extern void CFlashInitialMISCPageEnd();
#endif // End of #if(_MEMORY_LOCATION == _FLASH)

#if((_MEMORY_LOCATION == _FLASH) && (_EDID_PRO == _ON))
extern void CFlashSaveDDCData(void); // EDID pro
#endif // End of #if(_MEMORY_LOCATION == _FLASH)

extern bit CFlashCheckFlashType();
extern BYTE CFlashGetFlashDetailedInfo(BYTE ucFlashType, BYTE ucIndex);

#if(_AUTO_DETECT_FLASH_TYPE == _ON)
extern BYTE CFlashGetFlashSupportInfo(BYTE ucIndex);
#endif

extern bit CFlashWREN(BYTE ucPage);
extern bit CFlashWRDis(void);

#endif // End of #ifdef __REALTEK_FLASH__

// V015 System Patch Note (7) Modify 20100630 End

