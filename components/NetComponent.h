#pragma once
#include <IComponent.h>
#include <ComponentIndexes.h>

/**
 * Store entity values when online
 */
struct NetComponent : public IComponent
{
    explicit NetComponent(std::size_t eID) : IComponent{COMPONENT_NET, eID} {};

    int OnlineID{0};
    std::size_t confirmbutton_ID;
    bool codeReady=true;
    bool statelessbutton=false;
    bool statelessclick=false;
    
};