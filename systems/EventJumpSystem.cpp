#include <EventJumpSystem.h>
#include <PlayerConstants.h>
#include <StaminaUtils.h>

void EventJumpSystem::Update(TAKO::GameStorage& gameStorage, TAKO::EventManager& eventManager) {
    for (auto& event : gameStorage.getEventsOfType<JumpEvent>()) {
        auto& entity = gameStorage.getEntity(event.entityID);
        /////////// Guards ////////////
        PowerUpComponent* powerUpComp = static_cast<PowerUpComponent*>(entity.require(COMPONENT_POWERUP));
        if (!powerUpComp || powerUpComp->stunned) continue;   // Being stunned means no moevement should be processed.
        StaminaComponent* staminaComp = static_cast<StaminaComponent*>(entity.require(COMPONENT_STAMINA));
        if (!staminaComp) continue;
        VelocityComponent* velocityComp = static_cast<VelocityComponent*>(entity.require(COMPONENT_VELOCITY));
        if (!velocityComp) continue;
        ///////////////////////////////

        if (staminaComp->stamina >= JUMP_STAMINA) {
            if (velocityComp->jumping) {
                doubleJump(eventManager, staminaComp, velocityComp, powerUpComp);
            } else {
                simpleJump(eventManager, staminaComp, velocityComp, powerUpComp);
            }
        }
    }
}

void EventJumpSystem::prepareJump(TAKO::EventManager& eventManager, StaminaComponent* staminaComp, VelocityComponent* velocityComp) {
    StaminaUtils::decrementStamina(eventManager, staminaComp, JUMP_STAMINA);
    velocityComp->vel.Y = JUMP_SPEED;
    velocityComp->vel.X /= 2;
    velocityComp->vel.Z /= 2;       
}

void EventJumpSystem::simpleJump(TAKO::EventManager& eventManager, StaminaComponent* staminaComp, VelocityComponent* velocityComp, PowerUpComponent* powerUpComp) {
    prepareJump(eventManager, staminaComp, velocityComp);
    velocityComp->jumping = true;
    if(powerUpComp->pwup == PowerUpEnum::DOUBLE_JUMP){
        powerUpComp->pwupCooldown = JUMP_COOLDOWN;
    }
}

void EventJumpSystem::doubleJump(TAKO::EventManager& eventManager, StaminaComponent* staminaComp, VelocityComponent* velocityComp, PowerUpComponent* powerUpComp) {
    if(powerUpComp->pwupCooldown == 0 && powerUpComp->pwup == PowerUpEnum::DOUBLE_JUMP && !velocityComp->doublejumping){
        prepareJump(eventManager, staminaComp, velocityComp);
        velocityComp->doublejumping = true;
    }
}