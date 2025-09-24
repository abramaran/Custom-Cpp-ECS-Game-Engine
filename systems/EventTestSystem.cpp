#include <EventTestSystem.h>
#include <iostream>

void EventTestSystem::Update(GameStorage& gameStorage) {
    for (auto& e : gameStorage.getEventsOfType<TestEvent>()) {
        //std::cout << "Event: " << e.message << std::endl;
    }
}