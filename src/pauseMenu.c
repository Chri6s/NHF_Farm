#include "pauseMenu.h"
#include "main.h"
#include "render.h"
#include <stdio.h>


SDL_Texture* captureGameFrame(SDL_Renderer* renderer);

int PauseMenu(SDL_Renderer* renderer, Character* player, SDL_Texture* gameFrame) {

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 20);
    SDL_RenderFillRect(renderer, NULL);
    SDL_Texture* resume = loadTexture("assets/resume.png", renderer);
    SDL_Texture* saveGame = loadTexture("assets/saveGame.png", renderer);
    SDL_Texture* BTM = loadTexture("assets/BTM.png", renderer);
    Button resumeButton = { "newGame", {settings.screen_x / 2 - 100, settings.screen_y / 2 - 100, 200, 50} };
    Button saveGameButton = { "loadGame", {settings.screen_x / 2 - 100, settings.screen_y / 2, 200, 50} };
    Button BTMButton = { "exit", {settings.screen_x / 2 - 100, settings.screen_y / 2 + 100, 200, 50} };

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
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, gameFrame, NULL, NULL);

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 150); // Gray with 150 alpha
        SDL_RenderFillRect(renderer, NULL);

        renderButton(renderer, resume, resumeButton);
        renderButton(renderer, saveGame, saveGameButton);
        renderButton(renderer, BTM, BTMButton);
        SDL_RenderPresent(renderer);
        if (resumeClicked || escapePressed) {
            running = SDL_FALSE;
            player->pauseMenuOpen = 0;
            SDL_DestroyTexture(resume);
            SDL_DestroyTexture(saveGame);
            SDL_DestroyTexture(BTM);
            SDL_DestroyTexture(gameFrame);
            return 1;
        }
        if (saveGameClicked) {
            printf("EnterSavesMenu\n");
            //ide majd a SavesMenu methodusa kell.
            player->pauseMenuOpen = 0;
            SDL_DestroyTexture(resume);
            SDL_DestroyTexture(saveGame);
            SDL_DestroyTexture(BTM);

            SDL_DestroyTexture(gameFrame);
            return 1;
        }
        if (BTMClicked) {
            printf("BackToMenu\n");
            running = SDL_FALSE;
            SDL_DestroyTexture(resume);
            SDL_DestroyTexture(saveGame);
            SDL_DestroyTexture(BTM);
            SDL_DestroyTexture(gameFrame);
            return 2;
        }
    }
	SDL_DestroyTexture(resume);
	SDL_DestroyTexture(saveGame);
	SDL_DestroyTexture(BTM);

    return NULL;
}

SDL_Texture* captureGameFrame(SDL_Renderer* renderer) {
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, settings.screen_x, settings.screen_y);
    if (!texture) {
        fprintf(stderr, "Failed to create game frame texture: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, NULL, NULL, NULL);
    SDL_SetRenderTarget(renderer, NULL);

    return texture;
}