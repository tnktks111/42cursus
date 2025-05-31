#include "pipex.h"

char *gen_errmsg_head(char *shell, char *nxtarg);
char *gen_command_path(char *prefix, char *command_name);
char *gen_errmsg_cmd_not_found(char *shell_name, char *cmd_name);

//ex. shell = "bash", file = "infile" -> res = "bash: infile"
char *gen_errmsg_head(char *shell, char *nxtarg)
{
    char *tmp1;
    char *res;
    tmp1 = ft_strjoin(shell, ": ");
    if (!tmp1)
        return (NULL);
    res = ft_strjoin(tmp1, nxtarg);
    free(tmp1);
    if (!res)
        return (NULL);
    return (res);
}

char *gen_command_path(char *prefix, char *command_name)
{
    char *tmp;
    char *res;

    tmp = ft_strjoin(prefix, "/");
    if(!tmp)
        return (NULL);
    res = ft_strjoin(tmp, command_name);
    free(tmp);
    return (res);
}

char *gen_errmsg_cmd_not_found(char *shell_name, char *cmd_name)
{
    char *tmp;
    char *res;
    tmp = gen_errmsg_head(shell_name, cmd_name);
    res = ft_strjoin(tmp, ": command not found");
    free(tmp);
    if (!res)
        return (NULL);
    return (res);
}