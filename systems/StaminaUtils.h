#pragma once
#include <StaminaComponent.h>
#include <EventManager.h>

struct StaminaUtils
{
    static void decrementStamina(TAKO::EventManager& eventManager, StaminaComponent* pl_staminaComp, float stAction);
    static void addStamina(TAKO::EventManager& eventManager, StaminaComponent* pl_staminaComp, float stAction);

};