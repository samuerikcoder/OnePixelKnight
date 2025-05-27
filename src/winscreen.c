
#include "libs.h"

extern App app;
extern TTF_Font *gameFont;

int showWinScreen(Uint32 *gameStartTime, bool *gameMusicStarted, bool *shouldPlayGameMusic) {
    SDL_Event event;
    SDL_Texture *winTextTexture = NULL;
    SDL_Rect winTextRect;
    SDL_Color white = {255, 255, 255, 255};
    int selection = 1;

    if (*gameMusicStarted) {
        Mix_HaltMusic();
        *gameMusicStarted = false;
    }

    if (gameFont) {
        SDL_Surface *surface = TTF_RenderText_Blended(gameFont, "VOCE VENCEU!", white);
        if (surface) {
            winTextTexture = SDL_CreateTextureFromSurface(app.renderer, surface);
            winTextRect.x = (SCREEN_WIDTH - surface->w) / 2;
            winTextRect.y = (SCREEN_HEIGHT / 2) - surface->h - 20;
            winTextRect.w = surface->w;
            winTextRect.h = surface->h;
            SDL_FreeSurface(surface);
        } else {
            fprintf(stderr, "Erro ao renderizar texto de vitoria: %s\n", TTF_GetError());
        }
    } else {
        fprintf(stderr, "gameFont nao carregada para winscreen.\n");
    }
    
    SDL_Texture *instructionTextTexture = NULL;
    SDL_Rect instructionTextRect;
    if (gameFont) {
        SDL_Surface* surface = TTF_RenderText_Blended(gameFont, "Pressione ENTER para voltar ao Menu", white);
        if (surface) {
            instructionTextTexture = SDL_CreateTextureFromSurface(app.renderer, surface);
            instructionTextRect.x = (SCREEN_WIDTH - surface->w) / 2;
            instructionTextRect.y = (SCREEN_HEIGHT / 2) + 20;
            instructionTextRect.w = surface->w;
            instructionTextRect.h = surface->h;
            SDL_FreeSurface(surface);
        } else {
            fprintf(stderr, "Erro ao renderizar texto de instrucao (vitoria): %s\n", TTF_GetError());
        }
    }


    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    selection = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_RETURN:
                        case SDLK_KP_ENTER:
                            running = 0;
                            selection = 1;
                            break;
                        case SDLK_q:
                            running = 0;
                            selection = 0;
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(app.renderer, 0, 0, 50, 255);
        SDL_RenderClear(app.renderer);

        if (winTextTexture) {
            SDL_RenderCopy(app.renderer, winTextTexture, NULL, &winTextRect);
        }
        if (instructionTextTexture) {
            SDL_RenderCopy(app.renderer, instructionTextTexture, NULL, &instructionTextRect);
        }

        SDL_RenderPresent(app.renderer);
        SDL_Delay(16);
    }

    if (winTextTexture) {
        SDL_DestroyTexture(winTextTexture);
    }
    if (instructionTextTexture) {
        SDL_DestroyTexture(instructionTextTexture);
    }

    if (selection == 1) {
        *shouldPlayGameMusic = false;
    }
    
    return selection;
}