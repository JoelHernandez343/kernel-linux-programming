#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "parameters.h"

int main(int argc, char *argv[]){

    if (argc < 2){
        printf("You must enter the id number.\n");
        return -1;
    }

    if (strlen(argv[1]) != 10){
        printf("Enter only 10 digits between 0-9\n");
        return -1;
    }

    for (int i = 0; argv[1][i] != 0; ++i){
        char c = argv[1][i];

        if (c < '0' || c > '9'){
            printf("Enter only digits between 0-10\n");
            return -1;
        }
    }

    printf("Number to send: %s\n", argv[1]);
    
    int fd = open_parameter("/sys/module/gpio_id/parameters/school_id");

    write_parameter(fd, argv[1]);

    close(fd);
    return 0;
}