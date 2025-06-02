#include "../inc/pipex.h"

static int init_process(t_process *process, int size);
static int finish_processes(t_info *info, int process_cnt);
int exec_heredoc_process(int out_fd, t_info *info);
int exec_child_process(int stdin_fd, int stdout_fd, char *cmd, t_info *info);
int exec_n_commands(char *argv[], t_info *info);

static int init_process(t_process *process, int size)
{
    int i;

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

static int finish_processes(t_info *info, int process_cnt)
{
    int i;

    i = -1;
    while (++i < info->size - 1)
    {
        close(info->process.fd[i][0]);
        close(info->process.fd[i][1]);
        free(info->process.fd[i]);
    }
	i = -1;
	while (++i < process_cnt)
		waitpid(info->process.pid[i], &(info->process.status[i]), 0);
    free(info->process.pid);
    free(info->process.fd);
    free(info->process.status);
    if (process_cnt != info->size)
    {
        perror("fork");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
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
	exit(notify_interfered_by_eof(info));
}

int exec_child_process(int stdin_fd, int stdout_fd, char *cmd, t_info *info)
{
    char **command_elems;

    dup2(stdin_fd, STDIN_FILENO);
    dup2(stdout_fd, STDOUT_FILENO);
    close(stdin_fd);
    close(stdout_fd);
    command_elems = ft_split(cmd, ' ');
    if (!command_elems)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (cmd[0] != '\0' && find_approproate_prefix_and_exec(command_elems, info) == MALLOC_ERR)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    exit(notify_cmd_not_found(command_elems, info));
}

int exec_n_commands(char *argv[], t_info *info)
{
    int i;

    if (init_process(&info->process, info->size) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    i = -1;
    while (++i < info->size)
    {
        if (info->here_doc == True && i > 0)
            waitpid(info->process.pid[0], &(info->process.status[i]), 0);
        info->process.pid[i] = fork();
        if (info->process.pid[i] == -1)
            break;
        if (info->process.pid[i] == 0)
        {
            close_except_used_pipe(info->process.fd, i, info->size - 1);
            exec_process_helper(i, argv, info);
        }
    }
    return(finish_processes(info, i));
}

