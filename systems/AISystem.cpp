#include <AISystem.h>
#include <PlayerConstants.h>
#include <GameEnums.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <time.h>
#define PI 3.14159265

void AISystem::Init(SUMI::SUMIEngine& engine, GameStorage& gameStorage, int enemyID, int playerID){
	/////////////////////////////////////////////////////
	auto& playerEntity = gameStorage.getEntity(playerID);
    PositionComponent* pl_positionComp = static_cast<PositionComponent*>(playerEntity.require(COMPONENT_POSITION));
    if (!pl_positionComp) return;

	auto& enemyEntity = gameStorage.getEntity(enemyID);
	PositionComponent* en_positionComp = static_cast<PositionComponent*>(enemyEntity.require(COMPONENT_POSITION));
    if (!en_positionComp) return;
	BBoxComponent* en_bboxComp = static_cast<BBoxComponent*>(enemyEntity.require(COMPONENT_BBOX));
    if (!en_bboxComp) return;
	/////////////////////////////////////////////////////
	//Initialize vision bbox
	TAKO::Vector3f scale = TAKO::Vector3f(10, 2,2);
	TAKO::Vector3f rotation = TAKO::Vector3f(0,0,0);
	en_bboxComp->vision.node.setScale(scale);
	en_bboxComp->vision.node.setRotation(rotation);
	en_bboxComp->vision.node.setVisible(false);
	
	/*Estructura del árbol currently
			root(Sequence)
				  |
			   selector1
				  |
			⌐------------¬
		    |			 |
	   Isplayerfar	  selector2
	*/
	checkfar= Isplayerfar(gameStorage, enemyID, playerID);
    root->addChild (selector1);
	
	selector1->addChild (&checkfar);
	selector1->addChild (selector2);
	//timer=time(0);
	std::cout<<"Iniciando fuzzy logic"<<std::endl;
	//Life
	set.AddFunction("baja",0,0,20,-20,40,true);
	set.AddFunction("media",0,40,60,20,80,false);
	set.AddFunction("alta",0,80,100,60,120,false);
	//std::cout<<"funcion1"<<std::endl;
	//Stamine
	set.AddFunction("baja",0,0,20,-20,40,true);
	set.AddFunction("media",0,40,60,20,80,false);
	set.AddFunction("alta",0,80,100,60,120,false);
	//std::cout<<"funcion2"<<std::endl;
	//Fuzzy logic setting
	set.AddFunctionOutput(0,0,20,-20,40);
	set.AddFunctionOutput(0,40,60,20,80);
	set.AddFunctionOutput(0,80,100,60,120);
	//std::cout<<"salida"<<std::endl;
	//Rules
	std::vector<int> antecedents1{2,2};
	set.AddRule(antecedents1,0,2);
	std::vector<int> antecedents2{0,2};
	set.AddRule(antecedents2,0,1);
	std::vector<int> antecedents3{0,0};
	set.AddRule(antecedents3,0,0);
	//std::cout<<"todo añadido"<<std::endl;
	std::vector<double> input{45,55};
	double result=set.FuzzyProcess(input);
	//std::cout<<result<<std::endl;
}
void AISystem::Update(GameStorage& gameStorage, int enemyID, int playerID, EventManager& eventManager, const float frameDeltaTime){
	/////////// Guards ////////////
    auto& playerEntity = gameStorage.getEntity(playerID);
    PositionComponent* pl_positionComp = static_cast<PositionComponent*>(playerEntity.require(COMPONENT_POSITION));
    if (!pl_positionComp) return;
	BBoxComponent* pl_bboxComp = static_cast<BBoxComponent*>(playerEntity.require(COMPONENT_BBOX));
    if (!pl_bboxComp) return;
	VelocityComponent* pl_velocityComp = static_cast<VelocityComponent*>(playerEntity.require(COMPONENT_VELOCITY));
    if (!pl_velocityComp) return;
	DirectionComponent* pl_directionComp = static_cast<DirectionComponent*>(playerEntity.require(COMPONENT_DIRECTION));
    if (!pl_directionComp) return;
	DashComponent* pl_dashComp = static_cast<DashComponent*>(playerEntity.require(COMPONENT_DASH));
    if (!pl_dashComp) return;
	RotationComponent* pl_rotationComp = static_cast<RotationComponent*>(playerEntity.require(COMPONENT_ROTATION));
    if (!pl_rotationComp) return;

	auto& enemyEntity = gameStorage.getEntity(enemyID);
    PositionComponent* en_positionComp = static_cast<PositionComponent*>(enemyEntity.require(COMPONENT_POSITION));
    if (!en_positionComp) return;
	DashComponent* en_dashComp = static_cast<DashComponent*>(enemyEntity.require(COMPONENT_DASH));
    if (!en_dashComp) return;
	HealthComponent* en_healthComp = static_cast<HealthComponent*>(enemyEntity.require(COMPONENT_HEALTH));
    if (!en_healthComp) return;
	StaminaComponent* en_staminaComp = static_cast<StaminaComponent*>(enemyEntity.require(COMPONENT_STAMINA));
    if (!en_staminaComp) return;
	DirectionComponent* en_directionComp = static_cast<DirectionComponent*>(enemyEntity.require(COMPONENT_DIRECTION));
    if (!en_directionComp) return;
	VelocityComponent* en_velocityComp = static_cast<VelocityComponent*>(enemyEntity.require(COMPONENT_VELOCITY));
    if (!en_velocityComp) return;
	FistComponent* en_fistComp = static_cast<FistComponent*>(enemyEntity.require(COMPONENT_FIST));
    if (!en_fistComp) return;
	BBoxComponent* en_bboxComp = static_cast<BBoxComponent*>(enemyEntity.require(COMPONENT_BBOX));
    if (!en_bboxComp) return;
	IrranimatednodeComponent* en_animNode = static_cast<IrranimatednodeComponent*>(enemyEntity.require(COMPONENT_IRRANIMATEDNODE));
    if(!en_animNode) return;
    ///////////////////////////////

	
	
	while (!root->run());
	// std::cout << "--------------------" << std::endl;
	// std::cout << std::endl << "Sale del árbol" << std::endl;

	//State machine
	if(en_healthComp->HP<20){
		escape=true;
		jump=false;
		facing=false;
		follow=false;
		unlock=true;
		punch=true;
	}
	else{
		escape=false;
		jump=true;
		facing=true;
		follow=true;
		unlock=true;
		punch=true;
	}

	//Fuzzy Logic execute actions
	//Task behaviours programmed
	//Footies - Circle attack
	//Following
	//Run away
	//Power up hunt
	//Front attack and defense
	//Jump routines
	//Air punch routines

	float distance= sqrt(pow((en_positionComp->pos.X)-(pl_positionComp->pos.X),2)+
	pow((en_positionComp->pos.Z)-(pl_positionComp->pos.Z),2));
	//std::cout <<en_staminaComp->stamina<< std::endl;

	//Hacer que esté siempre mirando hacia tí
	//Tiempo de reacción para buscarle si acaba de hacer un dash
	if(facing){
		if(pl_dashComp->dashing==true || en_dashComp->dashing==true){
			turningtimer=clock();
			dash=true;
		}
		if(dash){
			if((clock()-turningtimer)>205000){
				if(distance>10){
					float x= pl_positionComp->pos.X - (en_positionComp->pos.X);
					float y= pl_positionComp->pos.Z - (en_positionComp->pos.Z);
					angleinc=atan2(y, x) *180/PI;
					en_directionComp->direction = -1*angleinc;
    				en_directionComp->zdirection =-1*angleinc;
					dash=false;
				}
			}
		}
		else{
			if(distance>10){
				float x= pl_positionComp->pos.X - (en_positionComp->pos.X);
				float y= pl_positionComp->pos.Z - (en_positionComp->pos.Z);
				angleinc=atan2(y, x) *180/PI;
				en_directionComp->direction = -1*angleinc;
    			en_directionComp->zdirection =-1*angleinc;
			}
		}
	}
	
	if(follow){
		if(distance>0 && distance<51){
			reactiontimer=clock();
		}
		if(distance>50 && pl_velocityComp->vel.Z==0 && pl_velocityComp->vel.X==0){
			if(!en_dashComp->dashing){
				en_velocityComp->vel.X=0;
			}
			if((clock()-reactiontimer)>50000){
				react=true;
			}
			if(react){
				en_velocityComp->vel.Z=MOVEMENT_SPEED;
			}
		}
		else{
			react=false;
			if(footies==true && distance>7){ //Footies
				en_velocityComp->vel.Z=20;
				en_velocityComp->vel.X=MOVEMENT_SPEED;
			}
			if(distance<7){
				//en_velocityComp->vel.Z=-600;
			}
		}

		for (auto& trainComp : gameStorage.getComponentsOfType<TrainComponent>()) {
			auto& trains = gameStorage.getEntity(trainComp.entityID);
        	/////////// Guards ////////////
        	PositionComponent* positionComp = static_cast<PositionComponent*>(trains.require(COMPONENT_POSITION));
        	if (!positionComp) continue;
        	///////////////////////////////
			int number = (trainComp.carriages/2);
			if(trainComp.carriages%2!=0){
				number++;
			}
			number--;
			//std::cout<<trainComp.bboxes[number].pos.X<<std::endl;
			if(trainComp.bboxes[number].pos.X!=0 && trainComp.bboxes[number].pos.X>-1300 && trainComp.bboxes[number].pos.X<900 && en_positionComp->pos.Z>-232 && en_positionComp->pos.Z<-60){
				unlock=false;
				en_velocityComp->vel.Z=0;
				en_directionComp->direction = 0;
				eventManager.postEvent<DashEvent>(enemyID, DashDirection::left);
			}
			else{
				unlock=true;
			}
		}

		for (auto& sawComp : gameStorage.getComponentsOfType<SawComponent>()) {
			float distancesaw= sqrt(pow((en_positionComp->pos.X)-(sawComp.nodes[0].getPosition().X),2)+
			pow((en_positionComp->pos.Z)-(sawComp.nodes[0].getPosition().Z),2)+
			pow((en_positionComp->pos.Y)-(sawComp.nodes[0].getPosition().Y),2));
			//std::cout<<distancesaw<<std::endl;
			if(distancesaw<60){
				//std::cout<<"escapar"<<std::endl;
				//en_directionComp->direction = -90;
				en_velocityComp->vel.Z=0;
				en_velocityComp->vel.X=-70;
			}
		}
	}

	if(jump){
		if(pl_positionComp->pos.Y>55){
			//footies=false;
			if(en_velocityComp->vel.Z!=0 && lastposrecordjump==en_positionComp->pos.Z){
				eventManager.postEvent<JumpEvent>(enemyID);
			}
			if(en_positionComp->pos.Y<pl_positionComp->pos.Y && lastposrecordjump==en_positionComp->pos.Z){
				eventManager.postEvent<JumpEvent>(enemyID);
				en_velocityComp->vel.Z=MOVEMENT_SPEED;
			}
			
		}
		else{
			//footies=true;
		}
		lastposrecordjump = en_positionComp->pos.Z;
	}

	if(punch){
		float angle = angleinc - 360*floor(angleinc/360);
		float plangle = pl_directionComp->direction - 360*floor(pl_directionComp->direction/360);
		 
		en_bboxComp->vision.node.setScale(TAKO::Vector3f(5, 2, 2));
		en_bboxComp->vision.node.setRotation(Vector3f(0 ,0, 0));
		en_bboxComp->vision.rot = Vector3f(0 ,0, 0);
		TAKO::Vector3f posChar  = en_positionComp->pos;
		en_bboxComp->vision.node.setPosition(Vector3f(posChar.X+40, posChar.Y+20, posChar.Z));
        en_bboxComp->vision.pos = Vector3f(posChar.X+40, posChar.Y+20, posChar.Z);
    	en_bboxComp->vision.pos = BBoxUtils::rotatePoint(en_bboxComp->vision.pos, en_positionComp->pos, (angle-en_bboxComp->vision.rot.Y));
    	en_bboxComp->vision.rot = Vector3f(0 ,angle, 0);
    	en_bboxComp->vision.node.setPosition(en_bboxComp->vision.pos);
    	en_bboxComp->vision.node.setRotation(Vector3f(0 ,angle, 0));
    	TAKO::Vector2f center = Vector2f(en_positionComp->pos.X, en_positionComp->pos.Z);
    	float w = en_bboxComp->vision.node.getScale().X * defaultBoxSize;
    	float h = en_bboxComp->vision.node.getScale().Z * defaultBoxSize;
    	BBoxUtils::rotate(en_bboxComp->vision, center, w, h, angle);
		BBoxUtils::calculateBBox(en_bboxComp->vision, en_bboxComp->vision.pos, en_bboxComp->vision.rot.Z, defaultBoxSize);

		bool collide = CollisionUtils::collides(en_bboxComp->vision,pl_bboxComp->body);
		if(en_positionComp->pos.Y<pl_positionComp->pos.Y){
			//eventManager.postEvent<PunchEvent>(enemyID, FistAction::block);
		} 
		if(collide){
			if(pl_bboxComp->hlf || pl_bboxComp->hrf){
				eventManager.postEvent<PunchEvent>(enemyID, FistAction::block);
			} 
			if(distance<36){
				int option=0;
				float plcompare=(plangle-180) - 360*floor((plangle-180)/360);

				if((angle-10)<plcompare && (angle+10)>plcompare){
					eventManager.postEvent<ChangeFistEvent>(enemyID, FistEnum::CROCHET);
				}
				else{
					eventManager.postEvent<ChangeFistEvent>(enemyID, FistEnum::DIRECT);
				}
				if(option==0){
        			if(lastFist != FistAction::right){
            			eventManager.postEvent<PunchEvent>(enemyID, FistAction::resetTimer);
            			lastFist = FistAction::right;
					}
        			eventManager.postEvent<PunchEvent>(enemyID, FistAction::right);
    			} 
				else if(option==1){
        			if(lastFist != FistAction::left){
            			eventManager.postEvent<PunchEvent>(enemyID, FistAction::resetTimer);
            			lastFist = FistAction::left;
        			}
       			 	eventManager.postEvent<PunchEvent>(enemyID, FistAction::left);
   				}
			}
			else{
				lastFist = FistAction::resetTimer; 
			}
			
		}
	}

	//std::cout <<pl_positionComp->pos.X<<" "<<pl_positionComp->pos.Z<<" "<<pl_positionComp->pos.Y<< std::endl;
	//Desbloqueo de emergencia de la IA
	if(unlock){
		if(lastposrecordlock != (int)en_positionComp->pos.Z){
			safetytimer=time(0);
			unlocktry=0;
		}
		else{
			if((time(0)-safetytimer)>2){
				eventManager.postEvent<JumpEvent>(enemyID);
				unlocktry=1;
			}
			
		}
		if(unlocktry==2){
			//std::cout <<"left"<< std::endl;
			eventManager.postEvent<DashEvent>(enemyID, DashDirection::left);
			unlocktry=0;
		}
		if(unlocktry==1){
			//std::cout <<"right"<< std::endl;
			eventManager.postEvent<DashEvent>(enemyID, DashDirection::right);
			unlocktry=2;
		}
		lastposrecordlock = (int)en_positionComp->pos.Z;
	}
	

	if(escape){
		en_bboxComp->vision.node.setScale(TAKO::Vector3f(13, 2, 2));
		facing=false;
		if(escapesearch){
			float angle=-1;
			float maxdistance=-1;
			for(int i=0;i<360;i++){
				en_bboxComp->vision.node.setRotation(Vector3f(0 ,0, 0));
				en_bboxComp->vision.rot = Vector3f(0 ,0, 0);
				TAKO::Vector3f posChar  = en_positionComp->pos;
				en_bboxComp->vision.node.setPosition(Vector3f(posChar.X+65, posChar.Y+20, posChar.Z));
        		en_bboxComp->vision.pos = Vector3f(posChar.X+65, posChar.Y+20, posChar.Z);
    			en_bboxComp->vision.pos = BBoxUtils::rotatePoint(en_bboxComp->vision.pos, en_positionComp->pos, (i-en_bboxComp->vision.rot.Y));
    			en_bboxComp->vision.rot = Vector3f(0 ,i, 0);
    			en_bboxComp->vision.node.setPosition(en_bboxComp->vision.pos);
    			en_bboxComp->vision.node.setRotation(Vector3f(0 ,i, 0));
    			TAKO::Vector2f center = Vector2f(en_positionComp->pos.X, en_positionComp->pos.Z);
    			float w = en_bboxComp->vision.node.getScale().X * defaultBoxSize;
    			float h = en_bboxComp->vision.node.getScale().Z * defaultBoxSize;
    			BBoxUtils::rotate(en_bboxComp->vision, center, w, h, i);
				BBoxUtils::calculateBBox(en_bboxComp->vision, en_bboxComp->vision.pos, en_bboxComp->vision.rot.Z, defaultBoxSize);

				bool collideprop=false;
				for(auto& bboxComp2 : gameStorage.getComponentsOfType<BBoxPropsComponent>()){
					auto& entity2 = gameStorage.getEntity(bboxComp2.entityID);

					collideprop=CollisionUtils::collides(en_bboxComp->vision, bboxComp2.body);
					if(collideprop){
						break;
					}
				}
				bool collidepl=CollisionUtils::collides(en_bboxComp->vision,pl_bboxComp->body);

				if(!collideprop && !collidepl){
					
					float xx = en_positionComp->pos.X + (20 * cos(i* PI/180));
					float zz = en_positionComp->pos.Z + (20 * sin(i* PI/180));
					float distance= sqrt(pow((xx)-(pl_positionComp->pos.X),2)+
					pow((zz)-(pl_positionComp->pos.Z),2));
					if(distance>maxdistance){
						xxescape=xx;
						zzescape=zz;
						maxdistance=distance;
						angle=i;
						
					}
				}
			}
			if(angle!=-1){
				double closeangle = (int)(angle - en_directionComp->direction) % 360;
				//std::cout <<escapecounter<< std::endl;
				if(std::abs(closeangle)>170) {
					escapecounter++; 
				}
				else{
					escapecounter=0;
				}
				
				if(escapecounter>50){
					en_directionComp->direction = en_directionComp->direction;
    				en_directionComp->zdirection = en_directionComp->zdirection;
					en_velocityComp->vel.Z=0;
				}
				else{
					en_directionComp->direction = -1*angle;
    				en_directionComp->zdirection = -1*angle;
					en_velocityComp->vel.Z=MOVEMENT_SPEED;
				}
				
				
				
				//Debugging bbox

				en_bboxComp->vision.node.setRotation(Vector3f(0 ,0, 0));
				en_bboxComp->vision.rot = Vector3f(0 ,0, 0);
				TAKO::Vector3f posChar  = en_positionComp->pos;
				en_bboxComp->vision.node.setPosition(Vector3f(posChar.X+65, posChar.Y+20, posChar.Z));
        		en_bboxComp->vision.pos = Vector3f(posChar.X+65, posChar.Y+20, posChar.Z);
    			en_bboxComp->vision.pos = BBoxUtils::rotatePoint(en_bboxComp->vision.pos, en_positionComp->pos, (angle-en_bboxComp->vision.rot.Y));
    			en_bboxComp->vision.rot = Vector3f(0 ,angle, 0);
    			en_bboxComp->vision.node.setPosition(en_bboxComp->vision.pos);
    			en_bboxComp->vision.node.setRotation(Vector3f(0 ,angle, 0));
    			TAKO::Vector2f center = Vector2f(en_positionComp->pos.X, en_positionComp->pos.Z);
    			float w = en_bboxComp->vision.node.getScale().X * defaultBoxSize;
    			float h = en_bboxComp->vision.node.getScale().Z * defaultBoxSize;
    			BBoxUtils::rotate(en_bboxComp->vision, center, w, h, angle);
				BBoxUtils::calculateBBox(en_bboxComp->vision, en_bboxComp->vision.pos, en_bboxComp->vision.rot.Z, defaultBoxSize);
			}
			else{
				en_velocityComp->vel.Z=0;

			}
			
				
		}
		//std::cout <<xxescape<<" "<<en_positionComp->pos.X<<" "<<zzescape<<" "<<en_positionComp->pos.Z<< std::endl;
		//std::cout <<en_positionComp->pos.X<<" "<<en_positionComp->pos.Z<<" "<<en_positionComp->pos.Y<< std::endl;
		if((xxescape-10)<en_positionComp->pos.X && en_positionComp->pos.X<(xxescape+10) && (zzescape-10)<en_positionComp->pos.Z && en_positionComp->pos.Z<(zzescape+10)){
			en_velocityComp->vel.Z=0;
			escapesearch=true;
		}
		else{
			en_velocityComp->vel.Z=MOVEMENT_SPEED;
		}
	}


}
