#include "pipex.h"
void file_parser(char *infile, char *outfile, t_info *info);

void file_parser(char *infile, char *outfile, t_info *info)
{
    char *err_head;
    info->in_fd = open(infile, O_RDONLY);
    info->out_fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (info->in_fd == -1)
    {
        info->is_valid_infile = False;
        err_head = gen_errmsg_head(info->shell_name, infile);
        perror(err_head);
        free(err_head);
    }
	if (info->out_fd == -1)
	{
		if (access(outfile, W_OK) == -1)
		{
			info->is_valid_outfile = False;
			err_head = gen_errmsg_head(info->shell_name, outfile);
			perror(err_head);
			free(err_head);
		}
	}
}