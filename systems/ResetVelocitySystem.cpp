#include <ResetVelocitySystem.h>

void ResetVelocitySystem::Update(TAKO::GameStorage& gameStorage) {
    for (auto& tagPlayable : gameStorage.getComponentsOfType<TagPlayable>()) {
        auto& entity = gameStorage.getEntity(tagPlayable.entityID);
        /////////// Guards ////////////
        VelocityComponent* velocityComp = static_cast<VelocityComponent*>(entity.require(COMPONENT_VELOCITY));
        if (!velocityComp) return;
        DashComponent* dashComp = static_cast<DashComponent*>(entity.require(COMPONENT_DASH));
        if (!dashComp || dashComp->dashing || velocityComp->hitAir) return;
        ///////////////////////////////
        velocityComp->vel.X = velocityComp->vel.Z = 0;
        velocityComp->blocking = false;
    }
}
