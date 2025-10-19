#include "RangeEnemy.h"
#include <GL/glew.h>
#include "TileMap.h"
#include <iostream>
#include "Game.h"
#include <GLFW/glfw3.h>




RangeEnemy::RangeEnemy(const glm::ivec2& position, ShaderProgram& shaderProgram, TileMap* map, const vector<int>& patrolSquare, Guard guard, int direction, Player* player)
{
    posEnemy = position;
    health = 3;
    damage = 1;
    speed = 1;
	fireRate = 1000;
	lastShotTime = fireRate;
	this->player = player;

    if (patrolSquare.size() > 0) this->patrolSquare = patrolSquare;
    else if (guard.guardPosition.size() > 0) {
        this->guardPosition = guard;
        this->currentGuardIndex = 0;
        this->guardTimer = guard.time;
    }

    this->direction = direction;

    size = glm::ivec2(32, 32);
    playerHasBeenDetected = false;
    this->map = map;
    this->init(shaderProgram);

}

bool RangeEnemy::canShoot()
{
    return lastShotTime >= fireRate;
}

enum EnemyAnims
{
    STAND_DOWN, STAND_UP, STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN,
};

void RangeEnemy::init(ShaderProgram& shaderProgram)
{
	s = &shaderProgram;
    spritesheet.loadFromFile("images/charizard.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(size, glm::vec2(0.5f, 0.25f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(8);

    sprite->setAnimationSpeed(STAND_DOWN, 3);
    sprite->addKeyframe(STAND_DOWN, glm::vec2(0.5f * 0, 0.25f *2));

    sprite->setAnimationSpeed(STAND_LEFT, 3);
    sprite->addKeyframe(STAND_LEFT, glm::vec2(0.5f * 1, 0.f));

    sprite->setAnimationSpeed(STAND_RIGHT, 3);
    sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.5f * 1, 0.25f *2));

    sprite->setAnimationSpeed(STAND_UP, 3);
    sprite->addKeyframe(STAND_UP, glm::vec2(0.f, 0.f));

    sprite->setAnimationSpeed(MOVE_DOWN, 2);
    sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.f, 0.25f *2));
    sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.f, 0.25f *3));


    sprite->setAnimationSpeed(MOVE_UP, 3);
    sprite->addKeyframe(MOVE_UP, glm::vec2(0.f, 0.0f));
    sprite->addKeyframe(MOVE_UP, glm::vec2(0.f, 0.25f));


    sprite->setAnimationSpeed(MOVE_LEFT, 3);
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.25f));


    sprite->setAnimationSpeed(MOVE_RIGHT, 3);
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.5f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.75f));


    sprite->changeAnimation(direction);
    lookingDirection = direction;
    sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));
}

void RangeEnemy::atack()
{
    if (!canShoot()) {
        return;
    }
	FireBall* newFireBall = new FireBall(posEnemy, -1, map, *s, player);
    fireBalls.push_back(newFireBall);
	lastShotTime = 0;
}

void RangeEnemy::update(int deltaTime, const glm::ivec2& playerPos)
{
    sprite->update(deltaTime);

    if (this->seePlayer(playerPos)) {
        playerHasBeenDetected = true;
        this->move(playerPos);
        this->atack();

    }
    else {
        if (patrolSquare.size() > 0)
            this->patrol();
        else if (guardPosition.guardPosition.size() > 0) {
            guardTimer -= deltaTime;

            if (guardTimer <= 0) {
                currentGuardIndex = (currentGuardIndex + 1) % guardPosition.guardPosition.size();
                guardTimer = guardPosition.time;
            }

            this->guard();
        }
    }
    lastShotTime += deltaTime;

    for (auto it = fireBalls.begin(); it != fireBalls.end(); ) {
        (*it)->update(deltaTime);

        if (!(*it)->isActive()) {
            delete* it;
            it = fireBalls.erase(it);
        }
        else {
            ++it;
        }
    }

}

void RangeEnemy::render()
{
    sprite->render();
    for (auto& fireBall : fireBalls) {
        fireBall->render();
    }
}


void RangeEnemy::move(const glm::ivec2& playerPos) {
    if (map == nullptr)
        return;

    int tileSize = map->getTileSize();
    int enemyTileX = (posEnemy.x + size.x / 2) / tileSize;
    int enemyTileY = (posEnemy.y + size.y / 2) / tileSize;
    int playerTileX = (playerPos.x + 8) / tileSize;
    int playerTileY = (playerPos.y + 24) / tileSize;

    int dx = playerTileX - enemyTileX;
    int dy = playerTileY - enemyTileY;

    float distance = sqrt(dx * dx + dy * dy);
    const float DESIRED_DISTANCE = 4.0f;
    const float TOLERANCE = 0.5f; 

    bool moved = false;

    if (abs(distance - DESIRED_DISTANCE) <= TOLERANCE) {
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
        return;
    }

    bool shouldMoveAway = distance < DESIRED_DISTANCE;

    if (shouldMoveAway) {
        dx = -dx;
        dy = -dy;
    }

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

bool RangeEnemy::tryMove(int dir) {
    glm::ivec2 oldPos = posEnemy;

    const char* dirName[] = { "DOWN", "UP", "LEFT", "RIGHT" };

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


    if (map->checkTileCollision(posEnemy, size, false)) {
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

void RangeEnemy::patrol() {
    if (map == nullptr)
        return;

    glm::ivec2 oldPos = posEnemy;
    bool moved = false;

    switch (patrolState) {
    case 0:
        if (sprite->animation() != MOVE_RIGHT)
            sprite->changeAnimation(MOVE_RIGHT);
        lookingDirection = RIGHT;
        posEnemy.x += speed;
        patrolProgress += speed;

        if (patrolProgress >= patrolSquare[0]) {
            patrolState = 1;
            patrolProgress = 0;
        }
        break;

    case 1:
        if (sprite->animation() != MOVE_DOWN)
            sprite->changeAnimation(MOVE_DOWN);
        lookingDirection = DOWN;
        posEnemy.y += speed;
        patrolProgress += speed;

        if (patrolProgress >= patrolSquare[1]) {
            patrolState = 2;
            patrolProgress = 0;
        }
        break;

    case 2:
        if (sprite->animation() != MOVE_LEFT)
            sprite->changeAnimation(MOVE_LEFT);
        lookingDirection = LEFT;
        posEnemy.x -= speed;
        patrolProgress += speed;

        if (patrolProgress >= patrolSquare[0]) {
            patrolState = 3;
            patrolProgress = 0;
        }
        break;

    case 3:
        if (sprite->animation() != MOVE_UP)
            sprite->changeAnimation(MOVE_UP);
        lookingDirection = UP;
        posEnemy.y -= speed;
        patrolProgress += speed;

        if (patrolProgress >= patrolSquare[1]) {
            patrolState = 0;
            patrolProgress = 0;
        }
        break;
    }

    if (map->checkTileCollision(posEnemy, size, false)) {
        posEnemy = oldPos;
        patrolState = (patrolState + 1) % 4;
        patrolProgress = 0;
    }

    sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));
}

void RangeEnemy::guard() {
    if (guardPosition.guardPosition.empty())
        return;

    int currentDirection = guardPosition.guardPosition[currentGuardIndex];

    static int lastDirection = -1;
    if (lastDirection != currentDirection) {
        lookingDirection = currentDirection;
        switch (currentDirection) {
        case DOWN:
            sprite->changeAnimation(STAND_DOWN);
            break;
        case UP:
            sprite->changeAnimation(STAND_UP);
            break;
        case LEFT:
            sprite->changeAnimation(STAND_LEFT);
            break;
        case RIGHT:
            sprite->changeAnimation(STAND_RIGHT);
            break;
        }
        lastDirection = currentDirection;
    }

    sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));
}