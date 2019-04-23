#ifndef DRAW_H
#define DRAW_H

#include "logic.h"

void prepSprites(void);

void readySprites(void);

void inGame(AppState *state);

// This function will be used to draw everything about the state of your app
// including the background and whatnot.
void fullDrawAppState(AppState *state);

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state);

char* itoa(int, char* , int);

#endif
