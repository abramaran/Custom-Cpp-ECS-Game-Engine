#pragma once
#include <GameStorage.h>

using namespace TAKO;
struct CollisionCameraSystem
{
    void Update(GameStorage& gameStorage,  int playerID);
    void moveUntilNotColliding(TAKO::Vector3f& auxPos, IrrcameranodeComponent* cameraNodeComp, OBB2D& camera, const OBB2D& obstacle, const TAKO::Vector3f& moveDirection);
};