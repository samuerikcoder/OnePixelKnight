#include "libs.h"

void checkEnemieCollisions(Entity *player, Entity *enemie) {
    SDL_Rect r1 = {
        (int)player->x,
        (int)player->y,
        player->width,
        player->height
    };

    SDL_Rect r2 = {
        (int)enemie->x,
        (int)enemie->y,
        enemie->width,
        enemie->height
    };

    if (SDL_HasIntersection(&r1, &r2) && player->isIntangible == 0) {
        damageSoundEffect();
        player->health--;

        player->isIntangible = 1;
        player->intangibleTimer = SDL_GetTicks();

        player->isShaking = 1;
        player->shakeTimer = SDL_GetTicks();
    }
}