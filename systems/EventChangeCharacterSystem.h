#pragma once
#include <GameStorage.h>
#include <SUMIEngine.h>

using namespace TAKO;
using namespace SUMI;

struct EventChangeCharacterSystem
{
    void Update(GameStorage& gameStorage, SUMIEngine& engine, Characters& characters);
};
