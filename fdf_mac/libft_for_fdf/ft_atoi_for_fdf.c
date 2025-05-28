/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_for_fdf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:23:09 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/24 16:21:07 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft_for_fdf.h"

long	ft_atoi_for_fdf(const char *str);


long	ft_atoi_for_fdf(const char *str)
{
	long	num;
	long	sign;

	if (!str)
		return (LONG_MAX);
	num = 0;
	sign = 1;
	if (*str && (*str == '+' || *str == '-'))
	{
		if (*str++ == '-')
			sign *= -1;
	}
	if (!(*str && ('0' <= *str && *str <= '9')))
		return (LONG_MAX);
	while (*str && ('0' <= *str && *str <= '9'))
	{
		num = num * 10 + (*str++ - '0');
		if ((sign > 0 && num > INT_MAX) || (sign < 0 && num > -(long)INT_MIN))
			return (LONG_MAX);
	}
	if (*str)
		return (LONG_MAX);
	return (sign * num);
}


