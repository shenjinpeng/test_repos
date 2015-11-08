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
// ID Code      : DisplayPort.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __DISPLAYPORT__

#include "Common\Header\Include.h"

#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

#if(_DP_SUPPORT == _ON)

//--------------------------------------------------
// Description  : AUX Link Training Pattern 1 interrupt
// Input Value  :
// Output Value :
//--------------------------------------------------
void CDpFakeTrainPattern1(void)
{
    // Read source lane
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);
    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpLaneCount);

    if((g_ucAdjustRequestL01 & 0x03) == 0x00)
    {
        if((g_ucDpLaneCount & 0x01) == 0x01)    // 1 lane
        {
            g_ucLane01Status |= 0x00;
            g_ucAdjustRequestL01 |= 0x02;
        }
        else if ( (g_ucDpLaneCount & 0x02) == 0x02 )    // 2 lane
        {
            g_ucLane01Status |= 0x00;
            g_ucAdjustRequestL01 |= 0x22;
        }
        else    // 4 lane
        {
            g_ucLane01Status |= 0x00;
            g_ucLane23Status |= 0x00;
            g_ucAdjustRequestL01 |= 0x22;
            g_ucAdjustRequestL23 |= 0x22;
        }

        g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN1_FAIL;
    }
    else
    {
        if((g_ucDpLaneCount & 0x01) == 0x01)            // 1 lane
        {
            g_ucLane01Status |= 0x01;
        }
        else if((g_ucDpLaneCount & 0x02) == 0x02)       // 2 lane
        {
            g_ucLane01Status |= 0x11;
        }
        else                                        // 4 lane
        {
            g_ucLane01Status |= 0x11;
            g_ucLane23Status |= 0x11;
        }

        g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN1_PASS;
        g_bFakeTP1Pass = 1;
    }

    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x02);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucLane01Status);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucLane23Status);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x04);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x80);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x06);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucAdjustRequestL23);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x07);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucAdjustRequestL23);
}


//--------------------------------------------------
// Description  : AUX fast Link Training Pattern 2 interrupt
// Input Value  :
// Output Value :
//--------------------------------------------------
void CDpFakeTrainPattern2(void)
{
    // Read source lane
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);
    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpLaneCount);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucTrainingLaneSet);

    if(((g_ucAdjustRequestL01 & 0x0C) == 0x00) && ((g_ucTrainingLaneSet & 0x18) == 0x00))
    {
        if((g_ucDpLaneCount & 0x01) == 0x01)    // 1 lane
        {
            g_ucLane01Status |= 0x01;
            g_ucAdjustRequestL01 |= 0x06;
        }
        else if ( (g_ucDpLaneCount & 0x02) == 0x02 )    // 2 lane
        {
            g_ucLane01Status |= 0x11;
            g_ucAdjustRequestL01 |= 0x66;
        }
        else    // 4 lane
        {
            g_ucLane01Status |= 0x11;
            g_ucLane23Status |= 0x11;
            g_ucAdjustRequestL01 |= 0x66;
            g_ucAdjustRequestL23 |= 0x66;
        }
        g_ucAlignStatus = 0x80;
        g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN2_FAIL;
    }
    else
    {
        if((g_ucDpLaneCount & 0x01) == 0x01)            // 1 lane
        {
            g_ucLane01Status |= 0x07;
        }
        else if((g_ucDpLaneCount & 0x02) == 0x02)       // 2 lane
        {
            g_ucLane01Status |= 0x77;

        }
        else                                        // 4 lane
        {
            g_ucLane01Status |= 0x77;
            g_ucLane23Status |= 0x77;
        }
        g_ucAlignStatus = 0x81;
        g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN2_PASS;
        g_bFakeTP2Pass = 1;
    }

    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x02);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucLane01Status);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucLane23Status);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x04);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucAlignStatus);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x06);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucAdjustRequestL01);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x07);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucAdjustRequestL23);
}

//--------------------------------------------------
// Description  : AUX Fake Link Training Pattern End interrupt
// Input Value  :
// Output Value :
//--------------------------------------------------
void CDpFakeTrainPatternEnd(void)
{
    g_ucLane01Status = 0;
    g_ucLane23Status = 0;

    g_ucAdjustRequestL01 = 0;
    g_ucAdjustRequestL23 = 0;

    g_bHDCPFail = _FALSE;

    g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_END;
}

//--------------------------------------------------
// Description  : AUX Link Training Pattern 1 interrupt
// Input Value  :
// Output Value :
//--------------------------------------------------
void CDpTrainPattern1(void)
{
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);

    // Read Bit Rate
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x00);
    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpRate);

    // Read Lane Count
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);
    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpLaneCount);

    // EQ Training CRC Disable
    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xb3);
    CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x00);

    // Disable CMU (PHY CTS)
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
    CScalerSetByteInt(_PB_DP_PWR_CTL_B4, 0x00);

    // Set PHY
    CScalerSetByteInt(_PB_DIG00_E0, 0xC0);
    CScalerSetByteInt(_PB_DP_RXMISC_02_AF, 0x87);
    CScalerSetByteInt(_PB_DP_RESERVED_05_BF, 0xF0);

    // Inverse DP Clock
    CScalerSetByteInt(_PB_DIG01_E1, 0xf0);

    if((g_ucDpRate & 0x0A) == 0x0A) // High Bit Rate for Mode Detect
    {
        //Set 2.7Ghz Bandwidth
        CScalerSetByteInt(_PB_DP_CDR_03_A3, 0x8C);
        CScalerSetByteInt(_PB_DP_RXMISC_01_AE, 0x01);
        CScalerSetByteInt(_PB_DP_FLD_08_AC, 0xC0);
        CScalerSetByteInt(_PB_DP_ADP_EQ_B2, 0x5E);

        CScalerSetByteInt(_PB_DP_CDR_01_A1, 0x32);
        CScalerSetByteInt(_PB_DP_CDR_02_A2, 0x01);
        CScalerSetByteInt(_PB_DP_FLD_09_AD, 0x8f);
        CScalerSetByteInt(_PB_DP_RXMISC_02_AF, 0xC7);
    }
    else if((g_ucDpRate & 0x06) == 0x06) // Low Bit Rate for Mode Detect
    {
        //Set 1.62G Bandwidth
        CScalerSetByteInt(_PB_DP_CDR_03_A3, 0x8C);
        CScalerSetByteInt(_PB_DP_RXMISC_01_AE, 0x01);
        CScalerSetByteInt(_PB_DP_FLD_08_AC, 0x40);
        CScalerSetByteInt(_PB_DP_ADP_EQ_B2, 0x56);

        CScalerSetByteInt(_PB_DP_CDR_01_A1, 0x72);
        CScalerSetByteInt(_PB_DP_CDR_02_A2, 0x21);
        CScalerSetByteInt(_PB_DP_FLD_09_AD, 0x8f);
        CScalerSetByteInt(_PB_DP_RXMISC_02_AF, 0xC7);
    }
    else //ATI Dos mode case 4lane/RBR
    {
        //Set 1.62G Bandwidth
        CScalerSetByteInt(_PB_DP_CDR_03_A3, 0x8C);
        CScalerSetByteInt(_PB_DP_RXMISC_01_AE, 0x01);
        CScalerSetByteInt(_PB_DP_FLD_08_AC, 0x40);
        CScalerSetByteInt(_PB_DP_ADP_EQ_B2, 0x56);

        CScalerSetByteInt(_PB_DP_CDR_01_A1, 0x72);
        CScalerSetByteInt(_PB_DP_CDR_02_A2, 0x21);
        CScalerSetByteInt(_PB_DP_FLD_09_AD, 0x8f);
        CScalerSetByteInt(_PB_DP_RXMISC_02_AF, 0xC7);

        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);

        // Set Bit Rate at RBR
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x00);
        CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x06);

        // Set 4 lane
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);
        CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x84);
    }

    // Scramble Disable
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB); // ATI Dos mode bug
    CScalerSetByteInt(_PB_DIG02_E2, 0xC0);

    g_ucButInt = 0;

    if((g_ucDpLaneCount & 0x01) == 0x01)
    {
        // 1 lane
        g_ucButInt |= _BIT3;
    }
    else if((g_ucDpLaneCount & 0x02) == 0x02)
    {
        // 2 lane
        g_ucButInt |= _BIT4;
    }
    else
    {
        // 4 lane
        g_ucButInt |= (_BIT4 | _BIT3);
    }

    if((g_ucDpLaneCount & 0x80) == 0x80)
    {
        // Set Enhanced Mode
        g_ucButInt |= _BIT2;
    }

    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DP_CTL_A1, g_ucButInt);

    //Set Lane Swap
    CScalerSetByteInt(_PC_LANE_SWAP_A4, 0x1B);

    if((g_ucDpLaneCount & 0x01) == 0x01)   // 1 lane
    {
        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
        CScalerSetByteInt(_PB_DP_PWR_CTL_B4, 0x11);

        // Reset FLD
        if((g_ucDpRate & 0x0A) == 0x0A)
        {
            CScalerSetByteInt(_PB_DP_FLD_08_AC, 0xC8);
            CScalerSetByteInt(_PB_DP_FLD_08_AC, 0xC0);
        }
        else if((g_ucDpRate & 0x06) == 0x06)
        {
            CScalerSetByteInt(_PB_DP_FLD_08_AC, 0x48);
            CScalerSetByteInt(_PB_DP_FLD_08_AC, 0x40);
        }

        CScalerSetByteInt(_PB_DP_OOBS_RXAMP_B0, 0x8d);
        CScalerSetByteInt(_PB_DP_OOBS_RXAMP_B0, 0x0d);

        // Wait for Stable When Phy Power ON/OFF
        /*
        for(g_ucButInt=0; g_ucButInt<=20; g_ucButInt++)
        */
        for(g_ucButInt = 0; g_ucButInt <= 30; g_ucButInt++)
        {
            _nop_();
        }

        CDpTP1Lane0Check();

        if((g_ucLane01Status & 0x01) == 0x01)
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN1_PASS;
        }
        else
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN1_FAIL;
        }
    }
    else if((g_ucDpLaneCount & 0x02) == 0x02)  // 2 lane
    {
        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
        CScalerSetByteInt(_PB_DP_PWR_CTL_B4, 0x33);

        // Reset FLD
        if((g_ucDpRate & 0x0A) == 0x0A)
        {
            CScalerSetByteInt(_PB_DP_FLD_08_AC, 0xC8);
            CScalerSetByteInt(_PB_DP_FLD_08_AC, 0xC0);
        }
        else if((g_ucDpRate & 0x06) == 0x06)
        {
            CScalerSetByteInt(_PB_DP_FLD_08_AC, 0x48);
            CScalerSetByteInt(_PB_DP_FLD_08_AC, 0x40);
        }

        CScalerSetByteInt(_PB_DP_OOBS_RXAMP_B0, 0x8d);
        CScalerSetByteInt(_PB_DP_OOBS_RXAMP_B0, 0x0d);


        // Wait for Stable of Phy Power ON/OFF
        /*
        for(g_ucButInt=0; g_ucButInt<=20; g_ucButInt++)
        */
        for(g_ucButInt = 0; g_ucButInt <= 30; g_ucButInt++)
        {
            _nop_();
        }

        CDpTP1Lane0Check();
        CDpTP1Lane1Check();

        if ((g_ucLane01Status & 0x11) == 0x11)
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN1_PASS;
        }
        else
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN1_FAIL;
        }
    }
    else    // 4 lane
    {
        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
        CScalerSetByteInt(_PB_DP_PWR_CTL_B4, 0xFF);

        // Reset FLD
        if((g_ucDpRate & 0x0A) == 0x0A)
        {
            CScalerSetByteInt(_PB_DP_FLD_08_AC, 0xC8);
            CScalerSetByteInt(_PB_DP_FLD_08_AC, 0xC0);
        }
        else if((g_ucDpRate & 0x06) == 0x06)
        {
            CScalerSetByteInt(_PB_DP_FLD_08_AC, 0x48);
            CScalerSetByteInt(_PB_DP_FLD_08_AC, 0x40);
        }

        CScalerSetByteInt(_PB_DP_OOBS_RXAMP_B0, 0x8d);
        CScalerSetByteInt(_PB_DP_OOBS_RXAMP_B0, 0x0d);

        // Wait for Stable of Phy Power ON/OFF
        /*
        for(g_ucButInt=0; g_ucButInt<=20; g_ucButInt++)
        */
        for(g_ucButInt = 0; g_ucButInt <= 30; g_ucButInt++)
        {
            _nop_();
        }

        CDpTP1Lane0Check();
        CDpTP1Lane1Check();
        CDpTP1Lane2Check();
        CDpTP1Lane3Check();

        if(((g_ucLane01Status & 0x11) == 0x11) && ((g_ucLane23Status & 0x11) == 0x11))
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN1_PASS;
        }
        else
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN1_FAIL;
        }
    }

    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x06);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucAdjustRequestL01);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x07);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucAdjustRequestL23);

    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x02);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucLane01Status);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucLane23Status);

    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x04);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x80);

    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
    CScalerSetByteInt(_PB_DIG02_E2, 0x00);
    CScalerSetByteInt(_PB_DIG03_E3, 0x21);
    CScalerSetByteInt(_PB_DIG03_E3, 0x01);

    if((g_ucDpRate & 0x0A) == 0x0A)
    {
        CScalerSetByteInt(_PB_DP_ADP_EQ_B2, 0x7E);
        CScalerSetByteInt(_PB_DP_RESERVED_05_BF, 0xF0);
        CScalerSetByteInt(_PB_DP_FLD_09_AD, 0x87);
    }
    else if((g_ucDpRate & 0x06) == 0x06)
    {
        CScalerSetByteInt(_PB_DP_ADP_EQ_B2, 0x76);
        CScalerSetByteInt(_PB_DP_RESERVED_05_BF, 0xF0);
        CScalerSetByteInt(_PB_DP_FLD_09_AD, 0x87);
    }
}

//--------------------------------------------------
// Description  : AUX Link Training Pattern 2 interrupt
// Input Value  :
// Output Value :
//--------------------------------------------------
void CDpTrainPattern2(void)
{
    // Reset FLD
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
    CScalerSetByteInt(_PB_DP_OOBS_RXAMP_B0, 0x8d);
    CScalerSetByteInt(_PB_DP_OOBS_RXAMP_B0, 0x0d);

    // Wait for Stable when reset
    for(g_ucButInt = 0; g_ucButInt <= 30; g_ucButInt++)
    {
        _nop_();
    }

    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
    CScalerSetByteInt(_PB_DIG02_E2, 0x80);

    // Read Source Lane
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);
    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpLaneCount);

    if((g_ucDpLaneCount&0x01) == 0x01)  // 1 Lane
    {
        CDpTP21LaneCheck();

        if((g_ucLane01Status == 0x07) && (g_ucAlignStatus == 0x81))
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN2_PASS;
        }
        else
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN2_FAIL;
        }
    }
    else if((g_ucDpLaneCount & 0x02) == 0x02)   // 2 Lanes
    {
        CDpTP22LaneCheck();

        if((g_ucLane01Status == 0x77) && (g_ucAlignStatus == 0x81))
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN2_PASS;
        }
        else
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN2_FAIL;
        }
    }
    else    // 4 lanes
    {
        CDpTP24LaneCheck();

        if((g_ucLane01Status == 0x77) && (g_ucLane23Status == 0x77) && (g_ucAlignStatus == 0x81))       // for CTS process
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN2_PASS;
        }
        else
        {
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN2_FAIL;
        }
    }

    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x02);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucLane01Status);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucLane23Status);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x04);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucAlignStatus);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x06);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucAdjustRequestL01);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x07);
    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, g_ucAdjustRequestL23);

    // Disable EQ-CRC Circuit
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xb3);
    CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x0F);

    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
    CScalerSetByteInt(_PB_DIG02_E2, 0x00);
}

//--------------------------------------------------
// Description  : AUX Link Training Pattern End interrupt
// Input Value  :
// Output Value :
//--------------------------------------------------
void CDpTrainPatternEnd(void)
{
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);

    // Read Bit Rate
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x00);
    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpRate);

    // Read Lane Count
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);
    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpLaneCount);

    // DP Mac Power Down
    CScalerSetByteInt(_PC_DP_CTL_A1, 0x40);

    g_ucButInt = 0;

    if((g_ucDpLaneCount & 0x01) == 0x01)
    {
        // 1 lane
        g_ucButInt |= _BIT3;
    }
    else if((g_ucDpLaneCount & 0x02) == 0x02)
    {
        // 2 lane
        g_ucButInt |= _BIT4;
    }
    else
    {
        // 4 lane
        g_ucButInt |= (_BIT4 | _BIT3);
    }

    if((g_ucDpLaneCount & 0x80) == 0x80)
    {
        // Set Enhanced Mode
        g_ucButInt |= _BIT2;
    }

    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DP_CTL_A1, g_ucButInt);

    g_ucLane01Status = 0;
    g_ucLane23Status = 0;

    g_ucAdjustRequestL01 = 0;
    g_ucAdjustRequestL23 = 0;

    g_bHDCPFail = _FALSE;

    g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_END;
}

//--------------------------------------------------
// Description  : AUX Link Training Pattern None interrupt
// Input Value  :
// Output Value :
//--------------------------------------------------
void CDpTrainPatternNone(void)
{
    g_ucAdjustRequestL01 = 0;
    g_ucAdjustRequestL23 = 0;

    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x70);
    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpTPStatus);

    // Test Sink CRC Start
    if((g_ucDpTPStatus&0x01) == 0x01 )
    {
        g_bDpCRCStart = 1;
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x46);
        CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x20);       // Reset Test_CRC_Count

        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x40);     // Reset RGB Test CRC value
        CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x41);
        CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x42);
        CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x43);
        CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x44);
        CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x45);
        CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x00);
    }

#if(_DP_POWER_MANAGEMENT == _ON)   // MacBook-Issue-CLR_DPCD_STATUS
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x06);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x00);
    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpTPStatus);

    if((g_ucDpTPStatus & 0x03) == 0x02)
    {
        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x02);
        CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
        CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x04);
        CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x80);

        g_ucDpPowerStatus = _DP_POWER_DOWN;
    }
    else if(g_ucDpPowerStatus == _DP_POWER_DOWN)
    {
        g_ucDpPowerStatus = _DP_POWER_NORMAL;
    }
#endif // End of #if(_DP_POWER_MANAGEMENT == _ON)
}


//--------------------------------------------------
// Description  : DP initial !!
// Input Value  : None
// Output Value :
//--------------------------------------------------
void CDpInitial(void)
{
    // DPCD table arrangement
    CScalerCodeW(tDP_DPCD_TABLE);

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DP_OUTPUT_CLK_CTL_A3, 0x00);

    // Aux setting
    CScalerSetByte(_PC_DP_RESERVE2_BC, 0x22);

    // High aux Z0
    CScalerSetDataPortByte(_PS_ACCESS_PORT_8D, 0x02, 0x20);

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
#if (_DP_PHYCTS_STEPBYSTEP == _ON)
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, 0x08, 0x00); // Clear the CTS enable register
#endif
#endif

#if (_DP_POWER_MANAGEMENT == _ON)

    g_ucDpPowerStatus = _DP_POWER_NORMAL;

    // Enable to DPCD 0x600 write
    CScalerPageSelect(_PAGEC);
    CScalerSetBit(_PC_DP_RESERVE2_BC, ~_BIT4, _BIT4);

    // DPCD 0x600 set to normal operation
    CScalerSetBit(_PC_DP_RESERVE2_BC, ~_BIT3, _BIT2);

    // Disable to DPCD 0x600 write
    CScalerSetBit(_PC_DP_RESERVE2_BC, ~_BIT4, 0x00);
#endif
}

//--------------------------------------------------
// Description  : DISABLE DP PHY/MAC and AUX channel
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpPowerDown(void)
{
    // Disable DP PHY
    CScalerPageSelect(_PAGEB);
    /*
    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);
    */
    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x00);

    // Reset DP Mac
    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_AUX_MODE_SET_D0, 0xE1);
    CScalerSetByte(_PC_DP_CTL_A1, 0x40);
    CScalerSetByte(_PC_DP_CTL_A1, 0x00);
    CScalerSetByte(_PC_AUX_MODE_SET_D0, 0xE3);
}

//--------------------------------------------------
// Description  : Dp interrupt initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpInterruptInitial(void)
{
    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_AUX_IIC_SET_D1, 0x02);
    CScalerSetByte(_PC_DPCD_CTL_C0, 0x00);
    CScalerSetByte(_PC_AUX_IRQ_STATUS_EN_DD, 0x04);
    CScalerSetByte(_PC_AUX_MODE_SET_D0, 0xE3);
    CScalerSetByte(_PC_DP_HDCP_IRQ_E3, 0x03);
    CScalerSetByte(_IRQ_CTRL0_04, 0x80);

    CScalerPageSelect(_PAGEB);

    /*
    if(GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT)
    {
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x02);
    }
    else if(GET_INPUT_PORT(g_ucSearchIndex) == _D1_INPUT_PORT)
    {
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x06);
    }
    */
#if (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x02);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x06);
#endif

    // DP AUX Initial
    CScalerSetByte(_PB_DP_AUX_00_B3, 0x80);
    CScalerSetByte(_PB_DP_AUX_01_B8, 0x51);
    CScalerSetByte(_PB_DP_AUX_02_B9, 0x05);
    CScalerSetBit(_PB_DIG03_E3, ~(_BIT0 | _BIT1), _BIT0);   // AUX clock: 27 MHz
}

//--------------------------------------------------
// Description  : Dp hotplug process (Long)
// Input Value  : ms Byte data of hot plug
// Output Value : None
//--------------------------------------------------
void CDpHotPlugProc(BYTE ms)
{
    CDpPowerDown();
    CDpInterruptInitial();
    CDpInitial();
    CScalerCodeW(tDP_DPCD_INITIAL);

#if(_HDCP_SUPPORT == _ON)
    CDpAdjustHDCP();
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    D0_HPD_LOW();
    CTimerDelayXms(ms);
    D0_HPD_HIGH();
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    D1_HPD_LOW();
    CTimerDelayXms(ms);
    D1_HPD_HIGH();
#endif

    // Enable INT0
    IE |= 0x01;
}

//--------------------------------------------------
// Description  : Dp Short hotplug process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpShortHotPlugProc(BYTE ms)
{
    CScalerCodeW(tDP_DPCD_INITIAL);

#if(_MCU_TYPE == _REALTEK_EMBEDDED)

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    D0_HPD_LOW();
    CTimerDelayXms(ms);
    D0_HPD_HIGH();
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    D1_HPD_LOW();
    CTimerDelayXms(ms);
    D1_HPD_HIGH();
#endif

#else
    // HPD
    CScalerPageSelect(_PAGEE);
    CScalerSetByte(_PE_PIN_SHARE_CTRL01_D5, 0x1c);
    CScalerSetByte(_PE_CEC_CR0_EB, 0x90);

    // 1ms: AMD or 10ms: Quanmdata/unigraf
    CTimerDelayXms(ms);
    CScalerSetByte(_PE_CEC_CR0_EB, 0xb0);
#endif

}

//--------------------------------------------------
// Description  : Dp Short hotplug process for CP IRQ(DP HDCP Fail)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpCPIRQ(BYTE ms)
{
    if(g_bFakeTPEndPass == _TRUE)
    {


        // Mac Reset
        CScalerPageSelect(_PAGEC);
        CScalerSetByte(_PC_AUX_MODE_SET_D0, 0xE1);
        CScalerSetBit(_PC_DP_CTL_A1, ~_BIT6, _BIT6);
        CScalerSetBit(_PC_DP_CTL_A1, ~_BIT6, 0x00);
        CScalerSetByte(_PC_AUX_MODE_SET_D0, 0xE3);

        g_bFakeTPEndPass = _FALSE;
    }

    // CP IRQ Flag
    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);
    CScalerSetDataPortBit(_PC_DPCD_ACCESS_PORT_L_C3, 0x01, ~_BIT2, _BIT2);

    // Reset HDCP Link Failure
    CScalerSetBit(_PC_DP_HDCP_INTGT_VRF_E4, ~_BIT7, 0x00);
    CScalerSetBit(_PC_DP_HDCP_INTGT_VRF_E4, ~_BIT7, _BIT7);

    // Manual Set DPCD
    CScalerSetByte(_PC_DP_HDCP_IRQ_E3, 0x3F);

    // CLR An
    CDpHDCPReset();

    g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_END;

#if(_MCU_TYPE == _REALTEK_EMBEDDED)

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    D0_HPD_LOW();
    CTimerDelayXms(ms);
    D0_HPD_HIGH();
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    D1_HPD_LOW();
    CTimerDelayXms(ms);
    D1_HPD_HIGH();
#endif

#else
    // HPD
    CScalerPageSelect(_PAGEE);
    CScalerSetByte(_PE_PIN_SHARE_CTRL01_D5, 0x1c);
    CScalerSetByte(_PE_CEC_CR0_EB, 0x90);

    // 1ms: AMD or 10ms: Quanmdata/unigraf
    CTimerDelayXms(ms);
    CScalerSetByte(_PE_CEC_CR0_EB, 0xb0);
#endif

}

//--------------------------------------------------
// Description  : Display Port PHY Stable Check (1.ANSI8B/10B, 2.CDR lock, 3.PHY Stable)
// Input Value  : None
// Output Value : TRUE--> Display PHY Stable, False--> Display PHY Fail.
//--------------------------------------------------
bit CDpIsDisplayPortPhyStable(void)
{
    /*
    if(ucCurrState != _ACTIVE_STATE)
    */
    if((ucCurrState != _ACTIVE_STATE) && (ucCurrState != _CHECK_STATE))
    {
        // for Link Layer CTS
        CDpMacReset();
    }

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);

    // use current DPCD setting in case of no LT
    CScalerRead(_PC_DPCD_DATA_PORT_L_C4, 1, pData, _NON_AUTOINC);

    if((pData[0] & 0x1F) == 0x01)
    {
        CScalerSetByte(_PC_DP_LANE_VALID_A5, 0xFF);
        CScalerSetByte(_PC_DP_LANE_LOCK_A6, 0xFF);
        CScalerRead(_PC_DP_LANE_VALID_A5, 2, pData, _AUTOINC);

        if(((pData[0] & 0x88) == 0) && ((pData[1] & 0x80) == 0))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else if((pData[0] & 0x1F) == 0x02)
    {
        CScalerSetByte(_PC_DP_LANE_VALID_A5, 0xFF);
        CScalerSetByte(_PC_DP_LANE_LOCK_A6, 0xFF);
        CScalerRead(_PC_DP_LANE_VALID_A5, 2, pData, _AUTOINC);

        if(((pData[0] & 0xCC) == 0) && ((pData[1] & 0xC0) == 0))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else if((pData[0] & 0x1F) == 0x04)
    {
        CScalerSetByte(_PC_DP_LANE_VALID_A5, 0xFF);
        CScalerSetByte(_PC_DP_LANE_LOCK_A6, 0xFF);
        CScalerRead(_PC_DP_LANE_VALID_A5, 2, pData, _AUTOINC);

        if(((pData[0] & 0xFF) == 0) && ((pData[1] & 0xF0) == 0))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Display Port Video  Stream Check (VBID Bit[3])
// Input Value  : None
// Output Value : TRUE--> Video Stream, False--> Idle Pattern.
//--------------------------------------------------
bit CDpIsDisplayPortVideoStream(void)
{
    // MSA pop up
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x00, 0xF8);

    /*
    if(ucCurrState == _SEARCH_STATE)
    */
    if(ucCurrState != _NOSUPPORT_STATE)
    {
        CTimerDelayXms(30); //Delay for MSA Pop Up(1 frame)
    }

    CScalerPageSelect(_PAGEC);
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x01, 1, pData, _NON_AUTOINC);
    if((pData[0] & 0x08) == 0x08)
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Get DP Main Stream Attributes
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpGetMsaValue(void)
{
    CScalerPageSelect(_PAGEC);

    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x16, 3, pData, _NON_AUTOINC);
    g_ulDpMvidValue = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));

    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x08, 2, pData, _NON_AUTOINC);
    g_usDpHactive = ((DWORD)pData[0] << 8) | ((DWORD)pData[1]);

    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x12, 2, pData, _NON_AUTOINC);
    g_usDpVactive = ((DWORD)pData[0] << 8) | ((DWORD)pData[1]);

    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x02, 1, &g_ucDpMsaMisc, _NON_AUTOINC);
}

//--------------------------------------------------
// Description  : Get DP Main Stream VsyncFrontPorch Value
// Input Value  : None
// Output Value : VsyncFrontPorch=pData[2:0]
//--------------------------------------------------
#if(_FRONT_PORCH_REGENERATOR == _ON)
DWORD CDpGetVsyncFrontPorch(void)
{
    DWORD xdata ulMvidValueData = 0;
    DWORD xdata ulNvidValueData = 0;
    DWORD xdata ulFrontPorchValueData = 0;
    WORD  xdata usHtotalValueData = 0;
    WORD  xdata usVtotalValueData = 0;
    WORD  xdata usVstartValueData = 0;
    WORD  xdata usVheightValueData = 0;

    CScalerPageSelect(_PAGEC);

    /*
    CTimerDelayXms(2);
    */

    // Get Mvid and Nvid value
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x16, 3, pData, _NON_AUTOINC);
    ulMvidValueData = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x19, 3, pData, _NON_AUTOINC);
    ulNvidValueData = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));

    // Get Htotal
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x04, 2, pData, _NON_AUTOINC);
    usHtotalValueData = (((WORD)pData[0] << 8) | ((WORD)pData[1] << 0));

    // Get Vtotal
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x0C, 2, pData, _NON_AUTOINC);
    usVtotalValueData = (((WORD)pData[0] << 8) | ((WORD)pData[1] << 0));

    // Get Vstart
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x10, 2, pData, _NON_AUTOINC);
    usVstartValueData = (((WORD)pData[0] << 8) | ((WORD)pData[1] << 0));

    // Get Vheight
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x12, 2, pData, _NON_AUTOINC);
    usVheightValueData = (((WORD)pData[0] << 8) | ((WORD)pData[1] << 0));

    // Calculate ulFrontPorchValue
    ulFrontPorchValueData = ((((DWORD)(usVtotalValueData - usVheightValueData - usVstartValueData)) * (ulNvidValueData * 256 / ulMvidValueData)) * ((DWORD)usHtotalValueData) / 256);

    pData[0] = (ulFrontPorchValueData >> 24);

    if(pData[0] == 0)
    {
        return(ulFrontPorchValueData);
    }
    else
    {
        return(0x000002);
    }
}
#endif //End of #if(_FRONT_PORCH_REGENERATOR == _ON)

//--------------------------------------------------
// Description  : Get DP Main Stream Attributes
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#if(_FRONT_PORCH_REGENERATOR == _ON)
DWORD CDpGetHsyncFrontPorch(void)
{
    DWORD  xdata ulMvidValueData = 0;
    DWORD  xdata ulNvidValueData = 0;
    DWORD  xdata ulFrontPorchValueData = 0;
    WORD   xdata usHtotalValueData = 0;
    WORD   xdata usHstartValueData = 0;
    WORD   xdata usHwidthValueData = 0;
    WORD   xdata usOffsetLine = 0;

    CScalerPageSelect(_PAGEC);

    /*
    CTimerDelayXms(2);
    */

    // Get Mvid and Nvid value
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x16, 3, pData, _NON_AUTOINC);
    ulMvidValueData = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x19, 3, pData, _NON_AUTOINC);
    ulNvidValueData = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));

    // Get Htotal
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x04, 2, pData, _NON_AUTOINC);
    usHtotalValueData = (((WORD)pData[0] << 8) | ((WORD)pData[1] << 0));

    // Get Hstart
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x6, 2, pData, _NON_AUTOINC);
    usHstartValueData = (((WORD)pData[0] << 8) | ((WORD)pData[1] << 0));

    // Get Hwidth
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x8, 2, pData, _NON_AUTOINC);
    usHwidthValueData = (((WORD)pData[0] << 8) | ((WORD)pData[1] << 0));

    CScalerPageSelect(_PAGEC);
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x02, 1, pData, _NON_AUTOINC);
    if((pData[0] & 0xE0) == 0)
    {
        pData[1] = 6;
    }
    else if((pData[0] & 0xE0) == 0x20)
    {
        pData[1] = 8;
    }
    else if((pData[0] & 0xE0) == 0x40)
    {
        pData[1] = 10;
    }
    else if((pData[0] & 0xE0) == 0x60)
    {
        pData[1] = 12;
    }
    else
    {
        pData[1] = 16;
    }

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);

    // use current DPCD setting in case of no LT
    CScalerRead(_PC_DPCD_DATA_PORT_L_C4, 1, &pData[2], _NON_AUTOINC);

    // 576*(8*2)*Lane_Count / (3_Channel*Color_deepth)
    usOffsetLine = (1536 * (WORD)(pData[2] & 0x1F) / (WORD)pData[1]);
    ulFrontPorchValueData = (((DWORD)(usHtotalValueData - usHwidthValueData - usHstartValueData + usOffsetLine)) * ulNvidValueData / ulMvidValueData);

    pData[0] = (ulFrontPorchValueData >> 24);

    if(pData[0] == 0)
    {
        return(ulFrontPorchValueData);
    }
    else
    {
        return(0x000002);
    }
}
#endif //End of #if(_FRONT_PORCH_REGENERATOR == _ON)

//--------------------------------------------------
// Description  : Display Format Initial of Display Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpDisplayFormatInitial(void)
{
#if(_FRONT_PORCH_REGENERATOR == _ON)
    DWORD xdata ulVsyncFrontPorchValue = 0;
    DWORD xdata ulHsyncFrontPorchValue = 0;
    DWORD xdata ulFrontPorchValue = 0;
#endif // End of #if(_Front_Porch_Regenerator == _ON)

    CScalerPageSelect(_PAGEC);
// start format @ frame-sync mode
#if(_DP_DISPLAY_FORMAT_SEL == _FRAME_SYNC_MODE)
    //bit7=start bit. 1-->start to generate
    //bit6=double buffer. 1-->double buffer active
    //bit5=HS/VS generation. 1-->framep-sync, 0-->full last line
    //bit4=DE generation. 1-->digital mode, 0: normal mode
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x35, 0xA0);
#endif // End of #if(_DP_DISPLAY_FORMAT_SEL == _FRAME_SYNC_MODE)

// start format @ full-last mode
#if(_DP_DISPLAY_FORMAT_SEL == _FULL_LAST_LINE)
    //bit7=start bit. 1-->start to generate
    //bit6=double buffer. 1-->double buffer active
    //bit5=HS/VS generation. 1-->framep-sync, 0-->full last line
    //bit4=DE generation. 1-->digital mode, 0: normal mode
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x35, 0x80);
#endif // End of #if(_DP_DISPLAY_FORMAT_SEL == _FULL_LAST_LINE)

    // The delay count of link clk for "BS or BE to Virtual VS" in even field
    pData[0] = 0x00; //H
    pData[1] = 0x00; //M //640pixels*2lines*24bits div 10 = 0xC00
    pData[2] = 0x02; //L

#if(_DP_INTERLACE == _ON)
    //The delay count of link clk for "BS or BE to Virtual VS" in odd field
    pData[3] = 0x00; //H
    pData[4] = 0x00; //M //640pixels*2lines*24bits div 10 = 0xC00
    pData[5] = 0x02; //L
#endif

#if(_FRONT_PORCH_REGENERATOR == _ON)
    ulVsyncFrontPorchValue = CDpGetVsyncFrontPorch();
    ulHsyncFrontPorchValue = CDpGetHsyncFrontPorch();
    ulFrontPorchValue = ( ulVsyncFrontPorchValue + ulHsyncFrontPorchValue ) * 100 / 100;

#if(_DP_INTERLACE == _ON)
    // odd field BS to VS delay
    pData[3] = (ulFrontPorchValue >> 16);
    pData[4] = (ulFrontPorchValue >> 8);
    pData[5] = (ulFrontPorchValue >> 0);

    CScalerPageSelect(_PAGEC);
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x01, 1, pData, _NON_AUTOINC);
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x03, 1, &pData[1], _NON_AUTOINC);
    if(((pData[0]&0x04) == 0x04) && ((pData[1] & 0x01) == 0x00))
    {
        DWORD xdata ulNvidValueData = 0;
        DWORD xdata ulMvidValueData = 0;
        WORD  xdata usHtotalValueData = 0;

        //get Mvid and Nvid value
        CScalerPageSelect(_PAGEC);
        CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x16, 3, pData, _NON_AUTOINC);
        ulMvidValueData = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));

        CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x19, 3, pData, _NON_AUTOINC);
        ulNvidValueData = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));

        //get Htotal
        CScalerPageSelect(_PAGEC);
        CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x04, 2, pData, _NON_AUTOINC);
        usHtotalValueData = (((WORD)pData[0] << 8) | ((WORD)pData[1] << 0));

        ulFrontPorchValue += (ulNvidValueData * 256 / ulMvidValueData) * ((DWORD)usHtotalValueData) / 256;
    }
#endif  // End of #if(_DP_INTERLACE == _ON)

    // even field BS to VS delay
    pData[0] = (ulFrontPorchValue >> 16);
    pData[1] = (ulFrontPorchValue >> 8);
    pData[2] = (ulFrontPorchValue >> 0);

    // LSB delay value
    CScalerPageSelect(_PAGEC);
    CScalerWrite(_PC_AUX_RESERVE0_C5, 3, pData, _AUTOINC);
#endif // End of #if(_Front_Porch_Regenerator == _ON)

    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x36, pData[0]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x37, pData[1]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x38, pData[2]);

#if(_DP_INTERLACE == _ON)
    // set BS to VS delay of odd field
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x39, pData[3]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3A, pData[4]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3B, pData[5]);
#else
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x39, pData[0]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3A, pData[1]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3B, pData[2]);

#endif  // End of #if(_DP_INTERLACE == _ON)

    //The delay count of link clk for "BS or BE to DE" in digital mode
    pData[1] = 0x00;
    pData[0] = 0x00;
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3C, pData[1]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3D, pData[0]);

    //Set Htotal
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x04, 2, pData, _NON_AUTOINC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3E, pData[0]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3F, pData[1]);

    //Set Hstart
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x06, 2, pData, _NON_AUTOINC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x40, pData[0]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x41, pData[1]);

    //Set Hwidth
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x08, 2, pData, _NON_AUTOINC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x42, pData[0]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x43, pData[1]);

    //Set HSW
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x0A, 2, pData, _NON_AUTOINC);
    pData[0] &= 0x7F;
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x44, pData[0]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x45, pData[1]);

    //Set Vtotal
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x0C, 2, pData, _NON_AUTOINC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x46, pData[0]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x47, pData[1]);

    //Set Vstart
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x10, 2, pData, _NON_AUTOINC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x48, pData[0]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x49, pData[1]);

    //Set Vheight
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x12, 2, pData, _NON_AUTOINC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x4A, pData[0]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x4B, pData[1]);

    //Set VSP and VSW
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x14, 2, pData, _NON_AUTOINC);
    pData[0] &= 0x7F;
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x4C, pData[0]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x4D, pData[1]);

#if(_DP_DISPLAY_FORMAT_SEL == _FRAME_SYNC_MODE)
    //bit7=start bit. 1-->start to generate
    //bit6=double buffer. 1-->double buffer active
    //bit5=HS/VS generation. 1-->framep-sync, 0-->full last line
    //bit4=DE generation. 1-->digital mode, 0: normal mode
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x35, 0xE0);
#endif // End of #if(_DP_DISPLAY_FORMAT_SEL == _FRAME_SYNC_MODE)

#if(_DP_DISPLAY_FORMAT_SEL == _FULL_LAST_LINE)
    //bit7=start bit. 1-->start to generate
    //bit6=double buffer. 1-->double buffer active
    //bit5=HS/VS generation. 1-->framep-sync, 0-->full last line
    //bit4=DE generation. 1-->digital mode, 0: normal mode
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x35, 0xC0);
#endif // End of #if(_DP_DISPLAY_FORMAT_SEL == _FULL_LAST_LINE)
}

//--------------------------------------------------
// Description  : Display port vedio fifo Auto-Test Function
// Input Value  : None
// Output Value : True: BIST PASS, False: BIST Fail
//--------------------------------------------------
bit CDpIsFifoUnderOverFlow(void)
{
    CScalerPageSelect(_PAGEC);

    /*
    if(ucCurrState != _ACTIVE_STATE)
    {
        CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x30, 0xff);
        CTimerDelayXms(60); // 30:MN_Tracking , 70:VS_Tracking
    }
    */

    if((ucCurrState != _ACTIVE_STATE) && (ucCurrState != _CHECK_STATE))
    {
        CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x30, 0xff);
        CTimerDelayXms(60); // Wait for 60ms to Check Fifo Status
    }

    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x30, 1, pData, _NON_AUTOINC);

    if( (pData[0] & 0x80) == 0x80)
    {
        return _TRUE;
    }

    else if( (pData[0] & 0x40) == 0x40)
    {
        return _TRUE;
    }

    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Display format is changed
// Input Value  : None
// Output Value : True: Format Change, False: Format no change
//--------------------------------------------------
bit CDpDisplayFormatChange(void)
{
    BYTE xdata ucMsa[1] = {0x00};

    CScalerPageSelect(_PAGEC);
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x02, 1, pData, _NON_AUTOINC);
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x31, 1, ucMsa, _NON_AUTOINC);
    pData[0] = ((0x0 << 5) | (((pData[0] & 0x06) >> 1) << 3) | ((pData[0] >> 5) << 0));

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DP_RESERVE4_BE, pData[0]);
    CScalerSetByte(_PC_DP_RESERVE5_BF, ucMsa[0]);

    if(pData[0] == ucMsa[0])
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : DP MAC INITIALTION
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpMacInitial(void)
{
    BYTE xdata ucBuf = 0x00;

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);

    // use current DPCD setting in case of no LT
    CScalerRead(_PC_DPCD_DATA_PORT_L_C4, 1, &pData[0], _NON_AUTOINC);
    if((pData[0] & 0x80) == 0x80)
    {
        ucBuf |= _BIT2;
    }

    if((pData[0] & 0x1F) == 0x01)
    {
        ucBuf |= _BIT3;
    }
    else if((pData[0] & 0x1F) == 0x02)
    {
        ucBuf |= _BIT4;
    }
    else if((pData[0] & 0x1F) == 0x04)
    {
        ucBuf |= (_BIT3 | _BIT4);
    }

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DP_CTL_A1, ucBuf);

    // DP Lane Swap Setting
    CScalerSetByte(_PC_LANE_SWAP_A4, 0x1B);

    // DP RGB and CLK Output Enable
    CScalerSetByte(_PC_DP_OUTPUT_CTL_A2, 0xF0);

    // DP 4-layer De-Skew select
    CScalerSetByte(_PC_MIN_DE_SKEW_A8, 0x1C);

    // 0x00:disable error correction, 0xF4:enable all error correction
    CScalerSetByte(_PC_MN_ERRC_A9, 0x00);

    // Read De-scrambling status
    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x02);
    CScalerRead(_PC_DPCD_DATA_PORT_L_C4, 1, &pData[0], _NON_AUTOINC);

    if((pData[0] & 0x20) == 0x20)
    {
        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
        CScalerSetByteInt(_PB_DIG02_E2, 0x80);
    }
    else
    {
        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
        CScalerSetByteInt(_PB_DIG02_E2, 0x00);
    }
}

//--------------------------------------------------
// Description  : Display port FIFO Adjustment
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpAdjustVsyncDelayCount(void)
{
    BYTE  xdata ucBuf = 0;
    DWORD xdata ulCurrentBStoVSDelayValue = 0;

#if(_DP_INTERLACE == _ON)
    DWORD xdata ulCurrentBStoVSDelayValueOdd = 0;
    DWORD xdata ulBStoVSDelayValueEven = 0;
    DWORD xdata ulBStoVSDelayValueOdd = 0;

#endif

    DWORD xdata ulHwidth = 0;
    DWORD xdata ulDelta_BStoVSDelayValue = 0;
    DWORD xdata ulMvidValueData = 0;
    DWORD xdata ulNvidValueData = 0;
    WORD  xdata usHtotalValueData = 0;
    BYTE  xdata ucFifoErrorCnt = 0;
    BYTE  xdata ucPixel = 0;

    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x5E, 0x2A);
    CTimerDelayXms(30);
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x5E, 1, pData, _NON_AUTOINC);

    while((pData[0] & 0x20) == 0x20)
    {
        CScalerPageSelect(_PAGEC);
        CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x5E, 0x2A);
        CTimerDelayXms(30);
        CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x5E, 1, pData, _NON_AUTOINC);

        if(ucBuf <= 30)
        {
            ucBuf++;
        }
        else
        {
            break;
        }
    }

    CScalerPageSelect(_PAGEC);
    // for progressive and interlace even field
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x36, 3, pData, _NON_AUTOINC);
    ulCurrentBStoVSDelayValue = ( ((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));

#if(_DP_INTERLACE == _ON)
    // for interlace odd field
    CScalerPageSelect(_PAGEC);
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x39, 3, pData, _NON_AUTOINC);
    ulCurrentBStoVSDelayValueOdd = ( ((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));

    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x01, 1, pData, _NON_AUTOINC);
    if((pData[0]&0x04) == 0x04)
    {


        CScalerPageSelect(_PAGEC);
        CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x30, 0xFF);
        CTimerDelayXms(30);
        CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x30, 1, pData, _NON_AUTOINC);

        //Fifo Overflow or Underflow
        if(((pData[0] & 0x80) == 0x80) || ((pData[0] & 0x40) == 0x40))
        {


            //exchange between the even and the odd
            ulBStoVSDelayValueEven = ulCurrentBStoVSDelayValueOdd;
            ulBStoVSDelayValueOdd = ulCurrentBStoVSDelayValue;

            pData[0] = (ulBStoVSDelayValueEven >> 16);
            pData[1] = (ulBStoVSDelayValueEven >> 8);
            pData[2] = (ulBStoVSDelayValueEven >> 0);

            //even field
            CScalerPageSelect(_PAGEC);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x36, pData[0]);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x37, pData[1]);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x38, pData[2]);

            pData[3] = (ulBStoVSDelayValueOdd >> 16);
            pData[4] = (ulBStoVSDelayValueOdd >> 8);
            pData[5] = (ulBStoVSDelayValueOdd >> 0);

            //odd field
            CScalerPageSelect(_PAGEC);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x39, pData[3]);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3A, pData[4]);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3B, pData[5]);

            // Display format reset
            CScalerPageSelect(_PAGEC);
            CScalerSetBit(_PC_DP_RESERVE2_BC, ~_BIT7, _BIT7);
            CScalerSetBit(_PC_DP_RESERVE2_BC, ~_BIT7, 0x00);

#if(_DP_DISPLAY_FORMAT_SEL == _FRAME_SYNC_MODE)
            CScalerPageSelect(_PAGEC);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x35, 0x00);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x35, 0xE0);
#endif // End of #if(_DP_DISPLAY_FORMAT_SEL == _FRAME_SYNC_MODE)

#if(_DP_DISPLAY_FORMAT_SEL == _FULL_LAST_LINE)
            CScalerPageSelect(_PAGEC);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x35, 0x00);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x35, 0xC0);
#endif // End of #if(_DP_DISPLAY_FORMAT_SEL == _FULL_LAST_LINE)

            CTimerDelayXms(30); // Wait for 1 frame

            CScalerPageSelect(_PAGEC);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x30, 0xFF);
            CTimerDelayXms(30);
            CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x30, 1, pData, _NON_AUTOINC);

            if(((pData[0] & 0x80) == 0x80) || ((pData[0] & 0x40) == 0x40))
            {


                //do nothing
            }
            else
            {


                return;
            }
        }
        else
        {


            return;
        }
    }
#endif

    //get Htotal
    CScalerPageSelect(_PAGEC);
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x04, 2, pData, _NON_AUTOINC);
    usHtotalValueData = (((WORD)pData[0] << 8) | ((WORD)pData[1] << 0));

    //get Mvid and Nvid value
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x16, 3, pData, _NON_AUTOINC);
    ulMvidValueData = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x19, 3, pData, _NON_AUTOINC);
    ulNvidValueData = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));

    //calculate adjust amount of BStoVSDelayValue (adjust 1-Line : for nVidia case)
    ulDelta_BStoVSDelayValue = (ulNvidValueData * 256 / ulMvidValueData) * ((DWORD)usHtotalValueData) / 256;

    while(ucFifoErrorCnt <= _BOUNDARY_CHECK_NUM)
    {
        CScalerPageSelect(_PAGEC);
        CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x30, 0xFF);
        CTimerDelayXms(30);
        CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x30, 1, pData, _NON_AUTOINC);

        //earily overflow  --> backward trace
        if ((pData[0] & 0x80) == 0x80)
        {


            ucFifoErrorCnt++;

            ulCurrentBStoVSDelayValue -= ulDelta_BStoVSDelayValue;

            pData[0] = (ulCurrentBStoVSDelayValue >> 16);
            pData[1] = (ulCurrentBStoVSDelayValue >> 8);
            pData[2] = (ulCurrentBStoVSDelayValue >> 0);

            //The delay count of link clk for "BS or BE to Virtual VS" in even field
            CScalerPageSelect(_PAGEC);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x36, pData[0]);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x37, pData[1]);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x38, pData[2]);

#if(_DP_INTERLACE == _ON)
            ulCurrentBStoVSDelayValueOdd -= ulDelta_BStoVSDelayValue;

            pData[3] = (ulCurrentBStoVSDelayValueOdd >> 16);
            pData[4] = (ulCurrentBStoVSDelayValueOdd >> 8);
            pData[5] = (ulCurrentBStoVSDelayValueOdd >> 0);

            // The delay count of link clk for "BS or BE to Virtual VS" in odd field
            CScalerPageSelect(_PAGEC);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x39, pData[3]);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3A, pData[4]);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3B, pData[5]);
#else
            // The delay count of link clk for "BS or BE to Virtual VS" in odd field
            CScalerPageSelect(_PAGEC);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x39, pData[0]);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3A, pData[1]);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x3B, pData[2]);
#endif
        }
        // earily underflow and non-overflow/non-underflow
        else if(((pData[0] & 0x40) == 0x40) && (ucCurrState == _NOSUPPORT_STATE))
        {


            ucFifoErrorCnt++;
            ucPixel++;

            //Set Hwidth
            CScalerPageSelect(_PAGEC);
            CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x08, 2, pData, _NON_AUTOINC);

            ulHwidth = ( (pData[0] << 8) | (pData[1]) ) - ucPixel;
            pData[0] = (ulHwidth >> 8);
            pData[1] = (ulHwidth >> 0);

            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x42, pData[0]);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x43, pData[1]);
        }
        else
        {
            break;
        }

        // Display format reset
        CScalerPageSelect(_PAGEC);
        CScalerSetBit(_PC_DP_RESERVE2_BC, ~_BIT7, _BIT7);
        CScalerSetBit(_PC_DP_RESERVE2_BC, ~_BIT7, 0x00);

#if(_DP_DISPLAY_FORMAT_SEL == _FRAME_SYNC_MODE)
        CScalerPageSelect(_PAGEC);
        CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x35, 0x00);
        CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x35, 0xE0);
#endif // End of #if(_DP_DISPLAY_FORMAT_SEL == _FRAME_SYNC_MODE)

#if(_DP_DISPLAY_FORMAT_SEL == _FULL_LAST_LINE)
        CScalerPageSelect(_PAGEC);
        CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x35, 0x00);
        CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x35, 0xC0);
#endif // End of #if(_DP_DISPLAY_FORMAT_SEL == _FULL_LAST_LINE)

        /*
        // 20:MN_Tracking , 60:VS_Tracking
        CTimerDelayXms(60);
        */
        CTimerDelayXms(30); //Wait for 1 frame
    }
}

//--------------------------------------------------
// Description  : Video Format Set
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpVideoSetting(void)
{
    CScalerPageSelect(_PAGEC);
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x02, 1, pData, _NON_AUTOINC);

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

// If Display Port use _YPBPR_TABLE_SET_SCALER, this mark need to roll back.
/*
#if(_YPBPR_TABLE_SET_SCALER == _ON)
*/
#if(_YPBPR_SUPPORT == _ON)
    if(((pData[0] & 0x06) == 4 ) || ( (pData[0] & 0x06) == 2))
    {
        CScalerCodeW(tYPBPR_TABLE_SET_SCALER);
    }
    // Clear YCbCr table for RGB mode
    else
    {
        CScalerPageSelect(_PAGE7);
        CScalerSetByte(_P7_YUV2RGB_CTRL_BF, 0x02);
        CScalerSetByte(_P7_YUV2RGB_ACCESS_C0, 0x00);
        CScalerSetByte(_P7_YUV2RGB_CTRL_BF, 0x00);
    }
#endif

#endif // End of #if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

    CScalerPageSelect(_PAGEC);
    pData[0] = (((0x0) << 5) | (((pData[0] & 0x06) >> 1) << 3) | (((pData[0]) >> 5) << 0));
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x31, pData[0]);
}

//--------------------------------------------------
// Description  : Stream Clock Regenerator1 by LinkClk & M/N value
// Input Value  : None
// Output Value : True--> DPLL Regenerator StreamClk. False--> DPLL doesn't Regenerator StreamClk by M/N code.
//--------------------------------------------------
#if(_DP_STREAM_CLOCK_SEL == _BY_MN_VALUE)
bit CDpStreamClkRegeneratByMN(void)
{
    DWORD  xdata ulMvidValue = 0;
    DWORD  xdata ulNvidValue = 0;
    DWORD  xdata ulLinkClkValue = 0;
    DWORD  xdata ulStreamClkValue = 0;
    SDWORD xdata lOffsetValue = 0;

#if((_TRACKING_MODE == _MNTRACKING) || (_TRACKING_MODE == _VS_AND_MN_TRACKING) || (_TRACKING_MODE == _VSTRACKING))
    DWORD   ulIcodeValue = 0;           //for M/N tracking & V/S tracking
#endif // End of #if( (_TRACKING_MODE == _MNTRACKING) || (_TRACKING_MODE == _VS_AND_MN_TRACKING) || (_TRACKING_MODE == _VSTRACKING))

#if((_TRACKING_MODE == _VSTRACKING) || (_TRACKING_MODE == _VS_AND_MN_TRACKING))
    DWORD  xdata ulHtotalValue = 0;
    DWORD  xdata ulVtotalValue = 0; // for V/S tracking
#endif // End of #if( (_TRACKING_MODE == _VSTRACKING) || (_TRACKING_MODE == _VS_AND_MN_TRACKING) )

    DWORD  xdata ulpllm = 0;
    DWORD  xdata ulXtal_clk = 0;
    BYTE   xdata ucpllo = 0;
    BYTE   xdata ucdivs = 0;
    BYTE   xdata ucdiv2 = 0;
    BYTE   xdata ucplln = 0;
    BYTE   xdata ucBuf = 0;
    BYTE   xdata ucdiv_pllo = 0;
    BYTE   xdata ucdiv_divs = 0;


#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    BYTE dpllvcomd;
#endif

    ulXtal_clk = _RTD_XTAL;

    // Get Mvid and Nvid value
    CScalerPageSelect(_PAGEC);
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x16, 3, pData, _NON_AUTOINC);
    ulMvidValue = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x19, 3, pData, _NON_AUTOINC);
    ulNvidValue = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0));

    if((ulMvidValue == 0) || (ulNvidValue == 0))
    {
        return _FALSE;
    }

    // Get link clk rate
    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerGetDataPortByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x00, 1, pData, _NON_AUTOINC);

    if(pData[0] == 0x0A)
    {
        ulLinkClkValue = 270000000;
    }
    else
    {
        ulLinkClkValue = 162000000;
    }

     pData[0] = (ulLinkClkValue >> 24);
     pData[1] = (ulLinkClkValue >> 16);
     pData[2] = (ulLinkClkValue >> 8);
     pData[3] = (ulLinkClkValue >> 0);

    // Calcuate streamclk
    (DWORD)ulStreamClkValue = ((DWORD)ulMvidValue * (ulLinkClkValue * 8 / ulNvidValue) / 8);

#if(_DP_INTERLACE == _ON)
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x01, 1, pData, _NON_AUTOINC);
    if((pData[0] & 0x04) == 0x04)
    {
        ucdiv2 = 1;
        ulStreamClkValue = ulStreamClkValue * 2;
    }
    else
    {
        ucdiv2 = 0;
    }

#else
    ucdiv2 = 0;
#endif

    // Get DPLL parameter
    // if "400Mhz > ulStreamClkValue > 270Mhz"
    if((400000000 > ulStreamClkValue) && (ulStreamClkValue >= 270000000))
    {
        ucpllo = 0;
        ucdivs = 0;
        ucplln = 5;

        ucdiv_divs = 1;
        ucdiv_pllo = 1;


#if(_DP_DPLL_INPUT_SEL == _LINKCLK)
        ulpllm = (((((ulStreamClkValue * ucdiv_divs * ucdiv_pllo) / 1000 * ucplln * 16) << 1) / (ulLinkClkValue / 1000 * 17)) + 1) >> 1;
#endif

#if(_DP_DPLL_INPUT_SEL == _XTAL)
        ulpllm = (((((ulStreamClkValue * ucdiv_divs * ucdiv_pllo) / 1000 * ucplln * 16) << 1) / (ulXtal_clk * 17)) + 1) >> 1;
#endif

        while( ulpllm > 257 )
        {
            ucplln = ucplln - 1;

#if(_DP_DPLL_INPUT_SEL == _LINKCLK)
            ulpllm = (((((ulStreamClkValue * ucdiv_divs * ucdiv_pllo) / 1000 * ucplln * 16) << 1) / (ulLinkClkValue / 1000 * 17)) + 1) >> 1;
#endif

#if(_DP_DPLL_INPUT_SEL == _XTAL)
            ulpllm = (((((ulStreamClkValue * ucdiv_divs * ucdiv_pllo) / 1000 * ucplln * 16) << 1) / (ulXtal_clk * 17)) + 1) >> 1;
#endif

            if(ucplln < 2)
            {
                return _FALSE;
            }
        }
    }
    // if "270MHz > ulStreamClkValue > 8.4375Mhz"
    else if((ulStreamClkValue < 270000000) && (ulStreamClkValue >= 8437500))
    {
        ucpllo = 1;

        if((ulStreamClkValue < 270000000) && (ulStreamClkValue >= 135000000))
        {
            ucdivs = 0;
        }
        else if((ulStreamClkValue < 135000000) && (ulStreamClkValue >= 67500000))
        {
            ucdivs = 1;
        }
        else if((ulStreamClkValue < 67500000) && (ulStreamClkValue >= 33750000))
        {
            ucdivs = 2;
        }
        else if((ulStreamClkValue < 33750000) && (ulStreamClkValue >= 16875000))
        {
            ucdivs = 4;
        }
        else
        {
            ucdivs = 8;
        }

        // because set 17 get minimum error for recovery stream clk , close to fact clk.
        ucplln = 5;

        ucdiv_divs = 2 * ucdivs;
        ucdiv_pllo = ucpllo;

        for(ucBuf = 0; ucBuf < ucpllo; ucBuf++)
        {
            ucdiv_pllo = 2 * ucdiv_pllo;
        }

        if(ucdiv_divs == 0)
        {
            ucdiv_divs = 1;
        }

        if(ucdiv_pllo == 0)
        {
            ucdiv_pllo = 1;
        }

#if(_DP_DPLL_INPUT_SEL == _LINKCLK)
        ulpllm = ((((((ulStreamClkValue * ucdiv_divs * ucdiv_pllo) / 1000) * ucplln * 16) << 1) / (ulLinkClkValue / 1000 * 17)) + 1) >> 1;
#endif

#if(_DP_DPLL_INPUT_SEL == _XTAL)
        ulpllm = ((((((ulStreamClkValue * ucdiv_divs * ucdiv_pllo) / 1000) * ucplln * 16) << 1) / (ulXtal_clk * 17)) + 1) >> 1;
#endif

        while( ulpllm > 257 )
        {
            ucplln = ucplln - 1;

#if(_DP_DPLL_INPUT_SEL == _LINKCLK)
            ulpllm = ((((((ulStreamClkValue * ucdiv_divs * ucdiv_pllo) / 1000) * ucplln * 16) << 1) / (ulLinkClkValue / 1000 * 17)) + 1) >> 1;
#endif

#if(_DP_DPLL_INPUT_SEL == _XTAL)
            ulpllm = ((((((ulStreamClkValue * ucdiv_divs * ucdiv_pllo) / 1000) * ucplln * 16) << 1) / (ulXtal_clk * 17)) + 1) >> 1;
#endif

            if(ucplln < 2)
            {
              return _FALSE;
            }
        }
    }
    else
    {
        return _FALSE;
    }


#if(_DP_DPLL_INPUT_SEL == _LINKCLK)
    if( ulLinkClkValue == 162000000)
    {
        lOffsetValue = ( (ulStreamClkValue * ucdiv_pllo * ucdiv_divs) - (ulLinkClkValue / ucplln) * ulpllm ) * 100 / (7725 * ulpllm / ucplln);   // 162MHz / 2^21 = 77.247 (ucLink_clock_limit = 340MHz)
    }
    else
    {
        lOffsetValue = ( (ulStreamClkValue * ucdiv_pllo * ucdiv_divs) - (ulLinkClkValue / ucplln) * ulpllm ) * 100 / (12875 * ulpllm / ucplln);  // 270MHz / 2^21 = 128.746
    }
#endif  // End of #if(_DP_DPLL_INPUT_SEL == _LINKCLK)


#if(_DP_DPLL_INPUT_SEL == _XTAL)
    lOffsetValue = ( (ulStreamClkValue * ucdiv_pllo * ucdiv_divs) -  ( (ulXtal_clk * 1000 / ucplln) * ulpllm )  ) / ( ((ulXtal_clk * 1000 / ucplln) * ulpllm) / 2097152);  // 2^21 = 2097152
#endif


#if(_SCALER_TYPE == _RTD2472D)
    // Original Formula : M_Code/Ich = 36.67 must be constant
    // Ich = M_Code * 100 / 3667
    // I   = 2.5u + D0[0]*2.5u + D0[1]*5u + D0[2]*10u + D0[3]*20u + D0[4]*30u (A)
    // Ich = I * (bit[5]+1) / 2
    // Ich = 33.75¡B31.25¡B28.75¡B26.25¡B23.75¡B21.25¡B18.75¡B16.25¡B13.75¡B11.25¡B8.75¡B6.25¡B3.75¡B1.25 , bit[5]=0
    // Otherwise bit[5]=1

    pData[5] = ((DWORD)ulpllm * 4 * 100 / 3667);

    pData[6] = 0x00;

    if(((pData[5] & 0x01) == 0x00) || (pData[5] >= 140))
    {
        pData[6] |= 0x20;
    }
    else
    {
        pData[5] = pData[5] << 1;
    }

    if(pData[5] >= 10)
    {
        pData[5] -= 10;
    }

    if(pData[5] >= 120)
    {
        pData[5] -= 120;
        pData[6] |= 0x10;
    }

    if(pData[5] >= 80)
    {
        pData[5] -= 80;
        pData[6] |= 0x08;
    }

    if(pData[5] >= 40)
    {
        pData[5] -= 40;
        pData[6] |= 0x04;
    }

    if(pData[5] >= 20)
    {
        pData[5] -= 20;
        pData[6] |= 0x02;
    }

    if(pData[5] >= 10)
    {
        pData[5] -= 10;
        pData[6] |= 0x01;
    }

    pData[6] |= 0x80;
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x71, pData[6]);

    // DPLL Startup
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x72, 0x0F);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x73, 0x02);

    ucBuf = 0x80;
    ucBuf = (ucBuf | ucpllo);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x70, ucBuf);

    ucBuf = 0x0;
    ucBuf = (ucBuf | ucpllo);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x70, ucBuf);

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

    dpllvcomd = 2;

    // Original Formula : M_Code/Ich = 10.67 must be constant
    // Ich = M_Code * 100 / 1067
    // I   = 2.5u + D0[0]*2.5u + D0[1]*5u + D0[2]*10u (A)
    // Ich = 20¡B17.5¡B15¡B12.5¡B10¡B7.5¡B5¡B2.5

    pData[5] = ((DWORD)ulpllm * 4 * 100 / 1067);

    pData[6] = 0x00;

    if(pData[5] >= 10)
    {
        pData[5] -= 10;
    }

    if(pData[5] >= 40)
    {
        pData[5] -= 40;
        pData[6] |= 0x04;
    }

    if(pData[5] >= 20)
    {
        pData[5] -= 20;
        pData[6] |= 0x02;
    }

    if(pData[5] >= 10)
    {
        pData[5] -= 10;
        pData[6] |= 0x01;
    }

    pData[6] |= 0x70;
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x71, pData[6]);


    //REG_DPLL_VCOMD[1:0]=11
    pData[6] = (0x06 | (dpllvcomd << 3) );
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x72, pData[6]);

#else

    No setting !!

#endif

    // M code Set
    // bit[7:0]=Set M code,0x00-->2,0x01-->3...0xff-->257.
    // M=18
    ucBuf = (ulpllm - 2);
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x51, ucBuf);

    // ucdiv2, ucdivS Set
    // bit7 = ucdiv2_SET,1-->enable,0-->disable.
    // bit[6:0]=00 -->ucdivS=1 ,01-->ucdivS=2
    // div 2
    ucBuf = (((ucdiv2) << 7) | ((ucdivs) << 0));
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x52, ucBuf);

    // N code,PLL_IN_OUT_SEL, double buffer active
    // bit7=PLL_CLK_INPUT_SEL,0 -->crystal in, 1-->link clk in.
    // bit[6:5]=PLL_CLK_OUTPUT_SEL,00-->PLL OUT,01-->crystal,1x-->link clk
    // bit4=double_buffer_active, 1:active
    // bit[3:0]=N code Set, 0000-->ucdiv2, 1111-->div17
    ucBuf = (((_DP_DPLL_INPUT_SEL) << 7) | ((0x0) << 5) | ((0x1) << 4) | ((ucplln - 2) << 0));

    // Offset Value Setting
    // Offset Value must to be positive
    pData[0] = (lOffsetValue >> 16) & (0x03);
    pData[1] = (lOffsetValue >> 8);
    pData[2] = (lOffsetValue >> 0);
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x55, pData[2]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x54, pData[1]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x53, pData[0]);

    // Enable SDM
    // Enable phase swallow
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x67, 0x10);

    // X'tal in and PLL out, N=2
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x50, ucBuf);

    // Load offset value
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x53, (pData[0] | 0x80));


#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

    //DPLL Auto-Calibration
    ucBuf = 0x80;
    ucBuf = (ucBuf | ucpllo);
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x70, ucBuf); //DPLLO=0

    ucBuf = 0x00;
    ucBuf = (ucBuf | ucpllo);

    // DPLLO=0 & REG_DPLL_CALBP=0 for D0 calibration
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x70, ucBuf);
    CTimerDelayXms(2);
    ucBuf = (ucBuf | 0x04);

    // Reg DPLL_CMPEN
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x70, ucBuf);
    CTimerDelayXms(1);
    ucBuf = (ucBuf | 0x08);

    // Reg DPLL_CALLCH
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x70, ucBuf);
    CTimerDelayXms(1);
    ucBuf = (ucBuf | 0x10);

    // Reg DPLL_CALSW
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x70, ucBuf);
#endif // End of #if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))



#if( (_TRACKING_MODE == _MNTRACKING) || (_TRACKING_MODE == _VS_AND_MN_TRACKING) )
///*--------------Enable M/N auto tracking------------------------
// I = (2^23)*( (Tdds / Tmn) * (1 / n), n = 4
// 1. Fdds = ulLinkClkValue * (ulpllm / ucplln) / 4 --> Tdds = (4 / ulLinkClkValue) * (plln / ulpllm)
// 2. Tmn = (2^15) * (1 / ulLinkClkValue)
// from1,2 we can get : 162Mhz,270Mhz --> I = (2^23) * (Tdds / 202 * (10^ - 6)) * 1 / 4) = 256 * (ucplln / ulpllm)

    ulIcodeValue = (64 * ucplln) / ulpllm;

    // Set I Code
    pData[0] = (ulIcodeValue >> 16);
    pData[1] = (ulIcodeValue >> 8);
    pData[2] = (ulIcodeValue >> 0);
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x57, pData[0]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x58, pData[1]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x59, pData[2]);

    // Set P Code
    pData[2] = 0x07;
    pData[1] = 0xff;
    pData[0] = 0xff;
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x5A, pData[2]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x5B, pData[1]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x5C, pData[0]);

    // Enable M/N tracking
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x56, 0x80);

    // Enable double buffer
    // N code,PLL_IN_OUT_SEL, double buffer active
    ucBuf = ( ((_DP_DPLL_INPUT_SEL) << 7) | ((0x0) << 5) | ((0x1) << 4) | ((ucplln - 2) << 0) );

    //bit7=PLL_CLK_INPUT_SEL,0 -->crystal in, 1-->link clk in.
    //bit[6:5]=PLL_CLK_OUTPUT_SEL,00-->PLL OUT,01-->crystal,1x-->link clk
    //bit4=double_buffer_active, 1:active
    //bit[3:0]=N code Set, 0000-->ucdiv2, 1111-->div17
    //x'tal in and PLL out, N=2
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x50, ucBuf);
//------------end---------------------------------------------------*/
#endif // End of #if( (_TRACKING_MODE == _MNTRACKING) || (_TRACKING_MODE == _VS_AND_MN_TRACKING) )
#if( (_TRACKING_MODE == _VSTRACKING) || (_TRACKING_MODE == _VS_AND_MN_TRACKING) )
///*--------------Enable V/S auto tracking for x'tal------------------------
// I = (2^23) * ( (Tdds / Tvs) * (1 / n), n = 1 or 2 or 4
// 1. Fdds = (DWORD)Streamclk * 2 * ucdivs / 4 --> Tdds = 4 / (Streamclk * 2 * ucdivs)
// 2. Tmn = ulHtotalValue * ulVtotalValue * (1 / Streamclk)
// from 1,2 we can get:162Mhz,270Mhz --> I = (1 / n) * (2^25) / ((Htotal * Vtotal) * ucdivs * 2), 2^25 = 33554432

    CScalerPageSelect(_PAGEC);

    // Get Htotal
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x04, 2, pData, _NON_AUTOINC);
    ulHtotalValue = ( ((DWORD)pData[0] << 8) | ((DWORD)pData[1] << 0) );

    // Get Vtotal
    CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x01, 1, pData, _NON_AUTOINC);

    // Set ODD-Vtotal if interlace-ODD
    if((pData[0] & 0x06) == 0x06)
    {
        CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x0E, 2, pData, _NON_AUTOINC);
    }
    // Set Even-Vtotal if interlace-EVEN or progressive
    else
    {
        CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x0C, 2, pData, _NON_AUTOINC);
    }
    ulVtotalValue = ( ((DWORD)pData[0] << 8) | ((DWORD)pData[1] << 0) );


    if(ucdivs == 0)
    {
        ulIcodeValue = 33554432 / ulHtotalValue / ulVtotalValue / 2;

        if(ulIcodeValue == 0)
        {
            ulIcodeValue = 1;
        }
    }
    else
    {
        ulIcodeValue = 33554432 / ulHtotalValue / ulVtotalValue / 2 / ucdivs / 2;

        if(ulIcodeValue == 0)
        {
            ulIcodeValue = 1;
        }
    }

    // Set I Code
    pData[0] = (ulIcodeValue >> 16);
    pData[1] = (ulIcodeValue >> 8);
    pData[2] = (ulIcodeValue >> 0);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x5F, pData[0]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x60, pData[1]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x61, pData[2]);

    // Set P Code
    pData[2] = 0x7f;
    pData[1] = 0xff;
    pData[0] = 0xff;
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x62, pData[2]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x63, pData[1]);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x64, pData[0]);

    // Enable V/S tracking
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x56, 0x40);

    // Enable double buffer
    // N code,PLL_IN_OUT_SEL, double buffer active
    ucBuf = ( ((_DP_DPLL_INPUT_SEL) << 7) | ((0x0) << 5) | ((0x1) << 4) | ((ucplln-2) << 0) );

    //bit7=PLL_CLK_INPUT_SEL,0 -->crystal in, 1-->link clk in.
    //bit[6:5]=PLL_CLK_OUTPUT_SEL,00-->PLL OUT,01-->crystal,1x-->link clk
    //bit4=double_buffer_active, 1:active
    //bit[3:0]=N code Set, 0000-->ucdiv2, 1111-->div17
    //x'tal in and PLL out, N=2
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x50, ucBuf);

#endif // End of #if( (_TRACKING_MODE == _VSTRACKING) || (_TRACKING_MODE == _VS_AND_MN_TRACKING) )

    return _TRUE;
}
#endif // End of #if(_DP_STREAM_CLOCK_SEL == _BY_MN_VALUE)


//--------------------------------------------------
// Main Process
//--------------------------------------------------
bit CDpStartupSetting(void)
{
    CDpMacInitial();

    /*
    if(ucCurrState == _SEARCH_STATE)
    */
    if(ucCurrState != _NOSUPPORT_STATE)
    {
        CTimerDelayXms(50);
    }

    //Check PHY Stable
    if((CDpIsDisplayPortPhyStable() == _FALSE ))
    {
        CTimerDelayXms(30); //Wait for 1 Frame

        if((CDpIsDisplayPortPhyStable() == _FALSE))
        {


            SET_DPHOTPLUG();
            g_bDpPowerDown = _TRUE;

            g_ucSearchTimes = 35;

            g_bDpDisplayPass = _FALSE;
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_NONE;
            return _FALSE;
        }
    }


    // Check DP Alignment
    if((CDpAlignCheck() == _FALSE))
    {
        CTimerDelayXms(30); //Wait for 1 Frame

        if((CDpAlignCheck() == _FALSE))
        {


            SET_DPHOTPLUG();
            g_bDpPowerDown = _TRUE;

            g_ucSearchTimes = 35;

            g_bDpDisplayPass = _FALSE;
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_NONE;
            return _FALSE;
        }
    }


    g_bDpPowerDown = _FALSE;

    // for DP HDCP
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_Z0CC2_AC, ~_BIT6, 0x00);

    // Check DP HDCP Status
    if( CDpHDCPStatus() == _FALSE)
    {
        SET_DPHOTPLUG();

        /*
        g_bHDCPFail = _TRUE;
        */
        g_bDpCPIRQ = _TRUE;

        /*
        g_ucSearchTimes = 25;
        */
        g_ucSearchTimes = 31;

        g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_NONE;
        return _FALSE;
    }

    // Mac Reset for Fake Link Training
    if(g_bFakeTPEndPass == _TRUE)
    {


        // Mac Reset
        CScalerPageSelect(_PAGEC);
        CScalerSetByte(_PC_AUX_MODE_SET_D0, 0xE1);
        /*
        CScalerSetByte(_PC_DP_CTL_A1, 0x40);
        CScalerSetByte(_PC_DP_CTL_A1, 0x00);
        */
        CScalerSetBit(_PC_DP_CTL_A1, ~_BIT6, _BIT6);
        CScalerSetBit(_PC_DP_CTL_A1, ~_BIT6, 0x00);

        CScalerSetByte(_PC_AUX_MODE_SET_D0, 0xE3);
        g_bFakeTPEndPass = _FALSE;

        /*
        if(ucCurrState != _SEARCH_STATE)
        {
            CTimerDelayXms(50);
            CScalerPageSelect(_PAGEC);
            CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x00, 0xF8);
        }
        */
    }

    // Check DP Video Stream
    if(CDpIsDisplayPortVideoStream() == _FALSE)
    {


        g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_END;
        g_bDpDisplayPass = _FALSE;
        return _FALSE;
    }


    // Display format reset
    CScalerPageSelect(_PAGEC);
    CScalerSetBit(_PC_DP_RESERVE2_BC, ~_BIT7, _BIT7);
    CScalerSetBit(_PC_DP_RESERVE2_BC, ~_BIT7, 0x00);

    // Pop up MSA
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x00, 0xF8);

    /*
    if(ucCurrState == _SEARCH_STATE)
    */
    if(ucCurrState != _NOSUPPORT_STATE)
    {
        CTimerDelayXms(30); //Wait for Pop Up MSA(1 frame)
    }

    // Get MSA value
    CDpGetMsaValue();

    // Video froamt Setting
    CDpVideoSetting();

    // Display Format Start up
    CDpDisplayFormatInitial();

#if(_DP_STREAM_CLOCK_SEL == _BY_MN_VALUE)
   if (CDpStreamClkRegeneratByMN() == _FALSE)
   {


        g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_END;
        g_bDpDisplayPass = _FALSE;
        return _FALSE;
   }
#endif // End of #if(_DP_STREAM_CLOCK_SEL == _BY_MN_VALUE)


   g_bDpDisplayPass = _TRUE;

   return _TRUE;

}

//--------------------------------------------------
// Main Process to Check Alignment
//--------------------------------------------------
bit CDpAlignCheck(void)
{
    BYTE ucBuf = 0;

    /*
    if(ucCurrState != _ACTIVE_STATE)
    */
    if((ucCurrState != _ACTIVE_STATE) && (ucCurrState != _CHECK_STATE))
    {
        // for Link Layer CTS
        CDpMacReset();
    }
    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);

    // use current DPCD setting in case of no LT
    CScalerRead(_PC_DPCD_DATA_PORT_L_C4, 1, pData, _NON_AUTOINC);

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_MIN_DE_SKEW_A8, 0x1c);
    CScalerSetByte(_PC_MN_ERRC_A9, 0x03);

    // Read Align Status
    CScalerRead(_PC_MN_ERRC_A9, 1, &ucBuf, _NON_AUTOINC);

    if(((ucBuf & 0x03) == 0x00) || ((pData[0] & 0x1F) == 0x01))
    {
        return _TRUE;
    }
    // Warning
    else if((ucBuf & 0x02) == 0x02)
    {
        CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x01, 1, &ucBuf, _NON_AUTOINC);

        // Idle Pattern
        if ((ucBuf & 0x08) == 0x08)
        {
            // Check all control symbols
            CScalerSetBit(_PC_MIN_DE_SKEW_A8, ~_BIT7, _BIT7);
            CScalerSetByte(_PC_MN_ERRC_A9, 0x03);

            // Read Align Status
            CScalerRead(_PC_MN_ERRC_A9, 1, &ucBuf, _NON_AUTOINC);

            if((ucBuf & 0x02) == 0x02)
            {
                CScalerSetBit(_PC_MIN_DE_SKEW_A8, ~_BIT7, 0x00);
                return _FALSE;
            }
            else
            {
                CScalerSetBit(_PC_MIN_DE_SKEW_A8, ~_BIT7, 0x00);
                return _TRUE;
            }
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP MAC Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpMacReset(void)
{
    BYTE ucBuf1 = 0;

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);

    // Use current DPCD setting in case of no LT
    CScalerRead(_PC_DPCD_DATA_PORT_L_C4, 1, pData, _NON_AUTOINC);

    if((pData[0] & 0x80) == 0x80)
    {
        ucBuf1 |= _BIT2;
    }

    if((pData[0] & 0x1F) == 0x01)
    {
        ucBuf1 |= _BIT3;
    }
    else if((pData[0] & 0x1F) == 0x02)
    {
        ucBuf1 |= _BIT4;
    }
    else
    {
        ucBuf1 |= (_BIT3 | _BIT4);
    }

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DP_CTL_A1, ucBuf1);
}

//--------------------------------------------------
// Description  : DP Sink Status update (DPCD 0x00205h)
// Input Value  : _TRUE-> In Sync, _FALSE -> out of sync
// Output Value : None
//--------------------------------------------------
void CDpSinkStatusSet(bit InSink)
{
    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);

    // DPCD 0x00205, SINK_STATUS report
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x05);
    if(InSink == _TRUE)
    {

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        // port D0 In Sync
        CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, 0x01);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        // port D1 In Sync
        CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, 0x03);
#endif

    }
    else
    {
        // Sink out of sync
        CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Display PHY CTS stepbystep
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

#if (_DP_PHYCTS_STEPBYSTEP == _ON)
void CDPPHYCTSSTEP(void)
{
    BYTE idata ucdpratelane = 0;
    BYTE idata ucidle = 0;

    BYTE idata ucctsEN = 0;
    BYTE idata ucctsPhase = 0;

    BYTE idata uccounter = 0;
    BYTE idata ucctsReadCRC_1 = 0;
    BYTE idata ucctsReadCRC_2 = 0;

    BYTE idata ucctsRightValue1 = 0;
    BYTE idata ucctsRightValue2 = 0;
    BYTE idata uclaneValid = 0;
    BYTE idata uclaneValid_2 = 0;
    BYTE idata uclaneValid_1 = 0;

    BYTE idata uceqCRC = 0;
    BYTE idata uclaneCount = 0;

    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x09);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x00);
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x0A);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x00);

    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x10);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x00);
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x11);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x00);
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x12);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x00);

    /*
    CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);
    if(GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT)
    {
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x02);
    }
    else if(GET_INPUT_PORT(g_ucSearchIndex) == _D1_INPUT_PORT)
    {
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x06);
    }

    CTimerDelayXms(30);
    CMiscIspDebugProc();
    */

    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x08);
    CScalerRead(_TCON_DATA_PORT_8C, 1, &ucctsEN, _NON_AUTOINC);

    while(ucctsEN == 0x77)
    {
        /*
        CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x02);
        */

        CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);
        /*
        if(GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT)
        {
            CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x02);
        }
        else if(GET_INPUT_PORT(g_ucSearchIndex) == _D1_INPUT_PORT)
        {
            CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x06);
        }
        */
#if (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x02);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x06);
#endif

        CTimerDelayXms(50);
        CMiscIspDebugProc();

        CScalerSetByte(_TCON_ADDR_PORT_8B, 0x09);
        CScalerRead(_TCON_DATA_PORT_8C, 1, &ucdpratelane, _NON_AUTOINC);

        CScalerSetByte(_TCON_ADDR_PORT_8B, 0x0A);
        CScalerRead(_TCON_DATA_PORT_8C, 1, &ucctsPhase, _NON_AUTOINC);

        // Clean the command register
        CScalerSetByte(_TCON_ADDR_PORT_8B, 0x0A);
        CScalerSetByte(_TCON_DATA_PORT_8C, 0x00);

        switch(ucctsPhase)
        {
            /*! frequency locked phase:
            //  _TRAINING_PATTERN1 are transmitted */
            case 1:
                if((ucdpratelane & 0x01) == 0x01)
                {
                    // Settings for 2.7Ghz Bandwidth (HBR)
                    bLED2 = ~bLED2;

                    // Counter value == 66, 67 are correct
                    ucctsRightValue1 = 0x66;
                    ucctsRightValue2 = 0x67;

                    CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);
                    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x00);
                    CScalerSetByte(_PB_DP_AUX_01_B8, 0x51);
                    CScalerSetByte(_PB_DP_AUX_02_B9, 0x05);
                    CScalerSetByte(_PB_DIG02_E2, 0x80);
                    CScalerSetByte(_PB_DP_AUX_00_B3, 0x80);
                    CScalerSetByte(_PB_DIG03_E3, 0x01);
                    CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);

                    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x00);
                    CScalerSetByte(_PB_DP_OOBS_SGN_DET_B1, 0x32);

                    CScalerSetByte(_PB_DIG00_E0, 0xC0);
                    CScalerSetByte(_PB_DP_RXMISC_02_AF, 0x87);

                    CScalerSetByte(_PB_DP_CDR_03_A3, 0x8C);
                    CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
                    CScalerSetByte(_PB_DP_FLD_08_AC, 0xC0);
                    CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
                    CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x5E);
                    CScalerSetByte(_PB_DP_RESERVED_00_BA, 0xF0);

                    // 0x11 for one lane, 0xff for four lane
                    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0xFF);

                    for(ucidle = 0; ucidle <= 20; ucidle++)
                    {
                        _nop_();
                    }

                    CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x8D);
                    CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x0D);


                    CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);
                    CScalerSetByte(_PB_DP_CDR_01_A1, 0x32);
                    CScalerSetByte(_PB_DP_CDR_02_A2, 0x01);
                    CScalerSetByte(_PB_DP_FLD_09_AD, 0x8F);

                    CScalerSetByte(_PB_DP_RXMISC_02_AF, 0xC7);
                    CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x8D);
                    CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x0D);
                    CScalerSetByte(_PB_DIG01_E1, 0xf0);

                }
                else if((ucdpratelane & 0x02) == 0x02)
                {
                    //! Settings for 1.62Ghz Bandwidth (RBR)
                    bLED2 = ~bLED2;

                    ucctsRightValue1 = 0xAA;
                    ucctsRightValue2 = 0xAC;

                    CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);
                    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x00);
                    CScalerSetByte(_PB_DP_AUX_01_B8, 0x51);
                    CScalerSetByte(_PB_DP_AUX_02_B9, 0x05);
                    CScalerSetByte(_PB_DIG02_E2, 0x80);
                    CScalerSetByte(_PB_DP_AUX_00_B3, 0x80);
                    CScalerSetByte(_PB_DIG03_E3, 0x01);
                    CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);

                    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x00);
                    CScalerSetByte(_PB_DP_OOBS_SGN_DET_B1, 0x32);

                    CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x06);
                    CScalerSetByte(_PB_DIG00_E0, 0xC0);
                    CScalerSetByte(_PB_DP_RXMISC_02_AF, 0x87);

                    CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
                    CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x56);
                    CScalerSetByte(_PB_DP_RESERVED_00_BA, 0xF0);

                    CScalerSetByte(_PB_DP_CDR_03_A3, 0x8C);
                    CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
                    CScalerSetByte(_PB_DP_FLD_08_AC, 0x40);

                    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0xFF);

                    for(ucidle = 0; ucidle <= 20; ucidle++)
                    {
                        _nop_();
                    }

                    CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x8D);
                    CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x0D);


                    CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);
                    CScalerSetByte(_PB_DP_CDR_01_A1, 0x72);
                    CScalerSetByte(_PB_DP_CDR_02_A2, 0x21);
                    CScalerSetByte(_PB_DP_FLD_09_AD, 0x8F);

                    CScalerSetByte(_PB_DP_RXMISC_02_AF, 0xC7);
                    CScalerSetByte(_PB_DP_RESERVED_00_BA, 0xC0);
                    CScalerSetByte(_PB_DIG01_E1, 0xf0);

                }
                else
                {
                    CMiscIspDebugProc();
                    CTimerDelayXms(50);
                }

                CScalerSetByte(_PAGE_SELECT_9F, _PAGEC);
                CScalerSetByte(_PC_DP_CTL_A1, 0x1C);
                CScalerSetByte(_PC_DP_LANE_VALID_A5, 0xFF);

                CScalerRead(_PC_DP_LANE_VALID_A5, 1, &uclaneValid_1, _NON_AUTOINC);

                CScalerSetByte(_TCON_ADDR_PORT_8B, 0x10);
                CScalerSetByte(_TCON_DATA_PORT_8C, 0x00);
                CTimerDelayXms(1);


                /*! 20081117: binbin+
                //! note of checking the CRC value of input data stream
                //! for lane0: pageC Reg[0xC6] = 00,
                //!     lane1: pageC Reg[0xC6] = 01,
                //!     lane2: pageC Reg[0xC6] = 02,
                //!     lane3: pageC Reg[0xC6] = 03
                //! then read the result from pageC Reg[0xCB] */

                /*! 20081117: binbin+
                //! note of checking PLL counter
                //! for lane0: pageC Reg[0xA4] = 0x00,
                //!     lane1: pageC Reg[0xA4] = 0x55,
                //!     lane2: pageC Reg[0xA4] = 0xAA,
                //!     lane3: pageC Reg[0xA4] = 0xFF
                //! then read the result from page2 Reg[0xCA-08], Reg[0xCA-09] */

                CScalerSetByte(_PAGE_SELECT_9F, _PAGEC);

                if((ucdpratelane & 0x10) == 0x10)
                {
                    uclaneCount = 0x08;
                    CScalerSetByte(_PC_LANE_SWAP_A4, 0x00);
                    CScalerSetByte(_PC_AUX_RESERVE1_C6, 0x00);
                }
                else if((ucdpratelane & 0x20) == 0x20)
                {
                    uclaneCount = 0x04;
                    CScalerSetByte(_PC_LANE_SWAP_A4, 0x55);
                    CScalerSetByte(_PC_AUX_RESERVE1_C6, 0x01);
                }
                else if((ucdpratelane & 0x40) == 0x40)
                {
                    uclaneCount = 0x02;
                    CScalerSetByte(_PC_LANE_SWAP_A4, 0xAA);
                    CScalerSetByte(_PC_AUX_RESERVE1_C6, 0x02);
                }
                else if((ucdpratelane & 0x80) == 0x80)
                {
                    uclaneCount = 0x01;
                    CScalerSetByte(_PC_LANE_SWAP_A4, 0xFF);
                    CScalerSetByte(_PC_AUX_RESERVE1_C6, 0x03);
                }

                // check the CRC value in pageC
                CScalerRead(_PC_READ_RESERVE1_CB, 1, &ucctsReadCRC_1, _NON_AUTOINC);

                CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);
                CScalerSetByte(_PB_DP_RESERVED_00_BA, 0x00);

                CScalerSetByte(_PAGE_SELECT_9F, _PAGEC);
                CScalerSetByte(_PC_DP_CTL_A1, 0x1C);
                CScalerSetByte(_PC_DP_LANE_VALID_A5, 0xFF);
                CScalerRead(_PC_DP_LANE_VALID_A5, 1, &uclaneValid_2, _NON_AUTOINC);

                uclaneValid = uclaneValid_1 | uclaneValid_2;

                CScalerSetByte(_PAGE_SELECT_9F, _PAGEC);
                if((ucdpratelane & 0x10) == 0x10)
                {
                    uclaneCount = 0x08;
                    CScalerSetByte(_PC_LANE_SWAP_A4, 0x00);
                    CScalerSetByte(_PC_AUX_RESERVE1_C6, 0x00);
                }
                else if((ucdpratelane & 0x20) == 0x20)
                {
                    uclaneCount = 0x04;
                    CScalerSetByte(_PC_LANE_SWAP_A4, 0x55);
                    CScalerSetByte(_PC_AUX_RESERVE1_C6, 0x01);
                }
                else if((ucdpratelane & 0x40) == 0x40)
                {
                    uclaneCount = 0x02;
                    CScalerSetByte(_PC_LANE_SWAP_A4, 0xAA);
                    CScalerSetByte(_PC_AUX_RESERVE1_C6, 0x02);
                }
                else if((ucdpratelane & 0x80) == 0x80)
                {
                    uclaneCount = 0x01;
                    CScalerSetByte(_PC_LANE_SWAP_A4, 0xFF);
                    CScalerSetByte(_PC_AUX_RESERVE1_C6, 0x03);
                }

                // check the CRC value in pageC
                CScalerRead(_PC_READ_RESERVE1_CB, 1, &ucctsReadCRC_2, _NON_AUTOINC);


                // check the PLL counter value
                CScalerSetByte(_PAGE_SELECT_9F, _PAGE2);
                CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x28);
                CScalerSetByte(_P2_HDMI_DATA_PORT_CA, 0x08);
                CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x29);
                CScalerRead(_P2_HDMI_DATA_PORT_CA, 1, &uccounter, _NON_AUTOINC);

                if(((uccounter >= ucctsRightValue1) || (uccounter <= ucctsRightValue2)) &&
                   ((uclaneValid & uclaneCount) == 0x00) &&
                   ((ucctsReadCRC_1 == 0x4A) || (ucctsReadCRC_1 == 0xB5)) && ((ucctsReadCRC_2 == 0x4A) || (ucctsReadCRC_2 == 0xB5)))
                {
                    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x10);
                    CScalerSetByte(_TCON_DATA_PORT_8C, 0x01);
                }
                else
                {
                    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x10);
                    CScalerSetByte(_TCON_DATA_PORT_8C, 0xFF);
                }

                break;
            /*! symbol locked phase:
            //! _TRAINING_PATTERN2 are transmitted */
            case 2:

                // DP Equalizer CRC control
                CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);
                CScalerSetByte(_PB_DIG02_E2, 0x80);

                if((ucdpratelane & 0x01) == 0x01)
                {
                    CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x7E);
                    CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
                    CScalerSetByte(_PB_DP_FLD_09_AD, 0x87);
                }
                else if((ucdpratelane & 0x02) == 0x02)
                {
                    CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x76);
                    CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
                    CScalerSetByte(_PB_DP_FLD_09_AD, 0x87);
                }

                CScalerSetByte(_PAGE_SELECT_9F, _PAGEC);
                CScalerSetByte(_PC_LANE_SWAP_A4, 0x1B);

                CScalerSetByte(_PAGE_SELECT_9F, _PAGEC);
                CScalerSetByte(_PC_DP_ACCESS_PORT_B3, 0xB3);
                CScalerSetByte(_PC_DP_DATA_PORT_B4, 0xAF);
                CScalerSetByte(_PC_DP_ACCESS_PORT_B3, 0xB3);
                CScalerSetByte(_PC_DP_DATA_PORT_B4, 0xAF);
                CScalerSetByte(_PC_DP_ACCESS_PORT_B3, 0xB3);
                CScalerRead(_PC_DP_DATA_PORT_B4, 1, &uceqCRC, _NON_AUTOINC);

                // Clean the replying flag
                CScalerSetByte(_TCON_ADDR_PORT_8B, 0x11);
                CScalerSetByte(_TCON_DATA_PORT_8C, 0x00);
                CScalerSetByte(_TCON_ADDR_PORT_8B, 0x11);


                if((ucdpratelane & 0x10) == 0x10)
                {
                    uclaneCount = 0x08;
                }
                else if((ucdpratelane & 0x20) == 0x20)
                {
                    uclaneCount = 0x04;
                }
                else if((ucdpratelane & 0x40) == 0x40)
                {
                    uclaneCount = 0x02;
                }
                else if((ucdpratelane & 0x40) == 0x80)
                {
                    uclaneCount = 0x01;
                }
                else
                {
                    CMiscIspDebugProc();
                    CTimerDelayXms(50);
                }

                /*! set the replying register */
                if( (uceqCRC & uclaneCount) == 0x00)
                {
                    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x11);
                    CScalerSetByte(_TCON_DATA_PORT_8C, 0x01);
                }
                else
                {
                    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x11);
                    CScalerSetByte(_TCON_DATA_PORT_8C, 0xFF);
                }
                break;
            /*! PRBS7 counter reset and counter start */
            case 3:

                CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);
                CScalerSetByte(_PB_DIG03_E3, 0x01);
                CScalerSetByte(_PB_DIG02_E2, 0x84);
                CScalerSetByte(_PB_DIG03_E3, 0x09);
                CTimerDelayXms(1);
                CScalerSetByte(_PB_DIG03_E3, 0x89);
                CScalerSetByte(_PB_DIG03_E3, 0x09);

                if((ucdpratelane & 0x10) == 0x10)
                {
                    CScalerSetByte(_PB_DIG05_E5, 0x00);
                }

                if((ucdpratelane & 0x20) == 0x20)
                {
                    CScalerSetByte(_PB_DIG05_E5, 0x20);
                }

                if((ucdpratelane & 0x40) == 0x40)
                {
                    CScalerSetByte(_PB_DIG05_E5, 0x40);
                }

                if((ucdpratelane & 0x80) == 0x80)
                {
                    CScalerSetByte(_PB_DIG05_E5, 0x60);
                }

                /*! set the replying register */
                CScalerRead(0xE8, 1, &uccounter, _NON_AUTOINC);
                CScalerSetByte(_TCON_ADDR_PORT_8B, 0x12);
                CScalerSetByte(_TCON_DATA_PORT_8C, uccounter);
                break;

            /*! counter read and replying upon the register */
            case 4:
                CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);

                /*! set the replying register */
                CScalerRead(0xE8, 1, &uccounter, _NON_AUTOINC);
                CScalerSetByte(_TCON_ADDR_PORT_8B, 0x12);
                CScalerSetByte(_TCON_DATA_PORT_8C, uccounter);

                break;


            /* Clear all status register */
            case 5:

                CScalerSetByte(_TCON_ADDR_PORT_8B, 0x09);
                CScalerSetByte(_TCON_DATA_PORT_8C, 0x00);
                CScalerSetByte(_TCON_ADDR_PORT_8B, 0x08);
                CScalerSetByte(_TCON_DATA_PORT_8C, 0x00);

                ucctsEN = 0x00;
                CScalerSetByte(_TCON_ADDR_PORT_8B, 0x08);
                CScalerSetByte(_TCON_ADDR_PORT_8B, ucctsEN);
                break;
            /* Clear all status register */
            default:
                break;
        }// End of Switch

    }// End of while(ucctsEN = 0x77)
}
#endif  // End of #if (_DP_PHYCTS_STEPBYSTEP == _ON)

#endif  // End of #if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
//--------------------------------------------------
// Description  : Detect DP cable connection
// Input Value  : None
// Output Value : True --> DP cable is connected, False --> DP cable isn't connected
//--------------------------------------------------
bit CDpCableConnect(void)   // for Cable Detect
{
    BYTE times = 0;
    do
    {
        /*
        if(bD0_CONNECT == 0)
        */
        if(CDpAuxPinCableConnect() == _FALSE)
        {
            times += _DP_CABLE_TIMESTEP;
            if(times >= _DP_CABLE_TIME)
            {
                g_bDpPlug = _TRUE;
                return _TRUE;
            }
        }
        else
        {
            if(g_bDpPlug == _TRUE)
            {


                g_bDpPlug = _FALSE;
                CDpInitial();
                CScalerCodeW(tDP_DPCD_INITIAL);
                g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_NONE;
                CLR_DPHOTPLUG();
            }

            return _FALSE;

        }   // End of if(CDpAuxPinCableConnect() == _FALSE)

        CTimerDelayXms(_DP_CABLE_TIMESTEP);

    }while(times < _DP_CABLE_TIME);
}
#endif // End of #if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)

//--------------------------------------------------
// Description  : Detect if Msa Is Change?
// Input Value  : None
// Output Value : _TRUE -> MsaMisc, Mvid, Hactive, Vactive is change
//--------------------------------------------------
bit CDpMsaIsChange(void)
{
    /*
    WORD  xdata ushactivecurr = g_usDpHactive;
    WORD  xdata usvactivecurr = g_usDpVactive;
    DWORD xdata ulmvidcurr = g_ulDpMvidValue;
    BYTE  xdata masmisccurr = g_ucDpMsaMisc;

    DWORD temp = 0;
    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x00, 0xF8);
    CTimerDelayXms(50);

    CDpGetMsaValue();

    if(masmisccurr != g_ucDpMsaMisc)
    {
        return _TRUE;
    }

    if(abs(g_usDpHactive - ushactivecurr) >= (WORD)4)
    {
        return _TRUE;
    }

    if(abs(g_usDpVactive - usvactivecurr) >= (WORD)4)
    {
        return _TRUE;
    }

    temp = (ulmvidcurr >> 7);

    if((g_ulDpMvidValue == 0) || (ulmvidcurr == 0))
    {
        return _FALSE;
    }

    if((abs(g_ulDpMvidValue - ulmvidcurr)) > (DWORD)temp)
    {
        return _TRUE;
    }

    return _FALSE;
    */

    WORD  xdata usHactiveCurr = g_usDpHactive;
    WORD  xdata usVactiveCurr = g_usDpVactive;
    DWORD xdata ulMvidCurr = g_ulDpMvidValue;
    BYTE  xdata ucMsaMiscCurr = g_ucDpMsaMisc;
    DWORD xdata ulTemp = 0;

    CScalerPageSelect(_PAGEC);
    CScalerSetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x00, 0xF8);

    CDpGetMsaValue();

    if(ucMsaMiscCurr != g_ucDpMsaMisc)
    {
        return _TRUE;
    }

    if(abs(g_usDpHactive - usHactiveCurr) >= 4)
    {
        return _TRUE;
    }

    if(abs(g_usDpVactive - usVactiveCurr) >= 4)
    {
        return _TRUE;
    }

    ulTemp = (ulMvidCurr >> 7);

    if((g_ulDpMvidValue == 0) || (ulMvidCurr == 0))
    {
        return _FALSE;
    }

    if(g_ulDpMvidValue >= ulMvidCurr)
    {
        if((g_ulDpMvidValue - ulMvidCurr) > ulTemp)
        {
            return _TRUE;
        }
    }
    else
    {
        if((ulMvidCurr - g_ulDpMvidValue) > ulTemp)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Name         : Fast Link Training set
// Date         : 20081118
// Edit         : fcchang
// Description  : Set the value into selected register
// Input Value  : ucRate   --> HBR==> 0x0A
//                             RBR==> 0x06
//                ucLane   --> One  lane==> 0x81
//                             Two  lane==> 0x82
//                             Four lane==> 0x84
// Output Value : None
//--------------------------------------------------
void CDpFastlinktrainSet(void)
{
    BYTE xdata ucbuf = 0;
    BYTE xdata ucPHYCheck = 0;
    BYTE xdata ucAlignCheck = 0;

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_AUX_MODE_SET_D0, 0xE1);

    CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);

    /*
    if(GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT)
    {
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x02);
    }
    else if(GET_INPUT_PORT(g_ucSearchIndex) == _D1_INPUT_PORT)
    {
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x06);
    }
    */
#if (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x02);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x06);
#endif

    CScalerSetByte(_PB_DP_AUX_00_B3, 0x80);
    CScalerSetByte(_PB_DIG02_E2, 0x00);

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x00);

    /*
    CScalerRead(_PC_DPCD_DATA_PORT_L_C4, 1, pData, _NON_AUTOINC);
    */
    CScalerRead(_PC_DPCD_DATA_PORT_L_C4, 1, &g_ucDpRate, _NON_AUTOINC);

    /*
    if(pData[0] == 0x0A)
    */
    if(g_ucDpRate == 0x0A)
    {
        CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x00);

        CScalerSetByte(_PB_DIG00_E0, 0xC0);
        CScalerSetByte(_PB_DP_RXMISC_02_AF, 0x87);
        CScalerSetByte(_PB_DP_CDR_03_A3, 0x8C);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
        CScalerSetByte(_PB_DP_FLD_08_AC, 0xC0);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
        CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x7E);

        CScalerSetByte(_PB_DP_CDR_01_A1, 0x32);
        CScalerSetByte(_PB_DP_CDR_02_A2, 0x01);
        CScalerSetByte(_PB_DP_FLD_09_AD, 0x87);
        CScalerSetByte(_PB_DP_RXMISC_02_AF, 0xC7);

        CScalerSetByte(_PB_DIG01_E1, 0xf0);

    }
    else
    {
        CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x00);

        CScalerSetByte(_PB_DIG00_E0, 0xC0);
        CScalerSetByte(_PB_DP_RXMISC_02_AF, 0x87);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
        CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x76);
        CScalerSetByte(_PB_DP_CDR_03_A3, 0x8C);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
        CScalerSetByte(_PB_DP_FLD_08_AC, 0x40);

        CScalerSetByte(_PB_DP_CDR_01_A1, 0x72);
        CScalerSetByte(_PB_DP_CDR_02_A2, 0x21);
        CScalerSetByte(_PB_DP_FLD_09_AD, 0x87);
        CScalerSetByte(_PB_DP_RXMISC_02_AF, 0xC7);

        CScalerSetByte(_PB_DIG01_E1, 0xf0);
    }


    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);
    CScalerRead(_PC_DPCD_DATA_PORT_L_C4, 1, pData, _NON_AUTOINC);



    CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);

    if((pData[0] & 0x07) == 0x01)
    {
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x11);
        /*
        for (ucbuf = 0; ucbuf <= 20; ucbuf++)
        {
            _nop_();
        }
        */
    }
    else if((pData[0] & 0x07) == 0x02)
    {
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x33);
        /*
        for(ucbuf=0; ucbuf<=20; ucbuf++)
        {
            _nop_();
        }
        */
    }
    else if((pData[0] & 0x07) == 0x04)
    {
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0xFF);
    }
    else
    {
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x11);
    }
/*
        for (ucbuf=0; ucbuf<=20; ucbuf++)
        {
            _nop_();
        }
    }
    else
    {
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x11);

        for (ucbuf=0; ucbuf<=20; ucbuf++)
        {
            _nop_();
        }
    }
*/

    // Reset FLD
    if((g_ucDpRate & 0x0A) == 0x0A)
    {
        CScalerSetByteInt(_PB_DP_FLD_08_AC, 0xC8);
        CScalerSetByteInt(_PB_DP_FLD_08_AC, 0xC0);
    }
    else if((g_ucDpRate & 0x06) == 0x06)
    {
        CScalerSetByteInt(_PB_DP_FLD_08_AC, 0x48);
        CScalerSetByteInt(_PB_DP_FLD_08_AC, 0x40);
    }
    CScalerSetByteInt(_PB_DP_OOBS_RXAMP_B0, 0x8d);
    CScalerSetByteInt(_PB_DP_OOBS_RXAMP_B0, 0x0d);

    for (ucbuf = 0; ucbuf <= 30; ucbuf++)
    {
        _nop_();
    }

    CScalerPageSelect(_PAGEC);
    //CScalerSetByte(_PC_DP_CTL_A1, 0x40);
    //CScalerSetByte(_PC_DP_CTL_A1, 0x00);
    CScalerSetByte(_PC_AUX_MODE_SET_D0, 0xE3);

    while(ucPHYCheck < 45)
    {
        if( CDpIsDisplayPortPhyStable() )
        {
            break;
        }
        else
        {
            CTimerDelayXms(10);
            ucPHYCheck++;
        }
    }
}

//--------------------------------------------------
// Description  : HDCP
// Input Value  :
// Output Value : True--> HDCP pass     False--> HDCP fail
//--------------------------------------------------
bit CDpHDCPStatus(void)
{
    if(g_bHDCPFail == _TRUE)
    {
        g_bHDCPFail = _FALSE;

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
        if(GET_SOURCE_SEARCH_AUTO() == _TRUE)
        {


            return _FALSE;
        }
#endif
    }

    CScalerPageSelect(_PAGEC);
    CScalerRead(_PC_DP_HDCP_DEBUG_EAS_EA, 1, pData, _NON_AUTOINC);

    if((pData[0] & 0xE0) == 0xE0)
    {
        CScalerPageSelect(_PAGEC);
        CScalerSetBit(_PC_DP_HDCP_INTGT_VRF_E4, ~_BIT1, _BIT1);
        CScalerRead(_PC_DP_HDCP_INTGT_VRF_E4, 1, pData, _NON_AUTOINC);
        if((pData[0] & 0x02) == 0x02)
        {


            return _FALSE;
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : HDCP key assign for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpAdjustHDCP(void)
{
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_Z0CC2_AC, ~_BIT6, 0x00);

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DP_HDCP_CONTROL_E0, 0x81);

    CAdjustWriteHDCPKey(_PC_DP_HDCP_KEY_DOWNLOAD_PORT_E1, 320, _NON_AUTOINC);

    CScalerSetByte(_PC_DP_HDCP_CONTROL_E0, 0x80);

    CScalerSetByte(_PC_DP_HDCP_INTGT_VRF_E4, 0xb4);

    /*
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x06);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x80);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x00);
    CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, 0xB7);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);
    CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, 0x28);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x02);
    CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, 0xA9);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
    CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, 0x51);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x04);
    CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, 0xD6);
    */
    CScalerCodeW(tDP_HDCP_BKSV_KEY);

    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x06);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x80);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x28);
    CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, 0x01);

    /*
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_Z0CC2_AC, ~_BIT6, _BIT6);
    */
}


//--------------------------------------------------
// Description  : calculation DP CRC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpCRCTest(void)
{
    BYTE xdata ucTestCRCTimes = 0;

    if(g_bDpCRCStart == 1)
    {
        g_bDpCRCStart = 0;

        CScalerSetByte(_PAGE_SELECT_9F, _PAGEC);
        CScalerSetByte(_PC_DP_CRC_AB, 0x80);

        if(CTimerPollingFlagProc(200, _PAGEC, _PC_DP_CRC_AB, _BIT6, 0x01))
        {
            CScalerPageSelect(_PAGEC);
            CScalerGetDataPortByte(_PC_DP_ACCESS_PORT_B3, 0x31, 1, pData, _NON_AUTOINC);

            if((pData[0] & 0x18) == 0x08)
            {
                CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
                CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);
                CScalerRead(_PC_DP_CRC_R_H_AC, 1, &pData[0], _NON_AUTOINC);
                CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x41);
                CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, 0x00);

                CScalerRead(_PC_DP_CRC_R_L_AD, 1, &pData[0], _NON_AUTOINC);
                CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x40);
                CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, 0x00);
            }
            else
            {
                CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
                CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);
                CScalerRead(_PC_DP_CRC_R_H_AC, 1, &pData[0], _NON_AUTOINC);
                CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x41);
                CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, pData[0]);

                CScalerRead(_PC_DP_CRC_R_L_AD, 1, &pData[0], _NON_AUTOINC);
                CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x40);
                CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, pData[0]);
            }

            CScalerRead(_PC_DP_CRC_G_H_AE, 1, &pData[0], _NON_AUTOINC);
            CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x43);
            CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, pData[0]);

            CScalerRead(_PC_DP_CRC_G_L_AF, 1, &pData[0], _NON_AUTOINC);
            CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x42);
            CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, pData[0]);

            CScalerRead(_PC_DP_CRC_B_H_B0, 1, &pData[0], _NON_AUTOINC);
            CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x45);
            CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, pData[0]);

            CScalerRead(_PC_DP_CRC_B_L_B1, 1, &pData[0], _NON_AUTOINC);
            CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x44);
            CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, pData[0]);

            ucTestCRCTimes++;

            CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x46);
            CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, (ucTestCRCTimes | 0x20));
        }

        CScalerSetByte(_PAGE_SELECT_9F, _PAGEC);
        CScalerSetByte(_PC_DP_CRC_AB, 0x00);
    }
    else
    {
        //do nothing
    }

}

//--------------------------------------------------
// Description  : check Training pattern 1 lane0 status.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpTP1Lane0Check(void)
{
    // Adjust Offset to MAX.
    CScalerSetByteInt(_PB_DP_RESERVED_00_BA, 0xF0);

    // Check 8B/10B for offset maximum (only do it at the 1st time)
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DP_LANE_VALID_A5, 0xFF);
    CScalerReadByteInt(_PC_DP_LANE_VALID_A5, &g_ucTP1Decode1);

    // Select CRC lane0
    CScalerSetByteInt(_PC_AUX_RESERVE1_C6, 0x00);

    // Check CRC for offset Max.
    CScalerReadByteInt(_PC_READ_RESERVE1_CB, &g_ucCrcLane1);

    // Adjust Offset to Min.
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
    CScalerSetByteInt(_PB_DP_RESERVED_00_BA, 0x00);

    // Check 8B/10B for offset min. (only do it at the 1st time)
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DP_LANE_VALID_A5, 0xFF);
    CScalerReadByteInt(_PC_DP_LANE_VALID_A5, &g_ucTP1Decode2);

    // Check CRC for offset min.
    CScalerReadByteInt(_PC_READ_RESERVE1_CB, &g_ucCrcLane2);

    // union the checking result
    g_ucTP1Decode = g_ucTP1Decode1 | g_ucTP1Decode2;

    // Lane_0 D10.2 Check
    if(((g_ucTP1Decode & 0x08) == 0x00) && ((g_ucCrcLane1 == 0x4A) || (g_ucCrcLane1 == 0xB5)) && ((g_ucCrcLane2 == 0x4A) || (g_ucCrcLane2 == 0xB5)))
    {
        if(g_bLTLane0FirstPass == _FALSE)
        {
            g_bLTLane0FirstPass = _TRUE;
            g_ucTP1Error = 0x08;
        }
        else
        {
            g_bLTLane0FirstPass = _FALSE;
            g_ucTP1Error = 0x00;
        }
    }
    else
    {
        g_bLTLane0FirstPass = _FALSE;
        g_ucTP1Error = 0x08;
    }

    if((g_ucTP1Error & 0x08) == 0x00)
    {
        g_ucLane01Status |= 0x01;
    }
    else
    {
        g_ucLane01Status &= 0xFE;

        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
        CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucTrainingLaneSet);

        g_ucAdjustRequestL01 = ((g_ucAdjustRequestL01 & 0xF0) | (g_ucTrainingLaneSet & 0x03) | (((g_ucTrainingLaneSet & 0x18) >> 1) & 0x0C));

        if(((g_ucTrainingLaneSet & 0x04) == 0x00) && ((g_ucAdjustRequestL01 & 0x03) != 0x03))
        {
            g_ucAdjustRequestL01 = g_ucAdjustRequestL01 + 0x01;
        }
        else if(g_bLTLane0FirstPass == _TRUE)
        {
            g_bLTLane0FirstPass = _FALSE;
            g_ucLane01Status |= 0x01;
        }

    }
}

//--------------------------------------------------
// Description  : check Training pattern 1 lane1 status.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpTP1Lane1Check(void)
{
    // Adjust Offset to MAX.
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
    CScalerSetByteInt(_PB_DP_RESERVED_00_BA, 0xF0);

    // Select CRC lane1
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_AUX_RESERVE1_C6, 0x01);

    // check CRC for offset max.
    CScalerReadByteInt(_PC_READ_RESERVE1_CB, &g_ucCrcLane1);

    // adjust offset to min.
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
    CScalerSetByteInt(_PB_DP_RESERVED_00_BA, 0x00);

    // check for offset min.
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerReadByteInt(_PC_READ_RESERVE1_CB, &g_ucCrcLane2);

    if(((g_ucTP1Decode & 0x04) == 0x00) && ((g_ucCrcLane1 == 0x4A) || (g_ucCrcLane1 == 0xB5)) && ((g_ucCrcLane2 == 0x4A) || (g_ucCrcLane2 == 0xB5)))
    {
        if(g_bLTLane1FirstPass == _FALSE)
        {
            g_bLTLane1FirstPass = _TRUE;
            g_ucTP1Error |= 0x04;
        }
        else
        {
            g_bLTLane1FirstPass = _FALSE;
            g_ucTP1Error &= 0xFB;
        }
    }
    else
    {
        g_bLTLane1FirstPass = _FALSE;
        g_ucTP1Error |= 0x04;
    }

    if((g_ucTP1Error & 0x04) == 0x00)
    {
        g_ucLane01Status |= 0x10;
    }
    else
    {
        g_ucLane01Status &= 0xEF;

        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x04);
        CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucTrainingLaneSet);

        g_ucAdjustRequestL01 = (g_ucAdjustRequestL01 & 0x0F) | ((g_ucTrainingLaneSet & 0x03) << 4) | ((g_ucTrainingLaneSet & 0x18) << 3);

        if (((g_ucTrainingLaneSet & 0x04) == 0x00) && ((g_ucAdjustRequestL01 & 0x30) != 0x30))
        {
            g_ucAdjustRequestL01 = g_ucAdjustRequestL01 + 0x10;
        }
        else if(g_bLTLane1FirstPass == _TRUE)
        {
            g_bLTLane1FirstPass = _FALSE;
            g_ucLane01Status |= 0x10;
        }
    }
}

//--------------------------------------------------
// Description  : check Training pattern 1 lane2 status.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpTP1Lane2Check(void)
{
    // Adjust Offset to MAX.
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
    CScalerSetByteInt(_PB_DP_RESERVED_00_BA, 0xF0);

    // Select CRC lane2
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_AUX_RESERVE1_C6, 0x02);

    // check CRC for offset max.
    CScalerReadByteInt(_PC_READ_RESERVE1_CB, &g_ucCrcLane1);

    // adjust offset to min.
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
    CScalerSetByteInt(_PB_DP_RESERVED_00_BA, 0x00);

    // check CRC for offset min.
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerReadByteInt(_PC_READ_RESERVE1_CB, &g_ucCrcLane2);

    g_ucTP1Decode = g_ucTP1Decode1 | g_ucTP1Decode2;

    // Lane_2 D10.2 Check
    if(((g_ucTP1Decode & 0x02) == 0x00) && ((g_ucCrcLane1 == 0x4A) || (g_ucCrcLane1 == 0xB5)) && ((g_ucCrcLane2 == 0x4A) || (g_ucCrcLane2 == 0xB5)))
    {
        if(g_bLTLane2FirstPass == _FALSE)
        {
            g_bLTLane2FirstPass = _TRUE;
            g_ucTP1Error |= 0x02;
        }
        else
        {
            g_bLTLane2FirstPass = _FALSE;
            g_ucTP1Error &= 0xFD;
        }
    }
    else
    {
        g_bLTLane2FirstPass = _FALSE;
        g_ucTP1Error |= 0x02;
    }

    if((g_ucTP1Error & 0x02) == 0x00)
    {
        g_ucLane23Status |= 0x01;
    }
    else
    {
        g_ucLane23Status &= 0xFE;

        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x05);
        CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucTrainingLaneSet);

        g_ucAdjustRequestL23 = (g_ucAdjustRequestL23 & 0xF0) | (g_ucTrainingLaneSet & 0x03) | ((g_ucTrainingLaneSet & 0x18) >> 1);

        if(((g_ucTrainingLaneSet & 0x04) == 0x00) && ((g_ucAdjustRequestL23 & 0x03) != 0x03))
        {
            g_ucAdjustRequestL23 = g_ucAdjustRequestL23 + 0x01;
        }
        else if(g_bLTLane2FirstPass == _TRUE)
        {
            g_bLTLane2FirstPass = _FALSE;
            g_ucLane23Status |= 0x01;
        }
    }
}

//--------------------------------------------------
// Description  : check Training pattern 1 lane3 status.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpTP1Lane3Check(void)
{
    // Adjust Offset to MAX.
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
    CScalerSetByteInt(_PB_DP_RESERVED_00_BA, 0xF0);

    // Select CRC lane3
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_AUX_RESERVE1_C6, 0x03);

    // check CRC for offset max.
    CScalerReadByteInt(_PC_READ_RESERVE1_CB, &g_ucCrcLane1);

    // adjust offset to min.
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
    CScalerSetByteInt(_PB_DP_RESERVED_00_BA, 0x00);

    // check CRC for offset min.
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerReadByteInt(_PC_READ_RESERVE1_CB, &g_ucCrcLane2);

    g_ucTP1Decode = g_ucTP1Decode1 | g_ucTP1Decode2;

    // Lane_3 D10.2 Check
    if(((g_ucTP1Decode & 0x01) == 0x00) && ((g_ucCrcLane1 == 0x4A) || (g_ucCrcLane1 == 0xB5)) && ((g_ucCrcLane2 == 0x4A) || (g_ucCrcLane2 == 0xB5)))
    {
        if(g_bLTLane3FirstPass == _FALSE)
        {
            g_bLTLane3FirstPass = _TRUE;
            g_ucTP1Error |= 0x01;
        }
        else
        {
            g_bLTLane3FirstPass = _FALSE;
            g_ucTP1Error &= 0xFE;
        }
    }
    else
    {
        g_bLTLane3FirstPass = _FALSE;
        g_ucTP1Error |= 0x01;
    }

    if((g_ucTP1Error & 0x01) == 0x00)
    {
        g_ucLane23Status |= 0x10;
    }
    else
    {
        g_ucLane23Status &= 0xEF;

        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x06);
        CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucTrainingLaneSet);

        g_ucAdjustRequestL23 = (g_ucAdjustRequestL23 & 0x0F) | ((g_ucTrainingLaneSet & 0x03) << 4) | ((g_ucTrainingLaneSet & 0x18) << 3);

        if(((g_ucTrainingLaneSet & 0x04) == 0x00) && ((g_ucAdjustRequestL23 & 0x30) != 0x30))
        {
            g_ucAdjustRequestL23 = g_ucAdjustRequestL23 + 0x10;
        }
        else if(g_bLTLane3FirstPass == _TRUE)
        {
            g_bLTLane3FirstPass = _FALSE;
            g_ucLane23Status |= 0x10;
        }
    }
}

//--------------------------------------------------
// Description  : check Training pattern 2 1 Lane status.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpTP21LaneCheck(void)
{
    // Write Clear EQ-CRC twice : for hardware bug
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xb3);
    CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x8F);
    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xb3);
    CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x8F);

    // Read EQ_CRC Down Status
    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xb3);
    CScalerReadByteInt(_PC_DP_DATA_PORT_B4, &g_ucButInt);

    // Check Lane0 EQ-CRC
    /*
    if((g_ucButInt & 0x08) == 0x00)
    {
        g_ucLane01Status |= 0x06;
    }
    else
    */
    if(((g_ucButInt & 0x08) == 0x00) && (g_bLT2Lane0FirstPass == _FALSE))   // force to increase pre-emphasis
    {
        g_bLT2Lane0FirstPass = _TRUE;
    }
    else if(((g_ucButInt & 0x08) == 0x00) && (g_bLT2Lane0FirstPass == _TRUE))   // pre-emphasis already increased
    {
        g_bLT2Lane0FirstPass = _FALSE;
        g_ucLane01Status |= 0x06;
    }

    if(((g_ucButInt & 0x08) != 0x00) || (g_bLT2Lane0FirstPass == _TRUE))
    {
        g_ucLane01Status &= 0xF9;

        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
        CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucTrainingLaneSet);

        g_ucAdjustRequestL01 = (g_ucAdjustRequestL01 & 0xF0) | (g_ucTrainingLaneSet & 0x03) | ((g_ucTrainingLaneSet & 0x18) >> 1);

        // ( Not Max Pre-emphasis ) && ( (current level) + (Pre-emphasis level) < 4
        if(((g_ucTrainingLaneSet & 0x20) == 0x00) && (((g_ucAdjustRequestL01 & 0x03) + ((g_ucAdjustRequestL01 & 0x0C) >> 2)) < 4))
        {
            g_ucAdjustRequestL01 = g_ucAdjustRequestL01 + 0x04;
            if((g_ucButInt & 0x08) != 0x00)
            {
                g_bLT2Lane0FirstPass = _FALSE;
            }
        }
        else if(g_bLT2Lane0FirstPass == _TRUE)
        {
            g_bLT2Lane0FirstPass = _FALSE;
            g_ucLane01Status |= 0x06;
        }
        else
        {
            g_bLT2Lane0FirstPass = _FALSE;
        }
    }

    // Disable De-skew and then Enable de-skew : for hardware bug
    CScalerSetByteInt(_PC_MIN_DE_SKEW_A8, 0x00);
    CScalerSetByteInt(_PC_MIN_DE_SKEW_A8, 0x99);

    // for 1 lane it must be align
    g_ucAlignStatus = 0x81;
}

//--------------------------------------------------
// Description  : check Training pattern 2 2 Lane status.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpTP22LaneCheck(void)
{
    // Write Clear EQ-CRC twice : for hardware bug
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xb3);
    CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x8F);
    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xb3);
    CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x8F);

    // Read EQ_CRC Down Status
    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xb3);
    CScalerReadByteInt(_PC_DP_DATA_PORT_B4, &g_ucButInt);

    // Check Lane0 EQ-CRC
    /*
    if((g_ucButInt & 0x08) == 0x00)
    {
        g_ucLane01Status |= 0x06;
    }
    else
    */
    if(((g_ucButInt & 0x08) == 0x00) && (g_bLT2Lane0FirstPass == _FALSE))   // force to increase pre-emphasis
    {
        g_bLT2Lane0FirstPass = _TRUE;
    }
    else if(((g_ucButInt & 0x08) == 0x00) && (g_bLT2Lane0FirstPass == _TRUE))   // pre-emphasis already increased
    {
        g_bLT2Lane0FirstPass = _FALSE;
        g_ucLane01Status |= 0x06;
    }

    if(((g_ucButInt & 0x08) != 0x00) || (g_bLT2Lane0FirstPass == _TRUE))
    {
        g_ucLane01Status &= 0xF9;

        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
        CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucTrainingLaneSet);

        g_ucAdjustRequestL01 = (g_ucAdjustRequestL01 & 0xF0) | (g_ucTrainingLaneSet & 0x03) | ((g_ucTrainingLaneSet & 0x18) >> 1);

        // ( Not Max Pre-emphasis ) && ( (current level) + (Pre-emphasis level) < 4
        if(((g_ucTrainingLaneSet & 0x20) == 0x00) && (((g_ucAdjustRequestL01 & 0x03) + ((g_ucAdjustRequestL01 & 0x0C) >> 2)) < 4))
        {
            g_ucAdjustRequestL01 = g_ucAdjustRequestL01 + 0x04;
            if((g_ucButInt & 0x08) != 0x00)
            {
                g_bLT2Lane0FirstPass = _FALSE;
            }
        }
        else if(g_bLT2Lane0FirstPass == _TRUE)
        {
            g_bLT2Lane0FirstPass = _FALSE;
            g_ucLane01Status |= 0x06;
        }
        else
        {
            g_bLT2Lane0FirstPass = _FALSE;
        }
    }

    // Check Lane1 EQ-CRC
    /*
    if((g_ucButInt & 0x04) == 0x00)
    {
        g_ucLane01Status |= 0x60;
    }
    else
    */

    if(((g_ucButInt & 0x04) == 0x00) && (g_bLT2Lane1FirstPass == _FALSE))   // force to increase pre-emphasis
    {
        g_bLT2Lane1FirstPass = _TRUE;
    }
    else if(((g_ucButInt & 0x04) == 0x00) && (g_bLT2Lane1FirstPass == _TRUE))   // pre-emphasis already increased
    {
        g_bLT2Lane1FirstPass = _FALSE;
        g_ucLane01Status |= 0x60;
    }

    if(((g_ucButInt & 0x04) != 0x00) || (g_bLT2Lane1FirstPass == _TRUE))
    {
        g_ucLane01Status &= 0x9F;

        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x04);
        CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucTrainingLaneSet);

        g_ucAdjustRequestL01 = (g_ucAdjustRequestL01 & 0x0F) | ((g_ucTrainingLaneSet & 0x03) << 4) | ((g_ucTrainingLaneSet & 0x18) << 3);

        // ( Not Max Pre-emphasis ) && ( (current level) + (Pre-emphasis level) < 4
        if(((g_ucTrainingLaneSet & 0x20) == 0x00) && ((((g_ucAdjustRequestL01 & 0x30) >> 4) + ((g_ucAdjustRequestL01 & 0xC0) >> 6)) < 4))
        {
            g_ucAdjustRequestL01 = g_ucAdjustRequestL01 + 0x40;
            if((g_ucButInt & 0x04) != 0x00)
            {
                g_bLT2Lane1FirstPass = _FALSE;
            }
        }
        else if(g_bLT2Lane1FirstPass == _TRUE)
        {
            g_bLT2Lane1FirstPass = _FALSE;
            g_ucLane01Status |= 0x60;
        }
        else
        {
            g_bLT2Lane1FirstPass = _FALSE;
        }
    }

    if((g_ucLane01Status & 0x66) == 0x66)
    {
        // Disable De-skew and then Enable de-skew : for hardware bug
        CScalerSetByteInt(_PC_MIN_DE_SKEW_A8, 0x00);
        CScalerSetByteInt(_PC_MIN_DE_SKEW_A8, 0x99);

        // Read  Align status
        CScalerSetByteInt(_PC_MN_ERRC_A9, 0x03);
        CScalerReadByteInt(_PC_MN_ERRC_A9, &g_ucButInt);

        if((g_ucButInt & 0x01) == 0x00)
        {
            g_ucAlignStatus = 0x81;
        }
        else
        {
            g_ucAlignStatus = 0x80;
        }
    }
    else
    {
        g_ucAlignStatus = 0x80;
    }
}

//--------------------------------------------------
// Description  : check Training pattern 2 4 Lane status.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpTP24LaneCheck(void)
{
    // Write Clear EQ-CRC twice : for hardware bug
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xb3);
    CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x8F);
    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xb3);
    CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x8F);

    // Read EQ_CRC Down Status
    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xb3);
    CScalerReadByteInt(_PC_DP_DATA_PORT_B4, &g_ucButInt); //read EQ_Down Status

    // Check Lane0 EQ-CRC
    /*
    if((g_ucButInt & 0x08) == 0x00)
    {
        g_ucLane01Status |= 0x06;
    }
    else
    */
    if(((g_ucButInt & 0x08) == 0x00) && (g_bLT2Lane0FirstPass == _FALSE))   // force to increase pre-emphasis
    {
        g_bLT2Lane0FirstPass = _TRUE;
    }
    else if(((g_ucButInt & 0x08) == 0x00) && (g_bLT2Lane0FirstPass == _TRUE))   // pre-emphasis already increased
    {
        g_bLT2Lane0FirstPass = _FALSE;
        g_ucLane01Status |= 0x06;
    }

    if(((g_ucButInt & 0x08) != 0x00) || (g_bLT2Lane0FirstPass == _TRUE))
    {
        g_ucLane01Status &= 0xF9;

        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
        CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucTrainingLaneSet);

        g_ucAdjustRequestL01 = (g_ucAdjustRequestL01 & 0xF0) | (g_ucTrainingLaneSet & 0x03) | ((g_ucTrainingLaneSet & 0x18) >> 1);

        // ( Not Max Pre-emphasis ) && ( (current level) + (Pre-emphasis level) < 4
        if(((g_ucTrainingLaneSet & 0x20) == 0x00) && (((g_ucAdjustRequestL01 & 0x03) + ((g_ucAdjustRequestL01 & 0x0C) >> 2)) < 4))
        {
            g_ucAdjustRequestL01 = g_ucAdjustRequestL01 + 0x04;
            if((g_ucButInt & 0x08) != 0x00)
            {
                g_bLT2Lane0FirstPass = _FALSE;
            }
        }
        else if(g_bLT2Lane0FirstPass == _TRUE)
        {
            g_bLT2Lane0FirstPass = _FALSE;
            g_ucLane01Status |= 0x06;
        }
        else
        {
            g_bLT2Lane0FirstPass = _FALSE;
        }
    }

    // Check Lane1 EQ-CRC
    /*
    if((g_ucButInt & 0x04) == 0x00)
    {
        g_ucLane01Status |= 0x60;
    }
    else
    */
    if(((g_ucButInt & 0x04) == 0x00) && (g_bLT2Lane1FirstPass == _FALSE))   // force to increase pre-emphasis
    {
        g_bLT2Lane1FirstPass = _TRUE;
    }
    else if(((g_ucButInt & 0x04) == 0x00) && (g_bLT2Lane1FirstPass == _TRUE))   // pre-emphasis already increased
    {
        g_bLT2Lane1FirstPass = _FALSE;
        g_ucLane01Status |= 0x60;
    }

    if(((g_ucButInt & 0x04) != 0x00) || (g_bLT2Lane1FirstPass == _TRUE))
    {
        g_ucLane01Status &= 0x9F;

        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x04);
        CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucTrainingLaneSet);

        g_ucAdjustRequestL01 = (g_ucAdjustRequestL01 & 0x0F) | ((g_ucTrainingLaneSet & 0x03) << 4) | ((g_ucTrainingLaneSet & 0x18) << 3);

        // ( Not Max Pre-emphasis ) && ( (current level) + (Pre-emphasis level) < 4
        if ( ((g_ucTrainingLaneSet & 0x20) == 0x00) && ( ( ( (g_ucAdjustRequestL01 & 0x30) >> 4 ) + ( (g_ucAdjustRequestL01 & 0xC0) >> 6 ) ) < 4 ) )
        {
            g_ucAdjustRequestL01 = g_ucAdjustRequestL01 + 0x40;
            if((g_ucButInt & 0x04) != 0x00)
            {
                g_bLT2Lane1FirstPass = _FALSE;
            }
        }
        else if(g_bLT2Lane1FirstPass == _TRUE)
        {
            g_bLT2Lane1FirstPass = _FALSE;
            g_ucLane01Status |= 0x60;
        }
        else
        {
            g_bLT2Lane1FirstPass = _FALSE;
        }
    }

    // Check Lane2 EQ-CRC
    /*
    if((g_ucButInt & 0x02) == 0x00)
    {
        g_ucLane23Status |= 0x06;
    }
    else
    */
    if(((g_ucButInt & 0x02) == 0x00) && (g_bLT2Lane2FirstPass == _FALSE))   // force to increase pre-emphasis
    {
        g_bLT2Lane2FirstPass = _TRUE;
    }
    else if(((g_ucButInt & 0x02) == 0x00) && (g_bLT2Lane2FirstPass == _TRUE))   // pre-emphasis already increased
    {
        g_bLT2Lane2FirstPass = _FALSE;
        g_ucLane23Status |= 0x06;
    }

    if(((g_ucButInt & 0x02) != 0x00) || (g_bLT2Lane2FirstPass == _TRUE))
    {
        g_ucLane23Status &= 0xF9;

        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x05);
        CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucTrainingLaneSet);

        g_ucAdjustRequestL23 = (g_ucAdjustRequestL23 & 0xF0) | (g_ucTrainingLaneSet & 0x03) | ((g_ucTrainingLaneSet & 0x18) >> 1);

        // ( Not Max Pre-emphasis ) && ( (current level) + (Pre-emphasis level) < 4
        if ( ((g_ucTrainingLaneSet & 0x20) == 0x00) && ( ( (g_ucAdjustRequestL23 & 0x03) + ( (g_ucAdjustRequestL23 & 0x0C) >> 2 ) ) < 4 ) )
        {
            g_ucAdjustRequestL23 = g_ucAdjustRequestL23 + 0x04;
            if((g_ucButInt & 0x02) != 0x00)
            {
                g_bLT2Lane2FirstPass = _FALSE;
            }
        }
        else if(g_bLT2Lane2FirstPass == _TRUE)
        {
            g_bLT2Lane2FirstPass = _FALSE;
            g_ucLane23Status |= 0x06;
        }
        else
        {
            g_bLT2Lane2FirstPass = _FALSE;
        }
    }

    // Check Lane3 EQ-CRC
    /*
    if((g_ucButInt & 0x01) == 0x00)
    {
        g_ucLane23Status |= 0x60;
    }
    else
    */
    if(((g_ucButInt & 0x01) == 0x00) && (g_bLT2Lane3FirstPass == _FALSE))   // force to increase pre-emphasis
    {
        g_bLT2Lane3FirstPass = _TRUE;
    }
    else if(((g_ucButInt & 0x01) == 0x00) && (g_bLT2Lane3FirstPass == _TRUE))   // pre-emphasis already increased
    {
        g_bLT2Lane3FirstPass = _FALSE;
        g_ucLane23Status |= 0x60;
    }

    if(((g_ucButInt & 0x01) != 0x00) || (g_bLT2Lane3FirstPass == _TRUE))
    {
        g_ucLane23Status &= 0x9F;

        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
        CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x06);
        CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucTrainingLaneSet);

        g_ucAdjustRequestL23 = (g_ucAdjustRequestL23 & 0x0F) | ((g_ucTrainingLaneSet & 0x03) << 4) | ((g_ucTrainingLaneSet & 0x18) << 3);

        // ( Not Max Pre-emphasis ) && ( (current level) + (Pre-emphasis level) < 4
        if ( ((g_ucTrainingLaneSet & 0x20) == 0x00) && ( ( ( (g_ucAdjustRequestL23 & 0x30) >> 4 ) + ( (g_ucAdjustRequestL23 & 0xC0) >> 6 ) ) < 4 ) )
        {
            g_ucAdjustRequestL23 = g_ucAdjustRequestL23 + 0x40;
            if((g_ucButInt & 0x01) != 0x00)
            {
                g_bLT2Lane3FirstPass = _FALSE;
            }
        }
        else if(g_bLT2Lane3FirstPass == _TRUE)
        {
            g_bLT2Lane3FirstPass = _FALSE;
            g_ucLane23Status |= 0x60;
        }
        else
        {
            g_bLT2Lane3FirstPass = _FALSE;
        }
    }

    if(((g_ucLane01Status & 0x66) == 0x66) && ((g_ucLane23Status & 0x66) == 0x66))
    {
        // Disable De-skew and then Enable de-skew : for hardware bug
        CScalerSetByteInt(_PC_MIN_DE_SKEW_A8, 0x00);
        CScalerSetByteInt(_PC_MIN_DE_SKEW_A8, 0x99);
        CScalerSetByteInt(_PC_MN_ERRC_A9, 0x03);

        // Read Align Status
        CScalerReadByteInt(_PC_MN_ERRC_A9, &g_ucButInt);

        if((g_ucButInt & 0x01) == 0x00)
        {
            g_ucAlignStatus = 0x81;
        }
        else
        {
            g_ucAlignStatus = 0x80;
        }
    }
    else
    {
        g_ucAlignStatus = 0x80;
    }
}

//--------------------------------------------------
// Description  : check DP status at active state (PHY, Align, FIFO, display format)
// Input Value  : None
// Output Value : True --> PHY, Align, FIFO, display format failed mode reset mode , False --> do nothing
//--------------------------------------------------
bit CDpActiveCheckFail(void)
{
    if(g_ucDpPowerStatus == _DP_POWER_DOWN)
    {


        return _TRUE;
    }

    if((CDpIsDisplayPortPhyStable() == _FALSE))
    {
        g_ucPhyUnstableCount++;

        if(g_ucPhyUnstableCount > _DP_ERROR_TOLERANCE)
        {


            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {

        g_ucPhyUnstableCount = 0;

        if( ( CDpAlignCheck() == _FALSE ) )
        {
            g_ucMisAlignCount++;

            if(g_ucMisAlignCount > _DP_ERROR_TOLERANCE)
            {


                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
        else
        {
            g_ucMisAlignCount = 0;
        }
        if( CDpIsFifoUnderOverFlow() == _TRUE )
        {
            g_ucFifoFailCount++;

            if(g_ucFifoFailCount > _DP_ERROR_TOLERANCE)
            {


                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
        else
        {
            g_ucFifoFailCount = 0;
        }
        if( ( CDpDisplayFormatChange() == _TRUE) )
        {
            g_ucChangeDisplayCount++;

            if(g_ucChangeDisplayCount > 1)
            {


                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
        else
        {
           g_ucChangeDisplayCount = 0;
        }

        if( CDpHDCPStatus() == _FALSE)
        {


            return _TRUE;
        }
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : check DP status at No support state
// Input Value  : None
// Output Value : True -->  mode reset mode , False --> do nothing
//--------------------------------------------------
bit CDpNosupportCheck(void)
{
    /*
    if(bD0_CONNECT == _TRUE)
    */
#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
    if(CDpAuxPinCableConnect() == _TRUE) // DP cable detect
    {


        return _TRUE;
    }
#endif

    /*
    if(CDpMsaIsChange() == _TRUE)
    {
        return _TRUE;
    }
    */

    if(CSourceHandler())
    {
        if(CModeDetect())
        {
            if(stModeInfo.ModeCurr == _MODE_NOSIGNAL)
            {
                // do nothing
            }
#if(_FRC_SUPPORT == _ON)
            else if(stModeInfo.ModeCurr == _MODE_NOSUPPORT)
#else
            else if((stModeInfo.ModeCurr == _MODE_NOSUPPORT) || (stModeInfo.IVFreq > _PANEL_MAX_FRAME_RATE))
#endif
            {
                // do nothing
            }
            else
            {


                return _TRUE;
            }
        }
    }
    else if(g_bDpDisplayPass == _FALSE)
    {


        return _TRUE;;
    }

    if(CDpMsaIsChange() == _TRUE)
    {


        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Display port Mac reset (DPCD table Reset)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDpHDCPReset(void)
{
    CScalerPageSelect(_PAGEC);

    CScalerSetByte(_PC_AUX_MODE_SET_D0, 0xE1);

    CScalerPageSelect(_PAGEC);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x06);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x80);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x0c);
    CScalerSetByte(_PC_DPCD_DATA_PORT_L_C4, 0x00);

    CScalerSetByte(_PC_AUX_MODE_SET_D0, 0xE3);
}

#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
//--------------------------------------------------
// Description  : Detect DP cable connect by Pin15(AuxP) and Pin17(AuxN)
// Input Value  : None
// Output Value : True --> DP cable disconnect, False --> DP cable connect
//--------------------------------------------------
bit CDpAuxPinCableConnect(void)
{
    if((bDP_Pin15_CONNECT == _TRUE) && (bDP_Pin17_CONNECT == _FALSE)) // Cable Disconnect
    {
        return _TRUE;
    }
    else // Cable Connect
    {
        return _FALSE;
    }
}
#endif // End of #if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)


//--------------------------------------------------
// Description  : DP Link Status Check (CDR, SYMBOL LOCK, EQ-CRC)
// Input Value  : None
// Output Value : True --> Link Status ok, False --> Link Status fail
//--------------------------------------------------
bit CDpLinkStatusCheck(void)
{
    CScalerPageSelect(_PAGEC);

    // Read Lane count
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x01);
    CScalerRead(_PC_DPCD_DATA_PORT_L_C4, 1, &pData[0], _NON_AUTOINC);

    // Read Lane01 status
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x02);
    CScalerRead(_PC_DPCD_DATA_PORT_L_C4, 1, &pData[1], _NON_AUTOINC);

    // Read lane23 status
    CScalerSetByte(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
    CScalerRead(_PC_DPCD_DATA_PORT_L_C4, 1, &pData[2], _NON_AUTOINC);

    if(((pData[0] & 0x07) == 0x01) && ((pData[1] & 0x07) == 0x07))
    {
        return _TRUE;
    }
    else if(((pData[0] & 0x07) == 0x02) && ((pData[1] & 0x77) == 0x77))
    {
        return _TRUE;
    }
    else if(((pData[0] & 0x07) == 0x04) && ((pData[1] & 0x77) == 0x77) && ((pData[2] & 0x77) == 0x77))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

#endif // End of #if(_DP_SUPPORT == _ON)

#endif // End of #if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)
