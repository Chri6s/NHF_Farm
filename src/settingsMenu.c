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

void getResolution(const char* resolution, int* width, int* height) {
	char buffer[10]; // Assuming each part (width/height) won't exceed 10 characters
	int i = 0, j = 0;

	// Extract width
	while (resolution[i] != 'x' && resolution[i] != '\0') {
		buffer[j++] = resolution[i++];
	}
	buffer[j] = '\0'; // Null-terminate the string
	*width = atoi(buffer); // Convert width to integer

	if (resolution[i] == 'x') {
		i++; // Skip the 'x'
	}

	// Extract height
	j = 0;
	while (resolution[i] != '\0') {
		buffer[j++] = resolution[i++];
	}
	buffer[j] = '\0'; // Null-terminate the string
	*height = atoi(buffer); // Convert height to integer
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

int createSettingsMenu() {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	font = TTF_OpenFont("../assets/fonts/Arial.ttf", 16);

	SDL_Window* window = SDL_CreateWindow("FarmR Settings",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	const char* fpsOptions[] = { "30", "60", "120" };
	const char* resolutionOptions[] = { "800x600", "1024x768", "1280x720", "1920x1080" };

	
	Dropdown fpsDropdown = { fpsOptions, 3, 1, { 100, 50, 100, 30 }, SDL_FALSE };
	Dropdown resolutionDropdown = { resolutionOptions, 4, 1, { 500, 50, 100, 30 }, SDL_FALSE };
	SDL_Rect startButton = { 600, 500, 100, 40 };

	SDL_bool running = SDL_TRUE;
	while (running) {
		Uint32 frameStart = SDL_GetTicks();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				TTF_CloseFont(font);
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				SDL_Quit();
				settings.target_fps = atoi(fpsOptions[fpsDropdown.selectedOption]);
				getResolution(resolutionOptions[resolutionDropdown.selectedOption], &settings.screen_x, &settings.screen_y);
				running = SDL_FALSE;
				return 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				int x = event.button.x;
				int y = event.button.y;
				if (x >= startButton.x && x <= (startButton.x + startButton.w) &&
					y >= startButton.y && y <= (startButton.y + startButton.h)) {
					TTF_CloseFont(font);
					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					SDL_Quit();
					settings.target_fps = atoi(fpsOptions[fpsDropdown.selectedOption]);
					getResolution(resolutionOptions[resolutionDropdown.selectedOption], &settings.screen_x, &settings.screen_y);
					running = SDL_FALSE;
					return 1;
				}
			}
			handleDropdownEvent(&event, &fpsDropdown);
			handleDropdownEvent(&event, &resolutionDropdown);

		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_Color white = { 255, 255, 255, 255 };
		SDL_Surface* maxFPSsurface= TTF_RenderText_Blended(font, "Max FPS:", white);
		SDL_Texture* maxFPStexture = SDL_CreateTextureFromSurface(renderer, maxFPSsurface);
		SDL_Rect maxFPSRect = { fpsDropdown.box.x, fpsDropdown.box.y - 20, maxFPSsurface->w, maxFPSsurface->h };
		SDL_RenderCopy(renderer, maxFPStexture, NULL, &maxFPSRect);
		SDL_FreeSurface(maxFPSsurface);
		SDL_DestroyTexture(maxFPStexture);

		SDL_Surface* ResolutionSurface = TTF_RenderText_Blended(font, "Resolution:", white);
		SDL_Texture* ResolutionTexture = SDL_CreateTextureFromSurface(renderer, ResolutionSurface);
		SDL_Rect resolutionRect = { resolutionDropdown.box.x, resolutionDropdown.box.y - 20, ResolutionSurface->w, ResolutionSurface->h };
		SDL_RenderCopy(renderer, ResolutionTexture, NULL, &resolutionRect);
		SDL_FreeSurface(ResolutionSurface);
		SDL_DestroyTexture(ResolutionTexture);

		drawDropdown(renderer, &fpsDropdown);
		drawDropdown(renderer, &resolutionDropdown);

		SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
		SDL_RenderFillRect(renderer, &startButton);

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

	return 0;
}