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
    int fd[2];
    int id;
    int arr[] = {1,2,3,4,5,6,7,8,9,9,8,7,65,66,4,2,3,1,4,5,6,7,4,3,2};
    int sizeArr;
    int sum;
    int start;
    int end;

    sizeArr = sizeof(arr) / sizeof(sizeArr);
    sum = 0;
    if (pipe(fd) < 0)
        return (1);
    id = fork();

    if ( id == 0)
    {
        start = 0;
        end = sizeArr / 2; 
    }else{
        start = sizeArr / 2;
        end =sizeArr;
    }
    while (start < end)
    {
        sum += arr[start];
        start++;
    }
    if (id == 0)
    {
        close(fd[0]);
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);
    }
    else
    {
        int total;
        close(fd[1]);
        read(fd[0], &total, sizeof(total));
        close(fd[0]); 
        sum += total;
        wait(NULL);
        printf("%d\n",sum);
    }
}
