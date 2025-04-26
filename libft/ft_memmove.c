#include <string.h>
void *ft_memmove(void *dst, const void *src, size_t len)
{
    char *dst_cpy;
    char *src_cpy;
    size_t i;
    dst_cpy = (char *)dst;
    src_cpy = (char *)src;
    if (!len || dst == src)
        return (dst);
    if (dst_cpy < src_cpy)
    {
        i = 0;
        while (i < len)
        {
            dst_cpy[i] = src_cpy[i];
            i++;
        }
    }
    else
    {
        while (len > 0)
        {
            len--;
            dst_cpy[len] = src_cpy[len];
        }
    }
    return (dst);
}