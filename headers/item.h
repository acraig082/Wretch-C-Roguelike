#ifndef FINALPROJECT_ITEMS_H
#define FINALPROJECT_ITEMS_H

#include "utilities.h"

#define NUM_ITEM_TYPES 4
#define ARMOR 'A'
#define WEAPON 'W'
#define POTION 'P'
#define SCROLL 'S'

/// item structs
typedef struct Item{
    Position *pos;
    char *itemName;
    char *description;
    int itemID;
    int pickedUp;
    char sym;
}Item;

#endif //FINALPROJECT_ITEMS_H
