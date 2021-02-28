#ifndef __L_CMDS__
#define __L_CMDS__ 5

// per indicare che un campo è vuoto
#define L_VOID -1

// evento E1: stampa
// <from G/S> <value>
#define L_EVENT_E1 1
#define L_FROM_G 0
#define L_FROM_S 1

// evento E2: stampa
// <value>
#define L_EVENT_E2 2

// evento E3: dump su consolle
#define L_EVENT_DUMP 3

// evento EXIT: termina il processo L
#define L_EVENT_EXIT 0

// il messaggio da scambiare con L
struct Lproc_message_t
{
    int event_type;     // l'evento che si vuole stampare su log
    int from;           // da chi arriva l'evento; L_VOID se non utile
    float value;        // il valore da stampare; L_VOID se non usato
};

#endif