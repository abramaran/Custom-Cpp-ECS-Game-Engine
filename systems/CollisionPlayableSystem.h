#pragma once
#include <GameStorage.h>
#include <CollisionUtils.h>
#include <PlayerConstants.h>
#include <EventManager.h>
#include <EntityManager.h>
using namespace TAKO;
struct CollisionPlayableSystem
{
    void Update(GameStorage& gameStorage, const float frameDeltaTime,EventManager& eventmanager, EntityManager& entityManager);
    bool sameY(float& dist, float& playerHeight,PositionComponent* posComp,PositionComponent* posComp2,OBB2D* body,OBB2D* body2);
    void restoreNewPosition(const float frameDeltaTime,PositionComponent* poscomp,RotationComponent* rotationcomp, VelocityComponent* velocitycomp, BBoxComponent* bboxComp, IrranimatednodeComponent* animatednodeComp);
    void youShallNotPass(const float frameDeltaTime,PositionComponent* poscomp,RotationComponent* rotationcomp, VelocityComponent* velocitycomp, BBoxComponent* bboxComp, IrranimatednodeComponent* animatednodeComp);
    
    bool detectPiston(const float frameDeltaTime,
    VelocityComponent* velComp, PositionComponent* posComp, 
    DashComponent* dashComp, BBoxComponent* bboxComp,
    PistonComponent* pistonComp, PositionComponent* posComp2,
    BBoxPropsComponent* bboxComp2,IrrbasicnodeComponent* node2,
    RotationComponent* rotComp,IrranimatednodeComponent* animatednodeComp,
    int characterID, EntityManager entityManager);

    void detectCollision(const float frameDeltaTime,
    BBoxComponent* bboxComp, BBoxPropsComponent* bboxComp2, 
    VelocityComponent* velComp, DashComponent* dashComp,
    PositionComponent* posComp, PositionComponent* posComp2, 
    RotationComponent* rotComp,
    IrranimatednodeComponent* animatednodeComp);

    void detectCollisionSlope(const float frameDeltaTime,
    BBoxComponent* bboxComp, SlopeComponent* slopeComp, 
    VelocityComponent* velComp, DashComponent* dashComp,
    PositionComponent* posComp, PositionComponent* posComp2, 
    RotationComponent* rotComp,
    IrranimatednodeComponent* animatednodeComp);

    void detectCollisionPlayer(const float frameDeltaTime,
    BBoxComponent* bboxComp, BBoxComponent* bboxComp2, 
    HealthComponent* healthComp, HealthComponent* healthComp2,
    VelocityComponent* velComp, VelocityComponent* velComp2, 
    PositionComponent* posComp,PositionComponent* posComp2, 
    RotationComponent* rotComp,RotationComponent* rotComp2,
    DashComponent* dashComp, DashComponent* dashComp2,
    IrranimatednodeComponent* animatednodeComp, IrranimatednodeComponent* animatednodeComp2);

    void detectTrain(const float frameDeltaTime, EventManager& eventManager, HealthComponent* healthComp,
    BBoxComponent* bboxComp, OBB2D bbox, 
    VelocityComponent* velComp, PowerUpComponent* pwupComp, RotationComponent* rotComp,
    DashComponent* dashComp,  PositionComponent* posComp, 
    PositionComponent* posComp2, IrranimatednodeComponent* animatednodeComp); 
    
    void detectSaw(const float frameDeltaTime, bool sense, EventManager& eventManager, HealthComponent* healthComp,
    BBoxComponent* bboxComp, OBB2D bbox, 
    VelocityComponent* velComp, PowerUpComponent* pwupComp, RotationComponent* rotComp,
    DashComponent* dashComp,  PositionComponent* posComp, 
    PositionComponent* posComp2, IrranimatednodeComponent* animatednodeComp);


    private:
        const float sqrtTwo = 1.141;
        const int defaultBoxSizeHalf = 5;
        const float maxScale = 20; // cambiar también en piston system
        const float speedPiston = 300;
        const int defaultBoxSize = 10;

};