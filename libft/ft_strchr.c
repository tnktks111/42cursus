/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:24:18 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/26 13:24:19 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;
	char	c_cpy;

	p = (char *)s;
	c_cpy = (char)c;
	while (*p && *p != c_cpy)
		p++;
	if (*p == '\0' && c_cpy != '\0')
		p = NULL;
	return (p);
}

// #include <stdio.h>
// int main()
// {
//     char s[] = "Hello World";
//     printf("%s",ft_strchr(s, 'H' + 256));
// }
