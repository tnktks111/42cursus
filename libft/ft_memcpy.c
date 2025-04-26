#include "libft.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    char *p1 = (char *)dest;
    const char *p2 = (const char *)src;
    while (n)
    {
        *p1++ = *p2++;
        n--;
    }
    return (dest);
}