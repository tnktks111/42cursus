#include "libft.h"

static size_t ft_min(size_t s1, size_t s2)
{
    if (s1 < s2)
        return s1;
    else
        return s2;
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    size_t i;
    char *subs;
    size_t sub_len;

    sub_len = ft_min(ft_strlen(s), len);
    if (start >= ft_strlen(s))
        sub_len = 0;
    subs = malloc(sub_len + 1);
    if (!subs)
        return (NULL);
    subs[sub_len] = '\0';
    i = 0;
    while (i < sub_len)
    {
        subs[i] = s[start + i];
        i++;
    }
    return (subs);
}
