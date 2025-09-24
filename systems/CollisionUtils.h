#pragma once
#include <GameStorage.h>

namespace TAKO{
struct CollisionUtils
{

    static bool overlaps1Way(const OBB2D& one,const OBB2D& two);
    static bool overlaps(const OBB2D& one,const OBB2D& two);
    static bool collides(const OBB2D& bbox1, const OBB2D& bbox2);
    static bool collidesBueno(const OBB2D& bbox1, const OBB2D& bbox2);
    static Vector2f getYComponentsBBox(const OBB2D& bbox);
    static Vector2f getXComponentsBBox(const OBB2D& bbox);
    static Vector2f getZComponentsBBox(const OBB2D& bbox);
    static float getPlayerHeight(const OBB2D& bbox);
};
}