#include "fdf.h"

int parser(int argc, char *argv, t_env *env);
int map_parser(int fd, t_env *env);
static int count_len(char **height_color);
void element_parser(char *str, long *res);

int parser(int argc, char *argv, t_env *env)
{
    int fd;

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
    if (line_counter(fd, env) == EXIT_FAILURE)
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

int handle_parse_error(t_env *env, t_data datas, int allocated, int errno)
{
    free(datas.line);
    free_splitted_datas(datas.elements);
    free_map_partial(env, allocated);
    if (errno == MALLOC_ERR)
        ft_putendl_fd("Error: malloc failed!\n", 2);
    if (errno == FORMAT_ERR)
        ft_putendl_fd("Error: Invalid Format!\n", 2);
    return (EXIT_FAILURE);
}

int map_parser(int fd, t_env *env)
{
    t_data datas;
    long height_color[2];
    int i;
    int j;

    env->map = (t_mappoint **)malloc(sizeof(t_mappoint*) * env->m_height);
    if (!env->map)
        return (EXIT_FAILURE);
    i = -1;
    while (++i < env->m_height)
    {
        datas.elements = NULL;
        datas.line = get_next_line(fd);
        if (!datas.line)
            return (handle_parse_error(env, datas, i, MALLOC_ERR));
        datas.elements = ft_split(datas.line, ' ');
        if (!datas.elements)
            return (handle_parse_error(env, datas, i, MALLOC_ERR));
        env->map[i] = (t_mappoint *)malloc(sizeof(t_mappoint) * env->m_width);
        if (!env->map[i])
            return (handle_parse_error(env, datas, i, MALLOC_ERR));
        j = -1;
        while (++j < env->m_width)
        {
            element_parser(datas.elements[j], height_color);
            if (height_color[0] == LONG_MAX)
                return (handle_parse_error(env, datas, i, FORMAT_ERR));
            env->map[i][j].a = set_quaternion(0, j, i, (int)height_color[0]);
            env->map[i][j].color = (int)height_color[1];
            env->map[i][j].va = rot_based_on_view_mode(env->map[i][j].a, env);
        }
        free(datas.line);
        free_splitted_datas(datas.elements);
    }
    adjust_offset(env);
    return (EXIT_SUCCESS);
}

static int count_len(char **height_color)
{
	int i;
	
	i = 0;
	while (height_color[i])
		i++;
	return (i);
}

void element_parser(char *str, long *res)
{
    int len;
	long long_height;
	int color;
	char **height_color;

    res[0] = LONG_MAX;
    res[1] = 0xffffff;
	height_color = ft_split(str, ',');
    len = count_len(height_color);
	if (len == 1 || len == 2)
    {
        long_height = ft_atoi_for_fdf(height_color[0]);
        if (len == 2)
        {
            color = ft_atoi_for_color(height_color[1]);
            if (color == -1)
            {
                free_splitted_datas(height_color);
                return;
            }
            res[1] = (long)color;
        }
        res[0] = long_height;
    }
    free_splitted_datas(height_color);
}
