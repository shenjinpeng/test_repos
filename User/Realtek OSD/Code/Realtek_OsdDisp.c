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

#define __REALTEK_OSDDISP__

#include "Common\Header\Include.h"

#if(_OSD_TYPE == _REALTEK_OSD)


//--------------------------------------------------
// Description  : Initial OSD flag state
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispInitial(void)
{
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispColorProcess(void)
{
BYTE i,j;
    CEepromLoadBriConData();

    CEepromLoadColorTempData();

 //   CAdjustContrast(stConBriData.Contrast);
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("stConBriData.Dicom_zp",stConBriData.Dicom);
CDebugMessage("stConBriData.Gamma_zp",stConBriData.Gamma);
CDebugMessage("stConBriData.Contrast_zp",stConBriData.Contrast);										
#endif
	CAdjustBrightness(stConBriData.Brightness);	
	
     if(!(stConBriData.Gamma==0)||(stConBriData.Gamma==4))//zhangping0602 for DC ON flower screen issue
     	{
	Adjust_LUTtable(stConBriData.Gamma-1);
	stSystemData.BackLight=tOSD_DICOMlumi[3];
     	}
	 
    else
    
    	{
	Adjust_LUTtable(stConBriData.Dicom+3);
	stSystemData.BackLight=tOSD_DICOMlumi[stConBriData.Dicom];//SJP20110726 0x00;//tOSD_DICOMlumi[stConBriData.Dicom] ;//0x00;//

    	}
	CAdjustBacklight(stSystemData.BackLight);
	

#if(_VIVID_COLOR_FUCTION == _ON)

    COsdDispVividColorHLWindow();
    COsdDispVividColor();

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

/*
BYTE COsdDispBacklightChangeover(BYTE ucValue)
{
    ucValue = ((WORD)ucValue * (_BACKLIGHT_MAX-_BACKLIGHT_MIN)/100) + _BACKLIGHT_MIN;

    return ucValue;
}
*/

//----------------------------------------------------------------------------------------------------
// OSD Display Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispFirstTimeLoadFont(void)
{
    CScalerLoadHardwareVLCFont(tFONT_GLOBAL, 0x00);
    CScalerLoadHardwareVLCFont(tFONT_GLOBAL_ICON, 0xd2);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispAutoProc(void)
{
    // V013 VGA Patch Note (10) 20100416 Modify Start
    // Patch Reason : Support Auto Config For Yuv Color.
    /*
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    */
#if((_YUV_AUTO_CONFIG_SUPPORT == _ON) && (_YPBPR_SUPPORT == _ON))
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
#else
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
#endif
    // V013 VGA Patch Note (10) 20100416 Modify End
    {

        // V012 Modify 20100304 Start
        // V012 Patch Note (1) : Add RGB/YUV color space convert function.

        // V013 VGA Patch Note (10) 20100416 Modify Start
        // Patch Reason : Support Auto Config For Yuv Color.
        /*
        #if(_COLOR_FORMAT_CONVERT == _ON)
        if(GET_COLOR_FORMAT_STATUS() == _YUV_COLOR_FORMAT)
        {
            return;
        }
        #endif
        */
#if((_COLOR_FORMAT_CONVERT == _ON) && (_YUV_AUTO_CONFIG_SUPPORT == _OFF))
        if(GET_COLOR_FORMAT_STATUS() == _YUV_COLOR_FORMAT)
        {
            return;
        }
#endif
        // V013 VGA Patch Note (10) 20100416 Modify End

        // V012 Modify 20100304 End

        COsdDispAutoProcPrevWork();
        CScalerLoadHardwareVLCFont(tFONT_AUTOCONFIG, 0x60);

        COsdFxDrawWindow(XSTART(0), YSTART(0), XEND(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_AUTO_STR)*12), YEND(140), tOSD_WINDOW2_STYLE);
        COsdFxChangeWindowColor(COLOR00(_CP_DARKBLUE), tOSD_WINDOW2_STYLE);
        COsdFxDrawWindow(XSTART(10), YSTART(20), XEND(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_AUTO_STR))*12 - 10, YEND(120), tOSD_WINDOW6_STYLE);
        COsdFxChangeWindowColor(COLOR00(_CP_LIGHTBLUE), tOSD_WINDOW6_STYLE);

        COsdFxSetPosition(WIDTH(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_AUTO_STR)*12), WIDTH(140), 100, 100, 0x01);

        COsdFxLoadIcon(ROW(3), COL(3), tOSD_AUTO_ICO);
        COsdFxLoadText(ROW(4), COL(7), stOsdUserData.Language, tOSD_AUTO_STR);

        COsdFxEnableOsd();

        CAutoDoAutoConfig();

        COsdFxDisableOsd();
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispAutoColorProc(void)
{
#if(_YPBPR_SUPPORT == _ON)
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
#else
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
#endif
    {
        COsdDispAutoProcPrevWork();
        CScalerLoadHardwareVLCFont(tFONT_AUTOCOLOR, 0x60);
        COsdFxDrawWindow(XSTART(0), YSTART(0), XEND(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_AUTOCOLOR_STR)*12), YEND(140), tOSD_WINDOW2_STYLE);
        COsdFxChangeWindowColor(COLOR00(_CP_DARKBLUE), tOSD_WINDOW2_STYLE);
        COsdFxDrawWindow(XSTART(10), YSTART(20), XEND(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_AUTOCOLOR_STR))*12 - 10, YEND(120), tOSD_WINDOW6_STYLE);
        COsdFxChangeWindowColor(COLOR00(_CP_LIGHTBLUE), tOSD_WINDOW6_STYLE);

        COsdFxSetPosition(WIDTH(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_AUTOCOLOR_STR)*12), WIDTH(140), 100, 100, 0x01);

        COsdFxLoadIcon(ROW(3), COL(3), tOSD_AUTO_ICO);
        COsdFxLoadText(ROW(4), COL(7), stOsdUserData.Language, tOSD_AUTOCOLOR_STR);

        COsdFxEnableOsd();
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("222222222222",0);
#endif


        CAutoDoWhiteBalance();

        COsdFxDisableOsd();
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispNoSignalProc(void)
{
    CScalerLoadHardwareVLCFont(tFONT_GLOBAL, 0x00);
    CScalerLoadHardwareVLCFont(tFONT_NO_SIGNAL, 0x60);

    COsdDispAutoProcPrevWork();

    COsdFxDrawWindow(XSTART(0), YSTART(0), XEND(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_NOSIGNAL_STR)*12), YEND(170), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_DARKBLUE), tOSD_WINDOW2_STYLE);
    COsdFxDrawWindow(XSTART(10), YSTART(20), XEND(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_NOSIGNAL_STR))*12 - 10, YEND(150), tOSD_WINDOW6_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_LIGHTBLUE), tOSD_WINDOW6_STYLE);
    COsdFxSetPosition(WIDTH(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_NOSIGNAL_STR)*12), WIDTH(170), 100, 100, 0x01);

    COsdFxLoadIcon(ROW(3), COL(3), tOSD_NOSIGNAL_ICO);
    COsdFxLoadText(ROW(4), COL(7), stOsdUserData.Language, tOSD_NOSIGNAL_STR);

    COsdFxLoadText(ROW(6), COL(3), stOsdUserData.Language, tOSD_INPUT_SOURCE_STR);
    COsdDispClearText(ROW(6), COL(10), 10, 1);

    COsdFxLoadText(ROW(6), COL(10), _ENGLISH, tOSD_SOURCE_STR[COsdDispJudgeSourceType()]);

    COsdFxChange1bitColor(ROW(6), COL(3), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));

    COsdFxEnableOsd();
  //  if (stConBriData.Dicom<8)
//		CAdjustBacklight(stConBriData.DicomLumi);
//    else
    stSystemData.BackLight=tOSD_DICOMlumi[stConBriData.Dicom] ;

    CAdjustBacklight(stSystemData.BackLight);
    CPowerPanelOn();
  //  bData=0;//sjp20110730
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispNoCableProc(void)
{
    CScalerLoadHardwareVLCFont(tFONT_GLOBAL, 0x00);
    CScalerLoadHardwareVLCFont(tFONT_NO_SIGNAL, 0x60);

    COsdDispAutoProcPrevWork();
    COsdFxDrawWindow(XSTART(0), YSTART(0), XEND(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_NOSIGNAL_STR)*12), YEND(140), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_DARKBLUE), tOSD_WINDOW2_STYLE);
    COsdFxDrawWindow(XSTART(10), YSTART(20), XEND(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_NOSIGNAL_STR))*12 - 10, YEND(120), tOSD_WINDOW6_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_LIGHTBLUE), tOSD_WINDOW6_STYLE);
    COsdFxSetPosition(WIDTH(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_NOSIGNAL_STR)*12), WIDTH(140), 100, 100, 0x01);

    COsdFxLoadIcon(ROW(3), COL(3), tOSD_NOCABLE_ICO);
    COsdFxLoadText(ROW(4), COL(7), stOsdUserData.Language, tOSD_NOCABLE_STR);
    COsdFxEnableOsd();

//    if (stConBriData.Dicom<8)
//		CAdjustBacklight(stConBriData.DicomLumi);
//    else
	stSystemData.BackLight=tOSD_DICOMlumi[stConBriData.Dicom] ;
	CAdjustBacklight(stSystemData.BackLight);
  
	CPowerPanelOn();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispNoSupportProc(void)
{
    CScalerLoadHardwareVLCFont(tFONT_GLOBAL, 0x00);
    CScalerLoadHardwareVLCFont(tFONT_OUT_OF_RANGE, 0x60);

    COsdDispAutoProcPrevWork();

    COsdFxDrawWindow(XSTART(0), YSTART(0), XEND(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_NOSUPPORT_STR)*12), YEND(170), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_DARKBLUE), tOSD_WINDOW2_STYLE);
    COsdFxDrawWindow(XSTART(10), YSTART(20), XEND(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_NOSUPPORT_STR))*12 - 10, YEND(150), tOSD_WINDOW6_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_LIGHTBLUE), tOSD_WINDOW6_STYLE);
    COsdFxSetPosition(WIDTH(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_NOSUPPORT_STR)*12), WIDTH(170), 100, 100, 0x01);

    COsdFxLoadIcon(ROW(3), COL(3), tOSD_NOSUPPORT_ICO);
    COsdFxLoadText(ROW(4), COL(7), stOsdUserData.Language, tOSD_NOSUPPORT_STR);

    COsdFxLoadText(ROW(6), COL(3), stOsdUserData.Language, tOSD_INPUT_SOURCE_STR);
    COsdDispClearText(ROW(6), COL(10), 10, 1);
    COsdFxLoadText(ROW(6), COL(10), _ENGLISH, tOSD_SOURCE_STR[COsdDispJudgeSourceType()]);

    COsdFxChange1bitColor(ROW(6), COL(3), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));
    COsdFxEnableOsd();

 //   if (stConBriData.Dicom<8)
//		CAdjustBacklight(stConBriData.DicomLumi);
//    else
	 stSystemData.BackLight=tOSD_DICOMlumi[stConBriData.Dicom] ;

	CAdjustBacklight(stSystemData.BackLight);

	CPowerPanelOn();
}

//----------------------------------------------------------------------------------------------------
// OSD Combination Functions
//----------------------------------------------------------------------------------------------------
void COsdDispFullSlider(BYTE ucRow, BYTE ucCol, BYTE ucLength, WORD usValue, WORD usRange, WORD usMin, BYTE ucColor, BYTE ucNumColor)
{
    COsdFxHLine(ucRow, ucCol, ucLength, ((ucColor & 0x0f) << 4), _WRITE_BYTE2);
    COsdFxHLine(ucRow, ucCol, 1, 0x0d, _WRITE_BYTE1);
    COsdFxHLine(ucRow, ucCol + ucLength - 1, 1, 0x0c, _WRITE_BYTE1);

    COsdFxSlider(ucRow, ucCol + 1, ucLength - 2, usValue, usRange + usMin, usMin);
    COsdFxHLine(ucRow - 1, ucCol + ucLength - 3, 3, ((ucNumColor & 0x0f) << 4), _WRITE_BYTE2);


    // V012 Modify 20100310 Start
    // V012 Patch Note (11) : If there is no allowance for Vpos adjusting, the OSD should show 0, not 255.
    /*
    COsdFxShowNumber((ucRow - 1), (ucCol + ucLength - 3), (100 * (usValue - usMin) / usRange), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    */

    // V012 Modify 20100331 Start
    // V012 Patch Note (27) : Rounding numbers shown in OSD to make them the same as they are transferred in DDCCI.
    /*
    COsdFxShowNumber((ucRow - 1), (ucCol + ucLength - 3), ((usValue - usMin) == 0 ) ? 0 : (100 * (usValue - usMin) / usRange), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    */
    COsdFxShowNumber((ucRow ), (ucCol + ucLength+2 ), ((usValue - usMin) == 0 ) ? 0 : (((100 * (usValue - usMin)) + (usRange / 2)) / usRange), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    // V012 Modify 20100331 End

    // V012 Modify 20100310 End

}

void COsdDispDicomContent(BYTE ucRow, BYTE ucCol,  BYTE usValue)
{

	COsdFxCalcStartAddress(ucRow, ucCol, 1);
	CScalerWriteAmount(0x92, 1, 0x6a, _NON_AUTOINC);
	COsdFxCalcStartAddress(ucRow, ucCol+1, 1);
	CScalerWriteAmount(0x92, 1, 0x6c, _NON_AUTOINC);
	
	COsdFxCalcStartAddress(ucRow, ucCol+9, 1);
	CScalerWriteAmount(0x92, 1, _LEFT_ICON, _NON_AUTOINC);
	
       COsdFxLoadText(ucRow,ucCol+12 , stOsdUserData.Language, tOSD_DICOM_STR);//zhangping 101110
	COsdFxLoadText(ucRow,ucCol +19, stOsdUserData.Language, tOSD_DICOM_STR2[usValue]);//zhangping 101110
	
       if(stConBriData.Dicom<8)
       	{
			COsdFxCalcStartAddress(ucRow, ucCol+24, 1);
			CScalerWriteAmount(0x92, 1, 0x00, _NON_AUTOINC);

			COsdFxCalcStartAddress(ucRow, ucCol+25, 1);
			CScalerWriteAmount(0x92, 1, _RIGHT_ICON, _NON_AUTOINC);
		
       	}
       else
       	{
			COsdFxCalcStartAddress(ucRow, ucCol+25, 1);
			CScalerWriteAmount(0x92, 1, 0x00, _NON_AUTOINC);

			COsdFxCalcStartAddress(ucRow, ucCol+24, 1);
			CScalerWriteAmount(0x92, 1, _RIGHT_ICON, _NON_AUTOINC);

       	}
       	
       /*
       if(stConBriData.Dicom<8)
       	{
		COsdFxLoadText(ucRow,ucCol +19, stOsdUserData.Language, tOSD_DICOM_STR2[usValue]);//zhangping 101110
		
       	}
       else
       	{
       	
		COsdFxCalcStartAddress(ucRow, ucCol+19, 1);
		CScalerWriteAmount(0x92, 1, 0x6a, _NON_AUTOINC);
		COsdFxCalcStartAddress(ucRow, ucCol+20, 1);
		CScalerWriteAmount(0x92, 1, 0x00, _NON_AUTOINC);
		COsdFxCalcStartAddress(ucRow, ucCol+21, 1);
		CScalerWriteAmount(0x92, 1, _0_, _NON_AUTOINC);
  	        }	
  	*/

	//COsdFxCalcStartAddress(ucRow, ucCol+25, 1);
	//CScalerWriteAmount(0x92, 1, _RIGHT_ICON, _NON_AUTOINC);
}

void COsdDispGammaContent(BYTE ucRow, BYTE ucCol,  BYTE usValue)
{

	COsdFxCalcStartAddress(ucRow, ucCol, 1);
	CScalerWriteAmount(0x92, 1, 0x6a, _NON_AUTOINC);
	COsdFxCalcStartAddress(ucRow, ucCol+1, 1);
	CScalerWriteAmount(0x92, 1, 0x6c, _NON_AUTOINC);

	COsdFxCalcStartAddress(ucRow, ucCol+9, 1);
	CScalerWriteAmount(0x92, 1, _LEFT_ICON, _NON_AUTOINC);

	
       COsdFxLoadText(ucRow,ucCol+12 , stOsdUserData.Language, tOSD_GAMMA_STR);//zhangping 101110
       COsdFxLoadText(ucRow,ucCol +18, stOsdUserData.Language, tOSD_GAMMA_STR2[usValue]);//zhangping 101110
	COsdFxCalcStartAddress(ucRow, ucCol+24, 1);
	CScalerWriteAmount(0x92, 1, _RIGHT_ICON, _NON_AUTOINC);
}
void COsdDispSignalContent(BYTE ucRow, BYTE ucCol,  BYTE usValue)
{

	COsdFxCalcStartAddress(ucRow, ucCol, 1);
	CScalerWriteAmount(0x92, 1, _LEFT_ICON, _NON_AUTOINC);
      // COsdFxLoadText(ucRow,ucCol+3 , stOsdUserData.Language, tOSD_GAMMA_STR);//zhangping 101110
       COsdFxLoadText(ucRow,ucCol +6, stOsdUserData.Language, tOSD_SIGNAL_TYPE[usValue]);//zhangping 101110
	COsdFxCalcStartAddress(ucRow, ucCol+14, 1);
	CScalerWriteAmount(0x92, 1, _RIGHT_ICON, _NON_AUTOINC);
}

void COsdDisp_YES_NO(BYTE ucRow, BYTE ucCol,  BYTE usValue)
{

	COsdFxCalcStartAddress(ucRow, ucCol, 1);
	CScalerWriteAmount(0x92, 1, _LEFT_ICON, _NON_AUTOINC);
      // COsdFxLoadText(ucRow,ucCol+3 , stOsdUserData.Language, tOSD_GAMMA_STR);//zhangping 101110
      if(usValue)
		COsdFxLoadText(ucRow,ucCol +7, stOsdUserData.Language, tOSD_YES);//zhangping 101110
      else
		COsdFxLoadText(ucRow,ucCol +7, stOsdUserData.Language, tOSD_NO);//zhangping 101110
	COsdFxCalcStartAddress(ucRow, ucCol+14, 1);
	CScalerWriteAmount(0x92, 1, _RIGHT_ICON, _NON_AUTOINC);
}


void COsdDispClearIcon(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight)
{
    BYTE temp;

    for(temp = 0; temp < ucHeight; temp++)
    {
        COsdFxCalcStartAddress(ucRow + temp, ucCol, 1);
        CScalerWriteAmount(0x92, ucWidth, 0x69, _NON_AUTOINC);
    }
}

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

void COsdDispPenPoint(BYTE ucSrcX, BYTE ucSrcY, BYTE ucDesX, BYTE ucDesY, BYTE ucState)
{
    //COsdFxHLine(ROW(ucSrcX), COL(ucSrcY), LENGTH(2), 0x69, _WRITE_BYTE1);
   // COsdFxHLine(ROW(ucDesX), COL(ucDesY), LENGTH(1), 0x6a, _WRITE_BYTE1);
    //COsdFxHLine(ROW(ucDesX), COL(ucDesY + 1), LENGTH(1), 0x6b, _WRITE_BYTE1);
    ucOsdState = ucState;
}

void COsdDispArrowPoint(BYTE ucSrcX, BYTE ucSrcY, BYTE ucDesX, BYTE ucDesY, BYTE ucState)
{
    COsdFxHLine(ROW(ucSrcX), COL(ucSrcY), LENGTH(1), 0x00, _WRITE_BYTE1);
    COsdFxHLine(ROW(ucDesX), COL(ucDesY), LENGTH(1), 0x4a, _WRITE_BYTE1);
    COsdFxChange1bitColor(ROW(ucDesX), COL(ucDesY), WIDTH(1), HEIGHT(1), FGCOLOR(_CP_RED), BGCOLOR(_CP_BLACK));
    ucOsdState = ucState;
}

void COsdDispWindowPoint(BYTE ucRowNum, BYTE ucState)
{
    //width:120 height:20
    COsdFxDrawWindow(XSTART(12), YSTART(17 + ucRowNum * 36), XEND(132), YEND(17 + ucRowNum * 36 + 20), tOSD_WINDOW4_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_RED), tOSD_WINDOW4_STYLE);
    ucOsdState = ucState;
}

void COsdDispWindowHPoint(BYTE ucRowNum, BYTE ucStart, BYTE ucInterval, BYTE ucItemNum, BYTE ucThick, BYTE ucState)
{
    //width:120 height:20
    COsdFxDrawWindow(XSTART(ucStart + ucInterval*ucItemNum), YSTART(18 + ucRowNum * 36), XEND(ucStart + ucInterval*ucItemNum + ucThick), YEND(18 + ucRowNum * 36 + 18), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_RED), tOSD_WINDOW2_STYLE);
    ucOsdState = ucState;
}

void COsdDispDrawInitWindow(void)
{
    BYTE temp;

 //   COsdDispClearIcon(ROW(0), COL(0), 5, 20);
    COsdDispClearText(ROW(0), COL(0), 10, 13);
//    COsdFxChange2bitColor(ROW(5), COL(0), WIDTH(5), HEIGHT(20), COLOR00(_CP_BLACK), COLOR01(_CP_WHITE), COLOR10(_CP_RED), COLOR11(_CP_GREEN));

    for(temp = 0; temp < 8; temp++)
    {
#if((_AUDIO_SUPPORT == _ON) && (_DDCCI_SUPPORT == _ON))

        COsdFxLoadText(ROW(5 + temp*2), COL(7), stOsdUserData.Language, tTEXT_TABLE[temp]);

#else
/*
#if((_AUDIO_SUPPORT != _ON))
        if(temp == 4)
        {
            continue;
        }
#endif

#if((_DDCCI_SUPPORT != _ON))
        if(temp == 7)
        {
            continue;
        }
#endif
*/
        COsdFxLoadText(ROW(1 + temp*1), COL(3), stOsdUserData.Language, tOSD_DICOM_STR);//zhangping 101109

        COsdFxLoadText(ROW(1 + temp*1), COL(9), stOsdUserData.Language, tOSD_DICOM_STR2[temp]);//zhangping 101109
#endif
    }
	
	COsdFxLoadText(ROW(9), COL(3), stOsdUserData.Language, tOSD_DSA_STR);//zhangping 101109
	COsdFxLoadText(ROW(10), COL(3), stOsdUserData.Language, tOSD_DSI_STR);//zhangping 101109
	COsdFxLoadText(ROW(11), COL(3), stOsdUserData.Language, tOSD_CT_STR);//zhangping 101109
	COsdFxLoadText(ROW(11), COL(6), stOsdUserData.Language, tOSD_MRI_STR);//zhangping 10110530
	
    for(temp = 0; temp < 3; temp++)
    	{         
	 COsdFxLoadText(ROW(12 + temp*1), COL(3), stOsdUserData.Language, tOSD_GAMMA_STR);//zhangping 101109	 
	 COsdFxLoadText(ROW(12 + temp*1), COL(9), stOsdUserData.Language, tOSD_GAMMA_STR2[temp]);//zhangping 101109
	}



	COsdFxLoadText(ROW(15), COL(3), stOsdUserData.Language, tOSD_SIGNAL_STR);//zhangping 101109
	COsdFxLoadText(ROW(16), COL(3), stOsdUserData.Language, tOSD_AUTO_ADJUST_STR);//zhangping 101109
// COsdDispFullSlider(ROW(9), COL(1), 12, stSystemData.BackLight, 255, 0, _CP_WHITE, _CP_WHITE);//draw brightness slide bar	

 //          COsdFxLoadText(ROW(5), COL(25), stOsdUserData.Language, tTEXT_TABLE[temp]);//zhangping 101109
 //          COsdDispFullSlider(ROW(9), COL(22), 12, stSystemData.BackLight, 255, 0, _CP_WHITE, _CP_WHITE);//draw brightness slide bar
//       COsdDispFullSlider(ROW(11), COL(22), 12, stConBriData.Contrast, _CONTRAST_MAX - _CONTRAST_MIN, _CONTRAST_MIN, _CP_WHITE, _CP_WHITE);//draw contrast slide bar

 //       COsdDispDicomContent(ROW(5), COL(14),stConBriData.Dicom);// draw dicom curve
  //      COsdDispGammaContent(ROW(7), COL(13),stConBriData.Gamma);// draw dicom curve
  //      COsdDispSignalContent(ROW(13), COL(22),0);// draw SIGNAL TYPE
 //       COsdDisp_YES_NO(ROW(15), COL(22),1);// draw AUTO ADJUST YES/NO
 //       COsdDisp_YES_NO(ROW(17), COL(22),1);// draw FACTORY RESET YES/NO
/*        if(stConBriData.Dicom<8)
        	{
		        COsdFxChange1bitColor(ROW(7), COL(5), WIDTH(35), HEIGHT(5), FGCOLOR(_CP_SELECTBOTTOM), BGCOLOR(_CP_BLACK));
        	}


*/
		
/*
#if(_AUDIO_SUPPORT != _ON)
    COsdFxLoadText(ROW(5 + 4*2), COL(7), stOsdUserData.Language, tTEXT_TABLE[4]);
    COsdFxHLine(ROW(13), COL(5), LENGTH(15), (_CP_GRAY << 4 | _CP_BACKGROUND), _WRITE_BYTE2);
#endif
*/
}

void COsdDispLanguageBack(void)
{

    BYTE temp;

    COsdDispClearIcon(ROW(5), COL(0), 5, 20);
    COsdDispClearText(ROW(5), COL(5), 18, 15);

    for(temp = 0; temp < 4; temp++)
    {
        COsdFxLoadText(ROW(5 + temp*2), COL(7), stOsdUserData.Language, tOSD_TABLE[temp]);
    }

    COsdDispPenPoint(ROW(5), COL(3), ROW(11), COL(3), _MENU_OSD_LANGUAGE);
    COsdFxDrawWindow(XSTART(40), YSTART(300), XEND(250), YEND(400), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_BLACK), tOSD_WINDOW2_STYLE);
    COsdFxChange1bitColor(ROW(11), COL(5), WIDTH(17), HEIGHT(1), FGCOLOR(_CP_YELLOW), BGCOLOR(_CP_BLACK));

    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;

}

void COsdDispShowFactoryModeValue(void)
{
    BYTE temp;
    CEepromLoadAdcData();

    for(temp = 0; temp < 3; temp++)
    {
        COsdFxShowNumber(ROW(5), COL(17 + temp * 5), stAdcData.AdcOffset[temp], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    }

    for(temp = 0; temp < 3; temp++)
    {
        COsdFxShowNumber(ROW(7), COL(16 + temp * 5), stAdcData.AdcGain[temp], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    }

    for(temp = 0; temp < 5; temp++)
    {
        SET_COLOR_TEMP_TYPE(temp);
        CEepromLoadColorTempData();
        COsdFxShowNumber(ROW(9 + temp*2), COsdFxGetColWithinText(15, temp + 4, tOSD_FACTORY_ITEM_STR), stColorTempData.ColorTemp[_RED], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
        COsdFxShowNumber(ROW(9 + temp*2), COsdFxGetColWithinText(20, temp + 4, tOSD_FACTORY_ITEM_STR), stColorTempData.ColorTemp[_GREEN], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
        COsdFxShowNumber(ROW(9 + temp*2), COsdFxGetColWithinText(25, temp + 4, tOSD_FACTORY_ITEM_STR), stColorTempData.ColorTemp[_BLUE], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    }

    COsdFxShowNumber(ROW(19), COL(17), stConBriData.Brightness, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
}

void COsdDispAutoProcPrevWork(void)
{
    COsdFxDisableOsd();
    COsdFxApplyMapSetting(_OSD_MAP2);

    COsdFxCloseWindow(WINNO(0));
    COsdFxCloseWindow(WINNO(1));
    COsdFxCloseWindow(WINNO(3));
    COsdFxCloseWindow(WINNO(4));
    COsdFxCloseWindow(WINNO(5));
}

void COsdDispColorTempSelect(void)
{
    switch(stOsdUserData.ColorTemp)
    {
        case _CT_9300:
            SET_COLOR_TEMP_TYPE(_CT_9300);
            break;

        case _CT_6500:
            SET_COLOR_TEMP_TYPE(_CT_6500);
            break;

        case _CT_5800:
            SET_COLOR_TEMP_TYPE(_CT_5800);
            break;

        case _CT_SRGB:
            SET_COLOR_TEMP_TYPE(_CT_SRGB);
            break;

        case _CT_USER:
            SET_COLOR_TEMP_TYPE(_CT_USER);
            break;
    }
    CEepromLoadColorTempData();
    CAdjustContrast(stConBriData.Contrast);
}

BYTE COsdDispSetWindowPosDisp(BYTE ucSelect, BYTE code *pArray)
{
    BYTE cnt, temp, temp1;
    WORD length;

    length = 0;
    cnt = 0;
    temp = 0;
    temp1 = 0;

    while(_TRUE)
    {
        if(*pArray == _END_)
        {
            if(temp == ucSelect)
            {
                pArray = pArray - cnt;
                break;
            }
            else
            {
                pArray++;
                cnt = 0;
            }

            temp++;//equal language select
        }

        pArray++;
        cnt++;
    }

    while(*pArray != _END_)
    {
        cnt = 0;
        while(tOSD_CHARWIDTH_TABLE[cnt][0] != _END_)
        {
            if((*pArray == tOSD_CHARWIDTH_TABLE[cnt][0]) && (tOSD_CHARWIDTH_TABLE[cnt][1] != _END_))
            {
                length += (tOSD_CHARWIDTH_TABLE[cnt][1]&0x0f);
                break;
            }
            cnt++;
        }
        if(tOSD_CHARWIDTH_TABLE[cnt][0] == _END_)
        {
            length += 12;
        }

        pArray++;
    }

    length = length / 12;
    temp = (length) + 12;
    return temp;
}

//----------------------------------------------------------------------------------------------------
// OSD Event Functions
//----------------------------------------------------------------------------------------------------
void COsdDispOsdTimerEvent(void)
{
    COsdFxDisableOsd();
	GCMode=0;//sjp20110630 for clean GCMODE while OSD disappear
#if(_VIVID_COLOR_FUCTION == _ON)
//    CAdjustHLWindowBrightness(stOsdUserData.MZBright);
//    CAdjustHLWindowContrast(stOsdUserData.MZContrast);
#endif

    ucOsdState = _MENU_NONE;

#if(_SWITCH_INPUT_SOURCE_OSD == _ON)

    if(GET_SOURCE_OSD_STATUS())
    {
        CLR_SOURCE_OSD_STATUS();
    }

#endif

}



#if(_VIVID_COLOR_FUCTION == _ON)
//----------------------------------------------------------------------------------------------------
// OSD Event Functions
//----------------------------------------------------------------------------------------------------
void COsdDispVividColorHLWindow(void)
{

    if(GET_WINDOW_SIZE() == _VIVID_WINDOW_SIZE_DISABLE)
    {
        CAdjustEnableHLWindow(_DISABLE);
    }
    else if(GET_WINDOW_SIZE() == _VIVID_WINDOW_SIZE_FULL)
    {
        CAdjustHLWindowHV(0, stDisplayInfo.DHWidth - 2, 0, stDisplayInfo.DVHeight - 2);
        CAdjustNormalizeFactor(stDisplayInfo.DHWidth - 2, stDisplayInfo.DVHeight - 2);
        CAdjustEnableHLWindow(_ENABLE);
    }
    else if(GET_WINDOW_SIZE() == _VIVID_WINDOW_SIZE_DEMO)
    {
        CAdjustHLWindowHV(0, stDisplayInfo.DHWidth / 2, 0, stDisplayInfo.DVHeight - 2);
        CAdjustNormalizeFactor(stDisplayInfo.DHWidth / 2, stDisplayInfo.DVHeight - 2);
        CAdjustEnableHLWindow(_ENABLE);
    }
    else if(GET_WINDOW_SIZE() == _VIVID_WINDOW_SIZE_USER)
    {
        CAdjustHLWindowHV(stOsdUserData.VividWinHPos, stOsdUserData.VividWinHWidth, stOsdUserData.VividWinVPos, stOsdUserData.VividWinVHeight);
        CAdjustNormalizeFactor(stOsdUserData.VividWinHWidth, stOsdUserData.VividWinVHeight);
        CAdjustEnableHLWindow(_ENABLE);
    }

    CAdjustHLWindowHVBorder(WIDTH(2), 0x3f, 0x3f, 0x00);

}

//----------------------------------------------------------------------------------------------------
// OSD Event Functions
//----------------------------------------------------------------------------------------------------
void COsdDispVividColorDCCMode(void)
{
    if(GET_DCC_MODE() != _VIVID_DCC_DISABLE)
    {
        CAdjustFillDCCTable(GET_DCC_MODE() - 1);
        CAdjustEnableDCC(_ENABLE);

        // V013 System Patch Note (10) Modify 20100518 Start
        // Patch Reason : Make the color adjust effect different inside and outside of Hightlight Window.
        if((GET_WINDOW_SIZE() == _VIVID_WINDOW_SIZE_DEMO) || (GET_WINDOW_SIZE() == _VIVID_WINDOW_SIZE_USER))
        {
            CScalerRead(_HW_ACCESS_PORT_60, 1, pData, _NON_AUTOINC);
            CScalerSetByte(_HW_ACCESS_PORT_60, (pData[0] & 0xC0) + _HW_WINDOW_CTRL0_0C); // Get 61-0c
            CScalerRead(_HW_DATA_PORT_61, 1, pData + 1, _NON_AUTOINC);

            pData[1] = (pData[1] & (~(_BIT3 | _BIT2))) | _BIT2;
            CScalerSetByte(_HW_ACCESS_PORT_60, (pData[0] & 0xC0) + _HW_WINDOW_CTRL0_0C); // Get 61-0c
            CScalerSetByte(_HW_DATA_PORT_61, pData[1]);
        }
        // V013 System Patch Note (10) Modify 20100518 End

    }
    else
    {
        CAdjustEnableDCC(_DISABLE);
    }
}

//----------------------------------------------------------------------------------------------------
// OSD Event Functions
//----------------------------------------------------------------------------------------------------
void COsdDispVividColorICMMode(void)
{
    if((GET_ICM_MODE() != _VIVID_ICM_DISABLE) && (GET_ICM_MODE() != _VIVID_ICM_USER))
    {
        CAdjustFillICMTable(GET_ICM_MODE() - 1);
        CAdjustEnableICM(_ICM_CM0 | _ICM_CM1 | _ICM_CM2 | _ICM_CM3);

        // V013 System Patch Note (10) Modify 20100518 Start
        // Patch Reason : Make the color adjust effect different inside and outside of Hightlight Window.
        if((GET_WINDOW_SIZE() == _VIVID_WINDOW_SIZE_DEMO) || (GET_WINDOW_SIZE() == _VIVID_WINDOW_SIZE_USER))
        {
            CScalerRead(_HW_ACCESS_PORT_60, 1, pData, _NON_AUTOINC);
            CScalerSetByte(_HW_ACCESS_PORT_60, (pData[0] & 0xC0) + _HW_WINDOW_CTRL0_0C); // Get 61-0c
            CScalerRead(_HW_DATA_PORT_61, 1, pData + 1, _NON_AUTOINC);

            pData[1] = (pData[1] & (~(_BIT3 | _BIT2))) | _BIT2;
            CScalerSetByte(_HW_ACCESS_PORT_60, (pData[0] & 0xC0) + _HW_WINDOW_CTRL0_0C); // Get 61-0c
            CScalerSetByte(_HW_DATA_PORT_61, pData[1]);
        }
        // V013 System Patch Note (10) Modify 20100518 End
    }
    else
    {
        CAdjustEnableICM(_DISABLE);
    }
}


//----------------------------------------------------------------------------------------------------
// OSD Event Functions
//----------------------------------------------------------------------------------------------------
void COsdDispVividColor(void)
{
    if(GET_DCC_MODE() != _VIVID_DCC_DISABLE)
    {
        CAdjustHLWindowContrast(_ENABLE, 128);
        CAdjustHLWindowBrightness(_ENABLE, 128);
        COsdDispVividColorDCCMode();
    }
    else
    {
        CAdjustHLWindowContrast(_ENABLE, stOsdUserData.VividContrast);
        CAdjustHLWindowBrightness(_ENABLE, stOsdUserData.VividBright);
    }

    COsdDispVividColorICMMode();
}

#endif // End of #if(_VIVID_COLOR_FUCTION == _ON)

#if (_DDCCI_SUPPORT == _ON)

BYTE COsdDispRealToPercent(WORD RealValue, WORD usMax, WORD usMin)
{
    WORD usTemp = 0;
    RealValue = MINOF(RealValue, usMax);
    RealValue = MAXOF(RealValue, usMin);

    if(usMax <= usMin)
    {
        usTemp = 0;
    }
    else
    {
        usTemp = (((DWORD)(RealValue - usMin) * 10000) / (usMax - usMin));
    }

    if((usTemp % 100) > 49)
    {
        usTemp = usTemp + 100;
    }

    usTemp = usTemp / 100;

    return((BYTE)usTemp);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD COsdDispPercentToRealValue(BYTE PercentValue, WORD usMax, WORD usMin)
{
    WORD usTemp = 0;
    PercentValue = MINOF(100, PercentValue);

    if(((DWORD)PercentValue * (usMax - usMin)) % 100 != 0)
    {
        usTemp = ((DWORD)PercentValue * (usMax - usMin)) / 100 + 1;
    }
    else
    {
        usTemp = ((DWORD)PercentValue * (usMax - usMin)) / 100;
    }

    return(usTemp + usMin);

}
#endif


//--------------------------------------------------
// Description  : Draw Timing and Input Source Information.
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdDispTimingAndInputSource(void)
{
    // V012 Modify 20100320 Start
    // V012 Patch Note (12) : Show video timing info in OSD.
    BYTE ucFlag = 0;
    // V012 Modify 20100320 End

    // V016 VGA Patch Note (3) Modify 20100831 Start
    // Patch Reason : Modify for 832x624@74.53Hz always shown as 832x624@75Hz.
    BYTE ucModeIndex = 0;
    // V016 VGA Patch Note (3) Modify 20100831 End

    // V014 VGA Patch Note (4) Modify 20100526 Start
    // Patch Reason : Modify for OSD Error while pressing menu key continuously in light process.
    COsdFxDisableOsd();
    ucOsdState = _MENU_NONE;
    // V014 VGA Patch Note (4) Modify 20100526 End

    CScalerLoadHardwareVLCFont(tFONT_GLOBAL, 0x00);
    CScalerLoadHardwareVLCFont(tFONT_NO_SIGNAL, 0x60);

    COsdDispAutoProcPrevWork();

    /*
    COsdFxDrawWindow(XSTART(0), YSTART(0), XEND(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_NOSIGNAL_STR)*12), YEND(140), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_DARKBLUE), tOSD_WINDOW2_STYLE);
    COsdFxDrawWindow(XSTART(10), YSTART(20), XEND(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_NOSIGNAL_STR))*12 - 10, YEND(120), tOSD_WINDOW6_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_LIGHTBLUE), tOSD_WINDOW6_STYLE);
    COsdFxSetPosition(WIDTH(COsdDispSetWindowPosDisp(stOsdUserData.Language, tOSD_NOSIGNAL_STR)*12), WIDTH(140), 170, 180, 0x01);
    */
    COsdFxDrawWindow(XSTART(0), YSTART(0), XEND(250), YEND(140), tOSD_WINDOW2_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_DARKBLUE), tOSD_WINDOW2_STYLE);
    COsdFxDrawWindow(XSTART(10), YSTART(20), XEND(240), YEND(120), tOSD_WINDOW6_STYLE);
    COsdFxChangeWindowColor(COLOR00(_CP_LIGHTBLUE), tOSD_WINDOW6_STYLE);

    // V016 System Patch Note (1) Modify 20100729 Start
    // Patch Reason : Modify OSD Set position and Draw Window Function
    /*
    COsdFxSetPosition(WIDTH(250), WIDTH(140), 170, 180, 0x01);
    */
    COsdFxSetPosition(WIDTH(250), WIDTH(140), 180, 20, 0x01);
    // V016 System Patch Note (1) Modify 20100729 End

    // show current input source type
    COsdFxLoadText(ROW(2), COL(5), stOsdUserData.Language, tOSD_INPUT_SOURCE_STR);
    COsdFxLoadText(ROW(2), COL(11), _ENGLISH, tOSD_SOURCE_STR[COsdDispJudgeSourceType()]);

    COsdFxChange1bitColor(ROW(2), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));

    // V012 Modify 20100320 Start
    // V012 Patch Note (12) : Show video timing info in OSD.
    /*
    COsdFxShowNumber(ROW(4), COL(5), stModeInfo.IHWidth, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
    COsdFxHLine(ROW(4), COL(6), LENGTH(1), 0x0e, _WRITE_BYTE1);
    COsdFxShowNumber(ROW(4), COL(7), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

    COsdFxShowNumber(ROW(4), COL(12), (stModeInfo.IVFreq + 5) / 10, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2));

    COsdFxHLine(ROW(4), COL(14), LENGTH(1), _H_, _WRITE_BYTE1);
    COsdFxHLine(ROW(4), COL(15), LENGTH(1), _z_, _WRITE_BYTE1);
    */
    #if(_YPBPR_SUPPORT == _ON)
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        switch(stModeInfo.ModeCurr)
        {
            // V013 VGA Patch Note (5) 20100409 Modify Start
            // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
            /*
            case _VIDEO_720x576i_50HZ:
            case _VIDEO_720x480i_60HZ:
            */
            case _VIDEO_1440x576i_50HZ:
            case _VIDEO_1440x480i_60HZ:
            // V013 VGA Patch Note (5) 20100409 Modify End

            case _VIDEO_1920x1080i_50HZ:
            case _VIDEO_1920x1080i_60HZ:

            // V013 VGA Patch Note (5) 20100409 Modify Start
            // Patch Reason : Modify YPbPr search mode flow to cover confuse mode problem.
            case _VIDEO_1920x1080i_50HZ_2:
            // V013 VGA Patch Note (5) 20100409 Modify End

                // V015 VGA Patch Note (12) Modify 20100625 Start
                // Patch Reason : Modify OSD Reslotion show type for vedio timing.
                /*
                COsdFxShowNumber(ROW(4), COL(4), stModeInfo.IVHeight * 2, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                COsdFxHLine(ROW(4), COL(8), LENGTH(1), _i_, _WRITE_BYTE1);
                */
                ucFlag = COsdDispShowResolution(ROW(4), COL(4), _TRUE, _INTERLACE_TIMING);
                // V015 VGA Patch Note (12) Modify 20100625 End
            break;

            case _VIDEO_720x576p_50HZ:
            case _VIDEO_720x480p_60HZ:
            case _VIDEO_1280x720p_50HZ:
            case _VIDEO_1280x720p_60HZ:
            case _VIDEO_1920x1080p_50HZ:
            case _VIDEO_1920x1080p_60HZ:
            default:

                // V015 VGA Patch Note (12) Modify 20100625 Start
                // Patch Reason : Modify OSD Reslotion show type for vedio timing.
                /*
                COsdFxShowNumber(ROW(4), COL(4), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                COsdFxHLine(ROW(4), COL(8), LENGTH(1), _p_, _WRITE_BYTE1);
                */
                ucFlag = COsdDispShowResolution(ROW(4), COL(4), _TRUE, _PROGRESS_TIMING);
                // V015 VGA Patch Note (12) Modify 20100625 End

            break;

        }
        // V015 VGA Patch Note (12) Modify 20100625 Start
        // Patch Reason : Modify OSD Reslotion show type for vedio timing.
        /*
        ucFlag = 0;
        */
        // V015 VGA Patch Note (12) Modify 20100625 End
    }
    else
    #endif
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
        {
            if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
            {
                pData[0] = stModeInfo.ModeCurr;
            }
            else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
            {
                CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);
                pData[0] = pData[(stModeInfo.ModeCurr % 4) * 4];
            }

            // V016 VGA Patch Note (3) Modify 20100831 Start
            // Patch Reason : Modify for 832x624@74.53Hz always shown as 832x624@75Hz.
            ucModeIndex = pData[0];
            // V016 VGA Patch Note (3) Modify 20100831 End

            switch(pData[0])
            {
                // V013 VGA Patch Note (24) Modify 20100514 Start
                // Patch Reason : Mode search updates.
                /*
                case _MODE_720x480i_60Hz:
                case _MODE_720x576i_50Hz:
                */
                // V013 VGA Patch Note (24) Modify 20100514 End

                case _MODE_1920x1080i_50Hz:
                case _MODE_1920x1080i_60HZ:
                case _MODE_1440x480i_60HZ:
                case _MODE_1440x576i_50Hz:
                case _MODE_1920x1080i_50HZ_2:

                    // V015 VGA Patch Note (12) Modify 20100625 Start
                    // Patch Reason : Modify OSD Reslotion show type for vedio timing.
                    /*
                    COsdFxShowNumber(ROW(4), COL(4), stModeInfo.IVHeight * 2, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                    COsdFxHLine(ROW(4), COL(8), LENGTH(1), _i_, _WRITE_BYTE1);
                    ucFlag = 0;
                    */
                    ucFlag = COsdDispShowResolution(ROW(4), COL(4), _TRUE, _INTERLACE_TIMING);
                    // V015 VGA Patch Note (12) Modify 20100625 End

                    break;

                // V015 VGA Patch Note (12) Modify 20100625 Start
                // Patch Reason : Modify OSD Reslotion show type for vedio timing.
                case _MODE_720x480_60HZ:
                case _MODE_720x480_60HZ_GTF:
                case _MODE_720x576_60HZ:
                case _MODE_1920x1080_60HZ_XBOX:
                case _MODE_1920x1080_60HZ_RB:
                case _MODE_1920x1080_60HZ:
                case _MODE_1920x1080_50HZ_2:
                case _MODE_1280x720_60HZ_2:
                // V015 VGA Patch Note (12) Modify 20100625 End

                case _MODE_720x480p_60HZ:
                case _MODE_720x576p_50Hz:
                case _MODE_1280x720p_50HZ:
                case _MODE_1280x720p_60HZ:
                case _MODE_1920x1080p_50Hz:
                case _MODE_1920x1080p_60HZ:

                    // V015 VGA Patch Note (12) Modify 20100625 Start
                    // Patch Reason : Modify OSD Reslotion show type for vedio timing.
                    /*
                    COsdFxShowNumber(ROW(4), COL(4), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                    COsdFxHLine(ROW(4), COL(8), LENGTH(1), _p_, _WRITE_BYTE1);
                    ucFlag = 0;
                    */
                    ucFlag = COsdDispShowResolution(ROW(4), COL(4), _TRUE, _PROGRESS_TIMING);
                    // V015 VGA Patch Note (12) Modify 20100625 End

                    break;

                // V016 VGA Patch Note (3) Modify 20100730 Start
                // Patch Reason : Modify 640x350_70 Timing to show blank on top and buttom.
                case _MODE_640x350_70HZ:
                    COsdFxShowNumber(ROW(4), COL(5), 640, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                    COsdFxHLine(ROW(4), COL(6), LENGTH(1), 0x0e, _WRITE_BYTE1);
                    COsdFxShowNumber(ROW(4), COL(7), 350, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
                    ucFlag = 1;
                    break;
                // V016 VGA Patch Note (3) Modify 20100730 End

                default:

                    // V015 VGA Patch Note (12) Modify 20100625 Start
                    // Patch Reason : Modify OSD Reslotion show type for vedio timing.
                    /*
                    COsdFxShowNumber(ROW(4), COL(5), stModeInfo.IHWidth, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                    COsdFxHLine(ROW(4), COL(6), LENGTH(1), 0x0e, _WRITE_BYTE1);
                    COsdFxShowNumber(ROW(4), COL(7), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
                    ucFlag = 1;
                    */
                    ucFlag = COsdDispShowResolution(ROW(4), COL(4), _FALSE, _PROGRESS_TIMING);
                    // V015 VGA Patch Note (12) Modify 20100625 End

                    break;
            }
        }
        else
        {
            // V015 VGA Patch Note (12) Modify 20100625 Start
            // Patch Reason : Modify OSD Reslotion show type for vedio timing.
            /*
            COsdFxShowNumber(ROW(4), COL(5), stModeInfo.IHWidth, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
            COsdFxHLine(ROW(4), COL(6), LENGTH(1), 0x0e, _WRITE_BYTE1);
            COsdFxShowNumber(ROW(4), COL(7), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            ucFlag = 1;
            */
            ucFlag = COsdDispShowResolution(ROW(4), COL(4), _FALSE, _PROGRESS_TIMING);
            // V015 VGA Patch Note (12) Modify 20100625 End
        }
    }
    if(ucFlag == 0)
    {
        COsdFxShowNumber(ROW(4), COL(10), (stModeInfo.IVFreq + 5) / 10, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2));
        COsdFxHLine(ROW(4), COL(12), LENGTH(1), _H_, _WRITE_BYTE1);
        COsdFxHLine(ROW(4), COL(13), LENGTH(1), _z_, _WRITE_BYTE1);
    }
    else
    {
        // V016 VGA Patch Note (3) Modify 20100831 Start
        // Patch Reason : Modify for 832x624@74.53Hz always shown as 832x624@75Hz.
        /*
        COsdFxShowNumber(ROW(4), COL(12), (stModeInfo.IVFreq + 5) / 10, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2));
        */
        if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) && (ucModeIndex == _MODE_832x624_75HZ))
        {
            COsdFxShowNumber(ROW(4), COL(12), 75, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2));
        }
        else
        {
            COsdFxShowNumber(ROW(4), COL(12), (stModeInfo.IVFreq + 5) / 10, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2));
        }
        // V016 VGA Patch Note (3) Modify 20100831 End

        COsdFxHLine(ROW(4), COL(14), LENGTH(1), _H_, _WRITE_BYTE1);
        COsdFxHLine(ROW(4), COL(15), LENGTH(1), _z_, _WRITE_BYTE1);
    }
    // V012 Modify 20100320 End

    COsdFxChange1bitColor(ROW(4), COL(5), WIDTH(20), HEIGHT(1), FGCOLOR(_CP_WHITE), BGCOLOR(_CP_BLACK));

    COsdFxEnableOsd();
}

//--------------------------------------------------
// Description  : Check Source Type.
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE COsdDispJudgeSourceType(void)
{
    BYTE temp = 0;

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    /*
    if(stSystemData.SearchIndex == 0)   //HDMI
    {
        temp = 2;
    }
    else if(stSystemData.SearchIndex == 1)   //VGA
    {
        temp = 0;
    }
    else if(stSystemData.SearchIndex == 2)   //DP
    {
        temp = 3;
    }
    else
    {
        temp = 0;
    }
    */
    if((GET_INPUTPORT_TYPE(stSystemData.SearchIndex) == _A0_VGA_PORT) || (GET_INPUTPORT_TYPE(stSystemData.SearchIndex) == _A1_VGA_PORT))
    {
        temp = 0;
    }
#if(_TMDS_SUPPORT == _ON)
    else if((GET_INPUTPORT_TYPE(stSystemData.SearchIndex) == _D0_DVI_PORT) || (GET_INPUTPORT_TYPE(stSystemData.SearchIndex) == _D1_DVI_PORT)
         || (GET_INPUTPORT_TYPE(stSystemData.SearchIndex) == _D0_DVI_I_PORT) || (GET_INPUTPORT_TYPE(stSystemData.SearchIndex) == _D1_DVI_I_PORT))
    {
        temp = 1;
    }
#if(_HDMI_SUPPORT == _ON)
    else if((GET_INPUTPORT_TYPE(stSystemData.SearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(stSystemData.SearchIndex) == _D1_HDMI_PORT))
    {
        temp = 2;
    }
#endif
#if(_DP_SUPPORT == _ON)
    else if((GET_INPUTPORT_TYPE(stSystemData.SearchIndex) == _D0_DP_PORT) || (GET_INPUTPORT_TYPE(stSystemData.SearchIndex) == _D1_DP_PORT))
    {
        temp = 3;
    }
#endif
#endif
    else
    {
        temp = 0;
    }

#else

#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
    if(GET_SOURCE_OSD_STATUS())
    {
        if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A0_VGA_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _A1_VGA_PORT))
        {
            temp = 0;
        }
        else if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT))
        {
            temp = 1;
        }
        else if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT))
        {
            temp = 2;
        }
        else if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DP_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DP_PORT))
        {
            temp = 3;
        }
        else
        {
            temp = 0;
        }
    }
#endif

#if(_YPBPR_SUPPORT == _ON)
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
#else
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
#endif
    {
        temp = 0;
    }

#if(_TMDS_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_DVI)
    {
        temp = 1;
    }

#if(_HDMI_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_HDMI)
    {
        temp = 2;
    }
#endif // End of #if(_HDMI_SUPPORT == _ON)

#if(_DP_SUPPORT == _ON)
    else if(GET_INPUTSOURCE_TYPE() == _SOURCE_DP)
    {
        temp = 3;
    }
#endif

#endif // End of #if(_TMDS_SUPPORT == _ON)

#endif

    return temp;

}

// V015 VGA Patch Note (12) Modify 20100625 Start
// Patch Reason : Modify OSD Reslotion show type for vedio timing.
//--------------------------------------------------
// Description  : Show Resolution function
// Input Value  : ucRow-Input Row, ucCol-Input Col, bVedioTiming-Vedio Timing Flag, bInterlace-Interlace Mode Flag
// Output Value : Flag for Information Style
//--------------------------------------------------
bit COsdDispShowResolution(BYTE ucRow, BYTE ucCol, bit bVedioTiming, bit bInterlace)
{
    bit bFlag = 0;

    // V016 VGA Patch Note (2) Modify 20100730 Start
    // Patch Reason : Modify OSD Reslotion show type for vedio timing, Update for V015 Patch Note (12).
    /*
    if((bVedioTiming == _TRUE))
    {
        if(GET_COLOR_FORMAT_STATUS() == _YUV_COLOR_FORMAT)
        {
            if(bInterlace == _INTERLACE_TIMING)
            {
                COsdFxShowNumber(ROW(ucRow), COL(ucCol), stModeInfo.IVHeight * 2, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                COsdFxHLine(ROW(ucRow), COL(ucCol + 4), LENGTH(1), _i_, _WRITE_BYTE1);
            }
            else
            {
                COsdFxShowNumber(ROW(ucRow), COL(ucCol), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                COsdFxHLine(ROW(ucRow), COL(ucCol + 4), LENGTH(1), _p_, _WRITE_BYTE1);
            }

            bFlag = 0;

            return bFlag;
        }
    }

    COsdFxShowNumber(ROW(ucRow), COL(ucCol + 1), stModeInfo.IHWidth, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
    COsdFxHLine(ROW(ucRow), COL(ucCol + 2), LENGTH(1), 0x0e, _WRITE_BYTE1);

    if(bInterlace == _INTERLACE_TIMING)
    {
        COsdFxShowNumber(ROW(ucRow), COL(ucCol + 3), stModeInfo.IVHeight * 2, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    }
    else
    {
        COsdFxShowNumber(ROW(ucRow), COL(ucCol + 3), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    }

    bFlag = 1;
    */
    if(bInterlace == _INTERLACE_TIMING)
    {
        COsdFxShowNumber(ROW(ucRow), COL(ucCol), stModeInfo.IVHeight * 2, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
        COsdFxHLine(ROW(ucRow), COL(ucCol + 4), LENGTH(1), _i_, _WRITE_BYTE1);
        bFlag = 0;
    }
    else
    {
        if((bVedioTiming == _TRUE) && ((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4)) && (GET_COLOR_FORMAT_STATUS() == _YUV_COLOR_FORMAT))
        {
            COsdFxShowNumber(ROW(ucRow), COL(ucCol), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
            COsdFxHLine(ROW(ucRow), COL(ucCol + 4), LENGTH(1), _p_, _WRITE_BYTE1);
            bFlag = 0;
        }
        else
        {
            COsdFxShowNumber(ROW(ucRow), COL(ucCol + 1), stModeInfo.IHWidth, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
            COsdFxHLine(ROW(ucRow), COL(ucCol + 2), LENGTH(1), 0x0e, _WRITE_BYTE1);
            COsdFxShowNumber(ROW(ucRow), COL(ucCol + 3), stModeInfo.IVHeight, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            bFlag = 1;
        }
    }
    // V016 VGA Patch Note (2) Modify 20100730 End

    return bFlag;
}

//--------------------------------------------------
// Description  : Load font, draw window when source from power saving
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void COSDDispTimingInfoStyle(void)
{
    // V016 VGA Patch Note (3) Modify 20100831 Start
    // Patch Reason : Modify for 832x624@74.53Hz always shown as 832x624@75Hz.
    BYTE ucModeIndex = 0;
    // V016 VGA Patch Note (3) Modify 20100831 End

    COsdDispClearText(ROW(23), COL(5), WIDTH(20), HEIGHT(1));

#if(_YPBPR_SUPPORT == _ON)
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
    {
        switch(stModeInfo.ModeCurr)
        {
            case _VIDEO_1440x576i_50HZ:
            case _VIDEO_1440x480i_60HZ:
            case _VIDEO_1920x1080i_50HZ:
            case _VIDEO_1920x1080i_60HZ:
            case _VIDEO_1920x1080i_50HZ_2:
                COsdDispShowResolution(ROW(22), COL(15), _TRUE, _INTERLACE_TIMING);
                break;

            case _VIDEO_720x576p_50HZ:
            case _VIDEO_720x480p_60HZ:
            case _VIDEO_1280x720p_50HZ:
            case _VIDEO_1280x720p_60HZ:
            case _VIDEO_1920x1080p_50HZ:
            case _VIDEO_1920x1080p_60HZ:
            default:
                COsdDispShowResolution(ROW(22), COL(15), _TRUE, _PROGRESS_TIMING);
                break;
        }
    }
    else
#endif
    {
        if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
        {
            if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
            {
                pData[0] = stModeInfo.ModeCurr;
            }
            else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
            {
                CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);
                pData[0] = pData[(stModeInfo.ModeCurr % 4) * 4];
            }

            // V016 VGA Patch Note (3) Modify 20100831 Start
            // Patch Reason : Modify for 832x624@74.53Hz always shown as 832x624@75Hz.
            ucModeIndex = pData[0];
            // V016 VGA Patch Note (3) Modify 20100831 End

            switch(pData[0])
            {
                case _MODE_1920x1080i_50Hz:
                case _MODE_1920x1080i_60HZ:
                case _MODE_1440x480i_60HZ:
                case _MODE_1440x576i_50Hz:
                case _MODE_1920x1080i_50HZ_2:
                    COsdDispShowResolution(ROW(22), COL(15), _TRUE, _INTERLACE_TIMING);
                    break;

                case _MODE_720x480_60HZ:
                case _MODE_720x480_60HZ_GTF:
                case _MODE_720x576_60HZ:
                case _MODE_1920x1080_60HZ_XBOX:
                case _MODE_1920x1080_60HZ_RB:
                case _MODE_1920x1080_60HZ:
                case _MODE_1920x1080_50HZ_2:
                case _MODE_1280x720_60HZ_2:
                case _MODE_720x480p_60HZ:
                case _MODE_720x576p_50Hz:
                case _MODE_1280x720p_50HZ:
                case _MODE_1280x720p_60HZ:
                case _MODE_1920x1080p_50Hz:
                case _MODE_1920x1080p_60HZ:
                    COsdDispShowResolution(ROW(22), COL(15), _TRUE, _PROGRESS_TIMING);
                    break;

                // V016 VGA Patch Note (3) Modify 20100730 Start
                // Patch Reason : Modify 640x350_70 Timing to show blank on top and buttom.
                case _MODE_640x350_70HZ:
                    COsdFxShowNumber(ROW(22), COL(16), 640, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
                    COsdFxHLine(ROW(22), COL(16), LENGTH(1), 0x0e, _WRITE_BYTE1);
                    COsdFxShowNumber(ROW(22), COL(17), 350, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
                    break;
                // V016 VGA Patch Note (3) Modify 20100730 End

                default:
                    COsdDispShowResolution(ROW(22), COL(15), _FALSE, _PROGRESS_TIMING);
                    break;
            }

        }
        else
        {
            COsdDispShowResolution(ROW(23), COL(9), _FALSE, _PROGRESS_TIMING);
        }
    }

    // V016 VGA Patch Note (3) Modify 20100831 Start
    // Patch Reason : Modify for 832x624@74.53Hz always shown as 832x624@75Hz.
    /*
    COsdFxShowNumber(ROW(23), COL(17), (stModeInfo.IVFreq + 5) / 10, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2));
    */
    if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) && (ucModeIndex == _MODE_832x624_75HZ))
    {
        COsdFxShowNumber(ROW(22), COL(23), 75, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2));
    }
    else
    {
        COsdFxShowNumber(ROW(22), COL(23), (stModeInfo.IVFreq + 5) / 10, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2));
    }
    // V016 VGA Patch Note (3) Modify 20100831 End

    COsdFxHLine(ROW(22), COL(25), LENGTH(1), _H_, _WRITE_BYTE1);
    COsdFxHLine(ROW(22), COL(26), LENGTH(1), _z_, _WRITE_BYTE1);

    COsdFxChange1bitColor(ROW(22), COL(5), WIDTH(30), HEIGHT(1), FGCOLOR(_CP_PINK), BGCOLOR(_CP_BLACK));
}
// V015 VGA Patch Note (12) Modify 20100625 End

#endif  // End of #if(_OSD_TYPE == _REALTEK_OSD)

