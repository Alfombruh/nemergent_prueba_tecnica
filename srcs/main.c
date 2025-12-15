#include "nemergent.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

static int rng(void){
    int sign = rand() % 2? 1 : -1;
    int base = rand();
    return (base * sign);
}

static void *insert_numbers(void *arg){
    t_nem *nem = (t_nem *)arg;
    unsigned int    i  = 0;
    while (i++ < nem->n_inserts){
        pthread_mutex_lock(&nem->mutex_rng);
        int random_number = rng();
        pthread_mutex_unlock(&nem->mutex_rng);
        if (random_number <= 0){
            pthread_mutex_lock(&nem->mutex_a);
            llist_add(&nem->list_a, random_number);
            pthread_mutex_unlock(&nem->mutex_a);
            continue;
        }else{
            pthread_mutex_lock(&nem->mutex_b);
            llist_add(&nem->list_b, random_number);
            pthread_mutex_unlock(&nem->mutex_b);
        }
    }
    return NULL;
}

static int  launch_threads(t_nem *nem){
    unsigned int    i = 0;
    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * nem->n_threads);
    if (!threads)
        return (1);
    while (i < nem->n_threads){
        if (pthread_create(&threads[i++], NULL, insert_numbers, nem)){
            free(threads);
            return (1);
        }
    }
    i = 0;
    while (i < nem->n_threads){
        if (pthread_join(threads[i], NULL)){
            free(threads);
            return (1);
        }
    }
    free(threads);
    return (0);
}

static int write_error(char *msg){
    write(2, msg, strlen(msg));
    return (1);
}

static void print_llists(t_nem *nem){
    unsigned int    size_a = llist_size(nem->list_a);
    unsigned int    size_b = llist_size(nem->list_b);
    unsigned int    real_size = nem->n_inserts * nem->n_threads;
    printf("list A:\n");
    llist_print(nem->list_a);
    printf("\n\nlist B:\n");
    llist_print(nem->list_b);
    printf("Size Check!\nLIST_A SIZE = %d\nLIST_B SIZE = %d\n", size_a, size_b);
    printf("Total size is: %d and was supossed to be %d\n", size_a + size_b, real_size);
}

static void free_struct(t_nem *nem){
    pthread_mutex_destroy(&nem->mutex_a);
    pthread_mutex_destroy(&nem->mutex_b);
    pthread_mutex_destroy(&nem->mutex_rng);
    llist_free(&nem->list_a);
    llist_free(&nem->list_b);
}

static int start_struct(t_nem *nem, char **argv){
    nem->n_threads = atoi(argv[1]);
    nem->n_inserts = atoi(argv[2]);
    nem->list_a = NULL;
    nem->list_b = NULL;
    if (nem->n_threads <= 0 || nem->n_inserts <= 0)
        return (1);
    pthread_mutex_init(&nem->mutex_a, NULL);
    pthread_mutex_init(&nem->mutex_b, NULL);
    pthread_mutex_init(&nem->mutex_rng, NULL);
    return (0);
}

int main(int argc, char **argv){
    if (argc != 3)
        return (write_error(ERROR_MSG));
    t_nem   nem;
    if (start_struct(&nem, argv))
        return (write_error(ERROR_MSG));
    srand(time(NULL));
    launch_threads(&nem);
    print_llists(&nem);
    free_struct(&nem);
    return (0);
}