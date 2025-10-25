#ifndef _MENU_SCREEN_INCLUDE
#define _MENU_SCREEN_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"
#include <vector>

enum class MenuState {
    MAIN_MENU,
    CONTROLS,
    CREDITS,
    PLAYING
};

struct MenuButton {
    Sprite* sprite;
    glm::vec2 position;
    glm::vec2 size;
    bool hovered;
};

class MenuScreen {
public:
    MenuScreen();
    ~MenuScreen();

    void init();
    void update(int deltaTime, int mouseX, int mouseY);
    void render();
    void handleClick(int mouseX, int mouseY);

    MenuState getCurrentState() const { return currentState; }
    void setCurrentState(MenuState state) { currentState = state; }
    bool shouldExit() const { return exitRequested; }
    void resetExitRequest() { exitRequested = false; }

private:
    void initShaders();
    void loadTextures();
    void createButtons();
    void renderBackground();
    void renderButtons();
    bool isPointInButton(int x, int y, const MenuButton& button);

    MenuState currentState;
    ShaderProgram texProgram;
    glm::mat4 projection;
    bool exitRequested;

  
    Texture backgroundTexture;
    Sprite* backgroundSprite;

    Texture controlsTexture;
    Sprite* controlsSprite;

    Texture creditsTexture;
    Sprite* creditsSprite;

    
    Texture startTexture;
    Texture controlsTexBtn;
    Texture creditsTexBtn;
    Texture exitTexture;
    Texture backTexture;

    
    MenuButton startButton;
    MenuButton controlsButton;
    MenuButton creditsButtonMenu;
    MenuButton exitButton;

    
    MenuButton backButton;
};

#endif // _MENU_SCREEN_INCLUDE