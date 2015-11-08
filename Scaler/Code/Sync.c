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
// ID Code      : Sync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYNC__

#include "Common\Header\Include.h"

#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
//--------------------------------------------------
// Description  : PHY set
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSyncScanInputPortResetPhy(void)
{
    CScalerPageSelect(_PAGEB);

    // FLD Reset
#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    if(g_ucIDCode == 0x0E) //  ver.F
    {
        CScalerSetBit(_PB_DP_FLD_08_AC, ~_BIT3, _BIT3);
        CScalerSetBit(_PB_DP_FLD_08_AC, ~_BIT3, 0x00);
    }
    else
    {
        CScalerSetBit(_PB_DP_FLD_08_AC, ~_BIT2, 0x00);
    }

#elif(_SCALER_TYPE == _RTD2472D)
    if(g_ucIDCode == 0x04) // ver.D
    {
        CScalerSetBit(_PB_DP_FLD_08_AC, ~_BIT3, _BIT3);
        CScalerSetBit(_PB_DP_FLD_08_AC, ~_BIT3, 0x00);
    }
    else
    {
        CScalerSetBit(_PB_DP_FLD_08_AC, ~_BIT2, 0x00);
    }
#else
     // do nothing
#endif

    CScalerSetBit(_PB_DP_AUX_00_B3, ~_BIT7, _BIT7);

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        if(g_ucIDCode >= 0x0F) //  ver.G
        {
            CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0xCd);
            CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x4d);
        }
        else
        {
            CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x8d);
            CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x0d);
        }
#elif(_SCALER_TYPE == _RTD2472D)

        CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x8d);
        CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x0d);
#else
        CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x8d);
        CScalerSetByte(_PB_DP_OOBS_RXAMP_B0, 0x0d);
#endif

}

//--------------------------------------------------
// Description  : Scan DVI input port to obtain if the signal is available
// Input Value  : None
// Output Value : Return _TRUE if the signal is available
//--------------------------------------------------
bit CSyncScanInputPortDVI(void)
{
    BYTE cnt0 = 0;

    // HDMI/DVI function enable
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_Z0CC2_AC, ~_BIT6, _BIT6);

#if(_SCALER_TYPE == _RTD2545LR)
    CSyncInputPort2DSwitch();
#endif

    if(GET_TMDS_INITIAL() == _TRUE)
    {
        // Ignore AVmute
        CScalerPageSelect(_PAGE2);
        CScalerSetBit(_P2_TMDS_RPS_AE, ~_BIT7, _BIT7);

        CPowerADCAPLLOff();

        // Set Measure Source to DVI/HDMI
        CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), 0x00);

        // Enable DE-Only Mode

        // Select HDMI Port
        CScalerPageSelect(_PAGEC);
        CScalerSetBit(_PC_DP_CTL_A1, ~_BIT5, _BIT5);

        // HDMI/DP selector
        CScalerPageSelect(_PAGEB);
        CScalerSetByte(_PB_DIG00_E0, 0xD0);

        // Z0 turn on
        CScalerSetByte(_PB_DP_Z0_CALIBRATION_B6, 0xf4);

        // Enable OOBS manual mode
        CScalerSetByte(_PB_DP_AUX_00_B3, 0x92);

        g_bHDMIHDCPFlag = 0;

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))
        // do nothing
#else
        CLR_TMDS_INITIAL();
#endif
    }

    if(ucCurrState == _SLEEP_STATE)
    {

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))
        CLR_TMDS_INITIAL();
#else
        // do nothing
#endif

        if(CSyncTMDSWakeUpDetect() == _TRUE)
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))

    // Solve OSD respond time in sleep, increase SearchTimes
    if(g_ucSearchTimes >= 3)
    {
        g_ucSearchTimes = g_ucSearchTimes - 3;
    }
    else
    {
        g_ucSearchTimes = 1;
    }

    // Check stable freq
    if(CSyncPhyFreqForRightCount(_TMDS_Freq_Right_Count, 1) == _TRUE)
    {
        if(GET_TMDS_INITIAL())
        {
            if((abs(g_usDVITMDSFreq - g_usTMDSFreq1)) <= ((g_usTMDSFreq / 100) + 1))
            {
                g_bNoResetPhyFlag = _TRUE;
            }
            else
            {
                g_bNoResetPhyFlag = _FALSE;
            }
        }
        else
        {
            g_bNoResetPhyFlag = _FALSE;
        }

        CLR_TMDS_INITIAL();
        g_usDVITMDSFreq = g_usTMDSFreq1;
        g_usTMDSFreq = g_usTMDSFreq1;
    }
    else
    {
        // Format Detect: Manual DVI
        CScalerPageSelect(_PAGE2);
        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_SCR_00, ~(_BIT3 | _BIT2), _BIT3);
        g_bNoResetPhyFlag = _FALSE;
        CLR_TMDS_INITIAL();
        return _FALSE;
    }

    // Fix SearchTimes when finding stable signal
    if((g_bHDMISearchTimesResetFlag == 1) && (g_ucSearchTimes <= 50))
    {
        g_ucSearchTimes = 50;
        g_bHDMISearchTimesResetFlag = 0;
    }

    if(g_bNoResetPhyFlag == _TRUE)
    {
        g_bNoResetPhyFlag = _FALSE;
    }
    else
    {
        // Set PHY parameters
        CSyncModeSetPhy();

        // Set Manual Mode
        CScalerPageSelect(_PAGEB);
        CScalerSetByte(_PB_DP_RXMISC_02_AF, 0xC7);

        // Reset PHY parameters
        CSyncScanInputPortResetPhy();

        // Wait for CDR ready
        CTimerDelayXms(10);
        CScalerPageSelect(_PAGEB);
        CScalerSetByte(_PB_DP_FLD_04_A8, 0xF0);
        CScalerRead(_PB_DP_FLD_04_A8, 1, pData, _NON_AUTOINC);

        if((pData[0] & 0xF0) != 0xF0)
        {
            return _FALSE;
        }
    }

#elif(_SCALER_TYPE == _RTD2545LR)

    CScalerPageSelect(_PAGEB);

    CScalerSetByte(_PB_DP_RXMISC_02_AF, 0x87);
    CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x16);
    CScalerSetByte(_PB_DP_AUX_00_B3, 0x92);
    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x7f);
    CScalerSetByte(_PB_DP_FLD_05_A9, 0xc2);
    CScalerSetByte(_PB_DP_FLD_06_AA, 0x85);
    CScalerSetByte(_PB_DP_FLD_07_AB, 0x0a);

    CSyncScanInputPortResetPhy();
    CSyncModeSetPhy();

    CScalerSetByte(_PB_DP_RXMISC_02_AF, 0xC7);

    CSyncScanInputPortResetPhy();
    CTimerDelayXms(100);

    if(ucCurrState == _SLEEP_STATE)
    {
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);
    }
    else
    {
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x7f);
    }

#endif  // End of #if(_SCALER_TYPE == _RTD2472D)

    // HDMI/DVI detect: Auto mode
    CScalerPageSelect(_PAGE2);

    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_SCR_00, ~(_BIT3 | _BIT1 | _BIT0), _BIT1);

    CTimerDelayXms(200); // for VG870: 200ms

    // Detect HDMI or DVI
    if(CHdmiFormatDetect()) // HDMI
    {
        CScalerPageSelect(_PAGE2);
        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, 0x02, ~_BIT3, _BIT3);
        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, 0x02, ~_BIT1, 0x00);
        CTimerDelayXms(5);
        CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x02);
        CScalerRead(_P2_HDMI_DATA_PORT_CA, 1, &pData[0], _NON_AUTOINC);

        if((pData[0] & 0x02) == 0x02)
        {
            return _FALSE;
        }

        // DE-only mode disable
        CScalerPageSelect(_PAGE2);
        CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~_BIT7, 0x00);

        // Set HDMI source
        SET_INPUTSOURCE_TYPE(_SOURCE_HDMI);
    }
    else                    //DVI
    {
        if((g_usTMDSFreq >= 20) && (g_usTMDSFreq <= 165))
        {
            // DE-only mode enable
            CScalerPageSelect(_PAGE2);
            CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~_BIT7, _BIT7);
        }
        else
        {
            // DE-only mode disable
            CScalerPageSelect(_PAGE2);
            CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~_BIT7, 0x00);
        }

        // Set DVI source
        SET_INPUTSOURCE_TYPE(_SOURCE_DVI);
    }

    // RGBHV detect
    for(cnt0 = 0; cnt0 < 2; cnt0++)
    {
        CScalerPageSelect(_PAGE2);
        CScalerSetByte(_P2_TMDS_CTRL_A4, 0xf8);

        CTimerWaitForEvent(_EVENT_IVS);
        CTimerWaitForEvent(_EVENT_IVS);

        CScalerRead(_P2_TMDS_CTRL_A4, 1, pData, _NON_AUTOINC);

        if(GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
        {
            pData[0] = ((pData[0] & 0xf8) == 0xf8) ? _TRUE : _FALSE;
        }
        else
        {
            pData[0] = ((pData[0] & 0xe0) == 0xe0) ? _TRUE : _FALSE;
        }

        if(pData[0] == _TRUE)
        {
#if(_HDMI_SUPPORT == _ON)
            if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT))
            {
                if(CHdmiVideoSetting() == _FALSE)
                {
                    return _FALSE;
                }
            }
            else
            {
                CHdmiVideoSetting();

#if(_HDMI_FROM_DVI_CONNECT == _OFF)
                if(CHdmiFormatDetect())
                {
                    return _FALSE;
                }
#endif
            }
#else
            if((GET_INPUTPORT_TYPE(g_ucSearchIndex) != _D0_HDMI_PORT) && (GET_INPUTPORT_TYPE(g_ucSearchIndex) != _D1_HDMI_PORT))
            {

#if(_HDMI_FROM_DVI_CONNECT == _OFF)
                if(CHdmiFormatDetect())
                {
                    return _FALSE;
                }
#endif
            }
#endif  // End of #if(_HDMI_SUPPORT == _ON)

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
#if((_HDMI_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
    {
        CHdmiAudioInitialSetting();
    }
#endif
#endif

                CPowerTMDSOn();
                return _TRUE;
        }
    } // End of for(cnt0=0; cnt0<2; cnt0++)

    return _FALSE;

}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Scan DP input port to obtain if the signal is available
// Input Value  : None
// Output Value : Return _TRUE if the signal is available
//--------------------------------------------------
bit CSyncScanInputPortDP(void)
{
#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)

    if(ucCurrState == _SEARCH_STATE)
    {
        CDpCableConnect();
    }
#endif

    if(g_ucDpPowerStatus == _DP_POWER_DOWN)
    {
        return _FALSE;
    }

    if(ucCurrState == _NOSUPPORT_STATE)
    {
        g_ucSearchTimes += 1;
    }

    if(GET_TMDS_INITIAL() == _TRUE)
    {
        CPowerADCAPLLOff();

        CScalerSetByte(_PAGE_SELECT_9F, _PAGEB);

#if (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x02);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x06);
#endif

#if(_HDCP_SUPPORT == _ON)
        CScalerPageSelect(_PAGE2);
        if(GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT)
        {
            CScalerSetBit(_P2_HDCP_PORT_CTRL_C2, ~_BIT1, (_DDC_CHANNEL_FOR_D0 << 1));
        }
        else if(GET_INPUT_PORT(g_ucSearchIndex) == _D1_INPUT_PORT)
        {
            CScalerSetBit(_P2_HDCP_PORT_CTRL_C2, ~_BIT1, (_DDC_CHANNEL_FOR_D1 << 1));
        }
        CScalerSetBit(_P2_HDCP_CTRL_C0, ~_BIT0, _BIT0);
#endif

        CLR_TMDS_INITIAL();
    }

    if((GET_DPHOTPLUG()) && (g_ucDpPowerStatus != _DP_POWER_DOWN))
    {
#if ((_HPD_TYPE == _HPD_SHORT) || (_HPD_TYPE == _HPD_BOTH))
        if(g_ucSearchTimes == 30)
        {

            if(g_bDpCPIRQ == _TRUE)
            {
                if(g_ucDisplayPortLtPreStatus == _TRAINING_PATTERN_NONE)
                {
                    CDpCPIRQ(2);
                }
            }
            else
            {
                if(g_ucDisplayPortLtPreStatus == _TRAINING_PATTERN_NONE)
                {


                    CLR_DPHOTPLUG();
                    g_bDpCPIRQ = _FALSE;
                    CDpShortHotPlugProc(2);  // (1):0.256us , (2):1.262us
                }
            }
        }

        else if(g_ucSearchTimes == 25)
        {
            if(g_bDpCPIRQ == _TRUE)
            {


                CLR_DPHOTPLUG();
                g_bDpCPIRQ = _FALSE;
                g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_NONE;
                CDpShortHotPlugProc(20);
            }
        }

#endif // End of #if ((_HPD_TYPE == _HPD_SHORT) || (_HPD_TYPE == _HPD_BOTH))
    }


    while (g_ucDisplayPortLtPreStatus == _TRAINING_PATTERN_END)
    {
        g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_NONE;

        if(g_bFakeTPEndPass == _TRUE)
        {


            CDpFastlinktrainSet();
            g_bDpSearchTimesReset = 1;
        }

        if(g_bDpSearchTimesReset == 1)
        {


            g_bDpSearchTimesReset = 0;
            g_ucSearchTimes = 15;
        }

        g_bFakeTP1Pass = 0;
        g_bFakeTP2Pass = 0;

        if(CDpStartupSetting() == _FALSE)
        {
           return _FALSE;
        }

        CDpAdjustVsyncDelayCount();

        if(CDpIsFifoUnderOverFlow() == _FALSE)
        {


            CLR_DPHOTPLUG();
            g_bDpCPIRQ = _FALSE;
            CPowerTMDSOn();
            SET_INPUTSOURCE_TYPE(_SOURCE_DP);
            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_NONE;
            return _TRUE;
        }
        else
        {

            g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_END;
            return _FALSE;
        }

    }   // End of while (g_ucDisplayPortLtPreStatus == _TRAINING_PATTERN_END)

    if(ucCurrState != _NOSUPPORT_STATE)
    {
        CTimerDelayXms(25);
    }

    return _FALSE;
}
#endif //End of #if(_DP_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Set Phy Frequency
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSyncModeSetPhy(void)
{
#if(_SCALER_TYPE == _RTD2472D)
    CScalerPageSelect(_PAGEB);
    CScalerSetBit(_PB_DP_FLD_08_AC, ~_BIT1, 0x00);

    if((g_usTMDSFreq > 20) && (g_usTMDSFreq < 50)) // 25~50MHz
    {
        if(g_ucIDCode >= 0x05)  // ver. E
        {
            // 6048 New Setting
            CScalerSetByte(_PB_DP_CDR_01_A1, 0x86);
            CScalerSetByte(_PB_DP_CDR_02_A2, 0x3D);
            CScalerSetByte(_PB_DP_CDR_03_A3, 0x94);
            CScalerSetBit(_PB_DP_FLD_08_AC, ~_BIT1, _BIT1);
        }
        else // ver. C/D
        {
            CScalerSetByte(_PB_DP_CDR_01_A1, 0x82);
            CScalerSetByte(_PB_DP_CDR_02_A2, 0x39);
            CScalerSetByte(_PB_DP_CDR_03_A3, 0x94);
        }

        CScalerSetByte(_PB_DP_FLD_09_AD, 0x2F);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF1);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
    }
    else if((g_usTMDSFreq >= 50) && (g_usTMDSFreq < 100)) // 55~100MHz
    {
        CScalerSetByte(_PB_DP_CDR_01_A1, 0x42);
        CScalerSetByte(_PB_DP_CDR_02_A2, 0x5a);
        CScalerSetByte(_PB_DP_CDR_03_A3, 0x94);
        CScalerSetByte(_PB_DP_FLD_09_AD, 0x2F);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF1);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
    }
    else if((g_usTMDSFreq >= 100) && (g_usTMDSFreq < 150)) // 100~150MHz
    {
        CScalerSetByte(_PB_DP_CDR_01_A1, 0x72);
        CScalerSetByte(_PB_DP_CDR_02_A2, 0x21);
        CScalerSetByte(_PB_DP_CDR_03_A3, 0x8c);
        CScalerSetByte(_PB_DP_FLD_09_AD, 0x07);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
    }
    else if((g_usTMDSFreq >= 150) && (g_usTMDSFreq < 200)) // 150~200MHz
    {
        CScalerSetByte(_PB_DP_CDR_01_A1, 0x72);
        CScalerSetByte(_PB_DP_CDR_02_A2, 0x21);
        CScalerSetByte(_PB_DP_CDR_03_A3, 0x8c);
        CScalerSetByte(_PB_DP_FLD_09_AD, 0x07);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
    }
    else if((g_usTMDSFreq >= 200) && (g_usTMDSFreq < 340)) // 200~340MHz
    {
        CScalerSetByte(_PB_DP_CDR_01_A1, 0x32);
        CScalerSetByte(_PB_DP_CDR_02_A2, 0x21);
        CScalerSetByte(_PB_DP_CDR_03_A3, 0x8c);
        CScalerSetByte(_PB_DP_FLD_09_AD, 0x07);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
    }

#elif((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

    CScalerPageSelect(_PAGEB);

    CScalerSetBit(_PB_DP_FLD_08_AC, ~_BIT1, 0x00);

    if((g_usTMDSFreq > 20) && (g_usTMDSFreq < 50)) // 25~50MHz
    {
        if(g_ucIDCode >= 0x0F) // >= ver.G
        {
            // 6049 New Setting
            CScalerSetByte(_PB_DP_CDR_01_A1, 0x86);
            CScalerSetByte(_PB_DP_CDR_02_A2, 0x3D);
            CScalerSetByte(_PB_DP_CDR_03_A3, 0x94);
            CScalerSetBit(_PB_DP_FLD_08_AC, ~_BIT1, _BIT1);
        }
        else
        {
            CScalerSetByte(_PB_DP_CDR_01_A1, 0x82);
            CScalerSetByte(_PB_DP_CDR_02_A2, 0x39);
            CScalerSetByte(_PB_DP_CDR_03_A3, 0x94);
        }

        CScalerSetByte(_PB_DP_FLD_09_AD, 0x2F);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF1);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
        CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x76);
    }
    else if((g_usTMDSFreq >= 50) && (g_usTMDSFreq < 100)) // 50~67.5MHz
    {
        CScalerSetByte(_PB_DP_CDR_01_A1, 0x42);
        CScalerSetByte(_PB_DP_CDR_02_A2, 0xba);
        CScalerSetByte(_PB_DP_CDR_03_A3, 0x94);
        CScalerSetByte(_PB_DP_FLD_09_AD, 0x2F);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF1);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
        CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x76);
    }
    else if((g_usTMDSFreq >= 100) && (g_usTMDSFreq < 150)) // 100~150MHz
    {
        CScalerSetByte(_PB_DP_CDR_01_A1, 0x72);
        CScalerSetByte(_PB_DP_CDR_02_A2, 0x21);//0x51
        CScalerSetByte(_PB_DP_CDR_03_A3, 0x8c);
        CScalerSetByte(_PB_DP_FLD_09_AD, 0x07);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
        CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x76);
    }
    else if((g_usTMDSFreq >= 150) && (g_usTMDSFreq < 200)) // 150~200MHz
    {
        CScalerSetByte(_PB_DP_CDR_01_A1, 0x72);
        CScalerSetByte(_PB_DP_CDR_02_A2, 0x21);//0x51
        CScalerSetByte(_PB_DP_CDR_03_A3, 0x8c);
        CScalerSetByte(_PB_DP_FLD_09_AD, 0x07);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
        CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x76);
    }
    else if((g_usTMDSFreq >= 200) && (g_usTMDSFreq < 340)) // 200~340MHz
    {
        CScalerSetByte(_PB_DP_CDR_01_A1, 0x32);
        CScalerSetByte(_PB_DP_CDR_02_A2, 0x21);
        CScalerSetByte(_PB_DP_CDR_03_A3, 0x8c);
        CScalerSetByte(_PB_DP_FLD_09_AD, 0x07);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
        CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x7E); // enable boost2
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xf4); //more HPF
    }

#elif(_SCALER_TYPE == _RTD2545LR)

    CScalerPageSelect(_PAGEB);
    CScalerSetBit(_PB_DP_FLD_08_AC, ~_BIT1, 0x00);

    CScalerRead(_PB_DP_FLD_03_A7, 1, pData, _NON_AUTOINC);
    pData[0] &= 0xf0;

    if(pData[0] == 0x80) // 25~50MHz
    {
        if(g_ucIDCode >= 0x55) // >= ver.E
        {
            // 6050 New Setting
            CScalerSetByte(_PB_DP_CDR_01_A1, 0x86);
            CScalerSetByte(_PB_DP_CDR_02_A2, 0x3D);
            CScalerSetByte(_PB_DP_CDR_03_A3, 0x94);
            CScalerSetBit(_PB_DP_FLD_08_AC, ~_BIT1, _BIT1);
        }
        else
        {
            CScalerSetByte(_PB_DP_CDR_01_A1, 0x82);
            CScalerSetByte(_PB_DP_CDR_02_A2, 0x39);
            CScalerSetByte(_PB_DP_CDR_03_A3, 0x94);
        }

        CScalerSetByte(_PB_DP_FLD_09_AD, 0x2F);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF1);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
        CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x76);
    }
    else if(pData[0] == 0xb0) // 50~100MHz
    {
        CScalerSetByte(_PB_DP_FLD_05_A9, 0x2c);
        CScalerSetByte(_PB_DP_FLD_06_AA, 0x4F);
        CScalerSetByte(_PB_DP_FLD_07_AB, 0xb2);
        CSyncScanInputPortResetPhy();

        CScalerRead(_PB_DP_FLD_03_A7, 1, pData, _NON_AUTOINC);
        pData[0] &= 0xf0;
        if(pData[0] == 0xb0) //50~67.5MHz
        {
            CScalerSetByte(_PB_DP_CDR_01_A1, 0x40);
            CScalerSetByte(_PB_DP_CDR_02_A2, 0xba);
            CScalerSetByte(_PB_DP_CDR_03_A3, 0x94);
            CScalerSetByte(_PB_DP_FLD_09_AD, 0x2F);
            CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF1);
            CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
            CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x76);
        }
        else if(pData[0] == 0x70) //67.5~100MHz
        {
            CScalerSetByte(_PB_DP_CDR_01_A1, 0x40);
            CScalerSetByte(_PB_DP_CDR_02_A2, 0xba);
            CScalerSetByte(_PB_DP_CDR_03_A3, 0x94);
            CScalerSetByte(_PB_DP_FLD_09_AD, 0x2F);
            CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF1);
            CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
            CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x76);
        }
    }
    else if(pData[0] == 0x70) // 100~200MHz
    {
        CScalerSetByte(_PB_DP_FLD_05_A9, 0x2c);
        CScalerSetByte(_PB_DP_FLD_06_AA, 0x59);
        CScalerSetByte(_PB_DP_FLD_07_AB, 0xb2);

        CSyncScanInputPortResetPhy();

        CScalerRead(_PB_DP_FLD_03_A7, 1, pData, _NON_AUTOINC);
        pData[0] &= 0xf0;

        if(pData[0] == 0x70) //100~150MHz
        {
            CScalerSetByte(_PB_DP_CDR_01_A1, 0x70);
            CScalerSetByte(_PB_DP_CDR_02_A2, 0x21);
            CScalerSetByte(_PB_DP_CDR_03_A3, 0x8c);
            CScalerSetByte(_PB_DP_FLD_09_AD, 0x07);
            CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
            CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
            CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x76);
        }
        else if(pData[0] == 0x30) //150~200MHz
        {
            CScalerSetByte(_PB_DP_CDR_01_A1, 0x70);
            CScalerSetByte(_PB_DP_CDR_02_A2, 0x21);
            CScalerSetByte(_PB_DP_CDR_03_A3, 0x8c);
            CScalerSetByte(_PB_DP_FLD_09_AD, 0x07);
            CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
            CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
            CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x76);
        }
    }
    else if(pData[0] == 0x30) // 200~340MHz
    {
        CScalerSetByte(_PB_DP_CDR_01_A1, 0x30);
        CScalerSetByte(_PB_DP_CDR_02_A2, 0x21);
        CScalerSetByte(_PB_DP_CDR_03_A3, 0x8c);
        CScalerSetByte(_PB_DP_FLD_09_AD, 0x07);
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
        CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
        CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x7E); // enable boost2
        CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xf4); //more HPF
    }

#endif  // End of #if(_SCALER_TYPE == _RTD2472D)

    CScalerPageSelect(_PAGEB);
    CScalerSetByte(_PB_DP_RXMISC_02_AF, 0xC7);
}

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))
//--------------------------------------------------
// Description  : Measure the Phy Frequency
// Input Value  : None
// Output Value : Return Phy Frequency
//--------------------------------------------------
WORD CSyncMeasurePhyFreq(bit bFlag)
{
    WORD usTempreadfreq = 0;

    CScalerPageSelect(_PAGEB);

    if(bFlag == 1)
    {
        // CMU_en & Rx_en
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x7F);
    }
    else
    {
        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);
    }


#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))

    CSyncInputPort2DSwitch();
#endif

    CScalerPageSelect(_PAGE2);

    // Address auto increase enable
    CScalerSetByte(_P2_HDMI_APC_C8, 0x01);

    // Detection clock source select to source clock
    CScalerSetBit(_P2_MAC_MEASURE_FREQ_AB, ~_BIT7, _BIT7);

    // Restart measure freq number
    CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x28);
    CScalerSetByte(_P2_HDMI_DATA_PORT_CA, 0x08);

    CTimerDelayXms(1);

    // Read freq number result
    CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x28);
    CScalerRead(_P2_HDMI_DATA_PORT_CA, 1, &pData[0], _NON_AUTOINC);

    CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x29);
    CScalerRead(_P2_HDMI_DATA_PORT_CA, 1, &pData[1], _NON_AUTOINC);

    // Calculate freq.
    usTempreadfreq = (((WORD)(pData[0] & 0x07) << 8) | pData[1]);

    usTempreadfreq = (WORD)((((DWORD)_RTD_XTAL * 1024) / ((DWORD)usTempreadfreq * 1000)) & 0xffff);

    // Address auto increase disable
    CScalerSetByte(_P2_HDMI_APC_C8, 0x00);

    CScalerSetBit(_P2_MAC_MEASURE_FREQ_AB, ~_BIT7, 0x00);

    return usTempreadfreq;

}

//--------------------------------------------------
// Description  : Count the Right Phy Frequency
// Input Value  : None
// Output Value : Return the right count
//--------------------------------------------------
bit CSyncPhyFreqForRightCount(BYTE ucCountNum, BYTE ucDelayTime)
{

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))


    BYTE ucCountData = 0, cnt0 = 0;

    if(ucCurrState == _SLEEP_STATE)
    {
        g_usTMDSFreq0 = CSyncMeasurePhyFreq(0);
    }
    else
    {
        g_usTMDSFreq0 = CSyncMeasurePhyFreq(1);
    }

    // Block no support freq
    if ((g_usTMDSFreq0 < 20) || (g_usTMDSFreq0 > 340))
    {
        return _FALSE;
    }

    for(cnt0 = 0; cnt0 < ucCountNum; cnt0++)
    {
        CTimerDelayXms(ucDelayTime);

        if(ucCurrState == _SLEEP_STATE)
        {
            g_usTMDSFreq1 = CSyncMeasurePhyFreq(0);
        }
        else
        {
            g_usTMDSFreq1 = CSyncMeasurePhyFreq(1);
        }

        if(abs((g_usTMDSFreq0 - g_usTMDSFreq1)) <= ((g_usTMDSFreq0 / 100) + 1))
        {
            ucCountData++;
        }
    }

    if(ucCountData == ucCountNum)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }

#else  // Else of #if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))

    BYTE ucCountData = 0, cnt0 = 0;
    WORD usTempfreq0 = 0, usTempfreq1 = 0;

    usTempfreq0 = CSyncMeasurePhyFreq(1);

    for(cnt0 = 0; cnt0 < ucCountNum; cnt0++)
    {
        CTimerDelayXms(ucDelayTime);
        usTempfreq1 = CSyncMeasurePhyFreq(1);

        if (abs((usTempfreq0 - usTempfreq1)) <= ((usTempfreq0 / 100) + 1))
        {
            ucCountData++;
        }
    }

    if(ucCountData == ucCountNum)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }

#endif
}


//--------------------------------------------------
// Description  : Power off Phy Z0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSyncPhyZ0PowerOff(void)
{
    CScalerPageSelect(_PAGEB);
    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);
}

bit CSyncCheckTMDSFreq(void)
{
    WORD usPresentReadFreq = 0;

    // CMU_en & Rx_en
    CScalerPageSelect(_PAGEB);
    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x7F);

    CScalerPageSelect(_PAGE2);

    // Address auto increase
    CScalerSetByte(_P2_HDMI_APC_C8, 0x01);

    // Detection clock source select to source clock
    CScalerSetBit(_P2_MAC_MEASURE_FREQ_AB, ~_BIT7, _BIT7);

    // Restart measure freq number
    CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x28);
    CScalerSetByte(_P2_HDMI_DATA_PORT_CA, 0x08);

    CTimerDelayXms(1);

    // Read freq number result
    CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x28);
    CScalerRead(_P2_HDMI_DATA_PORT_CA, 1, &pData[0], _NON_AUTOINC);

    CScalerSetByte(_P2_HDMI_ADDR_PORT_C9, 0x29);
    CScalerRead(_P2_HDMI_DATA_PORT_CA, 1, &pData[1], _NON_AUTOINC);

    // Calculate freq.
    usPresentReadFreq = (((WORD)(pData[0] & 0x07) << 8) | pData[1]);

    usPresentReadFreq = (WORD)((((DWORD)_RTD_XTAL * 1024) / ((DWORD)usPresentReadFreq * 1000)) & 0xffff);

    // Address auto increase disable
    CScalerSetByte(_P2_HDMI_APC_C8, 0x00);

    CScalerSetBit(_P2_MAC_MEASURE_FREQ_AB, ~_BIT7, 0x00);

    // Check Freq. with the one in sync.c
    if((abs(g_usTMDSFreq -  usPresentReadFreq)) <= ((g_usTMDSFreq / 100) + 1))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif // End of #if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

//--------------------------------------------------
// Description  : Input Port DVI/HDMI Wake Up Detect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit CSyncTMDSWakeUpDetect(void)
{
#if(_SCALER_TYPE == _RTD2545LR)
    BYTE cnt0 = 0, cnt1 = 0;
#endif

    BYTE cnt2 = 0;

    CScalerPageSelect(_PAGEB);
    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);

    CSyncInputPort2DSwitch();

    CTimerDelayXms(5);

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))

    CScalerPageSelect(_PAGE2);
    CScalerRead(_P2_UP_DOWN_CTRL1_B6, 1, pData, _NON_AUTOINC);

    if((pData[0] & 0x80) == 0x80)   // no clock
    {
        CSyncPhyZ0PowerOff();
        return _FALSE;
    }
    else
    {
        ((WORD *)pData)[6] = CSyncMeasurePhyFreq(0);
        ((WORD *)pData)[7] = CSyncMeasurePhyFreq(0);

        if(abs(((WORD *)pData)[7] - ((WORD *)pData)[6]) > ((g_usTMDSFreq / 100) + 1))
        {
            return _FALSE;
        }

        // Solve OSD respond time in sleep
        if(g_ucSearchTimes >= 3)
        {
            g_ucSearchTimes = g_ucSearchTimes - 3;
        }
        else
        {
            g_ucSearchTimes = 1;
        }

        if(CSyncPhyFreqForRightCount(_TMDS_Freq_SLEEP_Right_Count, 1) == _TRUE)
        {
            CScalerPageSelect(_PAGEB);
            CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x7F);

            g_usDVITMDSFreq = g_usTMDSFreq1;
            g_usTMDSFreq = g_usTMDSFreq1;

            CSyncModeSetPhy();

            CScalerPageSelect(_PAGEB);

            CScalerSetByte(_PB_DP_RXMISC_02_AF, 0xC7);
            CSyncScanInputPortResetPhy();

            cnt2 = 0;

            do
            {
                CTimerDelayXms(10);
                CScalerPageSelect(_PAGEB);
                CScalerSetByte(_PB_DP_FLD_04_A8, 0xF0);
                CScalerRead(_PB_DP_FLD_04_A8, 1, pData, _NON_AUTOINC);
                cnt2++;

            }
            while(((pData[0] & 0xF0) != 0xF0) && (cnt2 < 20)); // cnt0 < 20 ---> 200ms

            // HDMI/DVI detect: Auto mode
            CScalerPageSelect(_PAGE2);
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_SCR_00, ~(_BIT3 | _BIT1 | _BIT0), _BIT1);

            // Wait for detect
            CTimerWaitForEvent(_EVENT_IVS);
            CTimerWaitForEvent(_EVENT_IVS);

            if(CHdmiFormatDetect()) // HDMI
            {
                CScalerPageSelect(_PAGE2);
                CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~_BIT7, 0x00);
                SET_INPUTSOURCE_TYPE(_SOURCE_HDMI);
            }
            else                    //DVI
            {
                CScalerPageSelect(_PAGE2);
                CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~_BIT7, _BIT7);
                SET_INPUTSOURCE_TYPE(_SOURCE_DVI);
            }

            CScalerPageSelect(_PAGE2);
            CScalerSetByte(_P2_TMDS_CTRL_A4, 0xf8);

            CTimerWaitForEvent(_EVENT_IVS);
            CTimerWaitForEvent(_EVENT_IVS);

            CScalerRead(_P2_TMDS_CTRL_A4, 1, &pData, _NON_AUTOINC);

            if(GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
            {
                pData[0] = ((pData[0] & 0xf8) == 0xf8) ? _TRUE : _FALSE;
            }
            else
            {
                pData[0] = ((pData[0] & 0xe0) == 0xe0) ? _TRUE : _FALSE;
            }

            if(pData[0] == _TRUE)
            {
                return _TRUE;   // Hsync, Vsync is available
            }
            else
            {
                CSyncPhyZ0PowerOff();
                return _FALSE;  // Hsync, Vsync is not available
            }
        }
        else
        {
            CSyncPhyZ0PowerOff();

            return _FALSE;      //Clock Unstable
        }
    }


#elif(_SCALER_TYPE == _RTD2545LR)

    for(cnt0 = 0; cnt0 < 4; cnt0++)
    {
        CScalerPageSelect(_PAGE2);
        CScalerRead(_P2_UP_DOWN_CTRL1_B6, 1, pData, _NON_AUTOINC);
        pData[0] = ((pData[0] & 0x80) == 0x80) ? _FALSE : _TRUE;
        if(pData[0])
        {
            CScalerPageSelect(_PAGEB);
            CScalerSetByte(_PB_DIG00_E0, 0xD0);

            CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);
            CScalerSetByte(_PB_DP_RXMISC_02_AF, 0x87);
            CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x16);
            CScalerSetByte(_PB_DP_AUX_00_B3, 0x92);

            CScalerSetByte(_PB_DP_FLD_05_A9, 0x0b);
            CScalerSetByte(_PB_DP_FLD_06_AA, 0x17);
            CScalerSetByte(_PB_DP_FLD_07_AB, 0x1d);

            CSyncScanInputPortResetPhy();
            CTimerDelayXms(2);
            CScalerRead(_PB_DP_FLD_03_A7, 1, pData, _NON_AUTOINC);
            pData[0] &= 0xf0;
            if(pData[0] == 0x30)
            {
                cnt1++;
            }
            else
            {
                cnt1 = 0;
                return _FALSE;
            }
        }
    }

    CScalerSetByte(_PB_DP_AUX_00_B3, 0x92); // OOBS manual mode enable, bit 7

    CScalerPageSelect(_PAGEB);
    CScalerSetByte(_PB_DP_FLD_05_A9, 0xc4);
    CScalerSetByte(_PB_DP_FLD_06_AA, 0x82);
    CScalerSetByte(_PB_DP_FLD_07_AB, 0x0a);

    CSyncScanInputPortResetPhy();
    CTimerDelayXms(10);
    CScalerRead(_PB_DP_FLD_03_A7, 1, pData, _NON_AUTOINC);
    pData[0] &= 0xf0;

    if(pData[0] == 0x80)
    {
        CScalerSetByte(_PB_DP_FLD_05_A9, 0x1f);
        CScalerSetByte(_PB_DP_FLD_06_AA, 0x2d);
        CScalerSetByte(_PB_DP_FLD_07_AB, 0x44);
    }
    else if(pData[0] == 0xb0)
    {
        CScalerSetByte(_PB_DP_FLD_05_A9, 0x44);
        CScalerSetByte(_PB_DP_FLD_06_AA, 0x6c);
        CScalerSetByte(_PB_DP_FLD_07_AB, 0x82);
    }
    else if(pData[0] == 0x70)
    {
        CScalerSetByte(_PB_DP_FLD_05_A9, 0xff);
        CScalerSetByte(_PB_DP_FLD_06_AA, 0xc9);
        CScalerSetByte(_PB_DP_FLD_07_AB, 0x0a);
    }
    else
    {
        CScalerSetByte(_PB_DP_FLD_05_A9, 0xff);
        CScalerSetByte(_PB_DP_FLD_06_AA, 0xff);
        CScalerSetByte(_PB_DP_FLD_07_AB, 0x32);
    }

    cnt1 = 0;

    for(cnt0 = 0; cnt0 < 30; cnt0++)
    {
        CScalerPageSelect(_PAGE2);
        CScalerRead(_P2_UP_DOWN_CTRL1_B6, 1, pData, _NON_AUTOINC);
        pData[0] = ((pData[0] & 0x80) == 0x80) ? _FALSE : _TRUE;

        if(pData[0] == _TRUE)
        {
            CScalerPageSelect(_PAGEB);
            CScalerSetByte(_PB_DIG00_E0, 0xD0);

            CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);
            CScalerSetByte(_PB_DP_RXMISC_02_AF, 0x87);
            CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x16);
            CScalerSetByte(_PB_DP_AUX_00_B3, 0x92);

            CSyncScanInputPortResetPhy();
            CTimerDelayXms(2);
            CScalerRead(_PB_DP_FLD_03_A7, 1, pData, _NON_AUTOINC);
            pData[0] &= 0xf0;

            if(cnt0 == 0)
            {
                pData[1] = pData[0];
            }
            if((pData[0] == pData[1]) && (pData[0] != 0x80) && (pData[0] != 0x30))
            {
                cnt1++;
            }
            else
            {
                cnt1 = 0;
                return _FALSE;
            }
        }
    }

    cnt1 = 0;

    for(cnt0 = 0; cnt0 < 30; cnt0++)
    {
        CScalerPageSelect(_PAGE2);
        CScalerRead(_P2_UP_DOWN_CTRL1_B6, 1, pData, _NON_AUTOINC);
        pData[0] = ((pData[0] & 0x80) == 0x80) ? _FALSE : _TRUE;

        if(pData[0] == _TRUE)
        {
            CScalerPageSelect(_PAGEB);
            CScalerSetByte(_PB_DIG00_E0, 0xD0);

            CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);
            CScalerSetByte(_PB_DP_RXMISC_02_AF, 0x87);
            CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x16);
            CScalerSetByte(_PB_DP_AUX_00_B3, 0x92);

            CSyncScanInputPortResetPhy();
            CTimerDelayXms(2);
            CScalerRead(_PB_DP_FLD_03_A7, 1, pData, _NON_AUTOINC);
            pData[0] &= 0xf0;

            if(cnt0 == 0)
            {
                pData[1] = pData[0];
            }

            if((pData[0] == pData[1]) && (pData[0] != 0x80) && (pData[0] != 0x30))
            {
                cnt1++;

                if(cnt1 == 30)
                {
                    CScalerPageSelect(_PAGEB);
                    CScalerSetByte(_PB_DP_CDR_03_A3, 0x8c);
                    CScalerSetByte(_PB_DP_FLD_09_AD, 0x07);
                    CScalerSetByte(_PB_DP_RESERVED_05_BF, 0xF0);
                    CScalerSetByte(_PB_DP_RXMISC_01_AE, 0x01);
                    CScalerSetByte(_PB_DP_ADP_EQ_B2, 0x76);
                    CScalerSetByte(_PB_DP_RXMISC_02_AF, 0xC7);
                    CScalerSetByte(_PB_DIG01_E1, 0xf0);
                    CSyncScanInputPortResetPhy();

                    CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x7f);

                    CScalerPageSelect(_PAGE2);
                    CScalerSetByte(0xa4, 0xf8);
                    CTimerDelayXms(30);
                    CScalerRead(0xa4, 1, pData, _NON_AUTOINC);

                    pData[0] = ((pData[0] & 0xf8) == 0xf8) ? _TRUE : _FALSE;
                    if(pData[0])
                    {

                        CScalerPageSelect(_PAGEB);

                        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x7f);
                        return _TRUE;
                    }
                    else
                    {
                        CScalerPageSelect(_PAGEB);
                        CScalerSetByte(_PB_DP_PWR_CTL_B4, 0x08);
                        cnt1 = 0;

                        return _FALSE;
                    }
                }
            }
            else
            {
                cnt1 = 0;
                return _FALSE;
            }
        }
    }  // End of for(cnt0=0; cnt0<30; cnt0++)

#endif  // End of #if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
}

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))
//--------------------------------------------------
// Description  : Input Port 2D Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSyncInputPort2DInitial(void)
{
    if(!((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_I_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_I_PORT)))
    {
        if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_DVI_PORT ) || (_D0_INPUT_PORT_TYPE == _D0_DVI_I_PORT))
        {
            CScalerPageSelect(_PAGE2);
            CScalerSetBit(_P2_HDCP_PORT_CTRL_C2, ~_BIT1, (_DDC_CHANNEL_FOR_D1 << 1));

            CScalerPageSelect(_PAGEB);
            CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x06);
        }
        else if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT ) || (_D1_INPUT_PORT_TYPE == _D1_DVI_I_PORT))
        {
            CScalerPageSelect(_PAGE2);
            CScalerSetBit(_P2_HDCP_PORT_CTRL_C2, ~_BIT1, (_DDC_CHANNEL_FOR_D0 << 1));

            CScalerPageSelect(_PAGEB);
            CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x02);
        }
    }

    // for DP HDCP
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_Z0CC2_AC, ~_BIT6, 0x00);
}
#endif  // End of #if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

//--------------------------------------------------
// Description  : Input Port 2D Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSyncInputPort2DSwitch(void)
{
    CScalerPageSelect(_PAGE2);

    if(GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT)
    {
        CScalerSetBit(_P2_HDCP_PORT_CTRL_C2, ~_BIT1, (_DDC_CHANNEL_FOR_D0 << 1));
    }
    else if(GET_INPUT_PORT(g_ucSearchIndex) == _D1_INPUT_PORT)
    {
        CScalerSetBit(_P2_HDCP_PORT_CTRL_C2, ~_BIT1, (_DDC_CHANNEL_FOR_D1 << 1));
    }

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT))
    {
        CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT6 | _BIT5), ((_HDMI_BR_SWAP << 6) | (_HDMI_PN_SWAP << 5)));
    }
    else
    {
    
	if(GET_INPUTPORT_TYPE(g_ucSearchIndex) ==_D0_DVI_PORT)
		{
	      CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT6 | _BIT5 | _BIT4), ((_DVI_BR_SWAP << 6) | (_DVI_PN_SWAP << 5) | (0x0F)));
#if _DEBUG_MESSAGE_SUPPORT
				  CDebugMessage("DVI_1", 0);
#endif

		}
	/*
	else 
		{
		CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT6 | _BIT5 | _BIT4), ((0<< 6) | (_DVI_PN_SWAP << 5) | (0x0F)));
#if _DEBUG_MESSAGE_SUPPORT
		CDebugMessage("VGA", 0);
#endif
    		}
    		*/
    }

#endif

        CScalerPageSelect(_PAGEB);

        if(GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT)
        {
            CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x02);
        }
        else if(GET_INPUT_PORT(g_ucSearchIndex) == _D1_INPUT_PORT)
        {
            CScalerSetByte(_PB_DP_2D_SWITCH_B5, 0x06);
        }

}
#endif  // End of #if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

#endif  // End of #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

// V013 VGA Patch Note (9) Modify 20100414 Start
// Patch Reason : Add Checking Stable Signal mechanism for VGA Signal.
//--------------------------------------------------
// Description  : Check VGA input port is stable in Check State and Not Support State.
// Input Value  : None
// Output Value : Return _TRUE if the signal is stable
//--------------------------------------------------
bit CSyncCheckVGAIsStable(void)
{
    bit bStablePolarity = 0;
    BYTE ucOldSyncType = 0;
    BYTE ucOldModeCurr = stModeInfo.ModeCurr;
    BYTE ucOldPolarity = stModeInfo.Polarity;
    WORD usOldIHCount = 0;
    WORD usOldIVTotal = 0;
    WORD usOldIHSyncPulseCount = stModeInfo.IHSyncPulseCount;
    WORD usOldIVSyncPulseCount = stModeInfo.IVSyncPulseCount;

    // Measure H Start / End Postion is only for SOG Type when ucCurrState == _CHECK_STATE.
    if(CScalerGetBit(_SYNC_SELECT_47, _BIT4) == _BIT4)
    {
        return _TRUE;
    }

    // Disable Watch Dog
    CAdjustDisableWatchDog(_WD_ALL);

    // V016 System Patch Note (15) Modify 20100824 Start
    // Patch Reason : Fix IHCount=0 issue
    // Auto Measure Disable
    CModeAutoMeasureOff();
    // V016 System Patch Note (15) Modify 20100824 End

    // Back up IHCount and IVTotal
    usOldIHCount = stModeInfo.IHCount;
    usOldIVTotal = stModeInfo.IVTotal;

    // Back Up Stable Polarity
    bStablePolarity = ((bit)CScalerGetBit(_STABLE_MEASURE_4F, _BIT6) ^ (bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6));

    // Back Up Old Sync Type
    CScalerRead(_VSYNC_COUNTER_LEVEL_MSB_4C, 1, &ucOldSyncType, _NON_AUTOINC);

    // Enable Sync Processor Auto Run
    CSyncGetSyncTypeAutoRun();

    // Get New Sync Type
    CScalerRead(_VSYNC_COUNTER_LEVEL_MSB_4C, 1, pData, _NON_AUTOINC);

    // Sync Type is Changed
    if((ucOldSyncType & 0xF0) != (pData[0] & 0xF0))
    {
        return _FALSE;
    }

    // Check Stable Polarity
    if(bStablePolarity != ((bit)CScalerGetBit(_STABLE_MEASURE_4F, _BIT6) ^ (bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6)))
    {
        return _FALSE;
    }

    // Disable On-line Measure
    CScalerSetByte(_MEAS_HS_PERIOD_H_52, 0x00);

    if(CModeMeasureReady() == _TRUE)
    {
        if(CModeMeasureData() == _TRUE)
        {
            // Polarity is Changed
            if(ucOldPolarity != stModeInfo.Polarity)
            {
                return _FALSE;
            }

            // IHCount is Changed
            if(abs(stModeInfo.IHCount - usOldIHCount) > 2)
            {
                return _FALSE;
            }

            // IVTotal is Changed
            if(abs(stModeInfo.IVTotal - usOldIVTotal) > 2)
            {
                return _FALSE;
            }

            // IHSyncPulse is Changed
            if(abs(stModeInfo.IHSyncPulseCount - usOldIHSyncPulseCount) > 2)
            {
                return _FALSE;
            }

            // IVSyncPulse is Changed
            if(abs(stModeInfo.IVSyncPulseCount - usOldIVSyncPulseCount) > 2)
            {
                return _FALSE;
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

    // Enable On-line Measure
    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT7, _BIT7);

    // Polling Measure Ready
    CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent);

    // Clear Frame Sync Status
    CMiscClearStatusRegister();

    // Roll Back Mode Number
    if(stModeInfo.ModeCurr != ucOldModeCurr)
    {
        stModeInfo.ModeCurr = ucOldModeCurr;
    }

    if(ucCurrState == _CHECK_STATE)
    {
        // Clear Frame Sync Status
        CMiscClearStatusRegister();

        CTimerWaitForEvent(_EVENT_IVS);
        CTimerWaitForEvent(_EVENT_IVS);
        CTimerWaitForEvent(_EVENT_IVS);
    }

    return _TRUE;
}
// V013 VGA Patch Note (9) Modify 20100414 End

#if(_HSYNC_DETECTION == _AUTO_RUN)
//--------------------------------------------------
// Description  : Scan VGA input port to obtain if the signal is available
// Input Value  : None
// Output Value : Return _TRUE if the signal is available
//--------------------------------------------------
bit CSyncScanInputPortVGA(void)
{
    BYTE cnt, synctypetemp = _NO_SYNC_STATE;

#if(_HSYNC_TYPE_SELECT != _HSYNC_ONLY)
    bit flag = 0;
#endif

    // V013 VGA Patch Note (6) Modify 20100428 Start
    // Patch Reason : Use M2PLL as internal clock in analog source.
    CScalerPageSelect(_PAGE1);

#if(_SCALER_TYPE == _RTD2472D)
    if(CScalerGetBit(_P1_MULTIPLY_PLL_CTRL3_E5, _BIT0) == 0x00)
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    if(CScalerGetBit(_P1_M2PLL_WD_E5, _BIT0) == _BIT0)
#endif  // End of #if(_SCALER_TYPE == _RTD2472D)
    {
        CScalerSetBit(_FIFO_FREQUENCY_22, ~_BIT2, 0x00);
    }
    else
    {
        CScalerSetBit(_FIFO_FREQUENCY_22, ~_BIT2, _INTERNAL_CLK_FLAG);
    }
    // V013 VGA Patch Note (6) Modify 20100428 End

    CScalerPageSelect(_PAGE0);

    if((GET_INPUT_PORT(g_ucSearchIndex) == _A0_INPUT_PORT) || (GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT))
    {
        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_HSYNC_SOURCE_SWAP == _OFF ? 0x00 : _BIT3 | _BIT2));
        CScalerSetDataPortBit(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL2_06, ~ _BIT4, _BIT4);
        CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~_BIT3, 0x00);
        CScalerSetByte(_P0_ADC_CLAMP_CTRL1_D5, 0x00);
    }
    else if((GET_INPUT_PORT(g_ucSearchIndex) == _A1_INPUT_PORT) || (GET_INPUT_PORT(g_ucSearchIndex) == _D1_INPUT_PORT))
    {
        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_HSYNC_SOURCE_SWAP == _OFF ? _BIT3 | _BIT2 : 0x00));
        CScalerSetDataPortBit(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL2_06, ~_BIT5, _BIT5);
        CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~_BIT3, _BIT3);
        CScalerSetByte(_P0_ADC_CLAMP_CTRL1_D5, 0x54);
    }
// 2545LR W/O SOG1 Start
#if(_SCALER_TYPE == _RTD2545LR)
    CScalerSetByte(_P0_ADC_DCR_CTRL_D3, (_BIT0 << _SOG0_INPUT_SELECTT)); // SOG Input MUX Select
    CScalerSetByte(_P0_ADC_SOG_CMP_D2, 0x30);
#elif((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerSetByte(_P0_ADC_DCR_CTRL_D3, ((_BIT0 << _SOG0_INPUT_SELECTT) | (_BIT0 << _SOG1_INPUT_SELECTT))); // SOG Input MUX Select
    CScalerSetByte(_P0_ADC_SOG_CMP_D2, 0x34);
#else
    No Setting !!
#endif  //End of #if(_SCALER_TYPE == _RTD2545LR)
// 2545LR W/O SOG1 End

    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), _BIT1);

    CScalerPageSelect(_PAGE0);
#if(_HSYNC_TYPE_SELECT == _HSYNC_ONLY)

    for(cnt = 0; cnt < 2; cnt++)
    {
        synctypetemp = CSyncGetSyncTypeAutoRun();

        // V014 VGA Patch Note (9) Modify 20100604 Start
        // Patch Reason : Change capture window setting after signal type find out successful
        /*
        // V013 VGA Patch Note (22) Modify 20100511 Start
        // Patch Reason : Modify Capture Window Size for HEORV/OR Sync Type
        CSyncSetCaptureWindowfForHEORV();
        // V013 VGA Patch Note (22) Modify 20100511 End
        */
        // V014 VGA Patch Note (9) Modify 20100604 End

        if(synctypetemp != _NO_SYNC_STATE)
        {
            if(synctypetemp == _SOY_STATE)
            {
                SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);
            }
            else
            {
                SET_INPUTSOURCE_TYPE(_SOURCE_VGA);
            }

            // V014 VGA Patch Note (9) Modify 20100604 Start
            // Patch Reason : Change capture window setting after signal type find out successful
            CSyncSetCaptureWindowfForHEORV();
            // V014 VGA Patch Note (9) Modify 20100604 End

            return _TRUE;
        }
    }

#else

    CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, 0x00);

    for(cnt = 0; cnt < 4; cnt++)
    {
        synctypetemp = CSyncGetSyncTypeAutoRun();

        // V014 VGA Patch Note (9) Modify 20100604 Start
        // Patch Reason : Change capture window setting after signal type find out successful
        /*
        // V013 VGA Patch Note (22) Modify 20100511 Start
        // Patch Reason : Modify Capture Window Size for HEORV/OR Sync Type
        CSyncSetCaptureWindowfForHEORV();
        // V013 VGA Patch Note (22) Modify 20100511 End
        */
        // V014 VGA Patch Note (9) Modify 20100604 End

        if(synctypetemp != _NO_SYNC_STATE)
        {
            if((flag == 1) || (CScalerGetBit(_SYNC_SELECT_47, _BIT4) == 0))
            {
                if(synctypetemp == _SOY_STATE)
                {
                    SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);
                }
                else
                {
                    SET_INPUTSOURCE_TYPE(_SOURCE_VGA);
                }

                // V014 VGA Patch Note (9) Modify 20100604 Start
                // Patch Reason : Change capture window setting after signal type find out successful
                CSyncSetCaptureWindowfForHEORV();
                // V014 VGA Patch Note (9) Modify 20100604 End

                return _TRUE;
            }
            else if(CScalerGetBit(_SYNC_SELECT_47, _BIT4))
            {
                flag = 1;
            }
        }

        CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, CScalerGetBit(_SYNC_SELECT_47, _BIT4) ^ _BIT4);
    }

#endif  // End of #if(_HSYNC_TYPE_SELECT == _HSYNC_ONLY)

    CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, 0x00);
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);

    return _FALSE;
}

//-------------------------------------------------------------------
// Description  : Get VGA sync type by Hsync Type Detection Auto Run
// Input Value  : None
// Output Value : Return sync type
//-------------------------------------------------------------------
BYTE CSyncGetSyncTypeAutoRun(void)
{
    BYTE synctemp = 0;

    // V013 VGA Patch Note (23) Modify 20100513 Start
    // Patch Reason : For Video Mode Clamp Position Setting Flow
    bit bSearchYpbprTblFlag = _FALSE;
    // V013 VGA Patch Note (23) Modify 20100513 End

#if(_SCALER_TYPE == _RTD2545LR)
    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_POWER_C6, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));
#elif((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_POWER_C6, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));
#else
    No Setting !!
#endif  //End of #if(_SCALER_TYPE == _RTD2545LR)

    // V013 VGA Patch Note (15) Modify 20100422 Start
    // Patch Reason : Fix for avoid cover the value at check state.
    // Avoid Video8-C-port effect
    /*
    CScalerSetBit(_IPH_ACT_WID_H_16, ~_BIT7, 0x00);
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0x00);
    */
    // V013 VGA Patch Note (15) Modify 20100422 End

    // Disable CS_RAW Inverted
    CScalerSetBit(_SYNC_INVERT_48, ~(_BIT3), 0x00);

    // Select Measure Source to ADC HS/VS
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1);

    // Stable Measure Start
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, _BIT0);

    // Delay for Stable Measure
    CTimerDelayXms(5);

    // Check HSync OverFlow
    if((bit)CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT7))
    {
        return _NO_SYNC_STATE;
    }

    // Check Stable Flag
    if(!CTimerPollingEventProc(20, CMiscStableFlagPollingEvent))
    {
        // Change Stable Period Tolerance
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT3, 0x00);

        // Delay for Period Tolerance Change
        CTimerDelayXms(5);

        // Stable Measure Start
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, _BIT0);

        // Delay for Stable Measure
        CTimerDelayXms(5);

        if(CTimerPollingEventProc(20, CMiscStableFlagPollingEvent) == _FALSE)
        {
            // Reset Stable Period Tolerance
            CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT3, _BIT3);

            return _NO_SYNC_STATE;
        }
    }

    // Pop Up Stable Value
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT1, _BIT1);

    // Get stable period
    CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
    ((WORD *)pData)[1] = ((pData[0] & 0x07) << 8) | pData[1];

    // Set Vsync Counter Level
    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~(_BIT2 | _BIT1 | _BIT0), (BYTE)(((WORD *)pData)[1] >> 9) & 0x07);
    CScalerSetByte(_VSYNC_COUNTER_LEVEL_LSB_4D, (BYTE)(((WORD *)pData)[1] >> 1));

    // Enable Hsync Type Detection Auto Run
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);
    CScalerSetBit(_SYNC_SELECT_47, ~(_BIT6 | _BIT5), 0x00);
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);

    // Check the result of Auto Run

    // V012 Modify 20100329 Start
    // V012 Patch Note (19) : Adjust polling time of Auto Run Typer according to different Crystal frequency.
    /*
    if(CTimerPollingEventProc(90, CMiscHsyncTypeAutoRunFlagPollingEvent))
    */
    if(CTimerPollingFlagProc(_SP_AUTORUN_TIME_OUT, _PAGE_COMMON, _VSYNC_COUNTER_LEVEL_MSB_4C, _BIT7, _TRUE) == _TRUE)
    // V012 Modify 20100329 End
    {
        // V013 VGA Patch Note (21) Modify 20100511 Start
        // Patch Reason : Modify for FW doesn't pop up stable result after Stable Measure finish.
        // Pop Up Stable Value
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT1, _BIT1);
        // V013 VGA Patch Note (21) Modify 20100511 End

        synctemp = (CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, 0xff) & 0x70) >> 4;

        switch(synctemp)
        {
            case _NO_SIGNAL:        // No Signal
            case _NOT_SUPPORT:      // Not Support
            case _HSYNC_WITHOUT_VS: // Hsync only
                synctemp = _NO_SYNC_STATE;
                break;

            case _YPBPR_SYNC:       // YPbPr-Type CS
                if(CModeMeasureReady())
                {
                    if(CModeMeasureData())
                    {
                        if((stModeInfo.IHFreq >= _H_FREQ_MIN) && (stModeInfo.IHFreq <= _H_FREQ_MAX) && (stModeInfo.IVFreq >= _V_FREQ_MIN) && (stModeInfo.IVFreq <= _V_FREQ_MAX))
                        {
                            stModeInfo.ModeCurr = CYPbPrSearchMode();

                            // V013 VGA Patch Note (23) Modify 20100513 Start
                            // Patch Reason : For Video Mode Clamp Position Setting Flow
                            bSearchYpbprTblFlag = _TRUE;
                            // V013 VGA Patch Note (23) Modify 20100513 End

                            if(stModeInfo.ModeCurr != _MODE_NOSUPPORT)
                            {
                                synctemp = _SOY_STATE;
                                break;
                            }
                        }
                        else
                        {
                            stModeInfo.ModeCurr = 0;

                            synctemp = _SOY_STATE;
                            break;
                        }
                    }
                }
                synctemp = _NO_SYNC_STATE;
                break;

            case _SERRATION_CS:     // Serration-Type CS

#if(_YPBPR_SUPPORT == _ON)
#if(_HSYNC_TYPE_SELECT == _HSYNC_WITH_SOG_SOY)

                if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                {
                    if(CModeMeasureReady())
                    {
                        if(CModeMeasureData())
                        {
                            if((stModeInfo.IHFreq >= _H_FREQ_MIN) && (stModeInfo.IHFreq <= _H_FREQ_MAX) && (stModeInfo.IVFreq >= _V_FREQ_MIN) && (stModeInfo.IVFreq <= _V_FREQ_MAX))
                            {
                                stModeInfo.ModeCurr = CYPbPrSearchMode();

                                // V013 VGA Patch Note (23) Modify 20100513 Start
                                // Patch Reason : For Video Mode Clamp Position Setting Flow
                                bSearchYpbprTblFlag = _TRUE;
                                // V013 VGA Patch Note (23) Modify 20100513 End

                                if(stModeInfo.ModeCurr != _MODE_NOSUPPORT)
                                {
                                    if(CSyncDistinguishSogSoy() == _MODE_NOSUPPORT)
                                    {
                                        synctemp = _SOY_STATE;
                                    }
                                    else
                                    {
                                        synctemp = _CS_STATE;
                                    }
                                }
                                else
                                {
                                    synctemp = _CS_STATE;
                                }
                                break;
                            }
                            else
                            {
                                synctemp = _CS_STATE;
                                break;
                            }
                        }
                    }

                    synctemp = _NO_SYNC_STATE;
                    break;
                }
                else
                {
                    synctemp = _CS_STATE;
                    break;
                }
#else
                if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_YPBPR_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_YPBPR_PORT))
                {
                    stModeInfo.ModeCurr = 0;
                    synctemp = _SOY_STATE;
                }
                else
                {
                    synctemp = _CS_STATE;
                }

                break;

#endif  //End of #if(_HSYNC_TYPE_SELECT == _HSYNC_WITH_SOG_SOY)
#endif  //End of #if(_YPBPR_SUPPORT == _ON)
            case _XOR_OR_TYPE_CS_WITH_EQR:      // CS with Equalizer
            case _XOR_OR_TYPE_CS_WITHOUT_EQR:   // OR-Type & XOR-Type CS
                synctemp = _CS_STATE;
                break;

            case _SEPARATE_HSYNC:               // Separate Sync
                synctemp = _SS_STATE;
                break;

            default:
                synctemp = _NO_SYNC_STATE;
                break;
        }
    }
    else
    {
        synctemp = _NO_SYNC_STATE;
    }

#if(_HSYNC_TYPE_SELECT != _HSYNC_ONLY)
    if((synctemp != _NO_SYNC_STATE) && ((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4)))
    {
        // V015 VGA Patch Note (3) Modify 20100611 Start
        // Patch Reason : Solve SOG mistaken when enter white pattern in separate signal.
        /*
        // Get Stable High Period
        CScalerRead(_STABLE_HIGH_PERIOD_H_4A, 2, pData, _AUTOINC);
        stModeInfo.IHSyncPulseCount = ((pData[0] & 0x07) << 8) | pData[1];
        CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
        stModeInfo.IHCount = ((pData[0] & 0x07) << 8) | pData[1];

        if(((stModeInfo.IHSyncPulseCount * 7 / stModeInfo.IHCount) != 0) || (stModeInfo.IHSyncPulseCount < 4))
        {
            synctemp = _NO_SYNC_STATE;
        }
        */
#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        // Get Stable High Period
        CScalerRead(_STABLE_HIGH_PERIOD_H_4A, 2, pData, _AUTOINC);
        stModeInfo.IHSyncPulseCount = ((WORD)(pData[0] & 0x07) << 8) | pData[1];

        // Get H Stable Period
        CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
        stModeInfo.IHCount = ((pData[0] & 0x07) << 8) | pData[1];

        // Check H Sync
        if(((stModeInfo.IHSyncPulseCount * 7 / stModeInfo.IHCount) != 0) || (stModeInfo.IHSyncPulseCount < 4))
        {
            synctemp = _NO_SYNC_STATE;
        }

        // Init back up V Sync Pulse Width
        ((WORD *)pData)[6] = _MAX_VSYNC_HIGH_PERIOD;

        for(pData[4] = 0; pData[4] < 10; pData[4]++)
        {
            CScalerGetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, 0x0A, 2, &pData[2], _NON_AUTOINC);

            // Get DeVS High Period Width
            ((WORD *)pData)[7] = (((WORD)(pData[2] & 0x0F) << 8) | pData[3]);

            if((((WORD *)pData)[7] == ((WORD *)pData)[6]) || (((WORD *)pData)[7] >= _MAX_VSYNC_HIGH_PERIOD))
            {
                break;
            }

            // Back up current V Sync Count
            ((WORD *)pData)[6] = ((WORD *)pData)[7];
        }

        // Check V Sync
        if((((WORD *)pData)[7] >= _MAX_VSYNC_HIGH_PERIOD) || (((WORD *)pData)[7] <= 0))
        {
            synctemp = _NO_SYNC_STATE;
        }
#else
        // Get Stable High Period
        CScalerRead(_STABLE_HIGH_PERIOD_H_4A, 2, pData, _AUTOINC);
        stModeInfo.IHSyncPulseCount = ((pData[0] & 0x07) << 8) | pData[1];
        CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
        stModeInfo.IHCount = ((pData[0] & 0x07) << 8) | pData[1];

        if(((stModeInfo.IHSyncPulseCount * 7 / stModeInfo.IHCount) != 0) || (stModeInfo.IHSyncPulseCount < 4))
        {
            synctemp = _NO_SYNC_STATE;
        }
#endif // End of // #if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        // V015 VGA Patch Note (3) Modify 20100611 End
    }
#endif  // End of #if(_HSYNC_TYPE_SELECT != _HSYNC_ONLY)

    // V013 VGA Patch Note (23) Modify 20100513 Start
    // Patch Reason : For Video Mode Clamp Position Setting Flow

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
#if(_YPBPR_SUPPORT == _ON)
// V014 VGA Patch Note (6) Modify 20100527 End

    // V014 VGA Patch Note (6) Modify 20100527 Start
    // Patch Reason : Modify Video Mode Can't Light On
    /*
    if((bSearchYpbprTblFlag != _TRUE) && (synctemp != _NO_SYNC_STATE))
    */
    if((bSearchYpbprTblFlag != _TRUE) && ((synctemp != _NO_SYNC_STATE) && (CScalerGetBit(_SYNC_SELECT_47, _BIT4) == _BIT4)))
    // V014 VGA Patch Note (6) Modify 20100527 End
    {
        if(CModeMeasureReady() == _TRUE)
        {
            if(CModeMeasureData() == _TRUE)
            {
                if((stModeInfo.IHFreq >= _H_FREQ_MIN) && (stModeInfo.IHFreq <= _H_FREQ_MAX) && (stModeInfo.IVFreq >= _V_FREQ_MIN) && (stModeInfo.IVFreq <= _V_FREQ_MAX))
                {
                    stModeInfo.ModeCurr = CYPbPrSearchMode();

                    // V014 VGA Patch Note (6) Modify 20100527 Start
                    // Patch Reason : Modify Video Mode Can't Light On
                    if((stModeInfo.ModeCurr != _MODE_NOSUPPORT) && (stModeInfo.ModeCurr != _VIDEO_720x480p_60HZ))
                    {
                        synctemp = _SOY_STATE;
                    }
                    // V014 VGA Patch Note (6) Modify 20100527 End
                }
                else
                {
                    stModeInfo.ModeCurr = _MAX_YPBPR_MODE;
                }
            }
            else
            {
                synctemp = _NO_SYNC_STATE;
            }
        }
        else
        {
            synctemp = _NO_SYNC_STATE;
        }
    }

// V014 VGA Patch Note (6) Modify 20100527 Start
// Patch Reason : Modify Video Mode Can't Light On
#endif
// V014 VGA Patch Note (6) Modify 20100527 End

    // V013 VGA Patch Note (23) Modify 20100513 End

    return synctemp;
}

#else   // Else of #if(_HSYNC_DETECTION == _AUTO_RUN)

//--------------------------------------------------
// Description  : Scan VGA input port to obtain if the signal is available
// Input Value  : None
// Output Value : Return _TRUE if the signal is available
//--------------------------------------------------
bit CSyncScanInputPortVGA(void)
{
    BYTE cnt = 0;
    BYTE ucSyncType = _NO_SYNC_STATE;
    BYTE ucSourceSel = _SOURCE_FROM_NONE;
    bit flag = 0;

    // V013 VGA Patch Note (6) Modify 20100428 Start
    // Patch Reason : Use M2PLL as internal clock in analog source.
    CScalerPageSelect(_PAGE1);

#if(_SCALER_TYPE == _RTD2472D)
    if(CScalerGetBit(_P1_MULTIPLY_PLL_CTRL3_E5, _BIT0) == 0x00)
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    if(CScalerGetBit(_P1_M2PLL_WD_E5, _BIT0) == _BIT0)
#endif  // End of #if(_SCALER_TYPE == _RTD2472D)
    {
        CScalerSetBit(_FIFO_FREQUENCY_22, ~_BIT2, 0x00);
    }
    else
    {
        CScalerSetBit(_FIFO_FREQUENCY_22, ~_BIT2, _INTERNAL_CLK_FLAG);
    }
    // V013 VGA Patch Note (6) Modify 20100428 End

    CScalerPageSelect(_PAGE0);

    if((GET_INPUT_PORT(g_ucSearchIndex) == _A0_INPUT_PORT) || (GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT))
    {
        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_HSYNC_SOURCE_SWAP == _OFF ? 0x00 : _BIT3 | _BIT2));
        CScalerSetDataPortBit(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL2_06, ~ _BIT4, _BIT4);
        CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~_BIT3, 0x00);
        CScalerSetByte(_P0_ADC_CLAMP_CTRL1_D5, 0x00);
    }
    else if((GET_INPUT_PORT(g_ucSearchIndex) == _A1_INPUT_PORT) || (GET_INPUT_PORT(g_ucSearchIndex) == _D1_INPUT_PORT))
    {
        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_HSYNC_SOURCE_SWAP == _OFF ? _BIT3 | _BIT2 : 0x00));
        CScalerSetDataPortBit(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL2_06, ~_BIT5, _BIT5);
        CScalerSetBit(_P0_ADC_RGB_CTRL_CE, ~_BIT3, _BIT3);
        CScalerSetByte(_P0_ADC_CLAMP_CTRL1_D5, 0x54);
    }

#if(_SCALER_TYPE == _RTD2545LR)
    CScalerSetByte(_P0_ADC_DCR_CTRL_D3, (_BIT0 << _SOG0_INPUT_SELECTT)); // SOG Input MUX Select
    CScalerSetByte(_P0_ADC_SOG_CMP_D2, 0x30);
#elif((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerSetByte(_P0_ADC_DCR_CTRL_D3, ((_BIT0 << _SOG0_INPUT_SELECTT) | (_BIT0 << _SOG1_INPUT_SELECTT))); // SOG Input MUX Select
    CScalerSetByte(_P0_ADC_SOG_CMP_D2, 0x34);
#else
    No Setting !!
#endif  //End of #if(_SCALER_TYPE == _RTD2545LR)

    ucSourceSel = _SOURCE_FROM_HS_RAW;

    for(cnt = 0; cnt < 4; cnt++)
    {
        ucSyncType = CSyncGetSyncTypeNormalRun(ucSourceSel);

        if(ucSyncType == _NO_SYNC_STATE)
        {
            if(ucSourceSel == _SOURCE_FROM_HS_RAW)
            {
                ucSourceSel = _SOURCE_FROM_SOG;
            }
            else
            {
                ucSourceSel = _SOURCE_FROM_HS_RAW;
            }
        }
        else
        {
            if(ucSourceSel == _SOURCE_FROM_HS_RAW)
            {
                SET_INPUTSOURCE_TYPE(_SOURCE_VGA);

                // Clear Stable Flag
                CScalerSetByte(_HSYNC_TYPE_DETECTION_FLAG_4E, 0xff);
                return _TRUE;
            }
            else
            {
                if(flag)
                {
                    if(ucSyncType == _SOY_STATE)
                    {
                        SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);
                    }
                    else
                    {
                        SET_INPUTSOURCE_TYPE(_SOURCE_VGA);
                    }

                    // Clear Stable Flag
                    CScalerSetByte(_HSYNC_TYPE_DETECTION_FLAG_4E, 0xff);
                    return _TRUE;
                }
                else
                {
                    ucSourceSel = _SOURCE_FROM_HS_RAW;
                    flag = 1;
                }
            }
        }
    }

    CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, 0x00);
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);

    return _FALSE;
}

//--------------------------------------------------------------------
// Description  : Get VGA sync type by Hsync Type Detection Normal Run
// Input Value  : None
// Output Value : Return sync type
//--------------------------------------------------------------------
BYTE CSyncGetSyncTypeNormalRun(BYTE ucSourceSel)
{
    BYTE ucSyncType = _NO_SYNC_STATE;
    BYTE cnt = 0;

    if(ucSourceSel == _SOURCE_FROM_NONE)
    {
        return _NO_SYNC_STATE;  // No-Signal State
    }

    // Hsync Source Select
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, (ucSourceSel > 1 ? _BIT4 : 0));

#if(_SCALER_TYPE == _RTD2545LR)
    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_POWER_C6, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));
#elif((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_POWER_C6, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));
#else
    No Setting !!
#endif  //End of #if(_SCALER_TYPE == _RTD2545LR)

    // Avoid Video8-C-port effect
    CScalerSetBit(_IPH_ACT_WID_H_16, ~_BIT7, 0x00);
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0x00);

    // Disable CS_RAW Inverted
    CScalerSetBit(_SYNC_INVERT_48, ~(_BIT3), 0x00);

    // Select Measure Source to ADC HS/VS
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1);

    do
    {
        // Stable Measure Start
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, _BIT0);

        // Delay for Stable Measure
        CTimerDelayXms(5);

        // Check HSync OverFlow
        if((bit)CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT7))
        {
            return _NO_SYNC_STATE;  // No-Signal State
        }

        // Check Stable Flag
        if(!CTimerPollingEventProc(20, CMiscStableFlagPollingEvent))
        {
            // Change Stable Period Tolerance
            CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT3, 0x00);

            // Delay for Period Tolerance Change
            CTimerDelayXms(5);

            // Stable Measure Start
            CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);
            CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, _BIT0);

            // Delay for Stable Measure
            CTimerDelayXms(5);

            if(CTimerPollingEventProc(20, CMiscStableFlagPollingEvent) == _FALSE)
            {
                // Reset Stable Period Tolerance
                CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT3, _BIT3);

                return _NO_SYNC_STATE;  // Not-Support State
            }
        }

        // Pop Up Stable Value
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT1, _BIT1);

        // Check Hsync Polarity
        if((!(bit)(CScalerGetBit(_STABLE_MEASURE_4F, _BIT6))))
        {
            CScalerSetBit(_SYNC_INVERT_48, ~(_BIT3), _BIT3);
            cnt++;
        }
        else
        {
            break;  // Positive Polarity
        }

        if(cnt >= 2)
        {
            return _NO_SYNC_STATE;  // Not-Support State
        }

    }while(cnt < 2);

    // Get stable period
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT1, _BIT1);
    CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
    ((WORD *)pData)[1] = ((pData[0] & 0x07) << 8) | pData[1];

    // Set Vsync Counter Level
    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~(_BIT2 | _BIT1 | _BIT0), (BYTE)(((WORD *)pData)[1] >> 9) & 0x07);
    CScalerSetByte(_VSYNC_COUNTER_LEVEL_LSB_4D, (BYTE)(((WORD *)pData)[1] >> 1));

    // Enable Clamp Output and HS_OUT.
    CScalerSetBit(_SYNC_INVERT_48, ~(_BIT2 | _BIT4), (_BIT2 | _BIT4));

    // De-composite Circuit Enable
    CScalerSetBit(_SYNC_SELECT_47, ~(_BIT5 | _BIT6), 0x00);
    CScalerSetBit(_SYNC_SELECT_47, ~(_BIT5), _BIT5);

    // Clear Capture Window Unlock Flag
    CTimerDelayXms(40);
    CScalerSetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT0, _BIT0);

    // Delay for De-composite Circuit
    CTimerDelayXms(120);

    // Check Hsync Polarity Change Flag
    if((!(bit)(CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT1))))
    {
        // Select HS_OUT Source to DeHs & Switch ADC_VS Source to VS_RAW
        CScalerSetBit(_SYNC_CTRL_49, ~(_BIT5 | _BIT6), _BIT6);

        if(CTimerPollingFlagProc(40, _PAGE_COMMON, _HSYNC_TYPE_DETECTION_FLAG_4E, _BIT4, 1))
        {
            return _SS_STATE;   // Separate Sync State
        }

        return _NO_SYNC_STATE;          // No-Signal State
    }

    // Select HS_OUT Source to DeHs & Switch ADC_VS Source to DeVS
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT5 | _BIT6), (_BIT5 | _BIT6));

    // Check Capture Window Unlock
    if((bit)(CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT0)))
    {
        // Enable COAST Output and HS Recovery.
        CScalerSetBit(_SYNC_INVERT_48, ~(_BIT1 | _BIT6), (_BIT1 | _BIT6));

        ucSyncType = _CS_STATE;         // OR-Type & XOR-Type CS
    }
    else
    {
        // Disable COAST Output and HS Recovery.
        CScalerSetBit(_SYNC_INVERT_48, ~(_BIT1 | _BIT6), 0x00);

        // Check Equalization in Hsync
        if((bit)(CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT2)))
        {
            ucSyncType = _NO_SYNC_STATE;
            if(CModeMeasureReady())
            {
                if(CModeMeasureData())
                {
                    if((stModeInfo.IHFreq >= _H_FREQ_MIN) && (stModeInfo.IHFreq <= _H_FREQ_MAX) && (stModeInfo.IVFreq >= _V_FREQ_MIN) && (stModeInfo.IVFreq <= _V_FREQ_MAX))
                    {
                        stModeInfo.ModeCurr = CYPbPrSearchMode();
                        if(stModeInfo.ModeCurr != _MODE_NOSUPPORT)
                        {
                            ucSyncType = _SOY_STATE;    // YPbPr-Type CS
                        }
                    }
                }
            }
        }
        else
        {
#if(_YPBPR_SUPPORT == _ON)
                // Check Source Selection is SOG/SOY
                if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                {
                    if(CModeMeasureReady())
                    {
                        if(CModeMeasureData())
                        {
                            if((stModeInfo.IHFreq >= _H_FREQ_MIN) && (stModeInfo.IHFreq <= _H_FREQ_MAX) && (stModeInfo.IVFreq >= _V_FREQ_MIN) && (stModeInfo.IVFreq <= _V_FREQ_MAX))
                            {
                                stModeInfo.ModeCurr = CYPbPrSearchMode();
                                if(stModeInfo.ModeCurr != _MODE_NOSUPPORT)
                                {
                                    if(CSyncDistinguishSogSoy() == _MODE_NOSUPPORT)
                                    {
                                        ucSyncType = _SOY_STATE;
                                    }
                                    else
                                    {
                                        ucSyncType = _CS_STATE;
                                    }
                                }
                                else
                                {
                                    ucSyncType = _CS_STATE;     // Serration-Type CS
                                }
                            }
                        }
                    }

                    if(ucSyncType == _NO_SYNC_STATE)
                    {
                        return _NO_SYNC_STATE;  // No-Signal State
                    }
                }
                else
                {
                    ucSyncType = _CS_STATE;     // Serration-Type CS
                }
#else
            if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_YPBPR_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_YPBPR_PORT))
            {
                stModeInfo.ModeCurr = 0;
                ucSyncType = _SOY_STATE;        // YPbPr-Type CS
            }
            else
            {
                ucSyncType = _CS_STATE;         // Serration-Type CS
            }

#endif // End of #if(_YPBPR_SUPPORT == _ON)
        }
    }

    if((ucSyncType != _NO_SYNC_STATE) && ((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4)))
    {
        // V015 VGA Patch Note (3) Modify 20100611 Start
        // Patch Reason : Solve SOG mistaken when enter white pattern in separate signal.
        /*
        // Get Stable High Period
        CScalerRead(_STABLE_HIGH_PERIOD_H_4A, 2, pData, _AUTOINC);
        stModeInfo.IHSyncPulseCount = ((pData[0] & 0x07) << 8) | pData[1];
        CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
        stModeInfo.IHCount = ((pData[0] & 0x07) << 8) | pData[1];

        if(((stModeInfo.IHSyncPulseCount * 7 / stModeInfo.IHCount) != 0) || (stModeInfo.IHSyncPulseCount < 4))
        {
            ucSyncType = _NO_SYNC_STATE;
        }
        */
#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        // Get Stable High Period
        CScalerRead(_STABLE_HIGH_PERIOD_H_4A, 2, pData, _AUTOINC);
        stModeInfo.IHSyncPulseCount = ((WORD)(pData[0] & 0x07) << 8) | pData[1];

        // Get H Stable Period
        CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
        stModeInfo.IHCount = ((pData[0] & 0x07) << 8) | pData[1];

        // Check H Sync
        if(((stModeInfo.IHSyncPulseCount * 7 / stModeInfo.IHCount) != 0) || (stModeInfo.IHSyncPulseCount < 4))
        {
            ucSyncType = _NO_SYNC_STATE;
        }

        // Init back up V Sync Pulse Width
        ((WORD *)pData)[6] = _MAX_VSYNC_HIGH_PERIOD;

        for(pData[4] = 0; pData[4] < 10; pData[4]++)
        {
            CScalerGetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, 0x0A, 2, &pData[2], _NON_AUTOINC);

            // Get DeVS High Period Width
            ((WORD *)pData)[7] = (((WORD)(pData[2] & 0x0F) << 8) | pData[3]);

            if((((WORD *)pData)[7] == ((WORD *)pData)[6]) || (((WORD *)pData)[7] >= _MAX_VSYNC_HIGH_PERIOD))
            {
                break;
            }

            // Back up current V Sync Count
            ((WORD *)pData)[6] = ((WORD *)pData)[7];
        }

        // Check V Sync
        if((((WORD *)pData)[7] >= _MAX_VSYNC_HIGH_PERIOD) || (((WORD *)pData)[7] <= 0))
        {
            ucSyncType = _NO_SYNC_STATE;
        }
#else
        // Get Stable High Period
        CScalerRead(_STABLE_HIGH_PERIOD_H_4A, 2, pData, _AUTOINC);
        stModeInfo.IHSyncPulseCount = ((pData[0] & 0x07) << 8) | pData[1];
        CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
        stModeInfo.IHCount = ((pData[0] & 0x07) << 8) | pData[1];

        if(((stModeInfo.IHSyncPulseCount * 7 / stModeInfo.IHCount) != 0) || (stModeInfo.IHSyncPulseCount < 4))
        {
            ucSyncType = _NO_SYNC_STATE;
        }
#endif // End of // #if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        // V015 VGA Patch Note (3) Modify 20100611 End
    }

    return ucSyncType;
}

#endif   // End of #if(_HSYNC_DETECTION == _AUTO_RUN)

//--------------------------------------------------
// Description  : Modify VGA sync polarity
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSyncModifyPolarity(void)
{
    BYTE polarity;

    polarity = CScalerGetBit(_VGIP_SIGINV_11, 0xff);
    polarity &= ~(_BIT3 | _BIT2);

    if(!(bit)(stModeInfo.Polarity & _BIT0))
    {
        polarity |= _BIT2;
    }

    if(!(bit)(stModeInfo.Polarity & _BIT1))
    {
        polarity |= _BIT3;
    }

    CScalerSetByte(_VGIP_SIGINV_11, polarity);
}

//--------------------------------------------------
// Description  : Check SOY Mode same as SOG Mode
// Input Value  : None
// Output Value : Search Result
//--------------------------------------------------
BYTE CSyncDistinguishSogSoy(void)
{
    BYTE ucModeCnt = 0;

    for(ucModeCnt = 0; ucModeCnt < _MAX_PRESET_MODE; ucModeCnt++)
    {
        if(CModeComparePresetModeVGA(ucModeCnt) == _TRUE)
        {
            if(ucModeCnt == _MODE_640x480_60HZ)
            {
                return ucModeCnt;
            }
        }
    }

    return _MODE_NOSUPPORT;
}

// V013 VGA Patch Note (22) Modify 20100511 Start
// Patch Reason : Modify Capture Window Size for HEORV/OR Sync Type
//--------------------------------------------------
// Description  : Modify Capture Window For HEROV Sync Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSyncSetCaptureWindowfForHEORV(void)
{
    BYTE ucRef = 0;
    BYTE ucHSyncPulseCount = 0;
    BYTE ucVSyncPulseCount = 0;

    if(CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, _BIT7) != _BIT7)
    {
        return;
    }

    // V016 VGA Patch Note (13) Modify 20100831 Start
    // Patch Reason : Enable Coast Signal Cause Picture Distortion If H XOR V Type Was mistaken for Serration Type.
    // If input source is CS for SOG, Force Enable Coast function
    if(CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT1) == _BIT1)
    {
        // Get Hsync High Period
        CScalerRead(_STABLE_HIGH_PERIOD_H_4A, 2, pData, _AUTOINC);
        ((WORD *)pData)[1] = ((pData[0] & 0x07) << 8) | pData[1];

        // Get Hsync Stable Period
        CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
        ((WORD *)pData)[2] = ((pData[0] & 0x07) << 8) | pData[1];

        // Check HS Polarity, High Pulse Calculate By Positive Polarity.
        if(((WORD *)pData)[1] > (((WORD *)pData)[2] / 2))
        {
            ucHSyncPulseCount = (BYTE)(((WORD *)pData)[2] - ((WORD *)pData)[1]);
        }
        else
        {
            ucHSyncPulseCount = (BYTE)(((WORD *)pData)[1]);
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Formula :                                                                 //
        //              High Sync Pulse Count                                        //
        //          ------------------------------- = 0.220(us)                      //
        //            _INTERNAL_SYSTEM_CLK / 1000                                    //
        //                                                                           //
        // 0.220(us) Come From 1920x1440-60R (High Pulse is 0.173(us), give 57us tolerance)         //
        ///////////////////////////////////////////////////////////////////////////////

        // Reference Hsync High Pulse Width = 0.22us
        ucRef = (BYTE)((DWORD)_INTERNAL_SYSTEM_CLK * 22 / 100000 + 1);

        // Force Enable Coast Signal Function Limited High Pulse Less Than "ucRef" Width.
        if(ucHSyncPulseCount < ucRef)
        {
            CScalerSetDataPortBit(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_DETECT_TOLERANCE_SET_08, ~_BIT7, _BIT7);
        }
    }
    // V016 VGA Patch Note (13) Modify 20100831 End

    pData[0] = (CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, 0xff) & 0x70) >> 4;

    if((pData[0] == _XOR_OR_TYPE_CS_WITH_EQR) || (pData[0] == _XOR_OR_TYPE_CS_WITHOUT_EQR))
    {
        // V016 VGA Patch Note (13) Modify 20100831 Start
        // Patch Reason : Enable Coast Signal Cause Picture Distortion If H XOR V Type Was mistaken for Serration Type.
        // If input source is CS for SOG, Force Enable Coast function
        /*
        // Get Hsync High Period
        CScalerRead(_STABLE_HIGH_PERIOD_H_4A, 2, pData, _AUTOINC);
        ((WORD *)pData)[1] = ((pData[0] & 0x07) << 8) | pData[1];

        // Get Hsync Stable Period
        CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
        ((WORD *)pData)[2] = ((pData[0] & 0x07) << 8) | pData[1];

        if(((WORD *)pData)[1] > (((WORD *)pData)[2] / 2))
        {
            ucHSyncPulseCount = (BYTE)(((WORD *)pData)[2] - ((WORD *)pData)[1]);
        }
        else
        {
            ucHSyncPulseCount = (BYTE)(((WORD *)pData)[1]);
        }
        */
        // V016 VGA Patch Note (13) Modify 20100831 End

        ///////////////////////////////////////////////////////////////////////////////
        // Formula :                                                                 //
        //              High Sync Pulse Count                                        //
        //          ------------------------------- = 0.48(us)                       //
        //            _INTERNAL_SYSTEM_CLK / 1000                                    //
        ///////////////////////////////////////////////////////////////////////////////

        // Hsync High Pulse Width = 0.48us
        ucRef = (BYTE)((DWORD)_INTERNAL_SYSTEM_CLK * 48 / 100000 + 1);

        // If Hsync High Pulse less than 0.48us, Capture Window Must be samller.
        if(ucHSyncPulseCount > ucRef)
        {
            CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C, 0x08);
            CScalerSetByte(_SYNC_PROC_DATA_PORT_5D, 0x04);
            CSyncGetSyncTypeAutoRun();
        }
        else if((ucHSyncPulseCount == ucRef) || (ucHSyncPulseCount == ucRef - 1))
        {
            SET_VGA_INITIAL();
            CModeInitialVGA();

            // HSync Synchronize Source Select FeedbackHS
            CScalerSetBit(_SYNC_INVERT_48, ~_BIT0, _BIT0);

            if(CModeMeasureReady() == _TRUE)
            {
                // Pop up Measure Result
                CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT6, _BIT6);

                // Measure IVSyncPulseCount
                CScalerSetBit(_MEAS_HS_VS_HI_SEL_58, ~_BIT0, _BIT0);

                CScalerRead(_MEAS_HS_VS_HIGH_PERIOD_H_56, 2, &pData[8], _AUTOINC);
                ucVSyncPulseCount = (BYTE)(((pData[8] & 0xF0) << 4) | pData[9]) + 1;

                if(ucVSyncPulseCount <= 4)
                {
                    CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C, 0x08);
                    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D, 0x04);
                    CSyncGetSyncTypeAutoRun();
                }
            }

            CScalerSetBit(_SYNC_INVERT_48, ~_BIT0, 0x00);
        }
    }
}
// V013 VGA Patch Note (22) Modify 20100511 End
