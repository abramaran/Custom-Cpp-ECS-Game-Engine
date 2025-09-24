#pragma once

struct JumpEvent {
    explicit JumpEvent(std::size_t eID) : entityID{eID} {};

    std::size_t entityID;
};
