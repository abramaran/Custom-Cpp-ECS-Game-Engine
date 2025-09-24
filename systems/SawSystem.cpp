#include <SawSystem.h>

void SawSystem::Update(GameStorage& gameStorage){

    for(auto& sawComp : gameStorage.getComponentsOfType<SawComponent>()) { 
        auto& entity = gameStorage.getEntity(sawComp.entityID);
        /////////// Guards ////////////
        PositionComponent* posComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!posComp) return;

        for (size_t i = 0; i < sawComp.nodes.size(); i++)
        {
            float rotDelta = sawComp.rot;
            rotDelta += velRot;
            if(i % 2 != 0) rotDelta *= -1;

            TAKO::Vector3f rot = sawComp.nodes[i].getRotation();

            sawComp.nodes[i].setRotation(TAKO::Vector3f(rotDelta, rot.Y, rot.Z));
        }

        sawComp.rot += velRot;
        
    }
}
