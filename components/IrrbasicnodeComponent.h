#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <SUMIDrawableNode.h>

/**
 * Irrlicht basic node
 */
struct IrrbasicnodeComponent : public IComponent
{
    explicit IrrbasicnodeComponent(std::size_t eID) : IComponent{COMPONENT_IRRBASICNODE, eID} {};
    ~IrrbasicnodeComponent() {node.remove();};

    SUMI::SUMIDrawableNode node;
};