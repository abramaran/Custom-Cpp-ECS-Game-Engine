#include <PowerUpUtils.h>
#include <PlayerConstants.h>
void PowerUpUtils::setPowerUp(EventManager& eventManager, Entity& entity, PowerUpComponent* pl_powComp, PowerUpComponent* bx_powComp){
    pl_powComp->pwup = bx_powComp->pwup;
    // stun and double jump are not necessary here
    switch (pl_powComp->pwup) {
        case PowerUpEnum::DEFENSE:   
            pl_powComp->ExtraDef = exDef;
            break;
        case PowerUpEnum::DAMAGE:
            pl_powComp->ExtraDamage = exDam;
            break;
        case PowerUpEnum::VELOCITY:
            pl_powComp->ExtraVel = exVel;      
            break;
        case PowerUpEnum::HEALTH:
        {
            HealthComponent* healthComp = static_cast<HealthComponent*>(entity.require(COMPONENT_HEALTH));
            if (!healthComp) break;

            healthComp->HP += exHP;
            if(healthComp->HP > MAX_HP) healthComp->HP = MAX_HP;
            eventManager.postEvent<RefreshGUIBarsEvent>(entity.id);
            break;
        }
        case PowerUpEnum::ESTAMINA:
        {
            StaminaComponent* staminaComp = static_cast<StaminaComponent*>(entity.require(COMPONENT_STAMINA));
            if (!staminaComp) break;

            staminaComp->stamina += exEst;
            if(staminaComp->stamina > MAX_STAMINA) staminaComp->stamina = MAX_STAMINA;
            eventManager.postEvent<RefreshGUIBarsEvent>(entity.id);
        }
        break;
        default:
        {
        }
    break;
    }
    pl_powComp->pwupTime = bx_powComp->pwupTime; 
}

void PowerUpUtils::removePowerUpEffects(PowerUpComponent* powerUpComp){
    switch ( powerUpComp->pwup )
    {
        case PowerUpEnum::DEFENSE:
            powerUpComp->ExtraDef = 0;
            break;
        case PowerUpEnum::DAMAGE:
            powerUpComp->ExtraDamage = 0;
            break;
        case PowerUpEnum::VELOCITY:
            powerUpComp->ExtraVel = 0;
            break;
        default:
            break;
    }
    powerUpComp->pwup = PowerUpEnum::NO_P;
}