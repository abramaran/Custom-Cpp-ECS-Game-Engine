#pragma once

enum class FistAction {
    left,
    right,
    block,
    resetTimer
};

struct PunchEvent {
    explicit PunchEvent(std::size_t eID, FistAction f) : entityID{eID}, fist{f} {};

    std::size_t entityID;
    FistAction fist;
};
