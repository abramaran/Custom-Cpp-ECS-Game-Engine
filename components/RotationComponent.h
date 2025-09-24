#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <Vector3f.h>

/**
 * Rotation component
 *  Rotation of the entity in world coordinates
 */
struct RotationComponent : public IComponent
{
    explicit RotationComponent(std::size_t eID) : IComponent{COMPONENT_ROTATION, eID} {};

    TAKO::Vector3f rot;
};