#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
char	*get_path_var(char **envp)
{
	while (strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int main(int argc,char *argv[], char* env[])
{
    printf("%d\n",access("/bin/ls",R_OK));
}