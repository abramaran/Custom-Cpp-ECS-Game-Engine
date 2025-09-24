#pragma once

#include <string>
#include <Entity.h>
#include <GameStorage.h>
#include <ComponentManager.h>
#include <Vector3f.h>
#include <SUMIEngine.h>
#include <GameEnums.h>
#include <systems/BBoxUtils.h>
#include <systems/CollisionUtils.h>

struct Device;
struct SceneManager;

namespace TAKO {
    
struct EntityManager {
    explicit EntityManager(SUMI::SUMIEngine& en, GameStorage* gs, ComponentManager* cm);

    std::size_t createEntity();
    void destroyEntity(std::size_t entityID);
    void destroyAllEntities();

    // Crear otros constructores para tipos concretos de objeto.
    void createPlayable(std::size_t ID, Characters character, TAKO::Vector3f position, TAKO::Vector3f scale, TAKO::Vector3f rotation, const int graphicsMode);
    void generatePowerUp(int numofboxes, std::vector<std::pair<bool,TAKO::Vector3f>>& positions);

    std::size_t createPlayer(Characters character,TAKO::Vector3f position, TAKO::Vector3f scale, TAKO::Vector3f rotation, const int graphicsMode);
    std::size_t createEnemy(Characters character, TAKO::Vector3f position, TAKO::Vector3f scale, TAKO::Vector3f rotation, const int graphicsMode);

    std::size_t createCamera(TAKO::Vector3f position, TAKO::Vector3f lookat);
    std::size_t createPowerUpBox(std::string texturepath, std::string iconpath, TAKO::Vector3f position, int generatedPosition, TAKO::Vector3f scale, PowerUpEnum powerUp, float cooldown);
    std::size_t createPowerUp(std::string filepath, std::string iconpath, TAKO::Vector3f position, int generatedPosition, TAKO::Vector3f scale, PowerUpEnum powerUp, float cooldown);
    std::size_t createSlope(std::string filepath, TAKO::Vector3f position, TAKO::Vector3f rotation, TAKO::Vector3f scale, bool axis, bool positiveSense);

    std::size_t createPiston(TAKO::Vector3f position, TAKO::Vector3f rotation, TAKO::Vector3f scale);
    std::size_t createStaticMesh(std::string texturepath, TAKO::Vector3f position, TAKO::Vector3f rotation, TAKO::Vector3f scale);
    std::size_t createStaticCustomMesh(std::string filepath, TAKO::Vector3f position, TAKO::Vector3f rotation, TAKO::Vector3f scale, TAKO::Vector3f scaleBBox, TAKO::Vector3f positionBBox, TAKO::Vector3f rotationBBox, bool bbox);
    std::size_t createStaticCustomMeshNoBBox(std::string filepath, TAKO::Vector3f position, TAKO::Vector3f rotation, TAKO::Vector3f scale);
    std::size_t createResizableBillboard(Vector3f position, Vector3f scale, std::string filepath);
    std::size_t createSkyBox(Vector3f scale);

    std::size_t createLevel(Levels currentLevel, Characters currentCharacter, bool isonline, Characters enemyCharacter, const int graphicsMode);
    void createLevel1();
    void createLevel2();
    void createTrainComponent();
    void generatePowerUp(int numofboxes, std::vector<std::pair<bool,TAKO::Vector3f>>& positions, bool online);
    void generatePowerUpOnline(int type, int vectorpos, std::vector<std::pair<bool,TAKO::Vector3f>>& positions);

    std::size_t createBuscarSala();
    std::size_t createCrearSala();
    void createOpcionesSala();
    void createInitialMenu();
    void createMenu();
    void createSelectNivel();
    void createSelectNivelMulti();
    void createWaitNivel();
    void createSelectChara();
    void createOptions();
    void createCredits();
    void createControls(std::string texturepath);
    void createPause();
    void createLoseSingle();
    void createWinSingle();
    void createWinSingleEnd();
    void createLoseMulti();
    void createWinMulti();
    void createComicGame();
    void createCreditVideo();
    void createLogo();
    void createComicMenu();
    std::size_t createLoadScreen();


    std::size_t createCharacterPortrait(Vector3f position, Vector3f scale, std::string texturePath, bool isplayer);
    std::size_t createBackGround(std::string texturePath);
    std::size_t createRoomNumber(Vector3f position, Vector3f scale, std::string texturePath, int index);
    void createButton(std::size_t& id, Vector3f& position, Vector3f& scale, std::string& texturePath, bool selected);
    std::size_t createLevelButton(Vector3f position, Vector3f scale, std::string texturePath, Levels level, bool selected);
    std::size_t createStateButton(Vector3f position, Vector3f scale,std::string texturePath, StateEnum state);
    std::size_t createStatelessButton(Vector3f position, Vector3f scale,std::string texturePath);
    std::size_t createCharacterButton(Vector3f position, Vector3f scale, std::string texturePath, Characters character, std::string characterpicture, bool selected);
    std::size_t createConveyorBelt(Vector3f position, Vector3f scale, bool axis, bool sense);
    std::size_t createSaw(Vector3f position, Vector3f scale, bool sense, int num);
    std::size_t CreateLevelDecision();

    std::size_t getPlayerID();
    std::size_t getEnemyID();

    SUMI::SUMIEngine& engine;
    private:

        Entity& createEntityBase(); // Private so as to not mantain pointers to entities.

        GameStorage* gameStorage;
        ComponentManager* componentManager;

        int playerID{-1};
        int enemyID{-1};

        const float defaulScalePiston = 4;


        int multS = 2.5;
        const int mult2S = multS * 30;

        const TAKO::Vector3f sawPositions[16]{
                TAKO::Vector3f(-mult2S *1.715, mult2S *0.743, -mult2S *-7.328),
                TAKO::Vector3f(-mult2S *1.659, mult2S *0.560, -mult2S *-7.328),
                TAKO::Vector3f(-mult2S *1.715, mult2S *0.363, -mult2S *-7.328),
                TAKO::Vector3f(-mult2S *1.659, mult2S *0.182, -mult2S *-7.328),
                TAKO::Vector3f(-mult2S *-0.009, mult2S *0.743, -mult2S *-7.328),
                TAKO::Vector3f(-mult2S *-0.066, mult2S *0.560, -mult2S *-7.328),
                TAKO::Vector3f(-mult2S *-0.009, mult2S *0.363, -mult2S *-7.328),
                TAKO::Vector3f(-mult2S *-0.066, mult2S *0.182, -mult2S *-7.328),
                TAKO::Vector3f(-mult2S *1.659, mult2S *0.560, -mult2S *1.814),
                TAKO::Vector3f(-mult2S *1.710, mult2S *0.741, -mult2S *1.846),
                TAKO::Vector3f(-mult2S *1.659, mult2S *0.194, -mult2S *1.814),
                TAKO::Vector3f(-mult2S *1.710, mult2S *0.378, -mult2S *1.846),
                TAKO::Vector3f(-mult2S *0.000, mult2S *0.560, -mult2S *1.814),
                TAKO::Vector3f(-mult2S *0.014, mult2S *0.741, -mult2S *1.846),
                TAKO::Vector3f(-mult2S *-0.037, mult2S *0.194, -mult2S *1.814),
                TAKO::Vector3f(-mult2S *0.014, mult2S *0.378, -mult2S *1.846),
        };

        
        //static unsigned int STAMINA = 100;
};
} // namespace TAKO