/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:23:22 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/23 17:02:20 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft_for_fdf.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;

	if (!s)
		return ;
	c = (unsigned char *)s;
	while (n)
	{
		*c++ = '\0';
		n--;
	}
}
