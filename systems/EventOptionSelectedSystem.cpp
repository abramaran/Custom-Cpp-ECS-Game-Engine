#include <EventOptionSelectedSystem.h>
#include <OptionSelectedEvent.h>

void EventOptionSelectedSystem::Update(TAKO::GameStorage& gameStorage, EventManager& eventManager){
    for (auto& event : gameStorage.getEventsOfType<OptionSelectedEvent>()) {
        for (auto& mouseOverComp : gameStorage.getComponentsOfType<MouseOverComponent>()) {
            //////////////////////////////////////////////////////
            auto& entity = gameStorage.getEntity(mouseOverComp.entityID);
            NetComponent* netComp = static_cast<NetComponent*>(entity.require(COMPONENT_NET));
            if (!netComp) return;
            //////////////////////////////////////////////////////
            //If the confirm button is disable, skip this entity (true by default for other buttons)
            if(netComp->codeReady==true){
                if(mouseOverComp.isover){
                    if(netComp->statelessbutton==true){
                        netComp->statelessclick=true;
                    }
                    NextStateComponent* nextStateComp = static_cast<NextStateComponent*>(entity.require(COMPONENT_NEXTSTATE));
                    if (nextStateComp){
                        *event.changeState = true;
                        *event.nextState =  nextStateComp->state;
                        break;
                    }
                    SelectLevelComponent* nextLevelComp = static_cast<SelectLevelComponent*>(entity.require(COMPONENT_SELECTEDLEVEL));
                    if(nextLevelComp){
                        eventManager.postEvent<ChangeLevelEvent>(nextLevelComp->selectedLevel);
                        break;
                    }
                    SelectCharacterComponent* nextCharaComp = static_cast<SelectCharacterComponent*>(entity.require(COMPONENT_SELECTEDCHARACTER));
                    if(nextCharaComp){
                        eventManager.postEvent<ChangeCharacterEvent>(nextCharaComp->selectedCharacter, nextCharaComp->texturepath);
                        break;
                    }
                }
            }
        }
    }
}
