#include "structures.h"
#include <stdbool.h>
void updatePlayerPos(Character* player);
void handleKeyboardInput(Character* player, const Uint8* keystate, float deltaTime, SDL_Event event);
void initHotbar(Hotbar* hotbar);
void initPlayer(Character* player);
void removeItemFromHotbar(Hotbar* hotbar, int slotIndex);
bool addItemToHotbar(Hotbar* hotbar, Item* item, int slotIndex);
void freeHotbar(Hotbar* hotbar);