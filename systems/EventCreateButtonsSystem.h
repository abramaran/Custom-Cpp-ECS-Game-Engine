#pragma once
#include <GameStorage.h>
#include <EntityManager.h>

using namespace TAKO;
struct EventCreateButtonsSystem
{
   void Update(GameStorage& gameStorage, EntityManager& entManager);
};