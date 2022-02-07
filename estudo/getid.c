#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int id = fork();
    if (id == 0)
        sleep(1);
    else
        wait(NULL);
    printf("Current ID: %d, parent ID: %d fork id: %d \n",getpid(),getppid(),id);
    return (0);
}