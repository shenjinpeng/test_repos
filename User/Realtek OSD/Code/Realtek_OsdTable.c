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

#if(_OSD_TYPE == _REALTEK_OSD)

//----------------------------------------------------------------------------------------------------
// OSD Operation Table
//----------------------------------------------------------------------------------------------------
code void (*OperationTable[][4])(void) =
{
    { COsdMenuNone,                     COsdLeftNone,                       COsdRightNone,                      COsdExitNone                        },
    { COsdMenuDicomSetting,             COsdLeftDicomSetting,               COsdRightDicomSetting,              COsdExitDicomSetting                },
    { COsdMenuGammaSetting,             COsdLeftGammaSetting,               COsdRightGammaSetting,         COsdExitGammaSetting                     },
    { COsdMenuBrightnessSetting,               COsdLeftBrightnessSetting,                 COsdRightBrightnessSetting,                COsdExitBrightnessSetting         },
    { COsdMenuContrastSetting,              COsdLeftContrastSetting ,                 COsdRightContrastSetting,                COsdExitContrastSetting         },
    { COsdMenuSignalSource,             COsdLeftSignalSource,               COsdRightSignalSource,              COsdExitSignalSource                },

//#if(_AUDIO_SUPPORT == _ON)
//    { COsdMenuAudio,                    COsdLeftAudio,                      COsdRightAudio,                     COsdExitAudio                       },
//#endif

    { COsdMenuAutoAdjust,                  COsdLeftAutoAdjust,                    COsdRightAutoAdjust,                   COsdExitAutoAdjust                   },
    { COsdMenuFactory,                  COsdLeftFactory,                    COsdRightFactory,                   COsdExitFactory                     },

#if(_DDCCI_SUPPORT == _ON)
    { COsdMenuDDCCI,                    COsdLeftDDCCI,                      COsdRightDDCCI,                      COsdExitDDCCI},
#endif

    { COsdMenuSubDicom,              COsdLeftSubDicom,                COsdRightSubDicom,               COsdExitSubDicom                 },
    { COsdMenuSubGamma,              COsdLeftSubGamma,                COsdRightSubGamma,               COsdExitSubGamma                 },
 //   { COsdMenuContrast,                 COsdLeftContrast,                   COsdRightContrast,                  COsdExitContrast                    },
    { COsdMenuSubBrightness,            COsdLeftSubBrightness,              COsdRightSubBrightness,             COsdExitSubBrightness               },

    { COsdMenuSubContrast,              COsdLeftSubContrast,                COsdRightSubContrast,               COsdExitSubContrast                 },
//    { COsdMenuBrightness,               COsdLeftBrightness,                 COsdRightBrightness,                COsdExitBrightness                  },
    { COsdMenuSignalSelect,              COsdLeftSignalSelect,                COsdRightSignalSelect,               COsdExitSignalSelect                },
    { COsdMenuSubAutoAdjust,              COsdLeftSubAutoAdjust,                COsdRightSubAutoAdjust,               COsdExitSubAutoAdjust                },

    { COsdMenuSubFacReset,              COsdLeftSubFacReset,                COsdRightSubFacReset,               COsdExitSubFacReset},

    { COsdMenuColorAdj,                 COsdLeftColorAdj,                   COsdRightColorAdj,                  COsdExitColorAdj                    },
    { COsdMenuSubColorAdjR,             COsdLeftSubColorAdjR,               COsdRightSubColorAdjR,              COsdExitSubColorAdjR                },
    { COsdMenuSubColorAdjG,             COsdLeftSubColorAdjG,               COsdRightSubColorAdjG,              COsdExitSubColorAdjG                },
    { COsdMenuSubColorAdjB,             COsdLeftSubColorAdjB,               COsdRightSubColorAdjB,              COsdExitSubColorAdjB                },
    { COsdMenuAdjR,                     COsdLeftAdjR,                       COsdRightAdjR,                      COsdExitAdjR                        },
    { COsdMenuAdjG,                     COsdLeftAdjG,                       COsdRightAdjG,                      COsdExitAdjG                        },
    { COsdMenuAdjB,                     COsdLeftAdjB,                       COsdRightAdjB,                      COsdExitAdjB                        },
    { COsdMenuColorTemp,                COsdLeftColorTemp,                  COsdRightColorTemp,                 COsdExitColorTemp                   },
    { COsdMenuSubTempColor9300,         COsdLeftSubTempColor9300,           COsdRightSubTempColor9300,          COsdExitSubTempColor9300            },
    { COsdMenuSubTempColor6500,         COsdLeftSubTempColor6500,           COsdRightSubTempColor6500,          COsdExitSubTempColor6500            },
    { COsdMenuSubTempColor5800,         COsdLeftSubTempColor5800,           COsdRightSubTempColor5800,          COsdExitSubTempColor5800            },
    { COsdMenuSubTempSrgb,              COsdLeftSubTempSrgb,                COsdRightSubTempSrgb,               COsdExitSubTempSrgb                 },
    { COsdMenuSubTempUser,              COsdLeftSubTempUser,                COsdRightSubTempUser,               COsdExitSubTempUser                 },

#if(_DCR_MODE != _DCR_TYPE_OFF)
    { COsdMenuColorDCR,                 COsdLeftColorDCR,                   COsdRightColorDCR,                  COsdExitColorDCR                    },
#endif

    { COsdMenuClock,                    COsdLeftClock,                      COsdRightClock,                     COsdExitClock                       },
    { COsdMenuSubClock,                 COsdLeftSubClock,                   COsdRightSubClock,                  COsdExitSubClock                    },
    { COsdMenuPhase,                    COsdLeftPhase,                      COsdRightPhase,                     COsdExitPhase                       },
    { COsdMenuSubPhase,                 COsdLeftSubPhase,                   COsdRightSubPhase,                  COsdExitSubPhase                    },
    { COsdMenuSharpness,                COsdLeftSharpness,                  COsdRightSharpness,                 COsdExitSharpness                   },
    { COsdMenuSubSharpness0,            COsdLeftSubSharpness0,              COsdRightSubSharpness0,             COsdExitSubSharpness0               },
    { COsdMenuSubSharpness1,            COsdLeftSubSharpness1,              COsdRightSubSharpness1,             COsdExitSubSharpness1               },
    { COsdMenuSubSharpness2,            COsdLeftSubSharpness2,              COsdRightSubSharpness2,             COsdExitSubSharpness2               },
    { COsdMenuSubSharpness3,            COsdLeftSubSharpness3,              COsdRightSubSharpness3,             COsdExitSubSharpness3               },
    { COsdMenuSubSharpness4,            COsdLeftSubSharpness4,              COsdRightSubSharpness4,             COsdExitSubSharpness4               },
    { COsdMenuHPosition,                COsdLeftHPosition,                  COsdRightHPosition,                 COsdExitHPosition                   },
    { COsdMenuSubHPosition,             COsdLeftSubHPosition,               COsdRightSubHPosition,              COsdExitSubHPosition                },
    { COsdMenuVPosition,                COsdLeftVPosition,                  COsdRightVPosition,                 COsdExitVPosition                   },
    { COsdMenuSubVPosition,             COsdLeftSubVPosition,               COsdRightSubVPosition,              COsdExitSubVPosition                },

#if(_OD_SUPPORT == _ON)
    { COsdMenuOD,                       COsdLeftOD,                         COsdRightOD,                        COsdExitOD                          },
    { COsdMenuSubOD,                    COsdLeftSubOD,                      COsdRightSubOD,                     COsdExitSubOD                       },
#endif

    { COsdMenuOsdHPos,                  COsdLeftOsdHPos,                    COsdRightOsdHPos,                   COsdExitOsdHPos                     },
    { COsdMenuSubOsdHPos,               COsdLeftSubOsdHPos,                 COsdRightSubOsdHPos,                COsdExitSubOsdHPos                  },
    { COsdMenuOsdVPos,                  COsdLeftOsdVPos,                    COsdRightOsdVPos,                   COsdExitOsdVPos                     },
    { COsdMenuSubOsdVPos,               COsdLeftSubOsdVPos,                 COsdRightSubOsdVPos,                COsdExitSubOsdVPos                  },
    { COsdMenuOsdTime,                  COsdLeftOsdTime,                    COsdRightOsdTime,                   COsdExitOsdTime                     },
    { COsdMenuSubOsdTime,               COsdLeftSubOsdTime,                 COsdRightSubOsdTime,                COsdExitSubOsdTime                  },
    { COsdMenuLanguage,                 COsdLeftLanguage,                   COsdRightLanguage,                  COsdExitLanguage                    },
    { COsdMenuSubEng,                   COsdLeftSubEng,                     COsdRightSubEng,                    COsdExitSubEng                      },
    { COsdMenuSubFran,                  COsdLeftSubFran,                    COsdRightSubFran,                   COsdExitSubFran                     },
    { COsdMenuSubDeut,                  COsdLeftSubDeut,                    COsdRightSubDeut,                   COsdExitSubDeut                     },
    { COsdMenuSubEspa,                  COsdLeftSubEspa,                    COsdRightSubEspa,                   COsdExitSubEspa                     },
    { COsdMenuSubChi,                   COsdLeftSubChi,                     COsdRightSubChi,                    COsdExitSubChi                      },
    { COsdMenuSubSimpleChi,             COsdLeftSubSimpleChi,               COsdRightSubSimpleChi,              COsdExitSubSimpleChi                },
    { COsdMenuSubJap,                   COsdLeftSubJap,                     COsdRightSubJap,                    COsdExitSubJap                      },

    { COsdMenuSingalVGA,                COsdLeftSingalVGA,                  COsdRightSingalVGA,                 COsdExitSingalVGA                   },
    { COsdMenuSingalDVI,                COsdLeftSingalDVI,                  COsdRightSingalDVI,                 COsdExitSingalDVI                   },
    { COsdMenuSingalHDMI,               COsdLeftSingalHDMI,                 COsdRightSingalHDMI,                COsdExitSingalHDMI                  },
    { COsdMenuSingalDisplayPort,        COsdLeftSingalDisplayPort,          COsdRightSingalDisplayPort,         COsdExitSingalDisplayPort           },

#if(_SOURCE_SEARCH_TYPE_BY_OSD == _ON)
    { COsdMenuSingalAutoSearch,         COsdLeftSingalAutoSearch,           COsdRightSingalAutoSearch,          COsdExitSingalAutoSearch            },
#endif

#if(_AUDIO_SUPPORT == _ON)
    { COsdMenuVolume,                   COsdLeftVolume,                     COsdRightVolume,                    COsdExitVolume                      },
    { COsdMenuSubVolume,                COsdLeftSubVolume,                  COsdRightSubVolume,                 COsdExitSubVolume                   },
    { COsdMenuMute,                     COsdLeftMute,                       COsdRightMute,                      COsdExitMute                        },
#endif // End of #if(_AUDIO_SUPPORT==_ON)

#if(_DDCCI_SUPPORT == _ON)
    {COsdMenuDDCCIONOFF,                COsdLeftDDCCIONOFF,                 COsdRightDDCCIONOFF,                COsdExitDDCCIONOFF                  },
#endif

#if(_VIVID_COLOR_FUCTION == _ON)
    { COsdMenuVividColor,               COsdLeftVividColor,                 COsdRightVividColor,                COsdExitVividColor                  },
    { COsdMenuColorWindow,              COsdLeftColorWindow,                COsdRightColorWindow,               COsdExitColorWindow                 },
    { COsdMenuColorWindowDisable,       COsdLeftColorWindowDisable,         COsdRightColorWindowDisable,        COsdExitColorWindowDisable          },
    { COsdMenuColorWindowFull,          COsdLeftColorWindowFull,            COsdRightColorWindowFull,           COsdExitColorWindowFull             },
    { COsdMenuColorWindowDemo,          COsdLeftColorWindowDemo,            COsdRightColorWindowDemo,           COsdExitColorWindowDemo             },
    { COsdMenuColorWindowUser,          COsdLeftColorWindowUser,            COsdRightColorWindowUser,           COsdExitColorWindowUser             },
    { COsdMenuColorWindowUserHPos,      COsdLeftColorWindowUserHPos,        COsdRightColorWindowUserHPos,       COsdExitColorWindowUserHPos         },
    { COsdMenuColorWindowUserHPosAdj,   COsdLeftColorWindowUserHPosAdj,     COsdRightColorWindowUserHPosAdj,    COsdExitColorWindowUserHPosAdj      },
    { COsdMenuColorWindowUserVPos,      COsdLeftColorWindowUserVPos,        COsdRightColorWindowUserVPos,       COsdExitColorWindowUserVPos         },
    { COsdMenuColorWindowUserVPosAdj,   COsdLeftColorWindowUserVPosAdj,     COsdRightColorWindowUserVPosAdj,    COsdExitColorWindowUserVPosAdj      },
    { COsdMenuColorWindowUserHWid,      COsdLeftColorWindowUserHWid,        COsdRightColorWindowUserHWid,       COsdExitColorWindowUserHWid         },
    { COsdMenuColorWindowUserHWidAdj,   COsdLeftColorWindowUserHWidAdj,     COsdRightColorWindowUserHWidAdj,    COsdExitColorWindowUserHWidAdj      },
    { COsdMenuColorWindowUserVHei,      COsdLeftColorWindowUserVHei,        COsdRightColorWindowUserVHei,       COsdExitColorWindowUserVHei         },
    { COsdMenuColorWindowUserVHeiAdj,   COsdLeftColorWindowUserVHeiAdj,     COsdRightColorWindowUserVHeiAdj,    COsdExitColorWindowUserVHeiAdj      },
    { COsdMenuDCCMode,                  COsdLeftDCCMode,                    COsdRightDCCMode,                   COsdExitDCCMode                     },
    { COsdMenuDCCModeDisable,           COsdLeftDCCModeDisable,             COsdRightDCCModeDisable,            COsdExitDCCModeDisable              },
    { COsdMenuDCCModeMovie,             COsdLeftDCCModeMovie,               COsdRightDCCModeMovie,              COsdExitDCCModeMovie                },
    { COsdMenuDCCModePhoto,             COsdLeftDCCModePhoto,               COsdRightDCCModePhoto,              COsdExitDCCModePhoto                },
    { COsdMenuDCCModeGame,              COsdLeftDCCModeGame,                COsdRightDCCModeGame,               COsdExitDCCModeGame                 },
    { COsdMenuICMMode,                  COsdLeftICMMode,                    COsdRightICMMode,                   COsdExitICMMode                     },
    { COsdMenuICMModeDisable,           COsdLeftICMModeDisable,             COsdRightICMModeDisable,            COsdExitICMModeDisable              },
    { COsdMenuICMModeMovie,             COsdLeftICMModeMovie,               COsdRightICMModeMovie,              COsdExitICMModeMovie                },
    { COsdMenuICMModePhoto,             COsdLeftICMModePhoto,               COsdRightICMModePhoto,              COsdExitICMModePhoto                },
    { COsdMenuICMModeGame,              COsdLeftICMModeGame,                COsdRightICMModeGame,               COsdExitICMModeGame                 },
    { COsdMenuICMModeUser,              COsdLeftICMModeUser,                COsdRightICMModeUser,               COsdExitICMModeUser                 },
    { COsdMenuICMModeUserRedHue,        COsdLeftICMModeUserRedHue,          COsdRightICMModeUserRedHue,         COsdExitICMModeUserRedHue           },
    { COsdMenuICMModeUserRedHueAdj,     COsdLeftICMModeUserRedHueAdj,       COsdRightICMModeUserRedHueAdj,      COsdExitICMModeUserRedHueAdj        },
    { COsdMenuICMModeUserRedSat,        COsdLeftICMModeUserRedSat,          COsdRightICMModeUserRedSat,         COsdExitICMModeUserRedSat           },
    { COsdMenuICMModeUserRedSatAdj,     COsdLeftICMModeUserRedSatAdj,       COsdRightICMModeUserRedSatAdj,      COsdExitICMModeUserRedSatAdj        },
    { COsdMenuICMModeUserGreenHue,      COsdLeftICMModeUserGreenHue,        COsdRightICMModeUserGreenHue,       COsdExitICMModeUserGreenHue         },
    { COsdMenuICMModeUserGreenHueAdj,   COsdLeftICMModeUserGreenHueAdj,     COsdRightICMModeUserGreenHueAdj,    COsdExitICMModeUserGreenHueAdj      },
    { COsdMenuICMModeUserGreenSat,      COsdLeftICMModeUserGreenSat,        COsdRightICMModeUserGreenSat,       COsdExitICMModeUserGreenSat         },
    { COsdMenuICMModeUserGreenSatAdj,   COsdLeftICMModeUserGreenSatAdj,     COsdRightICMModeUserGreenSatAdj,    COsdExitICMModeUserGreenSatAdj      },
    { COsdMenuICMModeUserBlueHue,       COsdLeftICMModeUserBlueHue,         COsdRightICMModeUserBlueHue,        COsdExitICMModeUserBlueHue          },
    { COsdMenuICMModeUserBlueHueAdj,    COsdLeftICMModeUserBlueHueAdj,      COsdRightICMModeUserBlueHueAdj,     COsdExitICMModeUserBlueHueAdj       },
    { COsdMenuICMModeUserBlueSat,       COsdLeftICMModeUserBlueSat,         COsdRightICMModeUserBlueSat,        COsdExitICMModeUserBlueSat          },
    { COsdMenuICMModeUserBlueSatAdj,    COsdLeftICMModeUserBlueSatAdj,      COsdRightICMModeUserBlueSatAdj,     COsdExitICMModeUserBlueSatAdj       },
    { COsdMenuVividContrast,            COsdLeftVividContrast,              COsdRightVividContrast,             COsdExitVividContrast               },
    { COsdMenuVividContrastAdj,         COsdLeftVividContrastAdj,           COsdRightVividContrastAdj,          COsdExitVividContrastAdj            },
    { COsdMenuVividBrightness,          COsdLeftVividBrightness,            COsdRightVividBrightness,           COsdExitVividBrightness             },
    { COsdMenuVividBrightnessAdj,       COsdLeftVividBrightnessAdj,         COsdRightVividBrightnessAdj,        COsdExitVividBrightnessAdj          },
#endif

#if(_NON_LINEAR_SCALING_FUCTION == _ON)
    { COsdMenuNonLinearScaling,         COsdLeftNonLinearScaling,           COsdRightNonLinearScaling,          COsdExitNonLinearScaling            },
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
    { COsdMenuAspectRatio,              COsdLeftAspectRatio,                COsdRightAspectRatio,               COsdExitAspectRatio                 },
#endif

#if (_SRGB_COLOR_ENHANCE == _ON)
    { COsdMenuSrgb,                     COsdLeftSrgb,                       COsdRightSrgb,                      COsdExitSrgb                        },
    { COsdMenuHue,                      COsdLeftHue,                        COsdRightHue,                       COsdExitHue                         },
    { COsdMenuSubHue,                   COsdLeftSubHue,                     COsdRightSubHue,                    COsdExitSubHue                      },
    { COsdMenuSaturation,               COsdLeftSaturation,                 COsdRightSaturation,                COsdExitSaturation                  },
    { COsdMenuSubSaturation,            COsdLeftSubSaturation,              COsdRightSubSaturation,             COsdExitSubSaturation               },
#endif

// V012 Modify 20100304 Start
// V012 Patch Note (1) : Add RGB/YUV color space convert function.
#if(_COLOR_FORMAT_CONVERT == _ON)
    { COsdMenuRGBYUV,                   COsdLeftRGBYUV,                     COsdRightRGBYUV,                  COsdExitRGBYUV                    },
    { COsdMenuSubRGB,                   COsdLeftSubRGB,                     COsdRightSubRGB,                  COsdExitSubRGB                    },
    { COsdMenuSubYUV,                   COsdLeftSubYUV,                     COsdRightSubYUV,                  COsdExitSubYUV                    },
#endif
// V012 Modify 20100304 End

    { COsdMenuFAutoColor,               COsdLeftFAutoColor,                 COsdRightFAutoColor,                COsdExitFAutoColor                  },
    { COsdMenuFReset,                   COsdLeftFReset,                     COsdRightFReset,                    COsdExitFReset                      },
    { COsdMenuFOffset,                  COsdLeftFOffset,                    COsdRightFOffset,                   COsdExitFOffset                     },
    { COsdMenuFOffsetR,                 COsdLeftFOffsetR,                   COsdRightFOffsetR,                  COsdExitFOffsetR                    },
    { COsdMenuFOffsetRAdj,              COsdLeftFOffsetRAdj,                COsdRightFOffsetRAdj,               COsdExitFOffsetRAdj                 },
    { COsdMenuFOffsetG,                 COsdLeftFOffsetG,                   COsdRightFOffsetG,                  COsdExitFOffsetG                    },
    { COsdMenuFOffsetGAdj,              COsdLeftFOffsetGAdj,                COsdRightFOffsetGAdj,               COsdExitFOffsetGAdj                 },
    { COsdMenuFOffsetB,                 COsdLeftFOffsetB,                   COsdRightFOffsetB,                  COsdExitFOffsetB                    },
    { COsdMenuFOffsetBAdj,              COsdLeftFOffsetBAdj,                COsdRightFOffsetBAdj,               COsdExitFOffsetBAdj                 },
    { COsdMenuFGain,                    COsdLeftFGain,                      COsdRightFGain,                     COsdExitFGain                       },
    { COsdMenuFGainR,                   COsdLeftFGainR,                     COsdRightFGainR,                    COsdExitFGainR                      },
    { COsdMenuFGainRAdj,                COsdLeftFGainRAdj,                  COsdRightFGainRAdj,                 COsdExitFGainRAdj                   },
    { COsdMenuFGainG,                   COsdLeftFGainG,                     COsdRightFGainG,                    COsdExitFGainG                      },
    { COsdMenuFGainGAdj,                COsdLeftFGainGAdj,                  COsdRightFGainGAdj,                 COsdExitFGainGAdj                   },
    { COsdMenuFGainB,                   COsdLeftFGainB,                     COsdRightFGainB,                    COsdExitFGainB                      },
    { COsdMenuFGainBAdj,                COsdLeftFGainBAdj,                  COsdRightFGainBAdj,                 COsdExitFGainBAdj                   },
    { COsdMenuFColor9300,               COsdLeftFColor9300,                 COsdRightFColor9300,                COsdExitFColor9300                  },
    { COsdMenuFColor9300R,              COsdLeftFColor9300R,                COsdRightFColor9300R,               COsdExitFColor9300R                 },
    { COsdMenuFColor9300RAdj,           COsdLeftFColor9300RAdj,             COsdRightFColor9300RAdj,            COsdExitFColor9300RAdj              },
    { COsdMenuFColor9300G,              COsdLeftFColor9300G,                COsdRightFColor9300G,               COsdExitFColor9300G                 },
    { COsdMenuFColor9300GAdj,           COsdLeftFColor9300GAdj,             COsdRightFColor9300GAdj,            COsdExitFColor9300GAdj              },
    { COsdMenuFColor9300B,              COsdLeftFColor9300B,                COsdRightFColor9300B,               COsdExitFColor9300B                 },
    { COsdMenuFColor9300BAdj,           COsdLeftFColor9300BAdj,             COsdRightFColor9300BAdj,            COsdExitFColor9300BAdj              },
    { COsdMenuFColor6500,               COsdLeftFColor6500,                 COsdRightFColor6500,                COsdExitFColor6500                  },
    { COsdMenuFColor6500R,              COsdLeftFColor6500R,                COsdRightFColor6500R,               COsdExitFColor6500R                 },
    { COsdMenuFColor6500RAdj,           COsdLeftFColor6500RAdj,             COsdRightFColor6500RAdj,            COsdExitFColor6500RAdj              },
    { COsdMenuFColor6500G,              COsdLeftFColor6500G,                COsdRightFColor6500G,               COsdExitFColor6500G                 },
    { COsdMenuFColor6500GAdj,           COsdLeftFColor6500GAdj,             COsdRightFColor6500GAdj,            COsdExitFColor6500GAdj              },
    { COsdMenuFColor6500B,              COsdLeftFColor6500B,                COsdRightFColor6500B,               COsdExitFColor6500B                 },
    { COsdMenuFColor6500BAdj,           COsdLeftFColor6500BAdj,             COsdRightFColor6500BAdj,            COsdExitFColor6500BAdj              },
    { COsdMenuFColor5800,               COsdLeftFColor5800,                 COsdRightFColor5800,                COsdExitFColor5800                  },
    { COsdMenuFColor5800R,              COsdLeftFColor5800R,                COsdRightFColor5800R,               COsdExitFColor5800R                 },
    { COsdMenuFColor5800RAdj,           COsdLeftFColor5800RAdj,             COsdRightFColor5800RAdj,            COsdExitFColor5800RAdj              },
    { COsdMenuFColor5800G,              COsdLeftFColor5800G,                COsdRightFColor5800G,               COsdExitFColor5800G                 },
    { COsdMenuFColor5800GAdj,           COsdLeftFColor5800GAdj,             COsdRightFColor5800GAdj,            COsdExitFColor5800GAdj              },
    { COsdMenuFColor5800B,              COsdLeftFColor5800B,                COsdRightFColor5800B,               COsdExitFColor5800B                 },
    { COsdMenuFColor5800BAdj,           COsdLeftFColor5800BAdj,             COsdRightFColor5800BAdj,            COsdExitFColor5800BAdj              },
    { COsdMenuFSrgb,                    COsdLeftFSrgb,                      COsdRightFSrgb,                     COsdExitFSrgb                       },
    { COsdMenuFSrgbR,                   COsdLeftFSrgbR,                     COsdRightFSrgbR,                    COsdExitFSrgbR                      },
    { COsdMenuFSrgbRAdj,                COsdLeftFSrgbRAdj,                  COsdRightFSrgbRAdj,                 COsdExitFSrgbRAdj                   },
    { COsdMenuFSrgbG,                   COsdLeftFSrgbG,                     COsdRightFSrgbG,                    COsdExitFSrgbG                      },
    { COsdMenuFSrgbGAdj,                COsdLeftFSrgbGAdj,                  COsdRightFSrgbGAdj,                 COsdExitFSrgbGAdj                   },
    { COsdMenuFSrgbB,                   COsdLeftFSrgbB,                     COsdRightFSrgbB,                    COsdExitFSrgbB                      },
    { COsdMenuFSrgbBAdj,                COsdLeftFSrgbBAdj,                  COsdRightFSrgbBAdj,                 COsdExitFSrgbBAdj                   },
    { COsdMenuFUser,                    COsdLeftFUser,                      COsdRightFUser,                     COsdExitFUser                       },
    { COsdMenuFUserR,                   COsdLeftFUserR,                     COsdRightFUserR,                    COsdExitFUserR                      },
    { COsdMenuFUserRAdj,                COsdLeftFUserRAdj,                  COsdRightFUserRAdj,                 COsdExitFUserRAdj                   },
    { COsdMenuFUserG,                   COsdLeftFUserG,                     COsdRightFUserG,                    COsdExitFUserG                      },
    { COsdMenuFUserGAdj,                COsdLeftFUserGAdj,                  COsdRightFUserGAdj,                 COsdExitFUserGAdj                   },
    { COsdMenuFUserB,                   COsdLeftFUserB,                     COsdRightFUserB,                    COsdExitFUserB                      },
    { COsdMenuFUserBAdj,                COsdLeftFUserBAdj,                  COsdRightFUserBAdj,                 COsdExitFUserBAdj                   },
    { COsdMenuFBright,                  COsdLeftFBright,                    COsdRightFBright,                   COsdExitFBright                     },
    { COsdMenuFBrightAdj,               COsdLeftFBrightAdj,                 COsdRightFBrightAdj,                COsdExitFBrightAdj                  },
    { COsdMenuFAutoConfig,              COsdLeftFAutoConfig,                COsdRightFAutoConfig,               COsdExitFAutoConfig                 },
    { COsdMenuFExit,                    COsdLeftFExit,                      COsdRightFExit,                     COsdExitFExit                       },

};


#endif  // End of #if(_OSD_TYPE == _REALTEK_OSD)


