#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>
#include <GameEnums.h>
#include <string>
/**
 * Power up component
 */
struct PowerUpComponent : public IComponent
{
    explicit PowerUpComponent(std::size_t eID) : IComponent{COMPONENT_POWERUP, eID} {};

    PowerUpEnum pwup{PowerUpEnum::NO_P};
    float pwupTime {0.0};

    float pwupCooldown {0.0};
    float stunnedCooldown {0.0};

    float ExtraVel {0.0};
    float ExtraDamage {0.0};
    float ExtraDef {0.0};

    bool stunned {false};

    int  generatedPos{0};
    std::string icon_path;
};