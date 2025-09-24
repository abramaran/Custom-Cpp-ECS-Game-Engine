#pragma once
#include <GameStorage.h>
#include <GameEnums.h>
struct EventEndVideo
{
    void Update(GameStorage& gameStorage, bool& changeState, StateEnum& nextState);
};
