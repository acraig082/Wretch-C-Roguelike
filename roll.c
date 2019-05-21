#include "rogue.h"

int rollDice(Dice *d)
{
    int roll = 0;

    for (int x = 0; x < d->quantity; x++)
    {
        roll += (rand() % d->sides) + 1;
    }

    return roll;
}