#pragma once
#include <GameStorage.h>

using namespace TAKO;
struct TrainSystem
{
    void Update(GameStorage& gameStorage, float frameDeltaTime);

    const float mult2 = 90;
    const float min = -17.020 * mult2;
    const float max = 17.176 * mult2;
    const float vel = 600;
    const unsigned distance = 240;

    const float topLine = -mult2 *2.114;
    const float botLine = -mult2 *1.146;

    const int variability = 5;
    const int baseValue = 5;


};