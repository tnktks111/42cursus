/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_exec_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:31:05 by ttanaka           #+#    #+#             */
/*   Updated: 2025/06/03 21:09:32 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int		find_approproate_prefix_and_exec(char **command_elems, t_info *info);
void	exec_process_helper(int idx, char *argv[], t_info *info);

int	find_approproate_prefix_and_exec(char **command_elems, t_info *info)
{
	int		i;
	char	*command_path;

	i = -1;
	while (info->command_path_prefixs[++i])
	{
		command_path = gen_command_path(info->command_path_prefixs[i],
				command_elems[0]);
		if (!command_path)
		{
			free_splited_data(command_elems);
			perror("malloc");
			return (MALLOC_ERR);
		}
		execve(command_path, command_elems, info->envp);
		free(command_path);
	}
	execve(command_elems[0], command_elems, info->envp);
	return (EXIT_FAILURE);
}

void	exec_process_helper(int idx, char *argv[], t_info *info)
{
	if (idx == 0 && info->here_doc == true)
	{
		close_except_used_pipe(info->process.fd, idx, info->size - 1, info);
		exec_heredoc_process(info->process.fd[0][1], info);
	}
	else if (idx == 0)
	{
		if (info->is_valid_infile == true)
			exec_child_process(info->in_fd, info->process.fd[idx][1], argv[idx
				+ 2], info);
	}
	else if (idx == info->size - 1)
	{
		if (info->is_valid_outfile == true)
			exec_child_process(info->process.fd[idx - 1][0], info->out_fd,
				argv[idx + 2], info);
	}
	else
		exec_child_process(info->process.fd[idx - 1][0],
			info->process.fd[idx][1], argv[idx + 2], info);
}
