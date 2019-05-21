#include "rogue.h"
#include <math.h>
#include <curses.h>
#include <ncurses.h> //All output functions take y co-ordinate first and then x in their arguments

Player *playerSetUp(Level *level)
{
    Player *newPlayer;
    newPlayer = malloc(sizeof(Player));

    // puts player in the first room
    newPlayer->position.x = level->rooms[0]->position.x + 2;
    newPlayer->position.y = level->rooms[0]->position.y + 2;
    newPlayer->roomNumber = 0;

    // starting stats
    newPlayer->maxHealth = 30;
    newPlayer->currentHealth = 30;
    newPlayer->exp = 0;
    newPlayer->level = 0;
    newPlayer->newFloor = FALSE;
    for (int f = 0; f < 39; f++)
    {
        newPlayer->status[f] = ' ';
        newPlayer->status2[f] = ' ';
        newPlayer->status3[f] = ' ';
    }

    // starting ability scores
    newPlayer->abilities.STR = 0;
    newPlayer->abilities.DEX = 0;
    newPlayer->abilities.CON = 0;
    newPlayer->abilities.INT = 0;

    // setting up inventory
    int invCapacity = 10;
    newPlayer->i.currentSize = 0;
    newPlayer->i.capacity = invCapacity;
    newPlayer->i.inv = malloc(sizeof(Item*) * invCapacity);
    for(int b = 0; b < invCapacity; b++){
        newPlayer->i.inv[b] = newScroll("Empty", " ", -1, FALSE, '?', -1);
    }

    // starting equipment
    newPlayer->weapon = (Weapon *)getItemFromID(3);
    newPlayer->armor = emptyArmor();
    newPlayer->potion = emptyPotion();
    newPlayer->scroll = emptyScroll();


    // place on map
    newPlayer->standingOn = level->mapTiles[newPlayer->position.y][newPlayer->position.x];
    mvprintw(newPlayer->position.y, newPlayer->position.x, "@");
    move(newPlayer->position.y, newPlayer->position.x);

    sprintf(newPlayer->status2, "My terminal supports %d colors.", COLORS);

    return newPlayer;
}

Position *handleInput(WINDOW *stats, int input, Player *player, Level *level)
{
    /************\
     * direction
     *     1
     *  0 -|- 2
     *     3
     ************/

    Position *newPosition;
    newPosition = malloc(sizeof(Position));

    switch (input)
    {
        /* move up */
        case 'w':
        case 'W':
        case KEY_UP:
            newPosition->y = player->position.y - 1;
            newPosition->x = player->position.x;
            break;
        /* move down */
        case 's':
        case 'S':
        case KEY_DOWN:
            newPosition->y = player->position.y + 1;
            newPosition->x = player->position.x;
            break;
        /* move left */
        case 'a':
        case 'A':
        case KEY_LEFT:
            newPosition->y = player->position.y;
            newPosition->x = player->position.x - 1;
            break;
        /* move right */
        case 'd':
        case 'D':
        case KEY_RIGHT:
            newPosition->y = player->position.y;
            newPosition->x = player->position.x + 1;
            break;
        /* beep */
        case 'b':
        case 'B':
            beep();
            flash();
            newPosition->y = player->position.y;
            newPosition->x = player->position.x;
            break;
        /* pick up */
        case 'g':
        case 'G':
            pickUpItem(player, level);
            newPosition->y = player->position.y;
            newPosition->x = player->position.x;
            break;
        /* drop */
        case 't':
        case 'T':
            dropItem(stats, player);
            newPosition->y = player->position.y;
            newPosition->x = player->position.x;
            break;
        /* equip */
        case 'e':
        case 'E':
            equipItem(stats, player);
            newPosition->y = player->position.y;
            newPosition->x = player->position.x;
            break;
        /* use equipped potion */
        case 'p':
        case 'P':
            usePotion(player);
            newPosition->y = player->position.y;
            newPosition->x = player->position.x;
            break;
        /* use equipped scroll */
        case 'o':
        case 'O':
            useScroll(player, level);
            newPosition->y = player->position.y;
            newPosition->x = player->position.x;
            break;
        /* go down a floor */
        case '[':
            goDownFloor(player);
            newPosition->y = player->position.y;
            newPosition->x = player->position.x;
            break;
//        case KEY_MOUSE:
//            if(getmouse(&event) == OK){
//                return handleMouseInput(event, player, level);
//            }
//            break;
        default:
            newPosition->y = player->position.y;
            newPosition->x = player->position.x;
            break;
    }

    return newPosition;
}

//Position* handleMouseInput(MEVENT event, Player* player, Level* level){
//    Position* p = Position_new(event.y, event.x);
//
//    if(event.bstate & BUTTON1_PRESSED){
//        if(abs(event.y - player->position.y) < 10 && abs(event.x - player->position.x) < 10)
//        {
//            return p;
//        }
//        else {
//            return NULL;
//        }
//    }
//    else{
//        return NULL;
//    }
//}

/* check what is at next position */
int checkPosition(Position *newPosition, Player *player, Level *level)
{

    if (newPosition->y > MAX_HEIGHT - 2 ||
        newPosition->y < 0 ||
        newPosition->x > MAX_WIDTH - 2 ||
        newPosition->x < 0)
    {
        move(player->position.y, player->position.x);
        return 0;
    }
    else
    {
        switch (level->mapTiles[newPosition->y][newPosition->x])
        {
            case '.':
                // check if player has changed rooms
                if(checkRoomChange(player, level, newPosition) == TRUE)   return 1;
            case '#':
            case '+':
            case '%':
            case WEAPON:
            case ARMOR:
            case POTION:
            case SCROLL:
                playerMove(newPosition, player, level);
                return 1;
            case 'C':
            case 'g':
            case 'G':
            case 'k':
            case 'o':
            case 'O':
            //case 'w':
            case 'z':
            case 'D':
                for (int n = 0; n < level->numOfEnemies + 4; n++)
                {
                    if (level->foes[n].position.x == newPosition->x && level->foes[n].position.y == newPosition->y)
                    {
                        Attack(player, &(level->foes[n]), level, 1);
                    }
                }
                return 0;
            default:
//                playerMove(newPosition, player, level); //  no-clip for
//                return 1;                             //    testing
              move(player->position.y, player->position.x);
              return 0;
        }
    }

}

void playerMove(Position *newPosition, Player *player, Level *level)
{
    level->mapTiles[player->position.y][player->position.x] = player->standingOn;
    player->standingOn = level->mapTiles[newPosition->y][newPosition->x];

    level->mapTiles[newPosition->y][newPosition->x] = '@';
    move(newPosition->y, newPosition->x);

    player->position.y = newPosition->y;
    player->position.x = newPosition->x;

}

int checkRoomChange(Player* player, Level* level, Position* newPosition){
    if(level->mapTiles[player->position.y][player->position.x] != '.'){ //if just steping into room, change player's room
        int lastRoom = player->roomNumber;

        //check if player is just re-entering same room
        for(int i = level->rooms[lastRoom]->position.y; i < (level->rooms[lastRoom]->position.y + level->rooms[lastRoom]->height); i++){
            for(int j = level->rooms[lastRoom]->position.x; j < (level->rooms[lastRoom]->position.x + level->rooms[lastRoom]->width); j++){
                if(i == newPosition->y && j == newPosition->x){
                    playerMove(newPosition, player, level);
                    return 1;
                }
            }
        }

        //brute force check all rooms
        for (int k = 0; k < level->numRooms; k++){
            for(int g = level->rooms[k]->position.y; g < (level->rooms[k]->position.y + level->rooms[k]->height); g++){
                for(int h = level->rooms[k]->position.x; h < (level->rooms[k]->position.x + level->rooms[k]->width); h++){
                    if(g == newPosition->y && h == newPosition->x){
                        //level->rooms[player->roomNumber]->isVisible = FALSE;
//                        int y = level->rooms[player->roomNumber]->position.y;
//                        int x = level->rooms[player->roomNumber]->position.x;
//                        int h = level->rooms[player->roomNumber]->height;
//                        int w = level->rooms[player->roomNumber]->width;
//                        for(int i = y; i < y + h; i++){
//                            for(int j = x; j < x + w; j++){
//                                if(level->mapTiles[i][j] != '|' && level->mapTiles[i][j] != '-' && level->mapTiles[i][j] != '+'){
//                                    level->visible[i][j] = '.';
//                                }
//                            }
//                        }

                        player->roomNumber = k;
                        //level->rooms[player->roomNumber]->isVisible = TRUE;
                        playerMove(newPosition, player, level);
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void checkLevelUp(Player* player){
    if(player->exp > 30 && player->level == 0){
        player->level = 1;
    } else if(player->exp > 60 && player->level == 1){
        player->level = 2;
    } else if(player->exp > 90 && player->level == 2){
        player->level = 3;
    } else if(player->exp > 130 && player->level == 3){
        player->level = 4;
    } else if(player->exp > 180 && player->level == 4){
        player->level = 5;
    } else if(player->exp > 220 && player->level == 5){
        player->level = 6;
    } else if(player->exp > 300 && player->level == 6){
        player->level = 7;
    } else if(player->exp > 400 && player->level == 7){
        player->level = 8;
    } else if(player->exp > 500 && player->level == 8){
        player->level = 9;
    } else if(player->exp > 600 && player->level == 9){
        player->level = 10;
    } else{
        return;
    }


    int ability = rand() % 4;
    switch (ability){
        case 0:         // Upgrade STR
            player->abilities.STR++;
            sprintf(player->status, "you feel stronger");
            break;
        case 1:         // Upgrade DEX
            player->abilities.DEX++;
            sprintf(player->status, "you feel quicker");
            break;
        case 2:         // Upgrade CON
            player->abilities.CON++;
            player->maxHealth += 5;
            sprintf(player->status, "you feel healthier");
            break;
        case 3:         // Upgrade INT
            player->abilities.INT++;
            sprintf(player->status, "you feel more focused");
            break;
        default:
            break;
    }
    player->currentHealth = player->maxHealth;
}

void goDownFloor(Player* player){
    if(player->standingOn == '%'){
        player->newFloor = TRUE;
    }
}

Position* Position_new(int y, int x){
    Position* p = malloc(sizeof(Position));
    p->y = y;
    p->x = x;
    return p;
}