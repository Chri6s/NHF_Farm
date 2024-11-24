#include "mainMenu.h"

#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>
#include "definitions.h"
#include "savemanager.h"
#include "structures.h"
#include "main.h"
#include "render.h"
typedef struct {
	char* name;
	SDL_Rect box;
} Button;

void renderButton(SDL_Renderer* renderer, SDL_Texture* texture, Button button) {
	SDL_RenderCopy(renderer, texture, NULL, &button.box);
}
void MainMenu(SDL_Renderer* renderer) {
	SDL_Texture* background = loadTexture("../assets/mainMenu/mainMenu.png", renderer);
	SDL_Texture* newGameButton = loadTexture("../assets/mainMenu/NewGame.png", renderer);
	SDL_Texture* loadGameButton = loadTexture("../assets/mainMenu/loadGame.png", renderer);
	SDL_Texture* exitButton = loadTexture("../assets/mainMenu/exitGame.png", renderer);
	//SDL_Texture* newGameButtonHover = loadTexture("../assets/newgame_hover.png", renderer);
	//SDL_Texture* loadGameButtonHover = loadTexture("../assets/loadgame_hover.png", renderer);
	//SDL_Texture* exitButtonHover = loadTexture("../assets/exit_hover.png", renderer);
	//SDL_Texture* newGameButtonClicked = loadTexture("../assets/newgame_clicked.png", renderer);
	//SDL_Texture* loadGameButtonClicked = loadTexture("../assets/loadgame_clicked.png", renderer);
	//SDL_Texture* exitButtonClicked = loadTexture("../assets/exit_clicked.png", renderer);
	SDL_Texture* newGameButtonTexture = newGameButton;
	SDL_Texture* loadGameButtonTexture = loadGameButton;
	SDL_Texture* exitButtonTexture = exitButton;
	SDL_RenderClear(renderer);
	SDL_bool newGameHover = SDL_FALSE;
	SDL_bool loadGameHover = SDL_FALSE;
	SDL_bool exitHover = SDL_FALSE;
	SDL_bool newGameClicked = SDL_FALSE;
	SDL_bool loadGameClicked = SDL_FALSE;
	SDL_bool exitClicked = SDL_FALSE;
	SDL_bool running = SDL_TRUE;
	SDL_Event event;
	Button newGame = { "newGame", {settings.screen_x / 2 - 100, settings.screen_y / 2 - 100, 200, 50} };
	Button loadGame = { "loadGame", {settings.screen_x / 2 - 100, settings.screen_y / 2, 200, 50} };
	Button exit = { "exit", {settings.screen_x / 2 - 100, settings.screen_y / 2 + 100, 200, 50} };
	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = SDL_FALSE;
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.x >= newGame.box.x && event.motion.x <= newGame.box.x + newGame.box.w && event.motion.y >= newGame.box.y && event.motion.y <= newGame.box.y + newGame.box.h) {
					newGameHover = SDL_TRUE;
				}
				else {
					newGameHover = SDL_FALSE;
				}
				if (event.motion.x >= loadGame.box.x && event.motion.x <= loadGame.box.x + loadGame.box.w && event.motion.y >= loadGame.box.y && event.motion.y <= loadGame.box.y + loadGame.box.h) {
					loadGameHover = SDL_TRUE;
				}
				else {
					loadGameHover = SDL_FALSE;
				}
				if (event.motion.x >= exit.box.x && event.motion.x <= exit.box.x + exit.box.w && event.motion.y >= exit.box.y && event.motion.y <= exit.box.y + exit.box.h) {
					exitHover = SDL_TRUE;
				}
				else {
					exitHover = SDL_FALSE;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (event.button.x >= newGame.box.x && event.button.x <= newGame.box.x + newGame.box.w && event.button.y >= newGame.box.y && event.button.y <= newGame.box.y + newGame.box.h) {
						newGameClicked = SDL_TRUE;
					}
					if (event.button.x >= loadGame.box.x && event.button.x <= loadGame.box.x + loadGame.box.w && event.button.y >= loadGame.box.y && event.button.y <= loadGame.box.y + loadGame.box.h) {
						loadGameClicked = SDL_TRUE;
					}
					if (event.button.x >= exit.box.x && event.button.x <= exit.box.x + exit.box.w && event.button.y >= exit.box.y && event.button.y <= exit.box.y + exit.box.h) {
						exitClicked = SDL_TRUE;
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (event.button.x >= newGame.box.x && event.button.x <= newGame.box.x + newGame.box.w && event.button.y >= newGame.box.y && event.button.y <= newGame.box.y + newGame.box.h) {
						newGameClicked = SDL_FALSE;
						running = SDL_FALSE;
					}
					if (event.button.x >= loadGame.box.x && event.button.x <= loadGame.box.x + loadGame.box.w && event.button.y >= loadGame.box.y && event.button.y <= loadGame.box.y + loadGame.box.h) {
						loadGameClicked = SDL_FALSE;
						running = SDL_FALSE;
					}
					if (event.button.x >= exit.box.x && event.button.x <= exit.box.x + exit.box.w && event.button.y >= exit.box.y && event.button.y <= exit.box.y + exit.box.h) {
						exitClicked = SDL_FALSE;
						running = SDL_FALSE;
					}
				}
				break;
			}
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, background, NULL, NULL);
			renderButton(renderer, newGameButtonTexture, newGame);
			renderButton(renderer, loadGameButtonTexture, loadGame);
			renderButton(renderer, exitButtonTexture, exit);
			if (newGameClicked) {
				//newGame();
				printf("Enter New Game menu");
			}
			if (loadGameClicked) {
				//savesMenu();
				printf("Enter Saves menu");
			}
			if (exitClicked) {
				printf("Exit game");
				running = SDL_FALSE;
			}	
				SDL_RenderPresent(renderer);
		}
	}
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(newGameButton);
	SDL_DestroyTexture(loadGameButton);
	SDL_DestroyTexture(exitButton);
	//SDL_DestroyTexture(newGameButtonHover);
	//SDL_DestroyTexture(loadGameButtonHover);
	//SDL_DestroyTexture(exitButtonHover);
	//SDL_DestroyTexture(newGameButtonClicked);
	//SDL_DestroyTexture(loadGameButtonClicked);
	//SDL_DestroyTexture(exitButtonClicked);
	//SDL_DestroyTexture(newGameButtonTexture);
	//SDL_DestroyTexture(loadGameButtonTexture);
	//SDL_DestroyTexture(exitButtonTexture);
	printf("dawg wtf");
	return NULL;
}
