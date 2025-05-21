/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:41:24 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/21 13:04:14 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_list_info *dst, t_list_info *src, t_commands cmd)
{
	t_circ_doubly_list	*node_to_move;

	if (src->size == 0)
		return ;
	node_to_move = src->head;
	if ((src->size)-- == 1)
		src->head = NULL;
	else
	{
		src->head = (src->head)->nxt;
		sep_node(node_to_move);
	}
	if ((dst->size)++ == 0)
	{
		dst->head = node_to_move;
		node_to_move->nxt = node_to_move;
		node_to_move->prv = node_to_move;
	}
	else
	{
		insert_node(node_to_move, dst->head);
		dst->head = node_to_move;
	}
	if (cmd != pass)
		command_printer(cmd);
}

void	swap(t_list_info *info, t_commands cmd)
{
	int	content_tmp;
	int	in_lis_tmp;

	if (!info || !info->head || info->size < 2)
		return ;
	content_tmp = (info->head)->content;
	(info->head)->content = (info->head->nxt)->content;
	(info->head->nxt)->content = content_tmp;
	in_lis_tmp = (info->head)->in_lis;
	(info->head)->in_lis = (info->head->nxt)->in_lis;
	(info->head->nxt)->in_lis = in_lis_tmp;
	if (cmd != pass)
		command_printer(cmd);
}

void	rotate(t_list_info *info, t_bool reverse, t_commands cmd)
{
	if (!info || !(info->head))
		return ;
	if (reverse == True)
		info->head = (info->head)->prv;
	else
		info->head = (info->head)->nxt;
	if (cmd != pass)
		command_printer(cmd);
}

void	rotate_two_stack(t_list_info *info_a, t_list_info *info_b,
		t_commands cmd)
{
	if (cmd == rr)
	{
		rotate(info_a, False, pass);
		rotate(info_b, False, pass);
		command_printer(cmd);
	}
	else
	{
		rotate(info_a, True, pass);
		rotate(info_b, True, pass);
		command_printer(cmd);
	}
}
