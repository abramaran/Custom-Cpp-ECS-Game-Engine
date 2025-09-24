#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <Vector3f.h>
/**
 * Spawn points in a particular level where power-ups can be generated and any
 * other variable related 
 */
struct SpawnPointsComponent : public IComponent
{
    explicit SpawnPointsComponent(std::size_t eID) : IComponent{COMPONENT_SPAWNPOINT, eID} {};

    float time{0};
    int numBoxes{0};

    std::vector<std::pair<bool,TAKO::Vector3f>> positions;

     //Online values
    
    std::vector<int> type;  //type of power up
    std::vector<int> pos; //vector position
};