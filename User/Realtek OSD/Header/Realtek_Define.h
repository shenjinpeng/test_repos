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
// ID Code      : Osd.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definations of Load Font Fuction
//--------------------------------------------------
#define _SOFT_WARE                              0
#define _HARD_WARE                              1

#define _LOAD_FONT_TYPE                         _HARD_WARE

#define _OSD_ROTATE_FUCTION                     _OFF

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
/*
#define _SPECIAL_FUCTION_ITEN                   (_VIVID_COLOR_FUCTION + _NON_LINEAR_SCALING_FUCTION + _ASPECT_RATIO_SUPPORT + _SRGB_COLOR_ENHANCE)
*/
#define _SPECIAL_FUCTION_ITEN                   (_VIVID_COLOR_FUCTION + _NON_LINEAR_SCALING_FUCTION + _ASPECT_RATIO_SUPPORT + _SRGB_COLOR_ENHANCE + _COLOR_FORMAT_CONVERT)
// V012 Modify 20100304 End



