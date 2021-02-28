#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>

#define S_ON 1
#define S_OFF 0

int S_mode = S_ON;

// impostazione dei segnali da gestire
// ritorna -1 se qualcosa è andato storto
int set_signals( );

// comando START (SIGCONT)
void cmd_START( int sig );

// comando STOP (SIGUSR2)
void cmd_STOP( int sig );

// comando DUMP (SIGUSR1)
void cmd_DUMP( int sig );

int main( int argc, char** argv )
{

}

// impostazione dei segnali da gestire
// ritorna -1 se qualcosa è andato storto
int set_signals( )
{
    // SIGCONT per START

    // SIGUSR2 per STOP

    // SIGUSR1 per DUMP
}

// comando START (SIGCONT)
void cmd_START( int sig )
{
    // riattiva il processo
    S_mode = S_ON;
}

// comando STOP (SIGUSR2)
void cmd_STOP( int sig )
{
    // disattiva il processo
    S_mode = S_OFF;
}

// comando DUMP (SIGUSR1)
void cmd_DUMP( int sig )
{
    
}