#pragma once
#include <GameStorage.h>
#include <EntityManager.h>

using namespace TAKO;
struct EventDestroyButtonsSystem
{
    void Update(GameStorage& gameStorage, EntityManager& entManager);
};
