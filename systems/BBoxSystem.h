#pragma once
#include <GameStorage.h>

using namespace TAKO;
struct BBoxSystem
{
    void Update(GameStorage& gameStorage);

    private:
        const int defaultBoxSize = 10;
        const int fistLocation = defaultBoxSize/2 + 1;
        const int fistLocationY = 22;

};