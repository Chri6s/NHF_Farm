#include "pauseMenu.h"
#include "main.h"
#include "render.h"




SDL_Texture* generateBackground(SDL_Renderer* renderer) { // Valamiért ez a függvény nem tudja normálisan capture-olni a képernyőt, és csak egy szürke képet ad vissza...
		SDL_Rect viewport;
		SDL_RenderGetViewport(renderer, &viewport);

		// Create a target texture to hold the screenshot
		SDL_Texture* targetTexture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			viewport.w, viewport.h
		);

		// Store current render target
		SDL_Texture* previousTarget = SDL_GetRenderTarget(renderer);

		// Set new target and clear it
		SDL_SetRenderTarget(renderer, targetTexture);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		// Copy the current renderer content
		SDL_RenderCopy(renderer, previousTarget, NULL, NULL);

		// Reset to previous target
		SDL_SetRenderTarget(renderer, previousTarget);

		return targetTexture;
}


int PauseMenu(SDL_Renderer* renderer, Character* player, SDL_Texture* background) {
	SDL_Rect backgroundRect = { 0, 0, settings.screen_x, settings.screen_y };
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 120);
	SDL_RenderFillRect(renderer, NULL);

	SDL_Texture* resume = loadTexture("assets/resume.png", renderer);
	SDL_Texture* saveGame = loadTexture("assets/saveGame.png", renderer);
	SDL_Texture* BTM = loadTexture("assets/BTM.png", renderer);

	Button resumeButton = { "newGame", {settings.screen_x / 2 - 100, settings.screen_y / 2 - 100, 200, 50} };
	Button saveGameButton = { "loadGame", {settings.screen_x / 2 - 100, settings.screen_y / 2, 200, 50} };
	Button BTMButton = { "exit", {settings.screen_x / 2 - 100, settings.screen_y / 2 + 100, 200, 50} };

	renderButton(renderer, resume, resumeButton);
	renderButton(renderer, saveGame, saveGameButton);
	renderButton(renderer, BTM, BTMButton);
	SDL_RenderPresent(renderer);

	SDL_bool resumeClicked = SDL_FALSE;
	SDL_bool saveGameClicked = SDL_FALSE;
	SDL_bool BTMClicked = SDL_FALSE;
	SDL_bool escapePressed = SDL_FALSE;
	SDL_bool running = SDL_TRUE;
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = SDL_FALSE;
				return 0;
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (event.button.x >= resumeButton.box.x && event.button.x <= resumeButton.box.x + resumeButton.box.w && event.button.y >= resumeButton.box.y && event.button.y <= resumeButton.box.y + resumeButton.box.h) {
						resumeClicked = SDL_TRUE;
					}
					if (event.button.x >= saveGameButton.box.x && event.button.x <= saveGameButton.box.x + saveGameButton.box.w && event.button.y >= saveGameButton.box.y && event.button.y <= saveGameButton.box.y + saveGameButton.box.h) {
						saveGameClicked = SDL_TRUE;
					}
					if (event.button.x >= BTMButton.box.x && event.button.x <= BTMButton.box.x + BTMButton.box.w && event.button.y >= BTMButton.box.y && event.button.y <= BTMButton.box.y + BTMButton.box.h) {
						BTMClicked = SDL_TRUE;
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (event.button.x >= resumeButton.box.x && event.button.x <= resumeButton.box.x + resumeButton.box.w && event.button.y >= resumeButton.box.y && event.button.y <= resumeButton.box.y + resumeButton.box.h) {
						resumeClicked = SDL_FALSE;
						running = SDL_FALSE;
					}
					if (event.button.x >= saveGameButton.box.x && event.button.x <= saveGameButton.box.x + saveGameButton.box.w && event.button.y >= saveGameButton.box.y && event.button.y <= saveGameButton.box.y + saveGameButton.box.h) {
						saveGameClicked = SDL_FALSE;
						running = SDL_FALSE;
					}
					if (event.button.x >= BTMButton.box.x && event.button.x <= BTMButton.box.x + BTMButton.box.w && event.button.y >= BTMButton.box.y && event.button.y <= BTMButton.box.y + BTMButton.box.h) {
						BTMClicked = SDL_FALSE;
						running = SDL_FALSE;
					}
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					escapePressed = 1;
					break;
				}
			}
		}
		if (resumeClicked || escapePressed) {
			running = SDL_FALSE;
			player->pauseMenuOpen = 0;
			SDL_DestroyTexture(resume);
			SDL_DestroyTexture(saveGame);
			SDL_DestroyTexture(BTM);
			SDL_DestroyTexture(background);
			return 1;
		}
		if (saveGameClicked) {
			//ide majd a SavesMenu methodusa kell.
			player->pauseMenuOpen = 0;
			SDL_DestroyTexture(resume);
			SDL_DestroyTexture(saveGame);
			SDL_DestroyTexture(BTM);

			SDL_DestroyTexture(background);
			return 1;
		}
		if (BTMClicked) {
			running = SDL_FALSE;
			SDL_DestroyTexture(resume);
			SDL_DestroyTexture(saveGame);
			SDL_DestroyTexture(BTM);
			SDL_DestroyTexture(background);
			return 2;
		}
	}
	SDL_DestroyTexture(resume);
	SDL_DestroyTexture(saveGame);
	SDL_DestroyTexture(BTM);

	return NULL;
}

