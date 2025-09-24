#pragma once
#include <GameStorage.h>
#include <SUMIEngine.h>

using namespace TAKO;
using namespace SUMI;
struct EventChangeLevelSystem
{
    void Update(GameStorage& gameStorage, SUMIEngine& engine, Levels& level);
};
