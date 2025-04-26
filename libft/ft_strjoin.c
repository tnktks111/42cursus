#include "libft.h"

char *ft_strjoin(char const *s1, char const *s2)
{
    char *newstr;
    size_t s1_len = ft_strlen(s1);
    size_t s2_len = ft_strlen(s2);

    newstr = malloc(s1_len + s2_len + 1);
    if (!newstr)
        return (NULL);
    ft_strlcpy(newstr, s1, s1_len + 1);
    ft_strlcpy(&newstr[s1_len], s2, s2_len + 1);
    return (newstr);
}