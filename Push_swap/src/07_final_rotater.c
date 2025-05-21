/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_final_rotater.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:41:17 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/21 12:58:30 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	final_rotator(t_list_info *info)
{
	int	i;

	i = find_min_index_in_sorted_l(info);
	while (i > 0)
	{
		rotate(info, False, ra);
		i--;
	}
	while (i < 0)
	{
		rotate(info, True, rra);
		i++;
	}
}
