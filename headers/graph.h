#ifndef FINALPROJECT_GRAPH_H
#define FINALPROJECT_GRAPH_H


Node* newNode(int y, int x);
void getNewNeighbors(Node* nucleus, Level* level);
double initialCostHallway(int y, int x, Level* lvl);
double initialCostEnemy(int y, int x, Level* lvl);
double costSoFar(Node* n);
double heuristic(Position* start, Position* end);
void resetNode(Node* n);


#endif //FINALPROJECT_GRAPH_H
