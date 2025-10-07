#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program, int id)
{
	TileMap *map = new TileMap(levelFile, minCoords, program, id);
	
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program, int id)
{
	tileIds = {3,4,5,6,7,9,10,11,12,13,14,17,21,22,24,25,26,27,28,29,
			  33,34,37,39,40,41,42,44,45,46,47,51,52,54,55,56,57,59,
			  63,64,67,69,70,71,72,74,75,76,81,82,83,84,85,86,87,88,89,
			  90,91,92,93,99,101,102,103,104,105,106,107,108,109,110,111,116,
			  124,125,126,132,133,134,135,136,137,141,142,
			  154,155,156,165,166,168,169,170,
			  184,185,186,187,189,198,199,200,201,202,203,204,205,206,207,208,209,
			  211,212,217,219,228,229,230,231,232,233,234,235,236,237,238,239,
			  241,242,256,258,259,260,261,262,263,264,265,266,267,268,269,271,272,
			  282,283,284,293,294,295,296,297,298,299,301,302,312,313,314,334,335,336,
			  316,318,319,320,321,322,325,327,360,361,363,366,390,391,392,394,
	};
	this->id = id;
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * nTiles);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string& levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;

	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;

	getline(fin, line);
	sstream.clear(); sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;

	getline(fin, line);
	sstream.clear(); sstream.str(line);
	sstream >> tileSize >> blockSize;

	getline(fin, line);
	sstream.clear(); sstream.str(line);
	sstream >> tilesheetFile;

	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);

	getline(fin, line);
	sstream.clear(); sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	map = new int[mapSize.x * mapSize.y];


	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			int value;
			fin >> value;   
			map[j * mapSize.x + i] = value;
		}
	}

	fin.close();
	return true;
}


void TileMap::prepareArrays(const glm::vec2& minCoords, ShaderProgram& program)
{
	int tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	nTiles = 0;
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());

	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];

			nTiles++;
			posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);

			texCoordTile[0] = glm::vec2(
				float(tile % tilesheetSize.x) / tilesheetSize.x,
				float(tile / tilesheetSize.x) / tilesheetSize.y
			);
			texCoordTile[1] = texCoordTile[0] + tileTexSize;
			texCoordTile[1] -= halfTexel;

			vertices.push_back(posTile.x); vertices.push_back(posTile.y);
			vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
			vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
			vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
			vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
			vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);

			vertices.push_back(posTile.x); vertices.push_back(posTile.y);
			vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
			vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
			vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
			vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
			vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}



// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		if(map[y*mapSize.x+x] != 0)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		if(map[y*mapSize.x+x] != 0)
			return true;
	}
	
	return false;
}


bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;
	
	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for(int x=x0; x<=x1; x++)
	{
		if(map[y*mapSize.x+x] != 0)
		{
			if(*posY - tileSize * y + size.y <= 4)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}
	
	return false;
}

bool TileMap::isOutLeft(const glm::ivec2& pos) const
{
	return pos.x < 0;
}

bool TileMap::isOutRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	//cout << "is Out right" << endl;
	int mapWidthPixels = mapSize.x * tileSize;
	return pos.x + size.x > mapWidthPixels;
}

bool TileMap::isOutTop(const glm::ivec2& pos) const
{
	return pos.y < 0;
}

bool TileMap::isOutBottom(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int mapHeightPixels = mapSize.y * tileSize;
	return pos.y + size.y > mapHeightPixels;
}

bool TileMap::checkTileCollision(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0 = pos.x / tileSize;
	int x1 = (pos.x + size.x - 1) / tileSize;
	int y = (pos.y + size.y - 1) / tileSize;  

	if (x0 < 0 || x1 >= mapSize.x || y < 0 || y >= mapSize.y)
		return false;

	for (int x = x0; x <= x1; x++)
	{
		int currentTile = map[y * mapSize.x + x];

		for (int i = 0; i < tileIds.size(); i++)
		{
			if (currentTile == tileIds[i])
				return true;
		}
	}

	return false;
}

bool TileMap::checkChangeMap(const glm::ivec2& pos, const glm::ivec2& size, vector<int> tile) const
{
	int x0 = pos.x / tileSize;
	int x1 = (pos.x + size.x - 1) / tileSize;
	int y = (pos.y + size.y - 1) / tileSize;

	if (x0 < 0 || x1 >= mapSize.x || y < 0 || y >= mapSize.y)
		return false;
	for (int x = x0; x <= x1; x++)
	{
		int currentTile = map[y * mapSize.x + x];
		for (int i = 0; i < tile.size(); i++)
		{
			if (currentTile == tile[i])
				return true;
		}
	}
	return false;
}


























