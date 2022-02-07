#include "apue.h"

static void my_exit1(void)
{
    printf("first exit handler\n");
}
static void my_exit2(void)
{
    printf("second exit handler\n");
}

int main(void)
{
    if(atexit(my_exit2) != 0)
        err_sys("Can't register my _exit2");
    if(atexit(my_exit1) != 0)
        err_sys("Can't register my _exit1");
    printf("mais is done\n");
    return(0);
}