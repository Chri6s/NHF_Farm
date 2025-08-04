#pragma once
#include "sdl_includes.h"

typedef struct Button {
	char* name;
	SDL_Rect box;
} Button;

typedef struct SaveFile {
	char* name;
	SDL_Rect box;
} SaveFile;

void renderButton(SDL_Renderer* renderer, SDL_Texture* texture, Button button);
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);