#pragma once
#include <GameManager.h>
#include <GameEnums.h>
#include <StateStruct.h>

std::vector<TkeyStruct> TMappingMenuIni{
    {Key::KEY_ENTER ,  Action{StateEnum::MENU}},
    {Key::KEY_ESCAPE , Action{StateEnum::CLOSING}}
};

std::vector<TkeyStruct> TMappingMenu{
    {Key::KEY_1      , Action{StateEnum::SELECNIVEL}},  //    StateEnum::SELECNIVEL
    {Key::KEY_2      , Action{StateEnum::OPCIONESSALA}}, //SALA? <-- Aún no
    {Key::KEY_3      , Action{StateEnum::OPCIONES     }},
    {Key::KEY_4      , Action{StateEnum::CREDITOS     }},
    {Key::KEY_5      , Action{StateEnum::CLOSING      }},
    {Key::KEY_ESCAPE , Action{StateEnum::CLOSING     }}
};
std::vector<TkeyStruct> TMappingOpciones{
    {Key::KEY_1      , Action{StateEnum::CONTROLESPC    }},
    {Key::KEY_2      , Action{StateEnum::CONTROLESMANDO }},
    {Key::KEY_ESCAPE , Action{StateEnum::NO_STATE       }}
};
std::vector<TkeyStruct> TMappingControles{
    {Key::KEY_ESCAPE , Action{StateEnum::NO_STATE       }}
};
std::vector<TkeyStruct> TMappingCreditosMenu{
    {Key::KEY_ESCAPE , Action{StateEnum::NO_STATE        }},
    {Key::KEY_1      ,  Action{StateEnum::COMIC_MENU     }},
    {Key::KEY_2      ,  Action{StateEnum::VIDEO_CREDITOS }},
};
std::vector<TkeyStruct> TMappingPausa {
    {Key::KEY_ESCAPE ,  Action{StateEnum::MENU     }},
    {Key::KEY_1      ,  Action{StateEnum::NO_STATE }},
    {Key::KEY_2      ,  Action{StateEnum::START    }},
    {Key::KEY_3      ,  Action{StateEnum::OPCIONES }},
    {Key::KEY_4      ,  Action{StateEnum::MENU     }}

};
std::vector<TkeyStruct> TMappingInGame{
    {Key::KEY_ESCAPE     , Action{StateEnum::PAUSA  }},
    //{Key::KEY_R     , Action{StateEnum::IN_GAME}},
};
std::vector<TkeyStruct> TMappingWinSimgle{
    //{Key::KEY_1         , StateEnum:: },  //SIGUIENTE NIVEL
    {Key::KEY_2         , Action{StateEnum::START     }},
    {Key::KEY_3         , Action{StateEnum::SELECNIVEL}}, 
    {Key::KEY_ESCAPE    , Action{StateEnum::MENU      }}
};
std::vector<TkeyStruct> TMappingLoseSimgle{
    {Key::KEY_1         , Action{StateEnum::START  }},  
    //{Key::KEY_2         , StateEnum:: },  //SIGUIENTE NIVEL
    {Key::KEY_ESCAPE    , Action{StateEnum::MENU   }}
};
std::vector<TkeyStruct> TMappingWinMulti{
    //{Key::KEY_1         , StateEnum:: },  //SIGUIENTE NIVEL
    {Key::KEY_2         , Action{StateEnum::START  }},
    //{Key::KEY_3         , StateEnum::}, //SELECCIONAR NIVEL
    {Key::KEY_ESCAPE    , Action{StateEnum::MENU   }}
};
std::vector<TkeyStruct> TMappingLoseMulti{
    {Key::KEY_1         , Action{StateEnum::START  }},  
    //{Key::KEY_2         , StateEnum:: },  //SIGUIENTE NIVEL
    {Key::KEY_ESCAPE    , Action{StateEnum::MENU   }}
};

std::vector<TkeyStruct> TMappingSelectNivel{
    {Key::KEY_ENTER     , Action{StateEnum::START  }},
    {Key::KEY_ESCAPE    , Action{StateEnum::MENU   }},
    {Key::KEY_1         , Action{Levels::STATION   }},
    {Key::KEY_2         , Action{Levels::FACTORY   }}
};

std::vector<TkeyStruct> TMappingOpcionesSala{
    {Key::KEY_1         , Action{StateEnum::CREARSALA }},
    {Key::KEY_2         , Action{StateEnum::BUSCARSALA}},
    {Key::KEY_ESCAPE    , Action{StateEnum::MENU      }}
};
std::vector<TkeyStruct> TMappingCrearSala{
    //{Key::KEY_ENTER     , StateEnum::STARTMULTI  },
    {Key::KEY_ESCAPE    , Action{StateEnum::NO_STATE }}
};

std::vector<TkeyStruct> TMappingBuscarSala{
    {Key::KEY_ENTER     , Action{StateEnum::SELECNIVELESPERA  }},
    {Key::KEY_ESCAPE    , Action{StateEnum::NO_STATE }}
};

std::vector<TkeyStruct> TMappingSelectChara{
    {Key::KEY_ENTER      , Action{StateEnum::STARTMULTI}},
    {Key::KEY_ESCAPE     , Action{StateEnum::NO_STATE }} ,
    {Key::KEY_1          , Action{Characters::PUNCHIES,"media/Menu/Portraits/Punchies.png" }},
    {Key::KEY_2          , Action{Characters::BOSS1 ,"media/Menu/Portraits/BOSS1.png"}},
    {Key::KEY_3          , Action{Characters::BOSS2 ,"media/Menu/Portraits/BOSS2.png"}}
};

std::vector<TkeyStruct> TMappingComicGameVideo{
    {Key::KEY_ENTER     , Action{StateEnum::LOAD_SCREEN}}
};

std::vector<TkeyStruct> TMappingCreditosVideo{
    {Key::KEY_ENTER     , Action{StateEnum::NO_STATE}}
};
std::vector<TkeyStruct> TMappingLogo{
    {Key::NO_KEY     , Action{StateEnum::MENUINICIAL}}
};

std::vector<TkeyStruct> TMappingComicVideo{
    {Key::KEY_ENTER     , Action{StateEnum::NO_STATE}}
};
std::vector<TkeyStruct> TMappingComicmenu{
    {Key::KEY_ESCAPE     , Action{StateEnum::NO_STATE}},
    {Key::KEY_1          , Action{Levels::STATION}},
    {Key::KEY_2          , Action{Levels::FACTORY}},
    {Key::KEY_ENTER      , Action{StateEnum::VIDEO_COMIC}}

};
std::vector<TkeyStruct> TMappingEmpty{};

struct TStatestruct{
    StateEnum state; //cambiar eso a otra cosa
    void (GameManager::*pfuncUpdate)(); //puntero a funcion update
    void (GameManager::*pfuncRender)();
    std::vector<TkeyStruct> mapping;
};
//the commented maps are used for debugging ande
TStatestruct mapping[] = {
    { StateEnum::IN_GAME           , &GameManager::UpdateInGame            , &GameManager::RenderInGame    , TMappingInGame                              },
    { StateEnum::IN_GAMEMULTI      , &GameManager::UpdateInMultiplayer     , &GameManager::RenderInGame    , TMappingEmpty /*TMappingInGame*/            },
    { StateEnum::LOGO              , &GameManager::UpdateVideo             , &GameManager::RenderMenu      , TMappingLogo                                },
    { StateEnum::COMIC_GAME        , &GameManager::UpdateVideo             , &GameManager::RenderMenu      , TMappingComicGameVideo                      },
    { StateEnum::MENUINICIAL       , &GameManager::UpdateMenu              , &GameManager::RenderMenu      , TMappingMenuIni                             },
    { StateEnum::MENU              , &GameManager::UpdateMenu              , &GameManager::RenderMenu      , TMappingEmpty /*TMappingMenu*/              },
    { StateEnum::CONTROLESPC       , &GameManager::UpdatePause             , &GameManager::RenderMenu      , TMappingEmpty /*TMappingControles*/         },
    { StateEnum::OPCIONES          , &GameManager::UpdatePause             , &GameManager::RenderMenu      , TMappingEmpty /*TMappingOpciones*/          },
    { StateEnum::CONTROLESMANDO    , &GameManager::UpdatePause             , &GameManager::RenderMenu      , TMappingEmpty /*TMappingControles*/         },
    { StateEnum::PAUSA             , &GameManager::UpdatePause             , &GameManager::RenderMenu      , TMappingEmpty /*TMappingPausa*/             },
    { StateEnum::CREDITOS          , &GameManager::UpdateMenu              , &GameManager::RenderMenu      , TMappingEmpty /*TMappingCreditosMenu*/      },
    { StateEnum::VIDEO_CREDITOS    , &GameManager::UpdateVideo             , &GameManager::RenderMenu      , TMappingCreditosVideo                       },
    { StateEnum::VIDEO_COMIC       , &GameManager::UpdateVideo             , &GameManager::RenderMenu      , TMappingComicGameVideo                       },
    { StateEnum::YOU_WIN_S         , &GameManager::UpdateMenu              , &GameManager::RenderMenu      , TMappingEmpty /*TMappingWinSimgle*/         },
    { StateEnum::YOU_LOSE_S        , &GameManager::UpdateMenu              , &GameManager::RenderMenu      , TMappingEmpty /*TMappingLoseSimgle*/        },
    { StateEnum::YOU_WIN_M         , &GameManager::UpdateMenu              , &GameManager::RenderMenu      , TMappingEmpty /*TMappingWinSimgle*/         },
    { StateEnum::YOU_LOSE_M        , &GameManager::UpdateMenu              , &GameManager::RenderMenu      , TMappingEmpty /*TMappingLoseSimgle*/        },
    { StateEnum::SELECNIVEL        , &GameManager::UpdateMenuSelection     , &GameManager::RenderMenu      , TMappingEmpty /*TMappingSelectNivel*/       },
    { StateEnum::SELECPERSONAJE    , &GameManager::UpdateMenuSelection     , &GameManager::RenderMenu      , TMappingEmpty /*TMappingSelectChara*/       },
    { StateEnum::SELECPERSONAJE_M  , &GameManager::UpdateMenuRoomChar      , &GameManager::RenderMenu      , TMappingEmpty /*TMappingSelectChara*/       },
    { StateEnum::OPCIONESSALA      , &GameManager::UpdateMenu              , &GameManager::RenderMenu      , TMappingEmpty /*TMappingOpcionesSala*/      },
    { StateEnum::CREARSALA         , &GameManager::UpdateMenuRoomC         , &GameManager::RenderMenu      , TMappingEmpty /*TMappingCrearSala*/         },
    { StateEnum::BUSCARSALA        , &GameManager::UpdateMenuRoomS         , &GameManager::RenderMenu      , TMappingEmpty /*TMappingBuscarSala*/        },
    { StateEnum::SELECNIVELESPERA  , &GameManager::UpdateMenuRoomWait      , &GameManager::RenderMenu      , TMappingEmpty /*TMappingEmpty*/             },
    { StateEnum::SELECNIVEL_M      , &GameManager::UpdateMenuRoomStage     , &GameManager::RenderMenu      , TMappingEmpty /*TMappingSelectNivel*/       },
    { StateEnum::COMIC_MENU        , &GameManager::UpdateMenuSelection     , &GameManager::RenderMenu      , TMappingEmpty /*TMappingComicmenu*/         },
    { StateEnum::LOAD_SCREEN       , &GameManager::UpdateLoadScreen        , &GameManager::RenderMenu      , TMappingEmpty                               },
    { StateEnum::NO_STATE          , 0                                     , 0                             , TMappingEmpty                               }
};