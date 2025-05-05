/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:34:05 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/05 12:34:06 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_print_addr(void *ptr, int *cnt)
{
	char			*hex;
	char			buffer[16];
	unsigned long	addr;
	int				i;

	if (!ptr)
		return (-2);
	hex = "0123456789abcdef";
	addr = (unsigned long)ptr;
	i = 15;
	while (i >= 0)
	{
		buffer[i--] = hex[addr % 16];
		addr /= 16;
	}
	i = 0;
	while (buffer[i] == '0' && i++ < 15)
		;
	*cnt += (18 - i);
	if (write(1, "0x", 2) == -1 || write(1, &buffer[i], 16 - i) == -1)
		return (-1);
	return (0);
}

int	ft_print_hex(unsigned int un, int islower, int *cnt)
{
	char	c;

	if (un > 15)
		if (ft_print_hex(un / 16, islower, cnt) == -1)
			return (-1);
	if (islower)
		c = "0123456789abcdef"[un % 16];
	else
		c = "0123456789ABCDEF"[un % 16];
	(*cnt)++;
	if (ft_putchar(c) == -1)
		return (-1);
	return (0);
}

int	f_ptr_parser(char format, void *arg)
{
	int	cnt;
	int	n;

	cnt = 0;
	if (format == 's')
	{
		n = ft_putstr_and_len((char *)arg);
		if (n == -1)
			return (-1);
		cnt += n;
	}
	else if (format == 'p')
	{
		n = ft_print_addr(arg, &cnt);
		if (n == -2)
		{
			if (write(1, "(nil)", 5) == -1)
				return (-1);
			cnt += 5;
		}
		if (n == -1)
			return (-1);
	}
	return (cnt);
}

int	f_int_parser(char format, int arg)
{
	int	cnt;

	cnt = 0;
	if (format == 'c')
	{
		if (ft_putchar((char)arg) == -1)
			return (-1);
		cnt++;
	}
	else if (format == 'u')
	{
		if (ft_putunbr_and_len((unsigned int)arg, &cnt) == -1)
			return (-1);
	}
	else if (format == 'x' || format == 'X')
	{
		if (ft_print_hex((unsigned int)arg, (format == 'x'), &cnt) == -1)
			return (-1);
	}
	else
	{
		if (ft_putnbr_and_len(arg, &cnt) == -1)
			return (-1);
	}
	return (cnt);
}
