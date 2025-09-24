#include <BBoxRenderSystem.h>

void BBoxRenderSystem::Reset(GameStorage& gameStorage){
    for (auto& gb : gameStorage.getComponentsOfType<BBoxComponent>()) {
        gb.vision.node.setVisible(false); 
        gb.body.node.setVisible(false);
        gb.lf.node.setVisible(false);
        gb.rf.node.setVisible(false);
        gb.block.node.setVisible(false);
        gb.areaHit.setVisible(false);
    }
    for (auto& gb : gameStorage.getComponentsOfType<BBoxPropsComponent>()) { 
        gb.body.node.setVisible(false);
    }

}

void BBoxRenderSystem::Update(GameStorage& gameStorage, const float frameDeltaTime,SUMI::SUMIEngine& receiver, bool& visibility){
    time+= frameDeltaTime;

    if(receiver.IsKeyDown(KEY_Z)){
        if(time >= 0.2){
            time = 0;
            visibility = !visibility;
            for (auto& gb : gameStorage.getComponentsOfType<BBoxComponent>()) {
                gb.vision.node.setVisible(visibility);
                gb.body.node.setVisible(visibility);
                gb.lf.node.setVisible(visibility);
                gb.rf.node.setVisible(visibility);
                gb.block.node.setVisible(visibility);
            }
            for (auto& gb : gameStorage.getComponentsOfType<BBoxPropsComponent>()) { 
                gb.body.node.setVisible(visibility);
            }
            for (auto& gb : gameStorage.getComponentsOfType<SlopeComponent>()) { 
                gb.body.node.setVisible(visibility);
            }
        }
    }
}
