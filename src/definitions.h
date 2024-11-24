#pragma once
#define MAP_WIDTH 80
#define MAP_HEIGHT 80
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define MAX_TILES 16
#define ORIGINAL_TILE_SIZE 16
#define SCALINGFACTOR 4
#define TILE_SIZE (ORIGINAL_TILE_SIZE * SCALINGFACTOR)
#define FRAME_DELAY (1000 / settings.target_fps)
#define cryptoKey "FarmR"