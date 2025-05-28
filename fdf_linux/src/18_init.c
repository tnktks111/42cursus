/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:27:52 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 20:00:29 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	init_environment(t_env *env);

void	init_environment(t_env *env)
{
	env->errno = 0;
	env->mode = Iso;
	env->is_dragging = False;
	env->map = NULL;
	env->elevation_map = NULL;
	env->mlx_ptr = NULL;
	env->win_ptr = NULL;
	env->img = NULL;
	env->menu_xpm = NULL;
	env->start_xpm = NULL;
	env->addr = NULL;
	env->menu_xpm = NULL;
}
