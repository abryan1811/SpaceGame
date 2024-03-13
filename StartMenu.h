#include "raylib.h"

enum MenuOption{
    START_GAME,
    QUIT_GAME
};

class GameMenu {
public:
    GameMenu();
    void Update();
    void Draw();
    bool IsGameStartSelected() const;
    bool IsGameQuitSelected() const;

    private:
    MenuOption selectedOption;
};