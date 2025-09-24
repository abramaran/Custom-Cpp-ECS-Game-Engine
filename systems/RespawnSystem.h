#pragma once
#include <GameStorage.h>
#include <GameEnums.h>
#include <SUMIDrawableNode.h>
#include <EventManager.h>
using namespace TAKO;
struct RespawnSystem
{
   void Update(GameStorage& gameStorage, EventManager& eventMg);
};
