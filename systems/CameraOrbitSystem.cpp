#include <CameraOrbitSystem.h>
#include <CollisionUtils.h>
#include <BBoxUtils.h>
#include <SUMICameraNode.h>
#include <Vector3f.h>

void CameraOrbitSystem::Update(GameStorage& gameStorage,  int playerID){
    /////////// Guards ////////////
    auto& playerEntity = gameStorage.getEntity(playerID);
    PositionComponent* pl_positionComp = static_cast<PositionComponent*>(playerEntity.require(COMPONENT_POSITION));
    if (!pl_positionComp) return;
    ///////////////////////////////

    for (auto& irrcameraNodeComp : gameStorage.getComponentsOfType<IrrcameranodeComponent>()) {
        /////////// Guards ////////////
        auto& entity = gameStorage.getEntity(irrcameraNodeComp.entityID);
        LookAtComponent* lookAtComp = static_cast<LookAtComponent*>(entity.require(COMPONENT_LOOKAT));
        if (!lookAtComp) continue;
        DistanceComponent* distanceComp = static_cast<DistanceComponent*>(entity.require(COMPONENT_DISTANCE));
        if (!distanceComp) continue;
        DirectionComponent* directionComp = static_cast<DirectionComponent*>(entity.require(COMPONENT_DIRECTION));
        if (!directionComp) continue;
        PositionComponent* positionComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!positionComp) continue;
        ///////////////////////////////

        SUMI::SUMICameraNode* camera = &irrcameraNodeComp.node;
        TAKO::Vector3f* distance = &distanceComp->distance;
        float* direction  = &directionComp->direction;
        float* zdirection = &directionComp->zdirection;

        
        *distance = Vector3f(70.f,70.f,70.f);

        TAKO::Vector3f* playerPos = &pl_positionComp->pos;
        float xf = playerPos->X - cos( *direction * PI / 180.0f )  * distance->X;
        float yf = playerPos->Y - sin( *zdirection * PI / 180.0f ) * distance->Y;
        float zf = playerPos->Z + sin( *direction * PI / 180.0f )  * distance->Z;

        if(yf < 30){
            yf = 30.f;
        }


        //Change node
        camera->setPosition(TAKO::Vector3f(xf, yf, zf));
        camera->setTarget(TAKO::Vector3f(playerPos->X,playerPos->Y + 25.f,playerPos->Z));
        
        //Change components
        positionComp->pos = TAKO::Vector3f(xf,yf,zf);
        lookAtComp->lkat = TAKO::Vector3f(playerPos->X,playerPos->Y + 25.f,playerPos->Z);
    }

}
