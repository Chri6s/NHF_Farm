#include "ui_structs.h"
#include <stdio.h>

void renderButton(SDL_Renderer* renderer, SDL_Texture* texture, Button button) {
	SDL_RenderCopy(renderer, texture, NULL, &button.box);
}

/*
* @brief Loads a texture from the specified path
* @param path The path to the image
* @param renderer The renderer to load the texture into
* @returns SDL_Texture*
*/
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (!loadedSurface) {
		printf("Can't load image. Error: %s", IMG_GetError());
		return NULL;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);
	return texture;
}