#pragma once

#include "definitions.h"
#include <SDL.h>

typedef struct {
	int x, y, id, rotation;
	int planatable;
} Block;

typedef struct {
    float x, y;
    int width, height;
    SDL_Texture* texture;
} Character;

typedef struct {
	Block blocks[MAP_HEIGHT][MAP_WIDTH];
	char name[];
} Map;

typedef struct {
	float x, y;
	int width, height;
} Camera;

typedef struct {
	int screen_x, screen_y, target_fps;
} GameSettings;
// define here, to access everywhere
Map map; // The main map which stores every block and its data.