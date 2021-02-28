
#include "loglist.h"

// inizializzazione della lista
int loglist_init( loglist_t* list )
{
    // il parametro in ingresso deve essere dato...
    if( list == NULL ) return -1;

    // inizializzazione della lista
    list->first = NULL;
    list->last = NULL;
    list->actual = NULL;
    list->lenght = 0;
}

// aggiungi un elemento alla lista (nessuno spostamento del cursore)
int loglist_add( loglist_t* list, struct Lproc_message_t* elem )
{
    // allocazione del nuovo contenitore, se possibile
    __loglist_node* newnode = ( __loglist_node* ) malloc( sizeof( __loglist_node ) );
    if( newnode == NULL )
    {
        // allocazione fallita!
        return -1;
    }

    // riempimento del nodo appena creato
    newnode->elem = *elem;
    newnode->next = NULL;

    // inserimento del nodo nella lista
    if( list->lenght == 0 )
    {
        //inserimento all'inizio
        list->first = newnode;

        // il nuovo nodo deve diventare anche quello attuale, per evitare strani crash
        list->actual = newnode;
    }
    else
    {
        // inserimento in coda
        list->last->next = newnode;
    }

    // il nuovo nodo inserito va comunque in fondo alla lista
    list->last = newnode;

    // la lunghezza della lista aumenta
    list->lenght ++;

    return 0;
}

// scorri il puntatore una posizione avanti
int loglist_next( loglist_t* list )
{
    // se la lista è vuota, niente da fare
    if( list->lenght == 0 ) return -1;

    // se siamo in fondo alla lista, inutile
    if( list->actual == list->last ) return -2;

    // altrimenti, scorri
    list->actual = list->actual->next;

    return 0;
}

// puntatore all'inizio della lista
int loglist_goto_start( loglist_t* list )
{
    // se la lista è vuota, niente da fare
    if( list->lenght == 0 ) return -1;

    // altrimenti, muovi al primo elemento
    list->actual = list->first;

    return 0;
}

// ritorna il puntatore all'elemento attuale
struct Lproc_message_t* loglist_get( loglist_t* list )
{
    // ritorna null se la lista non contiene elementi
    if( list->lenght == 0 ) return NULL;

    // altrimenti ritorna il contenuto del nodo attuale
    return &list->actual->elem;
}