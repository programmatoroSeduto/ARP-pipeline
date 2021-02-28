#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>

void printmessage_SIGUSR1(int val)
{
    printf( "SIGUSR1(%d)! and %d\n", SIGUSR1, val );
}

void printmessage_SIGSTOP()
{
    printf( "SIGSTOP!\n" );
}

void printmessage_SIGCONT()
{
    printf( "SIGCONT!\n" );
}

int main( int argc, char** argv )
{
    printf( "my PID is %d\n", getpid() );
    
    printf( "listening for SIGUSR1...\n" );
    if( signal( SIGUSR1, printmessage_SIGUSR1 ) == SIG_ERR )
    {
        perror( "ERROR on signal()" );
        return -1;
    }
    printf( "listening for SIGCONT...\n" );
    if( signal( SIGCONT, printmessage_SIGCONT ) == SIG_ERR )
    {
        perror( "ERROR on signal()" );
        return -1;
    }
    printf( "listening for SIGUSR2...\n" );
    if( signal( SIGUSR2, printmessage_SIGSTOP ) == SIG_ERR )
    {
        perror( "ERROR on signal()" );
        return -1;
    }

    printf( "waiting...\n" );
    while(1) ;

    return 0;
}