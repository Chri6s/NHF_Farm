#include "character.h"
#include "structures.h"
#include <SDL.h>

void handleInput(Character* player, const Uint8* keystate, float deltaTime) {
    float speed = 500.0f;
    if (keystate[SDL_SCANCODE_W]) moveCharacter(player, 0, -speed * deltaTime);
    if (keystate[SDL_SCANCODE_S]) moveCharacter(player, 0, speed * deltaTime);
    if (keystate[SDL_SCANCODE_A]) moveCharacter(player, -speed * deltaTime, 0);
    if (keystate[SDL_SCANCODE_D]) moveCharacter(player, speed * deltaTime, 0);
}

void moveCharacter(Character* player, float deltaX, float deltaY) {
    player->x += deltaX;
    player->y += deltaY;
    if (player->x < 0) player->x = 0;
    if (player->y < 0) player->y = 0;

    if (player->x > (MAP_WIDTH * TILE_SIZE * SCALINGFACTOR ) - player->width)
        player->x = (MAP_WIDTH * TILE_SIZE * SCALINGFACTOR ) - player->width;

    if (player->y > (MAP_HEIGHT * TILE_SIZE * SCALINGFACTOR) - player->height)
        player->y = (MAP_HEIGHT * TILE_SIZE * SCALINGFACTOR ) - player->height;

}
void initPlayer(Character* player) {
    player->x = (MAP_WIDTH * TILE_SIZE * SCALINGFACTOR) / 2;
    player->y = (MAP_HEIGHT * TILE_SIZE * SCALINGFACTOR) / 2;
    player->width = 16;
    player->height = 32;
    player->texture = NULL;
}