#include <EventShowHUDSystem.h>
#include <ShowHUDEvent.h>
#include <GameEnums.h>

void EventShowHUDSystem::Update(GameStorage& gameStorage){
    for (auto& e : gameStorage.getEventsOfType<ShowHUDEvent>()) {
        for(auto& HUDComp : gameStorage.getComponentsOfType<HUDComponent>()){
            HUDComp.Background_icon.setVisible(true);
            HUDComp.CurrentFist_icon.setVisible(true);
            HUDComp.Health_icon.setVisible(true);
            HUDComp.Health_base_icon.setVisible(true);
            HUDComp.Health_symbol_icon.setVisible(true);
            HUDComp.PreviousFist_icon.setVisible(true);
            HUDComp.Stamina_icon.setVisible(true);
            HUDComp.Stamina_base_icon.setVisible(true);
            HUDComp.Stamina_symbol_icon.setVisible(true);

            auto& entity = gameStorage.getEntity(HUDComp.entityID);
            PowerUpComponent* pwupComp = static_cast<PowerUpComponent*>(entity.require(COMPONENT_POWERUP));
            if(pwupComp && pwupComp->pwup != PowerUpEnum::NO_P){     HUDComp.Power_up_icon.setVisible(true);     }
        }
    }
}
