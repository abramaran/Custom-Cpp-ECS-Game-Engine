#include <InputMenuSystem.h>
#include <StateStruct.h>
#include <OptionSelectedEvent.h>

void InputMenuSystem::Update(GameStorage& gameStorage, EventManager& eventManager, SUMIEngine& receiver, float& frameDeltaTime, std::vector<TkeyStruct>& keymapping, bool& changeState, StateEnum& nextState)
{
    keyTime += frameDeltaTime;
    for(auto i=0;i<keymapping.size();++i){

        if(keyTime > 0.2){
            keyTime = 0.2;
        }
        if(receiver.IsKeyDown(keymapping[i].key) && keyTime > 0.2)
        {
            keyTime = 0;

            switch (keymapping[i].action.type)
            {
            case typeEnum::state:
                if(keymapping[i].action.state >= -1){
                    changeState = true;
                    nextState = keymapping[i].action.state;
                }
                break;
            case typeEnum::level :
                eventManager.postEvent<ChangeLevelEvent>(keymapping[i].action.level);
                break;         
            case typeEnum::character :
                eventManager.postEvent<ChangeCharacterEvent>(keymapping[i].action.character,keymapping[i].action.path);
                break;
            default:
                break;
            }
           
        }
    }
}
