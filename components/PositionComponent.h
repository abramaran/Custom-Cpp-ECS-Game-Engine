#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <Vector3f.h>

/**
 * Position component
 *  Position of the entity in world coordinates
 */
struct PositionComponent : public IComponent
{
    explicit PositionComponent(std::size_t eID) : IComponent{COMPONENT_POSITION, eID} {};

    TAKO::Vector3f pos;
    bool onFloor{true};
};