#include "libs.h"

void cleanup(void) {
    if (player.texture)
        SDL_DestroyTexture(player.texture);

    if (app.renderer)
        SDL_DestroyRenderer(app.renderer);

    if (app.window)
        SDL_DestroyWindow(app.window);

    IMG_Quit();
    SDL_Quit();
}
