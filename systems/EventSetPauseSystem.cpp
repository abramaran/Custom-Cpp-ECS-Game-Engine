#include <EventSetPauseSystem.h>
#include <HideHUDEvent.h>
#include <BillboardUtils.h>

void EventSetPauseSystem::Update(GameStorage& gameStorage, EntityManager& entmanager){
    for (auto& e : gameStorage.getEventsOfType<HideHUDEvent>()) {
        for(auto& HUDComp : gameStorage.getComponentsOfType<HUDComponent>()){
            //TODO: add stamina and health final parts
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
