#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <OBB2D.h>

/**
 * Bounding box
 */
struct SlopeComponent : public IComponent
{
    explicit SlopeComponent(std::size_t eID) : IComponent{COMPONENT_SLOPE, eID} {};

    OBB2D body;

    bool axis; // True = X False = Z
    bool positiveSense; // True = + False = -

};