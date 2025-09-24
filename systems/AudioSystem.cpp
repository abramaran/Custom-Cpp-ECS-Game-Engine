#include <AudioSystem.h>
#include <optional>

void AudioSystem::Init(){
    system=SoundSystem("media/Banks/",0);
}
void AudioSystem::Update(GameStorage& gameStorage, int enemyID, int playerID){
	/////////// Guards ////////////
    auto& playerEntity = gameStorage.getEntity(playerID);
    PositionComponent* pl_positionComp = static_cast<PositionComponent*>(playerEntity.require(COMPONENT_POSITION));
    if (!pl_positionComp) return;

	VelocityComponent* pl_velocityComp = static_cast<VelocityComponent*>(playerEntity.require(COMPONENT_VELOCITY));
    if (!pl_velocityComp) return;

    auto& enemyEntity = gameStorage.getEntity(enemyID);
    PositionComponent* en_positionComp = static_cast<PositionComponent*>(enemyEntity.require(COMPONENT_POSITION));
    if (!en_positionComp) return;

	VelocityComponent* en_velocityComp = static_cast<VelocityComponent*>(enemyEntity.require(COMPONENT_VELOCITY));
    if (!en_velocityComp) return;
    ///////////////////////////////

    //Update listener(player) position
    system.setListernerPosition(pl_positionComp->pos.X, pl_positionComp->pos.Y, pl_positionComp->pos.Z);

    for(auto& soundComp : gameStorage.getComponentsOfType<SoundComponent>()){
        ////////////////////////////////////////////
		auto& entity = gameStorage.getEntity(soundComp.entityID);
        SoundComponent* entity_soundComp = static_cast<SoundComponent*>(entity.require(COMPONENT_SOUND));
        if (!entity_soundComp) return;
        PositionComponent* entity_posComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!entity_posComp) return;
        ///////////////////////////////////////////
		if(entity_soundComp->play){
            SoundEvent event=system.getEvent(entity_soundComp->event);
            event.start();
        }
        entity_soundComp->play=false;  
	}

    //Walking cycle 3D
    if(pl_velocityComp->vel.X!=0 || pl_velocityComp->vel.Y!=0){
        if(!pl_velocityComp->jumping){
            if((time(0)-walktimer)>1){
                SoundEvent event=system.getEvent("event:/Character/Footsteps1");
                event.setPosition(pl_positionComp->pos.X,pl_positionComp->pos.Y,pl_positionComp->pos.Z);
                event.start();
                walktimer=time(0);
            }
        }
    }

    for (auto& trainComp : gameStorage.getComponentsOfType<TrainComponent>()) {
		auto& trains = gameStorage.getEntity(trainComp.entityID); 
        if(trainComp.timer==0 && train==false){
            train=true;
            SoundEvent event=system.getEvent("event:/SFX/Crossing");
            event.start();
            SoundEvent event1=system.getEvent("event:/SFX/Train");
            event1.start();
            system.update();
        }
        if(trainComp.timer!=0){
            train=false;
        } 
    }
    //Siempre el final
    system.update();
}

void AudioSystem::PlayEvent(std::string event){
    //std::cout<<"play "+event<<std::endl;
    SoundEvent video=system.getEvent(event);
    video.start();
    system.update();
}

void AudioSystem::StopEvent(std::string event){
    //std::cout<<"stop "+event<<std::endl;
    std::optional<SoundEvent> evento=system.getEventInstance(event);
    if(evento){
        evento->stop();
    }
    system.update();
}

void AudioSystem::PlayVideo(){
    if(videomode==0){
    SoundEvent video=system.getEvent("event:/Videos/Logo");
    video.start();
    }
    if(videomode==1){
    SoundEvent video=system.getEvent("event:/Videos/Comic1");
    video.start();
    }
    if(videomode==2){
    SoundEvent video=system.getEvent("event:/Videos/Comic2");
    video.start();
    }
    system.update();
}
void AudioSystem::SetVideo(int mode){
    //0 ->Logo 1->Primer Comic 2->Segundo Comic
    videomode=mode;
}
void AudioSystem::SetVideoTime(int ms){
    if(videomode==0){
    if(ms%3==0){
    std::optional<SoundEvent> video=system.getEventInstance("event:/Videos/Logo");
    video->setTimelinePosition(ms);}
    }
    if(videomode==1){
    if(ms%3==0){
    std::optional<SoundEvent> video=system.getEventInstance("event:/Videos/Comic1");
    video->setTimelinePosition(ms);}
    }
    if(videomode==2){
    if(ms%3==0){
    std::optional<SoundEvent> video=system.getEventInstance("event:/Videos/Comic2");
    video->setTimelinePosition(ms);}
    }
    if(videomode==3){

    }
    system.update();
}
void AudioSystem::StopVideo(){
    if(videomode==0){
    std::optional<SoundEvent> video=system.getEventInstance("event:/Videos/Logo");
    video->stop();
    videomode=-1;
    }
    if(videomode==1){
    std::optional<SoundEvent> video=system.getEventInstance("event:/Videos/Comic1");
    video->stop();
    videomode=-1;
    }
    if(videomode==2){
    std::optional<SoundEvent> video=system.getEventInstance("event:/Videos/Comic2");
    video->stop();
    videomode=-1;
    }
    if(videomode==3){
        
    }
    system.update();
}

int AudioSystem::getVideoTime(){
    if(videomode==1){
    std::optional<SoundEvent> video=system.getEventInstance("event:/Videos/Comic1");
    int ms=video->getTimelinePosition();
    return ms;
    }
    else{
        return -1;
    }
}

void AudioSystem::SystemUpdate(){
    system.update();
}