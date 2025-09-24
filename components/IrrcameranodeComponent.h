#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <SUMICameraNode.h>

/**
 * SUMI camera node
 */
struct IrrcameranodeComponent : public IComponent
{
    explicit IrrcameranodeComponent(std::size_t eID) : IComponent{COMPONENT_IRRCAMERANODE, eID} {};

    SUMI::SUMICameraNode node;
};