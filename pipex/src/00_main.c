#include "../inc/pipex.h"

static void init_info(int argc, t_info *info, char *envp[]);
static void heredoc_checker(int argc, char *argv[], t_info *info);
int main(int argc, char *argv[], char *envp[]);

static void init_info(int argc, t_info *info, char *envp[])
{
    char *env_path;

    info->envp = envp;
	info->size = argc - 3;
    info->shell_name = get_last_section(ft_getenv("SHELL", info->envp));
	info->here_doc = False;
    info->is_valid_infile = True;
	info->is_valid_outfile = True;
    env_path = ft_getenv("PATH", envp);
    info->command_path_prefixs = ft_split(env_path, ':');
    free(env_path);
}

static void heredoc_checker(int argc, char *argv[], t_info *info)
{
	if (ft_strncmp(argv[1], "here_doc", 8) != 0)
		return;
	info->here_doc = True;
	info->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	info->limiter = argv[2];
}

void free_resources(t_info *info)
{
    if (info->here_doc == False)
        close(info->in_fd);
    close(info->out_fd);
    free(info->shell_name);
    free_splited_data(info->command_path_prefixs);
}

int main(int argc, char *argv[], char *envp[])
{
    t_info info;

    if (argc < 5 || (argc < 6 && ft_strncmp(argv[1], "here_doc", 8) != 0))
        return (notify_invalid_format());
    init_info(argc, &info, envp);
	heredoc_checker(argc, argv, &info);
    if (file_parser(argv[1], argv[argc - 1], &info) == EXIT_FAILURE)
    {
        free_resources(&info);
        return (EXIT_FAILURE);
    }
    if (exec_n_commands(argv, &info) == EXIT_FAILURE)
    {
        free_resources(&info);
        return (EXIT_FAILURE);
    }
    free_resources(&info);
    return (EXIT_SUCCESS);
}
