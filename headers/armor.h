#ifndef FINALPROJECT_ARMOR_H
#define FINALPROJECT_ARMOR_H

#include "item.h"

typedef struct Armor{
    Item base;
    int armorClass;
    int inUse;
}Armor;

Item *newArmor(char *armorName, char *desc, int idNum, int armorClass, int used, char symbol);
Armor * emptyArmor();

#endif //FINALPROJECT_ARMOR_H
