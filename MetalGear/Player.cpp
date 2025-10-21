#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Player.h"
#include "Game.h"
#include "Item.h"
#include <GLFW/glfw3.h>


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_DOWN, STAND_UP, STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, PUNCH_LEFT, PUNCH_RIGHT, PUNCH_UP, PUNCH_DOWN,
	STAND_DOWN_GUN, STAND_UP_GUN, STAND_LEFT_GUN, STAND_RIGHT_GUN, MOVE_LEFT_GUN, MOVE_RIGHT_GUN, MOVE_UP_GUN, MOVE_DOWN_GUN

};



void Player::heal(int life)
{
	health += life;
	if (health > 6)
		health = 6;
	std::cout << "Player healed, health now: " << health << std::endl;
}

void Player::takeDamage(int dmg)
{
	health -= dmg;
	if (health < 0)
		health = 0;
	std::cout << "Player took " << dmg << " damage, health now: " << health << std::endl;
}


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	health = 6;
	cout << "Player initialized with health: " << health << std::endl;
	equippedGun = false;
	spritesheet.loadFromFile("images/metal.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(13.6, 27.2), glm::vec2(0.0556f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(20);

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

		//gun
		sprite->setAnimationSpeed(MOVE_DOWN_GUN, 6);
		sprite->addKeyframe(MOVE_DOWN_GUN, glm::vec2(0.0556 * 8.f, 0.0f));
		sprite->addKeyframe(MOVE_DOWN_GUN, glm::vec2(0.0556 * 10.f, 0.0f));
		sprite->addKeyframe(MOVE_DOWN_GUN, glm::vec2(0.0556 * 12.f, 0.0f));
		sprite->addKeyframe(MOVE_DOWN_GUN, glm::vec2(0.0556 * 14.f, 0.0f));

		sprite->setAnimationSpeed(MOVE_UP_GUN, 6);
		sprite->addKeyframe(MOVE_UP_GUN, glm::vec2(0.0556 * 9.f, 0.0f));
		sprite->addKeyframe(MOVE_UP_GUN, glm::vec2(0.0556 * 11.f, 0.0f));
		sprite->addKeyframe(MOVE_UP_GUN, glm::vec2(0.0556 * 13.f, 0.0f));
		sprite->addKeyframe(MOVE_UP_GUN, glm::vec2(0.0556 * 15.f, 0.0f));

		sprite->setAnimationSpeed(MOVE_LEFT_GUN, 6);
		sprite->addKeyframe(MOVE_LEFT_GUN, glm::vec2(0.0556 * 8.f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT_GUN, glm::vec2(0.0556 * 10.f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT_GUN, glm::vec2(0.0556 * 12.f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT_GUN, glm::vec2(0.0556 * 14.f, 0.5f));

		sprite->setAnimationSpeed(MOVE_RIGHT_GUN, 6);
		sprite->addKeyframe(MOVE_RIGHT_GUN, glm::vec2(0.0556 * 9.f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT_GUN, glm::vec2(0.0556 * 11.f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT_GUN, glm::vec2(0.0556 * 13.f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT_GUN, glm::vec2(0.0556 * 15.f, 0.5f));

		sprite->setAnimationSpeed(STAND_DOWN_GUN, 6);
		sprite->addKeyframe(STAND_DOWN_GUN, glm::vec2(0.0556f * 8, 0.f));

		sprite->setAnimationSpeed(STAND_LEFT_GUN, 6);
		sprite->addKeyframe(STAND_LEFT_GUN, glm::vec2(0.0556f * 8, 0.5f));

		sprite->setAnimationSpeed(STAND_RIGHT_GUN, 6);
		sprite->addKeyframe(STAND_RIGHT_GUN, glm::vec2(0.0556f *9, 0.5f));

		sprite->setAnimationSpeed(STAND_UP_GUN, 6);
		sprite->addKeyframe(STAND_UP_GUN, glm::vec2(0.0556f * 9, 0.f));

		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	if (gun != nullptr) {
		gun->update(deltaTime);
	}
	lastPunch += deltaTime;

	static bool ePressedLastFrame = false;

	bool ePressedNow = Game::instance().getKey(GLFW_KEY_E);

	sprite->update(deltaTime);
	if (Game::instance().getKey(GLFW_KEY_LEFT) || Game::instance().getKey(GLFW_KEY_A))
	{
		if (sprite->animation() != (equippedGun ? MOVE_LEFT_GUN : MOVE_LEFT))
			sprite->changeAnimation(equippedGun ? MOVE_LEFT_GUN : MOVE_LEFT);

		posPlayer.x -= 2;

		if (map->checkTileCollision(posPlayer, glm::ivec2(13.6, 27.2), true))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(equippedGun ? STAND_LEFT_GUN : STAND_LEFT);
		}
	}
	else if (Game::instance().getKey(GLFW_KEY_RIGHT) || Game::instance().getKey(GLFW_KEY_D))
	{
		if (sprite->animation() != (equippedGun ? MOVE_RIGHT_GUN : MOVE_RIGHT))
			sprite->changeAnimation(equippedGun ? MOVE_RIGHT_GUN : MOVE_RIGHT);

		posPlayer.x += 2;

		if (map->checkTileCollision(posPlayer, glm::ivec2(13.6, 27.2), true))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(equippedGun ? STAND_RIGHT_GUN : STAND_RIGHT);
		}
	}
	else if (Game::instance().getKey(GLFW_KEY_UP) || Game::instance().getKey(GLFW_KEY_W))
	{
		if (sprite->animation() != (equippedGun ? MOVE_UP_GUN : MOVE_UP))
			sprite->changeAnimation(equippedGun ? MOVE_UP_GUN : MOVE_UP);

		posPlayer.y -= 2;

		if (map->checkTileCollision(posPlayer, glm::ivec2(13.6, 27.2), true))
		{
			posPlayer.y += 2;
			sprite->changeAnimation(equippedGun ? STAND_UP_GUN : STAND_UP);
		}
	}
	else if (Game::instance().getKey(GLFW_KEY_DOWN) || Game::instance().getKey(GLFW_KEY_S))
	{
		if (sprite->animation() != (equippedGun ? MOVE_DOWN_GUN : MOVE_DOWN))
			sprite->changeAnimation(equippedGun ? MOVE_DOWN_GUN : MOVE_DOWN);

		posPlayer.y += 2;

		if (map->checkTileCollision(posPlayer, glm::ivec2(13.6, 27.2), true))
		{
			posPlayer.y -= 2;
			sprite->changeAnimation(equippedGun ? STAND_DOWN_GUN : STAND_DOWN);
		}
	}
	else if (Game::instance().getKey(GLFW_KEY_Z)) {
		if (!equippedGun) {
			if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT) {
				sprite->changeAnimation(PUNCH_LEFT);
			}
			else if (sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT) {
				sprite->changeAnimation(PUNCH_RIGHT);
			}
			else if (sprite->animation() == STAND_UP || sprite->animation() == MOVE_UP) {
				sprite->changeAnimation(PUNCH_UP);
			}
			else if (sprite->animation() == STAND_DOWN || sprite->animation() == MOVE_DOWN) {
				sprite->changeAnimation(PUNCH_DOWN);
			}
			if (map->canPunchEnemies(posPlayer, glm::ivec2(13.6, 27.2)) && canPunch()) {
				map->doPunchDamageToEnemies(posPlayer, glm::ivec2(13.6, 27.2), 1);
				lastPunch = 0;
			}
		}
		else {
			int direction;
			if (sprite->animation() == STAND_LEFT_GUN || sprite->animation() == MOVE_LEFT_GUN) {
				direction = LEFT;
			}
			else if (sprite->animation() == STAND_RIGHT_GUN || sprite->animation() == MOVE_RIGHT_GUN) {
				direction = RIGHT;
			}
			else if (sprite->animation() == STAND_UP_GUN || sprite->animation() == MOVE_UP_GUN) {
				direction = UP;
			}
			else if (sprite->animation() == STAND_DOWN_GUN || sprite->animation() == MOVE_DOWN_GUN) {
				direction = DOWN;
			}

			gun->shoot(posPlayer, direction, map);
		}
	}
	else if (ePressedNow && !ePressedLastFrame) {
		if (map->checkItemCollision(posPlayer, glm::ivec2(13.6, 27.2))) {
			addItem(map->getItemAt(posPlayer, glm::ivec2(13.6, 27.2)));
			//todo: mostrar mensaje de item recogido
		}
	}
	else
	{
		if (!equippedGun) {
			if (sprite->animation() == MOVE_LEFT || sprite->animation() == PUNCH_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == PUNCH_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
			else if (sprite->animation() == MOVE_UP || sprite->animation() == PUNCH_UP)
				sprite->changeAnimation(STAND_UP);
			else if (sprite->animation() == MOVE_DOWN || sprite->animation() == PUNCH_DOWN)
				sprite->changeAnimation(STAND_DOWN);
		}
		else {
			if (sprite->animation() == MOVE_LEFT_GUN)
				sprite->changeAnimation(STAND_LEFT_GUN);
			else if (sprite->animation() == MOVE_RIGHT_GUN)
				sprite->changeAnimation(STAND_RIGHT_GUN);
			else if (sprite->animation() == MOVE_UP_GUN)
				sprite->changeAnimation(STAND_UP_GUN);
			else if (sprite->animation() == MOVE_DOWN_GUN)
				sprite->changeAnimation(STAND_DOWN_GUN);
		}
	}
	ePressedLastFrame = ePressedNow;


	static bool spacePressedLastFrame = false;

	bool spacePressedNow = Game::instance().getKey(GLFW_KEY_SPACE);

	if (spacePressedNow && !spacePressedLastFrame) {
		if (gun != nullptr) {
			equippedGun = !equippedGun;
			cout << (equippedGun ? "Gun equipped" : "Gun unequipped") << endl;
			if (!equippedGun) {
				if (sprite->animation() == STAND_LEFT_GUN )
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() == STAND_RIGHT_GUN)
					sprite->changeAnimation(STAND_RIGHT);
				else if (sprite->animation() == STAND_UP_GUN)
					sprite->changeAnimation(STAND_UP);
				else if (sprite->animation() == STAND_DOWN_GUN)
					sprite->changeAnimation(STAND_DOWN);
			}
			else {
				if (sprite->animation() == STAND_LEFT)
					sprite->changeAnimation(STAND_LEFT_GUN);
				else if (sprite->animation() == STAND_RIGHT)
					sprite->changeAnimation(STAND_RIGHT_GUN);
				else if (sprite->animation() == STAND_UP)
					sprite->changeAnimation(STAND_UP_GUN);
				else if (sprite->animation() == STAND_DOWN)
					sprite->changeAnimation(STAND_DOWN_GUN);
			}
		}
	}

	spacePressedLastFrame = spacePressedNow;


	static bool cPressedLastFrame = false;

	bool cPressedNow = Game::instance().getKey(GLFW_KEY_C);

	if (cPressedNow && !cPressedLastFrame) {
		cout << "Switching item" << endl;
		if (!items.empty()) {
			currentItem = (currentItem + 1) % items.size();
			cout << "current item " << currentItem << endl;
		}
	}

	cPressedLastFrame = cPressedNow;

	static bool xPressedLastFrame = false;

	bool xPressedNow = Game::instance().getKey(GLFW_KEY_X);

	if (xPressedNow && !xPressedLastFrame) {
		if (!items.empty()) {
			if (items[currentItem]->getType() == BULLETS && gun == nullptr) return;
			items[currentItem]->use(this);
			if (items[currentItem]->destroyAfterUse()) {
				delete items[currentItem];
				items.erase(items.begin() + currentItem);
				if (items.empty()) {
					currentItem = 0; 
				}
				else if (currentItem >= items.size()) {
					currentItem = items.size() - 1; 
				}
			}

		}
	}

	xPressedLastFrame = xPressedNow;

	cout << "Player position: (" << posPlayer.x << ", " << posPlayer.y << ")" << endl;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

bool Player::canPunch() {
	return lastPunch >= punchRate;
}

int Player::checkMap(glm::ivec2 &newPos)
{
	return map->changeMapIfNeeded(posPlayer, glm::ivec2(13.6, 27.2), newPos);
}

void Player::checkEnemies(int deltaTime)
{
	map->updateEnemies(deltaTime, posPlayer);
}

void Player::render()
{
	if (gun != nullptr && equippedGun) {
		gun->renderGun();
	}

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




