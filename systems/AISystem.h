#pragma once
#include <GameStorage.h>
#include <EventManager.h>
#include <PlayerConstants.h>
#include <BBoxUtils.h>
#include <CollisionUtils.h>
#include <Sequence.h>
#include <Selector.h>
#include <Isplayerfar.h>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <FuzzySet.h>
#include <SUMIEngine.h>

using namespace TAKO;
struct AISystem {
    public:
    void Update(GameStorage& gameStorage, int enemyID, int playerID, EventManager& eventManager, const float frameDeltaTime);
    void Init(SUMI::SUMIEngine& engine, GameStorage& gameStorage, int enemyID, int playerID);
    private:
    Sequence *root = new Sequence, *sequence1 = new Sequence; 
	Selector* selector1 = new Selector, *selector2 = new Selector; 
	Isplayerfar checkfar;
    //Timers
    time_t reactiontimer;
    time_t reactiontimerpunch;
    time_t footiestimer;
    time_t turningtimer;
    time_t safetytimer;
    int escapecounter;

    //Flags for behaviours
    bool dash=false;
    bool react=true;
    bool facing=false;
    bool follow=false;
    bool jump=false;
    bool unlock=true;
    bool escape=true;
    bool footies=true;
    bool punch=true;

    //Escape variables
    bool escapesearch=true;
    float xxescape;
    float zzescape;

    //Punch variable
    FistAction lastFist{FistAction::resetTimer};

    float lastposrecordjump;
    int lastposrecordlock;
    int unlocktry=0;
    float angleinc;
    double duration;
    int attackphase=0;
    float x=0;
    float z=0;
    //Fuzzylogic initialization
    FuzzySet set;
};