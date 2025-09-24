#pragma once
#include <PlayerConstants.h>
#include <GameStorage.h>

using namespace TAKO;
struct ConveyorBeltSystem
{
    void Update(GameStorage& gameStorage, const float frameDeltaTime);


    const float mult = 2.5;
    const float mult2 = mult *30;
    const float distance = 0.475 * mult2;
    const float max = distance * -22;
    const float vel = distance;
    const TAKO::Vector3f posInitL = TAKO::Vector3f(-mult2 *-0.021, mult2 *0.044, -mult2 *-7.986);
    const TAKO::Vector3f posInitR = TAKO::Vector3f(-mult2 *1.35, mult2 *0.044, -mult2 *2.218);


};