#include "game.h"
/*
						The main Game controller.
								<game.c>
		   This file is the main "conductor" of this orchestra.
	Making the renderer load tiles, draw tiles and other game mechanics.;
*/
#include "definitions.h"
#include "structures.h"
#include "render.h"
#include "character.h"
#include "main.h"
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "saveManager.h"

SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;
SDL_Texture* gameTexture = NULL;

void gameLoop(SDL_Renderer* renderer, Character* player, SDL_Texture* grassTexture, Camera* camera);
Uint32 frameStart;
int frameTime;
float deltaTime = 0.0f;
int editMode = 1;

/**
* @brief The main Initalization function for the game.
* @returns void
*/
void GameInit() {

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return -1;
	}

	gameWindow = initWindow("FarmR", settings.screen_x, settings.screen_y);
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* grass = loadTexture("../assets/grass.png", gameRenderer);
	SDL_Texture* characterTexture = loadTexture("../assets/character.png", gameRenderer);
	SDL_Surface* iconSurface = IMG_Load("../assets/icon.png");
	SDL_SetWindowIcon(gameWindow, iconSurface);
	SDL_FreeSurface(iconSurface);
	Character* player = (Character*)malloc(sizeof(Character));
	initPlayer(player);
	Camera camera = { player->x - (settings.screen_x / 2),player->y - (settings.screen_y / 2), settings.screen_x, settings.screen_y};
	player->texture = characterTexture;
	if(checkForSavesFolder() == 0) {
		if(system("mkdir -p ../saves") == 0) {
			return 1;
		} else {
			return -1;
		}
		return 0;
	}
	gameLoop(gameRenderer, player, grass, &camera);

	//shutdown
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(characterTexture);
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);
	IMG_Quit();
	SDL_Quit();
}
/**
* @brief Edits the Tile at the coordinate
* @param tileX The X coordinate of the choosen tile
* @param tileY The Y coordinate of the choosen tile 
* @returns void
*/
void editTile(int tileX, int tileY) {
	if (tileX >= 0 && tileY >= 0 && tileX < MAP_WIDTH && tileY < MAP_HEIGHT) {
		// Check if tile is already farmland; if not, change it
		if (map.blocks[tileX][tileY].id != 1) {
			printf("edited!");
			map.blocks[tileX][tileY].id = 1;
		}
	}
}
/**
* @brief Handles the logic for editing the map when switching on edit mode with G
* @param camera The camera's X and Y coordinates are needed for calculating the currently selected Tile
* @param event The event used for checking if the player clicked a Tile to edit.
* @returns void
*/
void editMap(Camera* camera, SDL_Event event) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	int selectedTileX = (mouseX / SCALINGFACTOR + camera->x) / TILE_WIDTH;
	int selectedTileY = (mouseY / SCALINGFACTOR + camera->y) / TILE_HEIGHT;
	printf("%d ", selectedTileX);
	printf("%d\n", selectedTileY);
	renderTileOutline(gameRenderer, selectedTileX, selectedTileY);
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			editTile(selectedTileX, selectedTileY);
		}
	}
}
/*
* @brief The main loop needed for rendering, keypress checking and things that need constant update (like timestamps, timers etc.)
* @param renderer The main renderer used for the game
* @param player The player's data in Character typedef form
* @param grassTexture In this version, the texture handling and loading is not yet present, therefore we just pass down this Texture for further use
* @param camera The camera used for tracking the player
* @returns void
*/
void gameLoop(SDL_Renderer* renderer, Character* player, SDL_Texture* grassTexture, Camera* camera) {
	SDL_Event event;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	SDL_Texture* otherTexture = loadTexture("../assets/farmland1.png", renderer);
	int quit = 0;
	while (quit == 0) {
		frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			}
		}

		handleKeyboardInput(player, keystate, deltaTime, event);
		SDL_RenderClear(renderer);
		renderGame(renderer, grassTexture, otherTexture, player, camera);
		if (editMode == 1) editMap(camera, event);

		SDL_RenderPresent(renderer);
		frameTime = SDL_GetTicks() - frameStart;
		if (FRAME_DELAY > frameTime) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
		deltaTime = (float)frameTime / 1000.0f; 
	}

}
