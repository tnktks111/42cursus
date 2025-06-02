#include "../inc/pipex.h"

void close_except_used_pipe(int **fd, int idx, int size);
void free_process_var(t_process *process);
void free_and_close_allocated_pipes(int **pipe, int allocated, int size);
int find_approproate_prefix_and_exec(char **command_elems, t_info *info);
void exec_process_helper(int idx, char *argv[], t_info *info);


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

void free_process_var(t_process *process)
{
    free(process->pid);
    free(process->status);
    free(process->fd);
}

void free_and_close_allocated_pipes(int **pipe, int allocated, int size)
{
    int i;

    i = -1;
    while(++i < allocated)
    {
        close(pipe[i][0]);
        close(pipe[i][1]);
        free(pipe[i]);
    }
    if (allocated < size && pipe[allocated])
        free(pipe);
}

int find_approproate_prefix_and_exec(char **command_elems, t_info *info)
{
    int i;
    char *command_path;

    i = -1;
    while (info->command_path_prefixs[++i])
    {
        command_path = gen_command_path(info->command_path_prefixs[i], command_elems[0]);
        if (!command_path)
        {
            free_splited_data(command_elems);
            perror("malloc");
            return(MALLOC_ERR);
        }
        execve(command_path, command_elems, NULL);
        free(command_path);
    }
    execve(command_elems[0], command_elems, NULL);
    return (EXIT_FAILURE);
}

void exec_process_helper(int idx, char *argv[], t_info *info) 
{
    if (idx == 0 && info->here_doc == True)
        exec_heredoc_process(info->process.fd[0][1], info);
    else if (idx == 0)
        exec_child_process(info->in_fd, info->process.fd[idx][1], argv[idx + 2], info);
    else if (idx == info->size - 1)
        exec_child_process(info->process.fd[idx - 1][0], info->out_fd, argv[idx + 2], info);
    else
        exec_child_process(info->process.fd[idx - 1][0], info->process.fd[idx][1], argv[idx + 2], info);
}