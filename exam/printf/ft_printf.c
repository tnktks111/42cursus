#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

void ft_putchar(char c)
{
    write(STDOUT_FILENO, &c, 1);
}

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int ft_putstr(char *s)
{
    int len = ft_strlen(s);
    write(STDOUT_FILENO, s, len);
    return (len);
}

int ft_putnbr(int n)
{
    char c;
    int cnt = 0;
    if (n == -2147483648)
        return (ft_putstr("-2147483648"));
    if (n < 0)
    {
        ft_putchar('-');
        n *= -1;
        cnt++;
    }
    if (n >= 10)
        cnt += ft_putnbr(n / 10);
    c = n % 10 + '0';
    ft_putchar(c);
    cnt++;
    return (cnt);
}

int ft_puthex(unsigned int n)
{
    static const char hex[17] = "0123456789abcdef";
    int cnt = 0;

    if (n > 15)
        cnt += ft_puthex(n / 16);
    ft_putchar(hex[n % 16]);
    cnt++;
    return (cnt);
}

int format_parser(va_list args, char format)
{
    if (format == 's')
        return (ft_putstr(va_arg(args, char*)));
    else if (format == 'd')
        return (ft_putnbr(va_arg(args, int)));
    else if (format == 'x')
        return (ft_puthex(va_arg(args, unsigned int)));
    return (EXIT_FAILURE);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		cnt;
	int		add;

	va_start(args, format);
	cnt = 0;
	while (*format)
	{
		if (*format == '%')
		{
			add = format_parser(args, *(++format));
			if (add == -1)
				return (-1);
			cnt += add;
			format++;
		}
		else
		{
			ft_putchar(*format++);
			cnt++;
		}
	}
	va_end(args);
	return (cnt);
}

#include <stdio.h>
int main()
{
    int res[6];
    res[0] = ft_printf("%s\n", "toto");
    res[1] = ft_printf("Magic %s is %d\n", "number", 42);
    res[2] = ft_printf("Hexadecimal for %d is %x\n", 42, 42);
    for (int i = 0; i < 3; i++)
        ft_printf("%d", res[i]);
    res[3] = printf("%s\n", "toto");
    res[4] = printf("Magic %s is %d\n", "number", 42);
    res[5] = printf("Hexadecimal for %d is %x\n", 42, 42);
    for (int i = 0; i < 3; i++)
        printf("%d", res[i]);
    return (0);
}