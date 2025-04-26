/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:58:11 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/26 17:01:26 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cur_last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	cur_last = *lst;
	while (cur_last && cur_last->next)
		cur_last = cur_last->next;
	cur_last->next = new;
}
