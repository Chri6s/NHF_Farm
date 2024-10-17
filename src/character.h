#include <SDL.h>
#include "structures.h"
void moveCharacter(Character* player, float deltaX, float deltaY);
void handleInput(Character* player, const Uint8* keystate, float deltaTime);
void initPlayer(Character* player);