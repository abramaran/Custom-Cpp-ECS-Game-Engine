#include <EventGUIbarsSystem.h>
#include <PlayerConstants.h>


void EventGUIbarsSystem::Update(GameStorage& gameStorage) {
    for (auto& event : gameStorage.getEventsOfType<RefreshGUIBarsEvent>()){
        /////////// Guards ////////////
        auto& entity = gameStorage.getEntity(event.id);
        HealthComponent* healthComp = static_cast<HealthComponent*>(entity.require(COMPONENT_HEALTH));
        if (!healthComp) continue;
        HUDComponent* hudComp = static_cast<HUDComponent*>(entity.require(COMPONENT_HUD));



        if (hudComp){ //player
            //////////////////////////////
            StaminaComponent* staminaComp = static_cast<StaminaComponent*>(entity.require(COMPONENT_STAMINA));
            if (!staminaComp) continue;
            ///////////////////////////////
            float fractionHealth = healthComp->HP / static_cast<float>(MAX_HP); // FIXME: al bajar de 0 como health es unsigned se vuelve muy grande.
            float fractionStamina = staminaComp->stamina / static_cast<float>(MAX_STAMINA);

            auto& Health_icon = hudComp->Health_icon;
            auto& Stamina_icon = hudComp->Stamina_icon;
            
            Health_icon.setScale(TAKO::Vector3f(hudComp->MAX_WIDTH_HEALTH * fractionHealth, Health_icon.getScale().Y, Health_icon.getScale().Z));
            Stamina_icon.setScale(TAKO::Vector3f(hudComp->MAX_WIDTH_STAMINA * fractionStamina, Stamina_icon.getScale().Y, Stamina_icon.getScale().Z));
        
        }
        else    //enemy
        {   
            ///////////////////////////////
            HealthBarComponent* hpBarComp = static_cast<HealthBarComponent*>(entity.require(COMPONENT_HEALTHBAR));
            if (!hpBarComp) continue;
            ///////////////////////////////
            float fractionHealth = healthComp->HP / static_cast<float>(MAX_HP);

            auto& Health_bar = hpBarComp->Health_bar;
            auto scale =  Health_bar.getScale();
            

            Health_bar.setScale(TAKO::Vector3f(hpBarComp->MAX_WIDTH_HEALTH * fractionHealth, scale.Y, scale.Z));

        }    
    }
}