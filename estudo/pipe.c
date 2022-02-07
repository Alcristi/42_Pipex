#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "./gnl/get_next_line.h"

int main(int argc, char **argv)
{
    int id;
    int fd[2];

    if (pipe(fd) < -1)
    {
        printf("An error ocurred with opening the pipe\n");
        return (1);
    }
    id = fork();
    if (id == 0)
    {
        close(fd[0]);
        int x;
        printf("Input: ");
        scanf("%d",&x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    }else{
        close(fd[1]);
        int y;
        read(fd[0], &y, sizeof(int));
        close(fd[0]);
        printf("Got from child process %d\n",y);
    }

}
