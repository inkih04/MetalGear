#pragma once
#include "Sprite.h"
#include <vector>

class TileMap;

enum LookingDirection
{
	DOWN, UP, LEFT, RIGHT
};

class Projectile {

public:
	void update(int deltaTime);
	void render();
	void calculateTrajectory();
	bool isActive() const { return active; }
	glm::ivec2 getPosition() const { return position; }
	glm::ivec2 getSize() const { return size; }
	std::vector<glm::ivec2> getTrajectoryPoints() const { return trajectoryPoints; }

protected:
	glm::ivec2 position;
	glm::ivec2 size;
	int direction;  
	int speed;
	int maxDistance;
	int distanceTraveled;

	bool active;
	Sprite* sprite;
	Sprite* explosionSprite;
	Texture spritesheet;
	TileMap* tileMap;

	std::vector<glm::ivec2> trajectoryPoints;
	int currentStep;
};