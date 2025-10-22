#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "ChangeMap.h"
#include "MeleEnemy.h"
#include "RangeEnemy.h"
#include "Guard.h"
#include "Gun.h"
#include "CaveEnemy.h"
#include "MedPack.h"
#include "Ammunition.h"
#include "Key.h"
#include "Player.h"
#include "HUD.h"


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
	maps[1] = loadMap1();
	maps[2] = loadMap2();
	maps[3] = loadMap3();
	maps[4] = loadMap4();
	maps[5] = loadMap5();
	maps[6] = loadMap6();
	maps[7] = loadMap7();
	maps[8] = loadMap8();
	maps[9] = loadMap9();
	maps[10] = loadMap10();
	maps[11] = loadMap11();
	maps[12] = loadMap12();
	maps[13] = loadMap13();
	maps[14] = loadMap14();
}

void Scene::reloadMap10() {
	float mapHeightPixels = 10 * 16;
	float mapWidthPixels = 15 * 16;
	maps[10] = TileMap::createTileMap("levels/mapa10-nopuerta.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 10,
		{ ChangeMap({274,213,342,343},9, glm::ivec2(mapWidthPixels * 0.75 - 8, mapHeightPixels * 0.35f)) }, { 11, 12, 14, 0 });
}

TileMap* Scene::loadMap1()
{
	TileMap* map = TileMap::createTileMap("levels/mapa1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 1, {}, { 0, 2, 0, 0 });
	//map->addEnemy(new RangeEnemy(glm::ivec2(120, 80), texProgram, map, {}, Guard(), DOWN, player));
	map->addItem(new MedPack(glm::ivec2(48, 48), texProgram));
	//map->addItem(new Ammunition(glm::ivec2(64, 80), texProgram));
	return map;
}

TileMap* Scene::loadMap2()
{
	TileMap* map = TileMap::createTileMap("levels/mapa2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 2, {}, { 1, 0, 0, 3 });
	map->addEnemy(new MeleEnemy(glm::ivec2(64, 4), texProgram, map, {}, Guard({ RIGHT, DOWN }, 1250), RIGHT, player));
	map->addEnemy(new MeleEnemy(glm::ivec2(182, 48), texProgram, map, {}, Guard({ LEFT, UP }, 1250), LEFT, player));
	map->addItem(new Ammunition(glm::ivec2(32, 128), texProgram));
	return map;
}

TileMap* Scene::loadMap3()
{
	TileMap* map = TileMap::createTileMap("levels/mapa3.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 3, {}, { 0, 0, 2, 4 });
	map->addEnemy(new MeleEnemy(glm::ivec2(120, 64), texProgram, map, { 24, 24 }, Guard(), DOWN, player));
	map->addItem(new MedPack(glm::ivec2(210, 48), texProgram)); //Assault Vest
	map->addItem(new Ammunition(glm::ivec2(98, 108), texProgram));
	return map;
}

TileMap* Scene::loadMap4()
{
	TileMap* map = TileMap::createTileMap("levels/mapa4.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 4, {}, { 5, 6, 3, 0 });
	map->addItem(new MedPack(glm::ivec2(194, 32), texProgram));
	map->addEnemy(new RangeEnemy(glm::ivec2(124, 46), texProgram, map, {32, 32}, Guard(), DOWN, player));
	return map;
}

TileMap* Scene::loadMap5()
{
	TileMap* map = TileMap::createTileMap("levels/mapa5.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 5, {}, { 0, 4, 0, 0 });
	map->addEnemy(new MeleEnemy(glm::ivec2(152, 44), texProgram, map, {}, Guard({ DOWN, LEFT}, 1250), DOWN, player));
	map->addEnemy(new MeleEnemy(glm::ivec2(174, 100), texProgram, map, {}, Guard({ UP, RIGHT }, 1250), UP, player));
	map->addItem(new Gun(glm::ivec2(80, 80), texProgram));
	map->addEnemy(new RangeEnemy(glm::ivec2(40, 64), texProgram, map, {}, Guard(), RIGHT, player));
	return map;
}

TileMap* Scene::loadMap6()
{
	float mapHeightPixels = 10 * 16;
	TileMap* map = TileMap::createTileMap("levels/mapa6.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 6,
		{ ChangeMap({100,70},7, glm::ivec2(-1.f, mapHeightPixels - 50.f)) }, { 4, 0, 0, 0 });

	map->addItem(new Ammunition(glm::ivec2(160, 50), texProgram));
	map->addEnemy(new CaveEnemy(glm::ivec2(192, 40), texProgram, map, {}, Guard(), DOWN, player));
	map->addEnemy(new MeleEnemy(glm::ivec2(206, 80), texProgram, map, {}, Guard(), LEFT, player));
	map->addItem(new MedPack(glm::ivec2(194, 126), texProgram));
	return map;
}

TileMap* Scene::loadMap7()
{
	float mapHeightPixels = 10 * 16;
	TileMap* map = TileMap::createTileMap("levels/mapa7.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 7,
		{ ChangeMap({19,18,20},6, glm::ivec2(-1.f, 50.f)),
		  ChangeMap({112},8, glm::ivec2(25.f, mapHeightPixels - 50.f)) }, {});

	map->addItem(new Ammunition(glm::ivec2(50, 48), texProgram));
	map->addEnemy(new CaveEnemy(glm::ivec2(162, 8), texProgram, map, {}, Guard(), DOWN, player));
	map->addEnemy(new MeleEnemy(glm::ivec2(56, 74), texProgram, map, {}, Guard({ RIGHT, DOWN }, 1250), RIGHT, player));
	map->addEnemy(new MeleEnemy(glm::ivec2(20, 124), texProgram, map, {}, Guard(), RIGHT, player));
	map->addItem(new MedPack(glm::ivec2(16, 16), texProgram));
	return map;
}

TileMap* Scene::loadMap8()
{
	float mapHeightPixels = 10 * 16;
	float mapWidthPixels = 15 * 16;
	TileMap* map = TileMap::createTileMap("levels/mapa8.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 8,
		{ ChangeMap({172},7, glm::ivec2(mapWidthPixels - 30, 20)),
		  ChangeMap({19,18,20},9, glm::ivec2(30, mapHeightPixels - 50)) }, {});

	map->addItem(new Ammunition(glm::ivec2(17, 24), texProgram));
	map->addEnemy(new CaveEnemy(glm::ivec2(143, 60), texProgram, map, {}, Guard({ RIGHT, UP, LEFT }, 1250), RIGHT, player));
	map->addItem(new MedPack(glm::ivec2(191, 12), texProgram));
	return map;
}

TileMap* Scene::loadMap9()
{
	float mapHeightPixels = 10 * 16;
	float mapWidthPixels = 15 * 16;
	TileMap* map = TileMap::createTileMap("levels/mapa9.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 9,
		{ ChangeMap({163,164,162},8, glm::ivec2(mapWidthPixels - 55, 40)),
		  ChangeMap({296,326},10, glm::ivec2(mapWidthPixels / 2.f, mapHeightPixels - 50)) }, {});

	map->addEnemy(new MeleEnemy(glm::ivec2(85, 70), texProgram, map, { 24, 24 }, Guard(), UP, player));
	return map;
}

TileMap* Scene::loadMap10()
{
	float mapHeightPixels = 10 * 16;
	float mapWidthPixels = 15 * 16;
	TileMap* map = TileMap::createTileMap("levels/mapa10-puerta.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 10,
		{ ChangeMap({274,213,342,343},9, glm::ivec2(mapWidthPixels * 0.75 - 8, mapHeightPixels * 0.35f)) }, { 11, 12, 0, 0 });
	map->addEnemy(new RangeEnemy(glm::ivec2(110, 60), texProgram, map, {}, Guard(), DOWN, player));
	return map;
}

TileMap* Scene::loadMap11()
{
	TileMap* map = TileMap::createTileMap("levels/mapa11.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 11, {}, { 0, 10, 0, 0 });
	map->addItem(new MedPack(glm::ivec2(194, 28), texProgram));
	map->addEnemy(new CaveEnemy(glm::ivec2(16, 42), texProgram, map, {}, Guard(), LEFT, player));
	map->addItem(new MedPack(glm::ivec2(48, 22), texProgram));
	return map;
}

TileMap* Scene::loadMap12()
{
	TileMap* map = TileMap::createTileMap("levels/mapa12.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 12, {}, { 10, 0, 13, 0 });
	map->addEnemy(new MeleEnemy(glm::ivec2(200, 95), texProgram, map, {}, Guard(), LEFT, player));
	return map;
}

TileMap* Scene::loadMap13()
{
	TileMap* map = TileMap::createTileMap("levels/mapa13.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 13, {}, { 0, 0, 0, 12 });
	map->addItem(new Key(glm::ivec2(32,42), texProgram));
	map->addItem(new Ammunition(glm::ivec2(210, 42), texProgram));
	map->addItem(new MedPack(glm::ivec2(16, 124), texProgram));
	return map;
}

TileMap* Scene::loadMap14()
{
	TileMap* map = TileMap::createTileMap("levels/mapa14.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 14, {}, {0,0,0,10});
	return map;
}


void Scene::init()
{
	initShaders();

	player = new Player();
	createMaps();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, this);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * maps[currentMapId]->getTileSize(), INIT_PLAYER_Y_TILES * maps[currentMapId]->getTileSize()));
	player->setTileMap(maps[currentMapId]);

	float mapWidthPixels = maps[currentMapId]->getMapSize().x * maps[currentMapId]->getTileSize();
	float mapHeightPixels = maps[currentMapId]->getMapSize().y * maps[currentMapId]->getTileSize();

	projection = glm::ortho(0.f, mapWidthPixels, mapHeightPixels, 0.f);
	currentTime = 0.0f;

	// Inicializar el HUD
	hud.init(texProgram);
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	checkMapChange();
	checkEnemies(deltaTime);
}

void Scene::checkEnemies(int deltaTime)
{
	player->checkEnemies(deltaTime);
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

	// Renderizar el mapa y el jugador
	maps[currentMapId]->render();
	player->render();

	// Configurar proyección fija para el HUD (siempre 240x160 sin importar el tamaño del mapa)
	float mapWidthPixels = maps[currentMapId]->getMapSize().x * maps[currentMapId]->getTileSize();
	float mapHeightPixels = maps[currentMapId]->getMapSize().y * maps[currentMapId]->getTileSize();
	glm::mat4 hudProjection = glm::ortho(0.f, mapWidthPixels, mapHeightPixels, 0.f);

	texProgram.setUniformMatrix4f("projection", hudProjection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	// Renderizar el HUD encima de todo
	hud.render(player->getHealth(), player);

	// Restaurar la proyección original si es necesario
	texProgram.setUniformMatrix4f("projection", projection);
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