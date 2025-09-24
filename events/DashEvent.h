#pragma once

enum class DashDirection {
    left,
    right
};

struct DashEvent {
    explicit DashEvent(std::size_t eID, DashDirection d) : entityID{eID}, direction{d} {};

    std::size_t entityID;
    DashDirection direction;
};
