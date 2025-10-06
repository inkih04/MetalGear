#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


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
	currentMapId = 1;
	maps[1] = TileMap::createTileMap("levels/mapa1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	maps[2] = TileMap::createTileMap("levels/mapa2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 2);
	maps[3] = TileMap::createTileMap("levels/mapa3.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 3);
	maps[4] = TileMap::createTileMap("levels/mapa4.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 4);
	maps[5] = TileMap::createTileMap("levels/mapa5.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 5);
	maps[6] = TileMap::createTileMap("levels/mapa6.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 6);
	maps[7] = TileMap::createTileMap("levels/mapa7.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 7);
	maps[8] = TileMap::createTileMap("levels/mapa8.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 8);
	maps[9] = TileMap::createTileMap("levels/mapa9.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 9);
	maps[10] = TileMap::createTileMap("levels/mapa10-puerta.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 10);
	maps[11] = TileMap::createTileMap("levels/mapa11.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 11);
	maps[12] = TileMap::createTileMap("levels/mapa12.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 12);
	maps[13] = TileMap::createTileMap("levels/mapa13.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 13);
	maps[14] = TileMap::createTileMap("levels/mapa14.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 14);
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