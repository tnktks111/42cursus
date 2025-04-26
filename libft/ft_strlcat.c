#include "libft.h"

size_t ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t i;
    size_t j;
    
    i = 0;
    j = 0;
    while (dst[i])
        i++;
    if (dstsize > i)
    {
        while (j < dstsize - i - 1 && src[j])
        {
            dst[i + j] = src[j];
            j++;
        }
        dst[i + j] = '\0';
        while (src[j])
            j++;
    }
    j = ft_strlen(src);
    if (i >= dstsize)
        return (dstsize + j);
    else
        return (i + j);
}