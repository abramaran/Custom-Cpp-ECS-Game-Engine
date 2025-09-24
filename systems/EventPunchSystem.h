#pragma once
#include <GameStorage.h>
#include <EntityManager.h>
#include <EventManager.h>

struct EventPunchSystem {
    void Update(TAKO::GameStorage& gameStorage, TAKO::EntityManager& entManager, TAKO::EventManager& eventManager, float deltatime);
    bool punch(TAKO::EventManager& eventManager, SoundComponent* soundComp, FistComponent* fistComp, StaminaComponent* staminaComp, std::string LorR, float frameDeltatime);
};