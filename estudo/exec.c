#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main (int argc, char* argv[], char *env[])
{
    int id;
    int err;
    int pp[2];
    pipe(pp);
    id = fork();
    if (id == 0)
    { 
        int file;
        close(pp[0]);
        file = open("pingResults.txt",O_WRONLY | O_CREAT, 0777);
        dup2(pp[1],1);
        close(pp[1]);
        if (file == -1)
            return (2);
        err =  execlp("ping","ping","-c","3","google.com",NULL);
        return (23);
    }
    else
    {
        // int wstatus;
        // pid_t id2;

        // id2 = wait(&wstatus);
        // wstatus = ((wstatus) & 0xff00) >> 8;
        // if (wstatus == 0)
        //     printf("Success!\n");
        // else
        //     printf("Failure with status code %d\n",wstatus);
        // printf("Some post processing goes here!\n");
        wait(NULL);
        dup2(pp[0],0);
        close (pp[0]);
        close(pp[1]);
        char *a[] = {"cat","-e",NULL};
        execve(argv[1],a,env);

    }

    return (0);
}