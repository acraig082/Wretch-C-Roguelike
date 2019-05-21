#include "rogue.h"
#include <ncurses.h>
#include <curses.h>
#include <math.h>

Enemy *newEnemySetUp(Level *level)
{
    Enemy *newEnemy;
    newEnemy = malloc(sizeof(Enemy));
    Dice *hitDice = malloc(sizeof(Dice));

    ///assign random species
    newEnemy->species = rand() % NUM_OF_ENEMY_TYPES;

    ///assign random room that is not the room the player is in
    int room = (rand() % level->numRooms - 1) + 1;
    newEnemy->roomNumber = room;

    ///random position in the room
    newEnemy->position.x = level->rooms[room]->position.x + (rand() % (level->rooms[room]->width - 4)) + 2;
    newEnemy->position.y = level->rooms[room]->position.y + (rand() % (level->rooms[room]->height - 4)) + 2;

    newEnemy->standingOn = level->mapTiles[newEnemy->position.y][newEnemy->position.x];


    switch (newEnemy->species)
    {
        case Cacogen:
            newEnemy->health = 25;
            newEnemy->symbol = 'C';
            newEnemy->expWorth = 20;
            newEnemy->armorClass = 14;
            hitDice->quantity = 1;
            hitDice->sides = 6;
            newEnemy->hit = hitDice;
            break;
        case Goblin:
            newEnemy->health = 12;
            newEnemy->symbol = 'g';
            newEnemy->armorClass = 10;
            newEnemy->expWorth = 9;
            hitDice->quantity = 1;
            hitDice->sides = 4;
            newEnemy->hit = hitDice;
            break;
        case Grootslang:
            newEnemy->health = 48;
            newEnemy->symbol = 'G';
            newEnemy->expWorth = 55;
            newEnemy->armorClass = 12;
            hitDice->quantity = 2;
            hitDice->sides = 8;
            newEnemy->hit = hitDice;
            break;
        case Kaliya:
            newEnemy->health = 30;
            newEnemy->symbol = 'k';
            newEnemy->expWorth = 42;
            newEnemy->armorClass = 15;
            hitDice->quantity = 2;
            hitDice->sides = 6;
            newEnemy->hit = hitDice;
            break;
        case Onocentaur:
            newEnemy->health = 25;
            newEnemy->symbol = 'O';
            newEnemy->expWorth = 23;
            newEnemy->armorClass = 14;
            hitDice->quantity = 1;
            hitDice->sides = 8;
            newEnemy->hit = hitDice;
            break;
        case Obour:
            newEnemy->health = 10;
            newEnemy->symbol = 'o';
            newEnemy->expWorth = 12;
            newEnemy->armorClass = 14;
            hitDice->quantity = 1;
            hitDice->sides = 6;
            newEnemy->hit = hitDice;
            break;
        case Zoanthrope:
            newEnemy->health = 20;
            newEnemy->symbol = 'z';
            newEnemy->expWorth = 8;
            newEnemy->armorClass = 8;
            hitDice->quantity = 1;
            hitDice->sides = 4;
            newEnemy->hit = hitDice;
            break;
        default:
            break;
    }

    level->mapTiles[newEnemy->position.y][newEnemy->position.x] = newEnemy->symbol;

    mvaddch(newEnemy->position.y, newEnemy->position.x, newEnemy->symbol);

    return newEnemy;
}

Enemy *scrollEventEnemySetUp(Player* player, Level* level){
    Enemy *newEnemy;
    newEnemy = malloc(sizeof(Enemy));
    Dice *hitDice = malloc(sizeof(Dice));

    int room = player->roomNumber;
    newEnemy->roomNumber = room;

    do{
        newEnemy->position.x = level->rooms[room]->position.x + (rand() % (level->rooms[room]->width - 4)) + 2;
        newEnemy->position.y = level->rooms[room]->position.y + (rand() % (level->rooms[room]->height - 4)) + 2;

        newEnemy->standingOn = level->mapTiles[newEnemy->position.y][newEnemy->position.x];
    } while(level->mapTiles[newEnemy->position.y][newEnemy->position.x] != '.');

    newEnemy->health = 5;
    newEnemy->symbol = 'D';     //DeathKnight
    newEnemy->expWorth = 0;
    newEnemy->armorClass = 12;
    hitDice->quantity = 1;
    hitDice->sides = 10;
    newEnemy->hit = hitDice;

    level->mapTiles[newEnemy->position.y][newEnemy->position.x] = newEnemy->symbol;

    mvaddch(newEnemy->position.y, newEnemy->position.x, newEnemy->symbol);

    return newEnemy;
}

void enemyChooseMove(Enemy *enemy, Player* player, Level *level)
{
    int chance = rand() % 6;
    int randDir = rand() % 4;
    Position *p = malloc(sizeof(Position));


    if(detectedPlayer(player, enemy) == TRUE){
        moveTowardPlayer(player, enemy, level->nodes[enemy->position.y][enemy->position.x], level->nodes[player->position.y][player->position.x], level);
    } else{
        if (chance == 1)
        {
            switch (randDir)
            {
                case LEFT:
                    p->x = enemy->position.x - 1;
                    p->y = enemy->position.y;
                    break;
                case UP:
                    p->x = enemy->position.x;
                    p->y = enemy->position.y - 1;
                    break;
                case RIGHT:
                    p->x = enemy->position.x + 1;
                    p->y = enemy->position.y;
                    break;
                case DOWN:
                    p->x = enemy->position.x;
                    p->y = enemy->position.y + 1;
                    break;
                default:
                    break;
            }

            if(p->y > 0 && p->x > 0 && p->y < MAX_HEIGHT && p->x < MAX_WIDTH){
                enemyCheckPosition(p, enemy, level);
            }
        }
    }

}

int enemyCheckPosition(Position *newPosition, Enemy *enemy, Level *level)
{
    switch (level->mapTiles[newPosition->y][newPosition->x])
    {
        case '.':
            if(level->mapTiles[enemy->position.y][enemy->position.x] != '.') //if just steping into room, change player's room
            {
                int lastRoom = enemy->roomNumber;

                //check if enemy is just re-entering same room
                for (int i = level->rooms[lastRoom]->position.y; i < (level->rooms[lastRoom]->position.y + level->rooms[lastRoom]->height); i++){
                    for (int j = level->rooms[lastRoom]->position.x; j < (level->rooms[lastRoom]->position.x + level->rooms[lastRoom]->width); j++){
                        if (i == newPosition->y && j == newPosition->x)
                        {
                            enemyMakeMove(newPosition, enemy, level);
                            return 1;
                        }
                    }
                }

                //brute force check all rooms
                for (int k = 0; k < level->numRooms; k++){
                    for (int g = level->rooms[k]->position.y; g < (level->rooms[k]->position.y + level->rooms[k]->height); g++){
                        for (int h = level->rooms[k]->position.x; h < (level->rooms[k]->position.x + level->rooms[k]->width); h++){
                            if (g == newPosition->y && h == newPosition->x)
                            {
                                enemy->roomNumber = k;
                                enemyMakeMove(newPosition, enemy, level);
                                return 1;
                            }
                        }
                    }
                }
            }
        case '#':
        case '+':
        case WEAPON:
        case ARMOR:
        case SCROLL:
        case POTION:
        case '%':
            enemyMakeMove(newPosition, enemy, level);
            return 1;
        case 'C':
        case 'g':
        case 'G':
        case 'k':
        case 'o':
        case 'O':
        case 'w':
        case 'z':
        case 'D':
        default:
            return 0;
    }
}

void enemyMakeMove(Position *newPosition, Enemy *enemy, Level *level)
{
    level->mapTiles[enemy->position.y][enemy->position.x] = enemy->standingOn;
    enemy->standingOn = level->mapTiles[newPosition->y][newPosition->x];

    level->mapTiles[newPosition->y][newPosition->x] = enemy->symbol;
    move(newPosition->y, newPosition->x);

    enemy->position.y = newPosition->y;
    enemy->position.x = newPosition->x;
}

int detectedPlayer(Player* player, Enemy* enemy){
    if(enemy->roomNumber != player->roomNumber && enemy->standingOn != '#' && enemy->standingOn != '+'){
        return FALSE;
    }
    else
    {
        if(player->standingOn == '#' || player->standingOn == '+'){
            if(rand() % (player->abilities.DEX + 2) > 0 ){
                return FALSE;
            } else{
                return TRUE;
            }
        }
        else if(rand() % (player->abilities.DEX + 2) > 2)
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }


    }
}

void moveTowardPlayer(Player* player, Enemy* enemy, Node* start, Node* end, Level* level){
    int y1 = start->pos->y;
    int x1 = start->pos->x;
    int y2 = end->pos->y;
    int x2 = end->pos->x;
    int count = 0;

    if((x1 == x2 && abs(y2 - y1) == 1) || (y1 == y2 && abs(x2 - x1) == 1)){
        Attack(player, enemy, level, FALSE);
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
            count++;
            if(current->neighbors[i] != NULL){
                double newCost = costSoFar(current) + current->neighbors[i]->cost;
                if(count > 600){
                    break;
                }
                if(newCost < costSoFar(current->neighbors[i])){
                    current->neighbors[i]->cameFrom = current;
                    double priority = newCost + heuristic(current->pos, end->pos);
                    push(&head, current->neighbors[i], priority);
                }
            }
        }

        if(count > 600){
            break;
        }
    }

    if(count < 600){
        Node* index = end;
        while (index != start){
            if(index->cameFrom == start){
                enemyCheckPosition(index->pos, enemy, level);
            }
            index = index->cameFrom;

        }
    }

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
