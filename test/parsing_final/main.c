
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "parsing.h"

int main( int argc, char** argv )
{
    // leggi il file di input
    struct config_file_t cf;
    int retval = parse_config_file( &cf );
    if( retval < 0 )
    {
        printf( "ERROR retval[%d]\n", retval );
        return 0;
    }
    else printf( "SUCCESS\n" );

    // stampa il config file per verifica
    print_config_file( &cf );

    return 0;
}