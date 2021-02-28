
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "Lcmds.h"
#include "loglist.h"

#define LENGHT_LIST 2

void print_msg( struct Lproc_message_t* msg );

int main()
{
    int returnval = 0;
    
    // inizializzazione della lista
    loglist_t log;
    loglist_init( &log );

    // aggiungi il primo elemento della lista
    printf( "creazione di una lista di %d elementi...\n", LENGHT_LIST );
    for( int i=0; i<LENGHT_LIST; i++ )
    {
        struct Lproc_message_t msg;
        msg.value = i + ((float)i)*0.1f;
        msg.from = i;
        msg.event_type = i;
        returnval = loglist_add( &log, &msg );
        printf( "aggiunto msg%d alla lista ... ritornato %d\n", i, returnval );
        if( returnval < 0 )
        {
            fflush( stdout );
            perror( "ERRORE in add() 1" );
            return -1;
        }
    }

    // scorrimento dei primi 2 elementi e stampa a video
    printf( "stampa della lista intera...\n" );
    for( int u=0; u<LENGHT_LIST; u++ )
    {
        printf( "indice %d\n", u );
        struct Lproc_message_t* msg = loglist_get( &log );
        if( msg == NULL )
        {
            printf( "ERRORE! get() ha ritornato NULL...\n" );
            return -1;
        }
        print_msg( msg );
        returnval = loglist_next( &log );
        printf( "next() ha ritornato %d\n", returnval );
    }

    // torna indietro e ristampa la lista
    printf( "================ UN ALTRO GIRO, PAPA' ================\n" );
    returnval = loglist_goto_start( &log );
    if( returnval < 0 )
    {
        printf( "ERRORE! papà ha detto no\n" );
        return -1;
    }
    printf( "================ UN ALTRO GIRO, PAPA' ================\n" );
    printf( "(ri)stampa della lista intera...\n" );
    printf( "stampa della lista intera...\n" );
    for( int u=0; u<LENGHT_LIST; u++ )
    {
        printf( "indice %d\n", u );
        struct Lproc_message_t* msg = loglist_get( &log );
        if( msg == NULL )
        {
            printf( "ERRORE! get() ha ritornato NULL...\n" );
            return -1;
        }
        print_msg( msg );
        returnval = loglist_next( &log );
        printf( "next() ha ritornato %d\n", returnval );
    }

    return 0;
}

void print_msg( struct Lproc_message_t* msg )
{
    printf( "LOG:\n" );
    printf( "event type: %d\n", msg->event_type );
    printf( "from: %d\n", msg->from );
    printf( "value: %f\n", msg->value );
}