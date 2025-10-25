#include "MenuScreen.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

MenuScreen::MenuScreen() {
    currentState = MenuState::MAIN_MENU;
    backgroundSprite = nullptr;
    controlsSprite = nullptr;
    creditsSprite = nullptr;
    exitRequested = false;
}

MenuScreen::~MenuScreen() {
    if (backgroundSprite != nullptr) delete backgroundSprite;
    if (controlsSprite != nullptr) delete controlsSprite;
    if (creditsSprite != nullptr) delete creditsSprite;
    if (startButton.sprite != nullptr) delete startButton.sprite;
    if (controlsButton.sprite != nullptr) delete controlsButton.sprite;
    if (creditsButtonMenu.sprite != nullptr) delete creditsButtonMenu.sprite;
    if (exitButton.sprite != nullptr) delete exitButton.sprite;
    if (backButton.sprite != nullptr) delete backButton.sprite;
}

void MenuScreen::init() {
    initShaders();
    loadTextures();
    createButtons();

    projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
}

void MenuScreen::initShaders() {
    Shader vShader, fShader;
    vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
    if (!vShader.isCompiled()) {
        std::cout << "Vertex Shader Error" << std::endl;
        std::cout << vShader.log() << std::endl;
    }
    fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
    if (!fShader.isCompiled()) {
        std::cout << "Fragment Shader Error" << std::endl;
        std::cout << fShader.log() << std::endl;
    }
    texProgram.init();
    texProgram.addShader(vShader);
    texProgram.addShader(fShader);
    texProgram.link();
    if (!texProgram.isLinked()) {
        std::cout << "Shader Linking Error" << std::endl;
        std::cout << texProgram.log() << std::endl;
    }
    texProgram.bindFragmentOutput("outColor");
    vShader.free();
    fShader.free();
}

void MenuScreen::loadTextures() {
    backgroundTexture.loadFromFile("screens/titulo_provisional.png", TEXTURE_PIXEL_FORMAT_RGBA);
    backgroundSprite = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT),
        glm::vec2(1.f, 1.f), &backgroundTexture, &texProgram);
    backgroundSprite->setPosition(glm::vec2(0.f, 0.f));


    controlsTexture.loadFromFile("screens/controls_screen.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
    controlsSprite = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT),
        glm::vec2(1.f, 1.f), &controlsTexture, &texProgram);
    controlsSprite->setPosition(glm::vec2(0.f, 0.f));

  
    creditsTexture.loadFromFile("screens/credits_screen.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
    creditsSprite = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT),
        glm::vec2(1.f, 1.f), &creditsTexture, &texProgram);
    creditsSprite->setPosition(glm::vec2(0.f, 0.f));
}

void MenuScreen::createButtons() {

    float centerX = SCREEN_WIDTH / 2.f;
    float startY = SCREEN_HEIGHT / 2.f;

 
    startTexture.loadFromFile("labels/start_game.png", TEXTURE_PIXEL_FORMAT_RGBA);
    controlsTexBtn.loadFromFile("labels/controls.png", TEXTURE_PIXEL_FORMAT_RGBA);
    creditsTexBtn.loadFromFile("labels/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
    exitTexture.loadFromFile("labels/exit_game.png", TEXTURE_PIXEL_FORMAT_RGBA);
    backTexture.loadFromFile("labels/back.png", TEXTURE_PIXEL_FORMAT_RGBA);


    startButton.sprite = Sprite::createSprite(glm::ivec2(200, 60), glm::vec2(1.f, 1.f),
        &startTexture, &texProgram);
    startButton.position = glm::vec2(centerX - 100, startY);
    startButton.size = glm::vec2(200, 60);
    startButton.hovered = false;


    controlsButton.sprite = Sprite::createSprite(glm::ivec2(180, 50), glm::vec2(1.f, 1.f),
        &controlsTexBtn, &texProgram);
    controlsButton.position = glm::vec2(centerX - 90, startY + 70);
    controlsButton.size = glm::vec2(180, 50);
    controlsButton.hovered = false;


    creditsButtonMenu.sprite = Sprite::createSprite(glm::ivec2(180, 50), glm::vec2(1.f, 1.f),
        &creditsTexBtn, &texProgram);
    creditsButtonMenu.position = glm::vec2(centerX - 90, startY + 130);
    creditsButtonMenu.size = glm::vec2(180, 50);
    creditsButtonMenu.hovered = false;

 
    exitButton.sprite = Sprite::createSprite(glm::ivec2(120, 40), glm::vec2(1.f, 1.f),
        &exitTexture, &texProgram);
    exitButton.position = glm::vec2(centerX - 60, startY + 190);
    exitButton.size = glm::vec2(120, 40);
    exitButton.hovered = false;

  
    backButton.sprite = Sprite::createSprite(glm::ivec2(150, 45), glm::vec2(1.f, 1.f),
        &backTexture, &texProgram);
    backButton.position = glm::vec2(centerX - 75, SCREEN_HEIGHT - 45);
    backButton.size = glm::vec2(150, 45);
    backButton.hovered = false;
}

void MenuScreen::update(int deltaTime, int mouseX, int mouseY) {
    if (currentState == MenuState::MAIN_MENU) {
        startButton.hovered = isPointInButton(mouseX, mouseY, startButton);
        controlsButton.hovered = isPointInButton(mouseX, mouseY, controlsButton);
        creditsButtonMenu.hovered = isPointInButton(mouseX, mouseY, creditsButtonMenu);
        exitButton.hovered = isPointInButton(mouseX, mouseY, exitButton);
    }
    else if (currentState == MenuState::CONTROLS || currentState == MenuState::CREDITS) {
        backButton.hovered = isPointInButton(mouseX, mouseY, backButton);
    }
}

void MenuScreen::render() {
    glm::mat4 modelview = glm::mat4(1.0f);

    texProgram.use();
    texProgram.setUniformMatrix4f("projection", projection);
    texProgram.setUniformMatrix4f("modelview", modelview);
    texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

    renderBackground();
    renderButtons();
}

void MenuScreen::renderBackground() {
    if (currentState == MenuState::MAIN_MENU) {
        texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
        backgroundSprite->render();
    }
    else if (currentState == MenuState::CONTROLS) {
        texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
        controlsSprite->render();
    }
    else if (currentState == MenuState::CREDITS) {
        texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
        creditsSprite->render();
    }
}

void MenuScreen::renderButtons() {
    if (currentState == MenuState::MAIN_MENU) {

        texProgram.setUniform4f("color", startButton.hovered ? 1.2f : 1.0f,
            startButton.hovered ? 1.2f : 1.0f,
            startButton.hovered ? 1.2f : 1.0f, 1.0f);
        startButton.sprite->setPosition(startButton.position);
        startButton.sprite->render();

        texProgram.setUniform4f("color", controlsButton.hovered ? 1.2f : 1.0f,
            controlsButton.hovered ? 1.2f : 1.0f,
            controlsButton.hovered ? 1.2f : 1.0f, 1.0f);
        controlsButton.sprite->setPosition(controlsButton.position);
        controlsButton.sprite->render();

        texProgram.setUniform4f("color", creditsButtonMenu.hovered ? 1.2f : 1.0f,
            creditsButtonMenu.hovered ? 1.2f : 1.0f,
            creditsButtonMenu.hovered ? 1.2f : 1.0f, 1.0f);
        creditsButtonMenu.sprite->setPosition(creditsButtonMenu.position);
        creditsButtonMenu.sprite->render();

        texProgram.setUniform4f("color", exitButton.hovered ? 1.2f : 1.0f,
            exitButton.hovered ? 1.2f : 1.0f,
            exitButton.hovered ? 1.2f : 1.0f, 1.0f);
        exitButton.sprite->setPosition(exitButton.position);
        exitButton.sprite->render();
    }
    else if (currentState == MenuState::CONTROLS || currentState == MenuState::CREDITS) {
        texProgram.setUniform4f("color", backButton.hovered ? 1.2f : 1.0f,
            backButton.hovered ? 1.2f : 1.0f,
            backButton.hovered ? 1.2f : 1.0f, 1.0f);
        backButton.sprite->setPosition(backButton.position);
        backButton.sprite->render();
    }
}

void MenuScreen::handleClick(int mouseX, int mouseY) {
    if (currentState == MenuState::MAIN_MENU) {
        if (isPointInButton(mouseX, mouseY, startButton)) {
            currentState = MenuState::PLAYING;
        }
        else if (isPointInButton(mouseX, mouseY, controlsButton)) {
            currentState = MenuState::CONTROLS;
        }
        else if (isPointInButton(mouseX, mouseY, creditsButtonMenu)) {
            currentState = MenuState::CREDITS;
        }
        else if (isPointInButton(mouseX, mouseY, exitButton)) {
            exitRequested = true;
        }
    }
    else if (currentState == MenuState::CONTROLS || currentState == MenuState::CREDITS) {
        if (isPointInButton(mouseX, mouseY, backButton)) {
            currentState = MenuState::MAIN_MENU;
        }
    }
}

bool MenuScreen::isPointInButton(int x, int y, const MenuButton& button) {
    return x >= button.position.x && x <= button.position.x + button.size.x &&
        y >= button.position.y && y <= button.position.y + button.size.y;
}