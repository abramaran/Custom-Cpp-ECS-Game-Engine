#include <CollisionCameraSystem.h>
#include <CollisionUtils.h>
#include <BBoxUtils.h>
#include <math.h>

void CollisionCameraSystem::Update(GameStorage& gameStorage,  int playerID) {
    /////////// Guards ////////////
    auto& playerEntity = gameStorage.getEntity(playerID);
    PositionComponent* pl_positionComp = static_cast<PositionComponent*>(playerEntity.require(COMPONENT_POSITION));
    if (!pl_positionComp) return;
    ///////////////////////////////

    for (auto& bboxCameraComp : gameStorage.getComponentsOfType<BBoxCameraComponent>()) {
        auto& camera = gameStorage.getEntity(bboxCameraComp.entityID);
        /////////// Guards ////////////
        PositionComponent* positionComp = static_cast<PositionComponent*>(camera.require(COMPONENT_POSITION));
        if (!positionComp) continue;
        IrrcameranodeComponent* cameraNodeComp = static_cast<IrrcameranodeComponent*>(camera.require(COMPONENT_IRRCAMERANODE));
        if (!cameraNodeComp) continue;
        ///////////////////////////////

        BBoxUtils::calculateBBox(bboxCameraComp.body, positionComp->pos, 0, 10);

        TAKO::Vector3f moveDirection = pl_positionComp->pos;
        moveDirection.Y += 25;
        moveDirection = (moveDirection - positionComp->pos).unit();

        TAKO::Vector3f auxPos = positionComp->pos;
        for(auto& bboxPropsComp : gameStorage.getComponentsOfType<BBoxPropsComponent>()) {
            moveUntilNotColliding(auxPos, cameraNodeComp, bboxCameraComp.body, bboxPropsComp.body, moveDirection);
        }
        for(auto& slopeComp : gameStorage.getComponentsOfType<SlopeComponent>()) {
            moveUntilNotColliding(auxPos, cameraNodeComp, bboxCameraComp.body, slopeComp.body, moveDirection);
        }
    }
}

void CollisionCameraSystem::moveUntilNotColliding(TAKO::Vector3f& auxPos, IrrcameranodeComponent* cameraNodeComp, OBB2D& camera, const OBB2D& obstacle, const TAKO::Vector3f& moveDirection) {
    bool positionDirty = false;

    while (CollisionUtils::collides(camera, obstacle)) {
        auxPos += moveDirection;
        BBoxUtils::calculateBBox(camera, auxPos, 0, 10);
        camera.node.setPosition(auxPos);
        positionDirty = true;
    }
    if (positionDirty) {
        cameraNodeComp->node.setPosition(auxPos);
    }
}