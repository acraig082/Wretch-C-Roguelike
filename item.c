#include "rogue.h"
#include "headers/item.h"
#include "headers/weapon.h"
#include "headers/armor.h"
#include "headers/scroll.h"
#include "headers/potion.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>

Item * getItemFromID(int id){
    char * name;
    char * desc;
    int used = FALSE;

    /// WEAPONS
    if(id < 100 || id == 555){
        Dice *dice = malloc(sizeof(Dice));
        int dual = FALSE;
        char sym = WEAPON;

        switch (id){
            case 0:
                name = "Studded Mace";
                desc = "Metal mace studded at the end for their pleasure.";
                dice->quantity = 1;
                dice->sides = 7;
                return newWeapon(name, desc, id, dice, used, dual, sym);
            case 1:
                name = "Kopis";
                desc = "Heavy knife with a curved blade.";
                dice->quantity = 2;
                dice->sides = 3;
                dual = FALSE;
                return newWeapon(name, desc, id, dice, used, dual, sym);
            case 2:
                name = "Khopesh";
                desc = "Big blade curved at the end. Half-sword, half-axe.";
                dice->quantity = 1;
                dice->sides = 10;
                dual = FALSE;
                return newWeapon(name, desc, id, dice, used, dual, sym);
            case 3:
                name = "Xiphos";
                desc = "Bronze sword with a wide, relatively short blade.";
                dice->quantity = 1;
                dice->sides = 6;
                dual = FALSE;
                return newWeapon(name, desc, id, dice, used, dual, sym);
            case 4:
                name = "Fear";
                desc = "Destruction will come upon them suddenly like a thief within the night...";
                dice->quantity = 2;
                dice->sides = 6;
                dual = TRUE;
                return newWeapon(name, desc, id, dice, used, dual, sym);
            case 5:
                name = "Trembling";
                desc = "...whether they be awake or asleep. They will moan:\n \"Fear and trembling have beset me\n   horror has overwhelmed me.\"";
                dice->quantity = 2;
                dice->sides = 6;
                dual = TRUE;
                return newWeapon(name, desc, id, dice, used, dual, sym);
            case 555:
                name = "Fear & Trembling";
                desc = "...whether they be awake or asleep. They will moan:\n \"Fear and trembling have beset me\n   horror has overwhelmed me.\"";
                dice->quantity = 2;
                dice->sides = 12;
                dual = TRUE;
                return newWeapon(name, desc, id, dice, used, dual, sym);
            default:
                break;
        }
    }
    /// ARMOR
    else if(id >= 100 && id < 200){
        int armorClass = 0;
        char sym = ARMOR;

        switch (id){
            case 100:
                name = "Iron Armor";
                desc = "Heavy iron that will protect you from most man-made weapons.";
                armorClass = 17;
                return newArmor(name, desc, id, armorClass, used, sym);
            case 101:
                name = "Steel Plate A.";
                desc = "Reinforced plate steel. Very expensive and very well polished.";
                armorClass = 18;
                return newArmor(name, desc, id, armorClass, used, sym);
            case 102:
                name = "Leather Armor";
                desc = "Stiffened breastplate and shoulders. Soft at the joints for quick movement.";
                armorClass = 14;
                return newArmor(name, desc, id, armorClass, used, sym);
            case 103:
                name = "Chainmail";
                desc = "Can protect light blows but shines when defending against projectiles";
                armorClass = 14;
                return newArmor(name, desc, id, armorClass, used, sym);
            case 104:
                name = "Scale Armor";
                desc = "Flexible but tough.";
                armorClass = 16;
                return newArmor(name, desc, id, armorClass, used, sym);
            case 105:
                name = "Reinforced Mail";
                desc = "Reinforced Chainmail.";
                armorClass = 15;
                return newArmor(name, desc, id, armorClass, used, sym);
            default:
                break;
        }
    }
    /// POTIONS
    else if(id >= 200 && id < 300){
        Dice *dice = malloc(sizeof(Dice));
        char sym = POTION;

        switch (id){
            case 200:
                name = "Health Potion";
                desc = "It looks to be a healing liquid but could also be disastrous";
                dice->sides = 10;
                dice->quantity= 1;
                return newPotion(name, desc, id, dice, used, sym);
            case 201:
                name = "Red Gloop";
                desc = "It looks to be a healing liquid but could also be disastrous";
                dice->sides = 6;
                dice->quantity= 1;
                return newPotion(name, desc, id, dice, used, sym);
            case 202:
                name = "Green Sludge";
                desc = "It looks to be a healing liquid but could also be disastrous";
                dice->sides = 4;
                dice->quantity= 1;
                return newPotion(name, desc, id, dice, used, sym);
            case 203:
                name = "Filthy Liquid";
                desc = "It looks to be a healing liquid but could also be disastrous";
                dice->sides = 2;
                dice->quantity= 1;
                return newPotion(name, desc, id, dice, used, sym);
            case 204:
                name = "Bitters";
                desc = "It looks to be a healing liquid but could also be disastrous";
                dice->sides = 5;
                dice->quantity= 1;
                return newPotion(name, desc, id, dice, used, sym);
            default:
                break;
        }
    }
    /// SCROLLS
    else if(id >= 300 && id < 400){
        char sym = SCROLL;
        switch (id){
            case 300:
                name = "aASadfsl";
                desc = "You can't understand it's cryptic, guttural language";
                return newScroll(name, desc, id, used, sym, 0);
            case 301:
                name = "LJHhkjh";
                desc = "You can't understand it's cryptic, guttural language";
                return newScroll(name, desc, id, used, sym, 1);
            case 302:
                name = "zLdSASDQ";
                desc = "You can't understand it's cryptic, guttural language";
                return newScroll(name, desc, id, used, sym, 2);
            case 303:
                name = "JUOMNlnht";
                desc = "You can't understand it's cryptic, guttural language";
                return newScroll(name, desc, id, used, sym, 3);
            case 304:
                name = "alfcTwOJB";
                desc = "You can't understand it's cryptic, guttural language";
                return newScroll(name, desc, id, used, sym, 4);
            case 305:
                name = "sifvnwHKJs";
                desc = "You can't understand it's cryptic, guttural language";
                return newScroll(name, desc, id, used, sym, 5);
            default:
                break;
        }
    }
    return newScroll("Empty", " ", -1, FALSE, '?', -1);
}

Item * getRandomItemFromSymbol(char symbol){
    int ran = rand() % 6; //0-5
    switch (symbol){
        case WEAPON:
            return getItemFromID(ran);
        case ARMOR:
            return getItemFromID(ran + 100);
        case POTION:
            return getItemFromID(ran + 200);
        case SCROLL:
            return getItemFromID(ran + 300);
        default:
            break;
    }

    return newScroll("Empty", " ", -1, FALSE, '?', -1);
}

Item * newItemSetUp(Level * level){
    Item * newItem = malloc(sizeof(Item));

    //new item can either be armor, weapon, potion, or scroll
    //all we need right now is position and symbol.
    //item will be randomized when player picks it up
    int newItemType = rand() % NUM_ITEM_TYPES;

    //random position

    switch (newItemType){
        case 0: //weapon
            newItem = getRandomItemFromSymbol(WEAPON);
            break;
        case 1:
            newItem = getRandomItemFromSymbol(ARMOR);
            break;
        case 2:
            newItem = getRandomItemFromSymbol(POTION);
            break;
        case 3:
            newItem = getRandomItemFromSymbol(SCROLL);
            break;
        default:
            break;

    }

    int randRoom = (rand() % level->numRooms - 3) + 3;

    newItem->pos = malloc(sizeof(Position));

    newItem->pos->x = level->rooms[randRoom]->position.x + (rand() % (level->rooms[randRoom]->width - 4)) + 2;
    newItem->pos->y = level->rooms[randRoom]->position.y + (rand() % (level->rooms[randRoom]->height - 4)) + 2;

    level->mapTiles[newItem->pos->y][newItem->pos->x] = newItem->sym;
    mvaddch(newItem->pos->y, newItem->pos->x, newItem->sym);

    return newItem;
}

Item * getItemFromPlayerLocation(Player *player, Level *level){
    int y = player->position.y;
    int x = player->position.x;
    for (int n = 0; n < level->numOfItems; n++)
    {
        if(level->loot[n]->pos->y == y && level->loot[n]->pos->x == x && level->loot[n]->pickedUp == FALSE){
            if(level->loot[n]->sym == SCROLL){
                Scroll* s = (Scroll*)level->loot[n];
                s->uses = player->abilities.INT + 1;
            }
            level->loot[n]->pickedUp = TRUE;
            return level->loot[n];
        }
    }

    return newScroll("Empty", " ", -1, FALSE, '?', -1);
}