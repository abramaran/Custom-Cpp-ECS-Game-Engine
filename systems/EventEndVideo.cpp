#include <EventEndVideo.h>

void EventEndVideo::Update(GameStorage& gameStorage, bool& changeState, StateEnum& nextState){
    for (auto& e : gameStorage.getEventsOfType<EndVideoEvent>()) { 
        changeState = true;
        nextState = e.newState;
    }
}