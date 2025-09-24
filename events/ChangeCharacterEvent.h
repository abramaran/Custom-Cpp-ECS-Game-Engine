#pragma once
#include <GameEnums.h>

struct ChangeCharacterEvent
{
    explicit ChangeCharacterEvent(Characters newChara, std::string path) : character{newChara}, texture{path}{};
    Characters character;
    std::string texture;
};