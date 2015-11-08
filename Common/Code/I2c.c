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
// ID Code      : I2c.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __I2C__

#include "Common\Header\Include.h"


//----------------------------------------------------------------------------------------------------
// I2C communication basic function for RTD2120
//----------------------------------------------------------------------------------------------------
void Delay5us(void)
{
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}
	
void CSetI2CSCL(BYTE Line)
{
	switch(Line)
	{
	
		case LS_LINE:
			SETLSSCL();
		break;
	
		default:
			SETI2CSCL();
		break;
		
	}
	
}

void CSetI2CSDA(BYTE Line)
{
	switch(Line)
	{

		case LS_LINE:
			SETLSSDA();
		break;
	
		
		default:
			SETI2CSDA();
		break;
		
	}
	
}


BYTE CCheckI2CSDA(BYTE Line)
{
	switch(Line)
	{
		case LS_LINE:
			return CHECKLSSDA();
		break;
		default:
			return CHECKI2CSDA();
		break;
		
	}
	
}

BYTE CCheckI2CSCL(BYTE Line)
{
	switch(Line)
	{

		case LS_LINE:
			return CHECKLSSCL();
		break;
	
		default:
			return  CHECKI2CSCL();
		break;
		
	}
	
}


void CClrI2CSCL(BYTE Line)
{
	switch(Line)
	{

		case LS_LINE:
			CLRLSSCL();
		break;
	
		default:
			CLRI2CSCL();

		break;
		
	}
	
}

void CClrI2CSDA(BYTE Line)
{
	switch(Line)
	{
	
		case LS_LINE:
			CLRLSSDA();
		break;
		
		default:
			CLRI2CSDA();
		break;
		
	}
	
}




BYTE CI2C_Start(BYTE I2CLine, BYTE device)
{
    BYTE ucTimeOut = _I2C_TIMEOUT_LIMIT;

    CSetI2CSCL(I2CLine);

    CSetI2CSDA(I2CLine);

    Delay5us();

    while(!(CCheckI2CSCL(I2CLine)))
    {
        if(ucTimeOut > 0)
        {
            ucTimeOut--;
        }
        else
        {
        #if _DEBUG_MESSAGE_SUPPORT
//		CDebugMessage("CI2C_Startfail", 0);
	#endif
            return _FALSE;
        }
    }

    CClrI2CSDA(I2CLine);
    Delay5us();
    CClrI2CSCL(I2CLine);

    Delay5us();

    return CI2cSendByte(I2CLine,device);
}

void CI2cStop(BYTE I2CLine)
{
    CClrI2CSDA(I2CLine);
    CSetI2CSCL(I2CLine);
    Delay5us();
    CSetI2CSDA(I2CLine);
}

BYTE CI2cGetAck(BYTE I2CLine)
{
    BYTE ack;

    CSetI2CSDA(I2CLine);
    CSetI2CSCL(I2CLine);

    Delay5us();
    ack = CCheckI2CSDA(I2CLine);
    CClrI2CSCL(I2CLine);
    Delay5us();

    CSetI2CSDA(I2CLine);

    return ack;
}

void CI2cSendAck(BYTE I2CLine)
{
    CClrI2CSDA(I2CLine);
    CSetI2CSCL(I2CLine);
    Delay5us();
    CClrI2CSCL(I2CLine);
    Delay5us();
}

void CI2cSendNoAck(BYTE I2CLine)
{
    CSetI2CSDA(I2CLine);
    CSetI2CSCL(I2CLine);
    Delay5us();
    CClrI2CSCL(I2CLine);

    Delay5us();
}

BYTE CI2cSendByte(BYTE I2CLine,BYTE ucValue)
{
    BYTE cnt;

    for(cnt = 0; cnt < 8; cnt++)
    {
        if((bit)(ucValue & 0x80))
        {
            CSetI2CSDA(I2CLine);
        }
        else
        {
            CClrI2CSDA(I2CLine);
        }

        CSetI2CSCL(I2CLine);
        Delay5us();
        CClrI2CSCL(I2CLine);

        Delay5us();

        ucValue = ucValue << 1;
    }

    if(CI2cGetAck(I2CLine))
    {
     #if _DEBUG_MESSAGE_SUPPORT

//	CDebugMessage("_I2C_BUSY", 0);
     #endif
        CI2cStop(I2CLine);
        return _I2C_BUSY;
    }
    else
    {
    
// #if _DEBUG_MESSAGE_SUPPORT

//CDebugMessage("_I2C_OK", 0);
// #endif
        return _I2C_OK;
    }
}

BYTE CI2cGetByte(BYTE I2CLine)
{
    BYTE cnt, value;

    value = 0;

    CSetI2CSDA(I2CLine);

    for(cnt = 0; cnt < 8; cnt++)
    {
        CSetI2CSCL(I2CLine);
        Delay5us();

        value = (value << 1) | CCheckI2CSDA(I2CLine);

        CClrI2CSCL(I2CLine);

        Delay5us();
    }

    return value;
}

bit CI2cWriteStart(BYTE I2CLine,BYTE ucDeviceAddr, BYTE ucStartAddr)
{
    BYTE timeoutcnt, control;

    timeoutcnt = _I2C_TIMEOUT_LIMIT;

    control = ucDeviceAddr | _I2C_WR;

    while(CI2C_Start(I2CLine, control) != _I2C_OK)
    {
    
        timeoutcnt--;
        if(!timeoutcnt)
        {
            return _FAIL;
        }
    }
if (I2CLine==LS_LINE)
{
    control = ucStartAddr | 0x80;

	if(CI2cSendByte(I2CLine,control ) != _I2C_OK)
	{
		return _FAIL;
	}
}	
else
{
    if(CI2cSendByte(I2CLine,ucStartAddr) != _I2C_OK)
    {
    #if _DEBUG_MESSAGE_SUPPORT
//	CDebugMessage("CI2cSendByte(I2CLine,ucStartAddr) != _I2C_OK", 0);
    #endif
        return _FAIL;
    }
}
    return _SUCCESS;

}

//--------------------------------------------------
// Description  : Read data from the selected device by I2C protocol
// Input Value  : ucDeviceAddr  --> Device address
//                ucStartAddr   --> Start address of selected device
//                usLength      --> Numbers of data we want to read
//                pReadArray    --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit CI2cRead(BYTE I2CLine,BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pReadArray)
{
    BYTE control;

    if(usLength == 0)
    {
        return _FAIL;
    }

    if(CI2cWriteStart(I2CLine,ucDeviceAddr, ucStartAddr) == _FAIL)
    {
    #if _DEBUG_MESSAGE_SUPPORT
//	CDebugMessage("CI2cWriteStart fail",0);
    #endif
        return _FAIL;
    }

    control = ucDeviceAddr | _I2C_RD;

    if(CI2C_Start(I2CLine,control) != _I2C_OK)
    {
        return _FAIL;
    }

    while(--usLength)
    {


        *pReadArray++ = CI2cGetByte(I2CLine);

        CI2cSendAck(I2CLine);
    }

    *pReadArray++ = CI2cGetByte(I2CLine);

    CI2cSendNoAck(I2CLine);
    CI2cStop(I2CLine);
#if _DEBUG_MESSAGE_SUPPORT
//	CDebugMessage("CI2cWriteStart truel",0);
#endif

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by I2C protocol
// Input Value  : ucDeviceAddr  --> Device address
//                ucStartAddr   --> Start address of selected device
//                usLength      --> Numbers of data we want to write
//                pWriteArray   --> Writing data array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit CI2cWrite(BYTE I2CLine,BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pWriteArray)
{
    BYTE control;

    if(usLength == 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(CI2cWriteStart(I2CLine,ucDeviceAddr, ucStartAddr) == _FAIL)
        {
        #if _DEBUG_MESSAGE_SUPPORT
//		CDebugMessage("CI2cWriteStart fail", 0);
	#endif
            return _FAIL;
        }

        control = _I2C_WRITE_SIZE - (ucStartAddr & 0x0f);
        #if _DEBUG_MESSAGE_SUPPORT
//		CDebugMessage("control ", control );
	#endif

        if(usLength > control)
        {
            usLength -= control;
            if(ucStartAddr >= 0xf0)
            {
                ucDeviceAddr += 2;
            }
            ucStartAddr += control;
        }
        else
        {
            control = usLength;
            usLength = 0;
        }

        while(control--)
        {
            if(CI2cSendByte(I2CLine,*pWriteArray++) != _I2C_OK)
            {
        #if _DEBUG_MESSAGE_SUPPORT
//		CDebugMessage("CI2cWriteStart fail2", 0);
	#endif
            
                return _FAIL;
            }
        }

        CI2cStop(I2CLine);
        CTimerDelayXms(5);
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Polling write cycle finish
// Input Value  : ucDeviceAddr  --> Device address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
#if(_MEMORY_LOCATION == _EEPROM)
bit CI2cWritePolling(BYTE I2CLine, BYTE ucDeviceAddr)
{
    BYTE control = 0, ucTimeoutCnt = 0;

    ucTimeoutCnt = _I2C_TIMEOUT_LIMIT;
    control = ucDeviceAddr | _I2C_WR;

    while(CI2C_Start(I2CLine, control)!= _I2C_OK)
    {
        ucTimeoutCnt--;

        if(!ucTimeoutCnt)
        {
            return _FAIL;
        }
    }

    CI2cStop(I2CLine);

    return _SUCCESS;
}
#endif // End of #if(_MEMORY_LOCATION == _EEPROM)

