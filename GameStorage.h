#pragma once

#include <vector>
#include <tuple>

// ECS
#include <Entity.h>

// Components
#include <PositionComponent.h>
#include <RotationComponent.h>
#include <VelocityComponent.h>
#include <SlopeComponent.h>
#include <LookAtComponent.h>
#include <StaminaComponent.h>
#include <DirectionComponent.h>
#include <DistanceComponent.h>
#include <PowerUpComponent.h>
#include <HealthComponent.h>
#include <BBoxComponent.h>
#include <BBoxPropsComponent.h>
#include <BBoxCameraComponent.h>
#include <IrranimatednodeComponent.h>
#include <IrrcameranodeComponent.h>
#include <IrrbasicnodeComponent.h>
#include <DashComponent.h>
#include <FistComponent.h>
#include <DamageFeedbackComponent.h>
#include <AIComponent.h>
#include <PistonComponent.h>
#include <DamageComponent.h>
#include <SpawnPointsComponent.h>
#include <HUDComponent.h>
#include <HealthBarComponent.h>
#include <NetComponent.h>
#include <MouseOverComponent.h>
#include <NextStateComponent.h>
#include <SelectCharacterComponent.h>
#include <ShowNumberComponent.h>
#include <SoundComponent.h>
#include <TrainComponent.h>
#include <ConveyorBeltComponent.h>
#include <SawComponent.h>

#include <TagPlayable.h>
#include <TagPlayer.h>
#include <TagMenuBackground.h>

// Events
#include <TestEvent.h>
#include <PowerUpEndEvent.h>
#include <PowerUpStartEvent.h>
#include <EndGameEvent.h>
#include <HideHUDEvent.h>
#include <ShowHUDEvent.h>
#include <MovementEvent.h>
#include <DashEvent.h>
#include <JumpEvent.h>
#include <ChangeFistEvent.h>
#include <PunchEvent.h>
#include <StunEvent.h>
#include <RefreshGUIBarsEvent.h>
#include <OptionSelectedEvent.h>
#include <DestroyButtonsEvent.h>
#include <CreateButtonsEvent.h>
#include <SelectLevelComponent.h>
#include <HideMenuEvent.h>
#include <ChangeAnimationEvent.h>
#include <ChangeCharacterEvent.h>
#include <ChangeLevelEvent.h>
#include <EndVideoEvent.h>

namespace TAKO {
struct GameStorage {
    explicit GameStorage();
    Entity& getEntity(std::size_t id);

    template <class T>
    std::vector<T>& getComponentsOfType() {
        return std::get<std::vector<T>>(componentVectors);
    }

    template <class T>
    std::vector<T>& getEventsOfType() {
        return std::get<std::vector<T>>(eventVectors);
    }

    std::vector<Entity> entities;
    std::tuple<
        //COMPONENTS
        std::vector<PositionComponent>,
        std::vector<RotationComponent>,
        std::vector<VelocityComponent>,
        std::vector<LookAtComponent>,
        std::vector<DirectionComponent>,
        std::vector<DistanceComponent>,
        std::vector<HealthComponent>,
        std::vector<StaminaComponent>,
        std::vector<PowerUpComponent>,
        std::vector<BBoxComponent>,
        std::vector<BBoxPropsComponent>,
        std::vector<BBoxCameraComponent>,
        std::vector<DashComponent>,
        std::vector<DamageFeedbackComponent>,
        std::vector<AIComponent>,
        std::vector<IrranimatednodeComponent>,
        std::vector<IrrcameranodeComponent>,
        std::vector<IrrbasicnodeComponent>,
        std::vector<FistComponent>,
        std::vector<DamageComponent>,
        std::vector<SpawnPointsComponent>,
        std::vector<SlopeComponent>,
        std::vector<HUDComponent>,
        std::vector<PistonComponent>,
        std::vector<HealthBarComponent>,
        std::vector<NetComponent>,
        std::vector<MouseOverComponent>,
        std::vector<NextStateComponent>,
        std::vector<SelectCharacterComponent>,
        std::vector<SelectLevelComponent>,
        std::vector<ShowNumberComponent>,
        std::vector<SoundComponent>,
        std::vector<TrainComponent>,
        std::vector<ConveyorBeltComponent>,
        std::vector<SawComponent>,
        //TAGS
        std::vector<TagPlayable>,
        std::vector<TagPlayer>,
        std::vector<TagMenuBackground>
    > componentVectors;

    std::tuple<
        std::vector<TestEvent>,
        std::vector<EndGameEvent>,
        std::vector<PowerUpEndEvent>,
        std::vector<PowerUpStartEvent>,
        std::vector<HideHUDEvent>,
        std::vector<ShowHUDEvent>,
        std::vector<MovementEvent>,
        std::vector<DashEvent>,
        std::vector<JumpEvent>,
        std::vector<ChangeFistEvent>,
        std::vector<PunchEvent>,
        std::vector<ChangeAnimationEvent>,
        std::vector<StunEvent>,
        std::vector<RefreshGUIBarsEvent>,
        std::vector<OptionSelectedEvent>,
        std::vector<DestroyButtonsEvent>,
        std::vector<CreateButtonsEvent>,
        std::vector<HideMenuEvent>,
        std::vector<ChangeLevelEvent>,
        std::vector<ChangeCharacterEvent>,
        std::vector<EndVideoEvent>
    > eventVectors;


    private:
        const std::size_t MAX_COMPONENTS{200};        
        const std::size_t MAX_EVENTS{50};        
        const std::size_t MAX_ENTITIES{200};
};

}