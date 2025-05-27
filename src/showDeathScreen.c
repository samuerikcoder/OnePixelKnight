#include "libs.h"

void closeDeathScreen(int *tryAgainGame, Uint32 **gameStartTime, bool **gameMusicStarted, bool **shouldPlayGameMusic)
{
    *tryAgainGame = 1;

    Mix_HaltMusic();

    startGameSoundEffect();

    **gameStartTime = SDL_GetTicks();

    **shouldPlayGameMusic = true;

    **gameMusicStarted = false;
}

int showDeathScreen(Uint32 *gameStartTime, bool *gameMusicStarted, bool *shouldPlayGameMusic)
{
    if (TTF_Init() != 0)
    {
        printf("Erro ao iniciar SDL_ttf: %s\n", TTF_GetError());
        return 0;
    }

    SDL_Surface *titleSurface = IMG_Load("../assets/deathhud/titledeath.png");
    if (!titleSurface)
    {
        printf("Erro ao carregar imagem do título: %s\n", IMG_GetError());
        return 0;
    }
    SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(app.renderer, titleSurface);
    int titleW = titleSurface->w;
    int titleH = titleSurface->h;
    SDL_FreeSurface(titleSurface);
    if (!titleTexture)
    {
        printf("Erro ao criar textura do título: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Surface *tryAgainSurface = IMG_Load("../assets/deathhud/tryagainbtn.png");
    if (!tryAgainSurface)
    {
        printf("Erro ao carregar imagem do botão tente novamente: %s\n", IMG_GetError());
        SDL_DestroyTexture(titleTexture);
        return 0;
    }
    SDL_Texture *tryAgainButtonTexture = SDL_CreateTextureFromSurface(app.renderer, tryAgainSurface);
    int tryAgainW = tryAgainSurface->w;
    int tryAgainH = tryAgainSurface->h;
    SDL_FreeSurface(tryAgainSurface);
    if (!tryAgainButtonTexture)
    {
        printf("Erro ao criar textura do botão iniciar: %s\n", SDL_GetError());
        SDL_DestroyTexture(titleTexture);
        return 0;
    }

    SDL_Surface *quitSurface = IMG_Load("../assets/images/menu/btnexit.png");
    if (!quitSurface)
    {
        printf("Erro ao carregar imagem do botão sair: %s\n", IMG_GetError());
        SDL_DestroyTexture(titleTexture);
        SDL_DestroyTexture(tryAgainButtonTexture);
        return 0;
    }
    SDL_Texture *quitButtonTexture = SDL_CreateTextureFromSurface(app.renderer, quitSurface);
    int quitW = quitSurface->w;
    int quitH = quitSurface->h;
    SDL_FreeSurface(quitSurface);
    if (!quitButtonTexture)
    {
        printf("Erro ao criar textura do botão sair: %s\n", SDL_GetError());
        SDL_DestroyTexture(titleTexture);
        SDL_DestroyTexture(tryAgainButtonTexture);
        return 0;
    }

    SDL_Rect titleRect = {
        (SCREEN_WIDTH - titleW) / 2,
        SCREEN_HEIGHT / 4 - titleH / 2,
        titleW,
        titleH};

    SDL_Rect tryAgainButtonRect = {
        (SCREEN_WIDTH - tryAgainW) / 2,
        SCREEN_HEIGHT / 2,
        tryAgainW,
        tryAgainH};

    SDL_Rect quitButtonRect = {
        (SCREEN_WIDTH - quitW) / 2,
        SCREEN_HEIGHT / 2 + 80,
        quitW,
        quitH};

    SDL_Event event;
    int running = 1;
    int tryAgainGame = 0;

    menuMusic();
    while (running && !tryAgainGame)
    {

        SDL_SetRenderDrawColor(app.renderer, 4, 12, 6, 255);
        SDL_RenderClear(app.renderer);

        SDL_RenderCopy(app.renderer, titleTexture, NULL, &titleRect);
        SDL_RenderCopy(app.renderer, tryAgainButtonTexture, NULL, &tryAgainButtonRect);
        SDL_RenderCopy(app.renderer, quitButtonTexture, NULL, &quitButtonRect);

        SDL_RenderPresent(app.renderer);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mx = event.button.x;
                int my = event.button.y;

                if (mx >= tryAgainButtonRect.x && mx <= tryAgainButtonRect.x + tryAgainButtonRect.w &&
                    my >= tryAgainButtonRect.y && my <= tryAgainButtonRect.y + tryAgainButtonRect.h)
                {
                    closeDeathScreen(&tryAgainGame, &gameStartTime, &gameMusicStarted, &shouldPlayGameMusic);
                }

                if (mx >= quitButtonRect.x && mx <= quitButtonRect.x + quitButtonRect.w &&
                    my >= quitButtonRect.y && my <= quitButtonRect.y + quitButtonRect.h)
                {
                    running = 0;
                }
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = 0;
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    closeDeathScreen(&tryAgainGame, &gameStartTime, &gameMusicStarted, &shouldPlayGameMusic);
                }
            }
        }

        SDL_Delay(16);
    }

    SDL_DestroyTexture(titleTexture);
    SDL_DestroyTexture(tryAgainButtonTexture);
    SDL_DestroyTexture(quitButtonTexture);
    TTF_Quit();

    return tryAgainGame;
}