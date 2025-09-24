#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <string>

/**
 * Direction component
 *  Used to transforms absolute movement to relative movement
 */
struct DirectionComponent : public IComponent
{
    explicit DirectionComponent(std::size_t eID) : IComponent{COMPONENT_DIRECTION, eID} {};

    float direction{0};
    float zdirection{0};
};