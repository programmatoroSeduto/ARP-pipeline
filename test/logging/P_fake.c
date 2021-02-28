#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "Lcmds.h"

// scrivi a L una serie di eventi
int main()
{
    // apri la pipe in scrittura
    int out_fd = open( "./fifopipe", O_WRONLY );
    if( out_fd < 0 )
    {
        printf( "(code %d) ", errno ); fflush( stdout ); perror( "ERRORE impossibile aprire il file FIFO in lettura" );
        exit(EXIT_FAILURE);
    }

    // comando da inviare
    struct Lproc_message_t cmd;
    cmd.event_type = L_EVENT_E1;
    cmd.from = L_FROM_G;
    cmd.value = 0.68f;

    // scrivi a quella faccia di ...
    if( write( out_fd, &cmd, sizeof( cmd ) ) < 0 )
    {
        close( out_fd );
        printf( "(code %d) ", errno ); fflush( stdout ); perror( "ERRORE impossibile aprire il file FIFO in lettura" );
        exit(EXIT_FAILURE);
    }

    // prova evento E2
    cmd.event_type = L_EVENT_E2;
    cmd.from = L_VOID;
    cmd.value = -2.556486486;

    // invia...
    if( write( out_fd, &cmd, sizeof( cmd ) ) < 0 )
    {
        close( out_fd );
        printf( "(code %d) ", errno ); fflush( stdout ); perror( "ERRORE impossibile aprire il file FIFO in lettura" );
        exit(EXIT_FAILURE);
    }

    // invia il comando "fallo uccidili tutti"
    // struct Lproc_message_t cmd;
    cmd.event_type = L_EVENT_EXIT;
    cmd.from = L_VOID;
    cmd.value = 0.f;

    // uccidili tutti
    if( write( out_fd, &cmd, sizeof( cmd ) ) < 0 )
    {
        close( out_fd );
        printf( "(code %d) ", errno ); fflush( stdout ); perror( "ERRORE impossibile aprire il file FIFO in lettura" );
        exit(EXIT_FAILURE);
    }

    // chiudi e scappa dalla polizia
    close( out_fd );
    exit(EXIT_SUCCESS);
}