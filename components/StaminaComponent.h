#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>

/**
 * Stamina points of a playable entity.
 */
struct StaminaComponent : public IComponent
{
    explicit StaminaComponent(std::size_t eID) : IComponent{COMPONENT_STAMINA, eID} {};

    float stamina;
};