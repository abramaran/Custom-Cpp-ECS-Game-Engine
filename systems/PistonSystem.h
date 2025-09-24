#pragma once
#include <GameStorage.h>
#include <EventManager.h>
#include <CollisionUtils.h>

using namespace TAKO;
struct PistonSystem
{
    void Update(GameStorage& gameStorage, const float frameDeltaTime);

    private:
        const float defaulScale = 4;
        const float maxScale = 20; // cambiar también en collision playable system
        const float pistonSpeed = 5;
};