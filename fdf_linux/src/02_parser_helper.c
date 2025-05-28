/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parser_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:27:04 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 20:46:06 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int		ft_count(char const *s, char c);
int		line_counter(int fd, t_env *env);
int		count_items(char **datas);
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

int	line_counter(int fd, t_env *env)
{
	char	*s;
	t_bool	first;

	first = True;
	env->m_height = 0;
	s = get_next_line(fd);
	while (s)
	{
		remove_end_n(s);
		if (first == True)
		{
			first = False;
			env->m_width = ft_count(s, ' ');
		}
		if (env->m_width != ft_count(s, ' '))
		{
			free(s);
			return (EXIT_FAILURE);
		}
		env->m_height++;
		free(s);
		s = get_next_line(fd);
	}
	return (EXIT_SUCCESS);
}

int	count_items(char **datas)
{
	int	cnt;

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
