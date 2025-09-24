#pragma once
#include <string>

struct ChangeAnimationEvent {
    explicit ChangeAnimationEvent(std::size_t eID, std::string anim) : entityID{eID}, newAnimation{anim} {};

    std::size_t entityID;
    std::string newAnimation;
};
