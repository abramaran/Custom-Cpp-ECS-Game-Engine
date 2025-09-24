#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <Vector3f.h>

/**
 * LookAt component
 *  Position where the entity points to
 */
struct LookAtComponent : public IComponent
{
    explicit LookAtComponent(std::size_t eID) : IComponent{COMPONENT_LOOKAT, eID} {};

    TAKO::Vector3f lkat;  
};