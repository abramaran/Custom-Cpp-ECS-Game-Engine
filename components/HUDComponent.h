#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <SUMIDrawableNode.h>
/**
 * Component ai
 */
using namespace SUMI;
struct HUDComponent : public IComponent
{
    explicit HUDComponent(std::size_t eID) : IComponent{COMPONENT_HUD, eID} {};

    SUMIDrawableNode Power_up_icon;
    SUMIDrawableNode Health_icon;
    SUMIDrawableNode Health_base_icon;
    SUMIDrawableNode Health_symbol_icon;
    SUMIDrawableNode Stamina_icon;
    SUMIDrawableNode Stamina_base_icon;
    SUMIDrawableNode Stamina_symbol_icon;
    SUMIDrawableNode CurrentFist_icon;
    SUMIDrawableNode PreviousFist_icon;
    SUMIDrawableNode Background_icon;

    float MAX_WIDTH_HEALTH = 0.27;
    float MAX_WIDTH_STAMINA = 0.23;
};