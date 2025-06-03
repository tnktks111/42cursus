/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:31:15 by ttanaka           #+#    #+#             */
/*   Updated: 2025/06/03 20:47:50 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_except_used_pipe(int **fd, int idx, int size, t_info *info);
void	free_process_var(t_process *process);
void	close_all_fd(t_info *info);
void	free_and_close_allocated_pipes(int **pipe, int allocated, int size);

void	close_except_used_pipe(int **fd, int idx, int size, t_info *info)
{
	int	i;

	i = -1;
	if (idx != 0 && info->here_doc == false && info->is_valid_infile == true)
		close(info->in_fd);
	if (idx != size && info->is_valid_outfile == true)
		close(info->out_fd);
	while (++i < size)
	{
		if (i != idx - 1)
			close(fd[i][0]);
		if (i != idx)
			close(fd[i][1]);
	}
}

void	free_process_var(t_process *process)
{
	free(process->pid);
	free(process->status);
	free(process->fd);
}

void	close_all_fd(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->size - 1)
	{
		close(info->process.fd[i][0]);
		close(info->process.fd[i][1]);
	}
	if (info->here_doc == false && info->is_valid_infile)
		close(info->in_fd);
	if (info->is_valid_outfile)
		close(info->out_fd);
}

void	free_and_close_allocated_pipes(int **pipe, int allocated, int size)
{
	int	i;

	i = -1;
	while (++i < allocated)
	{
		close(pipe[i][0]);
		close(pipe[i][1]);
		free(pipe[i]);
	}
	if (allocated < size && pipe[allocated])
		free(pipe);
}
