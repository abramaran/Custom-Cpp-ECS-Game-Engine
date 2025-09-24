#pragma once
#include <GameStorage.h>
#include <EventManager.h>
#include <Entity.h>

using namespace TAKO;
struct PowerUpUtils
{
    static void setPowerUp(EventManager& eventManager, Entity& entity, PowerUpComponent* pl_powComp, PowerUpComponent* bx_powComp);
    static void  removePowerUpEffects(PowerUpComponent* powerUpComp);
};
