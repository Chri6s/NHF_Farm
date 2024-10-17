#pragma once

#include "definitions.h"
#include <SDL.h>

typedef struct {
	int x, y, id, growingProgress, rotation;
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
	int x, y;
	int width, height;
} Camera;

// define here, to access everywhere
Map map; // The main map which stores every block and its data.