#pragma once
#include <GameStorage.h>
#include <EventManager.h>
#include <EntityManager.h>
#include <stack>
#include <SUMIEngine.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <string>

namespace TAKO
{
struct NetSystem {
    public:
    void Update(SUMI::SUMIEngine& receiver, EventManager& eventManager, GameStorage& gameStorage, int enemyID, int playerID, EntityManager& entManager, bool& changeState, StateEnum& nextState);
    void Init(GameStorage& gameStorage, int enemyID, int playerID);
    void InitMulti();
    void InitCreateRoom();
    void InitWaitScreen();
    void SelectCharUpdate(Characters& currentcharacter, Characters& currentenemy, GameStorage& gameStorage, SUMIEngine& engine, bool& changeState, StateEnum& nextState);
    void SelectStageUpdate(int mode, bool& changeState, StateEnum& nextState, Levels& level);
    void SetRoomUpdate(int mode, std::size_t confirmbutton_ID, GameStorage& gameStorage, SUMIEngine& engine, float& frameDeltaTime, bool& changeState, StateEnum& nextState);
    void Close();
    private:
    //Create a hint struct for the socket
    sockaddr_in server;
    //Socket creation
    int out;
    //ID inside the server
    int id;
    //ID of current room
    int room_id;
    //Input of room searched
    std::string keyInput="";
    float keyTime {0.0f};
    //Confirm button aux
    bool activated=false;
    //Punch
    FistAction lastFist{FistAction::resetTimer};

};
} // namespace TAKO