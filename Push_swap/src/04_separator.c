/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:19:31 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/21 15:14:42 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_and_rotate(t_list_info *info_a, t_list_info *info_b)
{
	push(info_a, info_b, pa);
	rotate(info_a, False, ra);
}

void	separator(t_list_info *info_a, t_list_info *info_b)
{
	int		i;
	t_bool	lis_started;

	lis_started = False;
	i = info_a->size;
	while (i--)
	{
		if (!(info_a->head)->in_lis)
		{
			push(info_b, info_a, pb);
			if (info_a->size + info_b->size > 50 && info_b->size > 1
				&& find_chunk_point(info_b->head->nxt, info_b->size
					- 1) < (info_b->head)->content)
				rotate(info_b, False, rb);
		}
		else
		{
			while (lis_started == True && info_b->head
				&& (info_a->head->content) > (info_b->head->content)
				&& (info_a->head->prv->content) < (info_b->head->content))
				push_and_rotate(info_a, info_b);
			rotate(info_a, False, ra);
			lis_started = True;
		}
	}
}
