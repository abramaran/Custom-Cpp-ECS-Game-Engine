#pragma once
#include <GameStorage.h>
#include <EventManager.h>

struct EventDashSystem {
    void Update(TAKO::GameStorage& gameStorage, TAKO::EventManager& eventManager);
    void prepareDash(TAKO::EventManager& eventManager, DashComponent* dashComp, StaminaComponent* staminaComp, VelocityComponent* velocityComp, PositionComponent* posComp);
};