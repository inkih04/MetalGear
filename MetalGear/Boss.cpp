#include "Boss.h"
#include <GL/glew.h>
#include "TileMap.h"
#include <iostream>
#include "Game.h"
#include <GLFW/glfw3.h>
#include "AudioManager.h"




Boss::Boss(const glm::ivec2& position, ShaderProgram& shaderProgram, TileMap* map, int direction, Player* player)
{
    posEnemy = position;
    this->health = 21;
    cout << "Boss created at position (" << position.x << ", " << position.y << ") with health " << health << endl;
    damage = 1;
    speed = 1;
    fireRate = 1500;
    lastShotTime = fireRate;
    this->player = player;
    this->direction = direction;

    teleportTimer = 0;
    teleportInterval = 3000; 
    currentPositionIndex = 0;

    teleportPositions.push_back(glm::ivec2(112, 71));
    teleportPositions.push_back(glm::ivec2(190, 54));
    teleportPositions.push_back(glm::ivec2(20, 100));
    teleportPositions.push_back(glm::ivec2(20, 54));
    teleportPositions.push_back(glm::ivec2(190, 95));

    damageCounter = 0;
    damageThreshold = 6;
    lastHealthCheck = health;

    size = glm::ivec2(32, 32);
    playerHasBeenDetected = false;
    this->map = map;
    this->init(shaderProgram);

}

bool Boss::checkCollisionWithPlayer(const glm::ivec2& playerPos, const glm::ivec2& playerSize) const
{
    if (dead) return false;

    bool collisionX = posEnemy.x < playerPos.x + playerSize.x &&
        posEnemy.x + size.x > playerPos.x;

    bool collisionY = posEnemy.y + 8 < playerPos.y + playerSize.y &&
        posEnemy.y + size.y > playerPos.y + 16;

    return collisionX && collisionY;
}

bool Boss::canShoot()
{
    return lastShotTime >= fireRate && !dead;
}

void Boss::takeDamage(int dmg)
{
    if (dead) return;

    int previousHealth = health;
    health -= dmg;

    int healthLost = lastHealthCheck - health;
    damageCounter += dmg;

    AudioManager::instance().playSound("sound_charizard");

    if (damageCounter >= damageThreshold) {
        std::cout << "Boss received " << damageCounter << " damage! Teleporting..." << std::endl;
        teleport();
        damageCounter = 0; 
        teleportTimer = 0; 
        lastHealthCheck = health;
    }

    if (health <= 0) {
        health = 0;
        dead = true;
        std::cout << "Boss (Mewtwo) defeated!" << std::endl;
    }
}

void Boss::teleport()
{
    int attempts = 0;
    int maxAttempts = teleportPositions.size();
    glm::ivec2 targetPosition;
    bool validPosition = false;

    while (attempts < maxAttempts && !validPosition) {
        currentPositionIndex = (currentPositionIndex + 1) % teleportPositions.size();
        targetPosition = teleportPositions[currentPositionIndex];

        glm::ivec2 playerPos = player->getPosition();

        float distanceX = abs(targetPosition.x - playerPos.x);
        float distanceY = abs(targetPosition.y - playerPos.y);

        if (distanceX > 48 || distanceY > 48) {
            validPosition = true;
        }

        attempts++;
    }

    if (!validPosition) {
        std::cout << "Boss: No valid teleport position found (player too close to all positions)" << std::endl;
        return;
    }

    posEnemy = targetPosition;
    sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));

    std::cout << "Boss teleported to position (" << posEnemy.x << ", " << posEnemy.y << ")" << std::endl;

}

enum EnemyAnims
{
    STAND_DOWN, STAND_UP, STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN,
};

void Boss::init(ShaderProgram& shaderProgram)
{
    s = &shaderProgram;
    spritesheet.loadFromFile("images/mewtwo.png", TEXTURE_PIXEL_FORMAT_RGBA);
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

void Boss::atack()
{
    if (!canShoot()) {
        return;
    }
    AudioManager::instance().playSound("sound_fireball");
    FireBall* newFireBall = new FireBall(glm::ivec2(posEnemy.x, posEnemy.y + 17), -1, map, *s, player);
    fireBalls.push_back(newFireBall);
    lastShotTime = 0;
}

void Boss::update(int deltaTime, const glm::ivec2& playerPos)
{
    sprite->update(deltaTime);

    if (this->seePlayer(playerPos)) {
        playerHasBeenDetected = true;
        this->move(playerPos);
        this->atack();

    }

    lastShotTime += deltaTime;

    if (!dead) {
        teleportTimer += deltaTime;

        if (teleportTimer >= teleportInterval) {
            teleport();
            teleportTimer = 0; 
            damageCounter = 0; 
            lastHealthCheck = health; 
        }
    }

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

void Boss::render()
{
    if (!dead)
        sprite->render();
    for (auto& fireBall : fireBalls) {
        fireBall->render();
    }
}

bool Boss::seePlayer(const glm::ivec2& playerPos) const
{
    if (map == nullptr)
        return false;

    if (playerHasBeenDetected)
        return true;
	if (health < 21) return true;

    glm::ivec2 mapSize = map->getMapSize();
    int tileSize = map->getTileSize();
    int mapHeightPixels = mapSize.y * tileSize;

    int playerCenterY = playerPos.y + 13;

    if (playerCenterY < mapHeightPixels - 100) {
        cout << "te vi por altura" << endl;
        return true;
    }

    return false;
}


void Boss::move(const glm::ivec2& playerPos) {
    return;
}
