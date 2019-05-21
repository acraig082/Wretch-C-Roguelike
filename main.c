#include "rogue.h"
#include <ncurses.h>
#include <curses.h>
#include <windows.h>
#include <sys/time.h>

int main()
{
    Player *user = malloc(sizeof(Player*));                             //the user
    int ch;                                                             //the key the user presses each turn
    Position *newPosition;                                              //user's new position they are trying to move to
    Level *l = malloc(sizeof(Level));                                   //a structure to hold the map, rooms, enemies
    int gameover = FALSE;                                               //bool to check if game is over
    char *str = malloc(sizeof(char) * MAX_WIN_WIDTH );                  //
    char *str2 = malloc(sizeof(char) * MAX_WIN_WIDTH );                 //
    char *str3 = malloc(sizeof(char) * MAX_WIN_WIDTH );                 //  status strings
    char *str4 = malloc(sizeof(char) * MAX_WIN_WIDTH );                 //
    char *str5 = malloc(sizeof(char) * MAX_WIN_WIDTH );                 //
    int newLevel = FALSE;



    ///***************** pre-processing **********************///
    HWND hWnd;
    SetConsoleTitle("W R E T C H");
    hWnd = FindWindow(NULL, "W R E T C H");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD NewSBSize = GetLargestConsoleWindowSize(hOut);
    SMALL_RECT DisplayArea = {0, 0, 0, 0};

    SetConsoleScreenBufferSize(hOut, NewSBSize);

    DisplayArea.Right = NewSBSize.X - 1;
    DisplayArea.Bottom = NewSBSize.Y - 1;

    SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
    ShowWindow(hWnd, SW_MAXIMIZE);

    /// ncurses start-up methods
    initscr();                      // creates WINDOW* stdsrc
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    srand((unsigned int)time(NULL));

    resize_term(MAX_WIN_HEIGHT + 10, MAX_WIN_WIDTH + 25);

    /// new windows separate from stdscr. This window is for displaying stats and updates
    WINDOW * stats = newwin(7, MAX_WIN_WIDTH, MAX_WIN_HEIGHT, 0); //(lines, columns, y, x)
    WINDOW * inv = newwin(MAX_WIN_HEIGHT + 7, 24, 0, MAX_WIN_WIDTH + 1);
    WINDOW * statusText[5];
    statusText[0] = newwin(5, 80, MAX_WIN_HEIGHT + 1, 2);
    statusText[1] = newwin(4, 80, MAX_WIN_HEIGHT + 2, 2);
    statusText[2] = newwin(3, 80, MAX_WIN_HEIGHT + 3, 2);
    statusText[3] = newwin(2, 80, MAX_WIN_HEIGHT + 4, 2);
    statusText[4] = newwin(1, 80, MAX_WIN_HEIGHT + 5, 2);

    refresh();

/*************************************************************************************/

    ///      Game Loop
    while(gameover == FALSE){
        ///              allocate view to empty
        char **view = malloc(sizeof(char *) * MAX_WIN_HEIGHT);
        for (int y = 0; y < MAX_WIN_HEIGHT; y++)
        {
            view[y] = malloc(sizeof(char) * MAX_WIN_WIDTH);
            for (int x = 0; x < MAX_WIN_WIDTH; x++)
            {
                view[y][x] = ' ';                       //initialize a 2d char array to empty space ' '
            }
        }


        if(newLevel == FALSE){
            titleSequence();
            erase();
            clear();
        }

        ///  set-up map
        mapSetUp(l);
        erase();
        clear();
        if(newLevel == FALSE){
            user = playerSetUp(l);
        }else{
            newLevel = FALSE;
            user->newFloor = FALSE;
            for(int i = 0; i < MAX_HEIGHT; i++){
                for(int j = 0; j < MAX_WIDTH; j++){
                    if(l->mapTiles[i][j] == '.' && l->mapTiles[i + 1][j] == '.' &&
                    l->mapTiles[i - 1][j] == '.' && l->mapTiles[i][j + 1] == '.' &&
                    l->mapTiles[i][j - 1] == '.'){
                        user->position.y = i;
                        user->position.x = j;
                        user->standingOn = '.';
                        checkRoomChange(user, l, &user->position);
                    }
                }
            }
        }

        ///             Turn Loop
        while ((ch = getch()) != 'q' && checkDeathPlayer(user) != 1)
        {

            ///           Player Move
            newPosition = handleInput(stats, ch, user, l);
            checkPosition(newPosition, user, l);
            checkLevelUp(user);

            ///             Enemy move
            for (int z = 0; z < l->numOfEnemies + 4; z++)
            {
                if(l->foes[z].symbol != '!'){
                    if (checkDeathEnemy(&(l->foes[z]), user, l) == 0){
                        enemyChooseMove(&(l->foes[z]), user, l);
                    }
                }
            }

            ///       drawing
            mapVisible(l, user);
            view = cutOutView(l, user);
            drawView(user, view, stats, statusText, inv, str, str2, str3, str4, str5); //

            newLevel = user->newFloor;
            if(ch == 'q' || user->newFloor == TRUE) break;
        }

        if(ch == 'q') break;        // if player pressed 'q', skip death sequence

        ///             Death Sequence
        if(newLevel == FALSE){
            deathScreen();
            flushinp();
            int retry;
            do{
                retry = getch();
                if(retry == 'y' || retry == 'Y'){
                    gameover = FALSE;
                }
                else if(retry == 'n' || retry == 'N'){
                    gameover = TRUE;
                }
                else{
                    retry = -1;
                    flushinp();
                }
            } while(retry < 0);
        }

        free(view);
    }

    endwin();
    return 0;
}