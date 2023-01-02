#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

size_t ft_strlen(char *str)
{
	int	cnt;

	cnt = 0;
	while (*str++)
		cnt++;
	return (cnt);
}

char	*ft_itoa(long vatemp, char *base)
{
	int		len;
	long	temp;
	size_t	base_len;
	char	*str;

	base_len = ft_strlen(base);
	len = 0;
	if (vatemp <= 0)
		len++;
	temp = vatemp;
	while (temp)
	{
		len++;
		temp /= base_len;
	}
	str = (char *)malloc(sizeof(char) * len + 1);
	str[len] = '\0';
	str[0] = '-';
	if (vatemp == 0)
		str[0] = '0';
	while (vatemp)
	{
		str[--len] = base[vatemp % base_len];
		vatemp /= base_len;
	}
	return (str);
}

int	ft_print_d(va_list **ap)
{
	int		vatemp;
	char	*str;
	int		print_size;
	char	*dec_base;

	dec_base = "0123456789";
	print_size = 0;
	vatemp = va_arg(**ap, int);
	str = ft_itoa(vatemp, dec_base);
	print_size = write(1, str, ft_strlen(str));
	free(str);
	return (print_size);
}

int	ft_print_s(va_list **ap)
{
	char	*vatemp;
	int		print_size;

	vatemp = va_arg(**ap, char *);
	if (vatemp == NULL)
		vatemp = "(null)";
	print_size = write(1, vatemp, ft_strlen(vatemp));
	return (print_size);
}

int	ft_print_sx(va_list **ap)
{
	unsigned int	vatemp;
	int				print_size;
	char			*str;
	char			*hex_base;

	hex_base = "0123456789abcdef";
	vatemp = va_arg(**ap, unsigned int);
	str = ft_itoa(vatemp, hex_base);
	print_size = write(1, str, ft_strlen(str));
	free(str);
	return (print_size);
}

int	print_va(const char *str, va_list *ap)
{
	int		print_size;

	print_size = 0;
	if (str[1] == 'd')
		print_size = ft_print_d(&ap);
	else if (str[1] == 's')
		print_size = ft_print_s(&ap);
	else if (str[1] == 'x')
		print_size = ft_print_sx(&ap);
	return (print_size);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		print_size;

	i = 0;
	print_size = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] != '%')
			print_size += write(1, &str[i], 1);
		else
			print_size += print_va(&str[i++], &ap);
		i++;
	}
	va_end(ap);
	return (print_size);
}

int	main(void)
{
	ft_printf("%d\n", 12);
	ft_printf("%s\n", "abcd");
	ft_printf("%s\n", NULL);
	ft_printf("%x\n", -1);

	return (0);
}
