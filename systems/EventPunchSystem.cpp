#include <EventPunchSystem.h>
#include <StaminaUtils.h>
#include <PlayerConstants.h>

void EventPunchSystem::Update(TAKO::GameStorage& gameStorage, TAKO::EntityManager& entManager, TAKO::EventManager& eventManager, float deltatime) {
    for (auto& event : gameStorage.getEventsOfType<PunchEvent>()) {
        auto& entity = gameStorage.getEntity(event.entityID);
        /////////// Guards ////////////
        PowerUpComponent* powerUpComp = static_cast<PowerUpComponent*>(entity.require(COMPONENT_POWERUP));
        if (!powerUpComp || powerUpComp->stunned) continue;   // Being stunned means no moevement should be processed.
        FistComponent* fistComp = static_cast<FistComponent*>(entity.require(COMPONENT_FIST));
        if (!fistComp) continue;
        StaminaComponent* staminaComp = static_cast<StaminaComponent*>(entity.require(COMPONENT_STAMINA));
        if (!staminaComp) continue;
        BBoxComponent* bboxComp = static_cast<BBoxComponent*>(entity.require(COMPONENT_BBOX));
        if (!bboxComp) continue;
        VelocityComponent* velocityComp = static_cast<VelocityComponent*>(entity.require(COMPONENT_VELOCITY));
        if (!velocityComp) continue;
        SoundComponent* soundComp = static_cast<SoundComponent*>(entity.require(COMPONENT_SOUND));
        if (!soundComp) return;
        ///////////////////////////////

        if (event.fist == FistAction::block) {
            velocityComp->blocking = true;
        } else {
            if (velocityComp->jumping) {
                // Process ground-pound
                if(event.fist != FistAction::resetTimer && staminaComp->stamina >= FALLINGHIT_DAMAGE && velocityComp->minYDist > RANGE_DOWN && velocityComp->minYDist != 10000){
                    velocityComp->vel.Y = FALLING_VEL;
                    velocityComp->hitDown = true;
                    velocityComp->vel.X = velocityComp->vel.Z = 0;
                }
                velocityComp->minYDist = 10000;
                fistComp->timerUppercut = 0;
            } else {
                // Process punches
                if (event.fist == FistAction::right) {
                    if(!bboxComp->hrf && bboxComp->hrfa){
                        bboxComp->hrf = punch(eventManager, soundComp, fistComp, staminaComp, "R", deltatime); 
                        bboxComp->hrfa = false;
                    }
                } else {
                    bboxComp->hrf = false;
                    bboxComp->hrfa = false;

                    if (event.fist == FistAction::left) {
                        if(!bboxComp->hlf && bboxComp->hlfa){
                            bboxComp->hlf =  punch(eventManager, soundComp, fistComp, staminaComp, "L", deltatime);   
                            bboxComp->hlfa = false;
                        }
                    } else {
                        bboxComp->hlf = false;
                        bboxComp->hlfa = false;

                        fistComp->timerUppercut = 0;
                    }
                }
            }
        }
    }
}

bool EventPunchSystem::punch(TAKO::EventManager& eventManager, SoundComponent* soundComp, FistComponent* fistComp, StaminaComponent* staminaComp, std::string LorR, float frameDeltatime){
   //if the player is jumping 
    switch (fistComp->currentFist)
    {
    case FistEnum::DIRECT:
        soundComp->event="event:/Character/DirectAir";
        soundComp->play=true;
        if(staminaComp->stamina >= DIRECTFIST_STAMINA){
            StaminaUtils::decrementStamina(eventManager, staminaComp, DIRECTFIST_STAMINA);
            return true;
        }
        break;
    case FistEnum::CROCHET:
        soundComp->event="event:/Character/CrochetAir";
        soundComp->play=true;
        if(staminaComp->stamina >= CROCHETFIST_STAMINA){
            StaminaUtils::decrementStamina(eventManager, staminaComp, CROCHETFIST_STAMINA);
            return true;
        }
        break;
    case FistEnum::UPPERCUT:
        if(fistComp->timerUppercut >= fistComp->CHARGE_UPPERCUT_TIME) {
            if (staminaComp->stamina >= UPPERCUTFIST_STAMINA) {
                soundComp->event="event:/Character/UpperCutAir";
                soundComp->play=true;
                eventManager.postEvent<ChangeAnimationEvent>(staminaComp->entityID, "UppercutRelease" + LorR);
                StaminaUtils::decrementStamina(eventManager, staminaComp, UPPERCUTFIST_STAMINA);
                return true;
            }
        } else {
            fistComp->timerUppercut += frameDeltatime;
        }
        break;
    default:
        break;
    }
    return false;
}
