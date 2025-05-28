/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_double2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:15:29 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 21:17:47 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft_for_fdf.h"

int		ipart(double x);
double	fpart(double x);
double	rfpart(double x);

int	ipart(double x)
{
	return (floor(x));
}

double	fpart(double x)
{
	return (x - ipart(x));
}

double	rfpart(double x)
{
	return (1 - fpart(x));
}
