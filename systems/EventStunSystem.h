#pragma once
#include <GameStorage.h>
#include <StunEvent.h>
#include <EventManager.h>
using namespace TAKO;
struct EventStunSystem
{
void Update(GameStorage& gameStorage, EventManager& eventManager, std::size_t player_ID);
};
