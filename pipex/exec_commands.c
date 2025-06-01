#include "pipex.h"
int exec_n_commands(int argc, char *argv[], t_info *info);

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

int exec_child_process(int stdin_fd, int stdout_fd, char *cmd, t_info *info)
{
    char **command_elems;
    char *command_path;
    char *err_msg;
    int i;

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

void finish_processes(t_process *process, int size)
{
    int i;

    i = -1;
    while (++i < size - 1)
    {
        close(process->fd[i][0]);
        close(process->fd[i][1]);
        waitpid(process->pid[i], &(process->status[i]), 0);
    }
    free(process->pid);
    free(process->fd);
    free(process->status);
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

int exec_n_commands(int argc, char *argv[], t_info *info)
{
    t_process process;
    int i;
    int n;

    n = argc - 3;
    if (init_process(&process, n) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    i = -1;
    while (++i < n)
    {
        process.pid[i] = fork();
        if (process.pid[i] == 0)
        {
            close_except_used_pipe(process.fd, i, n - 1);
            if (i == 0)
                exec_child_process(info->in_fd, process.fd[0][1], argv[2], info);
            else if (i == n - 1)
                exec_child_process(process.fd[n - 2][0], info->out_fd, argv[n + 1], info);
            else
                exec_child_process(process.fd[i - 1][0], process.fd[i][1], argv[i + 2], info);
        }
    }
    finish_processes(&process, n);
    return (EXIT_SUCCESS);
}
