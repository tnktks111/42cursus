#include "pipex.h"
void init_info(t_info *info);

void init_info(t_info *info)
{
    char *env_path;

    info->shell_name = get_last_section(ft_getenv("SHELL"));
    info->is_valid_infile = True;
	info->is_valid_outfile = True;
    env_path = ft_getenv("PATH");
    info->command_path_prefixs = ft_split(env_path, ':');
    free(env_path);
}