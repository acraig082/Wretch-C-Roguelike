#include "rogue.h"
#include <stdlib.h>

Item * newScroll(char *scrollName, char *contents, int idNum, int used, char symbol, int effect){
    Scroll *s = malloc(sizeof(Scroll));
    s->base.itemName = scrollName;
    s->base.description = contents;
    s->base.itemID = idNum;
    s->base.sym = symbol;
    s->base.pickedUp = FALSE;
    s->used = used;
    s->effect = effect;
    return(Item *)s;
}

Scroll * emptyScroll(){
    return (Scroll *)newScroll("Empty", " ", -1, FALSE, '?', -1);
}