#include "main.h"
#include "render.h"
#include "definitions.h"
#include "structures.h"
#include <SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

void updateCamera(Camera* camera, Character* player) {
	camera->x = player->x - camera->width / 2;
	camera->y = player->y - camera->height / 2;
	//alignment
	camera->x = ((float)camera->x / (TILE_SIZE * SCALINGFACTOR)) * (TILE_SIZE * SCALINGFACTOR);
	camera->y = ((float)camera->y / (TILE_SIZE * SCALINGFACTOR)) * (TILE_SIZE * SCALINGFACTOR);

	//border checking
	if (camera->x < 0) { 
		camera->x = 0; 
	}
	if (camera->y < 0) {
		camera->y = 0;
	}

	if (camera->x > (MAP_WIDTH * TILE_SIZE * SCALINGFACTOR) - camera->width) {
		camera->x = (MAP_WIDTH * TILE_SIZE * SCALINGFACTOR) - camera->width;
	}
	if (camera->y > (MAP_HEIGHT * TILE_SIZE * SCALINGFACTOR) - camera->height) {
		camera->y = (MAP_HEIGHT * TILE_SIZE * SCALINGFACTOR) - camera->height;
	}
}

void renderMap(SDL_Renderer* renderer, SDL_Texture* grassTexture, SDL_Texture* otherTexture, Camera* camera) {
	int startTileX = camera->x / (TILE_SIZE * SCALINGFACTOR);
	int startTileY = camera->y / (TILE_SIZE * SCALINGFACTOR);
	int endTileX = (camera->x + camera->width) / (TILE_SIZE * SCALINGFACTOR);
	int endTileY = (camera->y + camera->height) / (TILE_SIZE * SCALINGFACTOR);

	if (startTileX < 0) startTileX = 0;
	if (startTileY < 0) startTileY = 0;
	if (endTileX >= MAP_WIDTH) endTileX = MAP_WIDTH - 1;
	if (endTileY >= MAP_HEIGHT) endTileY = MAP_HEIGHT - 1;

	for (int y = startTileY; y <= endTileY; y++) {
		for (int x = startTileX; x <= endTileX; x++) {
			SDL_Rect dest = {
				(x * TILE_SIZE * SCALINGFACTOR) - camera->x,
				(y * TILE_SIZE * SCALINGFACTOR) - camera->y,
				TILE_SIZE* SCALINGFACTOR,
				TILE_SIZE* SCALINGFACTOR
			};
			Block currentBlock = map.blocks[y][x];
			if (currentBlock.id == 0) {
				SDL_RenderCopyEx(renderer, grassTexture, NULL, &dest, 0, 0, currentBlock.rotation);
			}
			else if (currentBlock.id == 1) {
				SDL_RenderCopy(renderer, otherTexture, NULL, &dest);
			}
		}
	}
}
void renderCharacter(SDL_Renderer* renderer, Character* player, Camera* camera) {
	SDL_Rect dest;
	dest.x = (settings.screen_x / 2) - (player->width * SCALINGFACTOR / 2);
	dest.y = (settings.screen_y / 2) - (player->height * SCALINGFACTOR / 2);
	dest.w = (int)(player->width * SCALINGFACTOR);
	dest.h = (int)(player->height * SCALINGFACTOR);
	SDL_RenderCopy(renderer, player->texture, NULL, &dest);
}

void renderScene(SDL_Renderer* renderer, Character* player, SDL_Texture* grassTexture, Camera* camera) {
	for (int y = 0; y < player->y / TILE_SIZE; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			SDL_Rect dest = {
				x * TILE_SIZE * SCALINGFACTOR,
				y * TILE_SIZE * SCALINGFACTOR,
				TILE_SIZE * SCALINGFACTOR,
				TILE_SIZE * SCALINGFACTOR
			};
			SDL_RenderCopy(renderer, grassTexture, NULL, &dest);
		}
	}
	for (int x = 0; x < MAP_WIDTH; x++) {
		SDL_Rect dest = {
			x * TILE_SIZE * SCALINGFACTOR,
			(player->y / TILE_SIZE) * TILE_SIZE * SCALINGFACTOR,
			TILE_SIZE * SCALINGFACTOR,
			TILE_SIZE * SCALINGFACTOR
		};
		SDL_RenderCopy(renderer, grassTexture, NULL, &dest);
	}
	renderCharacter(renderer, player, camera);

	for (int y = player->y / TILE_SIZE + 1; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			SDL_Rect dest = {
				x * TILE_SIZE * SCALINGFACTOR,
				y * TILE_SIZE * SCALINGFACTOR,
				TILE_SIZE * SCALINGFACTOR,
				TILE_SIZE * SCALINGFACTOR
			};
			SDL_RenderCopy(renderer, grassTexture, NULL, &dest);
		}
	}

}

void renderGame(SDL_Renderer* renderer, SDL_Texture* grassTexture, SDL_Texture* otherTexture, Character* player, Camera* camera) {
	updateCamera(camera, player);
	renderMap(renderer, grassTexture, otherTexture, camera);
	renderCharacter(renderer, player, camera);
	SDL_RenderPresent(renderer);
}

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

SDL_Window* initWindow(const char* windowName, int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return NULL;
	}

	SDL_Window* window = SDL_CreateWindow(windowName,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_SHOWN);

	if (window == NULL) {
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}

	return window;
}
