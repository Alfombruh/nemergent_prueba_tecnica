#ifndef NEMERGENT_H
#define NEMERGENT_H

#define ERROR_MSG "ERROR!\nEl modo de uso es:\n./nemergent \"numero de hilos\" \"numeros por hilo\"\n"

#include <pthread.h>

typedef struct s_llist{
    int number;
    struct s_llist *next;
} t_llist;

t_llist *llist_new(int number);
void    llist_add(t_llist **head, int number);
void    llist_print(t_llist *head);
void    llist_free(t_llist **head);

typedef struct s_nem{
    unsigned int n_threads;
    unsigned int n_inserts;
    t_llist *list_a;
    t_llist *list_b;
    pthread_mutex_t mutex_a;
    pthread_mutex_t mutex_b;
} t_nem;

#endif