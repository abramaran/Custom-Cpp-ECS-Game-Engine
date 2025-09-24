#pragma once
#include <GameStorage.h>
#include <EventManager.h>
#include <StaminaUtils.h>

using namespace TAKO;
struct StaminaSystem
{
   void Update(GameStorage& gameStorage, TAKO::EventManager& eventManager, const float frameDeltaTime);
   float time{0};
   
   const float  StaminaRegenerationTime = 1;
   const float  StaminaRegeneration = 10;
   
};