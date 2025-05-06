/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:34:08 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/05 12:34:13 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	format_parser(va_list args, char format)
{
	int	cnt;

	cnt = 0;
	if (format == '\0')
		return (-1);
	else if (format == 's' || format == 'p')
		cnt += f_ptr_parser(format, va_arg(args, void *));
	else if (format == 'c' || format == 'd' || format == 'i' || format == 'u'
		|| format == 'x' || format == 'X')
		cnt += f_int_parser(format, va_arg(args, int));
	else if (format == '%')
	{
		if (ft_putchar('%') == -1)
			return (-1);
		cnt++;
	}
	else
		return (-1);
	if (cnt == -1)
		return (-1);
	return (cnt);
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
			if (ft_putchar(*format++) == -1)
				return (-1);
			cnt++;
		}
	}
	va_end(args);
	return (cnt);
}

// //cw -I ./inc -I ./libft src/*.c
// #include <stdio.h>
// int main()
// {
//     int a = ft_printf(" %p \n", 0);
//     int b = printf(" %p \n", (void *)0);
//     printf("%d\n%d", a, b);
// }