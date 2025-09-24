#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <Vector3f.h>

/**
 * Velocity component
 *  Velocity of the entity in units/second
 */
struct VelocityComponent : public IComponent
{
    explicit VelocityComponent(std::size_t eID) : IComponent{COMPONENT_VELOCITY, eID} {};

    TAKO::Vector3f knockback;
    TAKO::Vector3f vel;

    //TODO: mirar donde deberian estar estas variables.
    float minYDist;
    bool hitDown;
    bool blocking; 
    
    bool jumping;
    bool doublejumping;

    bool onBelt {false};

    bool hitAir{false};
    float speedBelt {0};
};