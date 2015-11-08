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
// ID Code      : Scaler.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER__

#include "Common\Header\Include.h"

#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

//--------------------------------------------------
// Description  : Page select for scalar(Only for CR[A1]~CR[DF])
// Input Value  : Page Number
// Output Value : None
//--------------------------------------------------
void CScalerPageSelect(BYTE page)
{
#if(_SCALER_TYPE == _RTD2472D)
    CScalerSetByte(_PAGE_SELECT_9F, (page & 0x0F));
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerSetByte(_PAGE_SELECT_9F, (page & 0x1F));
#else
    No Setting !!
#endif //End of #if(_SCALER_TYPE == _RTD2472D)
}

//--------------------------------------------------
// Description  : Initial settings for scaler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerInitial(void)
{
#if(_MCU_TYPE == _REALTEK_EMBEDDED)
    CMcuSelectFlashClk(_XTAL_CLK);
#endif

    // Software reset for scaler
    CScalerSetBit(_HOST_CTRL_01, ~(_BIT0 | _BIT1 | _BIT2), _BIT0);

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
    CTimerDelayXms(10);
#else
    CTimerDelayXms(100);
#endif

    CScalerSetBit(_HOST_CTRL_01, ~_BIT0, 0x00);
    CScalerReset();
    CTimerDelayXms(10);
#if(_MCU_TYPE == _REALTEK_EMBEDDED)
    if(GET_POWERSTATUS())       // Power up Process
    {
        CMcuSelectFlashClk(_FLASH_CLK);
    }
#endif

#if(_RESET_CHECK_SUPPORT == _ON)
    CScalerSetBit(_HOST_CTRL_01, ~_BIT6, _BIT6);
#endif

}

//--------------------------------------------------
// Description  : Reset scaler process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerReset(void)
{
    CScalerResetProcess();

    g_ucFormerSearchPort = 0;

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))

    CSyncInputPort2DInitial();
#endif

    CScalerCodeW(tSCALER_POWERUP_INITIAL);

#if(_SCALER_TYPE == _RTD2545LR)
    CMiscSetPinShare();
#endif

    CAdjustDisableWatchDog(_WD_ALL);

    CMiscClearStatusRegister();

#if(_AUDIO_SUPPORT == _ON)
    CAdjustAudioControl(_DISABLE);
#endif

    CScalerInitialDisplayInterface();

    CScalerInitialDisplayOutput();
    CModeSetFreeRun();

    CScalerEnableDisplayTiming();

    if(GET_POWERSTATUS())
    {
        // OSD power up initial
        CScalerCodeW(tOSD_POWERUP_INITIAL);

        CAdjustTMDSErrorCorrectionOn();
        CAdjustColorPalette(tPALETTE_0);
        CAdjustSRGB();
        //CAdjustGamma(_COMPACT_GAMMA_NORMAL_TABLE, tGAMMA_COMPACT1, tGAMMA_COMPACT1, tGAMMA_COMPACT1);
        //CAdjustGamma(_FULL_GAMMA_COMPRESS_TABLE, tGAMMA_TABLE_RED, tGAMMA_TABLE_GREEN, tGAMMA_TABLE_BLUE);

#if(_GAMMA_FUNCTION == _ON)

        // V015 System Patch Note (7) Modify 20100630 Start
        // Patch Reason : New EEPROM emulation process.
        /*
#if(_SCALER_TYPE == _RTD2472D)
        CAdjustGamma(_FULL_GAMMA_NORMAL_TABLE, tGAMMA_TABLE_RED, tGAMMA_TABLE_GREEN, tGAMMA_TABLE_BLUE);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        CAdjustLUTGamma(tLUTGAMMA_TABLE_RED, tLUTGAMMA_TABLE_GREEN, tLUTGAMMA_TABLE_BLUE);//20080422 +Sharon
#else
    No Setting !!

#endif//End of #if(_SCALER_TYPE == _RTD2472D)
        */
#if(_SCALER_TYPE == _RTD2472D)

#if((_MEMORY_LOCATION == _FLASH) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH))
        CAdjustGamma(_FULL_GAMMA_NORMAL_TABLE, _MCU_FLASH_GAMMA_LUT_R, _MCU_FLASH_GAMMA_LUT_G, _MCU_FLASH_GAMMA_LUT_B);
#else
        CAdjustGamma(_FULL_GAMMA_NORMAL_TABLE, tGAMMA_TABLE_RED, tGAMMA_TABLE_GREEN, tGAMMA_TABLE_BLUE);
#endif

#elif((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

#if((_MEMORY_LOCATION == _FLASH) && (_GAMMA_LUT_LOCATION == _GAMMA_LUT_LOCATION_FLASH))
        CAdjustLUTGamma(_MCU_FLASH_GAMMA_LUT_R, _MCU_FLASH_GAMMA_LUT_G, _MCU_FLASH_GAMMA_LUT_B);
#else
        CAdjustLUTGamma(tLUTGAMMA_TABLE_RED, tLUTGAMMA_TABLE_GREEN, tLUTGAMMA_TABLE_BLUE);
#endif

#elif(_SCALER_TYPE == _RTD2545LR)
        CAdjustLUTGamma(tLUTGAMMA_TABLE_RED, tLUTGAMMA_TABLE_GREEN, tLUTGAMMA_TABLE_BLUE);

#else

    No Setting !!

#endif//End of #if(_SCALER_TYPE == _RTD2472D)
        // V015 System Patch Note (7) Modify 20100630 End


#endif// End of #if(_GAMMA_FUNCTION == _ON)
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("   UpdateGammaBlock(stConBriData.Dicom);", stConBriData.Dicom);
CDebugMessage("   UpdateGammaBlock(stConBriData.Gamma);", stConBriData.Gamma);
#endif

  //      UpdateGammaBlock(3);
  /*
     if(!(stConBriData.Gamma=0)||(stConBriData.Gamma==4))
	Adjust_LUTtable(stConBriData.Gamma-1);
     else
     	{
     	if(stConBriData.Dicom<=7)
		 Adjust_LUTtable(10);
	else
		Adjust_LUTtable(stConBriData.Dicom-1);

	 }
*/

#if(_SCALER_TYPE == _RTD2472D)

        if(_DISP_BIT_MODE == _DISP_18_BIT)          //Hudson V008_20080806 add Temporal Dithering offset table !!
        {
            CAdjustDither(tDITHER_SEQ_TABLE_0, tDITHER_TABLE_10_TO_6, tDITHER_TEMPOFFSET_TABLE);
        }

        else if(_DISP_BIT_MODE == _DISP_24_BIT)     //Hudson V008_20080806 add Temporal Dithering offset table !!
        {
            CAdjustDither(tDITHER_SEQ_TABLE_0, tDITHER_TABLE_10_TO_8_D_DOMAIN, tDITHER_TEMPOFFSET_TABLE);
        }

#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))

        if(_DISP_BIT_MODE == _DISP_18_BIT)          //Hudson V008_20080806 add Temporal Dithering offset table !!
        {
            CAdjustDither(tDITHER_SEQ_TABLE_0, tDITHER_TABLE_10_TO_6, tDITHER_TEMPOFFSET_TABLE, _OUTPUT_DITHER);
        }

        else if(_DISP_BIT_MODE == _DISP_24_BIT)     //Hudson V008_20080806 add Temporal Dithering offset table !!
        {
            CAdjustDither(tDITHER_SEQ_TABLE_0, tDITHER_TABLE_10_TO_8_D_DOMAIN, tDITHER_TEMPOFFSET_TABLE, _OUTPUT_DITHER);
        }

#else

    No Setting !!

#endif  //End of #if(_SCALER_TYPE == _RTD2472D)
        CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT6 | _BIT5 | _BIT4), ((_ADC_INPUT_SWAP_RG << 6) | (_ADC_INPUT_SWAP_RB << 5) | (_ADC_INPUT_SWAP_GB << 4)));
        CAdjustBrightness(stConBriData.Brightness);
        CAdjustContrast(stConBriData.Contrast);

#if (_SRGB_COLOR_ENHANCE == _ON)
        CAdjustSaturationHue(stOsdUserData.Hue, _FALSE);
        CAdjustSaturationHue(stOsdUserData.Sat, _TRUE);
#endif

#if(_OD_SUPPORT == _ON)
        CMemoryLoadODLUT(_OD_TABLE_COMMON);
#endif

#if(_HDCP_SUPPORT == _ON) // Hdcp compatibility
        CAdjustHDCP();
#endif

    }
    else
    {
        CPowerPanelOff();
        CScalerDisableDisplayTiming();
        CPowerDPLLOff();
        CPowerTMDSOff();
        CPowerM2PLLOff();
#if((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
        CPowerMPLLOff();
#endif
        CScalerSetByte(_HOST_CTRL_01, 0x46);

    }

}

//--------------------------------------------------
// Description  : Initial display interface for TTL and LVDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerInitialDisplayInterface(void)
{
#if(_PANEL_STYLE == _PANEL_TTL)
    CScalerCodeW(tTTL_INITIAL);
#endif // End of #if(_PANEL_STYLE == _PANEL_TTL)

#if(_PANEL_STYLE == _PANEL_LVDS)
    CScalerCodeW(tLVDS_INITIAL);

#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

#if(_PANEL_STYLE == _PANEL_RSDS)
    CScalerCodeW(tLVDS_INITIAL);
    CScalerCodeW(tRSDS_INITIAL);

//    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_RSDS_OUTPUT_CTRL0_C0, 0x40 | ( (_RSDS_GC_SWAP << 2) | (_RSDS_HL_SWAP << 1) | (_RSDS_PN_SWAP) ));
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_RSDS_OUTPUT_CTRL0_C0, 0x92);
    CScalerSetDataPortBit(_DISP_ACCESS_PORT_2A, _DISP_TIMING_20, ~_BIT0, _BIT0);

#endif // End of #if(_PANEL_STYLE == _PANEL_RSDS)
}

//--------------------------------------------------
// Description  : Initial display output from Panel.h settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerInitialDisplayOutput(void)
{
 // Display signal control settings
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT4 | _BIT2), (_DISP_BIT_MODE << 4) | (_DISP_OUTPUT_PORT << 2));
    CScalerSetByte(_VDISP_SIGINV_29, ( (_DHS_MASK << 7) | (_DISP_EO_SWAP << 6) | (_DISP_RB_SWAP << 5) | (_DISP_ML_SWAP << 4) | (_DISP_SKEW << 3) | (_DISP_DVS_INVERT << 2) | (_DISP_DHS_INVERT << 1) | (_DISP_DEN_INVERT)));

#if(_PANEL_TYPE == _AU_LVDS_23_WUXGA)
    CScalerSetBit(_VDISP_SIGINV_29, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#endif

}

//--------------------------------------------------
// Description  : Enable display output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerEnableDisplayOutput(void)
{
    CScalerGetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 1, pData, _NON_AUTOINC);
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, ((pData[0] & ~(_BIT1 | _BIT0)) | (_PANEL_STYLE & (_BIT1 | _BIT0))));
}

/*
//--------------------------------------------------
// Description  : Disable display output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerDisableDisplayOutput(void)
{
    CScalerGetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 1, pData, _NON_AUTOINC);
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, (pData[0] & ~_BIT3));
}
*/
//--------------------------------------------------
// Description  : Enable display
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerEnableDisplayTiming(void)
{
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT6 | _BIT1), _BIT1);
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT0, _BIT0);

    CScalerSetBit(_VDISP_CTRL_28, ~_BIT7, _BIT7);
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Disable display
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerDisableDisplayTiming(void)
{

#if(_PANEL_STYLE == _PANEL_TTL)

    CScalerSetBit(_VDISP_SIGINV_29, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#endif

    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT6 | _BIT1), _BIT6);
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT0, 0x00);
}

//----------------------------------------------------------------------------------------------------
// Scaler communication basic function
//----------------------------------------------------------------------------------------------------
#if(_MCU_TYPE != _REALTEK_EMBEDDED)
#if(_SCALER_TYPE == _RTD2545LR)
void CScalerSendReadStop(void)
{
    SETSCALERSDIO3(_HIGH);
    SETSCALERSDIO3(_LOW);
    SETSCALERSDIO3(_HIGH);

    SETSCALERSCLK();
}

void CScalerSendWriteStop(void)
{
    CLRSCALERSCLK();
    SETSCALERSCLK();

    SETSCALERSCLK();
    SETSCALERSDIO3(_HIGH);
    SETSCALERSDIO3(_LOW);
    SETSCALERSDIO3(_HIGH);
}
void CScalerSendAddr(BYTE ucAddr, bit bReadWrite, bit bAutoInc)
{
    SETSCALERSCLK();
    SETSCALERSDIO3(_HIGH);
    SETSCALERSDIO3(_LOW);
    SETSCALERSDIO3(_HIGH);

    CScalerSendByte(ucAddr);

    SETSCALERSDIO3(bReadWrite);
    CLRSCALERSCLK();
    SETSCALERSDIO3(bAutoInc);
    SETSCALERSCLK();

    SETSCALERSDIO3(_HIGH);
}

#else
void CScalerSendReadStop(void)
{
    SETSCALERSCLK();
    SETSCALERSCSB();
}

void CScalerSendWriteStop(void)
{
    CLRSCALERSCLK();
    SETSCALERSCLK();

    SETSCALERSCLK();
    SETSCALERSCSB();
}
void CScalerSendAddr(BYTE ucAddr, bit bReadWrite, bit bAutoInc)
{
    CLRSCALERSCSB();

    CScalerSendByte(ucAddr);

    SETSCALERSDIO3(bReadWrite);
    CLRSCALERSCLK();
    SETSCALERSDIO3(bAutoInc);
    SETSCALERSCLK();

    SETSCALERSDIO3(_HIGH);
}
#endif  // End of #if(_SCALER_TYPE == _RTD2545LR)

void CScalerSendByte(BYTE ucValue)
{
    SETSCALERSDIO3((bit)(ucValue & 0x01));
    CLRSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x02));
    SETSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x04));
    CLRSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x08));
    SETSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x10));
    CLRSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x20));
    SETSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x40));
    CLRSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x80));
    SETSCALERSCLK();
}

void CScalerSETSCLK(void)
{
    SETSCALERSCLK();
    SETSCALERSCLK();
    SETSCALERSCLK();
    SETSCALERSCLK();
    SETSCALERSCLK();
}

void CScalerCLRSCLK(void)
{
    CLRSCALERSCLK();
    CLRSCALERSCLK();
    CLRSCALERSCLK();
    CLRSCALERSCLK();
    CLRSCALERSCLK();
}
#if(_SCALER_TYPE == _RTD2545LR)
BYTE CScalerGetByte1(void)
{
    BYTE value = 0;

    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x01;
    }
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x02;
    }
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x04;
    }
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x08;
    }
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x10;
    }
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x20;
    }
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x40;
    }
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x80;
    }

    CScalerCLRSCLK();

    return value;
}

BYTE CScalerGetByte2(void)
{
    BYTE value = 0;

    CScalerSETSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x01;
    }
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x02;
    }
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x04;
    }
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x08;
    }
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x10;
    }
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x20;
    }
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x40;
    }
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x80;
    }

    CScalerSETSCLK();

    return value;
}
#else

BYTE CScalerGetByte(void)
{
    BYTE value = 0;

    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x01;
    }
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x02;
    }
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x04;
    }
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x08;
    }
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x10;
    }
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x20;
    }
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x40;
    }
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
    {
        value |= 0x80;
    }

    return value;
}

#endif

#endif  // End of #if(_MCU_TYPE != _REALTEK_EMBEDDED)


//--------------------------------------------------
// Description  : Write a data array into registers of scaler
// Input Value  : ucAddr    --> Start address of register
//                ucLength  --> Numbers of data we want to write
//                pArray    --> Pointer of the writing data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void CScalerWrite(BYTE ucAddr, WORD usLength, BYTE *pArray, bit bAutoInc)
{
#if(_MCU_TYPE == _REALTEK_EMBEDDED)

#if(_DP_SUPPORT == _ON)
    g_ucRegAddrBackUp = ucAddr;
#endif

    if(usLength > 0)
    {
        if(bAutoInc)
        {
            MCU_SCA_INF_CTRL_FFF3 |= 0x20;
        }
        else
        {
            MCU_SCA_INF_CTRL_FFF3 &= 0xDF;
        }

        MCU_SCA_INF_ADDR_FFF4 = ucAddr;

        do
        {
#if(_DP_SUPPORT == _ON)
            EX0 = 0;
#endif
            MCU_SCA_INF_DATA_FFF5 = *pArray++;

#if(_DP_SUPPORT == _ON)
            if(bAutoInc == _AUTOINC)
            {
                ucAddr++;
                g_ucRegAddrBackUp = ucAddr;
            }
#endif
#if(_DP_SUPPORT == _ON)
            EX0 = 1;
#endif

        }while(--usLength);
    }

#else

    if(usLength > 0)
    {
        CScalerSendAddr(ucAddr, _WRITE, bAutoInc);

        do
        {
            CScalerSendByte(*pArray++);

        }while(--usLength);

        CScalerSendWriteStop();
    }

#endif
}

//--------------------------------------------------
// Description  : Read data from registers of scaler and put it into an reading data array
// Input Value  : ucAddr    --> Start address of register
//                ucLength  --> Numbers of data we want to read
//                pArray    --> Pointer of the reading data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void CScalerRead(BYTE ucAddr, BYTE ucLength, BYTE *pArray, bit bAutoInc)
{
    BYTE odd = 0;

#if(_MCU_TYPE == _REALTEK_EMBEDDED)

#if(_DP_SUPPORT == _ON)
        g_ucRegAddrBackUp = ucAddr;
#endif

    if(ucLength > 0)
    {
        if(bAutoInc)
        {
            MCU_SCA_INF_CTRL_FFF3 |= 0x20;
        }
        else
        {
            MCU_SCA_INF_CTRL_FFF3 &= 0xDF;
        }

        MCU_SCA_INF_ADDR_FFF4 = ucAddr;


        do
        {
#if(_DP_SUPPORT == _ON)
            EX0 = 0;
#endif
            *pArray++ = MCU_SCA_INF_DATA_FFF5;

#if(_DP_SUPPORT == _ON)
            if(bAutoInc == _AUTOINC)
            {
                ucAddr++;
                g_ucRegAddrBackUp = ucAddr;
            }
#endif

#if(_DP_SUPPORT == _ON)
            EX0 = 1;
#endif

        }while(--ucLength);
    }

#else

    if(ucLength > 0)
    {
        CScalerSendAddr(ucAddr, _READ, bAutoInc);

        do
        {
#if(_SCALER_TYPE == _RTD2545LR)
            *pArray++ = (odd == 0) ? CScalerGetByte1() : CScalerGetByte2();
            odd = odd ^ 0x01;
#else
            *pArray++ = CScalerGetByte();
#endif

        }while(--ucLength);

        CScalerSendReadStop();
    }

#endif
}

//--------------------------------------------------
// Description  : Write a data array into registers of scaler
// Input Value  : ucAddr    --> Start address of register
//                ucLength  --> Numbers of data we want to write
//                pValue    --> Value we want to write
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void CScalerWriteAmount(BYTE ucAddr, WORD usLength, BYTE ucValue, bit bAutoInc)
{
#if(_MCU_TYPE == _REALTEK_EMBEDDED)

#if(_DP_SUPPORT == _ON)
    g_ucRegAddrBackUp = ucAddr;
#endif

    if(usLength > 0)
    {
        if(bAutoInc)
        {
            MCU_SCA_INF_CTRL_FFF3 |= 0x20;
        }
        else
        {
            MCU_SCA_INF_CTRL_FFF3 &= 0xDF;
        }

        MCU_SCA_INF_ADDR_FFF4 = ucAddr;

        do
        {
#if(_DP_SUPPORT == _ON)
            EX0 = 0;
#endif
            MCU_SCA_INF_DATA_FFF5 = ucValue;

#if(_DP_SUPPORT == _ON)
            if(bAutoInc == _AUTOINC)
            {
                ucAddr++;
                g_ucRegAddrBackUp = ucAddr;
            }
#endif
#if(_DP_SUPPORT == _ON)
            EX0 = 1;
#endif

        }while(--usLength);
    }

#else

    if(usLength > 0)
    {
        CScalerSendAddr(ucAddr, _WRITE, bAutoInc);

        do
        {
            CScalerSendByte(ucValue);

        }while(--usLength);

        CScalerSendWriteStop();
    }

#endif
}

//--------------------------------------------------
// Description  : Set the value into selected register
// Input Value  : ucAddr    --> Address of register
//                ucValue   --> Value we want to set
// Output Value : None
//--------------------------------------------------
void CScalerSetByte(BYTE ucAddr, BYTE ucValue)
{
    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
}

//--------------------------------------------------
// Description  : Set the value into selected register in data port
// Input Value  : ucAddr    --> Access Port Address of register
//                ucValue1  --> Data Port Value we want to set
//                ucValue2  --> Data Value we want to set
// Output Value : None
//--------------------------------------------------
void CScalerSetDataPortByte(BYTE ucAddr, BYTE ucValue1, BYTE ucValue2)
{
    if((ucAddr == _SU_ACCESS_PORT_33) || (ucAddr == _HW_ACCESS_PORT_60)
    || (ucAddr == _CB_ACCESS_PORT_64) || (ucAddr == _PC_ACCESS_PORT_9A))
    {
        CScalerSetByte(ucAddr, 0x80);
        ucValue1 = ucValue1 | 0x80;
    }

    CScalerWrite(ucAddr, 1, &ucValue1, _AUTOINC);
    CScalerWrite(ucAddr + 1, 1, &ucValue2, _AUTOINC);
    CScalerSetByte(ucAddr, 0x00);
}

//--------------------------------------------------
// Description  : Get bytes from selected register in data port
// Input Value  : ucAddr    --> Access Port Address of register
//                ucValue   --> Data Port Address we want to Get
//                ucLength  --> Numbers of data we want to read
//                pArray    --> Pointer of the reading data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void CScalerGetDataPortByte(BYTE ucAddr, BYTE ucValue, BYTE ucLength, BYTE *pArray, bit bAutoInc)
{
    if(ucLength > 0)
    {
        if((ucAddr == _SU_ACCESS_PORT_33) || (ucAddr == _HW_ACCESS_PORT_60)
        || (ucAddr == _CB_ACCESS_PORT_64) || (ucAddr == _PC_ACCESS_PORT_9A))
        {
            CScalerSetByte(ucAddr, 0x80);
            ucValue = ucValue | 0x80;
        }

        CScalerSetByte(ucAddr, ucValue);
        CScalerRead(ucAddr + 1, ucLength, pArray, bAutoInc);
    }
}

//--------------------------------------------------
// Description  : Set some bits of selected register
// Input Value  : ucAddr    --> Address of register
//                ucAnd     --> & operation
//                ucOr      --> | operation
// Output Value : None
//--------------------------------------------------
void CScalerSetBit(BYTE ucAddr, BYTE ucAnd, BYTE ucOr)
{
    BYTE value;

    CScalerRead(ucAddr, 1, &value, _AUTOINC);

    value = (value & ucAnd) | ucOr;

    CScalerWrite(ucAddr, 1, &value, _AUTOINC);
}

//--------------------------------------------------
// Description  : Set some bits of selected register in data port
// Input Value  : ucAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ucAnd     --> & operation
//                ucOr      --> | operation
// Output Value : None
//--------------------------------------------------
void CScalerSetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr)
{
    BYTE value;

    if((ucAddr == _SU_ACCESS_PORT_33) || (ucAddr == _HW_ACCESS_PORT_60)
    || (ucAddr == _CB_ACCESS_PORT_64) || (ucAddr == _PC_ACCESS_PORT_9A))
    {
        CScalerSetByte(ucAddr, 0x80);
        ucValue = ucValue | 0x80;
    }

    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
    CScalerRead(ucAddr + 1, 1, &value, _AUTOINC);

    value = (value & ucAnd) | ucOr;

    if((ucAddr == _SU_ACCESS_PORT_33) || (ucAddr == _HW_ACCESS_PORT_60)
    || (ucAddr == _CB_ACCESS_PORT_64) || (ucAddr == _PC_ACCESS_PORT_9A))
    {
        CScalerSetByte(ucAddr, 0x80);
        ucValue = ucValue | 0x80;
    }

    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
    CScalerWrite(ucAddr + 1, 1, &value, _AUTOINC);
    CScalerSetByte(ucAddr, 0x00);
}

//--------------------------------------------------
// Description  : Get bits from selected register
// Input Value  : ucAddr    --> Address of register
//                ucAnd     --> & operation
// Output Value : Value after & operation
//--------------------------------------------------
BYTE CScalerGetBit(BYTE ucAddr, BYTE ucAnd)
{
    BYTE value;

    CScalerRead(ucAddr, 1, &value, _AUTOINC);

    return (value & ucAnd);
}

/*
#if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)
//--------------------------------------------------
// Description  : Get bits from selected register in data port
// Input Value  : ucAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ucAnd     --> & operation
// Output Value : Value after & operation
//--------------------------------------------------
BYTE CScalerGetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd)
{
    BYTE value;

    if((ucAddr == _SU_ACCESS_PORT_33) || (ucAddr == _HW_ACCESS_PORT_60)
    || (ucAddr == _CB_ACCESS_PORT_64) || (ucAddr == _PC_ACCESS_PORT_9A))
    {
        CScalerSetByte(ucAddr, 0x80);
        ucValue = ucValue | 0x80;
    }

    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
    CScalerRead(ucAddr + 1, 1, &value, _AUTOINC);

    return (value & ucAnd);
}
#endif  // End of #if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)
*/

//--------------------------------------------------
// Description  : Write a table into scaler
// Input Value  : pArray    --> Selected table which contains numbers, address auto increasing information, address of registers and values
// Output Value : None
//--------------------------------------------------
void CScalerCodeW(BYTE code *pArray)
{
    BYTE length = 0;

#if(_MCU_TYPE == _REALTEK_EMBEDDED)

    do
    {
        if((*pArray & 0xfc) == 0)
        {
            return;
        }

        length = *pArray - 3;

        if((*(pArray + 1)) == _BURST)
        {
            MCU_SCA_INF_CTRL_FFF3 |= 0x20;

#if(_DP_SUPPORT == _ON)
            EX0 = 0;
#endif

            MCU_SCA_INF_ADDR_FFF4 = *(pArray + 2);

#if(_DP_SUPPORT == _ON)
            g_ucRegAddrBackUp = *(pArray + 2);
#endif
#if(_DP_SUPPORT == _ON)
            EX0 = 1;
#endif

            pArray += 3;

            do
            {
                MCU_SCA_INF_DATA_FFF5 = *pArray;
            }while(--length);

            pArray++;
        }
        else if((*(pArray + 1) == _AUTOINC) || (*(pArray + 1) == _NON_AUTOINC))
        {

            if(*(pArray + 1) == _NON_AUTOINC)
            {
                MCU_SCA_INF_CTRL_FFF3 |= 0x20;
            }
            else
            {
                MCU_SCA_INF_CTRL_FFF3 &= 0xDF;
            }
#if(_DP_SUPPORT == _ON)
            EX0 = 0;
#endif
            MCU_SCA_INF_ADDR_FFF4 = *(pArray + 2);

#if(_DP_SUPPORT == _ON)
            g_ucRegAddrBackUp = *(pArray + 2);
#endif
#if(_DP_SUPPORT == _ON)
            EX0 = 1;
#endif
            pArray += 3;

            do
            {
                MCU_SCA_INF_DATA_FFF5 = *pArray++;
            }while(--length);
        }

    }while(_TRUE);

#else


    do
    {
        if((*pArray & 0xfc) == 0)
        {
            return;
        }

        length = *pArray - 3;

        if((*(pArray + 1)) == _BURST)
        {
            CScalerSendAddr(*(pArray + 2), _WRITE, _NON_AUTOINC);

            pArray += 3;

            do
            {
                CScalerSendByte(*pArray);

            }while(--length);

            pArray++;
        }
        else if((*(pArray + 1) == _AUTOINC) || (*(pArray + 1) == _NON_AUTOINC))
        {
            CScalerSendAddr(*(pArray + 2), _WRITE, *(pArray + 1));

            pArray += 3;

            do
            {
                CScalerSendByte(*pArray++);

            }while(--length);

        }

        CScalerSendWriteStop();

    }while(_TRUE);

#endif  // End of #if(_MCU_TYPE == _REALTEK_EMBEDDED)
}

#if(_LOAD_FONT_TYPE == _HARD_WARE)
//--------------------------------------------------
// Description  : Load OSD font into OSD SRAM
// Input Value  : pArray    --> Font table
//                usOffset  --> Offset of font base start address
// Output Value : None
//--------------------------------------------------
void CScalerLoadHardwareVLCFont(BYTE *pArray, WORD usOffset)
{
    WORD num = 0;

#if(_OSD_ROTATE_FUCTION == _ON)
    if(GET_ROTATE_STATUS())
    {
        num = 0x85;
    }
    else
#endif
        num = 0x00;

    CScalerSetByte(_OSD_ADDR_MSB_90, 0x80);          // Byte2
    CScalerSetByte(_OSD_ADDR_LSB_91, 0x03);          // Address : 003h
    CScalerSetByte(_OSD_DATA_PORT_92, (BYTE)num);    // CCW swap, Rotation


    CScalerSetByte(_OSD_ADDR_MSB_90, 0xc0);
    CScalerSetByte(_OSD_ADDR_LSB_91, 0x05);
    CScalerWrite(_OSD_DATA_PORT_92, 8, pArray, _NON_AUTOINC);

    num = ((WORD)*(pArray + 8) << 8) | *(pArray + 9);

#if(_OSD_ROTATE_FUCTION == _ON)
    if(GET_ROTATE_STATUS())
    {
        usOffset = usOffset * 12;
        usOffset += _OSD_FONT_START_POSITION_ROTATE;
    }
    else
#endif
    {
        usOffset = usOffset * 9;
        usOffset += _OSD_FONT_START_POSITION;
    }

    CScalerSetByte(_OSD_ADDR_MSB_90, 0x80);
    CScalerSetByte(_OSD_ADDR_LSB_91, 0x07);
    CScalerSetByte(_OSD_DATA_PORT_92, 0x01);

    if(usOffset > 4095)
    {
        CScalerSetBit(_OSD_SCRAMBLE_93, ~_BIT3, _BIT3);
    }
    else
    {
        CScalerSetBit(_OSD_SCRAMBLE_93, ~_BIT3, 0x00);
    }
#if(_MCU_TYPE == _REALTEK_EMBEDDED)

    MCU_SCA_INF_CTRL_FFF3 &= 0xDF;

#if(_DP_SUPPORT == _ON)
    g_ucRegAddrBackUp = _OSD_ADDR_MSB_90;
#endif

    MCU_SCA_INF_ADDR_FFF4 = _OSD_ADDR_MSB_90;
    MCU_SCA_INF_DATA_FFF5 = (HIBYTE(usOffset) & 0x000f) | 0xd0;
    MCU_SCA_INF_DATA_FFF5 = LOBYTE(usOffset);

    pArray += 10;

    MCU_SCA_INF_CTRL_FFF3 |= 0x20;

#if(_DP_SUPPORT == _ON)
    g_ucRegAddrBackUp = _OSD_DATA_PORT_92;
#endif

    MCU_SCA_INF_ADDR_FFF4 = _OSD_DATA_PORT_92;

    for(usOffset = 0; usOffset < num; usOffset++)
    {
        MCU_SCA_INF_DATA_FFF5 = *pArray++;
    }

#else

    CScalerSendAddr(_OSD_ADDR_MSB_90, _WRITE, _AUTOINC);
    CScalerSendByte((HIBYTE(usOffset) & 0x000f) | 0xd0);
    CScalerSendByte(LOBYTE(usOffset));
    CScalerSendWriteStop();

    pArray += 10;

    CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);

    for(usOffset = 0; usOffset < num; usOffset++)
    {
        CScalerSendByte(*pArray++);
    }

    CScalerSendWriteStop();

#endif
    CScalerSetBit(_OSD_SCRAMBLE_93, ~_BIT3, 0x00);

    CScalerSetByte(_OSD_ADDR_MSB_90, 0x80);
    CScalerSetByte(_OSD_ADDR_LSB_91, 0x07);
    CScalerSetByte(_OSD_DATA_PORT_92, 0x00);

#if(_OSD_ROTATE_FUCTION == _ON)
    CScalerSetByte(_OSD_ADDR_MSB_90, 0x80);
    CScalerSetByte(_OSD_ADDR_LSB_91, 0x03);
    CScalerSetByte(_OSD_DATA_PORT_92, ((BYTE)GET_ROTATE_STATUS()));
#endif

}
#endif  // End of #if(_LOAD_FONT_TYPE == _HARD_WARE)

#if(_LOAD_FONT_TYPE == _SOFT_WARE)
//--------------------------------------------------
// Description  : Load OSD font into OSD SRAM
// Input Value  : pArray    --> Font table
//                usOffset  --> Offset of font base start address
//                usLength  --> Font amounts we want to load (unit in 1 bit font)
//                ucPar     --> Choose normal or compress font table
// Output Value : None
//--------------------------------------------------
void CScalerLoadFont(BYTE *pArray, WORD usOffset, WORD usLength, BYTE ucPar)
{
    BYTE temp0, temp1, temp2;

    if(usLength == 0)
    {
        return;
    }

    usOffset = usOffset * 9;
    usOffset += _OSD_FONT_START_POSITION;

    if(usOffset > 4095)
    {
        CScalerSetBit(_OSD_SCRAMBLE_93, ~_BIT3, _BIT3);
    }

    CScalerSetByte(_OSD_ADDR_MSB_90, ((HIBYTE(usOffset) & 0x000f) | 0xd0));
    CScalerSetByte(_OSD_ADDR_LSB_91, (LOBYTE(usOffset)));

    if(ucPar == _COMPRESS_FONT)
    {
        ucVLDCnt = 0;
        ucVLDTemp = 0;
        pvldarray = (pArray + 16);

        for(temp0 = 0; temp0 < 16; temp0++)
        {
            pData[temp0] = *(pArray + temp0);
        }
    }

    do
    {
        for(usOffset = 0; usOffset < 9; usOffset++)
        {
            if(ucPar == _COMPRESS_FONT)
            {
                temp0 = CScalerGetVLD() << 4;
                temp0 |= CScalerGetVLD();
                temp1 = CScalerGetVLD() << 4;
                temp1 |= CScalerGetVLD();
                temp2 = CScalerGetVLD() << 4;
                temp2 |= CScalerGetVLD();
            }
            else
            {
                temp0 = *pArray++;
                temp1 = *pArray++;
                temp2 = *pArray++;
            }

            CScalerSetByte(_OSD_DATA_PORT_92, ((temp1 << 4) | (temp2 & 0x0f)));
            CScalerSetByte(_OSD_DATA_PORT_92, ((temp2 & 0xf0) | (temp0 & 0x0f)));
            CScalerSetByte(_OSD_DATA_PORT_92, ((temp0 & 0xf0) | (temp1 >> 4)));
        }
    }
    while(--usLength);

    CScalerSetBit(_OSD_SCRAMBLE_93, ~_BIT3, 0x00);
}

BYTE CScalerGetVLD(void)
{
    BYTE zerocnt = 0;

    while(!CScalerGetBitVLD())
    {
        zerocnt += 1;
    }

    if(zerocnt == 0)
    {
        return *(pData);
    }

    switch(zerocnt)
    {
        case 1:
            return (CScalerGetBitVLD() ? *(pData + 1) : *(pData + 2));

        case 2:
            return (CScalerGetBitVLD() ? *(pData + 3) : *(pData + 4));

        case 3:
            return (CScalerGetBitVLD() ? *(pData + 5) : *(pData + 6));

        case 4:
            if (CScalerGetBitVLD())
            {
                return (CScalerGetBitVLD() ? *(pData + 7) : *(pData + 8));
            }
            else
            {
                if (CScalerGetBitVLD())
                {
                    return (CScalerGetBitVLD() ? *(pData + 9) : *(pData + 10));
                }
                else
                {
                    return (CScalerGetBitVLD() ? *(pData + 11) : *(pData + 12));
                }
            }

        default:
            if (CScalerGetBitVLD())
            {
                return (CScalerGetBitVLD() ? *(pData + 13) : *(pData + 14));
            }
            else
            {
                CScalerGetBitVLD();

                return *(pData + 15);
            }
    }
}

bit CScalerGetBitVLD(void)
{
    ucVLDTemp = ((ucVLDCnt & 0x07) == 0) ? *(pvldarray++) : (ucVLDTemp << 1);

    ucVLDCnt += 1;

    return (bit)(ucVLDTemp & 0x80);
}

#endif  // End of #if(_LOAD_FONT_TYPE == _SOFT_WARE)


#if(_OSD_ROTATE_FUCTION == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerSendRotateByte(void)
{
   BYTE x;
   for(x = 0; x < 3; x++)
   {
      CScalerSendByte(((ROTATETemp[26-x] << 3)&0x88));
      CScalerSendByte((((ROTATETemp[14-x] << 3)&0x88) + ((ROTATETemp[17-x] << 2)&0x44) + ((ROTATETemp[20-x] << 1)&0x22) + (ROTATETemp[23-x]&0x11)));
      CScalerSendByte((((ROTATETemp[2-x] << 3)&0x88) + ((ROTATETemp[5-x] << 2)&0x44) + ((ROTATETemp[8-x] << 1)&0x22) + (ROTATETemp[11-x]&0x11)));

      CScalerSendByte(((ROTATETemp[26-x] << 2)&0x88));
      CScalerSendByte((((ROTATETemp[14-x] << 2)&0x88) + ((ROTATETemp[17-x] << 1)&0x44) + (ROTATETemp[20-x]&0x22) + ((ROTATETemp[23-x] >> 1)&0x11)));
      CScalerSendByte((((ROTATETemp[2-x] << 2)&0x88) + ((ROTATETemp[5-x] << 1)&0x44) + (ROTATETemp[8-x]&0x22) + ((ROTATETemp[11-x] >> 1)&0x11)));

      CScalerSendByte(((ROTATETemp[26-x] << 1)&0x88));
      CScalerSendByte((((ROTATETemp[14-x] << 1)&0x88) + (ROTATETemp[17-x]&0x44) + ((ROTATETemp[20-x] >> 1)&0x22) + ((ROTATETemp[23-x] >> 2)&0x11)));
      CScalerSendByte((((ROTATETemp[2-x] << 1)&0x88) + (ROTATETemp[5-x]&0x44) + ((ROTATETemp[8-x] >> 1)&0x22) + ((ROTATETemp[11-x] >> 2)&0x11)));

      CScalerSendByte((ROTATETemp[26-x]&0x88));
      CScalerSendByte(((ROTATETemp[14-x]&0x88) + ((ROTATETemp[17-x] >> 1)&0x44) + ((ROTATETemp[20-x] >> 2)&0x22) + ((ROTATETemp[23-x] >> 3)&0x11)));
      CScalerSendByte(((ROTATETemp[2-x]&0x88) + ((ROTATETemp[5-x] >> 1)&0x44) + ((ROTATETemp[8-x] >> 2)&0x22) + ((ROTATETemp[11-x] >> 3)&0x11)));
   }
}

#endif // End of #if(_OSD_ROTATE_FUCTION == _ON)

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from registers of scaler and put it into an reading data array
// Input Value  : ucAddr    --> Start address of register
//                ucLength  --> Numbers of data we want to read
//                pArray    --> Pointer of the reading data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void CScalerReadByteInt(BYTE ucAddr, BYTE *pArray)
{
#if(_MCU_TYPE == _REALTEK_EMBEDDED)

    MCU_SCA_INF_ADDR_FFF4 = ucAddr;
    *pArray = MCU_SCA_INF_DATA_FFF5;

#endif
}

//--------------------------------------------------
// Description  : Set the value into selected register
// Input Value  : ucAddr    --> Address of register
//                ucValue   --> Value we want to set
// Output Value : None
//--------------------------------------------------
void CScalerSetByteInt(BYTE ucAddr, BYTE ucValue)
{

    MCU_SCA_INF_ADDR_FFF4 = ucAddr;
    MCU_SCA_INF_DATA_FFF5 = ucValue;

}

#endif //End of #if(_DP_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Scaler Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerResetProcess(void)
{
    CScalerCodeW(tSCALER_RESET_TABLE);

#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("g_ucSearchIndex_CScalerResetProcess=%d", g_ucSearchIndex);
#endif
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT))
    {
        CScalerPageSelect(_PAGE2);
        CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT6 | _BIT5 | _BIT4), ((_HDMI_BR_SWAP << 6 ) | (_HDMI_PN_SWAP << 5) | (0x0F)));
    }
    else
    {
        CScalerPageSelect(_PAGE2);
	if(GET_INPUTPORT_TYPE(g_ucSearchIndex) ==_D0_DVI_PORT)
		{
	        CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT6 | _BIT5 | _BIT4), ((_DVI_BR_SWAP << 6) | (_DVI_PN_SWAP << 5) | (0x0F)));
	#if _DEBUG_MESSAGE_SUPPORT
	CDebugMessage("DVI_2", 0);
	#endif
		}
	else
		{
		CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT6 | _BIT5 | _BIT4), ((0<< 6) | (_DVI_PN_SWAP << 5) | (0x0F)));
		
#if _DEBUG_MESSAGE_SUPPORT
		CDebugMessage("VGA", 0);
#endif
		}
    }
#else
    CScalerPageSelect(_PAGE2);
    CScalerSetByte(_P2_POWER_ON_OFF_CTRL_A7, 0x0F);
#endif
}

#endif  // End of #if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

