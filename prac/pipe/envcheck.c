#include <stdio.h>

int main(int argc, char **envp)
{
    int i ;

	(void) argc;
    i = 0;
    while (i < 32)
    {
        printf("<%d> %s\n", i, envp[i]);
        i++;
    }
	return 0;
}
