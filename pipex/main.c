#include "pipex.h"
int main(int argc, char *argv[])
{
    t_info info;
    init_info(argc, &info);
	heredoc_checker(argc, argv, &info);
    file_parser(argv[1], argv[argc - 1], &info);
    exec_n_commands(argv, &info);
    return (EXIT_SUCCESS);
}