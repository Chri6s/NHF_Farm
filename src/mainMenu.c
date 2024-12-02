#include "mainMenu.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "definitions.h"
#include "savemanager.h"
#include "structures.h"
#include "main.h"
#include "render.h"
#include <windows.h>
#include <commdlg.h>


// Utility function prototypes
void getExecutableDirectory(char* buffer, size_t size);
void renderButton(SDL_Renderer* renderer, SDL_Texture* texture, Button button);
int MainMenu(SDL_Renderer* renderer);

// Utility implementations
void getExecutableDirectory(char* buffer, size_t size) {
    GetModuleFileName(NULL, buffer, size);
    char* lastSlash = strrchr(buffer, '\\');
    if (lastSlash) {
        *lastSlash = '\0';
    }
}

void openFileAndLoad() {
    // Buffer to store the selected file path
    char filePath[MAX_PATH] = { 0 };

    // Initialize OPENFILENAME structure
    OPENFILENAME ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = L"*.save\0";
    ofn.hwndOwner = NULL;  // Parent window handle, set NULL for console apps
    ofn.lpstrFilter = L"*.save\0";
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    // Display the Open File Dialog
    if (GetOpenFileName(&ofn)) {
        printf("Selected file: %s\n", filePath);

        // Example: Load the file
        FILE* file = fopen(filePath, "r");
        if (file) {
            printf("File opened successfully. Reading contents:\n");
            char buffer[256];
            while (fgets(buffer, sizeof(buffer), file)) {
                printf("%s", buffer);
            }
            fclose(file);
        }
        else {
            printf("Failed to open file.\n");
        }
    }
    else {
        printf("No file selected or an error occurred.\n");
    }
}

int MainMenu(SDL_Renderer* renderer) {
    SDL_Texture* background = loadTexture("../assets/mainMenu/mainMenu.png", renderer);
    SDL_Texture* newGameButton = loadTexture("../assets/mainMenu/NewGame.png", renderer);
    SDL_Texture* loadGameButton = loadTexture("../assets/mainMenu/loadGame.png", renderer);
    SDL_Texture* exitButton = loadTexture("../assets/mainMenu/exitGame.png", renderer);
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
                return 0;
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
                running = SDL_FALSE;
                return 1;
            }
            if (loadGameClicked) {
                openFileAndLoad(); //ide majd a SavesMenu methodusa kell.
                printf("Enter Saves menu");
                return 1;
            }
            if (exitClicked) {
                printf("Exit game");
                running = SDL_FALSE;
                return 0;
            }
            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(newGameButton);
    SDL_DestroyTexture(loadGameButton);
    SDL_DestroyTexture(exitButton);
    return 2;
}

