#pragma once

enum class MovementDirection {
    forwards,
    backwards,
    left,
    right
};

struct MovementEvent {
    explicit MovementEvent(std::size_t eID, MovementDirection d) : entityID{eID}, direction{d} {};

    std::size_t entityID;
    MovementDirection direction;
};
