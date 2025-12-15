#ifndef NEMERGENT_H
#define NEMERGENT_H

#define ERROR_MSG "ERROR!\nEl modo de uso es:\n./nemergent \"numero de hilos\" \"numeros por hilo\"\n"

typedef struct s_llist{
    int number;
    struct s_llist *next;
} t_llist;

typedef struct s_nem{
    unsigned int n_threads;
    unsigned int n_inserts;
    t_llist *list_a;
    t_llist *list_b;
} t_nem;

#endif