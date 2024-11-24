#include "settingsMenu.h"
#include "main.h"
#include "structures.h"
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
TTF_Font* font = NULL;
/**
* @brief Draws a dropdown menu with its data defined in a Dropdown struct
* @param renderer The renderer that needs to handle the rendering of the Dropdown menu
* @param dropdown The data the menu needs to draw, selectable options, the number of options, the option that was selected etc.
* @returns void
*/
void drawDropdown(SDL_Renderer* renderer, Dropdown* dropdown) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &dropdown->box);
	SDL_SetRenderDrawColor(renderer, 205, 205, 205, 205);
	SDL_RenderFillRect(renderer, &dropdown->box);
	SDL_Color textColor = { 20, 20, 20, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, dropdown->options[dropdown->selectedOption], textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect = { dropdown->box.x + 5, dropdown->box.y + 5, textSurface->w, textSurface->h };
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	if (dropdown->open) {
		for (int i = 0; i < dropdown->optionCount; ++i) {
			SDL_Rect optionBox = { dropdown->box.x, dropdown->box.y + (i + 1) * dropdown->box.h,
								   dropdown->box.w, dropdown->box.h };
			SDL_RenderDrawRect(renderer, &optionBox);
			SDL_SetRenderDrawColor(renderer, 205, 205, 205, 1);
			SDL_RenderFillRect(renderer, &optionBox);
			textSurface = TTF_RenderText_Blended(font, dropdown->options[i], textColor);
			textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			SDL_Rect optionTextRect = { optionBox.x + 5, optionBox.y + 5, textSurface->w, textSurface->h };
			SDL_RenderCopy(renderer, textTexture, NULL, &optionTextRect);

			SDL_FreeSurface(textSurface);
			SDL_DestroyTexture(textTexture);
		}
	}
}


/**
* @brief Handles the events done on the dropdown menu
* @param event The event that got emitted
* @param dropdown The dropdown menu that has been affected.
* @returns void
*/
void handleDropdownEvent(SDL_Event* event, Dropdown* dropdown) {
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		int x = event->button.x, y = event->button.y;
		if (x >= dropdown->box.x && x <= dropdown->box.x + dropdown->box.w &&
			y >= dropdown->box.y && y <= dropdown->box.y + dropdown->box.h) {
			dropdown->open = !dropdown->open;
		}
		else if (dropdown->open) {
			for (int i = 0; i < dropdown->optionCount; ++i) {
				SDL_Rect optionBox = { dropdown->box.x, dropdown->box.y + (i + 1) * dropdown->box.h,
									   dropdown->box.w, dropdown->box.h };
				if (x >= optionBox.x && x <= optionBox.x + optionBox.w &&
					y >= optionBox.y && y <= optionBox.y + optionBox.h) {
					dropdown->selectedOption = i;
					dropdown->open = SDL_FALSE;
					break;
				}
			}
		}
	}
}

void createSettingsMenu() {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	font = TTF_OpenFont("../assets/fonts/Arial.ttf", 16);

	SDL_Window* window = SDL_CreateWindow("Game Settings",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	const char* fpsOptions[] = { "30", "60", "120" };
	const char* widthOptions[] = { "800", "1024", "1280", "1920" };
	const char* heightOptions[] = { "600", "768", "720", "1080" };

	Dropdown fpsDropdown = { fpsOptions, 3, 1, { 100, 50, 100, 30 }, SDL_FALSE };
	Dropdown widthDropdown = { widthOptions, 4, 1, { 300, 50, 100, 30 }, SDL_FALSE };
	Dropdown heightDropdown = { heightOptions, 4, 1, { 500, 50, 100, 30 }, SDL_FALSE };
	SDL_Rect startButton = { 600, 500, 100, 40 };

	SDL_bool running = SDL_TRUE;
	while (running) {
		Uint32 frameStart = SDL_GetTicks();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = SDL_FALSE;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				int x = event.button.x;
				int y = event.button.y;
				if (x >= startButton.x && x <= (startButton.x + startButton.w) &&
					y >= startButton.y && y <= (startButton.y + startButton.h)) {
					running = SDL_FALSE;
				}
			}
			handleDropdownEvent(&event, &fpsDropdown);
			handleDropdownEvent(&event, &widthDropdown);
			handleDropdownEvent(&event, &heightDropdown);

		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		drawDropdown(renderer, &fpsDropdown);
		drawDropdown(renderer, &widthDropdown);
		drawDropdown(renderer, &heightDropdown);

		SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
		SDL_RenderFillRect(renderer, &startButton);

		SDL_Color white = { 255, 255, 255, 255 };
		SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Start", white);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect textRect = { startButton.x + 10, startButton.y + 10, textSurface->w, textSurface->h };
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);

		SDL_RenderPresent(renderer);

		Uint32 frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < FRAME_DELAY) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}
	settings.target_fps = atoi(fpsOptions[fpsDropdown.selectedOption]);
	settings.screen_x = atoi(widthOptions[widthDropdown.selectedOption]);
	settings.screen_y = atoi(heightOptions[heightDropdown.selectedOption]);
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}