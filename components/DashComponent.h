#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>

/**
 * Dash-related variables for playable entities.
 */
struct DashComponent : public IComponent
{
    explicit DashComponent(std::size_t eID) : IComponent{COMPONENT_DASH, eID} {};

    TAKO::Vector3f previousPos{TAKO::Vector3f(0,0,0)};
    TAKO::Vector3f previousVel{TAKO::Vector3f(0,0,0)};
    float dashCooldown{0};
    bool  dashing{false};
    bool  dashed{false};
};