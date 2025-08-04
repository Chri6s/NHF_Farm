#pragma once
#include "sdl_includes.h"

struct Character;
struct Hotbar;
struct Item;

void updatePlayerPos(struct Character* player);
void handleKeyboardInput(struct Character* player, const Uint8* keystate);
void initHotbar(struct Hotbar* hotbar);
void initPlayer(struct Character* player);
void removeItemFromHotbar(struct Hotbar* hotbar, int slotIndex);
int addItemToHotbar(struct Hotbar* hotbar, struct Item* item, int slotIndex);
void freeHotbar(struct Hotbar* hotbar);
