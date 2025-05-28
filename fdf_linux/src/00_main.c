/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:26:57 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 20:08:23 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	mlx_handler(t_env *env);

int	main(int argc, char *argv[])
{
	t_env	env;

	init_environment(&env);
	if (parser(argc, argv[1], &env) == EXIT_FAILURE)
		return (1);
	if (mlx_handler(&env) == EXIT_FAILURE)
	{
		env.errno = 1;
		return (close_window(&env));
	}
	mlx_loop(env.mlx_ptr);
	return (0);
}

int	mlx_handler(t_env *env)
{
	env->mlx_ptr = mlx_init();
	if (!env->mlx_ptr)
		return (put_errmsg("Error: mlx_init() failed!\n"));
	env->win_ptr = mlx_new_window(env->mlx_ptr, W_WIDTH, W_HEIGHT, "fdf");
	if (!env->win_ptr)
		return (put_errmsg("Error: mlx_new_window() failed!\n"));
	env->img = mlx_new_image(env->mlx_ptr, W_WIDTH, W_HEIGHT);
	if (!env->img)
		return (put_errmsg("Error: mlx_new_image() failed!\n"));
	env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel,
			&env->line_length, &env->endian);
	env->elevation_map = (int *)malloc(sizeof(int) * W_WIDTH * W_HEIGHT);
	if (!env->elevation_map)
		return (put_errmsg("Error: MALLOC failed!\n"));
	hook_handler(env);
	env->start_xpm = mlx_xpm_file_to_image(env->mlx_ptr, START_FILE_PATH,
			&env->start_img_width, &env->start_img_height);
	if (!env->start_xpm)
		return (put_errmsg("Error: mlx_xpm_file_to_image() failed!\n"));
	env->display_menu = True;
	env->start = True;
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->start_xpm, 0, 0);
	return (0);
}
