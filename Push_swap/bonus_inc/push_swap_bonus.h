/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:57:37 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/21 19:20:12 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# include <limits.h>
// # include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define EXIT_SORTED -1
// #define INT_MAX 2147483647
// #define INT_MIN -2147483648
# define INF 2147483648L

typedef enum e_bool
{
	False,
	True
}								t_bool;

typedef enum e_commands
{
	sa,
	sb,
	ss,
	pa,
	pb,
	ra,
	rb,
	rr,
	rra,
	rrb,
	rrr,
	pass,
	Error
}								t_commands;

typedef struct s_circ_doubly_list
{
	long						content;
	int							in_lis;
	struct s_circ_doubly_list	*nxt;
	struct s_circ_doubly_list	*prv;
}								t_circ_doubly_list;

typedef struct s_list_info
{
	t_circ_doubly_list			*head;
	int							size;
}								t_list_info;

typedef struct s_score_info
{
	int							a_score;
	int							a_rev_score;
	int							b_score;
	int							b_rev_score;
	int							min_score;
	int							rotate_a_cnt;
	int							rotate_b_cnt;
	int							rotate_ab_cnt;
}								t_score_info;

int								argv_parser(int argc, char *argv[],
									t_list_info *info);

void							push(t_list_info *dst, t_list_info *src);
void							swap(t_list_info *info);
void							rotate(t_list_info *info, t_bool reverse);

t_circ_doubly_list				*ft_lstnew(long content);
void							sep_node(t_circ_doubly_list *node);
void							insert_node(t_circ_doubly_list *new_node,
									t_circ_doubly_list *nxt_node);
void							insert_node_tail(t_circ_doubly_list *new_node,
									t_circ_doubly_list *tail_node);
void							free_all_node(t_circ_doubly_list *head);

int								ft_puterr(void);
size_t							ft_strlen(const char *s);
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
long							*list_to_array(t_circ_doubly_list *head,
									int size);

void							quick_sort(long array[], int left, int right);

#endif