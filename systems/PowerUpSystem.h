#pragma once
#include <GameStorage.h>
#include <EventManager.h>

using namespace TAKO;
struct PowerUpSystem
{
    void Update(GameStorage& gameStorage, const float frameDeltaTime, EventManager& eventManager, std::size_t player_ID);
};
