/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:23:34 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/27 18:56:31 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return ((unsigned char)c >= 0 && (unsigned char)c <= 127);
}

// int main()
// {
// 	for (int i = 0; i < 255; i++)
// 	{
// 		if (!(isascii(i)) != !(ft_isascii(i)))
// 			printf("Fail at %d", i);
// 	}
// }
