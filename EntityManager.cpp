#include <EntityManager.h>
#include <iostream>
#include <vector>
#include <TAnimatedMesh.h>
#include <PlayerConstants.h>
#include <CameraConstants.h>
#include <PositionComponent.h>
#include <LookAtComponent.h>
#include <IrrcameranodeComponent.h>
#include <DirectionComponent.h>
#include <DistanceComponent.h>
#include <SUMIDrawableNode.h>
#include <chrono>
#include <malloc.h>

const Vector3f scaleNOTSelected{Vector3f(0.45,0.5,0)}; 

namespace TAKO
{

EntityManager::EntityManager(SUMI::SUMIEngine& en, GameStorage* gs, ComponentManager* cm) : engine{en}, gameStorage{gs}, componentManager{cm} {

}

Entity& EntityManager::createEntityBase() {
    gameStorage->entities.emplace_back();    
    return gameStorage->entities.back();
}

std::size_t EntityManager::createEntity() {
    return createEntityBase().id;
}

void EntityManager::destroyEntity(std::size_t entityID) {
    std::vector<Entity>::iterator iterator = std::find_if(gameStorage->entities.begin(), gameStorage->entities.end(), [&](const Entity & val){ 
        if (val.id == entityID) {
            return true;
        } else {
            return false;
        }
    });
    std::iter_swap(iterator, gameStorage->entities.end() - 1);

    componentManager->emptyEntityComponents(gameStorage->entities.back());
    gameStorage->entities.pop_back();
}

void EntityManager::destroyAllEntities() {
    for (auto& e : gameStorage->entities) {
        componentManager->emptyEntityComponents(e);
    }
    gameStorage->entities.clear();
}
void EntityManager::createInitialMenu(){
    createStateButton(Vector3f(0), Vector3f(1), "media/Menu/Numbers/none.png" , StateEnum::MENU);
    createStateButton(Vector3f(0,-0.71,-1), Vector3f(1,0.13,1), "media/Menu/Buttons/InitialButton.png" , StateEnum::MENU);
    createBackGround("media/Menu/Menu Inicio.jpg");
}
std::size_t EntityManager::createCharacterPortrait(Vector3f position, Vector3f scale, std::string texturePath, bool isplayer){
    auto& entity = createEntityBase();
    if(isplayer){
        auto& playerComp = componentManager->addComponent<TagPlayer>(entity.id);
    }
    else{
        auto& playableComp = componentManager->addComponent<TagPlayable>(entity.id);
    }
    auto& basicnodeComp = componentManager->addComponent<IrrbasicnodeComponent>(entity.id);

    basicnodeComp.node = engine.createHUD("media/Menu/Buttons/Buttons.obj",position);
    basicnodeComp.node.setScale(scale);
    engine.changeMaterial(basicnodeComp.node, texturePath);

    return entity.id;
}

void EntityManager::createSelectChara(){    
    createCharacterPortrait(Vector3f(-0.5,-0.1,0),Vector3f(0.5,0.9,0.5),"media/Menu/Portraits/Punchies.png", true);
    createCharacterPortrait(Vector3f( 0.5,-0.1,0),Vector3f(0.5,0.9,0.5),"media/Menu/Portraits/Punchies.png", false);

    createCharacterButton(Vector3f(-0.4,-0.461,-1),Vector3f(0.19,0.21,0.19),"media/Menu/Buttons/Punchies.png",Characters::PUNCHIES, "media/Menu/Portraits/Punchies.png", true);
    createCharacterButton(Vector3f(   0,-0.461,-1),Vector3f(0.19,0.21,0.19),"media/Menu/Buttons/Boss1.png",Characters::BOSS1, "media/Menu/Portraits/Dva.png", false);
    createCharacterButton(Vector3f( 0.4,-0.461,-1),Vector3f(0.19,0.21,0.19),"media/Menu/Buttons/Boss2.png",Characters::BOSS2, "media/Menu/Portraits/IA.png", false);

    createStatelessButton(Vector3f(0.85,-0.77,-1), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Fijar.png");
    createBackGround("media/Menu/Multijugador Seleccionar personaje.jpg");
}
std::size_t EntityManager::createBuscarSala(){
    std::size_t id=createStateButton(Vector3f(0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Entrar.png" , StateEnum::SELECNIVELESPERA);
    createStateButton(Vector3f(-0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Volver.png" , StateEnum::NO_STATE);
    createRoomNumber(Vector3f(-0.15,0.08,0), Vector3f(0.03,0.07,0.1),"media/Menu/Numbers/none.png", 0);
    createRoomNumber(Vector3f(-0.05,0.08,0), Vector3f(0.03,0.07,0.1),"media/Menu/Numbers/none.png", 1);
    createRoomNumber(Vector3f(0.05,0.08,0), Vector3f(0.03,0.07,0.1),"media/Menu/Numbers/none.png", 2);
    createRoomNumber(Vector3f(0.15,0.08,0), Vector3f(0.03,0.07,0.1),"media/Menu/Numbers/none.png", 3);
    createBackGround("media/Menu/BuscarSala.jpg");

    return id;
}
std::size_t EntityManager::createCrearSala(){
    std::size_t id=createStateButton(Vector3f(0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Aceptar.png" , StateEnum::SELECNIVEL_M);
    createStateButton(Vector3f(-0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Volver.png" , StateEnum::NO_STATE);
    createRoomNumber(Vector3f(-0.15,0.08,0), Vector3f(0.03,0.07,0.1),"media/Menu/Numbers/none.png", 0);
    createRoomNumber(Vector3f(-0.05,0.08,0), Vector3f(0.03,0.07,0.1),"media/Menu/Numbers/none.png", 1);
    createRoomNumber(Vector3f(0.05,0.08,0), Vector3f(0.03,0.07,0.1),"media/Menu/Numbers/none.png", 2);
    createRoomNumber(Vector3f(0.15,0.08,0), Vector3f(0.03,0.07,0.1),"media/Menu/Numbers/none.png", 3);
    createBackGround("media/Menu/CrearSala.jpg");

    return id;
}
void EntityManager::createSelectNivel(){
    createLevelButton(Vector3f(-0.5,0,0), scaleNOTSelected,"media/Menu/Buttons/Nivel1.png",Levels::STATION, true);
    createLevelButton(Vector3f( 0.5,0,0),  scaleNOTSelected,"media/Menu/Buttons/Nivel2.png",Levels::FACTORY, false);
    createStateButton(Vector3f(-0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Volver.png" , StateEnum::NO_STATE);  
    createStateButton(Vector3f(0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Aceptar.png" , StateEnum::COMIC_GAME);
    createBackGround("media/Menu/SeleccionarNivel.jpg");
}
void EntityManager::createSelectNivelMulti(){
    createLevelButton(Vector3f(-0.5,0,0),scaleNOTSelected,"media/Menu/Buttons/Nivel1.png",Levels::STATION, true);
    createLevelButton(Vector3f( 0.5,0,0),scaleNOTSelected,"media/Menu/Buttons/Nivel2.png",Levels::FACTORY, false);
    createStateButton(Vector3f(0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Aceptar.png" , StateEnum::SELECPERSONAJE_M);
    createBackGround("media/Menu/SeleccionarNivel.jpg");
}
void EntityManager::createWaitNivel(){
    createBackGround("media/Menu/Multijugador Esperando Escenario.jpg");
}

void EntityManager::createOpcionesSala(){
    createStateButton(Vector3f(-0.21, 0.1,0) ,Vector3f(0.9,0.19,0.1),"media/Menu/Buttons/CrearSala.png", StateEnum::CREARSALA);
    createStateButton(Vector3f(0.2,-0.47,0) , Vector3f(0.9,0.19,0.1),"media/Menu/Buttons/BuscarSala.png", StateEnum::BUSCARSALA);
    createStateButton(Vector3f(-0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Volver.png" , StateEnum::NO_STATE);
    createBackGround("media/Menu/Multijugador.jpg");
}

void EntityManager::createMenu(){
    createStateButton(Vector3f(0.44,0.55,-1) ,Vector3f(0.56,0.17,0.1),"media/Menu/Buttons/ModoHistoria.png", StateEnum::SELECNIVEL );
    createStateButton(Vector3f(0.41,0.20,-1) ,Vector3f(0.59,0.17,0.1),"media/Menu/Buttons/Multijugador.png", StateEnum::OPCIONESSALA);
    createStateButton(Vector3f(0.42,-0.11,-1),Vector3f(0.58,0.12,0.1),"media/Menu/Buttons/Opciones.png" , StateEnum::OPCIONES );
    createStateButton(Vector3f(0.42,-0.36,-1),Vector3f(0.58,0.12,0.1),"media/Menu/Buttons/Creditos.png" , StateEnum::CREDITOS );
    createStateButton(Vector3f(0.41,-0.65,-1),Vector3f(0.6,0.10,0.1),"media/Menu/Buttons/Salir.png", StateEnum::CLOSING );
    createBackGround("media/Menu/Menu principal.jpg");
}

void EntityManager::createOptions(){
    createStateButton(Vector3f(0.2,-0.47,0) , Vector3f(0.9,0.19,0.1),"media/Menu/Buttons/ControlesMando.png", StateEnum::CONTROLESMANDO);
    createStateButton(Vector3f(-0.21, 0.1,0) ,Vector3f(0.9,0.19,0.1),"media/Menu/Buttons/ControlesTeclado.png", StateEnum::CONTROLESPC);
    createStateButton(Vector3f(-0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Volver.png" , StateEnum::NO_STATE);
    createBackGround("media/Menu/Opciones.jpg");

}
void EntityManager::createCredits(){
    createStateButton(Vector3f(0.2,-0.47,0) , Vector3f(0.9,0.19,0.1),"media/Menu/Buttons/Creditos_2.png", StateEnum::VIDEO_CREDITOS);
    createStateButton(Vector3f(-0.21, 0.1,0) ,Vector3f(0.9,0.19,0.1),"media/Menu/Buttons/ContenidoExtra.png", StateEnum::COMIC_MENU);
    createStateButton(Vector3f(-0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Volver.png" , StateEnum::MENU);
    createBackGround("media/Menu/Creditos.jpg");
}
void EntityManager::createControls(std::string texturepath){
    createStateButton(Vector3f(-0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Volver.png" , StateEnum::NO_STATE);
    createBackGround(texturepath);
}
void EntityManager::createPause(){
    createStateButton(Vector3f(0, 0.25, 0) , Vector3f(0.4,0.13,0.1),"media/Menu/Buttons/Continuar.png", StateEnum::IN_GAME);
    createStateButton(Vector3f(0, -0.04, 0) , Vector3f(0.45,0.09,0.1),"media/Menu/Buttons/VolveraaEmpezar.png", StateEnum::RESTART);
    createStateButton(Vector3f(0,-0.30 , 0), Vector3f(0.23,0.09,0.1), "media/Menu/Buttons/Opciones_p.png" , StateEnum::OPCIONES);
    createStateButton(Vector3f(0,-0.53 , 0), Vector3f(0.15,0.09,0.1), "media/Menu/Buttons/Salir_p.png" , StateEnum::MENU);
    createBackGround("media/Menu/Pausa.jpg");
}
void EntityManager::createLoseSingle(){
    createStateButton(Vector3f(0, 0.16, 0) , Vector3f(0.3,0.1,0.1),"media/Menu/Buttons/Reintentar.png", StateEnum::START);
    createStateButton(Vector3f(0,-0.10 , 0), Vector3f(0.32,0.07,0.1), "media/Menu/Buttons/SeleccionarNivel.png" , StateEnum::VOLVER_SELECT);
    createStateButton(Vector3f(0,-0.35 , 0), Vector3f(0.1,0.07,0.1), "media/Menu/Buttons/Salir_p.png" , StateEnum::MENU);
    createBackGround("media/Menu/HasPerdido.jpg");
}
void EntityManager::createWinSingle(){
    createStateButton(Vector3f(0, 0.25, 0) , Vector3f(0.4,0.1,0.1),"media/Menu/Buttons/SiguienteNivel.png", StateEnum::SIGUIENTE_NIVEL);
    createStateButton(Vector3f(0, 0.04, 0) , Vector3f(0.25,0.09,0.1),"media/Menu/Buttons/VolverAJugar.png", StateEnum::RESTART);
    createStateButton(Vector3f(0,-0.20 , 0), Vector3f(0.32,0.08,0.1), "media/Menu/Buttons/SeleccionarNivel.png" , StateEnum::VOLVER_SELECT);
    createStateButton(Vector3f(0,-0.40 , 0), Vector3f(0.1,0.07,0.1), "media/Menu/Buttons/Salir_p.png" , StateEnum::MENU);
    createBackGround("media/Menu/HasGanado.jpg");
}
void EntityManager::createWinSingleEnd(){
    createStateButton(Vector3f(0, 0.25, 0) , Vector3f(0.35,0.1,0.1),"media/Menu/Buttons/IrACreditos.png", StateEnum::SIGUIENTE_NIVEL);
    createStateButton(Vector3f(0, 0.04, 0) , Vector3f(0.25,0.09,0.1),"media/Menu/Buttons/VolverAJugar.png", StateEnum::RESTART);
    createStateButton(Vector3f(0,-0.20 , 0), Vector3f(0.32,0.08,0.1), "media/Menu/Buttons/SeleccionarNivel.png" , StateEnum::VOLVER_SELECT);
    createStateButton(Vector3f(0,-0.40 , 0), Vector3f(0.1,0.07,0.1), "media/Menu/Buttons/Salir_p.png" , StateEnum::MENU);
    createBackGround("media/Menu/HasGanado.jpg");  
}
void EntityManager::createLoseMulti(){
    //createStateButton(Vector3f(0,0.18 , 0), Vector3f(0.4,0.08,0.1), "media/Menu/Buttons/VolverASala.png" , StateEnum::MENU);
    createStateButton(Vector3f(0), Vector3f(0.1,0.07,0.1), "media/Menu/Buttons/Salir_p.png" , StateEnum::MENU);
    createBackGround("media/Menu/HasPerdido.jpg");
}
void EntityManager::createWinMulti(){
    //createStateButton(Vector3f(0,0.18 , 0), Vector3f(0.4,0.08,0.1), "media/Menu/Buttons/VolverASala.png" , StateEnum::MENU);
    createStateButton(Vector3f(0), Vector3f(0.1,0.07,0.1), "media/Menu/Buttons/Salir_p.png" , StateEnum::MENU);
    createBackGround("media/Menu/HasGanado.jpg");
}
void EntityManager::createComicGame(){
    createStateButton(Vector3f(0.9,-0.9,-1), Vector3f(0.11,0.067,0.1), "media/Menu/Buttons/Saltar.png" , StateEnum::LOAD_SCREEN);
    createBackGround("media/Menu/Video_Base.jpg");
}
void EntityManager::createCreditVideo(){
    createStateButton(Vector3f(0.9,-0.9,-1), Vector3f(0.11,0.067,0.1), "media/Menu/Buttons/Saltar.png" , StateEnum::NO_STATE);
    createBackGround("media/Menu/Video_Base.jpg");
}
void EntityManager::createComicMenu(){
    createLevelButton(Vector3f(-0.5,0,0), scaleNOTSelected ,"media/Menu/Buttons/Comic1.png",Levels::STATION, true);
    createLevelButton(Vector3f( 0.5,0,0), scaleNOTSelected ,"media/Menu/Buttons/Comic2.png",Levels::FACTORY, false);
    createStateButton(Vector3f(-0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Volver.png" , StateEnum::NO_STATE);  
    createStateButton(Vector3f(0.85,-0.77,0), Vector3f(0.15,0.085,0.1), "media/Menu/Buttons/Aceptar.png" , StateEnum::VIDEO_COMIC);
    createBackGround("media/Menu/ContenidoExtra.jpg");
}
void EntityManager::createLogo(){
    createBackGround("media/Menu/Video_Base.jpg");
}
std::size_t EntityManager::createLoadScreen(){
    return createBackGround("media/Menu/Pantalla de Carga.jpg");
}
std::size_t EntityManager::createBackGround(std::string texturePath){
    auto& entity = createEntityBase();
    auto& backgroundTagComp = componentManager->addComponent<TagMenuBackground>(entity.id);  
    auto& basicNodeComp = componentManager->addComponent<IrrbasicnodeComponent>(entity.id);  

    basicNodeComp.node = engine.createHUD("media/Menu/Buttons/Buttons.obj", Vector3f(0,0,0));
    engine.changeMaterial(basicNodeComp.node, texturePath);

    return entity.id;
}
std::size_t EntityManager::createRoomNumber(Vector3f position, Vector3f scale, std::string texturePath, int index){
    auto& entity = createEntityBase();
    auto& positionComp = componentManager->addComponent<PositionComponent>(entity.id);  
    auto& basicNodeComp = componentManager->addComponent<IrrbasicnodeComponent>(entity.id);
    auto& showNumberComp = componentManager->addComponent<ShowNumberComponent>(entity.id);    

    positionComp.pos = position;
    basicNodeComp.node = engine.createHUD("media/Menu/titulo.obj",position);
    basicNodeComp.node.setScale(scale);
    basicNodeComp.node.setPosition(position);
    engine.changeMaterial(basicNodeComp.node,texturePath);
    showNumberComp.numberindex=index;   

    return entity.id;
}

std::size_t EntityManager::createStateButton(Vector3f position, Vector3f scale, std::string texturePath, StateEnum state){
    auto& entity = createEntityBase();

    createButton(entity.id, position, scale, texturePath, false);
    
    auto& nextStateComp = componentManager->addComponent<NextStateComponent>(entity.id);  
    nextStateComp.state = state;
    componentManager->addComponent<NetComponent>(entity.id);    

    return entity.id;
}

std::size_t EntityManager::createStatelessButton(Vector3f position, Vector3f scale, std::string texturePath){
    auto& entity = createEntityBase();

    createButton(entity.id, position, scale, texturePath, false);

    auto& netComp = componentManager->addComponent<NetComponent>(entity.id);
    netComp.statelessbutton=true;    

    return entity.id;
}

std::size_t EntityManager::createLevelButton(Vector3f position, Vector3f scale, std::string texturePath, Levels level, bool selected){
    auto& entity = createEntityBase();
    createButton(entity.id, position, scale, texturePath, selected);
  
    auto& selectLevel = componentManager->addComponent<SelectLevelComponent>(entity.id);
    selectLevel.selectedLevel = level;
    componentManager->addComponent<NetComponent>(entity.id);    

    return entity.id;
}

std::size_t EntityManager::createCharacterButton(Vector3f position, Vector3f scale, std::string texturePath, Characters character, std::string characterpicture, bool selected){
    auto& entity = createEntityBase();
    createButton(entity.id, position, scale, texturePath, selected);
  
    auto& selectChara = componentManager->addComponent<SelectCharacterComponent>(entity.id);
    selectChara.selectedCharacter = character;
    selectChara.texturepath = characterpicture;
    componentManager->addComponent<NetComponent>(entity.id);    

    return entity.id;
}

void EntityManager::createButton(std::size_t& id, Vector3f& position, Vector3f& scale, std::string& texturePath, bool selected){
    auto& positionComp = componentManager->addComponent<PositionComponent>(id);  
    auto& basicNodeComp = componentManager->addComponent<IrrbasicnodeComponent>(id);  
    auto& mouseOverComp = componentManager->addComponent<MouseOverComponent>(id);

    positionComp.pos = position;
    basicNodeComp.node = engine.createHUD("media/Menu/Buttons/Buttons.obj",position);
    basicNodeComp.node.setScale(scale);
    basicNodeComp.node.setPosition(position);

    mouseOverComp.notSelectedTexture = texturePath;
    mouseOverComp.SeletctedTexture = texturePath.insert(texturePath.length() - 4,"_S");
    mouseOverComp.selected = selected;
    if(selected){
        engine.changeMaterial(basicNodeComp.node, mouseOverComp.SeletctedTexture);   
    }
    else{
        engine.changeMaterial(basicNodeComp.node, mouseOverComp.notSelectedTexture);   
    }

}
void EntityManager::createLevel1(){
    int mult = 3;
    int multEscala = 4;

    // BUILDINGS:
    float multY = mult ;
    float mult2 = mult *30;
    float mult3x = mult *6;
    float mult3y = mult *6;
    float mult3z = mult *6;


    TAKO::Vector3f scale(150, 150,150);

    // Nube1
    createResizableBillboard(TAKO::Vector3f(-mult2 *12.077, mult2 *11.729, -mult2 *-26.330), scale, "media/meshes/Clouds/Nube1.obj");
    // Nube2
    createResizableBillboard(TAKO::Vector3f(-mult2 *-20.566, mult2 *16.839, -mult2 *10.598), scale, "media/meshes/Clouds/Nube2.obj");
    // Nube3
    createResizableBillboard(TAKO::Vector3f(-mult2 *29.623, mult2 *9.451, -mult2 *-5.720), 100, "media/meshes/Clouds/Nube3.obj");
    // Nube2.001
    createResizableBillboard(TAKO::Vector3f(-mult2 *14.225, mult2 *15.401, -mult2 *31.435), scale, "media/meshes/Clouds/Nube2.obj");
    // Nube2.002
    createResizableBillboard(TAKO::Vector3f(-mult2 *27.991, mult2 *13.280, -mult2 *-15.560), scale, "media/meshes/Clouds/Nube2.obj");
    // Nube2.003
    createResizableBillboard(TAKO::Vector3f(-mult2 *-21.137, mult2 *20.722, -mult2 *-16.721), scale, "media/meshes/Clouds/Nube2.obj");
    // Nube1.001
    createResizableBillboard(TAKO::Vector3f(-mult2 *-52.343, mult2 *21.058, -mult2 *8.115), scale, "media/meshes/Clouds/Nube1.obj");
    // Nube1.002
    createResizableBillboard(TAKO::Vector3f(-mult2 *-8.548, mult2 *10.108, -mult2 *-20.252), scale, "media/meshes/Clouds/Nube1.obj");
    // Nube1.003
    createResizableBillboard(TAKO::Vector3f(-mult2 *-9.539, mult2 *13.274, -mult2 *28.745), scale, "media/meshes/Clouds/Nube1.obj");

    int mult3 = 18; 


    // Train tracks
    createStaticCustomMesh("media/Level1/Assets/empty.obj",   TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30),  TAKO::Vector3f( 9.10483f * mult3, 0.080058f*mult3, 0.999365 * mult3), TAKO::Vector3f(-mult2 * 6.7414f, mult2 *0.079086 , -mult2 * 1.58393f), TAKO::Vector3f(0, 0, 0), true);

    // Ground
    createStaticCustomMesh("media/Level1/Assets/empty.obj",   TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30),  TAKO::Vector3f( 3.14518f * mult3, 0.26623f*mult3, 9.88865f * mult3), TAKO::Vector3f(-mult2 * 7.44366f, mult2 *0 , -mult2 * -2.54224f), TAKO::Vector3f(0, 90, 0), true);
    createStaticCustomMesh("media/Level1/Assets/empty.obj",   TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30),  TAKO::Vector3f( 1.35296f * mult3, 2*mult3, 0.318794 * mult3), TAKO::Vector3f(-mult2 * 14.2529f, mult2 * 2.01514f, -mult2 * -0.728568f), TAKO::Vector3f(0, 90, 0), true);
    createStaticCustomMesh("media/Level1/Assets/empty.obj",   TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30),  TAKO::Vector3f( 7.6942f * mult3, 0.26623f*mult3, 5.66077 * mult3), TAKO::Vector3f(-mult2 * 6.05664f, mult2 * 0, -mult2 * 8.25211f), TAKO::Vector3f(0, 0, 0), true);

    // EdificioEsquina2.005
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.238, mult3 *3.090, mult3 *0.904), TAKO::Vector3f(-mult2 *4.953, mult2 *3.321, -mult2 *-3.481), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // EdificioEsquina3
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.851, mult3 *3.090, mult3 *0.904), TAKO::Vector3f(-mult2 *2.891, mult2 *3.321, -mult2 *-3.560), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // EdificioEsquina3_Barrier_Left.008
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.054, mult3 *0.464, mult3 *1.430), TAKO::Vector3f(-mult2 *1.987, mult2 *0.567, -mult2 *-3.066), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // EdificioEsquina3_Barrier_Right
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.231, mult3 *0.464, mult3 *1.430), TAKO::Vector3f(-mult2 *3.959, mult2 *0.567, -mult2 *-3.057), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // EdificioEsquina3_Platform.002    
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.984, mult3 *0.226, mult3 *1.430), TAKO::Vector3f(-mult2 *2.892, mult2 *0.281, -mult2 *-3.057), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    
    createSlope("media/Level1/Assets/empty.obj",  TAKO::Vector3f(-mult2 *2.892, mult2 *0.383, -mult2 *-1.391), TAKO::Vector3f(0, 0, 0), TAKO::Vector3f(mult3 *0.984, mult3 *0.126, mult3 *0.236),false,true);

    // EdificioEsquina2_Entrance.002
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.467, mult3 *0.615, mult3 *0.858), TAKO::Vector3f(-mult2 *4.537, mult2 *0.715, -mult2 *-2.242), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // EdificioEsquina1_1.012
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.369, mult3 *1.189, mult3 *1.510), TAKO::Vector3f(-mult2 *7.681, mult2 *1.278, -mult2 *-2.547), TAKO::Vector3f(0.0, -65.017, 0.0), true);
    // EdificioEsquina1_1.013
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.564, mult3 *1.189, mult3 *1.245), TAKO::Vector3f(-mult2 *9.051, mult2 *1.278, -mult2 *-1.544), TAKO::Vector3f(0.0, 0.111, 0.0), true);
    // EdificioEsquina3_Cones.001
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.124, mult3 *1.939, mult3 *0.731), TAKO::Vector3f(-mult2 *1.074, mult2 *2.095, -mult2 *-3.691), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // RamenCorner
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.124, mult3 *1.939, mult3 *0.930), TAKO::Vector3f(-mult2 *-1.143, mult2 *2.095, -mult2 *-3.169), TAKO::Vector3f(0.0, -3.061, 0.0), true);
    // RamenCorner_Garage
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.124, mult3 *2.078, mult3 *0.930), TAKO::Vector3f(-mult2 *-2.273, mult2 *2.095, -mult2 *-2.277), TAKO::Vector3f(0.0, -0.529, 0.0), true);
    // RamenCorner_Cones
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.124, mult3 *1.939, mult3 *0.984), TAKO::Vector3f(-mult2 *-2.523, mult2 *2.095, -mult2 *-0.534), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // TrainTracks_RamenCorner
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.124, mult3 *1.939, mult3 *0.984), TAKO::Vector3f(-mult2 *-1.660, mult2 *1.969, -mult2 *1.362), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    
    // Slope_Cones
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.124, mult3 *1.939, mult3 *0.873), TAKO::Vector3f(-mult2 *-1.080, mult2 *1.850, -mult2 *3.453), TAKO::Vector3f(0.0, 2.679, 0.0), true);
    // Buildings_Combini.018
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.143, mult3 *2.098, mult3 *2.792), TAKO::Vector3f(-mult2 *-1.219, mult2 *1.850, -mult2 *6.626), TAKO::Vector3f(0.0, 3.717, 0.0), true);
    // Combini.001
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *3.107, mult3 *0.888, mult3 *1.828), TAKO::Vector3f(-mult2 *2.566, mult2 *0.437, -mult2 *6.868), TAKO::Vector3f(0.0, 0.441, 0.0), true);
    // ParedBa\F1o.001
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.434, mult3 *3.090, mult3 *2.913), TAKO::Vector3f(-mult2 *9.242, mult2 *3.321, -mult2 *6.780), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // DetrasCombini.014
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *6.526, mult3 *3.090, mult3 *1.180), TAKO::Vector3f(-mult2 *3.702, mult2 *3.321, -mult2 *8.941), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // ParedBa\F1o_1
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.641, mult3 *0.779, mult3 *0.788), TAKO::Vector3f(-mult2 *8.402, mult2 *0.464, -mult2 *7.444), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // ParedBa\F1o_2
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.267, mult3 *0.554, mult3 *0.788), TAKO::Vector3f(-mult2 *7.576, mult2 *0.464, -mult2 *7.444), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // Coche1
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.337, mult3 *0.446, mult3 *0.354), TAKO::Vector3f(-mult2 *6.120, mult2 *0.346, -mult2 *6.792), TAKO::Vector3f(0.0, -1.517, 0.0), true);
    // Coche2
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.337, mult3 *0.332, mult3 *0.296), TAKO::Vector3f(-mult2 *6.128, mult2 *0.346, -mult2 *7.385), TAKO::Vector3f(0.0, -1.230, 0.0), true);
    // Coche3
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.337, mult3 *0.332, mult3 *0.273), TAKO::Vector3f(-mult2 *6.111, mult2 *0.346, -mult2 *6.294), TAKO::Vector3f(0.0, -1.517, 0.0), true);
    // Farola1
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.031, mult3 *1.770, mult3 *0.032), TAKO::Vector3f(-mult2 *5.346, mult2 *0.496, -mult2 *4.965), TAKO::Vector3f(0.0, 270.029, 0.0), true);
    // EscaleraContenedor
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.346, mult3 *0.359, mult3 *0.627), TAKO::Vector3f(-mult2 *0.398, mult2 *0.118, -mult2 *4.528), TAKO::Vector3f(0.0, -0.700, 0.0), true);
    // EscaleraContenedor.001
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.346, mult3 *0.359, mult3 *0.627), TAKO::Vector3f(-mult2 *0.485, mult2 *0.030, -mult2 *4.528), TAKO::Vector3f(0.0, -0.700, 0.0), true);
    // SueloUnPocoSubido
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *2.827, mult3 *0.818, mult3 *2.490), TAKO::Vector3f(-mult2 *2.790, mult2 *-0.503, -mult2 *6.418), TAKO::Vector3f(0.0, 0.218, 0.0), true);
    // SueloUnPocoSubido.001
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *2.827, mult3 *0.818, mult3 *2.490), TAKO::Vector3f(-mult2 *3.150, mult2 *-0.503, -mult2 *7.992), TAKO::Vector3f(0.0, -0.901, 0.0), true);
    // SueloUnPocoSubido.002
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.878, mult3 *0.818, mult3 *0.774), TAKO::Vector3f(-mult2 *4.917, mult2 *-0.503, -mult2 *4.882), TAKO::Vector3f(0.0, -11.796, 0.0), true);
    // Contenedor
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.031, mult3 *1.770, mult3 *0.032), TAKO::Vector3f(-mult2 *5.346, mult2 *0.496, -mult2 *4.965), TAKO::Vector3f(0.0, 270.029, 0.0), true);
    // Baños_Container
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.359, mult3 *0.258, mult3 *0.480), TAKO::Vector3f(-mult2 *8.667, mult2 *0.508, -mult2 *6.267), TAKO::Vector3f(0.0, 179.882, 0.0), true);
    // Combini_Container
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.266, mult3 *0.280, mult3 *0.414), TAKO::Vector3f(-mult2 *4.748, mult2 *0.470, -mult2 *4.833), TAKO::Vector3f(0.0, 270.029, 0.0), true);
    // EdificioEsquina1_Container
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.266, mult3 *0.258, mult3 *0.404), TAKO::Vector3f(-mult2 *8.932, mult2 *0.478, -mult2 *-0.062), TAKO::Vector3f(0.0, 89.154, 0.0), true);
    // EscalerasContainer
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.308, mult3 *0.250, mult3 *0.476), TAKO::Vector3f(-mult2 *0.265, mult2 *0.673, -mult2 *4.663), TAKO::Vector3f(0.0, 1.673, 0.0), true);
    
    // TunelAlLado
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.726, mult3 *1.528, mult3 *0.961), TAKO::Vector3f(-mult2 *10.057, mult2 *1.856, -mult2 *-0.400), TAKO::Vector3f(0.0, 179.562, 0.0), true);
    // ContainerEdificio2
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-0.275, mult3 *0.280, mult3 *0.414), TAKO::Vector3f(-mult2 *5.260, mult2 *0.434, -mult2 *-1.992), TAKO::Vector3f(0.0, 181.688, 0.0), true);
    // Carteles
    createStaticCustomMesh("media/Level1/Assets/empty.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *-3.022, mult3 *1.954, mult3 *0.961), TAKO::Vector3f(-mult2 *2.685, mult2 *1.856, -mult2 *7.653), TAKO::Vector3f(0.0, 179.874, 0.0), true);

    // SueloEsquina.001
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.175, mult3 *0.818, mult3 *2.490), TAKO::Vector3f(-mult2 *2.888, mult2 *-0.536, -mult2 *-3.385), TAKO::Vector3f(0.0, 0.010, 0.0), true);
    // SueloEsquina.002
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.201, mult3 *0.818, mult3 *2.490), TAKO::Vector3f(-mult2 *6.736, mult2 *-0.532, -mult2 *-4.599), TAKO::Vector3f(0.0, 9.274, 0.0), true);
    // SueloEsquina.003
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.201, mult3 *0.818, mult3 *2.490), TAKO::Vector3f(-mult2 *8.307, mult2 *-0.527, -mult2 *-4.134), TAKO::Vector3f(0.0, 26.826, 0.0), true);
    // SueloEsquina.004
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.363, mult3 *0.850, mult3 *2.587), TAKO::Vector3f(-mult2 *10.697, mult2 *-0.562, -mult2 *-1.274), TAKO::Vector3f(0.0, 85.820, 0.0), true);
    // SueloEsquina.005
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.363, mult3 *0.850, mult3 *2.587), TAKO::Vector3f(-mult2 *10.808, mult2 *-0.562, -mult2 *-1.084), TAKO::Vector3f(0.0, 90.145, 0.0), true);
    // SueloEsquina.006
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.363, mult3 *0.850, mult3 *1.615), TAKO::Vector3f(-mult2 *4.542, mult2 *-0.562, -mult2 *-3.247), TAKO::Vector3f(0.0, 110.109, 0.0), true);
    // SueloEsquina
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.826, mult3 *0.623, mult3 *0.901), TAKO::Vector3f(-mult2 *4.505, mult2 *-0.346, -mult2 *-1.976), TAKO::Vector3f(0.0, 159.526, 0.0), true);
    // SueloRamen
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.175, mult3 *0.818, mult3 *2.490), TAKO::Vector3f(-mult2 *-0.946, mult2 *-0.536, -mult2 *-3.666), TAKO::Vector3f(0.0, -2.861, 0.0), true);
    // SueloRamen.001
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.175, mult3 *0.818, mult3 *2.490), TAKO::Vector3f(-mult2 *-0.835, mult2 *-0.536, -mult2 *-3.614), TAKO::Vector3f(0.0, -0.243, 0.0), true);

    // Tunel
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.773, mult3 *1.011, mult3 *1.084), TAKO::Vector3f(-mult2 *9.626, mult2 *0.986, -mult2 *1.587), TAKO::Vector3f(0.0, 0.218, 0.0), true);
    // CaminoTren
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.773, mult3 *1.011, mult3 *1.084), TAKO::Vector3f(-mult2 *-2.401, mult2 *0.986, -mult2 *1.587), TAKO::Vector3f(0.0, 0.218, 0.0), true);
    // SueloBanyo
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.839, mult3 *0.818, mult3 *2.040), TAKO::Vector3f(-mult2 *8.063, mult2 *-0.505, -mult2 *7.640), TAKO::Vector3f(0.0, 0.218, 0.0), true);
    // PasoDelTren
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.924, mult3 *0.832, mult3 *1.279), TAKO::Vector3f(-mult2 *0.919, mult2 *-0.609, -mult2 *1.602), TAKO::Vector3f(0.0, 0.218, 0.0), true);

    // PosteTren1
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.027, mult3 *1.145, mult3 *0.026), TAKO::Vector3f(-mult2 *5.241, mult2 *0.407, -mult2 *1.620), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // PosteTren2
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.027, mult3 *1.145, mult3 *0.026), TAKO::Vector3f(-mult2 *2.015, mult2 *0.407, -mult2 *1.620), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // EdificioTunel
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.091, mult3 *1.769, mult3 *1.076), TAKO::Vector3f(-mult2 *8.856, mult2 *1.557, -mult2 *3.715), TAKO::Vector3f(0.0, 0.000, 0.0), true);

    // OBJS
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Building3.obj",   TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/RamenShop.obj",   TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Building2.obj",   TAKO::Vector3f(0,-2,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Building1.obj",   TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Montan.obj",   TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Postes.obj",   TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Tunel_Done.obj",   TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/cercabanyo.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/banyos.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/combini.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/CasetaCombini.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/fabrica.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/CasetaIzquierda.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/suelo.obj", TAKO::Vector3f(0,0,11), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/sueloAlto.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/escaleras.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Coche.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/EdificioCosaRara.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/ParedEscalera.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Cono.obj", TAKO::Vector3f(0,2.3,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/EdificioSinCosaRara.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/EdificioCosaRara2.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Coche.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Coche.002.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Coche.003.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Coche.004.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/cercabanyo.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/CasetaCombini.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/MuroAlto.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/MuroAlto.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/MuroBanyo.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Barrera1.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Barrera2.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Cono.001.obj", TAKO::Vector3f(0,2.3,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Cono.002.obj", TAKO::Vector3f(0,2.3,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Cono.003.obj", TAKO::Vector3f(0,1,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Cono.004.obj", TAKO::Vector3f(0,4,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/BarreraRampa.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Rail.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Rail.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Rail.002.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Rail.003.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Cable.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Cable.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Cable.002.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Cable.003.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Muro trenizq.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Muro trendcha.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Contenedor.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Contenedor.002.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Contenedor.003.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Contenedor.004.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Contenedor.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/BarreraBaja.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/BarreraBaja.000.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/ParedEscalera.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/farola.002.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/farola.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/farola.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/farola.003.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Coche.004.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Muro trenizq.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/EdificioSinCosaRara.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/casetatren.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));

    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Cono.005.obj", TAKO::Vector3f(0,-3,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Veterinario.obj", TAKO::Vector3f(0,-12,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Veterinario Icono.obj", TAKO::Vector3f(0,-12,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/mitsudes.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/pleaseDrinkMoreWater.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/cuasmic.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/st andrews.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/GOGOGO.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));

    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/vert1.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Beige.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Beige.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/vert2.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Beige.002.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/autovia1.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/autovia2.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Molon.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Aps.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Hor.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Hor.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Doof.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Edificios.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *50, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/fabrica2.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));

    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Muro.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));

    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Ventanal.obj", TAKO::Vector3f(0,0,35), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));

    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Cono.005.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));

    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/farolilloramen.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/farolillo.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/Tunel_Done2.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level1/AssetsNuevos/cable.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    
    createTrainComponent();
}

void EntityManager::createLevel2(){
    int mult = 2.5; // This is 3 in createLevel
    int multEscala = 4;

    // BUILDINGS:
    float multY = mult ;
    float mult2 = mult *30; 
    float mult3 = mult * 6;
    float mult3x = mult *6;
    float mult3y = mult *6;
    float mult3z = mult *6;

    //BBoxes
    // Alto.001
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *5.194, mult3 *1.011, mult3 *1.000), TAKO::Vector3f(-mult2 *0.496, mult2 *0.222, -mult2 *2.650), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // Alto
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *5.194, mult3 *1.011, mult3 *1.000), TAKO::Vector3f(-mult2 *0.496, mult2 *0.222, -mult2 *-8.147), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // Medio.001
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.761, mult3 *0.812, mult3 *5.329), TAKO::Vector3f(-mult2 *4.565, mult2 *-0.191, -mult2 *-2.747), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // Medio
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *0.759, mult3 *0.812, mult3 *5.329), TAKO::Vector3f(-mult2 *-2.880, mult2 *-0.191, -mult2 *-2.747), TAKO::Vector3f(0.0, 0.000, 0.0), true);
    // Pared
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.774, mult3 *5.679, mult3 *8.107), TAKO::Vector3f(-mult2 *-5.402, mult2 *4.155, -mult2 *-3.253), TAKO::Vector3f(0.0, 0.218, 0.0), true);
    // Pared.001
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.774, mult3 *5.679, mult3 *8.107), TAKO::Vector3f(-mult2 *7.037, mult2 *4.155, -mult2 *-3.253), TAKO::Vector3f(0.0, 0.218, 0.0), true);
    // Pared.002
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *6.405, mult3 *5.679, mult3 *-1.446), TAKO::Vector3f(-mult2 *0.348, mult2 *4.155, -mult2 *4.908), TAKO::Vector3f(0.0, 0.218, 0.0), true);
    // Pared.003
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *6.405, mult3 *5.679, mult3 *-1.446), TAKO::Vector3f(-mult2 *0.348, mult2 *4.155, -mult2 *-10.536), TAKO::Vector3f(0.0, 0.218, 0.0), true);
    // Esquina
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.774, mult3 *5.679, mult3 *3.065), TAKO::Vector3f(-mult2 *5.851, mult2 *4.155, -mult2 *3.986), TAKO::Vector3f(0.0, 45.114, 0.0), true);
    // Esquina.001
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *1.774, mult3 *5.679, mult3 *3.065), TAKO::Vector3f(-mult2 *5.709, mult2 *4.155, -mult2 *-9.685), TAKO::Vector3f(0.0, -45.084, 0.0), true);
    // Suelo
    createStaticCustomMesh("media/Level1/Assets/empty.obj",TAKO::Vector3f(0,-1,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30), TAKO::Vector3f(mult3 *6.217, mult3 *1.363, mult3 *8.050), TAKO::Vector3f(-mult2 *1.265, mult2 *-1.327, -mult2 *-2.234), TAKO::Vector3f(0.0, 0.000, 0.0), true);


    // SLOPES
    // RampaMedio
    createSlope("media/Level1/Assets/empty.obj",TAKO::Vector3f(-mult2 *3.256, mult2 *0.331, -mult2 *-2.747), TAKO::Vector3f(0,0,0), TAKO::Vector3f(mult3 *0.571, mult3 *0.288, mult3 *1.630), true, false);
    // RampaMedio.001
    createSlope("media/Level1/Assets/empty.obj",TAKO::Vector3f(-mult2 *-1.554, mult2 *0.331, -mult2 *-2.747), TAKO::Vector3f(0,0,0), TAKO::Vector3f(mult3 *0.571, mult3 *0.288, mult3 *1.623), true, true);
    // Medio.004
    createSlope("media/Level1/Assets/empty.obj",TAKO::Vector3f(-mult2 *-2.885, mult2 *0.931, -mult2 *-6.444), TAKO::Vector3f(0,0,0), TAKO::Vector3f(mult3 *0.748, mult3 *0.304, mult3 *0.703), false, true);
    // RampaEsquina
    createSlope("media/Level1/Assets/empty.obj",TAKO::Vector3f(-mult2 *4.568, mult2 *0.931, -mult2 *-6.444), TAKO::Vector3f(0,0,0), TAKO::Vector3f(mult3 *0.748, mult3 *0.304, mult3 *0.703), false, true);
    // Medio.006
    createSlope("media/Level1/Assets/empty.obj",TAKO::Vector3f(-mult2 *-2.885, mult2 *0.931, -mult2 *0.953), TAKO::Vector3f(0,0,0), TAKO::Vector3f(mult3 *0.748, mult3 *0.304, mult3 *0.703), false, false);
    // RampaEsquina.001
    createSlope("media/Level1/Assets/empty.obj",TAKO::Vector3f(-mult2 *4.568, mult2 *0.931, -mult2 *0.953), TAKO::Vector3f(0,0,0), TAKO::Vector3f(mult3 *0.748, mult3 *0.304, mult3 *0.703), false, false);
    

    // Meshes

    createStaticCustomMeshNoBBox("media/Level2/Assets/GradaBaja.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/TubosTecho.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/GradaAlta.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    //createStaticCustomMeshNoBBox("media/Level2/Assets/Plane.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/GradaBaja.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/GradaMedia.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/EntradaGrada.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/PilarColumna.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/PilarColumna.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/PuertaArena.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Plataformas.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Cube.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));

    createStaticCustomMeshNoBBox("media/Level2/Assets/Verja.003.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Verja.002.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Verja.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Verja.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Esquina.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Esquina.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Entrada.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Entrada.004.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Entrada.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Entrada.003.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Entrada.002.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Plane.002.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/TubreiaEscondida.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/TelaEscondida.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/TuberiaEscondida.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Tuberia1.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/ColumnaTuberia1.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/Tuberia2.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Assets/ColumnaTuberia2.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));

    createStaticCustomMeshNoBBox("media/Level2/Other/Hierba.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/Hierba.002.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/Hierba.004.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/Hierba.005.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/Hierba.003.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/Hierba.006.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/Hierba.007.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/Hierba.008.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/Hierba.009.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/Hierba.010.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/Hierba.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));

    //Fondo
    createStaticCustomMeshNoBBox("media/Level2/Fondo/azulLejos.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Cube.034.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/EdificioSinCosaRaraOld.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/autovia1.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Cube.039.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Cube.041.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Cube.043.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Cube.044.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Cube.045.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/CasetaIzquierda.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Cube.047.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/EdificioCosaRara2.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Hor.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/vert1.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Beige.002.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Beige.000.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Edificios.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Edificios.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Molon.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Aps.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Aps.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Cube.003.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Hor.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/MuroAlto.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/MuroAlto.001.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/MuroAlto.002.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/MuroAlto.003.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/MuroAlto.004.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Fondo/Suelo.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));

    // Nubes
    // Nube1
    createResizableBillboard(TAKO::Vector3f(-mult2 *12.077, mult2 *35.444, -mult2 *-26.330), TAKO::Vector3f(200, 200, 200), "media/meshes/Clouds/Nube1.obj");
    // Nube1.001
    createResizableBillboard(TAKO::Vector3f(-mult2 *-26.535, mult2 *38.212, -mult2 *0.629), TAKO::Vector3f(200, 200, 200), "media/meshes/Clouds/Nube1.obj");
    // Nube1.002
    createResizableBillboard(TAKO::Vector3f(-mult2 *-8.548, mult2 *33.823, -mult2 *-20.252), TAKO::Vector3f(200, 200, 200), "media/meshes/Clouds/Nube1.obj");
    // Nube1.003
    createResizableBillboard(TAKO::Vector3f(-mult2 *-9.539, mult2 *36.989, -mult2 *28.745), TAKO::Vector3f(200, 200, 200), "media/meshes/Clouds/Nube1.obj");
    // Nube2
    createResizableBillboard(TAKO::Vector3f(-mult2 *-20.566, mult2 *40.554, -mult2 *10.598), TAKO::Vector3f(200, 200, 200), "media/meshes/Clouds/Nube2.obj");
    // Nube2.001
    createResizableBillboard(TAKO::Vector3f(-mult2 *14.225, mult2 *39.115, -mult2 *31.435), TAKO::Vector3f(200, 200, 200), "media/meshes/Clouds/Nube2.obj");
    // Nube2.002
    createResizableBillboard(TAKO::Vector3f(-mult2 *27.991, mult2 *43.843, -mult2 *-15.560), TAKO::Vector3f(200, 200, 200), "media/meshes/Clouds/Nube2.obj");
    // Nube2.003
    createResizableBillboard(TAKO::Vector3f(-mult2 *-21.137, mult2 *44.436, -mult2 *-16.721), TAKO::Vector3f(200, 200, 200), "media/meshes/Clouds/Nube2.obj");
    // Nube3
    createResizableBillboard(TAKO::Vector3f(-mult2 *39.199, mult2 *33.166, -mult2 *6.356), TAKO::Vector3f(200, 200, 200), "media/meshes/Clouds/Nube3.obj");
    
    // BeltIzq
    createConveyorBelt(TAKO::Vector3f(-mult2 *1.697, mult2 *0.096, -mult2 *-2.747), TAKO::Vector3f(mult3 *0.458, mult3 *0.166, mult3 *4.045), false, true);
    // BeltDch
    createConveyorBelt(TAKO::Vector3f(-mult2 *-0.027, mult2 *0.096, -mult2 *-2.747), TAKO::Vector3f(mult3 *0.458, mult3 *0.166, mult3 *4.045), false, false);


    // Saw
    createSaw(TAKO::Vector3f(-mult2 *-0.021, mult2 *0.424, -mult2 *-7.284), TAKO::Vector3f(mult3 *0.315, mult3 *0.469, mult3 *0.311), false, 0);
    // Saw.001
    createSaw(TAKO::Vector3f(-mult2 *1.705, mult2 *0.424, -mult2 *-7.284), TAKO::Vector3f(mult3 *0.315, mult3 *0.469, mult3 *0.311), false, 1);
    // Saw.002
    createSaw(TAKO::Vector3f(-mult2 *-0.021, mult2 *0.424, -mult2 *1.760), TAKO::Vector3f(mult3 *0.315, mult3 *0.469, mult3 *0.311), true, 2);
    // Saw.003
    createSaw(TAKO::Vector3f(-mult2 *1.705, mult2 *0.424, -mult2 *1.760), TAKO::Vector3f(mult3 *0.315, mult3 *0.469, mult3 *0.311), true, 3);

    // Dcha
    createPiston(TAKO::Vector3f(-mult2 *-1.389, mult2 *0.018, -mult2 *-6.416), TAKO::Vector3f(0,0,0), TAKO::Vector3f(mult3 *0.690, mult3 *0.431, mult3 *0.687));
    // EsquinaDcha
    createPiston(TAKO::Vector3f(-mult2 *3.074, mult2 *0.018, -mult2 *-6.416), TAKO::Vector3f(0,0,0), TAKO::Vector3f(mult3 *0.690, mult3 *0.431, mult3 *0.687));
    // Izq
    createPiston(TAKO::Vector3f(-mult2 *-1.389, mult2 *0.018, -mult2 *0.932), TAKO::Vector3f(0,0,0), TAKO::Vector3f(mult3 *0.690, mult3 *0.431, mult3 *0.687));
    // EsquinaIzq
    createPiston(TAKO::Vector3f(-mult2 *3.074, mult2 *0.018, -mult2 *0.932), TAKO::Vector3f(0,0,0), TAKO::Vector3f(mult3 *0.690, mult3 *0.431, mult3 *0.687));

    // Bases pistones
    createStaticCustomMeshNoBBox("media/Level2/Other/4.004.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/3.004.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/1.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));
    createStaticCustomMeshNoBBox("media/Level2/Other/2.004.obj", TAKO::Vector3f(0,0,0), TAKO::Vector3f(0,0,0), TAKO::Vector3f( mult *30, multY *30, mult *30));

}
std::size_t EntityManager::createLevel(Levels currentLevel, Characters currentCharacter, bool isonline, Characters enemyCharacter, const int graphicsMode){

    createCamera(TAKO::Vector3f(-403,60,-400),TAKO::Vector3f(0,0,0));

    //Spawn Positions
    auto& entity = createEntityBase();
    auto& spawnPoints = componentManager->addComponent<SpawnPointsComponent>(entity.id);
    Vector3f playerPos, enemyPos;

    switch (currentLevel)
    {
    case Levels::STATION :
        //std::cout<<"1"<<std::endl;
        engine.deleteResourcesFolder("media/Level2");
        engine.deleteResourcesFolder("media/Character/Boss2");
        createLevel1();
        if(!isonline)    enemyCharacter = Characters::BOSS1;
        spawnPoints.positions.emplace_back(std::make_pair(false, TAKO::Vector3f( -601, 24.3, -342)));
        spawnPoints.positions.emplace_back(std::make_pair(false, TAKO::Vector3f( -423, 17.3, -146)));
        spawnPoints.positions.emplace_back(std::make_pair(false, TAKO::Vector3f( 621, 25.3, 112)));
        spawnPoints.positions.emplace_back(std::make_pair(false, TAKO::Vector3f( -412, 123.3, 172)));
        spawnPoints.positions.emplace_back(std::make_pair(false, TAKO::Vector3f( -25, 23.3, 93)));
        spawnPoints.positions.emplace_back(std::make_pair(false, TAKO::Vector3f( -316, 120.3, -542)));
        playerPos = Vector3f(-403,47,-299);
        enemyPos  = Vector3f(-403,47,-11);
        break;
    case Levels::FACTORY :
        //std::cout<<"2"<<std::endl;
        engine.deleteResourcesFolder("media/Level2");
        engine.deleteResourcesFolder("media/Character/Boss1");
        createLevel2();
        if(!isonline)    enemyCharacter = Characters::BOSS2;
        spawnPoints.positions.emplace_back(std::make_pair(false, TAKO::Vector3f(-245, 76.3, -139)));
        spawnPoints.positions.emplace_back(std::make_pair(false, TAKO::Vector3f(  86,  241, -71)));
        spawnPoints.positions.emplace_back(std::make_pair(false, TAKO::Vector3f( -51,  4.3, 170)));
        spawnPoints.positions.emplace_back(std::make_pair(false, TAKO::Vector3f( 156, 76.3, 503)));
        spawnPoints.positions.emplace_back(std::make_pair(false, TAKO::Vector3f(-185,  241, 387)));
        playerPos = Vector3f( 164,63,170);
        enemyPos  = Vector3f(-270,63,170);
        break;
    default:
        //std::cout<<"No level"<<std::endl;
        break;
    }

    malloc_trim(0);
    createPlayer(currentCharacter, playerPos, Vector3f(12),Vector3f(0), graphicsMode);
    createEnemy(enemyCharacter,enemyPos, Vector3f(12),Vector3f(0), graphicsMode);
    //directional lights
    //TODO DELETE OR CHANGE VALUE? Maybe it's interesting to have a node in the ECS for the lights
    float r, g, b;
    r = 255;
    g = 241;
    b = 235; 
    r /= 250;
    g /= 250;
    b /= 250;
    engine.createDirectionalLight(glm::vec3(-1.0f,-10.0f, 1.0f), glm::vec3(r, g, b),glm::vec3(r, g, b), glm::vec3(0.8f));
    createSkyBox(Vector3f(400,400,400));

    return entity.id;
}

void EntityManager::createTrainComponent(){

    auto& entity = createEntityBase();

    int mult = 3;
    float mult2 = mult * 30; 
    float mult3 = mult * 6;
    TAKO::Vector3f pos = TAKO::Vector3f(-17.020 * mult2, mult2 *0.544, -mult2 *1.146);
    TAKO::Vector3f posMesh = TAKO::Vector3f(-17.020 * mult2, mult2 *0.544 + 20, -mult2 *1.146);
    TAKO::Vector3f scale = TAKO::Vector3f(mult3 *1.115, mult3 *0.702, mult3 *0.435);
    TAKO::Vector3f scaleMesh = TAKO::Vector3f( mult *30, mult *30, mult *30);
    
    auto& trainComp = componentManager->addComponent<TrainComponent>(entity.id);

    trainComp.line = true;
    srand(time(NULL));
    trainComp.carriages = rand() % 4 + 3;
    trainComp.timer = rand()% 5 + 5;

    for (unsigned i = 0; i < 8; i++)
    {
        trainComp.nodes.push_back(engine.createMesh("media/Level1/AssetsNuevos/tren.obj"));
        trainComp.nodes[i].setPosition(posMesh);
        trainComp.nodes[i].setScale(scaleMesh);


        // Nodes bbox
        OBB2D auxOB;
        trainComp.bboxes.push_back(auxOB);

        trainComp.bboxes[i].node = engine.createBBox();
        trainComp.bboxes[i].node.setPosition(pos);
        trainComp.bboxes[i].node.setScale(scale);
        trainComp.bboxes[i].node.setVisible(false);
    }
    

   
    //trainComp.bbox.node.setVisible(false);


    auto& positionComp = componentManager->addComponent<PositionComponent>(entity.id);
    positionComp.pos = pos;
}

std::size_t EntityManager::createResizableBillboard(Vector3f position, Vector3f scale, std::string filepath){
    auto& entity = createEntityBase();
    auto& irrbasicnodeComp = componentManager->addComponent<IrrbasicnodeComponent>(entity.id); // COMPONENT_IRRBASICNODE

    // SUMI::SUMIDrawableNode plano = engine.createVegetation("media/meshes/Clouds/Nube3.obj");
    // plano.setPosition(TAKO::Vector3f(0,70,0));
    // plano.setScale(TAKO::Vector3f(10,10,10));

    irrbasicnodeComp.node = engine.createVegetation(filepath); //engine.createVegetation(filepath.c_str());
    irrbasicnodeComp.node.setPosition(position);
    irrbasicnodeComp.node.setScale(scale);

    return entity.id;
}
std::size_t EntityManager::createSkyBox(Vector3f scale){
    //TODO: necesita ser una entidad del ecs para poder ser borrado
    auto& entity = createEntityBase();
    auto& irrbasicnodeComp = componentManager->addComponent<IrrbasicnodeComponent>(entity.id); // COMPONENT_IRRBASICNODE

    engine.createVegetation("media/meshes/Clouds/Nube3.obj");

    irrbasicnodeComp.node = engine.createSkyBox();
    irrbasicnodeComp.node.setScale(scale);

    return entity.id;
}

void EntityManager::generatePowerUp(int numofboxes, std::vector<std::pair<bool,TAKO::Vector3f>>& positions, bool online){
    auto i = 0;
    srand((unsigned) time(0));
    while(i<numofboxes){      
        int pwup = std::rand()%(7)+1;
        int position = std::rand()%(positions.size());
        if(!positions[position].first){
            positions[position].first = true;

            std::string iconPath;
            std::string filepath;
            float cooldown;
            PowerUpEnum pwType = static_cast<PowerUpEnum>(pwup);
            int pwCode=0;
            switch (pwType)
            {
            case PowerUpEnum::DEFENSE:
                pwCode=1;
                cooldown = 10;
                iconPath = "media/HUD/Pwup_defensa.png";
                filepath = "media/PowerUps/shield.obj";
                break;
            case PowerUpEnum::DAMAGE:
                pwCode=2;
                cooldown = 10;
                iconPath = "media/HUD/Pwup_fuerza.png";
                filepath = "media/PowerUps/strength.obj";
                break;
            case PowerUpEnum::VELOCITY:
                pwCode=3;   
                cooldown = 10;
                iconPath = "media/HUD/Pwup_velocidad.png";
                filepath = "media/PowerUps/gears.obj";
                break;
            case PowerUpEnum::HEALTH:
                pwCode=4;  
                cooldown = 5;
                iconPath = "media/HUD/Pwup_salud.png";
                filepath = "media/PowerUps/salud.obj";
                break;
            case PowerUpEnum::STUN:
                pwCode=5;  
                cooldown = 10;
                iconPath = "media/HUD/Pwup_stun.png";
                filepath = "media/PowerUps/stun.obj";
                break;
            case PowerUpEnum::ESTAMINA:
                pwCode=6; 
                cooldown = 5;
                iconPath = "media/HUD/Pwup_stamina.png";
                filepath = "media/PowerUps/stamina.obj";
                break;
            case PowerUpEnum::DOUBLE_JUMP:
            default:
                pwCode=7; 
                pwType = PowerUpEnum::DOUBLE_JUMP;
                cooldown = 5;
                iconPath = "media/HUD/Pwup_salto.png";
                filepath = "media/PowerUps/spring.obj";
                break;
            }
            //Setting up power up online sending
            if(online){
                for(auto& spawnPointComp : gameStorage->getComponentsOfType<SpawnPointsComponent>()){
                    spawnPointComp.type.push_back(pwCode);
                    spawnPointComp.pos.push_back(position);
                } 

            }
            //un switch con los paths, y cooldowns
            createPowerUp(filepath.c_str(), iconPath, positions[position].second,position, TAKO::Vector3f(15,15,15), pwType , cooldown);
            ++i;
        }
    }
}

void EntityManager::generatePowerUpOnline(int type, int vectorpos, std::vector<std::pair<bool,TAKO::Vector3f>>& positions){
    positions[vectorpos].first = true;
    std::string texturePath;
    std::string iconPath;
    std::string filepath;
    float cooldown;
    PowerUpEnum pwType;
    switch(type){
        case 1:
        pwType = PowerUpEnum::DEFENSE;
        cooldown = 10;
        iconPath = "media/HUD/Pwup_defensa.png";
        filepath = "media/PowerUps/shield.obj";
        break;
        case 2:
        pwType = PowerUpEnum::DAMAGE;
        cooldown = 10;
        iconPath = "media/HUD/Pwup_fuerza.png";
        filepath = "media/PowerUps/strength.obj";
        break;
        case 3:
        pwType = PowerUpEnum::VELOCITY;
        cooldown = 10;
        iconPath = "media/HUD/Pwup_velocidad.png";
        filepath = "media/PowerUps/gears.obj";        
        break;
        case 4:
        pwType = PowerUpEnum::HEALTH;
        cooldown = 5;
        iconPath = "media/HUD/Pwup_salud.png";
        filepath = "media/PowerUps/salud.obj";
        break;
        case 5:
        pwType = PowerUpEnum::STUN;
        cooldown = 10;
        iconPath = "media/HUD/Pwup_stun.png";
        filepath = "media/PowerUps/stun.obj";
        break;
        case 6:
        pwType = PowerUpEnum::ESTAMINA;
        cooldown = 5;
        iconPath = "media/HUD/Pwup_stamina.png";
        filepath = "media/PowerUps/stamina.obj";
        break;
        case 7:
        pwType = PowerUpEnum::DOUBLE_JUMP;
        cooldown = 10;
        iconPath = "media/HUD/Pwup_salto.png";
        filepath = "media/PowerUps/spring.obj";
        break;
    }

    createPowerUp(filepath.c_str(), iconPath, positions[vectorpos].second,vectorpos,TAKO::Vector3f(15,15,15), pwType , cooldown);

}

std::size_t EntityManager::createCamera(TAKO::Vector3f position, TAKO::Vector3f lookat) {
    auto& entity = createEntityBase();

    auto& positionComp = componentManager->addComponent<PositionComponent>(entity.id);
    auto& lookatComp = componentManager->addComponent<LookAtComponent>(entity.id);
    auto& irrcameranodeComp = componentManager->addComponent<IrrcameranodeComponent>(entity.id);
    auto& directionComp = componentManager->addComponent<DirectionComponent>(entity.id);
    auto& distanceComp = componentManager->addComponent<DistanceComponent>(entity.id);
    auto& bBoxCameraComp = componentManager->addComponent<BBoxCameraComponent>(entity.id);
    auto& velocityComp = componentManager->addComponent<VelocityComponent>(entity.id);
   

    positionComp.pos = TAKO::Vector3f(position.X,position.Y,position.Z);
    lookatComp.lkat = TAKO::Vector3f(lookat.X,lookat.Y,lookat.Z);
    distanceComp.distance = TAKO::Vector3f(70.f,70.f,70.f);
    velocityComp.vel = CAMERA_VEL_REGULAR;
    // Nodes bbox
    bBoxCameraComp.body.node = engine.createCubeMesh();
    bBoxCameraComp.body.node.setPosition(position);
    bBoxCameraComp.body.node.setRotation(lookat); //TODO ???
    bBoxCameraComp.body.node.setScale(TAKO::Vector3f(1.f,1.f,1.f));
    bBoxCameraComp.body.node.setVisible(false);


    //CAMERA NODE
    irrcameranodeComp.node = engine.getActiveCamera();
    return entity.id;
}
std::size_t EntityManager::createPowerUpBox(std::string texturepath, std::string iconpath, TAKO::Vector3f position, int generatedPosition, TAKO::Vector3f scale, PowerUpEnum powerUp, float cooldown){
    auto& entity = createEntityBase();

    auto& positionComp = componentManager->addComponent<PositionComponent>(entity.id);
    auto& rotationComp = componentManager->addComponent<RotationComponent>(entity.id);
    auto& pwupComp = componentManager->addComponent<PowerUpComponent>(entity.id);
    auto& basicnodeComp = componentManager->addComponent<IrrbasicnodeComponent>(entity.id);
    auto& bboxpropsComp =  componentManager->addComponent<BBoxPropsComponent>(entity.id);


    positionComp.pos = position;
    rotationComp.rot = Vector3f(0,0,0);
    //asignar textura según el tipo de PW, ahora será por defecto
    pwupComp.pwup = powerUp;
    pwupComp.pwupTime = cooldown;
    pwupComp.generatedPos = generatedPosition;
    pwupComp.icon_path = iconpath;

    // SUMI ENGINE
    basicnodeComp.node = engine.createCubeMesh();
    engine.changeMaterial(basicnodeComp.node, texturepath.c_str());
    basicnodeComp.node.setPosition(position);
    basicnodeComp.node.setScale(scale);

    // Nodes bbox
    bboxpropsComp.body.node = engine.createBBox();
    bboxpropsComp.body.node.setPosition(position);
    bboxpropsComp.body.node.setScale(scale);
    bboxpropsComp.body.node.setVisible(false);
    BBoxUtils::calculateBBox(bboxpropsComp.body, position, 0, defaultBoxSize);



    return entity.id;  
}

std::size_t EntityManager::createPowerUp(std::string filepath, std::string iconpath, TAKO::Vector3f position, int generatedPosition, TAKO::Vector3f scale, PowerUpEnum powerUp, float cooldown){
    auto& entity = createEntityBase();

    auto& positionComp = componentManager->addComponent<PositionComponent>(entity.id);
    auto& rotationComp = componentManager->addComponent<RotationComponent>(entity.id);
    auto& pwupComp = componentManager->addComponent<PowerUpComponent>(entity.id);
    auto& basicnodeComp = componentManager->addComponent<IrrbasicnodeComponent>(entity.id);
    auto& bboxpropsComp =  componentManager->addComponent<BBoxPropsComponent>(entity.id);


    positionComp.pos = position;
    rotationComp.rot = Vector3f(0,0,0);
    //asignar textura según el tipo de PW, ahora será por defecto
    pwupComp.pwup = powerUp;
    pwupComp.pwupTime = cooldown;
    pwupComp.generatedPos = generatedPosition;
    pwupComp.icon_path = iconpath;

    basicnodeComp.node = engine.createMesh(filepath.c_str());
    //engine.changeMaterial(basicnodeComp.node, "media/texture/");
    basicnodeComp.node.setPosition(position);
    basicnodeComp.node.setScale(scale);

    // Nodes bbox
    bboxpropsComp.body.node = engine.createBBox();
    bboxpropsComp.body.node.setPosition(position);
    bboxpropsComp.body.node.setScale(scale/6);
    bboxpropsComp.body.node.setVisible(false);
    BBoxUtils::calculateBBox(bboxpropsComp.body, position, 0, defaultBoxSize);

    


    return entity.id;  
}

void EntityManager::createPlayable(std::size_t ID, Characters character, TAKO::Vector3f position, TAKO::Vector3f scale, TAKO::Vector3f rotation, const int graphicsMode){
    auto playerID = ID;

    auto& playableComp = componentManager->addComponent<TagPlayable>(playerID); // COMPONENT_PLAYABLE
    auto& positionComp = componentManager->addComponent<PositionComponent>(playerID); // COMPONENT_POSITION
    auto& rotationComp = componentManager->addComponent<RotationComponent>(playerID); // COMPONENT_ROTATION
    auto& irranimatednodeComp = componentManager->addComponent<IrranimatednodeComponent>(playerID); // COMPONENT_IRRANIMATEDNODE
    auto& velocityComp = componentManager->addComponent<VelocityComponent>(playerID); // COMPONENT_VELOCITY
    auto& directionComp = componentManager->addComponent<DirectionComponent>(playerID); // COMPONENT_DIRECTION
    auto& bBoxComp = componentManager->addComponent<BBoxComponent>(playerID); // COMPONENT_BBOX
    auto& healthComp = componentManager->addComponent<HealthComponent>(playerID); // COMPONENT_HEALTH 
    auto& powerUpComp = componentManager->addComponent<PowerUpComponent>(playerID); // COMPONENT_POWERUP
    auto& staminaComp = componentManager->addComponent<StaminaComponent>(playerID); // COMPONENT_STAMINA
    auto& dashComp = componentManager->addComponent<DashComponent>(playerID); // COMPONENT_DASH
    auto& damageFeedbackComp = componentManager->addComponent<DamageFeedbackComponent>(playerID); // COMPONENT_DAMAGEFEEDBACK
    auto& fistComp = componentManager->addComponent<FistComponent>(playerID); // COMPONENT_FIST
    auto& soundComp = componentManager->addComponent<SoundComponent>(playerID); // COMPONENT_SOUND

    const int defaultBoxSize = 10;
    const int fistLocation = defaultBoxSize/2 + 1;
    const int fistLocationY = 22;

    std::string basePath;
    switch (character) {
        case Characters::PUNCHIES :
            basePath = "media/Character/Punchies/";
            break;
        case Characters::BOSS1 :
            basePath = "media/Character/Boss1/";
            break;
        case Characters::BOSS2 :
            basePath = "media/Character/Boss2/";
            break;
        default:
            break;
    }

    //Dash
    dashComp.dashCooldown = 0;
    dashComp.dashing = false;
    dashComp.previousPos = Vector3f(0,0,0);
    dashComp.previousVel = Vector3f(0,0,0);

    //HEALTH
    healthComp.HP = MAX_HP;

    //Stamina
    staminaComp.stamina = MAX_STAMINA;
    //POSITION
    positionComp.pos = position;
    //ROTATION
    rotationComp.rot = rotation;
    // Node Animated model

    irranimatednodeComp.node = engine.createAnimatedMesh(basePath + "Neutral.obj");

    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
    engine.loadAnimation8Axis(irranimatednodeComp.node, "Neutral", basePath + "Neutral/Neutral_000000.fbx", graphicsMode, "Neutral", 30);
    engine.loadAnimation8Axis(irranimatednodeComp.node, "Block", basePath + "Block/Block_000000.fbx", graphicsMode, "Block", 30);
    engine.loadAnimation8Axis(irranimatednodeComp.node, "DirectR", basePath + "DirectR/DirectR_000000.fbx", graphicsMode, "Neutral", 60, scale);
    engine.loadAnimation8Axis(irranimatednodeComp.node, "DirectL", basePath + "DirectL/DirectL_000000.fbx", graphicsMode, "Neutral", 60, scale);
    engine.loadAnimation8Axis(irranimatednodeComp.node, "CrochetR", basePath + "CrochetR/CrochetR_000000.fbx", graphicsMode, "Neutral", 60, scale);
    engine.loadAnimation8Axis(irranimatednodeComp.node, "CrochetL", basePath + "CrochetL/CrochetL_000000.fbx", graphicsMode, "Neutral", 60, scale);
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
    //std::cout << "Time loading Axis animations = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1).count() << "[ns]\n";
    begin1 = std::chrono::steady_clock::now();
    engine.loadAnimation(irranimatednodeComp.node, "Jump", basePath + "Jump/Jump_000000.fbx", graphicsMode, "", 60);
    engine.loadAnimation(irranimatednodeComp.node, "GroundPound", basePath + "GroundPound/GroundPound_000000.fbx", graphicsMode, "Neutral", 30);
    engine.loadAnimation(irranimatednodeComp.node, "UppercutPreviousR", basePath + "UppercutPreviousR/UppercutPreviousR_000000.fbx", graphicsMode, "UppercutHoldR", 60);
    engine.loadAnimation(irranimatednodeComp.node, "UppercutHoldR", basePath + "UppercutHoldR/UppercutHoldR_000000.fbx", graphicsMode, "UppercutHoldR", 30);
    engine.loadAnimation(irranimatednodeComp.node, "UppercutReleaseR", basePath + "UppercutReleaseR/UppercutReleaseR_000000.fbx", graphicsMode, "Neutral", 60, scale);
    engine.loadAnimation(irranimatednodeComp.node, "UppercutPreviousL", basePath + "UppercutPreviousL/UppercutPreviousL_000000.fbx", graphicsMode, "UppercutHoldL", 60);
    engine.loadAnimation(irranimatednodeComp.node, "UppercutHoldL", basePath + "UppercutHoldL/UppercutHoldL_000000.fbx", graphicsMode, "UppercutHoldL", 30);
    engine.loadAnimation(irranimatednodeComp.node, "UppercutReleaseL", basePath + "UppercutReleaseL/UppercutReleaseL_000000.fbx", graphicsMode, "Neutral", 60, scale);
    end1 = std::chrono::steady_clock::now();
    //std::cout << "Time loading Uppercut animations = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1).count() << "[ns]\n";

    irranimatednodeComp.node.setPosition(position);
    irranimatednodeComp.node.setRotation(rotation);
    irranimatednodeComp.node.setScale(scale);
    //BOUNDING BOX
    bBoxComp.body.pos = position;
    bBoxComp.body.rot = rotation;
    bBoxComp.lf.rot = rotation;
    bBoxComp.rf.rot = rotation;
    bBoxComp.block.rot = rotation;
    directionComp.direction = rotation.Y;
    // Nodes bbox
    bBoxComp.body.node = engine.createBBox();
    bBoxComp.body.node.setPosition(position);
    bBoxComp.body.node.setRotation(rotation);
    bBoxComp.body.node.setScale(TAKO::Vector3f(1, 5.3, 1));

    // Nodes lf
    bBoxComp.lf.node = engine.createBBox();
    bBoxComp.lf.node.setPosition(bBoxComp.lf.pos);
    bBoxComp.lf.node.setRotation(rotation);
    bBoxComp.lf.node.setScale(TAKO::Vector3f(1, 1, 1));

    // Nodes rf
    bBoxComp.rf.node = engine.createBBox();
    bBoxComp.rf.node.setPosition(bBoxComp.rf.pos);
    bBoxComp.rf.node.setRotation(rotation);
    bBoxComp.rf.node.setScale(TAKO::Vector3f(1, 1, 1));

    // Nodes block
    bBoxComp.block.node = engine.createBBox();
    bBoxComp.block.node.setPosition(bBoxComp.block.pos);
    bBoxComp.block.node.setRotation(rotation);
    bBoxComp.block.node.setScale(TAKO::Vector3f(0.75, 1.5, 1));

    // Nodes vision
    bBoxComp.vision.node = engine.createBBox();

    // Area hit debug
    bBoxComp.areaHit = engine.createSphereMesh();
    bBoxComp.areaHit.setVisible(false);
    bBoxComp.areaHit.setPosition(TAKO::Vector3f(position.X, position.Y, position.Z));
    bBoxComp.areaHit.setScale(TAKO::Vector3f(areaHit, areaHit, areaHit));
}
std::size_t EntityManager::createPlayer(Characters character, TAKO::Vector3f position, TAKO::Vector3f scale, TAKO::Vector3f rotation, const int graphicsMode) {
    auto& entity = createEntityBase();
    playerID = entity.id;
    createPlayable(entity.id, character, position, scale, rotation, graphicsMode);
    auto& playerComp = componentManager->addComponent<TagPlayer>(playerID); // COMPONENT_PLAYER
    auto& HUDComp = componentManager->addComponent<HUDComponent>(playerID);
    auto& netComp = componentManager->addComponent<NetComponent>(playerID);

    
    //HUD
    HUDComp.Health_icon = engine.createHUD("media/HUD/planoVida.obj",glm::vec3(-0.62, -0.642, -0.5));
    HUDComp.Health_icon.setScale(Vector3f(HUDComp.MAX_WIDTH_HEALTH,0.041,0));
    engine.changeMaterial(HUDComp.Health_icon,"media/HUD/Bar_vida.png");

    HUDComp.Health_base_icon = engine.createHUD("media/HUD/planoVida.obj",glm::vec3(-0.62, -0.65, 0));
    HUDComp.Health_base_icon.setScale(Vector3f(HUDComp.MAX_WIDTH_HEALTH + 0.0045,0.05,0));
    engine.changeMaterial(HUDComp.Health_base_icon,"media/HUD/hud_salud_base.png");

    HUDComp.Health_symbol_icon = engine.createHUD("media/HUD/planoVida.obj",glm::vec3(-0.61, -0.642, -1));
    HUDComp.Health_symbol_icon.setScale(Vector3f(0.03 * 0.5,0.05 * 0.5,0));
    engine.changeMaterial(HUDComp.Health_symbol_icon,"media/HUD/hud_salud_icono.png");

    HUDComp.Stamina_icon = engine.createHUD("media/HUD/planoVida.obj",glm::vec3(-0.62, -0.745, -0.5));
    HUDComp.Stamina_icon.setScale(Vector3f(HUDComp.MAX_WIDTH_STAMINA,0.027,0));
    engine.changeMaterial(HUDComp.Stamina_icon,"media/HUD/Bar_stamina.png");

    HUDComp.Stamina_base_icon = engine.createHUD("media/HUD/planoVida.obj",glm::vec3(-0.62, -0.752, 0));
    HUDComp.Stamina_base_icon.setScale(Vector3f(HUDComp.MAX_WIDTH_STAMINA + 0.003,0.035,0));
    engine.changeMaterial(HUDComp.Stamina_base_icon,"media/HUD/hud_stamina_base.png");

    HUDComp.Stamina_symbol_icon = engine.createHUD("media/HUD/planoVida.obj",glm::vec3(-0.61, -0.745, -1));
    HUDComp.Stamina_symbol_icon.setScale(Vector3f(0.02 * 0.7,0.035 * 0.7,0));
    engine.changeMaterial(HUDComp.Stamina_symbol_icon,"media/HUD/hud_stamina_icono.png");

    HUDComp.PreviousFist_icon = engine.createHUD("media/Menu/titulo.obj",glm::vec3(-0.9, -0.85, -1));
    HUDComp.PreviousFist_icon.setScale(Vector3f(0.03,0.1,0));
    engine.changeMaterial(HUDComp.PreviousFist_icon,"media/HUD/hud_crochet.png");

    HUDComp.CurrentFist_icon = engine.createHUD("media/Menu/titulo.obj",glm::vec3(-0.8, -0.7, 0));
    HUDComp.CurrentFist_icon.setScale(Vector3f(0.06,0.2,0));
    engine.changeMaterial(HUDComp.CurrentFist_icon,"media/HUD/hud_directo.png");


    HUDComp.Power_up_icon = engine.createHUD("media/Menu/titulo.obj",glm::vec3(0.85,-0.70,-1)); 
    HUDComp.Power_up_icon.setScale(Vector3f(0.04,0.15,0));
    engine.changeMaterial(HUDComp.Power_up_icon,"media/HUD/Pwup_stamina.png");
    HUDComp.Power_up_icon.setVisible(false);
    
    HUDComp.Background_icon = engine.createHUD("media/Menu/titulo.obj",glm::vec3(0.85,-0.70,0));
    HUDComp.Background_icon.setScale(Vector3f(0.06,0.2,0));
    engine.changeMaterial(HUDComp.Background_icon,"media/HUD/Pwup_box.png");
    
    return entity.id;
}

std::size_t EntityManager::createEnemy(Characters character, TAKO::Vector3f position, TAKO::Vector3f scale, TAKO::Vector3f rotation, const int graphicsMode) {
    auto& entity = createEntityBase();
    enemyID = entity.id;
    createPlayable(entity.id, character, position, scale, rotation, graphicsMode); //FIXME Poner el personaje que toque cuando esten las animaciones.

    auto& healthbarComp = componentManager->addComponent<HealthBarComponent>(enemyID);

    //HEALTH
    healthbarComp.Health_bar = engine.createVegetation("media/Menu/titulo.obj");
    healthbarComp.MAX_WIDTH_HEALTH = 10;
    engine.changeMaterial(healthbarComp.Health_bar, "media/HUD/Bar_vida.png");
    healthbarComp.Health_bar.setScale(Vector3f(healthbarComp.MAX_WIDTH_HEALTH,3,0));

    return entity.id;
}

/**
 * createStaticMesh
 *  Creates a new entity with mesh, position and rotation component.
 *  ATTENTION:: BBOXPROPS MESH TAKES WORLD NODE
 */
std::size_t EntityManager::createStaticMesh( std::string texturepath, TAKO::Vector3f position, TAKO::Vector3f rotation, TAKO::Vector3f scale) {
    auto& entity = createEntityBase();
    auto& positionComp = componentManager->addComponent<PositionComponent>(entity.id); // COMPONENT_POSITION 
    auto& rotationComp = componentManager->addComponent<RotationComponent>(entity.id); // COMPONENT_ROTATION
    auto& bBoxPropsComp = componentManager->addComponent<BBoxPropsComponent>(entity.id); // COMPONENT_BBOX_PROPS
    auto& irrbasicnodeComp = componentManager->addComponent<IrrbasicnodeComponent>(entity.id); // COMPONENT_IRRBASICNODE

    positionComp.pos = position;
    rotationComp.rot = rotation;

    // SUMI ENGINE
    irrbasicnodeComp.node = engine.createCubeMesh();
    engine.setMaterialTexture(irrbasicnodeComp.node, texturepath.c_str());
    irrbasicnodeComp.node.setPosition(position);
    irrbasicnodeComp.node.setRotation(rotation);
    irrbasicnodeComp.node.setScale(scale);

    // Nodes bbox
    bBoxPropsComp.body.node = engine.createCubeMesh();
    bBoxPropsComp.body.node.setPosition(position);
    bBoxPropsComp.body.node.setRotation(rotation);
    bBoxPropsComp.body.node.setScale(scale);
    BBoxUtils::calculateBBox(bBoxPropsComp.body, position, rotation.Y, defaultBoxSize);

    

    return entity.id;
}

std::size_t EntityManager::createPiston(TAKO::Vector3f position, TAKO::Vector3f rotation, TAKO::Vector3f scale){
    auto& entity = createEntityBase();
    auto& pistonComp = componentManager->addComponent<PistonComponent>(entity.id); // COMPONENT_PISTON
    auto& rotationComp = componentManager->addComponent<RotationComponent>(entity.id); // COMPONENT_ROTATION
    auto& positionComp = componentManager->addComponent<PositionComponent>(entity.id); // COMPONENT_POSITION
    auto& irrbasicnodeComp = componentManager->addComponent<IrrbasicnodeComponent>(entity.id); // COMPONENT_IRRBASICNODE
    auto& bBoxPropsComp = componentManager->addComponent<BBoxPropsComponent>(entity.id); // COMPONENT_BBOX_PROPS

    positionComp.pos = position;
    rotationComp.rot = rotation;

    pistonComp.activated1 = false;
    pistonComp.activated2 = false;
    pistonComp.down = false;
    pistonComp.up = false;
    pistonComp.timer = 0;

    scale.Y = defaulScalePiston;

    // SUMI ENGINE
    irrbasicnodeComp.node = engine.createCubeMesh();
    irrbasicnodeComp.node.setPosition(position);
    irrbasicnodeComp.node.setRotation(rotation);
    irrbasicnodeComp.node.setScale(scale);
    irrbasicnodeComp.node.setVisible(false);

    // Nodes bbox

    bBoxPropsComp.body.node = engine.createCubeMesh();
    bBoxPropsComp.body.node.setPosition(position);
    bBoxPropsComp.body.node.setRotation(rotation);
    bBoxPropsComp.body.node.setScale(scale);
    bBoxPropsComp.body.node.setVisible(false);
    BBoxUtils::calculateBBox(bBoxPropsComp.body, position, rotation.Y, defaultBoxSize);

    int mult = 2.5; // This is 3 in createLevel1

    // BUILDINGS:
    float multY = mult ;
    float mult2 = mult *30; 

    

    pistonComp.node = engine.createMesh("media/Level2/Other/PaloPiston.obj");
        //std::cout<<i<<std::endl;

    pistonComp.node.setPosition(TAKO::Vector3f(position.X, CollisionUtils::getYComponentsBBox(bBoxPropsComp.body).Y, position.Z));
    pistonComp.node.setScale(TAKO::Vector3f(30*mult, 30*mult, 30*mult));

    return entity.id;
}


std::size_t EntityManager::createStaticCustomMesh(std::string filepath, TAKO::Vector3f position, TAKO::Vector3f rotation, TAKO::Vector3f scale, TAKO::Vector3f scaleBBox, TAKO::Vector3f positionBBox,  TAKO::Vector3f rotationBBox, bool bbox) {

    auto& entity = createEntityBase();

    auto& positionComp = componentManager->addComponent<PositionComponent>(entity.id); // COMPONENT_POSITION 
    auto& rotationComp = componentManager->addComponent<RotationComponent>(entity.id); // COMPONENT_ROTATION

    auto& irrbasicnodeComp = componentManager->addComponent<IrrbasicnodeComponent>(entity.id); // COMPONENT_IRRBASICNODE

    positionComp.pos = positionBBox;
    rotationComp.rot = rotationBBox;

    // SUMI ENGINE
    irrbasicnodeComp.node = engine.createMesh(filepath.c_str());
    //engine.setMaterialTexture(irrbasicnodeComp.node, texturepath.c_str());
    irrbasicnodeComp.node.setPosition(position);
    irrbasicnodeComp.node.setRotation(rotation);
    irrbasicnodeComp.node.setScale(scale);

    // Nodes bbox
    if(bbox){
        auto& bBoxPropsComp = componentManager->addComponent<BBoxPropsComponent>(entity.id); // COMPONENT_BBOX_PROPS
        bBoxPropsComp.body.node = engine.createBBox();
        bBoxPropsComp.body.node.setPosition(positionBBox);
        bBoxPropsComp.body.node.setRotation(rotationBBox);
        bBoxPropsComp.body.node.setScale(scaleBBox);
        BBoxUtils::calculateBBox(bBoxPropsComp.body, positionBBox, rotationBBox.Y, defaultBoxSize);
    }

    return entity.id;
}

std::size_t EntityManager::createStaticCustomMeshNoBBox(std::string filepath,TAKO::Vector3f position, TAKO::Vector3f rotation, TAKO::Vector3f scale) {

    auto& entity = createEntityBase();
    auto& positionComp = componentManager->addComponent<PositionComponent>(entity.id); // COMPONENT_POSITION 
    auto& rotationComp = componentManager->addComponent<RotationComponent>(entity.id); // COMPONENT_ROTATION
    auto& irrbasicnodeComp = componentManager->addComponent<IrrbasicnodeComponent>(entity.id); // COMPONENT_IRRBASICNODE

    positionComp.pos = position;
    rotationComp.rot = rotation;

    // SUMI ENGINE
    irrbasicnodeComp.node = engine.createMesh(filepath.c_str());
    irrbasicnodeComp.node.setPosition(position);
    irrbasicnodeComp.node.setRotation(rotation);
    irrbasicnodeComp.node.setScale(scale);

    return entity.id;
}


// Create Conveyor Belt
// Creates a new Conveyor Belt with position component
// Axis:
//  X = true
//  Z = false
// 
// Sense
//  Positive = true
//  Negative = false
std::size_t EntityManager::createConveyorBelt(TAKO::Vector3f position, TAKO::Vector3f scale, bool axis, bool sense){

    auto& entity = createEntityBase();
    auto& positionComp = componentManager->addComponent<PositionComponent>(entity.id); // COMPONENT_POSITION 
    auto& convBeltComp = componentManager->addComponent<ConveyorBeltComponent>(entity.id); // COMPONENT_CONVEYOR_BELT 

    float rotation = 0;

    float mult = 2.5;
    float mult2 = mult *30;

    positionComp.pos = position;

    convBeltComp.sense = sense;
    convBeltComp.axis = axis;

    //if(axis) rotation = 90;


    // Nodes bbox
    convBeltComp.bbox.node = engine.createCubeMesh();
    convBeltComp.bbox.node.setPosition(position);
    convBeltComp.bbox.node.setRotation(TAKO::Vector3f(0, rotation, 0));
    convBeltComp.bbox.node.setScale(scale);
    convBeltComp.bbox.node.setVisible(false);

    BBoxUtils::calculateBBox(convBeltComp.bbox, position, rotation, defaultBoxSize);

    float distance = 0.475 * -mult2;

    int nodecont = 22;

    if(sense){
        TAKO::Vector3f posInit = TAKO::Vector3f(-mult2 *-0.021, mult2 *0.044, -mult2 *-7.986);
        for (size_t i = 0; i < nodecont; i++)
        {
            convBeltComp.nodes.push_back(engine.createMesh("media/Level2/Assets/CintaTransportadora.obj"));
            convBeltComp.nodes[i].setPosition(TAKO::Vector3f(posInit.X, posInit.Y, posInit.Z + distance*i));
            convBeltComp.nodes[i].setScale(TAKO::Vector3f(20*mult, 30*mult, 32*mult));
        }
        
    }
    else{
        TAKO::Vector3f posInit = TAKO::Vector3f(-mult2 *1.35, mult2 *0.044, -mult2 *2.218);
        for (size_t i = 0; i < nodecont; i++)
        {
            convBeltComp.nodes.push_back(engine.createMesh("media/Level2/Assets/CintaTransportadora.obj"));
            convBeltComp.nodes[i].setPosition(TAKO::Vector3f(posInit.X, posInit.Y, posInit.Z - distance*i));
            convBeltComp.nodes[i].setScale(TAKO::Vector3f(20*mult, 30*mult, 32*mult));  
            convBeltComp.nodes[i].setRotation(TAKO::Vector3f(0, 180, 0));      
        }  
        
    }


    return entity.id;
}

/**
 * createSlope
 *  Creates a new slpe with mesh, position and rotation component.
 *  Axis:
 *    X : TRUE
 *    Z : FALSE
 * 
 *  positiveSense
 *    +1 : TRUE
 *    -1 : FALSE
 * filepath
 *  ATTENTION:: CREATESLOPE MESH TAKES WORLD NODE
 */
std::size_t EntityManager::createSlope(std::string filepath, TAKO::Vector3f position, TAKO::Vector3f rotation, TAKO::Vector3f scale, bool axis, bool positiveSense) {
    auto& entity = createEntityBase();
    auto& positionComp = componentManager->addComponent<PositionComponent>(entity.id); // COMPONENT_POSITION 
    auto& rotationComp = componentManager->addComponent<RotationComponent>(entity.id); // COMPONENT_ROTATION
    auto& irrbasicnodeComp = componentManager->addComponent<IrrbasicnodeComponent>(entity.id); // COMPONENT_IRRBASICNODE
    auto& slopeComp = componentManager->addComponent<SlopeComponent>(entity.id); // COMPONENT_SLOPE

    positionComp.pos = position;
    rotationComp.rot = rotation;

    // SUMI ENGINE
    irrbasicnodeComp.node = engine.createMesh(filepath.c_str());
    irrbasicnodeComp.node.setPosition(position);
    irrbasicnodeComp.node.setRotation(rotation);
    irrbasicnodeComp.node.setScale(scale);
    irrbasicnodeComp.node.setVisible(false);
   

    // Nodes bbox
    slopeComp.body.node = engine.createCubeMesh();
    slopeComp.body.node.setPosition(position);
    slopeComp.body.node.setRotation(rotation);
    slopeComp.body.node.setScale(scale);
    slopeComp.body.node.setVisible(false);

    // direction and sense
    slopeComp.axis = axis;
    slopeComp.positiveSense = positiveSense;

    return entity.id;
}


std::size_t EntityManager::createSaw(TAKO::Vector3f position, TAKO::Vector3f scale, bool sense, int num){

    auto& entity = createEntityBase();
    auto& positionComp = componentManager->addComponent<PositionComponent>(entity.id); // COMPONENT_POSITION 
    auto& sawComp = componentManager->addComponent<SawComponent>(entity.id); // COMPONENT_CONVEYOR_BELT 
    
    int mult = 2.5;
  
    for (unsigned i = 0; i < 4; i++)
    {
        unsigned j = i + 4*num;
        sawComp.nodes.push_back(engine.createMesh("media/Level2/Assets/saw.obj"));
        //std::cout<<i<<std::endl;

        sawComp.nodes[i].setPosition(TAKO::Vector3f(sawPositions[j].X, sawPositions[j].Y, sawPositions[j].Z));
        sawComp.nodes[i].setScale(TAKO::Vector3f(30*mult, 30*mult, 30*mult));
    
    }

    float rotation = 0;

    positionComp.pos = position;

    sawComp.sense = sense;

    //if(axis) rotation = 90;


    // Nodes bbox
    sawComp.bbox.node = engine.createCubeMesh();
    sawComp.bbox.node.setPosition(position);
    sawComp.bbox.node.setRotation(TAKO::Vector3f(0, rotation, 0));
    sawComp.bbox.node.setScale(scale);
    sawComp.bbox.node.setVisible(false);

    BBoxUtils::calculateBBox(sawComp.bbox, position, rotation, defaultBoxSize);


    return entity.id;
}

std::size_t EntityManager::getPlayerID() {
    return playerID;
}

std::size_t EntityManager::getEnemyID() {
    return enemyID;
}
} // namespace TAKO
