#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <OBB2D.h>
#include <vector>

/**
 * Train Component
 */
struct TrainComponent : public IComponent
{
    explicit TrainComponent(std::size_t eID) : IComponent{COMPONENT_TRAIN, eID} {};

    std::vector<OBB2D> bboxes;
    std::vector<SUMI::SUMIDrawableNode> nodes;

    // between 4 - 7
    int carriages;

    // Seconds to next train
    float timer;


    // true = top , false = bot
    bool line;
};