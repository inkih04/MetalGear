#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"

void Game::init()
{
	bPlay = true;
	sceneInitialized = false;
	mouseX = 0;
	mouseY = 0;
	windowWidth = SCREEN_WIDTH;
	windowHeight = SCREEN_HEIGHT;

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	// Initialize menu screen
	menuScreen.init();
}

bool Game::update(int deltaTime)
{
	MenuState currentState = menuScreen.getCurrentState();

	if (currentState == MenuState::PLAYING) {
		if (!sceneInitialized) {
			scene.init();
			sceneInitialized = true;
		}
		scene.update(deltaTime);
	}
	else {
		menuScreen.update(deltaTime, mouseX, mouseY);
	}

	return bPlay;
}

void Game::render(int width, int height)
{
	windowWidth = width;
	windowHeight = height;

	int squareSize = std::min(width, height);

	int viewportX = (width - squareSize) / 2;
	int viewportY = (height - squareSize) / 2;

	glViewport(viewportX, viewportY, squareSize, squareSize);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	MenuState currentState = menuScreen.getCurrentState();
	if (currentState == MenuState::PLAYING) {
		scene.render();
	}
	else {
		menuScreen.render();
	}
}

void Game::keyPressed(int key)
{
	if (key == GLFW_KEY_ESCAPE) {
		if (menuScreen.getCurrentState() == MenuState::PLAYING) {
			menuScreen.setCurrentState(MenuState::MAIN_MENU);
		}
		else {
			bPlay = false;
		}
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	float scaleX = float(SCREEN_WIDTH) / float(windowWidth);
	float scaleY = float(SCREEN_HEIGHT) / float(windowHeight);

	mouseX = int(x * scaleX);
	mouseY = int(y * scaleY);
}

void Game::mousePress(int button)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		MenuState currentState = menuScreen.getCurrentState();

		if (currentState != MenuState::PLAYING) {
			menuScreen.handleClick(mouseX, mouseY);

			if (menuScreen.shouldExit()) {
				bPlay = false;
				menuScreen.resetExitRequest();
			}
		}
	}
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

void Game::setWindowSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}