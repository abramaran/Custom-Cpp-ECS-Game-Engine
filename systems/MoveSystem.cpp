#include <MoveSystem.h>
#include <iostream>


/**
 * MoveSystem::Update
 *  Updates the position component of entities based on their velocity component.
 */
void MoveSystem::Update(GameStorage& gameStorage,const float frameDeltaTime) {
    for (auto& irranimatednodeComp : gameStorage.getComponentsOfType<IrranimatednodeComponent>()) {
        /////////// Guards ////////////
        auto& entity = gameStorage.getEntity(irranimatednodeComp.entityID);
        DirectionComponent* directionComp = static_cast<DirectionComponent*>(entity.require(COMPONENT_DIRECTION));
        if (!directionComp) continue;
        RotationComponent* rotationComp = static_cast<RotationComponent*>(entity.require(COMPONENT_ROTATION));
        if (!rotationComp) continue;
        VelocityComponent* velocityComp = static_cast<VelocityComponent*>(entity.require(COMPONENT_VELOCITY));
        if (!velocityComp) continue;
        BBoxComponent* bboxComp = static_cast<BBoxComponent*>(entity.require(COMPONENT_BBOX));
        if (!bboxComp) continue;
        PositionComponent* positionComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!positionComp) continue;
        ///////////////////////////////

        std::string currAnim = irranimatednodeComp.node.getCurrentAnimation();
        if (!velocityComp->jumping && currAnim.rfind("Uppercut", 0) == 0) continue;   //El player no se debe mover durante el uppercut.

        float* direction = &directionComp->direction;

        irranimatednodeComp.node.setRotation(TAKO::Vector3f( 0, -*direction, 0));
        rotationComp->rot = TAKO::Vector3f( 0, *direction, 0);

        Vector3f* rot = &rotationComp->rot;
        Vector3f* vel = &velocityComp->vel;
        Vector3f* velfeedback = &velocityComp->knockback;
        Vector3f* pos = &positionComp->pos;
        Vector3f* posLf = &bboxComp->lf.pos;
        Vector3f* posRf = &bboxComp->rf.pos;
        Vector3f* posBlock = &bboxComp->block.pos;

        Vector3f facingForwardsBackwards( sin( ( rot->Y + 90.0f ) * PI/180.0f ), 0, cos( ( rot->Y + 90.0f ) * PI/180.0f ) );
        Vector3f facingRightLeft( sin( (rot->Y) * PI/180.0f ), 0, cos( (rot->Y) * PI/180.0f ) );

        facingForwardsBackwards.normalize();
        facingRightLeft.normalize();


        vel->Y -= GRAVITY;

        if(velocityComp->jumping) positionComp->onFloor = false;


        *velfeedback*= frameDeltaTime;
        pos->Y += vel->Y * frameDeltaTime;
        if(vel->Z != 0){
            float velocityZ = vel->Z * frameDeltaTime;
            if(vel->X != 0){
                velocityZ/=sqrtTwo;
            }

            facingForwardsBackwards *= velocityZ;
            *pos   += facingForwardsBackwards;         
            *posLf += facingForwardsBackwards;
            *posRf += facingForwardsBackwards;
            *posBlock += facingForwardsBackwards;

        }
        if(vel->X != 0){
            float velocityX = vel->X * frameDeltaTime;
            if(vel->Z != 0){
                velocityX/=sqrtTwo;
            }
            facingRightLeft *= velocityX;
            *pos   += facingRightLeft;
            *posLf += facingRightLeft;
            *posRf += facingRightLeft;
            *posBlock += facingRightLeft;
        }

        if(velocityComp->onBelt && velocityComp->speedBelt != 0){
            pos->Z += velocityComp->speedBelt * frameDeltaTime;
        }


        *pos += *velfeedback;
        *posLf += *velfeedback;
        *posRf += *velfeedback;
        *posBlock += *velfeedback;

        bboxComp->areaHit.setPosition(*pos);

        velocityComp->onBelt = false;
        velocityComp->speedBelt = 0;

    }
}

