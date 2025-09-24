#include <DisplayVideoSystem.h>
#include <StateStruct.h>
#include <unistd.h>
//start video event--> preparar las cosas para la carga del video????
//end video event -> change state to ingame?

void DisplayVideoSystem::Init(std::string namefile){
    cap = VideoCapture(namefile);
    cap.set(CV_CAP_PROP_POS_FRAMES,0);
    xFps = cap.get(CV_CAP_PROP_FPS);
    //std::cout << "FPS = " << xFps << "\n";
    xFps = (1.0/xFps);
    timelenght=120;
    framenumber=timelenght*cap.get(CV_CAP_PROP_FPS);
    timecounter=0;
    framenumber=0;
    currentframe=0;
    
}
unsigned char* cvMat2TexInput(Mat& img)
{
    cvtColor(img, img, COLOR_RGB2BGR);
    flip(img, img, 0);
    return img.data;
}

int DisplayVideoSystem::Update(GameStorage& gameStorage, SUMIEngine& engine, EventManager& eventManager, std::vector<TkeyStruct>& keymapping, float& frameDeltaTime, int soundms){

    for(auto& backgroundTag : gameStorage.getComponentsOfType<TagMenuBackground>()){
        auto& entity = gameStorage.getEntity(backgroundTag.entityID);
        IrrbasicnodeComponent* basicnodeComp = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
        if (!basicnodeComp) return 0;
        
        /*if(soundms!=-1){
        //    
        //cap.set(CV_CAP_PROP_POS_MSEC, soundms);
        
        //Frame rate sync
        //currentframe+= floor(timecounter/xFps);
        //timecounter= fmodf(timecounter, xFps);
        //timecounter += frameDeltaTime;
        
        //cap.set(CV_CAP_PROP_POS_FRAMES, currentframe-1);
        }*/
        cap >> frame;
        if (frame.empty()){
            eventManager.postEvent<EndVideoEvent>(keymapping[0].action.state);
            break;
        }
        
        int width = frame.cols;
        int height = frame.rows;
        unsigned char* frameimage = cvMat2TexInput(frame);

        engine.displayVideo(basicnodeComp->node,width,height, frameimage);
        
        waitKey(19);
    }
    return cap.get(CV_CAP_PROP_POS_MSEC);
}