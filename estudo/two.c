#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

int main()
{
    int p1[2];  //Child => Parent (Child writes in the p1[1] and Parent reads in the p1 [0])
    int p2[2]; // Parent => Child  (Parent writes in the p2[1] and Child reads in the p2 [0])
    int id;

    if (pipe(p1) == -1 || pipe(p2) == -1)
        return (1);
    id = fork();
    if (id == -1)
        return (2);
    if (id == 0)
    {
        close(p1[0]);
        close(p2[1]);
        int x;
        read (p2[0], &x, sizeof(x));
        printf("Receveid in the child : %d\n",x);
        x*=4;
        write (p1[1], &x, sizeof(x));
        printf("Wrote for child : %d\n",x);
        close(p1[1]);
        close(p2[0]);
    }else
    {
        close(p1[1]);
        close(p2[0]);
        srand(time(NULL));
        int y = rand() % 10;
        int s;
        write(p2[1], &y, sizeof(y));
       // printf("Wrote for parent %d\n", y);
        read (p1[0], &y, sizeof(y));
        printf("Result in the parent %d\n",y);
        close(p1[0]);
        close(p2[1]);
    }
    

}