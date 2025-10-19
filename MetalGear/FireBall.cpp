#include "TileMap.h"
#include "FireBall.h"

FireBall::FireBall(const glm::ivec2& position, int direction, TileMap* currentMap, ShaderProgram& shaderProgram, Player *player) {
	spritesheet.loadFromFile("images/fuego.png", TEXTURE_PIXEL_FORMAT_RGBA);

	sprite = Sprite::createSprite(glm::vec2(16, 16), glm::vec2(1 / 3.f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 3);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(position.x, position.y));

	this->player = player;
	this->playerPosition = player->getPosition();
	this->position = position;
	this->direction = direction;
	currentStep = 0;
	tileMap = currentMap;
	active = true;
	speed = 8;
	distanceTraveled = 0;
	maxDistance = 21800;
	calculateTrajectory();
	size = glm::ivec2(16, 16);
	cout << "FireBall created at position (" << position.x << ", " << position.y << ") moving in direction " << direction << endl;
}

void FireBall::hitTarget() {
	if (!active || player == nullptr) return;

	glm::ivec2 playerPos = player->getPosition();
	glm::ivec2 playerSize(16, 32); 

	bool collisionX = position.x < playerPos.x + playerSize.x &&
		position.x + size.x > playerPos.x;
	bool collisionY = position.y < playerPos.y + playerSize.y &&
		position.y + size.y > playerPos.y;

	if (collisionX && collisionY) {
		active = false; 
		cout << "FireBall hit player at (" << playerPos.x << ", " << playerPos.y << ")" << endl;
		player->takeDamage(1);
	}
}

FireBall::~FireBall() {
	delete sprite;
	delete explosionSprite;
}