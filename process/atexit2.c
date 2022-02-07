#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void bye(void)
{
    printf("THat was all, folks\n");
}

int main(void)
{
    long a;
    int i;

    a = sysconf(_SC_ATEXIT_MAX);
    

    i = atexit(bye);
    if (i != 0)
    {
        fprintf(stderr,"cannot set exit function\n");
        exit(EXIT_FAILURE);
    }
    printf("ATEXIT_MAX= %ld\n", a);
    exit(EXIT_SUCCESS);

}
