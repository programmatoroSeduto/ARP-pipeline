
#include "loglist.h"

// inizializzazione della lista
int loglist_init( loglist_t* list )
{
    // il parametro in ingresso deve essere dato...
    if( list == NULL ) return -1;

    // inizializzazione della lista
    list->first = NULL;
    list->last = NULL;
    list->actual = NULL;
    list->lenght = 0;
}