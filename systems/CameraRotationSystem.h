
#pragma once
#include <GameStorage.h>
#include <Vector2f.h>
#include <EntityManager.h>

using namespace TAKO;
struct CameraRotationSystem
{
    void Update(GameStorage& gameStorage, int playerID, int enemyID, const TAKO::Vector2f& cursorPosition);
    void setValues(float dir, float zdir);
    bool lockCamera {false};
    private:
        float direction     {0};
        float zdirection    {0};
};
