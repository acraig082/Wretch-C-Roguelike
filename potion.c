#include<stdio.h>
#include<stdlib.h>
#include "rogue.h"
#include "headers/potion.h"

Item *newPotion(char*name,char*desc,int idNum, Dice* health, int used, char symbol){
    Potion *p = malloc(sizeof(Potion));
    p->base.itemName = name;
    p->base.description = desc;
    p->base.itemID = idNum;
    p->base.pickedUp = FALSE;
    p->healDice = health;
    p->base.sym = symbol;
    p->used = used;
    return(Item *)p;
}

Potion * emptyPotion(){
    Dice *healing = malloc(sizeof(Dice*));
    healing->quantity = 0;
    healing->sides = 0;
    return (Potion *)newPotion("Empty", " ", -1, healing, FALSE, '?');
}