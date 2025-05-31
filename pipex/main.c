#include "pipex.h"
int main(int argc, char *argv[])
{
    t_info info;
    (void)argc;
    init_info(&info);
    file_parser(argv[1], argv[argc - 1], &info);
    exec_n_commands(argc, argv, &info);
    return (EXIT_SUCCESS);
}