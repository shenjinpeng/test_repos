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

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
#include "Common\Header\Include.h"

#if((_MERGE_EMULATION_TO_CODE == _ON) && (_MEMORY_LOCATION == _FLASH))
BYTE code tReservedFlashSpace[_FLASH_SPACE] = {0xFF};
#endif

BYTE code ucAvoidWarning = 0;
// V015 System Patch Note (7) Modify 20100630 End


