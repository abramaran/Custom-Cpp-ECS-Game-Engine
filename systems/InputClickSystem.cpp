#include <InputClickSystem.h>
#include <StateStruct.h>
#include <OptionSelectedEvent.h>

void InputClickSystem::Update(GameStorage& gameStorage, EventManager& eventManager, SUMIEngine& receiver, float& frameDeltaTime, bool& changeState, StateEnum& nextState)
{
    keyTime += frameDeltaTime;
    if (receiver.IsMouseKeyPressed(MouseKey::LEFT) && keyTime > 0.2) {
        keyTime = 0;
        eventManager.postEvent<OptionSelectedEvent>(&nextState, &changeState);
    }
}
