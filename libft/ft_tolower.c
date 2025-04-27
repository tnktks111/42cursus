/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:24:57 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/26 20:33:33 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isupper(int c)
{
	unsigned char c_cpy;

	c_cpy = (unsigned char)c;
	if (c_cpy >= 'A' && c_cpy <= 'Z')
		return (1);
	else
		return (0);
}

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		c += 32;
	return (c);
}

// // if the given parameter is not an unsigned char val(0 ~ 255), the behavior is undefined.
// int main()
// {
// 	for (int c = 0; c <= 255; ++c)
// 	{
// 		if (ft_tolower(c) != tolower(c))
// 			printf("at %d, ft: %d, original: %d\n", c, ft_tolower(c), tolower(c));
// 	}
// }
