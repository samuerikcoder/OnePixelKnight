#include "libs.h"

extern Platform platforms[];
extern int numPlatforms;
extern void checkPlatformCollisions(Entity *player);

void drawHealthBarSprite(int x, int y, int health);

App app;
Entity player;
Entity menemy;
Entity menemy2;
Entity menemy3;
Entity menemy4;
Entity senemy1;
Entity winFlag;

bool shouldPlayGameMusic = false;
Uint32 gameStartTime = 0;
bool gameMusicStarted = false;
SDL_Texture *screenshotButtonTexture;
SDL_Rect screenshotButtonRect = {1280 - 10 - 32, 10, 32, 16};

TTF_Font *gameFont = NULL;

bool checkPlayerFlagCollision(Entity *p, Entity *flag)
{
    if (p->x < flag->x + flag->width && 
        p->x + p->width > flag->x &&
        p->y < flag->y + flag->height &&
        p->y + p->height > flag->y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void runGame()
{
    memset(&winFlag, 0, sizeof(Entity));
    memset(&player, 0, sizeof(Entity));
    memset(&menemy, 0, sizeof(Entity));
    memset(&menemy2, 0, sizeof(Entity));
    memset(&menemy3, 0, sizeof(Entity));
    memset(&menemy4, 0, sizeof(Entity));
    memset(&senemy1, 0, sizeof(Entity));

    initLevelCoins();

    screenshotButtonTexture = loadTexture("../assets/hud/camera.png");
    if (!screenshotButtonTexture)
    {
        fprintf(stderr, "Erro ao carregar textura do botão de screenshot\n");
    }

    winFlag.width = 16;
    winFlag.height = 32;
    winFlag.texture = loadTexture("../assets/entitys/winflag.png");
    if (!winFlag.texture)
    {
        fprintf(stderr, "Erro ao carregar textura da bandeira de vitoria: %s\n", IMG_GetError());
    }
    winFlag.x = 640;
    winFlag.y = 600;

    app.camera.w = SCREEN_WIDTH;
    app.camera.h = SCREEN_HEIGHT;
    app.camera.x = 0;
    app.zoom = 1.5f;
    app.right = 0;
    app.left = 0;

    app.camera.y = platforms[0].rect.y - app.camera.h;

    player.texture = loadTexture("../assets/entitys/player.png");
    player.x = 0;
    player.y = 570;
    player.width = 32;
    player.height = 32;
    player.health = 3;

    menemy.x = platforms[2].rect.x;
    menemy.y = platforms[2].rect.y - 32;
    menemy.width = 32;
    menemy.height = 32;
    menemy.texture = loadTexture("../assets/entitys/menemy.png");
    menemy.dx = 2.0f;
    menemy.grounded = 1;

    menemy2.x = platforms[6].rect.x;
    menemy2.y = platforms[6].rect.y - 32;
    menemy2.width = 32;
    menemy2.height = 32;
    menemy2.texture = loadTexture("../assets/entitys/menemy.png");
    menemy2.dx = 2.0f;
    menemy2.grounded = 1;

    menemy3.x = platforms[10].rect.x;
    menemy3.y = platforms[10].rect.y - 32;
    menemy3.width = 32;
    menemy3.height = 32;
    menemy3.texture = loadTexture("../assets/entitys/menemy.png");
    menemy3.dx = 2.0f;
    menemy3.grounded = 1;

    menemy4.x = platforms[11].rect.x + platforms[11].rect.w - menemy4.width;
    menemy4.y = platforms[11].rect.y - 32;
    menemy4.width = 32;
    menemy4.height = 32;
    menemy4.texture = loadTexture("../assets/entitys/menemy.png");
    menemy4.dx = -2.0f;
    menemy4.grounded = 1;

    senemy1.x = platforms[15].rect.x;
    senemy1.y = platforms[15].rect.y - 32;
    senemy1.width = 16;
    senemy1.height = 16;
    senemy1.texture = loadTexture("../assets/entitys/senemy.png");
    senemy1.dx = 3.5f;
    senemy1.grounded = 1;

    initLevelCoins();

    Uint32 currentTime;

    player.coins_collected = 0;

    while (1)
    {
        drawHealthBarSprite(20, 20, player.health);
        checkCoinCollisions(&player);

        app.camera.x = (int)(player.x + player.width / 2 - (SCREEN_WIDTH / (2 * app.zoom)));
        float y_offset_para_descer_a_cena = 105.0f;
        app.camera.y = (int)(player.y + player.height / 2 - (SCREEN_HEIGHT / (2 * app.zoom)) - y_offset_para_descer_a_cena);

        if (app.camera.x < 0)
            app.camera.x = 0;
        if (app.camera.y < 0)
            app.camera.y = 0;

        prepareScene();
        doInput();

        if (shouldPlayGameMusic && !gameMusicStarted)
        {
            currentTime = SDL_GetTicks();
            if (currentTime - gameStartTime >= 2000)
            {
                gameMusic();
                printf("Musica tocando\n");
                gameMusicStarted = true;
            }
        }

        menemy.x += menemy.dx;
        if (menemy.x < platforms[2].rect.x)
        {
            menemy.x = platforms[2].rect.x;
            menemy.dx = 2.0f;
        }
        else if (menemy.x + menemy.width > platforms[2].rect.x + platforms[2].rect.w)
        {
            menemy.x = platforms[2].rect.x + platforms[2].rect.w - menemy.width;
            menemy.dx = -2.0f;
        }

        menemy2.x += menemy2.dx;
        if (menemy2.x < platforms[6].rect.x)
        {
            menemy2.x = platforms[6].rect.x;
            menemy2.dx = 2.0f;
        }
        else if (menemy2.x + menemy2.width > platforms[6].rect.x + platforms[6].rect.w)
        {
            menemy2.x = platforms[6].rect.x + platforms[6].rect.w - menemy2.width;
            menemy2.dx = -2.0f;
        }

        menemy3.x += menemy3.dx;
        if (menemy3.x < platforms[10].rect.x)
        {
            menemy3.x = platforms[10].rect.x;
            menemy3.dx = 2.0f;
        }
        else if (menemy3.x + menemy3.width > platforms[10].rect.x + platforms[10].rect.w)
        {
            menemy3.x = platforms[10].rect.x + platforms[10].rect.w - menemy3.width;
            menemy3.dx = -2.0f;
        }

        menemy4.x += menemy4.dx;
        if (menemy4.x < platforms[11].rect.x)
        {
            menemy4.x = platforms[11].rect.x;
            menemy4.dx = 2.0f;
        }
        else if (menemy4.x + menemy4.width > platforms[11].rect.x + platforms[11].rect.w)
        {
            menemy4.x = platforms[11].rect.x + platforms[11].rect.w - menemy4.width;
            menemy4.dx = -2.0f;
        }

        senemy1.x += senemy1.dx;
        if (senemy1.x < platforms[15].rect.x)
        {
            senemy1.x = platforms[15].rect.x;
            senemy1.dx = 3.0f;
        }
        else if (senemy1.x + senemy1.width > platforms[15].rect.x + platforms[15].rect.w)
        {
            senemy1.x = platforms[15].rect.x + platforms[15].rect.w - senemy1.width;
            senemy1.dx = -3.0f;
        }

        player.dy += 0.3f;
        if (player.dy > Y_MOVEMENT)
            player.dy = Y_MOVEMENT;

        if (app.left && player.x >= 0)
            player.dx = -X_MOVEMENT;
        else if (app.right)
        {
            player.dx = X_MOVEMENT;
        }
        else
            player.dx = 0.0f;

        player.x += player.dx;
        player.y += player.dy;
        player.grounded = 0;

        if (checkPlayerFlagCollision(&player, &winFlag))
        {
            int winAction = showWinScreen(&gameStartTime, &gameMusicStarted, &shouldPlayGameMusic);
            if (winAction == 1)
            { 
                int menuAction = showMenu(&gameStartTime, &gameMusicStarted, &shouldPlayGameMusic);

                if (menuAction == 1)
                {
                    player.health = 3;
                    player.isDead = false;
                    break;
                }
            }
            else
            {
                exit(0);
            }
        }

        checkPlatformCollisions(&player);
        checkEnemieCollisions(&player, &menemy);
        checkEnemieCollisions(&player, &menemy2);
        checkEnemieCollisions(&player, &menemy3);
        checkEnemieCollisions(&player, &menemy4);
        checkEnemieCollisions(&player, &senemy1);
        checkIfPlayerIsDead(&player);
        checkCoinCollisions(&player);

        currentTime = SDL_GetTicks();
        if (player.isIntangible == 1 && currentTime - player.intangibleTimer >= INTANGIBILITY_DURATION)
            player.isIntangible = 0;
        if (player.isShaking == 1 && currentTime - player.shakeTimer >= INTANGIBILITY_DURATION)
            player.isShaking = 0;

        blit(player.texture, (int)player.x, (int)player.y);
        blit(menemy.texture, (int)menemy.x, (int)menemy.y);
        blit(menemy2.texture, (int)menemy2.x, (int)menemy2.y);
        blit(menemy3.texture, (int)menemy3.x, (int)menemy3.y);
        blit(menemy4.texture, (int)menemy4.x, (int)menemy4.y);
        blit(senemy1.texture, (int)senemy1.x, (int)senemy1.y);
        drawPlayerShaking(&player);
        drawCoins(app.renderer, &app);

        if (winFlag.texture)
        {
            blit(winFlag.texture, (int)winFlag.x, (int)winFlag.y);
        }

        int uiCoinDisplayX = 20;
        int uiCoinDisplayY = 50;
        if (gameFont && coinTexture)
        {
            drawCoinUI(app.renderer, gameFont, coinTexture, player.coins_collected, uiCoinDisplayX, uiCoinDisplayY);
        }

        SDL_RenderCopy(app.renderer, screenshotButtonTexture, NULL, &screenshotButtonRect);
        int mouseX, mouseY;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

        if ((mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
            mouseX >= screenshotButtonRect.x &&
            mouseX <= screenshotButtonRect.x + screenshotButtonRect.w &&
            mouseY >= screenshotButtonRect.y &&
            mouseY <= screenshotButtonRect.y + screenshotButtonRect.h)
        {
            saveScreenshot(app.renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_Delay(200);
        }

        printf("Posição do Jogador: X = %.2f, Y = %.2f\n", player.x, player.y);
        presentScene();

        if (player.isDead && currentTime - player.shakeTimer >= INTANGIBILITY_DURATION)
        {
            Mix_HaltMusic();
            deathSoundEffect();
            int tryAgain = showDeathScreen(&gameStartTime, &gameMusicStarted, &shouldPlayGameMusic);
            if (tryAgain)
            {
                player.health = 3;
                player.isDead = false;
                break;
            }
            else
            {
                exit(0);
            }
        }

        SDL_Delay(16);
    }
}

int main(void)
{
    memset(&app, 0, sizeof(App));
    initSDL();
    atexit(cleanup);
    initTextures();
    initAudio();
    initPlatforms();
    initFont();

    if (!showMenu(&gameStartTime, &gameMusicStarted, &shouldPlayGameMusic))
        return 0;

    while (1)
    {
        runGame();
    }
    cleanupCoinSystem();
    closeAudio();
    return 0;
}
