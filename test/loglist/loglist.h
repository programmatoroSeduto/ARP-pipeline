#ifndef __LOGLIST_H_
#define __LOGLIST_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "Lcmds.h"

// l'elemento della lista
typedef struct node
{
    struct node*            next;
    struct Lproc_message_t  elem;
}
__loglist_node;

// l'elemento di partenza
typedef struct 
{
    __loglist_node*         first;
    __loglist_node*         last;
    __loglist_node*         actual;
    int                     lenght;
}
loglist_t;

// aggiungi un elemento alla lista (nessuno spostamento del cursore)
int loglist_init( loglist_t* list );

// aggiungi un elemento alla lista
int loglist_add( loglist_t* list, struct Lproc_message_t* elem );

// scorri il puntatore una posizione avanti
int loglist_next( loglist_t* list );

// puntatore all'inizio della lista
int loglist_goto_start( loglist_t* list );

// ritorna il puntatore all'elemento attuale
struct Lproc_message_t* loglist_get( loglist_t* list );

#endif