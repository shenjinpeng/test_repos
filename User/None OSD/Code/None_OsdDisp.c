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
// ID Code      : OsdDisp.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __NONE_OSDDISP__

#include "Common\Header\Include.h"

#if(_OSD_TYPE == _NONE_OSD)

//--------------------------------------------------
// Description  : Initial OSD flag state
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispInitial()
{
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispColorProcess()
{
BYTE i,j;

    CEepromLoadBriConData();
    CEepromLoadColorTempData();

    CAdjustContrast(stConBriData.Contrast);
    CAdjustBrightness(stConBriData.Brightness);
    stSystemData.BackLight=tOSD_DICOMlumi[stConBriData.Dicom] ;
    CAdjustBacklight(stSystemData.BackLight);


	
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("COsdDispColorProcess", stConBriData.Dicom);
#endif

#if(_VIVID_COLOR_FUCTION == _ON)

//    COsdDispVividColor(GET_VIVID_COLOR_TYPE());

#endif // End of #if(_VIVID_COLOR_FUCTION == _ON)

}

//----------------------------------------------------------------------------------------------------
// Changeover Functions
//----------------------------------------------------------------------------------------------------
BYTE COsdDispContrastChangeover(BYTE ucSelect, BYTE ucValue)
{
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_DVI)
    {
        ucValue -= 7;
    }

//    ucValue = ((WORD)ucValue * (_CONTRAST_MAX - _CONTRAST_MIN) / 100) + _CONTRAST_MIN;

    ucValue = (((WORD)stColorTempData.ColorTemp[ucSelect] * ucValue / 128) > 255) ? 255 : (BYTE)((WORD)stColorTempData.ColorTemp[ucSelect] * ucValue / 128);

    return ucValue;
}

BYTE COsdDispBacklightChangeover(BYTE ucValue)
{
    ucValue = ((WORD)ucValue * (_BACKLIGHT_MAX - _BACKLIGHT_MIN) / 100) + _BACKLIGHT_MIN;

    return ucValue;
}


//----------------------------------------------------------------------------------------------------
// OSD Display Functions
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
// OSD Event Functions
//----------------------------------------------------------------------------------------------------
void COsdDispOsdTimerEvent(void)
{
    COsdFxDisableOsd();
    ucOsdState = _MENU_NONE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispFirstTimeLoadFont(void)
{
    CScalerLoadHardwareVLCFont(tFONT_GLOBAL, 0x00);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispClearText(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight)
{
    BYTE temp;

    for(temp = 0; temp < ucHeight; temp++)
    {
        COsdFxHLine(ROW(ucRow + temp), COL(ucCol), LENGTH(ucWidth), 0x10, _WRITE_BYTE2);
        COsdFxHLine(ROW(ucRow + temp), COL(ucCol), LENGTH(ucWidth), 0x00, _WRITE_BYTE1);
        COsdFxHLine(ROW(ucRow + temp), COL(ucCol), LENGTH(ucWidth), 0x8c, _WRITE_BYTE0);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE COsdDispRealToPercent(WORD RealValue, WORD Max, WORD Min)
{
    WORD i;
    RealValue = MINOF(RealValue, Max);
    RealValue = MAXOF(RealValue, Min);

    if(Max <= Min)
    {
        i = 0;
    }
    else
    {
        i = (((DWORD)(RealValue - Min)*10000) / (Max - Min));
    }

    if((i % 100) > 49)
    {
        i = i + 100;
    }
        i = i / 100;

    return((BYTE)i);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD COsdDispPercentToRealValue(BYTE PercentValue, WORD Max, WORD Min)
{
    WORD i;
    PercentValue = MINOF(100, PercentValue);
    i = (((DWORD)PercentValue*(Max - Min)*10) / 100);

    if((i % 10) > 5)
    {
        i = i + 10;
    }

    return((i / 10) + Min);
}


#endif  // End of #if(_OSD_TYPE == _NONE_OSD)

