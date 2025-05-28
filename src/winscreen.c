#include "libs.h" 

extern App app;
extern TTF_Font *gameFont; 

int showWinScreen(Uint32 *gameStartTime, bool *gameMusicStarted, bool *shouldPlayGameMusic, int coinsCollected)  {
    SDL_Event event;
    int selection = 1; 

    SDL_Texture *backgroundTexture = NULL;
    SDL_Texture *coinsTextTexture = NULL; 
    SDL_Rect coinsTextRect;           
    SDL_Color textColor = {137, 162, 87, 255}; 

    backgroundTexture = IMG_LoadTexture(app.renderer, "../assets/hud/winscreen.png");
    if (backgroundTexture == NULL) {
        fprintf(stderr, "Erro ao carregar imagem de fundo para vitoria: %s\n", IMG_GetError());
    }

    if (gameFont) {
        char coinsStr[100]; 
        sprintf(coinsStr, "Moedas Coletadas: %d/54", coinsCollected);

        SDL_Surface *textSurface = TTF_RenderText_Blended(gameFont, coinsStr, textColor);
        if (textSurface) {
            coinsTextTexture = SDL_CreateTextureFromSurface(app.renderer, textSurface);
            if (coinsTextTexture) {
                coinsTextRect.x = 450;
                coinsTextRect.y = 480;
                coinsTextRect.w = textSurface->w;
                coinsTextRect.h = textSurface->h;
            } else {
                fprintf(stderr, "Erro ao criar textura para texto de moedas: %s\n", SDL_GetError());
            }
            SDL_FreeSurface(textSurface); 
        } else {
            fprintf(stderr, "Erro ao renderizar texto de moedas: %s\n", TTF_GetError());
        }
    } else {
        fprintf(stderr, "gameFont nao carregada para winscreen (texto moedas).\n");
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
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255); 
        SDL_RenderClear(app.renderer);

        if (backgroundTexture) {
            SDL_RenderCopy(app.renderer, backgroundTexture, NULL, NULL); 
        } else {
            SDL_SetRenderDrawColor(app.renderer, 4, 12, 6, 255); 
            SDL_RenderFillRect(app.renderer, NULL); 
        }

        if (coinsTextTexture) {
            SDL_RenderCopy(app.renderer, coinsTextTexture, NULL, &coinsTextRect);
        }

        SDL_RenderPresent(app.renderer);
        SDL_Delay(16); 
    }


    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
    }
    if (coinsTextTexture) { 
        SDL_DestroyTexture(coinsTextTexture);
    }

    if (selection == 1) { 
        *shouldPlayGameMusic = false; 
    }
    
    return selection;
}