#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <GameEnums.h>
/**
 * Fist component
 */
struct FistComponent : public IComponent
{
    explicit FistComponent(std::size_t eID) : IComponent{COMPONENT_FIST, eID} {};

    FistEnum currentFist{FistEnum::DIRECT};
    FistEnum previousFist{FistEnum::CROCHET};

    float timerUppercut {0};
    bool currentlyCharging {false};

    float CHARGE_UPPERCUT_TIME {0.7};
};