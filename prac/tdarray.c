#include <stdio.h>
#include <stdlib.h>

void	freeall(char **spl, int height)
{
	int		i = 0;
	
	while (i < height)
		free(spl[i++]);
	free(spl);
}

int	main(void)
{
	int		height = 3, width = 3;
	char	**spl, **save;
	int		i = 0;

	spl = (char **) malloc(sizeof(char *) * height);
	while (i < height)
		spl[i++] = (char *)malloc(sizeof(char) * width);
	spl[0][0] = '1'; spl[0][1] = '9'; spl[0][2] = '\0';
	spl[1][0] = '3'; spl[1][1] = '7'; spl[1][2] = '\0';
	spl[2] = NULL;
	save = spl;
	printf("%c", **spl + 1);
	/** while (*spl) */
	/** { */
	/**     printf("%s", *spl); */
	/**     printf("\n"); */
	/**     spl++; */
	/** } */
	freeall(save, height);
	return 0;
}
