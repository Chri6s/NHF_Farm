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
SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;
SDL_Texture* gameTexture = NULL;

void gameLoop(SDL_Renderer* renderer, Character* player, SDL_Texture* grassTexture, Camera* camera);
Uint32 frameStart;
int frameTime;
float deltaTime = 0.0f;

int GameInit() {

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return -1;
	}

	gameWindow = initWindow("FarmR", settings.screen_x, settings.screen_y);
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* grass = loadTexture("../assets/grass.png", gameRenderer);
	SDL_Texture* characterTexture = loadTexture("../assets/character.png", gameRenderer);
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			int rotation = (rand() % 3) * 90;
			Block block = {
				x,
				y,
				0,
				rotation,
				NULL
			};
			map.blocks[y][x] = block;
		}
	}
	SDL_Surface* iconSurface = IMG_Load("../assets/icon.png");
	SDL_SetWindowIcon(gameWindow, iconSurface);
	SDL_FreeSurface(iconSurface);
	Character* player = (Character*)malloc(sizeof(Character));
	initPlayer(player);
	Camera camera = { player->x - (settings.screen_x / 2),player->y - (settings.screen_y / 2), settings.screen_x, settings.screen_y};
	player->texture = characterTexture;
	gameLoop(gameRenderer, player, grass, &camera);

	//shutdown
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(characterTexture);
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);
	IMG_Quit();
	SDL_Quit();
	return 0;
}

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
		handleInput(player, keystate, deltaTime);
		SDL_RenderClear(renderer);
		renderGame(renderer, grassTexture, otherTexture, player, camera);
		SDL_RenderPresent(renderer);
		frameTime = SDL_GetTicks() - frameStart;
		if (FRAME_DELAY > frameTime) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
		deltaTime = (float)frameTime / 1000.0f; 
	}

}