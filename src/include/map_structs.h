#pragma once
#include "../definitions.h"

typedef struct Block {
	int x, y, id, rotation;
	int planatable;
} Block;

typedef struct Map {
	Block blocks[MAP_WIDTH][MAP_HEIGHT];
	char name[50]; // map name is same as save name
} Map;

typedef struct Save {
	char saveName[50];
	char LastPlayed[12];
	Map* mapdata;
} Save;