/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:43:07 by ttanaka           #+#    #+#             */
/*   Updated: 2025/06/03 20:45:45 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_process
{
	pid_t		*pid;
	int			**fd;
	int			*status;
}				t_process;

typedef struct s_info
{
	char		**envp;
	int			size;
	int			in_fd;
	int			out_fd;
	char		*limiter;
	bool		here_doc;
	bool		is_valid_infile;
	bool		is_valid_outfile;
	char		**command_path_prefixs;
	t_process	process;
}				t_info;

// 00_main.c
void			free_resources(t_info *info);

// 01_parse_file.c
int				file_parser(char *infile, char *outfile, t_info *info);

// 02_exec_commands.c
int				finish_processes(t_info *info, int process_cnt,
					bool in_child_process);
int				exec_heredoc_process(int out_fd, t_info *info);
int				exec_child_process(int stdin_fd, int stdout_fd, char *cmd,
					t_info *info);
int				exec_n_commands(char *argv[], t_info *info);

// 03_exec_helper.c
int				find_approproate_prefix_and_exec(char **command_elems,
					t_info *info);
void			exec_process_helper(int idx, char *argv[], t_info *info);

// 04_ft_getenv.c
char			*ft_getenv(const char *varname, char *envp[]);
char			*get_last_section(char *path);

// 05_gen_str.c
char			*gen_errmsg_head(char *shell, char *nxtarg);
char			*gen_command_path(char *prefix, char *command_name);

// 06_notify.c
unsigned char	notify_invalid_format(void);
unsigned char	notify_cmd_not_found(char **command_elems);
unsigned char	notify_interfered_by_eof(t_info *info);

// 07_free.c
void			close_except_used_pipe(int **fd, int idx, int size,
					t_info *info);
void			free_process_var(t_process *process);
void			close_all_fd(t_info *info);
void			free_and_close_allocated_pipes(int **pipe, int allocated,
					int size);

#endif