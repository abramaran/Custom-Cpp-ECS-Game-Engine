#pragma once
#include <GameStorage.h>
#include <SUMIEngine.h>
#include <EventManager.h>
#include <GameEnums.h>

using namespace TAKO;
using namespace SUMI;

struct InputClickSystem
{
    void Update(GameStorage& gameStorage, EventManager& eventManager, SUMIEngine& receiver, float& frameDeltaTime, bool& changeState, StateEnum& nextState);
    float keyTime {0.0f};
};
