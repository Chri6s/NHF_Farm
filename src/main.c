#include <windows.h>
#include "game.h"
#include "render.h"
#include "menus/settingsMenu.h"



/**
* @brief The main function that gets called on running the .exe file. This function right now, handles the startup, the settings menu before launching the game. This will be moved to another file, to make it more readable. 
* The functionality is basically: 1. creates the setting menu 2. handles everything in the handling menu until its closed or the user presses start 3. starts the GameInit function.
* @returns void
*/
int main(int argc, char* argv[]) {
    SetConsoleTitle(L"FarmR Debug");
    GameSettings* settings = malloc(sizeof(GameSettings));
    settings->screen_x = 800;
	settings->screen_y = 600;
	settings->target_fps = 60;
    if (createSettingsMenu(settings) == 0) {
        return 0;
    } // mivel handle-�lt�k a 0-�t (teh�t teljesen ki akar l�pni a user, �gy mindehogyan lefutatthatjuk a GameInit()-et.
    GameInit(settings);
    return 1;
}
