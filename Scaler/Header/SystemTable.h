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
// ID Code      : SystemTable.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#ifdef __SCALER__

//----------------------------------------------------------------------------------------------------
// Reset Tables
//----------------------------------------------------------------------------------------------------
BYTE code tSCALER_RESET_TABLE[] =
{
    5,  _AUTOINC,       _WATCH_DOG_CTRL0_0C,            0x00,0x00,                          //CR[0C] ~ CR[0D]
    19, _AUTOINC,       _VGIP_CTRL_10,                  0x00,0x00,0x00,0x00,0x00,0x00,0x00, //CR[10] ~ CR[16]
                                                        0x00,0x00,0x00,0x00,0x00,0x00,0x00, //CR[17] ~ CR[1D]

                                                        // V016 System Patch Note (17) Modify 20100825 Start
                                                        // Patch Reason : Select CR[1F]-bit5:4 to Pin Share Part.
                                                        /*
                                                        0x00,0x00,                          //CR[1E] ~ CR[1F]
                                                        */
                                                        0x00,0x20,                          //CR[1E] ~ CR[1F]
                                                        // V016 System Patch Note (17) Modify 20100825 End


//    5,  _AUTOINC,       _VDISP_CTRL_28,                 0x00,0x00,                          //CR[28] ~ CR[29]
    6,  _AUTOINC,       _FIFO_ACCESS_PORT_30,           0x00,0x00,0x00,                     //CR[30] ~ CR[32]
    5,  _AUTOINC,       _FS_DELAY_FINE_TUNING_43,       0x00,0x00,                          //CR[43] ~ CR[44]
    6,  _AUTOINC,       _SYNC_SELECT_47,                0x00,0x00,0x00,                     //CR[47] ~ CR[49]
    5,  _AUTOINC,       _STABLE_MEASURE_4F,             0x08,0x00,

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    // V012 Modify 20100331 Start
    // V012 Patch Note (21) : Fix the sync processor compatibility problem. Replace slower XTAL clock with M2PLL.
    /*
    4,  _NON_AUTOINC,   _FIFO_FREQUENCY_22,             0x00,
    */

    // V013 VGA Patch Note (6) Modify 20100428 Start
    // Patch Reason : Update V012 Patch Note (21) use m2pll/10 as internal clock just in analog source.
    /*
    4,  _NON_AUTOINC,   _FIFO_FREQUENCY_22,             (0x03 | _INTERNAL_CLK_FLAG),
    */
    4,  _NON_AUTOINC,   _FIFO_FREQUENCY_22,             0x03,
    // V013 VGA Patch Note (6) Modify 20100428 End
    // V012 Modify 20100331 End
#endif

    4,  _NON_AUTOINC,   _SYNC_PROC_ACCESS_PORT_5C,      _SYNC_G_CLAMP_START_00,

    // V013 VGA Patch Note (22) Modify 20100511 Start
    // Patch Reason : Modify Capture Window Size for HEORV/OR Sync Type
    /*
    13, _NON_AUTOINC,   _SYNC_PROC_DATA_PORT_5D,        0x04,0x10,0x04,0x10,0x02,0x01,0x30,0x21,0x04,0x80,  // For Measure Time Out Issue
    */
    13, _NON_AUTOINC,   _SYNC_PROC_DATA_PORT_5D,        0x04,0x10,0x04,0x10,0x02,0x01,0x30,0x21,0x20,0x80,
    // V013 VGA Patch Note (22) Modify 20100511 End

#if((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_RSDS_PWR_CTL_C3,
    4,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x03,
#endif

#if(_SCALER_TYPE == _RTD2472D)
    5,  _AUTOINC,       _YUV2RGB_CTRL_9C,               0x02,0x00, // turn off color space  !!
    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,               0x00,
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    4,  _NON_AUTOINC,   _YUV_RGB_CTRL_9C,               0x00,

#else
    No Setting !!
#endif

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE0,
    6,  _AUTOINC,       _P0_ADC_RED_CTL_CF,             0x40,0x40,0x40,

// Setting SOG1 Sync Compare Level before DC Restore.
#if(_SCALER_TYPE == _RTD2472D)
    4,  _NON_AUTOINC,   _P0_ADC_POWER_SOG_SOY_CTL_BA,   0x10,
#elif((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    4,  _NON_AUTOINC,   _P0_ADC_POWER_SOG_SOY_CTL_BA,   0x10,
#endif

#if(_SCALER_TYPE == _RTD2545LR)
    4,  _NON_AUTOINC,   _P0_ADC_POWER_C6,               0x68,
#else
    4,  _NON_AUTOINC,   _P0_ADC_POWER_C6,               0x78,
#endif

    4,  _NON_AUTOINC,   _P0_ADC_V_BIAS1_CD,             0x09,
    6,  _AUTOINC,       _P0_ADC_SOG_CMP_D2,             0x00, 0x00, 0x00, //for Mux select, DC Restore/Clamp Enable
    4,  _AUTOINC,       _P0_ADC_CLAMP_CTRL2_D6,         0xA8,

#if((_BJT_SUPPORT != _ON) && (_SCALER_TYPE == _RTD2545LR))
    4,  _NON_AUTOINC,   _P0_EBD_REGLATOR_VOL_DF,        0x02,
#endif

    4,  _NON_AUTOINC,   _P0_HS_SCHMITT_TRIGGER_CTRL_F4, 0xe9,
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE1,
    4,  _NON_AUTOINC,   _P1_FAST_PLL_CTRL_AA,           0x00,
    4,  _NON_AUTOINC,   _P1_MIX_B0,                     0x00,

#if(_SCALER_TYPE == _RTD2472D)                         //for power saving to wake up
    7,  _AUTOINC,       _P1_DPLL_OTHER_C3,              0x16,0x10,0x00,0x04,
    4,  _NON_AUTOINC,   _P1_MULTIPLY_PLL_CTRL0_E0,      0x10,
#else
    6,  _AUTOINC,       _P1_DCLK_FINE_TUNE_OFFSET_MSB_C4,               0x10,0x00,0x04,


#if(_RTD_XTAL == _XTAL27000K)
    5,  _AUTOINC,   _P1_M2PLL_M_E0,                     0x69, 0x13,
#elif(_RTD_XTAL == _XTAL24000K)
    5,  _AUTOINC,   _P1_M2PLL_M_E0,                     0x63, 0x13,
#elif(_RTD_XTAL == _XTAL14318K)
    5,  _AUTOINC,   _P1_M2PLL_M_E0,                     0xA8, 0x13,

// V012 Modify 20100331 Start
// V012 Patch Note (21) : Fix the sync processor compatibility problem. Replace slower XTAL clock with M2PLL.
/*
#elif(_RTD_XTAL == _XTAL24576K)
    5,  _AUTOINC,   _P1_M2PLL_M_E0,                     0x61, 0x13,
*/
// V012 Modify 20100331 End

#else
    No Setting !!
#endif

#endif

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE2,
    4,  _NON_AUTOINC,   _P2_UP_DOWN_CTRL0_B5,            0x58,
    4,  _NON_AUTOINC,   _P2_TMDS_DPC1_B8,                0x0C,

    4,  _NON_AUTOINC,   _P2_TMDS_OUTPUT_CTRL_A6,         0x78,
    7,  _AUTOINC,       _P2_TMDS_ACC0_A8 ,               0x03,0x00,0x31,0x70,
    4,  _NON_AUTOINC,   _P2_CPS_AD,                      0x24,

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE5,
    4,  _NON_AUTOINC,   _P5_SDRF_IN1_LINE_NUM_H_B7,     0x10,
    4,  _NON_AUTOINC,   _P5_SDRF_MN_LINE_NUM_H_CD,      0x10,
    4,  _NON_AUTOINC,   _P5_SDRF_MN_DISP_CTRL_CF,       0X05,
    4,  _NON_AUTOINC,   _P5_SDRF_MN_SDR_STATUS_D0,      0x10,
#endif

// Setting SOG0 Sync Compare Level before DC Restore.
#if(_SCALER_TYPE == _RTD2472D)
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE6,
    4,  _NON_AUTOINC,   _P6_SOY_CH0_CFG3_C3,            0x10,
#endif

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE0,
    4,  _NON_AUTOINC,   _P0_ADC_SOG_DAC_SOY_CONTROL_D7, 0x10,
#endif

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE7,
    5,  _AUTOINC,       _P7_YUV2RGB_CTRL_BF,            0x02,0x00,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,            0x00,
#endif

#if(_DCR_MODE != _DCR_TYPE_OFF)
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE7,
    4,  _NON_AUTOINC,   _P7_DCR_ACCESS_PORT_D8,         0x00,

#if((_DCR_MODE == _DCR_TYPE_1) || (_DCR_MODE == _DCR_TYPE_2))
    4,  _NON_AUTOINC,   _P7_DCR_DATA_PORT_D9,           0x04,
#endif

    4,  _NON_AUTOINC,   _P7_DCR_ACCESS_PORT_D8,         0x01,
#endif

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGEB,

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    4,  _NON_AUTOINC,   _PB_DP_CDR_03_A3,               0x8C,
#endif

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE3,
    _END
};


//----------------------------------------------------------------------------------------------------
// Initial Tables
//----------------------------------------------------------------------------------------------------
BYTE code tSCALER_POWERUP_INITIAL[] =
{
    4,  _NON_AUTOINC,   _HOST_CTRL_01,                  0x40,
    4,  _NON_AUTOINC,   _IRQ_CTRL0_04,                  0x80,

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    // V012 Modify 20100331 Start
    // V012 Patch Note (21) : Fix the sync processor compatibility problem. Replace slower XTAL clock with M2PLL.
    /*
    4,  _NON_AUTOINC,   _FIFO_FREQUENCY_22,             0x03, //fifo:M2PLL, xtal
    */

    // V013 VGA Patch Note (6) Modify 20100428 Start
    // Patch Reason : Update V012 Patch Note (21) use m2pll/10 as internal clock just in analog source.
    /*
    4,  _NON_AUTOINC,   _FIFO_FREQUENCY_22,(0x03 | _INTERNAL_CLK_FLAG), // Fifo:M2PLL, xtal
    */
    4,  _NON_AUTOINC,   _FIFO_FREQUENCY_22,             0x03,
    // V013 VGA Patch Note (6) Modify 20100428 End
    // V012 Modify 20100331 End
#endif

    4,  _NON_AUTOINC,   _HDMI_STATUS0_05,               0x80,
    4,  _NON_AUTOINC,   _MEAS_HS_VS_HI_SEL_58,          0x00,
    4,  _NON_AUTOINC,   _COLOR_CTRL_62,                 0x03,
    4,  _NON_AUTOINC,   _GAMMA_CTRL_67,                 0x00,
    4,  _NON_AUTOINC,   _OVERLAY_CTRL_6C,               0x00,
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_CTRL0_00,
    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x01,0x00,0x00,0x00,0x00,0x00,
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_RSDS_PWR_CTL_C3,
    4,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x03,

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE0,
    4,  _NON_AUTOINC,   _P0_ADC_V_BIAS1_CD,             0x09,
    4,  _NON_AUTOINC,   _P0_ADC_RGB_CTRL_CE,            0x8E,

#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    4,  _NON_AUTOINC,   _P0_POWER_ON_RESET_F3,          0x43,
#else
    4,  _NON_AUTOINC,   _P0_POWER_ON_RESET_F3,          0xc3,
#endif

    4,  _NON_AUTOINC,   _P0_HS_SCHMITT_TRIGGER_CTRL_F4, 0xe9,

    4,  _AUTOINC,       _P0_ADC_CLAMP_CTRL2_D6,         0xA8,

#if((_BJT_SUPPORT != _ON) && (_SCALER_TYPE == _RTD2545LR))
    4,  _NON_AUTOINC,   _P0_EBD_REGLATOR_VOL_DF,        0x02,
#endif

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE1,
    7,  _AUTOINC,       _P1_PLL_DIV_CTRL_A0,            0x04,0x47,0x00,0x18,
    4,  _NON_AUTOINC,   _P1_PLL_PHASE_INTERPOLATION_B5, 0x50,
    4,  _NON_AUTOINC,   _P1_DDS_MIX_1_B8,               0x0E,

#if(_SCALER_TYPE == _RTD2472D)
    7,  _AUTOINC,       _P1_DPLL_OTHER_C3,              0x16,0x10,0x00,0x04,
    4,  _NON_AUTOINC,   _P1_MULTIPLY_PLL_CTRL3_E5,      0x09,
    4,  _NON_AUTOINC,   _P1_MULTIPLY_PLL_CTRL0_E0,      0x10,
#else
    6,  _AUTOINC,   _P1_DCLK_FINE_TUNE_OFFSET_MSB_C4,    0x10,0x00,0x04,
    4,  _NON_AUTOINC,   _P1_M2PLL_WD_E5,        0x18,

#if(_RTD_XTAL == _XTAL27000K)
    5,  _AUTOINC,   _P1_M2PLL_M_E0,                     0x69, 0x13,
#elif(_RTD_XTAL == _XTAL24000K)
    5,  _AUTOINC,   _P1_M2PLL_M_E0,                     0x63, 0x13,
#elif(_RTD_XTAL == _XTAL14318K)
    5,  _AUTOINC,   _P1_M2PLL_M_E0,                     0xA8, 0x13,

// V012 Modify 20100331 Start
// V012 Patch Note (21) : Fix the sync processor compatibility problem. Replace slower XTAL clock with M2PLL.
/*
#elif(_RTD_XTAL == _XTAL24576K)
    5,  _AUTOINC,   _P1_M2PLL_M_E0,                     0x61, 0x13,
*/
// V012 Modify 20100331 End

#else
    No Setting !!
#endif

#endif

#if(_AUDIO_SUPPORT == _ON)
    4,  _NON_AUTOINC,   _V8_YUV_CONVERSION_1F,          0x10,  // For audio pin share
    9,  _AUTOINC,       _P1_BB_POWER0_F0,               0xff,0xff,0x27, 0x27,0x30,0xc0,
#else
    4,  _NON_AUTOINC,   _V8_YUV_CONVERSION_1F,          0x00,  // For audio pin share
    9,  _AUTOINC,       _P1_BB_POWER0_F0,               0xff,0xff,0x27, 0x27,0xff,0xc0,
#endif

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE2,
    4,  _NON_AUTOINC,   _P2_UP_DOWN_CTRL0_B5,            0x58,
    4,  _NON_AUTOINC,   _P2_TMDS_DPC1_B8,                0x0C,

    4,  _NON_AUTOINC,   _P2_HDMI_APC_C8,                0x01,// For DVI/HDMI enable

    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_BCHCR_02,// Enable BCH function
    4,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x0e,
    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_AVMCR_30,

#if(_HDMI_SUPPORT == _ON)
    7,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x68,0x00,0x81,0x01,// For Audio Output Enable and Mute
#elif(_TMDS_SUPPORT == _ON)
    4,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x08,// Enable Video Output
#endif

#if(_HDMI_SUPPORT == _ON)
    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_PVGCR0_45,
    5,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x09,0x00,//For HDMI Packet
    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_ACRCR_51,
    4,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x44,//For HDMI Color space auto switch between 4:2:2/4:4:4
    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_DPCR0_38,
    4,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x00,//Power On Audio PLL
    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_AFCR_03,
    4,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x06,//Enable Audio FIFO
    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_AOCR_62,
    4,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x00,//Disable SPDIF/I2S Output
#endif

    4,  _NON_AUTOINC,   _P2_HDCP_PORT_CTRL_C2,          0x01,
    4,  _NON_AUTOINC,   _DISP_ACCESS_PORT_2A,           _DISP_NEW_DV_DLY_23,
    4,  _NON_AUTOINC,   _DISP_DATA_PORT_2B,             0x40,
    4,  _NON_AUTOINC,   _DISP_ACCESS_PORT_2A,           _DISP_NEW_DV_CTRL_22,
    4,  _NON_AUTOINC,   _DISP_DATA_PORT_2B,             0xa0,

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,               _PAGE4,//SDRAM Setting
#if(_MEMORY_WORK_TYPE != _OD_OFF_FRC_OFF)
#if(_MEMORY_CONFIG == _1M_16BIT_1PCE)
        9,  _AUTOINC,       _P4_SDR_CTRL0_A1,               _SDR_ROW_DELAY,_SDR_COL_DELAY,0x0d,0x83,0x23,0x00,
#elif(_MEMORY_CONFIG == _1M_16BIT_2PCE)
        9,  _AUTOINC,       _P4_SDR_CTRL0_A1,               _SDR_ROW_DELAY,_SDR_COL_DELAY,0x0d,0x83,0x63,0x00,
#elif(_MEMORY_CONFIG == _2M_32BIT_1PCE)
        9,  _AUTOINC,       _P4_SDR_CTRL0_A1,               _SDR_ROW_DELAY,_SDR_COL_DELAY,0x0d,0x83,0x83,0x00,
#elif(_MEMORY_CONFIG == _2M_32BIT_2PCE)
        9,  _AUTOINC,       _P4_SDR_CTRL0_A1,               _SDR_ROW_DELAY,_SDR_COL_DELAY,0x0d,0x83,0xc3,0x00,
#endif

#if(_MEMORY_WORK_TYPE == _OD_ON_FRC_OFF)
        14, _AUTOINC,      _P4_SDR_AREF_CNT_A7,             0xc0,0x00,0x00,0x11,0x22,0x00,0x00,0x00,0x00,0x44,0x88,
#elif(_MEMORY_WORK_TYPE == _OD_OFF_FRC_ON)
        14, _AUTOINC,      _P4_SDR_AREF_CNT_A7,             0xc0,0x00,0x00,0x11,0x22,0x44,0x00,0x88,0x00,0x00,0x00,
#elif(_MEMORY_WORK_TYPE == _OD_ON_FRC_ON)
        14, _AUTOINC,      _P4_SDR_AREF_CNT_A7,             0xc0,0x00,0x00,0x11,0x22,0x40,0x00,0x80,0x00,0x04,0x08,
#endif


#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE5,
    4,  _NON_AUTOINC,   _P5_SDRF_IN1_LINE_NUM_H_B7,     0x10,
    4,  _NON_AUTOINC,   _P5_SDRF_MN_LINE_NUM_H_CD,      0x10,
    4,  _NON_AUTOINC,   _P5_SDRF_MN_DISP_CTRL_CF,       0X05,
    4,  _NON_AUTOINC,   _P5_SDRF_MN_SDR_STATUS_D0,      0x10,
#endif


#if(_SCALER_TYPE == _RTD2545LR)
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,               _PAGEE,
#if(_MEMORY_CONFIG == _1M_16BIT_1PCE)
    4,  _NON_AUTOINC,   _PE_PIN_SHARE_CTRL00_D4,       0x04,
#else
    4,  _NON_AUTOINC,   _PE_PIN_SHARE_CTRL00_D4,       0x06,
#endif
#else
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,               _PAGE10,
#if(_MEMORY_CONFIG == _1M_16BIT_1PCE)
    4,  _NON_AUTOINC,   _P10_PIN_SHARE_CTRL14_B7,      0x04,
#elif(_MEMORY_CONFIG == _1M_16BIT_2PCE)
    4,  _NON_AUTOINC,   _P10_PIN_SHARE_CTRL14_B7,      0x05,
#elif(_MEMORY_CONFIG == _2M_32BIT_1PCE)
    4,  _NON_AUTOINC,   _P10_PIN_SHARE_CTRL14_B7,      0x07,
#endif
#endif // End of #if(_SCALER_TYPE == _RTD2545LR)

#endif // End of #if(_MEMORY_CONFIG != _OD_OFF_FRC_OFF)

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGEB,
    4,  _NON_AUTOINC,   _PB_DP_RESERVED_01_BB,          0xc0,
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE3,
    _END
};


//----------------------------------------------------------------------------------------------------
// Display Interface Initial
//----------------------------------------------------------------------------------------------------
#if(_PANEL_STYLE == _PANEL_TTL)

BYTE code tTTL_INITIAL[] =
{
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             _TCON_CTRL0_00,0x00,

    4,  _NON_AUTOINC,   _DISP_ACCESS_PORT_2A,           _DISP_TIMING_20,
    4,  _NON_AUTOINC,   _DISP_DATA_PORT_2B,             0x02,

    _END
};
#endif // End of #if(_PANEL_STYLE == _PANEL_TTL)


#if(_PANEL_STYLE == _PANEL_LVDS)

BYTE code tLVDS_INITIAL[] =
{
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             _TCON_CTRL0_00,0x01,
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_LVDS_CTRL0_A0,

#if(_LVDS_TABLE_TYPE == 1)
//    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x40,0x13,0x83,0x1c,0x80,0x80,
    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x40,0x16,0x42,0x9c,0x80,0x80,
#elif(_LVDS_TABLE_TYPE == 2)
//    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x40,0x13,0x83,0x1d,0x80,0x80,
    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x40,0x16,0x42,0x9d,0x80,0x80,
#endif

    _END
};

#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)


#if(_PANEL_STYLE == _PANEL_RSDS)

BYTE code tRSDS_INITIAL[] =
{

    // AUO RSDS Panel  Model :M170E805 V.1   50 Pin , 30 Pin
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_LVDS_CTRL1_A1,
    5,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x12,0x43,


    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             _TCON_CTRL0_00,0x82, // Switch to RSDS
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             _TCON_CTRL1_01,0x00,

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             _TCON_RSDS_INTERLEAVING_H_C1,0x06,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             _TCON_RSDS_INTERLEAVING_L_C2,0x70,

    //TCON1  FXDIO
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON1_V_STA_LSB_10,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0x90,0x22,0x95,0x80,

    //TCON6    XSTB
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON6_V_STA_LSB_38,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0x35,0x22,0xac,0x80,

    //TCON7    POL
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON7_V_STA_LSB_40,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0d,0x00,0x00,0x02,0x88,

    //TCON4  BXDIO
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON4_V_STA_LSB_28,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0xb4,0x22,0xb9,0x80,

    //TCON5 YCLK
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON5_V_STA_LSB_30,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0xf4,0x21,0x94,0x80,

    //TCON11 YDIO
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON11_V_STA_LSB_60,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x00,0x0e,0xd0,0x33,0xd7,0x88,

    //TCON13 YOE
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON13_V_STA_LSB_70,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0x94,0x52,0x14,0x80,

    _END
};

#endif // End of #if(_PANEL_STYLE == _PANEL_RSDS)

//----------------------------------------------------------------------------------------------------
// OSD Power Up Initial
//----------------------------------------------------------------------------------------------------
BYTE code tOSD_POWERUP_INITIAL[] =
{
    6,  _AUTOINC,       _OSD_ADDR_MSB_90,               0x40,0x02,0x10,
    6,  _AUTOINC,       _OSD_ADDR_MSB_90,               0x00,0x03,0x30,
    6,  _AUTOINC,       _OSD_ADDR_MSB_90,               0x40,0x03,0x08,

    4,  _NON_AUTOINC,   _DISP_ACCESS_PORT_2A,           _DISP_OSD_REFERENCE_DEN_21,
    4,  _NON_AUTOINC,   _DISP_DATA_PORT_2B,             0x02,

    _END
};


#else //__SCALER__

extern BYTE code tSCALER_RESET_TABLE[];
extern BYTE code tSCALER_POWERUP_INITIAL[];

#if(_PANEL_STYLE == _PANEL_TTL)
extern BYTE code tTTL_INITIAL[];
#endif

#if(_PANEL_STYLE == _PANEL_LVDS)
extern BYTE code tLVDS_INITIAL[];
#endif

#if(_PANEL_STYLE == _PANEL_RSDS)
extern BYTE code tRSDS_INITIAL[];
#endif

extern BYTE code tOSD_POWERUP_INITIAL[];

#endif //__SCALER__

#ifdef __FRAMESYNC__

BYTE code tDCLK_OFFSET[16] =
{
    0,   0,  0,  0,
    0,   0,  0,  0,
    0,   0,  0,  0,
    0,   0,  0,  0,
};


#else //__FRAMESYNC__

extern BYTE code tDCLK_OFFSET[];

#endif //__FRAMESYNC__



#ifdef __REALTEK_EEPROM__

//----------------------------------------------------------------------------------------------------
// EDID Table
//----------------------------------------------------------------------------------------------------
BYTE code tEDID_TABLE_A0[] =
{
    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x4A,0x8B,0x3B,0x2A,0x01,0x01,0x01,0x01,
    0x1E,0x13,0x01,0x03,0x0E,0x33,0x1D,0x78,0xEF,0x8A,0x01,0x9A,0x58,0x52,0x8B,0x28,
    0x1E,0x50,0x54,0xEF,0xEF,0x80,0x81,0xC0,0xA9,0xC0,0xD1,0xC0,0x95,0x00,0x81,0x40,
    0x81,0x80,0x90,0x40,0xA9,0x40,0x7D,0x4B,0x80,0xA0,0x72,0xB0,0x2D,0x40,0x50,0xC8,
    0x46,0x48,0xFE,0x22,0x11,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,0x55,0x0A,
    0x6E,0x15,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x52,
    0x54,0x44,0x20,0x4D,0x6F,0x6E,0x69,0x74,0x6F,0x72,0x0A,0x20,0x00,0x00,0x00,0xFF,
    0x00,0x52,0x54,0x44,0x30,0x31,0x30,0x32,0x30,0x33,0x30,0x34,0x0A,0x20,0x00,0xE5,
};

BYTE code tEDID_TABLE_D0[] =
{

#if((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_DVI_I_PORT))

    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x4A,0x8B,0x3B,0x2A,0x01,0x01,0x01,0x01,
    0x1E,0x13,0x01,0x03,0x81,0x33,0x1D,0x78,0xEF,0x8A,0x01,0x9A,0x58,0x52,0x8B,0x28,
    0x1E,0x50,0x54,0xEF,0xEF,0x80,0x81,0xC0,0xA9,0xC0,0xD1,0xC0,0x95,0x00,0x81,0x40,
    0x81,0x80,0x90,0x40,0xA9,0x40,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
    0x45,0x00,0xFE,0x22,0x11,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,0x55,0x0A,
    0x6E,0x15,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x52,
    0x54,0x44,0x20,0x4D,0x6F,0x6E,0x69,0x74,0x6F,0x72,0x0A,0x20,0x00,0x00,0x00,0xFF,
    0x00,0x52,0x54,0x44,0x30,0x31,0x30,0x32,0x30,0x33,0x30,0x34,0x0A,0x20,0x00,0xDC,
    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x4A,0x8B,0x3B,0x2A,0x01,0x01,0x01,0x01,
    0x1E,0x13,0x01,0x03,0x81,0x33,0x1D,0x78,0xEF,0x8A,0x01,0x9A,0x58,0x52,0x8B,0x28,
    0x1E,0x50,0x54,0xEF,0xEF,0x80,0x81,0xC0,0xA9,0xC0,0xD1,0xC0,0x95,0x00,0x81,0x40,
    0x81,0x80,0x90,0x40,0xA9,0x40,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
    0x45,0x00,0xFE,0x22,0x11,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,0x55,0x0A,
    0x6E,0x15,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x52,
    0x54,0x44,0x20,0x4D,0x6F,0x6E,0x69,0x74,0x6F,0x72,0x0A,0x20,0x00,0x00,0x00,0xFF,
    0x00,0x52,0x54,0x44,0x30,0x31,0x30,0x32,0x30,0x33,0x30,0x34,0x0A,0x20,0x00,0xDC,

#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)

    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x4A,0x8B,0x3B,0x2A,0x01,0x01,0x01,0x01,
    0x1E,0x13,0x01,0x04,0xA2,0x33,0x1D,0x78,0xF7,0x8A,0x01,0x9A,0x58,0x52,0x8B,0x28,
    0x1E,0x50,0x54,0xEF,0xEF,0x80,0x81,0xC0,0xA9,0xC0,0xD1,0xC0,0x95,0x00,0x81,0x40,
    0x81,0x80,0x90,0x40,0xA9,0x40,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
    0x45,0x00,0xFE,0x22,0x11,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,0x55,0x0A,
    0x6E,0x15,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x52,
    0x54,0x44,0x20,0x4D,0x6F,0x6E,0x69,0x74,0x6F,0x72,0x0A,0x20,0x00,0x00,0x00,0xFF,
    0x00,0x52,0x54,0x44,0x30,0x31,0x30,0x32,0x30,0x33,0x30,0x34,0x0A,0x20,0x01,0xB1,
    0x02,0x03,0x23,0xF1,0x4E,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x90,0x91,0x92,0x93,
    0x94,0x95,0x96,0x23,0x09,0x7F,0x07,0x83,0x7F,0x00,0x00,0x67,0x03,0x0C,0x00,0x10,
    0x00,0x28,0xDE,0x8C,0x0A,0xD0,0x90,0x20,0x40,0x31,0x20,0x0C,0x40,0x55,0x00,0x54,
    0x0E,0x11,0x00,0x00,0x18,0x01,0x1D,0x80,0x18,0x71,0x1C,0x16,0x20,0x58,0x2C,0x25,
    0x00,0x54,0x0E,0x11,0x00,0x00,0x9E,0x8C,0x0A,0xA0,0x14,0x51,0xF0,0x16,0x00,0x26,
    0x7C,0x43,0x00,0x54,0x0E,0x11,0x00,0x00,0x98,0x8C,0x0A,0xD0,0x8A,0x20,0xE0,0x2D,
    0x10,0x10,0x3E,0x96,0x00,0x54,0x0E,0x11,0x00,0x00,0x18,0x8C,0x0A,0xA0,0x20,0x51,
    0x20,0x18,0x10,0x18,0x7E,0x23,0x00,0x54,0x0E,0x11,0x00,0x00,0x18,0x00,0x00,0x52,

#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x4A,0x8B,0x3B,0x2A,0x01,0x01,0x01,0x01,
    0x1E,0x13,0x01,0x04,0xA5,0x33,0x1D,0x78,0xEF,0x8A,0x01,0x9A,0x58,0x52,0x8B,0x28,
    0x1E,0x50,0x54,0xEF,0xEF,0x80,0x81,0xC0,0xA9,0xC0,0xD1,0xC0,0x95,0x00,0x81,0x40,
    0x81,0x80,0x90,0x40,0xA9,0x40,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
    0x45,0x00,0xFE,0x22,0x11,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,0x55,0x0A,
    0x6E,0x15,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x52,
    0x54,0x44,0x20,0x4D,0x6F,0x6E,0x69,0x74,0x6F,0x72,0x0A,0x20,0x00,0x00,0x00,0xFF,
    0x00,0x52,0x54,0x44,0x30,0x31,0x30,0x32,0x30,0x33,0x30,0x34,0x0A,0x20,0x01,0xB6,
    0x02,0x03,0x18,0xF0,0x44,0x01,0x02,0x03,0x04,0x23,0x09,0x7F,0x07,0x83,0x7F,0x00,
    0x00,0x66,0x03,0x0C,0x00,0x10,0x00,0x80,0xD5,0x09,0x80,0xA0,0x20,0xE0,0x2D,0x10,
    0x10,0x60,0xA2,0x00,0xFE,0x1F,0x11,0x00,0x00,0x18,0x8C,0x0A,0xD0,0x8A,0x20,0xE0,
    0x2D,0x10,0x10,0x3E,0x96,0x00,0xFE,0x1F,0x11,0x00,0x00,0x18,0x8C,0x0A,0xD0,0x8A,
    0x20,0xE0,0x2D,0x10,0x10,0x3E,0x96,0x00,0xFE,0x1F,0x11,0x00,0x00,0x18,0x01,0x1D,
    0x00,0x72,0x51,0xD0,0x1E,0x20,0x6E,0x28,0x55,0x00,0xFE,0x1F,0x11,0x00,0x00,0x1E,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x85,

#else

   0x00,

#endif
};

BYTE code tEDID_TABLE_D1[] =
{
#if((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_I_PORT))

    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x4A,0x8B,0x3B,0x2A,0x01,0x01,0x01,0x01,
    0x1E,0x13,0x01,0x03,0x81,0x33,0x1D,0x78,0xEF,0x8A,0x01,0x9A,0x58,0x52,0x8B,0x28,
    0x1E,0x50,0x54,0xEF,0xEF,0x80,0x81,0xC0,0xA9,0xC0,0xD1,0xC0,0x95,0x00,0x81,0x40,
    0x81,0x80,0x90,0x40,0xA9,0x40,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
    0x45,0x00,0xFE,0x22,0x11,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,0x55,0x0A,
    0x6E,0x15,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x52,
    0x54,0x44,0x20,0x4D,0x6F,0x6E,0x69,0x74,0x6F,0x72,0x0A,0x20,0x00,0x00,0x00,0xFF,
    0x00,0x52,0x54,0x44,0x30,0x31,0x30,0x32,0x30,0x33,0x30,0x34,0x0A,0x20,0x00,0xDC,
    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x4A,0x8B,0x3B,0x2A,0x01,0x01,0x01,0x01,
    0x1E,0x13,0x01,0x03,0x81,0x33,0x1D,0x78,0xEF,0x8A,0x01,0x9A,0x58,0x52,0x8B,0x28,
    0x1E,0x50,0x54,0xEF,0xEF,0x80,0x81,0xC0,0xA9,0xC0,0xD1,0xC0,0x95,0x00,0x81,0x40,
    0x81,0x80,0x90,0x40,0xA9,0x40,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
    0x45,0x00,0xFE,0x22,0x11,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,0x55,0x0A,
    0x6E,0x15,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x52,
    0x54,0x44,0x20,0x4D,0x6F,0x6E,0x69,0x74,0x6F,0x72,0x0A,0x20,0x00,0x00,0x00,0xFF,
    0x00,0x52,0x54,0x44,0x30,0x31,0x30,0x32,0x30,0x33,0x30,0x34,0x0A,0x20,0x00,0xDC,

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)

    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x4A,0x8B,0x3B,0x2A,0x01,0x01,0x01,0x01,
    0x1E,0x13,0x01,0x04,0xA2,0x33,0x1D,0x78,0xF7,0x8A,0x01,0x9A,0x58,0x52,0x8B,0x28,
    0x1E,0x50,0x54,0xEF,0xEF,0x80,0x81,0xC0,0xA9,0xC0,0xD1,0xC0,0x95,0x00,0x81,0x40,
    0x81,0x80,0x90,0x40,0xA9,0x40,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
    0x45,0x00,0xFE,0x22,0x11,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,0x55,0x0A,
    0x6E,0x15,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x52,
    0x54,0x44,0x20,0x4D,0x6F,0x6E,0x69,0x74,0x6F,0x72,0x0A,0x20,0x00,0x00,0x00,0xFF,
    0x00,0x52,0x54,0x44,0x30,0x31,0x30,0x32,0x30,0x33,0x30,0x34,0x0A,0x20,0x01,0xB1,
    0x02,0x03,0x23,0xF1,0x4E,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x90,0x91,0x92,0x93,
    0x94,0x95,0x96,0x23,0x09,0x7F,0x07,0x83,0x7F,0x00,0x00,0x67,0x03,0x0C,0x00,0x10,
    0x00,0x28,0xDE,0x8C,0x0A,0xD0,0x90,0x20,0x40,0x31,0x20,0x0C,0x40,0x55,0x00,0x54,
    0x0E,0x11,0x00,0x00,0x18,0x01,0x1D,0x80,0x18,0x71,0x1C,0x16,0x20,0x58,0x2C,0x25,
    0x00,0x54,0x0E,0x11,0x00,0x00,0x9E,0x8C,0x0A,0xA0,0x14,0x51,0xF0,0x16,0x00,0x26,
    0x7C,0x43,0x00,0x54,0x0E,0x11,0x00,0x00,0x98,0x8C,0x0A,0xD0,0x8A,0x20,0xE0,0x2D,
    0x10,0x10,0x3E,0x96,0x00,0x54,0x0E,0x11,0x00,0x00,0x18,0x8C,0x0A,0xA0,0x20,0x51,
    0x20,0x18,0x10,0x18,0x7E,0x23,0x00,0x54,0x0E,0x11,0x00,0x00,0x18,0x00,0x00,0x52,

#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x4A,0x8B,0x3B,0x2A,0x01,0x01,0x01,0x01,
    0x1E,0x13,0x01,0x04,0xA5,0x33,0x1D,0x78,0xEF,0x8A,0x01,0x9A,0x58,0x52,0x8B,0x28,
    0x1E,0x50,0x54,0xEF,0xEF,0x80,0x81,0xC0,0xA9,0xC0,0xD1,0xC0,0x95,0x00,0x81,0x40,
    0x81,0x80,0x90,0x40,0xA9,0x40,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
    0x45,0x00,0xFE,0x22,0x11,0x00,0x00,0x1E,0x00,0x00,0x00,0xFD,0x00,0x32,0x55,0x0A,
    0x6E,0x15,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x52,
    0x54,0x44,0x20,0x4D,0x6F,0x6E,0x69,0x74,0x6F,0x72,0x0A,0x20,0x00,0x00,0x00,0xFF,
    0x00,0x52,0x54,0x44,0x30,0x31,0x30,0x32,0x30,0x33,0x30,0x34,0x0A,0x20,0x01,0xB6,
    0x02,0x03,0x18,0xF0,0x44,0x01,0x02,0x03,0x04,0x23,0x09,0x7F,0x07,0x83,0x7F,0x00,
    0x00,0x66,0x03,0x0C,0x00,0x10,0x00,0x80,0xD5,0x09,0x80,0xA0,0x20,0xE0,0x2D,0x10,
    0x10,0x60,0xA2,0x00,0xFE,0x1F,0x11,0x00,0x00,0x18,0x8C,0x0A,0xD0,0x8A,0x20,0xE0,
    0x2D,0x10,0x10,0x3E,0x96,0x00,0xFE,0x1F,0x11,0x00,0x00,0x18,0x8C,0x0A,0xD0,0x8A,
    0x20,0xE0,0x2D,0x10,0x10,0x3E,0x96,0x00,0xFE,0x1F,0x11,0x00,0x00,0x18,0x01,0x1D,
    0x00,0x72,0x51,0xD0,0x1E,0x20,0x6E,0x28,0x55,0x00,0xFE,0x1F,0x11,0x00,0x00,0x1E,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x85,

#else

   0x00,

#endif

};

#else // __REALTEK_EEPROM__

extern BYTE code tEDID_TABLE_A0[];
extern BYTE code tEDID_TABLE_D0[];
extern BYTE code tEDID_TABLE_D1[];

#endif // __REALTEK_EEPROM__

#ifdef __ADJUST__

//----------------------------------------------------------------------------------------------------
// HDCP Key Table
//----------------------------------------------------------------------------------------------------
#if(_HDCP_SUPPORT == _ON)

#if(_EMBEDDED_HDCP_KEY == _ON)

BYTE code tHDCP_CTRL[] =
{
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE2,
    5,  _AUTOINC,       _P2_HDCP_ADDR_PORT_C3,          0x00,0xb7,
    5,  _AUTOINC,       _P2_HDCP_ADDR_PORT_C3,          0x01,0x28,
    5,  _AUTOINC,       _P2_HDCP_ADDR_PORT_C3,          0x02,0xa9,
    5,  _AUTOINC,       _P2_HDCP_ADDR_PORT_C3,          0x03,0x51,
    5,  _AUTOINC,       _P2_HDCP_ADDR_PORT_C3,          0x04,0xd6,
    5,  _AUTOINC,       _P2_HDCP_ADDR_PORT_C3,          0x40,0x91,

    _END
};

BYTE code tHDCP_KEY_TABLE[] =
{
    0x3a, 0x21, 0x17, 0x06, 0x72, 0x60, 0x3b, 0x6e,     // Key0
    0x0c, 0x58, 0x16, 0x4c, 0x5b, 0x3b, 0x68, 0x4b,     // Key1
    0x2f, 0x7b, 0x5d, 0x64, 0x10, 0x60, 0x71, 0x41,     // Key2
    0x6d, 0x4a, 0x1f, 0x48, 0x35, 0x78, 0x4b, 0x6a,     // Key3
    0x4b, 0x3c, 0x69, 0x2a, 0x20, 0x38, 0x55, 0x1c,     // Key4
    0x10, 0x16, 0x09, 0x5d, 0x0d, 0x07, 0x6e, 0x7a,     // Key5
    0x75, 0x1a, 0x35, 0x55, 0x7b, 0x5c, 0x26, 0x0d,     // Key6
    0x2c, 0x49, 0x1a, 0x1b, 0x3e, 0x55, 0x1f, 0x40,     // Key7
    0x11, 0x24, 0x4b, 0x4a, 0x5d, 0x56, 0x4b, 0x5c,     // Key8
    0x62, 0x70, 0x0b, 0x10, 0x52, 0x3f, 0x2b, 0x4d,     // Key9
    0x5d, 0x06, 0x78, 0x16, 0x72, 0x70, 0x2e, 0x06,     // Key10
    0x3a, 0x2c, 0x60, 0x06, 0x12, 0x6c, 0x32, 0x55,     // Key11
    0x54, 0x62, 0x38, 0x05, 0x13, 0x42, 0x49, 0x40,     // Key12
    0x61, 0x54, 0x28, 0x0c, 0x4a, 0x21, 0x7c, 0x32,     // Key13
    0x4b, 0x74, 0x04, 0x5d, 0x10, 0x69, 0x72, 0x62,     // Key14
    0x5d, 0x77, 0x55, 0x0d, 0x19, 0x79, 0x59, 0x43,     // Key15
    0x0a, 0x5f, 0x0d, 0x50, 0x58, 0x4f, 0x48, 0x42,     // Key16
    0x14, 0x64, 0x65, 0x54, 0x2f, 0x7a, 0x75, 0x04,     // Key17
    0x48, 0x35, 0x00, 0x59, 0x16, 0x0e, 0x2f, 0x4b,     // Key18
    0x4a, 0x7b, 0x04, 0x6c, 0x1a, 0x6d, 0x4b, 0x44,     // Key19
    0x50, 0x11, 0x63, 0x63, 0x47, 0x6e, 0x1a, 0x6b,     // Key20
    0x0f, 0x4c, 0x3e, 0x17, 0x66, 0x0d, 0x3b, 0x3a,     // Key21
    0x47, 0x62, 0x5a, 0x25, 0x3d, 0x0e, 0x1d, 0x55,     // Key22
    0x42, 0x0f, 0x43, 0x60, 0x3e, 0x7e, 0x56, 0x3c,     // Key23
    0x44, 0x4a, 0x44, 0x3b, 0x69, 0x17, 0x1b, 0x47,     // Key24
    0x19, 0x77, 0x2c, 0x7d, 0x72, 0x03, 0x66, 0x53,     // Key25
    0x7f, 0x5a, 0x03, 0x26, 0x17, 0x01, 0x28, 0x5e,     // Key26
    0x09, 0x1d, 0x43, 0x13, 0x35, 0x26, 0x4c, 0x15,     // Key27
    0x1e, 0x7f, 0x4d, 0x6b, 0x4d, 0x52, 0x46, 0x00,     // Key28
    0x3c, 0x38, 0x5c, 0x64, 0x6f, 0x72, 0x78, 0x11,     // Key29
    0x30, 0x65, 0x47, 0x70, 0x7a, 0x3c, 0x38, 0x69,     // Key30
    0x78, 0x26, 0x35, 0x09, 0x37, 0x14, 0x34, 0x57,     // Key31
    0x73, 0x4d, 0x28, 0x28, 0x7e, 0x5a, 0x28, 0x09,     // Key32
    0x08, 0x28, 0x6c, 0x69, 0x42, 0x43, 0x31, 0x15,     // Key33
    0x54, 0x23, 0x60, 0x1c, 0x03, 0x48, 0x7d, 0x48,     // Key34
    0x25, 0x5f, 0x2b, 0x04, 0x6c, 0x42, 0x22, 0x66,     // Key35
    0x11, 0x2a, 0x1a, 0x14, 0x29, 0x68, 0x59, 0x73,     // Key36
    0x76, 0x61, 0x16, 0x00, 0x3e, 0x11, 0x31, 0x20,     // Key37
    0x10, 0x59, 0x13, 0x44, 0x54, 0x32, 0x4f, 0x0e,     // Key38
    0x76, 0x47, 0x13, 0x6f, 0x7e, 0x24, 0x5a, 0x6a,     // Key39
};

#endif // End of #if(_EMBEDDED_HDCP_KEY == _ON)

#endif  // End of #if(_HDCP_SUPPORT == _ON)


#if(_SCALER_TYPE == _RTD2545LR)
BYTE code tSDRAM_PHASE_0[] =
{
    0x00,0x00,0x00,0x22,0x00,0x22,0x00,0x00,0x00,0x00,
};
#endif

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
BYTE code tSDRAM_PHASE_1[] =
{
    0x00,0x00,0x00,0x2D,0x00,0x2D,0x00,0x00,0x00,0x00,
};
#endif

#else // __ADJUST__

#if(_EMBEDDED_HDCP_KEY == _ON)
extern BYTE code tHDCP_CTRL[];
extern BYTE code tHDCP_KEY_TABLE[];
#endif // End of #if(_EMBEDDED_HDCP_KEY == _ON)

#if(_SCALER_TYPE == _RTD2545LR)
extern BYTE code tSDRAM_PHASE_0[];
#endif
#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
extern BYTE code tSDRAM_PHASE_1[];
#endif

#endif // __ADJUST__
