#include "pipex.h"
int exec_n_commands(char *argv[], t_info *info);

void close_all(int *fd, int size)
{
    int i;

    i = -1;
    while(++i < size)
        close(fd[i]);
}

void close_except_used_pipe(int **fd, int idx, int size)
{
    int i;

    i = -1;
    while (++i < size)
    {
        if (i != idx - 1)
            close(fd[i][0]);
        if (i != idx)
            close(fd[i][1]);
    }
}

int exec_heredoc_process(int out_fd, t_info *info)
{
	char *s;
	char *limiter_and_linebreak;
	int lim_len;

	limiter_and_linebreak = ft_strjoin(info->limiter, "\n");
	if (!limiter_and_linebreak)
		return (EXIT_FAILURE);
	lim_len = ft_strlen(limiter_and_linebreak);
	ft_putstr_fd("> ", STDOUT_FILENO);
	s = get_next_line(STDIN_FILENO);
	while (s)
	{
		if (ft_strncmp(s, limiter_and_linebreak, lim_len) == 0)
		{
			free(limiter_and_linebreak);
			free(s);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(s, out_fd);
		free(s);
		ft_putstr_fd("> ", STDOUT_FILENO);
		s = get_next_line(STDIN_FILENO);
	}
	free(limiter_and_linebreak);
	ft_putstr_fd(info->shell_name, STDERR_FILENO);
	ft_putendl_fd(": warning: here-document delimited by end-of-file", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int exec_child_process(int stdin_fd, int stdout_fd, char *cmd, t_info *info)
{
    char **command_elems;
    char *command_path;
    char *err_msg;
    int i;

	if (info->here_doc == True)
		waitpid(info->process.pid[0], &(info->process.status[0]), 0);
    dup2(stdin_fd, STDIN_FILENO);
    dup2(stdout_fd, STDOUT_FILENO);
    close(stdin_fd);
    close(stdout_fd);
    command_elems = ft_split(cmd, ' ');
    i = -1;
    while (info->command_path_prefixs[++i])
    {
        command_path = gen_command_path(info->command_path_prefixs[i], command_elems[0]);
        execve(command_path, command_elems, NULL);
        free(command_path);
    }
    err_msg = gen_errmsg_cmd_not_found(info->shell_name, command_elems[0]);
    if (!err_msg)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_putendl_fd(err_msg, STDERR_FILENO);
    free(err_msg);
    free_splited_data(command_elems);
    exit(127);
}

void finish_processes(t_info *info)
{
    int i;

    i = -1;
    while (++i < info->size - 1)
    {
        close(info->process.fd[i][0]);
        close(info->process.fd[i][1]);
    }
	i = -1;
	while (++i < info->size)
		waitpid(info->process.pid[i], &(info->process.status[i]), 0);
    free(info->process.pid);
    free(info->process.fd);
    free(info->process.status);
}

int init_process(t_process *process, int size)
{
    int i;
    process->pid = (pid_t *)malloc(sizeof(pid_t) * size);
    if (!process->pid)
        return (EXIT_FAILURE);
    process->fd = (int **)malloc(sizeof(int *) * (size - 1));
    if (!process->fd)
    {
        free(process->pid);
        return (EXIT_FAILURE);
    }
    i = -1;
    while (++i < size - 1)
    {
        process->fd[i] = (int *)malloc(sizeof(int) * 2);
        if (pipe(process->fd[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
    process->status = (int *)malloc(sizeof(int) * size);
    if (!process->status)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int exec_n_commands(char *argv[], t_info *info)
{
    int i;

    if (init_process(&info->process, info->size) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    i = -1;
    while (++i < info->size)
    {
        info->process.pid[i] = fork();
        if (info->process.pid[i] == 0)
        {
            close_except_used_pipe(info->process.fd, i, info->size - 1);
            if (i == 0 && info->here_doc == True)
				exec_heredoc_process(info->process.fd[0][1], info);
			else if (i == 0)
                exec_child_process(info->in_fd, info->process.fd[i][1], argv[i + 2], info);
            else if (i == info->size - 1)
                exec_child_process(info->process.fd[i - 1][0], info->out_fd, argv[i + 2], info);
            else
                exec_child_process(info->process.fd[i - 1][0], info->process.fd[i][1], argv[i + 2], info);
        }
    }
    finish_processes(info);
    return (EXIT_SUCCESS);
}
