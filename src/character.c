#include "character.h"
#include "structures.h"
#include "game.h"
#include <SDL.h>
#include <stdio.h>

/**
 * @brief Handles Keyboard inputs
 * @param player The player that data needs to be changed on input
 * @param keystate The key the user presses
 * @param deltaTime The deltaTime constant, used for calculating speed so it's not affected by FPS
 * @param event the main event gets emitted on input
 * @returns void
 */
void handleKeyboardInput(Character* player, const Uint8* keystate, float deltaTime, SDL_Event event) {
	float speed = 394.5f;
	int gkeypressed = 0;
	if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) moveCharacter(player, 0, -speed * deltaTime);
	if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) moveCharacter(player, 0, speed * deltaTime);
	if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) moveCharacter(player, -speed * deltaTime, 0);
	if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) moveCharacter(player, speed * deltaTime, 0);
	if (keystate[SDL_SCANCODE_G] && event.type == SDL_KEYDOWN && !gkeypressed) { 
		editMode = !editMode;
		gkeypressed = 1;
		printf("editMode is 1!");
	}
	if (event.type == SDL_KEYUP && keystate[SDL_SCANCODE_G]) {
		gkeypressed = 0;
	}
} 
/**
 * @brief Moves the character. Also handles boundary checking
 * @param player The Player that needs it's data to be changed
 * @param deltaX How much the player needs to be moved on the X axis
 * @param deltaY How much the player needs to be moved on the Y axis
 * @returns void
 */
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
/**
 * @brief Initializes the player's starting values
 * @param player The player that needs initialization
 * @returns void
 */
void initPlayer(Character* player) {
	player->x = (MAP_WIDTH * TILE_SIZE * SCALINGFACTOR) / 2;
	player->y = (MAP_HEIGHT * TILE_SIZE * SCALINGFACTOR) / 2;
	player->width = 16;
	player->height = 32;
	player->texture = NULL;
}