#ifndef _WIN_SCREEN_INCLUDE
#define _WIN_SCREEN_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"
#include "Texture.h"
#include "ShaderProgram.h"

class WinScreen
{
public:
    WinScreen();
    ~WinScreen();

    void init(ShaderProgram& shaderProgram);
    void update(int deltaTime, int mouseX, int mouseY);
    void render(ShaderProgram& shaderProgram);

    bool isMouseOverNewGame(int mouseX, int mouseY);
    bool isMouseOverExit(int mouseX, int mouseY);
    int checkButtonClick(int mouseX, int mouseY);

private:
    Texture backgroundTexture;
    Texture newGameTexture;
    Texture exitTexture;

    Sprite* backgroundSprite;
    Sprite* newGameSprite;
    Sprite* exitSprite;

    glm::vec2 newGameButtonPos;
    glm::vec2 exitButtonPos;
    glm::vec2 newGameButtonSize;
    glm::vec2 exitButtonSize;

    bool newGameHovered;
    bool exitHovered;
};

#endif // _WIN_SCREEN_INCLUDE
