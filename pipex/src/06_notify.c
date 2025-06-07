/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_notify.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:31:12 by ttanaka           #+#    #+#             */
/*   Updated: 2025/06/03 23:00:16 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

unsigned char	notify_invalid_format(void)
{
	ft_putendl_fd("Invalid format", STDERR_FILENO);
	return (EXIT_FAILURE);
}

unsigned char notify_invalid_cmd_path(char **command_elems)
{
	char *slash;
	ft_putstr_fd("bash", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(command_elems[0], STDERR_FILENO);
	slash = ft_strchr(command_elems[0], '/');
	if (!slash)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	free_splited_data(command_elems);
	return (127);
}

unsigned char	notify_interfered_by_eof(t_info *info)
{
	ft_putstr_fd("bash", STDERR_FILENO);
	ft_putstr_fd(": warning: here-document delimited by end-of-file (wanted `",
		STDERR_FILENO);
	ft_putstr_fd(info->limiter, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
	return (EXIT_SUCCESS);
}
