#include "pipex.h"
int exec_n_commands(int argc, char *argv[], t_info *info);

void close_all(int *fd, int size)
{
    int i;

    i = -1;
    while(++i < size)
        close(fd[i]);
}

void close_expect_used_pipe(int **fd, int idx, int size)
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

int exec_n_commands(int argc, char *argv[], t_info *info)
{
    pid_t *pid;
    int **fd;
    int *status;
    int i;
    int j;
    char **command_elems;
    char *command_path;
    char *err_msg;
    int n;
    int stdin_fd;
    int stdout_fd;

    n = argc - 3;
    pid = (pid_t*)malloc(sizeof(pid_t) * n);
    if (!pid)
        return (EXIT_FAILURE);
    fd = (int**)malloc(sizeof(int*) * (n - 1));
    i = -1;
    while (++i < n - 1)
    {
        fd[i] = (int*)malloc(sizeof(int) * 2);
        if (pipe(fd[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
    status = (int *)malloc(sizeof(int) * n);
    i = -1;
    while (++i < n)
    {
        pid[i] = fork();
        if (pid[i] == 0)
        {
            if (i == 0)
                stdin_fd = info->in_fd;
            else
                stdin_fd = fd[i - 1][0];
            if (i == n - 1)
                stdout_fd = info->out_fd;
            else
                stdout_fd = fd[i][1];
            close_expect_used_pipe(fd, i, n - 1);
            dup2(stdin_fd, STDIN_FILENO);
            dup2(stdout_fd, STDOUT_FILENO);
            close(stdin_fd);
            close(stdout_fd);
            command_elems = ft_split(argv[i + 2], ' ');
            j = -1;
            while (info->command_path_prefixs[++j])
            {
                command_path = gen_command_path(info->command_path_prefixs[j], command_elems[0]);
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
    }
    i = -1;
    while (++i < n - 1)
    {
        close(fd[i][0]);
        close(fd[i][1]);
        waitpid(pid[i], &status[i], 0);
    }
    free(pid);
    free(fd);
    free(status);
    return (EXIT_SUCCESS);
}
