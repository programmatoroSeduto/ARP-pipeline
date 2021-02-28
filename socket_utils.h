
// funzioni utili per aprire e chiudere socket
// NON USARE PER IL MOMENTO! serve una revisione
// dovranno essere utilizzate da G (in ingresso) e P (in uscita)

#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/select.h>

#define     ARPNET_STD_PORTNO     5080


int net_server_init( );


int net_accept_client(int sockfd, struct sockaddr_in* cli_addr);


int net_client_connection(char *IPaddr);


int net_accept_client_timeout(int sockfd, struct timeval* timeout, struct sockaddr_in* cli_addr);


int net_client_connection_timeout(char *ip_addr, struct timeval* timeout);

#endif