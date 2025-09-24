#pragma once
#include <Entity.h>

struct PowerUpEndEvent
{
   explicit PowerUpEndEvent(std::size_t entity_id): id{entity_id}{};
   
    std::size_t id;
};
