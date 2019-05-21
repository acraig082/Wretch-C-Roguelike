#include "rogue.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void pickUpItem(Player *player, Level *level){
    switch(player->standingOn){
        /********************************************************************************
        * If user is standing on Item symbol, checks if inventory is full, if it isn't,
        * finds the smallest inventory slot empty. Fills that slot with the corresponding item
        * located in the level via location.
        ********************************************************************************/
        case (WEAPON):
        case (ARMOR):
        case (POTION):
        case (SCROLL):
            if(player->i.currentSize != player->i.capacity){
                int emptySlot = -1;
                for(int e = 0; e < player->i.capacity; e++){
                    if(player->i.inv[e]->itemID < 0){
                        emptySlot = e;
                        break;
                    }
                }
                player->i.inv[emptySlot] = getItemFromPlayerLocation(player, level);
                player->i.inv[emptySlot]->pos = &(player->position);
                player->standingOn = '.';                                               //removes the item from map
                player->i.currentSize++;
                snprintf(player->status, 100, "%s", player->i.inv[emptySlot]->description);
            }
            break;
        default:
            break;
    }
}

void dropItem(WINDOW *stats, Player *player){

    if(player->i.currentSize > 0){
        switch(player->standingOn){
            case ('.'):
                mvwprintw(stats, 2, 2, "which item do you want to drop?");
                wrefresh(stats);
                flushinp();

                int r = getch();
                int choice = checkPlayerInput(r);

                if(choice >= 0){
                    switch (player->i.inv[choice]->sym){
                        case WEAPON:
                        case ARMOR:
                        case POTION:
                        case SCROLL:
                            player->standingOn = player->i.inv[choice]->sym;
                            player->i.inv[choice]->pos = &(player->position);
                            player->i.inv[choice]->pickedUp = FALSE;
                            player->i.inv[choice] = newScroll("Empty", " ", -1, FALSE, '?', -1);
                            player->i.currentSize--;
                            sprintf(player->status, "equipped");
                            return;
                        default:
                            sprintf(player->status, "can't drop that");
                            return;
                    }
                }
                else{
                    sprintf(player->status, "can't drop that");
                }
                break;
            default:
                sprintf(player->status, "no room to drop");
                break;
        }
    }
    else{
        sprintf(player->status, "no items to drop");
    }
}

void equipItem(WINDOW *stats, Player *player){
    if(player->i.currentSize > 0){
        mvwprintw(stats, 2, 2, "which item do you want to equip?");
        wrefresh(stats);
        flushinp();

        int r = getch();

        int choice = checkPlayerInput(r);

        if(choice >= 0){
            switch (player->i.inv[choice]->sym){
                case WEAPON:
                    if((player->i.inv[choice]->itemID == 4 && player->weapon->base.itemID == 5) || (player->i.inv[choice]->itemID == 5 && player->weapon->base.itemID == 4)){
                        player->weapon = (Weapon *)getItemFromID(555);
                        sprintf(player->status, "Destruction will come upon them suddenly like a thief");
                        sprintf(player->status2, "within the night, whether they be awake or asleep. They will moan:");
                        sprintf(player->status3, "Fear and trembling have beset me, horror has overwhelmed me.");
                        player->i.inv[choice] = newScroll("Empty", " ", -1, FALSE, '?', -1);
                        player->i.currentSize--;
                    } else{
                        if(player->weapon->base.itemID >= 0){
                            Item *temp = player->i.inv[choice];
                            player->i.inv[choice] = (Item *)player->weapon;
                            player->weapon = (Weapon *)temp;
                        }
                        else{
                            player->weapon = (Weapon *)player->i.inv[choice];
                            player->i.inv[choice] = newScroll("Empty", " ", -1, FALSE, '?', -1);
                            player->i.currentSize--;
                        }
                    }
                    break;
                case ARMOR:
                    if(player->armor->base.itemID >= 0){
                        Item *temp = player->i.inv[choice];
                        player->i.inv[choice] = (Item *)player->armor;
                        player->armor = (Armor *)temp;
                    }
                    else{
                        player->armor = (Armor *)player->i.inv[choice];
                        player->i.inv[choice] = newScroll("Empty", " ", -1, FALSE, '?', -1);
                        player->i.currentSize--;
                    }
                    break;
                case POTION:
                    if(player->potion->base.itemID >= 0){
                        Item *temp = player->i.inv[choice];
                        player->i.inv[choice] = (Item *)player->potion;
                        player->potion = (Potion *)temp;
                    }
                    else{
                        Item *temp = player->i.inv[choice];
                        player->i.inv[choice] = newScroll("Empty", " ", -1, FALSE, '?', -1);
                        player->potion = (Potion *)temp;
                        player->i.currentSize--;
                    }
                    break;
                case SCROLL:
                    if(player->scroll->base.itemID >= 0){
                        Item *temp = player->i.inv[choice];
                        player->i.inv[choice] = (Item *)player->scroll;
                        player->scroll = (Scroll *)temp;
                    }
                    else{
                        player->scroll = (Scroll *)player->i.inv[choice];
                        player->i.inv[choice] = newScroll("Empty", " ", -1, FALSE, '?', -1);
                        player->i.currentSize--;
                    }
                    break;
                default:
                    sprintf(player->status, "can't equip that");
                    return;
            }

        }
        else{
            sprintf(player->status, "can't equip that");
        }
    }
    else{
        sprintf(player->status, "no items to equip");
    }
}

int checkPlayerInput(int r){
    int choice = -1;
    switch (r){
        case '0':
        case KEY_IC:
            choice = 0;
            break;
        case '1':
        case KEY_C1:
            choice = 1;
            break;
        case '2':
        case KEY_DOWN:
            choice = 2;
            break;
        case '3':
        case KEY_C3:
            choice = 3;
            break;
        case '4':
        case KEY_LEFT:
            choice = 4;
            break;
        case '5':
        case KEY_B2:
            choice = 5;
            break;
        case '6':
        case KEY_RIGHT:
            choice = 6;
            break;
        case '7':
        case KEY_A1:
            choice = 7;
            break;
        case '8':
        case KEY_UP:
            choice = 8;
            break;
        case '9':
        case KEY_A3:
            choice = 9;
            break;
        default:
            break;
    }

    return choice;
}

void usePotion(Player* player){
    if(player->potion->base.itemID > 0){
        if(player->potion->used == FALSE){
            int healed = rollDice(player->potion->healDice);
            if(healed + player->currentHealth > player->maxHealth){
                player->currentHealth = player->maxHealth;
                sprintf(player->status, "you feel invigorated");
            }
            else{
                player->currentHealth = player->currentHealth + healed;
                sprintf(player->status, "you feel better");
            }
            player->potion->used = TRUE;
        } else{
            sprintf(player->status, "potion empty");
        }
    } else{
        sprintf(player->status, "no potion to use");
    }
}

void useScroll(Player* player, Level* level){
    if(player->scroll->base.itemID > 0){
        if(player->scroll->uses != 0){
            scrollEffects(player, level);
            player->scroll->uses--;
        } else{
            sprintf(player->status, "the scroll doesn't seem to have the same effect");
        }
    } else{
        sprintf(player->status, "no scroll to use");
    }
}

void scrollEffects(Player* player, Level* level){
    int y = 0;
    int x = 0;
    switch (player->scroll->effect){
        case 0:
            player->exp += 35;
            player->scroll->uses = 0;
            sprintf(player->status, "you can't take your eyes off the scroll");
            sprintf(player->status2, "You're lucid again after the most wildest dreams.");
            sprintf(player->status3, "You perceive things around you differently.");
            break;
        case 1:
            for(int i = level->numOfEnemies; i < level->numOfEnemies + 4; i++){
                level->foes[i] = *scrollEventEnemySetUp(player, level);
            }
            sprintf(player->status, "4 Death Knights appear");
            break;
        case 2:
            do{
                 y = rand() % (MAX_HEIGHT - 5) + 2;
                 x = rand() % (MAX_WIDTH - 5) + 2;
            } while(level->mapTiles[y][x] != '.');
            Position p;
            p.y = y;
            p.x = x;
            playerMove(&p, player, level);
            break;
        case 3:
            player->currentHealth -= 10;
            break;
        case 4:
            sprintf(player->status, "you hear screams");
            break;
        case 5:
            player->scroll = emptyScroll();
            player->weapon = emptyWeapon();
            player->armor = emptyArmor();
            player->potion = emptyPotion();
            sprintf(player->status, "your armor and sword disintegrate and crumble into dust.");
            sprintf(player->status2, "where once was a scroll in your hands is now a plume of smoke.");
            break;
        default:
            break;
    }
}