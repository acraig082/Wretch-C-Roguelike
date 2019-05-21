#include "rogue.h"
#include "headers/enemy.h"
#include <string.h>
#include <ncurses.h>
#include <curses.h>

void Attack(Player *player, Enemy *enemy, Level *level, int isPlayer)
{

    int dmg = 0;
    char str[40];
    char str2[10];

    ///user makes attack attempt
    if (isPlayer == 1)
    {
        switch (rollToHit(enemy->armorClass, player->abilities.DEX))
        {
            case -1:    //crit fail
                //stop hitting yourself, stop hitting yourself...
                dmg = rollDice(player->weapon->damage);
                dmg += player->abilities.STR;

                player->currentHealth -= dmg;

                sprintf(player->status, "you accidently hit yourself");
                break;
            case 0:     //miss
                sprintf(player->status, "you stagger and miss");
                break;
            case 1:     //hit
                dmg = rollDice(player->weapon->damage);
                dmg += player->abilities.STR;

                enemy->health -= dmg;

                strcpy(str, "strike landed for ");
                snprintf(str2, 10, "%d dmg", dmg);
                strcat(str, str2);
                sprintf(player->status, "%s", str);
                break;
            case 2:     //crit
                dmg = rollDice(player->weapon->damage);
                dmg += rollDice(player->weapon->damage);
                dmg += player->abilities.STR;

                enemy->health -= dmg;

                snprintf(str2, 10, "%d ", dmg);
                strcpy(str, "critical damage dealt");
                strcat(str2, str);
                sprintf(player->status, "%s", str2);
                break;
            default:
                break;
        }
    }
        ///enemy attemps to attack
    else
    {
        switch (rollToHit(player->armor->armorClass, -(player->abilities.DEX)))
        {
            case -1:    //crit fail
                //stop hitting yourself, stop hitting yourself...
                dmg = rollDice(enemy->hit);
                enemy->health -= dmg;
                break;
            case 0:     //miss
                //
                break;
            case 1:     //hit
                dmg = rollDice(enemy->hit);
                player->currentHealth -= dmg;
                break;
            case 2:     //crit
                dmg = rollDice(enemy->hit);
                dmg += rollDice(enemy->hit);
                player->currentHealth -= dmg;
                break;
            default:
                break;
        }
    }
}

int rollToHit(int AC, int modifier)
{
    int roll = rand() % 21;//roll d20 to hit


    if (roll >= 20)
    {                       //crit
        return 2;
    } else if (roll == 0)
    {                       //crit fail
        roll = rand() % 2; // 1/40 chance for crit fail
        if(roll == 1){
            return -1;
        }
        else{
            return 0;
        }
    } else
    {
        roll = roll + modifier;
        if (roll - AC >= 0)
        {     //hit
            return 1;
        } else
        {
            return 0;       //miss
        }
    }
}


int checkDeathPlayer(Player *player)
{
    if (player->currentHealth <= 0)
    {
        return 1;
    } else
    {
        return 0;
    }
}

int checkDeathEnemy(Enemy *enemy, Player *player, Level *level)
{
    if (enemy->health <= 0)
    {
        player->exp += enemy->expWorth;
        //level->numOfEnemies--;
        enemy->symbol = '!';
        level->mapTiles[enemy->position.y][enemy->position.x] = enemy->standingOn;
        enemy->position.x = 0;
        enemy->position.y = 0;
        return 1;
    } else
    {
        return 0;
    }
}
