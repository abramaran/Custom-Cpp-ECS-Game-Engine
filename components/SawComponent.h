#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>

/**
 * Component description
 */
struct SawComponent : public IComponent
{
    explicit SawComponent(std::size_t eID) : IComponent{COMPONENT_SAW, eID} {};

    std::vector<SUMI::SUMIDrawableNode> nodes;

    // true = x, false = z
    bool axis;

    // true = positive, false = negative
    bool sense;

    float rot{0};

    OBB2D bbox;
};