#pragma once
#include "Sprite.h"

enum ItemTypes
{
	GUN, LIFE, BULLETS
};

class Item
{
public:
	virtual ~Item() {}
	virtual int getType() = 0;
	void init(ShaderProgram& shaderProgram);
	bool collisionWithPlayer(const glm::ivec2& playerPos, const glm::ivec2& playerSize) const;
	bool canGrabItem(const glm::ivec2& playerPos, const glm::ivec2& playerSize);
	void collect();
	void render();


	glm::ivec2 position;
	bool collected;
	Sprite* sprite;
	Sprite* HUDsprite;
	Texture spritesheet;
};