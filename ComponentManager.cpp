#include <ComponentManager.h>
#include <iostream>

namespace TAKO {
ComponentManager::ComponentManager(GameStorage* gStorage) : gameStorage{gStorage} {

}

void ComponentManager::emptyEntityComponents(Entity& e) {
    auto c = &e.components;    
    for(auto it = c->begin();it <= c->end(); ++it){
        it = c->begin();
        auto a = *it;
        switch (a->componentType) {
            case COMPONENT_POSITION:
                deleteComponent<PositionComponent>(e.id);
                break;
            case COMPONENT_ROTATION:
                deleteComponent<RotationComponent>(e.id);
                break;
            case COMPONENT_VELOCITY:
                deleteComponent<VelocityComponent>(e.id);
                break;
            case COMPONENT_LOOKAT:
                deleteComponent<LookAtComponent>(e.id);
                break;
            case COMPONENT_DIRECTION:
                deleteComponent<DirectionComponent>(e.id);
                break;
            case COMPONENT_DISTANCE:
                deleteComponent<DistanceComponent>(e.id);
                break;
            case COMPONENT_HEALTH:
                deleteComponent<HealthComponent>(e.id);
                break;
            case COMPONENT_STAMINA:
                deleteComponent<StaminaComponent>(e.id);
                break;
            case COMPONENT_POWERUP:
                deleteComponent<PowerUpComponent>(e.id);
                break;
            case COMPONENT_SLOPE:
                {
                    SlopeComponent* slopeComp = static_cast<SlopeComponent*>(e.require(COMPONENT_SLOPE));

                    slopeComp->body.node.remove();

                    deleteComponent<SlopeComponent>(e.id);
                }
                break;
            case COMPONENT_BBOX:
                {
                    BBoxComponent* bboxComp = static_cast<BBoxComponent*>(e.require(COMPONENT_BBOX));
                    bboxComp->body.node.remove();
                    bboxComp->lf.node.remove();
                    bboxComp->rf.node.remove();
                    bboxComp->block.node.remove();
                    deleteComponent<BBoxComponent>(e.id);
                }
                break;
            case COMPONENT_BBOX_PROPS:
                {
                    BBoxPropsComponent* bboxComp = static_cast<BBoxPropsComponent*>(e.require(COMPONENT_BBOX_PROPS));
                    bboxComp->body.node.remove();
                    deleteComponent<BBoxPropsComponent>(e.id);
                }
                break;
            case COMPONENT_BBOX_CAMERA: //TODO Cámara comprobar que borra bien
                {
                    BBoxCameraComponent* bboxComp = static_cast<BBoxCameraComponent*>(e.require(COMPONENT_BBOX_CAMERA));
                    bboxComp->body.node.remove();
                    deleteComponent<BBoxCameraComponent>(e.id);
                }
                break;
            case COMPONENT_DASH:
                deleteComponent<DashComponent>(e.id);
                break;
            case COMPONENT_DAMAGEFEEDBACK:
                deleteComponent<DamageFeedbackComponent>(e.id);
                break;
            case COMPONENT_AI:
                deleteComponent<AIComponent>(e.id);
                break;
            case COMPONENT_IRRANIMATEDNODE:
                {
                    IrranimatednodeComponent* irrnodeComp = static_cast<IrranimatednodeComponent*>(e.require(COMPONENT_IRRANIMATEDNODE));
                    irrnodeComp->node.remove();

                    deleteComponent<IrranimatednodeComponent>(e.id);
                }
                break;
            case COMPONENT_IRRCAMERANODE:
                {
                    IrrcameranodeComponent* irrnodeComp = static_cast<IrrcameranodeComponent*>(e.require(COMPONENT_IRRCAMERANODE));
                    irrnodeComp->node.remove();
                    deleteComponent<IrrcameranodeComponent>(e.id);
                }
                break;
            case COMPONENT_IRRBASICNODE:
                {
                    IrrbasicnodeComponent* irrnodeComp = static_cast<IrrbasicnodeComponent*>(e.require(COMPONENT_IRRBASICNODE));
                    irrnodeComp->node.remove();
                    deleteComponent<IrrbasicnodeComponent>(e.id);
                }
                break;
            case COMPONENT_FIST:
                deleteComponent<FistComponent>(e.id);
                break;
            case COMPONENT_DAMAGE:
                deleteComponent<DamageComponent>(e.id);
                break;
            case COMPONENT_SPAWNPOINT:
                deleteComponent<SpawnPointsComponent>(e.id);
                break;
            case COMPONENT_HUD:
                {
                    HUDComponent*  HUDComp = static_cast<HUDComponent*>(e.require(COMPONENT_HUD));
                    HUDComp->Background_icon.remove();
                    HUDComp->CurrentFist_icon.remove();
                    HUDComp->Health_base_icon.remove();
                    HUDComp->Health_icon.remove();
                    HUDComp->Health_symbol_icon.remove();
                    HUDComp->Power_up_icon.remove();
                    HUDComp->PreviousFist_icon.remove();
                    HUDComp->Stamina_base_icon.remove();
                    HUDComp->Stamina_icon.remove();
                    HUDComp->Stamina_symbol_icon.remove();
                    deleteComponent<HUDComponent>(e.id);    
                }
                break;
            case COMPONENT_PISTON:
                {
                    PistonComponent* pistComp = static_cast<PistonComponent*>(e.require(COMPONENT_PISTON));

                    pistComp->node.remove();

                    deleteComponent<PistonComponent>(e.id);
                }  
                break;
            case COMPONENT_HEALTHBAR:
                {
                    HealthBarComponent*  Health_barComp = static_cast<HealthBarComponent*>(e.require(COMPONENT_HEALTHBAR));
                    Health_barComp->Health_bar.remove();
                    deleteComponent<HealthBarComponent>(e.id);
                }
                break;
            case COMPONENT_NET:
                deleteComponent<NetComponent>(e.id);
                break;
            case COMPONENT_MOUSEOVER:
                deleteComponent<MouseOverComponent>(e.id);
                break;
            case COMPONENT_NEXTSTATE:
                deleteComponent<NextStateComponent>(e.id);
                break;
            case COMPONENT_SELECTEDCHARACTER:
                deleteComponent<SelectCharacterComponent>(e.id);
                break;
            case COMPONENT_SELECTEDLEVEL:
                deleteComponent<SelectLevelComponent>(e.id);
                break;
            case COMPONENT_SHOWNUMBER:
                deleteComponent<ShowNumberComponent>(e.id);
                break;
            case COMPONENT_SOUND:
                deleteComponent<SoundComponent>(e.id);
                break;
            case COMPONENT_CONVEYOR_BELT:
                {
                    ConveyorBeltComponent* convComp = static_cast<ConveyorBeltComponent*>(e.require(COMPONENT_CONVEYOR_BELT));

                    for (size_t i = 0; i < convComp->nodes.size(); i++)
                    {
                        convComp->nodes[i].remove();
                    }

                    convComp->bbox.node.remove();

                    deleteComponent<ConveyorBeltComponent>(e.id);
                }
                break;
            case COMPONENT_SAW:
                {
                    SawComponent* sawComp = static_cast<SawComponent*>(e.require(COMPONENT_SAW));

                    for (size_t i = 0; i < sawComp->nodes.size(); i++)
                    {
                        sawComp->nodes[i].remove();
                    }

                    sawComp->bbox.node.remove();
                    

                    deleteComponent<SawComponent>(e.id);
                }
                break;
            case COMPONENT_TRAIN:
                {
                    TrainComponent* trainComp = static_cast<TrainComponent*>(e.require(COMPONENT_TRAIN));

                    for (size_t i = 0; i < trainComp->nodes.size() || i < trainComp->bboxes.size() ; i++)
                    {
                        trainComp->nodes[i].remove();
                        trainComp->bboxes[i].node.remove();
                    }
                    

                    deleteComponent<TrainComponent>(e.id);
                }
                break;
            case TAG_PLAYER:
                deleteComponent<TagPlayer>(e.id);
                break;
            case TAG_PLAYABLE:
                deleteComponent<TagPlayable>(e.id);
                break;
            case TAG_MENUBACKGROUND:
                deleteComponent<TagMenuBackground>(e.id);
                break;
            default:
                std::cout << "El componentType de este componente no se corresponde con ninguno de ComponentIndexes." << std::endl;
        }
    }
}
}