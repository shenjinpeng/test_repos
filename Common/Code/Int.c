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
// ID Code      : Int.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "Common\Header\Include.h"


#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// INT0 Interrupt, DP use
//--------------------------------------------------
void EXINT0(void) interrupt 0
{

#if(_DP_PHY_CTS_AUTO == _ON)
    bit bTEST_PRBS7_Flag = 0;
#endif

    EA = 0;

    // Backup Status
    CScalerReadByteInt(_PAGE_SELECT_9F, &g_ucRegPageBackUp);
    g_ucRegIntBackUp = MCU_SCA_INF_CTRL_FFF3;

    // Int defer protection
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_AUX_MODE_SET_D0, 0xE1);

    EA = 1;

    // Backup Status
    CScalerReadByteInt(_PC_DPCD_ACCESS_PORT_H_C1, &g_ucRegPortBackUp[0]);
    CScalerReadByteInt(_PC_DPCD_ACCESS_PORT_M_C2, &g_ucRegPortBackUp[1]);
    CScalerReadByteInt(_PC_DPCD_ACCESS_PORT_L_C3, &g_ucRegPortBackUp[2]);
    CScalerReadByteInt(_PC_DP_ACCESS_PORT_B3, &g_ucRegPortBackUp[3]);

    MCU_SCA_INF_CTRL_FFF3 &= 0xDF;

    // Clear IRQ Flag
    MCU_IRQ_STATUS_FF00 = 0x00;
    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xCC);
    CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x80);
    CScalerSetByteInt(_PC_AUX_IRQ_STATUS_DC, 0xFF);

    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x02);
    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpTPStatus);

    if((g_bDpFakeLT == _FALSE) && (g_bFakeTP1Pass != _TRUE) && (g_bFakeTP2Pass != _TRUE))
    {
        switch(g_ucDpTPStatus & 0x03)
        {
            case _TRAINING_PATTERN1:

                if(g_ucDisplayPortLtPreStatus != _TRAINING_PATTERN1_PASS) // for AMD Card DOS Mode bug
                {
                    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x02);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x02);
                    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x00);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x03);
                    CScalerSetByteInt(_PC_DPCD_DATA_PORT_L_C4, 0x00);

                    g_ucLane01Status = 0;
                    g_ucLane23Status = 0;

                    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);

                    /*
                    if(GET_INPUT_PORT(g_ucSearchIndex) == _D0_INPUT_PORT)
                    {
                        CScalerSetByteInt(_PB_DP_2D_SWITCH_B5, 0x02);
                    }
                    else if(GET_INPUT_PORT(g_ucSearchIndex) == _D1_INPUT_PORT)
                    {
                        CScalerSetByteInt(_PB_DP_2D_SWITCH_B5, 0x06);
                    }
                    */

#if (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                        CScalerSetByteInt(_PB_DP_2D_SWITCH_B5, 0x02);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                        CScalerSetByteInt(_PB_DP_2D_SWITCH_B5, 0x06);
#endif

                    // Turn off OOBS
                    CScalerSetByteInt(_PB_DP_AUX_00_B3, 0x80);

                    // Error Counter
                    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
                    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xB0);
                    CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x0C);   // stop error count
                    CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x8C);   // start error count

                    CDpTrainPattern1();
                }

                break;

            case _TRAINING_PATTERN2:

                if(g_ucDisplayPortLtPreStatus != _TRAINING_PATTERN2_PASS)     // for AMD Card DOS Mode bug
                {
                    CDpTrainPattern2();
                }

                break;

            case _TRAINING_PATTERN_END:

                if( g_ucDisplayPortLtPreStatus == _TRAINING_PATTERN2_PASS )
                {
                    CDpTrainPatternEnd();
                    g_bFakeTPEndPass = _FALSE;
                    g_bDpSearchTimesReset = 1;
                    ucModeControl &= ~_BIT6; // CLR HPD
                }
                else    // Training_Pattern_None
                {
                    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x06);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x80);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x0c);
                    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpTPStatus);

                    if(g_ucDpTPStatus != 0x00)
                    {
                        if(g_bFakeTPEndPass == _TRUE)
                        {
                                g_bHDCPFail = _TRUE;
                        }

                        // Auto Set DPCD
                        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
                        CScalerSetByteInt(_PC_DP_HDCP_IRQ_E3, 0x03);
                    }

                    CDpTrainPatternNone();

#if (_DP_PHY_CTS_AUTO == _ON)
                    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x00);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x01);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x02);
                    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpTPStatus);
                    if((g_ucDpTPStatus&0x0c) == 0x0c) //PRBS7 start
                    {
                        BYTE buf = 0;
                        bLED1 = 0;
                        bLED2 = 1;
                        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
                        CScalerSetByteInt(_PB_DP_PWR_CTL_B4, 0xff);

                        for (buf = 0; buf <= 20; buf++)
                        {
                            _nop_();
                        }

                        CScalerSetByteInt(_PB_DIG03_E3, 0x01);
                        CScalerSetByteInt(_PB_DIG02_E2, 0x84);
                        CScalerSetByteInt(_PB_DIG03_E3, 0x09);

                        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
                        CScalerSetByteInt(_PC_DP_CTL_A1, 0x1C);
                        CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xB0);
                        CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x90);
                        CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xB0);
                        CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x10);
                        CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xB0);
                        CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x90);
                        bTEST_PRBS7_Flag = 1;
                    }
                    else if(((g_ucDpTPStatus&0x0c) == 0x0) && (bTEST_PRBS7_Flag == 1)) //PRBS7 end
                    {
                        bTEST_PRBS7_Flag = 0;

                        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
                        CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, 0xB0);
                        CScalerSetByteInt(_PC_DP_DATA_PORT_B4, 0x10);
                        CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEB);
                        CScalerSetByteInt(_PB_DIG03_E3, 0x01);
                        CScalerSetByteInt(_PB_DIG02_E2, 0x00);
                    }
#endif // End of #if (_DP_PHY_CTS_AUTO == _ON)
                }
                break;

            default:
                break;
        }
    }
    else //20090203 wuzanne for autosearch No.007 g_bDpFakeLT == 1(fake link training)
    {
        switch(g_ucDpTPStatus & 0x03)
        {
            case _TRAINING_PATTERN1:

                if( g_ucDisplayPortLtPreStatus != _TRAINING_PATTERN1_PASS )     // for AMD Card DOS Mode bug
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

                    g_ucLane01Status = 0;
                    g_ucLane23Status = 0;

                    CDpFakeTrainPattern1();
                }

                break;

            case _TRAINING_PATTERN2:

                if( g_ucDisplayPortLtPreStatus != _TRAINING_PATTERN2_PASS )     // for AMD Card DOS Mode bug
                {
                    g_bFakeTP1Pass = 0;
                    CDpFakeTrainPattern2();
                }
                break;

            case _TRAINING_PATTERN_END:

                if( g_ucDisplayPortLtPreStatus == _TRAINING_PATTERN2_PASS )
                {
                    g_bFakeTP2Pass = 0;
                    CDpFakeTrainPatternEnd();
                    g_bFakeTPEndPass = _TRUE;
                    g_bDpSearchTimesReset = 1;
                    ucModeControl &= ~_BIT6; // CLR HPD
                }
                else    //  Training_Pattern_None
                {
                    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, 0x06);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, 0x80);
                    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, 0x0c);
                    CScalerReadByteInt(_PC_DPCD_DATA_PORT_L_C4, &g_ucDpTPStatus);

                    if(g_ucDpTPStatus != 0x00)
                    {
                        g_bHDCPFail = _TRUE;
                    }

                    CDpTrainPatternNone();
                }
                break;

            default:
                break;
        }
    }

    //  Restore Status
    CScalerSetByteInt(_PAGE_SELECT_9F, _PAGEC);
    CScalerSetByteInt(_PC_AUX_MODE_SET_D0, 0xE3);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_H_C1, g_ucRegPortBackUp[0]);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_M_C2, g_ucRegPortBackUp[1]);
    CScalerSetByteInt(_PC_DPCD_ACCESS_PORT_L_C3, g_ucRegPortBackUp[2]);

    CScalerSetByteInt(_PC_DP_ACCESS_PORT_B3, g_ucRegPortBackUp[3]);
    CScalerSetByteInt(_PAGE_SELECT_9F, g_ucRegPageBackUp);
    MCU_SCA_INF_CTRL_FFF3 = g_ucRegIntBackUp;

    MCU_SCA_INF_ADDR_FFF4 = g_ucRegAddrBackUp;
}
#endif //End of #if(_DP_SUPPORT == _ON)

//--------------------------------------------------
// Timer0 Interrupt (1ms)
//--------------------------------------------------
void IntProcTimer0(void) interrupt 1
{
    TR0 = _ON;
    TL0 = _TIMER0_COUNT_LBYTE;
    TH0 = _TIMER0_COUNT_HBYTE;

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
if(bWatchDogResetCtrl==_FALSE)
   MCU_WATCHDOG_TIMER_FFEA |= 0x40;

#endif

    bNotifyTimer0Int = _TRUE;

    if(--ucTimer0Cnt)
    {

#if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
        CDebugCheckTimeOut();
#endif

    }
    else
    {
    #if _DEBUG_MESSAGE_SUPPORT
//	CDebugMessage("1ms", 0);
    #endif
        if(bTimer0Ctrl == _FALSE)
        {
            CTimerDecreaseTimerCnt();
        }

        ucTimer0Cnt = 10;
	if(bTimer01minCtrl==_FALSE)	
		ucTimer0Cnt3--;	
	if((bAgeModeOn&&bTimerAgeModeCtrl)||((bTimerAgeModeCtrl==_FALSE	)&&(bAgeModeOn==_FALSE)))
		
		ucTimer0Cnt1--;
#if(_DCR_MODE == _DCR_TYPE_3)
        g_ucDcrTimer += 1;          // 10msec
#endif

    }
if(ucTimer0Cnt1==0)
{
		
	if(bAgeModeOn)
		{
		ucTimer0Cnt1=200;
		if(bAgeModeWhiteFlag)
			{
			CScalerSetByte(0x6D, 0x00);
			CScalerSetByte(0x6D, 0x00);
			CScalerSetByte(0x6D, 0x00);			

			}
		else
			{

			CScalerSetByte(0x6D, 0xFF);
			CScalerSetByte(0x6D, 0xFF);
			CScalerSetByte(0x6D, 0xFF);			

			}
		bAgeModeWhiteFlag=!bAgeModeWhiteFlag;
		}
	if(bTimerAgeModeCtrl==_FALSE)
		{
		
		bTimerAgeModeCtrl=_TRUE;
		}


}
	
if(ucTimer0Cnt3==0)	
	{
      
	ucTimer0Cnt3=100;
	
	ucTimer0Cnt2--;
		
	}

	if(ucTimer0Cnt2==0)
		{
		ucTimer0Cnt2=30;//sjp for power bug 20110804	
		if(bTimer01minCtrl==_FALSE)	
			bTimer01minCtrl	=_TRUE;
	
	        }
	
}

#if(_DEBUG_TOOL == _RS232)
//-------------------------------------------------------------------------------------------------------------------
// UART interrupt function (4)
//-------------------------------------------------------------------------------------------------------------------
void IntProcUart(void)  interrupt 4
{
    if(TI)
    {
        TI = 0;
    }

    if(RI)
    {
        if(!bUartCommandStart)
        {
            pUartData[0] = SBUF;
            switch(pUartData[0])
            {
                case 0x5a:
                case 0x5b:
                case 0x5c:
                case 0x5d:
                case 0x41:
                    bUartCommandStart = _TRUE;
                    ucUartCommandNum = 1;
                    break;
                default:
                    bUartCommandStart = _FALSE;
                    break;
            }
        }
        else
        {
            if(ucUartCommandNum < 5)
            {
                pUartData[ucUartCommandNum] = SBUF;
                ucUartCommandNum++;
                if(ucUartCommandNum == 5)
                {
                    bUartCommandStart = _FALSE;
                    bUartCommandSuccess = _TRUE;
                    ucUartCommandNum = 1;
                }
            }
        }

        RI = 0;
    }
}
#endif  // End of #if(_DEBUG_TOOL == _RS232)


//-------------------------------------------------------------------------------------------------------------------
// UART interrupt function (2)
//-------------------------------------------------------------------------------------------------------------------
#if(_DEBUG_TOOL == _ISP_FOR_RTD2120)
void IntProcDdcci(void)  interrupt 2
{
    BYTE tempbuf;

    if(!bRunCommand)
    {
        tempbuf = MCU_I2C_STATUS_FF2B;
#if(_DDCCI_SUPPORT == _ON)

        if(tempbuf & 0x08)
        {
            WORD i = 0xffff;
            if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
            {
                do
                {
                    Delay5us();
                }while (bDDCSCL && --i);
            }
            else
            {
                do
                {
                    Delay5us();
                }while (bDDCSCLDVI && --i);
            }

            if( g_ucDdcciTxCount == (g_ucDdcciTxBuf[_DDC_LENGTH]&0x7f)+2 )
            {
                CDDC2Bi_InitTx();
            }
            else
            {
                g_ucDdcciTxCount++;
                MCU_I2C_DATA_OUT_FF2A = g_ucDdcciTxBuf[g_ucDdcciTxCount];
                MCU_I2C_DATA_OUT_FF2A = g_ucDdcciTxBuf[g_ucDdcciTxCount];
            }
        }
        if(tempbuf & 0x01)
        {
            g_ucDdcciCommandNumber = 0;
            g_RxStatus = _DDC2B_CLEAR;
        }

        if(tempbuf & 0x04)
        {
            if(g_ucDdcciCommandNumber == 0)
            {
                g_ucDdcciRxBuf[g_ucDdcciCommandNumber++] = MCU_I2C_SUB_IN_FF28;
            }

            g_ucDdcciRxBuf[g_ucDdcciCommandNumber++] = MCU_I2C_DATA_IN_FF29;

            if( ((g_ucDdcciRxBuf[1]&0x7f)+3) == g_ucDdcciCommandNumber )
            {
                g_RxStatus = _DDC2B_COMPLETED;
            }
        }
#else

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
        if(tempbuf & 0x08)
        {
            if(g_bDebugMessageStart == 0)
            {
                MCU_I2C_DATA_OUT_FF2A = TxBUF;
            }
            else
            {
                if(bDataOutEnd)
                {
                    MCU_I2C_DATA_OUT_FF2A = TxBUF;
                    MCU_I2C_DATA_OUT_FF2A = TxBUF;
                    bDataOutEnd = 0;
                }
            }
        }
#else
        if(tempbuf & 0x08)
        {
            MCU_I2C_DATA_OUT_FF2A = TxBUF;
        }
#endif

        if(tempbuf & 0x01)
        {
            g_ucDdcciCommandNumber = 0;
        }

        if(tempbuf & 0x02)
        {
            g_ucDdcciCommandNumber = 0;
        }

        if(tempbuf & 0x04)
        {
            if(g_ucDdcciCommandNumber == 0)
            {
                ucDdcciData[g_ucDdcciCommandNumber] = MCU_I2C_SUB_IN_FF28;
            }

            g_ucDdcciCommandNumber++;
            ucDdcciData[g_ucDdcciCommandNumber] = MCU_I2C_DATA_IN_FF29;
            bRunCommand = _TRUE;
        }

        MCU_I2C_STATUS_FF2B = tempbuf & 0xc0;
#endif
    }   // End of if(!bRunCommand)
}
#endif  // #if(_DEBUG_TOOL == _ISP_FOR_RTD2120)

#if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
void IntProcDdcci(void)  interrupt 2
{
    BYTE tempbuf = 0;

#if(_DP_SUPPORT == _ON)
    BYTE ucFillRound = 0;
#endif

#if(_DDCCI_SUPPORT == _ON)
    if(GET_DDCCI_STATUS())
    {

        /*
        if(GET_INPUTSOURCE_TYPE() != _SOURCE_DP)
        */
        if(g_ucActiveInputSourceType != _SOURCE_DP)
        {
            // Reset IIC Data Buffer
            MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
            MCU_I2C_STATUS2_FF29 &= 0xCF;

            tempbuf = MCU_I2C_STATUS_FF27;

            if(tempbuf & 0x08)
            {
                MCU_I2C_IRQ_CTRL2_FF2A |= 0xa0;

                if( g_ucDdcciTxCount == (g_ucDdcciTxBuf[_DDC_LENGTH]&0x7f)+2 )
                {
                    /*
                    DDC2Bi_InitTx();
                    */
                    CDDC2Bi_InitTx();
                }
                else
                {
                    g_ucDdcciTxCount++;
                    MCU_I2C_DATA_OUT_FF26 = g_ucDdcciTxBuf[g_ucDdcciTxCount];
                    MCU_I2C_DATA_OUT_FF26 = g_ucDdcciTxBuf[g_ucDdcciTxCount];
                }

                MCU_I2C_IRQ_CTRL2_FF2A &= (~_BIT5);
            }

            if(tempbuf & 0x02)
            {
                g_ucDdcciCommandNumber = 0;
                g_RxStatus = _DDC2B_CLEAR;
            }

            if(tempbuf & 0x04)
            {
                /*
                if(MCU_I2C_SET_SLAVE_FF23 == 0x6e)
                {
                    if(!g_ucDdcciCommandNumber)
                    {
                        g_ucDdcciRxBuf[g_ucDdcciCommandNumber++] = MCU_I2C_SUB_IN_FF24;
                    }

                    g_ucDdcciRxBuf[g_ucDdcciCommandNumber++] = MCU_I2C_DATA_IN_FF25;

                    if(((g_ucDdcciRxBuf[1] & 0x7f) + 3) == g_ucDdcciCommandNumber)
                    {
                        g_RxStatus = _DDC2B_COMPLETED;
                    }
                }
                else
                {
                    if(g_ucDdcciCommandNumber == 0)
                    {
                        ucDdcciData[g_ucDdcciCommandNumber] = MCU_I2C_SUB_IN_FF24;
                    }
                    g_ucDdcciCommandNumber++;
                    ucDdcciData[g_ucDdcciCommandNumber] = MCU_I2C_DATA_IN_FF25;
                    bRunCommand = _TRUE;
                }
                */
                if(!g_ucDdcciCommandNumber)
                {
                    g_ucDdcciRxBuf[g_ucDdcciCommandNumber++] = MCU_I2C_SUB_IN_FF24;
                }

                g_ucDdcciRxBuf[g_ucDdcciCommandNumber++] = MCU_I2C_DATA_IN_FF25;

                if(((g_ucDdcciRxBuf[1] & 0x7f) + 3) == g_ucDdcciCommandNumber)
                {
                    g_RxStatus = _DDC2B_COMPLETED;
                }
            }

            MCU_I2C_STATUS_FF27 = tempbuf & 0xc0;
            MCU_I2C_STATUS2_FF29 = 0x00;

        }
#if(_DP_SUPPORT == _ON)
        /*
        else if(GET_INPUTSOURCE_TYPE() == _SOURCE_DP)
        */
        else if(g_ucActiveInputSourceType == _SOURCE_DP)
        {
            tempbuf = MCU_I2C_STATUS_FF27;
            MCU_I2C_STATUS_FF27 &= ~(tempbuf); // clear the flag information in hardware

            if((tempbuf & 0x01) != 0)
            {
                g_ucDdcciTxCount = 0;
            }

            if((tempbuf & 0x04) != 0)
            {
                if(g_ucDdcciTxCount == 0)
                {
                    g_ucDdcciRxBuf[g_ucDdcciTxCount++] = MCU_I2C_SUB_IN_FF24;
                }

                while((MCU_I2C_STATUS2_FF29 & 0x02) == 0)
                {
                    g_ucDdcciRxBuf[g_ucDdcciTxCount++] = MCU_I2C_DATA_IN_FF25;
                }

                if(((g_ucDdcciRxBuf[1] & 0x7F) + 3) == g_ucDdcciTxCount)
                {
                    g_RxStatus = _DDC2B_COMPLETED;

#if((_SCALER_TYPE == _RTD2472D) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
                    MCU_I2C_IRQ_CTRL2_FF2A = (MCU_I2C_IRQ_CTRL2_FF2A | _BIT6); //reset data buffer
#endif

                    if(g_ucDdcciRxBuf[2] == 0xF3) // Capabilities
                    {
                        /*
                        DDCCI_GetCapabilitiesRequest();
                        */
                        CDdcDDCCI_GetCapabilitiesRequest();
                        g_RxStatus = _DDC2B_CLEAR;
                    }
                    else if(g_ucDdcciRxBuf[2] == 0x03)
                    {
                        MCU_I2C_IRQ_CTRL2_FF2A |= _BIT5;
                        MCU_I2C_DATA_OUT_FF26 = 0x6E;
                        MCU_I2C_DATA_OUT_FF26 = 0x80;
                        MCU_I2C_DATA_OUT_FF26 = 0xBE;
                        MCU_I2C_IRQ_CTRL2_FF2A &= (~_BIT5);
                    }

                }
            }

            if((tempbuf & _BIT3) != 0)
            {
                MCU_I2C_IRQ_CTRL2_FF2A |= _BIT5;     // enable mcu write

                if(g_ucDdcciTxCount < ((g_ucDdcciTxBuf[1] & 0x7F) + 2))
                {
                    while(((MCU_I2C_STATUS2_FF29 & _BIT2) == 0) && (g_ucDdcciTxCount < ((g_ucDdcciTxBuf[1] & 0x7F) + 2)))
                    {
                        g_ucDdcciTxCount++;
                        MCU_I2C_DATA_OUT_FF26 = g_ucDdcciTxBuf[g_ucDdcciTxCount];
                    }

                }

                // Transmit NULL message 6E-80-BE
                // Inorder to fill the data buffer to full immediately
                // And avoid to fill the data by re-entering the INT again
                // for DP MCCS code modify start
                ucFillRound = 0;

                while(((MCU_I2C_STATUS2_FF29 & _BIT2) == 0) && (g_ucDdcciTxCount >= ((g_ucDdcciTxBuf[1] & 0x7F) + 2)))
                {
                    ucFillRound = ucFillRound % 3;

                    switch(ucFillRound)
                    {
                        case 0:
                            MCU_I2C_DATA_OUT_FF26 = 0x6E;
                            break;

                        case 1:
                            MCU_I2C_DATA_OUT_FF26 = 0x80;
                            break;

                        case 2:
                            MCU_I2C_DATA_OUT_FF26 = 0xBE;
                            break;

                        default:
                            break;
                    }

                    ucFillRound++;
                }
                // for DP MCCS code modify end

                MCU_I2C_IRQ_CTRL2_FF2A &= (~_BIT5);
            }

            MCU_I2C_STATUS2_FF29 = 0x80;
        }
#endif // End of #if(_DP_SUPPORT == _ON)
    }
    else
#endif
    {
        MCU_I2C_STATUS2_FF29 &= 0xCF;

        if(!bRunCommand)
        {
            tempbuf = MCU_I2C_STATUS_FF27;

            if(tempbuf & 0x02)
            {
                // V012 Modify 20100324 Start
                // V012 Patch Note (23) : Fix the issue that DDC debug could not read in power saving.
                // Clear SUB_I Flag
                MCU_I2C_STATUS_FF27 = 0xBD;
                // V012 Modify 20100324 End

                g_ucDdcciCommandNumber = 0;
                ucDdcciData[0] = MCU_I2C_SUB_IN_FF24;

                // V012 Modify 20100324 Start
                // V012 Patch Note (23) : Fix the issue that DDC debug could not read in power saving.
                /*
                //Reset IIC Data Buffer
                MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                */
                // Host write Enable
                MCU_I2C_IRQ_CTRL2_FF2A &= 0xDF;
                // V012 Modify 20100324 End
            }

            if(tempbuf & 0x04)
            {
                g_ucDdcciCommandNumber++;
                ucDdcciData[g_ucDdcciCommandNumber] = MCU_I2C_DATA_IN_FF25;

                // V012 Modify 20100324 Start
                // V012 Patch Note (23) : Fix the issue that DDC debug could not read in power saving.
                // Clear D_IN_I Flag
                MCU_I2C_STATUS_FF27 = 0xBB;
                // V012 Modify 20100324 End
            }

            // V012 Modify 20100324 Start
            // V012 Patch Note (23) : Fix the issue that DDC debug could not read in power saving.
            /*
            if((tempbuf & 0x10) && g_ucDdcciCommandNumber)
            */
            if((tempbuf & _BIT4) == _BIT4)
            {
                MCU_I2C_STATUS_FF27 = 0xAF;

                if(g_ucDdcciCommandNumber > 0)
                // V012 Modify 20100324 End
                {
#if(_DDC_CHANNEL_SEL == _HDMI_DDC_CHANNEL)
                    MCU_HDMI_DDC_CTRL2_FF2E |= 0x01;
#elif(_DDC_CHANNEL_SEL == _DVI_DDC_CHANNEL)
                    MCU_DVI_DDC_CTRL2_FF20 |= 0x01;
#else
                    MCU_ADC_DDC_CTRL2_FF1D |= 0x01;
#endif
                    g_usDebugCount = 1;

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
                    if(ucDdcciData[0] == 0x55)
                    {
                        if(ucDdcciData[1] == 0x00)
                        {
                            g_usFilterPro = 0;
                        }
                        else
                        {
                            g_usFilterPro = ((ucDdcciData[1] << 8) + ucDdcciData[2]);
                        }
                    }

                    if((ucDdcciData[0] == 0x2F) && g_bDebugMessageEven)
                    {
                        g_bDebugMessageEven = _FALSE;
                        g_bFwHalt = _FALSE;
                    }
                    else if((ucDdcciData[0] == 0x55) && (!g_bDebugMessageEven))
                    {
                        g_bDebugMessageEven = _TRUE;
                    }
#endif

                    // V012 Modify 20100324 Start
                    // V012 Patch Note (23) : Fix the issue that DDC debug could not read in power saving.
                    MCU_I2C_IRQ_CTRL2_FF2A |= 0x20;
                    // V012 Modify 20100324 End

                    bRunCommand = _TRUE;
                }
            // V012 Modify 20100324 Start
            // V012 Patch Note (23) : Fix the issue that DDC debug could not read in power saving.
            }
            // V012 Modify 20100324 End
        }

        // V012 Modify 20100324 Start
        // V012 Patch Note (23) : Fix the issue that DDC debug could not read in power saving.
        /*
        MCU_I2C_STATUS_FF27 &= 0x0C;

        // Host write/read Enable
        MCU_I2C_IRQ_CTRL2_FF2A &= 0xDF;
        */
        else
        {
            MCU_I2C_STATUS_FF27 = 0xA9;
        }
        // V012 Modify 20100324 End
    }
}
#endif  // #if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
