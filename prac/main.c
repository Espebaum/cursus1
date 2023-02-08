#include <stdio.h>
#include <string.h>

int	main()
{
	char		*line = "<<ab<<<<lk<<<j << a <<bv";
	const int	len = strlen(line);
	int			cnt;
	int			i;

	i = -1;
	cnt = 0;
	while (++i < len - 1)
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			cnt++;
			i++;
		}	
	}
	printf("cnt : %d\n", cnt);
	return (0);
}
