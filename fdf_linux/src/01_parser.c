/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:27:01 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 21:09:41 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int		parser(int argc, char *argv, t_env *env);
int		map_converter(int row, t_data datas, t_env *env);
int		map_parser(int fd, t_env *env);
void	element_parser(char *str, long *res);

int	parser(int argc, char *argv, t_env *env)
{
	int	fd;

	if (argc != 2)
	{
		ft_putendl_fd("Error: You must pass only one valid file path!", 2);
		return (EXIT_FAILURE);
	}
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error: Invalid FilePath!", 2);
		return (EXIT_FAILURE);
	}
	if (line_counter(fd, env) == EXIT_FAILURE || env->m_height == 0
		|| env->m_width == 0)
	{
		ft_putendl_fd("Error: Invalid Format!", 2);
		return (EXIT_FAILURE);
	}
	close(fd);
	fd = open(argv, O_RDONLY);
	if (map_parser(fd, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	handle_parse_error(t_env *env, t_data datas, int allocated, int errno)
{
	free(datas.line);
	free_splitted_datas(datas.elements);
	free_map_partial(env, allocated);
	if (errno == MALLOC_ERR)
		ft_putendl_fd("Error: malloc failed!", 2);
	if (errno == FORMAT_ERR)
		ft_putendl_fd("Error: Invalid Format!", 2);
	return (EXIT_FAILURE);
}

int	map_converter(int row, t_data datas, t_env *env)
{
	int		col;
	long	height_color[2];

	col = -1;
	while (++col < env->m_width)
	{
		element_parser(datas.elements[col], height_color);
		if (height_color[0] == LONG_MAX)
			return (EXIT_FAILURE);
		env->map[row][col].a = set_quaternion(0, col, row,
				(int)height_color[0]);
		env->map[row][col].color = (int)height_color[1];
		env->map[row][col].va = rot_based_on_view_mode(env->map[row][col].a,
				env);
	}
	free(datas.line);
	free_splitted_datas(datas.elements);
	return (EXIT_SUCCESS);
}

int	map_parser(int fd, t_env *env)
{
	t_data	datas;
	int		i;

	env->map = (t_mappoint **)malloc(sizeof(t_mappoint *) * env->m_height);
	if (!env->map)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < env->m_height)
	{
		datas.elements = NULL;
		datas.line = get_next_line(fd);
		if (!datas.line)
			return (handle_parse_error(env, datas, i, MALLOC_ERR));
		remove_end_n(datas.line);
		datas.elements = ft_split(datas.line, ' ');
		if (!datas.elements)
			return (handle_parse_error(env, datas, i, MALLOC_ERR));
		env->map[i] = (t_mappoint *)malloc(sizeof(t_mappoint) * env->m_width);
		if (!env->map[i])
			return (handle_parse_error(env, datas, i, MALLOC_ERR));
		if (map_converter(i, datas, env) == EXIT_FAILURE)
			return (handle_parse_error(env, datas, i + 1, FORMAT_ERR));
	}
	adjust_offset(env);
	return (EXIT_SUCCESS);
}

void	element_parser(char *str, long *res)
{
	int		len;
	long	long_height;
	int		color;
	char	**height_color;

	res[0] = LONG_MAX;
	res[1] = 0xffffff;
	height_color = ft_split(str, ',');
	len = ft_strarr_len(height_color);
	if (len == 1 || len == 2)
	{
		long_height = ft_atoi_for_fdf(height_color[0]);
		if (len == 2)
		{
			color = ft_atoi_for_color(height_color[1]);
			if (color == -1)
			{
				free_splitted_datas(height_color);
				return ;
			}
			res[1] = (long)color;
		}
		res[0] = long_height;
	}
	free_splitted_datas(height_color);
}
