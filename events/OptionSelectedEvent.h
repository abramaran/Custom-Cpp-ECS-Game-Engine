#pragma once
#include <GameEnums.h>

struct OptionSelectedEvent
{
   explicit OptionSelectedEvent(StateEnum* state, bool* changeState) : nextState{state}, changeState{changeState} {};
   StateEnum* nextState;
   bool* changeState;
};