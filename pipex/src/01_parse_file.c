#include "../inc/pipex.h"

int file_parser(char *infile, char *outfile, t_info *info);

int file_parser(char *infile, char *outfile, t_info *info)
{
    char *err_head;

	if (info->here_doc == True)
		return (EXIT_SUCCESS);
    info->in_fd = open(infile, O_RDONLY);
	if (info->in_fd == -1)
	{
		info->is_valid_infile = False;
		err_head = gen_errmsg_head(info->shell_name, infile);
		perror(err_head);
		free(err_head);
	}
	info->out_fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (info->out_fd == -1)
	{
		info->is_valid_outfile = False;
		err_head = gen_errmsg_head(info->shell_name, outfile);
		perror(err_head);
		free(err_head);
	}
	return (EXIT_SUCCESS);
}
