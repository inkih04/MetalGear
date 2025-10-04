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
	sprite = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.0556f, 0.5f), &spritesheet, &shaderProgram);
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
		/*if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
		*/
		if (map->isOutLeft(posPlayer))
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
		/*
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}*/
		if (map->isOutRight(posPlayer, glm::ivec2(16, 32)))
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

		if (map->isOutTop(posPlayer))
		{
			posPlayer.y += 2;
			sprite->changeAnimation(STAND_UP);
		}
	}
	else if (Game::instance().getKey(GLFW_KEY_DOWN) || Game::instance().getKey(GLFW_KEY_S)) {
		if (sprite->animation() != MOVE_DOWN)
			sprite->changeAnimation(MOVE_DOWN);
		posPlayer.y += 2;

		if (map->isOutBottom(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.y -= 2;
			sprite->changeAnimation(STAND_DOWN);
		}
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

	if (Game::instance().getKey(GLFW_KEY_Z)) {
		if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(PUNCH_LEFT);
		else if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(PUNCH_RIGHT);
		else if (sprite->animation() == STAND_UP || sprite->animation() == MOVE_UP)
			sprite->changeAnimation(PUNCH_UP);
		else if (sprite->animation() == STAND_DOWN || sprite->animation() == MOVE_DOWN)
			sprite->changeAnimation(PUNCH_DOWN);
	}


		
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
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




