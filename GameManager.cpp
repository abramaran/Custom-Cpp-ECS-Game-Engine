#include <GameManager.h>
#include <HideHUDEvent.h>
#include <ShowHUDEvent.h>
#include <StateMapping.h>
#include <tuple>

using namespace TAKO;

GameManager::GameManager() : componentManager(&gameStorage), entityManager(engine, &gameStorage, &componentManager), eventManager(&gameStorage) {
    engine.Init(RESOLUTION.X, RESOLUTION.Y, FULLSCREEN, "Go!Go!! Robot Brawl!");
    currentState.emplace(nextState);
    changeCurrentState();
}

bool GameManager::isWindowOpen() {
    return !engine.windowShouldClose();
}

void GameManager::changeCurrentState(){

    switch (currentState.top())
    {
    case CLOSING:
        currentState.pop();
        closeGame();
        break;
    case OPCIONES:
        eventManager.postEvent<DestroyButtonsEvent>();
        eventManager.postEvent<CreateButtonsEvent>(StateEnum::OPCIONES);
        entityManager.createOptions();
        break;
    case CONTROLESPC:
        eventManager.postEvent<DestroyButtonsEvent>();
        eventManager.postEvent<CreateButtonsEvent>(StateEnum::CONTROLESPC);
        break;
    case CONTROLESMANDO:
        eventManager.postEvent<DestroyButtonsEvent>();
        eventManager.postEvent<CreateButtonsEvent>(StateEnum::CONTROLESMANDO);
        break;
    case MENU:
        currentState = std::stack<StateEnum>();
        currentState.emplace(StateEnum::MENU);
        entityManager.destroyAllEntities();
        entityManager.createMenu();
        audiosystem.StopEvent("event:/Music/MusicLevel1");
        audiosystem.StopEvent("event:/Music/MusicLevel2");
        audiosystem.StopEvent("event:/Ambience/ConveyorBelts");
        engine.setCaptureCursor(false);
        break;
    case CREDITOS:
        entityManager.destroyAllEntities();
        entityManager.createCredits();
        break;
    case STARTMULTI:
        entityManager.destroyAllEntities(); //TODO: esto se quitará una vez puesta la loadscreen en el multi
        ResetLevel(true);
        currentState.pop();
        currentState.emplace(StateEnum::IN_GAMEMULTI);
        nextState = StateEnum::IN_GAMEMULTI;
    case IN_GAMEMULTI:
        if(currentLevel == Levels::STATION){
            audiosystem.StopEvent("event:/Music/MusicLevel1");
            audiosystem.PlayEvent("event:/Music/MusicLevel1");
        }
        if(currentLevel == Levels::FACTORY){
            audiosystem.StopEvent("event:/Music/MusicLevel2");
            audiosystem.StopEvent("event:/Ambience/ConveyorBelts");
            audiosystem.PlayEvent("event:/Music/MusicLevel2");
            audiosystem.PlayEvent("event:/Ambience/ConveyorBelts");
        }
        audiosystem.PlayEvent("event:/SFX/BellFightStart");
        engine.setCaptureCursor(true);
        eventManager.postEvent<ShowHUDEvent>();
        eventManager.postEvent<DestroyButtonsEvent>();
        break;
    case RESTART:
        entityManager.destroyAllEntities();
    case START:
        audiosystem.StopVideo();
        ResetLevel(false);
        currentState.pop();
        currentState.emplace(StateEnum::IN_GAME);
        nextState = StateEnum::IN_GAME;
    case IN_GAME: 
        if(currentLevel == Levels::STATION){
            audiosystem.StopEvent("event:/Music/MusicLevel1");
            audiosystem.PlayEvent("event:/Music/MusicLevel1");
        }
        if(currentLevel == Levels::FACTORY){
            audiosystem.StopEvent("event:/Music/MusicLevel2");
            audiosystem.StopEvent("event:/Ambience/ConveyorBelts");
            audiosystem.PlayEvent("event:/Music/MusicLevel2");
            audiosystem.PlayEvent("event:/Ambience/ConveyorBelts");
        }
        audiosystem.PlayEvent("event:/SFX/BellFightStart");
        engine.setCaptureCursor(CAPTURE_CURSOR);
        cameraRotationSystem.lockCamera = lockCamera;
        eventManager.postEvent<ShowHUDEvent>();
        eventManager.postEvent<DestroyButtonsEvent>();
        break;
    case PAUSA:
        eventManager.postEvent<DestroyButtonsEvent>();
        eventManager.postEvent<CreateButtonsEvent>(StateEnum::PAUSA);
        eventManager.postEvent<HideHUDEvent>();
        engine.setCaptureCursor(false);
        break;
    case MENUINICIAL:
        entityManager.destroyAllEntities();
        entityManager.createInitialMenu();
        break;
    case YOU_WIN_S:
        if(currentLevel == Levels::STATION){
            audiosystem.StopEvent("event:/Music/MusicLevel1");
        }
        if(currentLevel == Levels::FACTORY){
            audiosystem.StopEvent("event:/Music/MusicLevel2");
            audiosystem.StopEvent("event:/Ambience/ConveyorBelts");
        }
        engine.setCaptureCursor(false);
        entityManager.destroyAllEntities();
        eventManager.postEvent<HideHUDEvent>();
        if(currentLevel == Levels::STATION){
            entityManager.createWinSingle();
        }
        else if(currentLevel == Levels::FACTORY){
            entityManager.createWinSingleEnd();
        }
        break;
    case YOU_LOSE_S:
        if(currentLevel == Levels::STATION){
            audiosystem.StopEvent("event:/Music/MusicLevel1");
        }
        if(currentLevel == Levels::FACTORY){
            audiosystem.StopEvent("event:/Music/MusicLevel2");
            audiosystem.StopEvent("event:/Ambience/ConveyorBelts");
        }
        engine.setCaptureCursor(false);
        entityManager.destroyAllEntities();
        eventManager.postEvent<HideHUDEvent>();
        entityManager.createLoseSingle();
        break;
    case YOU_WIN_M:
        if(currentLevel == Levels::STATION){
            audiosystem.StopEvent("event:/Music/MusicLevel1");
        }
        if(currentLevel == Levels::FACTORY){
            audiosystem.StopEvent("event:/Music/MusicLevel2");
            audiosystem.StopEvent("event:/Ambience/ConveyorBelts");
        }
        engine.setCaptureCursor(false);
        entityManager.destroyAllEntities();
        eventManager.postEvent<HideHUDEvent>();
        entityManager.createWinMulti();
        break;
    case YOU_LOSE_M:
        if(currentLevel == Levels::STATION){
            audiosystem.StopEvent("event:/Music/MusicLevel1");
        }
        if(currentLevel == Levels::FACTORY){
            audiosystem.StopEvent("event:/Music/MusicLevel2");
            audiosystem.StopEvent("event:/Ambience/ConveyorBelts");
        }
        engine.setCaptureCursor(false);
        entityManager.destroyAllEntities();
        eventManager.postEvent<HideHUDEvent>();
        entityManager.createLoseMulti();
        break;
    case SELECPERSONAJE:
        currentEnemy = Characters::PUNCHIES;
        currentCharacter = Characters::PUNCHIES;
        entityManager.destroyAllEntities();
        entityManager.createSelectChara();
        break;
    case SELECPERSONAJE_M:
        currentEnemy = Characters::PUNCHIES;
        currentCharacter = Characters::PUNCHIES;
        entityManager.destroyAllEntities();
        entityManager.createSelectChara();
        break;
    case OPCIONESSALA:
        entityManager.destroyAllEntities();
        entityManager.createOpcionesSala();
        break;
    case CREARSALA:
        netsystem.InitMulti();
        netsystem.InitCreateRoom();
        entityManager.destroyAllEntities();
        confirmbutton_ID=entityManager.createCrearSala();
        break;
    case BUSCARSALA:
        netsystem.InitMulti();
        entityManager.destroyAllEntities();
        confirmbutton_ID=entityManager.createBuscarSala();
        break;
    case SELECNIVEL:
        currentLevel = Levels::STATION;
        entityManager.destroyAllEntities();
        entityManager.createSelectNivel();
        break;
    case SELECNIVEL_M:
        currentLevel = Levels::STATION;
        entityManager.destroyAllEntities();
        entityManager.createSelectNivelMulti();
        break;
    case SELECNIVELESPERA:
        netsystem.InitWaitScreen();
        entityManager.destroyAllEntities();
        entityManager.createWaitNivel();
        break;
    case COMIC_GAME:
        entityManager.destroyAllEntities();
        entityManager.createComicGame();
        initComic();
        break;
    case VIDEO_CREDITOS:
        entityManager.destroyAllEntities();
        entityManager.createCreditVideo();
        audiosystem.SetVideo(3);   
        displayvideoSystem.Init("media/Videos/Creditos.mp4");
        break;
    case VIDEO_COMIC:
        entityManager.destroyAllEntities();
        entityManager.createCreditVideo();
        initComic();
        break;
    case COMIC_MENU:
        entityManager.destroyAllEntities();
        entityManager.createComicMenu();
        break;
    case LOGO:
        audiosystem.Init();
        audiosystem.SetVideo(0);       
        entityManager.createLogo();
        displayvideoSystem.Init("media/Videos/Logo.mp4");
        audiosystem.PlayVideo();
        break;
    case SIGUIENTE_NIVEL:
        if(currentLevel == Levels::STATION){
            currentLevel = Levels::FACTORY;
            currentState.emplace(StateEnum::COMIC_GAME);
        }
        else if(currentLevel == Levels::FACTORY){
            currentState.empty();
            currentState.emplace(StateEnum::MENU);
            currentState.emplace(StateEnum::CREDITOS);
            currentState.emplace(StateEnum::VIDEO_CREDITOS);
        }
        changeCurrentState();
        break;
    case VOLVER_SELECT:
        currentState.empty();
        currentState.emplace(StateEnum::MENU);
        currentState.emplace(StateEnum::SELECNIVEL);
        changeCurrentState();
        break;
    case LOAD_SCREEN:
        entityManager.destroyAllEntities();
        eraseScreen = true;
        screenID = entityManager.createLoadScreen();
        break;
    default:
        break;
    }
}
void GameManager::newState(StateEnum newState){
    currentState.push(newState);
    changeCurrentState();
}
void GameManager::previousState(){
    currentState.pop();
    changeCurrentState();
    nextState = currentState.top();
}
void GameManager::closeGame(){
    engine.closeWindow();
}
void GameManager::initComic(){
    std::string videopath = "media/Videos/";
    if(currentLevel == Levels::FACTORY){
        audiosystem.SetVideo(2);
        audiosystem.PlayVideo();
        videopath += "Segundo_Comic.mp4";
    }
    else{
        audiosystem.SetVideo(1);
        audiosystem.PlayVideo();
        videopath += "Primer_Comic.mp4"; //TODO: cambiar el vídeo a uno sin sonido
    }
    displayvideoSystem.Init(videopath);
}
void GameManager::Init(bool isonline) {
    entityManager.createLevel(currentLevel, currentCharacter, isonline, currentEnemy, graphicsMode);
    bboxrendersystem.Reset(gameStorage);
    engine.resetDeltaTime();

    aisystem.Init(engine, gameStorage, entityManager.getEnemyID(), entityManager.getPlayerID());
}

void GameManager::ResetLevel(bool isonline){
    //entityManager.destroyAllEntities();
    Init(isonline);
    if(eraseScreen){  
        eraseScreen = false;
        entityManager.destroyEntity(screenID);
    }

    if(currentLevel == Levels::STATION)    cameraRotationSystem.setValues(-90,-90);
    else  cameraRotationSystem.setValues(180,-30);
}

//MENU UPDATES

void GameManager::UpdateInGame(){
    // TODO: considerar guardar el playerID al principio en vez de tantas llamadas
    
    //inputSystem.Update(eventManager, engine, entityManager.getPlayerID());
    eventDestroyButtonsSystem.Update(gameStorage, entityManager);
    powerupsystem.Update(gameStorage,frameDeltaTime,eventManager,entityManager.getPlayerID());

    resetVelocitySystem.Update(gameStorage);
    
    eventShowHUDSystem.Update(gameStorage);
    aisystem.Update(gameStorage, entityManager.getEnemyID(), entityManager.getPlayerID(), eventManager, frameDeltaTime);
    inputSystem.Update(eventManager, engine, entityManager.getPlayerID(), true);
    inputmenuSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, mapping[currentMapping].mapping, changeState, nextState);
    eventMovementSystem.Update(gameStorage);
    eventDashSystem.Update(gameStorage, eventManager);
    eventJumpSystem.Update(gameStorage, eventManager);
    eventChangeFistSystem.Update(gameStorage, engine);
    eventPunchSystem.Update(gameStorage, entityManager, eventManager, frameDeltaTime);

    trainSystem.Update(gameStorage, frameDeltaTime);
    sawSystem.Update(gameStorage);
    conveyorSystem.Update(gameStorage, frameDeltaTime);
    
    cameraRotationSystem.Update(gameStorage, entityManager.getPlayerID(), entityManager.getEnemyID(), engine.MouseRelativePosition);
    moveSystem.Update(gameStorage, frameDeltaTime);
    dashsystem.Update(gameStorage,frameDeltaTime);

    eventChangeAnimationSystem.Update(gameStorage);
    punchMoveSystem.Update(gameStorage);
    bboxSystem.Update(gameStorage);
    collisionPlayableSystem.Update(gameStorage, frameDeltaTime, eventManager, entityManager);
    pistonSystem.Update(gameStorage, frameDeltaTime);
    punchCollisionSystem.Update(gameStorage, eventManager, visibility);

    cameraOrbit.Update(gameStorage, entityManager.getPlayerID());
    collisionCameraSystem.Update(gameStorage, entityManager.getPlayerID());
    repositionBarSystem.Update(gameStorage,entityManager.getEnemyID());

    playableanimationsystem.Update(gameStorage);
    
    // Activar para poder visualizar bounding boxes
    // bboxrendersystem.Update(gameStorage,frameDeltaTime, engine, visibility);

    staminasystem.Update(gameStorage, eventManager, frameDeltaTime);
    audiosystem.Update(gameStorage, entityManager.getEnemyID(), entityManager.getPlayerID());

    respawnBoxSystem.Update(entityManager.getPlayerID(),gameStorage,frameDeltaTime,entityManager, false);

    respawnsystem.Update(gameStorage, eventManager);
    eventguibarssystem.Update(gameStorage);

    eventendgameSystem.Update(gameStorage, changeState, nextState);
    eventStunSystem.Update(gameStorage,eventManager,entityManager.getPlayerID());
    eventPowerEnd.Update(gameStorage);

    eventPowerStart.Update(entityManager.getPlayerID(), gameStorage, eventManager, entityManager,engine);
    setPositionSystem.Update(gameStorage);
    eventManager.deleteAllEvents();
    engine.MouseRelativePosition.x = engine.MouseRelativePosition.y = 0.5;
}

void GameManager::UpdateInMultiplayer(){
    // TODO: considerar guardar el playerID al principio en vez de tantas llamadas
    //inputSystem.Update(eventManager, engine, entityManager.getPlayerID());
    eventDestroyButtonsSystem.Update(gameStorage, entityManager);
    netsystem.Update(engine, eventManager, gameStorage, entityManager.getEnemyID(), entityManager.getPlayerID(), entityManager, changeState, nextState);
    powerupsystem.Update(gameStorage,frameDeltaTime,eventManager,entityManager.getPlayerID());

    resetVelocitySystem.Update(gameStorage);
    eventShowHUDSystem.Update(gameStorage);
    inputSystem.Update(eventManager, engine, entityManager.getPlayerID(), true);
    eventMovementSystem.Update(gameStorage);
    eventDashSystem.Update(gameStorage, eventManager);
    eventJumpSystem.Update(gameStorage, eventManager);
    eventChangeFistSystem.Update(gameStorage, engine);
    eventPunchSystem.Update(gameStorage, entityManager, eventManager, frameDeltaTime);

    sawSystem.Update(gameStorage);	
	conveyorSystem.Update(gameStorage, frameDeltaTime);
    
    cameraRotationSystem.Update(gameStorage, entityManager.getPlayerID(), entityManager.getEnemyID(), engine.MouseRelativePosition);
    moveSystem.Update(gameStorage, frameDeltaTime);
    dashsystem.Update(gameStorage,frameDeltaTime);

    eventChangeAnimationSystem.Update(gameStorage);
    punchMoveSystem.Update(gameStorage);
    bboxSystem.Update(gameStorage);
    collisionPlayableSystem.Update(gameStorage, frameDeltaTime, eventManager, entityManager);
    pistonSystem.Update(gameStorage, frameDeltaTime);
    punchCollisionSystem.Update(gameStorage, eventManager, visibility);

    cameraOrbit.Update(gameStorage, entityManager.getPlayerID());
    collisionCameraSystem.Update(gameStorage, entityManager.getPlayerID());
    repositionBarSystem.Update(gameStorage,entityManager.getEnemyID());

    playableanimationsystem.Update(gameStorage);
    //bboxrendersystem.Update(gameStorage,frameDeltaTime, engine, visibility);

    staminasystem.Update(gameStorage, eventManager, frameDeltaTime);
    eventguibarssystem.Update(gameStorage);
    audiosystem.Update(gameStorage, entityManager.getEnemyID(), entityManager.getPlayerID());

    respawnBoxSystem.Update(entityManager.getPlayerID(),gameStorage,frameDeltaTime,entityManager, true);

    respawnsystem.Update(gameStorage, eventManager);
    eventendgameSystem.Update(gameStorage, changeState, nextState);
    eventStunSystem.Update(gameStorage,eventManager,entityManager.getPlayerID());
    eventPowerEnd.Update(gameStorage);
    eventPowerStart.Update(entityManager.getPlayerID(), gameStorage, eventManager, entityManager,engine);

    setPositionSystem.Update(gameStorage);
    eventManager.deleteAllEvents();
    engine.MouseRelativePosition.x = engine.MouseRelativePosition.y = 0.5;
}

void GameManager::UpdatePause(){

    eventSetPauseSystem.Update(gameStorage, entityManager);
    eventDestroyButtonsSystem.Update(gameStorage, entityManager);
    eventCreateButtonsSystem.Update(gameStorage, entityManager);

    UpdateMenu(); //they make the same calls
}
void GameManager::UpdateLoadScreen(){
    changeState = true;
    nextState = StateEnum::START;
}

void GameManager::UpdateMenu(){
    inputmenuSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, mapping[currentMapping].mapping, changeState, nextState);
    inputclickSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, changeState, nextState);
    buttonSystem.Update(gameStorage, engine);
    eventOptionSelectedSystem.Update(gameStorage, eventManager);

    eventManager.deleteAllEvents();
}

void GameManager::UpdateMenuRoomChar(){
    inputmenuSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, mapping[currentMapping].mapping, changeState, nextState);
    inputclickSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, changeState, nextState);
    //inputOptionsSystem.Update(gameStorage);
    buttonSystem.Update(gameStorage, engine);
    eventOptionSelectedSystem.Update(gameStorage, eventManager);
    eventchangeLevelSystem.Update(gameStorage,engine,currentLevel);
    eventchangecharacterSystem.Update(gameStorage,engine,currentCharacter);
    netsystem.SelectCharUpdate(currentCharacter, currentEnemy, gameStorage, engine, changeState, nextState);

    eventManager.deleteAllEvents();
}

void GameManager::UpdateMenuRoomStage(){
    inputmenuSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, mapping[currentMapping].mapping, changeState, nextState);
    inputclickSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, changeState, nextState);
    //inputOptionsSystem.Update(gameStorage);
    buttonSystem.Update(gameStorage, engine);
    eventOptionSelectedSystem.Update(gameStorage, eventManager);
    eventchangeLevelSystem.Update(gameStorage,engine,currentLevel);
    eventchangecharacterSystem.Update(gameStorage,engine,currentCharacter);
    netsystem.SelectStageUpdate(0, changeState, nextState, currentLevel);
    
    eventManager.deleteAllEvents();
}

void GameManager::UpdateMenuRoomWait(){
    inputmenuSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, mapping[currentMapping].mapping, changeState, nextState);
    inputclickSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, changeState, nextState);
    buttonSystem.Update(gameStorage, engine);
    eventOptionSelectedSystem.Update(gameStorage, eventManager);
    netsystem.SelectStageUpdate(1, changeState, nextState, currentLevel);

    eventManager.deleteAllEvents();
}

void GameManager::UpdateMenuRoomC(){
    inputmenuSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, mapping[currentMapping].mapping, changeState, nextState);
    inputclickSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, changeState, nextState);
    buttonSystem.Update(gameStorage, engine);
    eventOptionSelectedSystem.Update(gameStorage, eventManager);
    netsystem.SetRoomUpdate(0, confirmbutton_ID, gameStorage,engine, frameDeltaTime, changeState, nextState);

    eventManager.deleteAllEvents();
}

void GameManager::UpdateMenuRoomS(){
    netsystem.SetRoomUpdate(1,confirmbutton_ID, gameStorage,engine, frameDeltaTime, changeState, nextState);
    inputmenuSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, mapping[currentMapping].mapping, changeState, nextState);
    inputclickSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, changeState, nextState);
    buttonSystem.Update(gameStorage, engine);
    eventOptionSelectedSystem.Update(gameStorage, eventManager);
   
    eventManager.deleteAllEvents();
}

void GameManager::UpdateMenuSelection(){
    inputmenuSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, mapping[currentMapping].mapping, changeState, nextState);
    inputclickSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, changeState, nextState);
    //inputOptionsSystem.Update(gameStorage);
    buttonSystem.Update(gameStorage, engine);
    eventOptionSelectedSystem.Update(gameStorage, eventManager);
    eventchangeLevelSystem.Update(gameStorage,engine,currentLevel);
    eventchangecharacterSystem.Update(gameStorage,engine,currentCharacter);
    eventManager.deleteAllEvents();
}

void GameManager::UpdateVideo(){
    //inputmenuSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, mapping[currentMapping].mapping, changeState, nextState);
    inputclickSystem.Update(gameStorage,eventManager,engine,frameDeltaTime, changeState, nextState);
    buttonSystem.Update(gameStorage, engine); //depende de si metemos un botón de skip
    //int soundms=audiosystem.getVideoTime();
    int ms=displayvideoSystem.Update(gameStorage, engine, eventManager,mapping[currentMapping].mapping, frameDeltaTime, 0);
    audiosystem.SetVideoTime(ms);
    eventOptionSelectedSystem.Update(gameStorage, eventManager);
    eventendvideoSystem.Update(gameStorage,changeState,nextState);
    eventManager.deleteAllEvents();
}

//UPDATE GENERAL
void GameManager::Update() {

    TStatestruct *next = mapping;
    void (GameManager::*punc)();


    if(changeState){
        changeState = false;
        if(nextState != 0){ 
            newState(nextState);
            engine.resetDeltaTime();
        }
        else{
            previousState();
        }
    }


    auto i = 0;
    while (next->state)
    { 
        if(currentState.top() == next->state ){
            currentMapping = i;
            frameDeltaTime = engine.getDeltaTime();
            punc = next->pfuncUpdate; //llamar a update especifico, a mapping
            (this->*punc)(); 
            punc = next->pfuncRender; //ahora mismo podría ser solo engine.RenderScene();
            (this->*punc)();
            break;
        }
        ++next;
        ++i;
    }
}

//MENUS RENDERS

void GameManager::RenderInGame(){
    //audiosystem.SystemUpdate();
    engine.RenderScene();
    //RenderGUI();
}

void GameManager::RenderMenu(){
    //audiosystem.SystemUpdate();
    engine.RenderScene();
}

void GameManager::RenderGUI(){
    //TODO borrar este metodo
}
