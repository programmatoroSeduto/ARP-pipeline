#ifndef __PARSING__
#define __PARSING__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

// dimensioni del buffer di lettura
#define BUF_SIZE 50

// il numero di righe nel file
#define N_ROW 7

// errori comuni
#define PARSING_ERR_INVALID_OPEN -1
#define PARSING_ERR_INVALID_FORMAT -2

// percorso del file
//define CONFIG_FILE_PATH "./config/config.txt"
#define CONFIG_FILE_PATH "./config.txt"

// le chiavi, nell'ordine
#define MY_IP 0
#define MY_PORTNO 1
#define NEXT_IP 2
#define NEXT_PORTNO 3
#define RF_VALUE 4
#define WAITING_TIME 5
#define LOG_PATH 6

// rappresentazione del file
struct config_file_t
{
    char my_IP[15];
    int my_portno;
    char next_IP[15];
    int next_portno;
    float RF_value;
    long waiting_time;
    char log_path[BUF_SIZE];
};

// funzione "main" per il parsing del file
int parse_config_file( struct config_file_t* cf );

// DEBUG stampa a video i dati della struttura
void print_config_file( struct config_file_t* cf );

#endif