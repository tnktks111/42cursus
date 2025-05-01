/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:23:40 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/27 15:02:19 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return ((unsigned char)c >= 32 && (unsigned char)c <= 126);
}

// int main()
// {
// 	for (int i = 0; i < 255; i++)
// 	{
// 		if (!(isprint(i)) != !(ft_isprint(i)))
// 			printf("Fail at %d", i);
// 	}
// }
