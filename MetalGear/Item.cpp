#include "Item.h"
#include "Player.h"
#include <iostream>


void Item::init(ShaderProgram& shaderProgram)
{
	collected = false;
	spritesheet.loadFromFile("images/pokeball.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::vec2(16, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 3);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->changeAnimation(0);

}

void Item::render()
{
	if (!collected)
		sprite->render();
}

void Item::collect()
{
	collected = true;
}

bool Item::collisionWithPlayer(const glm::ivec2& playerPos, const glm::ivec2& playerSize) const
{
	if (collected) return false;

	bool collisionX = position.x < playerPos.x + playerSize.x &&
		position.x + 16 > playerPos.x;
	bool collisionY = position.y < playerPos.y + playerSize.y &&
		position.y + 16 > playerPos.y + 16;
	return collisionX && collisionY;
}
bool Item::canGrabItem(const glm::ivec2& playerPos, const glm::ivec2& playerSize)
{
	if (collected) return false;
	int grabRange = 32;  

	int itemCenterX = position.x + 8;   
	int itemCenterY = position.y + 8;

	int playerCenterX = playerPos.x + playerSize.x / 2;
	int playerCenterY = playerPos.y + playerSize.y / 2;

	int distX = abs(itemCenterX - playerCenterX);
	int distY = abs(itemCenterY - playerCenterY);

	return distX <= grabRange && distY <= grabRange;
}