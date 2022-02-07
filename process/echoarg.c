#include "apue.h"
int p;
static int  s;
char r;
int main(int argc, char *argv[], char *envp[])
{
    int i;
    static int j = 19;
    const int pi = 3.14;

    // for (i = 0; i < argc; i++)
    //     printf("argv[%d]: %s\n", i, argv[i]);
    for (i = 0; envp[i] != NULL; i++)
        printf("envp[%d]: %s\n", i, envp[i]);
    exit(0);
}