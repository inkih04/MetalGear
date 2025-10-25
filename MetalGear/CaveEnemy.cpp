#include "CaveEnemy.h"
#include <GL/glew.h>
#include "TileMap.h"
#include <iostream>
#include "Game.h"
#include <GLFW/glfw3.h>
#include "AudioManager.h"




CaveEnemy::CaveEnemy(const glm::ivec2& position, ShaderProgram& shaderProgram, TileMap* map, const vector<int>& patrolSquare, Guard guard, int direction, Player* player)
{
    this->player = player;
    posEnemy = position;
    this->health = 6;
    damage = 2;
    speed = 0.5;


    if (patrolSquare.size() > 0) this->patrolSquare = patrolSquare;
    else if (guard.guardPosition.size() > 0) {
        this->guardPosition = guard;
        this->currentGuardIndex = 0;
        this->guardTimer = guard.time;
    }

    this->direction = direction;

    size = glm::ivec2(32, 16);
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

void CaveEnemy::init(ShaderProgram& shaderProgram)
{

    spritesheet.loadFromFile("images/geodude.png", TEXTURE_PIXEL_FORMAT_RGBA);

    sprite = Sprite::createSprite(size, glm::vec2(0.5f, 0.25f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(8);

    sprite->setAnimationSpeed(STAND_DOWN, 3);
    sprite->addKeyframe(STAND_DOWN, glm::vec2(0.5f * 0, 0.25f * 2));

    sprite->setAnimationSpeed(STAND_LEFT, 3);
    sprite->addKeyframe(STAND_LEFT, glm::vec2(0.5f * 1, 0.f));

    sprite->setAnimationSpeed(STAND_RIGHT, 3);
    sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.5f * 1, 0.25f * 2));

    sprite->setAnimationSpeed(STAND_UP, 3);
    sprite->addKeyframe(STAND_UP, glm::vec2(0.f, 0.f));

    sprite->setAnimationSpeed(MOVE_DOWN, 2);
    sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.f, 0.25f * 2));
    sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.f, 0.25f * 3));


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

void CaveEnemy::update(int deltaTime, const glm::ivec2& playerPos)
{
    sprite->update(deltaTime);
    if (dead) return;

    if (isRetreating) {
        retreatCooldown -= deltaTime;
        if (retreatCooldown <= 0) {
            isRetreating = false;
            retreatCooldown = 0;
        }
        return;
    }

    if (this->seePlayer(playerPos)) {
        playerHasBeenDetected = true;
        if (!this->checkCollisionWithPlayer(playerPos, glm::ivec2(16, 32))) {
            this->move(playerPos);
        }
        else {
            player->takeDamage(this->getDamage());
            retreat();
            isRetreating = true;
            retreatCooldown = RETREAT_COOLDOWN_TIME;
        }
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

}


void CaveEnemy::retreat() {
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

    bool pathClear = checkRetreatPath(posEnemy, retreatPos);

    if (pathClear && !map->checkTileCollision(retreatPos, size, false)) {
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

            pathClear = checkRetreatPath(posEnemy, retreatPos);

            if (pathClear && !map->checkTileCollision(retreatPos, size, false)) {
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


bool CaveEnemy::checkRetreatPath(glm::ivec2 start, glm::ivec2 end) {
    int tileSize = map->getTileSize();

    glm::ivec2 direction;
    if (end.x != start.x) {
        direction = glm::ivec2((end.x > start.x) ? 1 : -1, 0);
    }
    else {
        direction = glm::ivec2(0, (end.y > start.y) ? 1 : -1);
    }

    glm::ivec2 currentPos = start;
    while (currentPos != end) {
        currentPos.x += direction.x * tileSize;
        currentPos.y += direction.y * tileSize;

        if (map->checkTileCollision(currentPos, size, false)) {
            return false;
        }
    }

    return true;
}

void CaveEnemy::move(const glm::ivec2& playerPos) {
    if (map == nullptr)
        return;

    int tileSize = map->getTileSize();
    int enemyTileX = (posEnemy.x + size.x / 2) / tileSize;
    int enemyTileY = (posEnemy.y + size.y / 2) / tileSize;
    int playerTileX = (playerPos.x + 8) / tileSize;
    int playerTileY = (playerPos.y + 24) / tileSize;

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

bool CaveEnemy::tryMove(int dir) {
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

void CaveEnemy::patrol() {
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

void CaveEnemy::guard() {
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

void CaveEnemy::takeDamage(int dmg)
{
    if (dead) return;

    health -= dmg;

    AudioManager::instance().playSound("sound_geodude");

    if (health <= 0) {
        health = 0;
        dead = true;
        std::cout << "CaveEnemy (Geodude) defeated!" << std::endl;
    }
}