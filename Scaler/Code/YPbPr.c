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
// ID Code      : YPbPr.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __YPBPR__

#include "Common\Header\Include.h"

#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

#if(_YPBPR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Search mode for YPbPr
// Input Value  : None
// Output Value : YPbPr Mode number
//--------------------------------------------------
BYTE CYPbPrSearchMode(void)
{
    BYTE cnt, modetemp = _MODE_NOSUPPORT;

    for(cnt = 0; cnt < _MAX_YPBPR_MODE; cnt++)
    {
        if(CYPbPrCompareMode(cnt) == _TRUE)
        {
            modetemp = cnt;

            // V013 VGA Patch Note (5) 20100409 Modify Start
            // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
            modetemp = CYPbPrSearchAcceptiveMode(cnt);
            // V013 VGA Patch Note (5) 20100409 Modify End

            break;
        }
    }

    return modetemp;
}

//--------------------------------------------------
// Description  : Compare mode in YPbPr mode table
// Input Value  : Mode number
// Output Value : Return _TRUE if get an available mode
//--------------------------------------------------
bit CYPbPrCompareMode(BYTE ucModeCnt)
{
    if(abs(stModeInfo.IVFreq - tYPBPR_MODE_TABLE[ucModeCnt].IVFreq) > tYPBPR_MODE_TABLE[ucModeCnt].IVFreqTolerance)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IHFreq - tYPBPR_MODE_TABLE[ucModeCnt].IHFreq) > tYPBPR_MODE_TABLE[ucModeCnt].IHFreqTolerance)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IVTotal - tYPBPR_MODE_TABLE[ucModeCnt].IVTotal) > 1)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get mode information for YPbPr
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CYPbPrGetModeInfo(void)
{
    stModeInfo.IHTotal = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IHTotal;
    stModeInfo.IHStartPos = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IHStartPos;
    stModeInfo.IHWidth = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IHWidth;
    stModeInfo.IVStartPos = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IVStartPos;
    stModeInfo.IVHeight = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IVHeight;

// V013 VGA Patch Note (10) 20100416 Modify Start
// Patch Reason : Support Auto Config For Yuv Color.
#if((_FIFO_MODE_ONLY == _OFF) || (_YUV_AUTO_CONFIG_SUPPORT == _OFF))
// V013 VGA Patch Note (10) 20100416 Modify End

    stModeUserData.Clock = stModeInfo.IHTotal;
    stModeUserData.Phase = 0;
    stModeUserData.HPosition = stModeInfo.IHStartPos;
    stModeUserData.VPosition = stModeInfo.IVStartPos;

    // Test
    stModeUserCenterData.CenterClock = stModeInfo.IHTotal;
    stModeUserCenterData.CenterHPos = stModeInfo.IHStartPos;
    stModeUserCenterData.CenterVPos = stModeInfo.IVStartPos;

// V013 VGA Patch Note (10) 20100416 Modify Start
// Patch Reason : Support Auto Config For Yuv Color.
#else
    CEepromLoadCenterModeData(stModeInfo.ModeCurr);
#endif
// V013 VGA Patch Note (10) 20100416 Modify End
}

//--------------------------------------------------
// Description  : Start up settings for YPbPr
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CYPbPrStartUp(void)
{
    CScalerCodeW(tYPBPR_TABLE_SET_SCALER);

    // V013 VGA Patch Note (23) Modify 20100513 Start
    // Patch Reason : For Video Mode Clamp Position Setting Flow
    /*
    CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_G_CLAMP_START_00);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D, tYPBPR_CLAMP_POSITION_TABLE[(stModeInfo.ModeCurr * 2)]);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D, tYPBPR_CLAMP_POSITION_TABLE[(stModeInfo.ModeCurr * 2 + 1)]);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D, tYPBPR_CLAMP_POSITION_TABLE[(stModeInfo.ModeCurr * 2)]);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D, tYPBPR_CLAMP_POSITION_TABLE[(stModeInfo.ModeCurr * 2 + 1)]);
    */
    CYPbPrModeClampPositionSetting();
    // V013 VGA Patch Note (23) Modify 20100513 End
}

//--------------------------------------------------
// Description  : Setup YPbPr mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CYPbPrSetupMode(void)
{
// V013 VGA Patch Note (10) 20100416 Modify Start
// Patch Reason : Support Auto Config For Yuv Color.
#if((_FIFO_MODE_ONLY == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _ON))
    // Load mode user data from eeprom
    CEepromLoadModeData(stModeInfo.ModeCurr);
#endif
// V013 VGA Patch Note (10) 20100416 Modify End

    // Get information from mode table, such as IHTotal, IHStartPos, IHWidth, IVStartPos, IVHeight.
    CYPbPrGetModeInfo();

    // V016 VGA Patch Note (11) Modify 20100830 Start
    // Patch Reason : Modify Color Space Load Data Position For OverScan.
#if(_COLOR_FORMAT_CONVERT == _ON)
    CModeGetCurrentModeColorFormat();
#endif
    // V016 VGA Patch Note (11) Modify 20100830 End

    // Start up settings of VGA mode.
    CModeStartUpVGA();

    // Start up settings of YPbPR mode.
    CYPbPrStartUp();

// V012 Modify 20100316 Start
// V012 Patch Note (2) : Overscan function update.
#if(_OVERSCAN_SUPPORT == _ON)
    CModeOverScanSelect();
#endif
// V012 Modify 20100316 End

    // Get scaling option, Capture window setup, Scaling setup, Display setup
    CModeSetupDisplay();

    // Setup color processing
    CModeSetupColorProcess();

    CAdjustAdcGainOffset();

    CAdjustAdcClock(stModeUserData.Clock);

    CAdjustDcRestore();

    CAdjustPhase(stModeUserData.Phase);
    CAdjustHPosition();
    CAdjustVPosition();

    // V012 Modify 20100321 Start
    // V012 Patch Note (14) : Fix the issue that SOG interlace signal could not light up the display when  V sync pulse is only 1H.
    CModeCheckDVTotal();
    // V012 Modify 20100321 End

    CScalerPageSelect(_PAGE2);

    CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    CScalerSetBit(_P2_TMDS_OUTPUT_CTRL_A6, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // V013 VGA Patch Note (16) Modify 20100422 Start
    // Patch Reason : Add fineTune display position for VGA interlace mode.
    /*
    switch(stModeInfo.ModeCurr)
    {
        case 0: // 576i
        case 1: // 480i
        case 5: // 1080i 50Hz
        case 6: // 1080i 60Hz

        // V013 VGA Patch Note (5) 20100409 Modify Start
        // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
        case _VIDEO_1920x1080i_50HZ_2: // 1080i 50Hz_2
        // V013 VGA Patch Note (5) 20100409 Modify End

            CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, _BIT7);
            CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT0, _BIT0);
            CFrameSyncFineTune(_ODD);
            break;

    }
    */
    CFrameSyncAnalogFineTune();
    // V013 VGA Patch Note (16) Modify 20100422 End

#if(_FRC_SUPPORT == _ON)
    if(!GET_FRCSTATUS())
    {
        CModeSetFIFOForFrameSync();
#else
    {
#endif
        pData[0] = CFrameSyncDo();


        if(pData[0] == 2)
        {
            CModeResetMode();
            return;
        }
    }

// Issac-04-12 Begin
#if((_MEMORY_WORK_TYPE == _OD_ON_FRC_ON) || (_MEMORY_WORK_TYPE == _OD_OFF_FRC_ON))
    else
    {
#if(_FIELD_MERGE_SUPPORT == _ON)
        if(GET_FIELDMERGE_MODE())
        {
            CScalerSetBit(_VGIP_SIGINV_11, ~_BIT4, _BIT4);
        }
#endif
        // Disable video compensation & IVS-to-DVS-delay control by ODD when FRC
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0);
        CScalerSetBit(_FS_DELAY_FINE_TUNING_43, ~_BIT1, 0);
    }
#endif
// Issac-04-12 End

    CModeSetupEtcs(_FUNCTION_ENABLE);

    // V014 VGA Patch Note (6) Modify 20100527 Start
    // Patch Reason : Modify Video Mode Can't Light On
    /*
    CAdjustAdcClock(stModeUserData.Clock);
    */
    // V014 VGA Patch Note (6) Modify 20100527 End
}

// V013 VGA Patch Note (5) 20100409 Modify Start
// Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
//--------------------------------------------------
// Description  : YPbPr Search Acceptive Mode
// Input Value  : YPbPr Mode Table Index
// Output Value : YPbPr Mode Table Index
//--------------------------------------------------
BYTE CYPbPrSearchAcceptiveMode(BYTE ucModeCnt)
{
    if((ucModeCnt == _VIDEO_720x576p_50HZ) && (GET_INTERLACE_MODE() == 1))
    {
        ucModeCnt = _VIDEO_1920x1080i_50HZ_2;
    }

    return ucModeCnt;
}
// V013 VGA Patch Note (5) 20100409 Modify End

// V013 VGA Patch Note (23) Modify 20100513 Start
// Patch Reason : For Video Mode Clamp Position Setting Flow
//--------------------------------------------------
// Description  : Clamp Position settings for YPbPr Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CYPbPrModeClampPositionSetting(void)
{
    CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_G_CLAMP_START_00);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D, tYPBPR_CLAMP_POSITION_TABLE[(stModeInfo.ModeCurr * 2)]);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D, tYPBPR_CLAMP_POSITION_TABLE[(stModeInfo.ModeCurr * 2 + 1)]);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D, tYPBPR_CLAMP_POSITION_TABLE[(stModeInfo.ModeCurr * 2)]);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D, tYPBPR_CLAMP_POSITION_TABLE[(stModeInfo.ModeCurr * 2 + 1)]);
}
// V013 VGA Patch Note (23) Modify 20100513 End

#endif  // End of #if(_YPBPR_SUPPORT == _ON)

#endif  // End of #if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

