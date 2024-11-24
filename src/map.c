#include "map.h"
Map *map;

void initializeMap() {
	map = (Map*)malloc(sizeof(Map) + sizeof(Block)*MAP_WIDTH*MAP_HEIGHT);
	if (map == NULL) {
		printf("Error: Could not allocate memory for map\n");
		return NULL;
	}
	for (int x = 0; x < MAP_WIDTH; x++) {
		for (int y = 0; y < MAP_HEIGHT; y++) {
			map->blocks[x][y].id = 0;
			map->blocks[x][y].x = x;
			map->blocks[x][y].y = y;
			map->blocks[x][y].planatable = 0;
		}
	}
}
void unloadMap() {
	free(map);
}


