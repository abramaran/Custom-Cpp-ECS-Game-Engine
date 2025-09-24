#include <EventChangeFistSystem.h>
#include <ChangeFistEvent.h>
#include <GameEnums.h>
#include <algorithm>
#include <SUMIDrawableNode.h>
#include <string>

void changeFistIcon(FistEnum fist, SUMI::SUMIDrawableNode& HUDbox, SUMI::SUMIEngine& engine){
    std::string a;

    switch(fist){
        case FistEnum::DIRECT:
            engine.changeMaterial(HUDbox, "media/HUD/hud_directo.png");
            break;
        case FistEnum::CROCHET:
            engine.changeMaterial(HUDbox, "media/HUD/hud_crochet.png");
            break;
        case FistEnum::UPPERCUT:
            engine.changeMaterial(HUDbox, "media/HUD/hud_gancho.png");
            break;
    }
}
void EventChangeFistSystem::Update(TAKO::GameStorage& gameStorage, SUMI::SUMIEngine& engine) {
    for (auto& event : gameStorage.getEventsOfType<ChangeFistEvent>()) {
        auto& entity = gameStorage.getEntity(event.entityID);
        /////////// Guards ////////////
        FistComponent* fistComp = static_cast<FistComponent*>(entity.require(COMPONENT_FIST));
        if (!fistComp) continue;
        ///////////////////////////////

        if (event.fist) {
            if (fistComp->currentFist != *event.fist) {
                fistComp->previousFist = fistComp->currentFist;
                fistComp->currentFist = *event.fist;
            }
        } else if (event.cycle) {
            cycleThroughFists(*event.cycle, fistComp);
        } else {
            std::swap(fistComp->currentFist, fistComp->previousFist);
        }   
        /////////// Guards ////////////
        HUDComponent* hudComp = static_cast<HUDComponent*>(entity.require(COMPONENT_HUD));
        if (!hudComp) continue;
        ///////////////////////////////
        changeFistIcon(fistComp->currentFist,hudComp->CurrentFist_icon,engine);     
        changeFistIcon(fistComp->previousFist,hudComp->PreviousFist_icon,engine);     

    }
}

void EventChangeFistSystem::cycleThroughFists(int cycle, FistComponent* fistComp) {
    FistEnum newFist{};

    if(cycle > 0){
        switch (fistComp->currentFist) {
            case FistEnum::DIRECT:
                newFist = FistEnum::CROCHET;
                break;
            case FistEnum::CROCHET:
                newFist = FistEnum::UPPERCUT;
                break;
            case FistEnum::UPPERCUT:
                newFist = FistEnum::DIRECT;
                break;
        }
    } else {
        switch (fistComp->currentFist) {
            case FistEnum::DIRECT:
                newFist = FistEnum::UPPERCUT;
                break;
            case FistEnum::CROCHET:
                newFist = FistEnum::DIRECT;
                break;
            case FistEnum::UPPERCUT:
                newFist = FistEnum::CROCHET;
                break;
        } 
    }

    fistComp->previousFist = fistComp->currentFist;
    fistComp->currentFist = newFist;
}