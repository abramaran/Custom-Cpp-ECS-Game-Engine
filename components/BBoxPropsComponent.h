#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <OBB2D.h>

/**
 * Bounding box properties
 */
struct BBoxPropsComponent : public IComponent
{
    explicit BBoxPropsComponent(std::size_t eID) : IComponent{COMPONENT_BBOX_PROPS, eID} {};

    OBB2D body;
};