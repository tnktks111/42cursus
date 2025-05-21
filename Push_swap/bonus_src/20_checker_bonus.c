/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_checker_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:45:55 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/21 19:20:26 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/inc/get_next_line.h"
#include "push_swap_bonus.h"

void	put_ko(void)
{
	write(1, "KO\n", 3);
}

static t_commands	command_checker(char *s)
{
	if (ft_strncmp(s, "sa\n", 3) == 0)
		return (sa);
	if (ft_strncmp(s, "sb\n", 3) == 0)
		return (sb);
	if (ft_strncmp(s, "ss\n", 3) == 0)
		return (ss);
	if (ft_strncmp(s, "pa\n", 3) == 0)
		return (pa);
	if (ft_strncmp(s, "pb\n", 3) == 0)
		return (pb);
	if (ft_strncmp(s, "ra\n", 3) == 0)
		return (ra);
	if (ft_strncmp(s, "rb\n", 3) == 0)
		return (rb);
	if (ft_strncmp(s, "rr\n", 3) == 0)
		return (rr);
	if (ft_strncmp(s, "rra\n", 4) == 0)
		return (rra);
	if (ft_strncmp(s, "rrb\n", 4) == 0)
		return (rrb);
	if (ft_strncmp(s, "rrr\n", 4) == 0)
		return (rrr);
	else
		return (Error);
}

static void	operator(t_commands cmd, t_list_info *info_a, t_list_info *info_b)
{
	if (cmd == sa)
		swap(info_a);
	else if (cmd == sb)
		swap(info_b);
	else if (cmd == ss)
	{
		swap(info_a);
		swap(info_b);
	}
	else if (cmd == pa)
		push(info_a, info_b);
	else if (cmd == pb)
		push(info_b, info_a);
	else if (cmd == ra || cmd == rra)
		rotate(info_a, (t_bool)(cmd == rra));
	else if (cmd == rb || cmd == rrb)
		rotate(info_b, (t_bool)(cmd == rrb));
	else if (cmd == rr || cmd == rrr)
	{
		rotate(info_a, (t_bool)(cmd == rrr));
		rotate(info_b, (t_bool)(cmd == rrr));
	}
}

static int	is_sorted(t_list_info *info_a)
{
	int					i;
	t_circ_doubly_list	*curr;

	curr = info_a->head;
	i = info_a->size - 1;
	while (i-- > 0)
	{
		if (curr->nxt == NULL || curr->content >= curr->nxt->content)
			return (0);
		curr = curr->nxt;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_list_info	info_a;
	t_list_info	info_b;
	t_commands	cmd;
	char		*s;

	if (argc == 1)
		return (0);
	if (argv_parser(argc, argv, &info_a) == EXIT_FAILURE)
		return (ft_puterr(), 1);
	info_b.head = NULL;
	info_b.size = 0;
	s = get_next_line(0);
	while (s != NULL)
	{
		cmd = command_checker(s);
		if (cmd == Error)
			return (ft_puterr(), 1);
		operator(cmd, &info_a, &info_b);
		s = get_next_line(0);
	}
	if (!is_sorted(&info_a) || info_b.size != 0)
		write(1, "KO\n", 3);
	else
		write(1, "OK\n", 3);
	return (0);
}
