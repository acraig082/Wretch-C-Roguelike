#ifndef FINALPROJECT_LEVEL_H
#define FINALPROJECT_LEVEL_H

/// level structs
typedef struct Room
{
    Position position;
    int height;
    int width;
    int isVisible;

    // locations of the doors
    Position ** doors;

} Room;

typedef struct Level
{
    char **mapTiles;
    char **visible;
    Room **rooms;
    Enemy *foes;
    Item **loot;
    Node ***nodes;
    int numOfEnemies;
    int numRooms;
    int numOfItems;
} Level;


#endif //FINALPROJECT_LEVEL_H
