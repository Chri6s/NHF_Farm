#pragma once
struct Map;
struct Save;

int checkForSavesFolder();
void createNewSave(struct Map* map);
void saveGame(struct Save* save, struct Map* map);

