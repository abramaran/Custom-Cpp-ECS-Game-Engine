#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <Vector3f.h>

/**
 * Distance
 *  Distance between the camera and the player
 */
struct DistanceComponent : public IComponent
{
    explicit DistanceComponent(std::size_t eID) : IComponent{COMPONENT_DISTANCE, eID} {};

    TAKO::Vector3f distance;
};