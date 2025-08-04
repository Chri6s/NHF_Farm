#include "include/item_structs.h"
#include "definitions.h"
#include "item.h"
#include <SDL.h>
#include "game.h"
#include "character.h"

Item* initItem(int itemId) {

    Item* item = (Item*)malloc(sizeof(Item));
    if (item == NULL) {
        return NULL;
    }

    switch (itemId) {
    case 0:
        
        item->id = itemId;
        strcpy(item->name, "Hoe");
        item->srcX = 0;
        item->srcY = ORIGINAL_TILE_SIZE;
        item->srcW = ORIGINAL_TILE_SIZE;
        item->srcH = ORIGINAL_TILE_SIZE;
        item->quantity = 1;
        break;
    case 1:
        item->id = itemId;
        strcpy(item->name, "Carrot");
        item->srcX = 0;
        item->srcY = ORIGINAL_TILE_SIZE;
        item->srcW = ORIGINAL_TILE_SIZE;
        item->srcH = ORIGINAL_TILE_SIZE;
        item->quantity = 1;
        break;
    case 2:
        item->id = itemId;
        strcpy(item->name, "Wheat");
        item->srcX = ORIGINAL_TILE_SIZE * 2;
        item->srcY = ORIGINAL_TILE_SIZE;
        item->srcW = ORIGINAL_TILE_SIZE;
        item->srcH = ORIGINAL_TILE_SIZE;
        item->quantity = 1;
        break;
    }

    printf("Created item at address: %p\n", (void*)item);
    return item;

}