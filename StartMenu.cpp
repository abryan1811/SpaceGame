#include "StartMenu.h"

GameMenu::GameMenu() : selectedOption(START_GAME) {}

void GameMenu::Update() {
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP)){
        selectedOption = (selectedOption == START_GAME) ? QUIT_GAME : START_GAME;
    }
}

void GameMenu::Draw(){
    ClearBackground(BLACK);

    if (selectedOption == START_GAME) {
        DrawText("Start Game", 100, 200, 20, WHITE);
        DrawText("Quit Game", 100, 250, 20, GRAY);
    } else {
        DrawText("Start Game", 100, 200, 20, GRAY);
        DrawText("Quit Game", 100, 250, 20, WHITE);
    }
}

bool GameMenu::IsGameStartSelected() const {
    return selectedOption == START_GAME;
}

bool GameMenu::IsGameQuitSelected() const {
    return selectedOption == QUIT_GAME;
}