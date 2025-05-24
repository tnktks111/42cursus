#include "fdf.h"

int	ft_count(char const *s, char c);
int line_counter(int fd, t_env *env);
int count_items(char **datas);
void	**free_splitted_datas(char **words);

int	ft_count(char const *s, char c)
{
	int	cnt;

	if (!s || !s[0])
		return (0);
	cnt = 0;
	while (*s)
	{
		if (*s != c)
		{
			cnt++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (cnt);
}

int line_counter(int fd, t_env *env)
{
    char *s;
    int height;
    int first;

    first = 1;
    height = 0;
    s = get_next_line(fd);
    while (s)
    {
        if (first)
        {
            first = 0;
            env->m_width = ft_count(s, ' ');
        }
        if (env->m_width != ft_count(s, ' '))
        {
            ft_putendl_fd("Error: Invalid Format!!!", 2);
            return (EXIT_FAILURE);
        }
        height++;
        free(s);
        s = get_next_line(fd);
    }
    env->m_height = height;
    return (EXIT_SUCCESS);
}

int count_items(char **datas)
{
    int cnt;

    cnt = 0;
    while (datas[cnt])
        cnt++;
    return (cnt);
}

void	**free_splitted_datas(char **words)
{
    int	i;

	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
	return (NULL);
}
