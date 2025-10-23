#include "GameOverScreen.h"
#include <iostream>

// Resolución de referencia del juego
#define GAME_WIDTH 240.0f
#define GAME_HEIGHT 160.0f

// Posiciones configurables de los botones (ajusta estos valores según necesites)
// Estas coordenadas son relativas al tamaño del juego (240x160)
#define CONTINUE_BUTTON_X 45.0f
#define CONTINUE_BUTTON_Y 80.0f
#define EXIT_BUTTON_X 140.0f
#define EXIT_BUTTON_Y 80.0f

// Tamaños de los botones
#define CONTINUE_BUTTON_WIDTH 75.0f
#define CONTINUE_BUTTON_HEIGHT 10.0f
#define EXIT_BUTTON_WIDTH 50.0f
#define EXIT_BUTTON_HEIGHT 10.0f

GameOverScreen::GameOverScreen()
{
    backgroundSprite = nullptr;
    continueSprite = nullptr;
    exitSprite = nullptr;
    continueHovered = false;
    exitHovered = false;
}

GameOverScreen::~GameOverScreen()
{
    if (backgroundSprite != nullptr)
        delete backgroundSprite;
    if (continueSprite != nullptr)
        delete continueSprite;
    if (exitSprite != nullptr)
        delete exitSprite;
}

void GameOverScreen::init(ShaderProgram& shaderProgram)
{
    // Cargar texturas
    backgroundTexture.loadFromFile("screens/game_over.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
    continueTexture.loadFromFile("labels/continue.png", TEXTURE_PIXEL_FORMAT_RGBA);
    exitTexture.loadFromFile("labels/exit.png", TEXTURE_PIXEL_FORMAT_RGBA);

    // Crear sprite del fondo (pantalla completa del juego)
    backgroundSprite = Sprite::createSprite(glm::ivec2(GAME_WIDTH, GAME_HEIGHT),
        glm::vec2(1.0f, 1.0f),
        &backgroundTexture, &shaderProgram);
    backgroundSprite->setPosition(glm::vec2(0.0f, 0.0f));

    // Tamaños de los botones
    continueButtonSize = glm::vec2(CONTINUE_BUTTON_WIDTH, CONTINUE_BUTTON_HEIGHT);
    exitButtonSize = glm::vec2(EXIT_BUTTON_WIDTH, EXIT_BUTTON_HEIGHT);

    // Crear sprite del botón continuar
    continueSprite = Sprite::createSprite(continueButtonSize,
        glm::vec2(1.0f, 1.0f),
        &continueTexture, &shaderProgram);
    continueButtonPos = glm::vec2(CONTINUE_BUTTON_X, CONTINUE_BUTTON_Y);
    continueSprite->setPosition(continueButtonPos);

    // Crear sprite del botón salir
    exitSprite = Sprite::createSprite(exitButtonSize,
        glm::vec2(1.0f, 1.0f),
        &exitTexture, &shaderProgram);
    exitButtonPos = glm::vec2(EXIT_BUTTON_X, EXIT_BUTTON_Y);
    exitSprite->setPosition(exitButtonPos);

    std::cout << "GameOverScreen initialized" << std::endl;
    std::cout << "Continue button at: (" << continueButtonPos.x << ", " << continueButtonPos.y
        << ") size: (" << continueButtonSize.x << ", " << continueButtonSize.y << ")" << std::endl;
    std::cout << "Exit button at: (" << exitButtonPos.x << ", " << exitButtonPos.y
        << ") size: (" << exitButtonSize.x << ", " << exitButtonSize.y << ")" << std::endl;
}

void GameOverScreen::update(int deltaTime, int mouseX, int mouseY)
{
    // Actualizar estados de hover
    continueHovered = isMouseOverContinue(mouseX, mouseY);
    exitHovered = isMouseOverExit(mouseX, mouseY);
}

void GameOverScreen::render(ShaderProgram& shaderProgram)
{
    // Renderizar fondo
    shaderProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
    backgroundSprite->render();

    // Renderizar botón continuar con efecto hover
    shaderProgram.setUniform4f("color",
        continueHovered ? 1.2f : 1.0f,
        continueHovered ? 1.2f : 1.0f,
        continueHovered ? 1.2f : 1.0f,
        1.0f);
    continueSprite->render();

    // Renderizar botón salir con efecto hover
    shaderProgram.setUniform4f("color",
        exitHovered ? 1.2f : 1.0f,
        exitHovered ? 1.2f : 1.0f,
        exitHovered ? 1.2f : 1.0f,
        1.0f);
    exitSprite->render();
}

bool GameOverScreen::isMouseOverContinue(int mouseX, int mouseY)
{
    return (mouseX >= continueButtonPos.x &&
        mouseX <= continueButtonPos.x + continueButtonSize.x &&
        mouseY >= continueButtonPos.y &&
        mouseY <= continueButtonPos.y + continueButtonSize.y);
}

bool GameOverScreen::isMouseOverExit(int mouseX, int mouseY)
{
    return (mouseX >= exitButtonPos.x &&
        mouseX <= exitButtonPos.x + exitButtonSize.x &&
        mouseY >= exitButtonPos.y &&
        mouseY <= exitButtonPos.y + exitButtonSize.y);
}

int GameOverScreen::checkButtonClick(int mouseX, int mouseY)
{
    std::cout << "Checking click at: (" << mouseX << ", " << mouseY << ")" << std::endl;

    if (isMouseOverContinue(mouseX, mouseY))
    {
        std::cout << "Continue button clicked!" << std::endl;
        return 1; // Continuar
    }
    else if (isMouseOverExit(mouseX, mouseY))
    {
        std::cout << "Exit button clicked!" << std::endl;
        return 2; // Salir
    }

    return 0; // Ninguno
}