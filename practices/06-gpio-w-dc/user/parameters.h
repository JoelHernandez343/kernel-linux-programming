#ifndef PARAMETERS_H
#define PARAMETERS_H

int open_parameter(char *path);
void read_parameter(int fd, char *parameter);
void write_parameter(int fd, char *parameter);
void write_n_close(char *parameter, char *value);

#endif