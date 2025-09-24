#pragma once
#include <GameStorage.h>
#include <EntityManager.h>
using namespace TAKO;
struct RespawnBoxSystem
{
    void Update(int playerID, GameStorage& gameStorage, const float frameDeltaTime, EntityManager& entManager, bool online);
};