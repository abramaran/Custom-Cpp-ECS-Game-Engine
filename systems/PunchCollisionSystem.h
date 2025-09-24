#pragma once
#include <GameStorage.h>
#include <EventManager.h>
#include <CollisionUtils.h>
#include <StaminaUtils.h>
#include <PlayerConstants.h>
#include <EventManager.h>
using namespace TAKO;

struct PunchCollisionSystem
{
    void Update(GameStorage& gameStorage, EventManager& eventManager, const bool visibility);

    void applyFeedBack(
        DamageFeedbackComponent* damagefeedbackComp, 
        VelocityComponent* velocityComp,
        PositionComponent* posComp, 
        PositionComponent* posComp2,
        BBoxComponent* bboxComp2, 
        FistComponent* fistComp2
    );
    
    Vector3f detectDirection(Vector3f originPos,Vector3f posDamage, FistEnum fistType, Vector3f fistPos);

    void detectCollisionPunch(GameStorage& gameStorage, EventManager& eventManager, const bool visibility,
     SoundComponent* soundComp, SoundComponent* soundComp2,
     StaminaComponent* staminaComp,StaminaComponent* staminaComp2,
     FistComponent* fistComp, FistComponent* fistComp2,
     PowerUpComponent* powerupComp,PowerUpComponent* powerupComp2,
     BBoxComponent* bboxComponent, BBoxComponent* bboxComponent2,
     VelocityComponent* velocityComp, VelocityComponent* velocityComp2, 
     PositionComponent* positionComp, PositionComponent* positionComp2, 
     DamageFeedbackComponent* damagefeedbackComp, DamageFeedbackComponent* damagefeedbackComp2, 
     HealthComponent* healthComp, HealthComponent* healthComp2, 
     IrranimatednodeComponent* animNodeComponent, IrranimatednodeComponent* animNodeComponent2);
  
    int detectPunchDamage(FistComponent* fistComponent);
    std::pair<int, bool> detect1Way(
        TAKO::EventManager& eventManager, 
        const float dist,
        const bool visibility,
        bool& contact,
        SoundComponent* staminaComp, 
        DamageFeedbackComponent* dmgComponentVictim, 
        FistComponent* fistComp,
        BBoxComponent* bboxComponentAttacker, BBoxComponent* bboxComponentVictim,
        StaminaComponent* staminaCompAttacker, StaminaComponent* staminaCompVictim,
        PowerUpComponent* powerupComp, PowerUpComponent* powerupComp2,
        VelocityComponent* velocityCompAttacker, VelocityComponent* velocityCompVictim, 
        IrranimatednodeComponent* animNodeComponentAttacker);

    void applyDamage(
        GameStorage& gameStorage,
        EventManager& eventManager,
        const int totdmg,
        bool blocked,
        bool contact,
        DamageFeedbackComponent* damagefeedbackComp,
        HealthComponent* healthComp, 
        PowerUpComponent* pwupCpmp,
        PowerUpComponent* pwupCpmp2,
        PositionComponent* posComp,
        VelocityComponent* velocityComponent,
        PositionComponent* posComp2,
        BBoxComponent* bboxComp2,
        FistComponent* fistComp2
    );

    bool subDefense(int& totdmg1,VelocityComponent* velocityComp, const OBB2D& fist, Vector3f bodyPos, const BBoxComponent& enemy);

    private:
        const int defaultBoxSize = 10;
        const int fistLocation = defaultBoxSize/2 + 1;
        const int areadmg = 25*15;
        float range = 20;
        int damage1 = 0;
        int damage2 = 0;
};
