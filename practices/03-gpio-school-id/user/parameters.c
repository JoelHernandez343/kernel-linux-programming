#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "defs.h"

int open_parameter(char *path){
    int fd = open(path, O_RDWR);
    if (fd == -1){
        perror("Error opening parameter\n");
        exit(EXIT_FAILURE);
    }

    printf("Parameter descriptor is: %d\n", fd);

    return fd;
}

void read_parameter(int fd, char *parameter){
    if (read(fd, parameter, N) == -1){
        perror("Error reading parameter");
        exit(EXIT_FAILURE);
    }

    parameter[N - 1] = 0;
    printf("Parameter is: %s\n", parameter);
}

void write_parameter(int fd, char *parameter){
    int sent = write(fd, parameter, strlen(parameter) + 1);
    if (sent == -1){
        perror("Error writing on parameter");
        exit(EXIT_FAILURE);
    }
    printf("Bytes sent: %d\n", sent);
}