#include "ui_structs.h"
#include <stdio.h>

void renderButton(SDL_Renderer* renderer, SDL_Texture* texture, Button button) {
	printf("debug");

	SDL_RenderCopy(renderer, texture, NULL, &button.box);
}