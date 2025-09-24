#pragma once
#include <GameStorage.h>

using namespace TAKO;
struct CameraOrbitSystem
{
    void Update(GameStorage& gameStorage,int playerID);

    private:
        const float PI      = 3.14159265359f; //same as irrlicht
        bool nextframe{false};
        //irrlicht uses 3.1415926535897932384626433832795028841971693993751 for 64 bits floats
};