/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:23:22 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/26 21:54:17 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

void	ft_bzero(void *s, size_t n)
{
	char	*c;

	c = (char *)s;
	while (n)
	{
		*c++ = '\0';
		n--;
	}
}

#include <stdio.h>
#include <string.h>     // strcpy, strcmp, strlen
#include "libft.h"      // ft_strlcat, ft_strlen (仮定)

int main() {
	
    char dest[20];
    strcpy(dest, "abc");
    printf("%zu\n", ft_strlcat(dest, "def", sizeof(dest)));
    printf("%s\n", dest);

    strcpy(dest, "abc");
	printf("%zu\n", ft_strlcat(dest, "defgh", 8));
    printf("%s\n", dest);
	
    dest[0] = '\0';
	printf("%zu\n", ft_strlcat(dest, "xyz", 20));
    printf("%s\n", dest);
	
    strcpy(dest, "abc"); // strlen=3
	printf("%zu\n", ft_strlcat(dest, "", 20));
    printf("%s\n", dest);

    dest[0] = '\0'; 
	printf("%zu\n", ft_strlcat(dest, "abc", 1));
    printf("%s\n", dest);

    dest[0] = '\0'; // strlen=0
	printf("%zu\n", ft_strlcat(dest, "abc", 0));
    printf("%s\n", dest);

}