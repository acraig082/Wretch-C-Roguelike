#include "rogue.h"
#include <curses.h>
#include <ncurses.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************
 *  The map will keep track of the entire level.
 *  The view will be a cut out of a certain part
 *  of the map with the player in the center.
 *  The player will always be centralized in the
 *  middle of the terminal. The view will be bounded
 *  by the ends of the map. If the character gets close
 *  enough to one of the edges, no character will no longer
 *  be centralized within the view until they move away from the edge.
 *
 *  formal map access -> level->m[y-coordinate][x-coordinate]
 *
 * **********************************/

// set up and draw the rooms and doors
void mapSetUp(Level *level)
{
    Room **rooms;

    /// Partitions off map into sections for seperating random rooms
    int xPartitions = 5;
    int yPartitions = 6;
    level->numRooms = xPartitions * (yPartitions - 1);


    char **map = malloc(MAX_HEIGHT * sizeof(char *)); //rows
    for (int y = 0; y < MAX_HEIGHT; y++)
    {
        map[y] = malloc(MAX_WIDTH * sizeof(char)); //cols
        for (int x = 0; x < MAX_WIDTH; x++)
        {
            map[y][x] = ' ';
        }
    }

    ///              allocate view to empty
    char **visible = malloc(sizeof(char *) * MAX_HEIGHT);
    for (int y = 0; y < MAX_HEIGHT; y++)
    {
        visible[y] = malloc(sizeof(char) * MAX_WIDTH);
        for (int x = 0; x < MAX_WIDTH; x++)
        {
            visible[y][x] = ' ';                       //initialize a 2d char array to empty space ' '
        }
    }


    rooms = malloc(sizeof(Room) * xPartitions * yPartitions);

    double partitionW = 0;
    double partitionH = 0;
    int partitionWidth = 0;
    int partitionHeight = 0;


    partitionW = floor((double) MAX_WIDTH / xPartitions);
    partitionWidth = (int) partitionW;
    partitionH = floor((double) MAX_HEIGHT / yPartitions);
    partitionHeight = (int) partitionH;

    int exitRoom = rand() % level->numRooms;

    int i = 0;
    for (int m = 0; m < yPartitions - 1; m++)
    {
        for (int n = 0; n < xPartitions; n++)
        {
            int y = (rand() % (partitionHeight - 15)) + 2 + partitionHeight * m;
            int x = (rand() % (partitionWidth - 43)) + 2 + partitionWidth * n;
            int width = (rand() % (partitionWidth - 20) + 20);
            int height = (rand() % (partitionHeight - 5) + 5);
            rooms[i] = createRoom(y, x, height, width);
            if(i == exitRoom){
                drawRoom(rooms[i], map, TRUE);
            } else{
                drawRoom(rooms[i], map, FALSE);
            }
            i++;
        }
    }


    level->mapTiles = map;
    level->rooms = rooms;


    level->numOfEnemies = (rand() % (level->numRooms - 14)) + 20;
    level->foes = malloc(sizeof(Enemy) * (level->numOfEnemies + 4)); //4 extra enemies for scroll event
    for (int j = 0; j < level->numOfEnemies; j++)
    {
        level->foes[j] = *newEnemySetUp(level);
    }

    level->numOfItems = (rand() % 10) + 10;  //10 - 19
    level->loot =  malloc(sizeof(Item*) * level->numOfItems); //allocate for a random num of items on map
    for(int k = 0; k < level->numOfItems; k++)
    {
        level->loot[k] = newItemSetUp(level); //populate level with random item types
        if(level->loot[k]->sym == '?'){
            level->loot[k]->sym = '.';
        }
    }

    // initialize all nodes
    level->nodes = malloc(sizeof(Node**) * MAX_HEIGHT);
    for(int r = 0; r < MAX_HEIGHT; r++){
        level->nodes[r] = malloc(sizeof(Node*) * MAX_WIDTH);
        for(int c = 0; c < MAX_WIDTH; c++){
            level->nodes[r][c] = newNode(r, c);
            level->nodes[r][c]->cost = initialCostHallway(r, c, level);
        }
    }

    // initialize all node neighbors
    for(int g = 0; g < MAX_HEIGHT; g++){
        for(int h = 0; h < MAX_WIDTH; h++){
            getNewNeighbors(level->nodes[g][h], level);
        }
    }

    //draw all available doors
    for(int u = 0; u < level->numRooms; u++){
        for(int p = 0; p < 4; p++){
            switch (p){
                case 0:     ///left connection
                    //if room borders left
                    if(u % 5 == 0){
                        break;
                    }
                    connectDoors(level->nodes[level->rooms[u]->doors[0]->y][level->rooms[u]->doors[0]->x], level->nodes[level->rooms[u - 1]->doors[2]->y][level->rooms[u - 1]->doors[2]->x], level);
                    break;
                case 1:     ///up connection
                    //if room borders top
                    if(u < 5){
                        break;
                    }
                    connectDoors(level->nodes[level->rooms[u]->doors[1]->y][level->rooms[u]->doors[1]->x], level->nodes[level->rooms[u - 5]->doors[3]->y][level->rooms[u - 5]->doors[3]->x], level);
                    break;
                case 2:     ///right connection
                    //if room borders right
                    if(u % 5 == 4){
                        break;
                    }
                    connectDoors(level->nodes[level->rooms[u]->doors[2]->y][level->rooms[u]->doors[2]->x], level->nodes[level->rooms[u + 1]->doors[0]->y][level->rooms[u + 1]->doors[0]->x], level);
                    break;
                case 3:     ///down connection
                    //if room borders bottom
                    if(u > 19){
                        break;
                    }
                    connectDoors(level->nodes[level->rooms[u]->doors[3]->y][level->rooms[u]->doors[3]->x], level->nodes[level->rooms[u + 5]->doors[1]->y][level->rooms[u + 5]->doors[1]->x], level);
                    break;
                default:
                    break;
            }
        }
    }

    // initialize all nodes
    for(int r = 0; r < MAX_HEIGHT; r++){
        for(int c = 0; c < MAX_WIDTH; c++){
            level->nodes[r][c]->cost = initialCostEnemy(r, c, level);
        }
    }

    level->visible = visible;
    level->mapTiles = map;
}


char **cutOut(Level* level, int mapx, int mapy)
{
    //char ** newView = oldView;
    char **newView = malloc(sizeof(char *) * MAX_WIN_HEIGHT);
    for (int i = 0; i < MAX_WIN_HEIGHT; i++)
    {
        newView[i] = malloc(sizeof(char) * MAX_WIN_WIDTH);
    }

    if (mapx >= 0 && mapy >= 0)
    {
        for (int y = 0; y < MAX_WIN_HEIGHT - 1; y++)
        {
            for (int x = 0; x < MAX_WIN_WIDTH; x++)
            {
                if(level->visible[mapy + y][mapx + x] == level->mapTiles[mapy + y][mapx + x]){
                    newView[y][x] = level->mapTiles[mapy + y][mapx + x];
                }
                else{
                    newView[y][x] = ' ';
                }
            }
        }
    }

    return newView;

}

// if the player is near the edge of the screen, then dont scroll
char **cutOutView(Level* level, Player *player)
{
    /************\
     * direction
     *     1
     *  0 -|- 2
     *     3
     ************/

    int x = player->position.x;
    int y = player->position.y;

    int xBorder = (MAX_WIN_WIDTH - 2) / 2;
    int yBorder = (MAX_WIN_HEIGHT - 2) / 2;

    int mapx = x - xBorder;
    int mapy = y - yBorder;


    //shifting in x direction
    if (x - xBorder <= 1)
    {
        mapx = 0;
    } else if (x + xBorder >= MAX_WIDTH)
    {
        mapx = MAX_WIDTH - MAX_WIN_WIDTH;
    }

    //shifting view in y direction
    if (y - yBorder <= 1)
    {
        mapy = 0;
    } else if (y + yBorder >= MAX_HEIGHT)
    {
        mapy = MAX_HEIGHT - MAX_WIN_HEIGHT;
    }

    return cutOut(level, mapx, mapy);

}

void drawView(Player *player, char **newView, WINDOW *stats, WINDOW * statusText[], WINDOW *inventoryList, char *str, char *str2, char *str3, char *str4, char *str5) //, char *str, char *str2, char *str3
{
    drawInvWindow(inventoryList, player);
    drawStatsWindow(stats, statusText, player, str, str2, str3, str4, str5); //, str, str2, str3


    int y, x;

    for (y = 0; y < MAX_WIN_HEIGHT; y++)
    {
        for (x = 0; x < MAX_WIN_WIDTH; x++)
        {
            //attron(COLOR_PAIR(254));
            switch (newView[y][x]){
                case '@':
                    //attron(COLOR_PAIR(6));
                    mvprintw(y, x, "%c", newView[y][x]);
                    //attroff(COLOR_PAIR(6));
                    break;
                case WEAPON:
                case ARMOR:
                case POTION:
                case SCROLL:
                    //attron(COLOR_PAIR(3));
                    mvprintw(y, x, "%c", newView[y][x]);
                    //attroff(COLOR_PAIR(3));
                    break;
                case 'C':
                case 'g':
                case 'G':
                case 'k':
                case 'o':
                case 'O':
                case 'w':
                case 'z':
                case 'D':
                    //attron(A_ITALIC);
                    mvprintw(y, x, "%c", newView[y][x]);
                    //attroff(A_ITALIC);
                    break;
                case '%':
                    //attron(COLOR_PAIR(5));
                    mvprintw(y, x, "%c", newView[y][x]);
                    //attroff(COLOR_PAIR(5));
                    break;
                case '#':
                    //attron(COLOR_PAIR(5));
                    mvprintw(y, x, "%c", newView[y][x]);
                    //attroff(COLOR_PAIR(5));
                    break;
                case '|':
                case '-':
                    //attron(COLOR_PAIR(2));
                    mvprintw(y, x, "%c", newView[y][x]);
                    //attroff(COLOR_PAIR(2));
                    break;
                default:
                    mvprintw(y, x, "%c", newView[y][x]);
                    break;
            }
        }
    }

    for(int s = 0; s < MAX_WIN_WIDTH; s++){
        mvaddch(MAX_WIN_HEIGHT - 1, s, ' ');
    }

    wrefresh(stats);
    wrefresh(statusText[0]);
    wrefresh(statusText[1]);
    wrefresh(statusText[2]);
    wrefresh(statusText[3]);
    wrefresh(statusText[4]);
    wrefresh(inventoryList);
    wrefresh(stdscr);

}

void mapVisible(Level* level, Player* user){
    Room* r = level->rooms[user->roomNumber];
    if(r->isVisible == FALSE){
        //make room player is in visible
        int y = r->position.y;
        int x = r->position.x;

        for(int i = y; i < y + r->height; i++){
            for(int j = x; j < x + r->width; j++){
                level->visible[i][j] = level->mapTiles[i][j];
            }
        }
        //r->isVisible = TRUE;
    }

    if(level->mapTiles[user->position.y][user->position.x] == '+'){
        int stop = FALSE;
        int k = 1;
        while(stop == FALSE){
            if(level->mapTiles[user->position.y][user->position.x - k] != '#' &&
            level->mapTiles[user->position.y - k][user->position.x] != '#' &&
            level->mapTiles[user->position.y][user->position.x + k] != '#' &&
            level->mapTiles[user->position.y + k][user->position.x] != '#'){
                stop = TRUE;
            }
            else{
                if(level->mapTiles[user->position.y][user->position.x - k] == '#'){
                    level->visible[user->position.y][user->position.x - k] = '#';
                }
                if(level->mapTiles[user->position.y - k][user->position.x] == '#'){
                    level->visible[user->position.y - k][user->position.x] = '#';
                }
                if(level->mapTiles[user->position.y][user->position.x + k] == '#'){
                    level->visible[user->position.y][user->position.x + k] = '#';
                }
                if(level->mapTiles[user->position.y + k][user->position.x] == '#'){
                    level->visible[user->position.y + k][user->position.x] = '#';
                }
                k++;
            }
        }
    }

    for(int i = user->position.y - 2; i < user->position.y + 3; i++){
        for(int j = user->position.x - 2; j < user->position.x + 3; j++){
            level->visible[i][j] = level->mapTiles[i][j];
        }
    }

}
