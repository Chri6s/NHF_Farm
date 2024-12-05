#include "structures.h"
#include "definitions.h"
#include "saveManager.h"
#include "map.h"
#include <direct.h>
#include <io.h>
#define access _access
#define F_OK 0
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "crypto/base64.h"
#include "crypto/vigenere.h"
#include "debugmalloc.h"
#include <windows.h>
#include <tchar.h>

typedef struct SaveList {
	int count;
	Save** saves;
} SaveList;

int checkForSavesFolder() {
    return access("./saves", F_OK) != -1 ? 1 : 0;
}

void createNewSave(Map* map) {
    initializeMap("NewGame");
    Save* currentSave = (Save*)malloc(sizeof(Save));
    if (currentSave == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    currentSave->mapdata = (Map*)malloc(sizeof(Block) * MAP_WIDTH * MAP_HEIGHT);
    strcpy_s(currentSave->saveName, sizeof(currentSave->saveName), map->name);
}

void saveGame(Save* save, Map* map) {
    if (!checkForSavesFolder()) {
        if (_mkdir("../saves") == 0) printf("Creating saves folder failed!");
    }
    FILE* saveFile;
    char savePath[100];
    sprintf_s(savePath, sizeof(savePath), "../saves/%s.save", map->name);
    fopen_s(&saveFile, savePath, "wb");
    if (saveFile == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char header[72];
    sprintf_s(header, sizeof(header), "%s|%s\n", save->LastPlayed, save->saveName);

    size_t dataSize = sizeof(header) + sizeof(Block) * MAP_WIDTH * MAP_HEIGHT;
    char* data = (char*)malloc(dataSize);
    if (data) {
        memcpy(data, header, sizeof(header));
        memcpy(data + sizeof(header), map->blocks, sizeof(Block) * MAP_WIDTH * MAP_HEIGHT);
        char* encodedData = base64_encode(data);
        free(data);
        char* encryptedData = vi_encrypt(encodedData, cryptoKey);
        free(encodedData);
        fwrite(encryptedData, sizeof(char), strlen(encryptedData), saveFile);
        free(encryptedData);

        fclose(saveFile);
    }
}


//void parseSaves() {
//    if (!checkForSavesFolder()) {
//        printf("No saves folder found!\n");
//        return;
//    }
//
//    WIN32_FIND_DATA findFileData;
//    HANDLE hFind = FindFirstFile("../saves/*.save", &findFileData);
//
//    if (hFind == INVALID_HANDLE_VALUE) {
//        printf("Error opening saves folder!\n");
//        return;
//    }
//
//    SaveList* saveList = (SaveList*)malloc(sizeof(SaveList));
//    saveList->count = 0;
//    saveList->saves = NULL;
//
//    do {
//        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
//            char savePath[100];
//            sprintf_s(savePath, sizeof(savePath), "../saves/%s", findFileData.cFileName);
//
//            FILE* saveFile;
//            fopen_s(&saveFile, savePath, "rb");
//            if (saveFile == NULL) {
//                printf("Error opening save file: %s\n", findFileData.cFileName);
//                continue;
//            }
//
//            fseek(saveFile, 0, SEEK_END);
//            long fileSize = ftell(saveFile);
//            fseek(saveFile, 0, SEEK_SET);
//
//            char* encryptedData = (char*)malloc(fileSize + 1);
//            fread(encryptedData, sizeof(char), fileSize, saveFile);
//            encryptedData[fileSize] = '\0';
//            fclose(saveFile);
//
//            char* decodedData = vi_decrypt(encryptedData, cryptoKey);
//            free(encryptedData);
//
//            char* data = base64_decode(decodedData);
//            free(decodedData);
//
//            Save* save = (Save*)malloc(sizeof(Save));
//            memcpy(save->LastPlayed, data, 12);
//            memcpy(save->saveName, data + 12, 50);
//            save->mapdata = (Map*)malloc(sizeof(Block) * MAP_WIDTH * MAP_HEIGHT);
//            memcpy(save->mapdata, data + 62, sizeof(Block) * MAP_WIDTH * MAP_HEIGHT);
//            free(data);
//
//            saveList->count++;
//            saveList->saves = (Save**)realloc(saveList->saves, saveList->count * sizeof(Save*));
//            saveList->saves[saveList->count - 1] = save;
//        }
//    } while (FindNextFile(hFind, &findFileData) != 0);
//
//    FindClose(hFind);
//}
//
