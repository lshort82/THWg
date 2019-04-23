#ifndef LOGIC_H
#define LOGIC_H

#include "gba.h"

typedef struct {
    // Store whether or not the game is over in this member:
    int gameOver;
    int inGame;
    int won;
    int level;
} AppState;

typedef struct {
    int direction; //0 = down, 1 = up
    int leftx;
    int rightx;
    int topy;
    int bottomy;
    const u16 *image;
} Enemy;

void initializeEnemy(Enemy *enemy, int x, int y);

// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

#endif
