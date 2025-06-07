/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:30:56 by ttanaka           #+#    #+#             */
/*   Updated: 2025/06/03 23:04:46 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	init_info(int argc, t_info *info, char *envp[]);
static void	heredoc_checker(int argc, char *argv[], t_info *info);
void		free_resources(t_info *info);
int			main(int argc, char *argv[], char *envp[]);

static void	init_info(int argc, t_info *info, char *envp[])
{
	char	*env_path;

	info->envp = envp;
	info->size = argc - 3;
	info->here_doc = false;
	info->is_valid_infile = true;
	info->is_valid_outfile = true;
	env_path = ft_getenv("PATH", envp);
	info->command_path_prefixs = ft_split(env_path, ':');
	free(env_path);
}

static void	heredoc_checker(int argc, char *argv[], t_info *info)
{
	char	*err_head;

	if (ft_strncmp(argv[1], "here_doc", 8) != 0)
		return ;
	info->here_doc = true;
	info->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!info->out_fd)
	{
		info->is_valid_outfile = false;
		err_head = gen_errmsg_head("bash", argv[argc - 1]);
		perror(err_head);
		free(err_head);
	}
	info->limiter = argv[2];
}

void	free_resources(t_info *info)
{
	if (info->here_doc == false && info->is_valid_infile == true)
		close(info->in_fd);
	if (info->is_valid_outfile == true)
		close(info->out_fd);
	free_splited_data(info->command_path_prefixs);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info	info;

	if (argc < 5 || (argc < 6 && ft_strncmp(argv[1], "here_doc", 8) == 0))
		return (notify_invalid_format());
	init_info(argc, &info, envp);
	heredoc_checker(argc, argv, &info);
	if (file_parser(argv[1], argv[argc - 1], &info) == EXIT_FAILURE)
	{
		free_resources(&info);
		return (EXIT_FAILURE);
	}
	if (exec_n_commands(argv, &info) == EXIT_FAILURE)
	{
		free_resources(&info);
		return (EXIT_FAILURE);
	}
	free_resources(&info);
	return (info.exit_status);
}
