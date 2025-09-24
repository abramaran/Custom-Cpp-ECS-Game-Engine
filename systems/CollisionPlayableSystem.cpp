#include <CollisionPlayableSystem.h>
#include <PowerUpStartEvent.h>
#include <BBoxUtils.h>
#include <math.h>

void CollisionPlayableSystem::Update(GameStorage& gameStorage, const float frameDeltaTime,EventManager& eventManager, EntityManager& entityManager){

    for (auto& bboxComp : gameStorage.getComponentsOfType<BBoxComponent>()){
        auto& entity = gameStorage.getEntity(bboxComp.entityID);
        /////////// Guards ////////////
        RotationComponent* rotComp = static_cast<RotationComponent*>(entity.require(COMPONENT_ROTATION));
        if (!rotComp) continue;
        VelocityComponent* velComp = static_cast<VelocityComponent*>(entity.require(COMPONENT_VELOCITY));
        if (!velComp) continue;
        PositionComponent* posComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!posComp) continue;
        DashComponent*     dashComp = static_cast<DashComponent*>(entity.require(COMPONENT_DASH));
        if (!dashComp) continue;
        IrranimatednodeComponent* irranimatednodeComp = static_cast<IrranimatednodeComponent*>(entity.require(COMPONENT_IRRANIMATEDNODE));
        if (!irranimatednodeComp) continue;
        PowerUpComponent* pwupComp = static_cast<PowerUpComponent*>(entity.require(COMPONENT_POWERUP));
        if(!pwupComp) continue;
        ///////////////////////////////

        
        

        // Colisiones con el segundo luchador
        for (auto& bboxComp2 : gameStorage.getComponentsOfType<BBoxComponent>()){
            auto& entity2 = gameStorage.getEntity(bboxComp2.entityID);
            if(entity.id != entity2.id){
                /////////// Guards ////////////
                RotationComponent* rotComp2 = static_cast<RotationComponent*>(entity2.require(COMPONENT_ROTATION));
                if (!rotComp2) continue;
                VelocityComponent* velComp2 = static_cast<VelocityComponent*>(entity2.require(COMPONENT_VELOCITY));
                if (!velComp2) continue;
                PositionComponent* posComp2 = static_cast<PositionComponent*>(entity2.require(COMPONENT_POSITION));
                if (!posComp2) continue;
                DashComponent*     dashComp2 = static_cast<DashComponent*>(entity2.require(COMPONENT_DASH));
                if (!dashComp2) continue;   
                IrranimatednodeComponent* irranimatednodeComp2 = static_cast<IrranimatednodeComponent*>(entity2.require(COMPONENT_IRRANIMATEDNODE));
                if (!irranimatednodeComp2) continue;
                HealthComponent* healthComp = static_cast<HealthComponent*>(entity.require(COMPONENT_HEALTH));
                if (!healthComp) continue;
                HealthComponent* healthComp2 = static_cast<HealthComponent*>(entity2.require(COMPONENT_HEALTH));
                if (!healthComp2) continue;
                ///////////////////////////////
                detectCollisionPlayer(frameDeltaTime, &bboxComp,  &bboxComp2,  healthComp, healthComp2, velComp,  velComp2,  posComp, posComp2,  rotComp, rotComp2, dashComp, dashComp2, irranimatednodeComp,  irranimatednodeComp2);
                eventManager.postEvent<RefreshGUIBarsEvent>(healthComp->entityID);
                eventManager.postEvent<RefreshGUIBarsEvent>(healthComp2->entityID);


            }
        }        //bool foundcamera = false;

        // Colisiones con el resto de bounding boxes
        for(auto& bboxComp2 : gameStorage.getComponentsOfType<BBoxPropsComponent>()){
            auto& entity2 = gameStorage.getEntity(bboxComp2.entityID);

            /////////// Guards ////////////
            PositionComponent* posComp2 = static_cast<PositionComponent*>(entity2.require(COMPONENT_POSITION));
            if (!posComp2) continue;
            PowerUpComponent* pwupComp2 = static_cast<PowerUpComponent*>(entity2.require(COMPONENT_POWERUP));
            PistonComponent* pistonComp = static_cast<PistonComponent*>(entity2.require(COMPONENT_PISTON));
            
            if(!pwupComp2){ // It's a piston or a regular bbox.
                if(pistonComp){
                    IrrbasicnodeComponent* node2 = static_cast<IrrbasicnodeComponent*>(entity2.require(COMPONENT_IRRBASICNODE));
                    if(!detectPiston(frameDeltaTime, velComp, posComp, dashComp, &bboxComp, pistonComp, posComp2, &bboxComp2, node2,  rotComp, irranimatednodeComp, entity.id, entityManager)){
                        detectCollision(frameDeltaTime, &bboxComp,  &bboxComp2,  velComp, dashComp,  posComp, posComp2, rotComp, irranimatednodeComp);
                    }
                } else detectCollision(frameDeltaTime, &bboxComp,  &bboxComp2,  velComp, dashComp,  posComp, posComp2, rotComp, irranimatednodeComp);
            } else {
              // Power up box
                if(CollisionUtils::collides(bboxComp.body,bboxComp2.body)){  
                    eventManager.postEvent<PowerUpStartEvent>(entity.id,entity2.id);
                }
            }
        }
        for (auto& convBeltComp : gameStorage.getComponentsOfType<ConveyorBeltComponent>())
        {
            auto& entity2 = gameStorage.getEntity(convBeltComp.entityID);

            PositionComponent* posComp2 = static_cast<PositionComponent*>(entity2.require(COMPONENT_POSITION));
            BBoxUtils::calculateBBox(convBeltComp.bbox, posComp2->pos, 0, defaultBoxSize);


            if(CollisionUtils::collides(bboxComp.body, convBeltComp.bbox)){
                velComp->speedBelt = BELT_SPEED;
                if(!convBeltComp.sense)  velComp->speedBelt *= -1;

                velComp->onBelt = true;
            }
            
        }
        
        for(auto& slopeComp : gameStorage.getComponentsOfType<SlopeComponent>()){
            auto& entity2 = gameStorage.getEntity(slopeComp.entityID);

            /////////// Guards ////////////
            PositionComponent* posComp2 = static_cast<PositionComponent*>(entity2.require(COMPONENT_POSITION));
            if (!posComp2) continue;
            ///////////////////////////////
            detectCollisionSlope(frameDeltaTime, &bboxComp,  &slopeComp,  velComp, dashComp,  posComp, posComp2, rotComp, irranimatednodeComp);     
        }
        for(auto& trainComp : gameStorage.getComponentsOfType<TrainComponent>()){
            auto& entity2 = gameStorage.getEntity(trainComp.entityID);

            /////////// Guards ////////////
            PositionComponent* posComp2 = static_cast<PositionComponent*>(entity2.require(COMPONENT_POSITION));
            if (!posComp2) continue;
            
            HealthComponent* healthComp = static_cast<HealthComponent*>(entity.require(COMPONENT_HEALTH));
            if (!healthComp) continue;

            ///////////////////////////////

            for (unsigned i = 0; i < trainComp.bboxes.size(); i++)
            {
                detectTrain(frameDeltaTime, eventManager, healthComp, &bboxComp, trainComp.bboxes[i], velComp, pwupComp, rotComp, dashComp, posComp, posComp2, irranimatednodeComp);
            }
            
        }
        for (auto& sawComp : gameStorage.getComponentsOfType<SawComponent>())
        {
            auto& entity2 = gameStorage.getEntity(sawComp.entityID);

            /////////// Guards ////////////
            PositionComponent* posComp2 = static_cast<PositionComponent*>(entity2.require(COMPONENT_POSITION));
            if (!posComp2) continue;
            
            HealthComponent* healthComp = static_cast<HealthComponent*>(entity.require(COMPONENT_HEALTH));
            if (!healthComp) continue;

            ///////////////////////////////

            detectSaw(frameDeltaTime, sawComp.sense ,eventManager, healthComp, &bboxComp, sawComp.bbox, velComp, pwupComp, rotComp, dashComp, posComp, posComp2, irranimatednodeComp);


        }
        
    }
}

void CollisionPlayableSystem::youShallNotPass(const float frameDeltaTime,PositionComponent* poscomp,RotationComponent* rotationcomp, VelocityComponent* velocitycomp, BBoxComponent* bboxComp, IrranimatednodeComponent* animatednodeComp){
    Vector3f facingForwardsBackwards( sin( ( rotationcomp->rot.Y + 90.0f ) * M_PI/180.0f ), 0, cos( ( rotationcomp->rot.Y + 90.0f ) * M_PI/180.0f ) );
    Vector3f facingRightLeft( sin( (rotationcomp->rot.Y) * M_PI/180.0f ), 0, cos( (rotationcomp->rot.Y) * M_PI/180.0f ) );
    Vector3f& velfeedback = velocitycomp->knockback;
    facingForwardsBackwards.normalize();
    facingRightLeft.normalize();
    if(velocitycomp->vel.Z != 0){
        float velocityZ = velocitycomp->vel.Z * frameDeltaTime;
        if(velocitycomp->vel.X != 0){
            velocityZ /= sqrtTwo;
        }
        facingForwardsBackwards *= velocityZ;
        poscomp->pos -= facingForwardsBackwards;
        bboxComp->lf.pos -= facingForwardsBackwards;
        bboxComp->rf.pos -= facingForwardsBackwards;
        bboxComp->block.pos -= facingForwardsBackwards;
    }
    if(velocitycomp->vel.X != 0){
        float velocityX = velocitycomp->vel.X * frameDeltaTime;
        if(velocitycomp->vel.Z != 0){
            velocityX/= sqrtTwo;
        }
        facingRightLeft *= velocityX;
        poscomp->pos -= facingRightLeft;
        bboxComp->lf.pos -= facingRightLeft;
        bboxComp->rf.pos -= facingRightLeft;
        bboxComp->block.pos -= facingRightLeft;
    }

    poscomp->pos -= velfeedback;
    bboxComp->lf.pos -= velfeedback;
    bboxComp->rf.pos -= velfeedback;
    bboxComp->block.pos -= velfeedback;

    bboxComp->body.node.setPosition(poscomp->pos);
    bboxComp->lf.node.setPosition(TAKO::Vector3f(bboxComp->lf.pos.X, bboxComp->lf.node.getPosition().Y, bboxComp->lf.pos.Z));
    bboxComp->rf.node.setPosition(TAKO::Vector3f(bboxComp->rf.pos.X, bboxComp->rf.node.getPosition().Y, bboxComp->rf.pos.Z));
    bboxComp->block.node.setPosition(TAKO::Vector3f(bboxComp->block.pos.X, bboxComp->block.node.getPosition().Y, bboxComp->block.pos.Z));
}

void CollisionPlayableSystem::restoreNewPosition(const float frameDeltaTime,PositionComponent* poscomp,RotationComponent* rotationcomp, VelocityComponent* velocitycomp, BBoxComponent* bboxComp, IrranimatednodeComponent* animatednodeComp){  
    Vector3f facingForwardsBackwards( sin( ( rotationcomp->rot.Y + 90.0f ) * M_PI/180.0f ), 0, cos( ( rotationcomp->rot.Y + 90.0f ) * M_PI/180.0f ) );
    Vector3f facingRightLeft( sin( (rotationcomp->rot.Y) * M_PI/180.0f ), 0, cos( (rotationcomp->rot.Y) * M_PI/180.0f ) );

    facingForwardsBackwards.normalize();
    facingRightLeft.normalize();
    if(velocitycomp->vel.Z != 0){
        float velocityZ = velocitycomp->vel.Z * frameDeltaTime;
        if(velocitycomp->vel.X != 0){
            velocityZ /= sqrtTwo;
        }
        facingForwardsBackwards *= velocityZ;
        poscomp->pos += facingForwardsBackwards;
        bboxComp->lf.pos += facingForwardsBackwards;
        bboxComp->rf.pos += facingForwardsBackwards;
        bboxComp->block.pos += facingForwardsBackwards;
    }
    if(velocitycomp->vel.X != 0){
        float velocityX = velocitycomp->vel.X * frameDeltaTime;
        if(velocitycomp->vel.Z != 0){
            velocityX/=sqrtTwo;
        }
        facingRightLeft *= velocityX;
        poscomp->pos += facingRightLeft;
        bboxComp->lf.pos += facingRightLeft;
        bboxComp->rf.pos += facingRightLeft;
        bboxComp->block.pos += facingRightLeft;
    }

    bboxComp->body.node.setPosition(poscomp->pos);
    bboxComp->lf.node.setPosition(TAKO::Vector3f(bboxComp->lf.pos.X, bboxComp->lf.node.getPosition().Y, bboxComp->lf.pos.Z));
    bboxComp->rf.node.setPosition(TAKO::Vector3f(bboxComp->rf.pos.X, bboxComp->rf.node.getPosition().Y, bboxComp->rf.pos.Z));
    bboxComp->block.node.setPosition(TAKO::Vector3f(bboxComp->block.pos.X, bboxComp->block.node.getPosition().Y, bboxComp->block.pos.Z));
}

bool CollisionPlayableSystem::sameY(float& dist, float& playerHeight,PositionComponent* posComp,PositionComponent* posComp2,OBB2D* body,OBB2D* body2){
    float minY1, maxY1, minY2, maxY2;
    minY1 = posComp->pos.Y  - defaultBoxSizeHalf * body->node.getScale().Y;
    maxY1 = posComp->pos.Y  + defaultBoxSizeHalf * body2->node.getScale().Y;
    minY2 = posComp2->pos.Y - defaultBoxSizeHalf * body->node.getScale().Y;
    maxY2 = posComp2->pos.Y + defaultBoxSizeHalf * body2->node.getScale().Y;
    dist = minY1 - maxY2;
    playerHeight = abs(maxY1 - minY1);

    return (maxY1 < minY2 || maxY2 > minY1);
}

bool CollisionPlayableSystem::detectPiston(const float frameDeltaTime, VelocityComponent* velComp, PositionComponent* posComp, DashComponent* dashComp, BBoxComponent* bboxComp, PistonComponent* pistonComp, PositionComponent* posComp2, BBoxPropsComponent* bboxComp2, IrrbasicnodeComponent* node2, RotationComponent* rotComp,IrranimatednodeComponent* animatednodeComp, int characterID, EntityManager entityManager){
    float dist = 0;
    bool detected = false;
    float playerHeight = CollisionUtils::getPlayerHeight(bboxComp->body);;
    float maxY2 = posComp2->pos.Y + defaultBoxSizeHalf * bboxComp2->body.node.getScale().Y;
    float maxY2Alta = posComp2->pos.Y + defaultBoxSizeHalf * maxScale;
    float newPosY = maxY2 + bboxComp->body.node.getScale().Y * defaultBoxSizeHalf;
    int enemyID = entityManager.getEnemyID();
    int playerID = entityManager.getPlayerID();
    TAKO::Vector3f scale = bboxComp2->body.node.getScale();
    if( !pistonComp->down ){
        bboxComp2->body.node.setScale(Vector3f(scale.X, maxScale, scale.Z));
    } 
    

    if(CollisionUtils::collides(bboxComp->body, bboxComp2->body)){

            // For it to manage both players we have set a variable for each.
            // If either of them are on it will do the animation
            // If it was detected someone it will send them up
            if(characterID == playerID  && !pistonComp->activated1){
                pistonComp->activated1 = true; 
                detected = true;
            }
            else if (characterID == enemyID  && !pistonComp->activated2)
            {
                pistonComp->activated2 = true; 
                detected = true;
            }

            if(detected){
                velComp->vel.Y = speedPiston;
                posComp->pos.Y = maxY2Alta + 100;
                bboxComp->body.node.setPosition(posComp->pos);
                velComp->jumping = true;
                dashComp->dashing = false;
            }
    }

    if( !pistonComp->down ) {
        bboxComp2->body.node.setScale(Vector3f(scale.X, scale.Y, scale.Z));
    }

    return detected;
    
}

void CollisionPlayableSystem::detectCollision(const float frameDeltaTime,BBoxComponent* bboxComp, BBoxPropsComponent* bboxComp2, VelocityComponent* velComp, DashComponent* dashComp, PositionComponent* posComp,PositionComponent* posComp2, RotationComponent* rotComp,IrranimatednodeComponent* animatednodeComp){

    float dist = 0;
    float playerHeight = 0;
    float maxY2 = posComp2->pos.Y + defaultBoxSizeHalf * bboxComp2->body.node.getScale().Y;


    // TODO: Cambiar esto a una tupla que te devuelva la distancia y la altura del jugador. Ya no usamos sameY para calcular la altura lo hace colides
    bool sameYb = sameY(dist, playerHeight,posComp, posComp2, &bboxComp->body, &bboxComp2->body);

    // Velcomp->minYDist es lo que se usa para saber el objeto que este mas cercano en Y
    // Para ver si se puede hacer el puño para abajo
    //
    //    O <- player
    //    |
    //    | if(velComp->minYDist < DISTANCIA_GOLPE_ABAJO*) puedo hacer golpe abajo
    //    |
    //    V
    // ________ <- suelo
    //
    // * No se llama así de verdad
    if(dist < velComp->minYDist && CollisionUtils::overlaps(bboxComp->body, bboxComp2->body)){

        velComp->minYDist = dist;
    }


    if(CollisionUtils::collides(bboxComp->body, bboxComp2->body)){
        // We 'collide it', reverting its position to the previous one
        //youShallNotPass(entity1, world, frameDeltaTime);
        youShallNotPass(frameDeltaTime, posComp, rotComp, velComp, bboxComp, animatednodeComp);
        
        // If taking this previous position it still collides it means that it came from above
        if(CollisionUtils::collides(bboxComp->body,bboxComp2->body)){
            
            // We set the position to be above the object and it's velocity to 0
            float newPosY = maxY2 + bboxComp->body.node.getScale().Y * defaultBoxSizeHalf;
            if(abs(posComp->pos.Y - newPosY) < playerHeight/5 || posComp->pos.Y <= CollisionUtils::getYComponentsBBox(bboxComp2->body).getFirst()){ //abs(posComp->pos.Y - newPosY) < playerHeight/5 ||

                restoreNewPosition(frameDeltaTime,posComp,rotComp,velComp,bboxComp,animatednodeComp);
                posComp->pos.Y = newPosY;
                bboxComp->body.node.setPosition(posComp->pos);
                animatednodeComp->node.setPosition(posComp->pos);

                posComp->onFloor = true;
                velComp->vel.Y = 0;
                velComp->jumping = false;
                velComp->doublejumping = false;
                dashComp->dashed = false;
                velComp->hitAir = false;

            }
            else{
                dashComp->dashing = false;
                velComp->vel.X = 1; // Esto hace que no puedas atravesar el suelo al chocarte con la pared, idk why
                if(velComp->jumping == false){
                    velComp->vel.X = 1;
                    velComp->vel.Z = 0;
                }
            }

        }
        else{
            dashComp->dashed = false;
        }
        
    }                  
    //si colisiona hacer los calculos del moveSystem pero restando
}

void CollisionPlayableSystem::detectCollisionPlayer(const float frameDeltaTime,BBoxComponent* bboxComp, BBoxComponent* bboxComp2, HealthComponent* healthComp, HealthComponent* healthComp2, VelocityComponent* velComp, VelocityComponent* velComp2, PositionComponent* posComp,PositionComponent* posComp2, RotationComponent* rotComp,RotationComponent* rotComp2, DashComponent* dashComp, DashComponent* dashComp2, IrranimatednodeComponent* animatednodeComp, IrranimatednodeComponent* animatednodeComp2){
    
    float minY1, maxY1, minY2, maxY2;
    OBB2D bbox1 = bboxComp->body;
    OBB2D bbox2 = bboxComp2->body;
    
    minY1 = bbox1.node.getPosition().Y - defaultBoxSizeHalf * bbox1.node.getScale().Y;
    maxY1 = bbox1.node.getPosition().Y + defaultBoxSizeHalf * bbox1.node.getScale().Y;
    minY2 = bbox2.node.getPosition().Y - defaultBoxSizeHalf * bbox2.node.getScale().Y;
    maxY2 = bbox2.node.getPosition().Y + defaultBoxSizeHalf * bbox2.node.getScale().Y;

    std::string sep = " / ";

    //std::cout<<minY1<<sep<<maxY1<<std::endl<<minY2<<sep<<maxY2<<std::endl;

    //std::cout<<(CollisionUtils::overlaps(bbox1, bbox2) && !(minY1 > maxY2 || minY2 > maxY1))<<std::endl;
   // return (overlaps(bbox1, bbox2) && !(minY1 > maxY2 && minY2 > maxY1));

   // (overlaps(bbox1, bbox2) && (maxY1 > minY2 || maxY2 > minY1));


    if(CollisionUtils::collides(bboxComp->body, bboxComp2->body)){
        //td::cout<<"Colisiona"<<std::endl;
        youShallNotPass(frameDeltaTime,posComp ,rotComp ,velComp ,bboxComp , animatednodeComp );
        youShallNotPass(frameDeltaTime,posComp2,rotComp2,velComp2,bboxComp2, animatednodeComp2);

        if(CollisionUtils::collides(bboxComp->body, bboxComp2->body)){
            
            velComp->minYDist = 10000;
            velComp2->minYDist = 10000;
            float maxY = posComp->pos.Y + defaultBoxSizeHalf * bboxComp->body.node.getScale().Y;
            float maxY2 = posComp2->pos.Y + defaultBoxSizeHalf * bboxComp2->body.node.getScale().Y;
            float playerHeight = CollisionUtils::getPlayerHeight(bboxComp->body);
            float playerHeight2 = CollisionUtils::getPlayerHeight(bboxComp2->body);

            if(CollisionUtils::getYComponentsBBox(bboxComp2->body).getFirst() > CollisionUtils::getYComponentsBBox(bboxComp->body).getFirst()){
                float newPosY = maxY + bboxComp->body.node.getScale().Y * defaultBoxSizeHalf;

                if(abs(posComp2->pos.Y - newPosY) >= playerHeight*4/5){
                    // std::cout<<"1"<<std::endl;
                    restoreNewPosition(frameDeltaTime,posComp2,rotComp2,velComp2,bboxComp2,animatednodeComp2); 
                    restoreNewPosition(frameDeltaTime,posComp,rotComp,velComp,bboxComp,animatednodeComp);   
                    velComp2->vel.Z = -100;
                    velComp2->vel.X = -100;
                }
                else if(abs(posComp2->pos.Y - newPosY) < playerHeight/5){
                    // std::cout<<"2"<<std::endl;

                    restoreNewPosition(frameDeltaTime,posComp2,rotComp2,velComp2,bboxComp2,animatednodeComp2); 
                    restoreNewPosition(frameDeltaTime,posComp,rotComp,velComp,bboxComp,animatednodeComp); 
                    if(velComp2->hitDown){
                        velComp2->hitDown = false;
                        healthComp -= FALLINGHIT_DAMAGE;
                    }
                    
                    velComp2->vel.Y = 200;  
                }
                else{
                    // std::cout<<"3"<<std::endl;
                    dashComp2->dashing = false;
                    dashComp2->dashed = false;
                }
            }
            else 
            {
                float newPosY = maxY2 + bboxComp2->body.node.getScale().Y * defaultBoxSizeHalf; 
                if(CollisionUtils::getYComponentsBBox(bboxComp->body).getFirst()+1 >= CollisionUtils::getYComponentsBBox(bboxComp2->body).getSecond()){
                    velComp->vel.Y = 20;
                    // std::cout<<"4"<<std::endl;
                }
                else if(abs(posComp->pos.Y - newPosY) < playerHeight2/5){

                    // velComp->vel.Z = -0.5 * velComp->vel.Z;
                    // velComp->vel.X = -0.5 * velComp->vel.X;
                    // std::cout<<"5"<<std::endl;
                    restoreNewPosition(frameDeltaTime,posComp,rotComp,velComp,bboxComp,animatednodeComp);    
                    restoreNewPosition(frameDeltaTime,posComp2,rotComp2,velComp2,bboxComp2,animatednodeComp2); 
                    if(velComp->hitDown){
                        velComp->hitDown = false;
                        healthComp2 -= FALLINGHIT_DAMAGE;
                    } 

                    velComp->vel.Y = 200;  
                }
                else{
                    // std::cout<<"6"<<std::endl;
                    velComp->vel.Z = -100;
                    velComp->vel.X = -100;
                    dashComp->dashing = false;
                    dashComp->dashed = false;
                }

            }
        }
    }
    else
    {
        //std::cout<<"No colisiona"<<std::endl;

    }
    

//     if(CollisionUtils::collides(bboxComp->body, bboxComp2->body)){
//         velComp->vel.X += 100;
//         velComp2->vel.X -= 100;
//         velComp->vel.Z += 100;
//         velComp2->vel.Z -= 100;
//     }
}

void CollisionPlayableSystem::detectCollisionSlope(const float frameDeltaTime,BBoxComponent* bboxComp, SlopeComponent* slopeComp, VelocityComponent* velComp, DashComponent* dashComp, PositionComponent* posComp,PositionComponent* posComp2, RotationComponent* rotComp,IrranimatednodeComponent* animatednodeComp) {
    Vector2f xCoords = CollisionUtils::getXComponentsBBox(slopeComp->body);
    Vector2f yCoords = CollisionUtils::getYComponentsBBox(slopeComp->body);
    Vector2f zCoords = CollisionUtils::getZComponentsBBox(slopeComp->body);

    // Calculate percentage
    float percentage;
    if (slopeComp->axis) {  // Estamos en X
        percentage = (posComp->pos.X - xCoords.getFirst()) / (xCoords.getSecond() - xCoords.getFirst());
    } else {    // Estamos en Z
        percentage = (posComp->pos.Z - zCoords.getFirst()) / (zCoords.getSecond() - zCoords.getFirst());
    }

    if (percentage < 0 || percentage > 1) return;   // Player center is outside ramp.

    // Ramp sense
    percentage = (slopeComp->positiveSense)? percentage : 1 - percentage;

    // Calculate player's new Y position
    float rampHeight = yCoords.getSecond() - yCoords.getFirst();
    float playerHeight = CollisionUtils::getPlayerHeight(bboxComp->body);
    float newY = yCoords.getFirst() + rampHeight * percentage + playerHeight/2;

    bool collides = CollisionUtils::collides(bboxComp->body, slopeComp->body);
    if(collides && posComp->pos.Y-2 <= newY){
        youShallNotPass(frameDeltaTime, posComp ,rotComp ,velComp ,bboxComp ,animatednodeComp);

        if((CollisionUtils::collides(bboxComp->body, slopeComp->body) && abs(posComp->pos.Y - newY) < playerHeight/5) || (posComp->pos.Y < CollisionUtils::getYComponentsBBox(slopeComp->body).getFirst())) {
            restoreNewPosition(frameDeltaTime,posComp,rotComp,velComp,bboxComp,animatednodeComp);  

            posComp->onFloor = true;
            velComp->vel.Y = 0;
            velComp->jumping = false;
            velComp->doublejumping = false;
            velComp->hitAir = false;
            dashComp->dashed = false;
            dashComp->dashing = false;
            bboxComp->body.pos.Y = newY;
            posComp->pos.Y = newY;
        }
    }
}

void CollisionPlayableSystem::detectTrain(const float frameDeltaTime, EventManager& eventManager, HealthComponent* healthComp, BBoxComponent* bboxComp, OBB2D bbox, VelocityComponent* velComp, PowerUpComponent* pwupComp, RotationComponent* rotComp, DashComponent* dashComp, PositionComponent* posComp, PositionComponent* posComp2, IrranimatednodeComponent* animatednodeComp){

    if(CollisionUtils::collides(bboxComp->body, bbox)){
        Vector3f* rot = &rotComp->rot;
        Vector3f facingForwardsBackwards( sin( ( rot->Y + 90.0f ) * M_PI/180.0f ), 0, cos( ( rot->Y + 90.0f ) * M_PI/180.0f ) );
        facingForwardsBackwards.normalize();

        if(posComp->pos.Z> posComp2->pos.Z){
            
            
            pwupComp->stunned = true;
            pwupComp->stunnedCooldown = STUN_EFFECT_TRAIN;  
            // std::cout<<velComp->vel.X<<" . "<<velComp->vel.Z<<std::endl;

            float newPosZ = CollisionUtils::getZComponentsBBox(bbox).Y;
            posComp->pos.Z = newPosZ + 20;
            posComp->pos.Y += 10;
            

            if(velComp->jumping)
                facingForwardsBackwards *= 200;
            else
                facingForwardsBackwards *= 400;

            velComp->jumping = true;
            velComp->hitAir = true;
            dashComp->dashing = false;
            

            velComp->vel.X = facingForwardsBackwards.X;
            velComp->vel.Z = facingForwardsBackwards.Z;
            velComp->vel.Y = 30;

            healthComp->HP -= DAMAGE_TRAIN; // TODO meter esto en el if de arriba?

            eventManager.postEvent<RefreshGUIBarsEvent>(healthComp->entityID);

            
        }
        else{

            pwupComp->stunned = true;
            pwupComp->stunnedCooldown = STUN_EFFECT_TRAIN;  
            // std::cout<<velComp->vel.X<<" . "<<velComp->vel.Z<<std::endl;

            float newPosZ = CollisionUtils::getZComponentsBBox(bbox).X;
            posComp->pos.Z = newPosZ - 20;
            posComp->pos.Y += 10;
            

            if(velComp->jumping)
                facingForwardsBackwards *= -200;
            else
                facingForwardsBackwards *= -400;

            velComp->jumping = true;
            dashComp->dashing = false;

            velComp->vel.X = facingForwardsBackwards.X;
            velComp->vel.Z = facingForwardsBackwards.Z;
            velComp->vel.Y = 30;

            healthComp->HP -= DAMAGE_TRAIN; // TODO meter esto en el if de arriba?

            eventManager.postEvent<RefreshGUIBarsEvent>(healthComp->entityID);

        }
    }

}

void CollisionPlayableSystem::detectSaw(const float frameDeltaTime, bool sense ,EventManager& eventManager, HealthComponent* healthComp, BBoxComponent* bboxComp, OBB2D bbox, VelocityComponent* velComp, PowerUpComponent* pwupComp, RotationComponent* rotComp, DashComponent* dashComp, PositionComponent* posComp, PositionComponent* posComp2, IrranimatednodeComponent* animatednodeComp){

    if(CollisionUtils::collides(bboxComp->body, bbox)){
        Vector3f* rot = &rotComp->rot;
        Vector3f facingForwardsBackwards( sin( ( rot->Y + 90.0f ) * M_PI/180.0f ), 0, cos( ( rot->Y + 90.0f ) * M_PI/180.0f ) );
        facingForwardsBackwards.normalize();

        if(sense){
            
            
            pwupComp->stunned = true;
            pwupComp->stunnedCooldown = STUN_EFFECT_TRAIN;  
            // std::cout<<velComp->vel.X<<" . "<<velComp->vel.Z<<std::endl;

            float newPosZ = CollisionUtils::getZComponentsBBox(bbox).Y;
            posComp->pos.Z = newPosZ + 20;
            posComp->pos.Y += 10;
            

            if(velComp->jumping)
                facingForwardsBackwards *= 200;
            else
                facingForwardsBackwards *= 400;

            velComp->jumping = true;
            dashComp->dashing = false;
            velComp->hitAir = true;
            

            velComp->vel.X = facingForwardsBackwards.X;
            velComp->vel.Z = facingForwardsBackwards.Z;
            velComp->vel.Y = 30;

            healthComp->HP -= DAMAGE_SAW; // TODO meter esto en el if de arriba?

            eventManager.postEvent<RefreshGUIBarsEvent>(healthComp->entityID);

            
        }
        else{

            pwupComp->stunned = true;
            pwupComp->stunnedCooldown = STUN_EFFECT_TRAIN;  
            // std::cout<<velComp->vel.X<<" . "<<velComp->vel.Z<<std::endl;

            float newPosZ = CollisionUtils::getZComponentsBBox(bbox).X;
            posComp->pos.Z = newPosZ - 20;
            posComp->pos.Y += 10;
            

            if(velComp->jumping)
                facingForwardsBackwards *= -200;
            else
                facingForwardsBackwards *= -400;

            velComp->jumping = true;
            dashComp->dashing = false;
            velComp->hitAir = true;

            velComp->vel.X = facingForwardsBackwards.X;
            velComp->vel.Z = facingForwardsBackwards.Z;
            velComp->vel.Y = 30;

            healthComp->HP -= DAMAGE_SAW; // TODO meter esto en el if de arriba?

            eventManager.postEvent<RefreshGUIBarsEvent>(healthComp->entityID);

        }
    }

}