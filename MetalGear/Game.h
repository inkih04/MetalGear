#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "Scene.h"
#include "MenuScreen.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Game
{
public:
	Game() {}

	static Game& instance()
	{
		static Game G;
		return G;
	}

	void init();
	bool update(int deltaTime);
	void render(int width, int height);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	void getMousePosition(int& x, int& y) const; 
	void setWindowSize(int width, int height);

private:
	bool bPlay;
	Scene scene;
	MenuScreen menuScreen;
	bool keys[1024];
	int mouseX, mouseY;
	bool sceneInitialized;
	int windowWidth, windowHeight;
};

#endif // _GAME_INCLUDE