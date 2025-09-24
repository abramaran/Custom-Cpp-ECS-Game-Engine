#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <GameEnums.h>

/**
 * Number of frames and status of the visual feedback for received damage.
 */
struct DamageFeedbackComponent : public IComponent
{
    explicit DamageFeedbackComponent(std::size_t eID) : IComponent{COMPONENT_DAMAGEFEEDBACK, eID} {};
    
    TypeCollisionEnum  typepunch{TypeCollisionEnum::NONE};  //TODO: este componente deberia ser parte del fistcomponent
};