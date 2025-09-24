#include <EventDestroyButtonsSystem.h>
#include <GameEnums.h>
#include <DestroyButtonsEvent.h>

void EventDestroyButtonsSystem::Update(GameStorage& gameStorage, EntityManager& entManager){

    for (auto& event : gameStorage.getEventsOfType<DestroyButtonsEvent>()) {
        auto& vectorComp =  gameStorage.getComponentsOfType<NextStateComponent>();
        for(auto i = 0; i < vectorComp.size(); i = 0){
            entManager.destroyEntity(vectorComp[i].entityID);
        }

        auto& vectorbackgroundComp =  gameStorage.getComponentsOfType<TagMenuBackground>();
        for(auto i = 0; i < vectorbackgroundComp.size(); i = 0){
            entManager.destroyEntity(vectorbackgroundComp[i].entityID);
        }
    }
}