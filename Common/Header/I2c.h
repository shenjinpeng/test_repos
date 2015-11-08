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
// ID Code      : I2c.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of I2c.c
//--------------------------------------------------
#define _I2C_WRITE_SIZE                 16
#define _I2C_TIMEOUT_LIMIT              255

#define _I2C_BUSY                       0
#define _I2C_OK                         1

#define _I2C_WR                         0
#define _I2C_RD                         1

    enum I2C_Line
    {
        NVRAM_LINE,
    	 LS_LINE,
    };



//----------------------------------------------------------------------------------------------------

#ifdef __I2C__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------

//WORD PrelumValue;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void Delay5us(void);

BYTE CI2C_Start(BYTE I2CLine, BYTE device);//BYTE CI2cStart(BYTE ucDeviceAddr);

void CI2C_Stop(BYTE I2CLine);//void CI2cStop(void);
 BYTE CI2cGetAck(BYTE I2CLine); //BYTE CI2cGetAck(void);
void CI2cSendAck(BYTE I2CLine);//void CI2cSendAck(void);
BYTE CI2cSendByte(BYTE I2Cline,BYTE ucValue);//BYTE CI2cSendByte(BYTE ucValue);

BYTE CI2cGetByte(BYTE I2Cline);//BYTE CI2cGetByte(void);

bit CI2cRead(BYTE I2CLine,BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pReadArray);
bit CI2cWrite(BYTE I2CLine,BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pWriteArray);

#if(_MEMORY_LOCATION == _EEPROM)
bit CI2cWritePolling(BYTE I2CLine,BYTE ucDeviceAddr);
#endif


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------

//extern  WORD PrelumValue;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void Delay5us(void);
extern BYTE CI2C_Start(BYTE I2CLine, BYTE device);//BYTE CI2cStart(BYTE ucDeviceAddr);

extern void CI2C_Stop(BYTE I2CLine);//void CI2cStop(void);
extern BYTE CI2cGetAck(BYTE I2CLine); //BYTE CI2cGetAck(void);
extern void CI2cSendAck(BYTE I2CLine);//void CI2cSendAck(void);
extern BYTE CI2cSendByte(BYTE I2CLine,BYTE ucValue);//BYTE CI2cSendByte(BYTE ucValue);

extern BYTE CI2cGetByte(BYTE I2CLine);//BYTE CI2cGetByte(void);

extern bit CI2cRead(BYTE I2CLine,BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pReadArray);
extern bit CI2cWrite(BYTE I2CLine,BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pWriteArray);

#if(_MEMORY_LOCATION == _EEPROM)
extern bit CI2cWritePolling(BYTE I2CLine,BYTE ucDeviceAddr);
#endif

#endif

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of I2c.c
//--------------------------------------------------
#define SETI2CSDA()                 (bI2CSDA = _TRUE)
#define CLRI2CSDA()                 (bI2CSDA = _FALSE)
#define CHECKI2CSDA()               (bI2CSDA)

#define SETI2CSCL()                 (bI2CSCL = _TRUE)
#define CLRI2CSCL()                 (bI2CSCL = _FALSE)
#define CHECKI2CSCL()               (bI2CSCL)

#define SETLSSDA()                 (bLSSDA = _TRUE)
#define CLRLSSDA()                 (bLSSDA = _FALSE)
#define CHECKLSSDA()               (bLSSDA)

#define SETLSSCL()                 (bLSSCL = _TRUE)
#define CLRLSSCL()                 (bLSSCL = _FALSE)
#define CHECKLSSCL()               (bLSSCL)





