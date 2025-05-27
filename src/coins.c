#include "libs.h"
#include <stdio.h>

Coin coins[MAX_COINS];
int num_active_coins = 0;
SDL_Texture *coinTexture = NULL;
SDL_Texture *largeCoinTexture = NULL;

int offsetY_para_ficar_em_cima = -18;

void addCoin(int x, int y, CoinType type) {
    if (num_active_coins < MAX_COINS) {
        coins[num_active_coins].x = x;
        coins[num_active_coins].y = y;
        coins[num_active_coins].collected = false;
        coins[num_active_coins].type = type;

        if (type == COIN_TYPE_LARGE) {
            coins[num_active_coins].width = 24;
            coins[num_active_coins].height = 24;
        } else {
            coins[num_active_coins].width = 18;
            coins[num_active_coins].height = 18;
        }
        num_active_coins++;
    }
}


void addCoinRow(int startX, int startY, int count, int spacingX) {
    for (int i = 0; i < count; i++) {
        addCoin(startX + (i * (18 + spacingX)), startY, COIN_TYPE_NORMAL);
    }
}

void addCoinRowOnPlatform(Platform *platform, int offsetX, int offsetY, int count, int spacingX, CoinType type) {
    if (!platform) return;

    int startX = platform->rect.x + offsetX;
    int coinY = platform->rect.y + offsetY;

    int coinWidthForSpacing;
    if (type == COIN_TYPE_LARGE) {
        coinWidthForSpacing = 24;
    } else {
        coinWidthForSpacing = 18;
    }

    for (int i = 0; i < count; i++) {
        addCoin(startX + i * (coinWidthForSpacing + spacingX), coinY, type);
    }
}

void initLevelCoins(void) {
    num_active_coins = 0; 

    addCoinRowOnPlatform(&platforms[1], 30, -25, 4, 12, COIN_TYPE_NORMAL);
    addCoinRowOnPlatform(&platforms[5], 30, -25, 4, 12, COIN_TYPE_NORMAL);
    addCoinRowOnPlatform(&platforms[9], 30, -25, 4, 12, COIN_TYPE_NORMAL);

    addCoinRowOnPlatform(
        &platforms[13],             
        30,                         
        offsetY_para_ficar_em_cima,  
        1,                           
        0,                           
        COIN_TYPE_NORMAL             
    );

    if (platforms[10].rect.w > 0) { 
    int centerOffsetX = (platforms[10].rect.w / 2) - (24 / 2); 
    int onTopOffsetY = -24; 
    addCoin(platforms[10].rect.x + centerOffsetX, platforms[10].rect.y + onTopOffsetY, COIN_TYPE_LARGE);
    }
}

void drawCoins(SDL_Renderer *renderer, App *camera_app) {
    if (!coinTexture || !largeCoinTexture) {
        return;
    }

    for (int i = 0; i < num_active_coins; i++) {
        if (!coins[i].collected) {
            SDL_Rect destRect = {
                (int)((coins[i].x - camera_app->camera.x) * camera_app->zoom),
                (int)((coins[i].y - camera_app->camera.y) * camera_app->zoom),
                (int)(coins[i].width * camera_app->zoom),
                (int)(coins[i].height * camera_app->zoom)
            };

            SDL_Texture *currentCoinTexture = NULL;
            if (coins[i].type == COIN_TYPE_LARGE) {
                currentCoinTexture = largeCoinTexture;
            } else {
                currentCoinTexture = coinTexture;
            }

            if (currentCoinTexture) {
                SDL_RenderCopy(renderer, currentCoinTexture, NULL, &destRect);
            }
        }
    }
}

void checkCoinCollisions(Entity *player) {
    SDL_Rect playerRect = {(int)player->x, (int)player->y, player->width, player->height};
    for (int i = 0; i < num_active_coins; i++) {
        if (!coins[i].collected) {
            SDL_Rect coinRect = {(int)coins[i].x, (int)coins[i].y, coins[i].width, coins[i].height};
            if (SDL_HasIntersection(&playerRect, &coinRect)) {
                coins[i].collected = true;

                int value = 0;
                if (coins[i].type == COIN_TYPE_LARGE) {
                    value = 5;
                } else {
                    value = 1;
                }
                player->coins_collected += value;

                printf("Moeda (%s) coletada! Valor: %d. Total: %d\n",
                       (coins[i].type == COIN_TYPE_LARGE ? "Grande" : "Normal"),
                       value,
                       player->coins_collected);
                
                if (coinPickupSound) { 
                        Mix_PlayChannelTimed(-1, coinPickupSound, 1500, 2000); 
                }
            }
        }
    }
}

void cleanupCoinSystem(void) {
    if (coinTexture) {
        SDL_DestroyTexture(coinTexture);
        coinTexture = NULL; 
    }
    if (largeCoinTexture) { 
        SDL_DestroyTexture(largeCoinTexture);
        largeCoinTexture = NULL;
    }
}

void drawCoinUI(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture *iconTexture, int coinCount, int x, int y) {
    if (!renderer || !font || !iconTexture) {
        fprintf(stderr, "Erro: Renderer, fonte ou textura do ícone nulos para drawCoinUI.\n");
        return;
    }

   
    int iconWidth = 18;  
    int iconHeight = 18; 
    SDL_Rect iconDestRect = { x, y, iconWidth, iconHeight };
    SDL_RenderCopy(renderer, iconTexture, NULL, &iconDestRect);

    char textBuffer[32];
    sprintf(textBuffer, "x %d", coinCount);

    SDL_Color textColor = { 255, 255, 255, 255 };

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textBuffer, textColor);
    if (!textSurface) {
        printf("Não foi possível renderizar a superfície do texto! TTF_Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        printf("Não foi possível criar textura do texto! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    int textW = 0;
    int textH = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);

    SDL_Rect textDestRect = {
        x + iconWidth + 5,
        y + (iconHeight / 2) - (textH / 2),
        textW,
        textH
    };

    SDL_RenderCopy(renderer, textTexture, NULL, &textDestRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
