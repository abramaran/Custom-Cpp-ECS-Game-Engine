#pragma once
#include <GameEnums.h>
struct CreateButtonsEvent
{
    explicit CreateButtonsEvent(StateEnum state) : state{state} {};
    StateEnum state;
};