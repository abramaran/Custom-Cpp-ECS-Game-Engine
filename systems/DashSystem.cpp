#include <DashSystem.h>
#include <PlayerConstants.h>
#include <algorithm>
#include <string>

int signD(float val){
    if (val >= 0) 
        return 1;
    else if(val < 0)
        return -1;
    else 
        return 0;
}

void DashSystem::Update(GameStorage& gameStorage, const float frameDeltaTime){
  for (auto& dashComp : gameStorage.getComponentsOfType<DashComponent>()){
    auto& entity = gameStorage.getEntity(dashComp.entityID);
    PositionComponent* positionComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
    if (!positionComp) continue;
    IrranimatednodeComponent* irranimatednodeComp = static_cast<IrranimatednodeComponent*>(entity.require(COMPONENT_IRRANIMATEDNODE));
    if(!irranimatednodeComp) continue;
    VelocityComponent* velocityComp = static_cast<VelocityComponent*>(entity.require(COMPONENT_VELOCITY));

    dashComp.dashCooldown-=frameDeltaTime;
    dashComp.dashCooldown = std::max(0.f,dashComp.dashCooldown);
    
    if(dashComp.dashing && dashComp.previousPos.distance(positionComp->pos) > DASH_DISTANCE){
      Vector3f vectp1p2 = (positionComp->pos - dashComp.previousPos);
      vectp1p2 /= vectp1p2.module();
      vectp1p2 *= DASH_DISTANCE;
      vectp1p2 += dashComp.previousPos;

      positionComp->pos = vectp1p2;
      dashComp.dashing = false;
      velocityComp->vel = Vector3f(abs(dashComp.previousVel.X) * signD(velocityComp->vel.X), dashComp.previousVel.Y, dashComp.previousVel.Z) ;
    }
  }
}