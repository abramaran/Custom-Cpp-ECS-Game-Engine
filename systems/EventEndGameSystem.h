#pragma once
#include <GameStorage.h>
#include <SUMIEngine.h>
#include <stack>
#include <GameEnums.h>
#include <EventManager.h>

using namespace TAKO;
struct EventEndGameSystem
{
    void Update(GameStorage& gameStorage, bool& changeState, StateEnum& nextState);
};
