#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <SUMIAnimatedMeshNode.h>

/**
 *  Irrlicht animated node
 */
struct IrranimatednodeComponent : public IComponent
{
    explicit IrranimatednodeComponent(std::size_t eID) : IComponent{COMPONENT_IRRANIMATEDNODE, eID} {};
    ~IrranimatednodeComponent() {node.remove();};

    SUMI::SUMIAnimatedMeshNode node;
};