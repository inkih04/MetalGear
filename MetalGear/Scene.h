#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include <map>


// Scene contains all the entities of our game.
// It is responsible for updating and render them.
class Player;

class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void reloadMap10();

private:
	void initShaders();
	void createMaps();
	void checkMapChange();
	void checkEnemies(int deltaTime);
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
	map<int, TileMap*>maps;
	int currentMapId;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

