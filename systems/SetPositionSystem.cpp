#include <SetPositionSystem.h>

void SetPositionSystem::Update(GameStorage& gameStorage){

    for(auto& irrnodeComp : gameStorage.getComponentsOfType<IrranimatednodeComponent>()) { 
        auto& entity = gameStorage.getEntity(irrnodeComp.entityID);
        /////////// Guards ////////////
        PositionComponent* posComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!posComp) return;

        irrnodeComp.node.setPosition(posComp->pos);
    }
}
