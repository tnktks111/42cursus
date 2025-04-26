#include "libft.h"

char *ft_strrchr(const char *s, int c)
{
    char *res = NULL;
    char c_cpy = (char)c;
    while (*s)
    {
        if (*s == c_cpy)
            res = (char *)s;
        s++;
    }
    if (c_cpy == '\0')
        res = (char *)s;
    return (res);
}

// #include <stdio.h>
// int main()
// {
//     char *s = "Hello World";
//     printf("%s", ft_strrchr(s, 0));
// }