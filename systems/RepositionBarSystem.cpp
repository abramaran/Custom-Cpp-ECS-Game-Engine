#include <RepositionBarSystem.h>
#include<SUMIDrawableNode.h>
#include<BillboardUtils.h>

void RepositionBarSystem::Update(GameStorage& gameStorage, std::size_t enemyID)
{
    auto& entity = gameStorage.getEntity(enemyID);
    for (auto& healthBarComp : gameStorage.getComponentsOfType<HealthBarComponent>()) {
        PositionComponent* posComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!posComp) break;

        healthBarComp.Health_bar.setPosition(posComp->pos);
        healthBarComp.Health_bar.move(Vector3f(0,45,0));

    }
}