/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:23:46 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/26 14:19:53 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	c_cpy;

	p = (unsigned char *)s;
	c_cpy = (unsigned char)c;
	while (*p != c_cpy && n)
	{
		p++;
		n--;
	}
	if (n == 0)
		return (NULL);
	return ((void *)(p));
}
