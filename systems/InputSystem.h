#pragma once
#include <StaminaUtils.h>
#include <math.h>
#include <EntityManager.h>
#include <EventManager.h>

struct Tkeystruct;
struct InputSystem {
    void Update(TAKO::EventManager& eventManager, SUMI::SUMIEngine& receiver, int playerID, bool online);

    private:
    bool isFKeyDown{false};
    FistAction lastFist{FistAction::resetTimer};
};


