#include <EventMovementSystem.h>
#include <PlayerConstants.h>

void EventMovementSystem::Update(TAKO::GameStorage& gameStorage) {
    for (auto& event : gameStorage.getEventsOfType<MovementEvent>()) {
        auto& entity = gameStorage.getEntity(event.entityID);
        /////////// Guards ////////////
        PowerUpComponent* powerUpComp = static_cast<PowerUpComponent*>(entity.require(COMPONENT_POWERUP));
        if (!powerUpComp || powerUpComp->stunned) continue;   // Being stunned means no moevement should be processed.
        VelocityComponent* velocityComp = static_cast<VelocityComponent*>(entity.require(COMPONENT_VELOCITY));
        if (!velocityComp) continue;
        DashComponent* dashComp = static_cast<DashComponent*>(entity.require(COMPONENT_DASH));
        if (!dashComp) continue;
        ///////////////////////////////

        uint32_t speed;
        if (velocityComp->jumping) {
            speed = MOVEMENT_SPEED_JMP;
        } else {
            speed = MOVEMENT_SPEED;
        }

        switch (event.direction) {
            case MovementDirection::forwards:
                velocityComp->vel.Z = speed + powerUpComp->ExtraVel;
                break;
            case MovementDirection::backwards:
                velocityComp->vel.Z = - (speed + powerUpComp->ExtraVel);
                break;
            case MovementDirection::left:
                if(!dashComp->dashing){
                    velocityComp->vel.X = speed + powerUpComp->ExtraVel;
                }
                break;
            case MovementDirection::right:
                if(!dashComp->dashing){
                    velocityComp->vel.X = - (speed + powerUpComp->ExtraVel);
                }
                break;
        }
    }
}
