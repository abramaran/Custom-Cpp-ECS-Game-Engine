#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <OBB2D.h>

/**
 * Bounding box
 */
struct PistonComponent : public IComponent
{
    explicit PistonComponent(std::size_t eID) : IComponent{COMPONENT_PISTON, eID} {};

    SUMI::SUMIDrawableNode node;

    bool activated1;
    bool activated2;
    bool up;
    bool down;
    float timer;
};