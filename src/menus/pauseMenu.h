#pragma once
#include "ui_structs.h"
#include "character_structs.h"
#include "settings_structs.h"

int PauseMenu(SDL_Renderer* renderer, Character* player, GameSettings* settings, SDL_Texture* background);
SDL_Texture* generateBackground(SDL_Renderer* renderer);