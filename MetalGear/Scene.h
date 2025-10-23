#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "HUD.h"
#include "MessageDisplay.h"

class Scene
{
public:
    Scene();
    ~Scene();

    void init();
    void update(int deltaTime);
    void render();
    void reloadMap10();
	TileMap* getCurrentMap() const { return maps.at(currentMapId); }
    void showItemMessage(const std::string& itemImage) {
        messageDisplay.showMessage(itemImage, 1000); // 2 segundos
    }

private:
    void initShaders();
    void createMaps();
    void checkMapChange();
    void checkEnemies(int deltaTime);

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
};

#endif // _SCENE_INCLUDE