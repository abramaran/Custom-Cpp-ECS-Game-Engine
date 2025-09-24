#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <OBB2D.h>
#include <SUMIDrawableNode.h>

/**
 * Bounding box
 */
struct BBoxComponent : public IComponent
{
    explicit BBoxComponent(std::size_t eID) : IComponent{COMPONENT_BBOX, eID} {};

    OBB2D body;
    OBB2D vision;
    OBB2D rf; //Left Fist
    bool hrf; //Hit Right Fist
    bool hrfa {true}; //Hit Right Fist Already
    OBB2D lf; //Left Fist
    bool hlf; //Hit Left Fist
    bool hlfa {true}; //Hit Left Fist Already
    OBB2D block; //Blocking hitbox
    SUMI::SUMIDrawableNode areaHit;
};