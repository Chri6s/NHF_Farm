#include "structures.h"
#include "definitions.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int checkForSavesFolder() {
    return access("../saves", F_OK) != -1 ? 1 : 0;
}

void generateSave() {
    for (int x = 0; x < MAP_WIDTH; x++) {
		for (int y = 0; y < MAP_HEIGHT; y++) {
			int rotation = (rand() % 3) * 90;
			Block block = {
				x,
				y,
				0,
				rotation,
				NULL
			};
			map.blocks[x][y] = block;
		}
	}
}
void createNewSave() {

};
void parseSaves() {
    
}