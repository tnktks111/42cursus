#include "pipex.h"
int main(int argc, char *argv[])
{
    t_info info;
    (void)argc;
    init_info(&info);
    file_parser(argv[1], argv[4], &info);
    exec_commands(argv[2], argv[3], &info);
    return (EXIT_SUCCESS);
}