/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_calculator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:27:11 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 18:36:25 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_bool	is_in_screen(t_mappoint p0, t_mappoint p1, t_bool reversed);
void	calc_mapsize(t_env *env, double vessel[3][2]);
void	adjust_offset(t_env *env);
void	readjust_offset(t_env *env);

t_bool	is_in_screen(t_mappoint p0, t_mappoint p1, t_bool reversed)
{
	if (ft_db_max(p0.va.x, p1.va.x) < 0)
		return (False);
	if (ft_db_max(p0.va.y, p1.va.y) < 0)
		return (False);
	if (reversed == False)
	{
		if (ft_db_min(p0.va.x, p1.va.x) > W_WIDTH)
			return (False);
		if (ft_db_min(p0.va.y, p1.va.y) > W_HEIGHT)
			return (False);
	}
	else
	{
		if (ft_db_min(p0.va.x, p1.va.x) > W_HEIGHT)
			return (False);
		if (ft_db_min(p0.va.y, p1.va.y) > W_WIDTH)
			return (False);
	}
	return (True);
}

// calculate {{width_min, width_max}, {height_min, height_max}, {x_sum, y_sum}}
void	calc_mapsize(t_env *env, double vessel[3][2])
{
	int	r;
	int	c;

	vessel[0][0] = env->map[0][0].va.x;
	vessel[0][1] = env->map[0][0].va.x;
	vessel[1][0] = env->map[0][0].va.y;
	vessel[1][1] = env->map[0][0].va.y;
	vessel[2][0] = 0;
	vessel[2][1] = 0;
	r = -1;
	while (++r < env->m_height)
	{
		c = -1;
		while (++c < env->m_width)
		{
			vessel[0][0] = ft_db_min(env->map[r][c].va.x, vessel[0][0]);
			vessel[0][1] = ft_db_max(env->map[r][c].va.x, vessel[0][1]);
			vessel[1][0] = ft_db_min(env->map[r][c].va.y, vessel[1][0]);
			vessel[1][1] = ft_db_max(env->map[r][c].va.y, vessel[1][1]);
			vessel[2][0] += env->map[r][c].va.x;
			vessel[2][1] += env->map[r][c].va.y;
		}
	}
}

void	adjust_offset(t_env *env)
{
	double	map_data[3][2];

	calc_mapsize(env, map_data);
	env->user_offset_x = 0;
	env->user_offset_y = 0;
	env->w_width = ceil(map_data[0][1] - map_data[0][0]);
	env->w_height = ceil(map_data[1][1] - map_data[1][0]);
	env->scaling = ft_db_min((double)W_WIDTH / env->w_width, (double)W_HEIGHT
			/ env->w_height) * 0.4;
	env->virtual_square = ft_min(W_WIDTH, W_HEIGHT) / 2;
	env->offset_x = W_WIDTH / 2 - (map_data[2][0] * env->scaling
			/ (env->m_height * env->m_width));
	env->offset_y = W_HEIGHT / 2 - (map_data[2][1] * env->scaling
			/ (env->m_height * env->m_width));
}

void	readjust_offset(t_env *env)
{
	double	map_data[3][2];

	calc_mapsize(env, map_data);
	env->w_width = ceil(map_data[0][1] - map_data[0][0]);
	env->w_height = ceil(map_data[1][1] - map_data[1][0]);
	env->offset_x = W_WIDTH / 2 - (map_data[2][0] * env->scaling
			/ (env->m_height * env->m_width));
	env->offset_y = W_HEIGHT / 2 - (map_data[2][1] * env->scaling
			/ (env->m_height * env->m_width));
}
