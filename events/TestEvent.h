#pragma once
#include <string>

struct TestEvent
{
    explicit TestEvent(std::string msg) : message{msg} {};

    std::string message;
};
