#include "ft_printf.h"
#include "libft.h"

int	ft_putchar(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (0);
}

int		ft_putnbr_and_len(int n, int *cnt)
{
	char	c;

	if (n == -2147483648)
    {
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
        *cnt += 11;
    }
	else
	{
		if (n < 0)
		{
            (*cnt)++;
			if (ft_putchar('-') == -1)
				return (-1);
			n *= -1;
		}
		if (n >= 10)
			if (ft_putnbr_and_len(n / 10, cnt) == -1)
				return (-1);
        (*cnt)++;
		c = '0' + n % 10;
		if (ft_putchar(c) == -1)
			return (-1);
	}
	return (1);
}

int	ft_putunbr_and_len(unsigned int un, int *cnt)
{
    char	c;

    if (un >= 10)
        if (ft_putunbr_and_len(un / 10, cnt) == -1)
			return (-1);
    (*cnt)++;
    c = '0' + un % 10;
    if (ft_putchar(c) == -1)
		return (-1);
	return (0);
}

int	ft_putstr_and_len(char *s)
{
	if (s == (NULL))
    {
		if (write(1, "(null)", 6) == -1)
			return (-1);
        return (6);
    }
    if ((*s) == 0)
        return (0);
	if (write(1, s, ft_strlen(s)) == -1)
		return (-1);
    return (ft_strlen(s));
}
