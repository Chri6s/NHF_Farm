#ifndef MAP_H
#define MAP_H

#include "definitions.h"
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

extern Map* map;

void initializeMap(const char* name);

void loadMap(const char* filename);

void unloadMap(Map* map);

#endif