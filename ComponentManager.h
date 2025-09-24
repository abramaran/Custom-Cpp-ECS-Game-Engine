#pragma once

#include <GameStorage.h>
#include <IComponent.h>
#include <Entity.h>
#include <tuple>
#include <algorithm>

namespace TAKO {
struct ComponentManager {
    explicit ComponentManager(GameStorage* gStorage);
    
    void emptyEntityComponents(Entity& e);

    template <class T>
    T& addComponent(std::size_t entityID) {
        Entity& ent = gameStorage->getEntity(entityID);
        std::vector<T>& componentVector = gameStorage->getComponentsOfType<T>();

        componentVector.emplace_back(entityID);
        ent.components.push_back(&componentVector.back());
        return componentVector.back();
    }

    template <class T>
    void deleteComponent(std::size_t entityID) {
        std::vector<T>& vectorOfType = gameStorage->getComponentsOfType<T>();

        // 1. Iterador 1 apuntando al elemento component, iterador 2 a end()-1.
        typename std::vector<T>::iterator iterator = std::find_if(vectorOfType.begin(), vectorOfType.end(), [&](const T & val){ 
            if (val.entityID == entityID) {
                return true;
            } else {
                return false;
            }
        });

        // 2. Swap.
        std::iter_swap(iterator, vectorOfType.end() - 1);

        // 3. Buscar en el array de entidades la entidad del componente en el iterador 1.
        typename std::vector<Entity>::iterator iterEntity = std::find_if(gameStorage->entities.begin(), gameStorage->entities.end(), [&](const Entity & val){ 
            if (val.id == iterator->entityID) {
                return true;
            } else {
                return false;
            }
        });

        // 4. Actualizar puntero en la entidad.
        iterEntity->updateComponentPointer(&(*iterator));       

        // 5. Delete pointer from entity.
        gameStorage->getEntity(entityID).detachComponent(&(*(vectorOfType.end() - 1)));

        // 5. Pop back.
        vectorOfType.pop_back();
    }

    GameStorage* gameStorage;
};
}