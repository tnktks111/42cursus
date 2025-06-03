/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_ft_getenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:31:08 by ttanaka           #+#    #+#             */
/*   Updated: 2025/06/03 20:42:53 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*ft_getenv(const char *varname, char *envp[]);

char	*ft_getenv(const char *varname, char *envp[])
{
	int		i;
	char	*res;
	int		var_len;

	var_len = ft_strlen(varname);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], varname, var_len) == 0
			&& envp[i][var_len] == '=')
		{
			res = ft_strdup(envp[i] + (var_len + 1));
			if (!res)
				return (NULL);
			return (res);
		}
	}
	return (NULL);
}

// receive an allocated path and return last section(ex. "/bin/bash" -> "bash")
char	*get_last_section(char *path)
{
	char	*last_section;
	char	*res;

	last_section = ft_strrchr(path, '/');
	if (!last_section)
		return (path);
	last_section++;
	res = ft_strdup(last_section);
	free(path);
	return (res);
}

// // cc -Wall -Wextra -Werror ft_getenv.c -Lget_next_line -Llibft -lft -lgnl
// int main(void)
// {
//     char *pathvar;
//     char *pathvar2;

//     pathvar = get_last_section(ft_getenv("SHELL"));
//     pathvar2 = getenv("SHELL");
//     printf("ft_getenv:\n%s\n",pathvar);
//     printf("getenv:\n%s\n",pathvar2);
// }