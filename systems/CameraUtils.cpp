#include <CameraUtils.h>

void CameraUtils::setCameraVel(GameStorage& gameStorage, Vector3f velocity){
    for(auto& camComp : gameStorage.getComponentsOfType<IrrcameranodeComponent>()){  
        auto& camera_ent = gameStorage.getEntity(camComp.entityID);  
        VelocityComponent* cam_velComp = static_cast<VelocityComponent*>(camera_ent.require(COMPONENT_VELOCITY));  
        
        if (cam_velComp){  
            cam_velComp->vel = velocity;  
        }  
    } 
}