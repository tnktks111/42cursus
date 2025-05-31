#include "pipex.h"

char *ft_getenv(const char *varname);

char *ft_getenv(const char *varname)
{
    int fd;
    char *s;
    char *res;
    int var_len;

    var_len = ft_strlen(varname);
    fd = open("/proc/self/environ", O_RDONLY);
    if (fd == -1)
        return (NULL);
    s = get_next_line_for_getenv(fd);
    while (s)
    {
        if (ft_strncmp(s, varname, var_len) == 0)
        {
            res = ft_strdup(s + (var_len + 1));
            if (!res)
                return (NULL);
            free(s);
            return (res);
        }
        free(s);
        s = get_next_line_for_getenv(fd);
    }
    return (NULL);
}

//receive an allocated path and return last section(ex. "/bin/bash" -> "bash")
char *get_last_section(char *path)
{
    int i;
    char *res;

    i = ft_strlen(path);
    while (i > 0 && path[i] != '/')
        i--;
    res = ft_strdup(path + i + 1);
    if (!res)
        return (NULL);
    free(path);
    return (res);
}

// // cc -Wall -Wextra -Werror ft_getenv.c -Lget_next_line -Llibft -lft -lgnl
// int main(void)
// {
//     char *pathvar;
//     char *pathvar2;

//     pathvar = get_last_section(ft_getenv("SHELL"));
//     pathvar2 = getenv("SHELL");
//     printf("ft_getenv:\n%s\n",pathvar);
//     printf("getenv:\n%s\n",pathvar2);
// }