#include "pipex.h"
int exec_n_commands(int argc, char *argv[], t_info *info);

int exec_n_commands(int argc, char *argv[], t_info *info)
{
    pid_t *pid;
    int *fd;
    int *status;
    int i;
    int j;
    char **command_elems;
    char *command_path;
    char *err_msg;
    int n;

    n = argc - 3;
    pid = (pid_t*)malloc(sizeof(pid_t) * (2 * n));
    if (!pid)
        return (EXIT_FAILURE);
    fd = (int*)malloc(sizeof(int) * (2 * n));
    i = -1;
    fd[2 * n - 1] = info->in_fd;
    fd[0] = info->out_fd;
    while (++i < n)
    {
        if (pipe(&fd[2 * i + 1]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
    status = (int *)malloc(sizeof(int) * (2 * n));
    i = -1;
    while (++i < n)
    {
        pid[i] = fork();
        if (pid[i] == 0)
        {
            if (i != 0)
                close(fd[2 * n - 2 * i]);
            if (i != n - 1)
                close(fd[2 * n - 3 - 2 * i]);
            dup2(fd[2 * n - 1 - 2 * i], STDIN_FILENO);
            dup2(fd[2 * n - 2 - 2 * i], STDOUT_FILENO);
            close(fd[2 * n - 1 - 2 * i]);
            close(fd[2 * n - 2 - 2 * i]);
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
    while (++i < n)
    {
        close(fd[2 * i]);
        close(fd[2 * i + 1]);
        waitpid(pid[i], &status[i], 0);
    }
    return (EXIT_SUCCESS);
}
