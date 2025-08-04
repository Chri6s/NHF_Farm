#pragma once

#include "include/map_structs.h"
#include "include/sdl_includes.h"

struct Map;

Map* initializeMap(const char* name);
void loadMap(const char* filename, struct Map* map);
void unloadMap(struct Map* map);
