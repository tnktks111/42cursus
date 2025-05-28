/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:13:56 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 21:14:59 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft_for_fdf.h"

int		ft_max(int x, int y);
int		ft_min(int x, int y);
int		ft_abs(int x);
void	ft_swap(int *x, int *y);
void	ft_uint_swap(uint32_t *x, uint32_t *y);

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

int	ft_min(int x, int y)
{
	if (x < y)
		return (x);
	else
		return (y);
}

int	ft_abs(int x)
{
	if (x < 0)
		x *= -1;
	return (x);
}

void	ft_swap(int *x, int *y)
{
	int	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void	ft_uint_swap(uint32_t *x, uint32_t *y)
{
	uint32_t	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}
