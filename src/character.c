#include "character.h"
#include "structures.h"
#include <SDL.h>

void handleInput(Character* player, const Uint8* keystate, float deltaTime) {
	float speed = 394.5f;
	if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) moveCharacter(player, 0, -speed * deltaTime);
	if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) moveCharacter(player, 0, speed * deltaTime);
	if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) moveCharacter(player, -speed * deltaTime, 0);
	if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) moveCharacter(player, speed * deltaTime, 0);
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