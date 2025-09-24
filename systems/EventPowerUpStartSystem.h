#pragma once
#include <GameStorage.h>
#include <EventManager.h>
#include <EntityManager.h>
#include <SUMIEngine.h>

using namespace TAKO;
struct EventPowerUpStartSystem
{
    void Update(int playerID, GameStorage& gameStorage, TAKO::EventManager& eventManager, EntityManager& entManager, SUMI::SUMIEngine& engine);
};
