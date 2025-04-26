#include "libft.h"

char *ft_strdup(const char *s1)
{
    char *dst;
    size_t i;
    size_t len;
    if (!s1)
        return (NULL);
    i = 0;
    len = ft_strlen(s1);
    dst = malloc(len + 1);
    if (!dst)
        return (NULL);
    dst[len] = '\0';
    while (i < len)
    {
        dst[i] = s1[i];
        i++;
    }
    return (dst);
}
