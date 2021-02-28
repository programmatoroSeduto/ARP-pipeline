#include "parsing.h"

// funzione "main" per il parsing del file
int parse_config_file( struct config_file_t* cf )
{
    // apertura del file
    FILE* configfile = fopen( CONFIG_FILE_PATH, "r" );
    if( configfile == NULL )
    {
        // lettura andata male per qualche ragione
        return PARSING_ERR_INVALID_OPEN;
    }

    // caricamento del file
    char content[N_ROW][2][BUF_SIZE];
    int i = 0;
    int returnval = 0;
    while( returnval != EOF )
    {
        returnval = fscanf( configfile, "%s %s\n", content[i][0], content[i][1] );
        i++;
    }
    if( i < N_ROW )
    {
        // c'è stato un errore durante la lettura
        return PARSING_ERR_INVALID_FORMAT;
    }

    //for( int j=0; j<N_ROW; j++ )
        //printf( "%s %s\n", content[j][0], content[j][1] );

    // my_IP
    strcpy( cf->my_IP, content[MY_IP][1] );
    
    // my portno
    cf->my_portno = atoi( content[MY_PORTNO][1] );
    
    // next IP
    strcpy( cf->next_IP, content[NEXT_IP][1] );
    
    // next portno
    cf->next_portno = atoi( content[NEXT_PORTNO][1] );
    
    // RF_value
    cf->RF_value = atof( content[RF_VALUE][1] );
    
    // waiting time
    cf->waiting_time = atoi( content[WAITING_TIME][1] );
    
    // log path
    strcpy( cf->log_path, content[LOG_PATH][1] );
    
    // chiudi lo stream
    fclose( configfile );

    return 0;
}


// DEBUG stampa a video i dati della struttura
void print_config_file( struct config_file_t* cf )
{
    printf( "MY_IP:%s\n", cf->my_IP );
    printf( "MY_PORTNO:%d\n", cf->my_portno );
    printf( "NEXT_IP:%s\n", cf->next_IP );
    printf( "NEXT_PORTNO:%d\n", cf->next_portno );
    printf( "RF_VALUE:%f\n", cf->RF_value );
    printf( "WAITING_TIME:%ld\n", cf->waiting_time );
    printf( "LOG_PATH:%s\n", cf->log_path );
}