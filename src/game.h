#pragma once
#include "settings_structs.h"

// Forward declaration
struct Map;

int GameInit(GameSettings* settings);
void editTile(int tileX, int tileY, int replaceId, struct Map* map);
