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
// ID Code      : Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "reg52.h"
#include "intrins.h"
#include "math.h"

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
#include "string.h"
// V015 System Patch Note (7) Modify 20100630 End

#include "Common\Header\Global.h"

#include "Project\Project.h"


//---------------------------------------------------------------------------
#if(_PROJECT == _RTD2472D_DEMO_BOARD)
#include "Project\RTD2482D_Demo_Board.h"
#include "Pcb\RTD2482D_Demo_PCB.h"
#endif
#if(_PROJECT == _RTD2472D_QA_BOARD)
#include "Project\RTD2482D_QA_Board.h"
#include "Pcb\RTD2482D_QA_PCB.h"
#endif
#if(_PROJECT == _RTD2545LR_DEMO_BOARD)
#include "Project\RTD2545LR_Demo_Board.h"
#include "Pcb\RTD2545LR_DEMO_PCB.h"
#endif
#if(_PROJECT == _RTD2545LR_QA_BOARD)
#include "Project\RTD2545LR_QA_Board.h"
#include "Pcb\RTD2545LR_QA_PCB.h"
#endif
#if(_PROJECT == _RTD2472RD_DEMO_BOARD)
#include "Project\RTD2482RD_Demo_Board.h"
#include "Pcb\RTD2482RD_Demo_PCB.h"
#endif
#if(_PROJECT == _RTD2472RD_QA_BOARD)
#include "Project\RTD2482RD_QA_Board.h"
#include "Pcb\RTD2482RD_QA_PCB.h"
#endif

#include "Maindef\AdvanceDef.h"

//---------------------------------------------------------------------------
#if(_OSD_TYPE == _NONE_OSD)

#include "User\None OSD\Header\None_Define.h"
#include "User\None OSD\Header\None_ExtendTable.h"
#include "User\None OSD\Header\None_Struct.h"
#include "User\None OSD\Header\None_Osd.h"
#include "User\None OSD\Header\None_OsdTable.h"
#include "User\None OSD\Header\None_OsdDisp.h"
#include "User\None OSD\Header\None_OsdFunc.h"
#include "User\None OSD\Header\None_OsdFont.h"
#include "User\None OSD\Header\None_Key.h"
#include "User\None OSD\Header\None_Eeprom.h"
#include "User\None OSD\Header\None_EepromDefault.h"
#include "User\None OSD\Header\None_BankSwitch.h"

#elif(_OSD_TYPE == _REALTEK_OSD)

#include "User\Realtek OSD\Header\Realtek_Define.h"
#include "User\Realtek OSD\Header\Realtek_ExtendTable.h"
#include "User\Realtek OSD\Header\Realtek_Struct.h"
#include "User\Realtek OSD\Header\Realtek_Osd.h"
#include "User\Realtek OSD\Header\Realtek_Ddc.h"

#include "User\Realtek OSD\Header\Realtek_OsdTable.h"
#include "User\Realtek OSD\Header\Realtek_OsdDisp.h"
#include "User\Realtek OSD\Header\Realtek_OsdFunc.h"
#include "User\Realtek OSD\Header\Realtek_OsdFont.h"
#include "User\Realtek OSD\Header\Realtek_Key.h"
#include "User\Realtek OSD\Header\Realtek_Eeprom.h"
#include "User\Realtek OSD\Header\Realtek_EepromDefault.h"
#include "User\Realtek OSD\Header\Realtek_BankSwitch.h"
#include "User\Realtek OSD\Header\Realtek_Flash.h"

#else
    No Setting !!
#endif // End of #if(_OSD_TYPE == _NONE_OSD)

//---------------------------------------------------------------------------
#include "Panel\00_CMO_LVDS_17.h"
#include "Panel\01_AU_RSDS_17.h"
#include "Panel\02_AU_LVDS_15.h"
#include "Panel\03_AU_LVDS_20_WSXGA.h"
#include "Panel\04_AU_LVDS_20_UXGA.h"
#include "Panel\05_SAMSUNG_LVDS_19_WXGA.h"
#include "Panel\06_CMO_LVDS_20_SXGA_PLUS.h"
#include "Panel\07_CMO_LVDS_19_WXGA.h"
#include "Panel\08_CMO_LVDS_22_WSXGA_PLUS.h"
#include "Panel\09_AU_LVDS_22_WSXGA.h"
#include "Panel\10_AU_LVDS_23_WUXGA.h"
#include "Panel\11_AU_LVDS_21_5_WUXGA.h"
#include "Panel\12_AU_LVDS_24_WUXGA.h"

//---------------------------------------------------------------------------
#include "Maindef\Version.h"

#include "Common\Header\ModeTable.h"
#include "Common\Header\Timer.h"
#include "Common\Header\Mcu.h"
#include "Common\Header\I2c.h"
#include "Common\Header\Main.h"
#include "Common\Header\Uart.h"
#include "Common\Header\Debug.h"


//---------------------------------------------------------------------------
#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

#include "Scaler\Header\ScalerDef.h"
#include "Scaler\Header\Power.h"
#include "Scaler\Header\Mode.h"
#include "Scaler\Header\FrameSync.h"
#include "Scaler\Header\Scaler.h"
#include "Scaler\Header\Sync.h"
#include "Scaler\Header\SystemTable.h"
#include "Scaler\Header\Adjust.h"
#include "Scaler\Header\Auto.h"
#include "Scaler\Header\Source.h"
#include "Scaler\Header\Misc.h"
#include "Scaler\Header\Video.h"
#include "Scaler\Header\YPbPr.h"
#include "Scaler\Header\Memory.h"
#include "Scaler\Header\Hdmi.h"
#if(_DP_SUPPORT == _ON)
#include "Scaler\Header\DisplayPort.h"
#endif


#endif // End of #if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)

//---------------------------------------------------------------------------
#if(_DCR_MODE != _DCR_TYPE_OFF)
#include "DCR\Header\DCR_Type_1.h"
#include "DCR\Header\DCR_Type_2.h"
#include "DCR\Header\DCR_Type_3.h"
#endif

