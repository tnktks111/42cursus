#include "libft.h"

char *ft_strchr(const char *s, int c)
{
    char *p = (char *)s;
    char c_cpy = (char)c;
    while (*p && *p != c_cpy)
        p++;
    if (*p == '\0' && c_cpy != '\0')
        p = NULL;
    return (p);
}

// #include <stdio.h>
// int main()
// {
//     char s[] = "Hello World";
//     printf("%s",ft_strchr(s, 'H' + 256));
// }