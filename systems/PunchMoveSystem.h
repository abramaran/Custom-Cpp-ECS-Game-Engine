#pragma once
#include <GameStorage.h>

using namespace TAKO;

struct PunchMoveSystem
{
    void Update(GameStorage& gameStorage);

    private:
        const int defaultBoxSize = 10;
        const int fistLocation = defaultBoxSize/2 + 1;
        const float range = defaultBoxSize;

};