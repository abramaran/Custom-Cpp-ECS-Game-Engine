#pragma once
#include <GameEnums.h>

enum class typeEnum{
 state,
 character,
 level
};

struct Action{
    explicit Action(StateEnum st) : state{st}, type{typeEnum::state}{};
    explicit Action(Characters chara, std::string pth) : character{chara}, path{pth},  type{typeEnum::character}{};
    explicit Action(Levels lvl) : level{lvl}, type{typeEnum::level}{};

    StateEnum state;
    Characters character;
    std::string path;
    Levels     level;
    typeEnum   type;
};

struct TkeyStruct{
    Key key;
    Action action;
};
