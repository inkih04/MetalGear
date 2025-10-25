#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE

#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include <vector>
#include <unordered_set>
#include "ChangeMap.h"
#include "Item.h"
#include <iostream>

// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.

class Enemy;

class TileMap
{
private:
	TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program, int id, vector<ChangeMap> changeMap, vector<int> changeBorders);

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap* createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program, int id, vector<ChangeMap> changeMap, vector<int>changeBorders);
	~TileMap();

	enum Border {
		LEFT, RIGHT, TOP, BOTTOM
	};
	void render() const;
	void free();

	int getTileSize() const { return tileSize; }
	glm::ivec2 getMapSize() const { return mapSize; }  

	bool checkCollisionEnemyPlayer(const glm::ivec2& playerPos, const glm::ivec2& playerSize) const;
	void doDamegeToEnemies(const glm::ivec2& playerPos, const glm::ivec2& playerSize, int damage);
	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool isOutLeft(const glm::ivec2& pos) const;
	bool isOutRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool isOutTop(const glm::ivec2& pos) const;
	bool isOutBottom(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool checkTileCollision(const glm::ivec2& pos, const glm::ivec2& size, bool isPlayer) const;
	bool checkCollisionWithATile(const glm::ivec2& pos, const glm::ivec2& size, int tile) const;
	bool canPunchEnemies(const glm::ivec2& playerPos, const glm::ivec2& playerSize) const;
	void doPunchDamageToEnemies(const glm::ivec2& playerPos, const glm::ivec2& playerSize, int damage);
	int getTileAt(int x, int y);
	int getId() const { return id; }
	int changeMapIfNeeded(const glm::ivec2& pos, const glm::ivec2& size, glm::ivec2& newPos) const;
	bool checkItemCollision(const glm::ivec2& playerPos, const glm::ivec2& playerSize)const;
	Item* getItemAt(const glm::ivec2& playerPos, const glm::ivec2& playerSize) const;
	void addEnemy(Enemy* enemy);
	void addItem(Item* item) { items.push_back(item); }
	void updateEnemies(int deltaTime, const glm::ivec2& playerPos);
	std::unordered_set<int> getBlockTileIds() const { return tileIds;}




private:
	bool loadLevel(const string& levelFile);
	void prepareArrays(const glm::vec2& minCoords, ShaderProgram& program);

private:
	vector<Item*> items;
	vector<Enemy*> enemies;
	int id;
	vector<int> changeMapBorders; 
	vector<ChangeMap> changeMapTile; 
	std::unordered_set<int> tileIds;
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int nTiles;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int* map;
};

#endif // _TILE_MAP_INCLUDE