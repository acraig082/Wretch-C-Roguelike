#ifndef ROGUE_H
#define ROGUE_H

#include "headers/utilities.h"
#include "headers/enemy.h"
#include "headers/item.h"
#include "headers/armor.h"
#include "headers/weapon.h"
#include "headers/potion.h"
#include "headers/scroll.h"
#include "headers/level.h"
#include "headers/graph.h"
#include "headers/player.h"
#include <ncurses.h>
#include <curses.h> //All output functions take y co-ordinate first and then x in their arguments
#include <panel.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

//the max terminal window size
#define MAX_WIN_WIDTH 160
#define MAX_WIN_HEIGHT 48

//the size of the map
#define MAX_WIDTH 240
#define MAX_HEIGHT 120

/************\
 * direction
 * ---------
 *     1
 *  0 -|- 2
 *     3
 ************/
#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

/*** user interface functions ***/
void titleSequence();
void deathScreen();
void drawStatsWindow(WINDOW * stats, WINDOW * statusText[], Player *player, char *str, char *str2, char* str3, char *str4, char *str5);
void drawInvWindow(WINDOW *invList, Player *player);

/*** level/map functions ***/
void mapSetUp(Level *l);
char **cutOut(Level* level, int mapx, int mapy);
char **cutOutView(Level* level, Player *player);
void drawView(Player *player, char **newView, WINDOW *stats, WINDOW * statusText[], WINDOW *inventoryList, char *str, char *str2, char *str3, char *str4, char *str5);
void mapVisible(Level* level, Player* user);

/*** player functions ***/
Player * playerSetUp(Level *l);
Position * handleInput(WINDOW *stats, int input, Player *player, Level *level);
int checkPosition(Position *newPosition, Player *player, Level *level);
void playerMove(Position *newPosition, Player *player, Level *level);
int checkRoomChange(Player* player, Level* level, Position* newPosition);
void checkLevelUp(Player* player);
void goDownFloor(Player* player);

/*** enemy functions ***/
Enemy * newEnemySetUp(Level *level);
Enemy *scrollEventEnemySetUp(Player* player, Level* level);
void enemyMakeMove(Position *newPosition, Enemy *enemy, Level *level);
int enemyCheckPosition(Position *newPosition, Enemy *enemy, Level *level);
void enemyChooseMove(Enemy *enemy, Player* player, Level *level);
int detectedPlayer(Player* player, Enemy* enemy);
void moveTowardPlayer(Player* player, Enemy* enemy, Node* start, Node* end, Level* level);

/*** room functions ***/
Room *createRoom(int y, int x, int height, int width);
void drawRoom(Room *room, char ** map, int exitRoom);
void connectDoors(Node* start, Node* end, Level* level);

/*** combat functions ***/
void Attack(Player *player, Enemy *enemy, Level *level, int isPlayer);
int rollToHit(int AC, int modifier);
int checkDeathPlayer(Player *player);
int checkDeathEnemy(Enemy *enemy, Player *player, Level *level);

/*** item functions ***/
Item * getItemFromID(int id);
Item * getRandomItemFromSymbol(char symbol);
Item * newItemSetUp(Level *level);
Item * getItemFromPlayerLocation(Player *player, Level *level);

/*** Inventory functions ***/
void pickUpItem(Player *player, Level *level);
void dropItem(WINDOW *stats, Player *player);
void equipItem(WINDOW *stats, Player *player);
int checkPlayerInput(int r);
void usePotion(Player* player);
void useScroll(Player* player, Level* level);
void scrollEffects(Player* player, Level* level);

#endif