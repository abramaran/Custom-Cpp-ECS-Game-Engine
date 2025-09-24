#include <RespawnBoxSystem.h>
#include <PlayerConstants.h>
#include <Vector3f.h>

using namespace TAKO;

void RespawnBoxSystem::Update(int playerID, GameStorage& gameStorage, const float frameDeltaTime, EntityManager& entManager, bool online){
    /////////// Guards ////////////
    auto& playerEntity = gameStorage.getEntity(playerID);
    NetComponent* pl_netComp = static_cast<NetComponent*>(playerEntity.require(COMPONENT_NET));
    if (!pl_netComp) return;
    //////////////////////////////

    if(pl_netComp->OnlineID==0){

    for(auto& spawnPointComp : gameStorage.getComponentsOfType<SpawnPointsComponent>()) { 
        spawnPointComp.time += frameDeltaTime;

        if(spawnPointComp.time >= SPAWN_PWBOX_TIME){
            spawnPointComp.time = 0;
            if(spawnPointComp.numBoxes < MAX_PWBOXES){
                //A number between 0 and MAX_PWBOXES of power-up boxes are created
                int auxnumboxes = MAX_PWBOXES - spawnPointComp.numBoxes; //maximum of boxes that can be generated
                int numpw = std::rand()%(auxnumboxes + 1);         //actual number of boxes to be generated
                if(numpw > 0){
                    spawnPointComp.numBoxes += numpw;
                    //The type and position are randomply generated inside the EntityManager class
                    //We just pass the number of boxes to generate
                    entManager.generatePowerUp(numpw, spawnPointComp.positions, online);
                }
            }
        }
    }
    }

}

