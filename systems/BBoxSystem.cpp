#include <BBoxSystem.h>
#include <BBoxUtils.h>

void BBoxSystem::Update(GameStorage& gameStorage){
    for (auto& bboxComp : gameStorage.getComponentsOfType<BBoxComponent>()){
        auto& entity = gameStorage.getEntity(bboxComp.entityID);
        PositionComponent* positionComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!positionComp) continue;
        RotationComponent* rotationComp = static_cast<RotationComponent*>(entity.require(COMPONENT_ROTATION));
        if (!positionComp) continue;
        
        Vector3f* posChar  = &positionComp->pos;
        Vector3f* posLf    = &bboxComp.lf.pos;
        Vector3f* posRf    = &bboxComp.rf.pos;
        Vector3f* posBlock = &bboxComp.block.pos;

        float rot = -rotationComp->rot.Y; //We just care about the rotation on Y

        OBB2D* body = &bboxComp.body;
        OBB2D* lf = &bboxComp.lf;
        OBB2D* rf = &bboxComp.rf;
        OBB2D* block = &bboxComp.block;

        //Body bien
        body->node.setPosition(*posChar);
        body->pos = *posChar;

        TAKO::Vector2f center = Vector2f(posChar->X, posChar->Z);
        float w = bboxComp.body.node.getScale().X * defaultBoxSize;
        float h = bboxComp.body.node.getScale().Z * defaultBoxSize;
        
        BBoxUtils::rotate(*body, center, w, h, rot);

        body->node.setRotation(Vector3f(0,rot,0));
        body->rot = Vector3f(0,rot,0);

        //Left fist
        lf->pos = BBoxUtils::rotatePoint(lf->pos, body->pos, (rot-lf->rot.Y));
        lf->rot = Vector3f(0 ,rot, 0);

        lf->node.setPosition(lf->pos);
        lf->node.setRotation(Vector3f(0 ,rot, 0));

        center = Vector2f(lf->pos.X, lf->pos.Z);
        w = lf->node.getScale().X * defaultBoxSize;
        h = lf->node.getScale().Z * defaultBoxSize;
        BBoxUtils::rotate(*lf, center, w, h, rot);

        //Right fist

        rf->pos = BBoxUtils::rotatePoint(rf->pos, body->pos, (rot-rf->rot.Y));
        rf->rot = Vector3f(0 ,rot, 0);

        rf->node.setPosition(rf->pos);
        rf->node.setRotation(Vector3f(0 ,rot, 0));

        center = Vector2f(rf->pos.X, rf->pos.Z);
        w = rf->node.getScale().X * defaultBoxSize;
        h = rf->node.getScale().Z * defaultBoxSize;
        BBoxUtils::rotate(*rf, center, w, h, rot);

        //Block
        block->node.setPosition(Vector3f(posBlock->X + 10, posChar->Y+fistLocationY - 10, posBlock->Z));
        block->pos = Vector3f(posBlock->X + 10, posChar->Y+fistLocationY - 10, posBlock->Z);

        block->pos = BBoxUtils::rotatePoint(block->pos, body->pos, (rot-block->rot.Y));
        block->rot = Vector3f(0 ,rot, 0);

        block->node.setPosition(block->pos);
        block->node.setRotation(Vector3f(0 ,rot, 0));

        center = Vector2f(block->pos.X, block->pos.Z);
        w = block->node.getScale().X * defaultBoxSize;
        h = block->node.getScale().Z * defaultBoxSize;
        BBoxUtils::rotate(*block, center, w, h, rot);
    }
    for (auto& bboxpropsComp : gameStorage.getComponentsOfType<BBoxPropsComponent>()){
        auto& entity = gameStorage.getEntity(bboxpropsComp.entityID);
        PositionComponent* positionComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!positionComp) continue;
        RotationComponent* rotationComp = static_cast<RotationComponent*>(entity.require(COMPONENT_ROTATION));
        if (!rotationComp) continue;

        Vector3f& pos = positionComp->pos;
        OBB2D& body = bboxpropsComp.body;
        float rot = rotationComp->rot.Y; //We just care about the rotation on Y

        //BBoxUtils::calculateBBox(body, pos, rot, defaultBoxSize);

        body.node.setRotation(Vector3f(0, rot, 0));
        body.rot = (Vector3f(0,rot,0));
    }
    for (auto& bboxcameraComp : gameStorage.getComponentsOfType<BBoxCameraComponent>()){
        auto& entity = gameStorage.getEntity(bboxcameraComp.entityID);
        PositionComponent* positionComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!positionComp) continue;

        Vector3f& pos = positionComp->pos;
        OBB2D& body = bboxcameraComp.body;

        BBoxUtils::calculateBBox(body, pos, 0, defaultBoxSize);
        body.node.setPosition(pos);
        body.pos = pos;

    }

    for (auto& slopeComp : gameStorage.getComponentsOfType<SlopeComponent>()){
        auto& entity = gameStorage.getEntity(slopeComp.entityID);
        PositionComponent* positionComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!positionComp) continue;
        RotationComponent* rotationComp = static_cast<RotationComponent*>(entity.require(COMPONENT_ROTATION));
        if (!positionComp) continue;

        Vector3f* pos = &positionComp->pos;
        OBB2D* body = &slopeComp.body;
        float rot = rotationComp->rot.Y; //We just care about the rotation on Y
        TAKO::Vector2f center = Vector2f(pos->X, pos->Z);

        float w = body->node.getScale().X * defaultBoxSize;
        float h = body->node.getScale().Z * defaultBoxSize;

        BBoxUtils::rotate(*body, center, w, h, rot);

        body->pos = *pos;
        body->node.setRotation(Vector3f(0, rot, 0));
        body->rot = (Vector3f(0,rot,0));
    }

}