#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>

/**
 * Component description
 */
struct ShowNumberComponent : public IComponent
{
    explicit ShowNumberComponent(std::size_t eID) : IComponent{COMPONENT_SHOWNUMBER, eID} {};

    int numberindex;
};