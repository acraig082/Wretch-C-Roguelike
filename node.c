#include "rogue.h"
#include <math.h>

Node* newNode(int y, int x){
    Node* n = malloc(sizeof(Node));
    n->pos = malloc(sizeof(Position*));
    n->pos->y = y;
    n->pos->x = x;
    n->cameFrom = NULL;
    n->cost = 0.00;
    n->visited = FALSE;
    n->neighbors = malloc(sizeof(Node*) * 4);
    return n;
}

void getNewNeighbors(Node* nucleus, Level* level)
{
    int y = nucleus->pos->y;
    int x = nucleus->pos->x;


    /// left neighbor
    if(x < 1){
        level->nodes[y][x]->neighbors[0] = NULL;
    }
    else{
        level->nodes[y][x]->neighbors[0] = level->nodes[y][x - 1];
    }

    /// top neighbor
    if(y < 1){
        level->nodes[y][x]->neighbors[1] = NULL;
    }
    else{
        level->nodes[y][x]->neighbors[1] = level->nodes[y - 1][x];
    }


    /// right neighbor
    if(x >= MAX_WIDTH - 1){
        level->nodes[y][x]->neighbors[2] = NULL;
    }
    else{
        level->nodes[y][x]->neighbors[2] = level->nodes[y][x + 1];
    }


    /// bottom neighbor
    if(y >= MAX_HEIGHT - 1){
        level->nodes[y][x]->neighbors[3] = NULL;
    }
    else{
        level->nodes[y][x]->neighbors[3] = level->nodes[y + 1][x];
    }

}

double initialCostHallway(int y, int x, Level* lvl){
    char s = lvl->mapTiles[y][x];
    double cost = 99999.00;
    switch (s){
        case '#':
            cost = .5;
            break;
        case ' ':
        case '+':
            cost = 1.00;
            break;
        case '.':
        case '-':
        case '|':
            cost = 5.00;
            break;
        default:
            break;
    }
    return cost;
}

double initialCostEnemy(int y, int x, Level* lvl){
    char s = lvl->mapTiles[y][x];
    double cost = 99999.00;
    switch (s){
        case '#':
        case '+':
            cost = 2.00;
            break;
        case '.':
        case WEAPON:
        case ARMOR:
        case POTION:
        case SCROLL:
        case '%':
            cost = 1.00;
            break;
        case ' ':
        case '-':
        case '|':
            cost = 9999;
        default:
            break;
    }
    return cost;
}

double costSoFar(Node* n){
    if(n->cameFrom != n){
        if(n->cameFrom == NULL){
            return 99999;
        }
        return (n->cost + costSoFar(n->cameFrom));
    }
    else{
        return 0;
    }
}

double heuristic(Position* start, Position* end){
    int y1 = start->y;
    int x1 = start->x;
    int y2 = end->y;
    int x2 = end->x;

    int newY = abs(y2 - y1);
    int newX = abs(x2 - x1);

//    double hyp = sqrt(newY * newY + newX * newX);
//
//    return hyp;

    return (double)newY + newX;
}

void resetNode(Node* n){
    n->cameFrom = NULL;
}

