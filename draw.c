#include "draw.h"
#include "gba.h"
#include "images/sprites.h"
#include "images/garbage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
volatile OamEntry shadow[128];
volatile OamEntry* yellowJacket = &shadow[0];
Enemy enemies[MAX_LEVELS + 1];


/*
* This function prepares the sprites before any gameplay begins
*
*
*/
void prepSprites(void) {
    DMA[3].src = sprites_palette;
    DMA[3].dst = SPRITEPAL;
    DMA[3].cnt = SPRITES_PALETTE_LENGTH | DMA_ON;
    DMA[3].src = sprites;
    DMA[3].dst = &CHARBLOCKBASE[5];
    DMA[3].cnt = SPRITES_LENGTH | DMA_ON;
    for(int i = 0; i < 128; i++) {
        shadow[i].attr0 = ATTR0_HIDE;
    }
}

/*
* This function sets up the sprites before each level
*
*
*/
void readySprites(void) {
    yellowJacket = &shadow[0];
    yellowJacket->attr2 = GATECH_PALETTE_ID | GATECH_ID;
}

/*
* This function sets up the initial appearance of a level
*
*
*/
void fullDrawAppState(AppState *state) {
    fillScreenDMA(WHITE);
    drawRectDMA(220, 0, 20, 160, GOLD);
    char level[10] = "Level: ";
    itoa(state->level, level+7, 10);
    drawString(5, 10, level, BLACK);
    if (state->inGame) {
        yellowJacket->attr0 = 64 | SPRITES_PALETTE_TYPE | GATECH_SPRITE_SHAPE;
        yellowJacket->attr1 = 1 | GATECH_SPRITE_SIZE;
        DMA[3].src = shadow;
        DMA[3].dst = OAMMEM;
        DMA[3].cnt = 128*4 | DMA_ON;
    }
    int x = 32;
    int y = 0;
    for (int i = 0; i < state->level; i++) {
        x += (162/((state->level)+1));
        y += (148/((state->level)+1));
        initializeEnemy(&enemies[i], x, y);
        drawImageDMA(x, y, 16, 12, enemies[i].image);
    }

    if (state->level == 0) {
        drawString(5, 140, "Navigate to the Gold Zone!", BLACK);
    }
    if (state->level == 1) {
        drawString(5, 140, "Avoid the Evil UGA Logos!", BLACK);
    }
}

/*
* Performs all of the actions within a level
*
*
*/
void inGame(AppState *state) {
    int col = 1;
    int row = 64;
    int backwards = 0;
    while (state->inGame) {
        waitForVBlank();
        if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
            state->inGame = 0;
            yellowJacket->attr0 = ATTR0_HIDE;
            DMA[3].src = shadow;
            DMA[3].dst = OAMMEM;
            DMA[3].cnt = 128*4 | DMA_ON;
            return;
        }
        if (KEY_DOWN(BUTTON_RIGHT, BUTTONS)) {
            col++;
            backwards = 0;
        }
        if (KEY_DOWN(BUTTON_LEFT, BUTTONS)) {
            col--;
            backwards = 1;
        }
        if (KEY_DOWN(BUTTON_UP, BUTTONS)) {
            row--;
        }
        if (KEY_DOWN(BUTTON_DOWN, BUTTONS)) {
            row++;
        }
        for (int i = 0; i < state->level; i++) {
            if (enemies[i].direction) {
                if (!(enemies[i].topy)) {
                    enemies[i].direction = 0;
                    enemies[i].topy++;
                    enemies[i].bottomy++;
                } else {
                    enemies[i].topy--;
                    enemies[i].bottomy--;
                }
            } else {
                if ((enemies[i].bottomy) == 160) {
                    enemies[i].direction = 1;
                    enemies[i].topy--;
                    enemies[i].bottomy--;
                } else {
                    enemies[i].topy++;
                    enemies[i].bottomy++;
                }
            }
            drawImageDMA(enemies[i].leftx, enemies[i].topy, 16, 12, enemies[i].image);
            if (enemies[i].direction) {
                drawRectDMA(enemies[i].leftx, enemies[i].bottomy + 1, 16, 1, WHITE);
            } else {
                drawRectDMA(enemies[i].leftx, enemies[i].topy - 1, 16, 1, WHITE);
            }
            if ((col + 3) < enemies[i].rightx && (col+28) > enemies[i].leftx &&
                            (row + 3) < enemies[i].bottomy && (row+28) > enemies[i].topy) {
                yellowJacket->attr0 = ATTR0_HIDE;
                DMA[3].src = shadow;
                DMA[3].dst = OAMMEM;
                DMA[3].cnt = 128*4 | DMA_ON;
                state->gameOver = 1;
                return;
            }
            if (state->level == 0) {
                drawString(5, 140, "Navigate to the Gold Zone!", BLACK);
            }
            if (state->level == 1) {
                drawString(5, 140, "Avoid the Evil UGA Logos!", BLACK);
            }
        }
        yellowJacket->attr0 = row | SPRITES_PALETTE_TYPE | GATECH_SPRITE_SHAPE;
        if (backwards) {
            yellowJacket->attr1 = col | GATECH_SPRITE_SIZE | ATTR1_HFLIP;
        } else {
            yellowJacket->attr1 = col | GATECH_SPRITE_SIZE;
        }
        DMA[3].src = shadow;
        DMA[3].dst = OAMMEM;
        DMA[3].cnt = 128*4 | DMA_ON;
        if ((col < 0) || (row < 0) || (row > 130)) {
            yellowJacket->attr0 = ATTR0_HIDE;
            DMA[3].src = shadow;
            DMA[3].dst = OAMMEM;
            DMA[3].cnt = 128*4 | DMA_ON;
            state->gameOver = 1;
            return;
        }
        if (col > 198) {
            state->level++;
            yellowJacket->attr0 = ATTR0_HIDE;
            DMA[3].src = shadow;
            DMA[3].dst = OAMMEM;
            DMA[3].cnt = 128*4 | DMA_ON;
            if (state->level > MAX_LEVELS) {
                state->won = 1;
            }
            return;
        }

    }
}
