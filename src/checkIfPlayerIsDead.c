#include "libs.h"

void checkIfPlayerIsDead(Entity *player) {
    if (player->health <= 0) {
        player->isDead = true;
    }

    if (player->y > DEATH_Y_COORDINATE) {
    player->isDead = true;
    printf("Jogador morreu: Caiu abaixo de y=%d! Posição atual: %.2f\n", DEATH_Y_COORDINATE, player->y);
    }
}