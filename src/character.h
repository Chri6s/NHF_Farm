#include <SDL.h>
#include "structures.h"
void updatePlayerPos(Character* player);
void handleKeyboardInput(Character* player, const Uint8* keystate, float deltaTime, SDL_Event event);
void initPlayer(Character* player);