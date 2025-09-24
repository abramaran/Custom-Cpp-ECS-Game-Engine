#include <EventChangeLevelSystem.h>

void EventChangeLevelSystem::Update(TAKO::GameStorage& gameStorage, SUMIEngine& engine, Levels& level){
    for (auto& event : gameStorage.getEventsOfType<ChangeLevelEvent>()) {
        level = event.level;
        for(auto& changelvlButtonComp : gameStorage.getComponentsOfType<SelectLevelComponent>()){
            auto& entity = gameStorage.getEntity(changelvlButtonComp.entityID);
            IrrbasicnodeComponent* basicNodeComp = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
            if(!basicNodeComp) continue;
            MouseOverComponent* mouseNodeComp = static_cast<MouseOverComponent*>(entity.require(COMPONENT_MOUSEOVER));
            if(!mouseNodeComp) continue;
            
            if(changelvlButtonComp.selectedLevel == level){
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
