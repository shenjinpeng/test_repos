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
// ID Code      : Source.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SOURCE__

#include "Common\Header\Include.h"

#if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)


//--------------------------------------------------
// Description  : Measure Source type
// Input Value  : None
// Output Value : Return _TRUE if succeed
//--------------------------------------------------
bit CSourceHandler(void)
{
    if(GET_INPUTSOURCE_TYPE() == _SOURCE_NONE)
    {
    #if _DEBUG_MESSAGE_SUPPORT

CDebugMessage("GET_INPUTSOURCE_TYPE() == _SOURCE_NONE", 0);
	#endif
        if(CSourceScanHandler())
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Scan all input port and select active port
// Input Value  : None
// Output Value : Return _TRUE if the selected input source is exist
//--------------------------------------------------
bit CSourceScanHandler(void)
{
    if(g_ucSearchTimes > 0)                         // Scan same source until search time was zero.
    {
 	#if _DEBUG_MESSAGE_SUPPORT
//	CDebugMessage("CSourceScanInputPort_CSourceScanHandler", 0);
	#endif
        if(CSourceScanInputPort())
        {
            // For giving DP more times
            g_ucModeStableCount = 29;

            if(g_ucSearchTimes >= 1)
            {
                g_ucSearchTimes -= 1;
            }
            else
            {
                g_ucSearchTimes = 0;
            }

            CLR_SEARCH_FINISH();

#if(_YPBPR_SUPPORT == _ON)
            if((GET_INPUTSOURCE_TYPE() == _SOURCE_VGA) || (GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR))
#else
            if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
#endif
            {
                SET_VGA_INITIAL();
            }

            return _TRUE;
        }
        else
        {

            if(g_ucSearchTimes >= 1)
            {
                g_ucSearchTimes -= 1;
            }
            else
            {
                g_ucSearchTimes = 0;
            }

            SET_INPUTSOURCE_TYPE(_SOURCE_NONE);
        }
    }
    else
    {
        CSourceSwitchPortSetting();

        if(g_ucSearchFinish >= sizeof(tINPUT_PORT)) // Scan finish with no signal.
        {
            SET_SEARCH_FINISH();
            g_ucSearchFinish = 0;
        }
		

		
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check connect pin and scan all input port to obtain if the signal is available
// Input Value  : None
// Output Value : Return _TRUE if the selected input source is exist
//--------------------------------------------------
bit CSourceScanInputPort(void)
{
#if _DEBUG_MESSAGE_SUPPORT
CDebugMessage("g_ucSearchIndex_csourcescanibputport==", g_ucSearchIndex); 
#endif
//if(g_ucSearchIndex>1)g_ucSearchIndex=0;//sjp20111206
    if(GET_INPUTPORT_TYPE(g_ucSearchIndex) != _NO_PORT)
    {
        if(GET_SEARCH_INITIAL() == _TRUE)
        {

#if(_DP_SUPPORT == _ON)
            if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DP_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DP_PORT))
            {
#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))
                CSyncInputPort2DInitial();
#endif

                g_bDpFakeLT = 0;

                g_usDVITMDSFreq = 0;
            }
            else if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT)
                 || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT)
                 || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT)
                 || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT)
                 || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_I_PORT)
                 || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_I_PORT))
            {
                g_bHDMISearchTimesResetFlag = 1;
                CDpHDCPReset();

                g_bDpFakeLT = 1;
                g_bFakeTPEndPass = _TRUE;

            }
            else
            {

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))

                CSyncInputPort2DInitial();
#endif

                CDpHDCPReset();

                g_bDpFakeLT = 1;

                g_usDVITMDSFreq = 0;

            }

            if(GET_INPUT_SOURCE_SEARCH())
            {
                g_ucDisplayPortLtPreStatus = _TRAINING_PATTERN_NONE;
                CLR_DPHOTPLUG();
                g_bDpCPIRQ = _FALSE;
                CDpHotPlugProc(20);
            }

            CLR_INPUT_SOURCE_SEARCH();

#else

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2472D))
            if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT)
              || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT)
              || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT)
              || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT)
              || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_I_PORT)
              || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_I_PORT))
            {
                g_bHDMISearchTimesResetFlag = 1;

            }
            else
            {
                CSyncInputPort2DInitial();
                g_usDVITMDSFreq = 0;
            }
#endif

#if(_SCALER_TYPE == _RTD2472D)
            if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT)
            || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT)
            || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT)
            || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT)
            || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_I_PORT)
            || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_I_PORT))
            {
                // Search Port is not the same with prenious port, need HDCP Auto Reset
                if(GET_INPUT_PORT(g_ucSearchIndex) != g_ucFormerSearchPort)
                {
                    CScalerPageSelect(_PAGE2);
                    CScalerSetDataPortBit(_P2_HDCP_ADDR_PORT_C3, 0xC4, ~_BIT4, _BIT4);
                    CScalerSetDataPortBit(_P2_HDCP_ADDR_PORT_C3, 0xC4, ~_BIT4, 0x00);
                }
            }
            g_ucFormerSearchPort = GET_INPUT_PORT(g_ucSearchIndex);
#endif


#endif  // End of #if(_DP_SUPPORT == _ON)
#if _DEBUG_MESSAGE_SUPPORT
//CDebugMessage("CScalerResetProcess_CSourceScanInputPort", 0);
#endif 
            CScalerResetProcess();
            SET_TMDS_INITIAL();

            CLR_SEARCH_INITIAL();

        }   // End of if(GET_SEARCH_INITIAL() == _TRUE)

        switch(GET_INPUT_PORT(g_ucSearchIndex))
        {
           /********************/
            case _D0_INPUT_PORT:
           /********************/
#if((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT))
                if(CSyncScanInputPortDVI())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
#endif

#if(_DP_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                if(CSyncScanInputPortDP())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
#endif
#endif


#if(_D0_INPUT_PORT_TYPE == _D0_DVI_I_PORT)
    #if(_DVI_I_SEARCH == _DVI_FIRST)
                if(CSyncScanInputPortDVI())
                {
                    return _TRUE;
                }

                if(CSyncScanInputPortVGA())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
    #else
                if(CSyncScanInputPortVGA())
                {
                    return _TRUE;
                }

                if(CSyncScanInputPortDVI())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
    #endif
#endif


#if((_D0_INPUT_PORT_TYPE == _D0_VIDEO8_PORT) && (_VIDEO_SUPPORT == _ON))
                if(CVideoIsExist())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
#endif
            break;


           /********************/
            case _D1_INPUT_PORT:
           /********************/
#if((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT))
                if(CSyncScanInputPortDVI())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
#endif

#if(_DP_SUPPORT == _ON)
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                if(CSyncScanInputPortDP())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
#endif
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DVI_I_PORT)
    #if(_DVI_I_SEARCH == _DVI_FIRST)
                if(CSyncScanInputPortDVI())
                {
                    return _TRUE;
                }

                if(CSyncScanInputPortVGA())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
    #else
                if(CSyncScanInputPortVGA())
                {
                    return _TRUE;
                }

                if(CSyncScanInputPortDVI())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
    #endif
#endif
            break;


           /********************/
            case _A0_INPUT_PORT:
           /********************/

#if((_A0_INPUT_PORT_TYPE == _A0_VGA_PORT) || (_A0_INPUT_PORT_TYPE == _A0_YPBPR_PORT))
                if(CSyncScanInputPortVGA())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
#endif
            break;


           /********************/
            case _A1_INPUT_PORT:
           /********************/

#if((_A1_INPUT_PORT_TYPE == _A1_VIDEO8_PORT) && (_VIDEO_SUPPORT == _ON))
                if(CVideoIsExist())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
#endif


#if((_A1_INPUT_PORT_TYPE == _A1_VGA_PORT) || (_A1_INPUT_PORT_TYPE == _A1_YPBPR_PORT))
                if(CSyncScanInputPortVGA())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
#endif
            break;


           /********************/
            case _VI_INPUT_PORT:
           /********************/

#if(_VI_INPUT_PORT_TYPE == _VI_VIDEO8_PORT)
                if(CVideoIsExist())
                {
                    return _TRUE;
                }
                else
                {
                    break;
                }
#endif

            default:
            break;
        }
    }

    SET_INPUTSOURCE_TYPE(_SOURCE_NONE);
    return _FALSE;
}

//--------------------------------------------------
// Description  : Switch Input Port Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSourceSwitchPortSetting(void)
{
    BYTE cnt = 0;
    BYTE ucOldIndex = 0;

    ucOldIndex = g_ucSearchIndex;

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    if(GET_SOURCE_SEARCH_AUTO() == _TRUE)
    {
        SET_SOURCE_STATE(_SOURCE_AUTO_CHANGE_STATE);
    }
    else
    {
        SET_SOURCE_STATE(_CLR_AUTO_CHANGE_STATE);
    }
#endif

#if(_DP_SUPPORT == _ON)
    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DP_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DP_PORT))
    {
        if((g_bDpDisplayPass == _TRUE) && (g_ucDpPowerStatus != _DP_POWER_DOWN))
        {
            g_ucSearchTimes = GET_INPUTPORT_SEARCH_TIMES(g_ucSearchIndex);
            g_ucSearchFinish = sizeof(tINPUT_PORT);
            return;
        }
    }
#endif

    switch(GET_SOURCE_STATE())
    {
        case _SOURCE_AUTO_CHANGE_STATE:         // Auto Change Input Source by search priority in the same group.


            if(GET_FIRST_INPUT_PORT_SEARCH())   // Switch to the first priority of input port.
            {
                CSourceSwitchFirstInputPort();
                CLR_FIRST_INPUT_PORT_SEARCH();

                if(g_ucSearchIndex == stSystemData.SearchIndex)
                {
                    g_ucSearchFinish--;
                }
                else
                {
                    break;
                }
            }

            do                                  // Switch to the next port by search priority with group limit.
            {
                g_ucSearchIndex = (g_ucSearchIndex + 1) % (sizeof(tINPUT_PORT));

                if(g_ucSearchIndex == stSystemData.SearchIndex)
                {
                    continue;
                }

                g_ucSearchFinish++;

                if((GET_INPUTPORT_GROUP(g_ucSearchIndex) == GET_INPUTPORT_GROUP(ucOldIndex)) && (GET_INPUTPORT_TYPE(g_ucSearchIndex) != _NO_PORT))
                {
                    break;
                }

                cnt++;

            }while(cnt < sizeof(tINPUT_PORT));

            if(g_ucSearchFinish >= sizeof(tINPUT_PORT) || (cnt >= sizeof(tINPUT_PORT)))
            {
                g_ucSearchIndex = stSystemData.SearchIndex;
                SET_FIRST_INPUT_PORT_SEARCH();
            }
            break;

        case _CLR_AUTO_CHANGE_STATE:            // Disable Auto Change Input Source.
            g_ucSearchFinish = sizeof(tINPUT_PORT);
            break;

        case _SWITCH_INPUT_SOURCE_STATE:        // Switch Input Source by search priority without group limit.
            g_ucSearchFinish = sizeof(tINPUT_PORT);
            break;
    }

    g_ucSearchTimes = GET_INPUTPORT_SEARCH_TIMES(g_ucSearchIndex);

    SET_SEARCH_INITIAL();

}

//--------------------------------------------------
// Description  : Switch to the First Priority of Input Port in the same group
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSourceSwitchFirstInputPort(void)
{
    BYTE cnt = 0;

    for(cnt = _SEARCH_POL_0; cnt < sizeof(tINPUT_PORT); cnt++)
    {
        if(GET_INPUTPORT_GROUP(cnt) == GET_INPUTPORT_GROUP(g_ucSearchIndex))
        {
            if(cnt != g_ucSearchIndex)
            {
                break;
            }
        }
    }

    if(cnt < sizeof(tINPUT_PORT))
    {
        g_ucSearchIndex = cnt;
    }

    g_ucSearchFinish++;
}

//--------------------------------------------------
// Description  : Switch Input Port
// Input Value  : Input port type
// Output Value : Return _TRUE if the selected input port is exist
//--------------------------------------------------
bit CSourceSwitchInputPort(BYTE inputport)
{
    BYTE cnt = 0;

#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
    if(GET_SOURCE_OSD_STATUS())
    {
        CLR_SOURCE_OSD_STATUS();
    }
#endif

    for(cnt = 0; cnt < sizeof(tINPUT_PORT); cnt++)
    {
        if((GET_INPUT_PORT(cnt) == inputport) && (GET_INPUTPORT_TYPE(cnt) != _NO_PORT))
        {
            stSystemData.SearchIndex = cnt;
            return _TRUE;
        }
    }

    return _FALSE;
}

#if(_SWITCH_INPUT_SOURCE == _ON)
//--------------------------------------------------
// Description  : Switch Input Source
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSourceSwitchInputSource(void)
{
    stSystemData.SearchIndex = (stSystemData.SearchIndex + 1) % (sizeof(tINPUT_PORT));


    CModeResetMode();
    SET_SOURCE_STATE(_SWITCH_INPUT_SOURCE_STATE);
}
#endif

//--------------------------------------------------
// Description  : Initial source setting, we have to run this at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSourceInitialSetting(void)
{
    CLR_INPUT_SEARCH_INITIAL();
    SET_INPUTSOURCE_TYPE(_SOURCE_NONE);

#if(_SWITCH_INPUT_SOURCE == _OFF)
    SET_SOURCE_STATE(_SOURCE_AUTO_CHANGE_STATE);
    SET_FIRST_INPUT_PORT_SEARCH();
#endif

    g_ucSearchIndex = stSystemData.SearchIndex;
#if _DEBUG_MESSAGE_SUPPORT
		 CDebugMessage("stSystemData.SearchIndex_sourceinitialsetting", stSystemData.SearchIndex) ;
#endif
    g_ucSearchTimes = GET_INPUTPORT_SEARCH_TIMES(g_ucSearchIndex);
    g_ucSearchFinish = 0;

    CSourceInitialConnect();

#if(_DP_SUPPORT == _ON)
    SET_INPUT_SOURCE_SEARCH();
#endif

#if(_SWITCH_INPUT_SOURCE_OSD == _ON)
    CLR_SOURCE_OSD_STATUS();
#endif

    CLR_SEARCH_FINISH();

    SET_SEARCH_INITIAL();

}

//--------------------------------------------------
// Description  : Initial Connect setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSourceInitialConnect(void)
{
#ifdef _A0_PORT
    SET_PRE_A0_CONNECT(bA0_CONNECT);
#endif

#ifdef _A1_PORT
    SET_PRE_A1_CONNECT(bA1_CONNECT);
#endif

#if((_HDMI_SUPPORT == _ON) || (_TMDS_SUPPORT == _ON))

#ifdef _D0_PORT

#if(_DP_SUPPORT == _ON)

#if(_PCB_TYPE == _RTD2472RD_DEMO_PCB)
    SET_PRE_D0_CONNECT(CDpAuxPinCableConnect());
#else
    SET_PRE_D0_CONNECT(bD0_CONNECT);
#endif

#endif

#endif // End of #if(_DP_SUPPORT == _ON)

#ifdef _D1_PORT
    SET_PRE_D1_CONNECT(bD1_CONNECT);
#endif

#endif
}

//--------------------------------------------------
// Description  : Save the Search Index and Input Source to Eeprom
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSourceSaveSearchData(void)
{
    stSystemData.SearchIndex = g_ucSearchIndex;
    CEepromSaveSystemData();
}

//--------------------------------------------------
// Description  : Set Count Down after source stable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSourceSetCountDown(void)
{
    if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DP_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DP_PORT))
    {
        SET_COUNTDOWN_DP_STABLE();             // 500ms for DP
    }
    else if((GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_HDMI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D0_DVI_I_PORT) || (GET_INPUTPORT_TYPE(g_ucSearchIndex) == _D1_DVI_I_PORT))
    {
        if(g_bHDMIHDCPFlag == 1)
        {
            SET_COUNTDOWN_HDMI_HDCP_WORSE();   // 3 secs for HDCP
        }
        else
        {
            SET_COUNTDOWN_HDMI_STABLE();         // 300ms for no HDCP
        }
    }
    else
    {
        SET_COUNTDOWN_VGA_STABLE();            // 100ms for VGA
    }
}

#endif  // End of #if(_SCALER_SERIES_TYPE == _RTD2472D_SERIES)


