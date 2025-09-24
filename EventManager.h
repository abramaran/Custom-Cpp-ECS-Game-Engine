#pragma once
#include <GameStorage.h>

#include <vector>

namespace TAKO {
struct EventManager
{
    explicit EventManager(GameStorage* gStorage) : gameStorage{gStorage} {};

    void deleteAllEvents();

    template <class T, typename ... Args>
    T& postEvent(Args ... args) {
        auto& eventVector = gameStorage->getEventsOfType<T>();

        eventVector.emplace_back(args ...);
        return eventVector.back();
    }

    private:
        GameStorage* gameStorage;
};
}
