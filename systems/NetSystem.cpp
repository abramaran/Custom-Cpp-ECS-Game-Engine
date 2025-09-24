#include <NetSystem.h>
#include <PlayerConstants.h>
#include <Enums.h>
#include <GameEnums.h>
#include <fcntl.h>
#include <thread>
namespace TAKO{
    /*Packet Codes for the server:
    Each numerical code trigger a different action in the server part.
    - 5: Match initial conection.
    - 503: End of the match
    - 24: Create room
    - 25: Search existing room
    - 26: Host going out rooms menu, order to destroy room in server
    - 27: Request to add 2nd player to room
    - 28: Send stage selection to 2nd player
    - 29: Exchange of character selection
    - 30: Ready to start match after character selection
    - 300: Regular player state update package
    */
    void NetSystem::Init(GameStorage& gameStorage, int enemyID, int playerID){
        /////////// Guards ////////////
        auto& playerEntity = gameStorage.getEntity(playerID);
        PositionComponent* pl_positionComp = static_cast<PositionComponent*>(playerEntity.require(COMPONENT_POSITION));
        if (!pl_positionComp) return;
        DirectionComponent* pl_directionComp = static_cast<DirectionComponent*>(playerEntity.require(COMPONENT_DIRECTION));
        if (!pl_directionComp) return;

        auto& enemyEntity = gameStorage.getEntity(enemyID);
        PositionComponent* en_positionComp = static_cast<PositionComponent*>(enemyEntity.require(COMPONENT_POSITION));
        if (!en_positionComp) return;
        DirectionComponent* en_directionComp = static_cast<DirectionComponent*>(enemyEntity.require(COMPONENT_DIRECTION));
        if (!en_directionComp) return;
        ///////////////////////////////
        
        //Inicio de conexion con servidor provisional
        id=5; //5 significa id aún no asignado
        unsigned int buffer[80];
        int bytes_written=0;
        memcpy( &buffer[bytes_written], &id, sizeof( id ) );
        bytes_written += sizeof( id );
        float x= pl_positionComp->pos.X;
        memcpy( &buffer[bytes_written], &x, sizeof( x ) );
        bytes_written += sizeof( x );
        float y= pl_positionComp->pos.Z;
        memcpy( &buffer[bytes_written], &y, sizeof( y ) );
        bytes_written += sizeof( y );
        float facing=pl_directionComp->direction;
        memcpy( &buffer[bytes_written], &facing, sizeof( facing ) );
        bytes_written += sizeof( facing );

        
        int sendOk= sendto(out, buffer, sizeof(buffer), 0, (sockaddr*)&server, sizeof(server)); //For TCP send() is used
    }

    void NetSystem::InitMulti(){

        server.sin_family= AF_INET;
        server.sin_port= htons(54000);

        inet_pton(AF_INET, "127.0.0.1", &server.sin_addr); //66.175.211.92

        //Socket creation
        out= socket(AF_INET, SOCK_DGRAM, 0);    
        
        //Make socket non-blocking
        int status = fcntl(out, F_SETFL, fcntl(out, F_GETFL, 0) | O_NONBLOCK);
            if (status == -1){
                perror("calling fcntl");
            // handle the error.  By the way, I've never seen fcntl fail in this way
        }

    }

    void NetSystem::InitCreateRoom(){   
        std::cout<<"Sending request to create room"<<std::endl;
        int code=24;
        unsigned int buffer[80];
        int bytes_written=0;
        memcpy( &buffer[bytes_written], &code, sizeof( code ) );
        bytes_written += sizeof( code );
        int sendOk= sendto(out, buffer, sizeof(buffer), 0, (sockaddr*)&server, sizeof(server)); //For TCP send() is used


    }

    void NetSystem::InitWaitScreen(){   
        std::cout<<"Sending request to add 2nd player to room, waiting for host"<<std::endl;
        int code=27;
        unsigned int buffer[80];
        int bytes_written=0;
        memcpy( &buffer[bytes_written], &code, sizeof( code ) );
        bytes_written += sizeof( code );
        memcpy( &buffer[bytes_written], &room_id, sizeof( room_id ) );
        bytes_written += sizeof( room_id );
        int sendOk= sendto(out, buffer, sizeof(buffer), 0, (sockaddr*)&server, sizeof(server)); //For TCP send() is used
    }

    void NetSystem::SelectCharUpdate(Characters& currentcharacter, Characters& currentenemy, GameStorage& gameStorage, SUMIEngine& engine, bool& changeState, StateEnum& nextState){
        //Send current selection to the other player
        unsigned int buffer[80];
        int bytes_written=0;
        int packagecode=29;
        memcpy( &buffer[bytes_written], &packagecode, sizeof( packagecode ) );
        bytes_written += sizeof( packagecode );
        memcpy( &buffer[bytes_written], &room_id, sizeof( room_id ) );
        bytes_written += sizeof( room_id );
        memcpy( &buffer[bytes_written], &id, sizeof( id ) );
        bytes_written += sizeof( id );

        int character=-1;
        if(currentcharacter==Characters::PUNCHIES){
            character=0;
        }
        if(currentcharacter==Characters::BOSS1){
            character=1;
        }
        if(currentcharacter==Characters::BOSS2){
            character=2;
        }
        memcpy( &buffer[bytes_written], &character, sizeof( character ) );
        bytes_written += sizeof( character );

        int sendOk= sendto(out, buffer, sizeof(buffer), 0, (sockaddr*)&server, sizeof(server)); //For TCP send() is used

        //Receive enemy selection
        memset(buffer, 0, 80);
        int serverLenght = sizeof(server);
        unsigned int len= serverLenght;
        int bytes_received = recvfrom(out, &buffer, sizeof(buffer), 0,(sockaddr*)&server, &len);
        if(bytes_received!=-1){
            unsigned int bytes_read=0;
            int packagecode=-1;
            memcpy(&packagecode, &buffer[bytes_read], sizeof(packagecode));
            bytes_read += sizeof(packagecode);
            if(packagecode==29){
                int character=-1;
                memcpy(&character, &buffer[bytes_read], sizeof(character));
                bytes_read += sizeof(character);

                if(character==0){
                    currentenemy=Characters::PUNCHIES;
                    for(auto &tagplayer : gameStorage.getComponentsOfType<TagPlayable>()){
                        auto& entity = gameStorage.getEntity(tagplayer.entityID);
                        IrrbasicnodeComponent* basicnodeComp = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
                        if (!basicnodeComp) continue;
                        engine.changeMaterial(basicnodeComp->node, "media/Menu/Portraits/Punchies.png");
                    }
                }
                if(character==1){
                    currentenemy=Characters::BOSS1;
                    for(auto &tagplayer : gameStorage.getComponentsOfType<TagPlayable>()){
                        auto& entity = gameStorage.getEntity(tagplayer.entityID);
                        IrrbasicnodeComponent* basicnodeComp = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
                        if (!basicnodeComp) continue;
                        engine.changeMaterial(basicnodeComp->node, "media/Menu/Portraits/Dva.png");
                    }
                }
                if(character==2){
                    currentenemy=Characters::BOSS2;
                    for(auto &tagplayer : gameStorage.getComponentsOfType<TagPlayable>()){
                        auto& entity = gameStorage.getEntity(tagplayer.entityID);
                        IrrbasicnodeComponent* basicnodeComp = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
                        if (!basicnodeComp) continue;
                        engine.changeMaterial(basicnodeComp->node, "media/Menu/Portraits/IA.png");
                    }
                }

            }
            if(packagecode==30){
            //Received confirmation of server to start game state
                changeState=true;
                nextState=StateEnum::STARTMULTI;
            }
        }

        //Send the value of the confirm button
        for (auto& netComp : gameStorage.getComponentsOfType<NetComponent>()){
            if(netComp.statelessbutton==true){
                if(netComp.statelessclick==true){
                    auto& entity = gameStorage.getEntity(netComp.entityID);
                    IrrbasicnodeComponent* basicnodeComp = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
                    if (!basicnodeComp) continue;
                    engine.changeMaterial(basicnodeComp->node,"media/Menu/Buttons/Fijar_Lock.png");
                    for (auto& event : gameStorage.getEventsOfType<OptionSelectedEvent>()) {
                        for (auto& mouseOverComp : gameStorage.getComponentsOfType<MouseOverComponent>()) {
                            //////////////////////////////////////////////////////
                            auto& entity = gameStorage.getEntity(mouseOverComp.entityID);
                            NetComponent* netComp = static_cast<NetComponent*>(entity.require(COMPONENT_NET));
                            if (!netComp) return;
                            //////////////////////////////////////////////////////
                            netComp->codeReady=false;
                        }
                    }

                    //Send message of ready to server
                    int code=30;
                    unsigned int buffer[80];
                    int bytes_written=0;
                    memcpy( &buffer[bytes_written], &code, sizeof( code ) );
                    bytes_written += sizeof( code );
                    memcpy( &buffer[bytes_written], &room_id, sizeof( room_id ) );
                    bytes_written += sizeof( room_id );
                    memcpy( &buffer[bytes_written], &id, sizeof( id ) );
                    bytes_written += sizeof( id );
                    int sendOk= sendto(out, buffer, sizeof(buffer), 0, (sockaddr*)&server, sizeof(server)); //For TCP send() is used
                }
            }
        }
    }

    void NetSystem::SelectStageUpdate(int mode, bool& changeState, StateEnum& nextState, Levels& level){
        //Mode 0: Host screen - Mode 1: Wait Screen
        if(mode==0){
            //Send stage selection as host to the other client
            if(changeState==true && nextState==StateEnum::SELECPERSONAJE_M){
                unsigned int buffer[80];
                int bytes_written=0;
                int code=28;
                memcpy( &buffer[bytes_written], &code, sizeof( code ) );
                bytes_written += sizeof( code );
                memcpy( &buffer[bytes_written], &room_id, sizeof( room_id ) );
                bytes_written += sizeof( room_id );
                int levelcode=-1;
                if(level==Levels::STATION){
                    levelcode=0;
                }
                if(level==Levels::FACTORY){
                    levelcode=1;
                }
                memcpy( &buffer[bytes_written], &levelcode, sizeof( levelcode ) );
                bytes_written += sizeof( levelcode );

                int sendOk= sendto(out, buffer, sizeof(buffer), 0, (sockaddr*)&server, sizeof(server)); //For TCP send() is used
            }
        } 
        if(mode==1){
            //Wait for messages
            unsigned int buffer[80];
            int serverLenght = sizeof(server);
            unsigned int len= serverLenght;
            int bytes_received = recvfrom(out, &buffer, sizeof(buffer), 0,(sockaddr*)&server, &len);
            if(bytes_received!=-1){
                unsigned int bytes_read=0;
                int packagecode=-1;
                memcpy(&packagecode, &buffer[bytes_read], sizeof(packagecode));
                bytes_read += sizeof(packagecode);

                if(packagecode==26){ //The host has disconnected, reset everything and return to multiplayer main menu
                    std::cout<<"Going out multiplayer, host disconnected"<<std::endl;
                    keyInput="";
                    activated=false;
                    room_id=-1;
                    id=-1;
                    changeState=true;
                    nextState=StateEnum::OPCIONESSALA;
                }

                if(packagecode==28){ //We receive the stage selection from the host, change to character selection
                    int stage=-1;
                    memcpy(&stage, &buffer[bytes_read], sizeof(stage));
                    bytes_read += sizeof(stage);

                    if(stage==0){
                        level=Levels::STATION;
                    }
                    if(stage==1){
                        level=Levels::FACTORY;
                    }
                    changeState=true;
                    nextState=StateEnum::SELECPERSONAJE_M;
                }
            }

        } 
    }

    void NetSystem::SetRoomUpdate(int mode, std::size_t confirmbutton_ID, GameStorage& gameStorage, SUMIEngine& engine, float& frameDeltaTime,  bool& changeState, StateEnum& nextState){
        //Mode 0: Create room - Mode 1: Search room  
        if(mode==0){
        ///////////////////////////////////////////////
        auto entity = gameStorage.getEntity(confirmbutton_ID);
        MouseOverComponent* mouseOverComp = static_cast<MouseOverComponent*>(entity.require(COMPONENT_MOUSEOVER));
        if (!mouseOverComp) return;
        NetComponent* netComp = static_cast<NetComponent*>(entity.require(COMPONENT_NET));
        if (!netComp) return;
        ///////////////////////////////////////////////
        //Button disabled by default
        if(!activated){
        netComp->codeReady=false;}
        //Wait for reply
        unsigned int buffer[80];
        int serverLenght = sizeof(server);
        unsigned int len= serverLenght;
        int bytes_received = recvfrom(out, &buffer, sizeof(buffer), 0,(sockaddr*)&server, &len);
        if(bytes_received!=-1){
            unsigned int bytes_read=0;
            int packagecode=-1;
            memcpy(&packagecode, &buffer[bytes_read], sizeof(packagecode));
            bytes_read += sizeof(packagecode);
            //Packagecode 0: Room created, assign room_id - Packagecode 1: Second player connected, unblock confirm button
            if(packagecode==0){
                memcpy(&room_id, &buffer[bytes_read], sizeof(room_id));
                bytes_read += sizeof(room_id);
                memcpy(&id, &buffer[bytes_read], sizeof(id));
                bytes_read += sizeof(id);
                //Show on screen
                for (auto& showNumberComp : gameStorage.getComponentsOfType<ShowNumberComponent>()){
                    //////////////////////////////////////////////////////////////
                    auto& entity = gameStorage.getEntity(showNumberComp.entityID);
                    IrrbasicnodeComponent* basicnodeComp = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
                    if (!basicnodeComp) continue;
                    /////////////////////////////////////////////////////////////
                    
                    if(showNumberComp.numberindex==0){
                        std::string aux=std::to_string(room_id);
                        aux=aux.substr(0,1);
                        engine.changeMaterial(basicnodeComp->node,"media/Menu/Numbers/"+aux+".png");
                    }
                    if(showNumberComp.numberindex==1){
                        std::string aux=std::to_string(room_id);
                        aux=aux.substr(1,1);
                        engine.changeMaterial(basicnodeComp->node,"media/Menu/Numbers/"+aux+".png");
                    }
                    if(showNumberComp.numberindex==2){
                        std::string aux=std::to_string(room_id);
                        aux=aux.substr(2,1);
                        engine.changeMaterial(basicnodeComp->node,"media/Menu/Numbers/"+aux+".png");
                    }
                    if(showNumberComp.numberindex==3){
                        std::string aux=std::to_string(room_id);
                        aux=aux.substr(3,1);
                        engine.changeMaterial(basicnodeComp->node,"media/Menu/Numbers/"+aux+".png");
                    }
                }
            }
            if(packagecode==1){
                netComp->codeReady=true;
                activated=true;
            }
        }

        if(netComp->codeReady==true){
            mouseOverComp->SeletctedTexture="media/Menu/Buttons/Entrar_S.png";
            mouseOverComp->notSelectedTexture="media/Menu/Buttons/Entrar.png";
        }
        if(netComp->codeReady==false){
            mouseOverComp->SeletctedTexture="media/Menu/Buttons/Entrar_Lock.png";
            mouseOverComp->notSelectedTexture="media/Menu/Buttons/Entrar_Lock.png";
        }

        //We are going out of multiplayer, order to destroy the room we created
        if(changeState==1 && nextState==0){
            std::cout<<"Please destroy the room "<<room_id<<std::endl;

            memset(buffer, 0, 80);
            int bytes_written=0;
            int code=26;
            memcpy( &buffer[bytes_written], &code, sizeof( code ) );
            bytes_written += sizeof( code );
            memcpy( &buffer[bytes_written], &room_id, sizeof( room_id ) );
            bytes_written += sizeof( room_id );
          
            int sendOk= sendto(out, buffer, sizeof(buffer), 0, (sockaddr*)&server, sizeof(server));
            //Reset room id
            room_id=-1;
        }
        }

        if(mode==1){
            ///////////////////////////////////////////////
            auto entity = gameStorage.getEntity(confirmbutton_ID);
            MouseOverComponent* mouseOverComp = static_cast<MouseOverComponent*>(entity.require(COMPONENT_MOUSEOVER));
            if (!mouseOverComp) return;
            NetComponent* netComp = static_cast<NetComponent*>(entity.require(COMPONENT_NET));
            if (!netComp) return;
            ///////////////////////////////////////////////
            //Button disabled by default
            netComp->codeReady=false;
            keyTime += frameDeltaTime;
            if(keyTime > 0.2){
                keyTime = 0.2;
            }
            if (engine.IsKeyDown(Key::KEY_0) && keyTime > 0.2){
                keyTime = 0;
                if(keyInput.length()<4){
                    keyInput.push_back('0');
                }
            }
            if (engine.IsKeyDown(Key::KEY_1) && keyTime > 0.2){
                keyTime = 0;
                if(keyInput.length()<4){
                    keyInput.push_back('1');
                }
            }
            if (engine.IsKeyDown(Key::KEY_2) && keyTime > 0.2){
                keyTime = 0;
                if(keyInput.length()<4){
                    keyInput.push_back('2');
                }
            }
            if (engine.IsKeyDown(Key::KEY_3) && keyTime > 0.2){
                keyTime = 0;
                if(keyInput.length()<4){
                    keyInput.push_back('3');
                }
            }
            if (engine.IsKeyDown(Key::KEY_4) && keyTime > 0.2){
                keyTime = 0;
                if(keyInput.length()<4){
                    keyInput.push_back('4');
                }
            }
            if (engine.IsKeyDown(Key::KEY_5) && keyTime > 0.2){
                keyTime = 0;
                if(keyInput.length()<4){
                    keyInput.push_back('5');
                }
            }
            if (engine.IsKeyDown(Key::KEY_6) && keyTime > 0.2){
                keyTime = 0;
                if(keyInput.length()<4){
                    keyInput.push_back('6');
                }
            }
            if (engine.IsKeyDown(Key::KEY_7) && keyTime > 0.2){
                keyTime = 0;
                if(keyInput.length()<4){
                    keyInput.push_back('7');
                }
            }
            if (engine.IsKeyDown(Key::KEY_8) && keyTime > 0.2){
                keyTime = 0;
                if(keyInput.length()<4){
                    keyInput.push_back('8');
                }
            }
            if (engine.IsKeyDown(Key::KEY_9) && keyTime > 0.2){
                keyTime = 0;
                if(keyInput.length()<4){
                    keyInput.push_back('9');
                }
            }
            if (engine.IsKeyDown(Key::KEY_BACKSPACE) && keyTime > 0.2){
                keyTime = 0;
                if(keyInput.length()>0){
                    keyInput.pop_back();
                }
            }
            //Show on screen
            for (auto& showNumberComp : gameStorage.getComponentsOfType<ShowNumberComponent>()){
                //////////////////////////////////////////////////////////////
                auto& entity = gameStorage.getEntity(showNumberComp.entityID);
                IrrbasicnodeComponent* basicnodeComp = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
                if (!basicnodeComp) continue;
                /////////////////////////////////////////////////////////////
                engine.changeMaterial(basicnodeComp->node,"media/Menu/Numbers/none.png");    
            }
            for(int i=0;i<keyInput.length();i++){
                 for (auto& showNumberComp : gameStorage.getComponentsOfType<ShowNumberComponent>()){
                    //////////////////////////////////////////////////////////////
                    auto& entity = gameStorage.getEntity(showNumberComp.entityID);
                    IrrbasicnodeComponent* basicnodeComp = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
                    if (!basicnodeComp) continue;
                    /////////////////////////////////////////////////////////////
                    if(showNumberComp.numberindex==i){
                        std::string aux=keyInput.substr(i,1);
                        engine.changeMaterial(basicnodeComp->node,"media/Menu/Numbers/"+aux+".png");
                    }
                 }
            }
            int compare=-1;
            if(keyInput.length()==4){
                compare=stoi(keyInput);
                if(compare==room_id){
                    netComp->codeReady=true;
                    }
            }
            //std::cout<<keyInput<<std::endl;
            if(netComp->codeReady==true){
                mouseOverComp->SeletctedTexture="media/Menu/Buttons/Entrar_S.png";
                mouseOverComp->notSelectedTexture="media/Menu/Buttons/Entrar.png";
            }
            if(netComp->codeReady==false){
                mouseOverComp->SeletctedTexture="media/Menu/Buttons/Entrar_Lock.png";
                mouseOverComp->notSelectedTexture="media/Menu/Buttons/Entrar_Lock.png";
            }

            //Ask for correct room codes to the server
            unsigned int buffer[80];
            int bytes_written=0;
            int packagecode=25;
            memcpy( &buffer[bytes_written], &packagecode, sizeof( packagecode ) );
            bytes_written += sizeof( packagecode );
            memcpy( &buffer[bytes_written], &compare, sizeof( compare ) );
            bytes_written += sizeof( compare );
            int sendOk= sendto(out, buffer, sizeof(buffer), 0, (sockaddr*)&server, sizeof(server)); //For TCP send() is used

            //Receive answer to question
            memset(buffer, 0, 80);
            int serverLenght = sizeof(server);
            unsigned int len= serverLenght;
            int bytes_received = recvfrom(out, &buffer, sizeof(buffer), 0,(sockaddr*)&server, &len);
            if(bytes_received!=-1){
            unsigned int bytes_read=0;
            int roomanswer=-1; //Default
            memcpy(&roomanswer, &buffer[bytes_read], sizeof(roomanswer));
            bytes_read += sizeof(roomanswer);
            if(roomanswer==0){
                if(keyInput.length()==4){
                room_id=stoi(keyInput);}
                id=1;
                netComp->codeReady=true;
                //std::cout<<"My room code is: "<<room_id<<std::endl;
            }

        }
        }
    }

    void NetSystem::Update(SUMI::SUMIEngine& receiver, EventManager& eventManager, GameStorage& gameStorage, int enemyID, int playerID, EntityManager& entManager, bool& changeState, StateEnum& nextState){
        /////////// Guards ////////////
        auto& playerEntity = gameStorage.getEntity(playerID);
        PositionComponent* pl_positionComp = static_cast<PositionComponent*>(playerEntity.require(COMPONENT_POSITION));
        if (!pl_positionComp) return;
        DirectionComponent* pl_directionComp = static_cast<DirectionComponent*>(playerEntity.require(COMPONENT_DIRECTION));
        if (!pl_directionComp) return;
        VelocityComponent* pl_velocityComp = static_cast<VelocityComponent*>(playerEntity.require(COMPONENT_VELOCITY));
        if (!pl_velocityComp) return;
        FistComponent* pl_fistComp = static_cast<FistComponent*>(playerEntity.require(COMPONENT_FIST));
        if (!pl_fistComp) return;
        NetComponent* pl_netComp = static_cast<NetComponent*>(playerEntity.require(COMPONENT_NET));
        if (!pl_netComp) return;

        auto& enemyEntity = gameStorage.getEntity(enemyID);
        PositionComponent* en_positionComp = static_cast<PositionComponent*>(enemyEntity.require(COMPONENT_POSITION));
        if (!en_positionComp) return;
        DirectionComponent* en_directionComp = static_cast<DirectionComponent*>(enemyEntity.require(COMPONENT_DIRECTION));
        if (!en_directionComp) return;
        VelocityComponent* en_velocityComp = static_cast<VelocityComponent*>(enemyEntity.require(COMPONENT_VELOCITY));
        if (!en_velocityComp) return;
        FistComponent* en_fistComp = static_cast<FistComponent*>(enemyEntity.require(COMPONENT_FIST));
        if (!en_fistComp) return;
        ///////////////////////////////
        
        unsigned int buffer[80];

        //Wait for reply
        int serverLenght = sizeof(server);
        unsigned int len= serverLenght;

        //Flag to know we are receiving from other player (to send power ups)
        bool connectedplayer=false;
        //Assign id to component for power up generation 
        pl_netComp->OnlineID=id;

        int bytes_received = recvfrom(out, &buffer, sizeof(buffer), 0,(sockaddr*)&server, &len);
        if(bytes_received!=-1){ //Hemos recibido algo in fact
            
            unsigned int bytes_read=0;
            int who=7; //Default
            memcpy(&who, &buffer[bytes_read], sizeof(who));
            bytes_read += sizeof(who);
            
            if(who==30){

            }
            if(who==300){ //Procesar mensaje normal de actualizacion posicion enemiga
                connectedplayer=true;
                int roomcode=-1;
                memcpy(&roomcode, &buffer[bytes_read], sizeof(roomcode));
                bytes_read += sizeof(roomcode);
                int enemyid=-1;
                memcpy(&enemyid, &buffer[bytes_read], sizeof(enemyid));
                bytes_read += sizeof(enemyid);
                float x=7;
                memcpy(&x, &buffer[bytes_read], sizeof(x));
                bytes_read += sizeof(x);
                en_positionComp->pos.X=x;
                float y=7;
                memcpy(&y, &buffer[bytes_read], sizeof(y));
                bytes_read += sizeof(y);
                en_positionComp->pos.Z=y;
                float facing=0;
                memcpy(&facing, &buffer[bytes_read], sizeof(facing));
                bytes_read += sizeof(facing);
                en_directionComp->direction = facing;
                en_directionComp->zdirection = facing;
                float z=0;
                memcpy(&z, &buffer[bytes_read], sizeof(z));
                bytes_read += sizeof(z);
                en_positionComp->pos.Y=z;
                float right=3;
                memcpy(&right, &buffer[bytes_read], sizeof(right));
                bytes_read += sizeof(right);
                float left=3;
                memcpy(&left, &buffer[bytes_read], sizeof(left));
                bytes_read += sizeof(left);
                bool jump=false;
                bool block=false;
                memcpy(&jump, &buffer[bytes_read], sizeof(jump));
                bytes_read += sizeof(jump);
                memcpy(&block, &buffer[bytes_read], sizeof(block));
                bytes_read += sizeof(block);
                en_velocityComp->jumping=jump;
                en_velocityComp->blocking=block;
                if(right==1){
                    if(lastFist != FistAction::right){
            			eventManager.postEvent<PunchEvent>(enemyID, FistAction::resetTimer);
            			lastFist = FistAction::right;
					}
        			eventManager.postEvent<PunchEvent>(enemyID, FistAction::right);
                }
                else if(left==1){
                    if(lastFist != FistAction::left){
            			eventManager.postEvent<PunchEvent>(enemyID, FistAction::resetTimer);
            			lastFist = FistAction::left;
        			}
       			 	eventManager.postEvent<PunchEvent>(enemyID, FistAction::left);
                }
                else {
                   lastFist = FistAction::resetTimer; 
                }
                //Change punch
                int punchid=0;
                memcpy(&punchid, &buffer[bytes_read], sizeof(punchid));
                bytes_read += sizeof(punchid);
                if(punchid==1){
                    eventManager.postEvent<ChangeFistEvent>(enemyID, FistEnum::DIRECT);
                }
                else if(punchid==2){
                    eventManager.postEvent<ChangeFistEvent>(enemyID, FistEnum::CROCHET);
                }
                else if(punchid==3){
                    eventManager.postEvent<ChangeFistEvent>(enemyID, FistEnum::UPPERCUT);
                }
                //Si soy player 2 debo recibir la creacion de power ups
                int index=0;
                memcpy(&index, &buffer[bytes_read], sizeof(index));
                bytes_read += sizeof(index);
                //If the index is too big, maybe due to an error
                if(id==1 && index<20){    
                    for(int i=0;i<index;i++){
                    int type=0;
                    int pos=0;
                    memcpy(&type, &buffer[bytes_read], sizeof(type));
                    bytes_read += sizeof(type);
                    memcpy(&pos, &buffer[bytes_read], sizeof(pos));
                    bytes_read += sizeof(pos);
                    //std::cout<<type<<" "<<pos<<std::endl;
                    for(auto& spawnPointComp : gameStorage.getComponentsOfType<SpawnPointsComponent>()){
                    
                    entManager.generatePowerUpOnline(type,pos, spawnPointComp.positions);
                        }
                    }
                }
            }
            //std::cout<<bytes_read<<std::endl;
        }


        //New buffer
        memset(buffer, 0, 80);

        //Write out to that socket
        unsigned int bytes_written=0;
        int packagecode=300; //Player state update
        memcpy( &buffer[bytes_written], &packagecode, sizeof( packagecode ) );
        bytes_written += sizeof( packagecode );
        memcpy( &buffer[bytes_written], &room_id, sizeof( room_id ) );
        bytes_written += sizeof( room_id ); 
        memcpy( &buffer[bytes_written], &id, sizeof( id ) );
        bytes_written += sizeof( id );
        float x= pl_positionComp->pos.X;
        memcpy( &buffer[bytes_written], &x, sizeof( x ) );
        bytes_written += sizeof( x );
        float y= pl_positionComp->pos.Z;
        memcpy( &buffer[bytes_written], &y, sizeof( y ) );
        bytes_written += sizeof( y );
        float facing=pl_directionComp->direction;
        memcpy( &buffer[bytes_written], &facing, sizeof( facing ) );
        bytes_written += sizeof( facing );
        float z= pl_positionComp->pos.Y;
        memcpy( &buffer[bytes_written], &z, sizeof( z ) );
        bytes_written += sizeof( z );
        //Punch events
        float right=3;
        float left=3;
        if (receiver.IsMouseKeyPressed(MouseKey::RIGHT)) {
            right=1;
        } 
        else if (receiver.IsMouseKeyPressed(MouseKey::LEFT)) {
            left=1;
        }
        memcpy( &buffer[bytes_written], &right, sizeof( right ) );
        bytes_written += sizeof( right );
        memcpy( &buffer[bytes_written], &left, sizeof( left ) );
        bytes_written += sizeof( left );
        //Player variables
        bool jump=pl_velocityComp->jumping;
        bool block=pl_velocityComp->blocking;
        memcpy( &buffer[bytes_written], &jump, sizeof( jump ) );
        bytes_written += sizeof( jump );
        memcpy( &buffer[bytes_written], &block, sizeof( block ) );
        bytes_written += sizeof( block );
        //Punch change
        int punchid=0;
        if(pl_fistComp->currentFist==FistEnum::DIRECT){
            punchid=1;
        }
        else if(pl_fistComp->currentFist==FistEnum::CROCHET){
            punchid=2;
        }
        else if(pl_fistComp->currentFist==FistEnum::UPPERCUT){
            punchid=3;
        }
        memcpy( &buffer[bytes_written], &punchid, sizeof( punchid ) );
        bytes_written += sizeof( punchid );

        //Power up setting up
        if(id==0 && connectedplayer==true){
        for(auto& spawnPointComp : gameStorage.getComponentsOfType<SpawnPointsComponent>()){
        int index=spawnPointComp.type.size();
        memcpy( &buffer[bytes_written], &index, sizeof( index ) );
        bytes_written += sizeof( index );
        
            while(!spawnPointComp.type.empty()){
            memcpy( &buffer[bytes_written], &spawnPointComp.type[spawnPointComp.type.size()-1], sizeof( spawnPointComp.type[spawnPointComp.type.size()-1] ) );
            bytes_written += sizeof( spawnPointComp.type[spawnPointComp.type.size()-1] );
            memcpy( &buffer[bytes_written], &spawnPointComp.pos[spawnPointComp.type.size()-1], sizeof( spawnPointComp.pos[spawnPointComp.type.size()-1] ) );
            bytes_written += sizeof( spawnPointComp.pos[spawnPointComp.type.size()-1] );
            spawnPointComp.type.pop_back(); //Una especie de pila
            spawnPointComp.pos.pop_back(); 
            }
            } 
        }
        
        int sendOk= sendto(out, buffer, sizeof(buffer), 0, (sockaddr*)&server, sizeof(server)); //For TCP send() is used

        
    }
    void NetSystem::Close(){
        close(out);
    }
}
