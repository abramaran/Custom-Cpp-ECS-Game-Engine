#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>

/**
 * Component ai
 */
struct AIComponent : public IComponent
{
    explicit AIComponent(std::size_t eID) : IComponent{COMPONENT_AI, eID} {};

    int state;
};