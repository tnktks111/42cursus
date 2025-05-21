/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_argument_parser_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:40:58 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/21 16:14:32 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static long	ft_atoi_for_pushswap(const char *str)
{
	long	num;
	long	sign;

	if (!str)
		return (LONG_MAX);
	num = 0;
	sign = 1;
	if (*str && (*str == '+' || *str == '-'))
	{
		if (*str++ == '-')
			sign *= -1;
	}
	if (!(*str && ('0' <= *str && *str <= '9')))
		return (LONG_MAX);
	while (*str && ('0' <= *str && *str <= '9'))
	{
		num = num * 10 + (*str++ - '0');
		if ((sign > 0 && num > INT_MAX) || (sign < 0 && num > -(long)INT_MIN))
			return (LONG_MAX);
	}
	if (*str)
		return (LONG_MAX);
	return (sign * num);
}

static t_circ_doubly_list	*ft_lstmap(int argc, char *argv[])
{
	t_circ_doubly_list	*head;
	t_circ_doubly_list	*curr;
	t_circ_doubly_list	*new_node;
	long				new_content;
	int					i;

	head = NULL;
	i = 1;
	while (i < argc)
	{
		new_content = ft_atoi_for_pushswap(argv[i++]);
		new_node = ft_lstnew(new_content);
		if (!head)
		{
			head = new_node;
			curr = head;
		}
		else
			insert_node_tail(new_node, curr);
		curr = curr->nxt;
		if (new_content == LONG_MAX || !new_node)
			return (free_all_node(head), NULL);
	}
	return (head);
}

static t_bool	contains_duplicate(t_list_info *info_a)
{
	long	*l;
	int		i;

	l = list_to_array(info_a->head, info_a->size);
	if (!l)
		return (True);
	quick_sort(l, 0, info_a->size - 1);
	i = -1;
	while (++i < info_a->size - 1)
	{
		if (l[i] == l[i + 1])
			return (free(l), True);
	}
	free(l);
	return (False);
}

int	argv_parser(int argc, char *argv[], t_list_info *info)
{
	info->head = ft_lstmap(argc, argv);
	if (!info->head && argc == 1)
		return (EXIT_SORTED);
	if (!info->head)
		return (EXIT_FAILURE);
	info->size = argc - 1;
	if (contains_duplicate(info) == True)
		return (free_all_node(info->head), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
