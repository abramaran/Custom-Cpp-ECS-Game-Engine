#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>

/**
 * Bounding box properties
 */
struct TagMenuBackground : public IComponent
{
    explicit TagMenuBackground(std::size_t eID) :  IComponent{TAG_MENUBACKGROUND, eID} {};
};