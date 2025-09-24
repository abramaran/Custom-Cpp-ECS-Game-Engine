#include <EventDashSystem.h>
#include <PlayerConstants.h>
#include <StaminaUtils.h>

void EventDashSystem::Update(TAKO::GameStorage& gameStorage, TAKO::EventManager& eventManager) {
    for (auto& event : gameStorage.getEventsOfType<DashEvent>()) {
        auto& entity = gameStorage.getEntity(event.entityID);
        /////////// Guards ////////////
        PowerUpComponent* powerUpComp = static_cast<PowerUpComponent*>(entity.require(COMPONENT_POWERUP));
        if (!powerUpComp || powerUpComp->stunned) continue;   // Being stunned means no moevement should be processed.
        DashComponent* dashComp = static_cast<DashComponent*>(entity.require(COMPONENT_DASH));
        if (!dashComp) continue;
        StaminaComponent* staminaComp = static_cast<StaminaComponent*>(entity.require(COMPONENT_STAMINA));
        if (!staminaComp) continue;
        VelocityComponent* velocityComp = static_cast<VelocityComponent*>(entity.require(COMPONENT_VELOCITY));
        if (!velocityComp) continue;
        PositionComponent* positionComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!positionComp) continue;
        ///////////////////////////////

        if(!velocityComp->jumping){
            dashComp->dashed = false;
        }

        int sign;
        if (event.direction == DashDirection::right) {
            sign = -1;
        } else {
            sign = 1;
        }
    
        if(dashComp->dashCooldown == 0 && staminaComp->stamina >= DASH_STAMINA && !dashComp->dashed){
            prepareDash(eventManager, dashComp,staminaComp,velocityComp,positionComp);
            dashComp->dashed = true;
            velocityComp->vel.X = sign * (DASH_SPEED + powerUpComp->ExtraVel);
        }   
    }
}

void EventDashSystem::prepareDash(TAKO::EventManager& eventManager, DashComponent* dashComp, StaminaComponent* staminaComp, VelocityComponent* velocityComp, PositionComponent* posComp){
    dashComp->previousVel = velocityComp->vel;
    dashComp->previousPos = posComp->pos;
    velocityComp->vel.Y = 0;
    velocityComp->vel.Z = 0;
    dashComp->dashCooldown = DASH_COOLDOWN;
    dashComp->dashing = true;
    StaminaUtils::decrementStamina(eventManager, staminaComp, DASH_STAMINA);
}