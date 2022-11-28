#include "libft/libft.h"
#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
	printf("%ld\n", write(1, "\001\002\007\v\010\f\r\n", 8));
	printf("%d\n", printf("\001\002\007\v\010\f\r\n"));
	ft_printf("%d\n", ft_printf("\001\002\007\v\010\f\r\n"));
	printf("\001\002\007\v\010\f\r\n");

	printf("%p\n", -1);
	ft_printf("%p", (void *) -1);
	return 0;
}
