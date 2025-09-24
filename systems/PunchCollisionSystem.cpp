#include <PunchCollisionSystem.h>
#include <GameEnums.h>
#include <CameraConstants.h>
#include <StunEvent.h>

void PunchCollisionSystem::Update(GameStorage& gameStorage, EventManager& eventManager, const bool visibility){ //16, 160, 161
    for (auto& bboxComp : gameStorage.getComponentsOfType<BBoxComponent>()){
        auto& entity = gameStorage.getEntity(bboxComp.entityID);
        /////////// Guards ////////////
        PowerUpComponent* powerupComp = static_cast<PowerUpComponent*>(entity.require(COMPONENT_POWERUP));
        if (!powerupComp) continue;
        FistComponent* fistComp = static_cast<FistComponent*>(entity.require(COMPONENT_FIST));
        if (!fistComp) continue;
        VelocityComponent* velocityComp = static_cast<VelocityComponent*>(entity.require(COMPONENT_VELOCITY));
        if (!velocityComp) continue;
        PositionComponent* positionComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!positionComp) continue;
        DamageFeedbackComponent* damagefeedbackComp = static_cast<DamageFeedbackComponent*>(entity.require(COMPONENT_DAMAGEFEEDBACK));
        if (!damagefeedbackComp) continue;
        HealthComponent* heathComp = static_cast<HealthComponent*>(entity.require(COMPONENT_HEALTH));
        if (!heathComp) continue;
        StaminaComponent* staminaComp = static_cast<StaminaComponent*>(entity.require(COMPONENT_STAMINA));
        if (!staminaComp) continue;
        IrranimatednodeComponent* animNodeComp = static_cast<IrranimatednodeComponent*>(entity.require(COMPONENT_IRRANIMATEDNODE));
        if (!animNodeComp) continue;
        SoundComponent* soundComp = static_cast<SoundComponent*>(entity.require(COMPONENT_SOUND));
        if (!soundComp) continue;
        ///////////////////////////////

        for(auto& bboxComp2 : gameStorage.getComponentsOfType<BBoxComponent>()){
            auto& entity2 = gameStorage.getEntity(bboxComp2.entityID);

            if(entity.id < entity2.id ){
                /////////// Guards ////////////
                PowerUpComponent* powerupComp2 = static_cast<PowerUpComponent*>(entity2.require(COMPONENT_POWERUP));
                if (!powerupComp2) continue;
                FistComponent* fistComp2 = static_cast<FistComponent*>(entity2.require(COMPONENT_FIST));
                if (!fistComp2) continue;
                VelocityComponent* velocityComp2 = static_cast<VelocityComponent*>(entity2.require(COMPONENT_VELOCITY));
                if (!velocityComp2) continue;
                PositionComponent* positionComp2 = static_cast<PositionComponent*>(entity2.require(COMPONENT_POSITION));
                if (!positionComp2) continue;
                DamageFeedbackComponent* damagefeedbackComp2 = static_cast<DamageFeedbackComponent*>(entity2.require(COMPONENT_DAMAGEFEEDBACK));
                if (!damagefeedbackComp2) continue;
                HealthComponent* heathComp2 = static_cast<HealthComponent*>(entity2.require(COMPONENT_HEALTH));
                if (!heathComp2) continue;
                StaminaComponent* staminaComp2 = static_cast<StaminaComponent*>(entity2.require(COMPONENT_STAMINA));
                if (!staminaComp2) continue;
                IrranimatednodeComponent* animNodeComp2 = static_cast<IrranimatednodeComponent*>(entity2.require(COMPONENT_IRRANIMATEDNODE));
                if (!animNodeComp2) continue;
                SoundComponent* soundComp2 = static_cast<SoundComponent*>(entity2.require(COMPONENT_SOUND));
                if (!soundComp2) continue;
                ///////////////////////////////

                detectCollisionPunch(gameStorage, eventManager, visibility, soundComp, soundComp2, staminaComp,staminaComp2,fistComp,fistComp2,powerupComp,powerupComp2,&bboxComp,&bboxComp2,velocityComp,velocityComp2,positionComp,positionComp2,damagefeedbackComp,damagefeedbackComp2,heathComp,heathComp2, animNodeComp, animNodeComp2);
            }
        }
    }
}
int PunchCollisionSystem::detectPunchDamage(FistComponent* fistComponent){
    int damage = 0;
    //TODO  si está en el aire que se salte el switch y que haga otra cosa
    switch (fistComponent->currentFist)
    {
        case FistEnum::DIRECT:
            damage = DIRECTFIST_DAMAGE;
            break;
        case FistEnum::CROCHET:
            damage = CROCHETFIST_DAMAGE;
            break;
        case FistEnum::UPPERCUT:
            damage = UPPERCUTFIST_DAMAGE; 
            break;
        default:
            break;
    }
    return damage;
}


/**
 * Check if bboxComponent1's fists are hitting bboxComponent2.
 */
std::pair<int, bool> PunchCollisionSystem::detect1Way(TAKO::EventManager& eventManager, const float dist, const bool visibility,bool& contact, SoundComponent* soundComp, DamageFeedbackComponent* dmgComponentVictim, FistComponent* fistComp, BBoxComponent* bboxComponentAttacker, BBoxComponent* bboxComponentVictim, StaminaComponent* staminaCompAttacker, StaminaComponent* staminaCompVictim,PowerUpComponent* powerupComp, PowerUpComponent* powerupComp2,VelocityComponent* velocityCompAttacker, VelocityComponent* velocityCompVictim, IrranimatednodeComponent* animNodeComponentAttacker){
    int damage = detectPunchDamage(fistComp) + powerupComp2->ExtraDamage;
    int totdmg = 0;
    OBB2D* fistHit{nullptr};

    if(!bboxComponentAttacker->hlfa && bboxComponentAttacker->hlf){
        if(CollisionUtils::collidesBueno(bboxComponentAttacker->lf, bboxComponentVictim->body) && powerupComp2->pwup != PowerUpEnum::CANON){
            //totdmg += damage - powerupComp2->ExtraDef;
            totdmg += damage - powerupComp->ExtraDef;  
            contact = true;
            dmgComponentVictim->typepunch = TypeCollisionEnum::LEFT;
            fistHit = &(bboxComponentAttacker->lf);
            bboxComponentAttacker->hlfa = true;
            switch (fistComp->currentFist)
            {
                case FistEnum::DIRECT:
                soundComp->event="event:/Character/PunchBlocked";
                soundComp->play=true;
                    break;
                case FistEnum::CROCHET:
                soundComp->event="event:/Character/PunchBlocked";
                soundComp->play=true;
                    break;
                case FistEnum::UPPERCUT:
                soundComp->event="event:/Character/PunchBlocked";
                soundComp->play=true;
                    break;
                default:
                    break;
            }
        }
    }

    if(!bboxComponentAttacker->hrfa && bboxComponentAttacker->hrf){
        if(CollisionUtils::collidesBueno(bboxComponentAttacker->rf, bboxComponentVictim->body)){
            //totdmg += damage - powerupComp2->ExtraDef;  
            totdmg += damage - powerupComp->ExtraDef;  
            contact = true;
            dmgComponentVictim->typepunch = TypeCollisionEnum::RIGHT;
            fistHit = &(bboxComponentAttacker->rf);
            bboxComponentAttacker->hrfa = true;
        }
    }
    
    bboxComponentAttacker->areaHit.setVisible(false);
    if(velocityCompAttacker->hitDown && !velocityCompAttacker->jumping && dist < 100 && !CollisionUtils::overlaps(bboxComponentAttacker->body, bboxComponentVictim->body)){
        
        float dmgDownhit = areadmg / dist;
        if(dmgDownhit > areadmg)  dmgDownhit = areadmg;
        totdmg += dmgDownhit;
        //std::cout<<dmgDownhit<<std::endl;
        dmgComponentVictim->typepunch = TypeCollisionEnum::AREA;
        velocityCompAttacker->hitDown = false;
        StaminaUtils::decrementStamina(eventManager, staminaCompAttacker,FALLINGHIT_DAMAGE);
        if(visibility) {
            bboxComponentAttacker->areaHit.setVisible(true);
        }
    }
    else if(velocityCompAttacker->hitDown && !velocityCompAttacker->jumping){
        velocityCompAttacker->hitDown = false;
        dmgComponentVictim->typepunch = TypeCollisionEnum::AREA;
        StaminaUtils::decrementStamina(eventManager, staminaCompAttacker,FALLINGHIT_DAMAGE);
        if(visibility) {
            bboxComponentAttacker->areaHit.setVisible(true);
        }
    }

    bool blocked = false;
    if (velocityCompVictim->blocking) {
        StaminaUtils::decrementStamina(eventManager, staminaCompVictim,BLOCK_STAMINA);

        // If player 2 is blocking, not attacking and with stamina, they take no damage.
        if (staminaCompVictim->stamina <= 0) {
            velocityCompVictim->blocking = false;
        } else if (!bboxComponentVictim->hlf && !bboxComponentVictim->hrf && fistHit) {
            blocked = subDefense(totdmg, velocityCompVictim, *fistHit, bboxComponentAttacker->body.pos, *bboxComponentVictim);
            animNodeComponentAttacker->node.changeToAnimation("Neutral");

            contact = false;
        }
    }
    return {totdmg, blocked};
}

bool PunchCollisionSystem::subDefense(int& totdmg1,VelocityComponent* velocityComp, const OBB2D& fist, Vector3f bodyPos, const BBoxComponent& victim){
    if(CollisionUtils::overlaps(fist, victim.block)){
        Vector3f victimBlock = victim.block.pos;
        victimBlock.Y = victim.body.pos.Y;
        if (bodyPos.distance(victimBlock) < bodyPos.distance(victim.body.pos)) {
            totdmg1 -= DIRECTFIST_DAMAGE;
            if(totdmg1 < 0) totdmg1 = 0;
            return true;
        }
    }
    return false;
}

void PunchCollisionSystem::applyDamage(GameStorage& gameStorage, EventManager& eventManager, const int totdmg, bool blocked, bool contact,DamageFeedbackComponent* damagefeedbackComp,HealthComponent* healthComp, PowerUpComponent* pwupCpmp,PowerUpComponent* pwupCpmp2, PositionComponent* posComp, VelocityComponent* velocityComponent, PositionComponent* posComp2, BBoxComponent* bboxComp2, FistComponent* fistComp2){
    velocityComponent->knockback = Vector3f(0,0,0);
    if (totdmg > 0) {
        applyFeedBack(damagefeedbackComp, velocityComponent, posComp, posComp2, bboxComp2, fistComp2);
        if(pwupCpmp->pwup == PowerUpEnum::STUN && contact){  
            eventManager.postEvent<StunEvent>(healthComp->entityID,pwupCpmp->entityID);
        }
        eventManager.postEvent<RefreshGUIBarsEvent>(pwupCpmp2->entityID);
    }
    if (blocked) {
        velocityComponent->knockback += detectDirection(posComp->pos,posComp2->pos,FistEnum::DIRECT, bboxComp2->rf.pos);
    }
    healthComp->HP -= totdmg; // TODO meter esto en el if de arriba?
}

Vector3f PunchCollisionSystem::detectDirection(Vector3f originPos,Vector3f posDamage, FistEnum fistType, Vector3f fistPos){

    Vector3f direction = Vector3f(0,0,0);

    switch (fistType)
    {
        case FistEnum::DIRECT:
            direction = originPos - posDamage;
            direction /= direction.module();
            direction *= DIRECT_FEEDBACK;
            break;
        case FistEnum::CROCHET:
            direction = originPos - fistPos;
            direction.Y = 0;
            direction /= direction.module();
            direction *= CROCHET_FEEDBACK;
            break;
        case FistEnum::UPPERCUT:
            direction = originPos - posDamage;
            direction /= direction.module();
            direction *= UPPERCUT_FEEDBACK;
            break;
        default:
            break;
    }

    direction.Y += 10;
    return direction;
}
void PunchCollisionSystem::applyFeedBack(DamageFeedbackComponent* damagefeedbackComp, VelocityComponent* velocityComp, PositionComponent* posComp, PositionComponent* posComp2, BBoxComponent* bboxComp2, FistComponent* fistComp2){
   
    Vector3f vectDirection = Vector3f(0,0,0);

    switch (damagefeedbackComp->typepunch)
    {
    case TypeCollisionEnum::RIGHT:
        vectDirection = detectDirection(posComp->pos,posComp2->pos,fistComp2->currentFist, bboxComp2->rf.pos);
        break;
     case TypeCollisionEnum::LEFT:
        vectDirection =  detectDirection(posComp->pos,posComp2->pos,fistComp2->currentFist, bboxComp2->lf.pos);
        break;
     case TypeCollisionEnum::AREA:
        vectDirection = posComp->pos -  posComp2->pos;
        vectDirection.Y = 0;
        vectDirection /= vectDirection.module();
        vectDirection *= FALLINGHIT_FEEDBACK;
        break;
     default:
        break;
    }
    
    velocityComp->knockback = vectDirection;
}
void PunchCollisionSystem::detectCollisionPunch(GameStorage& gameStorage, EventManager& eventManager, const bool visibility, SoundComponent* soundComp, SoundComponent* soundComp2,StaminaComponent* staminaComp,StaminaComponent* staminaComp2,FistComponent* fistComp, FistComponent* fistComp2, PowerUpComponent* powerupComp,PowerUpComponent* powerupComp2,BBoxComponent* bboxComp, BBoxComponent* bboxComp2,VelocityComponent* velocityComp, VelocityComponent* velocityComp2, PositionComponent* positionComp, PositionComponent* positionComp2, DamageFeedbackComponent* damagefeedbackComp, DamageFeedbackComponent* damagefeedbackComp2, HealthComponent* healthComp, HealthComponent* healthComp2, IrranimatednodeComponent* animNodeComponent, IrranimatednodeComponent* animNodeComponent2){
    bool contact1 = false;
    bool contact2 = false;
    float dist = positionComp->pos.distance(positionComp2->pos);

    /*// TODO For debugging, delete in production.
    velocityComp2->blocking = true;
    velocityComp->blocking = true;*/

    // Damage received by player 1
    const auto [totdmg1, blocked1] = detect1Way(eventManager, dist,visibility,contact1, soundComp, damagefeedbackComp,fistComp2,bboxComp2,bboxComp,staminaComp2, staminaComp,powerupComp,powerupComp2,velocityComp2, velocityComp, animNodeComponent2);
    // Damage received by player 2
    const auto [totdmg2, blocked2] = detect1Way(eventManager, dist,visibility,contact2,soundComp2, damagefeedbackComp2,fistComp,bboxComp,bboxComp2,staminaComp, staminaComp2, powerupComp2,powerupComp,velocityComp, velocityComp2, animNodeComponent);
    applyDamage(gameStorage, eventManager, totdmg1, blocked2, contact1,damagefeedbackComp,healthComp,powerupComp2,powerupComp,positionComp, velocityComp, positionComp2,bboxComp2, fistComp2);
    applyDamage(gameStorage, eventManager, totdmg2, blocked1, contact2,damagefeedbackComp2,healthComp2,powerupComp,powerupComp2,positionComp2, velocityComp2, positionComp, bboxComp , fistComp);
}
