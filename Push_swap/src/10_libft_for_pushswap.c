/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_libft_for_pushswap.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:41:27 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/21 12:41:28 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_puterr(void)
{
	write(2, "Error\n", 6);
	return (1);
}

long	ft_min(long a, long b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

long	ft_max(long a, long b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

long	ft_abs(long num)
{
	if (num < 0)
		num *= -1;
	return (num);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
