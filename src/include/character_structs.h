#pragma once
#include "item_structs.h"

typedef struct Character {
	int x, y;
	int xSpeed, ySpeed;
	float speed;
	int editMode;
	int width, height;
	int pauseMenuOpen;
	HotbarSlot selectedItem;
	Hotbar hotbar;
	SDL_Texture* texture;
} Character;

typedef struct Camera {
	float x, y;
	int width, height;
} Camera;