/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_small_argc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:42:02 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/21 16:00:51 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	two_args_parser(t_list_info *info)
{
	if (info->head->content > info->head->nxt->content)
		command_printer(sa);
}

static void	three_args_parser(t_list_info *info)
{
	long	l1;
	long	l2;
	long	l3;

	l1 = info->head->content;
	l2 = info->head->nxt->content;
	l3 = info->head->nxt->nxt->content;
	if (l1 < l3 && l3 < l2)
	{
		command_printer(sa);
		command_printer(ra);
	}
	else if (l2 < l1 && l1 < l3)
		command_printer(sa);
	else if (l3 < l1 && l1 < l2)
		command_printer(rra);
	else if (l2 < l3 && l3 < l1)
		command_printer(ra);
	else if (l3 < l2 && l2 < l1)
	{
		command_printer(sa);
		command_printer(rra);
	}
}

void	small_args_parser(t_list_info *info)
{
	if (info->size == 2)
		two_args_parser(info);
	else
		three_args_parser(info);
}
