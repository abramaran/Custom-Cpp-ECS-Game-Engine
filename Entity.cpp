#include <Entity.h>
#include <EntityManager.h>
#include <iostream>
#include <stdexcept>

namespace TAKO {
std::size_t Entity::nextID{0};

Entity::Entity() : id{nextID} {
    ++nextID;
}

IComponent* Entity::require(ComponentIndex componentType) {
    for (IComponent* c : components) {
        if (c->componentType == componentType) {
            return c;
        }
    }

    return nullptr;
}


void Entity::updateComponentPointer(IComponent* newAddress) {
    for (int i = 0; i < components.size(); i++) {
        if (components[i]->componentType == newAddress->componentType) {
            components[i] = newAddress;
            break;
        }
    }
}

/**
 * Note: use ComponentManager.deleteComponent() for the correct deletion of a component.
 * Removes the pointer to the requested component from the components vector.
 */
void Entity::detachComponent(IComponent* component) {
    auto iterator = std::find_if(components.begin(), components.end(), [&](const auto & val){ 
        if (val->componentType == component->componentType) {
            return true;
        } else {
            return false;
        }
    });
    //auto iterator = std::find(components.begin(), components.end(), component);

    if ((*(iterator))->componentType != component->componentType) {
        throw std::invalid_argument("in Entity::detachComponent(): No component of type " + std::to_string(component->componentType) + " found in entity " + std::to_string(component->entityID));
    } else {
        std::iter_swap(iterator, components.end() - 1);
        components.pop_back();
    }
}
}