#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <SUMIDrawableNode.h>

using namespace SUMI;

struct HealthBarComponent : public IComponent
{
    explicit HealthBarComponent(std::size_t eID) : IComponent{COMPONENT_HEALTHBAR, eID} {};
    
    SUMIDrawableNode Health_bar;

    float MAX_WIDTH_HEALTH = 0.05;
 
};
