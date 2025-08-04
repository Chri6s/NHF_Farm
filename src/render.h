#pragma once
#include "definitions.h"
#include "sdl_includes.h"

struct Character;
struct Camera;
struct Map;
struct Button;

void renderCharacter(SDL_Renderer* renderer, struct Character* player, struct Camera* camera);
void renderMap(SDL_Renderer* renderer, SDL_Texture* grassTexture, SDL_Texture* otherTexture, struct Camera* camera, struct Map* map);
void renderTileOutline(SDL_Renderer* renderer, int selectedTileX, int selectedTileY, struct Camera* camera);
void updateCamera(struct Camera* camera, struct Character* player);
void renderButton(SDL_Renderer* renderer, SDL_Texture* texture, struct Button button);
void renderGame(SDL_Renderer* renderer, SDL_Texture* grassTexture, SDL_Texture* otherTexture, struct Character* player, struct Camera* camera, struct Map* map);
SDL_Window* initWindow(const char* windowName, int width, int height);
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);