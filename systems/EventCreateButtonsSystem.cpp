#include <EventCreateButtonsSystem.h>
#include <GameEnums.h>
#include <CreateButtonsEvent.h>

void EventCreateButtonsSystem::Update(GameStorage& gameStorage, EntityManager& entManager){
    for (auto& event : gameStorage.getEventsOfType<CreateButtonsEvent>()) {
         switch (event.state)
         {
         case PAUSA:
            entManager.createPause();
            break;
        case OPCIONES:
            entManager.createOptions();
            break;
        case CONTROLESMANDO:
            entManager.createControls("media/Menu/Controles Mando.jpg");
            break;
        case CONTROLESPC:
            entManager.createControls("media/Menu/Controles Keyboard.jpg");
            break;
        default:
            std::cout<<"El estado no corresponde con ninguna de las opciones"<<std::endl;
            break;
        }
    }
}