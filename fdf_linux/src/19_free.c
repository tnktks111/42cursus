/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   19_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:27:57 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 19:01:01 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	free_map_partial(t_env *env, int allocated);
void	free_map(t_env *env);
int		close_window(t_env *env);

void	free_map_partial(t_env *env, int allocated)
{
	int	i;

	i = -1;
	while (++i < allocated)
		free(env->map[i]);
	free(env->map);
}

void	free_map(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->m_height)
		free(env->map[i]);
	free(env->map);
}

int	close_window(t_env *env)
{
	if (env->elevation_map)
		free(env->elevation_map);
	if (env->mlx_ptr && env->img)
		mlx_destroy_image(env->mlx_ptr, env->img);
	if (env->mlx_ptr && env->menu_xpm)
		mlx_destroy_image(env->mlx_ptr, env->menu_xpm);
	if (env->mlx_ptr && env->start_xpm)
		mlx_destroy_image(env->mlx_ptr, env->start_xpm);
	if (env->mlx_ptr && env->win_ptr)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	if (env->mlx_ptr)
		mlx_destroy_display(env->mlx_ptr);
	if (env->map)
		free_map(env);
	free(env->mlx_ptr);
	exit(env->errno);
}
