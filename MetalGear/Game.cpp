#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "AudioManager.h"

void Game::init()
{
	bPlay = true;
	sceneInitialized = false;
	mouseX = 0;
	mouseY = 0;
	windowWidth = SCREEN_WIDTH;
	windowHeight = SCREEN_HEIGHT;

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	AudioManager::instance().init();

	// Initialize menu screen
	menuScreen.init();

	AudioManager::instance().playMusic("music_menu", true);
}

bool Game::update(int deltaTime)
{
	MenuState currentState = menuScreen.getCurrentState();

	static MenuState previousState = MenuState::MAIN_MENU;

	if (currentState == MenuState::PLAYING) {
		if (!sceneInitialized) {
			scene.init();
			sceneInitialized = true;
			// La música del mapa se iniciará en Scene::init()
		}
		scene.update(deltaTime);
	}
	else {
		// Si volvemos al menú desde el juego, reproducir música del menú
		if (previousState == MenuState::PLAYING && currentState != MenuState::PLAYING) {
			AudioManager::instance().playMusic("music_menu", true);
		}

		menuScreen.update(deltaTime, mouseX, mouseY);
	}

	previousState = currentState;

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
		MenuState currentState = menuScreen.getCurrentState();

		// Si estamos en game over, no hacer nada con ESC
		if (currentState == MenuState::PLAYING && scene.isGameOver()) {
			// No permitir salir con ESC durante game over
			return;
		}

		if (currentState == MenuState::PLAYING) {
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

		if (currentState == MenuState::PLAYING) {
			if (scene.isGameOver()) {
				float scaleX = 240.0f / float(SCREEN_WIDTH);
				float scaleY = 160.0f / float(SCREEN_HEIGHT);

				int gameMouseX = int(mouseX * scaleX);
				int gameMouseY = int(mouseY * scaleY);

				int result = scene.handleMouseClick(gameMouseX, gameMouseY);

				if (result == 1) {
					// Continue - la música se reiniciará en Scene::resetGame()
					std::cout << "Restarting game..." << std::endl;
				}
				else if (result == 2) {
					// Exit - volver al menú principal
					std::cout << "Returning to main menu..." << std::endl;
					menuScreen.setCurrentState(MenuState::MAIN_MENU);
					sceneInitialized = false;

					// Reproducir música del menú
					AudioManager::instance().playMusic("music_menu", true);
				}
			}
		}
		else {
			menuScreen.handleClick(mouseX, mouseY);
			if (menuScreen.shouldExit()) {
				bPlay = false;
				AudioManager::instance().cleanup();
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

void Game::getMousePosition(int& x, int& y) const
{
	// Escalar las coordenadas del mouse al tamaño del juego (240x160)
	float scaleX = 240.0f / float(SCREEN_WIDTH);
	float scaleY = 160.0f / float(SCREEN_HEIGHT);

	x = int(mouseX * scaleX);
	y = int(mouseY * scaleY);
}

void Game::setWindowSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}