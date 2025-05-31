#include "pipex.h"
int exec_commands(char *command1, char *command2, t_info *info);

int exec_commands(char *command1, char *command2, t_info *info)
{
    int fd[2];
    pid_t pid;
    pid_t pid2;
    int status;
    int status2;
    char *err_msg;
    char *command_path;
    char **command1_elems;
    char **command2_elems;
    int i;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (EXIT_FAILURE);  
    }
    if (pid == 0)
    {
        close(fd[0]);
        if (info->is_valid_infile == False)
        {
            close(fd[1]);
            exit(EXIT_FAILURE);
        }
        dup2(info->in_fd, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        command1_elems = ft_split(command1, ' ');
        i = -1;
        while (info->command_path_prefixs[++i])
        {
            command_path = gen_command_path(info->command_path_prefixs[i], command1_elems[0]);
            execve(command_path, command1_elems, NULL);
            free(command_path);
        }
        err_msg = gen_errmsg_cmd_not_found(info->shell_name, command1_elems[0]);
        if (!err_msg)
        {
            perror("malloc");
            return (EXIT_FAILURE);
        }
        ft_putendl_fd(err_msg, STDERR_FILENO);
        free(err_msg);
        free_splited_data(command1_elems);
        exit(127);
    }
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        return (EXIT_FAILURE);  
    }
    if (pid2 == 0)
    {
        waitpid(pid, &status, 0);
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        dup2(info->out_fd, STDOUT_FILENO);
        close(fd[0]);
        command2_elems = ft_split(command2, ' ');
        i = -1;
        while (info->command_path_prefixs[++i])
        {
            command_path = gen_command_path(info->command_path_prefixs[i], command2_elems[0]);
            execve(command_path, command2_elems, NULL);
            free(command_path);
        }
        err_msg = gen_errmsg_cmd_not_found(info->shell_name, command2_elems[0]);
        if (!err_msg)
        {
            perror("malloc");
            return (EXIT_FAILURE);
        }
        ft_putendl_fd(err_msg, STDERR_FILENO);
        free(err_msg);
        free_splited_data(command2_elems);
        return (EXIT_FAILURE);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid2, &status2, 0);
    return (EXIT_SUCCESS);
}
