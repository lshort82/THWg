#include "logic.h"
#include "gba.h"
#include "images/garbage.h"

void initializeAppState(AppState* appState) {
    appState->gameOver = 0;
    appState->inGame = 1;
    appState->level = 0;
    appState->won = 0;
}

void initializeEnemy(Enemy* enemy, int x, int y) {
    enemy->image = garbage;
    enemy->leftx = x;
    enemy->rightx = x + 16;
    enemy->topy = y;
    enemy->bottomy = y+12;
    enemy->direction = randint(0, 2);
}
