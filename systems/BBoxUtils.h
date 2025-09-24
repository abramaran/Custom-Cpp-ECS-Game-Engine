#pragma once
#include <OBB2D.h>
#include <Vector3f.h>
#include <Vector2f.h>

namespace TAKO{
struct BBoxUtils
{
    static Vector3f rotatePoint(Vector3f p1, Vector3f p2, float angle);
    static void calculateBBox(OBB2D& body, const Vector3f& pos, const float rot, const int defaultBoxSize);
    static float get_degrees(float num);
    static void rotate(OBB2D& bbox,  Vector2f center, const float w, const float h, float angle);
    static void computeAxes(OBB2D& bbox);
};
}