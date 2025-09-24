#pragma once
#include <GameStorage.h>

using namespace TAKO;
struct MoveSystem
{
    void Update(GameStorage& gameStorage,const float deltaTime);
    float get_degrees(float num);
    Vector3f rotatePoint(Vector3f p1, Vector3f p2, float angle);

    private:
        const float GRAVITY = 8; 
        const float PI      = 3.14159265359f; //same as irrlicht
        const float sqrtTwo = 1.141;
        //irrlicht uses 3.1415926535897932384626433832795028841971693993751 for 64 bits floats
};
