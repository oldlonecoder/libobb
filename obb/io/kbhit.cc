/******************************************************************************************
 *   Copyright (C) ...,2025,... by Serge Lussier                                          *
 *   serge.lussier@oldlonecoder.club / lussier.serge@gmail.com                            *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Codes ands files in this project is written          *
 *   by the author and owned by the auther (Serge Lussier), unless otherwise specified.   *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here.                    *
 *   Open source FREE licences also apply To the Code from the author (Serge Lussier)     *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... or whatever -  apply to this project.                 *
 *   ----------------------------------------------------------------------------------   *
 *   NOTE : All code source that I am the only author, I reserve for myself, the rights to*
 *   make it to restricted private license.                                               *
 ******************************************************************************************/




#include <lus/io/kbhit.h>


namespace lus::io
{

kbhit kbhit::NONE{kbhit::NO_KEY, 0, "NO KEY"};



kbhit::kbhit(kbhit::enums e, u64 c, std::string_view n): mnemonic(e), code(c), name(n){}





kbhit::dbgroup kbhit::keys_db
{
    {ARROW_UP                   ,0x00000000001b5b41,"ArrowUp"               },
    {ARROW_DOWN                 ,0x00000000001b5b42,"ArrowDown"             },
    {ARROW_LEFT                 ,0x00000000001b5b44,"ArrowLeft"             },
    {ARROW_RIGHT                ,0x00000000001b5b43,"ArrowRight"            },
    {ENTER                      ,0x000000000000000A,"Enter"                 },
    {ESCAPE                     ,0x000000000000001b,"ESC"                   },
    {BACKSPACE                  ,0x000000000000007F,"BackSpace"             },
    {HOME                       ,0x00000000001b5b48,"HOME"                  },
    {END                        ,0x00000000001b5b46,"End"                   },
    {PAGE_UP                    ,0x000000001b5b357e,"PageUP"                },
    {PAGE_DOWN                  ,0x000000001b5b367e,"PageDown"              },
    {INSERT                     ,0x000000001b5b327e,"Insert"                },
    {DELETE                     ,0x000000001b5b337e,"Delete"                },
    {TAB                        ,0x0000000000000009,"TAB"                   },
    {F1                         ,0x00000000001b4f50,"F1"                    },
    {F2                         ,0x00000000001b4f51,"F2"                    },
    {F3                         ,0x00000000001b4f52,"F3"                    },
    {F4                         ,0x00000000001b4f53,"F4"                    },
    {F5                         ,0x0000001b5b31357e,"F5"                    },
    {F6                         ,0x0000001b5b31377e,"F6"                    },
    {F7                         ,0x0000001b5b31387e,"F7"                    },
    {F8                         ,0x0000001b5b31397e,"F8"                    },
    {F9                         ,0x0000001b5b32307e,"F9"                    },
    {F10                        ,0x0000001b5b32317e,"F10"                   },
    {F11                        ,0x0000001b5b32337e,"F11"                   },
    {F12                        ,0x0000001b5b32347e,"F12"                   },
    {kbhit::SHIFT_ARROW_UP        ,0x00001b5b313b3241,"Shift+ArrowUp"         },
    {kbhit::SHIFT_ARROW_DOWN      ,0x00001b5b313b3242,"Shift+ArrowDown"       },
    {kbhit::SHIFT_ARROW_LEFT      ,0x00001b5b313b3244,"Shift+ArrowLeft"       },
    {kbhit::SHIFT_ARROW_RIGHT     ,0x00001b5b313b3243,"Shift+ArrowRight"      },
    {kbhit::SHIFT_END             ,0x00001b5b313b3246,"Shift+End"             },
    {kbhit::SHIFT_HOME            ,0x00001b5b313b3248,"Shift+Home"            },
    {kbhit::SHIFT_PAGE_UP         ,0x00001b5b353b327e,"Shift+PageUp"          },
    {kbhit::SHIFT_PAGE_DOWN       ,0x00001b5b363b327e,"Shift+PageDown"        },
    {kbhit::SHIFT_F1              ,0x000000001b4f3250,"Shift+F1"              },
    {kbhit::SHIFT_F2              ,0x000000001b4f3251,"Shift+F2"              },
    {kbhit::SHIFT_F3              ,0x000000001b4f3252,"Shift+F3"              },
    {kbhit::SHIFT_F4              ,0x000000001b4f3253,"Shift+F4"              },
    {kbhit::SHIFT_F5              ,0x001b5b31353b327e,"Shift+F5"              },
    {kbhit::SHIFT_F6              ,0x001b5b31373b327e,"Shift+F6"              },
    {kbhit::SHIFT_F7              ,0x001b5b31383b327e,"Shift+F7"              },
    {kbhit::SHIFT_F8              ,0x001b5b31393b327e,"Shift+F8"              },
    {kbhit::SHIFT_F9              ,0x001b5b32303b327e,"Shift+F9"              },
    {kbhit::SHIFT_F10             ,0x001b5b32313b327e,"Shift+F10"             },
    {kbhit::SHIFT_F11             ,0x001b5b32333b327e,"Shift+F11"             },
    {kbhit::SHIFT_F12             ,0x001b5b32343b327e,"Shift+F12"             },
    {kbhit::SHIFT_TAB             ,0x00000000001b5b5a,"Shift+Tab"             },
    {kbhit::SHIFT_ENTER           ,0x00000000001b4f4d,"Shift+Enter"           },
    {kbhit::CTRL_PAGE_UP          ,0x00001b5b353b357e,"Ctrl+PageUp"           },
    {kbhit::CTRL_PAGE_DOWN        ,0x00001b5b363b357e,"Ctrl+PageDown"         },
    {kbhit::CTRL_DELETE           ,0x00001b5b333b357e,"Ctrl+Delete"           },
    {kbhit::CTRL_END              ,0x00001b5b313b3546,"Ctrl+End"              },
    {kbhit::CTRL_ARROW_LEFT       ,0x00001b5b313b3544,"Ctrl+ArrowLeft"        },
    {kbhit::CTRL_ARROW_RIGHT      ,0x00001b5b313b3543,"Ctrl+ArrowRight"       },
    {kbhit::CTRL_ARROW_UP         ,0x00001b5b313b3541,"Ctrl+ArrowUp"          },
    {kbhit::CTRL_ARROW_DOWN       ,0x00001b5b313b3542,"Ctrl+ArrowDown"        },
    {kbhit::CTRL_HOME             ,0x00001b5b313b3548,"Ctrl+Home"             },
    {kbhit::CTRL_INSERT           ,0x00001b5b323b357e,"Ctrl+Insert"           },
    {kbhit::CTRL_Q                ,0x0000000000000011,"Ctrl+Q"                },
    {kbhit::CTRL_S                ,0x0000000000000013,"Ctrl+S"                },
    {kbhit::CTRL_V                ,0x0000000000000016,"Ctrl+V"                },
    {kbhit::CTRL_BACKSPACE        ,0x0000000000000008,"Ctrl+Back-Space"       },
    {kbhit::CTRL_F8               ,0x001b5b31393b357e,"Ctrl+F8"               },
    {kbhit::ALT_ARROW_LEFT        ,0x00001b5b313b3344,"Alt+ArrowLeft"         },
    {kbhit::ALT_ARROW_RIGHT       ,0x00001b5b313b3343,"Alt+ArrowRight"        },
    {kbhit::ALT_ARROW_UP          ,0x00001b5b313b3341,"Alt+ArrowUp"           },
    {kbhit::ALT_ARROW_DOWN        ,0x00001b5b313b3342,"Alt+ArrowDown"         },
    {kbhit::SHIFT_CTRL_ARROW_LEFT ,0x00001b5b313b3644,"Shift+Ctrl+ArrowLeft"  },
    {kbhit::SHIFT_CTRL_ARROW_RIGHT,0x00001b5b313b3643,"Shift+Ctrl+ArrowRight" },
    {kbhit::SHIFT_CTRL_ARROW_UP   ,0x00001b5b313b3641,"Shift+Ctrl+ArrowUp"    },
    {kbhit::SHIFT_CTRL_ARROW_DOWN ,0x00001b5b313b3642,"Shift+Ctrl+ArrowDown"  },
    {kbhit::SHIFT_CTRL_DEL        ,0x00001b5b313b3646,"Shift+Ctrl+Del"        },
    {kbhit::SHIFT_CTRL_HOME       ,0x00001b5b313b3648,"Shift+Ctrl+Home"       },
    {kbhit::SHIFT_ALT_ARROW_LEFT  ,0x00001b5b313b3444,"Shift+Alt+ArrowLeft"   },
    {kbhit::SHIFT_ALT_ARROW_RIGHT ,0x00001b5b313b3443,"Shift+Alt+ArrowRight"  },
    {kbhit::SHIFT_ALT_ARROW_UP    ,0x00001b5b313b3441,"Shift+Alt+ArrowUp"     },
    {kbhit::SHIFT_ALT_ARROW_DOWN  ,0x00001b5b313b3442,"Shift+Alt+ArrowDown"   },
    {kbhit::SHIFT_ALT_END         ,0x00001b5b313b3446,"Shift+Alt+End"         },
    {kbhit::SHIFT_ALT_HOME        ,0x00001b5b313b3448,"Shift+Alt+Home"        },
    {kbhit::SHIFT_ALT_PAGE_UP     ,0x00001b5b353b347e,"Shift+Alt+PageUp"      },
    {kbhit::SHIFT_ALT_PAGE_DOWN   ,0x00001b5b363b347e,"Shift+Alt+PageDown"    },
    {kbhit::CTRL_ALT_ARROW_LEFT   ,0x00001b5b313b3744,"Ctrl+Alt+ArrowLeft"    },
    {kbhit::CTRL_ALT_ARROW_RIGHT  ,0x00001b5b313b3743,"Ctrl+Alt+ArrowRight"   },
    {kbhit::CTRL_ALT_ARROW_UP     ,0x00001b5b313b3741,"Ctrl+Alt+ArrowUp"      },
    {kbhit::CTRL_ALT_ARROW_DOWN   ,0x00001b5b313b3742,"Ctrl+Alt+ArrowDown"    },
    {kbhit::CHARACTER             ,0x0000000000000000,"CHAR INPUT"            }, ///< Never hit.


    //...
};



kbhit::operator bool() const
{
    return code != kbhit::NO_KEY;
}


kbhit kbhit::query(u64 code_seq)
{
    for (auto const &k : kbhit::keys_db)
        if (k.code == code_seq) return k;
    return NONE;
}


kbhit kbhit::query(std::string_view s)
{
    for (auto const&k : kbhit::keys_db)
        if (k.name == s)
            return k;
    return NONE;
}


} // namespace lus::io
