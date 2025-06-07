/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_exec_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:31:03 by ttanaka           #+#    #+#             */
/*   Updated: 2025/06/03 23:04:25 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static int	init_process(t_process *process, int size);
int			finish_processes(t_info *info, int process_cnt,
				bool in_child_process);
int			exec_heredoc_process(int out_fd, t_info *info);
int			exec_child_process(int stdin_fd, int stdout_fd, char *cmd,
				t_info *info);
int			exec_n_commands(char *argv[], t_info *info);

static int	init_process(t_process *process, int size)
{
	int	i;

	process->pid = (pid_t *)malloc(sizeof(pid_t) * size);
	process->status = (int *)malloc(sizeof(int) * size);
	process->fd = (int **)malloc(sizeof(int *) * (size - 1));
	if (!process->pid || !process->status || !process->fd)
		return (free_process_var(process), EXIT_FAILURE);
	i = -1;
	while (++i < size - 1)
	{
		process->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!process->fd[i] || pipe(process->fd[i]) == -1)
		{
			free_and_close_allocated_pipes(process->fd, i, size - 1);
			free_process_var(process);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	finish_processes(t_info *info, int process_cnt, bool in_child_process)
{
	int	i;

	if (in_child_process == true)
		free_splited_data(info->command_path_prefixs);
	i = -1;
	while (++i < info->size - 1 && in_child_process == false)
	{
		close(info->process.fd[i][0]);
		close(info->process.fd[i][1]);
	}
	i = -1;
	while (++i < info->size - 1)
		free(info->process.fd[i]);
	i = -1;
	while (++i < process_cnt && in_child_process == false)
		waitpid(info->process.pid[i], &(info->process.status[i]), 0);
	free(info->process.fd);
	info->exit_status = info->process.status[process_cnt - 1];
	free(info->process.pid);
	free(info->process.status);
	if (process_cnt != info->size)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	exec_heredoc_process(int out_fd, t_info *info)
{
	char	*s;
	size_t	lim_len;

	lim_len = ft_strlen(info->limiter);
	ft_putstr_fd("> ", STDOUT_FILENO);
	s = get_next_line(STDIN_FILENO);
	while (s)
	{
		if (ft_strncmp(s, info->limiter, lim_len) == 0 && ft_strlen(s) > lim_len
			&& s[lim_len] == '\n')
		{
			finish_processes(info, info->size, true);
			free(s);
			close(out_fd);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(s, out_fd);
		free(s);
		ft_putstr_fd("> ", STDOUT_FILENO);
		s = get_next_line(STDIN_FILENO);
	}
	close(out_fd);
	finish_processes(info, info->size, true);
	exit(notify_interfered_by_eof(info));
}

int	exec_child_process(int stdin_fd, int stdout_fd, char *cmd, t_info *info)
{
	char	**command_elems;

	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close_all_fd(info);
	command_elems = ft_split(cmd, ' ');
	if (!command_elems)
	{
		finish_processes(info, info->size, true);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (cmd[0] != '\0' && find_approproate_prefix_and_exec(command_elems,
			info) == MALLOC_ERR)
	{
		finish_processes(info, info->size, true);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	finish_processes(info, info->size, true);
	exit(notify_invalid_cmd_path(command_elems));
}

int	exec_n_commands(char *argv[], t_info *info)
{
	int	i;

	if (init_process(&info->process, info->size) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < info->size)
	{
		if (info->here_doc == true && i > 0)
			waitpid(info->process.pid[0], &(info->process.status[i]), 0);
		info->process.pid[i] = fork();
		if (info->process.pid[i] == -1)
			break ;
		if (info->process.pid[i] == 0)
			exec_process_helper(i, argv, info);
	}
	return (finish_processes(info, i, false));
}
