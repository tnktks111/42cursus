#include "fdf.h"

static int is_hex(const char c);
int ft_atoi_for_color(const char *str);

static int is_hex(const char c)
{
	if ('0' <= c && c <= '9')
		return (c - '0');
	if ('a' <= c && c <= 'f')
		return (c - 'a' + 10);
	if ('A' <= c && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int ft_atoi_for_color(const char *str)
{
	int color;
    int signal;

	if (ft_strlen(str) > 8 || ft_strlen(str) < 3)
		return (-1);
	if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X'))
		return (-1);
	str += 2;
	color = 0;
	while (*str)
	{
        signal = is_hex(*str++);
		if (signal == -1)
			return (-1);
		color = color * 16 + signal;
	}
    return (color);
}