#include <StaminaUtils.h>
#include <StaminaComponent.h>
#include <PlayerConstants.h>
#include <EventManager.h>


void StaminaUtils::decrementStamina(TAKO::EventManager& eventManager, StaminaComponent* pl_staminaComp, float stAction){
    pl_staminaComp->stamina -= stAction;
    if( pl_staminaComp->stamina < 0){
        pl_staminaComp->stamina = 0;
    }
    eventManager.postEvent<RefreshGUIBarsEvent>(pl_staminaComp->entityID);
}
void StaminaUtils::addStamina(TAKO::EventManager& eventManager, StaminaComponent* pl_staminaComp, float stAction){
    pl_staminaComp->stamina += stAction;
    if( pl_staminaComp->stamina > MAX_STAMINA){
        pl_staminaComp->stamina = MAX_STAMINA;
    }
    eventManager.postEvent<RefreshGUIBarsEvent>(pl_staminaComp->entityID);
}
