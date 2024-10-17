#include <stdio.h>
#include <windows.h>
#include "game.h"

int main(int argc, char* argv[]) {
    SetConsoleTitle(L"FarmGame Debug");
    GameInit();
    return 0;
}
