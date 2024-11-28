#include <stdio.h>
#include <windows.h>
#include "game.h"
#include "render.h"
#include "settingsMenu.h"
#include "debugmalloc.h"



extern GameSettings settings = { 60, 800, 600 };

/**
* @brief The main function that gets called on running the .exe file. This function right now, handles the startup, the settings menu before launching the game. This will be moved to another file, to make it more readable. 
* The functionality is basically: 1. creates the setting menu 2. handles everything in the handling menu until its closed or the user presses start 3. starts the GameInit function.
* @returns void
*/
int main(int argc, char* argv[]) {
    SetConsoleTitle(L"FarmR Debug");
    createSettingsMenu();
    GameInit();
    return 1;
}
