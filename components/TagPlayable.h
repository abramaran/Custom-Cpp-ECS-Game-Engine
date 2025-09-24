#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>

/**
 * Bounding box properties
 */
struct TagPlayable : public IComponent
{
    explicit TagPlayable(std::size_t eID) : IComponent{TAG_PLAYABLE, eID} {};
};