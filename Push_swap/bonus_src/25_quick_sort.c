/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:41:33 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/21 15:58:05 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static void	int_swap(long *a, long *b)
{
	long	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	partition(long array[], int left, int right)
{
	int	i;
	int	j;
	int	pivot;

	i = left;
	j = right + 1;
	pivot = left;
	while (i < j)
	{
		while (array[++i] < array[pivot] && i != right)
			;
		while (array[pivot] < array[--j] && j != left)
			;
		if (i >= j)
			break ;
		int_swap(&array[i], &array[j]);
	}
	int_swap(&array[pivot], &array[j]);
	return (j);
}

void	quick_sort(long array[], int left, int right)
{
	int	q;

	if (left < right)
	{
		q = partition(array, left, right);
		quick_sort(array, left, q - 1);
		quick_sort(array, q + 1, right);
	}
}
