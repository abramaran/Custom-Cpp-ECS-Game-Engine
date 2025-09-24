#include <RespawnSystem.h>
#include <PlayerConstants.h>
#include <EndGameEvent.h>
#include <RefreshGUIBarsEvent.h>
void RespawnSystem::Update(GameStorage& gameStorage, EventManager& eventMg){
for(auto& healthComp : gameStorage.getComponentsOfType<HealthComponent>()) { 
    if(healthComp.HP == 0 ||healthComp.HP > MAX_HP){
        healthComp.HP = 0;
        eventMg.postEvent<EndGameEvent>();
        healthComp.HP == 0;

    }
}
}
