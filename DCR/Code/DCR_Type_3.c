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
// ID Code      : DCR.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __DCR_TYPE_3__

#include "Common\Header\Include.h"

#if(_DCR_MODE == _DCR_TYPE_3)

//--------------------------------------------------
// Description  : Initialized DCC and DCR function
// Input Value  : None
// Output Value : None
// Return Value : None
//--------------------------------------------------
void CDcrInitial(void)
{
    BYTE i = 0;

    CAdjustNormalizeFactor(stDisplayInfo.DHWidth, stDisplayInfo.DVHeight);  // Normalize factor
    CScalerPageSelect(_PAGE7);
    if(!CScalerGetBit(_P7_DCC_CTRL0_C7, _BIT7)) // no use dcc
    {
        CScalerSetByte(_P7_DCC_CTRL1_C8, 0x00); // disable DCC gain
        CScalerSetByte(_P7_DCC_CTRL0_C7, 0x40); // Y_formula 1, page0
        CScalerSetByte(_P7_DCC_ACCESS_PORT_C9, 0x03);
        for (i = 0; i < 9; i++)                     // page0 setting
        {
            CScalerSetByte(_P7_DCC_DATA_PORT_CA, tDCC_PAGE0[i]);
        }
    }
    else    // use dcc color type
    {
        CScalerSetBit(_P7_DCC_CTRL0_C7, ~(_BIT2 | _BIT1 | _BIT0), 0x00);    // BWL_EXP off page0

        CScalerSetByte(_P7_DCC_ACCESS_PORT_C9, 0x03);               // BBE off
        CScalerSetByte(_P7_DCC_DATA_PORT_CA, 0x00);

        CScalerSetByte(_P7_DCC_ACCESS_PORT_C9, 0x05);               // RH0/RH1 limiter off
        CScalerRead(_P7_DCC_DATA_PORT_CA, 1, pData, _NON_AUTOINC);
        pData[0] = pData[0] & 0x0f;
        CScalerSetByte(_P7_DCC_ACCESS_PORT_C9, 0x05);
        CScalerSetByte(_P7_DCC_DATA_PORT_CA, pData[0]);

        CScalerSetByte(_P7_DCC_ACCESS_PORT_C9, 0x07);
        CScalerSetByte(_P7_DCC_DATA_PORT_CA, 0x00);         // Y_MAX_LB =0, special detect
        CScalerSetByte(_P7_DCC_DATA_PORT_CA, 0xFF);         // Y_MIN_HB = 0xff, special detect
    }
                                                            // daniel DCR add 070531
    g_ucDcrCnt = 1;                                         // reset counter
    g_ucDcrTargetPre = _PWM_HIGH + 10;                      // diff from the 4 value
    g_ucDcrTemp = _PWM_LOW + 5;                             // diff from the 4 value
    g_ucDcrPwm = stSystemData.BackLight;
    g_ucDcrTimer = 0;
}

#if(_ACER_HIGH_ACM == _ON)
//--------------------------------------------------
// Description  : A timer for DCR control.
// Input Value  : None
// Output Value : None
// Return Value : None
//--------------------------------------------------
void CDcr5MinTimerCount(void)
{
    if(g_usDCR5MinTimer != 15000)
    {
        g_usDCR5MinTimer = g_usDCR5MinTimer + 1;
    }
    else
    {
        if(GET_DCR_ULTRA_MIN())
        {
            g_ucDcrPwm = _ULTRA_MIN;
            CLR_DCR_ULTRA_MIN();
        }
        else
        {
            g_ucDcrPwm = _PWM_MIN;
            SET_DCR_ULTRA_MIN();
        }

        g_usDCR5MinTimer = 0;
    }
}
#endif  // End of #if(_ACER_HIGH_ACM == _ON)

//--------------------------------------------------
// Description  : Main function of DCR type 3.
// Input Value  : None
// Output Value : None
// Return Value : None
//--------------------------------------------------
void CDcrDcr3(void)
{
    BYTE S0Percentage = 0;          // daniel 20070626
    BYTE S0S6Total = 0;     // daniel 20070626
    BYTE diff = 0;
    bit bTargetChange = 0;

    CScalerPageSelect(_PAGE7);

    CScalerSetBit(_P7_DCC_CTRL0_C7, ~(_BIT7 | _BIT1 | _BIT0), _BIT7);   // enable DCC , page0
    CScalerSetByte(_P7_DCC_ACCESS_PORT_C9, 0x0C);
    CScalerRead(_P7_DCC_DATA_PORT_CA, 11, pData, _NON_AUTOINC);

//  Y_MAX_VAL = pData[2];   Y_MIN_VAL = pData[3];   S0_VALUE  = pData[4];

    S0S6Total = pData[4] + pData[5] + pData[6] + pData[7] + pData[8] + pData[9] + pData[10];  // daniel 20070626
    S0Percentage = (WORD)pData[4] * 100 / 255;              // S0_VALUE %

    if(S0Percentage < 80)
    {
        if((bit)CScalerGetBit(_VGIP_CTRL_10, _BIT1))
        {
            if(pData[3] > 252)                      // Y_MIN_VAL > 252
            {
                g_ucDcrPwm = _PWM_MAX;
            }
            else
            {
                g_ucDcrPwm = _PWM_HIGH;
            }
        }
        else                        // analog input
        {
            if(pData[3] > 215)                  // Y_MIN_VAL > 215
            {
                g_ucDcrPwm = _PWM_MAX;
            }
            else if(S0S6Total <= 1)         // daniel 20070626
            {
                g_ucDcrPwm = _PWM_MAX;          // daniel 20070626
            }
            else
            {
                g_ucDcrPwm = _PWM_HIGH;
            }
        }
    }
    else if(S0Percentage < 90)
    {
        if(pData[2] > 220)                          // Y_MAX_VAL > 220
        {
            g_ucDcrPwm = _PWM_HIGH;
        }
        else
        {
            g_ucDcrPwm = _PWM_LOW;
        }
    }
    else
    {
        if((bit)CScalerGetBit(_VGIP_CTRL_10, _BIT1))
        {
            if(pData[2] < 4)                        // Y_MAX_VAL < 4
            {
                g_ucDcrPwm = _PWM_MIN;
            }
            else if(pData[2] > 220)                 // Y_MAX_VAL > 220
            {
                g_ucDcrPwm = _PWM_HIGH;
            }
            else
            {
                g_ucDcrPwm = _PWM_LOW;
            }
        }
        else                    // analog input
        {
#if(_ACER_HIGH_ACM == _ON)

            if(pData[2] < 10)                       // Y_MAX_VAL < 10  test
            {
                if((g_ucDcrTemp == _PWM_MIN) || (g_ucDcrTemp == _ULTRA_MIN))
                {
                    CDcr5MinTimerCount();
                }
                else
                {
                    SET_DCR_ULTRA_MIN();
                    g_ucDcrPwm = _PWM_MIN;
                    g_usDCR5MinTimer = 0;
                }
            }
#else
            if(pData[2] < 10)                       // Y_MAX_VAL < 10
            {
                g_ucDcrPwm = _PWM_MIN;
            }
#endif
            else if(pData[2] > 220)                 // Y_MAX_VAL > 220
            {
                g_ucDcrPwm = _PWM_HIGH;
            }
            else
            {
                g_ucDcrPwm = _PWM_LOW;
            }
        }
    }

    if(!GET_DCR_STATUS())
    {
        g_ucDcrPwm = stSystemData.BackLight;
    }

    // ------- step by step PWM -------------//
    pData[1] = g_ucDcrCurrentPWM;

    if(g_ucDcrTemp == g_ucDcrPwm)                       // target_pre = target_now
    {
        bTargetChange = 0;
    }
    else
    {
        bTargetChange = 1;
        g_ucDcrCnt = 1;
    }

    //****************************************************************
    // Suppose 1 -> 400 takes 8sec (DCR3 runs every 20msec).
    // g_usDcrStep inidicate how many g_ucDcrCnt counts, then PWM +/- 1
    //****************************************************************
    if(bTargetChange)
    {
        if(pData[1] > g_ucDcrPwm)               // current > target_now
        {
            diff = pData[1] - g_ucDcrPwm;
            g_usDcrStep = 4000 / diff;          // how many g_ucDcrCnt, then PWM +/- 1
        }
        else
        {
            diff = g_ucDcrPwm - pData[1];
            g_usDcrStep = 4000 / diff;
        }
    }

    if(pData[1] == g_ucDcrPwm)
    {
        pData[1] = pData[1];
        g_ucDcrCnt = 1;
    }
    else if(((g_ucDcrTargetPre == _PWM_MAX) && (g_ucDcrPwm == _PWM_MIN))
         || ((g_ucDcrTargetPre1 == _PWM_MAX) && (g_ucDcrTargetPre != _PWM_MIN) && (g_ucDcrPwm == _PWM_MIN)) )   // test
    {
        if(g_ucDcrCnt % ((g_usDcrStep / 10) * 2) == 0)      // 16s      MAX-MIN
        {
            CTimerDelayXms((g_usDcrStep % 10)* 2 * 2);
            pData[1] = pData[1] - 1;
        }
    }
    else if(pData[1] > g_ucDcrPwm)
    {
        if(g_ucDcrCnt % (g_usDcrStep / 10) == 0)                // 8s
        {
            CTimerDelayXms((g_usDcrStep % 10)* 2);
            pData[1] = pData[1] - 1;
        }
    }
    else if(((g_ucDcrTargetPre == _PWM_MIN) && (g_ucDcrPwm == _PWM_MAX))
         || ((g_ucDcrTargetPre1 == _PWM_MIN) && (g_ucDcrTargetPre != _PWM_MAX) && (g_ucDcrPwm == _PWM_MAX)) )   // test
    {
        if(g_ucDcrCnt % ((g_usDcrStep / 10) * 2) == 0)      // 16s      MIN-MAX
        {
            CTimerDelayXms((g_usDcrStep % 10) * 2 * 2);
            pData[1] = pData[1] + 1;
        }
    }
    else                                        // pData[1] < g_ucDcrPwm
    {
        if(g_ucDcrCnt % (g_usDcrStep / 10) == 0)                // 8s
        {
            CTimerDelayXms((g_usDcrStep % 10)* 2);
            pData[1] = pData[1] + 1;
        }
    }

    g_ucDcrCurrentPWM = pData[1];
    pData[1] = ((WORD)pData[1] * g_ucDCRPercent + (WORD)(stSystemData.BackLight * (100 - g_ucDCRPercent))) / 100;
    CAdjustBacklight(pData[1]);

    if(bTargetChange)
    {
        g_ucDcrTargetPre1 = g_ucDcrTargetPre;
        g_ucDcrTargetPre = g_ucDcrTemp;
        g_ucDcrTemp = g_ucDcrPwm;
    }

    g_ucDcrCnt = g_ucDcrCnt + 1;
}

#endif // End of #if(_DCR_MODE == _DCR_TYPE_3)


