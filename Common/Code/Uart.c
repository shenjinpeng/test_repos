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
// ID Code      : Uart.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __UART__

#include "Common\Header\Include.h"

#if(_DEBUG_TOOL == _RS232)
//--------------------------------------------------
// Description  : RS-232 initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CUartInitial(void)
{
    // 221880Hz
    PCON = 0x80;    // If SMOD = 1 then Y = 2 else Y = 1
//  PCON = 0x00;    // If SMOD = 1 then Y = 2 else Y = 1

    SCON = 0x50;// uart zp0704
    TMOD = 0x21;

    //Set  Y=2 , CRYSTAL = 27MHz , TH1=239  --> Baud Rate = 9600 bps

#if(_SCALER_TYPE == _RTD2472D)
    TH1 = 239;      // TH1 = 256 - (Y*CRYSTAL/384*BAUD RATE) -->CRYSTAL = 27MHz
#elif((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    TH1 = 256 - ( 2 * (_EMCU_XTAL * 1000) / 384 / 9600);   //239;      // TH1 = 256 - (Y*CRYSTAL/384*BAUD RATE) -->CRYSTAL = 27MHz
#endif
//   TL1 = 0;//uart zp0704
 //   IE = 0x82;   // Enable interrupts of Timer0 and Timer1uart zp0704
    EA = 1;
    ET1 =1;//uart zp0704

    TR1 = 1;

    ES = 1;
    PS = 0;//uart zp0704
    bUartCommandSuccess = _FALSE;
    bUartCommandStart = _FALSE;

    DebugPrintf("RS232 System Initial Success!!!\n", 0);
    DebugPrintf("Values == %x", 100);

}

//-------------------------------------------------------------------------------------------------------------------
//  Uart Main Loop
//-------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Uart handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------

// Uart Command:
// 1.into  debug mode   0x5a,0x01,0x02,0x03,0x04
// 2.exit  debug mode   0x5b,0x04,0x03,0x02,0x01
// 3.read  RTD          0x5c,0x74,address,count,index
// 4.read  other        0x5c,slave address,address,count,index
// 5.write rtd          0x5d,0x74,address,value,rever
// 6.write other        0x5d,slave address,address,value,rever

void CUartHandler(void)
{
    BYTE cnt;

    if(bUartCommandSuccess == _FALSE)
    {
        return;
    }

    if(pUartData[0] == 0x5a)
    {
        if((pUartData[1] == 0x01) && (pUartData[2] == 0x02) && (pUartData[3] == 0x03) && (pUartData[4] == 0x04))
        {
            //TxRxShow();
            bDebugModeEnable = _TRUE;
        }
    }
    while(bDebugModeEnable)
    {
        if(bUartCommandSuccess)
        {
            bUartCommandSuccess = 0;
            if(pUartData[0] == 0x5b)
            {
                if((pUartData[1] == 0x04) && (pUartData[2] == 0x03) && (pUartData[3] == 0x02) && (pUartData[4] == 0x01))
                {
                    //TxRxShow();
                    COsdFxDisableOsd();
                    bDebugModeEnable = _FALSE;
                    break;
                }
            }

            switch(pUartData[0])
            {
                case 0x5c:
                    //TxRxShow();
                    if(pUartData[1] == 0x74)
                    {
                        CUartPutCharToScr(pUartData[3]);

                        CScalerRead(pUartData[2], pUartData[3], pData, pUartData[4]);
                        for(cnt = 0; cnt < pUartData[3]; cnt++)
                        {
                            //CScalerRead(pUartData[2], pUartData[3], pData, pUartData[4]);
                            CUartPutCharToScr(pData[cnt]);
                        }
                    }
                    else
                    {
                        CUartPutCharToScr(pUartData[3]);

                        for(cnt = 0; cnt < pUartData[3]; cnt++)
                        {
                            CI2cRead(NVRAM_LINE,pUartData[1], pUartData[2], pUartData[3], pData);
                            CUartPutCharToScr(pData[cnt]);
                        }
                    }
                    break;

                case 0x5d:
                    //TxRxShow();
                    if(pUartData[1] == 0x74)
                    {
                        CScalerSetByte(pUartData[2], pUartData[3]);
                    }
                    else
                    {
                        pData[0] = pUartData[3];
                        CI2cWrite(NVRAM_LINE,pUartData[1], pUartData[2], LENGTH(1), pData);
                    }
                    break;

                default:
                    break;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Uart
// Input Value  : ch
// Output Value : None
//--------------------------------------------------
void CUartPutCharToScr(BYTE ch)
{
    ES = 0;

    SBUF = ch;          // transfer UART

    while (!TI)
    {
                        // wait buffer completing.
    }

    ES = 1;

    while (TI)
    {
                        // wait transfer completing.
    }
}

void CUartEnable(void)
{

    CScalerRead(_PAGE_SELECT_9F, 1, &ucPageInfo, _NON_AUTOINC);
//    ucPageInfo = pData[0];

    //change P3.0(Pin 58) is Rxd; P3.1(Pin 59) is Txd --> for UART used
#if(_SCALER_TYPE == _RTD2472D)
    MCU_PIN_SHARE_CTRL02_FF96 = 0xB6;
#elif((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerPageSelect(_PAGE10);
    CScalerSetByte(_P10_PIN_SHARE_CTRL09_A9, 0x5B);
#endif

    TR1 = 1;
    ES = 1;      //Reference IE (中斷致能暫存器) --> ES (致能串列埠 UART之中斷)
    PS = 1;

}

void CUartDisable(void)
{

    //change P3.0(Pin 58) is HSCL1, P3.1(Pin 59) is HSDA1
#if(_SCALER_TYPE == _RTD2472D)
    MCU_PIN_SHARE_CTRL02_FF96 = (((BYTE)_PIN_58_59_DDC1_ENABLE << 7) | (_PIN_58 << 4) | (_PIN_59 << 1));
#elif((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    CScalerPageSelect(_PAGE10);
    CScalerSetByte(_P10_PIN_SHARE_CTRL09_A9, (((BYTE)_PIN_58_59_DDC1_ENABLE << 6) | (_PIN_58 << 3) | (_PIN_59)));
#endif

   CScalerSetByte(_PAGE_SELECT_9F, ucPageInfo);


    TR1 = 0;
    ES = 0;      //Reference IE (中斷致能暫存器) --> ES (致能串列埠 UART之中斷)
    PS = 0;

}

//--------------------------------------------------
// Description  : Uart
// Input Value  : ch
// Output Value : None
//--------------------------------------------------
void CUartTransferNumToScr(WORD ch, BYTE mode )
{
    BYTE NUMBUFFER[4], i, time;


    ES = 0;

    if (mode == 0)
    {
        TI = 0;
        SBUF = ch; // transfer UART
        while (!TI)
        {
            ;        // wait buffer completing.
        }
    }
    else if (mode == 1)
    {
        //dec
        NUMBUFFER[3] = ch / 1000;
        NUMBUFFER[2] = (ch % 1000) / 100;
        NUMBUFFER[1] = ((ch % 1000) % 100) / 10;
        NUMBUFFER[0] = ((ch % 1000) % 100) % 10;
/*
        NUMBUFFER[2] = ch / 100;
        NUMBUFFER[1] = (ch % 100) / 10;
        NUMBUFFER[0] = (ch % 100) % 10;
*/
        if (NUMBUFFER[3] != 0)
        {
            time = 4;
        }
        else if (NUMBUFFER[2] != 0)
        {
            time = 3;
        }
        else if (NUMBUFFER[1] != 0)
        {
            time = 2;
        }
        else
        {
            time = 1;
        }

        for (i = 0; i < time; i++)
        {
            TI = 0;
            SBUF = NUMBUFFER[time - i - 1] + '0'; // transfer UART
            while (!TI)
            {
                ;   // wait buffer completing.
            }
        }
    }
    else if (mode == 2)
    {
        //hex
        NUMBUFFER[3] = (ch & 0x0F);
        NUMBUFFER[2] = ((ch >> 4) & 0x0F);
        NUMBUFFER[1] = ((ch >> 8) & 0x0F);
        NUMBUFFER[0] = ((ch >> 12) & 0x0F);

        for (i = 0; i < 4; i++)
        {
            TI = 0;

            if (NUMBUFFER[i] > 9)
            {
                SBUF = NUMBUFFER[i] - 10 + 'A';
            }
            else
            {
                SBUF = NUMBUFFER[i] + '0';      // transfer UART
            }
            while (!TI)
            {
                ;                    // wait buffer completing.
            }
        }
    }

    ES = 1;

}

//--------------------------------------------------
// Description  : Uart
// Input Value  : ch
// Output Value : None
//--------------------------------------------------
BYTE DebugPrintf(const BYTE code* pstr, WORD value)
{
    BYTE StrIndex = 0;

    CUartEnable();

    for(StrIndex = 0x00; *(pstr+StrIndex) != '\0'; StrIndex++)
      {
        if(*(pstr + StrIndex) == '\n')
        {
            CUartTransferNumToScr('\r', 0);
            CUartTransferNumToScr(*(pstr + StrIndex), 0);
        }
        else if(*(pstr + StrIndex) == '%' && *(pstr + StrIndex + 1) == 'd')
        {
            StrIndex++;
            CUartTransferNumToScr(value, 1);
        }
        else if(*(pstr + StrIndex) == '%' && *(pstr + StrIndex + 1) == 'x')
        {
            StrIndex++;
            CUartTransferNumToScr(value, 2);
        }
        else
        {
            CUartTransferNumToScr(*(pstr + StrIndex), 0);
        }
    }

    CUartDisable();

    return StrIndex;

}

#endif  // End of #if(_DEBUG_TOOL == _RS232)

