#include <BillboardUtils.h>

void BillboardUtils::ResetBillboard(GameStorage& gameStorage, SUMIDrawableNode& Billboardnode){
    for(auto& cameraComponent : gameStorage.getComponentsOfType<IrrcameranodeComponent>()) { 
        /////////// Guards ////////////
        auto& entity = gameStorage.getEntity(cameraComponent.entityID);
        PositionComponent* posComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        LookAtComponent* lookComp = static_cast<LookAtComponent*>(entity.require(COMPONENT_LOOKAT));
        ///////////////////////////////


        posComp->pos = glm::vec3(0.0f, 0.0f, 1.0f);
        lookComp->lkat = glm::vec3(0,0,0);
        cameraComponent.node.setPosition(posComp->pos);
        cameraComponent.node.setTarget(lookComp->lkat);
        Billboardnode.setVisible(true);
        Billboardnode.setPosition(lookComp->lkat);
    }
}
