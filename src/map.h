#ifndef MAP_H
#define MAP_H

#include "definitions.h"
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>


Map* initializeMap(const char* name);

void loadMap(const char* filename, Map* map);

void unloadMap(Map* map);

#endif