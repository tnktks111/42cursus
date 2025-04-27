/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:23:37 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/27 18:56:41 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return ((unsigned char)c >= '0' && (unsigned char)c <= '9');
}

// int main()
// {
// 	for (int i = 0; i < 255; i++)
// 	{
// 		if (!(isdigit(i)) != !(ft_isdigit(i)))
// 			printf("Fail at %d", i);
// 	}
// }
