#pragma once
#include <GameStorage.h>
#include <SUMIEngine.h>

struct EventChangeFistSystem {
    void Update(TAKO::GameStorage& gameStorage, SUMI::SUMIEngine& engine);
    void cycleThroughFists(int cycle, FistComponent* fistComp);
};