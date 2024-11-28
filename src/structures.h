#pragma once

#include "definitions.h"
#include <SDL.h>

typedef struct {
	int x, y, id, rotation;
	int planatable;
} Block;

typedef struct {
	char* name;
	SDL_Rect box;
} Button;

typedef struct {
	char* name;
	SDL_Rect box;
} SaveFile;

typedef struct {
	char name[20];
	int id;
	int srcX, srcY, srcW, srcH;
	int quantity;
	int slot;
	SDL_Texture* texture;
} Item;

typedef struct {
	SDL_Rect slot;
	Item* item;
} HotbarSlot;

typedef struct {
	HotbarSlot items[HOTBAR_SIZE];
	int selectedSlot;
	int x, y, w, h;
} Hotbar;

typedef struct {
	Block blocks[MAP_WIDTH][MAP_HEIGHT];
	char name[50]; // map name is same as save name
} Map;

typedef struct {
	int x, y;
	int xSpeed, ySpeed;
	float speed;
	int editMode;
	int width, height;
	HotbarSlot selectedItem;
	Hotbar hotbar;
	SDL_Texture* texture;
} Character;


typedef struct {
	float x, y;
	int width, height;
} Camera;

typedef struct {
	int screen_x, screen_y, target_fps;
} GameSettings;

typedef struct {
	char saveName[50];
	char LastPlayed[12];
	Map *mapdata;
} Save;

typedef struct {
	const char** options;
	int optionCount;
	int selectedOption;
	SDL_Rect box;
	SDL_bool open;
} Dropdown;
