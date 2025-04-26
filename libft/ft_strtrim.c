#include "libft.h"

static int *init_seen(int *seen, char const *set)
{
    size_t i;
    i = 0;
    while (i < 256)
        seen[i++] = 0;
    i = 0;
    while (set[i])
        seen[(unsigned char)set[i++]] = 1;
    return (seen);
}

char *ft_strtrim(char const *s1, char const *set)
{
    int seen[256];
    size_t i;
    size_t j;
    size_t len;
    char *newstr;

    init_seen(seen, set);
    i = 0;
    j = 0;
    len = 0;
    while (s1[i])
        if (seen[(unsigned char)s1[i++]])
            j += 1;
    len = i - j;
    newstr = malloc(len + 1);
    if (!newstr)
        return (NULL);
    newstr[len] = '\0';
    i = 0;
    j = 0;
    while (i < len)
    {
        while (seen[(unsigned char)s1[i + j]])
            j++;
        newstr[i] = s1[i + j];
        i++;
    }
    return (newstr);
}