#include <EventChangeCharacterSystem.h>

void EventChangeCharacterSystem::Update(GameStorage& gameStorage, SUMIEngine& engine, Characters& characters){
    for (auto& event : gameStorage.getEventsOfType<ChangeCharacterEvent>()) {
        characters = event.character;
        for(auto &tagplayer : gameStorage.getComponentsOfType<TagPlayer>()){
            auto& entity = gameStorage.getEntity(tagplayer.entityID);

            IrrbasicnodeComponent* basicnodeComp = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
            if (!basicnodeComp) continue;

            engine.changeMaterial(basicnodeComp->node, event.texture);

        }
        for(auto& changecharaButtonComp : gameStorage.getComponentsOfType<SelectCharacterComponent>()){
            auto& entity = gameStorage.getEntity(changecharaButtonComp.entityID);
            IrrbasicnodeComponent* basicNodeComp = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
            if(!basicNodeComp) continue;
            MouseOverComponent* mouseNodeComp = static_cast<MouseOverComponent*>(entity.require(COMPONENT_MOUSEOVER));
            if(!mouseNodeComp) continue;

            if(changecharaButtonComp.selectedCharacter == characters){
                mouseNodeComp->selected = true;
                engine.changeMaterial(basicNodeComp->node, mouseNodeComp->SeletctedTexture);
            }
            else{
                mouseNodeComp->selected = false;
                engine.changeMaterial(basicNodeComp->node, mouseNodeComp->notSelectedTexture);
            }
        }
    }
}