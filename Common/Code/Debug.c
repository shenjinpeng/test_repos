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
// ID Code      : Debug.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------


#define __Debug__

#include "Common\Header\Include.h"

#if((_DEBUG_TOOL == _ISP_FOR_RTD2120) && (_DEBUG_MESSAGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Debug Message process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDebugMessage(BYTE *pArray1, DWORD pArray2)
{
    bit halt = 0;
    BYTE index = 0, length = 0, checksum = 0;

    if(ucDdcciData[0] == 0x55)
    {
        g_bDebugMessageEven = _TRUE;
    }

    if(g_bDebugMessageEven == _FALSE)
    {
        return;
    }

    if(*pArray1 == 0)
    {
        TxBUF = 0xFC;
        TxTemp = 0xFC;
        return;
    }

    halt = 1; // FW stop

    if(g_bDebugMessageStart == 0)
    {
        TxBUF = 0xF1;
        TxTemp = 0xF1;
    }

    for(index = 0; index < 4; index++)
    {
        pDebugMessageBUF[index] = 0;
    }

    do
    {
        if(bRunCommand)
        {
            switch(ucDdcciData[0])
            {
                case 0x20:  //Handshake Setting
                    TxBUF = TxTemp;
                    break;

                case 0x25:  //Debug Message Start
                    if(g_bDebugMessageStart == _FALSE)
                    {
                        if(*pArray1 != 0)
                        {
                            index = 0;      //Sending Index
                            length = 0;     //Total Length
                            checksum = 0;

                            do
                            {
                                checksum ^= pArray1[length];

                            }while((pArray1[length++] != 0) && (length < 240)); //To count the length of pArray1 and checksum

                            pDebugMessageBUF[0] = (BYTE)(pArray2 >> 24);
                            pDebugMessageBUF[1] = (BYTE)(pArray2 >> 16);
                            pDebugMessageBUF[2] = (BYTE)(pArray2 >> 8);
                            pDebugMessageBUF[3] = (BYTE)(pArray2);
                            checksum = checksum ^ pDebugMessageBUF[0] ^ pDebugMessageBUF[1] ^ pDebugMessageBUF[2] ^ pDebugMessageBUF[3];

                            length = (length - 1 + 4) + 4;    //Total Length = length of {Sending Data + Start Code(2) + Length Code(1) + CheckSum(1)}
                            g_bDebugMessageStart = 1; //Debug Message Start

                            MCU_I2C_DATA_OUT_FF2A = 0xFA;
                            TxBUF = 0xFA;
                        }
                        else
                        {
                            //initial setting
                            g_bDebugMessageStart = 0;
                            bDataOutEnd = 0;
                            index = 0;
                            length = 0;
                            TxBUF = 0;
                        }
                    }
                    else
                    {
                        if((bDataOutEnd == 0) && (length != 0xff))
                        {
                            if(index == 0)
                            {
                                TxBUF = 0xFA;                   //Start of Check Code 1
                            }
                            else if(index == 1)
                            {
                                TxBUF = 0xF5;                   //Start of Check Code 2
                            }
                            else if(index == 2)
                            {
                                TxBUF = length - 4;             //Length Code
                            }
                            else if(index == length - 1)
                            {
                                TxBUF = checksum;               //CheckSum Code
                            }
                            else
                            {
                                if(index < length - 5)          //Sending Data
                                {
                                    TxBUF = pArray1[index - 3];
                                }
                                else
                                {
                                    TxBUF = pDebugMessageBUF[index - (length - 5)];
                                }

                            }

                            if(index < length)
                            {
                                index++;
                            }
                            else
                            {
                                index = 0;
                                TxBUF = 0xFA;
                            }

                            bDataOutEnd = 1;                    //End of Data Output
                        }
                    }
                    break;

                case 0x2A:  //Debug Message End
                    if(g_bDebugMessageStart)
                    {
                        g_bDebugMessageStart = 0; //Debug Message End
                        bDataOutEnd = 0;
                        halt = 0;               // FW run
                        TxTemp = 0x00;
                        TxBUF = 0xF7;
                    }
                    break;

                case 0x2F:  //Debug Message Event finsih
                    TxBUF = 0xF5;
                    MCU_I2C_DATA_OUT_FF2A = 0xF5;
                    g_bDebugMessageStart = 0;
                    bDataOutEnd = 0;
                    g_bDebugMessageEven = 0;
                    TxTemp = 0x00;
                    halt = 0;
                    break;

                default:
                    break;
            }

            bRunCommand = 0;

            g_ucDdcciCommandNumber = 0;
        }
    }
    while(halt != 0);

    g_bDebugMessageStart = 0;
    bDataOutEnd = 0;
}
#endif  // End of #if((_DEBUG_MESSAGE_SUPPORT == _ON) && (_DEBUG_TOOL == _ISP_FOR_RTD2120))

#if((_DEBUG_TOOL == _ISP_FOR_EMBEDDED) && (_DEBUG_MESSAGE_SUPPORT == _ON) && (_POLLING_MESSAGE_NBYTES == _POLLING_BY_1BYTE))
//--------------------------------------------------
// Description  : Debug Message process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDebugMessage(BYTE *pArray1, DWORD pArray2)
{
    BYTE cnt = 0, length = 0, checksum = 0;

    if(ucDdcciData[0] == 0x55)
    {
        g_bDebugMessageEven = _TRUE;
    }

    if(g_bDebugMessageEven == _FALSE)
    {
        return;
    }

    if(*pArray1 == 0)
    {
        MCU_I2C_IRQ_CTRL2_FF2A |= 0x20;
        MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
        MCU_I2C_DATA_OUT_FF26 = 0xFC;
        MCU_I2C_IRQ_CTRL2_FF2A &= 0xDF;
        return;
    }

    if((g_usFilterPro & 0xF800) == 0xC800)
    {
        switch(pArray1[0])
        {
            case '0':
                if((g_usFilterPro & _BIT0) == 0)
                {
                    return;
                }
                break;

            case '1':
                if((g_usFilterPro & _BIT1) == 0)
                {
                    return;
                }
                break;

            case '2':
                if((g_usFilterPro & _BIT2) == 0)
                {
                    return;
                }
                break;

            case '3':
                if((g_usFilterPro & _BIT3) == 0)
                {
                    return;
                }
                break;

            case '4':
                if((g_usFilterPro & _BIT4) == 0)
                {
                    return;
                }
                break;

            case '5':
                if((g_usFilterPro & _BIT5) == 0)
                {
                    return;
                }
                break;

            case '6':
                if((g_usFilterPro & _BIT6) == 0)
                {
                    return;
                }
                break;

            case '7':
                if((g_usFilterPro & _BIT7) == 0)
                {
                    return;
                }
                break;

            case '8':
                if((g_usFilterPro & _BIT8) == 0)
                {
                    return;
                }
                break;

            case '9':
                if((g_usFilterPro & _BIT9) == 0)
                {
                    return;
                }
                break;

            default:
                if((g_usFilterPro & _BIT10) == 0)
                {
                    return;
                }
                break;
        }
    }

    g_bFwHalt = 1;

    for(cnt = 0; cnt < 4; cnt++)
    {
        pDebugMessageBUF[cnt] = 0;
    }

    if(g_bDebugMessageStart == 0)
    {
        MCU_I2C_IRQ_CTRL2_FF2A |= 0x20;
        MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
        MCU_I2C_DATA_OUT_FF26 = 0xF1;
    }

    do
    {
        if(bRunCommand)
        {
            MCU_I2C_IRQ_CTRL2_FF2A |= 0x20;
            cnt = 0;

            switch(ucDdcciData[0])
            {
                case 0x20:
                case 0x55:
                    if(ucDdcciData[1] == 0x5A)
                    {
                        do
                        {
                            MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                            MCU_I2C_DATA_OUT_FF26 = 0xE2;

                        }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                    }
                    else if(ucDdcciData[1] == 0xA5)
                    {
                        do
                        {
                            MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                            MCU_I2C_DATA_OUT_FF26 = 0xE9;

                        }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                    }
                    else
                    {
                        do
                        {
                            MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                            MCU_I2C_DATA_OUT_FF26 = 0xF1;

                        }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                    }
                    break;

                case 0x25:
                    if(g_bDebugMessageStart == _FALSE)
                    {
                        if(*pArray1 != 0)
                        {
                            length = 0;
                            checksum = 0;

                            do
                            {
                                checksum ^= pArray1[length];

                            }while((pArray1[length++] != 0) && (length < 240)); //To count the length of pArray1 and checksum

                            pDebugMessageBUF[0] = (BYTE)(pArray2 >> 24);
                            pDebugMessageBUF[1] = (BYTE)(pArray2 >> 16);
                            pDebugMessageBUF[2] = (BYTE)(pArray2 >> 8);
                            pDebugMessageBUF[3] = (BYTE)(pArray2);
                            checksum = checksum ^ pDebugMessageBUF[0] ^ pDebugMessageBUF[1] ^ pDebugMessageBUF[2] ^ pDebugMessageBUF[3];

                            length = (length - 1 + 4) + 4;    //Total Length = length of {Sending Data + Start Code(2) + Length Code(1) + CheckSum(1)}
                            g_bDebugMessageStart = 1; //Debug Message Start

                            do
                            {
                                MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                                MCU_I2C_DATA_OUT_FF26 = 0xFA;

                            }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                        }
                        else
                        {
                            //initial setting
                            g_bDebugMessageStart = 0;
                            length = 0;
                        }
                    }
                    else
                    {
                        if((length != 0xff))
                        {
                            if(ucDdcciData[1] >= length)
                            {
                                ucDdcciData[1] = 0;
                            }
                            if(ucDdcciData[1] == 0)
                            {
                                do
                                {
                                    MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                                    MCU_I2C_DATA_OUT_FF26 = 0xFA;

                                }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                            }
                            else if(ucDdcciData[1] == 1)
                            {
                                do
                                {
                                    MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                                    MCU_I2C_DATA_OUT_FF26 = 0xF5;

                                }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                            }
                            else if(ucDdcciData[1] == 2)
                            {
                                do
                                {
                                    MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                                    MCU_I2C_DATA_OUT_FF26 = length - 4;

                                }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                            }
                            else if(ucDdcciData[1] == length - 1)
                            {
                                do
                                {
                                    MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                                    MCU_I2C_DATA_OUT_FF26 = checksum;

                                }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                            }
                            else
                            {
                                do
                                {
                                    MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                                    if(ucDdcciData[1] < length - 5)
                                    {
                                        MCU_I2C_DATA_OUT_FF26 = pArray1[ucDdcciData[1] - 3];
                                    }
                                    else
                                    {
                                        MCU_I2C_DATA_OUT_FF26 = pDebugMessageBUF[ucDdcciData[1] - (length - 5)];
                                    }

                                }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                            }
                        }
                    }
                    break;

                case 0x2A:  //Debug Message End
                    if(g_bDebugMessageStart)
                    {
                        g_bDebugMessageStart = 0; //Debug Message End
                        g_bFwHalt = 0;
                        do
                        {
                            MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                            MCU_I2C_DATA_OUT_FF26 = 0xF7;

                        }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                    }
                    break;

                case 0x2F:  //Debug Message Event finsih
                    do
                    {
                        MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                        MCU_I2C_DATA_OUT_FF26 = 0xF5;

                    }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));

                    g_bDebugMessageStart = 0;
                    g_bFwHalt = 0;
                    g_bDebugMessageEven = 0;
                    MCU_I2C_IRQ_CTRL2_FF2A &= 0xBF;
                    break;

                default:
                    break;
            }

            bRunCommand = 0;

            g_ucDdcciCommandNumber = 0;

            MCU_I2C_IRQ_CTRL2_FF2A &= 0xDF;

#if(_DDC_CHANNEL_SEL == _HDMI_DDC_CHANNEL)
            MCU_HDMI_DDC_CTRL2_FF2E &= 0xFE;
#elif(_DDC_CHANNEL_SEL == _DVI_DDC_CHANNEL)
            MCU_DVI_DDC_CTRL2_FF20 &= 0xFE;
#else
            MCU_ADC_DDC_CTRL2_FF1D &= 0xFE;
#endif
        }
    }
    while(g_bFwHalt != 0);
    g_bDebugMessageStart = 0;
    g_bFwHalt = 0;
}
#endif  // End of #if((_DEBUG_TOOL == _ISP_FOR_EMBEDDED) && (_DEBUG_MESSAGE_SUPPORT == _ON) && (_POLLING_MESSAGE_NBYTES == _POLLING_BY_1BYTE))

#if((_DEBUG_TOOL == _ISP_FOR_EMBEDDED) && (_DEBUG_MESSAGE_SUPPORT == _ON) && (_POLLING_MESSAGE_NBYTES == _POLLING_BY_16BYTE))
//--------------------------------------------------
// Description  : Debug Message process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDebugMessage(BYTE *pArray1, DWORD pArray2)
{
    BYTE cnt = 0, length = 0, checksum = 0, index = 0;

    if(ucDdcciData[0] == 0x55)
    {
        g_bDebugMessageEven = _TRUE;
    }

    if(g_bDebugMessageEven == _FALSE)
    {
        return;
    }

    if(*pArray1 == 0)
    {
        MCU_I2C_IRQ_CTRL2_FF2A |= 0x20;
        MCU_I2C_IRQ_CTRL2_FF2A |= 0x40; //Reset IIC Data Buffer
        MCU_I2C_DATA_OUT_FF26 = 0xFC;
        return;
    }

    if((g_usFilterPro & 0xF800) == 0xC800)
    {
        switch(pArray1[0])
        {
            case '0':
                if((g_usFilterPro & _BIT0) == 0)
                {
                    return;
                }
                break;

            case '1':
                if((g_usFilterPro & _BIT1) == 0)
                {
                    return;
                }
                break;

            case '2':
                if((g_usFilterPro & _BIT2) == 0)
                {
                    return;
                }
                break;

            case '3':
                if((g_usFilterPro & _BIT3) == 0)
                {
                    return;
                }
                break;

            case '4':
                if((g_usFilterPro & _BIT4) == 0)
                {
                    return;
                }
                break;

            case '5':
                if((g_usFilterPro & _BIT5) == 0)
                {
                    return;
                }
                break;

            case '6':
                if((g_usFilterPro & _BIT6) == 0)
                {
                    return;
                }
                break;

            case '7':
                if((g_usFilterPro & _BIT7) == 0)
                {
                    return;
                }
                break;

            case '8':
                if((g_usFilterPro & _BIT8) == 0)
                {
                    return;
                }
                break;

            case '9':
                if((g_usFilterPro & _BIT9) == 0)
                {
                    return;
                }
                break;

            default:
                if((g_usFilterPro & _BIT10) == 0)
                {
                    return;
                }
                break;
        }
    }

    g_bDebugMessageStart = 0;
    g_bFwHalt = 1;

    MCU_I2C_IRQ_CTRL2_FF2A |= 0x20;
    MCU_I2C_IRQ_CTRL2_FF2A |= 0x40; //Reset IIC Data Buffer
    MCU_I2C_DATA_OUT_FF26 = 0xF1;

    for(checksum = 0; checksum < 4; checksum++)
    {
        pDebugMessageBUF[checksum] = 0;
    }

    do
    {
        if(bRunCommand)
        {
            MCU_I2C_IRQ_CTRL2_FF2A |= 0x20;
            cnt = 0;

            switch(ucDdcciData[0])
            {
                case 0x20:  //Handshake Setting
                case 0x55:
                    if(ucDdcciData[1] == 0x5A)
                    {
                        do
                        {
                            MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                            MCU_I2C_DATA_OUT_FF26 = 0xE7;

                        }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                    }
                    else if(ucDdcciData[1] == 0xA5)
                    {
                        do
                        {
                            MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                            MCU_I2C_DATA_OUT_FF26 = 0xEC;

                        }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                    }
                    else
                    {
                        do
                        {
                            MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                            MCU_I2C_DATA_OUT_FF26 = 0xF1;

                        }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                    }
                    break;

                case 0x25:  //Debug Message Start
                    if(ucDdcciData[1] == 0)
                    {
                        do
                        {
                            MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                            length = 0;     //Total Length
                            index = 0;
                            checksum = 0x00;//initial checksum
                            do
                            {
                                checksum += pArray1[length];

                            }while((pArray1[length++] != 0) && (length < 240)); //To count the length of pArray1 and checksum

                            pDebugMessageBUF[0] = (BYTE)(pArray2 >> 24);
                            pDebugMessageBUF[1] = (BYTE)(pArray2 >> 16);
                            pDebugMessageBUF[2] = (BYTE)(pArray2 >> 8);
                            pDebugMessageBUF[3] = (BYTE)(pArray2);
                            length = length - 1;

                            MCU_I2C_DATA_OUT_FF26 = 0xFA;
                            MCU_I2C_DATA_OUT_FF26 = 0xF5;
                            MCU_I2C_DATA_OUT_FF26 = length;
                            MCU_I2C_DATA_OUT_FF26 = pDebugMessageBUF[0];
                            MCU_I2C_DATA_OUT_FF26 = pDebugMessageBUF[1];
                            MCU_I2C_DATA_OUT_FF26 = pDebugMessageBUF[2];
                            MCU_I2C_DATA_OUT_FF26 = pDebugMessageBUF[3];

                            index = checksum;
                            checksum = 0x0F;
                            checksum = checksum + length + pDebugMessageBUF[0] + pDebugMessageBUF[1] + pDebugMessageBUF[2] + pDebugMessageBUF[3];

                            pDebugMessageBUF[0] = checksum + index;// save checksum for all string and data
                            MCU_I2C_DATA_OUT_FF26 = pDebugMessageBUF[0];//checksum for all string and data
                            MCU_I2C_DATA_OUT_FF26 = checksum + pDebugMessageBUF[0];

                        }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x09) && ((cnt++) < _DATA_OUT_COUNT));
                    }
                    else
                    {
                        do
                        {
                            MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                            index = (ucDdcciData[1] - 1) * 15;
                            checksum = ucDdcciData[1] + 0x0F;
                            pDebugMessageBUF[0] = 1;

                            do
                            {
                                MCU_I2C_DATA_OUT_FF26 = pArray1[index];
                                checksum += pArray1[index];
                                index++;
                                pDebugMessageBUF[0] = pDebugMessageBUF[0] + 1;

                            }while((index < (ucDdcciData[1] * 15)) && (pArray1[index] != 0));

                            MCU_I2C_DATA_OUT_FF26 = checksum;

                        }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != pDebugMessageBUF[0]) && ((cnt++) < _DATA_OUT_COUNT));

                        g_bDebugMessageStart = 1;
                    }
                    break;

                case 0x2A:  //Debug Message End
                    if(g_bDebugMessageStart)
                    {
                        g_bDebugMessageStart = 0; //Debug Message End
                        g_bFwHalt = 0;
                        do
                        {
                            MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                            MCU_I2C_DATA_OUT_FF26 = 0xF7;

                        }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));
                    }

                    break;

                case 0x2F:  //Debug Message Event finsih
                    do
                    {
                        MCU_I2C_IRQ_CTRL2_FF2A |= 0x40;
                        MCU_I2C_DATA_OUT_FF26 = 0xF5;

                    }while(((MCU_DDCCI_REMAIN_FF35 & 0x1F) != 0x01) && ((cnt++) < _DATA_OUT_COUNT));

                    g_bDebugMessageEven = 0;
                    g_bFwHalt = 0;
                    MCU_I2C_IRQ_CTRL2_FF2A &= 0xBF;
                    break;

                default:
                    break;
            }

            bRunCommand = 0;

            g_ucDdcciCommandNumber = 0;

            MCU_I2C_IRQ_CTRL2_FF2A &= 0xDF;

#if(_DDC_CHANNEL_SEL == _HDMI_DDC_CHANNEL)
            MCU_HDMI_DDC_CTRL2_FF2E &= 0xFE;
#elif(_DDC_CHANNEL_SEL == _DVI_DDC_CHANNEL)
            MCU_DVI_DDC_CTRL2_FF20 &= 0xFE;
#else
            MCU_ADC_DDC_CTRL2_FF1D &= 0xFE;
#endif
        }
    }
    while(g_bFwHalt != 0);
    g_bDebugMessageStart = 0;
    g_bFwHalt = 0;
}
#endif  // End of #if((_DEBUG_TOOL == _ISP_FOR_EMBEDDED) && (_DEBUG_MESSAGE_SUPPORT == _ON) && (_POLLING_MESSAGE_NBYTES == _POLLING_BY_16BYTE))

#if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)
//--------------------------------------------------
// Description  : Check Time Out for Debug
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CDebugCheckTimeOut(void)
{
#if(_DDC_CHANNEL_SEL == _HDMI_DDC_CHANNEL)

    if((MCU_HDMI_DDC_CTRL2_FF2E & _BIT0) == _BIT0)
    {
        if(g_usDebugCount > 0)
        {
            if(g_usDebugCount > _TIME_OUT_COUNT)
            {
                MCU_HDMI_DDC_CTRL2_FF2E &= 0xFE;
                g_usDebugCount = 0;
            }
            else
            {
                g_usDebugCount++;
            }
        }
    }

#elif(_DDC_CHANNEL_SEL == _DVI_DDC_CHANNEL)

    if((MCU_DVI_DDC_CTRL2_FF20 & _BIT0) == _BIT0)
    {
        if(g_usDebugCount > 0)
        {
            if(g_usDebugCount > _TIME_OUT_COUNT)
            {
                MCU_DVI_DDC_CTRL2_FF20 &= 0xFE;
                g_usDebugCount = 0;
            }
            else
            {
                g_usDebugCount++;
            }
        }
    }

#else

    if((MCU_ADC_DDC_CTRL2_FF1D & _BIT0) == _BIT0)
    {
        if(g_usDebugCount > 0)
        {
            if(g_usDebugCount > _TIME_OUT_COUNT)
            {
                MCU_ADC_DDC_CTRL2_FF1D &= 0xFE;
                g_usDebugCount = 0;
            }
            else
            {
                g_usDebugCount++;
            }
        }
    }
#endif  // End of #if(_DDC_CHANNEL_SEL == _HDMI_DDC_CHANNEL)
}
#endif  // End of #if(_DEBUG_TOOL == _ISP_FOR_EMBEDDED)

