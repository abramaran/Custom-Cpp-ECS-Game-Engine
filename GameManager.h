#pragma once

#include <utility>
#include <stack>       
// SUMIEngine
#include <SUMIEngine.h>
#include <BillboardUtils.h>

// ECS
#include <EntityManager.h>
#include <ComponentManager.h>
#include <EventManager.h>
#include <GameStorage.h>

// Systems
#include <InputSystem.h>
#include <PowerUpSystem.h>
#include <CameraRotationSystem.h>
#include <MoveSystem.h>
#include <BBoxSystem.h>
#include <CameraOrbitSystem.h>
#include <CollisionCameraSystem.h>
#include <CollisionPlayableSystem.h>
#include <PunchMoveSystem.h>
#include <PunchCollisionSystem.h>
#include <RespawnSystem.h>
#include <StaminaSystem.h>
#include <DashSystem.h>
#include <PlayableAnimationSystem.h>
#include <BBoxRenderSystem.h>
#include <AISystem.h>
#include <NetSystem.h>
#include <AudioSystem.h>
#include <RespawnBoxSystem.h>
#include <PistonSystem.h>
#include <ResetVelocitySystem.h>
#include <RepositionBarSystem.h>
#include <ButtonSystem.h>
#include <SetPositionSystem.h>
#include <InputMenuSystem.h>
#include <InputClickSystem.h>
#include <DisplayVideoSystem.h>

#include <EventGUIbarsSystem.h>
#include <EventMovementSystem.h>
#include <EventJumpSystem.h>
#include <EventDashSystem.h>
#include <EventChangeFistSystem.h>
#include <EventChangeAnimationSystem.h>
#include <EventPunchSystem.h>
#include <EventTestSystem.h>
#include <EventPowerUpEndSystem.h>
#include <EventPowerUpStartSystem.h>
#include <EventShowHUDSystem.h>
#include <EventStunSystem.h>
#include <EventOptionSelectedSystem.h>
#include <EventDestroyButtonsSystem.h>
#include <EventCreateButtonsSystem.h>
#include <EventEndGameSystem.h>
#include <EventChangeCharacterSystem.h>
#include <EventChangeLevelSystem.h>
#include <EventEndVideo.h>
#include <TrainSystem.h>
#include <SawSystem.h>
#include <ConveyorBeltSystem.h>

#include <glew.h>
#include <glfw3.h>

// SUMIEngine
#include <SUMIEngine.h>


#include <EventSetPauseSystem.h>
#include <EventEndGameSystem.h>
#include <BillboardUtils.h>

struct TkeyStruct;
using namespace TAKO;

struct GameManager
{
    explicit GameManager();

    bool isWindowOpen();
    void Init(bool isonline);
    void ResetLevel(bool isonline);
    void Update();
    void UpdateInGame();
    void UpdateInMultiplayer();
    void UpdateMenu();
    void UpdateMenuRoomChar();
    void UpdateMenuRoomStage();
    void UpdateMenuRoomWait();
    void UpdateMenuRoomC();
    void UpdateMenuRoomS();
    void UpdateMenuSelection();
    void UpdatePause();
    void UpdateVideo();
    void UpdateLoadScreen();


    void RenderGUI();
    void RenderInGame();
    void RenderMenu();
    void RenderPause();



    void changeCurrentState( );
    void newState(StateEnum newState);
    void previousState( );
    void closeGame();
    void initComic();

    SceneManager& getSceneManager();
    void createLevel1();
    private:
        SUMI::SUMIEngine engine;
        // TODO borrar esto de irrlicht
        SceneManager* scmanager = nullptr;
        //MyEventReceiver receiver;
        // hasta aqui

        GameStorage  gameStorage;
        ComponentManager componentManager;
        EntityManager   entityManager;
        EventManager eventManager;

        TrainSystem trainSystem;
        SawSystem sawSystem;
        PowerUpSystem powerupsystem;
        InputSystem inputSystem;
        CameraRotationSystem cameraRotationSystem;
        MoveSystem moveSystem;
        CameraOrbitSystem   cameraOrbit;
        CollisionCameraSystem collisionCameraSystem;
        CollisionPlayableSystem collisionPlayableSystem;
        BBoxSystem bboxSystem;
        PunchMoveSystem punchMoveSystem;
        PunchCollisionSystem punchCollisionSystem;
        RespawnSystem respawnsystem;
        DashSystem    dashsystem;
        StaminaSystem staminasystem;
        PlayableAnimationSystem playableanimationsystem;
        BBoxRenderSystem bboxrendersystem;
        AISystem aisystem;
        NetSystem netsystem;
        EventGUIbarsSystem eventguibarssystem;
  
        AudioSystem audiosystem;
        RespawnBoxSystem respawnBoxSystem;
        PistonSystem pistonSystem;
        ConveyorBeltSystem conveyorSystem;

        ResetVelocitySystem resetVelocitySystem;
        RepositionBarSystem repositionBarSystem;
        ButtonSystem buttonSystem;
        SetPositionSystem setPositionSystem;
        InputMenuSystem inputmenuSystem;
        InputClickSystem inputclickSystem;
        DisplayVideoSystem displayvideoSystem;

        EventTestSystem eventTestSystem;
        EventMovementSystem eventMovementSystem;
        EventJumpSystem eventJumpSystem;
        EventDashSystem eventDashSystem;
        EventChangeFistSystem eventChangeFistSystem; 
        EventChangeAnimationSystem eventChangeAnimationSystem;
        EventPunchSystem eventPunchSystem;


        EventPowerUpEndSystem     eventPowerEnd;
        EventPowerUpStartSystem eventPowerStart;
        EventEndGameSystem   eventendgameSystem;
        EventSetPauseSystem  eventSetPauseSystem;
        EventShowHUDSystem   eventShowHUDSystem;
        EventStunSystem      eventStunSystem;
        EventOptionSelectedSystem  eventOptionSelectedSystem;
        EventDestroyButtonsSystem  eventDestroyButtonsSystem;
        EventCreateButtonsSystem   eventCreateButtonsSystem;
        EventChangeLevelSystem eventchangeLevelSystem;
        EventChangeCharacterSystem eventchangecharacterSystem;
        EventEndVideo eventendvideoSystem;

        float frameDeltaTime;
        const float UPDATE_TICK_TIME = (1.f/60.f);
        bool visibility{false}; 

        std::stack<StateEnum> currentState;
        u_int32_t currentMapping;
        std::size_t screenID;
        bool        eraseScreen{false};
        bool changeState{false};
        StateEnum nextState{StateEnum::LOGO};
        Levels currentLevel{Levels::STATION};
        Characters currentCharacter{Characters::PUNCHIES};
        Characters currentEnemy{Characters::PUNCHIES};

        std::size_t confirmbutton_ID;

        const bool FULLSCREEN {true};
        const bool CAPTURE_CURSOR {true};
        int graphicsMode {2}; // 1 high, 2 low
        //const Vector2f RESOLUTION {1366, 768};      // Ordenadores Irene y Jose
        //const Vector2f RESOLUTION {740, 480};     // 480p
        const Vector2f RESOLUTION {1920, 1080};   // FullHD

        const bool lockCamera {false};
};
