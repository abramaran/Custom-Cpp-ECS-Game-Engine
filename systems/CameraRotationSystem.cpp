#include <CameraRotationSystem.h>
#include "PlayerConstants.h"

int const pi = 3.14159;


void CameraRotationSystem::setValues(float dir, float zdir){
    direction = dir;
    zdirection = zdir;
}

void CameraRotationSystem::Update(GameStorage& gameStorage, int playerID, int enemyID, const TAKO::Vector2f& cursorPosition){
    /////////// Guards ////////////
    auto& playerEntity = gameStorage.getEntity(playerID);
    DirectionComponent* pl_directionComp = static_cast<DirectionComponent*>(playerEntity.require(COMPONENT_DIRECTION));
    if (!pl_directionComp) return;
    PositionComponent* positionPlayerComp = static_cast<PositionComponent*>(playerEntity.require(COMPONENT_POSITION)); 
    if (!positionPlayerComp) return;
    VelocityComponent* velCompp = static_cast<VelocityComponent*>(playerEntity.require(COMPONENT_VELOCITY));
        if(!velCompp) return;

    auto& enemyEntity = gameStorage.getEntity(enemyID);
    PositionComponent* positionEnemyComp = static_cast<PositionComponent*>(enemyEntity.require(COMPONENT_POSITION)); 
    if (!positionEnemyComp) return;
    
    

    for (auto& irrcameranodeComp : gameStorage.getComponentsOfType<IrrcameranodeComponent>()) {
        /////////// Guards ////////////
        auto& entity = gameStorage.getEntity(irrcameranodeComp.entityID);
        DirectionComponent* directionComp = static_cast<DirectionComponent*>(entity.require(COMPONENT_DIRECTION));
        if (!directionComp) continue;
        VelocityComponent* velComp = static_cast<VelocityComponent*>(entity.require(COMPONENT_VELOCITY));
        if(!velComp) continue;
        ///////////////////////////////

        // X axis
        if(!lockCamera){
            // MANUAL CAMERA
            float change_x = ( cursorPosition.X - 0.5 ) * velComp->vel.X; //vel of camera movement
            direction += change_x;
        }
        else{
            // lOCK CAMERA
            TAKO::Vector3f positionPlayer = positionPlayerComp->pos;
            TAKO::Vector3f positionEnemy = positionEnemyComp ->pos;
            TAKO::Vector3f directionLook = positionPlayer - positionEnemy;
            directionLook = directionLook.unit();
            //directionLook.print("DirectionLook");
            TAKO::Vector3f direcitonLookBase = TAKO::Vector3f(-1,0,0);

            float dot = directionLook.X *direcitonLookBase.X + directionLook.Z * direcitonLookBase.Z;      
            float det = directionLook.X *direcitonLookBase.Z - directionLook.Z * direcitonLookBase.X;  
            float mod1 = directionLook.module();
            float mod2 = direcitonLookBase.module();  

            // angle = rad * pi =  acos(dot / (mod1 * mod2)) * pi
            // angle w/ rad = angle / pi
            float angle = acos(dot / (mod1 * mod2)) / M_PI; // number of radians w/ pi

            if(positionPlayer.Z < positionEnemy.Z) angle *= -1; // depending on location we set behind as negative

            // We set the angle right, otherwise it'd go from -1 to 1
            if(angle != 0){
                angle *= 180;
                angle += 180;
            }
            
            // We flip the angle so that it doesn't put its back towards the enemy
            direction = 180 + angle;

            //Set velocity
            float distance= sqrt(pow((positionEnemyComp->pos.X)-(positionPlayerComp->pos.X),2)+
	        pow((positionEnemyComp->pos.Z)-(positionPlayerComp->pos.Z),2));
            //std::cout<<distance<<std::endl;
            //Range of speed 20 - 100 Range of distance 25 - 150
            if(distance<25){
                velCompp->vel.Z=20;
                velCompp->vel.X=20;
            }
            else if(distance>150){
                velCompp->vel.Z=100;
                velCompp->vel.X=100;
            }
            else{
                float per=((distance - 25) * 100) / (150 - 25);
                float aux=(per * (100 - 20) / 100) + 20;
                //velCompp->vel.Z=aux;
                //velCompp->vel.X=aux;
            }
            //std::cout<<velCompp->vel.Z<<std::endl;
        }

        // Y Axis
        float change_y = ( cursorPosition.Y - 0.5 ) * velComp->vel.Y; //TODO Permitir invertir eje y de la camara aqui.

        zdirection -= change_y;
        if( zdirection < -90 )
            zdirection = -90;
        else
        if( zdirection > 90 )
            zdirection = 90;

        // Set variables to components
        directionComp->direction = direction;
        directionComp->zdirection = zdirection;

        pl_directionComp->direction = direction;
        pl_directionComp->zdirection = zdirection;
    }
}
