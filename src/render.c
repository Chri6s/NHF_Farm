#include "render.h"
#include "definitions.h"
#include "structures.h"
#include <SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

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
void updateCamera(Camera* camera, Character* player) {
	camera->x = player->x - (camera->width / 2) + (player->width / 2);
	camera->y = player->y - (camera->height / 2) + (player->height / 2);

	if (camera->x < 0) camera->x = 0;
	if (camera->x < 0) camera->y = 0;
	if (camera->x > (MAP_WIDTH * TILE_SIZE) - camera->width)
		camera->x = (MAP_WIDTH * TILE_SIZE) - camera->width;
	if (camera->y > (MAP_HEIGHT * TILE_SIZE) - camera->height)
		camera->y = (MAP_HEIGHT * TILE_SIZE) - camera->height;
}

void renderMap(SDL_Renderer* renderer, SDL_Texture* grassTexture, SDL_Texture* otherTexture, Camera* camera) {
	int startTileX = camera->x / TILE_SIZE;
	int startTileY = camera->y / TILE_SIZE;
	int endTileX = (camera->x + camera->width) / TILE_SIZE;
	int endTileY = (camera->y + camera->height) / TILE_SIZE;

	for (int y = startTileY; y <= endTileY; y++) {
		for (int x = startTileY; x < endTileX; x++) {
			SDL_Rect dest = {
				x * TILE_SIZE * SCALINGFACTOR - camera->x,
				y * TILE_SIZE * SCALINGFACTOR - camera->y,
				TILE_SIZE * SCALINGFACTOR,
				TILE_SIZE * SCALINGFACTOR
			};
			Block currentBlock = map.blocks[y][x];
			if (currentBlock.id == 0) {
				SDL_RenderCopyEx(renderer, grassTexture, NULL, &dest, 0, 0, currentBlock.rotation);
			}
			else if (map.blocks[y][x].id == 1) {
				SDL_RenderCopy(renderer, otherTexture, NULL, &dest);
			}
		}
	}
}
void renderCharacter(SDL_Renderer* renderer, Character* player, Camera* camera) {
	SDL_Rect dest = {
		(player->x * SCALINGFACTOR) - camera->x,
		player->y * SCALINGFACTOR - camera->y - (player->height * SCALINGFACTOR - TILE_SIZE * SCALINGFACTOR),
		player->width * SCALINGFACTOR,
		player->height * SCALINGFACTOR
	};
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


/*void generatePlayArea(SDL_Texture* tileTexture, int scaleFactor) {
	for (int y = 0; y <= MAP_HEIGHT; y++) {
		for (int x = 0; x <= MAP_WIDTH; x++) {
			SDL_Rect destRect = {
				x * tileWidth * scaleFactor,
				y * tileHeight * scaleFactor,
				tileWidth * scaleFactor,
				tileHeight * scaleFactor
			};
			Block block = {
				x,
				y,
				1,
				999
			};
			map.blocks[x][y] = block;
			switch (rand() % 2) {
			case 0:
				SDL_RenderCopyEx(gameRenderer, tileTexture, NULL, &destRect, 0, 0, 90);
				break;
			case 1:
				SDL_RenderCopyEx(gameRenderer, tileTexture, NULL, &destRect, 0, 0, 180);
				break;
			case 2:
				SDL_RenderCopyEx(gameRenderer, tileTexture, NULL, &destRect, 0, 0, 270);
				break;
			}
		}
	} 
	SDL_RenderPresent(gameRenderer);
}
*/
//void InitStage(void) {
//	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
//	SDL_SetRenderDrawColor(gameRenderer, 0xA1, 0xDA, 0xAA, 0xFF);
//	SDL_RenderClear(gameRenderer);
//}
//SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }