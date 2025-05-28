/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_int_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:13:48 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 21:16:10 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft_for_fdf.h"

void	ft_init_int_buffer(int *buffer, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		buffer[i] = INT_MIN;
	return ;
}
