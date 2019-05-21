#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

typedef struct Inventory{
    int capacity;
    int currentSize;
    Item **inv;
}Inventory;

typedef struct AbilityScores{
    int STR;
    int DEX;
    int CON;
    int INT;
}AbilityScores;

/// player struct
typedef struct Player
{
    Position position;
    char standingOn;
    int currentHealth;
    int maxHealth;
    int exp;
    Inventory i;
    Weapon *weapon;
    Armor *armor;
    Potion *potion;
    Scroll *scroll;
    int roomNumber;                 //the room the player is in
    int level;                      //the level the player is based on exp
    AbilityScores abilities;        //STR, DEX, CON, INT
    int newFloor;                   //if the player has entered a new floor
    char status[100];
    char status2[100];
    char status3[100];
    char status4[100];
    char status5[100];
} Player;

#endif //FINALPROJECT_PLAYER_H
