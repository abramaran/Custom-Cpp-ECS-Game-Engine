#pragma once
#include <GameStorage.h>
using namespace TAKO;

struct RepositionBarSystem
{
    void Update(GameStorage& gameStorage, std::size_t enemyID);
};
