#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <GameEnums.h>

/**
 * Selected Character Component
 *  Choosed character by the player, in single player is punchies default
 */
struct SelectCharacterComponent : public IComponent
{
    explicit SelectCharacterComponent(std::size_t eID) : IComponent{COMPONENT_SELECTEDCHARACTER, eID} {};

    Characters selectedCharacter;
    std::string texturepath;
};