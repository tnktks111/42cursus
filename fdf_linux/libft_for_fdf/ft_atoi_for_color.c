/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_for_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:13:37 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 21:18:03 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft_for_fdf.h"

static int	is_hex(const char c);
int			ft_atoi_for_color(const char *str);

static int	is_hex(const char c)
{
	if ('0' <= c && c <= '9')
		return (c - '0');
	if ('a' <= c && c <= 'f')
		return (c - 'a' + 10);
	if ('A' <= c && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int	ft_atoi_for_color(const char *str)
{
	int		color;
	int		signal;
	size_t	len;

	len = ft_strlen(str);
	if (len > 8 || len < 3 || len % 2 == 1)
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
