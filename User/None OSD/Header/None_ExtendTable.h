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
#if((_EXTEND_TABLE_SUPPORT == _ON) && (_OSD_TYPE == _NONE_OSD))

//----------------------------------------------------------------------------------------------------
// Filter Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
#define _SU_COEF_EXTEND                                 128







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


#endif //End of #if(_OSD_TYPE == _NONE_OSD)
