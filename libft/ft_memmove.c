/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:23:55 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/26 14:19:08 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_cpy;
	char	*src_cpy;
	size_t	i;

	dst_cpy = (char *)dst;
	src_cpy = (char *)src;
	if (!len || dst == src)
		return (dst);
	if (dst_cpy < src_cpy)
	{
		i = 0;
		while (i < len)
			dst_cpy[i++] = *src_cpy++;
	}
	else
	{
		while (len > 0)
		{
			len--;
			dst_cpy[len] = src_cpy[len];
		}
	}
	return (dst);
}
