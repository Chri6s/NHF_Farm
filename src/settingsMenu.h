#pragma once
#include "structures.h"
void drawDropdown(SDL_Renderer* renderer, Dropdown* dropdown);
void handleDropdownEvent(SDL_Event* event, Dropdown* dropdown);
int createSettingsMenu();
void getResolution(const char* resolution, int* width, int* height);
