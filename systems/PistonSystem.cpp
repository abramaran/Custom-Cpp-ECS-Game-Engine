#include <PistonSystem.h>

void PistonSystem::Update(GameStorage& gameStorage, const float frameDeltaTime){

    for (auto& pistonComp : gameStorage.getComponentsOfType<PistonComponent>()){

        auto& entity = gameStorage.getEntity(pistonComp.entityID);

        IrrbasicnodeComponent* node2 = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
        if (!node2) continue;

        BBoxPropsComponent* bbox = static_cast<BBoxPropsComponent*>(entity.require(COMPONENT_BBOX_PROPS));
        if (!bbox) continue;

        if((pistonComp.activated1 || pistonComp.activated2) && node2->node.getScale().Y > defaulScale){

            pistonComp.down    = true;
            pistonComp.activated1 = true;
            pistonComp.activated2 = true;
            Vector3f scale              = node2->node.getScale();

            node2->node.setScale(TAKO::Vector3f(scale.X,  scale.Y - (pistonSpeed * frameDeltaTime), scale.Z));
            bbox->body.node.setScale(TAKO::Vector3f(scale.X,  scale.Y - (pistonSpeed * frameDeltaTime), scale.Z));

        }
        else if(pistonComp.down && (pistonComp.activated1 || pistonComp.activated2) && node2->node.getScale().Y <= defaulScale){

            pistonComp.down    = false;
            pistonComp.activated1 = false;
            pistonComp.activated2 = false;

        }
        else if(!pistonComp.down && (pistonComp.activated1 || pistonComp.activated2) && node2->node.getScale().Y <= defaulScale){

            node2->node.setScale(TAKO::Vector3f(node2->node.getScale().X, maxScale, node2->node.getScale().Z));
            bbox->body.node.setScale(TAKO::Vector3f(node2->node.getScale().X,  maxScale-3 , node2->node.getScale().Z));
        }
        TAKO::Vector3f pos = pistonComp.node.getPosition();
        pistonComp.node.setPosition(TAKO::Vector3f(pos.X, CollisionUtils::getYComponentsBBox(bbox->body).Y , pos.Z));
    }   
}