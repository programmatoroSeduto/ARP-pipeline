
// file per testare il codice in generale
// DA ELIMINARE alla fine del progetto

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define FILENAME "./testconfig.txt"
#define N_ROWS 3
#define BUF_SIZE 50

int main( int argc, char** argv )
{
    // apri il file di test da parsare
    // int fd = open( FILENAME, O_RDONLY );
    FILE* fp = fopen( FILENAME, "r" );
    if( fp == NULL )
    {
        perror( "open" );
        exit( EXIT_FAILURE );
    }

    // leggi tutte le righe del file
    char text[N_ROWS][2][BUF_SIZE];
    for( int i=0 ; i<N_ROWS; i++ )
    {
        fscanf( fp, "%s %s\n", text[i][0], text[i][1] );
        printf( "%s %s\n", text[i][0], text[i][1] );
    }

    // chiudi il file
    fclose( fp );

    exit( EXIT_SUCCESS );
}