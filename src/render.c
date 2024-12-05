#include "main.h"
#include "render.h"
#include "definitions.h"
#include "structures.h"
#include "map.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "settingsMenu.h"
#include "pauseMenu.h"
/**
* @brief This function is the main logic of the Camera, used for checking if the camera's edges hit the bounds.
* @param camera The camera that needs this logic
* @param player The player that the camera needs to track
* @returns void
*/
void updateCamera(Camera* camera, Character* player) {
	// Center the camera on the player
	camera->x = player->x + (player->width / 2) - (camera->width / 2);
	camera->y = player->y + (player->height / 2) - (camera->height / 2);

	if (camera->x < 0) camera->x = 0;
	if (camera->y < 0) camera->y = 0;

	int mapWidth = TILE_SIZE * MAP_WIDTH;
	int mapHeight = TILE_SIZE * MAP_HEIGHT;

	// Border checking for the camera
	if (camera->x > mapWidth - camera->width) {
		camera->x = mapWidth - camera->width;
	}
	if (camera->y > mapHeight - camera->height) {
		camera->y = mapHeight - camera->height;
	}

}





/*
* @brief Renders the map with predefined textures. This is the main rendering function that is used to render the tiles and playarea. Currently built to only handle 2 types of tiles, the functionality of rendering any type of
* tile is planned. This function is already made with the optimization of only rendering what the player can see, that's why the camera is a parameter for this function.
* @param renderer The renderer that needs the map to be rendered into
* @param grassTexture The texture of the grass (right now hardcoded, sadly)
* @param otherTexture The other texture that isn't grass (for example, farmland)
* @param camera The camera that's view need to be renderer.
* @returns void
*/
void renderMap(SDL_Renderer* renderer, SDL_Texture* grassTexture, SDL_Texture* otherTexture, Camera* camera, Map* map) {
	int startTileX = camera->x / (TILE_SIZE);
	int startTileY = camera->y / (TILE_SIZE);
	int endTileX = (camera->x + camera->width) / (TILE_SIZE);
	int endTileY = (camera->y + camera->height) / (TILE_SIZE);

	if (startTileX < 0) startTileX = 0;
	if (startTileY < 0) startTileY = 0;
	if (endTileX >= MAP_WIDTH) endTileX = MAP_WIDTH - 1;
	if (endTileY >= MAP_HEIGHT) endTileY = MAP_HEIGHT - 1;

	for (int x = startTileX; x <= endTileX; x++) {
		for (int y = startTileY; y <= endTileY; y++) {
			SDL_Rect dest = {
				(x * TILE_SIZE) - camera->x,
				(y * TILE_SIZE) - camera->y,
				TILE_SIZE,
				TILE_SIZE
			};
			Block currentBlock = map->blocks[x][y];
			if (currentBlock.id == 0) {
				SDL_RenderCopyEx(renderer, grassTexture, NULL, &dest, 0, 0, currentBlock.rotation);
			}
			else if (currentBlock.id == 1) {
				SDL_RenderCopy(renderer, otherTexture, NULL, &dest);
			}
		}
	}
}
/*
*  @brief Renders the character onto the screen. Animations are not yet implemented, this function is very likely to be removed.
*  @param renderer The renderer where the Character needs to be rendered
*  @param player The player to render
*  @param camera The camera that is locked onto the player
*  @returns void
*/
void renderCharacter(SDL_Renderer* renderer, Character* player, Camera* camera) {
	SDL_Rect dest = {
		player->x - camera->x,
		player->y - camera->y,
		player->width,
		player->height
	};
	SDL_RenderCopy(renderer, player->texture, NULL, &dest);
}
/*
* @brief Renders an outline for the selected Tile. Used in Edit mode.
* @param renderer The renderer, context.
* @param selectedTileX [Map index, not pixel!] The selected Tile's X coordinate in the map matrix Re=[0,79]
* @param selectedTileY [Map index, not pixel!] The selected Tile's Y coordinate in the map matrix Re=[0,79]
* @returns void
*/
void renderTileOutline(SDL_Renderer* renderer, int selectedTileX, int selectedTileY, Camera* camera) {
	if (selectedTileX >= 0 && selectedTileY >= 0) {
		SDL_Rect outlineRect = {
			(selectedTileX * TILE_SIZE) - camera->x,
			(selectedTileY * TILE_SIZE) - camera->y,
			TILE_SIZE,
			TILE_SIZE
		};
		SDL_SetRenderDrawColor(renderer, 204, 204, 204, 255);
		SDL_RenderDrawRect(renderer, &outlineRect);
		for (int i = 0; i < 3; ++i) {  // Adjust the loop count to make it thicker
			SDL_Rect outlineRect = {
				(selectedTileX * TILE_SIZE - camera->x) + i,        // Shift right by i pixels
				(selectedTileY * TILE_SIZE - camera->y) + i,        // Shift down by i pixels
				TILE_SIZE - 2 * i, // Decrease width by 2*i to keep centered
				TILE_SIZE - 2 * i // Decrease height by 2*i to keep centered
			};
			SDL_RenderDrawRect(renderer, &outlineRect);
		}

	}
}
/*
* @brief Handles the order of rendering the visual components of the game. Wrapper function, better to only reference this one function than individually each one.
* @param renderer The renderer desired for the game
* @param grassTexture The texture for the grass (hardcoded)
* @param otherTexture The texture outside of grass (farmland)
* @param player The player's data
* @param camera The camera's data
* @returns void
*/
void renderGame(SDL_Renderer* renderer, SDL_Texture* grassTexture, SDL_Texture* otherTexture, Character* player, Camera* camera, Map* map) {
	updateCamera(camera, player);
	updatePlayerPos(player);
	renderMap(renderer, grassTexture, otherTexture, camera, map);
	renderCharacter(renderer, player, camera);
	SDL_RenderPresent(renderer);
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
/*
* @brief Helper function, creates a screen centered on the screen.
* @param windowName The name of the window
* @param width The width of the window in pixels
* @param height The height of the window in pixels
* @returns SDL_Window*
*/
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
void renderButton(SDL_Renderer* renderer, SDL_Texture* texture, Button button) {
	SDL_RenderCopy(renderer, texture, NULL, &button.box);
}