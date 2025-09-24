#include <PowerUpSystem.h>
#include <GameEnums.h>
#include <algorithm>
#include <PlayerConstants.h>
#include <CameraConstants.h>
#include <PowerUpEndEvent.h>
#include <CameraUtils.h>

void PowerUpSystem::Update(GameStorage& gameStorage, const float frameDeltaTime, EventManager& eventManager, std::size_t player_ID) {
    for (auto& powerUpComp : gameStorage.getComponentsOfType<PowerUpComponent>()) {
        /////////// Guards ////////////
        auto& entity = gameStorage.getEntity(powerUpComp.entityID);

        if(!entity.require(TAG_PLAYABLE)) continue;

        if(powerUpComp.pwup != PowerUpEnum::NO_P){
            powerUpComp.pwupTime-=frameDeltaTime;
            if(powerUpComp.pwupTime < 0) powerUpComp.pwupTime = 0;
            
            powerUpComp.pwupCooldown-=frameDeltaTime;
            if(powerUpComp.pwupCooldown < 0) powerUpComp.pwupCooldown = 0;
            if(powerUpComp.pwupTime <= 0){
                //no more power-up 
                eventManager.postEvent<PowerUpEndEvent>(entity.id);
            }
        }

        if(powerUpComp.stunned){
            powerUpComp.stunnedCooldown-=frameDeltaTime;
            if(powerUpComp.stunnedCooldown < 0) powerUpComp.stunnedCooldown = 0;
            if(powerUpComp.stunned && powerUpComp.stunnedCooldown == 0){
                powerUpComp.stunnedCooldown = 0;
                powerUpComp.stunned = false;
                if(entity.id == player_ID){
                    CameraUtils::setCameraVel(gameStorage,CAMERA_VEL_REGULAR);
                }
            }

        }
    }
}
