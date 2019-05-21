#include "rogue.h"
#include <stdlib.h>

Item *newArmor(char *armorName, char *desc, int idNum, int armorClass, int used, char sym){
    Armor *a = malloc(sizeof(Armor));
    a->base.itemName = armorName;
    a->base.itemID = idNum;
    a->base.description = desc;
    a->base.pickedUp = FALSE;
    a->armorClass = armorClass;
    a->inUse = used;
    a->base.sym = sym;
    return (Item *)a;
}

Armor * emptyArmor(){
    return (Armor *)newArmor("Empty", " ", -1, 13, FALSE, '?');
}