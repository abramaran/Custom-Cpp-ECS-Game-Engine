#include <InputSystem.h>
#include <Enums.h>
#include <GameEnums.h>
#include <PlayerConstants.h>

using namespace TAKO;

void InputSystem::Update(EventManager& eventManager, SUMI::SUMIEngine& receiver, int playerID, bool online){
    // Movement
    if(true){
    if (receiver.IsKeyDown(Key::KEY_A)) {
        eventManager.postEvent<MovementEvent>(playerID, MovementDirection::left);
    }     
    if (receiver.IsKeyDown(Key::KEY_D)) {
        eventManager.postEvent<MovementEvent>(playerID, MovementDirection::right);
    }     
    if (receiver.IsKeyDown(Key::KEY_W)) {
        eventManager.postEvent<MovementEvent>(playerID, MovementDirection::forwards);
    }     
    if (receiver.IsKeyDown(Key::KEY_S)) {
        eventManager.postEvent<MovementEvent>(playerID, MovementDirection::backwards);
    }     
    }
    // Dash
    if (receiver.IsKeyDown(Key::KEY_Q)) {
        eventManager.postEvent<DashEvent>(playerID, DashDirection::left);
    }     
    if (receiver.IsKeyDown(Key::KEY_E)) {
        eventManager.postEvent<DashEvent>(playerID, DashDirection::right);
    }

    // Jump
    if (receiver.IsKeyDown(Key::KEY_SPACE)) {
        eventManager.postEvent<JumpEvent>(playerID);
    }
    
    // Block
    if (receiver.IsKeyDown(Key::KEY_LSHIFT) || receiver.IsKeyDown(Key::KEY_RSHIFT)) {
        eventManager.postEvent<PunchEvent>(playerID, FistAction::block);
    }

    // Change fists
    if (receiver.IsKeyDown(Key::KEY_1)) {
        eventManager.postEvent<ChangeFistEvent>(playerID, FistEnum::DIRECT);
    } else if (receiver.IsKeyDown(Key::KEY_2)) {
        eventManager.postEvent<ChangeFistEvent>(playerID, FistEnum::CROCHET);
    } else if (receiver.IsKeyDown(Key::KEY_3)) {
        eventManager.postEvent<ChangeFistEvent>(playerID, FistEnum::UPPERCUT);
    } else {
        int scrollWheelValue = receiver.WheelMoved();
        if (scrollWheelValue != 0) {
            eventManager.postEvent<ChangeFistEvent>(playerID, scrollWheelValue);
        }
    }
    if (receiver.IsKeyDown(Key::KEY_F)) {
        if (!isFKeyDown) {
            eventManager.postEvent<ChangeFistEvent>(playerID);
            isFKeyDown = true;
        }
    } else {
        isFKeyDown = false;
    }

    // Punch
    if (receiver.IsMouseKeyPressed(MouseKey::RIGHT)) {
        if (lastFist != FistAction::right) {
            eventManager.postEvent<PunchEvent>(playerID, FistAction::resetTimer);
            lastFist = FistAction::right;
        }
        eventManager.postEvent<PunchEvent>(playerID, FistAction::right);
    } else if (receiver.IsMouseKeyPressed(MouseKey::LEFT)) {
        if (lastFist != FistAction::left) {
            eventManager.postEvent<PunchEvent>(playerID, FistAction::resetTimer);
            lastFist = FistAction::left;
        }
        eventManager.postEvent<PunchEvent>(playerID, FistAction::left);
    } else {
        lastFist = FistAction::resetTimer;
    }
}