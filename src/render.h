#pragma once
#include <SDL.h>
#include "definitions.h"
#include "structures.h"

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
void renderMap(SDL_Renderer* renderer, SDL_Texture* grassTexture, SDL_Texture* otherTexture, Camera* camera);
void renderScene(SDL_Renderer* renderer, Character* player, SDL_Texture* grassTexture, Camera* camera);
void renderCharacter(SDL_Renderer* renderer, Character* player, Camera* camera);
SDL_Window* initWindow(const char* windowName, int width, int height);
void renderGame(SDL_Renderer* renderer, SDL_Texture* grassTexture, SDL_Texture* otherTexture, Character* player, Camera* camera);
void updateCamera(Camera* camera, Character* player);