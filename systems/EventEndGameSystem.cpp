#include <EventEndGameSystem.h>
#include <EndGameEvent.h>
#include <PlayerConstants.h>
#include <BillboardUtils.h>

void EventEndGameSystem::Update(GameStorage& gameStorage, bool& changeState, StateEnum& nextState){
    for (auto& e : gameStorage.getEventsOfType<EndGameEvent>()) { 
        //FIXME deberia llamarse playerTag
        for(auto& playableTag : gameStorage.getComponentsOfType<TagPlayer>()) { 
            ///////////// Guards ////////////
            auto& entity = gameStorage.getEntity(playableTag.entityID);
            HealthComponent* healthComp = static_cast<HealthComponent*>(entity.require(COMPONENT_HEALTH));
            if (!healthComp) continue;

            changeState = true;
            
            if(healthComp->HP == 0 ||healthComp->HP > MAX_HP){
                if(nextState == StateEnum::IN_GAMEMULTI){
                    nextState = StateEnum::YOU_LOSE_M;
                }
                else{
                    nextState = StateEnum::YOU_LOSE_S;
                }
            }
            else{
                if(nextState == StateEnum::IN_GAMEMULTI){
                    nextState = StateEnum::YOU_WIN_M;
                }
                else{
                    nextState = StateEnum::YOU_WIN_S;
                }            
            }
        }
    }
}