#include "libft.h"

char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t i;
    size_t j;

    i = 0;
    if (!(*needle))
        return (char *)(haystack);
    while (i < len && haystack[i])
    {
        if (haystack[i] == needle[0])
        {
            j = 0;
            while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
                j++;
            if (!needle[j] && i + j <= len)
                return (char *)(&haystack[i]);
        }
        i++;
    }
    return (NULL);
}
