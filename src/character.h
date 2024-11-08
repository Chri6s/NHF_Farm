#include <SDL.h>
#include "structures.h"
void moveCharacter(Character* player, float deltaX, float deltaY);
void handleKeyboardInput(Character* player, const Uint8* keystate, float deltaTime, SDL_Event event);
void initPlayer(Character* player);