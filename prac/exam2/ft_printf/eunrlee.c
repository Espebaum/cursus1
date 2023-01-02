#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

char	*ft_itoa(long num, char *base)
{
	int	len;
	char	*str;
	int	base_len;
	long	n;

	n = num;
	base_len = ft_strlen(base);
	len = 0;
	while (n)
	{
		len++;
		n /= base_len;
	}
	str = (char *)malloc(sizeof(char) * len + 1);
	str[len] = 0;
	while (--len >= 0)
	{
		str[len] = (num % base_len) + '0';
		num /= base_len;
	}
	return (str);
}


int	print_hex(va_list ap)
{
	unsigned int	num;
	char *str;
	char *hex;

	hex = "0123456789abcdef";
	num = va_arg(ap, unsigned int);
	str = ft_itoa(num, hex);
	return (write(1, str, ft_strlen(str)));
}

int	print_digit(va_list ap)
{
	int	num;
	char	*str;
	char	*dec;
	int		ret;

	dec = "0123456789";
	num = va_arg(ap, int);
	str = ft_itoa(num, dec);
	ret = write(1, str, ft_strlen(str));
	free(str);
	return (ret);
}

int	print_str(va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (!str)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}

int	print_type(va_list ap, char c)
{
	if (c == 's')
		return(print_str(ap));
	else if (c == 'd')
		return(print_digit(ap));
	else if (c == 'x')
		return(print_hex(ap));
	return (0);
}

int	ft_print(va_list ap, const char *format)
{
	int	ret;

	ret = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ret += print_type(ap, *format);
		}
		else
			ret += write(1, format, 1);
		format++;
	}
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int	ret;

	va_start(ap, format);
	ret = ft_print(ap, format);
	va_end(ap);
	return (ret);
}

int	main()
{
	ft_printf("%d", 123);
}
