#pragma	once
#include "sdl_includes.h"
#include "../definitions.h"

typedef struct Item {
	char name[20];
	int id;
	int srcX, srcY, srcW, srcH;
	int quantity;
	int slot;
	SDL_Texture* texture;
} Item;

typedef struct HotbarSlot {
	SDL_Rect slot;
	Item* item;
} HotbarSlot;

typedef struct Hotbar {
	HotbarSlot items[HOTBAR_SIZE];
	int selectedSlot;
	int x, y, w, h;
} Hotbar;
