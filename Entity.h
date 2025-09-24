#pragma once

#include <vector>
#include <cstddef>

#include <IComponent.h>
#include <ComponentIndexes.h>

namespace TAKO {
struct Entity {
    Entity();

    IComponent* require(ComponentIndex componentType);
    void detachComponent(IComponent*);
    void updateComponentPointer(IComponent*);
    
    std::size_t id;
    std::vector<IComponent*> components;

    private:
        static std::size_t nextID;
};
}