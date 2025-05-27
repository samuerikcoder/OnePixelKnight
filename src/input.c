#include "libs.h"

static void doKeyDown(SDL_KeyboardEvent *event) {
    if (event->repeat == 0) {
        switch (event->keysym.scancode) {
            case SDL_SCANCODE_LEFT:
                app.left = 1;
                break;
            case SDL_SCANCODE_RIGHT:
                app.right = 1;
                break;
            case SDL_SCANCODE_SPACE:
                if (player.grounded && player.x >= 0) {
                    player.dy = -Y_MOVEMENT;
                    player.grounded = 0;
                    jumpSoundEffect();
                }
                break;
            case SDL_SCANCODE_ESCAPE:
                exit(0);
                break;
            default:
                break;
        }
    }
}

static void doKeyUp(SDL_KeyboardEvent *event) {
    switch (event->keysym.scancode) {
        case SDL_SCANCODE_LEFT:
            app.left = 0;
            break;
        case SDL_SCANCODE_RIGHT:
            app.right = 0;
            break;
        default:
            break;
    }
}

void doInput(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                doKeyDown(&event.key);
                break;
            case SDL_KEYUP:
                doKeyUp(&event.key);
                break;
            default:
                break;
        }
    }
}
