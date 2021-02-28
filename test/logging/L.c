
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "Lcmds.h"

// ciclo di funzionamento del processo L
void Lproc_body( int in, int out );

// scrivi qualcosa su output
int Lproc_log_write( int log_out, char* msg, int msg_size );

// evento E1
int Lproc_event_E1( int log_out, int from, float value );

// evento E2
int Lproc_event_E2( int log_out, float value );

// evento DUMP (TODO)
// int Lproc_dump(  )

// servizio di logging come processo separato
// AVVIO DEL PROGRAMMA:
//      L <log_path> <FIFO_input_file>
int main( int argc, char** argv )
{
    // passaggio di comandi da shell
    if( argc < 3 )
    {
        printf( "ERORRE passati meno argomenti di quelli che servono\n" );
        printf( "COME USARE QUESTO PROGRAMMA:\n" );
        printf( "$%s %s %s\n", argv[0], "<log_path>", "<FIFO_input>" );

        exit(EXIT_FAILURE);
    }

    const char* log_path = argv[1];
    const char* FIFO_input = argv[2];

    // apri il file FIFO se possibile
    int fd_in = open( FIFO_input, O_RDONLY );
    if( fd_in < 0 )
    {
        printf( "(code %d) ", errno ); fflush( stdout ); perror( "ERRORE impossibile aprire il file FIFO in lettura" );
        exit(EXIT_FAILURE);
    }

    // crea il file di log
    int fd_out = creat( log_path, 0770 );
    if( fd_in < 0 )
    {
        close( fd_in );
        printf( "(code %d) ", errno ); fflush( stdout ); perror( "ERRORE impossibile aprire il file log di output" );
        exit(EXIT_FAILURE);
    }

    // ciclo di funzionamento del programma
    Lproc_body( fd_in, fd_out );

    // chiudi il file di log
    close( fd_out );

    // chiudi il file FIFO
    close( fd_in );

    exit( EXIT_SUCCESS );
}



// ciclo di funzionamento del processo L
void Lproc_body( int in, int out )
{
    // il messaggio da ricevere da P
    struct Lproc_message_t lmsg;
    int rval = -1;
    
    // ciclo di funzionamento
    while( 1 )
    {
        // reset del messaggio, per sicurezza
        lmsg.event_type = L_EVENT_EXIT;
        lmsg.from = L_VOID;
        lmsg.value = 0.f;

        // attesa del nuovo messaggio dal fd in
        rval = read( in, &lmsg, sizeof( struct Lproc_message_t ) );
        if( rval < 0 )
        {
            printf( "(code %d) ", errno ); fflush( stdout ); perror( "ERRORE impossibile leggere da FIFO" );
            break;
        }

        // interpretazione del messaggio in base al comando
        switch( lmsg.event_type )
        {
        case L_EVENT_EXIT:
            return;

        case L_EVENT_E1:
            // stampa per evento di tipo E1
            Lproc_event_E1( out, lmsg.from, lmsg.value );
        break;

        case L_EVENT_E2:
            // stampa per evento di tipo E2
            Lproc_event_E2( out, lmsg.value );
        break;

        case L_EVENT_DUMP:
            // dump (TODO)
            printf( "dump!\n" );
        break;

        default:
            printf( "ERRORE comando non valido!\n" );
            return;
        }
    }

    // COMANDO L_EVENT_EXIT oppure errore
    // chiudi il processo L
    return;
}



// scrivi qualcosa su output; ritorna -1 se qualcosa non va, 0 altrimenti
int Lproc_log_write( int log_out, char* msg, int msg_size )
{
    if( write( log_out, msg, msg_size ) < 0 )
    {
        // usa la perror() e errno per capire cosa è andato storto
        return -1;
    }

    // tutto è andato per ilverso giusto
    return 0;
}



// evento E1
int Lproc_event_E1( int log_out, int from, float value )
{
    struct timeval now;
    gettimeofday( &now, NULL );

    char str[50];
    sprintf( str, "[%ld, %ld] %s %f\n", now.tv_sec, now.tv_usec, ( from == L_FROM_G ? "from G" : "from S" ), value );
    int msg_size = strlen( str );

    return Lproc_log_write( log_out, str, msg_size );
}

// evento E2
int Lproc_event_E2( int log_out, float value )
{
    struct timeval now;
    gettimeofday( &now, NULL );

    char str[50];
    sprintf( str, "[%ld, %ld] %f\n", now.tv_sec, now.tv_usec, value );
    int msg_size = strlen( str );

    return Lproc_log_write( log_out, str, msg_size );
}