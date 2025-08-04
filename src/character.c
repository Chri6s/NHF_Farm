#include "character.h"
#include "character_structs.h"
#include "game.h"
#include "main.h"
/**
 * @brief Handles Keyboard inputs
 * @param player The player that data needs to be changed on input
 * @param keystate The key the user presses
 * @param deltaTime The deltaTime constant, used for calculating speed so it's not affected by FPS
 * @param event the main event gets emitted on input
 * @returns void
 */
void handleKeyboardInput(Character* player, const Uint8* keystate) {
	player->xSpeed = 0;
	player->ySpeed = 0;
	static int gpressed = 0;
	static int escapepressed = 0;
	// movement
	if ((keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) && !player->pauseMenuOpen) player->ySpeed = -player->speed;
	if ((keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) && !player->pauseMenuOpen)  player->ySpeed = player->speed;
	if ((keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) && !player->pauseMenuOpen) player->xSpeed = -player->speed;
	if ((keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) && !player->pauseMenuOpen) player->xSpeed = player->speed;
	// hotbar / inventory
	if (keystate[SDL_SCANCODE_1]) player->hotbar.selectedSlot = 1;
	if (keystate[SDL_SCANCODE_2]) player->hotbar.selectedSlot = 2;
	if (keystate[SDL_SCANCODE_3]) player->hotbar.selectedSlot = 3;
	if (keystate[SDL_SCANCODE_4]) player->hotbar.selectedSlot = 4;
	if (keystate[SDL_SCANCODE_5]) player->hotbar.selectedSlot = 5;
	if (keystate[SDL_SCANCODE_6]) player->hotbar.selectedSlot = 6;
	if (keystate[SDL_SCANCODE_7]) player->hotbar.selectedSlot = 7;
	if (keystate[SDL_SCANCODE_8]) player->hotbar.selectedSlot = 8;
	if (keystate[SDL_SCANCODE_9]) player->hotbar.selectedSlot = 9;

	// Edit mode toggle
	if (keystate[SDL_SCANCODE_G] && !gpressed) {
		gpressed = 1;
		player->editMode = !player->editMode;
	}
	if (!keystate[SDL_SCANCODE_G]) {
		gpressed = 0;
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
int addItemToHotbar(Hotbar* hotbar, Item* item, int slotIndex) {
	if (hotbar == NULL || item == NULL || slotIndex < 0 || slotIndex > HOTBAR_SIZE) {
		return 0;
	}
	hotbar->items[slotIndex].item = item;
    item->slot = slotIndex;
	printf("Added to Slot: %d\n", slotIndex);
	return 1;
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
void initHotbar(Hotbar* hotbar, GameSettings* settings) {
	SDL_memset(hotbar, 0, sizeof(Hotbar));
	for (int i = 0; i < HOTBAR_SIZE; i++) {
		hotbar->items[i].slot.x = (settings->screen_x / 2 - hotbar->items[i].slot.w / 2) - (hotbar->items[i].slot.w / 2) - 3 * (ORIGINAL_TILE_SIZE * 4) + i * (ORIGINAL_TILE_SIZE * 4);
		hotbar->items[i].slot.y = (settings->screen_y - (ORIGINAL_TILE_SIZE * 4) - ORIGINAL_TILE_SIZE);
	}
	for (int i = 0; i < 8; i++) {
		SDL_Rect rect;
		rect.w = ORIGINAL_TILE_SIZE * 4;
		rect.h = ORIGINAL_TILE_SIZE * 4;
		rect.y = (settings->screen_y - (ORIGINAL_TILE_SIZE * 4) - ORIGINAL_TILE_SIZE);
		rect.x = (settings->screen_x / 2 - rect.w / 2) - (rect.w / 2) - 3 * (ORIGINAL_TILE_SIZE * 4) + i * (ORIGINAL_TILE_SIZE * 4);
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
	player->x = 40;
	player->y = 40;
	player->xSpeed = 0;
	player->ySpeed = 0;
	player->speed = 20;
	player->editMode = 0;
	player->width = TILE_SIZE;
	player->height = TILE_SIZE * 2;
	player->texture = NULL;
	player->hotbar.selectedSlot = 0;
	player->pauseMenuOpen = 0;
	player->selectedItem = player->hotbar.items[player->hotbar.selectedSlot];
}