/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:23:32 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/27 18:55:51 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_islower(int c)
{
	return ((unsigned char)c >= 'a' && (unsigned char)c <= 'z');
}

static int	ft_isupper(int c)
{
	return ((unsigned char)c >= 'A' && (unsigned char)c <= 'Z');
}

int	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}

// int main()
// {
// 	for (int i = 0; i < 255; i++)
// 	{
// 		if (!(isalpha(i)) != !(ft_isalpha(i)))
// 			printf("Fail at %d", i);
// 	}
// }
