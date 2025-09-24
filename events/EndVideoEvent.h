#pragma once
#include <GameEnums.h>

struct EndVideoEvent
{
    explicit EndVideoEvent(StateEnum state) : newState{state}{};
    StateEnum newState;
};
