#include "libft.h"

void *ft_memset(void *s, int c, size_t n)
{
    size_t rest = n;
    char *cur = (char *)s;
    while (rest)
    {
        *cur++ = (char)c;
        rest--;
    }
    return (s);
}

// #include <stdio.h>
// int main()
// {
//     char buf1[16];
//     ft_memset(buf1, '\0', 16);
//     ft_memset(buf1, 'a', 4);
//     printf("%s\n", buf1);
//     char buf2[16];
//     memset(buf2, '\0', 16);
//     memset(buf2, 'a', 4);
//     printf("%s\n", buf2);
// }
