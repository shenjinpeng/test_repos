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
// ID Code      : Timer.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __TIMER__

#include "Common\Header\Include.h"

//--------------------------------------------------
// Description  : Check if it's time to execute events
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CTimerHandler(void)
{
    BYTE timereventcnt;

    for(timereventcnt = 0; timereventcnt < _MAX_EVENT_AMOUNT; timereventcnt++)
    {
        if(TimerEvent[timereventcnt].Time == 0)
        {
            bTimer0Ctrl = _TRUE;
            TimerEvent[timereventcnt].Time = _INACTIVE_TIMER_EVENT;
            bTimer0Ctrl = _FALSE;
            (*TimerEvent[timereventcnt].Event)();
        }
    }
}

//--------------------------------------------------
// Description  : Set up a timer for an event. If the event is exist,
//                this function is ignored and do not change the executing time.
// Input Value  : usTime    --> Unit in 10ms, range in 0.01 ~ 655.3 sec
//                Event     --> Execute Event while timeup
// Output Value : None
//--------------------------------------------------
void CTimerActiveTimerEvent(WORD usTime, void (*Event)())
{
    BYTE timereventcnt;

    for(timereventcnt = 0; timereventcnt < _MAX_EVENT_AMOUNT; timereventcnt++)
    {
        if((TimerEvent[timereventcnt].Time != _INACTIVE_TIMER_EVENT) && (TimerEvent[timereventcnt].Event == Event))
        {
            return;
        }
    }

    for(timereventcnt = 0; timereventcnt < _MAX_EVENT_AMOUNT; timereventcnt++)
    {
        if(TimerEvent[timereventcnt].Time == _INACTIVE_TIMER_EVENT)
        {
            bTimer0Ctrl = _TRUE;
            TimerEvent[timereventcnt].Time = usTime;
            bTimer0Ctrl = _FALSE;
            TimerEvent[timereventcnt].Event = Event;
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Reactive a timer for an event. If the event is exist,
//                this function will reset the executing time and restart.
// Input Value  : usTime    --> Unit in 10ms, range in 0.01 ~ 655.3 sec
//                Event     --> Execute Event while timeup
// Output Value : None
//--------------------------------------------------
void CTimerReactiveTimerEvent(WORD usTime, void (*Event)())
{
    BYTE timereventcnt;

    for(timereventcnt = 0; timereventcnt < _MAX_EVENT_AMOUNT; timereventcnt++)
    {
        if((TimerEvent[timereventcnt].Time != _INACTIVE_TIMER_EVENT) && (TimerEvent[timereventcnt].Event == Event))
        {
            bTimer0Ctrl = _TRUE;
            TimerEvent[timereventcnt].Time = usTime;
            bTimer0Ctrl = _FALSE;
            return;
        }
    }

    CTimerActiveTimerEvent(usTime, Event);
}

//--------------------------------------------------
// Description  : Cancel an event
// Input Value  : Event     --> Event which we want to cancel
// Output Value : None
//--------------------------------------------------
void CTimerCancelTimerEvent(void (*Event)())
{
    BYTE timereventcnt;

    for(timereventcnt = 0; timereventcnt < _MAX_EVENT_AMOUNT; timereventcnt++)
    {
        if(TimerEvent[timereventcnt].Event == Event)
        {
            bTimer0Ctrl = _TRUE;
            TimerEvent[timereventcnt].Time = _INACTIVE_TIMER_EVENT;
            bTimer0Ctrl = _FALSE;
        }
    }
}

//--------------------------------------------------
// Description  : Initial timer and events. We have to run this function at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CTimerInitialTimerEvent(void)
{
    BYTE timereventcnt;

    for(timereventcnt = 0; timereventcnt < _MAX_EVENT_AMOUNT; timereventcnt++)
    {
        TimerEvent[timereventcnt].Time = _INACTIVE_TIMER_EVENT;
    }

    TR0 = 1;
}

//--------------------------------------------------
// Description  : Decrease timer counts while 10ms Interrupt is up
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CTimerDecreaseTimerCnt(void)
{
    BYTE timerdeccnt;

    for(timerdeccnt = 0; timerdeccnt < _MAX_EVENT_AMOUNT; timerdeccnt++)
    {
        if((TimerEvent[timerdeccnt].Time != _INACTIVE_TIMER_EVENT) && (TimerEvent[timerdeccnt].Time != 0))
        {
            TimerEvent[timerdeccnt].Time--;
        }
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Count down event process
// Input Value  : pEventCnt --> Event counter
//                ucWaitCnt --> Count down number (Max: 254)
//                Event     --> Execute Event while counter is zero
// Output Value : None
//----------------------------------------------------------------------------------------------------
void CTimerCountDownEventProc(BYTE *pEventCnt, BYTE ucWaitCnt, void (*Event)(void))
{
    if(*pEventCnt == _INACTIVE_COUNTDOWN_EVENT)
    {
        *pEventCnt = ucWaitCnt;
    }
    else if(*pEventCnt == 0)
    {
        *pEventCnt = _INACTIVE_COUNTDOWN_EVENT;
        Event();
    }
    else
    {
        *pEventCnt = *pEventCnt - 1;
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Polling Event Process
// Input Value  : ucTimeout --> Timeout number (Max: 255 ms)
//                Event     --> Polling event. This event has to return _TRUE or _FALSE
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------------------------------------
bit CTimerPollingEventProc(BYTE ucTimeout, bit (*Event)(void))
{
    do
    {
        CTimerDelayXms(1);

        if(Event())
        {
            return _TRUE;
        }
    }
    while(--ucTimeout);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Hold program for 0 ~ 65535 ms
// Input Value  : usNum     --> Delay time
// Output Value : None
//--------------------------------------------------
void CTimerDelayXms(WORD usNum)
{
    if(usNum)
    {
        bNotifyTimer0Int = _FALSE;

        while(_TRUE)
        {
            if(bNotifyTimer0Int)
            {
                bNotifyTimer0Int = _FALSE;

                if(--usNum)
                {
                    TR0 = _ON;
                }
                else
                {
                    return;
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : ucEvent   --> Specified event
// Output Value : Return _TRUE while timeout
//--------------------------------------------------
bit CTimerWaitForEvent(BYTE ucEvent)
{
    BYTE temp;
    BYTE timeoutcnt = 30;                   // 30ms timeout

    CScalerSetByte(_STATUS1_03, 0x00);      // Clear status (status register will be cleared after write)

    bNotifyTimer0Int = _FALSE;

    do
    {
        if(bNotifyTimer0Int)
        {
            bNotifyTimer0Int = _FALSE;

            if(--timeoutcnt)
            {
                TR0 = _ON;
            }
        }

        CScalerRead(_STATUS1_03, 1, &temp, _NON_AUTOINC);

        temp &= ucEvent;
    }
    while((temp == 0) && (timeoutcnt != 0));

    return timeoutcnt ? _FALSE : _TRUE;
}

//----------------------------------------------------------------------------------------------------
// Description  : Polling Scaler Flag Process
// Input Value  : ucTimeout --> Timeout number (Max: 255 ms)
//                ucPage    --> Current Page (Common Area use _PAGE_COMMON)
//                ucRegister--> Current Register
//                ucBit     --> Polling Bit
//                bSuccess  --> 1 or 0 when finished for Polling Bit
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------------------------------------
bit CTimerPollingFlagProc(WORD usTimeout, BYTE ucPage, BYTE ucRegister, BYTE ucBit, bit bSuccess)
{
    // V012 Modify 20100324 Start
    // V012 Patch Note (18) : Fix the sync processor unlock issue which causes APLL setting fail.
    /*
    if(ucPage != _PAGE_COMMON)
    {
        CScalerPageSelect(ucPage);
    }

    do
    {
        CTimerDelayXms(1);

        if(!((bit)CScalerGetBit(ucRegister, ucBit) ^ bSuccess))
        {
            return _TRUE;
        }
    }
    while(--usTimeout);

    return _FALSE;
    */

    // V016 VGA Patch Note (8) Modify 20100809 Start
    // Patch Reason : Modify the function to aviod mode change while polling the flag.
    /*
    if(ucPage != _PAGE_COMMON)
    {
        CScalerPageSelect(ucPage);
    }

    // APLL Process is on going & Sync Processor Auto Run Enabled with Separate Sync Type.
    if((GET_APLL_PROCESS() == _TRUE)
    && (CScalerGetBit(_SYNC_SELECT_47, (_BIT6 | _BIT5 | _BIT4)) == 0x60)
    && (CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0xE0))
    {
        do
        {
            CTimerDelayXms(1);

            // Sync Processor Capture Window Unlock
            if(CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT0) == _BIT0)
            {
                // Clear Unlock Flags
                CScalerSetByte(_HSYNC_TYPE_DETECTION_FLAG_4E, 0xFF);
            }

            if(((bit)CScalerGetBit(ucRegister, ucBit) ^ bSuccess) == _FALSE)
            {
                return _TRUE;
            }
        }
        while(--usTimeout);
    }
    else
    {
        do
        {
            CTimerDelayXms(1);

            if(((bit)CScalerGetBit(ucRegister, ucBit) ^ bSuccess) == _FALSE)
            {
                return _TRUE;
            }
        }
        while(--usTimeout);
    }

    return _FALSE;
    */
    do
    {
        if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
        {
            // Check Input Sync status (Hsync Overflow | Stable Period Change | Stable Polarity Change)
            // to avoid mode change.
            if((bit)(CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, (_BIT7 | _BIT6 | _BIT5))) == _TRUE)
            {
                return _FALSE;
            }

            // APLL Process is on going & Sync Processor Auto Run Enabled with Separate Sync Type.
            if((GET_APLL_PROCESS() == _TRUE)
            && (CScalerGetBit(_SYNC_SELECT_47, (_BIT6 | _BIT5 | _BIT4)) == 0x60)
            && (CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0xE0))
            {
                // Sync Processor Capture Window Unlock
                if(CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT0) == _BIT0)
                {
                    // Clear Unlock Flags
                    CScalerSetByte(_HSYNC_TYPE_DETECTION_FLAG_4E, 0xFF);
                }
            }
        }

        CTimerDelayXms(1);

        if(ucPage != _PAGE_COMMON)
        {
            CScalerPageSelect(ucPage);
        }

        if(((bit)CScalerGetBit(ucRegister, ucBit) ^ bSuccess) == _FALSE)
        {
            return _TRUE;
        }
    }
    while(--usTimeout);

    return _FALSE;
    // V016 VGA Patch Note (8) Modify 20100809 End

    // V012 Modify 20100324 End
}

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
#if(_MEMORY_LOCATION == _FLASH)
//----------------------------------------------------------------------------------------------------
// Description  : Polling MCU Flag Process
// Input Value  : ucTimeout --> Timeout number (Max: 255 ms)
//                ucAddress --> MCU Register's Address
//                ucBit     --> Polling Bit
//                bSuccess  --> 1 or 0 when finished for Polling Bit
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------------------------------------
bit CTimerPollingFlagProcForMcu(WORD usTimeout, BYTE *pucAddress, BYTE ucBit, bit bSuccess)
{
    do
    {
        CTimerDelayXms(1);

        if(!((bit)((*pucAddress) & ucBit) ^ bSuccess))
        {
            return _TRUE;
        }
    }
    while(--usTimeout);

    return _FALSE;
}
#endif  // End of #if(_MEMORY_LOCATION == _FLASH)
*/
// V015 System Patch Note (7) Modify 20100630 End

