#pragma once
#include <string>

struct StunEvent
{
    explicit StunEvent(std::size_t victim, std::size_t attacker) :  Victim_id{victim}, Attacker_id{attacker}{};

    std::size_t Victim_id;
    std::size_t Attacker_id;
};
