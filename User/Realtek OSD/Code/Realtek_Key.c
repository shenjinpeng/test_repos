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
// ID Code      : Key.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __REALTEK_KEY__

#include "Common\Header\Include.h"

#if(_OSD_TYPE == _REALTEK_OSD)


//--------------------------------------------------
// Description  : Key scan process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyHandler(void)
{

    // Clear the key message
    ucKeyMessage = _NONE_KEY_MESSAGE;

    if(CKeyScanReady())
    {
        // Store previous key state
        ucKeyStatePrev = ucKeyStateCurr;

        // Get current key state
        ucKeyStateCurr = CKeyScan();

        // Power key process, return if power key is pressed
        if(CKeyPowerKeyProc())
        {
            return;
        }

        // Convert key state to key message, store in (ucKeyNotify)
        CKeyMessageProc();
    }
}

//--------------------------------------------------
// Description  : Check power key process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyCheckPowerKey(void)
{
    // Store previous key state
    ucKeyStatePrev = ucKeyStateCurr;

    // Get current key state
    ucKeyStateCurr = CKeyScan();

    // Power key process
    CKeyPowerKeyProc();
}

//--------------------------------------------------
// Description  : Initial key status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyInitial(void)
{
    CLR_KEYSCANREADY();
    CLR_KEYSCANSTART();
}

//--------------------------------------------------
// Description  : Key scan ready process. We wait 0.02 sec in order to keep the keypad debounce
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit CKeyScanReady(void)
{
    if(GET_KEYSCANSTART() && GET_KEYSCANREADY())
    {
        return _TRUE;
    }
    else if(!GET_KEYSCANSTART())
    {
        // Wait 0.02 sec in order to keep the keypad debounce
        SET_KEYSCANSTART();
        CTimerReactiveTimerEvent(SEC(0.02), CKeyScanReadyTimerEvent);

        return _FALSE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Key scan ready timer event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyScanReadyTimerEvent(void)
{
    SET_KEYSCANREADY();
}

//--------------------------------------------------
// Description  : Key repeat enable timer event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyRepeatEnableTimerEvent(void)
{
    SET_KEYREPEATSTART();
}

//--------------------------------------------------
// Description  : Key message translation
// Input Value  : ucKeyMask     --> Key mask
//                ucKeyMsg      --> Key message
// Output Value : None
//--------------------------------------------------
void CKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg)
{
    if((ucKeyStatePrev ^ ucKeyStateCurr) & ucKeyMask)
    {
        ucKeyMessage = ucKeyMsg;
    }
    else
    {
        if(GET_KEYREPEATENABLE())
        {
            if(GET_KEYREPEATSTART())
            {
                ucKeyMessage = ucKeyMsg;
            }
            else
            {
                CTimerActiveTimerEvent(SEC(_KEY_REPEAT_START_TIME), CKeyRepeatEnableTimerEvent);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Power key process
// Input Value  : None
// Output Value : Return _TRUE if power key is pressed
//--------------------------------------------------
bit CKeyPowerKeyProc(void)
{
    if(ucKeyStateCurr & _POWER_KEY_MASK)
    {
        if((ucKeyStatePrev ^ ucKeyStateCurr) & _POWER_KEY_MASK)
        {
//cclee
           //CTimerDelayXms(25);
            //ucKeyStateCurr = CKeyScan();

            //if((ucKeyStatePrev ^ ucKeyStateCurr) & _POWER_KEY_MASK)
            //{
                CKeyPowerKeyMix();

                SET_POWERSWITCH();

                return _TRUE;
            //}
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get key status
// Input Value  : None
// Output Value : Return Key status
//--------------------------------------------------
BYTE CKeyScan(void)
{

    BYTE keystate = 0;

#if((_PCB_TYPE == _RTD2472D_DEMO_PCB) || (_PCB_TYPE == _RTD2472RD_DEMO_PCB) || (_PCB_TYPE == _RTD2545LR_DEMO_PCB))

    BYTE code ADC_SCAN_TABLE[][2] =
    {
        { 0x00, 0x14 },                 //(0.00)  0.00 ~ 0.30
        { 0x40, 0x80 },                 //(1.60)  1.40 ~ 1.80
        { 0x90, 0xd8 },                 //(2.80)  2.60 ~ 3.00
    };

    BYTE voltage1 = 0, voltage2 = 0;

    do
    {

#if((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122)) //Anderson 080107 for RTD2122
        MCU_ADC_CTRL_FF0B = 0x80;
#else
        MCU_ADC_CTRL_FF08 = 0x80;
#endif

        CTimerDelayXms(1);
        voltage1 = (AD_KEY1 & 0xfc);
        voltage2 = (AD_KEY0 & 0xfc);

#if((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122))
        MCU_ADC_CTRL_FF0B = 0x80;
#else
        MCU_ADC_CTRL_FF08 = 0x80;
#endif

        CTimerDelayXms(1);

        if (abs((AD_KEY1 & 0xfc) - voltage1) < 2 && abs((AD_KEY0 & 0xfc) - voltage2) < 2)
        {
            break;
        }

    }while (1);


    voltage1 = (AD_KEY1 & 0xfc);
    voltage2 = (AD_KEY0 & 0xfc);

    if((ADC_SCAN_TABLE[0][0] <= voltage1) && (voltage1 < ADC_SCAN_TABLE[0][1]))         // RIGHT(0.00)  0.00 ~ 0.30
    {
        keystate = keystate |_RIGHT_KEY_MASK ;
    }
    if((ADC_SCAN_TABLE[1][0] < voltage1) && (voltage1 < ADC_SCAN_TABLE[1][1]))          // LEFT (1.55)  1 ~ 1.26 //1.45 ~ 1.65
    {
        keystate = keystate |_LEFT_KEY_MASK ;
    }
    if((ADC_SCAN_TABLE[2][0] < voltage1) && (voltage1 < ADC_SCAN_TABLE[2][1]))          // NONE (2.10)  2.1~2.3 //2.00 ~ 2.20
    {
        keystate = keystate |_KEY5_MASK ;//SJP20110804 AUTO KEY
    }

    if((ADC_SCAN_TABLE[0][0] <= voltage2) && (voltage2 < ADC_SCAN_TABLE[0][1]))         // POWER(0.00)  0.00 ~ 0.30
    {
        keystate = keystate | _POWER_KEY_MASK;
    }
    if((ADC_SCAN_TABLE[1][0] < voltage2) && (voltage2 < ADC_SCAN_TABLE[1][1]))          // MENU (1.55)  1.45 ~ 1.65
    {
        keystate = keystate | _MENU_KEY_MASK;
    }
    if((ADC_SCAN_TABLE[2][0] < voltage2) && (voltage2 < ADC_SCAN_TABLE[2][1]))          // EXIT (2.10)  2.00 ~ 2.20
    {
        keystate = keystate | _EXIT_KEY_MASK;
    }

#elif((_PCB_TYPE == _RTD2472D_QA_PCB) || (_PCB_TYPE == _RTD2472RD_QA_PCB) || (_PCB_TYPE == _RTD2545LR_QA_PCB))
    if(!bRIGHT_KEY)
    {
        keystate = keystate | _RIGHT_KEY_MASK;
    }

    if(!bLEFT_KEY)
    {
        keystate = keystate | _LEFT_KEY_MASK;
    }

    if(!bEXIT_KEY)
    {
        keystate = keystate | _EXIT_KEY_MASK;
    }

    if(!bMENU_KEY)
    {
        keystate = keystate | _MENU_KEY_MASK;
    }

    if(!bPOWER_KEY)
    {
        keystate = keystate | _POWER_KEY_MASK;
    }

#else

    No Setting !!


#endif

    if(keystate != 0)
    {
        CKeyInitial();
    }

    return keystate;

}

//--------------------------------------------------
// Description  : We can add some settings here while combo key with power key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyPowerKeyMix(void)
{
    switch(ucKeyStateCurr)
    {
        case _POWER_RIGHT_KEY_MASK:
            ucOsdEventMsg = _ENTER_FACTORY_MODE_MSG;
            break;

        case _POWER_MENU_KEY_MASK:
            break;

        case _POWER_LEFT_RIGHT_KEY_MASK:
            break;
    }
}

//--------------------------------------------------
// Description  : Convert keypad status into key message, stores in ucKeyNotify
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyMessageProc(void)
{
    switch(ucKeyStateCurr)
    {
        case _MENU_KEY_MASK:
            CKeyMessageConvert(_MENU_KEY_MASK, _MENU_KEY_MESSAGE);
            break;

        case _RIGHT_KEY_MASK:
            CKeyMessageConvert(_RIGHT_KEY_MASK, _RIGHT_KEY_MESSAGE);
            break;

        case _LEFT_KEY_MASK:
            CKeyMessageConvert(_LEFT_KEY_MASK, _LEFT_KEY_MESSAGE);
            break;

        case _EXIT_KEY_MASK:
            CKeyMessageConvert(_EXIT_KEY_MASK, _EXIT_KEY_MESSAGE);
            break;

	case _KEY5_MASK:
            CKeyMessageConvert(_KEY5_MASK,_5_KEY_MESSAGE);//auto keymessage=4 sjp20110804
            break;
			
        case _LSLUMI_MASK:
            CKeyMessageConvert(_LSLUMI_MASK, _LSLUMI_MESSAGE);//LSLUMI KEYMESSAGE=8 SJP20110623
            break;
			
	case _PWMLUMI_MASK:
           CKeyMessageConvert(_PWMLUMI_MASK, _PWMLUMI_MESSAGE);//pwmLUMI KEYMESSAGE=9 SJP20110715			
           break;
		   
	case _AUTOCOLOR_MASK:
           CKeyMessageConvert(_AUTOCOLOR_MASK,_AUTOCOLOR_MESSAGE);//AUTOCOLOR KEYMESSAGE=6 SJP20110815
           break;
       case   _AGE_MODE_MASK:
		    CKeyMessageConvert(_AGE_MODE_MASK,_AGE_MODE_MESSAGE);//AUTOCOLOR KEYMESSAGE=6 SJP20110815
		    
	    
           break;
		   
        default:
            CLR_KEYREPEATSTART();
            CTimerCancelTimerEvent(CKeyRepeatEnableTimerEvent);
            break;
			
    }
}


//--------------------------------------------------
// Description  : For Demo Board Led Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyKeyPadLedControl(void)
{
    switch(ucCurrState)
    {
        case _PWOFF_STATE:
            bLED1 = 1;
            bLED2 = 1;
            break;

        case _ACTIVE_STATE:

            // V013 System Patch Note (9) 20100512 Modify Start
            // Patch Reason : Make sure LED doesn't turn green before backlight lights up.
            if(GET_READYFORDISPLAY() == _TRUE)
            {
                break;
            }
            // V013 System Patch Note (9) 20100512 Modify End

            bLED1 = 0;
            bLED2 = 1;
            break;

        case _INITIAL_STATE:
        case _SEARCH_STATE:
        case _NOSIGNAL_STATE:
        case _NOSUPPORT_STATE:
        case _SLEEP_STATE:
if(bWatchDogResetCtrl==_FALSE)
{
            bLED1 = 1;
            bLED2 = 0;
}
            break;

        default:
            break;
    }
}


#endif  // End of #if(_OSD_TYPE == _REALTEK_OSD)

