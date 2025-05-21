/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_lis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:41:00 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/21 15:14:15 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	solve_lis_length(long *l, int size)
{
	long	*dp;
	int		i;
	int		j;

	dp = (long *)malloc(sizeof(long) * size);
	if (!dp)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < size)
		dp[i] = INF;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j <= i)
		{
			if (j == 0 || l[i] > dp[j - 1])
				dp[j] = ft_min(l[i], dp[j]);
		}
	}
	i = -1;
	while (++i < size)
		if (dp[i] == INF)
			break ;
	return (free(dp), i);
}

static int	start_idx_for_circular_lis(t_list_info *info)
{
	long				*l;
	int					i;
	int					j;
	int					max;
	int					tmp;

	max = 0;
	i = -1;
	while (++i < info->size)
	{
		l = list_to_array(info->head, info->size);
		tmp = solve_lis_length(l, info->size);
		if (i == 0 && tmp == info->size)
			return (free(l), EXIT_SORTED);
		if (tmp > max)
		{
			max = tmp;
			j = i;
		}
		free(l);
		info->head = info->head->nxt;
	}
	return (j);
}

int	lis(t_list_info *info)
{
	t_circ_doubly_list	*curr;
	long				**dp;
	long				*l;
	int					i;

	i = start_idx_for_circular_lis(info);
	curr = info->head;
	while (i-- > 0)
		curr = curr->nxt;
	l = list_to_array(curr, info->size);
	dp = init_dp_table(info->size);
	if (!dp)
		return (free(l), free_all_node(info->head), EXIT_FAILURE);
	create_dp_table(dp, l, info->size);
	lis_restorator(dp, l, info->size);
	i = 0;
	while (i < info->size)
	{
		curr->in_lis = 0;
		if (l[i++] == 1)
			curr->in_lis = 1;
		curr = curr->nxt;
	}
	return (free(l), free_dp_table(dp, i), EXIT_SUCCESS);
}
