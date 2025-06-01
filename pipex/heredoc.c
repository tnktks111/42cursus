#include "pipex.h"

void heredoc_checker(int argc, char *argv[], t_info *info);

void heredoc_checker(int argc, char *argv[], t_info *info)
{
	if (ft_strncmp(argv[1], "here_doc", 8) != 0)
		return;
	info->here_doc = True;
	info->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
	info->limiter = argv[2];
}
