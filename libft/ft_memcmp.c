/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:23:50 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/26 13:23:51 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_cpy;
	unsigned char	*s2_cpy;
	size_t			i;

	s1_cpy = (unsigned char *)s1;
	s2_cpy = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1_cpy[i] == s2_cpy[i])
		i++;
	return (s1_cpy[i] - s2_cpy[i]);
}

// #include <stdio.h>
// int main()
// {
//     char s1[] = {0, 2, 4, 4};
//     char s2[] = {1, 2, 3, 4, 5};
//     printf("%d", ft_memcmp(s1, s2, 3));
// }
