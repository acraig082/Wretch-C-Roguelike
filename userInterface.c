#include "rogue.h"
#include <ncurses.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

void titleSequence()
{

    FILE *fp;

    char **title = malloc(MAX_WIN_HEIGHT * sizeof(char *)); //rows

    for (int y = 0; y < MAX_WIN_HEIGHT; y++)
    {
        title[y] = malloc(MAX_WIN_WIDTH * sizeof(char)); //cols
        for (int x = 0; x < MAX_WIN_WIDTH; x++)
        {
            title[y][x] = ' ';
        }
    }


    ///    frame 1    ///
    fp = fopen("../screens/title.txt", "r");
    int width = 100;

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char buff[width];

    while (fgets(buff, width, fp) != NULL)
    {
        printf("%s", buff);
    }

    fclose(fp);
    sleep(1);

    ///    frame 2    ///
    fp = fopen("../screens/title2.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char buff2[width];

    while (fgets(buff2, width, fp) != NULL)
    {
        printf("%s", buff2);
    }

    fclose(fp);
    sleep(1);


    ///    frame 3    ///
    fp = fopen("../screens/title3.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char buff3[width];

    while (fgets(buff3, width, fp) != NULL)
    {
        printf("%s", buff3);
    }

    fclose(fp);
    flushinp();
    getch();



    ///    frame 4    ///
    fp = fopen("../screens/controls.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char buff4[width];

    while (fgets(buff4, width, fp) != NULL)
    {
        printf("%s", buff4);
    }

    fclose(fp);
    flushinp();
    getch();

    ///    frame 5    ///
    fp = fopen("../screens/opening1.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char buff5[width];

    while (fgets(buff5, width, fp) != NULL)
    {
        printf("%s", buff5);
    }

    fclose(fp);
    sleep(1);


    ///    frame 6    ///
    fp = fopen("../screens/opening3.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char buff6[width];

    while (fgets(buff6, width, fp) != NULL)
    {
        printf("%s", buff6);
    }

    fclose(fp);
    flushinp();
    getch();


    ///    frame 7    ///
    fp = fopen("../screens/opening2.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char buff7[width];

    while (fgets(buff7, width, fp) != NULL)
    {
        printf("%s", buff7);
    }

    fclose(fp);
    sleep(1);

    for (int v = 0; v < MAX_WIN_HEIGHT; v++)
    {
        free(title[v]); //cols
    }
    free(title);
    flushinp();
}

void deathScreen(){
    FILE *fp;

    char **title = malloc(MAX_WIN_HEIGHT * sizeof(char *)); //rows
    for (int y = 0; y < MAX_WIN_HEIGHT; y++)
    {
        title[y] = malloc(MAX_WIN_WIDTH * sizeof(char)); //cols
        for (int x = 0; x < MAX_WIN_WIDTH; x++)
        {
            title[y][x] = ' ';
        }
    }


    ///    frame 1    ///
    fp = fopen("../screens/dead.txt", "r");
    int width = 100;

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char buff[width];

    while (fgets(buff, width, fp) != NULL)
    {
        printf("%s", buff);
    }

    fclose(fp);
    sleep(1);


    ///    frame 2    ///
    fp = fopen("../screens/dead2.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char buff2[width];

    while (fgets(buff2, width, fp) != NULL)
    {
        printf("%s", buff2);
    }

    fclose(fp);
    sleep(1);


    ///    frame 3    ///
    fp = fopen("../screens/dead3.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char buff3[width];

    while (fgets(buff3, width, fp) != NULL)
    {
        printf("%s", buff3);
    }

    fclose(fp);
    sleep(1);


    ///    frame 4    ///
    fp = fopen("../screens/retry.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char buff4[width];

    while (fgets(buff4, width, fp) != NULL)
    {
        printf("%s", buff4);
    }

    fclose(fp);
    for (int v = 0; v < MAX_WIN_HEIGHT; v++)
    {
        free(title[v]); //cols
    }
    free(title);
}

void drawStatsWindow(WINDOW * stats, WINDOW * statusText[], Player *player, char *str, char *str2, char* str3, char *str4, char *str5){ //, char *str, char *str2, char* str3

    for (int f = 0; f < MAX_WIN_WIDTH + 1; f++)
    {
        str[f] = ' ';
        str2[f] = ' ';
        str3[f] = ' ';
        str4[f] = ' ';
        str5[f] = ' ';
    }

    int buffSize = 10;
    char buff[buffSize];
    char buff2[buffSize];
    char buff3[buffSize];
    char buff4[buffSize];

    int parts = MAX_WIN_WIDTH / 8;
    int statusUpdate = 0;
    int hpPartition = parts * 5;
    int acPartition = parts * 6;
    int expPartition = parts * 7;

    /// display a status update for events(ex. hit, crit, level up)
    int h = 0; //indexer
    while (player->status[h] != '\0')
    {
        str[statusUpdate + h + 2] = player->status[h];
        h++;
    }
    while(h <= MAX_WIN_WIDTH){
        str[statusUpdate + h + 2] = ' ';
        h++;
    }
    h = 0;
    while(player->status2[h] != '\0'){
        str2[statusUpdate + h + 2] = player->status2[h];
        h++;
    }
    while(h <= MAX_WIN_WIDTH){
        str2[statusUpdate + h + 2] = ' ';
        h++;
    }
    h = 0;
    while(player->status3[h] != '\0'){
        str3[statusUpdate + h + 2] = player->status3[h];
        h++;
    }
    while(h <= MAX_WIN_WIDTH){
        str3[statusUpdate + h + 2] = ' ';
        h++;
    }
    h = 0;
    while(player->status4[h] != '\0'){
        str4[statusUpdate + h + 2] = player->status4[h];
        h++;
    }
    while(h <= MAX_WIN_WIDTH){
        str4[statusUpdate + h + 2] = ' ';
        h++;
    }
    h = 0;
    while(player->status5[h] != '\0'){
        str5[statusUpdate + h + 2] = player->status5[h];
        h++;
    }
    while(h <= MAX_WIN_WIDTH){
        str5[statusUpdate + h + 2] = ' ';
        h++;
    }


    mvwprintw(statusText[0], 0, 0, str);
    mvwprintw(statusText[1], 0, 0, str2);
    mvwprintw(statusText[2], 0, 0, str3);
    mvwprintw(statusText[3], 0, 0, str4);
    mvwprintw(statusText[4], 0, 0, str5);

    // once printed, shift status down
    h = 0;
    while(h != 99){
        player->status5[h] = player->status4[h];
        h++;
    }
    h = 0;
    while(h != 99){
        player->status4[h] = player->status3[h];
        h++;
    }
    h = 0;
    while(h != 99){
        player->status3[h] = player->status2[h];
        h++;
    }
    h = 0;
    while(h != 99){
        player->status2[h] = player->status[h];
        h++;
    }
    h = 0;
    while(h != 99){
        player->status[h] = ' ';
        h++;
    }

    for (int f = 0; f < MAX_WIN_WIDTH + 1; f++)
    {
        str[f] = ' ';
    }


    /// display HP
    strcpy(str, "HP:");
    snprintf(buff, 10, "%d/%d", player->currentHealth, player->maxHealth);
    strcat(str, buff);


    mvwprintw(stats, 2, hpPartition, str);


    for (int f = 0; f < MAX_WIN_WIDTH + 1; f++)
    {
        str[f] = ' ';
    }


    /// display AC
    strcpy(str, "AC:");
    snprintf(buff2, 10, "%d", player->armor->armorClass);
    strcat(str, buff2);

    // print ac
    mvwprintw(stats, 2, acPartition, str);

    // clear string
    for (int f = 0; f < MAX_WIN_WIDTH + 1; f++)
    {
        str[f] = ' ';
    }


    /// display EXP
    strcpy(str, "EXP:");
    snprintf(buff3, 10, "%d", player->exp);
    strcat(str, buff3);

    mvwprintw(stats, 2, expPartition, str);

    // clear string
    for (int f = 0; f < MAX_WIN_WIDTH + 1; f++)
    {
        str[f] = ' ';
        str2[f] = ' ';
//        str3[f] = ' ';
//        str4[f] = ' ';
//        str5[f] = ' ';
    }


    /// display Player Level
    strcpy(str, "LVL:");
    snprintf(buff4, 10, "%d", player->level);
    strcat(str, buff4);

    mvwprintw(stats, 3, expPartition, str);

    box(stats, 0, 0);   // window border
    //box(statusText, 0, 0);
}

void drawInvWindow(WINDOW *invList, Player *player){

    mvwprintw(invList, 4, 5, "                ");
    mvwprintw(invList, 5, 4, "                ");
    mvwprintw(invList, 6, 5, "                ");
    mvwprintw(invList, 7, 5, "                ");
    mvwprintw(invList, 8, 5, "                ");
    mvwprintw(invList, 9, 5, "                ");
    mvwprintw(invList, 10, 5, "                ");
    mvwprintw(invList, 11, 5, "                ");
    mvwprintw(invList, 12, 5, "                ");
    mvwprintw(invList, 13, 5, "                ");

    mvwprintw(invList, 33, 11, "                    ");
    mvwprintw(invList, 34, 11, "                    ");
    mvwprintw(invList, 35, 11, "                    ");
    mvwprintw(invList, 36, 11, "                    ");


    char *str = malloc(sizeof(char) * MAX_WIN_WIDTH );
    for (int f = 0; f < MAX_WIN_WIDTH + 1; f++)
    {
        str[f] = ' ';
    }

    box(invList,0,0);
    mvwprintw(invList, 1, 1, "Inventory");
    mvwprintw(invList, 2, 1, "_________");

    char *buf = malloc(sizeof(char)*1);
    char *buf2 = malloc(sizeof(char)*2);
    sprintf(buf, "%d", player->i.currentSize);
    mvwprintw(invList, 1, 14, buf);
    mvwprintw(invList, 1, 15, "/");
    sprintf(buf2, "%d", player->i.capacity);
    mvwprintw(invList, 1, 16, buf2);

    mvwprintw(invList, 4, 1, "(0)");
    mvwprintw(invList, 5, 1, "(1)");
    mvwprintw(invList, 6, 1, "(2)");
    mvwprintw(invList, 7, 1, "(3)");
    mvwprintw(invList, 8, 1, "(4)");
    mvwprintw(invList, 9, 1, "(5)");
    mvwprintw(invList, 10, 1, "(6)");
    mvwprintw(invList, 11, 1, "(7)");
    mvwprintw(invList, 12, 1, "(8)");
    mvwprintw(invList, 13, 1, "(9)");

    for(int i = 0; i < player->i.capacity; i++){

        mvwprintw(invList, 4 + i, 5, player->i.inv[i]->itemName);

    }


    mvwprintw(invList, 30, 1, "Equipment");
    mvwprintw(invList, 31, 1, "_________");
    mvwprintw(invList, 33, 1, "Weapon : ");
    mvwprintw(invList, 33, 11, player->weapon->base.itemName);
    mvwprintw(invList, 34, 1, "Armor  : ");
    mvwprintw(invList, 34, 11, player->armor->base.itemName);
    mvwprintw(invList, 35, 1, "Potion : ");
    mvwprintw(invList, 35, 11, player->potion->base.itemName);
    mvwprintw(invList, 36, 1, "Scroll : ");
    mvwprintw(invList, 36, 11, player->scroll->base.itemName);


    free(str);
}
