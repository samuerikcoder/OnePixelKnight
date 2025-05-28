#ifndef LIBS_H
#define LIBS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define X_MOVEMENT 5.0f
#define Y_MOVEMENT 8.0f

#define SMALL_W 80
#define SMALL_H 16
#define MEDIUM_W 176
#define MEDIUM_H 16
#define LARGE_W 256
#define LARGE_H 16
#define BG_W 1000
#define BG_H 500

#define MAX_COINS 100

#define DEATH_Y_COORDINATE 800

#define INTANGIBILITY_DURATION 2000

extern TTF_Font *gameFont;

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int up;
    int down;
    int left;
    int right;
    SDL_Rect camera;
    float zoom;
    SDL_Texture *textureSmalld;
    SDL_Texture *textureMediumd;
    SDL_Texture *textureLarged;
    SDL_Texture *textureSmallb;
    SDL_Texture *textureMediumb;
    SDL_Texture *textureLargeb;
    SDL_Texture *texturebg1;
    SDL_Texture *healthBarTexture;
    SDL_Texture *cameraTexture;
    SDL_Texture *coinTexture;
} App;

typedef struct Entity {
    float x, y;
    float dx, dy;
    SDL_Texture *texture;
    int grounded;
    int width, height;

    int health;
    bool isIntangible;
    int intangibleTimer;

    bool isShaking;
    int shakeTimer;

    bool isDead;

    int coins_collected;
} Entity;


typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
} Platform;

typedef enum {
    COIN_TYPE_NORMAL = 1,
    COIN_TYPE_LARGE = 5
} CoinType;

typedef struct {
    int x, y;
    int width, height;
    bool collected;
    CoinType type; 
} Coin;

extern App app;
extern Entity player;
extern Platform platforms[];
extern int numPlatforms;
extern SDL_Texture *textureSmalld;
extern SDL_Texture *textureMediumd;
extern SDL_Texture *textureLarged;
extern SDL_Texture *textureSmallb;
extern SDL_Texture *textureMediumb;
extern SDL_Texture *textureLargeb;
extern SDL_Texture *texturebg1; 
extern SDL_Texture *healthBarTexture; 
extern SDL_Texture *cameraTexture;  

extern Coin coins[MAX_COINS];
extern int num_active_coins;
extern SDL_Texture *coinTexture;
extern SDL_Texture *largeCoinTexture;


extern TTF_Font *gameFont;

extern Mix_Music *currentMusic;
extern Mix_Chunk *jumpSound;
extern Mix_Chunk *damageSound;
extern Mix_Chunk *deathSound;
extern Mix_Chunk *startGameSound;
extern Mix_Chunk *coinPickupSound;



int showWinScreen(Uint32 *gameStartTime, bool *gameMusicStarted, bool *shouldPlayGameMusic, int coinsCollected);
void initSDL(void);
void cleanup(void);
void prepareScene(void);
void prepareMenuScene(void);
void doInput(void);
void presentScene(void);
SDL_Texture *loadTexture(const char *filename);
void blit(SDL_Texture *texture, int x, int y);
void drawPlatforms(void);
void initGame(void);
int showMenu(Uint32 *gameStartTime, bool *gameMusicStarted, bool *shouldPlayGameMusic);
extern SDL_Texture *healthBarTexture;
void checkEnemieCollisions(Entity *player, Entity *enemie);
void delay(int number_of_seconds);
void drawPlayerShaking(Entity *player);

void initTextures(void);
void initPlatforms(void);
void initAudio(void);
void jumpSoundEffect(void);
void damageSoundEffect(void);
void deathSoundEffect(void);
void menuMusic(void);
void gameMusic(void);
void playMusic(const char *filename);
void closeAudio(void);
void startGameSoundEffect(void);
void checkIfPlayerIsDead(Entity *player);
int showDeathScreen(Uint32 *gameStartTime, bool *gameMusicStarted, bool *shouldPlayGameMusic);
void saveScreenshot(SDL_Renderer *renderer, int width, int height);
void initLevelCoins(void);
void drawCoins(SDL_Renderer *renderer, App *camera_app);
void checkCoinCollisions(Entity *player);
void cleanupCoinSystem(void); 
void drawCoinUI(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture *iconTexture, int coinCount, int x, int y);
void initFont(void); 

#endif
