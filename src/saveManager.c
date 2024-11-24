#include "structures.h"
#include "definitions.h"
#include "saveManager.h"
#include "map.h"
#include <direct.h>
#define access _access
#define F_OK 0
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "crypto/base64.h"
#include "crypto/vigenere.h"

int checkForSavesFolder() {
    return access("../saves", F_OK) != -1 ? 1 : 0;
}

void createNewSave() {
    initializeMap();
    Save* currentSave = (Save*)malloc(sizeof(Save));
    if (currentSave == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    currentSave->mapdata = (Map*)malloc(sizeof(Block) * MAP_WIDTH * MAP_HEIGHT);
    strcpy_s(currentSave->saveName, sizeof(currentSave->saveName), map->name);
}

void saveGame(Save save) {
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
    sprintf_s(header, sizeof(header), "%s|%s\n", save.LastPlayed, save.saveName);

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

void parseSaves() {

}