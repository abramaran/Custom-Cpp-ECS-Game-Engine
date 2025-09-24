#pragma once
#include <Entity.h>

struct PowerUpStartEvent
{
    explicit PowerUpStartEvent(std::size_t playable, std::size_t pwbox): id_playable{playable}, id_pw{pwbox}{};//entity{ent} {};

    std::size_t id_playable;
    std::size_t id_pw;
    
};