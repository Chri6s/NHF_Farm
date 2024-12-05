#include "map.h"
#include "debugmalloc.h"
#include <stdio.h>



Map* initializeMap(const char* name) {
    Map* map = (Map*)malloc(sizeof(Map));
    if (map == NULL) {
        printf("Error: Could not allocate memory for map\n");
        return;
    }

    // Set map name
    strncpy(map->name, name, sizeof(map->name) - 1);
    map->name[sizeof(map->name) - 1] = '\0';  // Ensure null termination
    // Initialize all blocks to default values
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            int rotation = (rand() % 3) * 90;
            map->blocks[x][y].id = 0;
            map->blocks[x][y].x = x;
            map->blocks[x][y].y = y;
			map->blocks[x][y].rotation = rotation;
            map->blocks[x][y].planatable = 0;
        }
    }
    return map;
}

void loadMap(const char* filename, Map* map) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Could not open map file: %s\n", filename);
        return;
    }

    // Allocate memory for the map if it hasn't been initialized
    if (map == NULL) {
        map = (Map*)malloc(sizeof(Map));
        if (map == NULL) {
            printf("Error: Could not allocate memory for map\n");
            fclose(file);
            return;
        }
    }

    // Read map name
    size_t read_name = fread(map->name, sizeof(char), sizeof(map->name), file);
    if (read_name != sizeof(map->name)) {
        printf("Error: Failed to read map name\n");
        fclose(file);
        return;
    }

    // Read block data
    size_t read_blocks = fread(map->blocks, sizeof(Block), MAP_WIDTH * MAP_HEIGHT, file);
    if (read_blocks != MAP_WIDTH * MAP_HEIGHT) {
        printf("Error: Failed to read block data\n");
        fclose(file);
        return;
    }

    fclose(file);
    printf("Map loaded successfully: %s\n", map->name);
}

void saveMap(const char* filename, Map* map) {
    if (map == NULL) {
        printf("Error: No map to save\n");
        return;
    }

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Could not create map file: %s\n", filename);
        return;
    }

    // Write map name
    fwrite(map->name, sizeof(char), sizeof(map->name), file);

    // Write block data
    fwrite(map->blocks, sizeof(Block), MAP_WIDTH * MAP_HEIGHT, file);

    fclose(file);
    printf("Map saved successfully as: %s\n", map->name);
}

void unloadMap(Map* map) {
    if (map != NULL) {
        free(map);
        map = NULL;
    }
}