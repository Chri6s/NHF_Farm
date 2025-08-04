#pragma once
#include "ui_structs.h"
#include "settings_structs.h"

#define INITIAL_FRAME_DELAY (1000 / 60)

typedef struct Dropdown {
	const char** options;
	int optionCount;
	int selectedOption;
	SDL_Rect box;
	SDL_bool open;
} Dropdown;

int createSettingsMenu(GameSettings* settings);
