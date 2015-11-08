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
// ID Code      : OsdFunc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __NONE_OSDFX__

#include "Common\Header\Include.h"

#if(_OSD_TYPE == _NONE_OSD)

//----------------------------------------------------------------------------------------------------
// OSD Basic Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxApplyMapSetting(BYTE ucOsdmaptype)
{
    switch(ucOsdmaptype)
    {
        case _OSD_MAP0:
            COsdFxCodeWrite(tOSD_ROW_COMMAND0);
            ucOsdMap = _OSD_MAP0;
            break;

        case _OSD_MAP1:
            ucOsdMap = _OSD_MAP1;
            break;

        case _OSD_MAP2:
            ucOsdMap = _OSD_MAP2;
            break;

        case _OSD_MAP3:
            ucOsdMap = _OSD_MAP3;
            break;

        case _OSD_MAP4:
            ucOsdMap = _OSD_MAP4;
            break;

        case _OSD_MAP5:

            ucOsdMap = _OSD_MAP5;
            break;
    }

    COsdFxSetFrameCtrlCommand();
    COsdFxSetCharCommandMap();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxSetFrameCtrlCommand(void)
{
    pData[0] = 0xc0;
    pData[1] = 0x04;
    CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);
    pData[0] = ((tOSD_OSDMAP_INF[ucOsdMap][0] + 1) & 0x00ff);
    pData[1] = (((tOSD_OSDMAP_INF[ucOsdMap][0] + 1) & 0x0f00) >> 4) | (_OSD_FONT_START_POSITION & 0x000f);
    pData[2] = (_OSD_FONT_START_POSITION & 0x0ff0) >> 4;
    CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxSetCharCommandMap(void)
{
    CScalerSetByte(_OSD_ADDR_MSB_90, 0x50 | (((tOSD_OSDMAP_INF[ucOsdMap][0] + 1) & 0x0f00) >> 8));
    CScalerSetByte(_OSD_ADDR_LSB_91, (BYTE)(tOSD_OSDMAP_INF[ucOsdMap][0] + 1));
    CScalerWriteAmount(_OSD_DATA_PORT_92, tOSD_OSDMAP_INF[ucOsdMap][0] * tOSD_OSDMAP_INF[ucOsdMap][1], 0x00, _NON_AUTOINC);

    CScalerSetByte(_OSD_ADDR_MSB_90, 0x90 | (((tOSD_OSDMAP_INF[ucOsdMap][0] + 1) & 0x0f00) >> 8));
    CScalerSetByte(_OSD_ADDR_LSB_91, (BYTE)(tOSD_OSDMAP_INF[ucOsdMap][0] + 1));
    CScalerWriteAmount(_OSD_DATA_PORT_92, tOSD_OSDMAP_INF[ucOsdMap][0] * tOSD_OSDMAP_INF[ucOsdMap][1], 0x10, _NON_AUTOINC);

    CScalerSetByte(_OSD_ADDR_MSB_90, 0x10 | (((tOSD_OSDMAP_INF[ucOsdMap][0] + 1) & 0x0f00) >> 8));
    CScalerSetByte(_OSD_ADDR_LSB_91, (BYTE)(tOSD_OSDMAP_INF[ucOsdMap][0] + 1));
    CScalerWriteAmount(_OSD_DATA_PORT_92, tOSD_OSDMAP_INF[ucOsdMap][0] * tOSD_OSDMAP_INF[ucOsdMap][1], 0x8c, _NON_AUTOINC);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxEnableOsd(void)
{
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxDisableOsd(void)
{
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxChangeWindowColor(BYTE ucWindowColor, BYTE *pStyle)
{
    pData[0] = 0x41;
    pData[1] = ((*(pStyle)) * 4) + (3);
    CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

    pData[0] = ((*(pStyle + ((3) + 1) + 1)) & 0xf0) | (ucWindowColor & 0x0f);
    CScalerWrite(_OSD_DATA_PORT_92, 1, pData, _NON_AUTOINC);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxCloseWindow(BYTE ucWinNumber)
{
    pData[0] = 0x81;
    pData[1] = (BYTE)(ucWinNumber * 4 + 3);
    pData[2] = 0x00;
    CScalerWrite(_OSD_ADDR_MSB_90, 3, pData, _AUTOINC);
}


//--------------------------------------------------
// Description  :
// Input Value  :
//                ucPar:
//                bit 0 (Align left or right)   [ 0: Align left     1: Align right        ]
//                bit 1 (Force to show number)  [ 0: Disable        1: Enable             ]
//                bit 4 ~ 6 (Show numbers)      [ 0 ~ 7: Show 1 ~ 8 numbers               ]
// Output Value :
//--------------------------------------------------
void COsdFxShowNumber(BYTE ucRow, BYTE ucCol, WORD usValue, BYTE ucPar)
{
    BYTE index, temp, i;

    pData[4] = (_0_ + (usValue / 10000));
    pData[3] = (_0_ + (usValue % 10000) / 1000);
    pData[2] = (_0_ + (usValue % 1000) / 100);
    pData[1] = (_0_ + (usValue % 100) / 10);
    pData[0] = (_0_ + (usValue % 10));

    for(index = 0; index < 5; index++)
    {
        if(pData[4 - index] != ((bit)(ucPar & _BIT1) ? 0x00 : _0_))
        {
            index = 4 - index;
            break;
        }
    }

    if(usValue == 0 && !((bit)(ucPar & 0x02)) )
    {
        index = 0;
    }

    if((bit)(ucPar & _BIT1))
    {
        temp = (ucPar & 0x70) >> 4;
        index = (ucPar & 0x70) >> 4;
    }
    else
    {
        temp = (ucPar & 0x70) >> 4;
        if(temp < index)
        {
            temp = index;
        }
    }

    if((bit)(ucPar & 0x01))     // Align Right
    {
        COsdFxCalcStartAddress(ucRow, ucCol - temp, _WRITE_BYTE1);
    }
    else                        // Align Left
    {
        COsdFxCalcStartAddress(ucRow, ucCol, _WRITE_BYTE1);
    }

    for(i = 0; i <= temp; i++)
    {
        if(index >= temp)
        {
            pData[i + 8] = pData[index - i];
        }
        else
        {
            if(i < (temp - index))
            {
                pData[i + 8] = 0x00;
            }
            else
            {
                pData[i + 8] = pData[index - (i - (temp - index))];
            }
        }
    }

    CScalerWrite(_OSD_DATA_PORT_92, (temp + 1), &pData[8], _NON_AUTOINC);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxCodeWrite(BYTE code *pArray)
{
    BYTE cnt, temp;

    CScalerWrite(_OSD_ADDR_MSB_90, 2, pArray, _AUTOINC);
    pArray += 2;

    cnt = 0;

    while(_TRUE)
    {
        if(*pArray == _EXT_)
        {
            CScalerWrite(_OSD_DATA_PORT_92, cnt, pArray - cnt, _NON_AUTOINC);
            cnt = 0;

            if(*(pArray + 1) > 3)
            {
                return;
            }

            temp = _EXT_ + *(pArray + 1);

            if(*(pArray + 2) == _REPEAT_)
            {
                CScalerWriteAmount(_OSD_DATA_PORT_92, *(pArray + 3), temp, _NON_AUTOINC);
                pArray += 4;
            }
            else
            {
                CScalerWrite(_OSD_DATA_PORT_92, 1, &temp, _NON_AUTOINC);
                pArray += 2;
            }
        }
        else if(*pArray == _REPEAT_)
        {
            CScalerWrite(_OSD_DATA_PORT_92, cnt, pArray - cnt, _NON_AUTOINC);

            CScalerWriteAmount(_OSD_DATA_PORT_92, *(pArray + 1) - 1, *(pArray - 1), _NON_AUTOINC);

            pArray += 2;
            cnt = 0;
        }
        else if(*pArray == _NEXT_)
        {
            CScalerWrite(_OSD_DATA_PORT_92, cnt, pArray - cnt, _NON_AUTOINC);
            pArray++;
            cnt = 0;

            if(*(pArray) != _END_)
            {
                CScalerWrite(_OSD_ADDR_MSB_90, 2, pArray, _AUTOINC);
                pArray += 2;
            }
            else
            {
                break;
            }
        }
        else if(*(pArray) == _END_)
        {
            CScalerWrite(_OSD_DATA_PORT_92, cnt, pArray - cnt, _NON_AUTOINC);
            break;
        }
        else
        {
            pArray++;
            cnt++;
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxCalcStartAddress(BYTE ucRow, BYTE ucCol, BYTE ucIndicate)
{
    WORD startaddress;
    BYTE temp;

    startaddress = tOSD_OSDMAP_INF[ucOsdMap][0] + 1;

    for(temp = 0; temp < ucRow; temp++)
    {
        startaddress += tOSD_OSDMAP_INF[ucOsdMap][1];
    }

    CScalerSetByte(_OSD_ADDR_MSB_90, (BYTE)(((startaddress + ucCol)  & 0x0fff) >> 8 ) | (((ucIndicate << 2) + 1) << 4));
    CScalerSetByte(_OSD_ADDR_LSB_91, (BYTE)((startaddress + ucCol) & 0x00ff));
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxLoadText(BYTE ucRow, BYTE ucCol, BYTE ucSelect, BYTE code *pArray)
{
    BYTE cnt, cnt1, cnt2, ss, temp, temp1, temp2, temp3;
    WORD length;

    length = cnt = cnt1 = cnt2 = ss = temp = temp1 = 0;

    while(_TRUE)
    {
        if(*(pArray + cnt) == _END_)
        {
            if(temp == ucSelect)
            {
                break;
            }
            else
            {
                pArray += (cnt + 1);
                cnt = 0;
            }
            temp++;
        }
        cnt++;
    }

    cnt = cnt1 = cnt2 = temp1 = 0;
    temp3 = ucRow;
    COsdFxCalcStartAddress(ucRow, ucCol, _WRITE_BYTE0);
    while(*(pArray + cnt) != _END_)
    {
        switch(*(pArray + cnt))
        {
            case _EXT_:
                if(*(pArray + cnt + 1) > 3)
                {
                    return;
                }
                temp = _EXT_ + *(pArray + cnt + 1);
                cnt += 2;
                break;

            case _REPEAT_:
                if(temp1 < (*(pArray + cnt + 1) - 1))
                {
                    temp1++;
                }
                else
                {
                    cnt += 2;
                    temp1 = 0;
                    continue;
                }
                break;

            case _NEXT_:
                if(length % 12)
                {
                    COsdFxCalcStartAddress(ucRow, ucCol + cnt1, _WRITE_BYTEALL);
                    pData[0] = 0x00;
                    pData[1] = ((12 - length % 12) < 4) ? (12 - length % 12) + 12 : (12 - length % 12);
                    pData[2] = 0x00;
                    CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);
                }
                cnt++;
                COsdFxCalcStartAddress(++ucRow, ucCol, _WRITE_BYTE0);
                length = 0;
                cnt1 = 0;
                continue;

            default:
                temp = *(pArray + cnt);
                cnt++;
                break;
        }

        cnt1++;
        ss = 0;
        temp2 = 0;
        while(_TRUE)
        {
            if((temp == (tOSD_CHARWIDTH_TABLE[0])[ss*2]) && ((tOSD_CHARWIDTH_TABLE[0])[ss*2+1] != _END_))
            {
                pData[0] = (tOSD_CHARWIDTH_TABLE[0])[ss*2+1];
                length += ((tOSD_CHARWIDTH_TABLE[0])[ss*2+1] & 0x0f);
                CScalerWrite(_OSD_DATA_PORT_92, 1, pData, _NON_AUTOINC);
                break;
            }
            else
            {
                if(((tOSD_CHARWIDTH_TABLE[0])[ss*2] == _END_) && ((tOSD_CHARWIDTH_TABLE[0])[ss*2+1] == _END_))
                {
                    temp2 = 1;
                    break;
                }
            }
            ss++;
        }

        ss = 0;
        while(temp2 == 1)
        {
            if((temp == (tOSD_CHARWIDTH_TABLE[ucSelect+1])[ss*2]) && ((tOSD_CHARWIDTH_TABLE[ucSelect+1])[ss*2+1] != _END_))
            {
                pData[0] = (tOSD_CHARWIDTH_TABLE[ucSelect+1])[ss*2+1];
                length += ((tOSD_CHARWIDTH_TABLE[ucSelect+1])[ss*2+1] & 0x0f);
                CScalerWrite(_OSD_DATA_PORT_92, 1, pData, _NON_AUTOINC);
                break;
            }
            else
            {
                if(((tOSD_CHARWIDTH_TABLE[ucSelect+1])[ss*2] == _END_) && ((tOSD_CHARWIDTH_TABLE[ucSelect+1])[ss*2+1] == _END_))
                {
                    COsdFxCalcStartAddress(ucRow, ucCol + cnt1, _WRITE_BYTE0);
                    length += 12;
                    break;
                }
            }
            ss++;
        }
    }

    if(length % 12)
    {
        COsdFxCalcStartAddress(ucRow, ucCol + cnt1, _WRITE_BYTEALL);
        pData[0] = 0x00;
        pData[1] = ((12 - length % 12) < 4) ? (12 - length % 12) + 12 : (12 - length % 12);
        pData[2] = 0x00;

        CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);
    }

    ucRow = temp3;
    cnt = 0;
    temp1 = 0;
    COsdFxCalcStartAddress(ucRow, ucCol, _WRITE_BYTE1);
    while(*(pArray + cnt) != _END_)
    {
        switch(*(pArray + cnt))
        {
            case _EXT_:
                if(*(pArray + cnt + 1) > 3)
                {
                    return;
                }
                temp = _EXT_ + *(pArray + cnt + 1);
                cnt += 2;
                break;

            case _REPEAT_:
                if(temp1 < (*(pArray + cnt + 1) - 1))
                {
                    temp1++;
                }
                else
                {
                    cnt += 2;
                    temp1 = 0;
                    continue;
                }
                break;

            case _NEXT_:
                cnt++;
                COsdFxCalcStartAddress(++ucRow, ucCol, _WRITE_BYTE1);
                continue;

            default:
                temp = *(pArray + cnt);
                cnt++;
                break;
        }

        CScalerWrite(_OSD_DATA_PORT_92, 1, &temp, _NON_AUTOINC);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD COsdFxGetColWithinText(BYTE ucPos, BYTE ucSelect, BYTE *pArray, BYTE ucType)
{
    BYTE cnt, ss, temp, temp1, temp2;
    DWORD length, Picec;

    length = cnt = ss = temp = temp1 = 0;

    while(_TRUE)
    {
        if(*(pArray + cnt) == _END_)
        {
            if(temp == ucSelect)
            {
                break;
            }
            else
            {
                pArray += (cnt + 1);
                cnt = 0;
            }
            temp++;
        }
        cnt++;
    }

    Picec = cnt;

    cnt = temp1 = 0;

    while(*(pArray + cnt) != _END_)
    {
        switch(*(pArray + cnt))
        {
            case _EXT_:
                if(*(pArray + cnt + 1) > 3)
                {
                    return 0;
                }
                temp = _EXT_ + *(pArray + cnt + 1);
                cnt += 2;
                break;

            case _REPEAT_:
                if(temp1 < (*(pArray + cnt + 1) - 1))
                {
                    temp1++;
                }
                else
                {
                    cnt += 2;
                    temp1 = 0;
                    continue;
                }
                break;

            default:
                temp = *(pArray + cnt);
                cnt++;
                break;
        }

        ucPos++;
        ss = 0;
        temp2 = 0;
        while(_TRUE)
        {
            if((temp == (tOSD_CHARWIDTH_TABLE[0])[ss*2]) && ((tOSD_CHARWIDTH_TABLE[0])[ss*2+1] != _END_))
            {
                length += ((tOSD_CHARWIDTH_TABLE[0])[ss*2+1] & 0x0f);
                break;
            }
            else
            {
                if(((tOSD_CHARWIDTH_TABLE[0])[ss*2] == _END_) && ((tOSD_CHARWIDTH_TABLE[0])[ss*2+1] == _END_))
                {
                    temp2 = 1;
                    break;
                }
            }
            ss++;
        }

        ss = 0;
        while(temp2 == 1)
        {
            if((temp == (tOSD_CHARWIDTH_TABLE[ucSelect+1])[ss*2]) && ((tOSD_CHARWIDTH_TABLE[ucSelect+1])[ss*2+1] != _END_))
            {
                length += ((tOSD_CHARWIDTH_TABLE[ucSelect+1])[ss*2+1] & 0x0f);
                break;
            }
            else
            {
                if(((tOSD_CHARWIDTH_TABLE[ucSelect+1])[ss*2] == _END_) && ((tOSD_CHARWIDTH_TABLE[ucSelect+1])[ss*2+1] == _END_))
                {
                    length += 12;
                    break;
                }
            }
            ss++;
        }
    }

    temp = 12 - length % 12;
    if(length % 12)
    {
        cnt = (temp < 4) ? temp + 12 : temp;
    }
    else
    {
        cnt = 0;
    }

    if(cnt == 0)
    {
        cnt = 0;
    }
    else if( cnt < 12)
    {
        cnt = 1;
    }
    else
    {
        cnt = 2;
    }

    temp = (BYTE)(length / 12) + cnt;

    temp1 = (length - 12) / 2;
    temp2 = (temp1 / 12) + (((temp1 % 12) > 5) ? 1 : 0);

    if(ucType == _TEXTWITH)
    {
        return (ucPos - temp) + ((length % 12) ? 1 : 0);
    }
    else if(ucType == _PIECE)
    {
        return (Picec);
    }
    else if(ucType == _LENGTH)
    {
        return (length);
    }
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxLoadIcon(BYTE ucRow, BYTE ucCol, BYTE code *pArray)
{
    COsdFxLoadText(ucRow, ucCol, 0, pArray);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxChange1bitColor(BYTE ucRow, BYTE ucCol, BYTE ucSizeW, BYTE ucSizeH, BYTE ucForegroundColor, BYTE ucBackgroundColor)
{
    BYTE cntY, temp;

    temp = ((ucForegroundColor & 0x0f) << 4) | (ucBackgroundColor & 0x0f);

    for(cntY = 0; cntY < ucSizeH; cntY++)
    {
        COsdFxCalcStartAddress(ucRow + cntY, ucCol, _WRITE_BYTE2);

        CScalerWriteAmount(_OSD_DATA_PORT_92, ucSizeW, temp, _NON_AUTOINC);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxChange2bitColor(BYTE ucRow, BYTE ucCol, BYTE ucSizeW, BYTE ucSizeH, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3)
{
    BYTE cntY, temp;

    temp = 0xa0 | ((ucColor3 & 0x07) << 1) | ((ucColor0 & 0x04) >> 2);

    for(cntY = 0; cntY < ucSizeH; cntY++)
    {
        COsdFxCalcStartAddress(ucRow + cntY, ucCol, _WRITE_BYTE0);

        CScalerWriteAmount(_OSD_DATA_PORT_92, ucSizeW, temp, _NON_AUTOINC);
    }

    temp = ((ucColor0 & 0x03) << 6) | ((ucColor2 & 0x07) << 3) | (ucColor1 & 0x07);

    for(cntY = 0; cntY < ucSizeH; cntY++)
    {
        COsdFxCalcStartAddress(ucRow + cntY, ucCol, _WRITE_BYTE2);

        CScalerWriteAmount(_OSD_DATA_PORT_92, ucSizeW, temp, _NON_AUTOINC);
    }

}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxChange4bitLUTColor(BYTE ucRow, BYTE ucCol, BYTE ucSizeW, BYTE ucSizeH, BYTE ucColor0)
{
    BYTE ucCntY, ucTemp;

    ucTemp = 0x90 | (ucColor0 & 0x0f);

    for(ucCntY = 0; ucCntY < ucSizeH; ucCntY++)
    {
        COsdFxCalcStartAddress(ucRow + ucCntY, ucCol, _WRITE_BYTE0);

        CScalerWriteAmount(_OSD_DATA_PORT_92, ucSizeW, ucTemp, _NON_AUTOINC);
    }

    ucTemp = 0x00;

    for(ucCntY = 0; ucCntY < ucSizeH; ucCntY++)
    {
        COsdFxCalcStartAddress(ucRow + ucCntY, ucCol, _WRITE_BYTE2);

        CScalerWriteAmount(_OSD_DATA_PORT_92, ucSizeW, ucTemp, _NON_AUTOINC);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE *pStyle)
{
    BYTE cnt0, cnt1;

    cnt0 = CScalerGetBit(_OVERLAY_CTRL_6C, _BIT0);

    pData[0] = (cnt0 == 0x00) ? 0xc1 : 0xe1;
    pData[1] = ((*(pStyle)) * 4) + 1;
    CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

#if(_SCALER_TYPE == _RTD2472D)
    pData[0] = ((usXStart & 0x03F) << 2);
    pData[1] = (((usYStart & 0x007) << 5) | ((usXStart & 0x7C0) >> 6));
    pData[2] = (usYStart >> 3);
    pData[3] = ((usXEnd & 0x03F) << 2);
    pData[4] = (((usYEnd & 0x007) << 5) | ((usXEnd & 0x7C0) >> 6));
    pData[5] = (usYEnd >> 3);
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    pData[0] = ((usXStart & 0x03F) << 2) | ((usXStart & 0x800) << 1) | (usYStart & 0x800);
    pData[1] = (((usYStart & 0x007) << 5) | ((usXStart & 0x7C0) >> 6));
    pData[2] = ((usYStart & 0x7F8) >> 3);
    pData[3] = ((usXEnd & 0x03F) << 2) | ((usXEnd & 0x800) << 1) | (usYEnd & 0x800);
    pData[4] = (((usYEnd & 0x007) << 5) | ((usXEnd & 0x7C0) >> 6));
    pData[5] = ((usYEnd & 0x7F8) >> 3);
#else
   No Setting !!
#endif  // End of #if(_SCALER_TYPE == _RTD2472D)
    CScalerWrite(_OSD_DATA_PORT_92, 6, pData, _NON_AUTOINC);

    CTimerDelayXms(40);

    for(cnt1 = 0; cnt1 < 2; cnt1++)
    {
        pData[0] = 0xc1;
        pData[1] = ((*(pStyle)) * 4) + (cnt1 * 3);
        CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

        for(cnt0 = 0; cnt0 < 3; cnt0++)
        {
            pData[cnt0] = (*(pStyle + ((cnt1 * 3) + cnt0) + 1));
        }

        CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxHLine(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucValue, BYTE ucIndicate)
{
    COsdFxCalcStartAddress(ucRow, ucCol, ucIndicate);

    if(ucIndicate == _WRITE_BYTEALL)
    {
        CScalerWriteAmount(_OSD_DATA_PORT_92, ucLength * 3, ucValue, _NON_AUTOINC);
    }
    else
    {
        CScalerWriteAmount(_OSD_DATA_PORT_92, ucLength, ucValue, _NON_AUTOINC);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxVLine(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucValue, BYTE ucIndicate)
{
    BYTE cnt;

    for(cnt = 0; cnt < ucLength; cnt++)
    {
        COsdFxCalcStartAddress(ucRow + cnt, ucCol, ucIndicate);

        if(ucIndicate == _WRITE_BYTEALL)
        {
            CScalerWriteAmount(_OSD_DATA_PORT_92, 3, ucValue, _NON_AUTOINC);
        }
        else
        {
            CScalerWriteAmount(_OSD_DATA_PORT_92, 1, ucValue, _NON_AUTOINC);
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdFxSetPosition(WORD usOsdActWidth, WORD usOsdActHeight, BYTE ucHPos, BYTE ucVPos, BYTE ucPar)
{
    if(ucHPos > _OSD_HPOSITION_RANGE)
    {
        ucHPos = _OSD_HPOSITION_RANGE;
    }

    if(ucVPos > _OSD_VPOSITION_RANGE)
    {
        ucVPos = _OSD_VPOSITION_RANGE;
    }

    usOsdActWidth = _OSD_HPOSITION_OFFSET + ((DWORD)(ucHPos)*(stDisplayInfo.DHWidth / 4 - usOsdActWidth / 4 - 4)) / _OSD_HPOSITION_RANGE;
    usOsdActHeight = _OSD_VPOSITION_OFFSET + ((DWORD)(_OSD_VPOSITION_RANGE - ucVPos)*(stDisplayInfo.DVHeight / 4 - usOsdActHeight / 4 - 6)) / _OSD_VPOSITION_RANGE;

    CScalerSetBit(_OSD_SCRAMBLE_93, 0xf8, 0x02);

    pData[0] = CScalerGetBit(_OVERLAY_CTRL_6C, _BIT0);

    pData[0] = (pData[0] == 0x00) ? 0xc0 : 0xe0;
    pData[1] = 0x00;
    CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

    pData[0] = usOsdActHeight >> 1;
    pData[1] = (BYTE)(usOsdActWidth >> 2);
    pData[2] = ((BYTE)(usOsdActWidth & 0x0003) << 6) | ((usOsdActHeight & 0x01) << 5) | ucPar;
    CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);

    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetBit(_OSD_SCRAMBLE_93, 0xf8, 0x05);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD COsdFxGetAdcClockRange(BYTE ucPar)
{
    WORD delta;

    CAdjustCheckAdcClockRange(stModeUserData.Clock, &delta);

    if(ucPar == _GET_CLOCKRANGE_MAX)
    {
        if(delta < _CLOCK_BIAS)
        {
            return (stModeInfo.IHTotal + delta);
        }
        else
        {
            if(stModeUserCenterData.CenterClock < stModeInfo.IHTotal)
            {
                if((stModeUserCenterData.CenterClock - stModeInfo.IHTotal + delta) < _CLOCK_BIAS)
                {
                    return (stModeInfo.IHTotal - delta + 2 * _CLOCK_BIAS);
                }
                else
                {
                    return (stModeUserCenterData.CenterClock + _CLOCK_BIAS);
                }
            }
            else
            {
                if((stModeInfo.IHTotal + delta - stModeUserCenterData.CenterClock) < _CLOCK_BIAS)
                {
                    return (stModeInfo.IHTotal + delta);
                }
                else
                {
                    return (stModeUserCenterData.CenterClock + _CLOCK_BIAS);
                }
            }
        }
    }
    else if(ucPar == _GET_CLOCKRANGE_MIN)
    {
        if(delta < _CLOCK_BIAS)
        {
            return (stModeInfo.IHTotal - delta);
        }
        else
        {
            if(stModeUserCenterData.CenterClock < stModeInfo.IHTotal)
            {
                if((stModeUserCenterData.CenterClock - stModeInfo.IHTotal + delta) < _CLOCK_BIAS)
                {
                    return (stModeInfo.IHTotal - delta);
                }
                else
                {
                    return (stModeUserCenterData.CenterClock - _CLOCK_BIAS);
                }
            }
            else
            {
                if((stModeInfo.IHTotal + delta - stModeUserCenterData.CenterClock) < _CLOCK_BIAS)
                {
                    return (stModeInfo.IHTotal + delta - 2 * _CLOCK_BIAS);
                }
                else
                {
                    return (stModeUserCenterData.CenterClock - _CLOCK_BIAS);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD COsdFxGetHPositionRange(BYTE ucPar)
{
    if(ucPar == _GET_HPOSITIONRANGE_MAX)
    {
        return (stModeUserCenterData.CenterHPos + _HPOSITION_BIAS);
    }

    else if(ucPar == _GET_HPOSITIONRANGE_MIN)
    {
        return (stModeUserCenterData.CenterHPos - _HPOSITION_BIAS);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD COsdFxGetVPositionRange(BYTE ucPar)
{
    if(ucPar == _GET_VPOSITIONRANGE_MAX)
    {
        return (stModeUserCenterData.CenterVPos + _VPOSITION_BIAS);
    }

    else if(ucPar == _GET_VPOSITIONRANGE_MIN)
    {
        return (stModeUserCenterData.CenterVPos - _VPOSITION_BIAS);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD COsdFxDetOverRange(WORD ucValue, WORD ucMax, WORD ucMin, BYTE ucSymbol)
{
    switch(ucSymbol)
    {
        case _DET_OVERRANGE_MAX:
            if (ucValue >= ucMax)
            {
                return ucMax;
            }
            else
            {
                ucValue++;
                return ucValue;
            }

        case _DET_OVERRANGE_MIN:
            if (ucValue <= ucMin)
            {
                return ucMin;
            }
            else
            {
                ucValue--;
                return ucValue;
            }
    }
}


#endif  // End of #if(_OSD_TYPE == _NONE_OSD)

