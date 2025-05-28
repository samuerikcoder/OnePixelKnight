#include "libs.h"

Mix_Music *currentMusic = NULL;

Mix_Chunk *jumpSound = NULL;
Mix_Chunk *damageSound = NULL;
Mix_Chunk *deathSound = NULL;
Mix_Chunk *startGameSound = NULL;
Mix_Chunk *coinPickupSound = NULL;

Uint32 lastJumpSoundTime = 0;
Uint32 lastDamageSoundTime = 0;

#define MAX_CONCURRENT_JUMP_SOUNDS 5
#define JUMP_SOUND_COOLDOWN 200
#define DAMAGE_SOUND_COOLDOWN 150
#define JUMP_SOUND_CHANNEL 1

#define CRITICAL_SOUND_CHANNEL 0

void initAudio(void)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        printf("Erro ao iniciar SDL_mixer: %s\n", Mix_GetError());
        return;
    }
    Mix_AllocateChannels(32);
    Mix_ReserveChannels(1);

    jumpSound = Mix_LoadWAV("../assets/sounds/cartoon-jump-6462.wav");
    damageSound = Mix_LoadWAV("../assets/sounds/8-bit-damage.wav");
    deathSound = Mix_LoadWAV("../assets/sounds/videogame-death-sound-43894.wav");
    startGameSound = Mix_LoadWAV("../assets/sounds/start.wav");
    coinPickupSound = Mix_LoadWAV("../assets/sounds/coin.mp3");

    if (!jumpSound || !damageSound || !deathSound || !startGameSound || !coinPickupSound)
    {
        printf("Erro ao carregar efeitos sonoros: %s\n", Mix_GetError());
        return;
    }

    Mix_VolumeChunk(jumpSound, 100 / 8);
    Mix_VolumeChunk(damageSound, 128 / 8);
    Mix_VolumeChunk(deathSound, 128 / 8);
    Mix_VolumeChunk(startGameSound, 110 / 8);
    Mix_VolumeChunk(coinPickupSound, 128 / 8);

    Mix_VolumeMusic(50 / 8);
}

void jumpSoundEffect(void)
{
    int channel = Mix_PlayChannel(JUMP_SOUND_CHANNEL, jumpSound, 0);
    if (channel == -1)
    {
        printf("Falha ao tocar jumpSound (sem canais gerais livres): %s\n", Mix_GetError());
    }
    else
    {
        printf("Tocando jumpSound no canal %d\n", channel);
    }
}

void damageSoundEffect(void)
{
    Uint32 now = SDL_GetTicks();

    if (now - lastDamageSoundTime < DAMAGE_SOUND_COOLDOWN)
    {
        return;
    }

    if (damageSound)
    {
        int channel = Mix_PlayChannel(-1, damageSound, 0);
        if (channel == -1)
        {
            printf("Falha ao tocar damageSound (sem canais gerais livres): %s\n", Mix_GetError());
        }
        else
        {
            printf("Tocando damageSound no canal %d\n", channel);
            lastDamageSoundTime = now;
        }
    }
}

void deathSoundEffect(void)
{
    if (deathSound)
    {
        Mix_HaltChannel(CRITICAL_SOUND_CHANNEL);

        int channel = Mix_PlayChannel(CRITICAL_SOUND_CHANNEL, deathSound, 0);
        if (channel == -1)
        {
            printf("Falha CRÍTICA ao tocar deathSound no canal RESERVADO %d: %s\n", CRITICAL_SOUND_CHANNEL, Mix_GetError());
        }
        else
        {
            printf("deathSound tocando no canal RESERVADO %d\n", channel);
        }
    }
}

void startGameSoundEffect(void)
{
    if (startGameSound)
    {
        int channel = Mix_PlayChannel(-1, startGameSound, 0);
        if (channel == -1)
        {
            printf("Falha ao tocar startGameSound: %s\n", Mix_GetError());
        }
        else
        {
            printf("Tocando startGameSound no canal %d\n", channel);
        }
    }
}

void playMusic(const char *filepath)
{
    if (currentMusic != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(currentMusic);
        currentMusic = NULL;
    }

    currentMusic = Mix_LoadMUS(filepath);
    if (!currentMusic)
    {
        printf("Erro ao carregar música: %s\n", Mix_GetError());
        return;
    }

    if (Mix_PlayMusic(currentMusic, -1) == -1)
    {
        printf("Erro ao tocar música: %s\n", Mix_GetError());
        Mix_FreeMusic(currentMusic);
        currentMusic = NULL;
    }
}

void menuMusic(void)
{
    playMusic("../assets/sounds/8-bit-heaven-26287.mp3");
}

void gameMusic(void)
{
    playMusic("../assets/sounds/8-bit-dungeon-251388.mp3");
}

void closeAudio(void)
{
    if (jumpSound)
        Mix_FreeChunk(jumpSound);
    jumpSound = NULL;
    if (damageSound)
        Mix_FreeChunk(damageSound);
    damageSound = NULL;
    if (deathSound)
        Mix_FreeChunk(deathSound);
    deathSound = NULL;
    if (startGameSound)
        Mix_FreeChunk(startGameSound);
    startGameSound = NULL;

    if (currentMusic != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(currentMusic);
        currentMusic = NULL;
    }

    if (coinPickupSound)
        Mix_FreeChunk(coinPickupSound);
    coinPickupSound = NULL;

    Mix_CloseAudio();
}