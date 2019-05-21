#ifndef FINALPROJECT_UTILITIES_H
#define FINALPROJECT_UTILITIES_H

/// utility structs
typedef struct Position {
    int x;
    int y;
    // TILE_TYPE tile;
} Position;

typedef struct Node {
    double cost;
    int visited;
    Position* pos;
    struct Node* cameFrom;
    struct Node** neighbors;
} Node;

typedef struct Dice{
    int quantity;
    int sides;
}Dice;

typedef struct PQNode {
    double priority;  // lower values have higher priority
    Node* data;
    struct PQNode *prev, *next;
} PQNode;

typedef struct PriorityQueue{
    PQNode *front;
    PQNode *rear;
}PriorityQueue;


/// Position functions
Position* Position_new(int y, int x);

/// Dice functions
int rollDice(Dice *d);

/// Priority Queue functions
PQNode* PQNode_new(Node* d, double p);
Node* peek(PQNode** head);
void pop(PQNode** head);
void push(PQNode** head, Node* d, double p);
int isEmpty(PQNode** head);

/// Location functions


#endif //FINALPROJECT_UTILITIES_H
