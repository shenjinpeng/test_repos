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
// ID Code      : Version.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Information table length
//--------------------------------------------------
#define _INFOR_TABLE_LENGTH         0x08

// V012 Modify 20100326 Start
// V012 Patch Note (25) : Add scalar ID code checking in ISP.
//--------------------------------------------------
// Item End Flag
//--------------------------------------------------
#define _VERSION_ITEM_END           0xFE


//--------------------------------------------------
// FW Supported Scalar ID Code Table Count
//--------------------------------------------------
enum  FWSupportedScalerTypeEnum
{
    _SCALER_NO_RL6048,              // 0
    _SCALER_NO_RL6049,              // 1
    _SCALER_NO_RL6093,              // 2
    _SCALER_NO_RL6086,              // 3
    _SCALER_NO_RL6001,              // 4
    _SCALER_NO_RL6158,              // 5
    _SCALER_NO_RL6138,              // 6
    _SCALER_NO_RL6156,              // 7
    _SCALER_SUPPORTED_COUNT,
};


//--------------------------------------------------
// FW Supported Scalar Type Index
//--------------------------------------------------
#if(_SCALER_TYPE == _RTD2472D)
#define _FW_SUPPORTED_SCALER_INDEX  _SCALER_NO_RL6048
#elif((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#define _FW_SUPPORTED_SCALER_INDEX  _SCALER_NO_RL6049
#endif
// V012 Modify 20100326 End


//--------------------------------------------------
// Date Information
//--------------------------------------------------
#define _DATE_INFORMATION           20100921

#define _DATE_INFORMATION0          ((BYTE)((_DATE_INFORMATION >> 24) & 0x000000FF))
#define _DATE_INFORMATION1          ((BYTE)((_DATE_INFORMATION >> 16) & 0x000000FF))
#define _DATE_INFORMATION2          ((BYTE)((_DATE_INFORMATION >> 8)  & 0x000000FF))
#define _DATE_INFORMATION3          ((BYTE)((_DATE_INFORMATION >> 0)  & 0x000000FF))

/*
//--------------------------------------------------
// Flah EMULATION
//--------------------------------------------------
#define _FLASH_EMULATION            (_MEMORY_LOCATION & _BIT0)
*/
//--------------------------------------------------
// Eeprom EMULATION
//--------------------------------------------------
#define _EEPROM_EMULATION           (_MEMORY_LOCATION & _BIT0)

//--------------------------------------------------
// Checksum
//--------------------------------------------------
/*
#define _INFOR_CHECKSUM             (_INFOR_TABLE_LENGTH + _DATE_INFORMATION0 + _DATE_INFORMATION1 + _DATE_INFORMATION2 + _DATE_INFORMATION3 + _FLASH_TYPE + _FLASH_EMULATION)
*/
#define _INFOR_CHECKSUM             (_INFOR_TABLE_LENGTH + _DATE_INFORMATION0 + _DATE_INFORMATION1 + _DATE_INFORMATION2 + _DATE_INFORMATION3 + _FLASH_TYPE + _EEPROM_EMULATION)

//--------------------------------------------------
// Project Name
//--------------------------------------------------
#if(_PROJECT == _RTD2472D_DEMO_BOARD)

#define _PROJECT_NAME               'R', 'T', 'D', '2', '4', '7', '2', 'D', '_', 'D', 'e', 'm', 'o', _END_

#elif(_PROJECT == _RTD2472RD_DEMO_BOARD)

#define _PROJECT_NAME               'R', 'T', 'D', '2', '4', '7', '2', 'R', 'D', '_', 'D', 'e', 'm', 'o', _END_

#elif(_PROJECT == _RTD2545LR_DEMO_BOARD)

#define _PROJECT_NAME               'R', 'T', 'D', '2', '5', '4', '5', 'L', 'R', '_', 'D', 'e', 'm', 'o', _END_

#elif(_PROJECT == _RTD2472D_QA_BOARD)

#define _PROJECT_NAME               'R', 'T', 'D', '2', '4', '7', '2', 'D', '_', 'Q', 'A', _END_

#elif(_PROJECT == _RTD2545LR_QA_BOARD)

#define _PROJECT_NAME               'R', 'T', 'D', '2', '5', '4', '5', 'L', 'R', '_', 'Q', 'A', _END_

#elif(_PROJECT == _RTD2472RD_QA_BOARD)

#define _PROJECT_NAME               'R', 'T', 'D', '2', '4', '7', '2', 'R', 'D', '_', 'Q', 'A', _END_

#elif(_PROJECT == _RTD2270L_I_DEMO_BOARD)

#define _PROJECT_NAME               'R', 'T', 'D', '2', '2', '7', '0', 'I', '_', 'D', 'e', 'm', 'o', _END_

#elif(_PROJECT == _RTD2270L_I_QA_BOARD)

#define _PROJECT_NAME               'R', 'T', 'D', '2', '2', '7', '0', 'I', '_', 'Q', 'A', _END_

#elif(_PROJECT == _RTD2270L_M_DEMO_BOARD)

#define _PROJECT_NAME               'R', 'T', 'D', '2', '2', '7', '0', 'M', '_', 'D', 'e', 'm', 'o', _END_

#elif(_PROJECT == _RTD2270L_M_QA_BOARD)

#define _PROJECT_NAME               'R', 'T', 'D', '2', '2', '7', '0', 'M', '_', 'Q', 'A', _END_

#elif(_PROJECT == _RTD2270L_R_DEMO_BOARD)

#define _PROJECT_NAME               'R', 'T', 'D', '2', '2', '7', '0', 'R', '_', 'D', 'e', 'm', 'o', _END_

#elif(_PROJECT == _RTD2270L_R_QA_BOARD)

#define _PROJECT_NAME               'R', 'T', 'D', '2', '2', '7', '0', 'R', '_', 'Q', 'A', _END_

#else

#define _PROJECT_NAME               'N', 'U', 'L', 'L', _END_

#endif

//--------------------------------------------------
// Project Version
//--------------------------------------------------
#define _PROJECT_VERSION            'V', '0', '1', '6', _END_


#ifdef __MAIN__

BYTE code tFW_INFOR_TABLE[] =
{
    _INFOR_TABLE_LENGTH,    // Table Length
    _DATE_INFORMATION0,     // Date
    _DATE_INFORMATION1,
    _DATE_INFORMATION2,
    _DATE_INFORMATION3,
    _FLASH_TYPE,            // Flash Type
    /*
    _FLASH_EMULATION,       // Flash Emulation
    */
    _EEPROM_EMULATION,      // Eeprom Emulation
    _INFOR_CHECKSUM,        // Check Sum
    _PROJECT_NAME,          // Project Name
    _PROJECT_VERSION,       // Project Version
};


// V012 Modify 20100326 Start
// V012 Patch Note (25) : Add scalar ID code checking in ISP.
//--------------------------------------------------
// Scalar ID Code Check Function Key Word
//--------------------------------------------------
BYTE code tSCALER_IDCODE_INFO_MAGIC_CODE[] =
{
    0x09, 0x05, 0x02, 0x07,
};


//--------------------------------------------------
// Current Scalar Type Index Setting
//--------------------------------------------------
BYTE code tSCALER_SUPPORT_INFO[] =
{
    _FW_SUPPORTED_SCALER_INDEX, // Current Scalar type index
    _SCALER_SUPPORTED_COUNT,    // Supported Scaler Type Count
};


//--------------------------------------------------
// Scalar ID Code Table
//--------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
//  Please do not change the order of below scalar ID Code tables arbitrarily //
////////////////////////////////////////////////////////////////////////////////

BYTE code tSCALER_RL6048_IDCODE_INFO[] =
{
    // Scalar Type : RL6048
    // A, B, C, D, E
    0x01, 0x02, 0x02, 0x04, 0x05, _VERSION_ITEM_END,
};

BYTE code tSCALER_RL6049_IDCODE_INFO[] =
{
    // Scalar Type : RL6049
    // A, B, C, D, E, F, G, H
    0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x0F, _VERSION_ITEM_END,
};

BYTE code tSCALER_RL6093_IDCODE_INFO[] =
{
    // Scalar Type : RL6093
    // A, B, C
    0x21, 0x22, 0x23, _VERSION_ITEM_END,
};

BYTE code tSCALER_RL6086_IDCODE_INFO[] =
{
    // Scalar Type : RL6086
    // A, B, C
    0x61, 0x69, 0x62, 0x6A, 0x63, 0x6B, _VERSION_ITEM_END,
};

BYTE code tSCALER_RL6001_IDCODE_INFO[] =
{
    // V016 System Patch Note (16) Modify 20100824 Start
    // Patch Reason : Add new ID Code for the new IC.
    /*
    // Scalar Type : RL6001
    // Version A, B
    0x31, 0x32, _VERSION_ITEM_END,
    */
    // Scalar Type : RL6001
    // A, B, C
    0x31, 0x32, 0x33, _VERSION_ITEM_END,
    // V016 System Patch Note (16) Modify 20100824 End
};

BYTE code tSCALER_RL6158_IDCODE_INFO[] =
{
    // V016 System Patch Note (16) Modify 20100824 Start
    // Patch Reason : Add new ID Code for the new IC.
    /*
    // Scalar Type : RL6158
    // Version A, B
    0x71, 0x79, _VERSION_ITEM_END,
    */
    // Scalar Type : RL6158
    // A, B
    0x71, 0x79, 0x72, 0x7A, _VERSION_ITEM_END,
    // V016 System Patch Note (16) Modify 20100824 End
};

BYTE code tSCALER_RL6138_IDCODE_INFO[] =
{
    // Scalar Type : RL6138
    // A
    0x51, _VERSION_ITEM_END,
};

BYTE code tSCALER_RL6156_IDCODE_INFO[] =
{
    // V016 System Patch Note (16) Modify 20100824 Start
    // Patch Reason : Add new ID Code for the new IC.
    /*
    // Scalar Type : RL6156
    // Version A
    0xB1, _VERSION_ITEM_END,
    */
    // Scalar Type : RL6156
    // A, B, C, D
    0xB1, 0xB2, 0xB3, _VERSION_ITEM_END,
    // V016 System Patch Note (16) Modify 20100824 End
};
// V012 Modify 20100326 End

#endif


