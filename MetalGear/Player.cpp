#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_DOWN, STAND_UP, STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, PUNCH_LEFT, PUNCH_RIGHT, PUNCH_UP, PUNCH_DOWN
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/metal.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(13.6, 27.2), glm::vec2(0.0556f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(12);

		sprite->setAnimationSpeed(STAND_DOWN, 6);
		sprite->addKeyframe(STAND_DOWN, glm::vec2(0.0556f * 0, 0.f));

		sprite->setAnimationSpeed(PUNCH_UP, 2);
		sprite->addKeyframe(PUNCH_UP, glm::vec2(0.0556f * 17, 0.f));
		sprite->addKeyframe(STAND_UP, glm::vec2(0.0556f, 0.f));

		sprite->setAnimationSpeed(PUNCH_DOWN, 2);
		sprite->addKeyframe(PUNCH_DOWN, glm::vec2(0.0556f * 16, 0.f));
		sprite->addKeyframe(PUNCH_DOWN, glm::vec2(0.0556f * 0, 0.f));

		sprite->setAnimationSpeed(PUNCH_LEFT, 2);
		sprite->addKeyframe(PUNCH_LEFT, glm::vec2(0.0556f * 16, 0.5f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0556f * 0, 0.5f));

		sprite->setAnimationSpeed(PUNCH_RIGHT, 2);
		sprite->addKeyframe(PUNCH_RIGHT, glm::vec2(0.0556f * 17, 0.5f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0556f, 0.5f));

	
		sprite->setAnimationSpeed(STAND_LEFT, 6);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0556f*0, 0.5f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 6);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0556f, 0.5f));

		sprite->setAnimationSpeed(STAND_UP, 6);
		sprite->addKeyframe(STAND_UP, glm::vec2(0.0556f, 0.f));

		sprite->setAnimationSpeed(MOVE_DOWN, 6);
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.0556 * 0.f, 0.0f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.0556 * 2.f, 0.0f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.0556 * 4.f, 0.0f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.0556 * 6.f, 0.0f));

		sprite->setAnimationSpeed(MOVE_UP, 6);
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.0556 * 1.f, 0.0f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.0556 * 3.f, 0.0f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.0556 * 5.f, 0.0f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.0556 * 7.f, 0.0f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 6);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0556 * 0.f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0556 * 2.f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0556 * 4.f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0556 * 6.f, 0.5f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 6);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0556 * 1.f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0556 * 3.f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0556 * 5.f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0556 * 7.f, 0.5f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getKey(GLFW_KEY_LEFT) || Game::instance().getKey(GLFW_KEY_A))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if (map->checkTileCollision(posPlayer, glm::ivec2(13.6, 27.2)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}

	}
	else if(Game::instance().getKey(GLFW_KEY_RIGHT) || Game::instance().getKey(GLFW_KEY_D))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);

		posPlayer.x += 2;
		
		if (map->checkTileCollision(posPlayer, glm::ivec2(13.6, 27.2)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}

	}
	else if (Game::instance().getKey(GLFW_KEY_UP) || Game::instance().getKey(GLFW_KEY_W)) 
	{
		if (sprite->animation() != MOVE_UP)
			sprite->changeAnimation(MOVE_UP);
		posPlayer.y -= 2;

		if (map->checkTileCollision(posPlayer, glm::ivec2(13.6, 27.2)))
		{
			posPlayer.y += 2;
			sprite->changeAnimation(STAND_UP);
		}

	}
	else if (Game::instance().getKey(GLFW_KEY_DOWN) || Game::instance().getKey(GLFW_KEY_S)) {

		if (sprite->animation() != MOVE_DOWN)
			sprite->changeAnimation(MOVE_DOWN);
		posPlayer.y += 2;

		if (map->checkTileCollision(posPlayer, glm::ivec2(13.6, 27.2)))
		{
			posPlayer.y -= 2;
			sprite->changeAnimation(STAND_DOWN);
		}

	}
	else if (Game::instance().getKey(GLFW_KEY_Z)) {
		if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(PUNCH_LEFT);
		else if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(PUNCH_RIGHT);
		else if (sprite->animation() == STAND_UP || sprite->animation() == MOVE_UP)
			sprite->changeAnimation(PUNCH_UP);
		else if (sprite->animation() == STAND_DOWN || sprite->animation() == MOVE_DOWN)
			sprite->changeAnimation(PUNCH_DOWN);
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT || sprite->animation() == PUNCH_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT || sprite->animation() == PUNCH_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
		else if (sprite->animation() == MOVE_UP || sprite->animation() == PUNCH_UP)
			sprite->changeAnimation(STAND_UP);
		else if (sprite->animation() == MOVE_DOWN || sprite->animation() == PUNCH_DOWN)
			sprite->changeAnimation(STAND_DOWN);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Player::checkMap(glm::ivec2 &newPos)
{
	int idMap = map->getId();
	if (idMap == 1) {
		if (map->isOutRight(posPlayer, glm::ivec2(13.6, 27.2))) {
			cout << "Cambio a mapa 2" << endl;
			newPos = glm::ivec2(0, posPlayer.y);
			return 2;
		}
	}
	else if (idMap == 2) {
		if (map->isOutLeft(posPlayer)) {
			cout << "Cambio a mapa 1" << endl;
			float mapWidthPixels = map->getMapSize().x * map->getTileSize();
			newPos = glm::ivec2(mapWidthPixels -20, posPlayer.y);
			return 1;
		}
		else if (map->isOutBottom(posPlayer, glm::ivec2(13.6, 27.2))) {
			cout << "Cambio a mapa 3" << endl;
			newPos = glm::ivec2(posPlayer.x, 0);
			return 3;
		}
	}
	else if (idMap == 3) {
		if (map->isOutTop(posPlayer)) {
			cout << "Cambio a mapa 2" << endl;
			float mapHeightPixels = map->getMapSize().y * map->getTileSize();
			newPos = glm::ivec2(posPlayer.x, mapHeightPixels - 30);
			return 2;
		}
		else if (map->isOutBottom(posPlayer, glm::ivec2(13.6, 27.2))) {
			cout << "Cambio a mapa 4" << endl;
			newPos = glm::ivec2(posPlayer.x, 0);
			return 4;
		}
	}
	else if (idMap == 4) {
		if (map->isOutTop(posPlayer)) {
			cout << "Cambio a mapa 3" << endl;
			float mapHeightPixels = map->getMapSize().y * map->getTileSize();
			newPos = glm::ivec2(posPlayer.x, mapHeightPixels - 30);
			return 3;
		}
		else if (map->isOutRight(posPlayer, glm::ivec2(13.6, 27.2))) {
			cout << "Cambio a mapa 6" << endl;
			newPos = glm::ivec2(0, posPlayer.y);
			return 6;
		}
		else if (map->isOutLeft(posPlayer)) {
			cout << "Cambio a mapa 5" << endl;
			float mapWidthPixels = map->getMapSize().x * map->getTileSize();
			newPos = glm::ivec2(mapWidthPixels - 20, posPlayer.y);
			return 5;
		}
	}
	else if (idMap == 5) {
		if (map->isOutRight(posPlayer, glm::ivec2(13.6, 27.2))) {
			cout << "Cambio a mapa 4" << endl;
			newPos = glm::ivec2(0, posPlayer.y);
			return 4;
		}
	}
	else if (idMap == 6) {
		if (map->isOutLeft(posPlayer)) {
			cout << "Cambio a mapa 4" << endl;
			float mapWidthPixels = map->getMapSize().x * map->getTileSize();
			newPos = glm::ivec2(mapWidthPixels - 20, posPlayer.y);
			return 4;
		}
		else if (map->checkChangeMap(posPlayer, glm::ivec2(13.6, 27.2), { 100, 70 })) {
			cout << "Cambio a mapa 7" << endl;
			float mapHeightPixels = map->getMapSize().y * map->getTileSize();
			newPos = glm::ivec2(posPlayer.x, mapHeightPixels - 50);
			return 7;
		}
	}
	else if (idMap == 7) {
		if (map->checkChangeMap(posPlayer, glm::ivec2(13.6, 27.2), { 19 })) {
			cout << "Cambio a mapa 6" << endl;
			newPos = glm::ivec2(posPlayer.x, 50);
			return 6;
		}
		else if (map->checkChangeMap(posPlayer, glm::ivec2(13.6, 27.2), { 112})) {
			cout << "Cambio a mapa 8" << endl;
			float mapHeightPixels = map->getMapSize().y * map->getTileSize();
			newPos = glm::ivec2(25, mapHeightPixels - 50);
			return 8;
		}
	}
	else if (idMap == 8) {
		if (map->checkChangeMap(posPlayer, glm::ivec2(13.6, 27.2), { 172 })) {
			cout << "Cambio a mapa 7" << endl;
			float mapWidthPixels = map->getMapSize().x * map->getTileSize();
			newPos = glm::ivec2(mapWidthPixels - 30, 20);
			return 7;
		}
		else if (map->checkChangeMap(posPlayer, glm::ivec2(13.6, 27.2), {19, 18, 20})) {
			cout << "Cambio a mapa 9" << endl;
			float mapHeightPixels = map->getMapSize().y * map->getTileSize();
			newPos = glm::ivec2(30, mapHeightPixels - 50);
			return 9;
		}
	}
	else if (idMap == 9) {
		if (map->checkChangeMap(posPlayer, glm::ivec2(13.6, 27.2), { 163, 164, 162})) {
			cout << "Cambio a mapa 8" << endl;
			float mapWidthPixels = map->getMapSize().x * map->getTileSize();
			newPos = glm::ivec2(mapWidthPixels - 55,  40);
			return 8;
		}
		else if (map->checkChangeMap(posPlayer, glm::ivec2(13.5, 27.2), { 296,326})) {
			cout << "Cambio a mapa 10" << endl;
			float mapHeightPixels = map->getMapSize().y * map->getTileSize();
			newPos = glm::ivec2(posPlayer.x -40, mapHeightPixels -40);
			return 10;
		}
	}
	else if (idMap == 10) {
		if (map->isOutBottom(posPlayer, glm::ivec2(13.6, 27.2))) {
			cout << "Cambio mapa a 9" << endl;
			newPos = glm::ivec2(posPlayer.x + 48, 60);
			return 9;
		}
	
	}

	return idMap;
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




