#include "WinScreen.h"
#include <iostream>

#define GAME_WIDTH 240.0f
#define GAME_HEIGHT 160.0f

// Posiciones de los botones - ajusta estos valores según necesites
#define NEW_GAME_BUTTON_X 0.0f
#define NEW_GAME_BUTTON_Y 60.0f
#define EXIT_BUTTON_X 150.0f
#define EXIT_BUTTON_Y 60.0f

// Tamaños de los botones - ajusta estos valores según necesites
#define NEW_GAME_BUTTON_WIDTH 90.0f
#define NEW_GAME_BUTTON_HEIGHT 30.0f
#define EXIT_BUTTON_WIDTH 90.0f
#define EXIT_BUTTON_HEIGHT 30.0f

WinScreen::WinScreen()
{
    backgroundSprite = nullptr;
    newGameSprite = nullptr;
    exitSprite = nullptr;
    newGameHovered = false;
    exitHovered = false;
}

WinScreen::~WinScreen()
{
    if (backgroundSprite != nullptr)
        delete backgroundSprite;
    if (newGameSprite != nullptr)
        delete newGameSprite;
    if (exitSprite != nullptr)
        delete exitSprite;
}

void WinScreen::init(ShaderProgram& shaderProgram)
{
    std::cout << "WinScreen::init() START" << std::endl;

    // Cargar texturas
    std::cout << "Loading win_screen.jpg..." << std::endl;
    if (!backgroundTexture.loadFromFile("screens/win_screen.jpg", TEXTURE_PIXEL_FORMAT_RGBA))
    {
        std::cout << "ERROR: Failed to load screens/win_screen.jpg" << std::endl;
        // Intenta cargar como PNG si JPG falla
        if (!backgroundTexture.loadFromFile("screens/win_screen.png", TEXTURE_PIXEL_FORMAT_RGBA))
        {
            std::cout << "ERROR: Failed to load screens/win_screen.png too!" << std::endl;
            return;
        }
        else
        {
            std::cout << "Loaded win_screen.png successfully" << std::endl;
        }
    }
    else
    {
        std::cout << "Loaded win_screen.jpg successfully" << std::endl;
    }

    std::cout << "Loading new_game.png..." << std::endl;
    if (!newGameTexture.loadFromFile("labels/new_game.png", TEXTURE_PIXEL_FORMAT_RGBA))
    {
        std::cout << "ERROR: Failed to load labels/new_game.png" << std::endl;
        return;
    }
    else
    {
        std::cout << "Loaded new_game.png successfully" << std::endl;
    }

    std::cout << "Loading exit_game_win.png..." << std::endl;
    if (!exitTexture.loadFromFile("labels/exit_game_win.png", TEXTURE_PIXEL_FORMAT_RGBA))
    {
        std::cout << "ERROR: Failed to load labels/exit_game_win.png" << std::endl;
        return;
    }
    else
    {
        std::cout << "Loaded exit_game_win.png successfully" << std::endl;
    }

    std::cout << "Creating background sprite..." << std::endl;
    // Crear sprite de fondo
    backgroundSprite = Sprite::createSprite(glm::ivec2(GAME_WIDTH, GAME_HEIGHT),
        glm::vec2(1.0f, 1.0f),
        &backgroundTexture, &shaderProgram);

    if (backgroundSprite == nullptr)
    {
        std::cout << "ERROR: Failed to create background sprite" << std::endl;
        return;
    }

    backgroundSprite->setPosition(glm::vec2(0.0f, 0.0f));
    std::cout << "Background sprite created successfully" << std::endl;

    // Configurar tamaños de botones
    newGameButtonSize = glm::vec2(NEW_GAME_BUTTON_WIDTH, NEW_GAME_BUTTON_HEIGHT);
    exitButtonSize = glm::vec2(EXIT_BUTTON_WIDTH, EXIT_BUTTON_HEIGHT);

    std::cout << "Creating new game sprite..." << std::endl;
    // Crear sprite de New Game
    newGameSprite = Sprite::createSprite(newGameButtonSize,
        glm::vec2(1.0f, 1.0f),
        &newGameTexture, &shaderProgram);

    if (newGameSprite == nullptr)
    {
        std::cout << "ERROR: Failed to create newGame sprite" << std::endl;
        return;
    }

    newGameButtonPos = glm::vec2(NEW_GAME_BUTTON_X, NEW_GAME_BUTTON_Y);
    newGameSprite->setPosition(newGameButtonPos);
    std::cout << "New game sprite created successfully" << std::endl;

    std::cout << "Creating exit sprite..." << std::endl;
    // Crear sprite de Exit
    exitSprite = Sprite::createSprite(exitButtonSize,
        glm::vec2(1.0f, 1.0f),
        &exitTexture, &shaderProgram);

    if (exitSprite == nullptr)
    {
        std::cout << "ERROR: Failed to create exit sprite" << std::endl;
        return;
    }

    exitButtonPos = glm::vec2(EXIT_BUTTON_X, EXIT_BUTTON_Y);
    exitSprite->setPosition(exitButtonPos);
    std::cout << "Exit sprite created successfully" << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "WinScreen initialized SUCCESSFULLY" << std::endl;
    std::cout << "Background sprite: " << (backgroundSprite != nullptr ? "OK" : "NULL") << std::endl;
    std::cout << "NewGame sprite: " << (newGameSprite != nullptr ? "OK" : "NULL") << std::endl;
    std::cout << "Exit sprite: " << (exitSprite != nullptr ? "OK" : "NULL") << std::endl;
    std::cout << "New Game button at: (" << newGameButtonPos.x << ", " << newGameButtonPos.y
        << ") size: (" << newGameButtonSize.x << ", " << newGameButtonSize.y << ")" << std::endl;
    std::cout << "Exit button at: (" << exitButtonPos.x << ", " << exitButtonPos.y
        << ") size: (" << exitButtonSize.x << ", " << exitButtonSize.y << ")" << std::endl;
    std::cout << "========================================" << std::endl;
}

void WinScreen::update(int deltaTime, int mouseX, int mouseY)
{
    // Actualizar estados de hover
    newGameHovered = isMouseOverNewGame(mouseX, mouseY);
    exitHovered = isMouseOverExit(mouseX, mouseY);
}

void WinScreen::render(ShaderProgram& shaderProgram)
{
    // Verificar que los sprites estén inicializados antes de renderizar
    if (backgroundSprite == nullptr || newGameSprite == nullptr || exitSprite == nullptr)
    {
        std::cout << "ERROR: WinScreen sprites not initialized!" << std::endl;
        return;
    }

    // Renderizar fondo
    shaderProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
    backgroundSprite->render();

    // Renderizar botón New Game con efecto hover
    shaderProgram.setUniform4f("color",
        newGameHovered ? 1.2f : 1.0f,
        newGameHovered ? 1.2f : 1.0f,
        newGameHovered ? 1.2f : 1.0f,
        1.0f);
    newGameSprite->render();

    // Renderizar botón Exit con efecto hover
    shaderProgram.setUniform4f("color",
        exitHovered ? 1.2f : 1.0f,
        exitHovered ? 1.2f : 1.0f,
        exitHovered ? 1.2f : 1.0f,
        1.0f);
    exitSprite->render();
}

bool WinScreen::isMouseOverNewGame(int mouseX, int mouseY)
{
    return (mouseX >= newGameButtonPos.x &&
        mouseX <= newGameButtonPos.x + newGameButtonSize.x &&
        mouseY >= newGameButtonPos.y &&
        mouseY <= newGameButtonPos.y + newGameButtonSize.y);
}

bool WinScreen::isMouseOverExit(int mouseX, int mouseY)
{
    return (mouseX >= exitButtonPos.x &&
        mouseX <= exitButtonPos.x + exitButtonSize.x &&
        mouseY >= exitButtonPos.y &&
        mouseY <= exitButtonPos.y + exitButtonSize.y);
}

int WinScreen::checkButtonClick(int mouseX, int mouseY)
{
    std::cout << "Checking click at: (" << mouseX << ", " << mouseY << ")" << std::endl;

    if (isMouseOverNewGame(mouseX, mouseY))
    {
        std::cout << "New Game button clicked!" << std::endl;
        return 1; // Código para reiniciar juego
    }
    else if (isMouseOverExit(mouseX, mouseY))
    {
        std::cout << "Exit button clicked!" << std::endl;
        return 2; // Código para volver al menú principal
    }

    return 0; // No se hizo clic en ningún botón
}