#pragma once
#include <array>
#include <Vector3f.h>
#include <Vector2f.h>
#include <SUMIDrawableNode.h>

/**
 * Bounding box
 *  
 */
typedef struct{
    std::array<TAKO::Vector2f, 4> corner;
    std::array<TAKO::Vector2f, 2> axis;
    std::array<double, 2> origin;
    TAKO::Vector3f pos;
    TAKO::Vector3f rot;  
    SUMI::SUMIDrawableNode node;
}OBB2D;
