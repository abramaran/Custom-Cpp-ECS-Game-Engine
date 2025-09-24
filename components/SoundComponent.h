#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>

/**
 * Component description
 */
struct SoundComponent : public IComponent
{
    explicit SoundComponent(std::size_t eID) : IComponent{COMPONENT_SOUND, eID} {};

    std::string event;
    bool play;
};