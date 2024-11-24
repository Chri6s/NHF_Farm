#pragma once

#include "definitions.h"
#include <SDL.h>

typedef struct {
	int x, y, id, rotation;
	int planatable;
} Block;

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
