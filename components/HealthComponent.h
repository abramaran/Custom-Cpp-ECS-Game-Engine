#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
/**
 * Total Health Points of an entity
 */
struct HealthComponent : public IComponent
{
    explicit HealthComponent(std::size_t eID) : IComponent{COMPONENT_HEALTH, eID} {};

    unsigned int HP;
};