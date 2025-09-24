#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <GameEnums.h>
/**
 * Store player values when online
 */
struct NextStateComponent  : public IComponent
{
    explicit NextStateComponent(std::size_t eID) : IComponent{COMPONENT_NEXTSTATE, eID} {};
    StateEnum state;
};