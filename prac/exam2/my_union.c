#include <unistd.h>

void	a_union(char *argv1, char *argv2)
{
	char	ar1[127];
	char	ar2[127];
	int	i;

	i = -1;
	while (++i < 127)
		ar1[i] = 0;
	i = -1;
	while (++i < 127)
		ar2[i] = 0;
	i = 0;
	while (argv1[i])
	{
		if (ar1[(int)argv1[i]] == 0)
		{
			write(1, &argv1[i], 1);
			ar1[(int)argv1[i]]++;
		}
		i++;
	}
	i = 0;
	while (argv2[i])
	{
		if (ar1[(int)argv1[i]] == 0 && ar2[(int)argv2[i]] == 0)
		{
			write(1, &argv2[i], 1);
			ar2[(int)argv2[i]]++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
		return write(1, "\n", 1);
	a_union(argv[1], argv[2]);
	return (0);
}
