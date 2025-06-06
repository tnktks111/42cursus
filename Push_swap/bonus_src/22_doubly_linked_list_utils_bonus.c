/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_doubly_linked_list_utils_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:41:22 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/21 15:57:54 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

t_circ_doubly_list	*ft_lstnew(long content)
{
	t_circ_doubly_list	*newnode;

	newnode = malloc(sizeof(t_circ_doubly_list));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	newnode->nxt = newnode;
	newnode->prv = newnode;
	return (newnode);
}

void	sep_node(t_circ_doubly_list *node)
{
	if (!node)
		return ;
	(node->prv)->nxt = node->nxt;
	(node->nxt)->prv = node->prv;
}

void	insert_node(t_circ_doubly_list *new_node, t_circ_doubly_list *nxt_node)
{
	if (!new_node || !nxt_node)
		return ;
	(new_node)->prv = nxt_node->prv;
	(new_node)->nxt = nxt_node;
	(nxt_node->prv)->nxt = new_node;
	nxt_node->prv = new_node;
}

void	insert_node_tail(t_circ_doubly_list *new_node,
		t_circ_doubly_list *tail_node)
{
	if (!new_node || !tail_node)
		return ;
	(new_node)->nxt = (tail_node)->nxt;
	((tail_node)->nxt)->prv = new_node;
	(tail_node)->nxt = new_node;
	(new_node)->prv = tail_node;
}

void	free_all_node(t_circ_doubly_list *head)
{
	t_circ_doubly_list	*curr;
	t_circ_doubly_list	*tmp;

	if (!head)
		return ;
	curr = head->nxt;
	while (curr && curr != head)
	{
		tmp = curr;
		curr = curr->nxt;
		free(tmp);
	}
	free(head);
}
