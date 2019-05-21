
#include "rogue.h"
#include <stdlib.h>

Item * newWeapon(char *name, char *desc, int id, Dice *hitDice, int used, int dual, char sym){
    Weapon *w = malloc(sizeof(Weapon));
    w->base.itemName = name;
    w->base.itemID = id;
    w->base.description = desc;
    w->base.pickedUp = FALSE;
    w->damage = hitDice;
    w->inUse = used;
    w->dualWieldable = dual;
    w->base.sym = sym;
    return (Item *)w;
}

Weapon * emptyWeapon(){
    Dice *hitDice = malloc(sizeof(Dice));
    hitDice->quantity = 1;
    hitDice->sides = 3;
    return (Weapon *)newWeapon("Empty", " ", -1, hitDice, FALSE, FALSE, '?');
}