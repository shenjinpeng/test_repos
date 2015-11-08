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

#define __DCR_TYPE_1__

#include "Common\Header\Include.h"


#if(_DCR_MODE == _DCR_TYPE_1)

//--------------------------------------------------
// Description  : DCR Measurement by HW Control
// Input Value  : None
// Output Value : None
// Return Value : None
//--------------------------------------------------
void CDcrMeasureStartHD(void)
{
    DWORD ulTempB = 0;
    WORD usTempS = 0;
    WORD usTempE = 0;

    // get the horizontal boundary
    CScalerRead(_DISP_ACCESS_PORT_2A, 1, &pData[0], _NON_AUTOINC);
    CScalerSetByte(_DISP_ACCESS_PORT_2A, ((pData[0] & 0xC0) | 0x05));
    CScalerRead(_DISP_DATA_PORT_2B, 2, &pData, _NON_AUTOINC);
    usTempS = 0;
    usTempS = pData[0];
    usTempS = usTempS << 8;
    usTempS = usTempS | pData[1];
    CScalerRead(_DISP_ACCESS_PORT_2A, 1, &pData[0], _NON_AUTOINC);
    CScalerSetByte(_DISP_ACCESS_PORT_2A, ((pData[0] & 0xC0) | 0x07));
    CScalerRead(_DISP_DATA_PORT_2B, 2, &pData, _NON_AUTOINC);
    usTempE = 0;
    usTempE = pData[0];
    usTempE = usTempE << 8;
    usTempE = usTempE | pData[1];
    g_usHorBoundary = usTempE - usTempS;

    // get the vertical boundary
    CScalerRead(_DISP_ACCESS_PORT_2A, 1, &pData[0], _NON_AUTOINC);
    CScalerSetByte(_DISP_ACCESS_PORT_2A, ((pData[0] & 0xC0) | 0x10));
    CScalerRead(_DISP_DATA_PORT_2B, 2, &pData, _NON_AUTOINC);
    usTempS = 0;
    usTempS = pData[0];
    usTempS = usTempS << 8;
    usTempS = usTempS | pData[1];
    CScalerRead(_DISP_ACCESS_PORT_2A, 1, &pData[0], _NON_AUTOINC);
    CScalerSetByte(_DISP_ACCESS_PORT_2A, ((pData[0] & 0xC0) | 0x12));
    CScalerRead(_DISP_DATA_PORT_2B, 2, &pData, _NON_AUTOINC);
    usTempE = 0;
    usTempE = pData[0];
    usTempE = usTempE << 8;
    usTempE = usTempE | pData[1];
    g_usVerBoundary = usTempE - usTempS;

    CScalerPageSelect(_PAGE7);

    //CScalerSetBit(_P7_DCR_ACCESS_PORT_D8, ~_BIT1, _BIT1);  // Set RESULT_READ to read the result
    CScalerSetByte(_P7_DCR_ACCESS_PORT_D8, 0x17);
    CScalerRead(_P7_DCR_DATA_PORT_D9, 1, &pData[0], _NON_AUTOINC);
    CScalerSetByte(_P7_DCR_ACCESS_PORT_D8, 0x1B);
    CScalerRead(_P7_DCR_DATA_PORT_D9, 1, &pData[1], _NON_AUTOINC);
    CScalerSetByte(_P7_DCR_ACCESS_PORT_D8, 0x1F);
    CScalerRead(_P7_DCR_DATA_PORT_D9, 1, &pData[2], _NON_AUTOINC);
    CScalerSetByte(_P7_DCR_ACCESS_PORT_D8, 0x23);
    CScalerRead(_P7_DCR_DATA_PORT_D9, 1, &pData[3], _NON_AUTOINC);

    ulTempB = pData[0];
    ulTempB = ulTempB << 8;
    ulTempB = (ulTempB & 0x0000ff00) | pData[1];
    ulTempB = ulTempB << 8;
    ulTempB = (ulTempB & 0x00ffff00) | pData[2];
    ulTempB = ulTempB << 8;
    ulTempB = (ulTempB & 0xffffff00) | pData[3];

    ulTempB = ulTempB / g_usVerBoundary;
    ulTempB = ulTempB / g_usHorBoundary;

    g_usRGBInfo = ulTempB;

    CDcrDcr1();

    CScalerSetBit(_P7_DCR_ACCESS_PORT_D8, ~_BIT1, 0x00);    // Set RESULT_READ to read the result
}

//--------------------------------------------------
// Description  : DCR Type 1 process
// Input Value  : None
// Output Value : None
// Return Value : None
//--------------------------------------------------
void CDcrDcr1(void)
{
    if(g_usRGBInfo < 96 )
    {
        pData[0] = (DWORD)255 * g_usRGBInfo / 96;
    }
    else
    {
        pData[0] = 255;
    }

    pData[0] = ((WORD)pData[0] * g_ucDCRPercent + (WORD)(stSystemData.BackLight * (100 - g_ucDCRPercent))) / 100;

    CDcrSlowAdjust(pData[0]);
    g_ucPreDCCLum = 0;
}

//--------------------------------------------------
// Description  : Step by step adjust the backlight
//                by control PWM
// Input Value  : ucValue
// Output Value : None
// Return Value : None
//--------------------------------------------------
void CDcrSlowAdjust(WORD ucValue)
{
    pData[0] = ucValue;

    // Step by step PWM
    if(g_ucPreBacklightPWM > pData[0])              // white to black
    {
        if((g_ucPreBacklightPWM - pData[0]) > 20)
        {
            pData[0] = g_ucPreBacklightPWM - 10;
        }
        else
        {
            pData[0] = g_ucPreBacklightPWM - 1;
        }
    }
    else if(g_ucPreBacklightPWM < pData[0])         // black to white
    {
        if((pData[0] - g_ucPreBacklightPWM) > 20)
        {
            pData[0] = g_ucPreBacklightPWM + 10;
        }
        else
        {
            pData[0] = g_ucPreBacklightPWM + 1;
        }
    }
    else
    {
        pData[0] = g_ucPreBacklightPWM;
    }
    // End of step by step

    g_ucPreBacklightPWM = pData[0];
    CAdjustBacklight(pData[0]);
}

#endif // End of #if(_DCR_MODE == _DCR_TYPE_1)


