#include "MeleEnemy.h"
#include <GL/glew.h>
#include "TileMap.h"
#include <iostream>
#include "Game.h"
#include <GLFW/glfw3.h>




MeleEnemy::MeleEnemy(const glm::ivec2& position, ShaderProgram& shaderProgram, TileMap* map)
{
	//this->map = map;
	posEnemy = position;
	health = 3;
	damage = 1;
	speed = 1;
	size = glm::ivec2(16, 16);
    playerHasBeenDetected = false;
    playerHasBeenDetected = false;
    isRetreating = false;
    retreatCooldown = 0;
	this->map = map;
	this->init(shaderProgram);
	
}


enum EnemyAnims
{
    STAND_DOWN, STAND_UP, STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN,
};

void MeleEnemy::init(ShaderProgram& shaderProgram)
{

	spritesheet.loadFromFile("images/pikachu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(size, glm::vec2(0.25f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);

	sprite->setAnimationSpeed(STAND_DOWN, 3);
	sprite->addKeyframe(STAND_DOWN, glm::vec2(0.25f * 2, 0.f));

	sprite->setAnimationSpeed(STAND_LEFT, 3);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.25f * 1, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 3);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f*3, 0.5));

	sprite->setAnimationSpeed(STAND_UP, 3);
	sprite->addKeyframe(STAND_UP, glm::vec2(0.25f*0, 0.f));

	sprite->setAnimationSpeed(MOVE_DOWN, 3);
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25 * 2.f, 0.0f));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25 * 2.f, 0.5f));
    sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25 * 2.f, 0.0f));


	sprite->setAnimationSpeed(MOVE_UP, 3);
	sprite->addKeyframe(MOVE_UP, glm::vec2(0.25 * 0.f, 0.0f));
	sprite->addKeyframe(MOVE_UP, glm::vec2(0.25 * 0.f, 0.5f));
    sprite->addKeyframe(MOVE_UP, glm::vec2(0.25 * 0.f, 0.0f));


	sprite->setAnimationSpeed(MOVE_LEFT, 3);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25 * 1.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25 * 1.f, 0.5f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25 * 1.f, 0.f));


	sprite->setAnimationSpeed(MOVE_RIGHT, 3);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25 * 3.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25 * 3.f, 0.5f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25 * 3.f, 0.f));


	sprite->changeAnimation(0);
	lookingDirection = DOWN;
	sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));
}

void MeleEnemy::update(int deltaTime, const glm::ivec2& playerPos)
{
	sprite->update(deltaTime);
    if (isRetreating) {
        retreatCooldown -= deltaTime;
        if (retreatCooldown <= 0) {
            isRetreating = false;
            retreatCooldown = 0;
        }
        return;  
    }

	bool debug = false;
    if (debug) {

        if (Game::instance().getKey(GLFW_KEY_LEFT) || Game::instance().getKey(GLFW_KEY_A))
        {
            if (sprite->animation() != MOVE_LEFT)
                sprite->changeAnimation(MOVE_LEFT);
            posEnemy.x -= speed;
            if (map->checkTileCollision(posEnemy, glm::ivec2(13.6, 27.2)))
            {
                posEnemy.x += speed;
                sprite->changeAnimation(STAND_LEFT);
            }

        }
        else if (Game::instance().getKey(GLFW_KEY_RIGHT) || Game::instance().getKey(GLFW_KEY_D))
        {
            if (sprite->animation() != MOVE_RIGHT)
                sprite->changeAnimation(MOVE_RIGHT);

            posEnemy.x += speed;

            if (map->checkTileCollision(posEnemy, glm::ivec2(13.6, 27.2)))
            {
                posEnemy.x -= speed;
                sprite->changeAnimation(STAND_RIGHT);
            }

        }
        else if (Game::instance().getKey(GLFW_KEY_UP) || Game::instance().getKey(GLFW_KEY_W))
        {
            if (sprite->animation() != MOVE_UP)
                sprite->changeAnimation(MOVE_UP);
            posEnemy.y -= speed;

            if (map->checkTileCollision(posEnemy, glm::ivec2(13.6, 27.2)))
            {
                posEnemy.y += speed;
                sprite->changeAnimation(STAND_UP);
            }

        }
        else if (Game::instance().getKey(GLFW_KEY_DOWN) || Game::instance().getKey(GLFW_KEY_S)) {

            if (sprite->animation() != MOVE_DOWN)
                sprite->changeAnimation(MOVE_DOWN);
            posEnemy.y += speed;;

            if (map->checkTileCollision(posEnemy, glm::ivec2(13.6, 27.2)))
            {
                posEnemy.y -= speed;;
                sprite->changeAnimation(STAND_DOWN);
            }

        }

        sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
    }
    else {
        if (this->seePlayer(playerPos)) {
            playerHasBeenDetected = true; 
            if (!this->checkCollisionWithPlayer(playerPos, glm::ivec2(13.6, 27.2))) {
                this->move(playerPos);
            }
            else {
				retreat();
                isRetreating = true;
                retreatCooldown = RETREAT_COOLDOWN_TIME;
            }
        }
    }
}
void MeleEnemy::retreat() {
    int tileSize = map->getTileSize();
    glm::ivec2 retreatPos = posEnemy;
    int retreatDistance = tileSize * 2;  
    int retreatDirection = lookingDirection;  

    switch (lookingDirection) {
    case LEFT:
        retreatPos.x += retreatDistance;  
        retreatDirection = RIGHT;
        break;
    case RIGHT:
        retreatPos.x -= retreatDistance;  
        retreatDirection = LEFT;
        break;
    case UP:
        retreatPos.y += retreatDistance; 
        retreatDirection = DOWN;
        break;
    case DOWN:
        retreatPos.y -= retreatDistance;  
        retreatDirection = UP;
        break;
    }

    if (!map->checkTileCollision(retreatPos, size)) {
        posEnemy = retreatPos;
        lookingDirection = retreatDirection;

        switch (retreatDirection) {
        case LEFT:
            sprite->changeAnimation(STAND_LEFT);
            break;
        case RIGHT:
            sprite->changeAnimation(STAND_RIGHT);
            break;
        case UP:
            sprite->changeAnimation(STAND_UP);
            break;
        case DOWN:
            sprite->changeAnimation(STAND_DOWN);
            break;
        }
    }
    else {
        bool retreated = false;

        std::vector<int> directions = { LEFT, RIGHT, UP, DOWN };
        for (int dir : directions) {
            if (dir == lookingDirection) continue;  

            retreatPos = posEnemy;
            switch (dir) {
            case LEFT:
                retreatPos.x -= retreatDistance;
                break;
            case RIGHT:
                retreatPos.x += retreatDistance;
                break;
            case UP:
                retreatPos.y -= retreatDistance;
                break;
            case DOWN:
                retreatPos.y += retreatDistance;
                break;
            }

            if (!map->checkTileCollision(retreatPos, size)) {
                posEnemy = retreatPos;
                lookingDirection = dir;
                retreated = true;

                switch (dir) {
                case LEFT:
                    sprite->changeAnimation(STAND_LEFT);
                    break;
                case RIGHT:
                    sprite->changeAnimation(STAND_RIGHT);
                    break;
                case UP:
                    sprite->changeAnimation(STAND_UP);
                    break;
                case DOWN:
                    sprite->changeAnimation(STAND_DOWN);
                    break;
                }
                break;
            }
        }

        if (!retreated) {
            switch (lookingDirection) {
            case LEFT:
                sprite->changeAnimation(STAND_LEFT);
                break;
            case RIGHT:
                sprite->changeAnimation(STAND_RIGHT);
                break;
            case UP:
                sprite->changeAnimation(STAND_UP);
                break;
            case DOWN:
                sprite->changeAnimation(STAND_DOWN);
                break;
            }
        }
    }

    sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));
}

void MeleEnemy::move(const glm::ivec2& playerPos) {
    if (map == nullptr)
        return;

    int tileSize = map->getTileSize();
    int enemyTileX = (posEnemy.x + size.x / 2) / tileSize;
    int enemyTileY = (posEnemy.y + size.y / 2) / tileSize;
    int playerTileX = (playerPos.x + 7) / tileSize;
    int playerTileY = (playerPos.y + 13) / tileSize;

    int dx = playerTileX - enemyTileX;
    int dy = playerTileY - enemyTileY;

    bool moved = false;

    if (abs(dx) > abs(dy)) {
        if (dx < 0) {
            moved = tryMove(LEFT);
        }
        else if (dx > 0) {
            moved = tryMove(RIGHT);
        }

        if (!moved && dy != 0) {
            if (dy < 0) {
                moved = tryMove(UP);
            }
            else {
                moved = tryMove(DOWN);
            }
        }
    }
    else {
        if (dy < 0) {
            moved = tryMove(UP);
        }
        else if (dy > 0) {
            moved = tryMove(DOWN);
        }

        if (!moved && dx != 0) {
            if (dx < 0) {
                moved = tryMove(LEFT);
            }
            else {
                moved = tryMove(RIGHT);
            }
        }
    }

    if (!moved) {
        switch (lookingDirection) {
        case LEFT:
            if (sprite->animation() == MOVE_LEFT)
                sprite->changeAnimation(STAND_LEFT);
            break;
        case RIGHT:
            if (sprite->animation() == MOVE_RIGHT)
                sprite->changeAnimation(STAND_RIGHT);
            break;
        case UP:
            if (sprite->animation() == MOVE_UP)
                sprite->changeAnimation(STAND_UP);
            break;
        case DOWN:
            if (sprite->animation() == MOVE_DOWN)
                sprite->changeAnimation(STAND_DOWN);
            break;
        }
    }

    sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));
}

bool MeleEnemy::tryMove(int dir) {
    glm::ivec2 oldPos = posEnemy;

    lookingDirection = dir;
    switch (dir) {
    case LEFT:
        if (sprite->animation() != MOVE_LEFT)
            sprite->changeAnimation(MOVE_LEFT);
        posEnemy.x -= speed;
        break;
    case RIGHT:
        if (sprite->animation() != MOVE_RIGHT)
            sprite->changeAnimation(MOVE_RIGHT);
        posEnemy.x += speed;
        break;
    case UP:
        if (sprite->animation() != MOVE_UP)
            sprite->changeAnimation(MOVE_UP);
        posEnemy.y -= speed;
        break;
    case DOWN:
        if (sprite->animation() != MOVE_DOWN)
            sprite->changeAnimation(MOVE_DOWN);
        posEnemy.y += speed;
        break;
    }

    if (map->checkTileCollision(posEnemy, size)) {
        posEnemy = oldPos;

        switch (dir) {
        case LEFT:
            sprite->changeAnimation(STAND_LEFT);
            break;
        case RIGHT:
            sprite->changeAnimation(STAND_RIGHT);
            break;
        case UP:
            sprite->changeAnimation(STAND_UP);
            break;
        case DOWN:
            sprite->changeAnimation(STAND_DOWN);
            break;
        }

        return false;
    }

    return true;  
}