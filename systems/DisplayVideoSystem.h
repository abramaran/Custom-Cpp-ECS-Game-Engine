#pragma once
#include <GameStorage.h>
#include <SUMIEngine.h>
#include <EventManager.h>
#include <opencv.hpp>
#include <time.h>
using namespace TAKO;
using namespace cv;
using namespace SUMI;

struct TkeyStruct;

struct DisplayVideoSystem
{
    int Update(GameStorage& gameStorage, SUMIEngine& engine,EventManager& eventManager, std::vector<TkeyStruct>& keymapping, float& frameDeltaTime, int soundms); 
    void Init(std::string namefile);
    private:
    VideoCapture cap;
    float xFps;
    TickMeter t;
    Mat frame;
    float resta;
    float timelenght;
    int framenumber;
    float timecounter;
    int currentframe;

};
