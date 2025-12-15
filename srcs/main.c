#include "nemergent.h"
#include <unistd.h>
#include <string.h>

static int write_error(char *msg){
    write(2, msg, strlen(msg));
    return (1);
}

int main(int argc, char **argv){
    (void) argv;
    if (argc != 3)
        return (write_error(ERROR_MSG));
    return (0);
}