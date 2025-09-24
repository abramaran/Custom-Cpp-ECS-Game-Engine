#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <OBB2D.h>

/**
 * Bounding box properties
 */
struct BBoxCameraComponent : public IComponent
{
    explicit BBoxCameraComponent(std::size_t eID) : IComponent{COMPONENT_BBOX_CAMERA, eID} {};

    OBB2D body;
};