#include <EventManager.h>
#include <tuple>

namespace TAKO {
void EventManager::deleteAllEvents() {
    std::apply([&](auto&... vectorEvent){(vectorEvent.clear(), ...);}, gameStorage->eventVectors);
}
}