#ifndef PIPEX_H
#define PIPEX_H
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

typedef enum e_bool
{
    False, True
} t_bool;

typedef struct s_info
{
    char *shell_name;
    int in_fd;
    int out_fd;
    t_bool is_valid_infile;
	t_bool is_valid_outfile;
    char **command_path_prefixs;
} t_info;

char *ft_getenv(const char *varname);
char *get_last_section(char *path);

char *gen_errmsg_head(char *shell, char *nxtarg);
char *gen_command_path(char *prefix, char *command_name);
char *gen_errmsg_cmd_not_found(char *shell_name, char *cmd_name);

void file_parser(char *infile, char *outfile, t_info *info);

void init_info(t_info *info);

int exec_commands(char *command1, char *command2, t_info *info);
int exec_n_commands(int argc, char *argv[], t_info *info);

#endif