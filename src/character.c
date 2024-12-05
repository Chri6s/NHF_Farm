#include "character.h"
#include "structures.h"
#include "game.h"
#include <SDL.h>

void handleKeyboardInput(Character* player, const Uint8* keystate, float deltaTime) {
	float speed = 394.5f;
	if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) moveCharacter(player, 0, -speed * deltaTime);
	if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) moveCharacter(player, 0, speed * deltaTime);
	if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) moveCharacter(player, -speed * deltaTime, 0);
	if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) moveCharacter(player, speed * deltaTime, 0);
	if (keystate[SDL_SCANCODE_G] || editMode == 0) { 
		editMode = 1;
	}
	else if (keystate[SDL_SCANCODE_G] || editMode == 1) {
		editMode = 0;
	};
} 

	// Pause menu toggle
	if (keystate[SDL_SCANCODE_ESCAPE] && !escapepressed) {
		escapepressed = 1;
		player->pauseMenuOpen = !player->pauseMenuOpen;
	}
	if (!keystate[SDL_SCANCODE_ESCAPE]) {
		escapepressed = 0;
	}

} 
/**
 * @brief Moves the character. Also handles boundary checking
 * @param player The Player that needs it's data to be changed
 * @param deltaX How much the player needs to be moved on the X axis
 * @param deltaY How much the player needs to be moved on the Y axis
 * @returns void
 */
void updatePlayerPos(Character* player) {
	Character* newPos = player;
	newPos->x += player->xSpeed;
	newPos->y += player->ySpeed;
	if (player->x < 0) player->x = 0;
	if (player->y < 0) player->y = 0;

	if (player->x > (MAP_WIDTH * TILE_SIZE ) - player->width)
		player->x = (float)(MAP_WIDTH * TILE_SIZE) - player->width;

	if (player->y > (MAP_HEIGHT * TILE_SIZE) - player->height)
		player->y = (float)(MAP_HEIGHT * TILE_SIZE) - player->height;

	player->xSpeed = 0;
	player->ySpeed = 0;
}
/**
 * @brief Adds an item to the hotbar
 * @param hotbar The hotbar that needs the item
 * @param item The item that needs to be added
 * @param slotIndex The slot index where the item needs to be added
 * @returns bool
 */
bool addItemToHotbar(Hotbar* hotbar, Item* item, int slotIndex) {
	if (hotbar == NULL || item == NULL || slotIndex < 0 || slotIndex > HOTBAR_SIZE) {
		return false;
	}
	hotbar->items[slotIndex].item = item;
    item->slot = slotIndex;
	printf("Added to Slot:\n", slotIndex);
	return true;
}
/**
 * @brief Removes an item from the hotbar
 * @param hotbar The hotbar that needs the item removed
 * @param slotIndex The slot index where the item needs to be removed
 * @returns void
 */
void removeItemFromHotbar(Hotbar* hotbar, int slotIndex) {
	if (hotbar == NULL || slotIndex < 0 || slotIndex > HOTBAR_SIZE) {
		if (hotbar->items[slotIndex].item != NULL) {
			free(hotbar->items[slotIndex].item);
			hotbar->items[slotIndex].item = NULL;
		}
	}
}

/**
 * @brief Initializes the hotbar with the items
 * @param hotbar The hotbar that needs to be initialized
 * @returns void
 */
void initHotbar(Hotbar* hotbar) {
	SDL_memset(hotbar, 0, sizeof(Hotbar));
	for (int i = 0; i < HOTBAR_SIZE; i++) {
		hotbar->items[i].slot.x = (settings.screen_x / 2 - hotbar->items[i].slot.w / 2) - (hotbar->items[i].slot.w / 2) - 3 * (ORIGINAL_TILE_SIZE * 4) + i * (ORIGINAL_TILE_SIZE * 4);
		hotbar->items[i].slot.y = (settings.screen_y - (ORIGINAL_TILE_SIZE * 4) - ORIGINAL_TILE_SIZE);
	}
	for (int i = 0; i < 8; i++) {
		SDL_Rect rect;
		rect.w = ORIGINAL_TILE_SIZE * 4;
		rect.h = ORIGINAL_TILE_SIZE * 4;
		rect.y = (settings.screen_y - (ORIGINAL_TILE_SIZE * 4) - ORIGINAL_TILE_SIZE);
		rect.x = (settings.screen_x / 2 - rect.w / 2) - (rect.w / 2) - 3 * (ORIGINAL_TILE_SIZE * 4) + i * (ORIGINAL_TILE_SIZE * 4);
		hotbar->items[i].slot = rect;
		hotbar->items[i].item = NULL;
	}
}
/**
 * @brief Frees the hotbar and all of it's items
 * @param hotbar The hotbar that needs to be freed
 * @returns void
 */
void freeHotbar(Hotbar* hotbar) {
    for (int i = 0; i < HOTBAR_SIZE; i++) {
        if (hotbar->items[i].item != NULL) {
            SDL_DestroyTexture(hotbar->items[i].item->texture);
			free(&hotbar->items[i]);
            hotbar->items[i].item = (Item*){0};
        }
    }
	free(hotbar);
}
/**
 * @brief Initializes the player's starting values
 * @param player The player that needs initialization
 * @returns void
 */
void initPlayer(Character* player) {
	player->x = (MAP_WIDTH / 2);
	player->y = (MAP_HEIGHT / 2);
	player->xSpeed = 0;
	player->ySpeed = 0;
	player->speed = 20;
	player->editMode = 1;
	player->width = TILE_SIZE;
	player->height = TILE_SIZE * 2;
	player->texture = NULL;
	player->hotbar.selectedSlot = 0;
	player->pauseMenuOpen = 0;
	player->selectedItem = player->hotbar.items[player->hotbar.selectedSlot];
}