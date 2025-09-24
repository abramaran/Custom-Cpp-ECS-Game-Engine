#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <cstdint>
/**
* Damage Value
*/
struct DamageComponent : public IComponent
{
explicit DamageComponent(std::size_t eID) : IComponent{COMPONENT_DAMAGE, eID} {};

    uint32_t Damage;
    size_t ownerID;
    float time{0};
};
