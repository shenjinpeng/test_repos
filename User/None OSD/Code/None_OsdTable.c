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
// ID Code      : OsdTable.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "Common\Header\Include.h"

#if(_OSD_TYPE == _NONE_OSD)

//----------------------------------------------------------------------------------------------------
// OSD Operation Table
//----------------------------------------------------------------------------------------------------
code void (*OperationTable[][4])(void) =
{
    { COsdMenuNone,                 COsdLeftNone,                   COsdRightNone,                  COsdExitNone                 },
};


#endif  // End of #if(_OSD_TYPE == _NONE_OSD)

