#pragma once
#include <GameEnums.h>
using namespace TAKO;
struct ChangeLevelEvent
{
    explicit ChangeLevelEvent(Levels newLevel) : level{newLevel} {};
    Levels level;
};