#include "libs.h"

SDL_Texture *textureSmalld = NULL;
SDL_Texture *textureMediumd = NULL;
SDL_Texture *textureLarged = NULL;

SDL_Texture *textureSmallb = NULL;
SDL_Texture *textureMediumb = NULL;
SDL_Texture *textureLargeb = NULL;

SDL_Texture *texturebg1 = NULL;

SDL_Texture *healthBarTexture = NULL;

SDL_Texture *loadTexture(const char *filename)
{
    SDL_Surface *surface = IMG_Load(filename);
    if (!surface)
    {
        printf("Erro ao carregar imagem %s: %s\n", filename, IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void initTextures(void)
{

    app.healthBarTexture = loadTexture("../assets/hud/3hp.png");
    if (!healthBarTexture)
    {
        printf("Erro ao carregar bg1.png\n");
    }

    textureSmalld = loadTexture("../assets/plataforms/smalld.png");
    textureMediumd = loadTexture("../assets/plataforms/mediumd.png");
    textureLarged = loadTexture("../assets/plataforms/larged.png");
    textureSmallb = loadTexture("../assets/plataforms/smallb.png");
    textureMediumb = loadTexture("../assets/plataforms/mediumb.png");
    ;
    textureLargeb = loadTexture("../assets/plataforms/largeb.png");

    if (!textureSmallb || !textureMediumb || !textureLargeb)
    {
        printf("Erro ao carregar alguma textura Type B de plataforma!\n");
    }

    if (!textureSmalld || !textureMediumd || !textureLarged)
    {
        printf("Erro ao carregar alguma textura Type D de plataforma!\n");
    }

    if (coinTexture == NULL) { 
        coinTexture = loadTexture("../assets/entitys/coin.png"); 
        if (!coinTexture) {
            fprintf(stderr, "Erro ao carregar textura da moeda\n");
        }
    }

    largeCoinTexture = loadTexture("../assets/entitys/largeCoin.png");
    if (!largeCoinTexture) {
        printf("Falha ao carregar textura da moeda grande!\n");
    }
}

void initFont(void) {
    gameFont = TTF_OpenFont("../assets/font/04B_30__.ttf", 24);
    if (gameFont == NULL) {
        printf("Falha ao carregar a fonte! TTF_Error: %s\n", TTF_GetError());
    }
}

void initSDL(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        exit(1);
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        printf("Erro ao inicializar SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() == -1) {
    printf("SDL_ttf não pôde inicializar! TTF_Error: %s\n", TTF_GetError());
    }


    app.window = SDL_CreateWindow("ONE PIXEL KNIGHT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!app.window)
    {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    if (!app.renderer)
    {
        printf("Erro ao criar renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(app.window);
        SDL_Quit();
        exit(1);
    }
}
