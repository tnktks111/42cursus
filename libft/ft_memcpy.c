/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:23:53 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/26 14:19:37 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*p1;
	const char	*p2 = (const char *)src;

	p1 = (char *)dest;
	while (n)
	{
		*p1++ = *p2++;
		n--;
	}
	return (dest);
}
