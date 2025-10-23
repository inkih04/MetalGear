#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "HUD.h"
#include "MessageDisplay.h"
#include "GameOverScreen.h"

class Scene
{
public:
    Scene();
    ~Scene();

    void init();
    void update(int deltaTime);
    void render();
    void reloadMap10();
    void resetGame(); // Nueva función para reiniciar el juego

    TileMap* getCurrentMap() const { return maps.at(currentMapId); }

    void showItemMessage(const std::string& itemImage) {
        messageDisplay.showMessage(itemImage, 1000);
    }

    bool isGameOver() const { return gameOver; }
    int handleMouseClick(int mouseX, int mouseY); // Para manejar clics en game over - retorna 1=continue, 2=exit, 0=nada

private:
    void initShaders();
    void createMaps();
    void checkMapChange();
    void checkEnemies(int deltaTime);
    void checkGameOver(); // Nueva función para verificar game over

    // Map loading functions
    TileMap* loadMap1();
    TileMap* loadMap2();
    TileMap* loadMap3();
    TileMap* loadMap4();
    TileMap* loadMap5();
    TileMap* loadMap6();
    TileMap* loadMap7();
    TileMap* loadMap8();
    TileMap* loadMap9();
    TileMap* loadMap10();
    TileMap* loadMap11();
    TileMap* loadMap12();
    TileMap* loadMap13();
    TileMap* loadMap14();

private:
    map<int, TileMap*> maps;
    int currentMapId;
    Player* player;
    ShaderProgram texProgram;
    float currentTime;
    glm::mat4 projection;
    HUD hud;
    MessageDisplay messageDisplay;
    GameOverScreen gameOverScreen;
    bool gameOver;
};

#endif // _SCENE_INCLUDE