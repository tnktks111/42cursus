/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_for_getenv.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:29:18 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/30 19:14:48 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_get_and_put_c_for_getenv(t_buf_node *node, t_string *res)
{
	int	c;

	while (1)
	{
		c = ft_getc(node);
		if (c == RD_ERR)
		{
			if (res->str)
				free(res->str);
			return (0);
		}
		if (c == EOF || c == 0)
			return (1);
		if (ft_putc(res, (char)c) == MALLOC_ERR)
		{
			if (res->str)
				free(res->str);
			return (0);
		}
	}
}

char	*get_next_line_for_getenv(int fd)
{
	static t_hashtable	hashtable;
	t_buf_node			*node;
	t_string			res;
	int					i;

	if (!hashtable.initialized)
	{
		i = 0;
		while (i < HASH_SIZE)
			(hashtable.table)[i++].fd = -1;
		hashtable.initialized = 1;
	}
	if (fd < 0)
		return (NULL);
	res.str = NULL;
	res.len = 0;
	res.cap = 0;
	node = ft_search(fd, hashtable.table);
	if (!node || !ft_get_and_put_c_for_getenv(node, &res))
		return (NULL);
	return (adjust_string(&res));
}
