#ifndef FINALPROJECT_POTION_H
#define FINALPROJECT_POTION_H

typedef struct Potion{
    Item base;
    Dice *healDice;
    int used;
}Potion;

Item * newPotion(char *potionName, char *desc, int idNum, Dice *healing, int used, char symbol);
Potion * emptyPotion();

#endif //FINALPROJECT_POTION_H
