#include "libft.h"

void *ft_memchr(const void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char *)s;
    unsigned char c_cpy = (unsigned char)c;
    while (*p != c_cpy && n)
    {
        p++;
        n--;
    }
    if (n == 0)
        return (NULL);
    return (void *)(p);
}
