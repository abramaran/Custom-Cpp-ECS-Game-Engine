#pragma once
#include <cstddef>
#include <vector>
#include<ComponentIndexes.h>

struct IComponent
{   
    IComponent(ComponentIndex cType, std::size_t eID) : componentType{cType}, entityID{eID} {};

    ComponentIndex componentType;
    std::size_t entityID;
};
