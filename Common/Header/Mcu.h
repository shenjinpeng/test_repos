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
// ID Code      : Mcu.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Flash Setting
//--------------------------------------------------

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
#define _FLASH_BANK                 3
*/
#define _XDATA_START_BANK           3

#if(_XDATA_START_BANK > _FLASH_BANK)
#error !_FLASH_BANK should be larger than _XDATA_START_BANK!!!
#endif
// V015 System Patch Note (7) Modify 20100630 End

//--------------------------------------------------
// Definitions of MCU clk select
//--------------------------------------------------
#define _XTAL_CLK                   0
#define _FLASH_CLK                  1

//--------------------------------------------------
// Definitions of Crystal Frequency
//--------------------------------------------------
#if(_MCU_TYPE == _REALTEK_EMBEDDED)
#define _EMCU_XTAL                  ((DWORD)_M2PLL_CLK_MHZ * 1000 / _FLASH_CLK_DIV / _MCU_CLK_DIV)
#define _MCU_INST_CYCLE             ((DWORD)1000000 * 12 / _EMCU_XTAL)

#else
#define _MCU_INST_CYCLE             ((DWORD)1000000 * 12 / _MCU_XTAL)
#endif

//--------------------------------------------------
// Timer Period (unit: ns)
//--------------------------------------------------
#define _10MS_PERIOD                ((DWORD)10000000)
#define _1MS_PERIOD                 ((DWORD)1000000)
#define _HALF_MS_PERIOD             ((DWORD)500000)

//--------------------------------------------------
// Timer0 Settings (1ms)
//--------------------------------------------------
#define _TIMER0_COUNT_NUM           (0xFFFF - (_1MS_PERIOD / _MCU_INST_CYCLE) + 35)
#define _TIMER0_COUNT_LBYTE         (_TIMER0_COUNT_NUM & 0x00FF)
#define _TIMER0_COUNT_HBYTE         (_TIMER0_COUNT_NUM >> 8)

// V012 Modify 20100329 Start
// V012 Patch Note (19) : Adjust polling time of Auto Run Typer according to different Crystal frequency.
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Auto Run Typer Time Out Base Counter(0x200000) Reference 27M Crystal About 80ms:                      //                                                                            //
// 120 = 80 + 40(Tolerance), _XTAL27000K / _MCU_XTAL Is Linear Operator
// _AUTORUN_TYPER_TIME_OUT = (BYTE)((DWORD)120 * _XTAL27000K / _MCU_XTAL)                                //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _SP_AUTORUN_TIME_OUT        ((WORD)((DWORD)120 * _XTAL27000K / _MCU_XTAL))
// V012 Modify 20100329 End

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
#if(_MCU_TYPE == _REALTEK_EMBEDDED)
//--------------------------------------------------
// Definitions of Flash Space
//--------------------------------------------------
#define _FLASH_SPACE  ((_END_PAGE - _START_PAGE + 2) * _PAGE_SIZE)
#endif
*/
// V015 System Patch Note (7) Modify 20100630 End

//----------------------------------------------------------------------------------------------------

#ifdef __MCU__

//--------------------------------------------------
// RTD2120 MCU Global Variables
//--------------------------------------------------
#if((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122))

sfr CKCON = 0x8E;

#if(_MEMORY_LOCATION == _FLASH)
BYTE xdata MCU_FLASH[(_END_PAGE - _START_PAGE + 2) * _PAGE_SIZE]  _at_ (_START_PAGE * _PAGE_SIZE);
#endif

BYTE xdata MCU_DDCRAM_A0[128]       _at_ 0xF900;
BYTE xdata MCU_DDCRAM_D0[256]       _at_ 0xF980;

volatile BYTE xdata MCU_PIN_SHARE0_FF00      _at_ 0xFF00;
volatile BYTE xdata MCU_PIN_SHARE1_FF01      _at_ 0xFF01;
volatile BYTE xdata MCU_PIN_SHARE2_FF02      _at_ 0xFF02;
volatile BYTE xdata MCU_PORT5_OE_FF03        _at_ 0xFF03;
volatile BYTE xdata MCU_PORT6_OE_FF04        _at_ 0xFF04;
volatile BYTE xdata MCU_PORT7_OE_FF05        _at_ 0xFF05;
volatile BYTE xdata MCU_PORT1_TYPE_FF09      _at_ 0xFF09;

volatile BYTE xdata MCU_PORT50_FF50[8]       _at_ 0xFF50;
volatile BYTE xdata MCU_PORT60_FF58[8]       _at_ 0xFF58;
volatile BYTE xdata MCU_PORT76_77_FF60[2]    _at_ 0xFF60;

volatile BYTE xdata MCU_LVRST_CTRL_FF0A      _at_ 0xFF0A;
volatile BYTE xdata MCU_ADC_CTRL_FF0B        _at_ 0xFF0B;
volatile BYTE xdata MCU_ADC0_RESULT_FF0C     _at_ 0xFF0C;
volatile BYTE xdata MCU_ADC1_RESULT_FF0D     _at_ 0xFF0D;
volatile BYTE xdata MCU_ADC2_RESULT_FF0E     _at_ 0xFF0E;
volatile BYTE xdata MCU_ADC3_RESULT_FF0F     _at_ 0xFF0F;

volatile BYTE xdata MCU_PLL_CTRL_FF10        _at_ 0xFF10;
volatile BYTE xdata MCU_PLL_FILTER_CTRL_FF11 _at_ 0xFF11;
volatile BYTE xdata MCU_PLL_M_N_DIV_FF12     _at_ 0xFF12;
volatile BYTE xdata MCU_REGULATOR_CTRL_FF13  _at_ 0xFF13;

volatile BYTE xdata MCU_ADC_DDC_ENA_FF20     _at_ 0xFF20;
volatile BYTE xdata MCU_ADC_DDC_CTRL_FF21    _at_ 0xFF21;
volatile BYTE xdata MCU_DVI_DDC_ENA_FF23     _at_ 0xFF23;
volatile BYTE xdata MCU_DVI_DDC_CTRL_FF24    _at_ 0xFF24;
volatile BYTE xdata MCU_DDCRAM_CTRL_FF26     _at_ 0xFF26;

volatile BYTE xdata MCU_I2C_SET_SLAVE_FF27   _at_ 0xFF27;
volatile BYTE xdata MCU_I2C_SUB_IN_FF28      _at_ 0xFF28;
volatile BYTE xdata MCU_I2C_DATA_IN_FF29     _at_ 0xFF29;
volatile BYTE xdata MCU_I2C_DATA_OUT_FF2A    _at_ 0xFF2A;
volatile BYTE xdata MCU_I2C_STATUS_FF2B      _at_ 0xFF2B;
volatile BYTE xdata MCU_I2C_IRQ_CTRL_FF2C    _at_ 0xFF2C;

volatile BYTE xdata MCU_PWM_CLK_CTRL_FF30    _at_ 0xFF30;
volatile BYTE xdata MCU_PWM_DIV_N_FF31       _at_ 0xFF31;
volatile BYTE xdata MCU_PWM0_DUTY_WIDTH_FF32 _at_ 0xFF32;
volatile BYTE xdata MCU_PWM1_DUTY_WIDTH_FF33 _at_ 0xFF33;
volatile BYTE xdata MCU_PWM2_DUTY_WIDTH_FF34 _at_ 0xFF34;
volatile BYTE xdata MCU_PWM_SRC_SELECT_FF35  _at_ 0xFF35;
volatile BYTE xdata MCU_WATCHDOG_TIMER_FF36  _at_ 0xFF36;

volatile BYTE xdata MCU_ISP_SLAVE_ADDR_FF37  _at_ 0xFF37;
volatile BYTE xdata MCU_OPTION_FF38          _at_ 0xFF38;

volatile BYTE xdata MCU_FC_PAGE_ERASE_FF39   _at_ 0xFF39;
volatile BYTE xdata MCU_RAM_TEST_FF3A        _at_ 0xFF3A;
volatile BYTE xdata MCU_FC_MASS_ERASE0_FF90  _at_ 0xFF90;
volatile BYTE xdata MCU_FC_PAGE_ERASE1_FF91  _at_ 0xFF91;
volatile BYTE xdata MCU_FC_PR_CRC_ISP0_FF92  _at_ 0xFF92;
volatile BYTE xdata MCU_FC_PR_CRC_ISP1_FF93  _at_ 0xFF93;
volatile BYTE xdata MCU_FC_PD_ISP_FF94       _at_ 0xFF94;
volatile BYTE xdata MCU_FC_R_CRC_ISP0_FFA0   _at_ 0xFFA0;
volatile BYTE xdata MCU_FC_R_CRC_ISP1_FFA1   _at_ 0xFFA1;
volatile BYTE xdata MCU_F_R_CRC_ISP0_FFA2    _at_ 0xFFA2;
volatile BYTE xdata MCU_F_R_CRC_ISP1_FFA3    _at_ 0xFFA3;
volatile BYTE xdata MCU_FT_CTRL1_FFB0        _at_ 0xFFB0;
volatile BYTE xdata MCU_FT_CTRL2_FFB1        _at_ 0xFFB1;
volatile BYTE xdata MCU_FT_CTRL3_FFB2        _at_ 0xFFB2;
volatile BYTE xdata MCU_FT_CTRL4_FFB3        _at_ 0xFFB3;
volatile BYTE xdata MCU_FT_CTRL5_FFB4        _at_ 0xFFB4;
volatile BYTE xdata MCU_DEBUG_MODE_CTRL_FFC0 _at_ 0xFFC0;

#if(_BANK_SWITCHING_SUPPORT == _ON)
volatile BYTE xdata MCU_BANK_SWITCH_CTRL_FFFC _at_ 0xFFFC;
volatile BYTE xdata MCU_BANK_SEL_FFFE         _at_ 0xFFFE;
#endif

#endif // End of #if((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122))


//--------------------------------------------------
// RTD Embeded MCU Global Variables
//--------------------------------------------------
#if(_MCU_TYPE == _REALTEK_EMBEDDED)

sfr CKCON = 0x8E;

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
#if(_MEMORY_LOCATION == _FLASH)
#if(_FLASH_SPACE < 0xFB00)
    BYTE xdata MCU_FLASH[_FLASH_SPACE]  _at_ (_START_PAGE * _PAGE_SIZE);
#else
    #error Flash Overflow!!
#endif

#endif
*/
// V015 System Patch Note (7) Modify 20100630 End

BYTE xdata MCU_DDCRAM_A0[128]           _at_ 0xFC80;
BYTE xdata MCU_DDCRAM_DDC2[256]         _at_ 0xFD00;
BYTE xdata MCU_DDCRAM_DDC3[256]         _at_ 0xFE00;

volatile BYTE xdata MCU_IRQ_STATUS_FF00          _at_ 0xFF00;
volatile BYTE xdata MCU_IRQ_PRIORITY_FF01        _at_ 0xFF01;
volatile BYTE xdata MCU_PORT6_OE_FF04            _at_ 0xFF04;
volatile BYTE xdata MCU_ADC_CTRL_FF08            _at_ 0xFF08;
volatile BYTE xdata MCU_ADC1_RESULT_FF0A         _at_ 0xFF0A;
volatile BYTE xdata MCU_ADC2_RESULT_FF0B         _at_ 0xFF0B;

#if(_SCALER_TYPE == _RTD2472D)
volatile BYTE xdata MCU_REV_DUMMY2_FF19          _at_ 0xFF19;
#endif


volatile BYTE xdata MCU_ADC_DDC_ENA_FF1B         _at_ 0xFF1B;

volatile BYTE xdata MCU_ADC_DDC_CTRL1_FF1C       _at_ 0xFF1C;
volatile BYTE xdata MCU_ADC_DDC_CTRL2_FF1D       _at_ 0xFF1D;
volatile BYTE xdata MCU_DVI_DDC_CTRL1_FF1F       _at_ 0xFF1F;
volatile BYTE xdata MCU_DVI_DDC_CTRL2_FF20       _at_ 0xFF20;
volatile BYTE xdata MCU_HDMI_DDC_CTRL1_FF2D      _at_ 0xFF2D;

volatile BYTE xdata MCU_DVI_DDC_ENA_FF1E         _at_ 0xFF1E;

volatile BYTE xdata MCU_DDCRAM_PART_FF21         _at_ 0xFF21;
volatile BYTE xdata MCU_I2C_SET_SLAVE_FF23       _at_ 0xFF23;
volatile BYTE xdata MCU_I2C_SUB_IN_FF24          _at_ 0xFF24;
volatile BYTE xdata MCU_I2C_DATA_IN_FF25         _at_ 0xFF25;
volatile BYTE xdata MCU_I2C_DATA_OUT_FF26        _at_ 0xFF26;
volatile BYTE xdata MCU_I2C_STATUS_FF27          _at_ 0xFF27;
volatile BYTE xdata MCU_I2C_IRQ_CTRL_FF28        _at_ 0xFF28;
volatile BYTE xdata MCU_I2C_STATUS2_FF29         _at_ 0xFF29;
volatile BYTE xdata MCU_I2C_IRQ_CTRL2_FF2A       _at_ 0xFF2A;
volatile BYTE xdata MCU_I2C_CHANNEL_CTRL_FF2B    _at_ 0xFF2B;
volatile BYTE xdata MCU_HDMI_DDC_ENA_FF2C        _at_ 0xFF2C;
volatile BYTE xdata MCU_HDMI_DDC_CTRL2_FF2E       _at_ 0xFF2E;

volatile BYTE xdata MCU_DVI_DDC_INDEX_FF31       _at_ 0xFF31;
volatile BYTE xdata MCU_DVI_DDC_ACCESS_FF32      _at_ 0xFF32;
volatile BYTE xdata MCU_HDMI_DDC_INDEX_FF33      _at_ 0xFF33;
volatile BYTE xdata MCU_HDMI_DDC_ACCESS_FF34     _at_ 0xFF34;
volatile BYTE xdata MCU_DDCCI_REMAIN_FF35        _at_ 0xFF35;

volatile BYTE xdata MCU_COMM_INST_EN_FF60        _at_ 0xFF60;
volatile BYTE xdata MCU_COMM_OP_CODE_FF61        _at_ 0xFF61;
volatile BYTE xdata MCU_WREN_OP_CODE_FF62        _at_ 0xFF62;
volatile BYTE xdata MCU_FLASH_PROG_ISP0_FF64     _at_ 0xFF64;

volatile BYTE xdata MCU_FLASH_PROG_ISP1_FF65     _at_ 0xFF65;
volatile BYTE xdata MCU_FLASH_PROG_ISP2_FF66     _at_ 0xFF66;

volatile BYTE xdata MCU_COMM_INST_READ_P0_FF67   _at_ 0xFF67;

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
volatile BYTE xdata MCU_COMM_INST_READ_P1_FF68   _at_ 0xFF68;
volatile BYTE xdata MCU_COMM_INST_READ_P2_FF69   _at_ 0xFF69;
// V015 System Patch Note (7) Modify 20100630 End

volatile BYTE xdata MCU_READ_OP_CODE_FF6A        _at_ 0xFF6A;
volatile BYTE xdata MCU_FAST_READ_OP_CODE_FF6B   _at_ 0xFF6B;
volatile BYTE xdata MCU_READ_INSTRUCTION_FF6C    _at_ 0xFF6C;

volatile BYTE xdata MCU_PROG_OP_CODE_FF6D        _at_ 0xFF6D;

volatile BYTE xdata MCU_CEN_CTRL_FF76            _at_ 0xFF76;

volatile BYTE xdata MCU_PIN_SHARE_CTRL00_FF94    _at_ 0xFF94;
volatile BYTE xdata MCU_PIN_SHARE_CTRL01_FF95    _at_ 0xFF95;
volatile BYTE xdata MCU_PIN_SHARE_CTRL02_FF96    _at_ 0xFF96;
volatile BYTE xdata MCU_PIN_SHARE_CTRL03_FF97    _at_ 0xFF97;
volatile BYTE xdata MCU_PIN_SHARE_CTRL04_FF98    _at_ 0xFF98;
volatile BYTE xdata MCU_PIN_SHARE_CTRL05_FF99    _at_ 0xFF99;
volatile BYTE xdata MCU_PIN_SHARE_CTRL06_FF9A    _at_ 0xFF9A;
volatile BYTE xdata MCU_PIN_SHARE_CTRL07_FF9B    _at_ 0xFF9B;
volatile BYTE xdata MCU_PIN_SHARE_CTRL08_FF9C    _at_ 0xFF9C;
volatile BYTE xdata MCU_PIN_SHARE_CTRL09_FF9D    _at_ 0xFF9D;
volatile BYTE xdata MCU_PIN_SHARE_CTRL0A_FF9E    _at_ 0xFF9E;
volatile BYTE xdata MCU_PIN_SHARE_CTRL0B_FF9F    _at_ 0xFF9F;
volatile BYTE xdata MCU_PIN_SHARE_CTRL0C_FFA0    _at_ 0xFFA0;
volatile BYTE xdata MCU_PIN_SHARE_CTRL0D_FFA1    _at_ 0xFFA1;
volatile BYTE xdata MCU_PIN_SHARE_CTRL0E_FFA2    _at_ 0xFFA2;
volatile BYTE xdata MCU_PIN_SHARE_CTRL0F_FFA3    _at_ 0xFFA3;
volatile BYTE xdata MCU_PIN_SHARE_CTRL10_FFA4    _at_ 0xFFA4;
volatile BYTE xdata MCU_PIN_SHARE_CTRL11_FFA5    _at_ 0xFFA5;
volatile BYTE xdata MCU_PIN_SHARE_CTRL12_FFA6    _at_ 0xFFA6;
volatile BYTE xdata MCU_PIN_DRIV_CTRL11_FFA7     _at_ 0xFFA7;

volatile BYTE xdata MCU_CEC_CR0_FFAB              _at_ 0xFFAB;

volatile BYTE xdata MCU_PORT_READ_CTRL_FFC0      _at_ 0xFFC0;
volatile BYTE xdata MCU_PORT52_PIN_REG_FFC1      _at_ 0xFFC1;
volatile BYTE xdata MCU_PORT53_PIN_REG_FFC2      _at_ 0xFFC2;
volatile BYTE xdata MCU_PORT54_PIN_REG_FFC3      _at_ 0xFFC3;
volatile BYTE xdata MCU_PORT57_PIN_REG_FFC6      _at_ 0xFFC6;
volatile BYTE xdata MCU_PORT60_PIN_REG_FFC7      _at_ 0xFFC7;
volatile BYTE xdata MCU_PORT62_PIN_REG_FFC9      _at_ 0xFFC9;
volatile BYTE xdata MCU_PORT63_PIN_REG_FFCA      _at_ 0xFFCA;
volatile BYTE xdata MCU_PORT64_PIN_REG_FFCB      _at_ 0xFFCB;
volatile BYTE xdata MCU_PORT65_PIN_REG_FFCC      _at_ 0xFFCC;
volatile BYTE xdata MCU_PORT66_PIN_REG_FFCD      _at_ 0xFFCD;
volatile BYTE xdata MCU_PORT67_PIN_REG_FFCE      _at_ 0xFFCE;

volatile BYTE xdata MCU_PORT74_PIN_REG_FFD3      _at_ 0xFFD3;
volatile BYTE xdata MCU_PORT75_PIN_REG_FFD4      _at_ 0xFFD4;
volatile BYTE xdata MCU_PORT80_PIN_REG_FFD6      _at_ 0xFFD6;
volatile BYTE xdata MCU_PORT81_PIN_REG_FFD7      _at_ 0xFFD7;

volatile BYTE xdata MCU_PORTC_PIN_REG_FFE6       _at_ 0xFFE6;
volatile BYTE xdata MCU_WATCHDOG_TIMER_FFEA      _at_ 0xFFEA;
volatile BYTE xdata MCU_CTRL_FFED                _at_ 0xFFED;
volatile BYTE xdata MCU_CLOCK_CTRL_FFEE          _at_ 0xFFEE;

volatile BYTE xdata MCU_SCA_INF_CTRL_FFF3        _at_ 0xFFF3;
volatile BYTE xdata MCU_SCA_INF_ADDR_FFF4        _at_ 0xFFF4;
volatile BYTE xdata MCU_SCA_INF_DATA_FFF5        _at_ 0xFFF5;

volatile BYTE xdata MCU_BANK_SWITCH_CTRL_FFFC    _at_ 0xFFFC;
volatile BYTE xdata MCU_BANK_START_FFFD          _at_ 0xFFFD;
volatile BYTE xdata MCU_BANK_SEL_FFFE            _at_ 0xFFFE;

volatile BYTE xdata MCU_PWM_CK_SEL_FF3A          _at_ 0xFF3A;
volatile BYTE xdata MCU_PWM03_M_FF3B             _at_ 0xFF3B;
volatile BYTE xdata MCU_PWM45_M_FF3C             _at_ 0xFF3C;
volatile BYTE xdata MCU_PWM01_N_MSB_FF3D         _at_ 0xFF3D;
volatile BYTE xdata MCU_PWM0_N_LSB_FF3E          _at_ 0xFF3E;
volatile BYTE xdata MCU_PWM1_N_LSB_FF3F          _at_ 0xFF3F;
volatile BYTE xdata MCU_PWM23_N_MSB_FF40         _at_ 0xFF40;
volatile BYTE xdata MCU_PWM2_N_LSB_FF41          _at_ 0xFF41;
volatile BYTE xdata MCU_PWM3_N_LSB_FF42          _at_ 0xFF42;
volatile BYTE xdata MCU_PWM45_N_MSB_FF43         _at_ 0xFF43;
volatile BYTE xdata MCU_PWM4_N_LSB_FF44          _at_ 0xFF44;
volatile BYTE xdata MCU_PWM5_N_LSB_FF45          _at_ 0xFF45;
volatile BYTE xdata MCU_PWML_FF46                _at_ 0xFF46;
volatile BYTE xdata MCU_PWM_VS_CTRL_FF47         _at_ 0xFF47;
volatile BYTE xdata MCU_PWM_EN_FF48              _at_ 0xFF48;
volatile BYTE xdata MCU_PWM_CK_FF49              _at_ 0xFF49;
volatile BYTE xdata MCU_PWM0H_DUT_FF4A           _at_ 0xFF4A;
volatile BYTE xdata MCU_PWM1H_DUT_FF4B           _at_ 0xFF4B;
volatile BYTE xdata MCU_PWM01L_DUT_FF4C          _at_ 0xFF4C;
volatile BYTE xdata MCU_PWM2H_DUT_FF4D           _at_ 0xFF4D;
volatile BYTE xdata MCU_PWM3H_DUT_FF4E           _at_ 0xFF4E;
volatile BYTE xdata MCU_PWM23L_DUT_FF4F          _at_ 0xFF4F;
volatile BYTE xdata MCU_PWM4H_DUT_FF50           _at_ 0xFF50;
volatile BYTE xdata MCU_PWM5H_DUT_FF51           _at_ 0xFF51;
volatile BYTE xdata MCU_PWM45L_DUT_FF52          _at_ 0xFF52;
volatile BYTE xdata MCU_REV_DUMMY3_FF53          _at_ 0xFF53;

#else

  /*
  #error No Match Scalar Type !!
  */

#endif  // End of #if(_MCU_TYPE == _REALTEK_EMBEDDED)


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CMcuInitial(void);

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
void CMcuFlashClkDiv(BYTE clkdiv);
void CMcuClkDiv(BYTE clkdiv);
void CMcuSelectFlashClk(bit select);
#endif  // End of #if(_MCU_TYPE == _REALTEK_EMBEDDED)

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
#if((_MCU_TYPE == _REALTEK_RTD2120) || (_MCU_TYPE == _REALTEK_RTD2122))

#if(_MEMORY_LOCATION == _FLASH)
extern BYTE xdata MCU_FLASH[(_END_PAGE - _START_PAGE + 2) * _PAGE_SIZE];
#endif

extern BYTE xdata MCU_DDCRAM_A0[128];
extern BYTE xdata MCU_DDCRAM_D0[256];

extern volatile BYTE xdata MCU_PIN_SHARE0_FF00;
extern volatile BYTE xdata MCU_PIN_SHARE1_FF01;
extern volatile BYTE xdata MCU_PIN_SHARE2_FF02;
extern volatile BYTE xdata MCU_PORT5_OE_FF03;
extern volatile BYTE xdata MCU_PORT6_OE_FF04;
extern volatile BYTE xdata MCU_PORT7_OE_FF05;
extern volatile BYTE xdata MCU_PORT1_TYPE_FF09;

extern volatile BYTE xdata MCU_PORT50_FF50[8];
extern volatile BYTE xdata MCU_PORT60_FF58[8];
extern volatile BYTE xdata MCU_PORT76_77_FF60[2];

extern volatile BYTE xdata MCU_LVRST_CTRL_FF0A;
extern volatile BYTE xdata MCU_ADC_CTRL_FF0B;
extern volatile BYTE xdata MCU_ADC0_RESULT_FF0C;
extern volatile BYTE xdata MCU_ADC1_RESULT_FF0D;
extern volatile BYTE xdata MCU_ADC2_RESULT_FF0E;
extern volatile BYTE xdata MCU_ADC3_RESULT_FF0F;

extern volatile BYTE xdata MCU_PLL_CTRL_FF10;
extern volatile BYTE xdata MCU_PLL_FILTER_CTRL_FF11;
extern volatile BYTE xdata MCU_PLL_M_N_DIV_FF12;
extern volatile BYTE xdata MCU_REGULATOR_CTRL_FF13;

#if(_SCALER_TYPE == _RTD2472D)
extern volatile BYTE xdata MCU_REV_DUMMY2_FF19;
#endif


extern volatile BYTE xdata MCU_ADC_DDC_ENA_FF20;
extern volatile BYTE xdata MCU_ADC_DDC_CTRL_FF21;
extern volatile BYTE xdata MCU_DVI_DDC_ENA_FF23;
extern volatile BYTE xdata MCU_DVI_DDC_CTRL_FF24;
extern volatile BYTE xdata MCU_DDCRAM_CTRL_FF26;

extern volatile BYTE xdata MCU_I2C_SET_SLAVE_FF27;
extern volatile BYTE xdata MCU_I2C_SUB_IN_FF28;
extern volatile BYTE xdata MCU_I2C_DATA_IN_FF29;
extern volatile BYTE xdata MCU_I2C_DATA_OUT_FF2A;
extern volatile BYTE xdata MCU_I2C_STATUS_FF2B;
extern volatile BYTE xdata MCU_I2C_IRQ_CTRL_FF2C;

extern volatile BYTE xdata MCU_PWM_CLK_CTRL_FF30;
extern volatile BYTE xdata MCU_PWM_DIV_N_FF31;
extern volatile BYTE xdata MCU_PWM0_DUTY_WIDTH_FF32;
extern volatile BYTE xdata MCU_PWM1_DUTY_WIDTH_FF33;
extern volatile BYTE xdata MCU_PWM2_DUTY_WIDTH_FF34;
extern volatile BYTE xdata MCU_PWM_SRC_SELECT_FF35;
extern volatile BYTE xdata MCU_WATCHDOG_TIMER_FF36;

extern volatile BYTE xdata MCU_ISP_SLAVE_ADDR_FF37;
extern volatile BYTE xdata MCU_OPTION_FF38;

extern volatile BYTE xdata MCU_FC_PAGE_ERASE_FF39;
extern volatile BYTE xdata MCU_RAM_TEST_FF3A;
extern volatile BYTE xdata MCU_FC_MASS_ERASE0_FF90;
extern volatile BYTE xdata MCU_FC_PAGE_ERASE1_FF91;
extern volatile BYTE xdata MCU_FC_PR_CRC_ISP0_FF92;
extern volatile BYTE xdata MCU_FC_PR_CRC_ISP1_FF93;
extern volatile BYTE xdata MCU_FC_PD_ISP_FF94;
extern volatile BYTE xdata MCU_FC_R_CRC_ISP0_FFA0;
extern volatile BYTE xdata MCU_FC_R_CRC_ISP1_FFA1;
extern volatile BYTE xdata MCU_F_R_CRC_ISP0_FFA2;
extern volatile BYTE xdata MCU_F_R_CRC_ISP1_FFA3;
extern volatile BYTE xdata MCU_FT_CTRL1_FFB0;
extern volatile BYTE xdata MCU_FT_CTRL2_FFB1;
extern volatile BYTE xdata MCU_FT_CTRL3_FFB2;
extern volatile BYTE xdata MCU_FT_CTRL4_FFB3;
extern volatile BYTE xdata MCU_FT_CTRL5_FFB4;
extern volatile BYTE xdata MCU_DEBUG_MODE_CTRL_FFC0;

#if(_BANK_SWITCHING_SUPPORT == _ON)
extern volatile BYTE xdata MCU_BANK_SWITCH_CTRL_FFFC;
extern volatile BYTE xdata MCU_BANK_SEL_FFFE;
#endif

#endif

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
/*
#if(_MEMORY_LOCATION == _FLASH)
#if(_FLASH_SPACE < 0xFB00)
extern BYTE xdata MCU_FLASH[_FLASH_SPACE];
#endif
#endif
*/
// V015 System Patch Note (7) Modify 20100630 End

extern BYTE xdata MCU_DDCRAM_A0[128];
extern BYTE xdata MCU_DDCRAM_DDC2[256];
extern BYTE xdata MCU_DDCRAM_DDC3[256];

extern volatile BYTE xdata MCU_IRQ_STATUS_FF00;
extern volatile BYTE xdata MCU_IRQ_PRIORITY_FF01;
extern volatile BYTE xdata MCU_PORT6_OE_FF04;
extern volatile BYTE xdata MCU_ADC_CTRL_FF08;
extern volatile BYTE xdata MCU_ADC1_RESULT_FF0A;
extern volatile BYTE xdata MCU_ADC2_RESULT_FF0B;

extern volatile BYTE xdata MCU_ADC_DDC_ENA_FF1B;

extern volatile BYTE xdata MCU_ADC_DDC_CTRL2_FF1D;
extern volatile BYTE xdata MCU_DVI_DDC_ENA_FF1E;
extern volatile BYTE xdata MCU_DVI_DDC_CTRL2_FF20;
extern volatile BYTE xdata MCU_DDCRAM_PART_FF21;

extern volatile BYTE xdata MCU_I2C_SET_SLAVE_FF23;
extern volatile BYTE xdata MCU_I2C_SUB_IN_FF24;
extern volatile BYTE xdata MCU_I2C_DATA_IN_FF25;
extern volatile BYTE xdata MCU_I2C_DATA_OUT_FF26;
extern volatile BYTE xdata MCU_I2C_STATUS_FF27;
extern volatile BYTE xdata MCU_I2C_IRQ_CTRL_FF28;
extern volatile BYTE xdata MCU_I2C_STATUS2_FF29;
extern volatile BYTE xdata MCU_I2C_IRQ_CTRL2_FF2A;
extern volatile BYTE xdata MCU_I2C_CHANNEL_CTRL_FF2B;
extern volatile BYTE xdata MCU_HDMI_DDC_ENA_FF2C;
extern volatile BYTE xdata MCU_HDMI_DDC_CTRL2_FF2E;

extern volatile BYTE xdata MCU_DVI_DDC_INDEX_FF31;
extern volatile BYTE xdata MCU_DVI_DDC_ACCESS_FF32;
extern volatile BYTE xdata MCU_HDMI_DDC_INDEX_FF33;
extern volatile BYTE xdata MCU_HDMI_DDC_ACCESS_FF34;
extern volatile BYTE xdata MCU_DDCCI_REMAIN_FF35;

extern volatile BYTE xdata MCU_COMM_INST_EN_FF60;
extern volatile BYTE xdata MCU_COMM_OP_CODE_FF61;
extern volatile BYTE xdata MCU_WREN_OP_CODE_FF62;
extern volatile BYTE xdata MCU_EWSR_OP_CODE_FF63;
extern volatile BYTE xdata MCU_FLASH_PROG_ISP0_FF64;
extern volatile BYTE xdata MCU_FLASH_PROG_ISP1_FF65;
extern volatile BYTE xdata MCU_FLASH_PROG_ISP2_FF66;

// V015 System Patch Note (7) Modify 20100630 Start
// Patch Reason : New EEPROM emulation process.
extern volatile BYTE xdata MCU_COMM_INST_READ_P0_FF67;
extern volatile BYTE xdata MCU_COMM_INST_READ_P1_FF68;
extern volatile BYTE xdata MCU_COMM_INST_READ_P2_FF69;
// V015 System Patch Note (7) Modify 20100630 End

extern volatile BYTE xdata MCU_READ_OP_CODE_FF6A;
extern volatile BYTE xdata MCU_FAST_READ_OP_CODE_FF6B;
extern volatile BYTE xdata MCU_READ_INSTRUCTION_FF6C;

extern volatile BYTE xdata MCU_PROG_OP_CODE_FF6D;
extern volatile BYTE xdata MCU_CEN_CTRL_FF76;

extern volatile BYTE xdata MCU_PIN_SHARE_CTRL00_FF94;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL01_FF95;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL02_FF96;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL03_FF97;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL04_FF98;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL05_FF99;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL06_FF9A;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL07_FF9B;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL08_FF9C;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL09_FF9D;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL0A_FF9E;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL0B_FF9F;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL0C_FFA0;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL0D_FFA1;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL0E_FFA2;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL0F_FFA3;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL10_FFA4;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL11_FFA5;
extern volatile BYTE xdata MCU_PIN_SHARE_CTRL12_FFA6;
extern volatile BYTE xdata MCU_PIN_DRIV_CTRL11_FFA7;

extern volatile BYTE xdata MCU_CEC_CR0_FFAB;

extern volatile BYTE xdata MCU_PORT_READ_CTRL_FFC0;
extern volatile BYTE xdata MCU_PORT52_PIN_REG_FFC1;
extern volatile BYTE xdata MCU_PORT53_PIN_REG_FFC2;
extern volatile BYTE xdata MCU_PORT54_PIN_REG_FFC3;
extern volatile BYTE xdata MCU_PORT57_PIN_REG_FFC6;
extern volatile BYTE xdata MCU_PORT60_PIN_REG_FFC7;
extern volatile BYTE xdata MCU_PORT62_PIN_REG_FFC9;
extern volatile BYTE xdata MCU_PORT63_PIN_REG_FFCA;
extern volatile BYTE xdata MCU_PORT64_PIN_REG_FFCB;
extern volatile BYTE xdata MCU_PORT65_PIN_REG_FFCC;
extern volatile BYTE xdata MCU_PORT66_PIN_REG_FFCD;
extern volatile BYTE xdata MCU_PORT67_PIN_REG_FFCE;

extern volatile BYTE xdata MCU_PORT74_PIN_REG_FFD3;
extern volatile BYTE xdata MCU_PORT75_PIN_REG_FFD4;
extern volatile BYTE xdata MCU_PORT80_PIN_REG_FFD6;
extern volatile BYTE xdata MCU_PORT81_PIN_REG_FFD7;

extern volatile BYTE xdata MCU_PORTC_PIN_REG_FFE6;
extern volatile BYTE xdata MCU_WATCHDOG_TIMER_FFEA;
extern volatile BYTE xdata MCU_CTRL_FFED;
extern volatile BYTE xdata MCU_CLOCK_CTRL_FFEE;

extern volatile BYTE xdata MCU_SCA_INF_CTRL_FFF3;
extern volatile BYTE xdata MCU_SCA_INF_ADDR_FFF4;
extern volatile BYTE xdata MCU_SCA_INF_DATA_FFF5;

extern volatile BYTE xdata MCU_BANK_SWITCH_CTRL_FFFC;
extern volatile BYTE xdata MCU_BANK_START_FFFD;
extern volatile BYTE xdata MCU_BANK_SEL_FFFE;

extern volatile BYTE xdata MCU_PWM_CK_SEL_FF3A;
extern volatile BYTE xdata MCU_PWM03_M_FF3B;
extern volatile BYTE xdata MCU_PWM45_M_FF3C;
extern volatile BYTE xdata MCU_PWM01_N_MSB_FF3D;
extern volatile BYTE xdata MCU_PWM0_N_LSB_FF3E;
extern volatile BYTE xdata MCU_PWM1_N_LSB_FF3F;
extern volatile BYTE xdata MCU_PWM23_N_MSB_FF40;
extern volatile BYTE xdata MCU_PWM2_N_LSB_FF41;
extern volatile BYTE xdata MCU_PWM3_N_LSB_FF42;
extern volatile BYTE xdata MCU_PWM45_N_MSB_FF43;
extern volatile BYTE xdata MCU_PWM4_N_LSB_FF44;
extern volatile BYTE xdata MCU_PWM5_N_LSB_FF45;
extern volatile BYTE xdata MCU_PWML_FF46;
extern volatile BYTE xdata MCU_PWM_VS_CTRL_FF47;
extern volatile BYTE xdata MCU_PWM_EN_FF48;
extern volatile BYTE xdata MCU_PWM_CK_FF49;
extern volatile BYTE xdata MCU_PWM0H_DUT_FF4A;
extern volatile BYTE xdata MCU_PWM1H_DUT_FF4B;
extern volatile BYTE xdata MCU_PWM01L_DUT_FF4C;
extern volatile BYTE xdata MCU_PWM2H_DUT_FF4D;
extern volatile BYTE xdata MCU_PWM3H_DUT_FF4E;
extern volatile BYTE xdata MCU_PWM23L_DUT_FF4F;
extern volatile BYTE xdata MCU_PWM4H_DUT_FF50;
extern volatile BYTE xdata MCU_PWM5H_DUT_FF51;
extern volatile BYTE xdata MCU_PWM45L_DUT_FF52;
extern volatile BYTE xdata MCU_REV_DUMMY3_FF53;

#else

    //#error No Match Scalar Type !!

#endif  // End of #if(_MCU_TYPE == _REALTEK_EMBEDDED)

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CMcuInitial(void);

#if(_MCU_TYPE == _REALTEK_EMBEDDED)
extern void CMcuFlashClkDiv(BYTE clkdiv);
extern void CMcuClkDiv(BYTE clkdiv);
extern void CMcuSelectFlashClk(bit select);
#endif  // End of #if(_MCU_TYPE == _REALTEK_EMBEDDED)

#endif

//----------------------------------------------------------------------------------------------------
