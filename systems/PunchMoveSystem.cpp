#include <PunchMoveSystem.h>
#include <Vector3f.h>

void PunchMoveSystem::Update(GameStorage& gameStorage){
    for(auto& bboxComp : gameStorage.getComponentsOfType<BBoxComponent>()) { 
        /////////// Guards ////////////
        auto& entity = gameStorage.getEntity(bboxComp.entityID);
        IrranimatednodeComponent* nodeComp = static_cast<IrranimatednodeComponent*>(entity.require(COMPONENT_IRRANIMATEDNODE));
        if (!nodeComp) continue;
        PositionComponent* posComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!posComp) continue;
        ///////////////////////////////
        
        Vector3f* posChar = &posComp->pos;
        Vector3f* posLf   = &bboxComp.lf.pos;
        Vector3f* posRf   = &bboxComp.rf.pos;
        Vector3f* rotLf   = &bboxComp.lf.rot;
        Vector3f* rotRf   = &bboxComp.rf.rot;
        
        if(bboxComp.hlf) {
            *posLf = nodeComp->node.getCurrentBboxPosition();
            *posLf += *posChar;
        } else {
            bboxComp.hlfa = true;
            *posLf = Vector3f(posChar->X + fistLocation, posLf->Y, posChar->Z + fistLocation);
        }
        if(bboxComp.hrf) {
            *posRf = nodeComp->node.getCurrentBboxPosition();
            *posRf += *posChar;
        } else {
            bboxComp.hrfa = true;
            *posRf = Vector3f(posChar->X + fistLocation, posRf->Y, posChar->Z - fistLocation);
        }
        bboxComp.block.pos = Vector3f(posChar->X, bboxComp.block.pos.Y, posChar->Z);
        bboxComp.block.rot.Y = 0.f;
        rotLf->Y = 0.f;
        rotRf->Y = 0.f;
    }
}