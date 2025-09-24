#include <EventEndGameSystem.h>
#include <EventPowerUpEndSystem.h>
#include <PowerUpUtils.h>
//TODO: rename system
void EventPowerUpEndSystem::Update(GameStorage& gameStorage){
    for (auto& e : gameStorage.getEventsOfType<PowerUpEndEvent>()) {
        auto& entity = gameStorage.getEntity(e.id);
        PowerUpComponent* powerUpComp = static_cast<PowerUpComponent*>(entity.require(COMPONENT_POWERUP));
        if (!powerUpComp) continue;

        PowerUpUtils::removePowerUpEffects(powerUpComp);

        powerUpComp->pwupCooldown = 0;
        powerUpComp->pwupTime = 0;

        HUDComponent* HUDComp = static_cast<HUDComponent*>(entity.require(COMPONENT_HUD));
        if (!HUDComp) continue;
        HUDComp->Power_up_icon.setVisible(false);
    }
}
