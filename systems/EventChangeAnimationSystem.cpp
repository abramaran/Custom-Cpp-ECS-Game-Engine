#include <EventChangeAnimationSystem.h>

void EventChangeAnimationSystem::Update(TAKO::GameStorage& gameStorage) {
    for (auto& event : gameStorage.getEventsOfType<ChangeAnimationEvent>()) {
        ///////////// Guards ////////////
        auto& entity = gameStorage.getEntity(event.entityID);
        IrranimatednodeComponent* animNodeComp = static_cast<IrranimatednodeComponent*>(entity.require(COMPONENT_IRRANIMATEDNODE));
        if (!animNodeComp) continue;
        /////////////////////////////////
        animNodeComp->node.changeToAnimation(event.newAnimation);
    }
};
