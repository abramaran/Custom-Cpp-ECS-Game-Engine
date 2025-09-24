#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <GameEnums.h>
#include <string>
/**
 * Selected Level Component
 *  Choosed level by the player
 */
struct SelectLevelComponent : public IComponent
{
    explicit SelectLevelComponent(std::size_t eID) : IComponent{COMPONENT_SELECTEDLEVEL, eID} {};
    Levels selectedLevel{Levels::STATION};
};