#include "MeleEnemy.h"
#include <GL/glew.h>
#include <iostream>



enum EnemyAnims
{
	STAND_DOWN, STAND_UP, STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN,
};

MeleEnemy::MeleEnemy(const glm::ivec2& position, ShaderProgram& shaderProgram, TileMap* map)
{
	//this->map = map;
	posEnemy = position;
	health = 3;
	damage = 1;
	size = glm::ivec2(16, 16);
	this->map = map;
	this->init(shaderProgram);
	
}

void MeleEnemy::init(ShaderProgram& shaderProgram)
{

	spritesheet.loadFromFile("images/pikachu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(size, glm::vec2(0.25f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_DOWN, 6);
	sprite->addKeyframe(STAND_DOWN, glm::vec2(0.25f * 2, 0.f));

	sprite->setAnimationSpeed(STAND_LEFT, 6);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.25f * 1, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 6);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f*3, 0.5));

	sprite->setAnimationSpeed(STAND_UP, 6);
	sprite->addKeyframe(STAND_UP, glm::vec2(0.25f*0, 0.f));

	sprite->setAnimationSpeed(MOVE_DOWN, 6);
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25 * 2.f, 0.0f));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25 * 2.f, 0.5f));


	sprite->setAnimationSpeed(MOVE_UP, 6);
	sprite->addKeyframe(MOVE_UP, glm::vec2(0.25 * 0.f, 0.0f));
	sprite->addKeyframe(MOVE_UP, glm::vec2(0.25 * 0.f, 0.5f));


	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25 * 1.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25 * 1.f, 0.5f));


	sprite->setAnimationSpeed(MOVE_RIGHT, 6);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25 * 3.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25 * 3.f, 0.5f));


	sprite->changeAnimation(0);
	lookingDirection = DOWN;
	sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));
}

void MeleEnemy::update(int deltaTime, const glm::ivec2& playerPos)
{
	sprite->update(deltaTime);
	//sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));
	if (this->seePlayer(playerPos)) {
		cout << "Veo al jugador" << endl;
	}
}