#pragma once
#include "definitions.h"
#include "structures.h"

void renderCharacter(SDL_Renderer* renderer, Character* player, Camera* camera);
void renderMap(SDL_Renderer* renderer, SDL_Texture* grassTexture, SDL_Texture* otherTexture, Camera* camera, Map* map);
void renderTileOutline(SDL_Renderer* renderer, int selectedTileX, int selectedTileY, Camera* camera);
void updateCamera(Camera* camera, Character* player);
void renderButton(SDL_Renderer* renderer, SDL_Texture* texture, Button button);

void renderGame(SDL_Renderer* renderer, SDL_Texture* grassTexture, SDL_Texture* otherTexture, Character* player, Camera* camera, Map* map);


SDL_Window* initWindow(const char* windowName, int width, int height);
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);