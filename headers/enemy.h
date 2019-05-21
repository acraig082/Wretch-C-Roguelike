#ifndef FINALPROJECT_ENEMY_H
#define FINALPROJECT_ENEMY_H

//#include "utilities.h"

#define NUM_OF_ENEMY_TYPES 7

typedef enum Enemies{
    Cacogen,    //0  //literally just means genetic monstrosity; alien human hybrid
    Goblin,     //1
    Grootslang, //2
    Kaliya,     //3  //poisonous serpent
    Onocentaur, //4  //donkey centaur
    Obour,      //5  //blood-thirsty ghoul
//    Wendigo,      //"it would attack other men and eat their flesh, but every bite would just make them larger and hungrier"
//    //feeds off player
    Zoanthrope,  //6  //man-ape
    Knob //7
    //bosses

}Enemies;

/// enemy structs
typedef struct Enemy
{
    Position position;
    char symbol;
    char standingOn;
    int health;
    int armorClass;
    Dice *hit;
    int expWorth;
    int species;
    int roomNumber; //the room the enemy is in
} Enemy;


#endif //FINALPROJECT_ENEMY_H
