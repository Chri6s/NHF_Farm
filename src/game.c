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
#include "saveManager.h"
#include "map.h"
#include "mainMenu.h"
#include "pauseMenu.h"
#include <stdlib.h>
#include <stdio.h>

SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;
SDL_Texture* gameTexture = NULL;

int offsetX = 0, offsetY = 0, tileX = 0, tileY = 0;
int PauseMenuReturns = 999;	
void gameLoop(SDL_Renderer* renderer, Character* player, SDL_Texture* grassTexture, Camera* camera);
Uint32 frameStart;
int frameTime;
float deltaTime = 0.0f;
int editMode = 0;

/**
* @brief The main Initalization function for the game.
* @returns void
*/
int GameInit() {
	PauseMenuReturns = 999;
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return -1;
	}

	gameWindow = initWindow("FarmR", settings.screen_x, settings.screen_y);
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_TEXTUREACCESS_TARGET);
	if (MainMenu(gameRenderer) == 0) {
		return 0;
	}

	SDL_Texture* grass = loadTexture("../assets/grass.png", gameRenderer);
	SDL_Texture* characterTexture = loadTexture("../assets/character.png", gameRenderer);
	SDL_Surface* iconSurface = IMG_Load("../assets/icon.png");

	SDL_SetWindowIcon(gameWindow, iconSurface);
	SDL_FreeSurface(iconSurface);

	Character* player = (Character*)malloc(sizeof(Character));
	initPlayer(player);

	Save* save = (Save*)malloc(sizeof(Save));
	Camera camera = { (MAP_WIDTH / 2) * TILE_SIZE, (MAP_HEIGHT / 2) * TILE_SIZE, settings.screen_x, settings.screen_y };;
	player->texture = characterTexture;

	initializeMap("NewGame");
	if(checkForSavesFolder() == 0) {
		if(system("mkdir -p ./saves") == 0) {
			return 1;
		} else {
			return -1;
		}
		return 0;
	}
	gameLoop(gameRenderer, player, grass, &camera);

	//shutdown
	free(player);
	free(save);
	unloadMap(map);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(characterTexture);
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);
	IMG_Quit();
	SDL_Quit();
	if (PauseMenuReturns == 2) GameInit();
	return 0;
}
/**
* @brief Edits the Tile at the coordinate
* @param tileX The X coordinate of the choosen tile
* @param tileY The Y coordinate of the choosen tile 
* @returns void
*/
void editTile(int tileX, int tileY, int replaceId) {
	if (tileX >= 0 && tileY >= 0 && tileX < MAP_WIDTH && tileY < MAP_HEIGHT) {
		// Check if tile is already farmland; if not, change it
		if (map->blocks[tileX][tileY].id != 1 && replaceId == 1) {
			map->blocks[tileX][tileY].id = 1;
		}
		else if (map->blocks[tileX][tileY].id != 0 && replaceId == 0) {
			map->blocks[tileX][tileY].id = 0;
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
		while (SDL_PollEvent(&event)) {
			frameStart = SDL_GetTicks();
			if (event.type == SDL_QUIT) {
				quit = 1;
				return NULL;
			}
			else if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					settings.screen_x = event.window.data1;
					settings.screen_x = event.window.data2;
					camera->height = settings.screen_y;
					camera->width = settings.screen_x;

				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT && player->editMode) {
				editTile(tileX, tileY, 1);
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && player->editMode) {
				editTile(tileX, tileY, 0);
			}
		}

		handleKeyboardInput(player, keystate);
		SDL_RenderClear(renderer);
		renderGame(renderer, grassTexture, otherTexture, player, camera);
		if (player->pauseMenuOpen) {
			SDL_Texture* background = generateBackground(renderer);
			PauseMenuReturns = PauseMenu(gameRenderer, player, background);
		}
		if (PauseMenuReturns == 2 || PauseMenuReturns == 0) quit = 1;
		if (player->editMode && !player->pauseMenuOpen) {
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			offsetX = mouseX + camera->x;
			offsetY = mouseY + camera->y;

			tileX = offsetX / TILE_SIZE;
			tileY = offsetY / TILE_SIZE;
			renderTileOutline(gameRenderer, tileX, tileY, camera);
		};

		SDL_RenderPresent(renderer);
		frameTime = SDL_GetTicks() - frameStart;
		if (FRAME_DELAY > frameTime) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
		deltaTime = (float)frameTime / 1000.0f; 
	}

}
