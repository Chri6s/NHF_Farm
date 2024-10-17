#include "character.h"
#include "structures.h"
#include <SDL.h>

void handleInput(Character* player, const Uint8* keystate) {
    if (keystate[SDL_SCANCODE_W]) moveCharacter(player, 0, -0.2);
    if (keystate[SDL_SCANCODE_S]) moveCharacter(player, 0, 0.2);
    if (keystate[SDL_SCANCODE_A]) moveCharacter(player, -0.2, 0);
    if (keystate[SDL_SCANCODE_D]) moveCharacter(player, 0.2, 0);
}

void moveCharacter(Character* player, float deltaX, float deltaY) {
    player->x += deltaX;
    player->y += deltaY;
}
void initPlayer(Character* player) {
    player->x = 0;
    player->y = 0;
    player->width = 16;
    player->height = 32;
    player->texture = NULL;
}