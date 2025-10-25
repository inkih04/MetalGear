#ifndef _GAME_OVER_SCREEN_INCLUDE
#define _GAME_OVER_SCREEN_INCLUDE

#include "Sprite.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>

class GameOverScreen
{
public:
    GameOverScreen();
    ~GameOverScreen();

    void init(ShaderProgram& shaderProgram);
    void update(int deltaTime, int mouseX, int mouseY); 
    void render(ShaderProgram& shaderProgram); 

    bool isMouseOverContinue(int mouseX, int mouseY);
    bool isMouseOverExit(int mouseX, int mouseY);
    int checkButtonClick(int mouseX, int mouseY);

private:
    Texture backgroundTexture;
    Texture continueTexture;
    Texture exitTexture;

    Sprite* backgroundSprite;
    Sprite* continueSprite;
    Sprite* exitSprite;

    glm::vec2 continueButtonPos;
    glm::vec2 continueButtonSize;
    glm::vec2 exitButtonPos;
    glm::vec2 exitButtonSize;

    // Estados de hover
    bool continueHovered;
    bool exitHovered;
};

#endif // _GAME_OVER_SCREEN_INCLUDE