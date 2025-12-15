#include "nemergent.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static int write_error(char *msg){
    write(2, msg, strlen(msg));
    return (1);
}

static int start_struct(t_nem *nem, char **argv){
    nem->n_threads = atoi(argv[1]);
    nem->n_inserts = atoi(argv[2]);
    if (nem->n_threads <= 0 || nem->n_inserts <= 0)
        return (1);
    return (0);
}

int main(int argc, char **argv){
    (void) argv;
    if (argc != 3)
        return (write_error(ERROR_MSG));
    t_nem nem;
    if (start_struct(&nem, argv))
        return (write_error(ERROR_MSG));
    srand(time);
    return (0);
}