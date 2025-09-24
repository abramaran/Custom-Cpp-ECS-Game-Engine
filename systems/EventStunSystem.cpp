#include <EventStunSystem.h>
#include <PlayerConstants.h>
#include <CameraConstants.h>
#include <CameraUtils.h>
#include <PowerUpEndEvent.h>

void EventStunSystem::Update(GameStorage& gameStorage, EventManager& eventManager, std::size_t player_ID){
    for (auto& e : gameStorage.getEventsOfType<StunEvent>()) {
        
        auto& victimEnt   = gameStorage.getEntity( e.Victim_id );
        auto& attackerEnt = gameStorage.getEntity(e.Attacker_id);

        PowerUpComponent* vm_pwupComp = static_cast<PowerUpComponent*>(victimEnt.require(COMPONENT_POWERUP));
        if(!vm_pwupComp) continue;
        PowerUpComponent* at_pwupComp = static_cast<PowerUpComponent*>(attackerEnt.require(COMPONENT_POWERUP));
        if(!at_pwupComp) continue;

        vm_pwupComp->stunned = true;
        vm_pwupComp->stunnedCooldown = STUN_EFFECT_COOLDOWN;  

        eventManager.postEvent<PowerUpEndEvent>(e.Attacker_id);  

        if(e.Victim_id == player_ID){
            CameraUtils::setCameraVel(gameStorage, CAMERA_VEL_SLOW);
        }
    }
}