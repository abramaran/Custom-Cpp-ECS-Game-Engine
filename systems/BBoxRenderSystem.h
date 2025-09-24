#pragma once
#include <GameStorage.h>
#include <SUMIEngine.h>

using namespace TAKO;
struct BBoxRenderSystem
{
    void Reset(GameStorage& gameStorage);
    void Update(GameStorage& gameStorage,const float frameDeltaTime, SUMI::SUMIEngine& receiver, bool& visibility);
    float time{0.f};
};