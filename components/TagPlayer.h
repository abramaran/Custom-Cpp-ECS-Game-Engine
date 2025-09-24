#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>

/**
 * Bounding box properties
 */
struct TagPlayer : public IComponent
{
    explicit TagPlayer(std::size_t eID) : IComponent{TAG_PLAYER, eID} {};
};