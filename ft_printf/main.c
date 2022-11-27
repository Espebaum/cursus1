#include "libft/libft.h"
#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	int	num = 1;
	int	*a = &num;
	char	*b = "bus";


	printf("%p\n", a);
	ft_printf("%p\n", a);
	ft_printf("ab%s\n", b);
	ft_printf("ab%s", b);
	printf("\n");
	printf("%d", num + (int) write(1, "AB", 2));
	return 0;
}
