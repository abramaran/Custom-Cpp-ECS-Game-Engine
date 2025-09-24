#include <EventHideHUDSystem.h>
#include <HideHUDEvent.h>

void EventHideHUDSystem::Update(GameStorage& gameStorage){
    for (auto& e : gameStorage.getEventsOfType<HideHUDEvent>()) {
        for(auto& HUDComp : gameStorage.getComponentsOfType<HUDComponent>()){
            HUDComp.Background_icon.setVisible(false);
            HUDComp.CurrentFist_icon.setVisible(false);
            HUDComp.Health_icon.setVisible(false);
            HUDComp.Health_base_icon.setVisible(false);
            HUDComp.Health_symbol_icon.setVisible(false);
            HUDComp.Power_up_icon.setVisible(false);
            HUDComp.PreviousFist_icon.setVisible(false);
            HUDComp.Stamina_icon.setVisible(false);
            HUDComp.Stamina_base_icon.setVisible(false);
            HUDComp.Stamina_symbol_icon.setVisible(false);
        }
    }
}
