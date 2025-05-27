#include "libs.h"

void blit(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest = {
        (int)((x - app.camera.x) * app.zoom),
        (int)((y - app.camera.y) * app.zoom),
        (int)(player.width * app.zoom),
        (int)(player.height * app.zoom)};
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void drawPlatforms(void)
{
    for (int i = 0; i < numPlatforms; i++)
    {
        SDL_Rect drawRect = {
            (int)((platforms[i].rect.x - app.camera.x) * app.zoom),
            (int)((platforms[i].rect.y - app.camera.y) * app.zoom),
            (int)(platforms[i].rect.w * app.zoom),
            (int)(platforms[i].rect.h * app.zoom)};

        if (platforms[i].texture != NULL)
        {
            SDL_RenderCopy(app.renderer, platforms[i].texture, NULL, &drawRect);
        }
        else
        {
            SDL_SetRenderDrawColor(app.renderer, 4, 12, 6, 255);
            SDL_RenderFillRect(app.renderer, &drawRect);
        }
    }
}

void drawHealthBarSprite(int x, int y, int health)
{
    if (!app.healthBarTexture)
    {
        printf("app.healthBarTexture é NULL!\n");
        return;
    }

    int w = 80;
    int h = 16;

    if (health < 0)
        health = 0;

    switch (health)
    {
    case 3:
        app.healthBarTexture = loadTexture("../assets/hud/3hp.png");
        break;
    case 2:
        app.healthBarTexture = loadTexture("../assets/hud/2hp.png");
        break;
    case 1:
        app.healthBarTexture = loadTexture("../assets/hud/1hp.png");
        break;
    case 0:
        app.healthBarTexture = loadTexture("../assets/hud/nolife.png");
        break;
    }

    SDL_Rect srcRect = {0, 0, w, h};
    SDL_Rect dstRect = {x, y, w, h};

    SDL_RenderCopy(app.renderer, app.healthBarTexture, &srcRect, &dstRect);
}

void drawPlayerShaking(Entity *player)
{
    int renderX = player->x;
    int renderY = player->y;

    if (player->isShaking)
    {
        renderX += (rand() % 5) - 2;
        renderY += (rand() % 5) - 2;
    }

    SDL_Rect playerRect = {
        (int)((renderX - app.camera.x) * app.zoom),
        (int)((renderY - app.camera.y) * app.zoom),
        (int)(player->width * app.zoom),
        (int)(player->height * app.zoom)};

    SDL_RenderCopy(app.renderer, player->texture, NULL, &playerRect);
}

void prepareScene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 17, 35, 24, 255);
    SDL_RenderClear(app.renderer);
    drawPlatforms();
    drawHealthBarSprite(20, 20, player.health);
}

void prepareMenuScene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
    SDL_RenderPresent(app.renderer);
}
