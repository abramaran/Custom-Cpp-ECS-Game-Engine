#include <ConveyorBeltSystem.h>

void ConveyorBeltSystem::Update(GameStorage& gameStorage, const float frameDeltaTime){
    for (auto& convComp : gameStorage.getComponentsOfType<ConveyorBeltComponent>()){
        auto& entity = gameStorage.getEntity(convComp.entityID);
        bool reset = false;

        if(convComp.sense){                       
            float max = -distance * convComp.nodes.size() + posInitL.Z;
            if(max >= convComp.nodes[0].getPosition().Z){
                TAKO::Vector3f posInit = TAKO::Vector3f(-mult2 *-0.021, mult2 *0.044, -mult2 *-7.986);
                for (size_t i = 0; i < convComp.nodes.size(); i++)
                {
                    convComp.nodes[i].setPosition(TAKO::Vector3f(posInit.X, posInit.Y, posInit.Z - distance*i));

                }
            }
            else{
                for (size_t i = 0; i < convComp.nodes.size(); i++)
                {
                    TAKO::Vector3f pos = convComp.nodes[i].getPosition();
                    if(max >= pos.Z){
                        convComp.nodes[i].setPosition(TAKO::Vector3f(pos.X, pos.Y, posInitL.Z));
                    }
                    else{
                        convComp.nodes[i].setPosition(TAKO::Vector3f(pos.X, pos.Y, pos.Z - BELT_SPEED * frameDeltaTime));
                    }
                }
            }
   
        }
        else{
            float max = distance * convComp.nodes.size() + posInitR.Z;
            // We reset to avoid gaps
            if(max <= convComp.nodes[0].getPosition().Z){
                TAKO::Vector3f posInit = TAKO::Vector3f(-mult2 *1.35, mult2 *0.044, -mult2 *2.218);
                for (size_t i = 0; i < convComp.nodes.size(); i++)
                {
                    convComp.nodes[i].setPosition(TAKO::Vector3f(posInit.X, posInit.Y, posInit.Z + distance*i));

                }
            }
            else{
                // We move normally
                for (size_t i = 0; i < convComp.nodes.size(); i++)
                {
                    TAKO::Vector3f pos = convComp.nodes[i].getPosition();

                

                    if(max <= pos.Z){
                        convComp.nodes[i].setPosition(TAKO::Vector3f(pos.X, pos.Y, posInitR.Z));
                    }
                    else{
                        convComp.nodes[i].setPosition(TAKO::Vector3f(pos.X, pos.Y, pos.Z + BELT_SPEED * frameDeltaTime));
                    }
                }
            }
        }  
    }
}