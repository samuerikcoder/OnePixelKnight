#include "libs.h"

void saveScreenshot(SDL_Renderer *renderer, int width, int height) {
    SDL_Surface *screenshot = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
    if (!screenshot) {
        printf("Erro ao criar surface: %s\n", SDL_GetError());
        return;
    }

    if (SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA32, screenshot->pixels, screenshot->pitch) != 0) {
        printf("Erro ao ler pixels: %s\n", SDL_GetError());
        SDL_FreeSurface(screenshot);
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char filename[128];
    snprintf(filename, sizeof(filename), "screenshots/screenshot%04d-%02d-%02d_%02d-%02d-%02d.bmp",
             t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
             t->tm_hour, t->tm_min, t->tm_sec);

    system("mkdir -p screenshots");

    if (SDL_SaveBMP(screenshot, filename) != 0) {
        printf("Erro ao salvar BMP: %s\n", SDL_GetError());
    } else {
        printf("Screenshot salva em: %s\n", filename);
    }

    SDL_FreeSurface(screenshot);
}