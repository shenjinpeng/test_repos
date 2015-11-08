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
// ID Code      : Extend.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if((_EXTEND_TABLE_SUPPORT == _ON) && (_OSD_TYPE == _REALTEK_OSD))

//----------------------------------------------------------------------------------------------------
// Filter Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
#define _SU_COEF_EXTEND                                 128

#if(_VIVID_COLOR_FUCTION == _ON)
//--------------------------------------------------
// Vivid Color Table
//--------------------------------------------------
#define _DCC_CONTROL_EXTEND                             9
#define _DCC_USERCURVE_EXTEND                           23
#define _ICM_TABLE_EXTEND                               51

#endif // End of #if(_VIVID_COLOR_FUCTION == _ON)

//--------------------------------------------------
// OSD Font Table
//--------------------------------------------------

#define _FONT_GLOBAL_EXTEND                             1414
#define _FONT_GLOBAL2ND_EXTEND                          168
#define _FONT_GLOBAL_ICON_EXTEND                        504
#define _FONT_NO_SIGNAL_EXTEND                          678
#define _FONT_AUTOCONFIG_EXTEND                         269
#define _FONT_OUT_OF_RANGE_EXTEND                       487
#define _FONT_AUTOCOLOR_EXTEND                          283
#define _FONT_JAP_EXTEND                                1130
#define _FONT_CHI_EXTEND                                1278
#define _FONT_COLORTEMP_EXTEND                          254





#define _EXTENDTABLE_START                              0x0200

//----------------------------------------------------------------------------------------------------
// Filter Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
#define _SU_COEF_0_EXTEND_ADDRESS                       (_EXTENDTABLE_START)
#define _SU_COEF_1_EXTEND_ADDRESS                       (_SU_COEF_0_EXTEND_ADDRESS          + _SU_COEF_EXTEND)
#define _SU_COEF_2_EXTEND_ADDRESS                       (_SU_COEF_1_EXTEND_ADDRESS          + _SU_COEF_EXTEND)
#define _SU_COEF_3_EXTEND_ADDRESS                       (_SU_COEF_2_EXTEND_ADDRESS          + _SU_COEF_EXTEND)
#define _SU_COEF_4_EXTEND_ADDRESS                       (_SU_COEF_3_EXTEND_ADDRESS          + _SU_COEF_EXTEND)

#define _SU_COEF_EXTEND_END_ADDRESS                     (_SU_COEF_0_EXTEND_ADDRESS + (_SU_COEF_EXTEND * 5))

#if(_VIVID_COLOR_FUCTION == _ON)
//--------------------------------------------------
// Vivid Color Table
//--------------------------------------------------
#define _DCC_CONTROL_MOVIE_EXTEND_ADDRESS               (_SU_COEF_EXTEND_END_ADDRESS)
#define _DCC_CONTROL_PHOTO_EXTEND_ADDRESS               (_DCC_CONTROL_MOVIE_EXTEND_ADDRESS      + _DCC_CONTROL_EXTEND)
#define _DCC_CONTROL_GAME_EXTEND_ADDRESS                (_DCC_CONTROL_PHOTO_EXTEND_ADDRESS      + _DCC_CONTROL_EXTEND)
#define _DCC_USERCURVE_MOVIE_EXTEND_ADDRESS             (_DCC_CONTROL_GAME_EXTEND_ADDRESS       + _DCC_CONTROL_EXTEND)
#define _DCC_USERCURVE_PHOTO_EXTEND_ADDRESS             (_DCC_USERCURVE_MOVIE_EXTEND_ADDRESS    + _DCC_USERCURVE_EXTEND)
#define _DCC_USERCURVE_GAME_EXTEND_ADDRESS              (_DCC_USERCURVE_PHOTO_EXTEND_ADDRESS    + _DCC_USERCURVE_EXTEND)
#define _ICM_MOVIE0_EXTEND_ADDRESS                      (_DCC_USERCURVE_GAME_EXTEND_ADDRESS     + _DCC_USERCURVE_EXTEND)
#define _ICM_MOVIE1_EXTEND_ADDRESS                      (_ICM_MOVIE0_EXTEND_ADDRESS             + _ICM_TABLE_EXTEND)
#define _ICM_MOVIE2_EXTEND_ADDRESS                      (_ICM_MOVIE1_EXTEND_ADDRESS             + _ICM_TABLE_EXTEND)
#define _ICM_MOVIE3_EXTEND_ADDRESS                      (_ICM_MOVIE2_EXTEND_ADDRESS             + _ICM_TABLE_EXTEND)
#define _ICM_PHOTO0_EXTEND_ADDRESS                      (_ICM_MOVIE3_EXTEND_ADDRESS             + _ICM_TABLE_EXTEND)
#define _ICM_PHOTO1_EXTEND_ADDRESS                      (_ICM_PHOTO0_EXTEND_ADDRESS             + _ICM_TABLE_EXTEND)
#define _ICM_PHOTO2_EXTEND_ADDRESS                      (_ICM_PHOTO1_EXTEND_ADDRESS             + _ICM_TABLE_EXTEND)
#define _ICM_PHOTO3_EXTEND_ADDRESS                      (_ICM_PHOTO2_EXTEND_ADDRESS             + _ICM_TABLE_EXTEND)
#define _ICM_GAME0_EXTEND_ADDRESS                       (_ICM_PHOTO3_EXTEND_ADDRESS             + _ICM_TABLE_EXTEND)
#define _ICM_GAME1_EXTEND_ADDRESS                       (_ICM_GAME0_EXTEND_ADDRESS              + _ICM_TABLE_EXTEND)
#define _ICM_GAME2_EXTEND_ADDRESS                       (_ICM_GAME1_EXTEND_ADDRESS              + _ICM_TABLE_EXTEND)
#define _ICM_GAME3_EXTEND_ADDRESS                       (_ICM_GAME2_EXTEND_ADDRESS              + _ICM_TABLE_EXTEND)

#define _VIVID_COLOR_EXTEND_END_ADDRESS                 (_DCC_CONTROL_MOVIE_EXTEND_ADDRESS + (_DCC_CONTROL_EXTEND * 3) + (_DCC_USERCURVE_EXTEND * 3) + (_ICM_TABLE_EXTEND * 12))

#else
#define _VIVID_COLOR_EXTEND_END_ADDRESS                 (_SU_COEF_EXTEND_END_ADDRESS)

#endif // End of #if(_VIVID_COLOR_FUCTION == _ON)

//--------------------------------------------------
// OSD Font Table
//--------------------------------------------------
#define _FONT_GLOBAL_EXTEND_ADDRESS                     (_VIVID_COLOR_EXTEND_END_ADDRESS)
#define _FONT_GLOBAL2ND_EXTEND_ADDRESS                  (_FONT_GLOBAL_EXTEND_ADDRESS + _FONT_GLOBAL_EXTEND)
#define _FONT_GLOBAL_ICON_EXTEND_ADDRESS                (_FONT_GLOBAL2ND_EXTEND_ADDRESS + _FONT_GLOBAL2ND_EXTEND)
#define _FONT_NO_SIGNAL_EXTEND_ADDRESS                  (_FONT_GLOBAL_ICON_EXTEND_ADDRESS + _FONT_GLOBAL_ICON_EXTEND)
#define _FONT_AUTOCONFIG_EXTEND_ADDRESS                 (_FONT_NO_SIGNAL_EXTEND_ADDRESS + _FONT_NO_SIGNAL_EXTEND)
#define _FONT_OUT_OF_RANGE_EXTEND_ADDRESS               (_FONT_AUTOCONFIG_EXTEND_ADDRESS + _FONT_AUTOCONFIG_EXTEND)
#define _FONT_AUTOCOLOR_EXTEND_ADDRESS                  (_FONT_OUT_OF_RANGE_EXTEND_ADDRESS + _FONT_OUT_OF_RANGE_EXTEND)
#define _FONT_JAP_EXTEND_ADDRESS                        (_FONT_AUTOCOLOR_EXTEND_ADDRESS + _FONT_AUTOCOLOR_EXTEND)
#define _FONT_CHI_EXTEND_ADDRESS                        (_FONT_JAP_EXTEND_ADDRESS + _FONT_JAP_EXTEND)
#define _FONT_COLORTEMP_EXTEND_ADDRESS                  (_FONT_CHI_EXTEND_ADDRESS + _FONT_CHI_EXTEND)

#define _FONT_EXTEND_END_ADDRESS                        (_FONT_GLOBAL_EXTEND_ADDRESS + _FONT_GLOBAL_EXTEND + _FONT_GLOBAL_EXTEND + _FONT_GLOBAL2ND_EXTEND + _FONT_GLOBAL_ICON_EXTEND + _FONT_NO_SIGNAL_EXTEND + _FONT_AUTOCONFIG_EXTEND + _FONT_OUT_OF_RANGE_EXTEND + _FONT_AUTOCOLOR_EXTEND + _FONT_JAP_EXTEND + _FONT_CHI_EXTEND + _FONT_COLORTEMP_EXTEND)



#endif // End of #if(_OSD_TYPE == _REALTEK_OSD)
