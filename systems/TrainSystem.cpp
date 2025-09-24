#include <TrainSystem.h>
#include <CollisionUtils.h>
#include <BBoxUtils.h>
#include <math.h>

void TrainSystem::Update(GameStorage& gameStorage, float frameDeltaTime) {
    
    for (auto& trainComp : gameStorage.getComponentsOfType<TrainComponent>()) { 
        auto& trains = gameStorage.getEntity(trainComp.entityID);
        /////////// Guards ////////////
        PositionComponent* positionComp = static_cast<PositionComponent*>(trains.require(COMPONENT_POSITION));
        if (!positionComp) continue;
        ///////////////////////////////

        trainComp.timer -= frameDeltaTime;
        if(trainComp.timer < 0) trainComp.timer = 0;

        if(trainComp.timer <= 0){
            if (trainComp.line)
            {
                positionComp->pos.Z = topLine;

                if((positionComp->pos.X - distance * 8) < max)
                    positionComp->pos.X += vel * frameDeltaTime;
                else{
                    trainComp.line = rand() % 2;
                    if(trainComp.line){
                        positionComp->pos.X = min;
                    }
                    else
                    {
                        positionComp->pos.X = max;
                    }
                    trainComp.carriages = rand() % 4 + 3;
                    trainComp.timer = rand() % variability + baseValue;
                    break;
                }

                TAKO::Vector3f auxPos = positionComp->pos;

                TAKO::Vector3f tmpPos = positionComp->pos;
                    tmpPos.Y += 20;

                for (unsigned i = 0; i < trainComp.carriages; i++)
                {
                    auxPos.X -= distance;

                    trainComp.bboxes[i].pos = auxPos;
                    trainComp.bboxes[i].node.setPosition(auxPos);

                    BBoxUtils::calculateBBox(trainComp.bboxes[i], auxPos, 0, 10);

                    tmpPos = auxPos;
                    tmpPos.Y += 20;

                    trainComp.nodes[i].setPosition(tmpPos);

                }
            }
            else
            {
                positionComp->pos.Z = botLine;

                if((positionComp->pos.X + distance * 8) > min)
                    positionComp->pos.X -= vel * frameDeltaTime;
                else{
                    trainComp.line = rand() % 2;
                    if(trainComp.line){
                        positionComp->pos.X = min;
                    }
                    else
                    {
                        positionComp->pos.X = max;
                    }
                    
                    trainComp.carriages = rand() % 4 + 3;
                    trainComp.timer = rand() % variability + baseValue;
                    break;
                }

                TAKO::Vector3f auxPos = positionComp->pos;

                TAKO::Vector3f tmpPos = positionComp->pos;
                    tmpPos.Y += 20;


                for (unsigned i = 0; i < trainComp.carriages; i++)
                {
                    auxPos.X += distance;

                    trainComp.bboxes[i].pos = auxPos;
                    trainComp.bboxes[i].node.setPosition(auxPos);

                    BBoxUtils::calculateBBox(trainComp.bboxes[i], auxPos, 0, 10);

                    tmpPos = auxPos;
                    tmpPos.Y += 20;

                    trainComp.nodes[i].setPosition(tmpPos);

                }
            }
        }


       
        
        
    }
}
