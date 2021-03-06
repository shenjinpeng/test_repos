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

#define __DCR_TYPE_2__

#include "Common\Header\Include.h"


#if(_DCR_MODE == _DCR_TYPE_2)

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
    // end of getting horizontal bondary

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
    // end of getting vertical boundary

    CScalerPageSelect(_PAGE7);

    //CScalerSetBit(_P7_DCR_ACCESS_PORT_D8, ~_BIT1, _BIT1);  // Set RESULT_READ to read the result
    CScalerSetByte(_P7_DCR_ACCESS_PORT_D8, 0x17);
    CScalerRead(_P7_DCR_DATA_PORT_D9, 1, &pData[0], _NON_AUTOINC);    //above_th1_val_3
    CScalerSetByte(_P7_DCR_ACCESS_PORT_D8, 0x1B);
    CScalerRead(_P7_DCR_DATA_PORT_D9, 1, &pData[1], _NON_AUTOINC);    //above_th1_val_2
    CScalerSetByte(_P7_DCR_ACCESS_PORT_D8, 0x1F);
    CScalerRead(_P7_DCR_DATA_PORT_D9, 1, &pData[2], _NON_AUTOINC);    //above_th1_val_1
    CScalerSetByte(_P7_DCR_ACCESS_PORT_D8, 0x23);
    CScalerRead(_P7_DCR_DATA_PORT_D9, 1, &pData[3], _NON_AUTOINC);    //above_th1_val_0

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

    CDcrDcr2();

    CScalerSetBit(_P7_DCR_ACCESS_PORT_D8, ~_BIT1, 0x00);  // Set RESULT_READ to read the result
}

//--------------------------------------------------
// Description  : DCR Type 2 process
// Input Value  : None
// Output Value : None
// Return Value : None
//--------------------------------------------------

void CDcrDcr2(void)
{
    if(g_usRGBInfo < 48 )       // 16
    {
        pData[0] = ((DWORD)50 * 10000 / 48)  * g_usRGBInfo / 10000;

        if(pData[0] == 0)
        {
            pData[0] = ((((DWORD)50 * 10000 / 48) * g_usRGBInfo) >= 5000) ? 1 : 0;
        }
    }
    else if(g_usRGBInfo < 96)   // 32
    {
        pData[0] = ((DWORD)(220 - 50) * 10000 / (96 - 48))  * (g_usRGBInfo - 48) / 10000 + 50;
    }
    else if(g_usRGBInfo < 144)  // 48
    {
        pData[0] = ((DWORD)(230 - 220) * 10000 / (144 - 96))  * (g_usRGBInfo - 96) / 10000 + 220;
    }
    else if(g_usRGBInfo < 288)  // 96
    {
        pData[0] = 230;
    }
    else if(g_usRGBInfo < 336)  // 112
    {
        pData[0] = ((DWORD)(240 - 230) * 10000 / (336 - 288))  * (g_usRGBInfo - 288) / 10000 + 230;
    }
    else if(g_usRGBInfo < 576)  // 192
    {
        pData[0] = 240;
    }
    else if(g_usRGBInfo < 672)  // 224
    {
        pData[0] = ((DWORD)(255 - 240) * 10000 / (672 - 576))  * (g_usRGBInfo - 576) / 10000 + 240;
    }
    else                    // 240~
    {
        pData[0] = 255;
    }

    CDcrSlowAdjust(pData[0]);

    pData[1] = ((DWORD)255 * 10000 / (765 - 0))  * (g_usRGBInfo - 0) / 10000;   // g_usRGBInfo ratio
    pData[1] = 255 - pData[1];

    // step by step DCC
    if(g_ucPreDCCLum > pData[1])                // white to black
    {
        if((g_ucPreDCCLum - pData[1]) > 20)
        {
            pData[1] = g_ucPreDCCLum - 10;
        }
        else
        {
            pData[1] = g_ucPreDCCLum - 1;
        }
    }
    else if(g_ucPreDCCLum < pData[1])           // black to white
    {
        if((pData[1] - g_ucPreDCCLum) > 20)
        {
            pData[1] = g_ucPreDCCLum + 10;
        }
        else
        {
            pData[1] = g_ucPreDCCLum + 1;
        }
    }
    else
    {
        pData[1] = g_ucPreDCCLum;
    }
    // End of step by step

#if(_VIVID_COLOR_FUCTION == _ON)
    CAdjustDCRFillDCCTable(pData[1]);           // watch for the pData[1]
#endif

    g_ucPreDCCLum = pData[1];
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

#if(_VIVID_COLOR_FUCTION == _ON)
//--------------------------------------------------
// Description    : Fill DCC table , then enable DCC function,DCR Interpolation
// Input Value   : pControlTable, pUserCurveTable, both parameters accroding to Vivid color software.
// Output Value : None
// Return Value : None
//--------------------------------------------------
void CAdjustDCRFillDCCTable( BYTE lamp_value)
{
    BYTE i = 0;

    CScalerPageSelect(_PAGE7);
    CScalerRead(_P7_DCC_CTRL0_C7, 1, &i, _NON_AUTOINC);
    i = (i & 0xfc) | 0x01;
    CScalerSetByte(_P7_DCC_CTRL0_C7, i);

    // fill DCC user curve table
    CScalerSetByte(_P7_DCC_ACCESS_PORT_C9, 0x00);

    if(g_usRGBInfo < 48)
    {
        for (i = 0; i < 15; i++)
        {
            pData[0] = tDCR_USERCURVE255[i];
            CScalerSetByte(_P7_DCC_DATA_PORT_CA, pData[0]);
        }

        for (i = 0; i < 5; i++)
        {
            CScalerSetByte(_P7_DCC_DATA_PORT_CA, 0x00);
        }
    }
    else if(g_usRGBInfo < 336)
    {
        CAdjustFillDCCTable(0);
    }
    else
    {
        for (i = 0; i < 15; i++)
        {
            pData[0] = (WORD)(tDCR_USERCURVE255[i] - tDCR_USERCURVE0[i]) * lamp_value / 255 + tDCR_USERCURVE0[i];
            CScalerSetByte(_P7_DCC_DATA_PORT_CA, pData[0]);
        }

        for (i = 0; i < 5; i++)
        {
            CScalerSetByte(_P7_DCC_DATA_PORT_CA, 0x00);
        }
    }
}
#endif // End of #if(_VIVID_COLOR_FUCTION == _ON)

#endif // End of #if(_DCR_MODE == _DCR_TYPE_2)


