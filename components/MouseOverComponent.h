#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <OBB2D.h>

/**
 * Bounding box
 */
struct MouseOverComponent : public IComponent
{
    explicit MouseOverComponent(std::size_t eID) : IComponent{COMPONENT_MOUSEOVER, eID} {};
    bool isover{false};
    bool selected{false};
    std::string notSelectedTexture;
    std::string SeletctedTexture;
};