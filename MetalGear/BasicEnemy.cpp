#include "BasicEnemy.h"
#include <GL/glew.h>
#include <iostream>

enum EnemyAnims
{
	STAND_DOWN, STAND_UP, STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, PUNCH_LEFT, PUNCH_RIGHT, PUNCH_UP, PUNCH_DOWN
};

BasicEnemy::BasicEnemy(const glm::ivec2& pos, ShaderProgram& shaderProgram)
{
	posEnemy = pos;
	health = 3;
	damage = 1;
	size = glm::ivec2(13.6, 27.2);
	this->init(shaderProgram);
	
}

void BasicEnemy::init(ShaderProgram& shaderProgram)
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
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0556f * 0, 0.5f));

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
	sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));
}

void BasicEnemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}