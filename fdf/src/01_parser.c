#include "fdf.h"

int parser(int argc, char *argv, t_env *env);
int map_parser(int fd, t_env *env);
static int count_len(char **elements);
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

int map_parser(int fd, t_env *env)
{
    char *line;
    char **datas;
    long elements[2];
    int i;
    int j;

    env->map = (t_mappoint **)malloc(sizeof(t_mappoint*) * env->m_height);
    if (!env->map)
        return (EXIT_FAILURE);
    i = -1;
    while (++i < env->m_height)
    {
        line = get_next_line(fd);
        if (!line)
            return (free(line), free_map_partial(env, i), ft_putendl_fd("Error: malloc failed!\n", 2), EXIT_FAILURE);
        datas = ft_split(line, ' ');
        if (!datas)
            return(free(line), free_splitted_datas(datas), free_map_partial(env, i), ft_putendl_fd("Error: malloc failed!\n", 2), EXIT_FAILURE);
        env->map[i] = (t_mappoint *)malloc(sizeof(t_mappoint) * env->m_width);
        if (!env->map[i])
            return (free(line), free_splitted_datas(datas), free_map_partial(env, i), ft_putendl_fd("Error: malloc failed!\n", 2), EXIT_FAILURE);
        j = -1;
        while (++j < env->m_width)
        {
            element_parser(datas[j], elements);
            if (elements[0] == LONG_MAX)
                return (free(line), free_splitted_datas(datas), free_map_partial(env, i + 1), ft_putendl_fd("Error: Invalid Format!\n", 2), EXIT_FAILURE);
            env->map[i][j].a = set_quaternion(0, j, i, (int)elements[0]);
            env->map[i][j].color = (int)elements[1];
            env->map[i][j].va = rot_isometric(env->map[i][j].a, env);
        }
        free(line);
        free_splitted_datas(datas);
    }
    calc_mapsize(env);
    return (EXIT_SUCCESS);
}

static int count_len(char **elements)
{
	int i;
	
	i = 0;
	while (elements[i])
		i++;
	return (i);
}

void element_parser(char *str, long *res)
{
    int len;
	long long_height;
	int color;
	char **elements;

    res[0] = LONG_MAX;
    res[1] = 0xffffff;
	elements = ft_split(str, ',');
    len = count_len(elements);
	if (len == 1 || len == 2)
    {
        long_height = ft_atoi_for_fdf(elements[0]);
        if (len == 2)
        {
            color = ft_atoi_for_color(elements[1]);
            if (color == -1)
            {
                free_splitted_datas(elements);
                return;
            }
            res[1] = (long)color;
        }
        res[0] = long_height;
    }
    free_splitted_datas(elements);
}