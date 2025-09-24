#pragma once
#include <GameStorage.h>
#include <SUMIEngine.h>
#include <EntityManager.h>

using namespace TAKO;
using namespace SUMI;

struct EventSetPauseSystem
{
    void Update(GameStorage& gameStorage, EntityManager& entmanager);
};
