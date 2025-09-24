#include <GameStorage.h>
#include <algorithm>
#include <stdexcept>

namespace TAKO {
    GameStorage::GameStorage() {
        std::apply([&](auto&... vectorComp){(vectorComp.reserve(MAX_COMPONENTS), ...);}, componentVectors);
        std::apply([&](auto&... vectorEvent){(vectorEvent.reserve(MAX_EVENTS), ...);}, eventVectors);
        entities.reserve(MAX_ENTITIES);
    }

    Entity& GameStorage::getEntity(std::size_t id) {
        std::vector<Entity>::iterator iterator = std::find_if(entities.begin(), entities.end(), [&](const Entity & val){ 
            if (val.id == id) {
                return true;
            } else {
                return false;
            }
        });

        if (iterator->id != id) {
            throw std::invalid_argument("in GameStorage::getEntity(): entity " + std::to_string(id) + "not found.");
        } else { 
            return *iterator;
        }
    }
}