/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_utils_for_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:41:27 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/21 15:58:01 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	ft_puterr(void)
{
	write(2, "Error\n", 6);
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && (unsigned char)s1[i] == (unsigned char)s2[i]
		&& i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

long	*list_to_array(t_circ_doubly_list *head, int size)
{
	long	*array;
	int		i;

	array = (long *)malloc(sizeof(long) * size);
	if (!array)
		return (NULL);
	i = 0;
	while (i < size)
	{
		array[i++] = head->content;
		head = head->nxt;
	}
	return (array);
}
