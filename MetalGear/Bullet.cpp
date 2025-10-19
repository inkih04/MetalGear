#include "TileMap.h"
#include "Bullet.h"

Bullet::Bullet(const glm::ivec2& position, int direction, TileMap* currentMap, ShaderProgram& shaderProgram) {
	spritesheet.loadFromFile("images/fuego.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::vec2(16, 16), glm::vec2(1 / 3.f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 3);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(position.x, position.y));

	this->position = position;
	this->direction = direction;
	currentStep = 0;
	tileMap = currentMap;
	active = true;
	speed = 4;
	distanceTraveled = 0;
	maxDistance = 800;
	calculateTrajectory();
	size = glm::ivec2(16, 16);
	cout << "Bullet created at position (" << position.x << ", " << position.y << ") moving in direction " << direction << endl;
}

Bullet::~Bullet() {
	delete sprite;
	delete explosionSprite;
}