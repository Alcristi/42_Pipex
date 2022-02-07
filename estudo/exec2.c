#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[], char *env[])
{
    char *newargv[] = {"/usr/bin/ls",NULL};
    char *newenviron[] = {NULL};

    if ( argc != 2){
        fprintf(stderr, "Usage: %s <file-to-exec> \n",argv[0]);
    }
    //newargv[0] = argv[1];
    execve("/usr/bin/ls",newargv,env);
    perror("execve");
    exit(EXIT_FAILURE);
} 