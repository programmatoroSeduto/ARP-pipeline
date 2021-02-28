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

// inizializzazione della lista
int loglist_init( loglist_t* list );

#endif