#pragma once
#include <GameStorage.h>
#include <EventManager.h>

struct EventJumpSystem {
    void Update(TAKO::GameStorage& gameStorage, TAKO::EventManager& eventManager);
    
    void prepareJump(TAKO::EventManager& eventManager, StaminaComponent* staminaComp, VelocityComponent* velocityComp);
    void simpleJump(TAKO::EventManager& eventManager, StaminaComponent* staminaComp, VelocityComponent* velocityComp, PowerUpComponent* powerUpComp);
    void doubleJump(TAKO::EventManager& eventManager, StaminaComponent* staminaComp, VelocityComponent* velocityComp, PowerUpComponent* powerUpComp);
};