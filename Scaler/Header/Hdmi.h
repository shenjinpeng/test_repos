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
// ID Code      : Hdmi.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of MCK Frequence
//--------------------------------------------------
#define _AUDIO_128_TIMES        1
#define _AUDIO_256_TIMES        2

#define _AUDIO_MCK_32000        _AUDIO_256_TIMES
#define _AUDIO_MCK_44100        _AUDIO_256_TIMES
#define _AUDIO_MCK_48000        _AUDIO_256_TIMES
#define _AUDIO_MCK_88200        _AUDIO_256_TIMES
#define _AUDIO_MCK_96000        _AUDIO_256_TIMES
#define _AUDIO_MCK_176400       _AUDIO_128_TIMES
#define _AUDIO_MCK_192000       _AUDIO_128_TIMES

//--------------------------------------------------
// Definitions of DAC
//--------------------------------------------------
#define _DAC_DEVICE_ADDR        0x20    //CS4360
#define _DAC_CONTROL_ADDR       0x01

//----------------------------------------------------------------------------------------------------
#ifdef __HDMI__

BYTE code tHDMI_NO_PORT_WARNING[] = { 0x00,};

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Global Hdmi Table
//--------------------------------------------------
BYTE code tHDMI_YPBPR_ITU601[] =
{
#if(_SCALER_TYPE == _RTD2472D)
    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,            0x02,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x0C,0x04,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x1C,0xa8,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x2C,0x06,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x3C,0x62,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x4C,0x01,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x5C,0x91,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x6C,0x03,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x7C,0x40,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x8C,0x08,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x9C,0x12,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xAC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xBC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xCC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xDC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xEC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xFC,0x00,
    4,  _NON_AUTOINC,   _YUV_RGB_ACCESS_9D,          0x0C,
    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,            0x01,
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,             0x07, // Page 7
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,         0x02,// Enable Coefficient Access
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x00,0x04,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x08,0xa8,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x10,0x06,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x18,0x62,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x20,0x01,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x28,0x91,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x30,0x03,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x38,0x40,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x40,0x08,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x48,0x12,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x50,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x58,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x60,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x68,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x70,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x78,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x80,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x88,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x90,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x98,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0xA0,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0xA8,0x00,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_ACCESS_C0,       0x06,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,         0x01,
#else
    No Setting !!

#endif    // End of #if(_SCALER_TYPE == _RTD2472D)
    _END
};

BYTE code tHDMI_YPBPR_ITU709[] =
{
#if(_SCALER_TYPE == _RTD2472D)
    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,            0x02,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x0C,0x04,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x1C,0xa8,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x2C,0x07,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x3C,0x2c,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x4C,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x5C,0xda,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x6C,0x02,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x7C,0x22,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x8C,0x08,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0x9C,0x73,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xAC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xBC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xCC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xDC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xEC,0x00,
    5,  _AUTOINC,       _YUV_RGB_ACCESS_9D,          0xFC,0x00,
    4,  _NON_AUTOINC,   _YUV_RGB_ACCESS_9D,          0x0C,
    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,            0x01,
#elif((_SCALER_TYPE == _RTD2545LR) || (_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,             0x07,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,         0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x00,0x04,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x08,0xa8,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x10,0x07,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x18,0x2c,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x20,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x28,0xda,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x30,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x38,0x22,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x40,0x08,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x48,0x73,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x50,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x58,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x60,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x68,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x70,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x78,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x80,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x88,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x90,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0x98,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0xA0,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,       0xA8,0x00,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_ACCESS_C0,       0x06,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,         0x01,

#else
    No Setting !!

#endif   // End of #if(_SCALER_TYPE == _RTD2472D)

    _END
};



BYTE code tHDMI_AUDIO_DAC[] =
{

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE1,
#if(_SCALER_TYPE == _RTD2472D)
    5,  _AUTOINC,       _P1_BB_POWER0_F0,               0xff,0xff,
#endif

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD))
    5,  _AUTOINC,       _P1_AOUT_CTL_F4,                0x10,0x10,
#endif

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE2,

#if(_SCALER_TYPE == _RTD2472D)
    9,  _AUTOINC,       _P1_BB_POWER0_F0,               0xff,0xff,0x67,0x27,0x10,0x10,
#endif
    _END

};

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
enum AudioFreqDef
{
    _AUDIO_FREQ_32000 = 1,
    _AUDIO_FREQ_44100,
    _AUDIO_FREQ_48000,
    _AUDIO_FREQ_88200,
    _AUDIO_FREQ_96000,
    _AUDIO_FREQ_176400,
    _AUDIO_FREQ_192000,
    _AUDIO_FREQ_NONE,
};
#endif

#endif  // End of #if(_HDMI_SUPPORT == _ON)


//--------------------------------------------------
// Global Variables
//--------------------------------------------------
#if(_HDMI_SUPPORT == _ON)
BYTE xdata ucHdmiCtrl = 0;
BYTE xdata ucAudioRate = 0;

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
#if(_AUDIO_SUPPORT == _ON)
BYTE xdata g_usHDMILockedFreq = 0;
#endif
#endif

#endif  // End of #if(_HDMI_SUPPORT == _ON)


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bit CHdmiFormatDetect(void);

#if(_HDMI_SUPPORT == _ON)
void CHdmiAVMuteCheck(void);
#endif

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
bit CHdmiAudioReadyDetect(void);
void CHdmiAudioInitialSetting(void);
#else
bit CHdmiAudioFIFODetect(void);
#endif

void CHdmiAudioModeDetect(void);
bit CHdmiVideoSetting(void);

#if(_EXT_DAC_SUPPORT == _ON)
void CHdmiResetDAC(void);
void CHdmiAdjustDACSampleRate(BYTE ucModeType);
#endif

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
bit CHdmiAudioFirstTracking(void);
bit CHdmiAudioEnabledCheck(void);
void CHdmiEnableAudioOutput(void);
void CHdmiAudioControl(void);
#else
void CHdmiAudioWaitingFlagReadyEven(void);
void CHdmiAudioFirstTracking(void);
#endif

void CHdmiEnableAudioOutput(void);
//void CHdmiHotPlugProc(BYTE ms);

#else

//--------------------------------------------------
// Extern Global Hdmi Table
//--------------------------------------------------
extern BYTE code tHDMI_NO_PORT_WARNING[];

#if(_HDMI_SUPPORT == _ON)
extern BYTE code tHDMI_YPBPR_ITU601[];
extern BYTE code tHDMI_YPBPR_ITU709[];
extern BYTE code tHDMI_AUDIO_DAC[];
#endif // End of #if(_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE xdata ucHdmiCtrl;
extern BYTE xdata ucAudioRate;

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
#if(_AUDIO_SUPPORT == _ON)
extern BYTE xdata g_usHDMILockedFreq;
#endif
#endif

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern bit CHdmiFormatDetect(void);

#if(_HDMI_SUPPORT == _ON)
extern void CHdmiAVMuteCheck(void);
#endif

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
extern bit CHdmiAudioReadyDetect(void);
extern void CHdmiAudioInitialSetting(void);
#else
extern bit CHdmiAudioFIFODetect(void);
#endif

extern bit CHdmiVideoSetting(void);
extern void CHdmiAudioModeDetect(void);
extern void CHdmiResetDAC(void);
extern void CHdmiAdjustDACSampleRate(BYTE ucModeType);

#if(_AUDIO_SUPPORT == _ON)
#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
extern bit CHdmiAudioFirstTracking(void);
extern void CHdmiAudioControl(void);
extern bit CHdmiAudioEnabledCheck(void);
#else
extern void CHdmiAudioWaitingFlagReadyEven(void);
extern void CHdmiAudioFirstTracking(void);
#endif

extern void CHdmiEnableAudioOutput(void);
//extern void CHdmiHotPlugProc(BYTE ms);

#endif

#endif // End of #ifdef __HDMI__

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Input source is the HDMI format
//--------------------------------------------------
#define GET_HDMIINPUT()                 (bit)(ucHdmiCtrl & _BIT0)
#define SET_HDMIINPUT()                 (ucHdmiCtrl |= _BIT0)
#define CLR_HDMIINPUT()                 (ucHdmiCtrl &= ~_BIT0)

#if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))
//--------------------------------------------------
// Macro of HDMI Audio Tracked
//--------------------------------------------------
#define GET_HDMIAUDIOUNTRACKED()                  (bit)(ucHdmiCtrl & _BIT1)
#define SET_HDMIAUDIOUNTRACKED()                  (ucHdmiCtrl |= _BIT1)
#define CLR_HDMIAUDIOUNTRACKED()                  (ucHdmiCtrl &= ~_BIT1)

//--------------------------------------------------
// Macro of HDMI Audio Waiting Time Flag
//--------------------------------------------------
#define GET_HDMIAUDIOTRACKED()          (bit)(ucHdmiCtrl & _BIT2)
#define SET_HDMIAUDIOTRACKED()          (ucHdmiCtrl |= _BIT2)
#define CLR_HDMIAUDIOTRACKED()          (ucHdmiCtrl &= ~_BIT2)


//--------------------------------------------------
// Macro of HDMI AVMute Flag
//--------------------------------------------------
#define GET_AVMUTE()       (bit)(ucHdmiCtrl & _BIT3)
#define SET_AVMUTE()       (ucHdmiCtrl |= _BIT3)
#define CLR_AVMUTE()       (ucHdmiCtrl &= ~_BIT3)

#else  // Else of #if((_SCALER_TYPE == _RTD247xRD) || (_SCALER_TYPE == _RTD248xRD) || (_SCALER_TYPE == _RTD2545LR))

//--------------------------------------------------
// Macro of HDMI Audio PLL Lock Ready Flag
//--------------------------------------------------
#define GET_AUDIOPLLLOCKREADY()         (bit)(ucHdmiCtrl & _BIT1)
#define SET_AUDIOPLLLOCKREADY()         (ucHdmiCtrl |= _BIT1)
#define CLR_AUDIOPLLLOCKREADY()         (ucHdmiCtrl &= ~_BIT1)

//--------------------------------------------------
// Macro of HDMI Audio Resume Flag
//--------------------------------------------------
#define GET_AVRESUME()                  (bit)(ucHdmiCtrl & _BIT2)
#define SET_AVRESUME()                  (ucHdmiCtrl |= _BIT2)
#define CLR_AVRESUME()                  (ucHdmiCtrl &= ~_BIT2)

//--------------------------------------------------
// Macro of HDMI Audio Waiting Time Flag
//--------------------------------------------------
#define GET_AUDIOWAITINGFLAG()          (bit)(ucHdmiCtrl & _BIT3)
#define SET_AUDIOWAITINGFLAG()          (ucHdmiCtrl |= _BIT3)
#define CLR_AUDIOWAITINGFLAG()          (ucHdmiCtrl &= ~_BIT3)

//--------------------------------------------------
// Macro of HDMI Audio Waiting Time Out Flag
//--------------------------------------------------
#define GET_AUDIOWAITINGTIMEOUT()       (bit)(ucHdmiCtrl & _BIT4)
#define SET_AUDIOWAITINGTIMEOUT()       (ucHdmiCtrl |= _BIT4)
#define CLR_AUDIOWAITINGTIMEOUT()       (ucHdmiCtrl &= ~_BIT4)

#endif

//--------------------------------------------------
// Macro of 2472 Demo Board Audio ClassD 3005
//--------------------------------------------------
#define SET_AUDIOPWR()                  (bAUDIO_PWR = _LOW)
#define CLR_AUDIOPWR()                  (bAUDIO_PWR = _HIGH)

#define SET_AMPPWR()                    (bSHDN_AMP = _LOW)
#define CLR_AMPPWR()                    (bSHDN_AMP = _HIGH)


