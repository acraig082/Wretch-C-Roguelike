#ifndef FINALPROJECT_SCROLL_H
#define FINALPROJECT_SCROLL_H

#include "item.h"

typedef struct Scroll{
    Item base;
    char *contents;
    int used;
    int uses;
    int effect;
}Scroll;

Item * newScroll(char *scrollName, char *contents, int idNum, int used, char symbol, int effect);
Scroll * emptyScroll();

#endif //FINALPROJECT_SCROLL_H
