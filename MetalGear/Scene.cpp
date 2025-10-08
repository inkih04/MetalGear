#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "ChangeMap.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 5 
#define INIT_PLAYER_Y_TILES 4 

Scene::Scene()
{
	currentMapId = 1;
	player = NULL;
}

Scene::~Scene()
{

	if (player != NULL)
		delete player;
}

void Scene::createMaps()
{
	float mapHeightPixels = 10 * 16;
	float mapWidthPixels = 15 * 16;

																											//LEFT RIGHT TOP BOTTOM  
	currentMapId = 1;
	maps[1] = TileMap::createTileMap("levels/mapa1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 1, {}, { 0, 2, 0, 0 });
	maps[2] = TileMap::createTileMap("levels/mapa2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 2, {}, { 1, 0, 0, 3 });
	maps[3] = TileMap::createTileMap("levels/mapa3.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 3, {}, { 0, 0, 2, 4 });
	maps[4] = TileMap::createTileMap("levels/mapa4.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 4, {}, { 5, 6, 3, 0 });
	maps[5] = TileMap::createTileMap("levels/mapa5.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 5, {}, { 0, 4, 0, 0 });

																												//idTile, idNewMap, newPosition. -1.f means keep current position
	maps[6] = TileMap::createTileMap("levels/mapa6.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 6, {ChangeMap({100,70},7, glm::ivec2(-1.f, mapHeightPixels - 50.f)) }, { 4, 0, 0, 0 });

	maps[7] = TileMap::createTileMap("levels/mapa7.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 7, {ChangeMap({19,18,20},6, glm::ivec2(-1.f, 50.f)),
		ChangeMap({112},8, glm::ivec2(25.f, mapHeightPixels- 50.f)) }, {});

	maps[8] = TileMap::createTileMap("levels/mapa8.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 8, {ChangeMap({172},7, glm::ivec2(mapWidthPixels - 30, 20)),
		ChangeMap({19,18,20},9, glm::ivec2(30, mapHeightPixels - 50)) }, {});

	maps[9] = TileMap::createTileMap("levels/mapa9.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 9, { ChangeMap({163, 164, 162}, 8, glm::ivec2(mapWidthPixels - 55, 40)),
			ChangeMap({296, 326}, 10, glm::ivec2(mapWidthPixels/2.f, mapHeightPixels - 50))}, {});

	maps[10] = TileMap::createTileMap("levels/mapa10-puerta.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 10, { ChangeMap({274,213},9, glm::ivec2(mapWidthPixels*0.75 -8, mapHeightPixels*0.35f)) }, {11, 12, 0, 0});
	maps[11] = TileMap::createTileMap("levels/mapa11.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 11, {}, { 0, 10, 0, 0 });
	maps[12] = TileMap::createTileMap("levels/mapa12.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 12, {}, { 10, 0, 13, 0 });
	maps[13] = TileMap::createTileMap("levels/mapa13.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 13, {}, { 0, 0, 0, 12});
	maps[14] = TileMap::createTileMap("levels/mapa14.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 14, {}, {});
}


void Scene::init()
{
	initShaders();
	createMaps();

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * maps[currentMapId]->getTileSize(), INIT_PLAYER_Y_TILES * maps[currentMapId]->getTileSize()));
	player->setTileMap(maps[currentMapId]);

	float mapWidthPixels = maps[currentMapId]->getMapSize().x * maps[currentMapId]->getTileSize();
	float mapHeightPixels = maps[currentMapId]->getMapSize().y * maps[currentMapId]->getTileSize();

	projection = glm::ortho(0.f, mapWidthPixels, mapHeightPixels, 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	checkMapChange();
}

void Scene::checkMapChange()
{
	glm::ivec2 newPos;
	int mapId = player->checkMap(newPos);
	if (mapId != currentMapId) {
		currentMapId = mapId;
		player->setTileMap(maps[currentMapId]);
		player->setPosition(glm::vec2(float(newPos.x), float(newPos.y)));
	}
}

void Scene::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	maps[currentMapId]->render();
	player->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;
	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}