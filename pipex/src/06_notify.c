#include "../inc/pipex.h"

unsigned char notify_invalid_format(void)
{
    ft_putstr_fd("Invalid format", STDERR_FILENO);
    return (EXIT_FAILURE);
}

unsigned char notify_cmd_not_found(char **command_elems, t_info *info)
{
    ft_putstr_fd(info->shell_name, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd(command_elems[0], STDERR_FILENO);
    ft_putendl_fd(": command not found", STDERR_FILENO);
    free_splited_data(command_elems);
    return(127);
}

unsigned char notify_interfered_by_eof(t_info *info)
{
	ft_putstr_fd(info->shell_name, STDERR_FILENO);
	ft_putstr_fd(": warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
    ft_putstr_fd(info->limiter, STDERR_FILENO);
    ft_putendl_fd("')", STDERR_FILENO);
    return (EXIT_SUCCESS);
}
