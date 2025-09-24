#pragma once
#include <GameStorage.h>
#include <SUMIEngine.h>
#include <EventManager.h>
#include <GameEnums.h>
struct TkeyStruct;

using namespace TAKO;
using namespace SUMI;
struct InputMenuSystem
{
    void Update(GameStorage& gameStorage, EventManager& eventManager, SUMIEngine& receiver, float& frameDeltaTime, std::vector<TkeyStruct>& keymapping, bool& changeState, StateEnum& nextState);
    float keyTime {0.0f};
};
