/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_line_drawer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:27:19 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 19:58:47 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	fill_background(t_env *env, int color);
void	line_drawer(t_env *env);
void	vertical_line_drawer(t_env *env);
void	horizontal_line_drawer(t_env *env);

void	fill_background(t_env *env, int color)
{
	int		x;
	int		y;
	char	*pixel_destination;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			pixel_destination = env->addr + (y * env->line_length) + (x
					* (env->bits_per_pixel / 8));
			*(unsigned int *)pixel_destination = color;
		}
	}
}

void	line_drawer(t_env *env)
{
	ft_bzero(env->addr, W_HEIGHT * env->line_length);
	ft_init_int_buffer(env->elevation_map, W_WIDTH * W_HEIGHT);
	fill_background(env, BACKGROUND);
	vertical_line_drawer(env);
	horizontal_line_drawer(env);
	env->menu_xpm = mlx_xpm_file_to_image(env->mlx_ptr, XPM_FILE_PATH,
			&env->menu_img_width, &env->menu_img_height);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
	env->display_menu = True;
	if (env->display_menu == True)
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->menu_xpm, 10,
			10);
}

void	vertical_line_drawer(t_env *env)
{
	int			r;
	int			c;
	t_mappoint	p0_screen;
	t_mappoint	p1_screen;

	c = -1;
	while (++c < env->m_width)
	{
		r = -1;
		while (++r < env->m_height - 1)
		{
			p0_screen = env->map[r][c];
			p1_screen = env->map[r + 1][c];
			p0_screen.va.x = env->map[r][c].va.x * env->scaling + env->offset_x
				+ env->user_offset_x;
			p0_screen.va.y = env->map[r][c].va.y * env->scaling + env->offset_y
				+ env->user_offset_y;
			p1_screen.va.x = env->map[r + 1][c].va.x * env->scaling
				+ env->offset_x + env->user_offset_x;
			p1_screen.va.y = env->map[r + 1][c].va.y * env->scaling
				+ env->offset_y + env->user_offset_y;
			xiaolin_wu(env, p0_screen, p1_screen, False);
		}
	}
}

void	horizontal_line_drawer(t_env *env)
{
	int			r;
	int			c;
	t_mappoint	p0_screen;
	t_mappoint	p1_screen;

	r = -1;
	while (++r < env->m_height)
	{
		c = -1;
		while (++c < env->m_width - 1)
		{
			p0_screen = env->map[r][c];
			p1_screen = env->map[r][c + 1];
			p0_screen.va.x = env->map[r][c].va.x * env->scaling + env->offset_x
				+ env->user_offset_x;
			p0_screen.va.y = env->map[r][c].va.y * env->scaling + env->offset_y
				+ env->user_offset_y;
			p1_screen.va.x = env->map[r][c + 1].va.x * env->scaling
				+ env->offset_x + env->user_offset_x;
			p1_screen.va.y = env->map[r][c + 1].va.y * env->scaling
				+ env->offset_y + env->user_offset_y;
			xiaolin_wu(env, p0_screen, p1_screen, False);
		}
	}
}
