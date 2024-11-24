#pragma once
#include "structures.h"
void drawDropdown(SDL_Renderer* renderer, Dropdown* dropdown);
void handleDropdownEvent(SDL_Event* event, Dropdown* dropdown);
void createSettingsMenu();
