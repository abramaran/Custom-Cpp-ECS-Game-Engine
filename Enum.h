#pragma once
#include <GameManager.h>
struct TkeyStruct{
    Key key;
    StateEnum state;
};
std::vector<TkeyStruct> TMappingMenuIni{
    {Key::KEY_ENTER , StateEnum::MENU},
    {Key::KEY_ESCAPE , StateEnum::CLOSING      }
};
std::vector<TkeyStruct> TMappingMenu{
    {Key::KEY_1     ,  StateEnum::START},  //    StateEnum::SELECNIVEL
    //{Key::KEY_2      , StateEnum::MULTIJUGADOR      }, //SALA?
    {Key::KEY_3      , StateEnum::OPCIONES      },
    {Key::KEY_4      , StateEnum::CREDITOS      }//,
    //{Key::KEY_ESCAPE , StateEnum::CLOSING      }
};

std::vector<TkeyStruct> TMappingOpciones{
    {Key::KEY_1      , StateEnum::CONTROLESPC    },
    {Key::KEY_2      , StateEnum::CONTROLESMANDO },
    {Key::KEY_ESCAPE , StateEnum::NO_STATE       }
};
std::vector<TkeyStruct> TMappingControles{
    {Key::KEY_ESCAPE , StateEnum::NO_STATE       }
};

std::vector<TkeyStruct> TMappingPausa {
    {Key::KEY_ESCAPE , StateEnum::MENU},
    {Key::KEY_1     ,  StateEnum::NO_STATE},
    {Key::KEY_2     ,  StateEnum::START},
    {Key::KEY_3     ,  StateEnum::OPCIONES}
};
std::vector<TkeyStruct> TMappingInGame{
    {Key::KEY_P     , StateEnum::PAUSA},
    {Key::KEY_R     , StateEnum::IN_GAME},
};

struct TStatestruct{
    StateEnum state; //cambiar eso a otra cosa
    void (GameManager::*pfuncUpdate)(); //puntero a funcion update
    void (GameManager::*pfuncRender)();
    std::vector<TkeyStruct> mapping;
};
TStatestruct mapping[] = {
    { StateEnum::IN_GAME           , &GameManager::UpdateInGame   , &GameManager::RenderInGame    , TMappingInGame                    },
    { StateEnum::MENUINICIAL       , &GameManager::UpdateMenu     , &GameManager::RenderMenu      , TMappingMenuIni      },
    { StateEnum::MENU              , &GameManager::UpdateMenu     , &GameManager::RenderMenu      , TMappingMenu         },
    { StateEnum::CONTROLESPC       , &GameManager::UpdateMenu     , &GameManager::RenderMenu      , TMappingControles    },
    { StateEnum::OPCIONES          , &GameManager::UpdateMenu     , &GameManager::RenderMenu      , TMappingOpciones     },
    { StateEnum::CONTROLESMANDO    , &GameManager::UpdateMenu     , &GameManager::RenderMenu      , TMappingControles    },
    { StateEnum::PAUSA             , &GameManager::UpdatePause    , &GameManager::RenderMenu      , TMappingPausa        },
    { StateEnum::CREDITOS          , &GameManager::UpdateMenu     , &GameManager::RenderMenu      , TMappingControles    },
   // {   StateEnum::YOU_WIN           , &GameManager::UpdateFin                  , &GameManager::RenderGanador               },
   // {   StateEnum::YOU_LOSE          , &GameManager::UpdateFin                  , &GameManager::RenderPerdedor              },
    {   StateEnum::NO_STATE          , 0                                        , 0                                         }
};