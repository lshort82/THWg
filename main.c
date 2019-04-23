#include "gba.h"
#include "logic.h"
#include "draw.h"
#include "images/sprites.h"
#include "images/garbage.h"
#include "images/techtower.h"
#include "images/buzz.h"


#include <stdio.h>
#include <stdlib.h>
// AppState enum definition
typedef enum {
    // TA-TODO: Add any additional states you need for your app.
    START,
    START_NODRAW,
    APP_INIT,
    APP,
    APP_EXIT,
    APP_EXIT_NODRAW,
} GBAState;

int main(void) {

    REG_DISPCNT = MODE3 | BG2_ENABLE | OBJ_ENABLE | SPRITES_DIMENSION_TYPE;
    GBAState state = START;

    // We store the "previous" and "current" states.
    AppState currentAppState;

    // We store the current and previous values of the button input.
    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;
    prepSprites();

    while (1) {
        // Load the current state of the buttons
        currentButtons = BUTTONS;

        // TA-TODO: Manipulate the state machine below as needed.
        switch(state) {
            case START:
                // Wait for VBlank
                waitForVBlank();

                drawFullScreenImageDMA(techtower);
                state = START_NODRAW;
                break;
            case START_NODRAW:

                // Start the app by switching the state to APP_INIT.
                if (KEY_JUST_PRESSED(BUTTON_START, BUTTONS, previousButtons)) {
                    state = APP_INIT;
                }
                break;
            case APP_INIT:
                // Initialize the app. Switch to the APP state.
                initializeAppState(&currentAppState);
                // Draw the initial state of the app
                readySprites();


                state = APP;
                break;
            case APP:
                // Process the app for one frame, store the next state

                // Wait for VBlank before we do any drawing.
                waitForVBlank();
                fullDrawAppState(&currentAppState);
                // Undraw the previous state
                //undrawAppState(&currentAppState);

                // Draw the current state
                //drawAppState(&nextAppState);
                // Now set the current state as the next state for the next iter.
                waitForVBlank();
                inGame(&currentAppState);
                if (currentAppState.won) {
                    state = APP_EXIT;
                    break;
                }
                if (currentAppState.gameOver) {
                    state = APP_INIT;
                    break;
                }
                if (!currentAppState.inGame) {
                    state = START;
                    break;
                }
                state = APP;
                break;
            case APP_EXIT:
                // Wait for VBlank
                waitForVBlank();

                // TA-TODO: Draw the exit / gameover screen
                drawFullScreenImageDMA(buzz);

                state = APP_EXIT_NODRAW;
                break;
            case APP_EXIT_NODRAW:
                // TA-TODO: Check for a button press here to go back to the start screen
                if (KEY_JUST_PRESSED(BUTTON_SELECT, BUTTONS, previousButtons)) {
                     state = START;
                }
                break;
        }

        // Store the current state of the buttons
        previousButtons = currentButtons;
    }

    return 0;
}
