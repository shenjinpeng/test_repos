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
// ID Code      : Struct.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __REALTEK_BANK0__

#include "Common\Header\Include.h"

#if(_OSD_TYPE == _REALTEK_OSD)

//--------------------------------------------------
// Description  : .......
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdBankSwitchNoPortWarning(void)
{

#if(_TMDS_SUPPORT == _ON)
    BYTE temp;
#endif
#if(_DP_SUPPORT == _ON)
    BYTE temp1;
#endif
#if(_TMDS_SUPPORT == _ON)
    temp = tHDMI_NO_PORT_WARNING;
#endif
#if(_DP_SUPPORT == _ON)
    temp1 = tDP_NO_PORT_WARNING;
#endif

}

//--------------------------------------------------
// Description  : Initial OSD flag state
// Input Value  :
// Output Value :
//--------------------------------------------------
void COsdBankSwitchCancelTimer(void)
{
    COsdBankSwitchNoPortWarning();
    CTimerCancelTimerEvent(COsdDispOsdTimerEvent);
}


#endif  // End of #if(_OSD_TYPE == _REALTEK_OSD)

