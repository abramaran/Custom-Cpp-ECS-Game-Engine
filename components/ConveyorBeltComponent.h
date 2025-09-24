#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>

/**
 * Component description
 */
struct ConveyorBeltComponent : public IComponent
{
    explicit ConveyorBeltComponent(std::size_t eID) : IComponent{COMPONENT_CONVEYOR_BELT, eID} {};

    // true = x, false = z
    bool axis;

    // true = positive, false = negative
    bool sense;

    OBB2D bbox;

    std::vector<SUMI::SUMIDrawableNode> nodes;

    float increment{0};

};