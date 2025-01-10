#pragma once

#include "definitions.h"
#include "debugmalloc.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

typedef struct Block {
	int x, y, id, rotation;
	int planatable;
} Block;

typedef struct Button {
	char* name;
	SDL_Rect box;
} Button;

typedef struct SaveFile {
	char* name;
	SDL_Rect box;
} SaveFile;

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

typedef struct Map {
	Block blocks[MAP_WIDTH][MAP_HEIGHT];
	char name[50]; // map name is same as save name
} Map;

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

typedef struct GameSettings{
	int screen_x, screen_y, target_fps;
} GameSettings;

typedef struct Camera{
	float x, y;
	int width, height;
} Camera;

typedef struct Save {
	char saveName[50];
	char LastPlayed[12];
	Map *mapdata;
} Save;

typedef struct Dropdown {
	const char** options;
	int optionCount;
	int selectedOption;
	SDL_Rect box;
	SDL_bool open;
} Dropdown;
