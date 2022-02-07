#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[])
{
    int i;
    int *second;
    i = 0;
    srand(2);
    while ( i++ < 20)
        printf("[%d] = %d\n",i,rand());
    return (0);
}
