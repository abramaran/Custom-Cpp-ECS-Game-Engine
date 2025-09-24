#include <EventPowerUpStartSystem.h>
#include <PowerUpStartEvent.h>
#include <PowerUpUtils.h>

#include <iostream>

void EventPowerUpStartSystem::Update(int playerID, GameStorage& gameStorage, EventManager& eventManager, EntityManager& entManager, SUMI::SUMIEngine& engine) {
    /////////// Guards ////////////
    auto& playerEntity = gameStorage.getEntity(playerID);
    NetComponent* pl_netComp = static_cast<NetComponent*>(playerEntity.require(COMPONENT_NET));
    if (!pl_netComp) return;
    //////////////////////////////

    //if(pl_netComp->OnlineID==0)
    for (auto& e : gameStorage.getEventsOfType<PowerUpStartEvent>()) {
        for(auto& spawnPointComp : gameStorage.getComponentsOfType<SpawnPointsComponent>()) { 
            auto& playable_ent = gameStorage.getEntity(e.id_playable);
            auto& powerup_box_ent = gameStorage.getEntity(e.id_pw);


            PowerUpComponent* pl_powComp = static_cast<PowerUpComponent*>(playable_ent.require(COMPONENT_POWERUP));
            if (!pl_powComp) continue;
            PowerUpComponent* bx_powComp = static_cast<PowerUpComponent*>(powerup_box_ent.require(COMPONENT_POWERUP));
            if (!bx_powComp) continue;


            PowerUpUtils::removePowerUpEffects(pl_powComp);
            PowerUpUtils::setPowerUp(eventManager, playable_ent, pl_powComp, bx_powComp);

            HUDComponent* pl_hudComp = static_cast<HUDComponent*>(playable_ent.require(COMPONENT_HUD));
            if (pl_hudComp && pl_powComp->pwup != PowerUpEnum::NO_P)
            {
                pl_hudComp->Power_up_icon.setVisible(true);
                engine.changeMaterial(pl_hudComp->Power_up_icon,bx_powComp->icon_path);    //Change HUD icon to current power-up;
            }
            --spawnPointComp.numBoxes;
            spawnPointComp.positions[bx_powComp->generatedPos].first = false;          //indicate that the postion it's not being used
            entManager.destroyEntity(e.id_pw);                                  //delete power-up box  
        }
    }
}


