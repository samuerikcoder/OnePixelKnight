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
Entity menemy5;   
Entity menemy6; 
Entity menemy7; 
Entity menemy8; 
Entity senemy1;
Entity senemy2;
Entity senemy3;
Entity senemy4;
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
    memset(&menemy5, 0, sizeof(Entity));
    memset(&menemy6, 0, sizeof(Entity));
    memset(&menemy7, 0, sizeof(Entity));
    memset(&menemy8, 0, sizeof(Entity));
    memset(&senemy1, 0, sizeof(Entity)); 
    memset(&senemy2, 0, sizeof(Entity)); 
    memset(&senemy3, 0, sizeof(Entity)); 
    memset(&senemy4, 0, sizeof(Entity)); 

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
    winFlag.x = 5970;
    winFlag.y = 468;

    app.camera.w = SCREEN_WIDTH;
    app.camera.h = SCREEN_HEIGHT;
    app.camera.x = 0;
    app.zoom = 1.5f;
    app.right = 0;
    app.left = 0;

    app.camera.y = platforms[0].rect.y - app.camera.h;

    player.texture = loadTexture("../assets/entitys/player.png");
    player.x = platforms[0].rect.x;
    player.y = platforms[0].rect.y -32;
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
    
    menemy5.x = platforms[21].rect.x + platforms[21].rect.w - menemy4.width;
    menemy5.y = platforms[21].rect.y - 32;
    menemy5.width = 32;
    menemy5.height = 32;
    menemy5.texture = loadTexture("../assets/entitys/menemy.png");
    menemy5.dx = -2.0f;
    menemy5.grounded = 1;

    menemy6.x = platforms[25].rect.x + platforms[25].rect.w - menemy4.width;
    menemy6.y = platforms[25].rect.y - 32;
    menemy6.width = 32;
    menemy6.height = 32;
    menemy6.texture = loadTexture("../assets/entitys/menemy.png");
    menemy6.dx = -2.0f;
    menemy6.grounded = 1;
    
    menemy7.x = platforms[29].rect.x + platforms[29].rect.w - menemy4.width;
    menemy7.y = platforms[29].rect.y - 32;
    menemy7.width = 32;
    menemy7.height = 32;
    menemy7.texture = loadTexture("../assets/entitys/menemy.png");
    menemy7.dx = -2.0f;
    menemy7.grounded = 1;

    menemy8.x = platforms[33].rect.x + platforms[33].rect.w - menemy4.width;
    menemy8.y = platforms[33].rect.y - 32;
    menemy8.width = 32;
    menemy8.height = 32;
    menemy8.texture = loadTexture("../assets/entitys/menemy.png");
    menemy8.dx = -2.0f;
    menemy8.grounded = 1;

    senemy1.x = platforms[15].rect.x;
    senemy1.y = platforms[15].rect.y - 32;
    senemy1.width = 16;
    senemy1.height = 16;
    senemy1.texture = loadTexture("../assets/entitys/senemy.png");
    senemy1.dx = 3.5f;
    senemy1.grounded = 1; 

    senemy2.x = platforms[22].rect.x;
    senemy2.y = platforms[22].rect.y - 32;
    senemy2.width = 16;
    senemy2.height = 16;
    senemy2.texture = loadTexture("../assets/entitys/senemy.png");
    senemy2.dx = 3.5f;
    senemy2.grounded = 1;

    senemy3.x = platforms[26].rect.x;
    senemy3.y = platforms[26].rect.y - 32;
    senemy3.width = 16;
    senemy3.height = 16;
    senemy3.texture = loadTexture("../assets/entitys/senemy.png");
    senemy3.dx = 3.5f;
    senemy3.grounded = 1; 

    senemy4.x = platforms[32].rect.x;
    senemy4.y = platforms[32].rect.y - 32;
    senemy4.width = 16;
    senemy4.height = 16;
    senemy4.texture = loadTexture("../assets/entitys/senemy.png");
    senemy4.dx = 3.5f;
    senemy4.grounded = 1; 

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

        menemy5.x += menemy5.dx;
        if (menemy5.x < platforms[25].rect.x)
        {
            menemy5.x = platforms[25].rect.x;
            menemy5.dx = 2.0f;
        }
        else if (menemy5.x + menemy5.width > platforms[25].rect.x + platforms[25].rect.w)
        {
            menemy5.x = platforms[25].rect.x + platforms[25].rect.w - menemy5.width;
            menemy5.dx = -2.0f;
        }

        menemy6.x += menemy6.dx;
        if (menemy6.x < platforms[21].rect.x)
        {
            menemy6.x = platforms[21].rect.x;
            menemy6.dx = 2.0f;
        }
        else if (menemy6.x + menemy6.width > platforms[21].rect.x + platforms[21].rect.w)
        {
            menemy6.x = platforms[21].rect.x + platforms[21].rect.w - menemy6.width;
            menemy6.dx = -2.0f;
        }

        menemy7.x += menemy7.dx;
        if (menemy7.x < platforms[29].rect.x)
        {
            menemy7.x = platforms[29].rect.x;
            menemy7.dx = 2.0f;
        }
        else if (menemy7.x + menemy7.width > platforms[29].rect.x + platforms[29].rect.w)
        {
            menemy7.x = platforms[29].rect.x + platforms[29].rect.w - menemy7.width;
            menemy7.dx = -2.0f;
        }


        menemy8.x += menemy8.dx;
        if (menemy8.x < platforms[33].rect.x)
        {
            menemy8.x = platforms[33].rect.x;
            menemy8.dx = 2.0f;
        }
        else if (menemy8.x + menemy8.width > platforms[33].rect.x + platforms[33].rect.w)
        {
            menemy8.x = platforms[33].rect.x + platforms[33].rect.w - menemy8.width;
            menemy8.dx = -2.0f;
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

        senemy2.x += senemy2.dx;
        if (senemy2.x < platforms[22].rect.x)
        {
            senemy2.x = platforms[22].rect.x;
            senemy2.dx = 3.0f;
        }
        else if (senemy2.x + senemy2.width > platforms[22].rect.x + platforms[22].rect.w)
        {
            senemy2.x = platforms[22].rect.x + platforms[22].rect.w - senemy2.width;
            senemy2.dx = -3.0f;
        }

        senemy3.x += senemy3.dx;
        if (senemy3.x < platforms[26].rect.x)
        {
            senemy3.x = platforms[26].rect.x;
            senemy3.dx = 3.0f;
        }
        else if (senemy3.x + senemy3.width > platforms[26].rect.x + platforms[26].rect.w)
        {
            senemy3.x = platforms[26].rect.x + platforms[26].rect.w - senemy3.width;
            senemy3.dx = -3.0f;
        }

        senemy4.x += senemy4.dx;
        if (senemy4.x < platforms[32].rect.x)
        {
            senemy4.x = platforms[32].rect.x;
            senemy4.dx = 3.0f;
        }
        else if (senemy4.x + senemy4.width > platforms[32].rect.x + platforms[32].rect.w)
        {
            senemy4.x = platforms[32].rect.x + platforms[32].rect.w - senemy4.width;
            senemy4.dx = -3.0f;
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
            int winAction = showWinScreen(&gameStartTime, &gameMusicStarted, &shouldPlayGameMusic, player.coins_collected);            if (winAction == 1)
            { 

                exit(0);
                /* int menuAction = showMenu(&gameStartTime, &gameMusicStarted, &shouldPlayGameMusic);

                if (menuAction == 1)
                {
                    player.health = 3;
                    player.isDead = false;
                    break;
                } */
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
        checkEnemieCollisions(&player, &menemy5);
        checkEnemieCollisions(&player, &menemy6);
        checkEnemieCollisions(&player, &menemy7);
        checkEnemieCollisions(&player, &menemy8);
        checkEnemieCollisions(&player, &senemy1);
        checkEnemieCollisions(&player, &senemy2);
        checkEnemieCollisions(&player, &senemy3);
        checkEnemieCollisions(&player, &senemy4);
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
        blit(menemy5.texture, (int)menemy5.x, (int)menemy5.y);
        blit(menemy6.texture, (int)menemy6.x, (int)menemy6.y);
        blit(menemy7.texture, (int)menemy7.x, (int)menemy7.y);
        blit(menemy8.texture, (int)menemy8.x, (int)menemy8.y);
        blit(senemy1.texture, (int)senemy1.x, (int)senemy1.y);
        blit(senemy2.texture, (int)senemy2.x, (int)senemy2.y);
        blit(senemy3.texture, (int)senemy3.x, (int)senemy3.y);
        blit(senemy4.texture, (int)senemy4.x, (int)senemy4.y);
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
