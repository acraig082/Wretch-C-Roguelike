#ifndef FINALPROJECT_WEAPON_H
#define FINALPROJECT_WEAPON_H

#include "item.h"
#include "utilities.h"

typedef struct Weapon{
    Item base;
    Dice *damage;
    int inUse;
    int dualWieldable;
}Weapon;

Item *newWeapon(char *weaponName, char *desc, int idNum, Dice *d, int used, int dual, char symbol);
Weapon * emptyWeapon();

#endif //FINALPROJECT_WEAPON_H
