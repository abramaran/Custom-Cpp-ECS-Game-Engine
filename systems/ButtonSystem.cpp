#include <ButtonSystem.h>

void ButtonSystem::Update(GameStorage& gameStorage, SUMIEngine& engine)
{
    Vector2f cursorPos = Vector2f(engine.lastXMouse,engine.lastYMouse);
    Vector2f centreScreen = engine.getWindowSize();
    centreScreen *= 0.5;

    for(auto& mouseOverComp : gameStorage.getComponentsOfType<MouseOverComponent>()){
        auto entity = gameStorage.getEntity(mouseOverComp.entityID);
        ///////////////////////
        PositionComponent* posComp = static_cast<PositionComponent*>(entity.require(COMPONENT_POSITION));
        if (!posComp) continue;
        IrrbasicnodeComponent* basicnodeComp = static_cast<IrrbasicnodeComponent*>(entity.require(COMPONENT_IRRBASICNODE));
        if (!basicnodeComp || !basicnodeComp->node.getVisible()) continue;
        ///////////////////////

        Vector2f size_w = Vector2f(centreScreen.X * basicnodeComp->node.getScale().X, centreScreen.Y * basicnodeComp->node.getScale().Y);
        Vector2f pos_w = Vector2f(centreScreen.X * posComp->pos.X, centreScreen.Y * posComp->pos.Y);
        
        Vector2f centrePos = Vector2f(centreScreen.X + pos_w.X, centreScreen.Y - pos_w.Y );

        float limit_right = centrePos.X + size_w.X;
        float limit_left  = centrePos.X - size_w.X;

        float limit_down = centrePos.Y + size_w.Y;
        float limit_up   = centrePos.Y - size_w.Y;

        if(limit_right > cursorPos.X && limit_left < cursorPos.X && limit_down > cursorPos.Y && limit_up < cursorPos.Y)
        {
            if(!mouseOverComp.isover){
                mouseOverComp.isover = true;
                engine.changeMaterial(basicnodeComp->node, mouseOverComp.SeletctedTexture);
            }
        }
        else{
            
            if(mouseOverComp.isover){
                mouseOverComp.isover = false;
                if(!mouseOverComp.selected){
                    engine.changeMaterial(basicnodeComp->node, mouseOverComp.notSelectedTexture);
                }
            }
        }
        if(mouseOverComp.isover){
            engine.changeMaterial(basicnodeComp->node, mouseOverComp.SeletctedTexture);
        }
        if(!mouseOverComp.isover){
            engine.changeMaterial(basicnodeComp->node, mouseOverComp.notSelectedTexture);
            if(mouseOverComp.selected){
                engine.changeMaterial(basicnodeComp->node, mouseOverComp.SeletctedTexture);
            }
        }
    }
}
