#include "rogue.h"
#include <curses.h>
#include <ncurses.h>
#include <math.h>

Room *createRoom(int y, int x, int height, int width)
{
    Room *newRoom;
    newRoom = malloc(sizeof(Room));

    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->height = height;
    newRoom->width = width;
    newRoom->isVisible = FALSE;

    newRoom->doors = malloc(sizeof(Position) * 4);

    /* left door */
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->y = rand() % (height - 2) + newRoom->position.y + 1;
    newRoom->doors[0]->x = newRoom->position.x;

    /* top door */
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->x = (rand() % (width - 2)) + newRoom->position.x + 1;
    newRoom->doors[1]->y = newRoom->position.y;

    /* right door */
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->y = rand() % (height - 2) + newRoom->position.y + 1;
    newRoom->doors[2]->x = newRoom->position.x + width - 1;

    /* bottom door */
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->x = rand() % (width - 2) + newRoom->position.x + 1;
    newRoom->doors[3]->y = newRoom->position.y + newRoom->height - 1;


    return newRoom;
}

void drawRoom(Room *room, char **map, int exitRoom)
{
    int x = 0;
    int y = 0;

    /* draw top and bottom */
    for (x = room->position.x; x < room->position.x + room->width; x++)
    {
        map[room->position.y][x] = '-'; /* top */
        printf("%c", map[64][x]);
        map[room->position.y + room->height - 1][x] = '-'; /* bottom */
    }

    /* draw floors and side walls */
    for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++)
    {
        /* draw side walls */
        map[y][room->position.x] = '|';
        map[y][room->position.x + room->width - 1] = '|';

        /* draw floors */
        for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
        {
            map[y][x] = '.';
        }
    }

    /* draw doors */
    map[room->doors[0]->y][room->doors[0]->x] = '+';
    map[room->doors[1]->y][room->doors[1]->x] = '+';
    map[room->doors[2]->y][room->doors[2]->x] = '+';
    map[room->doors[3]->y][room->doors[3]->x] = '+';

    if(exitRoom == TRUE){
        do{
            y = (rand() % room->height) + room->position.y;
            x = (rand() % room->width) + room->position.x;
        } while(map[y][x] != '.');
        map[y][x] = '%';
    }

}

void connectDoors(Node* start, Node* end, Level* level)
{
    if(start == NULL || end == NULL){
        return;
    }
    PQNode* head = PQNode_new(start, 0);

    start->cost = 0;
    start->cameFrom = start;



    while (isEmpty(&head) == FALSE){
        Node* current = peek(&head);
        pop(&head);

        if(isEmpty(&head)){
            head = PQNode_new(current, 0);
        }


        if(current->pos == end->pos){
            break;
        }

        for(int i = 0; i < 4; i++){
            if(current->neighbors[i] != NULL){
                double newCost = costSoFar(current) + current->neighbors[i]->cost;
                if(newCost < costSoFar(current->neighbors[i])){
                    current->neighbors[i]->cameFrom = current;
                    double priority = newCost + heuristic(current->pos, end->pos);
                    push(&head, current->neighbors[i], priority);
                }
            }
        }
    }



    ///draw hallway
    int y = start->pos->y;
    int x = start->pos->x;
    int y2 = end->pos->y;
    int x2 = end->pos->x;

    Node* index = end;
    while (index != start){
        y = index->cameFrom->pos->y;
        x = index->cameFrom->pos->x;
        level->mapTiles[y][x] = '#';
        index = index->cameFrom;
    }

    level->mapTiles[y][x] = '+';
    level->mapTiles[y2][x2] = '+';

    while(head->next != NULL){
        pop(&head);
    }
    pop(&head);
    free(head);

    for(int i = 0; i < MAX_HEIGHT; i++){
        for (int j = 0; j < MAX_WIDTH; j++)
        {
            resetNode(level->nodes[i][j]);
        }
    }

}