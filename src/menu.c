#include "libs.h"

void closeMenu(int *startGame, Uint32 **gameStartTime, bool **gameMusicStarted, bool **shouldPlayGameMusic)
{
    *startGame = 1;

    Mix_HaltMusic();

    startGameSoundEffect();

    **gameStartTime = SDL_GetTicks();

    **shouldPlayGameMusic = true;

    **gameMusicStarted = false;
}

int showMenu(Uint32 *gameStartTime, bool *gameMusicStarted, bool *shouldPlayGameMusic)
{
    if (TTF_Init() != 0)
    {
        printf("Erro ao iniciar SDL_ttf: %s\n", TTF_GetError());
        return 0;
    }

    SDL_Surface *titleSurface = IMG_Load("../assets/images/menu/title.png");
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

    SDL_Surface *startSurface = IMG_Load("../assets/images/menu/btnstart.png");
    if (!startSurface)
    {
        printf("Erro ao carregar imagem do botão iniciar: %s\n", IMG_GetError());
        SDL_DestroyTexture(titleTexture);
        return 0;
    }
    SDL_Texture *startButtonTexture = SDL_CreateTextureFromSurface(app.renderer, startSurface);
    int startW = startSurface->w;
    int startH = startSurface->h;
    SDL_FreeSurface(startSurface);
    if (!startButtonTexture)
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
        SDL_DestroyTexture(startButtonTexture);
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
        SDL_DestroyTexture(startButtonTexture);
        return 0;
    }

    SDL_Rect titleRect = {
        (SCREEN_WIDTH - titleW) / 2,
        SCREEN_HEIGHT / 4 - titleH / 2,
        titleW,
        titleH};

    SDL_Rect startButtonRect = {
        (SCREEN_WIDTH - startW) / 2,
        SCREEN_HEIGHT / 2,
        startW,
        startH};

    SDL_Rect quitButtonRect = {
        (SCREEN_WIDTH - quitW) / 2,
        SCREEN_HEIGHT / 2 + 80,
        quitW,
        quitH};

    SDL_Event event;
    int running = 1;
    int startGame = 0;

    menuMusic();
    while (running && !startGame)
    {

        SDL_SetRenderDrawColor(app.renderer, 4, 12, 6, 255);
        SDL_RenderClear(app.renderer);

        SDL_RenderCopy(app.renderer, titleTexture, NULL, &titleRect);
        SDL_RenderCopy(app.renderer, startButtonTexture, NULL, &startButtonRect);
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

                if (mx >= startButtonRect.x && mx <= startButtonRect.x + startButtonRect.w &&
                    my >= startButtonRect.y && my <= startButtonRect.y + startButtonRect.h)
                {
                    closeMenu(&startGame, &gameStartTime, &gameMusicStarted, &shouldPlayGameMusic);
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
                    closeMenu(&startGame, &gameStartTime, &gameMusicStarted, &shouldPlayGameMusic);
                }
            }
        }

        SDL_Delay(16);
    }

    SDL_DestroyTexture(titleTexture);
    SDL_DestroyTexture(startButtonTexture);
    SDL_DestroyTexture(quitButtonTexture);
    TTF_Quit();

    return startGame;
}