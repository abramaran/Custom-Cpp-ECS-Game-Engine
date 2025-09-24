#pragma once
#include <SoundSystem.h>
#include <GameStorage.h>
#include <ctime>

using namespace TAKO;
struct AudioSystem {
    public:
    void Init();
    void Update(GameStorage& gameStorage, int enemyID, int playerID);
    void PlayEvent(std::string event);
    void StopEvent(std::string event);
    void PlayVideo();
    void SetVideo(int mode);
    void SetVideoTime(int ms);
    int  getVideoTime();
    void StopVideo();
    void SystemUpdate();
    private:
    SoundSystem system;
    int videomode=0; //-1 if none

    bool train;

    //Walking cycle
    time_t walktimer{time(0)};

};
