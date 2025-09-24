#include <StaminaSystem.h>
#include <PlayerConstants.h>
#include <StaminaUtils.h>

void StaminaSystem::Update(GameStorage& gameStorage, TAKO::EventManager& eventManager, const float frameDeltaTime){
    time += frameDeltaTime;
    if(time >= StaminaRegenerationTime){
        time = 0;
        for (auto& staminaComp : gameStorage.getComponentsOfType<StaminaComponent>()) {
            StaminaUtils::addStamina(eventManager, &staminaComp,StaminaRegeneration);
        }
    }
}