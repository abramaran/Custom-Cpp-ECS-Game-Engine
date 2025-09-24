#pragma once
#include <GameEnums.h>
#include <optional>

struct ChangeFistEvent {
    explicit ChangeFistEvent(std::size_t eID) : entityID{eID} {};   // For changing to previous fist
    explicit ChangeFistEvent(std::size_t eID, FistEnum f) : entityID{eID}, fist{f} {}; // For changing to a specific fist
    explicit ChangeFistEvent(std::size_t eID, int c) : entityID{eID}, cycle{c} {}; // For cycling through the fists

    std::size_t entityID;
    std::optional<FistEnum> fist;
    std::optional<int> cycle;
};
